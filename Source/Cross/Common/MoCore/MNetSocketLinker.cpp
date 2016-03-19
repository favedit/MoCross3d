#include "MoCrNetLinker.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����˿������������ࡣ</T>
//============================================================
MNetSocketLinker::MNetSocketLinker(){
   _socketType = -1;
}

//============================================================
// <T>�����˿������������ࡣ</T>
//============================================================
MNetSocketLinker::~MNetSocketLinker(){
}

//============================================================
// <T>�������Ӵ���</T>
//
// @return ������
//============================================================
TBool MNetSocketLinker::OnSocketConnect(){
   MO_DEBUG(TC("Socket linker connected. (type=%s)"), SocketName());
   return ETrue;
}

//============================================================
// <T>����Ͽ�����</T>
//
// @return ������
//============================================================
TBool MNetSocketLinker::OnSocketDisconnect(){
   MO_DEBUG(TC("Socket linker disconnected. (type=%s)"), SocketName());
   return ETrue;
}

//============================================================
// <T>��ö˿����ơ�</T>
//
// @return ����
//============================================================
TCharC* MNetSocketLinker::SocketName(){
   return TC("SocketLinker");
}

//============================================================
// <T>��ö˿����͡�</T>
//
// @return ����
//============================================================
TInt MNetSocketLinker::SocketType(){
   return _socketType;
}

MO_NAMESPACE_END
