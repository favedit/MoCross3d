#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���컺����С�</T>
//============================================================
FBufferedQueue::FBufferedQueue(){
   _lockCd = EStreamLock_Lock;
   _countPush = 0;
   _lengthPush = 0;
   _countPop = 0;
   _lengthPop = 0;
   _pPool = MO_CREATE(FStreamBlockPool);
   MO_CLEAR(_pReadBlock);
   _pReadBlocks = MO_CREATE(FBufferedQueueBlockList);
   MO_CLEAR(_pWriteBlock);
   _pWriteBlocks = MO_CREATE(FBufferedQueueBlockList);
}

//============================================================
// <T>����������С�</T>
//============================================================
FBufferedQueue::~FBufferedQueue(){
   MO_DELETE(_pReadBlocks);
   MO_DELETE(_pWriteBlocks);
   MO_DELETE(_pPool);
}

//============================================================
// <T>��һ��������Ϣд��ܵ���</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FBufferedQueue::InnerPush(TAnyC* pData, TInt length){
   TBool result = EFalse;
   // ����д��
   if(NULL != _pWriteBlock){
      if(!_pWriteBlock->TestPushAble(length)){
         // ��ȡ����
         _pWriteBlock->FlipForRead();
         // �����ȡ����
         _pReadBlocks->Push(_pWriteBlock);
         _pWriteBlock = NULL;
      }
   }
   // �ռ��ڴ�
   if(NULL == _pWriteBlock){
      _pWriteBlock = (FBufferedQueueBlock*)_pPool->Alloc();
   }
   // д������
   if(NULL != _pWriteBlock){
      EStreamResult resultCd = _pWriteBlock->Push(pData, length);
      if(EStreamResult_Success == resultCd){
         _countPush++;
         _lengthPush += length;
         result = ETrue;
         //MO_DEBUG("Push data success. (length=%d, write=%d)", _length, length);
      }else{
         MO_ERROR(TC("Push data failue. (length=%d)"), result);
      }
   }
   return result;
}

//============================================================
// <T>�ӹܵ��ڵ���һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
TInt FBufferedQueue::InnerPop(TAny* pData, TInt capacity){
   TInt result = 0;
   // ��ö�ȡ��
   if(NULL == _pReadBlock){
      if(!_pReadBlocks->IsEmpty()){
         _pReadBlock = _pReadBlocks->Shift();
      }
   }
   // ��д�뻺�彻������
   if(NULL == _pReadBlock){
      if(NULL != _pWriteBlock){
         if(!_pWriteBlock->IsEmpty()){
            _pReadBlock = _pWriteBlock;
            _pReadBlock->FlipForRead();
            MO_CLEAR(_pWriteBlock);
         }
      }
   }
   // �����Ƿ��ܹ���ȡ����
   if(NULL != _pReadBlock){
      TInt length;
      EStreamResult resultCd = _pReadBlock->Pop(pData, capacity, &length);
      if(EStreamResult_Success == resultCd){
         _countPop++;
         _lengthPop += length;
         result = length;
         // MO_DEBUG("Read length. (length=%d, read=%d)", _length, length);
      }else if(EStreamResult_ReadEnd == resultCd){
         _pPool->Free(_pReadBlock);
         _pReadBlock = NULL;
      }else if(EStreamResult_ReadCapacity == resultCd){
         result = -1;
      }
   }
   return result;
}

//============================================================
// <T>���������</T>
//
// @return ����
//============================================================
TInt FBufferedQueue::Count(){
   TInt count = 0;
   _locker.Enter();
   count = (TInt)(_countPush - _countPop);
   _locker.Leave();
   return count;
}

//============================================================
// <T>�����Ƿ���д��ָ�����ȵ����ݡ�</T>
//
// @param length ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FBufferedQueue::TestPushAble(TInt length){
   return ETrue;
}

//============================================================
// <T>�����Ƿ��ܴӹܵ��ڵ���һ�����ݡ�</T>
//
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
TBool FBufferedQueue::TestPopAble(){
   return EFalse;
}

//============================================================
// <T>��һ��������Ϣд��ܵ���</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FBufferedQueue::Push(TAnyC* pData, TInt length){
   TBool result = EFalse;
   switch(_lockCd){
      case EStreamLock_Unlock:{
         result = InnerPush(pData, length);
         break;
      }
      case EStreamLock_Lock:{
         _locker.Enter();
         result = InnerPush(pData, length);
         _locker.Leave();
         break;
      }
      default:{
         MO_FATAL(TC("Unknown lock mode."));
         break;
      }
   }
   return result;
}

//============================================================
// <T>�ӹܵ��ڵ���һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
TInt FBufferedQueue::Pop(TAny* pData, TInt capacity){
   TInt result = 0;
   switch(_lockCd){
      case EStreamLock_Unlock:{
         result = InnerPop(pData, capacity);
         break;
      }
      case EStreamLock_Lock:{
         _locker.Enter();
         result = InnerPop(pData, capacity);
         _locker.Leave();
         break;
      }
      default:{
         MO_FATAL(TC("Unknown lock mode."));
         break;
      }
   }
   return result;
}

//============================================================
// <T>����ʽ��һ��������Ϣд��ܵ���</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FBufferedQueue::BlockedPush(TAnyC* pData, TInt length){
   TBool result = EFalse;
   while(ETrue){
      result = Push(pData, length);
      // �����
      if(result){
         break;
      }else{
         MO_LIB_MICRO_SLEEP(0);
      }
   }
   return result;
}

//============================================================
// <T>����ʽ�ӹܵ��ڵ���һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
TInt FBufferedQueue::BlockedPop(TAny* pData, TInt capacity){
   TBool result = EFalse;
   while(ETrue){
      result = Pop(pData, capacity);
      // �����
      if(0 == result){
         MO_LIB_MICRO_SLEEP(0);
      }else{
         break;
      }
   }
   return result;
}

//============================================================
// <T>��ö�����Ϣ��</T>
//
// @param pInfo ������Ϣ
//============================================================
TBool FBufferedQueue::FetchInfo(SQueueInfo* pInfo){
   // ������
   if(NULL == pInfo){
      return EFalse;
   }
   // ���ñ���
   pInfo->count = (TInt32)(_countPush - _countPop);
   pInfo->length = (TInt32)(_lengthPush - _lengthPop);
   pInfo->countPush = _countPush;
   pInfo->lengthPush = _lengthPush;
   pInfo->countPop = _countPop;
   pInfo->lengthPop = _lengthPop;
   return ETrue;
}

//============================================================
// <T>����ڲ���Ϣ��</T>
//============================================================
void FBufferedQueue::Dump(){
   TInt count = (TInt)(_countPush - _countPop);
   TInt length = (TInt)(_lengthPush - _lengthPop);
   TFsDump dump;
   dump.AppendFormat(TC("Buffered queue dump. (capacity=%d, count=%d, length=%d)\n"), _pPool->Capacity(), count, length);
   _pPool->Track(&dump);
   MO_INFO((TCharC*)dump);
}

MO_NAMESPACE_END
