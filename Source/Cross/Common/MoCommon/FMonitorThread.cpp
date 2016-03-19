#include "MoCmMonitor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������̡߳�</T>
//============================================================
FMonitorThread::FMonitorThread(){
}

//============================================================
// <T>�����������̡߳�</T>
//============================================================
FMonitorThread::~FMonitorThread(){
}

//============================================================
// <T>��������������̡߳�</T>
//
// @return ������
//============================================================
TResult FMonitorThread::Process(){
   // �������
   TTimeSpan interval = _machine->Interval();
   // ѭ������
   while(!IsStop()){
      // ��������
      _machine->Process();
      // ����
      MO_LIB_SLEEP(interval);
   }
   return ESuccess;
}

MO_NAMESPACE_END
