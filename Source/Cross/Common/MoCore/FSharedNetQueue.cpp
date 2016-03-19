#include "MoCrNetMessage.h"
#include "MoCrNetPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
FSharedNetQueue::FSharedNetQueue(){
}

//============================================================
FSharedNetQueue::~FSharedNetQueue(){
};

//============================================================
// <T>ѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FSharedNetQueue::PushMessage(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ���л�·������
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pMessage->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_FATAL(TC("Message serialize failure."));
      return EFalse;
   }
   // �����ݷ���ܵ�
   return Push(buffer, length);
}

//============================================================
// <T>ѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FSharedNetQueue::PushRouter(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ���л�·������
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pRouter->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_FATAL(TC("Router serialize failure."));
      return EFalse;
   }
   // �����ݷ���ܵ�
   return Push(buffer, length);
}

//============================================================
// <T>ѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FSharedNetQueue::PushTransfer(TNetTransfer* pTransfer){
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
   TInt blockLength = *(TInt32*)(TAny*)buffer;
   if(blockLength > MO_NETMESSAGE_MAXLENGTH){
      MO_FATAL(TC("Write message length is error. (memory=0x%08X, block_length=%d)"), buffer, blockLength);
   }
   if(length > MO_NETMESSAGE_MAXLENGTH){
      MO_FATAL(TC("Write data length is error. (memory=0x%08X, data_length=%d)"), buffer, length);
   }
   if(blockLength != length){
      MO_FATAL(TC("Write data length is not equals. (memory=0x%08X, block_length=%d, data_length=%d)"), buffer, blockLength, length);
   }
   // �����ݷ���ܵ�
   return Push(buffer, length);
}

//============================================================
// <T>ѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FSharedNetQueue::TryPushTransfer(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   // ���л�·������
   TInt length = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pTransfer->Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_WARN(TC("Transfer serialize failure. (message_code=%d)"), pTransfer->MessageHead().Code());
      return EFalse;
   }
   if(length <= 0){
      MO_WARN(TC("Transfer serialize failure. (message_code=%d, length=%d)"), pTransfer->MessageHead().Code(), length);
      return EFalse;
   }
   // ��Ϣ���
   TInt blockLength = *(TInt32*)(TAny*)buffer;
   if(blockLength > MO_NETMESSAGE_MAXLENGTH){
      MO_WARN(TC("Write message length is error. (memory=0x%08X, block_length=%d)"), buffer, blockLength);
   }
   if(length > MO_NETMESSAGE_MAXLENGTH){
      MO_WARN(TC("Write data length is error. (memory=0x%08X, data_length=%d)"), buffer, length);
   }
   if(blockLength != length){
      MO_WARN(TC("Write data length is not equals. (memory=0x%08X, block_length=%d, data_length=%d)"), buffer, blockLength, length);
   }
   // �����ݷ���ܵ�
   return TryPush(buffer, length);
}

//============================================================
// <T>�Զ�����ʽѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FSharedNetQueue::BlockedPushMessage(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   TBool result = EFalse;
   // �����̺߳���ȡ�߳̿���ͬʱ��������Ҫͬ����
   _lockPush.Enter();
   result = PushMessage(pMessage);
   _lockPush.Leave();
   // ���ݽ������
   if(result){
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>�Զ�����ʽѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FSharedNetQueue::BlockedPushRouter(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   TBool result = EFalse;
   // �����̺߳���ȡ�߳̿���ͬʱ��������Ҫͬ����
   _lockPush.Enter();
   result = PushRouter(pRouter);
   _lockPush.Leave();
   // ���ݽ������
   if(result){
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>�Զ�����ʽѹ��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
TBool FSharedNetQueue::BlockedPushTransfer(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   TBool result = EFalse;
   // �����̺߳���ȡ�߳̿���ͬʱ��������Ҫͬ����
   _lockPush.Enter();
   result = PushTransfer(pTransfer);
   _lockPush.Leave();
   // ���ݽ������
   if(result){
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>�Զ�����ʽѹ��һ���ܵ����ݡ�</T>
//
// @param pMessage ��Ϣ����
// @return  ������
//============================================================
//TBool FSharedNetQueue::BlockedPushPipe(FSharedNetPipe* pPipe){
//   // ��ùܵ���Ϣ
//   TByte* pMemory;
//   TInt total, length, first, last;
//   FSharedQueue::InnerGetInfo(&pMemory, &total, &length, &first, &last);
//   // ���������Ƿ����һ��д��
//   TByte* pRead;
//   TInt rtotal, rlength, rfirst, rlast;
//   pPipe->GetInfo(&pRead, &rtotal, &rlength, &rfirst, &rlast);
//   pRead += rfirst;
//   TInt capacity = *(TInt32*)pRead;
//   if(capacity > rlength){
//      return EFalse;
//   }
//   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
//   if(rfirst > rlast) {
//       pPipe->TryRead(buffer, capacity);
//       pRead = buffer;
//   }
//   TInt fill = MO_ALIGN_4(capacity + sizeof(TInt32));
//   TInt remain = (first <= last) ? total - last : first - last;
//   // ���ڴ���ֱ�Ӹ�������
//   TBool result = EFalse;
//   if(remain >= (fill + MoPipeReserveLength)){
//      pMemory += last;
//      *(TInt32*)pMemory = capacity;
//      memcpy(pMemory + sizeof(TInt32), pRead, capacity);
//      InnerSetInfo(first, last +  fill);
//      result = ETrue;
//   }else{
//      result = FSharedQueue::Push(pRead, capacity);
//   }
//   if(result){
//      if(buffer != pRead){
//         pPipe->FollowRead(capacity);
//      }
//      _futex.Wake();
//   }
//   return result;
//}

MO_NAMESPACE_END
