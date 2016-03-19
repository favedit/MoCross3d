#include "MoCrNetTransferIocp.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������ݽ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetIocpTransferReceiveThread::FNetIocpTransferReceiveThread(){
}

//============================================================
// <T>�����������ݽ����߳�ʵ����</T>
//============================================================
FNetIocpTransferReceiveThread::~FNetIocpTransferReceiveThread(){
}

//============================================================
// <T>�������ݽ��մ���</T>
//
// @return ������
//============================================================
TResult FNetIocpTransferReceiveThread::Process(){
   MO_INFO(TC("Iocp query thread process."));
   // ��ȡ������Ϣ
   MO_ASSERT(_pService);
   STransferServiceConfig& config = _pService->Config();
   _dataCheck = config.dataCheck;
   _dataCompress = config.dataCompress;
   _dataMask = config.dataMask;
   // ��ý�����ɶ˿�
   FNetIocp* pPool = (FNetIocp*)_pService->SocketPool();
   MO_ASSERT(pPool);
   TAny* pHandle = pPool->NativeHandle();
   MO_ASSERT(pHandle);
   // ������ӹ���ģ��
   //FNetBufferedSocketModule* pSocketsModule = _pService->SocketsModule();
   //MO_ASSERT(pSocketsModule);
   // ��ý������ӹܵ�
   //FQueue* pReceiveQueue = _pService->ReceiveNodeQueue();
   //MO_ASSERT(pReceiveQueue);
   // ������������
   //_pInputQueue = _pService->QueueStorage()->Connection()->InputQueue();
   //MO_ASSERT(_pInputQueue);
   //............................................................
   while(!IsStop()){
      // ��ȡ�����¼��б�
	  DWORD transdBytes = 0;
      PULONG_PTR completionKey = 0;
      OVERLAPPED* pOverlap= NULL;
      TBool result = GetQueuedCompletionStatus(pHandle, &transdBytes, (PULONG_PTR)&completionKey, &pOverlap, INFINITE);
      MO_DEBUG(TC("Get queued completion status. (result=%d)"), result);
      // ��������
      if(EFalse == result){
         continue;
      }
      SIocpData* pIocpOverlap = CONTAINING_RECORD(pOverlap, SIocpData, Overlapped);
      MO_DEBUG(TC("Get queued completion data. (data=%d)"), pIocpOverlap);
      //// ���������¼��б�
      //TInt n = -1;
      //while(++n < count){
      //   // ��ȡ�¼�
      //   epoll_event& event = events[n];
      //   // ������Ӷ���
      //   INetSocket* pNetSocket = (INetSocket*)event.data.ptr;
      //   if(NULL == pNetSocket){
      //      MO_WARN("Shared net socket is not exists. (socket=0x%08X)", pNetSocket);
      //      continue;
      //   }
      //   FNetBufferedSocket* pSocket = MO_CAST_STATIC(pNetSocket, FNetBufferedSocket*);
      //   if(NULL == pSocket){
      //      MO_WARN("Shared net socket convert invalid. (socket=0x%08X)", pSocket);
      //      continue;
      //   }
      //   // ���Ӵ�����
      //   TUint32 code = event.events;
      //   if(EPOLLERR == (EPOLLERR & code)){
      //      MO_WARN("Epoll socket error. (socket=0x%08X, error_code=%d)", pSocket, code);
      //      _pService->CloseSocketWithNotify(pSocket);
      //      continue;
      //   }
      //   // ���Ӱ�رմ���
      //   if(EPOLLHUP == (EPOLLHUP & code)){
      //      MO_WARN("Epoll socket half disconnect. (socket=0x%08X, error_code=%d)", pSocket, code);
      //      _pService->CloseSocketWithNotify(pSocket);
      //      continue;
      //   }
      //   // �����յ����ݴ���
      //   if(EPOLLIN == (EPOLLIN & code)){
      //      SNetSocketInfo* pSocketInfo = pSocket->Info();
      //      TUint64 lastReceiveTotal = pSocketInfo->receiveTotal;
      //      TInt length = pSocket->DoBufferReceive();
      //      if(length > 0){
      //         _receiveTotal += length;
      //         // �����״�����
      //         if(0 == lastReceiveTotal){
      //            ReceiveFirstData(pSocket);
      //         }
      //         // �յ����ݴ���
      //         ReceiveData(pSocket);
      //      }else if(length < 0){
      //         // ���ӹرմ���
      //         MO_INFO("Epoll socket receive disconnect. (socket=0x%08X, code=%d, length=%d)", pSocket, code, length);
      //         _pService->CloseSocketWithNotify(pSocket);
      //         continue;
      //      }
      //   }
      //}
   }
   return ESuccess;
}
MO_NAMESPACE_END
