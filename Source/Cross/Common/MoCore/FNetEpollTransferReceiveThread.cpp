#include "MoCrNetTransferEpoll.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_LINUX

//============================================================
// <T>�����������ݽ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetEpollTransferReceiveThread::FNetEpollTransferReceiveThread(){
}

//============================================================
// <T>�����������ݽ����߳�ʵ����</T>
//============================================================
FNetEpollTransferReceiveThread::~FNetEpollTransferReceiveThread(){
}

//============================================================
// <T>�������ݽ��մ���</T>
//
// @return ִ�н��
//============================================================
TInt FNetEpollTransferReceiveThread::Process(){
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
#endif // __CYGWIN__
   return ESuccess;
}

#endif // _MO_LINUX

MO_NAMESPACE_END
