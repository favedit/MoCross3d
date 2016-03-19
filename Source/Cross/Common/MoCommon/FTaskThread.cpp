#include "MoCmTask.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������̡߳�</T>
//============================================================
FTaskThread::FTaskThread(){
   _name = TC("Task Thread");
   _interval = 10000;
   MO_CLEAR(_pTask);
}

//============================================================
// <T>���������̡߳�</T>
//============================================================
FTaskThread::~FTaskThread(){
}

//============================================================
// <T>ִ�д���</T>
//
// @return ������
//============================================================
TResult FTaskThread::Process(){
   while(!IsStop()){
      _pTask = _pConsole->PopTask();
      if(_pTask != NULL){
         _pTask->Process();
         MO_DELETE(_pTask);
      }
      SleepMicro(_interval);
   }
   return ESuccess;
}

MO_NAMESPACE_END
