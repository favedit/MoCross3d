#include "MoCmString8.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ������塣</T>
//============================================================
FStringBuffer8::FStringBuffer8(){
}

//============================================================
// <T>�����ַ������塣</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
FStringBuffer8::FStringBuffer8(TChar8C* pValue, TInt length){
   Assign(pValue, length);
}

//============================================================
// <T>�����ַ������塣</T>
//
// @param ptr �ַ���ָ��
//============================================================
FStringBuffer8::FStringBuffer8(const TString8PtrC& ptr){
   Assign(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>�����ַ������塣</T>
//
// @param value �ַ���
//============================================================
FStringBuffer8::FStringBuffer8(const MString8& value){
   Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����ַ������塣</T>
//============================================================
FStringBuffer8::~FStringBuffer8(){
   MO_FREE(_pMemory);
}

//============================================================
// <T>�����ڴ��С��</T>
//
// @param size ��С
// @param copy ����
// @param extends ��չ
//============================================================
void FStringBuffer8::InnerResize(TInt size, TBool copy, TBool extends, TBool force){
   if(size > _capacity){
      // ���ڴ治��ʱ�����¼����ڴ�����
      TInt capacity = size;
      if(extends){
         capacity = RTypes<TChar8>::CalculateTypeCapacity(_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      TChar8* pAlloc = MO_TYPES_ALLOC(TChar8, capacity);
      MO_ASSERT(pAlloc);
      // ���������ǰ�ڴ�
      if(NULL != _pMemory){
         // �������С�ڴ棬���鳤��
         if(_length > capacity){
            _length = capacity;
         }
         // ������Ч����
         if(copy && (_length > 0)){
            MO_LIB_TYPES_COPY(TChar8, pAlloc, capacity, _pMemory, _length);
         }
         // �ͷ���ǰ�ڴ�
         MO_FREE(_pMemory);
      }
      // �����µ��ڴ�
      _pMemory = pAlloc;
      _pMemory[_length] = 0;
      _capacity = capacity;
   }
}

MO_NAMESPACE_END
