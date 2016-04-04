//============================================================
//   DYNAMIC LINK LIBRARY : Mo3DSExporter Project Overview
//------------------------------------------------------------
// 从3DS MAX中导出模型的动态链接库。
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
// <T>加载动态库。</T>
//
// @param hInstance 实例句柄
// @param reason 加载类型
// @param pReserved 保留字
// @return 类名
//============================================================
TInt32 main(TInt argumentsCount, TChar** pArguments){
#ifdef __TEST__2
   // 调试参数
   //TString sourceFileName = TC("D:/Resource/xiong/xiong.fbx");
   //TString targetFileName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.model");
   //TString targetConfigName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.xml");
   TString sourceFileName = TC("D:/MoProject/Resource/demo/model/fd-pvw-展示/fd-sc.car.01-场景.汽车.01/md-001-汽车.奥迪/model.fbx");
   TString targetFileName = TC("D:/MoProject/Asset/demo/model/pvw.sc.car.01.001.model");
#else
   // 获取参数
   if(argumentsCount != 3){
      return -1;
   }
   TString sourceFileName = pArguments[1];
   TString targetFileName = pArguments[2];
#endif // __TEST__
   // 设置语言
   setlocale(LC_ALL, "chs");
   // 初始化处理
   MoInitialize();
   MO_STATIC_DEBUG(TC("Source file: [%s]"), (TCharC*)sourceFileName);
   MO_STATIC_DEBUG(TC("Target file: [%s]"), (TCharC*)targetFileName);
   // 打开场景
   FModelScene* pScene = RModelManager::SafeInstance().OpenScene(sourceFileName);
   // 存储资源
   FFbxResModel* pModel = MO_CREATE(FFbxResModel);
   pScene->Store(pModel);
   pModel->SaveFile(targetFileName);
   // 释放处理
   MO_DELETE(pScene);
   MoRelease();
   // getchar();
   return 0;
}
