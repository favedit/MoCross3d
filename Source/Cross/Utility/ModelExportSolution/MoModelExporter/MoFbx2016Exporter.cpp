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
TInt32 main(TChar** pArguments, TInt count){
   TString fileName = TC("D:/Resource/xiong/xiong.fbx");
   //TString targetFileName = TC("D:/Microbject/MoCloud3d/Script/source/ar3/model/xiong.model");
   //TString targetConfigName = TC("D:/Microbject/MoCloud3d/Script/source/ar3/model/xiong.xml");
   TString targetFileName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.model");
   TString targetConfigName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.xml");
   // ��ʼ������
   MoInitialize();
   // �򿪳���
   FModelScene* pScene = RModelManager::SafeInstance().OpenScene(fileName);
   // �洢��Դ
   FFbxResModel* pModel = MO_CREATE(FFbxResModel);
   pScene->Store(pModel);
   pModel->SaveFile(targetFileName);
   pModel->SaveConfigFile(targetConfigName);
   // �ͷŴ���
   MO_DELETE(pScene);
   MoRelease();
   // getchar();
   return 0;
}
