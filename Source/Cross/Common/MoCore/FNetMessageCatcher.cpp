#include "MoCrNetConnection.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������Ϣ������׽����</T>
//============================================================
FNetMessageCatcher::FNetMessageCatcher(){
   _name = TC("message.trap.catcher");
}

//============================================================
// <T>��װ������Ϣ������׽����</T>
//============================================================
TBool FNetMessageCatcher::Install(){
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
