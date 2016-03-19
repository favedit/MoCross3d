#include "MoCrNetTransferSingle.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������ݷ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetSingleSocketSendThread::FNetSingleSocketSendThread(){
   MO_CLEAR(_pSocket);
}

//============================================================
// <T>�����������ݷ����߳�ʵ����</T>
//============================================================
FNetSingleSocketSendThread::~FNetSingleSocketSendThread(){
}

//============================================================
// <T>�������ݷ��ʹ���</T>
// <P>�յ�����������Ϣ������Ŀ�꼯�ϣ�
// <P> �� Ŀ��Server�յ�����������Ϣ������Ŀ�꼯�ϣ���ֳɶ��·�ɰ���������ͬ�ķ���������</P>
// <P>�յ�����������Ϣ������Ŀ�꼯�ϣ���ֳɶ��·�ɰ���������ͬ�ķ���������</P>
//
// @return ������
//============================================================
TResult FNetSingleSocketSendThread::Process(){
   // ���������Ϣ
   MO_ASSERT(_pService);
   STransferServiceConfig& config = _pService->Config();
   _protocol = config.protocol;
   _dataCompress = config.dataCompress;
   TInt receiveFirstTimeout = config.receiveFirstTimeout;
   TInt receiveTimeout = config.receiveTimeout;
   TInt sendTimeout = config.sendTimeout;
   // ��÷�����ɶ˿�
   MO_ASSERT(_pSocket);
   // ������ӹ���ģ��
   _pSocketsModule = _pService->SocketsModule();
   MO_ASSERT(_pSocketsModule);
   // ������������
   _pOutputQueue = _pService->QueueStorage()->Connection()->OutputQueue();
   MO_ASSERT(_pOutputQueue);
   // ������Ϣ
   TInt loop = 0;
   TNetTransfer transfer;
   TInt timeout = MO_MD_NTS_EVENT_TIMEOUT;
   while(!IsStop()){
      TDateTime tick = RDateTime::Current();
      // ��鳬ʱ
      SNetSocketInfo* pInfo = _pSocket->Info();
      if(receiveFirstTimeout > 0){
         if(pInfo->receiveDateTime == pInfo->createDateTime){
            TTimeTick firstTick = tick - pInfo->receiveDateTime;
            if(firstTick > receiveFirstTimeout){
               MO_WARN(TC("Epoll socket disconnect first timeout. (socket=0x%08X, current_tick=0x%16X, receive_tick=0x%16X, first_timeout=%d, first_tick=%d)"),
                     _pSocket, tick, pInfo->receiveDateTime, receiveFirstTimeout, firstTick);
               _pService->CloseSocketWithNotify(_pSocket);
               break;
            }
         }
      }
      if(receiveTimeout > 0){
         TTimeTick receiveTick = tick - pInfo->receiveDateTime;
         if(receiveTick > receiveTimeout){
            MO_WARN(TC("Epoll socket receive timeout. (socket=0x%08X, current_tick=0x%16X, receive_tick=0x%16X, receive_timeout=%d, receive_tick=%d)"),
                  _pSocket, tick, pInfo->receiveDateTime, receiveTimeout, receiveTick);
            _pService->CloseSocketWithNotify(_pSocket);
            break;
         }
      }
      if(sendTimeout > 0){
         TTimeTick sendTick = tick - pInfo->sendDateTime;
         if(sendTick > sendTimeout){
            MO_WARN(TC("Epoll socket send timeout. (socket=0x%08X, current_tick=0x%16X, send_tick=0x%16X, send_timeout=%d, send_tick=%d)"),
                  _pSocket, tick, pInfo->sendDateTime, sendTimeout, sendTick);
            _pService->CloseSocketWithNotify(_pSocket);
            break;
         }
      }
      // ������Ϣ����
      TInt length = _pSocket->DoBufferSend();
      if(length > 0){
         _sendTotal += length;
         loop++;
      }else if(-1 == length){
         // �ر�����
         MO_INFO(TC("Epoll socket receive disconnect. (socket=0x%08X, length=%d)"), _pSocket, length);
         _pService->CloseSocketWithNotify(_pSocket);
         break;
      }
      // δ��ȡ�����ݺ�δ�������ݵ�����£����ߴ���
      if(0 == length){
         MO_LIB_MICRO_SLEEP(MO_MD_NTS_NOTIFY_INTERVAL);
      }
   }
   return ESuccess;
}

MO_NAMESPACE_END
