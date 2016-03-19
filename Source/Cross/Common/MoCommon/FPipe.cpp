#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ݹܵ�����</T>
//
// @return ���ݹܵ�����
//============================================================
FPipe::FPipe(){
   _linked = ETrue;
   RType<SPipeInfo>::Clear(&_info);
   MO_CLEAR(_pMemory);
}

//============================================================
FPipe::FPipe(TSize capacity){
   _linked = EFalse;
   RType<SPipeInfo>::Clear(&_info);
   capacity += capacity % sizeof(TUint32);
   _info.capacity = capacity;
   _pMemory = MO_TYPES_ALLOC(TByte, capacity);
   RTypes<TByte>::Clear(_pMemory, capacity);
}

//============================================================
// <T>�������ݹܵ�����</T>
//
// @param pMemory �ڴ�ָ��
// @param capacity �������
// @return ���ݹܵ�����
//============================================================
FPipe::FPipe(TByte* pMemory, TSize capacity){
   _linked = ETrue;
   RType<SPipeInfo>::Clear(&_info);
   _info.capacity = capacity;
   _pMemory = pMemory;
}

//============================================================
FPipe::~FPipe(){
   if(!_linked){
      MO_FREE(_pMemory);
   }
}

//============================================================
SPipeInfo* FPipe::Info(){
   return &_info;
}

//============================================================
SPipeAtom FPipe::Atom(){
   SPipeAtom atom;
   atom.infoPtr = &_info;
   atom.memoryPtr = _pMemory;
   atom.Fetch();
   return atom;
}

//============================================================
// <T>��ùܵ��Ա�ռ�ó��ȡ�</T>
//
// @return ��ռ�ó��ȡ�
//============================================================
TInt FPipe::Length(){
   TInt first = _info.first;
   TInt last = _info.last;
   TInt length = (first <= last) ? last - first : (_info.capacity - first) + last;
   return length;
}

//============================================================
// <T>��ùܵ���ʣ��ĳ��ȡ�</T>
//
// @return ʣ��ĳ���
//============================================================
TInt FPipe::Reamin(){
   TInt first = _info.first;
   TInt last = _info.last;
   TInt length = (first <= last) ? last - first : (_info.capacity - first) + last;
   return _info.capacity - length - MoPipeReserveLength;
}

//============================================================
//<T>���ùܵ��ռ䡣</T>
//============================================================
TBool FPipe::Reset(){
   memset(&_info, 0, sizeof(SPipeInfo));
   MO_CLEAR(_pMemory);
   return ETrue;
}

MO_NAMESPACE_END
