#include "MoModelParser.h"
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

MO_NAMESPACE_BEGIN;

//============================================================
// <T>构造FBX场景。</T>
//============================================================
FModelScene::FModelScene() {
   MO_CLEAR(_pManager);
   // MO_CLEAR(_pFbxScene);
   _pMeshs = MO_CREATE(FModelMeshs);
}

//============================================================
// <T>析构FBX场景。</T>
//============================================================
FModelScene::~FModelScene() {
   // 释放所有网格
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
// <T>配置处理。</T>
//============================================================
TResult FModelScene::Setup(){
   //FbxManager* pFbxManager = _pManager->FbxManager();
   //_pFbxScene = FbxScene::Create(pFbxManager, "");
   return ESuccess;
}

//============================================================
// <T>网格节点处理。</T>
//============================================================
TResult FModelScene::ProcessMesh(const aiScene* pAiScene, const aiNode* pAiNode, const aiMesh* pAiMesh){
   // 创建网格
   FModelMesh* pMesh = MO_CREATE(FModelMesh);
   pMesh->SetScene(this);
   pMesh->SetAiNode(pAiNode);
   pMesh->SetAiMesh(pAiMesh);
   pMesh->Setup();
   _pMeshs->Push(pMesh);
   return ESuccess;
}

//============================================================
// <T>节点处理。</T>
//============================================================
TResult FModelScene::ProcessNode(const aiScene* pAiScene, const aiNode* pAiNode){
   // 处理信息
   aiString name = pAiNode->mName;
   TInt meshCount = pAiNode->mNumMeshes;
   TInt nodeCount = pAiNode->mNumChildren;
   MO_DEBUG("Process node %s. (child_count=%d, mesh_count=%d)", name.C_Str(), nodeCount, meshCount);
   // 处理网格集合
   for(TInt i = 0; i < meshCount; i++){
      TInt meshIndex = pAiNode->mMeshes[i];
      aiMesh* pAiMesh = pAiScene->mMeshes[meshIndex];
      ProcessMesh(pAiScene, pAiNode, pAiMesh);
   }
   // 处理子节点集合
   for(int i = 0; i < nodeCount; i++){
      aiNode* pAiChild = pAiNode->mChildren[i];
      ProcessNode(pAiScene, pAiChild);
   }
   return ESuccess;
}

//============================================================
// <T>序列化数据到输出流。</T>
//
// @param pOutput 输出流
// @return 处理结果
//============================================================
TResult FModelScene::Store(FFbxResModel* pResModel){
   MO_ASSERT_POINTER(pResModel);
   // 设置属性
   pResModel->SetCode(_code);
   // 设置网格集合
   TInt meshCount = _pMeshs->Count();
   for(TInt n = 0; n < meshCount; n++){
      FModelMesh* pFbxMesh = _pMeshs->Get(n);
      // 创建网格
      FFbxResModelMesh* pResMesh = MO_CREATE(FFbxResModelMesh);
      pFbxMesh->Store(pResMesh);
      pResModel->Meshs()->Push(pResMesh);
   }
   return ESuccess;
}

//============================================================
// <T>加载文件。</T>
//
// @param pFileName 文件名称
// @return 处理结果
//============================================================
TResult FModelScene::LoadFile(TCharC* pFileName){
   MO_ASSERT_POINTER(pFileName);
   // 导入场景
   Assimp::Importer import;
   const aiScene* pAiScene = import.ReadFile(pFileName, aiProcess_Triangulate | aiProcess_FlipUVs);
   // 处理节点
   ProcessNode(pAiScene, pAiScene->mRootNode);
   //// 设置名称
   //TFileInfo fileInfo = pFileName;
   //_code = fileInfo.Code();
   //// 获得参数
   //FbxManager* pFbxManager = _pManager->FbxManager();
   //FbxIOSettings* pFbxIoSettings = _pManager->FbxIoSettings();
   //SFbxSdkVersion& managerVersion = _pManager->Version();
   //TString8 fileName;
   //fileName.Assign16(pFileName);
   //// 创建导入器
   //FbxImporter* pImporter = FbxImporter::Create(pFbxManager, NULL);
   //TBool initializeStatusCd = pImporter->Initialize(fileName.MemoryC(), -1, pFbxIoSettings);
   //if(!initializeStatusCd){
   //   MO_FATAL(TC("Open fbx file failure. (file_name={1})"), pFileName);
   //}
   //// 导入场景
   //_pFbxScene->Clear();
   //TBool importStatusCd = pImporter->Import(_pFbxScene);
   //if (!importStatusCd) {
   //   MO_FATAL(TC("Import fbx scene failure. (file_name={1})"), pFileName);
   //}
   //// 释放导入器
   //MO_DESTORY(pImporter);
   //// 处理节点
   //FbxNode* pRootNode = _pFbxScene->GetRootNode();
   //ProcessNode(pRootNode);
   return ESuccess;
}

MO_NAMESPACE_END;
