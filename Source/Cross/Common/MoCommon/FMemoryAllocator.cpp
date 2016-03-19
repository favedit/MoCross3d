#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ڴ�ʵ����</T>
//
// @param typeSize ԭ�Ӵ�С
//============================================================
FMemoryAllocator::FMemoryAllocator(){
   MO_CLEAR(_pAlloc);
}

//============================================================
// <T>�������ڴ�ʵ����</T>
//============================================================
FMemoryAllocator::~FMemoryAllocator(){
   // ɾ�������ռ�����
   /*while(NULL != _pUsed){
      SMemoryEntry* pAtom = _pUsed;
      _pUsed = _pUsed->pNext;
      MO_PTR_DELETE(pAtom);
   }*/
   // ɾ�������ռ�����
   while(NULL != _pAlloc){
      TAny* pMemory = _pAlloc->pMemory;
      _pAlloc = _pAlloc->pNext;
#ifdef _MO_WINDOWS
      _aligned_free(pMemory);
#else
      free(pMemory);
#endif
   }
}

//============================================================
// <T>��չԭ���ڴ档</T>
// <P>�ռ��ڴ�ĵ�һ��Ϊ�ռ������ڶ��鿪ʼΪǰ����Ϊ����Ϣ���󲿷�Ϊ��������</P>
//
// @param pEntry �ڴ�ԭ��ʵ��
//============================================================
void FMemoryAllocator::EntryExtend(){
   // ����Ҫ�ռ��ĸ���
   TInt atomSize = sizeof(SMemoryEntry);
   // TODO: TInt pageSize = getpagesize();
   TInt pageSize = 8192;
   TInt count = MO_LIB_MAX(pageSize / atomSize, MO_OBJECT_CAPACITY);
   // ��չ�ڴ�
   TUint allocSize = sizeof(SMemoryEntry) + atomSize * count;
   TByte* pMemory = (TByte*)MO_ALIGNED_ALLOC(allocSize, sizeof(TInt));
   MO_ASSERT(pMemory);
   memset(pMemory, 0, allocSize);
   // �����һ���ڴ���
   SMemoryEntry* pAllocAtom = (SMemoryEntry*)pMemory;
   pAllocAtom->pMemory = pMemory;
   // ѹ�����ռ���
   if(NULL != _pAlloc){
      _pAlloc->pPrior = pAllocAtom;
   }
   pAllocAtom->pNext = _pAlloc;
   _pAlloc = pAllocAtom;
   // ��ʼ�������ڴ�ԭ��
   pMemory += sizeof(SMemoryEntry);
   TInt n = -1;
   while(++n < count){
      // ����ʼ��
      SMemoryEntry* pEntry = (SMemoryEntry*)pMemory;
      pEntry->pAllocator = this;
      pMemory += atomSize;
      // ѹ��δʹ�õĶ���
      if(NULL != _pUnused){
         _pUnused->pPrior = pEntry;
      }
      pEntry->pNext = _pUnused;
      _pUnused = pEntry;
   }
}

//============================================================
// <T>�ռ�һ���ڴ�ԭ��ʵ����</T>
//
// @return �ڴ�ԭ��ʵ��
//============================================================
SMemoryEntry* FMemoryAllocator::EntryAlloc(){
   // ���û�п�ʹ�õ��ڴ棬����չ������
   if(NULL == _pUnused){
      EntryExtend();
   }
   // ���һ�����õ������ڴ�
   SMemoryEntry* pEntry = _pUnused;
   _pUnused = pEntry->pNext;
   // ѹ��ʹ���еĶ���
   //EntryPush(pEntry);
   // ��¼�ռ�����
   pEntry->Alloc();
   // �����ռ����ڴ�
   return pEntry;
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
TAny* FMemoryAllocator::Alloc(TInt size){
   MO_ASSERT(size > 0);
   SMemoryEntry* pEntry = EntryAlloc();
   MO_ASSERT(pEntry);
   TByte* pMemory = (TByte*)MO_ALIGNED_ALLOC(size, sizeof(TInt));
   pEntry->Link(pMemory, size);
   return pEntry->pMemory;
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param pOwnerName ӵ��������
// @param pTypeName ��������
// @param size �ڴ��С
// @param pFileName �ļ�����
// @param fileLine �ļ�����
// @return �ڴ�ָ��
//============================================================
TAny* FMemoryAllocator::Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber){
   MO_ASSERT(size > 0);
   SMemoryEntry* pEntry = EntryAlloc();
   MO_ASSERT(pEntry);
   TByte* pMemory = (TByte*)MO_ALIGNED_ALLOC(size, sizeof(TInt));
   pEntry->SetTypeName(pTypeName);
   pEntry->SetFileInfo(pFileName, lineNumber);
   pEntry->Link(pMemory, size);
   return pEntry->pMemory;
}

//============================================================
// <T>�ͷ��ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FMemoryAllocator::Free(TAny* pMemory){
   // ��õ�ǰʹ�õ�ʵ��
   MO_ASSERT(pMemory);
   TInt* pAlloc = ((TInt*)pMemory) - 1;
   SMemoryEntry* pEntry = (SMemoryEntry*)pAlloc[0];
   MO_ASSERT(pEntry);
   // ����ڴ�ת����ȷ��
   MO_ASSERT(pEntry->pAllocator == this);
   MO_ASSERT(pEntry->pMemory == pMemory);
   // �ͷ��ڴ�
   MO_ALIGNED_FREE(pEntry->pAlloc);
   // ��¼�ͷŲ���
   pEntry->Free();
   // ѹ��δʹ�õĶ���
   //MLinkedEntryC<SMemoryEntry*>::EntryFree(pEntry);
}

MO_NAMESPACE_END
