#ifndef __MO_CM_POOL_H__
#define __MO_CM_POOL_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_ENTRY_H__
#include "MoCmEntry.h"
#endif // __MO_CM_ENTRY_H__

#ifndef __MO_CM_VECTOR_H__
#include "MoCmVector.h"
#endif // __MO_CM_VECTOR_H__

#ifndef __MO_CM_LIST_H__
#include "MoCmList.h"
#endif // __MO_CM_LIST_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>ʵ���ض���</T>
//
// @struct
//============================================================
enum EInstancedFlag{
   EInstancedFlag_Unknown = 0,
   EInstancedFlag_Using   = 1,
};

//============================================================
// <T>���󻺳�ء�</T>
//
// @history 130320 MAOCY ����
//============================================================
template <typename T>
class MPool{
public:
   typedef FList<T> FItemList;
protected:
   FItemList* _pUsingItems;
   FItemList* _pFreeItems;
public:
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MPool(){
      _pUsingItems = MO_CREATE(FItemList);
      _pFreeItems = MO_CREATE(FItemList);
   }
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MO_ABSTRACT ~MPool(){
      MO_DELETE(_pFreeItems);
      MO_DELETE(_pUsingItems);
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ��ж���</T>
   MO_INLINE TBool HasItem(){
      TBool hasUsing = !_pUsingItems->IsEmpty();
      TBool hasFree = !_pFreeItems->IsEmpty();
      return hasUsing | hasFree;
   }
   //------------------------------------------------------------
   // <T>��ö��������</T>
   MO_INLINE TInt Count(){
      TInt usingCount = _pUsingItems->Count();
      TInt freeCount = _pFreeItems->Count();
      return usingCount + freeCount;
   }
   //------------------------------------------------------------
   // <T>����Ƿ���ʹ�ö���</T>
   MO_INLINE TBool HasUsingItem(){
      return !_pUsingItems->IsEmpty();
   }
   //------------------------------------------------------------
   // <T>���ʹ�ö��󼯺ϡ�</T>
   MO_INLINE FItemList* UsingItems(){
      return _pUsingItems;
   }
   //------------------------------------------------------------
   // <T>���ʹ�ö��������</T>
   MO_INLINE TInt UsingCount(){
      return _pUsingItems->Count();
   }
   //------------------------------------------------------------
   // <T>����Ƿ��п��ж���</T>
   MO_INLINE TBool HasFreeItem(){
      return !_pFreeItems->IsEmpty();
   }
   //------------------------------------------------------------
   // <T>��ÿ��ж��������</T>
   MO_INLINE TInt FreeCount(){
      return _pFreeItems->Count();
   }
   //------------------------------------------------------------
   // <T>��ÿ��ж��󼯺ϡ�</T>
   MO_INLINE FItemList* FreeItems(){
      return _pFreeItems;
   }
public:
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   T Store(T pItem){
      MO_CHECK(pItem, return pItem);
#ifdef _MO_DEBUG
      if(NULL != pItem){
         if(!_pFreeItems->Contains(pItem)){
            _pFreeItems->Push(pItem);
         }else{
            MO_ERROR(TC("Storage item is already exists. (using_count=%d, free_count=%d)"),
                  _pUsingItems->Count(), _pFreeItems->Count());
         }
      }
#else
      _pFreeItems->Push(pItem);
#endif // _MO_DEBUG
      return pItem;
   }
   //------------------------------------------------------------
   // <T>���ײ��ռ�һ������</T>
   T AllocFirst(){
      T pItem = NULL;
      if(!_pFreeItems->IsEmpty()){
         pItem = _pFreeItems->Shift();
         _pUsingItems->Push(pItem);
      }else{
         MO_ERROR(TC("Free item is empty. alloc item failure. (using_count=%d, free_count=%d)"),
               _pUsingItems->Count(), _pFreeItems->Count());
      }
      return pItem;
   }
   //------------------------------------------------------------
   // <T>��β���ռ�һ������</T>
   T AllocLast(){
      T pItem = NULL;
      if(!_pFreeItems->IsEmpty()){
         pItem = _pFreeItems->Pop();
         _pUsingItems->Push(pItem);
      }else{
         MO_ERROR(TC("Free item is empty. alloc item failure. (using_count=%d, free_count=%d)"),
               _pUsingItems->Count(), _pFreeItems->Count());
      }
      return pItem;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻���������</T>
   TBool FreeFirst(T pItem){
      MO_CHECK(pItem, return EFalse);
      // ��ʹ�ü����Ƴ�
#ifdef _MO_DEBUG
      if(_pUsingItems->Contains(pItem)){
         _pUsingItems->Remove(pItem);
      }else{
         MO_ERROR(TC("Free item is not exists in use collection. (using_count=%d, free_count=%d)"),
               _pUsingItems->Count(), _pFreeItems->Count());
      }
      // �����ͷż�����
      if(!_pFreeItems->Contains(pItem)){
         _pFreeItems->Unshift(pItem);
      }else{
         MO_ERROR(TC("Free item is already exists in free collection. (using_count=%d, free_count=%d)"),
               _pUsingItems->Count(), _pFreeItems->Count());
      }
#else
      _pUsingItems->Remove(pItem);
      _pFreeItems->Unshift(pItem);
#endif // _MO_DEBUG
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻������ײ���</T>
   TBool FreeLast(T pItem){
      MO_CHECK(pItem, return EFalse);
      // ��ʹ�ü����Ƴ�
#ifdef _MO_DEBUG
      if(_pUsingItems->Contains(pItem)){
         _pUsingItems->Remove(pItem);
      }else{
         MO_ERROR(TC("Free item is not exists in use collection. (using_count=%d, free_count=%d)"),
               _pUsingItems->Count(), _pFreeItems->Count());
      }
      // �����ͷż�����
      if(!_pFreeItems->Contains(pItem)){
         _pFreeItems->Push(pItem);
      }else{
         MO_ERROR(TC("Free item is already exists in free collection. (using_count=%d, free_count=%d)"),
               _pUsingItems->Count(), _pFreeItems->Count());
      }
#else
      _pUsingItems->Remove(pItem);
      _pFreeItems->Push(pItem);
#endif // _MO_DEBUG
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�Ƴ�һ������</T>
   TBool Remove(T pItem){
      MO_CHECK(pItem, return EFalse);
      // �Ƴ�ʹ���ж���
      _pUsingItems->Remove(pItem);
      // �Ƴ������ж���
      _pFreeItems->Remove(pItem);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�ͷ����ж���</T>
   void Clear(){
      _pUsingItems->Clear();
      _pFreeItems->Clear();
   }
   //------------------------------------------------------------
   // <T>�ͷ����ж���</T>
   void Release(){
      // ɾ������ʹ�ö���
      if(!_pUsingItems->IsEmpty()){
         TListIteratorC<T> iterator = _pUsingItems->IteratorC();
         while(iterator.Next()){
            T pItem = *iterator;
            MO_DELETE(pItem);
         }
         _pUsingItems->Clear();
      }
      // ɾ���������ɶ���
      if(!_pFreeItems->IsEmpty()){
         TListIteratorC<T> iterator = _pFreeItems->IteratorC();
         while(iterator.Next()){
            T pItem = *iterator;
            MO_DELETE(pItem);
         }
         _pFreeItems->Clear();
      }
   }
};

//============================================================
// <T>�䳤���󻺳�ء�</T>
//
// @tool
//============================================================
template <typename T>
class TPool : public MPool<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤����ء�</T>
   TPool(){
   }
   //------------------------------------------------------------
   // <T>�����䳤����ء�</T>
   ~TPool(){
   }
};

//============================================================
// <T>�䳤���󻺳�ء�</T>
//
// @class
//============================================================
template <typename T>
class FPool :
      public FObject,
      public MPool<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   FPool(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   ~FPool(){
   }
};

//============================================================
// <T>����洢����ء�</T>
//
// @history 130320 MAOCY ����
//============================================================
template <typename T>
class MStoragePool{
public:
   typedef FList<T> FItemList;
   typedef FVector<T> FItemVector;
protected:
   FItemList* _pItems;
   FItemList* _pUsingItems;
   FItemList* _pFreeItems;
   FItemVector* _pStorage;
public:
   //------------------------------------------------------------
   // <T>�������洢����ء�</T>
   MStoragePool(){
      _pItems = MO_CREATE(FItemList);
      _pUsingItems = MO_CREATE(FItemList);
      _pFreeItems = MO_CREATE(FItemList);
      _pStorage = MO_CREATE(FItemVector);
   }
   //------------------------------------------------------------
   // <T>��������洢����ء�</T>
   MO_ABSTRACT ~MStoragePool(){
      MO_DELETE(_pItems);
      MO_DELETE(_pUsingItems);
      MO_DELETE(_pFreeItems);
      MO_DELETE(_pStorage);
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ��ж���</T>
   MO_INLINE TBool HasItem(){
      return !_pItems->IsEmpty();
   }
   //------------------------------------------------------------
   // <T>��ö��������</T>
   MO_INLINE TInt Count(){
      return _pItems->Count();
   }
   //------------------------------------------------------------
   // <T>��ö��󼯺ϡ�</T>
   MO_INLINE FItemList* Items(){
      return _pItems;
   }
   //------------------------------------------------------------
   // <T>����Ƿ���ʹ�ö���</T>
   MO_INLINE TBool HasUsingItem(){
      return !_pUsingItems->IsEmpty();
   }
   //------------------------------------------------------------
   // <T>���ʹ�ö��������</T>
   MO_INLINE TInt UsingCount(){
      return _pUsingItems->Count();
   }
   //------------------------------------------------------------
   // <T>���ʹ�ö��󼯺ϡ�</T>
   MO_INLINE FItemList* UsingItems(){
      return _pUsingItems;
   }
   //------------------------------------------------------------
   // <T>����Ƿ��п��ж���</T>
   MO_INLINE TBool HasFreeItem(){
      return !_pFreeItems->IsEmpty();
   }
   //------------------------------------------------------------
   // <T>������ɶ��������</T>
   MO_INLINE TInt FreeCount(){
      return _pFreeItems->Count();
   }
   //------------------------------------------------------------
   // <T>��ÿ��ж��󼯺ϡ�</T>
   MO_INLINE FItemList* FreeItems(){
      return _pFreeItems;
   }
   //------------------------------------------------------------
   // <T>��ô洢�б�</T>
   MO_INLINE FItemVector* Storage(){
      return _pStorage;
   }
public:
   //------------------------------------------------------------
   // <T>�����������Ҷ���</T>
   MO_INLINE T* FindByIndex(TInt index){
      return _pStorage->Nvl(index, NULL);
   }
   //------------------------------------------------------------
   // <T>����������ö���</T>
   MO_INLINE T* GetByIndex(TInt index){
      return _pStorage->Get(index);
   }
public:
   //------------------------------------------------------------
   // <T>�����һ�����õ�������</T>
   TInt FindNextIndex(TBool checked = ETrue){
      // ���Ҵ��ںͿɷŵ�
      TInt count = _pStorage->Count();
      if(checked){
         for(TInt n = 0; n < count; n++){
            T pFind = _pStorage->Get(n);
            if(NULL == pFind){
               return n;
            }
         }
      }
      // ����λ��
      return count;
   }
   //------------------------------------------------------------
   // <T>�洢����</T>
   TInt Store(T pItem, TBool checked = ETrue){
      MO_ASSERT(pItem);
      // ���뼯��
      _pItems->Push(pItem);
      // �������ɼ���
      _pFreeItems->Push(pItem);
      // ����洢����
      TInt index = -1;
      if(checked){
         index = StorageStore(pItem);
      }else{
         index = _pStorage->Count();
         _pStorage->Push(pItem);
      }
      return index;
   }
   //------------------------------------------------------------
   // <T>�洢�����ڴ洢�����С�</T>
   TInt StorageStore(T pItem){
      MO_ASSERT(pItem);
      // ���Ҵ��ںͿɷŵ�
      TInt findIndex = -1;
      TInt count = _pStorage->Count();
      for(TInt n = 0; n < count; n++){
         T pFind = _pStorage->Get(n);
         if(NULL == pFind){
            if(-1 == findIndex){
               findIndex = n;
            }
         }else if(pFind == pItem){
            return n;
         }
      }
      // ����λ��
      TInt index = -1;
      if(-1 == findIndex){
         index = _pStorage->Count();
         _pStorage->Push(pItem);
      }else{
         index = findIndex;
         _pStorage->Set(findIndex, pItem);
      }
      return index;
   }
   //------------------------------------------------------------
   // <T>�洢�����ڴ洢�����С�</T>
   TInt StorageRemove(T pItem){
      MO_ASSERT(pItem);
      // ���Ҵ��ںͿɷŵ�
      TBool result = EFalse;
      TInt count = _pStorage->Count();
      for(TInt n = 0; n < count; n++){
         T pFind = _pStorage->Get(n);
         if(pFind == pItem){
            _pStorage->Set(n, NULL);
            result = ETrue;
         }
      }
      return result;
   }
   //------------------------------------------------------------
   // <T>���ײ��ռ�һ������</T>
   T AllocFirst(){
      T pItem = NULL;
      if(!_pFreeItems->IsEmpty()){
         pItem = _pFreeItems->Shift();
         _pUsingItems->Push(pItem);
      }else{
         MO_FATAL(TC("Free item is empty. alloc item failure. (total=%d, used=%d, free=%d)"),
               _pItems->Count(), _pUsingItems->Count(), _pFreeItems->Count());
      }
      return pItem;
   }
   //------------------------------------------------------------
   // <T>��β���ռ�һ������</T>
   T AllocLast(){
      T pItem = NULL;
      if(!_pFreeItems->IsEmpty()){
         pItem = _pFreeItems->Pop();
         _pUsingItems->Push(pItem);
      }else{
         MO_FATAL(TC("Free item is empty. alloc item failure. (total=%d, used=%d, free=%d)"),
               _pItems->Count(), _pUsingItems->Count(), _pFreeItems->Count());
      }
      return pItem;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻���������</T>
   void FreeFirst(T pItem){
      MO_ASSERT(pItem);
      if(!_pUsingItems->Contains(pItem)){
         MO_FATAL(TC("Free item is not exists collection. (total=%d, used=%d, free=%d)"),
               _pItems->Count(), _pUsingItems->Count(), _pFreeItems->Count());
      }
      _pUsingItems->Remove(pItem);
      _pFreeItems->Unshift(pItem);
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻������ײ���</T>
   void FreeLast(T pItem){
      MO_ASSERT(pItem);
      if(!_pUsingItems->Contains(pItem)){
         MO_FATAL(TC("Free item is not exists collection. (total=%d, used=%d, free=%d)"),
               _pItems->Count(), _pUsingItems->Count(), _pFreeItems->Count());
      }
      _pUsingItems->Remove(pItem);
      _pFreeItems->Push(pItem);
   }
   //------------------------------------------------------------
   // <T>�Ƴ�һ������</T>
   void Remove(T pItem){
      MO_ASSERT(pItem);
      // �Ƴ�����
      _pItems->Remove(pItem);
      // �Ƴ�ʹ���ж���
      _pUsingItems->Remove(pItem);
      // �Ƴ������ж���
      _pFreeItems->Remove(pItem);
      // �������
      StorageRemove(pItem);
   }
   //------------------------------------------------------------
   // <T>������ж���</T>
   void Clear(){
      _pItems->Clear();
      _pUsingItems->Clear();
      _pFreeItems->Clear();
      _pStorage->Clear();
   }
   //------------------------------------------------------------
   // <T>�ͷ����ж���</T>
   void Release(){
      // ɾ�������Ӷ���
      TListIteratorC<T> iterator = _pItems->IteratorC();
      while(iterator.Next()){
         T pItem = *iterator;
         MO_DELETE(pItem);
      }
      // ��ռ���
      _pItems->Clear();
      _pUsingItems->Clear();
      _pFreeItems->Clear();
      _pStorage->Clear();
   }
};

//============================================================
// <T>�䳤���󻺳�ء�</T>
//
// @tool
//============================================================
template <typename T>
class TStoragePool : public MStoragePool<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤����ء�</T>
   TStoragePool(){
   }
   //------------------------------------------------------------
   // <T>�����䳤����ء�</T>
   ~TStoragePool(){
   }
};

//============================================================
// <T>�䳤���󻺳�ء�</T>
//
// @class
//============================================================
template <typename T>
class FStoragePool :
      public FObject,
      public MStoragePool<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   FStoragePool(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   ~FStoragePool(){
   }
};

//============================================================
// <T>������ڻ��ࡣ</T>
//
// @struct
//============================================================
class MO_CM_DECLARE MObjectEntry{
protected:
   TInt16 _entryType;
   TInt16 _entryFlag;
   MObjectEntry* _pEntryPrior;
   MObjectEntry* _pEntryNext;
public:
   //------------------------------------------------------------
   // <T>���������ڻ��ࡣ</T>
   MObjectEntry(){
      _entryType = 0;
      _entryFlag = 0;
      MO_CLEAR(_pEntryPrior);
      MO_CLEAR(_pEntryNext);
   }
public:
   //------------------------------------------------------------
   // <T>���������͡�</T>
   MO_INLINE TInt EntryType(){
      return _entryType;
   }
   //------------------------------------------------------------
   // <T>����������͡�</T>
   MO_INLINE void SetEntryType(TInt entryType){
      _entryType = (TInt16)entryType;
   }
   //------------------------------------------------------------
   // <T>�����ڱ�־��</T>
   MO_INLINE TInt EntryFlag(){
      return _entryFlag;
   }
   //------------------------------------------------------------
   // <T>������ڱ�־��</T>
   MO_INLINE void SetEntryFlag(TInt entryFlag){
      _entryFlag = (TInt16)entryFlag;
   }
   //------------------------------------------------------------
   // <T>������ǰһ����</T>
   MO_INLINE MObjectEntry* EntryPrior(){
      return _pEntryPrior;
   }
   //------------------------------------------------------------
   // <T>�������ǰһ����</T>
   MO_INLINE void SetEntryPrior(MObjectEntry* pEntryPrior){
      _pEntryPrior = pEntryPrior;
   }
   //------------------------------------------------------------
   // <T>�����ں�һ����</T>
   MO_INLINE MObjectEntry* EntryNext(){
      return _pEntryNext;
   }
   //------------------------------------------------------------
   // <T>������ں�һ����</T>
   MO_INLINE void SetEntryNext(MObjectEntry* pEntryNext){
      _pEntryNext = pEntryNext;
   }
public:
   //------------------------------------------------------------
   // <T>�ж�����Ƿ�ʹ���С�</T>
   MO_INLINE TBool IsEntryUsing(){
      return EInstancedFlag_Using == (_entryFlag & EInstancedFlag_Using);
   }
   //------------------------------------------------------------
   // <T>��������Ƿ�ʹ���С�</T>
   MO_INLINE void SetEntryUsing(TBool value){
      if(value){
         _entryFlag |= EInstancedFlag_Using;
      }else{
         _entryFlag &= ~EInstancedFlag_Using;
      }
   }
};

//============================================================
// <T>ֻ��������ڵ�������</T>
//
// @tool
//============================================================
template <typename T>
class TObjectEntryIteratorC{
public:
   typedef MObjectEntry SEntry;
protected:
   SEntry* _pStart;
   SEntry* _pCurrent;
public:
   //------------------------------------------------------------
   // <T>����ֻ��������ڵ�������</T>
   TObjectEntryIteratorC(){
      MO_CLEAR(_pStart);
      MO_CLEAR(_pCurrent);
   }
   //------------------------------------------------------------
   // <T>����ֻ��������ڵ�������</T>
   TObjectEntryIteratorC(const TObjectEntryIteratorC& iterator){
      _pStart = iterator._pStart;
      _pCurrent = iterator._pCurrent;
   }
   //------------------------------------------------------------
   // <T>����ֻ��������ڵ�������</T>
   TObjectEntryIteratorC(SEntry* pStart){
      _pStart = pStart;
      MO_CLEAR(_pCurrent);
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator *(){
      return _pCurrent;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator->(){
      return _pCurrent;
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return (NULL == _pCurrent);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      return (NULL == _pCurrent) ? (NULL != _pStart) : (NULL != _pCurrent->EntryNext());
   }
   //------------------------------------------------------------
   //<T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      _pCurrent = (NULL == _pCurrent) ? _pStart : _pCurrent->EntryNext();
      return (NULL != _pCurrent);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return (NULL == _pCurrent) ? (NULL != _pStart) : (NULL != _pCurrent->EntryPrior());
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      _pCurrent = (NULL == _pCurrent) ? _pStart : _pCurrent->EntryPrior();
      return (NULL != _pCurrent);
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* Get(){
      return (T*)_pCurrent;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   template <typename C>
   MO_INLINE C Get(){
      return (C)_pCurrent;
   }
public:
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _pCurrent = NULL;
   }
};

//============================================================
// <T>������ڻ���ء�</T>
//
// @history 130320 MAOCY ����
//============================================================
template <typename T>
class MObjectEntryPool{
public:
   typedef TInt (*HComparer)(T source, T target);
   typedef MObjectEntry SEntry;
   typedef TObjectEntryIteratorC<T> TIteratorC;
protected:
   TInt32 _capacity;
   TInt32 _count;
   SEntry* _pFirst;
   SEntry* _pLast;
   SEntry* _pFree;
public:
   //------------------------------------------------------------
   // <T>���������ڻ���ء�</T>
   MObjectEntryPool(){
      _capacity = 0;
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      MO_CLEAR(_pFree);
   }
   //------------------------------------------------------------
   // <T>����������ڻ���ء�</T>
   MO_ABSTRACT ~MObjectEntryPool(){
   }
protected:
   //------------------------------------------------------------
   // <T>�ռ�һ��δʹ�õĽڵ㡣</T>
   MO_INLINE SEntry* EntryAlloc(){
      SEntry* pEntry = NULL;
      if(NULL == _pFree){
         pEntry = MO_CREATE(T);
         _capacity++;
      }else{
         pEntry = _pFree;
         _pFree = _pFree->EntryNext();
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ����ʹ�õĽڵ㡣</T>
   MO_INLINE void EntryFree(SEntry* pEntry){
      MO_ASSERT(pEntry);
      pEntry->SetEntryNext(_pFree);
      _pFree = pEntry;
   }
   //------------------------------------------------------------
   // <T>������ڵ�ѹ��βλ�á�</T>
   MO_INLINE void EntryPush(SEntry* pEntry){
      MO_ASSERT(pEntry);
      if(NULL == _pLast){
         _pFirst = pEntry;
      }else{
         _pLast->SetEntryNext(pEntry);
      }
      pEntry->SetEntryPrior(_pLast);
      pEntry->SetEntryNext(NULL);
      _pLast = pEntry;
      _count++;
   }
   //------------------------------------------------------------
   // <T>��������ɾ������ڵ㡣</T>
   MO_INLINE void EntryRemove(SEntry* pEntry){
      MO_ASSERT(pEntry);
      // ����ǰ�ڵ�
      if(NULL == pEntry->EntryPrior()){
         _pFirst = pEntry->EntryNext();
      }else{
         pEntry->EntryPrior()->SetEntryNext(pEntry->EntryNext());
      }
      // �����ڵ�
      if(NULL == pEntry->EntryNext()){
         _pLast = pEntry->EntryPrior();
      }else{
         pEntry->EntryNext()->SetEntryPrior(pEntry->EntryPrior());
      }
      // ��������
      _count--;
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ���ʹ�ö���</T>
   MO_INLINE TBool HasUsing(){
      return _count > 0;
   }
   //------------------------------------------------------------
   // <T>���ʹ�ö��������</T>
   MO_INLINE TInt UsingCount(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>�����λ�õ����ݡ�</T>
   MO_INLINE T* UsingFirst() const{
      return (T*)_pFirst;
   }
   //------------------------------------------------------------
   // <T>���βλ�õ����ݡ�</T>
   MO_INLINE T* UsingLast() const{
      return (T*)_pLast;
   }
public:
   //------------------------------------------------------------
   // <T>���ʹ������λ�õ�ֻ�����ݵ�������</T>
   MO_INLINE TIteratorC UsingIteratorC() const{
      return TIteratorC(_pFirst);
   }
   //------------------------------------------------------------
   // <T>���ʹ����βλ�õ�ֻ�����ݵ�������</T>
   MO_INLINE TIteratorC UsingLastIteratorC() const{
      return TIteratorC(_pLast);
   }
   //------------------------------------------------------------
   // <T>����ͷ��е�ֻ�����ݵ�������</T>
   MO_INLINE TIteratorC FreeIteratorC() const{
      return TIteratorC(_pFree);
   }
public:
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�������Ƿ���ָ�����ݡ�</T>
   MO_INLINE TBool Contains(T* pItem) const{
      if(_count > 0){
         // �Ƚ�������Ŀ
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            if(pEntry == pItem){
               return ETrue;
            }
            pEntry = pEntry->EntryNext();
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ռ�һ������</T>
   MO_INLINE T* Alloc(){
      // �ռ�һ��δʹ�õýڵ�
      SEntry* pEntry = EntryAlloc();
      // ����Ϊ����
      pEntry->SetEntryUsing(ETrue);
      // ���ڵ�ѹ��β��
      EntryPush(pEntry);
      return (T*)pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻���ء�</T>
   MO_INLINE TBool Free(T* pItem){
      MO_ASSERT(pItem);
      // ����Ϊ������
      SEntry* pEntry = (SEntry*)pItem;
      pEntry->SetEntryUsing(EFalse);
      // �ͷŽڵ�
      EntryRemove(pEntry);
      EntryFree(pEntry);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>������ж���</T>
   MO_INLINE void Clear(){
      // �ͷ�����
      if(_count > 0){
         _pLast->SetEntryNext(_pFree);
         _pFree = _pFirst;
      }
      // ��������
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
   }
   //------------------------------------------------------------
   // <T>�ͷ����ж���</T>
   MO_INLINE void Release(){
      // ������ж���
      Clear();
      // �ͷ����ж���
      SEntry* pEntry = _pFree;
      while(NULL != pEntry){
         SEntry* pNext = pEntry->EntryNext();
         MO_DELETE(pEntry);
         pEntry = pNext;
      }
      MO_CLEAR(_pFree);
      _capacity = 0;
   }
public:
   //------------------------------------------------------------
   // <T>��ʾ������Ϣ��</T>
   MO_INLINE void Dump(){
      TInt entryCapacity = sizeof(SEntry);
      TInt entrySize = entryCapacity * _capacity;
      MO_DEBUG("Instanced pool. (capacity=%d, entry_capacity=%d, entry_size=%d, using_count=%d, free_count=%d)",
            _capacity, entryCapacity, entrySize, _count, _capacity - _count);
   }
};

//============================================================
// <T>������ڻ���ء�</T>
//
// @tool
//============================================================
template <typename T>
class TObjectEntryPool :
      public MObjectEntryPool<T>{
public:
   //------------------------------------------------------------
   // <T>���������ڻ���ء�</T>
   TObjectEntryPool(){
   }
   //------------------------------------------------------------
   // <T>����������ڻ���ء�</T>
   MO_ABSTRACT ~TObjectEntryPool(){
   }
};

//============================================================
// <T>������ڻ���ء�</T>
//
// @class
//============================================================
template <typename T>
class FObjectEntryPool :
      public FObject,
      public MObjectEntryPool<T>{
public:
   //------------------------------------------------------------
   // <T>���������ڻ���ء�</T>
   FObjectEntryPool(){
   }
   //------------------------------------------------------------
   // <T>����������ڻ���ء�</T>
   MO_ABSTRACT ~FObjectEntryPool(){
   }
};

//============================================================
// <T>ʵ���ض���</T>
//
// @struct
//============================================================
class MO_CM_DECLARE MInstancedPoolObject{
protected:
   TInt32 _objectIndex;
   TInt16 _objectType;
   TInt16 _objectFlag;
public:
   //------------------------------------------------------------
   // <T>����ʵ���ض���</T>
   MInstancedPoolObject(){
      _objectIndex = -1;
      _objectType = 0;
      _objectFlag = 0;
   }
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt ObjectIndex(){
      return _objectIndex;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void SetObjectIndex(TInt objectIndex){
      _objectIndex = (TInt32)objectIndex;
   }
   //------------------------------------------------------------
   // <T>������͡�</T>
   MO_INLINE TInt ObjectType(){
      return _objectType;
   }
   //------------------------------------------------------------
   // <T>�������͡�</T>
   MO_INLINE void SetObjectType(TInt objectType){
      _objectType = (TInt16)objectType;
   }
   //------------------------------------------------------------
   // <T>��ñ�־��</T>
   MO_INLINE TInt ObjectFlag(){
      return _objectFlag;
   }
   //------------------------------------------------------------
   // <T>���ñ�־��</T>
   MO_INLINE void SetObjectFlag(TInt objectFlag){
      _objectFlag = (TInt16)objectFlag;
   }
public:
   //------------------------------------------------------------
   // <T>�ж϶����Ƿ�ʹ���С�</T>
   MO_INLINE TBool IsObjectUsing(){
      return EInstancedFlag_Using == (_objectFlag & EInstancedFlag_Using);
   }
   //------------------------------------------------------------
   // <T>���ö����Ƿ�ʹ���С�</T>
   MO_INLINE void SetObjectUsing(TBool value){
      if(value){
         _objectFlag |= EInstancedFlag_Using;
      }else{
         _objectFlag &= ~EInstancedFlag_Using;
      }
   }
};

//============================================================
// <T>ʵ������ؽڵ㡣</T>
//
// @struct
//============================================================
template <typename T>
struct SInstancedPoolEntry{
public:
   TInt32 prior;
   TInt32 next;
   T item;
};

//============================================================
// <T>ֻ��ʵ��ص�������</T>
//
// @tool
//============================================================
template <typename T>
class TInstancedIteratorC{
public:
   typedef SInstancedPoolEntry<T> SEntry;
protected:
   TInt _start;
   TInt _index;
   SEntry* _pEntities;
public:
   //------------------------------------------------------------
   // <T>����ֻ��ʵ��ص�������</T>
   TInstancedIteratorC(){
      _start = -1;
      _index = -1;
      MO_CLEAR(_pEntities);
   }
   //------------------------------------------------------------
   // <T>����ֻ��ʵ��ص�������</T>
   TInstancedIteratorC(const TInstancedIteratorC& iterator){
      _start = iterator._start;
      _index = iterator._index;
      _pEntities = iterator._pEntities;
   }
   //------------------------------------------------------------
   // <T>����ֻ��ʵ��ص�������</T>
   TInstancedIteratorC(TInt first, SEntry* pEntities){
      _start = first;
      _index = -1;
      _pEntities = pEntities;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator *(){
      SEntry& entry = _pEntities[_index];
      return &entry.item;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator->(){
      SEntry& entry = _pEntities[_index];
      return &entry.item;
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return (-1 == _index);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      return (-1 == _index) ? (-1 != _start) : (-1 != _pEntities[_index].next);
   }
   //------------------------------------------------------------
   //<T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      _index = (-1 == _index) ? _start : _pEntities[_index].next;
      return (-1 != _index);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return (-1 == _index) ? (-1 != _start) : (-1 != _pEntities[_index].prior);
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      _index = (-1 == _index) ? _start : _pEntities[_index].prior;
      return (-1 != _index);
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* Get(){
      SEntry& entry = _pEntities[_index];
      return &entry.item;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   template <typename C>
   MO_INLINE C Get(){
      SEntry& entry = _pEntities[_index];
      return (C)&entry.item;
   }
public:
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _index = -1;
   }
};

//============================================================
// <T>ʵ������ء�</T>
//
// @history 130320 MAOCY ����
//============================================================
template <typename T>
class MInstancedPool{
public:
   typedef TInt (*HComparer)(T source, T target);
   typedef SInstancedPoolEntry<T> SEntry;
   typedef TInstancedIteratorC<T> TIteratorC;
protected:
   TInt _capacity;
   TInt _count;
   TInt32 _first;
   TInt32 _last;
   TInt32 _free;
   SEntry* _pEntries;
public:
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MInstancedPool(){
      _capacity = 0;
      _count = 0;
      _first = -1;
      _last = -1;
      _free = -1;
      MO_CLEAR(_pEntries);
   }
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MO_ABSTRACT ~MInstancedPool(){
   }
public:
   //------------------------------------------------------------
   // <T>ǿ��������</T>
   void ForceCapacity(TInt capacity){
      MO_ASSERT(capacity > 0);
      // �ͷž��ڴ�
      MO_FREE(_pEntries);
      // �ռ��ڴ�
      _pEntries = MO_TYPES_ALLOC(SEntry, capacity);
      RTypes<SEntry>::Clear(_pEntries, capacity);
      // �������ɳ�
      _count = 0;
      _first = -1;
      _last = -1;
      _free = -1;
      for(TInt n = 0; n < capacity; n++){
         SEntry& entry = _pEntries[n];
         // ��������
         new(&entry.item)T();
         // ��������
         entry.prior = -1;
         entry.item.SetObjectIndex(n);
         // ���뻺��
         entry.next = _free;
         _free = n;
      }
      _capacity = capacity;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   void ExtendCapacity(TInt count){
      TInt capacity = _capacity + count;
      // �ռ��ڴ�
      SEntry* pEntries = MO_TYPES_ALLOC(SEntry, capacity);
      // ��������
      if(NULL != _pEntries){
         // ���ƴ���
         if(_capacity > 0){
            RTypes<SEntry>::Copy(pEntries, _pEntries, _capacity);
         }
         // �ͷž��ڴ�
         MO_FREE(_pEntries);
      }
      // ����ڴ�
      RTypes<SEntry>::Clear(pEntries + _capacity, count);
      // �������ɳ�
      for(TInt n = 0; n < count; n++){
         SEntry& entry = pEntries[_capacity + n];
         // ��������
         new(&entry.item)T();
         // ��������
         entry.prior = -1;
         entry.item.SetObjectIndex(_capacity + n);
         // ���뻺��
         entry.next = _free;
         _free = n;
      }
      _capacity = capacity;
   }
protected:
   //------------------------------------------------------------
   // <T>�ռ�һ��δʹ�õĽڵ㡣</T>
   MO_INLINE SEntry& EntryAlloc(){
      // �鿴δʹ�ýڵ����Ƿ������ɽڵ�
      if(-1 == _free){
         MO_FATAL("Alloc entry failure. pool is full. (count=%d)", _count);
      }
      SEntry& entry = _pEntries[_free];
      _free = entry.next;
      return entry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ����ʹ�õĽڵ㡣</T>
   MO_INLINE void EntryFree(SEntry& entry){
      entry.next = _free;
      _free = entry.item.ObjectIndex();
   }
   //------------------------------------------------------------
   // <T>������ڵ�ѹ����λ�á�</T>
   MO_INLINE TInt EntryGet(TInt index) const{
      MO_ASSERT_RANGE(index, 0, _count);
      // ���ָ��λ������
      TInt find = _first;
      while(--index >= 0){
         find = _pEntries[find].next;
      }
      return find;
   }
   //------------------------------------------------------------
   // <T>������ڵ�ѹ��βλ�á�</T>
   MO_INLINE void EntryPush(SEntry& entry){
      TInt index = entry.item.ObjectIndex();
      if(-1 == _last){
         _first = index;
      }else{
         _pEntries[_last].next = index;
      }
      entry.prior = _last;
      entry.next = -1;
      _last = index;
      _count++;
   }
   //------------------------------------------------------------
   // <T>��������ɾ������ڵ㡣</T>
   MO_INLINE void EntryRemove(SEntry& entry){
      // ����ǰ�ڵ�
      if(-1 == entry.prior){
         _first = entry.next;
      }else{
         _pEntries[entry.prior].next = entry.next;
      }
      // �����ڵ�
      if(-1 == entry.next){
         _last = entry.prior;
      }else{
         _pEntries[entry.next].prior = entry.prior;
      }
      // ��������
      _count--;
   }
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Capacity(){
      return _capacity;
   }
   //------------------------------------------------------------
   // <T>����Ƿ���ʹ�ö���</T>
   MO_INLINE TBool HasUsingItem(){
      return _count > 0;
   }
   //------------------------------------------------------------
   // <T>���ʹ�ö��������</T>
   MO_INLINE TInt UsingCount(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>�����λ�õ����ݡ�</T>
   MO_INLINE T* UsingFirst() const{
      if(-1 != _first){
         SEntry& entry = _pEntries[_first];
         return &entry.item;
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>���βλ�õ����ݡ�</T>
   MO_INLINE T* UsingLast() const{
      if(-1 != _last){
         SEntry& entry = _pEntries[_last];
         return &entry.item;
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����Ƿ��п��ж���</T>
   MO_INLINE TBool HasFreeItem(){
      return (_capacity - _count) > 0;
   }
   //------------------------------------------------------------
   // <T>��ÿ��ж��������</T>
   MO_INLINE TInt FreeCount(){
      return _capacity - _count;
   }
   //------------------------------------------------------------
   // <T>����������ö���</T>
   MO_INLINE T* Get(TInt index) const{
      MO_CHECK_RANGE(index, 0, _capacity, return NULL);
      SEntry& entry = _pEntries[index];
      return &entry.item;
   }
   //------------------------------------------------------------
   // <T>�����������ʹ���еĶ���</T>
   MO_INLINE T* FindUsing(TInt index) const{
      MO_CHECK_RANGE(index, 0, _capacity, return NULL);
      SEntry& entry = _pEntries[index];
      T* pItem = &entry.item;
      if(pItem->IsObjectUsing()){
         return pItem;
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>�����������ʹ���еĶ���</T>
   MO_INLINE T* GetUsing(TInt index) const{
      MO_CHECK_RANGE(index, 0, _capacity, return NULL);
      SEntry& entry = _pEntries[index];
      T* pItem = &entry.item;
      if(pItem->IsObjectUsing()){
         return pItem;
      }
      MO_DEBUG_FATAL("Object is freeed. (index=%d)", index);
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����ָ��λ�õ����ݡ�</T>
   MO_INLINE T* FindListByIndex(TInt index) const{
      MO_CHECK_RANGE(index, 0, _capacity, return NULL);
      TInt find = EntryGet(index);
      if(-1 != find){
         SEntry& entry = _pEntries[find];
         return &entry.item;
      }
      MO_DEBUG_FATAL("Can't find item on index. (index=%d)", index);
      return NULL;
   }
   //------------------------------------------------------------
   // <T>���ָ��λ�õ����ݡ�</T>
   MO_INLINE T* GetListByIndex(TInt index) const{
      MO_CHECK_RANGE(index, 0, _capacity, return NULL);
      TInt find = EntryGet(index);
      if(-1 != find){
         SEntry& entry = _pEntries[find];
         return &entry.item;
      }
      MO_DEBUG_FATAL("Can't find item on index. (index=%d)", index);
      return NULL;
   }
public:
   //------------------------------------------------------------
   // <T>���ʹ������λ�õ�ֻ�����ݵ�������</T>
   MO_INLINE TIteratorC UsingIteratorC() const{
      return TIteratorC(_first, _pEntries);
   }
   //------------------------------------------------------------
   // <T>���ʹ����βλ�õ�ֻ�����ݵ�������</T>
   MO_INLINE TIteratorC UsingLastIteratorC() const{
      return TIteratorC(_last, _pEntries);
   }
   //------------------------------------------------------------
   // <T>����ͷ��е�ֻ�����ݵ�������</T>
   MO_INLINE TIteratorC FreeIteratorC() const{
      return TIteratorC(_free, _pEntries);
   }
public:
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�������Ƿ���ָ�����ݡ�</T>
   MO_INLINE TBool Contains(T* pItem) const{
      if(_count > 0){
         // �Ƚ�������Ŀ
         TInt index = _first;
         while(-1 != index){
            SEntry& entry = _pEntries[index];
            T* pFind = &entry.item;
            if(pFind == pItem){
               return ETrue;
            }
            index = entry.next;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ռ�һ������</T>
   MO_INLINE T* Alloc(){
      // �ռ�һ��δʹ�õýڵ�
      SEntry& entry = EntryAlloc();
      // ������������
      T* pItem = &entry.item;
      // ����Ϊ����
      pItem->SetObjectUsing(ETrue);
      // ���ڵ�ѹ��β��
      EntryPush(entry);
      return pItem;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻���ء�</T>
   MO_INLINE TBool Free(T* pItem){
      MO_ASSERT(pItem);
      // ��������
#ifdef _MO_DEBUG
      if(!Contains(pItem)){
         MO_FATAL("Free item is not exists in using collection. (capacity=%d, using_count=%d, free_count=%d)",
               _capacity, _count, _capacity - _count);
         return EFalse;
      }
#endif // _MO_DEBUG
      // ����Ϊ������
      pItem->SetObjectUsing(EFalse);
      // �ͷŽڵ�
      TInt index = pItem->ObjectIndex();
      SEntry& entry = _pEntries[index];
      EntryRemove(entry);
      EntryFree(entry);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ʹ���������Լ��϶����������</T>
   void Sort(HComparer hComparer){
      MO_ASSERT(hComparer);
      //if((_count > 1) && (-1 != _first) && (-1 != _last)) {
      //   RInstancedList<SEntry, T>::Sort(_first, _first, _last, hComparer);
      //}
   }
   //------------------------------------------------------------
   // <T>������ж���</T>
   MO_INLINE void Clear(){
      // �ͷ�����
      if(_count > 0){
         _pEntries[_last].next = _free;
         _free = _first;
      }
      // ��������
      _count = 0;
      _first = -1;
      _last = -1;
   }
   //------------------------------------------------------------
   // <T>�ͷ����ж���</T>
   MO_INLINE void Release(){
      // �ͷ����ж���
      for(TInt n = 0; n < _capacity; n++){
         SEntry& entry = _pEntries[n];
         T* pItem = &entry.item;
         pItem->~T();
      }
      MO_FREE(_pEntries);
      // ��������
      _capacity = 0;
      _count = 0;
      _first = -1;
      _last = -1;
      _free = -1;
   }
public:
   //------------------------------------------------------------
   // <T>��ʾ������Ϣ��</T>
   MO_INLINE void Dump(){
      TInt entryCapacity = sizeof(SEntry);
      TInt entrySize = entryCapacity * _capacity;
      MO_DEBUG("Instanced pool. (capacity=%d, entry_capacity=%d, entry_size=%d, using_count=%d, free_count=%d)",
            _capacity, entryCapacity, entrySize, _count, _capacity - _count);
   }
};

//============================================================
// <T>�䳤ʵ������ء�</T>
//
// @tool
//============================================================
template <typename T>
class TInstancedPool :
      public MInstancedPool<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤ʵ������ء�</T>
   TInstancedPool(){
   }
   //------------------------------------------------------------
   // <T>�����䳤ʵ������ء�</T>
   ~TInstancedPool(){
   }
};

//============================================================
// <T>�䳤ʵ������ء�</T>
//
// @class
//============================================================
template <typename T>
class FInstancedPool :
      public FObject,
      public MInstancedPool<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤ʵ������ء�</T>
   FInstancedPool(){
   }
   //------------------------------------------------------------
   // <T>�����䳤ʵ������ء�</T>
   MO_ABSTRACT ~FInstancedPool(){
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_POOL_H__
