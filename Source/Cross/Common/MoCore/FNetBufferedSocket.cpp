#include "MoCrNetEpoll.h"
#include "MoCrNetPipe.h"
#include "MoCrNetSocket.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲���������</T>
//============================================================
FNetBufferedSocket::FNetBufferedSocket(){
   // ������Ϣ
   RType<SNetBufferedSocket>::Clear(&_info);
   _info.receiveBufferSize = MO_SVC_SOCKET_RECEIVE;
   _info.sendBufferSize = MO_SVC_SOCKET_SEND;
   _processing = EFalse;
   // ���û���
   MO_CLEAR(_pReceivePool);
   MO_CLEAR(_pSendPool);
   // �����ܵ�
   _pInputPipe = MO_CREATE(FNetBufferedPipe);
   _pInputPipe->SetLockCd(EStreamLock_Unlock);
   _pOutputPipe = MO_CREATE(FNetBufferedPipe);
   _pOutputPipe->SetLockCd(EStreamLock_Unlock);
}

//============================================================
// <T>���������������</T>
//============================================================
FNetBufferedSocket::~FNetBufferedSocket(){
   MO_DELETE(_pInputPipe);
   MO_DELETE(_pOutputPipe);
}

//============================================================
// <T>����׽���Ϣ������ָ�롣</T>
//
// @return �׽�����Ϣ�����ָ���ָ��
//============================================================
SNetSocketInfo* FNetBufferedSocket::Info(){
   return &_info;
}

//============================================================
// <T>�����׽��ֵ���Ϣ��</T>
//
// @param pInfo �׽��ֵ���Ϣ�Ľṹ��ָ��
//============================================================
void FNetBufferedSocket::SetInfo(SNetSocketInfo* pInfo){
   MO_ASSERT(pInfo);
   memcpy(&_info, pInfo, sizeof(SNetSocketInfo));
   _host = pInfo->host;
}

//============================================================
// <T>�����ܵ��ֿ��ռ�����</T>
//
// @param pAllocator �ܵ��ֿ��ռ���
//============================================================
void FNetBufferedSocket::LinkAllocator(TInt capacity, FBufferedPipeBlockAllocator* pAllocator){
   // �������뻺��
   _pInputPipe->Pool()->SetCapacity(capacity);
   _pInputPipe->SetAllocator(pAllocator);
   // �����������
   _pOutputPipe->Pool()->SetCapacity(capacity);
   _pOutputPipe->SetAllocator(pAllocator);
}

//============================================================
// <T>��ȡ����˿����ݵ���ǰ�������ݹܵ���</T>
//
// @return ��ȡ��������,�������-1��ʶ�û������Ѿ��رա�
//============================================================
TInt FNetBufferedSocket::DoBufferReceive(){
   // ����Ƿ�����
   if(!_isConnected){
      return 0;
   }
   // ѭ����������
   TInt result = 0;
   while(ETrue){
      // ��ȡ����
      TByte buffer[MO_SVC_SOCKET_RECEIVE];
      TInt length = Receive(buffer, MO_SVC_SOCKET_RECEIVE);
      if(0 == length){
         // �ͻ����ѶϿ�
         result = -1;
         break;
      }else if(length > 0){
         // �������ݰ�
         MO_DEBUG(TC("Receive socket data. (handle=%d, host=%s:%d, length=%d)"),
               _info.handle, _info.host, _info.port, length);
         // TChar dump[MO_DUMP_MAXLENGTH];
         // MO_DEBUG("Receive socket data. (handle=%d, host=%s:%d, length=%d)\n%s",
         //       _gInfo->handle, _gInfo->host, _gInfo->port, length,
         //       RByte::Dump(buffer, length, dump, MO_DUMP_MAXLENGTH));
         // д�����ӵ�����ܵ�
         TInt lengthWrite;
         if(EStreamResult_Success != _pInputPipe->Write(buffer, length, &lengthWrite)){
            MO_ERROR(TC("Socket input queue is full. (length=%d, remain=%d)"), length, _pInputPipe->Length());
         }
         result += length;
         break;
      }else{
         // ������
         TInt code = errno;
         if((EINTR == code) || (EAGAIN == code) || (EWOULDBLOCK == code)){
            // �����������´μ�������
            break;
         }else if((ENOENT == code) || (ENOTSOCK == code) || (ECONNRESET == code)){
            // �쳣�������ر�����
            result = -1;
            break;
         }else{
            // ����������ر�����
            MO_ERROR(TC("Receive socket data unknown error. (handle=%d, host=%s:%d, length=%d, code=%d)"),
                  _info.handle, _info.host, _info.port, length, code);
            result = -1;
            break;
         }
      }
   }
   return result;
}

//============================================================
// <T>�ӵ�ǰ���ӵ�����ܵ��ж�ȡ���ݣ����͸�ָ������˿ڡ�</T>
//
// @return ��ȡ��������,�������-1��ʶ�û������Ѿ��رա�
//============================================================
TInt FNetBufferedSocket::DoBufferSend(){
   // ����Ƿ�����
   if(!_isConnected){
      return 0;
   }
   // ����Ƿ����Ҫ���͵�����
   if(0 == _pOutputPipe->Length()){
      return 0;
   }
   // ѭ����������
   TInt result = 0;
   while(ETrue){
      // ���Ҫ���͵�����
      TInt lengthPeek = 0;
      TByte buffer[MO_SVC_SOCKET_SEND];
      if(EStreamResult_Success != _pOutputPipe->Peek(buffer, MO_SVC_SOCKET_SEND, &lengthPeek)){
         break;
      }
      if(0 == lengthPeek){
         break;
      }
      // ��������
      TInt length = Send(buffer, lengthPeek);
      if(0 == length){
         // �ͻ����ѶϿ�
         result = -1;
         break;
      }else if(length > 0){
         MO_DEBUG(TC("Send socket buffer data. (handle=%d, host=%s:%d, peekLength=%d, sendLength=%d)"),
               _info.handle, _info.host, _info.port, lengthPeek, length);
         // ���Ѿ����͵����ݲ����Ƴ����͹ܵ�
         TInt lengthSend = 0;
         if(EStreamResult_Success != _pOutputPipe->Read(buffer, length, &lengthSend)){
            MO_ERROR(TC("Socket send buffer failure. (capacity=%d, length=%d)"), _pOutputPipe->Length(), length);
            result = -1;
            break;
         }
         result += length;
         // ���û��ȫ����������������뿪����ѭ��
         if(length != lengthPeek){
            break;
         }
      }else{
         // ������
         TInt code = errno;
         if((EINTR == code) || (EAGAIN == code) || (EWOULDBLOCK == code)){
            // ���ͳ������������´��ط�
            break;
         }else if((ENOTSOCK == code) || (ENOENT == code) || (EPIPE == code) ||
               (ECONNRESET == code) || (EDESTADDRREQ == code) || (EACCES == code)){
            // �Է��Ѿ��رգ���ǰ������Ҫ�ر�
            result = -1;
            break;
         }else{
            // ����������ر�����
            MO_ERROR(TC("Send socket data unknown error. (handle=%d, host=%s:%d, length=%d, code=%d)"),
                  _info.handle, _info.host, _info.port, length, code);
            result = -1;
            break;
         }
      }
   }
   return result;
}

//============================================================
// <T>�����������ӡ�</T>
//============================================================
TBool FNetBufferedSocket::Update(){
   _info.updateDateTime = RDateTime::Current();
   return ETrue;
}

//============================================================
// <T>��ʼ�������ӡ�</T>
//============================================================
TBool FNetBufferedSocket::Startup(){
   // ����Ƿ�����
   if(_processing){
      return EFalse;
   }
   // ��������
   TDateTime tick = RDateTime::Current();
   _isConnected = ETrue;
   _info.createDateTime = tick;
   _info.updateDateTime = tick;
   _info.receiveSerial = 0;
   _info.receiveDateTime = tick;
   _info.receiveTick = 0;
   _info.sendSerial = 0;
   _info.sendDateTime = tick;
   // ���û����С
   SetReceiveBufferSize(_info.receiveBufferSize);
   SetSendBufferSize(_info.sendBufferSize);
   // ���ӵ�����
#ifdef _MO_LINUX
#ifndef __CYGWIN__
   if(NULL != _pReceivePool){
      _pReceivePool->Add(this, EPOLLIN | EPOLLHUP | EPOLLERR);
   }
   if(NULL != _pSendPool){
      _pSendPool->Add(this, EPOLLOUT);
   }
#endif
#endif
   _processing = ETrue;
   return ETrue;
}

//============================================================
// <T>�ر��������ӡ�</T>
//============================================================
TBool FNetBufferedSocket::Shutdown(){
   // ����Ƿ�����
   if(!_processing){
      return EFalse;
   }
   // �ӳ���ɾ��
   if(NULL != _pReceivePool){
      _pReceivePool->Remove(this, 0);
      MO_CLEAR(_pReceivePool);
   }
   if(NULL != _pSendPool){
      _pSendPool->Remove(this, 0);
      MO_CLEAR(_pSendPool);
   }
   // ������Ϣ
   _pInputPipe->Reset();
   _pOutputPipe->Reset();
   // �رն���
   Close();
   _processing = EFalse;
   return ETrue;
}

MO_NAMESPACE_END
