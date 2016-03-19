#include <fcntl.h>
#ifdef _MO_LINUX
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include "MoCmNet.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FNetServerSocket, FInstance);

//============================================================
// <T>���������·�˿ڡ�</T>
//
// @return ������·�˿�
//============================================================
FNetServerSocket::FNetServerSocket(){
   RType<SNetSocketInfo>::Clear(&_info);
}

//============================================================
// <T>���������·�˿ڡ�</T>
//
// @param port �˿�
// @return ������·�˿�
//============================================================
FNetServerSocket::FNetServerSocket(TInt port){
   RType<SNetSocketInfo>::Clear(&_info);
   _info.port = port;
}

//============================================================
// <T>���������������ӡ�</T>
//============================================================
FNetServerSocket::~FNetServerSocket(){
   if(INVALID_SOCKET != _info.handle){
      Disconnect();
   }
}

//============================================================
// <T>�������˿���Ϣ��</T>
//
// @return ����˿���Ϣ
//============================================================
SNetSocketInfo* FNetServerSocket::Info(){
   return &_info;
}

//============================================================
// <T>�󶨷���˿ڡ�</T>
//
// @return ������
//============================================================
TResult FNetServerSocket::Bind(){
   // ��������
   _info.handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(INVALID_SOCKET == _info.handle){
      MO_PERROR(socket);
      return EFailure;
   }
   // ������
   struct sockaddr_in address;
   address.sin_family = AF_INET;
   if(_host.IsEmpty()){
      address.sin_addr.s_addr = htonl(INADDR_ANY);
   }else if(_host.Equals(TC("*"))){
      address.sin_addr.s_addr = htonl(INADDR_ANY);
   }else{
#ifdef _UNICODE
#else
      address.sin_addr.s_addr = inet_addr((TCharC*)_host);
#endif
   }   
   address.sin_port = htons(_info.port);
   memset(address.sin_zero, 0, sizeof(address.sin_zero));
   // �趨����
   TUint32 value = ETrue;
   if(EError == setsockopt(_info.handle, SOL_SOCKET, SO_REUSEADDR, (PChar8)&value, sizeof(TUint32))){
      MO_PERROR(setsockopt);
      return EFailure;
   }
   // ������
   TInt result = bind(_info.handle, (struct sockaddr*)&address, sizeof(struct sockaddr_in));
   if(SOCKET_ERROR == result){
      MO_ERROR(TC("Tcp server socket bind failure. (host=%s:%d)"), (TCharC*)_host, _info.port);
      MO_PFATAL(socket);
      return EFailure;
   }
   MO_DEBUG(TC("Tcp server socket bind success. (host=%s:%d)"), (TCharC*)_host, _info.port);
   return ESuccess;
}

//============================================================
// <T>��������˿ڡ�</T>
//
// @return ������
//============================================================
TResult FNetServerSocket::Listen(){
   TInt result = listen(_info.handle, SOMAXCONN);
   if(SOCKET_ERROR == result){
      MO_PERROR(socket);
      return EFailure;
   }
   MO_DEBUG(TC("Tcp server socket listen success. (host=%s:%d)"), (TCharC*)_host, _info.port);
   return ESuccess;
}

//============================================================
// <T>���ӷ���</T>
//
// @return ������
//============================================================
TResult FNetServerSocket::Connect(){
   TResult result = Bind();
   if(result == ESuccess){
      result = Listen();
   }
   return result;
}

//============================================================
// <T>���տͻ����ӡ�</T>
//
// @param pInfo ������Ϣ
// @return ������
//============================================================
TResult FNetServerSocket::Accept(SNetAcceptInfo* pInfo){
   MO_CHECK(pInfo, return ENull);
   // ���ն˿�
   sockaddr_in address;
#ifdef _MO_WINDOWS
   int size = sizeof(struct sockaddr_in);
#else
   socklen_t size = sizeof(struct sockaddr_in);
#endif
   TInt handle = accept(_info.handle, (struct sockaddr*)&address, &size);
   if(handle > 0){
      // �ɹ�������
      pInfo->handle = handle;
      pInfo->ip = address.sin_addr.s_addr;
      pInfo->port = address.sin_port;
      TChar8C* pHost = inet_ntoa(address.sin_addr);
#ifdef _MO_UNICODE
      TFsCode host;
      host.Assign8(pHost);
      MO_LIB_STRING_COPY(pInfo->host, host.Length() + 1, host.MemoryC());
#else
      MO_LIB_STRING_COPY(pInfo->host, sizeof(pInfo->host), inet_ntoa(address.sin_addr));
#endif // _MO_UNICODE
      return ESuccess;
   }else{
      // ������
      if(_isBlock){
         MO_PFATAL(accept);
         return EFailure;
      }
   }
   return ESuccess;
}

//============================================================
// <T>�Ͽ�����</T>
//
// @return ������
//============================================================
TResult FNetServerSocket::Disconnect(){
   return Close();
}

MO_NAMESPACE_END
