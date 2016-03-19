#include "MoCmString16.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ������塣</T>
//============================================================
TStringBuffer16::TStringBuffer16(){
}

//============================================================
// <T>�����ַ������塣</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
TStringBuffer16::TStringBuffer16(TChar16C* pValue, TInt length){
   Assign(pValue, length);
}

//============================================================
// <T>�����ַ������塣</T>
//
// @param ptr �ַ���ָ��
//============================================================
TStringBuffer16::TStringBuffer16(const TString16PtrC& ptr){
   Assign(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>�����ַ������塣</T>
//
// @param value �ַ���
//============================================================
TStringBuffer16::TStringBuffer16(const MString16& value){
   Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����ַ������塣</T>
//============================================================
TStringBuffer16::~TStringBuffer16(){
   MO_FREE(_pMemory);
}

//============================================================
// <T>�����ڴ��С��</T>
//
// @param size ��С
// @param copy ����
// @param extends ��չ
//============================================================
void TStringBuffer16::InnerResize(TInt size, TBool copy, TBool extends, TBool force){
   if(size > _capacity){
      // ���ڴ治��ʱ�����¼����ڴ�����
      TInt capacity = size;
      if(extends){
         capacity = RTypes<TChar16>::CalculateTypeCapacity(_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      TChar16* pAlloc = MO_TYPES_ALLOC(TChar16, capacity);
      MO_ASSERT(pAlloc);
      // ���������ǰ�ڴ�
      if(NULL != _pMemory){
         // �������С�ڴ棬���鳤��
         if(_length > capacity){
            _length = capacity;
         }
         // ������Ч����
         if(copy && (_length > 0)){
            MO_LIB_TYPES_COPY(TChar16, pAlloc, capacity, _pMemory, _length);
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
