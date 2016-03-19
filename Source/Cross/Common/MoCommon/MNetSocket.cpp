#include <fcntl.h>
#ifdef _MO_LINUX
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include "MoCmNet.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����·�˿ڡ�</T>
//============================================================
MNetSocket::MNetSocket(){
   MO_CLEAR(_pConnection);
   _isConnected = EFalse;
   _isBlock = ETrue;
}

//============================================================
// <T>������·�˿ڡ�</T>
//============================================================
MNetSocket::~MNetSocket(){
}

//============================================================
// <T>�ж��Ƿ����ӡ�</T>
//
// @return �Ƿ�����
//============================================================
TBool MNetSocket::IsConnected(){
   return _isConnected;
}

//============================================================
// <T>�����·���ӡ�</T>
//
// @return ��·����
//============================================================
INetConnection* MNetSocket::Connection(){
   return _pConnection;
}

//============================================================
// <T>�������ӡ�</T>
//
// @param pConnection ����
//============================================================
void MNetSocket::SetConnection(INetConnection* pConnection){
   _pConnection = pConnection;
}

//============================================================
// <T>��÷��ͱ�־��</T>
//
// @return ���ͱ�־
//============================================================
TBool MNetSocket::SendFlag(){
   return Info()->sendFlag;
}

//============================================================
// <T>���÷��ͱ�־��</T>
//
// @param flag ���ͱ�־
//============================================================
void MNetSocket::SetSendFlag(TBool flag){
   Info()->sendFlag = flag;
}

//============================================================
// <T>�����·�˿ھ����</T>
//
// @return �˿ھ��
//============================================================
TSocket MNetSocket::Handle(){
   return Info()->handle;
}

//============================================================
// <T>���þ����</T>
//
// @param handle ���
//============================================================
void MNetSocket::SetHandle(TSocket handle){
   Info()->handle = handle;
   _isConnected = ETrue;
}

//============================================================
// <T>�����·�������ơ�</T>
//
// @return ��������
//============================================================
TCharC* MNetSocket::Host(){
   return _host;
}

//============================================================
// <T>������ӵ�ַ��</T>
//
// @return ���ӵ�ַ
//============================================================
TUint32 MNetSocket::Ip(){
   return Info()->ip;
}

//============================================================
// <T>�����������ơ�</T>
//
// @param host ��������
//============================================================
void MNetSocket::SetHost(TCharC* pHost){
   _host.Assign(pHost);
}

//============================================================
// <T>������Ӷ˿ڡ�</T>
//
// @return ���Ӷ˿�
//============================================================
TUint16 MNetSocket::Port(){
   return Info()->port;
}

//============================================================
// <T>���ö˿ڡ�</T>
//
// @param port �˿�
//============================================================
void MNetSocket::SetPort(TUint16 port){
   Info()->port = port;
}

//============================================================
// <T>��ô���ʱ�䡣</T>
//
// @return ����ʱ��
//============================================================
TDateTime MNetSocket::CreateDateTime(){
   return Info()->createDateTime;
}

//============================================================
// <T>���ô������ڡ�</T>
//
// @param datetime ��������
//============================================================
void MNetSocket::SetCreateDateTime(TDateTime datetime){
   Info()->createDateTime = datetime;
}

//============================================================
// <T>�����������þ����</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::SetReuseAddress(TBool flag){
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
   TUint32 value = flag;
   if(EError == setsockopt(handle, SOL_SOCKET, SO_REUSEADDR, (PChar8)&value, sizeof(TUint32))){
      MO_PERROR(setsockopt);
      return EFalse;
   }
   MO_NET_DEBUG(TC("Set reuse address. (handle=%d, host=%s:%d, flag=%d)"),
         handle, pInfo->host, pInfo->port, flag);
   return ETrue;
}

//============================================================
// <T>�������̽�����</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::SetDontLinger(TBool flag){
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
   struct linger value;
   value.l_onoff = EFalse;
   value.l_linger = 0;
   if(EError == setsockopt(handle, SOL_SOCKET, SO_LINGER, (PChar8)&value, sizeof(struct linger))){
      MO_PERROR(setsockopt);
      return EFalse;
   }
   MO_NET_DEBUG(TC("Set don't linger. (handle=%d, host=%s:%d, flag=%d)"),
         handle, pInfo->host, pInfo->port, flag);
   return ETrue;
}

//============================================================
// <T>�����������������ݡ�</T>
//
// @param flag ������
// @param time ����ʱ��
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::SetLinger(TBool flag, TInt timeout){
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
   struct linger value;
   value.l_onoff = (TUint16)flag;
   value.l_linger = timeout;
   if(EError == setsockopt(handle, SOL_SOCKET, SO_LINGER, (PChar8)&value, sizeof(struct linger))){
      MO_PERROR(setsockopt);
      return EFalse;
   }
   MO_NET_DEBUG(TC("Set linger. (handle=%d, host=%s:%d, flag=%d, timeout=%d)"),
         handle, pInfo->host, pInfo->port, flag, timeout);
   return ETrue;
}

//============================================================
// <T>���÷��ͳ�ʱ��</T>
//
// @param timeout ��ʱ(΢������1/1000000��)
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::SetSendTimeout(TInt timeout){
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
   struct timeval value;
   value.tv_sec = timeout / 1000000;
   value.tv_usec = timeout % 1000000;
   if(EError == setsockopt(handle, SOL_SOCKET, SO_SNDTIMEO, (PChar8)&value, sizeof(struct timeval))){
      MO_PERROR(setsockopt);
      return EFalse;
   }
   MO_NET_DEBUG(TC("Set send timeout. (handle=%d, host=%s:%d, timeout=%d)"),
         handle, pInfo->host, pInfo->port, timeout);
   return ETrue;
}

//============================================================
// <T>���ý��ճ�ʱ��</T>
//
// @param timeout ��ʱ(1/1000��)
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::SetReceiveTimeout(TInt timeout){
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
   struct timeval value;
   value.tv_sec = timeout / 1000000;
   value.tv_usec = timeout % 1000000;
   if(EError == setsockopt(handle, SOL_SOCKET, SO_RCVTIMEO, (PChar8)&value, sizeof(struct timeval))){
      MO_PERROR(setsockopt);
      return EFalse;
   }
   MO_NET_DEBUG(TC("Set receive timeout. (handle=%d, host=%s:%d, timeout=%d)"),
         handle, pInfo->host, pInfo->port, timeout);
   return ETrue;
}

//============================================================
// <T>���÷��ͻ�������С��</T>
//
// @param size ��������С
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::SetSendBufferSize(TInt size){
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
   TUint32 value = size;
   TInt result = setsockopt(handle, SOL_SOCKET, SO_SNDBUF, (PChar8)&value, sizeof(TUint32));
   if(result < 0){
      MO_PERROR(setsockopt);
      return EFalse;
   }
   MO_NET_DEBUG(TC("Set send buffer size. (handle=%d, host=%s:%d, size=%d)"),
         handle, pInfo->host, pInfo->port, size);
   return ETrue;
}

//============================================================
// <T>���ý��ջ�������С��</T>
//
// @param size ��������С
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::SetReceiveBufferSize(TInt size){
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
   TUint32 value = size;
   if(EError == setsockopt(handle, SOL_SOCKET, SO_RCVBUF, (PChar8)&value, sizeof(TUint32))){
      MO_PERROR(setsockopt);
      return EFalse;
   }
   MO_NET_DEBUG(TC("Set receive buffer size. (handle=%d, host=%s:%d, size=%d)"),
         handle, pInfo->host, pInfo->port, size);
   return ETrue;
}

//============================================================
// <T>���÷Ƕ�����ʽ��</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::SetNonBlock(){
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
#ifdef _MO_WINDOWS
   TDword argp = 1;
   ioctlsocket(handle, FIONBIO, &argp);
#else
   fcntl(handle, F_SETFL, O_NONBLOCK);
#endif // _MO_WINDOWS
   _isBlock = EFalse;
   MO_NET_DEBUG(TC("Set none block. (handle=%d, host=%s:%d)"),
         handle, pInfo->host, pInfo->port);
   return ETrue;
}

//============================================================
// <T>�������ݡ�</T>
//
// @param pBuffer ����ָ��
// @param length ���ݳ���
// @return ���ճ���
//============================================================
TInt MNetSocket::Receive(TByte* pBuffer, TInt length){
   SNetSocketInfo* pInfo = Info();
   TInt result = recv(pInfo->handle, (TChar8*)pBuffer, length, 0);
   if(result < 0){
      TInt code = errno;
      if(ESuccess == code){
         return 0;
      }else if(EINTR == code){
         return 0;
      }else if(EAGAIN == code){
         return 0;
      }else if(EBADF == code){
         // TODO:
         return 0;
      }else if(ESuccess != code){
         MO_ERROR(TC("Receive data failure. (handle=%d, host=%s:%d)"),
               pInfo->handle, pInfo->host, pInfo->port);
      }
   }else if(result > 0){
       pInfo->receiveTotal += result;
       pInfo->receiveDateTime = RDateTime::Current();
   }
   return result;
}

//============================================================
// <T>�������ݡ�</T>
//
// @param pBuffer ����ָ��
// @param length ���ݳ���
// @return ���ͳ���
//============================================================
TInt MNetSocket::Send(TByteC* pBuffer, TInt length){
   MO_ASSERT(pBuffer);
   MO_ASSERT(length > 0);
   SNetSocketInfo* pInfo = Info();
   TSocket handle = pInfo->handle;
   TInt result = send(handle, (TChar8C*)pBuffer, length, 0);
   if(result < 0){
      // ������
      TInt code = errno;
      if((EINTR == code) || (EAGAIN == code) || (EWOULDBLOCK == code)){
         // ������
      }else if((ENOTSOCK == code) || (ENOENT == code) || (EPIPE == code) ||
            (ECONNRESET == code) || (EDESTADDRREQ == code) || (EACCES == code)){
         // ʧ�����
         MO_ERROR(TC("Send data failure. (handle=%d, host=%s:%d, error_code=%d)"),
               handle, pInfo->host, pInfo->port, code);
      }else{
         MO_ERROR(TC("Send data error. (handle=%d, host=%s:%d, error_code=%d)"),
               handle, pInfo->host, pInfo->port, code);
      }
   }else if(result > 0){
       pInfo->sendTotal += result;
       pInfo->sendDateTime = RDateTime::Current();
   }
   return result;
}

//============================================================
// <T>�ر����ӡ�</T>
//
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool MNetSocket::Close(){
   _isConnected = EFalse;
   TSocket handle = Handle();
   if(INVALID_SOCKET != handle){
#ifdef _MO_WINDOWS
      closesocket(handle);
#else
      TInt result = close(handle);
      if(0 != result){
         MO_PERROR(close);
      }
#endif
      handle = INVALID_SOCKET;
      return ETrue;
   }
   return EFalse;
}

MO_NAMESPACE_END
