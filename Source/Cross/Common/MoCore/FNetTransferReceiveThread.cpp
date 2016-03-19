#ifdef _MO_LINUX
#ifndef __CYGWIN__
#include <sys/syscall.h>
#endif
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include "MoCrNetEpoll.h"
#include "MoCrNetPipe.h"
#include "MoCrNetTransfer.h"

//============================================================
#define MO_NET_RECEIVE_DATA_STR "<policy-file-request/>\0";
#define MO_NET_SEND_DATA_STR    "<cross-domain-policy><allow-access-from domain=\"*\" to-ports=\"*\"/></cross-domain-policy>\0";
#define MO_NET_RECEIVE_TGW_STR  "tgw_l7_forward"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������ݽ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetTransferReceiveThread::FNetTransferReceiveThread(){
   _code = TC("STR");
   _name = TC("Thread.Transfer.Receive");
   MO_CLEAR(_pService);
   MO_CLEAR(_pCommander);
   MO_CLEAR(_pInputQueue);
   _dataCheck = ETrue;
   _dataCompress = ETrue;
   _dataMask = ETrue;
   _receiveTotal = 0;
   _threadId = 0;
   _pCatcher = MO_CREATE(FNetTransferCatcher);
}

//============================================================
// <T>�����������ݽ����߳�ʵ����</T>
//============================================================
FNetTransferReceiveThread::~FNetTransferReceiveThread(){
   MO_DELETE(_pCatcher);
}

//============================================================
// <T>���ô���������</T>
//
// @param pService ����������
//============================================================
void FNetTransferReceiveThread::SetService(FNetTransferService* pService){
   MO_ASSERT(pService);
   _pService = pService;
   _pCommander = pService->Commander();
}

//============================================================
void FNetTransferReceiveThread::NotifyWake(){
}

//============================================================
#ifdef _MO_LINUX
pid_t FNetTransferReceiveThread::ThreadId(){
   return _threadId;
}
#endif

//============================================================
// <T>����һ����Ϣ��������ܵ���</T>
//
// @param pSocket ��������
// @param pBuffer ����ָ��
// @param length ���ݳ���
//============================================================
TInt FNetTransferReceiveThread::ReceiveMessage(FNetBufferedSocket* pSocket, TByteC* pBuffer, TInt size){
   MO_ASSERT(pSocket);
   MO_ASSERT(pBuffer);
   // �������˿���Ϣ
   TCharC* pHost = pSocket->Host();
   TUint32 ip  = pSocket->Ip();
   TUint16 port = pSocket->Port();
   TSocket handle = pSocket->Handle();
   TUint16 index = pSocket->Index();
   TUint16 serial = pSocket->Serial();
   TNetSerial receiveSerial = pSocket->ReceiveSerial();
   //TNetTick receiveTick = pSocket->ReceiveTick();
   // �����Ϣ
   TInt length = 0;
   TNetMessageBuffer message;
   TBool unserializeResult = message.Uncompress(pBuffer, size, &length, _dataMask, _dataCheck);
   //if(_dataCompress){
   //   unserializeResult = message.Uncompress(pBuffer, size, &length);
   //}else{
   //   if(_dataMask){
   //      unserializeResult = message.UnserializeMask(pBuffer, size, &length);
   //   }else{
   //      if(_dataCheck){
   //         unserializeResult = message.Unserialize(pBuffer, size, &length);
   //      }else{
   //         unserializeResult = message.UnserializeUncheck(pBuffer, size, &length);
   //      }
   //   }
   //}
   if(!unserializeResult){
      TChar dump[MO_FS_DUMP_LENGTH];
      TInt dumpSize = MO_LIB_MIN(size, MO_NETMESSAGE_BYTEDUMP_MAXLENGTH);
      MO_ERROR(TC("Receive message unserial failure. (host=%s:%d, handle=%d, index=%d:%d, size=%d)\n%s"),
            pHost, port, handle, index, serial, size,
            RByte::Dump(pBuffer, dumpSize, dump, MO_FS_DUMP_LENGTH));
      _pCommander->SendInvalidUnserialNotify(pSocket);
      return EFailure;
   }
   // �����Ϣ��Ϣ
   TInt code = message.MessageHead().Code();
   TNetMessageInfo* pMessageInfo = message.MessageInfo();
   if(NULL == pMessageInfo){
      TChar dump[MO_FS_DUMP_LENGTH];
      TInt dumpSize = MO_LIB_MIN(size, MO_NETMESSAGE_BYTEDUMP_MAXLENGTH);
      MO_ERROR(TC("Receive message unknown failure. (host=%s:%d, handle=%d, index=%d:%d, code=%d)\n%s"),
            pHost, port, handle, index, serial, code,
            RByte::Dump(pBuffer, dumpSize, dump, MO_FS_DUMP_LENGTH));
      _pCommander->SendInvalidUnknownNotify(pSocket);
      return EFailure;
   }
   // �����Ϣ�汾
   TNetVersion version = message.MessageHead().Version();
   if(pMessageInfo->Version() != version){
      TChar dump[MO_FS_DUMP_LENGTH];
      TInt dumpSize = MO_LIB_MIN(size, MO_NETMESSAGE_BYTEDUMP_MAXLENGTH);
      MO_ERROR(TC("Receive message version failure. (name=%s, receive_version=0x%04X, local_version=0x%04X)\n%s"),
            pMessageInfo->Name(), version, pMessageInfo->Version(),
            RByte::Dump(pBuffer, dumpSize, dump, MO_FS_DUMP_LENGTH));
      _pCommander->SendInvalidVersionNotify(pSocket);
      return EFailure;
   }
   // �����Ϣ����
   if(_dataCheck){
      TNetSerial messageSerial = message.MessageHead().Serial();
      if(messageSerial <= receiveSerial){
         TChar dump[MO_FS_DUMP_LENGTH];
         message.Dump(dump, MO_FS_DUMP_LENGTH);
         TChar format[MO_FS_DUMP_LENGTH];
         message.DumpMemory(format, MO_FS_DUMP_LENGTH);
         MO_ERROR(TC("Receive message serial failure. (name=%s, receive_serial=%d, socket_serial=%d)\n%s"),
               pMessageInfo->Name(), messageSerial, receiveSerial, dump, format);
         _pCommander->SendInvalidUnknownNotify(pSocket);
         return EFailure;
      }
      pSocket->SetReceiveSerial(messageSerial);
   }
   // �����Ϣʱ�� (TODO����ʱ�����)
   if(_dataCheck){
      TNetTick messageTick = message.MessageHead().Tick();
      //if(messageTick < receiveTick){
      //   TChar dump[MO_FS_DUMP_LENGTH];
      //   message.Dump(dump, MO_FS_DUMP_LENGTH);
      //   TChar format[MO_FS_DUMP_LENGTH];
      //   message.DumpMemory(format, MO_FS_DUMP_LENGTH);
      //   MO_ERROR("Receive message tick failure. (name=%s, receive_tick=%d, socket_tick=%d)\n%s",
      //         pMessageInfo->Name(), messageTick, receiveTick, dump, format);
      //   _pService->SendInvalidUnknownNotify(pSocket);
      //   return EFailure;
      //}
      pSocket->SetReceiveTick(messageTick);
   }
   // ���´�����Ϣͷ��Ϣ
   TNetTransfer transfer(&message);
   TNetTransferHead& head = transfer.TransferHead();
   head.SetHandle(handle);
   head.SetHost(ip, port);
   head.SetSocket(index, serial);
   // ���л���Ϣ����
   if(!_pInputQueue->PushTransfer(&transfer)){
      TChar dump[MO_FS_DUMP_LENGTH];
      message.Dump(dump, MO_FS_DUMP_LENGTH);
      TChar format[MO_FS_DUMP_LENGTH];
      message.DumpMemory(format, MO_FS_DUMP_LENGTH);
      MO_DEBUG(TC("Receive message full failure. (host=%s:%d, handle=%d:%d:%d)\n%s%s"),
            pHost, port, handle, index, serial, dump, format);
      _pCommander->SendInvalidFullNotify(pSocket);
      return EWarn;
   }
   MO_DEBUG(TC("Receive tcp message. (host=%s:%d, handle=%d:%d:%d, length=%d)"),
         pHost, port, handle, index, serial, length);
   return ESuccess;
}

//============================================================
// <T>����һ����Ϣ�ʼİ���������ܵ���</T>
//
// @param pSocket ��������
// @param pBuffer ����ָ��
// @param length ���ݳ���
//============================================================
TInt FNetTransferReceiveThread::ReceiveRouter(FNetBufferedSocket* pSocket, TByteC* pBuffer, TInt size){
   MO_ASSERT(pSocket);
   MO_ASSERT(pBuffer);
   TCharC* pHost = pSocket->Host();
   TUint32 ip = pSocket->Ip();
   TUint16 port = pSocket->Port();
   TSocket handle = pSocket->Handle();
   TUint16 index = pSocket->Index();
   TUint16 serial = pSocket->Serial();
   // �����л�·������
   TInt length;
   TNetRouter router;
   if(!router.Unserialize(pBuffer, size, &length)){
      TChar dump[MO_FS_DUMP_LENGTH];
      TInt dumpSize = MO_LIB_MIN(size, MO_NETMESSAGE_BYTEDUMP_MAXLENGTH);
      MO_ERROR(TC("Unserial router failure. (host=%s:%d, handle=%d, index=%d:%d, size=%d)\n%s"),
            pHost, port, handle, index, serial, size,
            RByte::Dump(pBuffer, dumpSize, dump, MO_FS_DUMP_LENGTH));
      _pCommander->SendInvalidUnserialNotify(pSocket);
      return EFailure;
   }
   // ��ô�����Ϣ
   TNetTransfer transfer(&router);
   TNetTransferHead& head = transfer.TransferHead();
   head.SetHandle(handle);
   head.SetHost(ip, port);
   head.SetSocket(index, serial);
   // ���л���Ϣ����
   if(!_pInputQueue->PushTransfer(&transfer)){
      TChar dump[MO_FS_DUMP_LENGTH];
      TChar format[MO_FS_DUMP_LENGTH];
      MO_ERROR(TC("Receive router failure. (host=%s:%d, handle=%d, index=%d:%d)\n%s%s"),
            pHost, port, handle, index, serial,
            transfer.Dump(dump, MO_FS_DUMP_LENGTH),
            transfer.DumpMemory(format, MO_FS_DUMP_LENGTH));
      _pCommander->SendInvalidFullNotify(pSocket);
      return EFailure;
   }
   MO_DEBUG(TC("Receive tcp router. (socket=0x%08X, host=%s:%d, handle=%d, index=%d:%d, length=%d)"),
         pSocket, pHost, port, handle, index, serial, length);
   return ESuccess;
}

//============================================================
// <T>����һ������˿ڵ����ݡ�</T>
//
// @param pSocket ��������
//============================================================
TInt FNetTransferReceiveThread::ReceiveFirstData(FNetBufferedSocket* pSocket){
   // ������ӵ�����ܵ�
   INetPipe* pPipe = pSocket->InputPipe();
   MO_ASSERT(pPipe);
   TInt lengthPeek = 0;
   TByte buffer[MO_FS_TEXT_LENGTH];
   RBytes::Clear(buffer, MO_FS_TEXT_LENGTH);
   if(EStreamResult_Success == pPipe->Peek(buffer, MO_FS_TEXT_LENGTH, &lengthPeek)){
      TChar8C* pBuffer = (TChar8C*)buffer;
      // ����TGWЭ��
      TInt tgwLength = RString8::Length(MO_NET_RECEIVE_TGW_STR);
      if(RTypes<TChar8>::Equals(pBuffer, MO_NET_RECEIVE_TGW_STR, tgwLength)){
         // ��ȡ����
         TInt lengthRead = 0;
         TInt receiveLength = RString8::Length(pBuffer) + 1;
         EStreamResult resultCd = pPipe->Read(buffer, receiveLength, &lengthRead);
         if(EStreamResult_Success != resultCd){
            TChar dump[MO_FS_DUMP_LENGTH];
            MO_ERROR(TC("Read pipe tgw data failure. (peek_length=%d, receive_length=%d, result_cd=%d)\n%s"),
                  lengthPeek, receiveLength, (TCharC*)buffer, resultCd,
                  RByte::Dump(buffer, lengthPeek, dump, MO_FS_DUMP_LENGTH));
         }
      }
      // ����Ȩ��Э��
      if(buffer[lengthPeek - 1] == 0){
         // �ж��Ƿ�ΪȨ����Ϣ
         TChar8C* pReceiveInfo = MO_NET_RECEIVE_DATA_STR;
         TInt receiveLength = RString8::Length(pReceiveInfo) + 1;
         if(RString8::Equals(pReceiveInfo, (TChar8C*)buffer)){
            // ��ȡȨ������
            TInt lengthRead = 0;
            if(EStreamResult_Success == pPipe->Read(buffer, receiveLength, &lengthRead)){
               MO_DEBUG(TC("Receive and send security data success. (socket=0x%08X, host=%s:%d, handle=%d)"),
                     pSocket, pSocket->Host(), pSocket->Port(), pSocket->Handle());
            }else{
               MO_ERROR(TC("Receive and read security data failue. (socket=0x%08X, host=%s:%d, handle=%d)"),
                     pSocket, pSocket->Host(), pSocket->Port(), pSocket->Handle());
            }
            // ����Ȩ������
            INetPipe* pOutputPipe = pSocket->OutputPipe();
            TChar8C* pSendInfo = MO_NET_SEND_DATA_STR;
            TInt lengthWrite = 0;
            TInt sendLength = RString8::Length(pSendInfo) + 1;
            if(EStreamResult_Success != pOutputPipe->Write(pSendInfo, sendLength, &lengthWrite)){
               MO_INFO(TC("Receive and send security data failue. (socket=0x%08X, host=%s:%d, handle=%d)"),
                     pSocket, pSocket->Host(), pSocket->Port(), pSocket->Handle());
            }
         }
      }
   }
   return lengthPeek;
}

//============================================================
// <T>����һ������˿ڵ����ݡ�</T>
//
// @param pSocket ��������
//============================================================
TInt FNetTransferReceiveThread::ReceiveData(FNetBufferedSocket* pSocket){
   // ѭ������
   TInt loop = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   // ������ӵ�����ܵ�
   INetPipe* pPipe = pSocket->InputPipe();
   MO_ASSERT(pPipe);
   // ��ȡ����ܵ���������Ϣ
   TBool continueCd = ETrue;
   while(continueCd){
      // �ж��Ƿ����������Ϣͷ
      TInt length = pPipe->Length();
      if(length < (TInt)sizeof(SNetHead)){
         break;
      }
      // ��ȡ��Ϣ�ĳ���
      TNetLength size = 0;
      TInt lengthPeek;
      if(EStreamResult_Success != pPipe->Peek(&size, sizeof(TNetLength), &lengthPeek)){
         break;
      }
      if(lengthPeek != sizeof(TNetLength)){
         break;
      }
      if(0 == size){
         break;
      }
      // ��Ϣ���ȴ��ڹܵ����ȣ�������Ϣ
      if(size > MO_NETMESSAGE_MAXLENGTH){
         TChar dump[MO_FS_DUMP_LENGTH];
         TByte buffer[MO_NETMESSAGE_BYTEDUMP_MAXLENGTH];
         TInt peekSize = MO_LIB_MIN(length, MO_NETMESSAGE_BYTEDUMP_MAXLENGTH);
         pPipe->Peek(buffer, peekSize, &lengthPeek);
         MO_ERROR(TC("Invalid net socket data. (length=%d, size=%d, peek_size=%d)\n%s"),
               length, size, peekSize,
               RByte::Dump(buffer, peekSize, dump, MO_FS_DUMP_LENGTH));
         _pService->CloseSocketWithNotify(pSocket);
         break;
      }
      // ��Ϣ����һ��������
      if((TUint)length < size){
         break;
      }
      // ����ȫ�ֹܵ��Ƿ��ܷ��¸���Ϣ
      if(!_pInputQueue->TestPushAble(size)){
         MO_ERROR(TC("Server input queue is full. (message_size=%d)"), size);
         break;
      }
      // �����Ϣ���ݣ�д��ȫ�ֹܵ�
      TInt lengthRead;
      if(EStreamResult_Success != pPipe->Read(buffer, size, &lengthRead)){
         MO_ERROR(TC("Socket pipe try read failure. (size=%d)"), size);
         continue;
      }
      // �������ͷ��Ϣ
      SNetHead* pHead = (SNetHead*)buffer;
      if(pHead->length != size){
         MO_ERROR(TC("Socket net head data is invalid. (head_length=%d, size=%d)"), pHead->length, size);
         _pService->CloseSocketWithNotify(pSocket);
         break;
      }
      switch(pHead->protocol){
         case ENetProtocol_Message:{
            // �յ�������Ϣ
            TInt receiveResult = ReceiveMessage(pSocket, buffer, size);
            loop++;
            if(EFailure == receiveResult){
               MO_ERROR(TC("Receive message failure. (socket=0x%08X, receive_result=%d)"), pSocket, receiveResult);
               _pService->CloseSocketWithNotify(pSocket);
               continueCd = EFalse;
            }
            break;
         }
         case ENetProtocol_Router:{
            // �յ�������Ϣ�ʼİ�
            ReceiveRouter(pSocket, buffer, size);
            loop++;
            break;
         }
         default:{
            // δ֪��ʽ
            MO_ERROR(TC("Unsupport package mode. (protocol=%d)"), pHead->protocol);
            _pService->CloseSocketWithNotify(pSocket);
            continueCd = EFalse;
            break;
         }
      }
   }
   return loop;
}

//============================================================
// <T>�������ݽ��մ���</T>
//
// @return ������
//============================================================
TResult FNetTransferReceiveThread::Process(){
#ifdef _MO_LINUX
#ifndef __CYGWIN__
   _threadId = syscall(SYS_gettid);
#endif
#endif
   // ��ȡ������Ϣ
   MO_ASSERT(_pService);
   STransferServiceConfig& config = _pService->Config();
   _dataCheck = config.dataCheck;
   _dataCompress = config.dataCompress;
   _dataMask = config.dataMask;
   // ��ý�����ɶ˿�
   INetSocketPool* pPool = _pService->SocketPool();
   MO_ASSERT(pPool);
   TUint handle = pPool->Handle();
   MO_ASSERT(handle > 0);
   // ������ӹ���ģ��
   FNetBufferedSocketModule* pSocketsModule = _pService->SocketsModule();
   MO_ASSERT(pSocketsModule);
   // ��ý������ӹܵ�
   FQueue* pReceiveQueue = _pService->ReceiveNodeQueue();
   MO_ASSERT(pReceiveQueue);
   // ������������
   _pInputQueue = _pService->QueueStorage()->Connection()->InputQueue();
   MO_ASSERT(_pInputQueue);
   // ��װ��׽��
   _pCatcher->Install();
#ifdef _MO_LINUX
#ifndef __CYGWIN__
   // ѭ������
   TInt timeout = MO_MD_NTS_EVENT_TIMEOUT;
   epoll_event events[MO_MD_NTS_EVENT_MAXCOUNT];
   while(!IsStop()){
      _pCatcher->Enter();
      if(MO_TRAP_CATCHER(_pCatcher)){
         _pCatcher->Recorded();
         //............................................................
         // ��ȡ�����¼��б�
         TInt count = epoll_wait(handle, events, MO_MD_NTS_EVENT_MAXCOUNT, timeout);
         // ���ݻ������Ļ�����һ�δ���ǿ�����̷��أ�����ȴ���ʱ����
         if(MO_MD_NTS_EVENT_MAXCOUNT == count){
            timeout = 0;
         }else{
            timeout = MO_MD_NTS_EVENT_TIMEOUT;
         }
         // �����ݴ����ʱ����
         if(0 == count){
            _pCatcher->Leave();
            continue;
         }
         // ִ�д���ʱ
         if(count < 0){
            if(EINTR == errno){
               // �ں��жϴ���
               MO_PWARN(epoll_wait);
               _pCatcher->Leave();
               continue;
            }else{
               MO_PFATAL(epoll_wait);
            }
         }
         // ���������¼��б�
         TInt n = -1;
         while(++n < count){
            // ��ȡ�¼�
            epoll_event& event = events[n];
            // ������Ӷ���
            INetSocket* pNetSocket = (INetSocket*)event.data.ptr;
            if(NULL == pNetSocket){
               MO_WARN("Shared net socket is not exists. (socket=0x%08X)", pNetSocket);
               continue;
            }
            FNetBufferedSocket* pSocket = MO_CAST_STATIC(pNetSocket, FNetBufferedSocket*);
            if(NULL == pSocket){
               MO_WARN("Shared net socket convert invalid. (socket=0x%08X)", pSocket);
               continue;
            }
            // ���Ӵ�����
            TUint32 code = event.events;
            if(EPOLLERR == (EPOLLERR & code)){
               MO_WARN("Epoll socket error. (socket=0x%08X, error_code=%d)", pSocket, code);
               _pService->CloseSocketWithNotify(pSocket);
               continue;
            }
            // ���Ӱ�رմ���
            if(EPOLLHUP == (EPOLLHUP & code)){
               MO_WARN("Epoll socket half disconnect. (socket=0x%08X, error_code=%d)", pSocket, code);
               _pService->CloseSocketWithNotify(pSocket);
               continue;
            }
            // �����յ����ݴ���
            if(EPOLLIN == (EPOLLIN & code)){
               SNetSocketInfo* pSocketInfo = pSocket->Info();
               TUint64 lastReceiveTotal = pSocketInfo->receiveTotal;
               TInt length = pSocket->DoBufferReceive();
               if(length > 0){
                  _receiveTotal += length;
                  // �����״�����
                  if(0 == lastReceiveTotal){
                     ReceiveFirstData(pSocket);
                  }
                  // �յ����ݴ���
                  ReceiveData(pSocket);
               }else if(length < 0){
                  // ���ӹرմ���
                  MO_INFO("Epoll socket receive disconnect. (socket=0x%08X, code=%d, length=%d)", pSocket, code, length);
                  _pService->CloseSocketWithNotify(pSocket);
                  continue;
               }
            }
         }
      }else{
         _pCatcher->JumpFinish();
      }
      _pCatcher->Leave();
   }
#endif
#endif
   return ESuccess;
}
MO_NAMESPACE_END
