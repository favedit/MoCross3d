//============================================================
//   DYNAMIC LINK LIBRARY : Mo3DSExport Project Overview
//------------------------------------------------------------
// ��3DS MAX�е���ģ�͵Ķ�̬���ӿ⡣
// - �ڲ�û�е�������ֻ��һ���ſ⡣
// - Ŀ�����ڲ���Ҫ����3DS MAX���������£����¶�̬���ر�����Ķ�̬�⡣
//  ������������һ��DLL(Mo3DSExporter)�ṩ��
//------------------------------------------------------------
// Copyright From MAOCY
// 2010-05-02 (^o^)
//============================================================

#include "MoFbxDefine.h"
#include "MoFbxParser.h"

MO_NAMESPACE_INCLUDE;

//============================================================
// <T>���ض�̬�⡣</T>
//
// @param hInstance ʵ���ӱ�
// @param reason ����ԭ��
// @param pReserved ����
// @return ����
//============================================================
/*TBool WINAPI DllMain(TInstance hInstance, TUint32 reason, TAny* pReserved){
   switch(reason){
      // ���̿�ʼ����
      case DLL_PROCESS_ATTACH:{
         DisableThreadLibraryCalls(hInstance);
         //MoInitialize();
         break;
      }
      // �߳̿�ʼ����
      case DLL_THREAD_ATTACH:
         break;
      // �߳̽�������
      case DLL_THREAD_DETACH:
         break;
      // ���̽�������
      case DLL_PROCESS_DETACH:{
         //MoRelease();
         break;
      }
   }
   return ETrue;
}
*/