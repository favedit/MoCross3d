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

#define __TEST__

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
#ifdef __TEST__2
   // ���Բ���
   //TString sourceFileName = TC("D:/Resource/xiong/xiong.fbx");
   //TString targetFileName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.model");
   //TString targetConfigName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.xml");
   TString sourceFileName = TC("D:/MoProject/Resource/demo/model/fd-pvw-չʾ/fd-sc.car.01-����.����.01/md-001-����.�µ�/model.fbx");
   TString targetFileName = TC("D:/MoProject/Asset/demo/model/pvw.sc.car.01.001.model");
#else
   // ��ȡ����
   if(argumentsCount != 3){
      return -1;
   }
   TString sourceFileName = pArguments[1];
   TString targetFileName = pArguments[2];
#endif // __TEST__
   // ��������
   setlocale(LC_ALL, "chs");
   // ��ʼ������
   MoInitialize();
   MO_STATIC_DEBUG(TC("Source file: [%s]"), (TCharC*)sourceFileName);
   MO_STATIC_DEBUG(TC("Target file: [%s]"), (TCharC*)targetFileName);
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
