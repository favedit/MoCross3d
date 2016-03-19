#include <fcntl.h>
#ifdef _MO_WINDOWS
#undef SetNetPort
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include "MoCmNet.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ͻ���·�˿ڡ�</T>
//
// @return �ͻ���·�˿�
//============================================================
FNetUdpClientSocket::FNetUdpClientSocket(){
   RType<SNetSocketInfo>::Clear(&_info);
}

//============================================================
// <T>����ͻ���·�˿ڡ�</T>
//
// @param host ��������
// @param port �˿�
// @return �ͻ���·�˿�
//============================================================
FNetUdpClientSocket::FNetUdpClientSocket(TCharC* pHost, TInt port){
   RType<SNetSocketInfo>::Clear(&_info);
   _host.Assign(pHost);
   _info.port = port;
}

//============================================================
// <T>�����ͻ���·�˿ڡ�</T>
//============================================================
FNetUdpClientSocket::~FNetUdpClientSocket(){
   if(INVALID_SOCKET != Handle()){
      Disconnect();
   }
}

//============================================================
SNetSocketInfo* FNetUdpClientSocket::Info(){
   return &_info;
}

//============================================================
// <T>����ָ����������</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetUdpClientSocket::Connect(){
   // ��������
   TSocket handle = socket(AF_INET, SOCK_DGRAM, 0);
   if(INVALID_SOCKET == handle){
      MO_PERROR(socket);
      return EFalse;
   }
   // ������
   struct sockaddr_in address;
   address.sin_family = AF_INET;
   address.sin_port = htons(_info.port);
#ifdef _UNICODE
#else
   address.sin_addr.s_addr = inet_addr((TCharC*)_host);
#endif
   memset(address.sin_zero, 0, sizeof(address.sin_zero));
   if(ESuccess != connect(handle, (struct sockaddr*)&address, sizeof(struct sockaddr_in))){
      MO_ERROR(TC("Connect socket error. (host=%s, port=%d)"), (TCharC*)_host, _info.port);
      MO_PERROR(connect);
      // �ر��Ѿ��򿪵����Ӿ��
#ifdef _MO_WINDOWS
      if(ESuccess != closesocket(handle)){
         MO_PERROR(closesocket);
      }
#else
      if(ESuccess != close(handle)){
         MO_PERROR(close);
      }
#endif
      return EFalse;
   }
   _info.handle = handle;
   _isConnected = ETrue;
   return ETrue;
}

//============================================================
TBool FNetUdpClientSocket::Connect(TCharC* pHost, TUint16 port){
   SetHost(pHost);
   SetPort(port);
   return Connect();
}

//============================================================
// <T>�Ͽ����ӡ�</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetUdpClientSocket::Disconnect(){
   _isConnected = EFalse;
   if(INVALID_SOCKET == _info.handle){
#ifdef _MO_WINDOWS
      closesocket(_info.handle);
#else
      close(_info.handle);
#endif
      _info.handle = INVALID_SOCKET;
      return ETrue;
   }
   return EFalse;
}

MO_NAMESPACE_END
