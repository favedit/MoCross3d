#ifdef _MO_WINDOWS

#include "MoCmString16.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>构造一个ANSI字符串类。</T>
//============================================================
FString16::FString16(){
}

//============================================================
// <T>从ANSI字符串构造实例。</T>
//
// @param pSource ANSI字符串
// @param length(-1) 长度
//============================================================
FString16::FString16(TChar16C* pValue, TInt length){
   Assign(pValue, length);
}

//============================================================
// <T>从ANSI字符对象构造实例。</T>
//
// @param source ANSI字符对象
//============================================================
FString16::FString16(const TString16PtrC& ptr){
   Assign(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>从ANSI字符对象构造实例。</T>
//
// @param source ANSI字符对象
//============================================================
FString16::FString16(const MString16& value){
   Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>构造一个ANSI字符串类。</T>
//============================================================
FString16::~FString16(){
   MO_FREE(_pMemory);
}

//============================================================
// <T>调整内存大小。</T>
//
// @param size 大小
// @param copy 复制
// @param extends 扩展
//============================================================
void FString16::InnerResize(TInt size, TBool copy, TBool extends, TBool force){
   if(size != _capacity){
      // 如果收集不成功，则不进行复制数据处理
      TChar16* pAlloc = MO_TYPES_ALLOC(TChar16, size);
      MO_ASSERT(pAlloc);
      // 如果存在以前内存
      if(NULL != _pMemory){
         // 如果是缩小内存，则检查长度
         if(_length > size){
            _length = size;
         }
         // 复制有效数据
         if(copy && (_length > 0)){
            MO_LIB_TYPES_COPY(TChar16, pAlloc, size, _pMemory, _length);
         }
         // 释放以前内存
         MO_FREE(_pMemory);
      }
      // 设置新的内存
      _pMemory = pAlloc;
      _pMemory[_length] = 0;
      _capacity = size;
   }
}

MO_NAMESPACE_END

#endif // _WINDOWS
