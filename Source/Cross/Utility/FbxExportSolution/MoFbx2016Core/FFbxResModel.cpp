#include "MoFbxResource.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>����FBX������</T>
//============================================================
FFbxResModel::FFbxResModel(){
   _typeName = TC("Model");
   _guid = RGuid::Generate();
   _pMeshs = MO_CREATE(FFbxResMeshs);
}

//============================================================
// <T>����FBX������</T>
//============================================================
FFbxResModel::~FFbxResModel() {
   MO_DELETE(_pMeshs);
}

//============================================================
// <T>���л��ڲ����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FFbxResModel::Serialize(IDataOutput * pOutput){
   FFbxResource::Serialize(pOutput);
   // ������񼯺�
   TInt meshCount = _pMeshs->Count();
   pOutput->WriteInt32((TInt32)meshCount);
   for(TInt n = 0; n < meshCount; n++){
      FFbxResModelMesh* pMesh = _pMeshs->Get(n);
      pMesh->Serialize(pOutput);
   }
   // �����������
   pOutput->WriteInt32((TInt32)0);
   // �����������
   pOutput->WriteInt32((TInt32)0);
   return ESuccess;
}

//============================================================
// <T>�����ڲ����ݵ����ýڵ㡣</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FFbxResModel::SaveConfig(FXmlNode* pConfig){
   FFbxResource::SaveConfig(pConfig);
   pConfig->Set(TC("guid"), _guid);
   FXmlNode* pXmlAsset = pConfig->CreateNode(TC("Asset"));
   // ����������
   pXmlAsset->CreateNode(TC("Cameras"));
   // �����Դ����
   pXmlAsset->CreateNode(TC("Lights"));
   // ���λͼ����
   pXmlAsset->CreateNode(TC("Bitmaps"));
   // ������ʼ���
   pXmlAsset->CreateNode(TC("Materials"));
   // �����ʾ����
   FXmlNode* pXmlDisplays = pXmlAsset->CreateNode(TC("Displays"));
   FXmlNode* pXmlDisplay = pXmlDisplays->CreateNode(TC("Entity"));
   pXmlDisplay->Set(TC("guid"), (TCharC*)RGuid::Generate());
   pXmlDisplay->Set(TC("model_guid"), _guid);
   pXmlDisplay->Set(TC("model_code"), _code);
   // ������񼯺�
   FXmlNode* pXmlMeshs = pXmlDisplay->CreateNode(TC("Renderables"));
   TInt meshCount = _pMeshs->Count();
   for(TInt n = 0; n < meshCount; n++){
      FFbxResModelMesh* pMesh = _pMeshs->Get(n);
      FXmlNode* pXmlMesh = pXmlMeshs->CreateNode();
      pMesh->SetGuid(RGuid::Generate());
      pMesh->SaveConfig(pXmlMesh);
      pXmlMesh->SetName(TC("Renderable"));
      pXmlMesh->Set(TC("mesh_guid"), (TCharC*)RGuid::Generate());
      pXmlMesh->Set(TC("material_guid"), (TCharC*)RGuid::Generate());
   }
   // �������
   FXmlNode* pXmlStage = pConfig->CreateNode(TC("Stage"));
   pXmlStage->Set(TC("active_chapter"), TC("default"));
   FXmlNode* pXmlScenes = pXmlStage->CreateNode(TC("Scenes"));
   FXmlNode* pXmlScene = pXmlScenes->CreateNode(TC("Scene"));
   pXmlScene->Set(TC("code"), TC("default"));
   pXmlScene->Set(TC("active_region"), TC("default"));
   FXmlNode* pXmlRegions = pXmlScene->CreateNode(TC("Regions"));
   FXmlNode* pXmlRegion = pXmlRegions->CreateNode(TC("Region"));
   pXmlRegion->Set(TC("code"), TC("default"));
   pXmlRegion->CreateNode(TC("Technique"));
   pXmlRegion->CreateNode(TC("Viewports"));
   pXmlRegion->CreateNode(TC("DirectionalLight"));
   pXmlRegion->CreateNode(TC("Lights"));
   FXmlNode* pXmlLayers = pXmlScene->CreateNode(TC("Layers"));
   FXmlNode* pXmlLayer = pXmlLayers->CreateNode(TC("Layer"));
   FXmlNode* pXmlLayerSprite = pXmlLayer->CreateNode(TC("Sprite"));
   pXmlLayerSprite->Set(TC("guid"), (TCharC*)RGuid::Generate());
   pXmlLayerSprite->Set(TC("template_guid"), pXmlDisplay->Get(TC("guid")));
   return ESuccess;
}

//============================================================
// <T>�洢�ļ���</T>
//
// @param pFileName �ļ�����
// @return ������
//============================================================
TResult FFbxResModel::SaveFile(TCharC* pFileName){
   MO_ASSERT_POINTER(pFileName);
   FByteFile* pFile = MO_CREATE(FByteFile);
   pFile->EnsureSize(1024 * 1024);
   Serialize(pFile);
   pFile->SaveFile(pFileName);
   MO_DELETE(pFile);
   return ESuccess;
}

//============================================================
// <T>�洢�����ļ���</T>
//
// @param pFileName �ļ�����
// @return ������
//============================================================
TResult FFbxResModel::SaveConfigFile(TCharC* pFileName){
   MO_ASSERT_POINTER(pFileName);
   FXmlDocument* pDocument = MO_CREATE(FXmlDocument);
   FXmlNode* pRoot = pDocument->Root();
   SaveConfig(pRoot);
   pDocument->SaveFile(pFileName);
   MO_DELETE(pDocument);
   return ESuccess;
}

MO_NAMESPACE_END;
