#ifdef _MO_WINDOWS

#include "MoCmString16.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����һ��ANSI�ַ����ࡣ</T>
//============================================================
FString16::FString16(){
}

//============================================================
// <T>��ANSI�ַ�������ʵ����</T>
//
// @param pSource ANSI�ַ���
// @param length(-1) ����
//============================================================
FString16::FString16(TChar16C* pValue, TInt length){
   Assign(pValue, length);
}

//============================================================
// <T>��ANSI�ַ�������ʵ����</T>
//
// @param source ANSI�ַ�����
//============================================================
FString16::FString16(const TString16PtrC& ptr){
   Assign(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>��ANSI�ַ�������ʵ����</T>
//
// @param source ANSI�ַ�����
//============================================================
FString16::FString16(const MString16& value){
   Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>����һ��ANSI�ַ����ࡣ</T>
//============================================================
FString16::~FString16(){
   MO_FREE(_pMemory);
}

//============================================================
// <T>�����ڴ��С��</T>
//
// @param size ��С
// @param copy ����
// @param extends ��չ
//============================================================
void FString16::InnerResize(TInt size, TBool copy, TBool extends, TBool force){
   if(size != _capacity){
      // ����ռ����ɹ����򲻽��и������ݴ���
      TChar16* pAlloc = MO_TYPES_ALLOC(TChar16, size);
      MO_ASSERT(pAlloc);
      // ���������ǰ�ڴ�
      if(NULL != _pMemory){
         // �������С�ڴ棬���鳤��
         if(_length > size){
            _length = size;
         }
         // ������Ч����
         if(copy && (_length > 0)){
            MO_LIB_TYPES_COPY(TChar16, pAlloc, size, _pMemory, _length);
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

#endif // _WINDOWS
