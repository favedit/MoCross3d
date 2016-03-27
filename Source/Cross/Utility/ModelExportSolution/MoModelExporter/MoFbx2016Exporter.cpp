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

//============================================================
// <T>���ض�̬�⡣</T>
//
// @param hInstance ʵ�����
// @param reason ��������
// @param pReserved ������
// @return ����
//============================================================
TInt32 main(TInt argumentsCount, TChar** pArguments){
   // ��ȡ����
   if(argumentsCount != 3){
      return -1;
   }
   TString sourceFileName = pArguments[1];
   TString targetFileName = pArguments[2];
   // ���Բ���
   //TString sourceFileName = TC("D:/Resource/xiong/xiong.fbx");
   //TString targetFileName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.model");
   //TString targetConfigName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.xml");
   //TString sourceFileName = TC("D:/MoProject/Resource/demo/model/fd-pvw-չʾ/fd-sc.house.01-����չʾ.01 (2LDK)/md-001-����չʾ/model.fbx");
   //TString targetFileName = TC("D:/MoProject/Asset/demo/model/pvw.sc.house.01.001.model");

   // ��ʼ������
   MoInitialize();
   MO_STATIC_DEBUG("Source file: [%s]", sourceFileName);
   MO_STATIC_DEBUG("Target file: [%s]", targetFileName);
   // �򿪳���
   FModelScene* pScene = RModelManager::SafeInstance().OpenScene(sourceFileName);
   // �洢��Դ
   FFbxResModel* pModel = MO_CREATE(FFbxResModel);
   pScene->Store(pModel);
   pModel->SaveFile(targetFileName);
   // �ͷŴ���
   MO_DELETE(pScene);
   MoRelease();
   // getchar();
   return 0;
}
