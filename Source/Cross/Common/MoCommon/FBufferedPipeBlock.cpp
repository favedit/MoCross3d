#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���컺���������ֿ顣</T>
//============================================================
FBufferedPipeBlock::FBufferedPipeBlock(){
}

//============================================================
// <T>���������������ֿ顣</T>
//============================================================
FBufferedPipeBlock::~FBufferedPipeBlock(){
}

//============================================================
// <T>���������Ƿ��ܹ���ȡ��</T>
//
// @param length ���ݳ���
// @return �Ƿ��ܹ���ȡ
//============================================================
TBool FBufferedPipeBlock::TestReadAble(TInt length){
   TInt position = _position + length;
   return (position <= _length);
}

//============================================================
// <T>���������Ƿ��ܹ�д�롣</T>
//
// @param length ���ݳ���
// @return �Ƿ��ܹ�д��
//============================================================
TBool FBufferedPipeBlock::TestWriteAble(TInt length){
   TInt free = _capacity - _position;
   return (length <= free);
}

//============================================================
// <T>�ӹܵ��ڲ���һ�����ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ��������
// @param pLength ��ȡ����
// @return ������
//============================================================
EStreamResult FBufferedPipeBlock::Peek(TAny* pData, TInt length, TInt *pLength){
   // ������
   MO_ASSERT(pData);
   // �����Ч��
   if((0 == length) || (0 == _length) || (_position == _length)){
      *pLength = 0;
      return EStreamResult_Success;
   }
   // ������ݳ���
   TInt lengthPeek = length;
   if(_position + length > _length){
      lengthPeek = _length - _position;
   }
   // ��ȡ����
   MO_LIB_MEMORY_COPY(pData, length, _pMemory + _position, lengthPeek);
   // ����λ��
   *pLength = lengthPeek;
   return EStreamResult_Success;
}

//============================================================
// <T>�ӹܵ��ڶ�ȡһ�����ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ��������
// @param pLength ��ȡ����
// @return ������
//============================================================
EStreamResult FBufferedPipeBlock::Read(TAny* pData, TInt length, TInt *pLength){
   // ������
   MO_ASSERT(pData);
   // �������
   if((0 == length) || (0 == _length) || (_position == _length)){
      *pLength = 0;
      return EStreamResult_Success;
   }
   // ������ݳ���
   TInt lengthRead = length;
   if(_position + length > _length){
      lengthRead = _length - _position;
   }
   // ��ȡ����
   MO_LIB_MEMORY_COPY(pData, length, _pMemory + _position, lengthRead);
   // ����λ��
   _position += lengthRead;
   _lengthTotalRead += lengthRead;
   *pLength = lengthRead;
   return EStreamResult_Success;
}

//============================================================
// <T>��һ������д��ܵ���</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @param pLength д�볤��
// @return ������
//============================================================
EStreamResult FBufferedPipeBlock::Write(TAnyC* pData, TInt length, TInt *pLength){
   // ������
   MO_ASSERT(pData);
   // ��鳤��
   if((0 == length) || (_position == _length)){
      *pLength = 0;
      return EStreamResult_Success;
   }
   // �жϹܵ��Ƿ����д��
   TInt lengthWrite = length;
   if(_position + length > _length){
      lengthWrite = _length - _position;
   }
   // д������
   MO_LIB_MEMORY_COPY(_pMemory + _position, _length - _position, pData, lengthWrite);
   // ����λ��
   _position += lengthWrite;
   _lengthTotalWrite += lengthWrite;
   *pLength = lengthWrite;
   return EStreamResult_Success;
}

//============================================================
// <T>������Ϣ��</T>
//
// @param pTrack ��������
//============================================================
void FBufferedPipeBlock::Track(MString* pTrack){
   TInt percent = _lengthMax * 100 / _capacity;
   pTrack->AppendFormat(TC("block=0x%08X, capacity=%d/%d(%d%), total_read=%8d, total_write=%8d, length=%8d, position=%8d"),
         this, _lengthMax, _capacity, percent, _lengthTotalRead, _lengthTotalWrite, _length, _position);
}

MO_NAMESPACE_END
