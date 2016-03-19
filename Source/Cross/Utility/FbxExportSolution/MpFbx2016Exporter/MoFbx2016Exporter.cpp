//============================================================
//   DYNAMIC LINK LIBRARY : Mo3DSExporter Project Overview
//------------------------------------------------------------
// ��3DS MAX�е���ģ�͵Ķ�̬���ӿ⡣
//------------------------------------------------------------
// Copyright From MAOCY
// 2010-05-02 (^o^)
//============================================================

#include <MoCommon.h>
#include <MoFbx2016Core.h>
#include "MpFbxDefine.h"

MO_NAMESPACE_INCLUDE;
MO_NAMESPACE_USING(FBXSDK_NAMESPACE);

void ProcessNode(FbxNode* pNode){
   TChar8C* pName = pNode->GetName();
   printf("%s\n", pName);
   //FbxNodeAttribute::EType attributeType;
   //if(pNode->GetNodeAttribute()){
   //   switch(pNode->GetNodeAttribute()->GetAttributeType()){
   //      case KFbxNodeAttribute::eMESH:
   //         //ProcessMesh(pNode);
   //         break;
   //      case KFbxNodeAttribute::eSKELETON:
   //         //ProcessSkeleton(pNode);
   //         break;
   //      case KFbxNodeAttribute::eLIGHT:
   //         //ProcessLight(pNode);
   //         break;
   //      case KFbxNodeAttribute::eCAMERA:
   //         //ProcessCamera();
   //         break;
   //   }
   //}
   TInt nodeCount = pNode->GetChildCount();
   for(TInt32 i = 0; i < nodeCount; i++){
      FbxNode* pChildNode = pNode->GetChild(i);
      ProcessNode(pChildNode);
   }
}


//============================================================
// <T>���ض�̬�⡣</T>
//
// @param hInstance ʵ�����
// @param reason ��������
// @param pReserved ������
// @return ����
//============================================================
TInt32 main(TChar** pArguments, TInt count){
   TString fileName = TC("D:/Resource/xiong/xiong.fbx");
   //TString targetFileName = TC("D:/Microbject/MoCloud3d/Script/source/ar3/model/xiong.model");
   //TString targetConfigName = TC("D:/Microbject/MoCloud3d/Script/source/ar3/model/xiong.xml");
   TString targetFileName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong.model");
   TString targetConfigName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong.xml");
   // ��ʼ������
   MoInitialize();
   // ����������
   FFbxManager* pManager = MO_CREATE(FFbxManager);
   pManager->Setup();
   // ��������
   FFbxScene* pScene = MO_CREATE(FFbxScene);
   pScene->SetManager(pManager);
   pScene->Setup();
   pScene->LoadFile(fileName);
   // �洢��Դ
   FFbxResModel* pModel = MO_CREATE(FFbxResModel);
   pScene->Store(pModel);
   pModel->SaveFile(targetFileName);
   pModel->SaveConfigFile(targetConfigName);
   // �ͷŴ���
   MO_DELETE(pScene);
   MO_DELETE(pManager);
   MoRelease();
   // getchar();
   return 0;
}
