#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���컺����п顣</T>
//============================================================
FBufferedQueueBlock::FBufferedQueueBlock(){
   _count = 0;
   _countMax = 0;
}

//============================================================
// <T>����������п顣</T>
//
// @param capacity ��������
//============================================================
FBufferedQueueBlock::~FBufferedQueueBlock(){
}

//============================================================
// <T>���������Ƿ��ܹ�д�롣</T>
//
// @param length ���ݳ���
// @return �Ƿ��ܹ�д��
//============================================================
TBool FBufferedQueueBlock::TestPushAble(TInt length){
   TInt free = _capacity - _position - sizeof(TInt32);
   return (length <= free);
}

//============================================================
// <T>���������Ƿ��ܹ���ȡ��</T>
//
// @param length ���ݳ���
// @return �Ƿ��ܹ���ȡ
//============================================================
TBool FBufferedQueueBlock::TestPopAble(TInt length){
   // �������
   TInt position = _position + sizeof(TInt32);
   if(position > _length){
      return EFalse;
   }
   // ������ݳ���
   TInt32 dataLength = *(TInt32*)(_pMemory + _position);
   if(0 == dataLength){
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>��һ������д��ܵ���</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
EStreamResult FBufferedQueueBlock::Push(TAnyC* pData, TInt length){
   // ������
   MO_ASSERT(pData);
   // ��鳤��
   if(0 == length){
      MO_WARN(TC("Write empty data. (data=0x%08X, length=%d)"), pData, length);
      return EStreamResult_WriteEmpty;
   }
   // �жϹܵ��Ƿ����д��
   TInt free = _length - _position;
   TInt dataSize = sizeof(TInt32) + length;
   if(dataSize > free){
      MO_WARN(TC("Current queue is full. (data=0x%08X, capacity=%d, position=%d, free=%d, length=%d)"), pData, _capacity, _position, free, length);
      return EStreamResult_WriteFull;
   }
   // д������
   FStreamBlockHead* pHead = (FStreamBlockHead*)(_pMemory + _position);
   pHead->length = length;
   MO_LIB_MEMORY_COPY(pHead->data, free, pData, length);
   // ����λ��
   _position += sizeof(TInt32) + length;
#ifdef _MO_DEBUG
   _count++;
   if(_count > _countMax){
      _countMax = _count;
   }
#endif // _DEBUG
   return EStreamResult_Success;
}

//============================================================
// <T>�ӹܵ��ڵ���һ�����������ݡ�</T>
// <P>�ȶ������ݳ���(4byte)���ٶ����������ݡ�</P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
EStreamResult FBufferedQueueBlock::Pop(TAny* pData, TInt capacity, TInt* pLength){
   // ������
   MO_ASSERT(pData);
   MO_ASSERT(capacity > 0);
   // �������
   TInt position = _position + sizeof(TInt32);
   if(position >= _length){
      return EStreamResult_ReadEnd;
   }
   // ������ݳ���
   FStreamBlockHead* pHead = (FStreamBlockHead*)(_pMemory + _position);
   // ��鳤��
   if(pHead->length > capacity){
      MO_WARN(TC("Current data capacity is not enouth. (data=0x%08X, capacity=%d, length=%d)"), pData, capacity, pHead->length);
      return EStreamResult_ReadCapacity;
   }
   // �����Ч
   if(position + pHead->length > _length){
      MO_WARN(TC("Current data is invalid. (data=0x%08X, capacity=%d, length=%d)"), pData, capacity, pHead->length);
      return EStreamResult_ReadEnd;
   }
   // ��ȡ����
   MO_LIB_MEMORY_COPY(pData, capacity, pHead->data, pHead->length);
   // ����λ��
#ifdef _MO_DEBUG
   _count--;
#endif // _DEBUG
   _position += sizeof(TInt32) + pHead->length;
   *pLength = pHead->length;
   return EStreamResult_Success;
}

//============================================================
// <T>������Ϣ��</T>
//
// @param pTrack ��������
//============================================================
void FBufferedQueueBlock::Track(MString* pTrack){
   TInt percent = _lengthMax * 100 / _capacity;
   pTrack->AppendFormat(TC("block=0x%08X, capacity=%d/%d(%d%), length=%d, position=%d, count=%d/%d"), this, _lengthMax, _capacity, percent, _length, _position, _count, _countMax);
}

MO_NAMESPACE_END
