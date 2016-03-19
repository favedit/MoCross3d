#include "MoCrNetTransfer.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������Ϣ������׽����</T>
//============================================================
FNetTransferCatcher::FNetTransferCatcher(){
   _name = TC("transfer.trap.catcher");
}

//============================================================
// <T>��װ������Ϣ������׽����</T>
//============================================================
TBool FNetTransferCatcher::Install(){
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
