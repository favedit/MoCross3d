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

MO_NAMESPACE_INCLUDE;

//============================================================
// <T>加载动态库。</T>
//
// @param hInstance 实例句柄
// @param reason 加载类型
// @param pReserved 保留字
// @return 类名
//============================================================
TInt32 main(TChar** pArguments, TInt count){
   TString fileName = TC("D:/Resource/xiong/xiong.fbx");
   //TString targetFileName = TC("D:/Microbject/MoCloud3d/Script/source/ar3/model/xiong.model");
   //TString targetConfigName = TC("D:/Microbject/MoCloud3d/Script/source/ar3/model/xiong.xml");
   TString targetFileName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.model");
   TString targetConfigName = TC("D:/Microbject/MoTypeScript/Script/res/model/xiong/xiong.xml");
   // 初始化处理
   MoInitialize();
   // 打开场景
   FModelScene* pScene = RModelManager::SafeInstance().OpenScene(fileName);
   // 存储资源
   FFbxResModel* pModel = MO_CREATE(FFbxResModel);
   pScene->Store(pModel);
   pModel->SaveFile(targetFileName);
   pModel->SaveConfigFile(targetConfigName);
   // 释放处理
   MO_DELETE(pScene);
   MoRelease();
   // getchar();
   return 0;
}
