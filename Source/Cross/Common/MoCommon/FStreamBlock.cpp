#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���컺���������ֿ顣</T>
//============================================================
FStreamBlock::FStreamBlock(){
   MO_CLEAR(_pMemory);
   _capacity = 0;
   _length = 0;
   _lengthMax = 0;
   _position = 0;
   _lengthTotalRead = 0;
   _lengthTotalWrite = 0;
}

//============================================================
// <T>���������������ֿ顣</T>
//============================================================
FStreamBlock::~FStreamBlock(){
   MO_FREE(_pMemory);
}

//============================================================
// <T>ǿ�ƹܵ���������</T>
//
// @param capacity ����
//============================================================
void FStreamBlock::ForceCapacity(TInt capacity){
   MO_ASSERT(capacity > 0);
   // �ͷ��ڴ�
   if(NULL != _pMemory){
      MO_FREE(_pMemory);
   }
   // �����ڴ�
   _pMemory = MO_TYPES_ALLOC(TByte, capacity);
   _capacity = capacity;
   _position = 0;
}

//============================================================
// <T>�ж��ڴ��Ƿ�Ϊ�ա�</T>
//
// @return �Ƿ�Ϊ��
//============================================================
TBool FStreamBlock::IsEmpty(){
   return (0 == _position);
}

//============================================================
// <T>���������Ƿ��ܹ�д�롣</T>
//
// @param length ���ݳ���
// @return �Ƿ��ܹ�д��
//============================================================
TBool FStreamBlock::TestPushAble(TInt length){
   return EFalse;
}

//============================================================
// <T>���������Ƿ��ܹ���ȡ��</T>
//
// @param length ���ݳ���
// @return �Ƿ��ܹ���ȡ
//============================================================
TBool FStreamBlock::TestPopAble(TInt length){
   return EFalse;
}

//============================================================
// <T>��ת���ݶ�ȡ����</T>
//
// @return ������
//============================================================
TBool FStreamBlock::FlipForRead(){
   _length = _position;
   _position = 0;
#ifdef _MO_DEBUG
   // ͳ����󳤶�
   if(_length > _lengthMax){
      _lengthMax = _length;
   }
#endif // _DEBUG
   return ETrue;
}

//============================================================
// <T>��ת����д�봦��</T>
//
// @return ������
//============================================================
TBool FStreamBlock::FlipForWrite(){
   _length = _capacity;
   _position = 0;
   return ETrue;
}

//============================================================
// <T>�������ݴ���</T>
//
// @return ������
//============================================================
TBool FStreamBlock::Reset(){
   _capacity = 0;
   _length = 0;
   _lengthMax = 0;
   _position = 0;
   _lengthTotalRead = 0;
   _lengthTotalWrite = 0;
   return ETrue;
}

//============================================================
// <T>������Ϣ��</T>
//
// @param pTrack ��������
//============================================================
void FStreamBlock::Track(MString* pTrack){
   TInt percent = _lengthMax * 100 / _capacity;
   pTrack->AppendFormat(TC("block=0x%08X, capacity=%d/%d(%d%), length=%d, position=%d"), this, _lengthMax, _capacity, percent, _length, _position);
}

MO_NAMESPACE_END
