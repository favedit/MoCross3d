#include "MoCrNetTransferSingle.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������ݽ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetSingleSocketReceiveThread::FNetSingleSocketReceiveThread(){
   MO_CLEAR(_pSocket);
}

//============================================================
// <T>�����������ݽ����߳�ʵ����</T>
//============================================================
FNetSingleSocketReceiveThread::~FNetSingleSocketReceiveThread(){
}

//============================================================
// <T>�������ݽ��մ���</T>
//
// @return ������
//============================================================
TResult FNetSingleSocketReceiveThread::Process(){
   // ��ȡ������Ϣ
   MO_ASSERT(_pService);
   STransferServiceConfig& config = _pService->Config();
   _dataCheck = config.dataCheck;
   _dataCompress = config.dataCompress;
   _dataMask = config.dataMask;
   // �������˿���Ϣ
   MO_ASSERT(_pSocket);
   // ������ӹ���ģ��
   FNetBufferedSocketModule* pSocketsModule = _pService->SocketsModule();
   MO_ASSERT(pSocketsModule);
   // ��ý������ӹܵ�
   FQueue* pReceiveQueue = _pService->ReceiveNodeQueue();
   MO_ASSERT(pReceiveQueue);
   // ������������
   _pInputQueue = _pService->QueueStorage()->Connection()->InputQueue();
   MO_ASSERT(_pInputQueue);
   while(!IsStop()){
      SNetSocketInfo* pSocketInfo = _pSocket->Info();
      TUint64 lastReceiveTotal = pSocketInfo->receiveTotal;
      TInt length = _pSocket->DoBufferReceive();
      if(length > 0){
         _receiveTotal += length;
         // �����״�����
         if(0 == lastReceiveTotal){
            ReceiveFirstData(_pSocket);
         }
         // �յ����ݴ���
         ReceiveData(_pSocket);
      }else if(length < 0){
         // ���ӹرմ���
         MO_INFO(TC("Epoll socket receive disconnect. (socket=0x%08X, length=%d)"), _pSocket, length);
         _pService->CloseSocketWithNotify(_pSocket);
         break;
      }
   }
   return ESuccess;
}
MO_NAMESPACE_END
