#ifdef _MO_LINUX
#include <sys/ipc.h>
#include <sys/shm.h>
#endif
#include "MoCmMemory.h"
#include "MoCmLanguage.h"
#include "MoCmShared.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ�������ڴ�Ρ�</T>
//
// @param pMemory �ڴ�ָ��
// @param length ���ݳ���
//============================================================
void TShareSegment::Initialize(TAny* pMemory, TInt length, TBool created){
   _pMemory = (TByte*)pMemory;
   _position = 0;
   _length = length;
   _created = created;
}

//============================================================
// <T>�Ƿ񱻴�����</T>
// <T>����ڴ��Ǳ�������ֱ��ʹ�õģ����طǡ�</T>
//
// @return
//    <L value="ETrue">�����ڴ����½���</L>
//    <L value="EFalse">�����ڴ��ǹ�����ʹ�õ�</L>
//============================================================
TBool TShareSegment::IsCreated(){
   return _created;
}

//============================================================
// <T>��ù������ڴ�ָ�롣</T>
//
// @return �ڴ�ָ��
//============================================================
TAny* TShareSegment::Memory(){
   return _pMemory;
}

//============================================================
// <T>��õ�ǰ�ڴ�λ�á�</T>
//
// @return �ڴ�λ��
//============================================================
TInt TShareSegment::Position(){
   return _position;
}

//============================================================
// <T>����ڴ泤�ȡ�</T>
//
// @return �ڴ泤��
//============================================================
TInt TShareSegment::Length(){
   return _length;
}

//============================================================
// <T>���ʣ����ڴ�ָ�롣</T>
//
// @return ʣ����ڴ�ָ��
//============================================================
TInt TShareSegment::Remain(){
   return _length - _position;
}

//============================================================
// <T>��õ�ǰλ�õ��ڴ�ָ�롣</T>
//
// @return �ڴ�ָ��
//============================================================
TAny* TShareSegment::RemainMemory(){
   return _pMemory + _position;
}

//============================================================
// <T>�ӹ����ڴ����ռ�һ��ָ����С���ڴ档</T>
//
// @param size �ڴ��С
// @return �����ڴ�
//============================================================
TAny* TShareSegment::Alloc(TSize size){
   TByte* pMemory = NULL;
   if(size > 0){
      pMemory = _pMemory + _position;
      _position += size;
   }
   return pMemory;
}

//============================================================
// <T>�ڵ�ǰ�����ڴ���ڣ������µĹ����ڴ�Ρ�</T>
//
// @param size ��С
// @return �����ڴ��
//============================================================
TShareSegment TShareSegment::CreateSegment(TSize size){
   TShareSegment segment(_pMemory + _position, size, _created);
   _position += size;
   return segment;
}

//============================================================
// <T>���乲������С���ڴ�飬�͹�����������</T>
//
// @param pShared �������
//============================================================
void TShareSegment::SharedLink(MShared* pShared){
   MO_ASSERT(pShared);
   TSize capacity = pShared->SharedCapacity();
   TShareSegment segment = CreateSegment(capacity);
   pShared->SharedLink(segment);
}

//============================================================
// <T>��⹲���ڴ��Ƿ����������</T>
//============================================================
void TShareSegment::Check(){
   if(_position != _length){
      TChar lengthBuffer[MO_MEMORY_FORMATLENGTH];
      TChar positionBuffer[MO_MEMORY_FORMATLENGTH];
      MO_FATAL(TC("Share memory segment is invalid. (length=%s, position=%s)"),
            RInt::FormatCapacity(_length, lengthBuffer, MO_MEMORY_FORMATLENGTH),
            RInt::FormatCapacity(_position, positionBuffer, MO_MEMORY_FORMATLENGTH));
   }
}

MO_NAMESPACE_END
