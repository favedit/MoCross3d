#include "MoCrNetTransferEpoll.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_LINUX

//============================================================
// <T>�����������ݷ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetEpollTransferSendThread::FNetEpollTransferSendThread(){
}

//============================================================
// <T>�����������ݷ����߳�ʵ����</T>
//============================================================
FNetEpollTransferSendThread::~FNetEpollTransferSendThread(){
}

//============================================================
// <T>�������ݷ��ʹ���</T>
// <P>�յ�����������Ϣ������Ŀ�꼯�ϣ�
// <P> �� Ŀ��Server�յ�����������Ϣ������Ŀ�꼯�ϣ���ֳɶ��·�ɰ���������ͬ�ķ���������</P>
// <P>�յ�����������Ϣ������Ŀ�꼯�ϣ���ֳɶ��·�ɰ���������ͬ�ķ���������</P>
//
// @return ִ�н��
//============================================================
TInt FNetEpollTransferSendThread::Process(){
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
            continue;
         }
         // ִ�д���ʱ
         if(count < 0){
            if(EINTR == errno){
               // �ں��жϴ���
               MO_PWARN(epoll_wait);
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
#endif // __CYGWIN__
   return ESuccess;
}

#endif // _MO_LINUX

MO_NAMESPACE_END
