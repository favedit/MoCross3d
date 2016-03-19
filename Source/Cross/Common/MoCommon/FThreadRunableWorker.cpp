#include "MoCmThread.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����̳߳صĹ�������</T>
//
// @param pPool �����
// @return �̳߳صĹ�������
//============================================================
FThreadRunableWorker::FThreadRunableWorker(IThreadRunablePool* pPool){
   MO_ASSERT(pPool);
   _pPool = pPool;
   _stop = EFalse;
}

//============================================================
// <T>ִ�д���</T>
//
// @return ������
//============================================================
TResult FThreadRunableWorker::Process(){
   while(!_stop){
      // ִ�д���
      if(NULL != _runableHandle){
         (*_runableHandle)(this);
         MO_CLEAR(_runableHandle);
      }
      // ���𣬵ȴ���һ��ִ������
      Suspend();
   }
   return ESuccess;
}

MO_NAMESPACE_END
