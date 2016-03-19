#include "MoCmMonitor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���춨ʱ��������׽����</T>
//============================================================
FMonitorCatcher::FMonitorCatcher(){
   _name = TC("monitor.trap.catcher");
}

//============================================================
// <T>��װ��ʱ��������׽����</T>
//============================================================
TBool FMonitorCatcher::Install(){
#ifdef _MO_TRAP
   // ��׽�Ƿ���������
   Register(SIGILL);
   // ��׽�Ƿ���������
   Register(SIGTRAP);
   // ��׽�Ƿ���ַ����
   Register(SIGBUS);
   // ��׽����������
   Register(SIGFPE);
   // ��׽�Ƿ��ڴ�����
   Register(SIGSEGV);
#endif // _MO_TRAP
   return ETrue;
}

MO_NAMESPACE_END
