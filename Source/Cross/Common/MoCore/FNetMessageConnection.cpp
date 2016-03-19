#ifdef _MO_LINUX
#include <unistd.h>
#endif
#include <MoCmStream.h>
#include <MoCmNet.h>
#include "MoCrNetConnection.h"

#define MO_MD_MESSAGE_WAIT_INTERVAL 1

MO_NAMESPACE_BEGIN

//============================================================
FNetMessageConnection::FNetMessageConnection(){
   _isConnected = EFalse;
   _isUdpConnected = EFalse;
   _pSocket = MO_CREATE(FNetClientSocket);
   _pUdpSocket = MO_CREATE(FNetUdpClientSocket);
   _pipeLength = 1024*32;
   _queueLength = 1024*64;
   MO_CLEAR(_pInputPipe);
   MO_CLEAR(_pInputQueue);
   MO_CLEAR(_pInputUdpQueue);
   MO_CLEAR(_pOutputPipe);
   MO_CLEAR(_pOuputQueue);
}

//============================================================
FNetMessageConnection::~FNetMessageConnection(){
   MO_DELETE(_pSocket);
   MO_DELETE(_pUdpSocket);
   MO_DELETE(_pInputPipe);
   MO_DELETE(_pInputQueue);
   MO_DELETE(_pInputUdpQueue);
   MO_DELETE(_pOutputPipe);
   MO_DELETE(_pOuputQueue);
};

//============================================================
TBool FNetMessageConnection::Create(){
   _pInputPipe = MO_CREATE(FPipe, _pipeLength);
   _pInputQueue = MO_CREATE(FQueue, _queueLength);
   _pInputUdpQueue = MO_CREATE(FQueue, _queueLength);
   _pOutputPipe = MO_CREATE(FPipe, _pipeLength);
   _pOuputQueue = MO_CREATE(FQueue, _queueLength);
   return ETrue;
}

//============================================================
TBool FNetMessageConnection::Connect(TCharC* pHost, TUint16 port){
   // ���ӷ�����
   _isConnected = _pSocket->Connect(pHost, port);
   return _isConnected;
}

//============================================================
TBool FNetMessageConnection::UdpConnect(TCharC* pHost, TUint16 port){
   // ���ӷ�����
   _isUdpConnected = _pUdpSocket->Connect(pHost, port);
   return _isUdpConnected;
}

//============================================================
TBool FNetMessageConnection::SetNonBlock(){
   MO_ASSERT(_isConnected);
   _pSocket->SetNonBlock();
   return ETrue;
}

//============================================================
TBool FNetMessageConnection::SetUdpNonBlock(){
   MO_ASSERT(_isUdpConnected);
   _pUdpSocket->SetNonBlock();
   return ETrue;
}

//============================================================
TBool FNetMessageConnection::Disconnect(){
   // �Ͽ�TCP����
   _pSocket->Disconnect();
   _isConnected = EFalse;
   // �Ͽ�UDP����
   _pUdpSocket->Disconnect();
   _isUdpConnected = EFalse;
   return ETrue;
}

//============================================================
TBool FNetMessageConnection::OnStartup(){
   return ETrue;
}

//============================================================
TBool FNetMessageConnection::AbandonReceiveMessages(){
   while(ETrue){
      // �ж��Ƿ���ڳ�������
      TUint32 length = (TUint32)_pInputPipe->Length();
      if(length <= sizeof(SNetHead)){
         break;
      }
      // �����Ƿ���������Ϣ
      TUint32 size = 0;;
      if(!_pInputPipe->TryPeek(&size, sizeof(TUint32))){
         break;
      }
      // ��Ϣ����һ��������
      if(length < size){
         break;
      }
      // ����һ����Ϣ
      TByte readBuffer[MO_NETMESSAGE_MAXLENGTH];
      _pInputPipe->Read(readBuffer, size);
   }
   return ETrue;
}

//============================================================
// <T>��ȡ�������ݣ�д����ջ��塣�����������������Ϣ�������д����Ϣ�ܵ���</T>
//
// @return ������
//============================================================
TBool FNetMessageConnection::ProcessTcpReceive(){
   // �����Ƿ��Ѿ�����
   if(!_isConnected){
      return EFalse;
   }
   // ��������
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   TInt received = _pSocket->Receive(buffer, MO_NETMESSAGE_MAXLENGTH);
   if(-1 == received){
      _pSocket->Disconnect();
      return EFalse;
   }
   if(received > 0){
      MO_DEBUG(TC("Receive socket tcp data. (length=%d)"), received);
      TBool result = _pInputPipe->TryWrite(buffer, received);
      if(!result){
         // �����Ѿ����յ���Ϣ
         AbandonReceiveMessages();
         // ����д������
         result = _pInputPipe->TryWrite(buffer, received);
         if(!result){
            MO_FATAL(TC("Input pipe buffer is full."));
         }
      }
   }
   // �ж��Ƿ���ڳ�������
   TUint32 length = (TUint32)_pInputPipe->Length();
   if(length <= sizeof(SNetHead)){
      return EFalse;
   }
   // �����Ƿ���������Ϣ
   TNetLength size = 0;;
   if(!_pInputPipe->TryPeek(&size, sizeof(TNetLength))){
      return EFalse;
   }
   // ��Ϣ����һ��������
   if(length < size){
      return EFalse;
   }
   // ������Ϣ�ܵ��Ƿ��ܷ��¸���Ϣ
   TUint32 remain = (TUint32)_pInputQueue->Reamin();
   if(remain < size){
      return EFalse;
   }
   // �����Ϣ���ݣ�д����Ϣ�ܵ�
   TByte readBuffer[MO_NETMESSAGE_MAXLENGTH];
   TInt readed = _pInputPipe->Read(readBuffer, size);
   if(readed <= 0){
      MO_ERROR(TC("Read pipe failure. (size=%d)"), size);
      return EFalse;
   }
   // �������ͷ��Ϣ
   SNetHead* pHead = (SNetHead*)readBuffer;
   if(ENetProtocol_Message != pHead->protocol){
      MO_FATAL(TC("Unknown net head protocol. (protocol=%d)"), pHead->protocol);
      return EFalse;
   }
   // �洢��Ϣ
   return _pInputQueue->Push(readBuffer, readed);
}

//============================================================
// <T>��ȡ�������ݣ�д����ջ��塣�����������������Ϣ�������д����Ϣ�ܵ���</T>
//
// @return ������
//============================================================
TBool FNetMessageConnection::ProcessUdpReceive(){
   // �����Ƿ��Ѿ�����
   if(!_isUdpConnected){
      return EFalse;
   }
   // ��������
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   TInt received = _pUdpSocket->Receive(buffer, MO_NETMESSAGE_MAXLENGTH);
   // ������
   if(-1 == received){
      _pSocket->Disconnect();
      return EFalse;
   }
   // δ���յ���Ϣ
   if(0 == received){
      return EFalse;
   }
   MO_DEBUG(TC("Receive socket udp data. (length=%d)"), received);
   // ������Ϣ�ܵ��Ƿ��ܷ��¸���Ϣ
   TInt remain = _pInputUdpQueue->Reamin();
   if(remain < received){
      // ����ǰ�����Ϣ
      _pInputUdpQueue->Reset();
   }
   // �������ͷ��Ϣ
   SNetHead* pHead = (SNetHead*)buffer;
   if(ENetProtocol_Message != pHead->protocol){
      MO_FATAL(TC("Unknown net head protocol. (protocol=%d)"), pHead->protocol);
      return EFalse;
   }
   // �洢��Ϣ
   return _pInputUdpQueue->Push(buffer, received);
}

//============================================================
// <T>��ȡ�������ݣ�д����ջ��塣�����������������Ϣ�������д����Ϣ�ܵ���</T>
//
// @return ������
//============================================================
TBool FNetMessageConnection::ProcessReceive(){
   TBool result = ProcessTcpReceive();
   result |= ProcessUdpReceive();
   return result;
}

//============================================================
// <T>����һ��������Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return ������
//============================================================
TBool FNetMessageConnection::PushMessage(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ����Ƿ��Ѿ�����
   if(!_isConnected){
      return EFalse;
   }
   // ���л���Ϣ
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(pMessage->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
#ifdef _MO_DEBUG
      TChar dump[MO_FS_DUMP_LENGTH];
      TChar format[MO_FS_DUMP_LENGTH];
      MO_STATIC_DEBUG(TC("Send tcp net message.\n%s%s"),
            pMessage->Dump(dump, MO_FS_DUMP_LENGTH),
            pMessage->DumpMemory(format, MO_FS_DUMP_LENGTH));
#endif
      // ������Ϣ
      TInt result = _pSocket->Send(buffer, length);
      if(EError == result){
         _pSocket->Disconnect();
         return EFalse;
      }
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>����һ��������Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return ������
//============================================================
TBool FNetMessageConnection::PushUdpMessage(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ����Ƿ��Ѿ�����
   if(!_isUdpConnected){
      return EFalse;
   }
   // ���л���Ϣ
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(pMessage->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
#ifdef _MO_DEBUG
      TChar dump[MO_FS_DUMP_LENGTH];
      TChar format[MO_FS_DUMP_LENGTH];
      MO_STATIC_DEBUG(TC("Send udp net message.\n%s%s"),
            pMessage->Dump(dump, MO_FS_DUMP_LENGTH),
            pMessage->DumpMemory(format, MO_FS_DUMP_LENGTH));
#endif
      // ������Ϣ
      TInt result = _pUdpSocket->Send(buffer, length);
      if(EError == result){
         _pUdpSocket->Disconnect();
         return EFalse;
      }
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>����һ��TCP��Ϣ��</T>
//============================================================
TBool FNetMessageConnection::PopupMessage(TNetMessage* pMessage){
   // ����Ƿ��Ѿ�����
   if(!_isConnected){
      return EFalse;
   }
   // ������Ϣ
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   TInt length = _pInputQueue->Pop(buffer, MO_NETMESSAGE_MAXLENGTH);
   if(length > 0){
      // �����л���Ϣ
      TInt msgLength;
      if(pMessage->Unserialize(buffer, length, &msgLength)){
#ifdef _MO_DEBUG
         // �����Ϣ��Ϣ
         TChar dump[MO_FS_DUMP_LENGTH];
         TChar format[MO_FS_DUMP_LENGTH];
         MO_DEBUG(TC("Receive net message.\n%s%s"),
               pMessage->Dump(dump, MO_FS_DUMP_LENGTH),
               pMessage->DumpMemory(format, MO_FS_DUMP_LENGTH));
#endif
      }
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>����һ��UDP��Ϣ��</T>
//============================================================
TBool FNetMessageConnection::PopupUdpMessage(TNetMessage* pMessage){
   // ����Ƿ��Ѿ�����
   if(!_isConnected){
      return EFalse;
   }
   // ������Ϣ
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   TInt length = _pInputUdpQueue->Pop(buffer, MO_NETMESSAGE_MAXLENGTH);
   if(length > 0){
      // �����л���Ϣ
      TInt msgLength;
      if(pMessage->Unserialize(buffer, length, &msgLength)){
#ifdef _MO_DEBUG
         // �����Ϣ��Ϣ
         TChar dump[MO_FS_DUMP_LENGTH];
         TChar format[MO_FS_DUMP_LENGTH];
         MO_DEBUG(TC("Receive net message.\n%s%s"),
               pMessage->Dump(dump, MO_FS_DUMP_LENGTH),
               pMessage->DumpMemory(format, MO_FS_DUMP_LENGTH));
#endif
      }
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>һֱ�ȵ���ȡ����Ϣ���ء�</T>
//============================================================
TBool FNetMessageConnection::WaitMessage(TNetMessage* pMessage){
   // ����Ƿ��Ѿ�����
   if(!_isConnected){
      return EFalse;
   }
   // ���յ���һ����Ϣ
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   while(ETrue){
      // ������Ϣ
      TInt length = _pInputQueue->Pop(buffer, MO_NETMESSAGE_MAXLENGTH);
      if(length > 0){
         // �����л���Ϣ
         TInt msgLength;
         if(pMessage->Unserialize(buffer, length, &msgLength)){
#ifdef _MO_DEBUG
            // �����Ϣ��Ϣ
            TChar dump[MO_FS_DUMP_LENGTH];
            TChar format[MO_FS_DUMP_LENGTH];
            MO_DEBUG(TC("Receive net message.\n%s%s"),
                  pMessage->Dump(dump, MO_FS_DUMP_LENGTH),
                  pMessage->DumpMemory(format, MO_FS_DUMP_LENGTH));
#endif
            break;
         }
      }
      MO_LIB_SLEEP(MO_MD_MESSAGE_WAIT_INTERVAL);
   }
   return ETrue;
}

//============================================================
// <T>һֱ�ȵ���ȡ����Ϣ���ء�</T>
//============================================================
TBool FNetMessageConnection::ProcessWaitMessage(TNetMessage* pMessage){
   // ���յ���һ����Ϣ
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   while(ETrue){
      // ����Ƿ��Ѿ�����
      if(!_isConnected){
         return EFalse;
      }
      // ������Ϣ
      ProcessReceive();
      // ������Ϣ
      TInt length = _pInputQueue->Pop(buffer, MO_NETMESSAGE_MAXLENGTH);
      if(length > 0){
         // �����л���Ϣ
         TInt msgLength;
         if(pMessage->Unserialize(buffer, length, &msgLength)){
#ifdef _MO_DEBUG
            // �����Ϣ��Ϣ
            TChar dump[MO_FS_DUMP_LENGTH];
            TChar format[MO_FS_DUMP_LENGTH];
            MO_DEBUG(TC("Receive net message.\n%s%s"),
                  pMessage->Dump(dump, MO_FS_DUMP_LENGTH),
                  pMessage->DumpMemory(format, MO_FS_DUMP_LENGTH));
#endif
            break;
         }
      }
      MO_LIB_SLEEP(1);
   }
   return ETrue;
}

//============================================================
TBool FNetMessageConnection::DoConnect(){
   //TNmCrConnectRequest request;
   //return PushMessage(&request);
   return ETrue;
}

//============================================================
TBool FNetMessageConnection::DoUdpConnect(){
   //TNmCrUdpConnectRequest request;
   //request.SetClientId(_clientId);
   //return PushUdpMessage(&request);
   return ETrue;
}

MO_NAMESPACE_END
