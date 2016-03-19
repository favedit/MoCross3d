#include "MoCmMemory.h"
#include "MoCmString8.h"

MO_NAMESPACE_BEGIN

//============================================================
TThreadLocker RAllocator::_locker;
IMemoryStorage* RAllocator::_pStorage = NULL;
FMemoryAllocator* RAllocator::_pMemoryAllocator = NULL;
FBlockAllocatorFreeSet* RAllocator::_pBlockAllocatorSet = NULL;
FBlockAllocatorFreeList* RAllocator::_pBlockAllocators = NULL;
FBlockLockAllocatorFreeList* RAllocator::_pBlockLockAllocators = NULL;

//============================================================
// <T>�����ڴ��ռ�����</T>
//============================================================
void RAllocator::Create(){
   _pStorage = MO_MEM_CREATE(FAllocatorStorage);
   // �����������ڴ��ռ���
//   _pMemoryAllocator = MO_MEM_CREATE(FMemoryLockAllocator);
//   // �������ڴ��б�
//   _pBlockAllocatorSet = MO_MEM_CREATE(FBlockAllocatorFreeSet);
//   // �������ڴ��б�
//   _pBlockAllocators = MO_MEM_CREATE(FBlockAllocatorFreeList);
//   // �����������ڴ��б�
//   _pBlockLockAllocators = MO_MEM_CREATE(FBlockLockAllocatorFreeList);
}

//============================================================
// <T>�ͷ��ڴ��ռ�����</T>
//============================================================
void RAllocator::Destroy(){
//   // �ͷ����м������ڴ��б�
//   if(!_pBlockLockAllocators->IsEmpty()){
//      TListIteratorC<FBlockLockAllocator*> iterator = _pBlockLockAllocators->IteratorC();
//      while(iterator.Next()){
//         FBlockLockAllocator* pBlockLockAllocator = iterator.Get();
//         MO_MEM_DELETE(pBlockLockAllocator);
//      }
//   }
//   MO_PTR_DELETE(_pBlockLockAllocators);
//   // �ͷ����п��ڴ��б�
//   if(!_pBlockAllocatorSet->IsEmpty()){
//      TSetIterator<TUint, FBlockAllocator*> iterator = _pBlockAllocatorSet->IteratorC();
//      while(iterator.Next()){
//         FBlockAllocator* pBlockAllocator = iterator.Value();
//         MO_MEM_DELETE(pBlockAllocator);
//      }
//   }
//   MO_PTR_DELETE(_pBlockAllocatorSet);
//   // �ͷ����п��ڴ��б�
//   if(!_pBlockAllocators->IsEmpty()){
//      TListIteratorC<FBlockAllocator*> iterator = _pBlockAllocators->IteratorC();
//      while(iterator.Next()){
//         FBlockAllocator* pBlockAllocator = iterator.Get();
//         MO_MEM_DELETE(pBlockAllocator);
//      }
//   }
//   MO_MEM_DELETE(_pBlockAllocators);
//   // �ͷŲ������ڴ��ռ���
//   MO_MEM_DELETE(_pMemoryAllocator);
//   // ����ɾ����������
//   FAllocatorStorage* pStorage = _pStorage;
//   _pStorage = NULL;
   MO_MEM_DELETE(_pStorage);
}

//============================================================
// <T>��ô洢����</T>
//
// @return �洢��
//============================================================
IMemoryStorage* RAllocator::Storage(){
   return _pStorage;
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
TAny* RAllocator::Alloc(TUint size){
#ifdef _MO_DEBUG
   if(NULL != _pStorage){
      return _pStorage->Alloc(NULL, NULL, (TInt)size, NULL, 0);
   }else{
      TAny* pAlloc = malloc(sizeof(TAny*) + size);
      *(TInt*)pAlloc = 0;
      return (TByte*)pAlloc + sizeof(TAny*);
   }
#else
   return malloc(size);
#endif // _DEBUG
};

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param pTypeName ��������
// @param size �ڴ��С
// @param pFileName �ļ�����
// @param lineNumber �ļ�����
// @return �ڴ�ָ��
//============================================================
TAny* RAllocator::Alloc(TChar8C* pTypeName, TUint size, TChar8C* pFileName, TInt lineNumber){
#ifdef _MO_DEBUG
   if(NULL != _pStorage){
      return _pStorage->Alloc(NULL, pTypeName, (TInt)size, pFileName, lineNumber);
   }else{
      TAny* pAlloc = malloc(sizeof(TAny*) + size);
      *(TInt*)pAlloc = 0;
      return (TByte*)pAlloc + sizeof(TAny*);
   }
#else
   return malloc(size);
#endif // _DEBUG
};

//============================================================
// <T>�ͷ��ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void RAllocator::Free(TAny* pMemory){
   MO_ASSERT(pMemory);
#ifdef _MO_DEBUG
   if(NULL != _pStorage){
      _pStorage->Free(pMemory);
   }else{
      TAny* pAlloc = (TByte*)pMemory - sizeof(TAny*);
      free(pAlloc);
   }
#else
   free(pMemory);
#endif // _DEBUG
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
TAny* RAllocator::TypeAlloc(TUint size){
#ifdef _MO_DEBUG
   if(NULL != _pStorage){
      return _pStorage->Alloc(NULL, NULL, (TInt)size, NULL, 0);
   }else{
      TAny* pAlloc = malloc(sizeof(TAny*) + size);
      *(TInt*)pAlloc = 0;
      return (TByte*)pAlloc + sizeof(TAny*);
   }
#else
   return malloc(size);
#endif // _DEBUG
};

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param pTypeName ��������
// @param size �ڴ��С
// @param pFileName �ļ�����
// @param lineNumber �ļ�����
// @return �ڴ�ָ��
//============================================================
TAny* RAllocator::TypeAlloc(TChar8C* pTypeName, TUint size, TChar8C* pFileName, TInt lineNumber){
#ifdef _MO_DEBUG
   if(NULL != _pStorage){
      return _pStorage->Alloc(NULL, pTypeName, (TInt)size, pFileName, lineNumber);
   }else{
      TAny* pAlloc = malloc(sizeof(TAny*) + size);
      *(TInt*)pAlloc = 0;
      return (TByte*)pAlloc + sizeof(TAny*);
   }
#else
   return malloc(size);
#endif // _DEBUG
};

//============================================================
// <T>�ͷ��ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void RAllocator::TypeFree(TAny* pMemory){
   MO_ASSERT(pMemory);
#ifdef _MO_DEBUG
   if(NULL != _pStorage){
      _pStorage->Free(pMemory);
   }else{
      TAny* pAlloc = (TByte*)pMemory - sizeof(TAny*);
      free(pAlloc);
   }
#else
   free(pMemory);
#endif // _DEBUG
}

//============================================================
FBlockAllocator* RAllocator::BlockAllocatorAlloc(TInt size){
   FBlockAllocator* pAllocator = MO_PTR_CREATE(FBlockAllocator, size);
   _locker.Enter();
   _pBlockAllocators->Push(pAllocator);
   _locker.Leave();
   return pAllocator;
}

//============================================================
void RAllocator::BlockAllocatorFree(FBlockAllocator* pAllocator){
   MO_ASSERT(pAllocator);
   _locker.Enter();
   _pBlockAllocators->Remove(pAllocator);
   _locker.Leave();
   MO_PTR_DELETE(pAllocator);
}

//============================================================
FBlockLockAllocator* RAllocator::BlockLockAllocatorAlloc(TInt size){
   FBlockLockAllocator* pAllocator = MO_PTR_CREATE(FBlockLockAllocator, size);
   _locker.Enter();
   _pBlockLockAllocators->Push(pAllocator);
   _locker.Leave();
   return pAllocator;
}

//============================================================
void RAllocator::BlockLockAllocatorFree(FBlockLockAllocator* pAllocator){
   MO_ASSERT(pAllocator);
   _locker.Enter();
   _pBlockLockAllocators->Remove(pAllocator);
   _locker.Leave();
   MO_PTR_DELETE(pAllocator);
}

//============================================================
TBool RAllocator::CalculateStatistics(TUint& used, TUint& total){
   used = 0;
   total = 0;
   // �Ǽ����ڴ�������Ϣ
   if(!_pBlockAllocators->IsEmpty()){
      TListIteratorC<FBlockAllocator*> iterator = _pBlockAllocators->IteratorC();
      while(iterator.Next()){
         FBlockAllocator* pAllocator = iterator.Get();
         used += pAllocator->GetMemoryUsed();
         total += pAllocator->GetMemoryTotal();
      }
   }
   // �����ڴ�������Ϣ
   if(!_pBlockLockAllocators->IsEmpty()){
      TListIteratorC<FBlockLockAllocator*> iterator = _pBlockLockAllocators->IteratorC();
      while(iterator.Next()){
         FBlockLockAllocator* pAllocator = iterator.Get();
         used += pAllocator->GetMemoryUsed();
         total += pAllocator->GetMemoryTotal();
      }
   }
   return ETrue;
}

//============================================================
void RAllocator::DumpTrack(){
   TInt memoryUsed = 0;
   TInt memoryTotal = 0;
   //MO_STATIC_TRACK("-- Track memory - %s --------------------------------------", "begin");
   // �Ǽ����ڴ�������Ϣ
   if(!_pBlockAllocators->IsEmpty()){
      TListIteratorC<FBlockAllocator*> iterator = _pBlockAllocators->IteratorC();
      while(iterator.Next()){
         FBlockAllocator* pAllocator = iterator.Get();
         memoryUsed += pAllocator->GetMemoryUsed();
         memoryTotal += pAllocator->GetMemoryTotal();
         pAllocator->Dump();
      }
   }
   // �����ڴ�������Ϣ
   if(!_pBlockLockAllocators->IsEmpty()){
      TListIteratorC<FBlockLockAllocator*> iterator = _pBlockLockAllocators->IteratorC();
      while(iterator.Next()){
         FBlockLockAllocator* pAllocator = iterator.Get();
         memoryUsed += pAllocator->GetMemoryUsed();
         memoryTotal += pAllocator->GetMemoryTotal();
         pAllocator->Dump();
      }
   }
   //MO_STATIC_TRACK("-- Track memory - end -- used=0x%08X, total=0x%08X ------------------", memoryUsed, memoryTotal);
}

MO_NAMESPACE_END
