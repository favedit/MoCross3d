#include <fcntl.h>
#ifdef _MO_LINUX
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include "MoCmNet.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FNetSocket, FInstance);

//============================================================
// <T>������·�˿ڡ�</T>
//============================================================
FNetSocket::FNetSocket(){
   RType<SNetSocketInfo>::Clear(&_info);
}

//============================================================
// <T>������·�˿ڡ�</T>
//
// @param host ��������
// @param port �˿�
// @param handle ���
//============================================================
FNetSocket::FNetSocket(TCharC* pHost, TInt port, TSocket handle){
   _host.Assign(pHost);
   _info.handle = handle;
   _info.port = port;
   _isConnected = ETrue;
}

//============================================================
// <T>������·�˿ڡ�</T>
//============================================================
FNetSocket::~FNetSocket(){
}

//============================================================
// <T>�������˿���Ϣ��</T>
//
// @return ����˿���Ϣ
//============================================================
SNetSocketInfo* FNetSocket::Info(){
   return &_info;
}

//============================================================
// <T>���ն˿����ݡ�</T>
//
// @param pInfo ������Ϣ
// @return ������
//============================================================
TResult FNetSocket::Accept(SNetAcceptInfo* pInfo){
   MO_CHECK(pInfo, return ENull);
   _host.Assign(pInfo->host);
   _info.handle = pInfo->handle;
   _info.port = pInfo->port;
   _isConnected = ETrue;
   return ESuccess;
}

MO_NAMESPACE_END
