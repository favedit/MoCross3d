#include "MoCmSharedList.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲������ڵ��ռ�����</T>
//============================================================
FSharedListAllocator::FSharedListAllocator(){
   _capacity = 0;
   _entryCapacity = 0;
   _gHead = NULL;
   _gLists = 0;
   _gEntries = NULL;
}

//============================================================
// <T>��������������</T>
//============================================================
void FSharedListAllocator::SetCapacity(TInt capacity){
   _capacity = capacity;
}

//============================================================
// <T>���ýڵ�������</T>
//============================================================
void FSharedListAllocator::SetEntryCapacity(TInt entryCapacity){
   _entryCapacity = entryCapacity;
}

//============================================================
// <T>�����ڴ��ʼ����</T>
//============================================================
void FSharedListAllocator::OnSharedInitialize(){
   // ��ʼ��ͷ��Ϣ
   _gHead->listCount = 0;
   _gHead->listUnused = 0;
   _gHead->entryCount = 0;
   _gHead->entryUnused = 0;
   // ��ʼ������ͷ��Ϣ
   for(TInt32 n = 0; n < _capacity; n++){
      SSharedListHead& list = _gLists[n];
      list.count = 0;
      list.index = n;
      list.first = -1;
      list.last = -1;
      list.prior = n - 1;
      list.next = (_capacity - 1 == n) ? -1 : n + 1;
   }
   // ��ʼ������ڵ���Ϣ
   for(TInt32 n = 0; n < _entryCapacity; n++){
      SSharedListEntry& entry = _gEntries[n];
      entry.list = -1;
      entry.index = n;
      entry.prior = n - 1;
      entry.next = (_entryCapacity - 1 == n) ? -1 : n + 1;
      entry.code = -1;
   }
}

//============================================================
// <T>���乲���ڴ档</T>
//============================================================
void FSharedListAllocator::OnSharedLink(TShareSegment& segment){
   MO_ASSERT(_capacity > 0);
   MO_ASSERT(_entryCapacity > 0);
   _gHead = segment.TypeAlloc<SHead>();
   _gLists = segment.TypeAlloc<SSharedListHead>(_capacity);
   _gEntries = segment.TypeAlloc<SSharedListEntry>(_entryCapacity);
}

//============================================================
// <T>���㹲���ڴ��С��</T>
//============================================================
TSize FSharedListAllocator::SharedCapacity(){
   TSize capacity = sizeof(SHead);
   capacity += sizeof(SSharedListHead) * _capacity;
   capacity += sizeof(SSharedListEntry) * _entryCapacity;
   return capacity;
}

//============================================================
// <T>�ռ�һ��δʹ�õ�����</T>
//============================================================
SSharedListHead* FSharedListAllocator::AllocList(){
   // ���δʹ�õ�����
   TInt index = _gHead->listUnused;
   MO_ASSERT(index >= 0);
   _gHead->listUnused = _gLists[index].next;
   _gHead->listCount++;
   return &_gLists[index];
}

//============================================================
// <T>�ͷ�һ������</T>
//============================================================
void FSharedListAllocator::FreeList(SSharedListHead* pList){
   MO_ASSERT(pList);
   TInt index = pList->index;
   pList->first = -1;
   pList->last = -1;
   _gLists[index].next = _gHead->listUnused;
   _gHead->listUnused = index;
   _gHead->listCount--;
}

//============================================================
// <T>�ռ�һ���ڵ㡣</T>
//============================================================
SSharedListEntry& FSharedListAllocator::AllocEntry(){
   // ���δʹ�õ�����
   TInt index = _gHead->entryUnused;
   MO_ASSERT(index >= 0);
   SSharedListEntry& entry = _gEntries[index];
   _gHead->entryUnused = entry.next;
   _gHead->entryCount++;
   return entry;
}

//============================================================
// <T>�ͷ�һ������λ�á�</T>
//============================================================
void FSharedListAllocator::FreeEntry(SSharedListEntry& entry){
   TInt index = entry.index;
   _gEntries[index].next = _gHead->entryUnused;
   _gHead->entryUnused = index;
   _gHead->entryCount--;
}

//============================================================
// <T>�ͷ�һ����������</T>
//============================================================
void FSharedListAllocator::FreeEntries(SSharedListHead* pList){
   if(pList->count > 0){
      _gEntries[pList->last].next = _gHead->entryUnused;
      _gHead->entryUnused = pList->first;
      _gHead->entryCount -= pList->count;
   }
}

MO_NAMESPACE_END
