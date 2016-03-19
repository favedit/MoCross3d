#include "MoFbxParser.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>����FBX������</T>
//============================================================
FFbxScene::FFbxScene() {
   MO_CLEAR(_pManager);
   MO_CLEAR(_pFbxScene);
   _pMeshs = MO_CREATE(FFbxMeshs);
}

//============================================================
// <T>����FBX������</T>
//============================================================
FFbxScene::~FFbxScene() {
   // �ͷ���������
   if(_pMeshs != NULL){
      TInt count = _pMeshs->Count();
      for(TInt n = 0; n < count; n++){
         FFbxMesh* pMesh = _pMeshs->Get(n);
         MO_DELETE(pMesh);
      }
      MO_DELETE(_pMeshs);
   }
   MO_DESTORY(_pFbxScene);
   MO_CLEAR(_pManager);
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FFbxScene::Setup(){
   FbxManager* pFbxManager = _pManager->FbxManager();
   _pFbxScene = FbxScene::Create(pFbxManager, "");
   return ESuccess;
}

//============================================================
// <T>����ڵ㴦��</T>
//============================================================
TResult FFbxScene::ProcessMesh(FbxNode * pFbxNode){
   // �������
   FbxMesh* pFbxMesh = pFbxNode->GetMesh();
   if(pFbxMesh == NULL){
      return EFailure;
   }
   // ��������
   FFbxMesh* pMesh = MO_CREATE(FFbxMesh);
   pMesh->SetScene(this);
   pMesh->SetNodeHandle(pFbxNode);
   pMesh->Setup();
   _pMeshs->Push(pMesh);
   return ESuccess;
}

//============================================================
// <T>�ڵ㴦��</T>
//============================================================
TResult FFbxScene::ProcessNode(FbxNode * pFbxNode){
   // ��������Ϣ
   TString name;
   name.Assign8(pFbxNode->GetName());
   FbxNodeAttribute::EType typeCd = FbxNodeAttribute::eUnknown;
   TCharC* pTypeName = NULL;
   FbxNodeAttribute* pFbxNodeAttribute = pFbxNode->GetNodeAttribute();
   if(pFbxNodeAttribute != NULL){
      typeCd = pFbxNodeAttribute->GetAttributeType();
      pTypeName = RFbxEnum::ParseName(typeCd);
   }
   MO_DEBUG(TC("Process node. (name=%s, type=%d[%s])"), (TCharC*)name, typeCd, pTypeName);
   // ����������
   switch(typeCd){
      case FbxNodeAttribute::eMesh:
         ProcessMesh(pFbxNode);
         break;
      case FbxNodeAttribute::eSkeleton:
         //ProcessSkeleton(pFbxNode);
         break;
      case FbxNodeAttribute::eLight:
         //ProcessLight(pFbxNode);
         break;
      case FbxNodeAttribute::eCamera:
         //ProcessCamera(pFbxNode);
         break;
   }
   // �����ӽ�㼯��
   TInt nodeCount = pFbxNode->GetChildCount();
   for(TInt32 i = 0; i < nodeCount; i++){
      FbxNode* pChildNode = pFbxNode->GetChild(i);
      ProcessNode(pChildNode);
   }
   return ESuccess;
}

//============================================================
// <T>���л����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FFbxScene::Store(FFbxResModel* pResModel){
   MO_ASSERT_POINTER(pResModel);
   // ��������
   pResModel->SetCode(_code);
   // �������񼯺�
   TInt meshCount = _pMeshs->Count();
   for(TInt n = 0; n < meshCount; n++){
      FFbxMesh* pFbxMesh = _pMeshs->Get(n);
      // ��������
      FFbxResModelMesh* pResMesh = MO_CREATE(FFbxResModelMesh);
      pFbxMesh->Store(pResMesh);
      pResModel->Meshs()->Push(pResMesh);
   }
   return ESuccess;
}

//============================================================
// <T>�����ļ���</T>
//
// @param pFileName �ļ�����
// @return ������
//============================================================
TResult FFbxScene::LoadFile(TCharC* pFileName){
   MO_ASSERT_POINTER(pFileName);
   // ��������
   TFileInfo fileInfo = pFileName;
   _code = fileInfo.Code();
   // ��ò���
   FbxManager* pFbxManager = _pManager->FbxManager();
   FbxIOSettings* pFbxIoSettings = _pManager->FbxIoSettings();
   SFbxSdkVersion& managerVersion = _pManager->Version();
   TString8 fileName;
   fileName.Assign16(pFileName);
   // ����������
   FbxImporter* pImporter = FbxImporter::Create(pFbxManager, NULL);
   TBool initializeStatusCd = pImporter->Initialize(fileName.MemoryC(), -1, pFbxIoSettings);
   if(!initializeStatusCd){
      MO_FATAL(TC("Open fbx file failure. (file_name={1})"), pFileName);
   }
   // ��ð汾��
   SFbxSdkVersion version;
   pImporter->GetFileVersion(version.major, version.minor, version.revision);
   if(managerVersion.major < version.major){
      MO_FATAL(TC("Open fbx major version failure. (file_name={1})"), pFileName);
   }else if (managerVersion.minor < version.minor) {
      MO_FATAL(TC("Open fbx minor version failure. (file_name={1})"), pFileName);
   }
   // ���볡��
   _pFbxScene->Clear();
   TBool importStatusCd = pImporter->Import(_pFbxScene);
   if (!importStatusCd) {
      MO_FATAL(TC("Import fbx scene failure. (file_name={1})"), pFileName);
   }
   // �ͷŵ�����
   MO_DESTORY(pImporter);
   // ����ڵ�
   FbxNode* pRootNode = _pFbxScene->GetRootNode();
   ProcessNode(pRootNode);
   return ESuccess;
}

MO_NAMESPACE_END;
