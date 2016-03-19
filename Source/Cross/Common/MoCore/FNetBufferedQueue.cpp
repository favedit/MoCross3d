#include "MoCrNetMessage.h"
#include "MoCrNetPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������绺����С�</T>
//============================================================
FNetBufferedQueue::FNetBufferedQueue(){
}

//============================================================
// <T>�������绺����С�</T>
//============================================================
FNetBufferedQueue::~FNetBufferedQueue(){
};

//============================================================
// <T>���������</T>
//
// @return ����
//============================================================
TInt FNetBufferedQueue::Count(){
   return FBufferedQueue::Count();
}

//============================================================
// <T>�����Ƿ���д��ָ�����ȵ����ݡ�</T>
//
// @param length ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FNetBufferedQueue::TestPushAble(TInt length){
   return FBufferedQueue::TestPushAble(length);
}

//============================================================
// <T>�����Ƿ��ܴӹܵ��ڵ���һ�����ݡ�</T>
//
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
TBool FNetBufferedQueue::TestPopAble(){
   return FBufferedQueue::TestPopAble();
}

//============================================================
// <T>��һ��������Ϣд��ܵ���</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FNetBufferedQueue::Push(TAnyC* pData, TInt length){
   return FBufferedQueue::Push(pData, length);
}

//============================================================
// <T>�ӹܵ��ڵ���һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
TInt FNetBufferedQueue::Pop(TAny* pData, TInt capacity){
   return FBufferedQueue::Pop(pData, capacity);
}

//============================================================
// <T>��ܵ��ڶ���ʽѹ��һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param size ���ݳ���
// @return ѹ�������Ƿ�ɹ���ΪFalseʱ��ǰ�̻߳����
//============================================================
TBool FNetBufferedQueue::BlockedPush(TAnyC* pData, TInt length){
   return FBufferedQueue::BlockedPush(pData, length);
}

//============================================================
// <T>�ӹܵ��ڶ���ʽ����һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0ʱ��ǰ�̻߳����
//============================================================
TInt FNetBufferedQueue::BlockedPop(TAny* pData, TInt capacity){
   return FBufferedQueue::BlockedPop(pData, capacity);
}

//============================================================
// <T>ѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FNetBufferedQueue::PushMessage(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ���л�·������
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pMessage->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_FATAL(TC("Message serialize failure."));
   }
   // �����ݷ���ܵ�
   return FBufferedQueue::Push(buffer, length);
}

//============================================================
// <T>ѹ��һ��·�ɡ�</T>
//
// @param pRouter ·�ɶ���
// @return  ������
//============================================================
TBool FNetBufferedQueue::PushRouter(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ���л�·������
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pRouter->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_FATAL(TC("Router serialize failure."));
   }
   // �����ݷ���ܵ�
   return FBufferedQueue::Push(buffer, length);
}

//============================================================
// <T>ѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FNetBufferedQueue::PushTransfer(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   // ���л�·������
   TInt length = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pTransfer->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_FATAL(TC("Transfer serialize failure. (message_code=%d)"), pTransfer->MessageHead().Code());
      return EFalse;
   }
   if(length <= 0){
      MO_FATAL(TC("Transfer serialize failure. (message_code=%d, length=%d)"), pTransfer->MessageHead().Code(), length);
      return EFalse;
   }
   // ��Ϣ���
   TInt bufferLength = *(TInt32*)(TAny*)buffer;
   if(bufferLength > MO_NETMESSAGE_MAXLENGTH){
      MO_FATAL(TC("Write message length is error. (memory=0x%08X, block_length=%d)"), buffer, bufferLength);
   }
   if(length > MO_NETMESSAGE_MAXLENGTH){
      MO_FATAL(TC("Write data length is error. (memory=0x%08X, data_length=%d)"), buffer, length);
   }
   if(bufferLength != length){
      MO_FATAL(TC("Write data length is not equals. (memory=0x%08X, block_length=%d, data_length=%d)"), buffer, bufferLength, length);
   }
   // �����ݷ���ܵ�
   return FBufferedQueue::Push(buffer, length);
}

//============================================================
// <T>��ö�����Ϣ��</T>
//
// @param pInfo ������Ϣ
//============================================================
TBool FNetBufferedQueue::FetchInfo(SQueueInfo* pInfo){
   return FBufferedQueue::FetchInfo(pInfo);
}

//============================================================
// <T>����ڲ���Ϣ��</T>
//============================================================
void FNetBufferedQueue::Dump(){
   FBufferedQueue::Dump();
}

MO_NAMESPACE_END
