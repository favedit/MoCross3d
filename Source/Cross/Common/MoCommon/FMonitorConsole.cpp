#include "MoCmMonitor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������������̨��</T>
//============================================================
FMonitorConsole::FMonitorConsole(){
   _machine = FMonitorMachine::InstanceCreate();
   MO_CLEAR(_pThread);
}

//============================================================
// <T>��������������̨��</T>
//============================================================
FMonitorConsole::~FMonitorConsole(){
}

//============================================================
// <T>ע���������</T>
//
// @param pMonitor ������
//============================================================
TResult FMonitorConsole::Register(IMonitor* pMonitor){
   MO_CHECK(pMonitor, return ENull);
   TResult resultCd = _machine->Register(pMonitor);
   return resultCd;
}

//============================================================
// <T>ע����������</T>
//
// @param pMonitor ������
//============================================================
TResult FMonitorConsole::Unregister(IMonitor* pMonitor){
   MO_CHECK(pMonitor, return ENull);
   TResult resultCd = _machine->Unregister(pMonitor);
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FMonitorConsole::Startup(){
   MO_CHECK(!_pThread, return EFailure);
   // ���������
   _machine->Startup();
   // ���������߳�
   _pThread = MO_CREATE(FMonitorThread);
   _pThread->SetMachine(_machine);
   _pThread->Start();
   return ESuccess;
}

//============================================================
// <T>ִ�д���</T>
//
// @return ������
//============================================================
TResult FMonitorConsole::Execute(){
   _machine->Execute();
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FMonitorConsole::Shutdown(){
   MO_ASSERT(_pThread);
   _pThread->Stop();
   return ESuccess;
}

MO_NAMESPACE_END
