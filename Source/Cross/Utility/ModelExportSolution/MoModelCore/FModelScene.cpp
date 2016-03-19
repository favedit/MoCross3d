#include "MoModelParser.h"
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

MO_NAMESPACE_BEGIN;

//============================================================
// <T>����FBX������</T>
//============================================================
FModelScene::FModelScene() {
   MO_CLEAR(_pManager);
   // MO_CLEAR(_pFbxScene);
   _pMeshs = MO_CREATE(FModelMeshs);
}

//============================================================
// <T>����FBX������</T>
//============================================================
FModelScene::~FModelScene() {
   // �ͷ���������
   if(_pMeshs != NULL){
      TInt count = _pMeshs->Count();
      for(TInt n = 0; n < count; n++){
         FModelMesh* pMesh = _pMeshs->Get(n);
         MO_DELETE(pMesh);
      }
      MO_DELETE(_pMeshs);
   }
   // MO_DESTORY(_pFbxScene);
   MO_CLEAR(_pManager);
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FModelScene::Setup(){
   //FbxManager* pFbxManager = _pManager->FbxManager();
   //_pFbxScene = FbxScene::Create(pFbxManager, "");
   return ESuccess;
}

//============================================================
// <T>����ڵ㴦��</T>
//============================================================
TResult FModelScene::ProcessMesh(const aiScene* pAiScene, const aiNode* pAiNode, const aiMesh* pAiMesh){
   // ��������
   FModelMesh* pMesh = MO_CREATE(FModelMesh);
   pMesh->SetScene(this);
   pMesh->SetAiNode(pAiNode);
   pMesh->SetAiMesh(pAiMesh);
   pMesh->Setup();
   _pMeshs->Push(pMesh);
   return ESuccess;
}

//============================================================
// <T>�ڵ㴦��</T>
//============================================================
TResult FModelScene::ProcessNode(const aiScene* pAiScene, const aiNode* pAiNode){
   // ������Ϣ
   aiString name = pAiNode->mName;
   TInt meshCount = pAiNode->mNumMeshes;
   TInt nodeCount = pAiNode->mNumChildren;
   MO_DEBUG("Process node %s. (child_count=%d, mesh_count=%d)", name.C_Str(), nodeCount, meshCount);
   // �������񼯺�
   for(TInt i = 0; i < meshCount; i++){
      TInt meshIndex = pAiNode->mMeshes[i];
      aiMesh* pAiMesh = pAiScene->mMeshes[meshIndex];
      ProcessMesh(pAiScene, pAiNode, pAiMesh);
   }
   // �����ӽڵ㼯��
   for(int i = 0; i < nodeCount; i++){
      aiNode* pAiChild = pAiNode->mChildren[i];
      ProcessNode(pAiScene, pAiChild);
   }
   return ESuccess;
}

//============================================================
// <T>���л����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FModelScene::Store(FFbxResModel* pResModel){
   MO_ASSERT_POINTER(pResModel);
   // ��������
   pResModel->SetCode(_code);
   // �������񼯺�
   TInt meshCount = _pMeshs->Count();
   for(TInt n = 0; n < meshCount; n++){
      FModelMesh* pFbxMesh = _pMeshs->Get(n);
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
TResult FModelScene::LoadFile(TCharC* pFileName){
   MO_ASSERT_POINTER(pFileName);
   // ���볡��
   Assimp::Importer import;
   const aiScene* pAiScene = import.ReadFile(pFileName, aiProcess_Triangulate | aiProcess_FlipUVs);
   // ����ڵ�
   ProcessNode(pAiScene, pAiScene->mRootNode);
   //// ��������
   //TFileInfo fileInfo = pFileName;
   //_code = fileInfo.Code();
   //// ��ò���
   //FbxManager* pFbxManager = _pManager->FbxManager();
   //FbxIOSettings* pFbxIoSettings = _pManager->FbxIoSettings();
   //SFbxSdkVersion& managerVersion = _pManager->Version();
   //TString8 fileName;
   //fileName.Assign16(pFileName);
   //// ����������
   //FbxImporter* pImporter = FbxImporter::Create(pFbxManager, NULL);
   //TBool initializeStatusCd = pImporter->Initialize(fileName.MemoryC(), -1, pFbxIoSettings);
   //if(!initializeStatusCd){
   //   MO_FATAL(TC("Open fbx file failure. (file_name={1})"), pFileName);
   //}
   //// ���볡��
   //_pFbxScene->Clear();
   //TBool importStatusCd = pImporter->Import(_pFbxScene);
   //if (!importStatusCd) {
   //   MO_FATAL(TC("Import fbx scene failure. (file_name={1})"), pFileName);
   //}
   //// �ͷŵ�����
   //MO_DESTORY(pImporter);
   //// ����ڵ�
   //FbxNode* pRootNode = _pFbxScene->GetRootNode();
   //ProcessNode(pRootNode);
   return ESuccess;
}

MO_NAMESPACE_END;
