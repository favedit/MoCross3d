#include "MoCmProperty.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���������ߡ�</T>
//============================================================
FPack::FPack(){
}

//============================================================
// <T>�����ַ���������ߡ�</T>
//============================================================
FPack::FPack(EPropertyPack packCd){
   _packCd = packCd;
}

//============================================================
// <T>�����ַ���������ߡ�</T>
//============================================================
FPack::~FPack(){
   MO_FREE(_pMemory);
}

//============================================================
// <T>�����ڴ��С��</T>
// <P>����һ��ʹ���ǣ����ռ���һ���ڴ档
// ��ǰ��С�ڴ治��ʱ���������ռ�ָ����С1.5�����ڴ������ݣ���δʹ�õ���Ϊ����ʹ�á�
// ���ڴ治�ٷ�����С�ϸı��ʱ�򣬿���ʹ��ѹ�������ͷŵ�����δʹ�õĻ����ڴ档</P>
//
// @param size ��С
//============================================================
void FPack::InnerResize(TInt size, TBool copy, TBool extends){
   if(size > _capacity){
      // ���ڴ治��ʱ�����¼����ڴ�����
      TInt capacity = size;
      if(extends){
         capacity = RTypes<TChar>::CalculateTypeCapacity(_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      TChar* pAlloc = MO_TYPES_ALLOC(TChar, capacity);
      MO_ASSERT(pAlloc);
      // ���������ǰ�ڴ�
      if(NULL != _pMemory){
         // �������С�ڴ棬���鳤��
         if(_length > capacity){
            _length = capacity;
         }
         // ������Ч����
         if(copy && (_length > 0)){
            MO_LIB_TYPES_COPY(TChar, pAlloc, capacity, _pMemory, _length);
         }
         // �ͷ���ǰ�ڴ�
         MO_FREE(_pMemory);
      }
      // �����µ��ڴ�
      _pMemory = pAlloc;
      _capacity = capacity;
   }
}

MO_NAMESPACE_END
