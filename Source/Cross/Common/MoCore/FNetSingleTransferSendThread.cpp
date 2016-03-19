#include "MoCrNetTransferSingle.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������ݷ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetSingleTransferSendThread::FNetSingleTransferSendThread(){
}

//============================================================
// <T>�����������ݷ����߳�ʵ����</T>
//============================================================
FNetSingleTransferSendThread::~FNetSingleTransferSendThread(){
}

//============================================================
// <T>�������ݷ��ʹ���</T>
// <P>�յ�����������Ϣ������Ŀ�꼯�ϣ�
// <P> �� Ŀ��Server�յ�����������Ϣ������Ŀ�꼯�ϣ���ֳɶ��·�ɰ���������ͬ�ķ���������</P>
// <P>�յ�����������Ϣ������Ŀ�꼯�ϣ���ֳɶ��·�ɰ���������ͬ�ķ���������</P>
//
// @return ������
//============================================================
TResult FNetSingleTransferSendThread::Process(){
   // ���������Ϣ
   MO_ASSERT(_pService);
   STransferServiceConfig& config = _pService->Config();
   _protocol = config.protocol;
   _dataCompress = config.dataCompress;
   TInt receiveFirstTimeout = config.receiveFirstTimeout;
   TInt receiveTimeout = config.receiveTimeout;
   TInt sendTimeout = config.sendTimeout;
   // ������ӹ���ģ��
   _pSocketsModule = _pService->SocketsModule();
   MO_ASSERT(_pSocketsModule);
   // ������������
   _pOutputQueue = _pService->QueueStorage()->Connection()->OutputQueue();
   MO_ASSERT(_pOutputQueue);
   // ������Ϣ
   TInt loop = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   TNetTransfer transfer;
   TInt timeout = MO_MD_NTS_EVENT_TIMEOUT;
   while(!IsStop()){
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
            MO_ERROR(TC("Router unserialize failure. (length=%d)"), length);
         }
      }
      // δ��ȡ�����ݺ�δ�������ݵ�����£����ߴ���
      if(0 == readCount){
         MO_LIB_MICRO_SLEEP(MO_MD_NTS_NOTIFY_INTERVAL);
      }
   }
   return ESuccess;
}

MO_NAMESPACE_END
