#include "MoCmString8.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ�����</T>
//============================================================
FString8::FString8(){
}

//============================================================
// <T>�����ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
FString8::FString8(TChar8C* pValue, TInt length){
   Assign(pValue, length);
}

//============================================================
// <T>�����ַ�����</T>
//
// @param ptr �ַ���ָ��
//============================================================
FString8::FString8(const TString8PtrC& ptr){
   Assign(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>�����ַ�����</T>
//
// @param value �ַ���
//============================================================
FString8::FString8(const MString8& value){
   Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����ַ�����</T>
//============================================================
FString8::~FString8(){
   MO_FREE(_pMemory);
}

//============================================================
// <T>�����ڴ��С��</T>
//
// @param size ��С
// @param copy ����
// @param extends ��չ
//============================================================
MO_OVERRIDE void FString8::InnerResize(TInt size, TBool copy, TBool extends, TBool force){
   if(size != _capacity){
      // ����ռ����ɹ����򲻽��и������ݴ���
      TChar8* pAlloc = MO_TYPES_ALLOC(TChar8, size);
      MO_ASSERT(pAlloc);
      // ���������ǰ�ڴ�
      if(NULL != _pMemory){
         // �������С�ڴ棬���鳤��
         if(_length > size){
            _length = size;
         }
         // ������Ч����
         if(copy && (_length > 0)){
            MO_LIB_TYPES_COPY(TChar8, pAlloc, size, _pMemory, _length);
         }
         // �ͷ���ǰ�ڴ�
         MO_FREE(_pMemory);
      }
      // �����µ��ڴ�
      _pMemory = pAlloc;
      _pMemory[_length] = 0;
      _capacity = size;
   }
}

MO_NAMESPACE_END
