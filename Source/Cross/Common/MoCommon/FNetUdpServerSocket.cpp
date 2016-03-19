#include <fcntl.h>
#ifdef _MO_LINUX
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include "MoCmNet.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������·�˿ڡ�</T>
//
// @return ������·�˿�
//============================================================
FNetUdpServerSocket::FNetUdpServerSocket(){
   RType<SNetSocketInfo>::Clear(&_info);
}

//============================================================
// <T>���������·�˿ڡ�</T>
//
// @param port �˿�
// @return ������·�˿�
//============================================================
FNetUdpServerSocket::FNetUdpServerSocket(TInt port){
   RType<SNetSocketInfo>::Clear(&_info);
   _info.port = port;
}

//============================================================
// <T>���������������ӡ�</T>
//============================================================
FNetUdpServerSocket::~FNetUdpServerSocket(){
   if(INVALID_SOCKET != _info.handle){
      Disconnect();
   }
}

//============================================================
SNetSocketInfo* FNetUdpServerSocket::Info(){
   return &_info;
}

//============================================================
// <T>�󶨷���˿ڡ�</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetUdpServerSocket::Bind(){
   // ��������
   _info.handle = socket(AF_INET, SOCK_DGRAM, 0);
   if(INVALID_SOCKET == _info.handle){
      MO_PERROR(socket);
      return EFalse;
   }
   // ������
   struct sockaddr_in address;
   address.sin_family = AF_INET;
   if(_host.IsEmpty()){
      address.sin_addr.s_addr = htonl(INADDR_ANY);
   }else{
#ifdef _UNICODE
#else
      address.sin_addr.s_addr = inet_addr((TCharC*)_host);
#endif
   }
   address.sin_port = htons(_info.port);
   memset(address.sin_zero, 0, sizeof(address.sin_zero));
#ifdef _MO_DEBUG
   // �趨����
   TUint32 value = ETrue;
   if(EError == setsockopt(_info.handle, SOL_SOCKET, SO_REUSEADDR, (PChar8)&value, sizeof(TUint32))){
      MO_PERROR(setsockopt);
      return EFalse;
   }
#endif
   // ������
   TInt result = bind(_info.handle, (struct sockaddr*)&address, sizeof(struct sockaddr_in));
   if(SOCKET_ERROR == result){
      MO_ERROR(TC("Udp server socket bind failure. (host=%s:%d)"), (TCharC*)_host, _info.port);
      MO_PFATAL(socket);
      return EFalse;
   }
   MO_DEBUG(TC("Udp server socket bind success. (host=%s:%d)"), (TCharC*)_host, _info.port);
   return ETrue;
}

//============================================================
// <T>���ӷ���</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetUdpServerSocket::Connect(){
   return Bind();
}

//============================================================
// <T>�Ͽ�����</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetUdpServerSocket::Disconnect(){
   return Close();
}

MO_NAMESPACE_END
