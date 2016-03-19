#include "MoCmThread.h"
#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����̳߳صĹ�������</T>
//
// @param pPool �����
// @return �̳߳صĹ�������
//============================================================
FThreadWorker::FThreadWorker(){
   _typeCd = EThread_Worker;
   MO_CLEAR(_pPool);
   _busy = EFalse;
   _stop = EFalse;
   _interval = 1000; // 1����
#ifdef _MO_DEBUG
   _timeout = 60000000; // Ĭ���߳�����1����
#else
   _timeout = 600000000; // Ĭ���߳�����10����
#endif
   _freeDate = 0;
}

//============================================================
// <T>ִ�д���</T>
//
// @return ִ�н��
//============================================================
TBool FThreadWorker::TestTimeout(TDateTime current){
   if(!_busy){
      if(0 != _freeDate){
         TTimeSpan span = current - _freeDate;
         if(span > _timeout){
            return ETrue;
         }
      }
   }
   return EFalse;
}

//============================================================
// <T>ִ�д���</T>
//
// @return ������
//============================================================
TResult FThreadWorker::OnProcess(){
   return ESuccess;
}

//============================================================
// <T>ִ�д���</T>
//
// @return ������
//============================================================
TResult FThreadWorker::Process(){
   // ��鹤����
   MO_ASSERT(_pPool);
   // �����߼�
   while(!_stop){
      // ִ�д���
      TInt resultCd = ESuccess;
      if(_busy){
         resultCd = OnProcess();
         _busy = EFalse;
      }
      if(ESuccess != resultCd){
         MO_ERROR(TC("Thread worker process faliure. (result=%d)"), resultCd);
      }
      // �ع����
      _pPool->DoWait(this);
   }
   return ESuccess;
}

//============================================================
// <T>������Ϣ��</T>
//
// @param pTrack �ַ���
// @return ִ�н��
//============================================================
TBool FThreadWorker::Track(MString* pTrack){
   pTrack->AppendFormat(TC("%s"), (TCharC*)_name);
   return ETrue;
}

MO_NAMESPACE_END
