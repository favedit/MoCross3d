#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����߳��ڴ档</T>
//============================================================
FThreadMemory::FThreadMemory(){
   // ������ڴ�洢�б�
   _pBlockAllocators = MO_PTR_CREATE(FBlockAllocatorFreeSet);
}

//============================================================
// <T>�ͷ��߳��ڴ�顣</T>
//============================================================
FThreadMemory::~FThreadMemory(){
   // �ͷſ��ڴ��б�
   TSetIterator<TUint, FBlockAllocator*> iterator = _pBlockAllocators->IteratorC();
   while(iterator.Next()){
      RAllocator::BlockAllocatorFree(iterator.Value());
   }
   MO_PTR_DELETE(_pBlockAllocators);
}

//============================================================
// <T>�ռ��߳��ڴ�顣</T>
//
// @param size �ڴ��С
// @return �ڴ��
//============================================================
TAny* FThreadMemory::Alloc(TUint size){
   FBlockAllocator* pAllocator = _pBlockAllocators->Get(size);
   if(NULL == pAllocator){
      pAllocator = RAllocator::BlockAllocatorAlloc(size);
      _pBlockAllocators->Set(size, pAllocator);
   }
   return pAllocator->Alloc(size);
}

//============================================================
// <T>�ռ��߳��ڴ�顣</T>
//
// @param pTypeName ����
// @param size �ڴ��С
// @param pFileName �ļ�����
// @param line �ļ��к�
// @return �ڴ��
//============================================================
TAny* FThreadMemory::Alloc(TCharC* pTypeName, TUint size, TChar8C* pFileName, TInt fileLine){
   FBlockAllocator* pAllocator = _pBlockAllocators->Get(size);
   if(NULL == pAllocator){
      pAllocator = RAllocator::BlockAllocatorAlloc(size);
      _pBlockAllocators->Set(size, pAllocator);
   }
   return pAllocator->Alloc(NULL, pTypeName, size, pFileName, fileLine);
}

//============================================================
// <T>�ͷ��߳��ڴ�顣</T>
//
// @param pMemory �ڴ����
//============================================================
void FThreadMemory::Free(TAny* pMemory){
   MO_ASSERT(pMemory);
   // ��õ�ǰʹ�õ�ʵ��
   TInt* pAlloc = ((TInt*)pMemory) - 1;
   IAllocator* pAllocator = (IAllocator*)pAlloc[0];
   // �ͷ������ڴ��
   pAllocator->Free(pMemory);
}

MO_NAMESPACE_END
