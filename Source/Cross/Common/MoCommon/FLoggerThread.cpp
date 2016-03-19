#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������־ˢ���̡߳�</T>
//============================================================
FLoggerThread::FLoggerThread(){
   // Ĭ�ϼ��Ϊ1��
   _interval = 1000;
   MO_CLEAR(_pWriters);
}

//============================================================
// <T>������־ˢ���̡߳�</T>
//============================================================
FLoggerThread::~FLoggerThread(){
}

//============================================================
// <T>ˢ�´���</T>
//
// @return ������
//============================================================
TResult FLoggerThread::Process(){
   while(!IsStop()){
      // ˢ��������־�����
      _locker.Enter();
      TListIteratorC<ILoggerWriter*> iterator = _pWriters->IteratorC();
      while(iterator.Next()){
         iterator->Refresh();
      }
      _locker.Leave();
      // ���ߴ���
      Sleep((TInt)_interval);
   }
   return ESuccess;
}

MO_NAMESPACE_END
