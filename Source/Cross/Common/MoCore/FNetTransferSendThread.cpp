#ifdef _MO_LINUX
#ifndef __CYGWIN__
#include <sys/syscall.h>
#endif
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif
#include <MoCmStream.h>
#include "MoCrNetEpoll.h"
#include "MoCrNetPipe.h"
#include "MoCrNetTransfer.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������ݷ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetTransferSendThread::FNetTransferSendThread(){
   _code = TC("STS");
   _name = TC("Thread.Transfer.Send");
   MO_CLEAR(_pService);
   MO_CLEAR(_pSocketsModule);
   MO_CLEAR(_pOutputQueue);
   MO_CLEAR(_pUdpServerSocket);
   _dataCompress = EFalse;
   _sendTotal = 0;
   _threadId = 0;
   _pCatcher = MO_CREATE(FNetTransferCatcher);
}

//============================================================
// <T>�����������ݷ����߳�ʵ����</T>
//============================================================
FNetTransferSendThread::~FNetTransferSendThread(){
   MO_DELETE(_pCatcher);
}

//============================================================
// <T>���ô���������</T>
//
// @param pService ����������
//============================================================
void FNetTransferSendThread::SetService(FNetTransferService* pService){
   MO_ASSERT(pService);
   _pService = pService;
}

#ifdef _MO_LINUX
//============================================================
void FNetTransferSendThread::NotifyWake(){
   _notifyFutex.WakeGroup(1);
}

//============================================================
void FNetTransferSendThread::NotifyWait(){
   _notifyFutex.WaitGroup();
}

//============================================================
pid_t FNetTransferSendThread::ThreadId(){
   return _threadId;
}
#endif // _LINUX

//============================================================
// <T>������Ϣ��ָ������˿ڡ�</T>
//
// @param pSocket �˿�
// @param pMessage ��Ϣ
// @return ���ͳ���
//============================================================
TInt FNetTransferSendThread::SendTcpMessage(FNetBufferedSocket* pSocket, TNetMessage* pMessage){
   MO_ASSERT(pSocket);
   MO_ASSERT(pMessage);
   TFsDump dump;
   TFsDump format;
   // ������ݴ�С
   TInt capacity = pMessage->Capacity();
   if(0 == capacity){
      MO_WARN(TC("Empty tcp message.\n%s%s"),
            pMessage->DumpMessage((TChar*)dump, TFsDump::Size()),
            pMessage->DumpMessageMemory((TChar*)format, TFsDump::Size()));
      return 0;
   }
   // ����Ϣд�����ӵ�����ܵ���TCP�������ݣ�
   TBool result = EFalse;
   if(_dataCompress){
      result = pSocket->OutputPipe()->WriteMessageCompress(pMessage);
   }else{
      result = pSocket->OutputPipe()->WriteMessage(pMessage);
   }
   if(!result){
      // ���ӷ�������������Ҫ���͵���Ϣ
#ifdef _MO_DEBUG
      MO_WARN(TC("Socket output buffer is full. (length=%d, host=%s:%d#%d)\n%s%s"),
            pSocket->OutputPipe()->Length(), pSocket->Host(), pSocket->Port(), pSocket->Serial(),
            pMessage->DumpMessage((TChar*)dump, dump.Capacity()),
            pMessage->DumpMessageMemory((TChar*)format, dump.Capacity()));
#else
      TInt code = pMessage->MessageHead().Code();
      TNetMessageInfo* pInfo = RNetMessageFactory::CodeInfo(code);
      if(NULL != pInfo){
         MO_WARN(TC("Socket output buffer is full. (length=%d, host=%s:%d#%d, message=%s)"),
               pSocket->OutputPipe()->Length(), pSocket->Host(), pSocket->Port(), pSocket->Serial(), pInfo->Name());
      }else{
         MO_WARN(TC("Socket output buffer is full. (length=%d, host=%s:%d#%d, message=unknown)"),
               pSocket->OutputPipe()->Length(), pSocket->Host(), pSocket->Port(), pSocket->Serial());
      }
#endif
      return 0;
   }
   // ����������Ϣ
   MO_DEBUG(TC("Send tcp message to target. (host=%s:%d#%d)\nServer =>> %s%s"),
         pSocket->Host(), pSocket->Port(), pSocket->Serial(),
         pMessage->DumpMessage((TChar*)dump, dump.Capacity()),
         pMessage->DumpMessageMemory((TChar*)format, dump.Capacity()));
   return capacity;
}

//============================================================
// <T>����·�ɸ�ָ������˿ڡ�</T>
//
// @param pSocket �˿�
// @param pRouter ·��
// @return ���ͳ���
//============================================================
TInt FNetTransferSendThread::SendTcpRouter(FNetBufferedSocket* pSocket, TNetRouter* pRouter){
   MO_ASSERT(pSocket);
   MO_ASSERT(pRouter);
   TFsDump dump;
   TFsDump format;
   // ������ݴ�С
   TInt capacity = pRouter->Capacity();
   if(0 == capacity){
      MO_WARN(TC("Empty tcp router.\n%s%s"),
            pRouter->DumpRouter((TChar*)dump, dump.Size()),
            pRouter->DumpRouterMemory((TChar*)format, format.Size()));
      return 0;
   }
   // ����Ϣд�����ӵ�����ܵ���TCP�������ݣ�
   if(!pSocket->OutputPipe()->WriteRouter(pRouter)){
      TInt code = pRouter->MessageHead().Code();
      TNetMessageInfo* pInfo = RNetMessageFactory::CodeInfo(code);
      if(NULL != pInfo){
         MO_WARN(TC("Socket output buffer is full. (length=%d, host=%s:%d#%d, message=%s)"),
               pSocket->OutputPipe()->Length(), pSocket->Host(), pSocket->Port(), pSocket->Serial(), pInfo->Name());
      }else{
         MO_WARN(TC("Socket output buffer is full. (length=%d, host=%s:%d#%d, message=unknown)"),
               pSocket->OutputPipe()->Length(), pSocket->Host(), pSocket->Port(), pSocket->Serial());
      }
      // ���ӷ�������������Ҫ���͵���Ϣ
      //MO_WARN("Socket output buffer is full. (capacity=%d, length=%d, host=%s:%d#%d)\n%s%s",
      //      pSocket->OutputPipe()->Capacity(), pSocket->OutputPipe()->Length(),
      //      pSocket->Host(), pSocket->Port(), pSocket->Serial(),
      //      pRouter->DumpRouter((TChar*)dump, dump.Size()),
      //      pRouter->DumpRouterMemory((TChar*)format, format.Size()));
      return 0;
   }
   // ����������Ϣ
   MO_DEBUG(TC("Send tcp router to target. (host=%s:%d:%d)\nServer =>> %s%s"),
         pSocket->Host(), pSocket->Port(), pSocket->Serial(),
         pRouter->DumpRouter((TChar*)dump, dump.Size()),
         pRouter->DumpRouterMemory((TChar*)format, format.Size()));
   return capacity;
}

//============================================================
// <T>����UDP��Ϣ��ָ������˿ڡ�</T>
//
// @param pSocket �˿�
// @param pMessage ��Ϣ
// @return ���ͳ���
//============================================================
TInt FNetTransferSendThread::SendUdpMessage(FNetBufferedSocket* pSocket, TNetMessage* pMessage){
   MO_ASSERT(pSocket);
   MO_ASSERT(pMessage);
   TFsDump dump;
   TFsDump format;
   // ���㷢�͵�ַ
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pMessage->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serial udp message failure.\n%s%s"),
            pMessage->DumpMessage((TChar*)dump, dump.Size()),
            pMessage->DumpMemory((TChar*)format, format.Size()));
      return 0;
   }
#ifdef _MO_LINUX
   struct sockaddr_in addr;
   socklen_t addrSize = sizeof(struct sockaddr_in);
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = pSocket->UdpAddress();
   addr.sin_port = pSocket->UdpPort();
   TSocket udpHandle = _pUdpServerSocket->Handle();
   TInt sended = sendto(udpHandle, buffer, length, 0, (struct sockaddr*)&addr, addrSize);
   if(sended <= 0){
      TChar address[MoNetHostLength];
      inet_ntop(addr.sin_family, &addr.sin_addr, address, MoNetHostLength);
      MO_ERROR("Send udp message failure. (address=%d[%s], port=%d, sended=%d)\n%s%s",
            pSocket->UdpAddress(), address, addr.sin_port, sended,
            pMessage->DumpMessage((TChar*)dump, dump.Size()),
            pMessage->DumpMemory((TChar*)format, format.Size()));
      return 0;
   }
#ifdef _MO_DEBUG
   TChar address[MoNetHostLength];
   inet_ntop(addr.sin_family, &addr.sin_addr, address, MoNetHostLength);
   MO_DEBUG("Send udp message to target. (address=%d[%s], port=%d, sended=%d)",
         pSocket->UdpAddress(), address, addr.sin_port, sended,
         pMessage->DumpMessage((TChar*)dump, dump.Size()),
         pMessage->DumpMemory((TChar*)format, format.Size()));
#endif
#endif // _LINUX
   return length;
}

//============================================================
// <T>����һ����Ϣ��ָ���������ӡ�</T>
// <P>���ݲ������ͳ�ȥ��ֻ�Ƿ������Ӷ���ķ��ͳ��</P>
//
// @param message ��Ϣ
// @param handle ������
// @return ִ�н��
//============================================================
TInt FNetTransferSendThread::ProcessTarget(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   TFsDump format;
   // �����Ϣ����
   TNetMessageHead& headMessage = pTransfer->MessageHead();
   TInt messageCode = headMessage.Code();
   TNetMessageInfo* pInfo = pTransfer->MessageInfo();
   if(NULL == pInfo){
      // �Ƿ�����Ϣ
      MO_WARN(TC("Invalid message code. (code=%d)\n%s"), headMessage.Code(),
            pTransfer->DumpMemory((TChar*)format, MO_FS_DUMP_LENGTH));
      return 0;
   }
   TBool udpMessage = pInfo->IsUdpSupport();
   // �������˿�
   SNetSocketTarget& target = pTransfer->TransferHead().Socket();
   TUint16 index = target.Index(); 
   FNetBufferedSocket* pSocket = _pSocketsModule->FindIndex(index);
   if(NULL == pSocket){
      if(!udpMessage){
         // ���Ӳ����ڻ��Թرգ�����Ҫ���͵���Ϣ
         MO_DEBUG(TC("Socket is not found. (index=0x%04X:%d, message=%s)"), index, index, pInfo->Name());
      }
      return 0;
   }
   // ��������Ƿ�ر�
   if(!pSocket->IsConnected()){
      // �����Ѿ��رգ�����Ҫ���͵���Ϣ
      MO_DEBUG(TC("Socket is allready shutdown. (index=0x%04X:%d, message=%s:%08X)"),
            index, index, pInfo->Name(), messageCode);
      return 0;
   }
   // ���UDP��־
   TBool udpSupport = udpMessage && pSocket->IsUdpSupport();
   // ���˿ڴ���ʱ��
   TUint16 serial = target.Serial();
   TUint16 socketSerial = pSocket->Serial();
   if(!udpSupport && (socketSerial != serial)){
      // ���Ӳ����ڻ��Թرգ�����Ҫ���͵���Ϣ
      MO_DEBUG(TC("Socket flag is different. (socket=0x%08X(%d), index=%d, socket_serial=%d, message_serial=%d, message=%s:%08X)"),
            pSocket, pSocket->Index(), index, socketSerial, serial, pInfo->Name(), messageCode);
      return 0;
   }
   // ���͹㲥����
   if(udpSupport){
      return SendUdpMessage(pSocket, pTransfer);
   }
   // ������Ϣ����
   if(ENetProtocol_Message == _protocol){
      return SendTcpMessage(pSocket, pTransfer);
   }
   // ����·������
   return SendTcpRouter(pSocket, pTransfer);
}

//============================================================
// <T>�������ݷ��ʹ���</T>
// <P>�յ�����������Ϣ������Ŀ�꼯�ϣ�
// <P> �� Ŀ��Server�յ�����������Ϣ������Ŀ�꼯�ϣ���ֳɶ��·�ɰ���������ͬ�ķ���������</P>
// <P>�յ�����������Ϣ������Ŀ�꼯�ϣ���ֳɶ��·�ɰ���������ͬ�ķ���������</P>
//
// @return ������
//============================================================
TResult FNetTransferSendThread::Process(){
#ifdef _MO_LINUX
#ifndef __CYGWIN__
   // ���������Ϣ
   MO_ASSERT(_pService);
   STransferServiceConfig& config = _pService->Config();
   _protocol = config.protocol;
   _dataCompress = config.dataCompress;
   TInt receiveFirstTimeout = config.receiveFirstTimeout;
   TInt receiveTimeout = config.receiveTimeout;
   TInt sendTimeout = config.sendTimeout;
   // ��÷�����ɶ˿�
   INetSocketPool* pSendPool = _pService->SendPool();
   MO_ASSERT(pSendPool);
   TInt handle = pSendPool->Handle();
   // ������ӹ���ģ��
   _pSocketsModule = _pService->SocketsModule();
   MO_ASSERT(_pSocketsModule);
   // ������������
   _pOutputQueue = _pService->QueueStorage()->Connection()->OutputQueue();
   MO_ASSERT(_pOutputQueue);
   // ��װ��׽��
   _pCatcher->Install();
   _threadId = syscall(SYS_gettid);
   // ������Ϣ
   TInt loop = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   TNetTransfer transfer;
   TInt timeout = MO_MD_NTS_EVENT_TIMEOUT;
   epoll_event events[MO_MD_NTS_EVENT_MAXCOUNT];
   while(!IsStop()){
      _pCatcher->Enter();
      if(MO_TRAP_CATCHER(_pCatcher)){
         _pCatcher->Recorded();
         //............................................................
         TInt readCount = 0;
         TInt readTotal = 0;
         TDateTime tick = RDateTime::Current();
         // ����������Ϣ��
         for(TInt n = 0; n < MO_MD_NTS_EVENT_MAXCOUNT; n++){
            // ����һ����Ϣ���ֲ�����������ܵ���
            TInt readed = _pOutputQueue->Pop(buffer, MO_NETMESSAGE_MAXLENGTH);
            if(0 == readed){
               break;
            } 
            readCount++;
            readTotal += readed;
            // ��ȡ�ܵ���Ϣ
            TInt length;
            if(transfer.Unserialize(buffer, readed, &length)){
               // ��ȡ��Ϣ����
               TInt targetType = transfer.RouterHead().TargetType();
               // ������Ϣ
               if(ENetTerminal_ServerTransfer == targetType){
                  // �����������Ϣ
                  _pService->ProcessTransfer(&transfer);
               }else{
                  // ������Ϣ��Ŀ��
                  ProcessTarget(&transfer);
               }
            }else{
               MO_ERROR("Router unserialize failure. (length=%d)", length);
            }
         }
         //............................................................
         // ��ȡ�����¼��б�
         TInt count = epoll_wait(handle, events, MO_MD_NTS_EVENT_MAXCOUNT, timeout);
         // ���ݻ������Ļ�����һ�δ���ǿ�����̷��أ�����ȴ���ʱ����
         if(MO_MD_NTS_EVENT_MAXCOUNT == count){
            timeout = 0;
         }else{
            timeout = MO_MD_NTS_EVENT_TIMEOUT;
         }
         // ������ʱ��˯��һ��
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
         //............................................................
         // ���������¼��б�
         TInt n = -1;
         TUint sendCount = 0;
         while(++n < count){
            // ��ȡ�¼�
            epoll_event& event = events[n];
            // ������Ӷ���
            INetSocket* pNetSocket = (INetSocket*)event.data.ptr;
            FNetBufferedSocket* pSocket = MO_CAST_STATIC(pNetSocket, FNetBufferedSocket*);
            // ���ӿ����Ѿ����رգ���Ч�Ķ�ȡ����
            if(NULL == pSocket){
               MO_WARN("Shared net socket is not exists. (socket=0x%08X)", pSocket);
               continue;
            }
            // ��鳬ʱ
            SNetSocketInfo* pInfo = pSocket->Info();
            if(receiveFirstTimeout > 0){
               if(pInfo->receiveDateTime == pInfo->createDateTime){
                  TTimeTick firstTick = tick - pInfo->receiveDateTime;
                  if(firstTick > receiveFirstTimeout){
                     MO_WARN("Epoll socket disconnect first timeout. (socket=0x%08X, current_tick=0x%16X, receive_tick=0x%16X, first_timeout=%d, first_tick=%d)",
                           pSocket, tick, pInfo->receiveDateTime, receiveFirstTimeout, firstTick);
                     _pService->CloseSocketWithNotify(pSocket);
                     continue;
                  }
               }
            }
            if(receiveTimeout > 0){
               TTimeTick receiveTick = tick - pInfo->receiveDateTime;
               if(receiveTick > receiveTimeout){
                  MO_WARN("Epoll socket receive timeout. (socket=0x%08X, current_tick=0x%16X, receive_tick=0x%16X, receive_timeout=%d, receive_tick=%d)",
                        pSocket, tick, pInfo->receiveDateTime, receiveTimeout, receiveTick);
                  _pService->CloseSocketWithNotify(pSocket);
                  continue;
               }
            }
            if(sendTimeout > 0){
               TTimeTick sendTick = tick - pInfo->sendDateTime;
               if(sendTick > sendTimeout){
                  MO_WARN("Epoll socket send timeout. (socket=0x%08X, current_tick=0x%16X, send_tick=0x%16X, send_timeout=%d, send_tick=%d)",
                        pSocket, tick, pInfo->sendDateTime, sendTimeout, sendTick);
                  _pService->CloseSocketWithNotify(pSocket);
                  continue;
               }
            }
            // ���Ӵ�����
            TUint32 code = event.events;
            if(EPOLLERR & code){
               MO_WARN("Epoll socket error. (socket=0x%08X, error_code=%d)", pSocket, code);
               _pService->CloseSocketWithNotify(pSocket);
               continue;
            }
            // ���Ӱ�رմ���
            if(EPOLLHUP & code){
               MO_WARN("Epoll socket half disconnect. (socket=0x%08X, error_code=%d)", pSocket, code);
               _pService->CloseSocketWithNotify(pSocket);
               continue;
            }
            // ���ӷ������ݴ���
            if(EPOLLOUT & code){
               // ������Ϣ����
               TInt length = pSocket->DoBufferSend();
               if(length > 0){
                  sendCount++;
                  _sendTotal += length;
                  loop++;
               }else if(-1 == length){
                  // �ر�����
                  MO_INFO("Epoll socket receive disconnect. (socket=0x%08X, code=%d, length=%d)", pSocket, code, length);
                  _pService->CloseSocketWithNotify(pSocket);
               }
            }
         }
         // δ��ȡ�����ݺ�δ�������ݵ�����£����ߴ���
         if((0 == readCount) && (0 == sendCount)){
            MO_LIB_MICRO_SLEEP(MO_MD_NTS_NOTIFY_INTERVAL);
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
