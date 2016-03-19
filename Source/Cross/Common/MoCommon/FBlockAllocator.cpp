#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ڴ�ʵ����</T>
//
// @param typeSize ԭ�Ӵ�С
//============================================================
FBlockAllocator::FBlockAllocator(TInt blockSize){
   MO_CLEAR(_pName);
   _count = 0;
   _blockSize = blockSize;
   _pEntries = MO_CREATE(FMemoryEntryList);
//   MO_CLEAR(_pAlloc);
//   MO_CLEAR(_pFirst);
//   MO_CLEAR(_pLast);
//   MO_CLEAR(_pUnused);
   //_total = 0;
   //_memoryTotal = 0;
}

//============================================================
// <T>�������ڴ�ʵ����</T>
//============================================================
FBlockAllocator::~FBlockAllocator(){
   // ɾ�������ռ�����
//   while(NULL != _pAlloc){
//      TAny* pMemory = _pAlloc->pAlloc;
//      _pAlloc = _pAlloc->pNext;
//      MO_ALIGNED_FREE(pMemory);
//   }
   MO_DELETE(_pEntries);
}

//============================================================
// <T>��չԭ���ڴ档</T>
// <P>�ռ��ڴ�ĵ�һ��Ϊ�ռ������ڶ��鿪ʼΪǰ����Ϊ����Ϣ���󲿷�Ϊ��������</P>
//
// @param pEntry �ڴ�ԭ��ʵ��
//============================================================
void FBlockAllocator::EntryExtend(){
//   MO_ASSERT(_blockSize > 0);
//   // ����Ҫ�ռ��ĸ�����ʹҪ�ռ����ڴ澡������ҳ��
//   TInt atomSize = sizeof(SMemoryEntry) + sizeof(TInt) + _blockSize;
//   // TODO: TInt pageSize = getpagesize();
//   TInt pageSize = 8192;
//   TInt count = MO_MAX((pageSize - sizeof(SMemoryEntry)) / atomSize, MO_OBJECT_CAPACITY);
//   TUint allocSize = sizeof(SMemoryEntry) + atomSize * count;
//   //_total += count;
//   //_memoryTotal += allocSize;
//   // �ռ��ڴ�
//   TByte* pMemory = (TByte*)MO_ALIGNED_ALLOC(allocSize, sizeof(TInt));
//   MO_ASSERT(pMemory);
//   memset(pMemory, 0, allocSize);
//   // �����һ���ڴ���
//   SMemoryEntry* pAllocAtom = (SMemoryEntry*)pMemory;
//   pAllocAtom->pMemory = pMemory;
//   pMemory += sizeof(SMemoryEntry);
//   // ѹ�����ռ���
//   if(NULL != _pAlloc){
//      _pAlloc->pPrior = pAllocAtom;
//   }
//   pAllocAtom->pNext = _pAlloc;
//   _pAlloc = pAllocAtom;
//   // ��ʼ�������ڴ�ԭ��
//   while(--count >= 0){
//      // ����ʼ��
//      SMemoryEntry* pEntry = (SMemoryEntry*)pMemory;
//      pEntry->pAllocator = this;
//      //pEntry->Link(pMemory + sizeof(SMemoryEntry), _atomSize);
//      pMemory += atomSize;
//      // ѹ��δʹ�õĶ���
//      if(NULL != _pUnused){
//         _pUnused->pPrior = pEntry;
//      }
//      pEntry->pNext = _pUnused;
//      _pUnused = pEntry;
//   }
}

//============================================================
// <T>������ڵ�ѹ��βλ�á�</T>
//
// @param pEntry �ڴ�ԭ��ʵ��
//============================================================
void FBlockAllocator::EntryPush(SMemoryEntry* pEntry){
//   MO_ASSERT(pEntry);
//   if(NULL == _pLast){
//      _pFirst = pEntry;
//   }else{
//      _pLast->pNext = pEntry;
//   }
//   pEntry->pPrior = _pLast;
//   _pLast = pEntry;
//   // ��������
//   _count++;
//   pEntry->pNext = NULL;
}

//============================================================
// <T>��������ɾ������ڵ㡣</T>
//
// @param pEntry �ڴ�ԭ��ʵ��
//============================================================
void FBlockAllocator::EntryRemove(SMemoryEntry* pEntry){
//   MO_ASSERT(pEntry);
//   SMemoryEntry* pPrior = pEntry->pPrior;
//   SMemoryEntry* pNext = pEntry->pNext;
//   // ����ǰ�ڵ�
//   if(NULL == pPrior){
//      _pFirst = pNext;
//   }else{
//      pPrior->pNext = pNext;
//   }
//   // �����ڵ�
//   if(NULL == pNext){
//      _pLast = pPrior;
//   }else{
//      pNext->pPrior = pPrior;
//   }
//   // ��������
//   _count--;
//   // �ͷŽڵ�
//   pEntry->pNext = _pUnused;
//   _pUnused = pEntry;
}

//============================================================
// <T>�ռ�һ���ڴ�ԭ��ʵ����</T>
//
// @return �ڴ�ԭ��ʵ��
//============================================================
SMemoryEntry* FBlockAllocator::EntryAlloc(){
//   // ���û�п�ʹ�õ��ڴ棬����չ������
//   if(NULL == _pUnused){
//      EntryExtend();
//   }
//   // ���һ�����õ������ڴ�
//   SMemoryEntry* pEntry = _pUnused;
//   _pUnused = pEntry->pNext;
//   // ѹ��ʹ���еĶ���
//   EntryPush(pEntry);
//   // ��¼�ռ�����
//   pEntry->Alloc();
//   // �����ռ����ڴ�
//   return pEntry;
   return NULL;
}

//============================================================
// <T>��ȡ�����ơ�</T>
//
// @return ������
//============================================================
TCharC* FBlockAllocator::Name(){
   return _pName;
}

//============================================================
// <T>���������ơ�</T>
//
// @param pName ������
//============================================================
void FBlockAllocator::SetName(TCharC* pName){
   _pName = pName;
}

//============================================================
// <T>��ȡ��ʹ���ڴ档</T>
//
// @return ��ʹ���ڴ�
//============================================================
TInt FBlockAllocator::GetMemoryUsed(){
   return _blockSize * _count;
}

//============================================================
// <T>��ȡ��ʹ���ڴ档</T>
//
// @return ��ʹ���ڴ�
//============================================================
TInt FBlockAllocator::GetMemoryTotal(){
   //return _memoryTotal;
   return 0;
}

//============================================================
// <T>�ռ�һ�鶨�����ڴ档</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
TAny* FBlockAllocator::Alloc(TInt size){
   SMemoryEntry* pEntry = EntryAlloc();
   MO_ASSERT(pEntry);
   return pEntry->pMemory;
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param pOwnerName ӵ��������
// @param pTypeName ��������
// @param size �ڴ��С
// @param pFileName �ļ�����
// @param lineNumber �ļ�����
// @return �ڴ�ָ��
//============================================================
TAny* FBlockAllocator::Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber){
   // MO_DEBUG("new %s(%d)\n", pTypeName, size);
   //MO_ASSERT(_blockSize == size);
   SMemoryEntry* pEntry = EntryAlloc();
   MO_ASSERT(pEntry);
   pEntry->SetTypeName(pTypeName);
   pEntry->SetFileInfo(pFileName, lineNumber);
   return pEntry->pMemory;
}

//============================================================
// <T>�ͷ��ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FBlockAllocator::Free(TAny* pMemory){
   // ��õ�ǰʹ�õ�ʵ��
   MO_ASSERT(pMemory);
   TInt* pAlloc = ((TInt*)pMemory) - 1;
   //SMemoryEntry* pEntry = MO_CAST_FORCE<TAny*, SMemoryEntry*>(pAlloc);
   SMemoryEntry* pEntry = (SMemoryEntry*)pAlloc[0];
   MO_ASSERT(pEntry);
   // ����ڴ�ת����ȷ��
   MO_ASSERT(pEntry->pAllocator == this);
   MO_ASSERT(pEntry->pMemory == pMemory);
   // ��¼�ͷŲ���
   pEntry->Free();
   _count--;
   // ѹ��δʹ�õĶ���
   EntryRemove(pEntry);
}

//============================================================
void FBlockAllocator::Dump(){
   //MO_TRACK("Size %08d memory is used. [used=%d, free=%d, total=%d, usedTotal=%d, allocTotal=%d]", _atomSize, _count, _total - _count, _total, GetMemoryUsed(), _memoryTotal);
//   SMemoryEntry* pEntry = _pFirst;
//   while(NULL != pEntry){
//      //MO_TRACK("-- Block [type=%s, alloc=%d/%d file=%s(%d)]", pEntry->pTypeName, pEntry->allocCount, pEntry->freeCount, pEntry->pFileName, pEntry->fileLine);
//      pEntry = pEntry->pNext;
//   }
}

//============================================================
FBlockLockAllocator::FBlockLockAllocator(TUint atomSize){
}

//============================================================
FBlockLockAllocator::~FBlockLockAllocator(){
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
TAny* FBlockLockAllocator::Alloc(TInt size){
   _locker.Enter();
   TAny* pMemory = FBlockAllocator::Alloc(size);
   _locker.Leave();
   return pMemory;
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param pOwnerName ӵ��������
// @param pTypeName ��������
// @param size �ڴ��С
// @param pFileName �ļ�����
// @param lineNumber �ļ�����
// @return �ڴ�ָ��
//============================================================
TAny* FBlockLockAllocator::Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber){
   _locker.Enter();
   TAny* pMemory = FBlockAllocator::Alloc(pOwnerName, pTypeName, size, pFileName, lineNumber);
   _locker.Leave();
   return pMemory;
}

//============================================================
// <T>�ͷ��ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FBlockLockAllocator::Free(TAny* pMemory){
   _locker.Enter();
   FBlockAllocator::Free(pMemory);
   _locker.Leave();
}

MO_NAMESPACE_END
