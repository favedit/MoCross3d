//============================================================
// <T>�ڴ����</T>
//============================================================
#ifndef __MO_CM_MEMORY_H__
#define __MO_CM_MEMORY_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_LOCK_H__
#include "MoCmLock.h"
#endif // __MO_CM_LOCK_H__

#ifndef __MO_CM_VECTOR_H__
#include "MoCmVector.h"
#endif // __MO_CM_VECTOR_H__

#ifndef __MO_CM_LIST_H__
#include "MoCmList.h"
#endif // __MO_CM_LIST_H__

#ifndef __MO_CM_SET_H__
#include "MoCmSet.h"
#endif // __MO_CM_SET_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

#define MO_MEMORY_FORMATLENGTH 40

MO_NAMESPACE_BEGIN

//============================================================
struct SAllocatorInfo;
class FAllocatorStorage;
class MShared;

//============================================================
// <T>�ڴ涨�塣</T>
//============================================================
enum EMemory{
   /// @enum δ֪����
   EMemory_Unknown = 0,
   /// @enum ϵͳ�ڴ�
   EMemory_System = 1,
   /// @enum �����ڴ�
   EMemory_Share = 2,
};

//============================================================
// <T>�ڴ����������ࡣ</T>
//============================================================
class MO_CM_DECLARE RMemoryCapacity{
public:
   static TSize Parse(TCharC* pSize);
   static TCharC* Format(TSize size, TChar* pBuffer, TSize length);
};

//============================================================
// <T>�ڴ��ռ����ӿڡ�</T>
//============================================================
class MO_CM_DECLARE IAllocator{
public:
   //------------------------------------------------------------
   // <T>�����ڴ��ռ����ӿڡ�</T>
   MO_ABSTRACT ~IAllocator(){
   }
public:
   MO_VIRTUAL TAny* Alloc(TInt size = 0) = 0;
   MO_VIRTUAL TAny* Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber) = 0;
   MO_VIRTUAL void Free(TAny* pMemory) = 0;
};

//============================================================
// <T>�ڴ�ԭ���ࡣ</T>
//
// @history 100224 MAOCY ����
//============================================================
class MO_CM_DECLARE SMemoryEntry{
public:
   IAllocator* pAllocator;
   SMemoryEntry* pPrior;
   SMemoryEntry* pNext;
   TInt* pAlloc;
   TAny* pMemory;
   TUint size;
   //------------------------------------------------------------
   TCharC* pTypeName;
   TChar8C* pFileName;
   TInt fileLine;
   //------------------------------------------------------------
   TUint allocCount;
   TUint freeCount;
   TDateTime createDateTime;
   TDateTime usedDateTime;
public:
   SMemoryEntry(IAllocator* pAllocator);
   MO_ABSTRACT ~SMemoryEntry();
public:
   void SetTypeName(TCharC* pTypeName);
   void SetFileInfo(TChar8C* pFileName, TInt line);
   void Link(TByte* pData, TUint size);
   void Alloc();
   void Free();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<SMemoryEntry*> FMemoryEntryList;

//============================================================
// <T>�ڴ������ģ���ࡣ</T>
//============================================================
class MO_CM_DECLARE FMemoryAllocator :
      public FBase,
      public IAllocator{
protected:
   SMemoryEntry* _pAlloc;
   SMemoryEntry* _pFirst;
   SMemoryEntry* _pLast;
   SMemoryEntry* _pUnused;
public:
   FMemoryAllocator();
   MO_ABSTRACT ~FMemoryAllocator();
protected:
   void EntryExtend();
   SMemoryEntry* EntryAlloc();
public:
   MO_OVERRIDE TAny* Alloc(TInt size = 0);
   MO_OVERRIDE TAny* Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber);
   MO_OVERRIDE void Free(TAny* pMemory);
};

//============================================================
// <T>�ڴ������ģ���ࡣ</T>
//
// @source FMemoryAllocator.cpp
//============================================================
class MO_CM_DECLARE FMemoryLockAllocator : public FMemoryAllocator{
protected:
   TThreadLocker _locker;
public:
   FMemoryLockAllocator();
   MO_ABSTRACT ~FMemoryLockAllocator();
public:
   MO_OVERRIDE TAny* Alloc(TInt size = 0);
   MO_OVERRIDE TAny* Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber);
   MO_OVERRIDE void Free(TAny* pMemory);
};

//============================================================
// <T>���ڴ�����ࡣ</T>
//
// @class
//============================================================
class MO_CM_DECLARE FBlockAllocator :
      public FBase,
      public IAllocator{
protected:
   TCharC* _pName;
   TInt _count;
   TInt _blockSize;
   FMemoryEntryList* _pEntries;
   //TInt _total;
   //TInt _memoryTotal;
public:
   FBlockAllocator(TInt blockSize = 0);
   MO_ABSTRACT ~FBlockAllocator();
protected:
   MO_ABSTRACT void EntryExtend();
   MO_INLINE void EntryPush(SMemoryEntry* pEntry);
   MO_INLINE void EntryRemove(SMemoryEntry* pEntry);
   MO_INLINE SMemoryEntry* EntryAlloc();
public:
   TCharC* Name();
   void SetName(TCharC* pName);
   TInt GetMemoryUsed();
   TInt GetMemoryTotal();
public:
   //------------------------------------------------------------
   // <T>��÷ֿ鳤�ȡ�</T>
   MO_INLINE TInt BlockSize(){
      return _blockSize;
   }
   //------------------------------------------------------------
   // <T>���÷ֿ鳤�ȡ�</T>
   MO_INLINE void SetBlockSize(TInt blockSize){
      MO_ASSERT(blockSize > 0);
      if(0 == _blockSize){
         _blockSize = blockSize;
      }else if(_blockSize != blockSize){
         MO_FATAL(TC("Block size is set only once."));
      }
   }
public:
   MO_OVERRIDE TAny* Alloc(TInt size = 0);
   MO_OVERRIDE TAny* Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber);
   MO_OVERRIDE void Free(TAny* pMemory);
public:
   void Dump();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FFreeSet<TUint, FBlockAllocator*> FBlockAllocatorFreeSet;
typedef MO_CM_DECLARE FFreeList<FBlockAllocator*> FBlockAllocatorFreeList;

//============================================================
// <T>�������ڴ�����ࡣ</T>
//
// @source FBlockAllocator.cpp
//============================================================
class MO_CM_DECLARE FBlockLockAllocator : public FBlockAllocator{
protected:
   TThreadLocker _locker;
public:
   FBlockLockAllocator(TUint atomSize);
   MO_OVERRIDE ~FBlockLockAllocator();
public:
   MO_OVERRIDE TAny* Alloc(TInt size = 0);
   MO_OVERRIDE TAny* Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber);
   MO_OVERRIDE void Free(TAny* pMemory);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FFreeSet<TUint, FBlockLockAllocator*> FBlockLockAllocatorFreeSet;
typedef MO_CM_DECLARE FFreeList<FBlockLockAllocator*> FBlockLockAllocatorFreeList;

//============================================================
// <T>�ڴ������ģ���ࡣ</T>
// <P>�����ڴ��С�ֿ�洢����ͬ��С�Ĵ洢��һ��</P>
//============================================================
class MO_CM_DECLARE FThreadMemory{
protected:
   FBlockAllocatorFreeSet* _pBlockAllocators;
public:
   FThreadMemory();
   MO_ABSTRACT ~FThreadMemory();
public:
   TAny* Alloc(TUint size);
   TAny* Alloc(TCharC* pTypeName, TUint size, TChar8C* pFileName, TInt fileLine);
   void Free(TAny* pMemory);
};

//============================================================
// <T>�����ռ���Ϣ��</T>
//============================================================
struct MO_CM_DECLARE SAllocatorInfo{
public:
   IMemoryStorage* storagePtr;
   TInt index;
   TInt size;
   TChar8C* ownerNamePtr;
   TChar8C* typeNamePtr;
   TChar8C* fileNamePtr;
   TInt lineNumber;
   TInt count;
   TInt total;
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FFreeVector<SAllocatorInfo*> FAllocatorInfoVector;

//============================================================
// <T>�����ռ���Ϣ��</T>
//============================================================
struct MO_CM_DECLARE SAllocatorHeader{
public:
   SAllocatorInfo* infoPtr;
};

//============================================================
// <T>�ռ���Ϣ�洢����</T>
//============================================================
class MO_CM_DECLARE FAllocatorStorage :
      public FBase,
      public IMemoryStorage{
protected:
   TBool _able;
   TThreadLocker _locker;
   TInt64 _lengthAlloc;
   TInt64 _lengthFree;
   FAllocatorInfoVector* _pInfos;
public:
   FAllocatorStorage();
   MO_ABSTRACT ~FAllocatorStorage();
public:
   MO_OVERRIDE TBool IsAble();
   MO_OVERRIDE void Enable();
   MO_OVERRIDE void Disable(TBool detail = EFalse);
   MO_OVERRIDE TBool FetchInfo(SMemoryInfo* pInfo);
public:
   MO_OVERRIDE TAny* Alloc(TChar8C* pOwnerName, TChar8C* pTypeName, TInt size, TChar8C* pFileName = NULL, TInt lineNumber = 0);
   MO_OVERRIDE void Free(TAny* pMemory);
public:
   MO_OVERRIDE void Reset();
   MO_OVERRIDE void Dump(TBool detail = EFalse);
};

//============================================================
// <T>�ڴ��ռ�����</T>
//============================================================
class MO_CM_DECLARE RAllocator{
protected:
   static TThreadLocker _locker;
   static IMemoryStorage* _pStorage;
   static FMemoryAllocator* _pMemoryAllocator;
   static FBlockAllocatorFreeSet* _pBlockAllocatorSet;
   static FBlockAllocatorFreeList* _pBlockAllocators;
   static FBlockLockAllocatorFreeList* _pBlockLockAllocators;
public:
   static void Create();
   static void Destroy();
public:
   static IMemoryStorage* Storage();
public:
   static TAny* Alloc(TUint size);
   static TAny* Alloc(TChar8C* pTypeName, TUint size, TChar8C* pFileName, TInt line);
   static void Free(TAny* pMemory);
public:
   static TAny* TypeAlloc(TUint size);
   static TAny* TypeAlloc(TChar8C* pTypeName, TUint size, TChar8C* pFileName, TInt line);
   static void TypeFree(TAny* pMemory);
public:
   static FBlockAllocator* BlockAllocatorAlloc(TInt size);
   static void BlockAllocatorFree(FBlockAllocator* pAllocator);
public:
   static FBlockLockAllocator* BlockLockAllocatorAlloc(TInt size);
   static void BlockLockAllocatorFree(FBlockLockAllocator* pAllocator);
public:
   static TBool CalculateStatistics(TUint& used, TUint& total);
   static void DumpTrack();
};

//============================================================
// <T>�������ӿڡ�</T>
//============================================================
class MO_CM_DECLARE RActivator{
protected:
   static TThreadLocker _locker;
public:
   static void Initialize();
   static void Release();
public:
   static TAny* Create(TChar8C* pClassName, TInt size, TChar8C* pFileName, TInt line);
   static void Remove(TAny* pObject);
   static void Destroy(TAny* pObject);
public:
   static void Lock();
   static void Unlock();
};

/*
//============================================================
// <T>�����ڴ��ռ�����</T>
//
// @reference
//============================================================
template <typename T>
class RBlockAllocator : public RStatic<RBlockAllocator<T>, EManager>{
protected:
   FBlockLockAllocator* _pAllocator;
public:
   //------------------------------------------------------------
   MO_OVERRIDE( RBlockAllocator() ){
      _pAllocator = RAllocator::BlockLockAllocatorAlloc(sizeof(T));
      //MO_DEBUG("Block memory allocator connect. (type=%s(%d), allocator=0x%08X)", typeid(T).name(), size, _pAllocator);
      return this;
   }
   //------------------------------------------------------------
   MO_OVERRIDE( ~RBlockAllocator() ){
      RAllocator::BlockLockAllocatorFree(_pAllocator);
   }
public:
   //------------------------------------------------------------
   // �ռ�һ��ָ����С���ڴ�
   static IAllocator* Allocator(){
      return RBlockAllocator::_static._pAllocator;
   };
   //------------------------------------------------------------
   // �ռ�һ��ָ����С���ڴ�
   static T* Alloc(TUint size = 0){
      return (T*)RBlockAllocator::_static._pAllocator->Alloc(size);
   };
   //------------------------------------------------------------
   // �ռ�һ��ָ����С���ڴ�
   static T* Alloc(TCharC* pTypeName, TUint size, TChar8C* pFileName, TInt line){
      return (T*)RBlockAllocator::_static._pAllocator->Alloc(pTypeName, size, pFileName, line);
   };
   //------------------------------------------------------------
   // �ͷ��ڴ�
   static void Free(TAny* pMemory){
      RBlockAllocator::_static._pAllocator->Free(pMemory);
   }
};*/

//============================================================
// <T>�����ڴ�������Ϣ��</T>
//
// @history 100305 MAOCY ����
//============================================================
struct SShareMemoryInfo{
   // ϵͳ�����־(MOSM)
   TChar8 flag[4];
   // �ڴ�����С
   TInt size;
   // ��������
   TDateTime createDate;
   // ���ʹ������
   TDateTime updateDate;
};

//============================================================
// <T>�����ڴ�����������</T>
// <P>�����ڴ����λ������Ϣ���֣�����Ϊ�������ݲ��֡�</P>
//
// @history 100305 MAOCY ����
//============================================================
typedef TInt TShareKey;
//------------------------------------------------------------
class MO_CM_DECLARE RShareMemory{
protected:
   static TAny* InnerCreate(TShareKey key, TSize size);
public:
   static TShareKey MakeKey(TCharC* pFileName, TInt id);
   //------------------------------------------------------------
   static TBool FetchInfo(TShareKey key, SShareMemoryInfo& info);
   static TAny* Create(TShareKey key, TSize size);
   static TAny* TryCreate(TShareKey key, TSize size, TBool& created);
   static TAny* Connect(TShareKey key, TBool readOnly = EFalse);
   static void Free(TShareKey key);
};

//============================================================
// <T>�����ڴ�������</T>
//
// @class
// @history 100303 MAOCY ����
//============================================================
class MO_CM_DECLARE TShareSegment{
protected:
   TByte* _pMemory;
   TInt _position;
   TInt _length;
   TBool _created;
public:
   //------------------------------------------------------------
   // <T>���칲���ڴ�������</T>
   TShareSegment(){
      _pMemory = NULL;
      _position = 0;
      _length = 0;
      _created = EFalse;
   }
   //------------------------------------------------------------
   // <T>���칲���ڴ�������</T>
   TShareSegment(TAny* pMemory, TInt length, TBool created){
      _pMemory = (TByte*)pMemory;
      _position = 0;
      _length = length;
      _created = created;
   }
public:
   void Initialize(TAny* pMemory, TInt length, TBool created);
public:
   TBool IsCreated();
   TAny* Memory();
   TInt Position();
   TInt Length();
   TInt Remain();
   TAny* RemainMemory();
   TAny* Alloc(TSize size);
   TShareSegment CreateSegment(TSize size);
   void SharedLink(MShared* pShared);
   void Check();
public:
   //------------------------------------------------------------
   // <T>�ӹ����ڴ����ռ�һ��ָ�����͵��ڴ档</T>
   template <typename T> T* TypeAlloc(){
      TByte* pMemory = _pMemory + _position;
      _position += sizeof(T);
      MO_ASSERT(_length >= _position);
      return (T*)pMemory;
   }
   //------------------------------------------------------------
   // <T>�ӹ����ڴ����ռ�ָ��������ָ�����͵��ڴ档</T>
   template <typename T> T* TypeAlloc(TInt count){
      TByte* pMemory = NULL;
      MO_ASSERT(count > 0);
      pMemory = _pMemory + _position;
      _position += sizeof(T) * count;
      MO_ASSERT(_length >= _position);
      return (T*)pMemory;
   }
   //------------------------------------------------------------
   template <typename T> TShareSegment CreateTypeSegment(){
      TShareSegment segment;
      segment.Initialize(_pMemory + _position, sizeof(T), _created);
      _position += sizeof(T);
      MO_ASSERT(_length >= _position);
      return segment;
   }
   //------------------------------------------------------------
   template <typename T> TShareSegment CreateTypeSegment(TInt count){
      TShareSegment segment;
      TInt capacity = sizeof(T) * count;
      segment.Initialize(_pMemory + _position, capacity, _created);
      _position += capacity;
      MO_ASSERT(_length >= _position);
      return segment;
   }
};

//============================================================
// <T>�����ڴ��ռ����ӿڡ�</T>
//
// @class
// @history 100303 MAOCY ����
//============================================================
class MO_CM_DECLARE IShareAllocator{
public:
   //------------------------------------------------------------
   // <T>���������ڴ��ռ����ӿڡ�</T>
   MO_ABSTRACT ~IShareAllocator(){
   }
public:
   MO_VIRTUAL TAny* MemoryC() = 0;
   MO_VIRTUAL TAny* Alloc(TSize size) = 0;
   MO_VIRTUAL TBool Skip(TSize size) = 0;
   MO_VIRTUAL TShareSegment CreateSegment(TSize size) = 0;
   MO_VIRTUAL TBool Free() = 0;
};

//============================================================
// <T>�����ڴ�������</T>
//
// @class
// @history 100303 MAOCY ����
//============================================================
class MO_CM_DECLARE FShareMemory :
      public FObject,
      public IShareAllocator{
protected:
   TBool _linked;
   TBool _created;
   TInt _position;
   TInt _capacity;
   TShareKey _key;
   TFsPath _keyName;
   TByte* _pMemory;
#ifdef _MO_WINDOWS
   HANDLE _hMemory;
#endif
public:
   FShareMemory();
   MO_ABSTRACT ~FShareMemory();
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TShareKey Key(){
      return _key;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void SetKey(TShareKey key){
      _key = key;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* KeyName(){
      return _keyName;
   }
   //------------------------------------------------------------
   // <T>�����������ơ�</T>
   MO_INLINE void SetKeyName(TCharC* pKeyName){
      _keyName = pKeyName;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ��Ѿ�������</T>
   TBool IsLinked(){
      return _linked;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ��Ѿ�������</T>
   TBool IsCreated(){
      return _created;
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Capacity(){
      return _capacity;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void SetCapacity(TInt capacity){
      _capacity = capacity;
   }
   //------------------------------------------------------------
   // <T>����ڴ档</T>
   MO_INLINE TAny* MemoryC(){
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>���λ���ڴ档</T>
   MO_INLINE TAny* PositionMemoryC(){
      return _pMemory + _position;
   }
public:
   MO_ABSTRACT TBool Create();
   MO_ABSTRACT TBool Connect();
   // MO_METHOD_ABSTRACT TBool TryCreate(TShareKey key, TSize capacity);
   //MO_METHOD_ABSTRACT TBool Link(TShareKey key);
public:
   MO_ABSTRACT TAny* Alloc(TSize size);
   MO_ABSTRACT TBool Skip(TSize size);
   MO_ABSTRACT TShareSegment CreateSegment(TSize size);
   MO_ABSTRACT TBool Free();
};

//============================================================
// <T>�������ݿ�洢���塣</T>
//
// @class
// @history 100118 MAOCY ����
//============================================================
template <typename E>
class FEntryStorage : public FObject{
protected:
   TThreadLocker _locker;
   FBlockAllocator* _pAllocator;
   E* _pUnused;
   TUint _count;
   TUint _total;
public:
   //------------------------------------------------------------
   FEntryStorage(){
      _pAllocator = RAllocator::BlockAllocatorAlloc(sizeof(E));
      MO_CLEAR(_pUnused);
      _count = 0;
      _total = 0;
   }
   //------------------------------------------------------------
   ~FEntryStorage(){
      // �ͷ��������ݿ�
      RAllocator::BlockAllocatorFree(_pAllocator);
   }
public:
   //------------------------------------------------------------
   TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   TInt Total(){
      return _total;
   }
   //------------------------------------------------------------
   E* Alloc(){
      E* pEntry = NULL;
      _locker.Enter();
      if(NULL == _pUnused){
         //pEntry = MO_CALLOC(_pAllocator, E);
         _total++;
      }else{
         _count--;
         pEntry = _pUnused;
         _pUnused = pEntry->pNext;
      }
      _locker.Leave();
      pEntry->pNext = NULL;
      return pEntry;
   }
   //------------------------------------------------------------
   TBool AllocList(TInt count, E** ppFirst, E** ppLast){
      E* pFirst = NULL;
      E* pLast = NULL;
      E* pAlloc = NULL;
      _locker.Enter();
      while(--count >= 0){
         // �ռ�һ�����ݿ�
         if(NULL == _pUnused){
            //pAlloc = MO_CALLOC(_pAllocator, E);
            _total++;
         }else{
            pAlloc = _pUnused;
            _pUnused = pAlloc->pNext;
            _count--;
         }
         // �洢���ݿ�
         pAlloc->pNext = NULL;
         if(NULL == pFirst){
            pFirst = pAlloc;
            pLast = pAlloc;
         }else{
            pLast->pNext = pAlloc;
            pLast = pAlloc;
         }
      }
      *ppFirst = pFirst;
      *ppLast = pAlloc;
      _locker.Leave();
      return ETrue;
   }
   //------------------------------------------------------------
   void Free(E* pEntry){
      MO_ASSERT(pEntry);
      _locker.Enter();
      // �ͷŽڵ�
      pEntry->pNext = _pUnused;
      _pUnused = pEntry;
      _count++;
      _locker.Leave();
   }
   //------------------------------------------------------------
   void FreeList(TInt count, E* pFirst, E* pLast){
      MO_ASSERT(pFirst);
      MO_ASSERT(pLast);
      _locker.Enter();
      _count += count;
      pLast->pNext = _pUnused;
      _pUnused = pFirst;
      _locker.Leave();
   }
};

//============================================================
// <T>�������ݿ�洢���塣</T>
//
// @class
// @history 100118 MAOCY ����
//============================================================
template <typename E>
class FEntryBufferedAllocator{
protected:
   FEntryStorage<E>* _pStorage;
   E* _pFirst;
   E* _pLast;
   TInt _count;
   TInt _capacity;
   TInt _total;
public:
   //------------------------------------------------------------
   FEntryBufferedAllocator(FEntryStorage<E>* pStorage){
      _pStorage = pStorage;
      _pFirst = NULL;
      _pLast = NULL;
      _count = 0;
      _capacity = 32;
      _total = 64;
   }
   //------------------------------------------------------------
   ~FEntryBufferedAllocator(){
      Release();
   }
public:
   //------------------------------------------------------------
   E* Alloc(){
      // ���û�п����ռ��ģ���Ԥ���ռ�
      if(NULL == _pFirst){
         _pStorage->AllocList(_capacity, &_pFirst, &_pLast);
         _count += _capacity;
      }
      // �ռ�һ��δʹ�ÿ�
      E* pEntry = _pFirst;
      _pFirst = pEntry->pNext;
      if(NULL == _pFirst){
         _pLast = NULL;
      }
      pEntry->pNext = NULL;
      _count--;
      return pEntry;
   }
   //------------------------------------------------------------
   void Free(E* pEntry){
      MO_ASSERT(pEntry);
      // �ͷŶ���
      _count++;
      if(NULL == _pFirst){
         _pLast = pEntry;
      }else{
         pEntry->pNext = _pFirst;
      }
      _pFirst = pEntry;
      // ���ڻ������ʱȫ���ͷ�
      if(_count > _total){
         Release();
      }
   }
   //------------------------------------------------------------
   void FreeList(TInt count, E* pFirst, E* pLast){
      MO_ASSERT(pFirst);
      MO_ASSERT(pLast);
      // �ͷŶ���
      _count += count;
      if(NULL == _pFirst){
         _pLast = pLast;
      }else{
         pLast->pNext = _pFirst;
      }
      _pFirst = pFirst;
      // ���ڻ������ʱȫ���ͷ�
      if(_count > _total){
         Release();
      }
   }
   //------------------------------------------------------------
   void Release(){
      if(NULL != _pFirst){
         // �ͷŶ���
         _pStorage->FreeList(_count, _pFirst, _pLast);
         _count = 0;
         _pFirst = NULL;
         _pLast = NULL;
      }
   }
};

//============================================================
// <T>�������ݿ�洢���塣</T>
//
// @class
// @history 100118 MAOCY ����
//============================================================
template <typename A, typename E>
class FEntryBufferedStorage : public FEntryStorage<E>{
public:
   typedef FList<A*> FAtomAllocatorList;
protected:
   FAtomAllocatorList* _pAtomAllocators;
public:
   //------------------------------------------------------------
   FEntryBufferedStorage(){
      _pAtomAllocators = MO_CREATE(FAtomAllocatorList);
   }
   //------------------------------------------------------------
   ~FEntryBufferedStorage(){
      // �ͷ����л���
      TListIteratorC<A*> iterator = _pAtomAllocators->IteratorC();
      while(iterator.Next()){
         A* pAllocator = iterator.Get();
         MO_DELETE(pAllocator);
      }
      MO_DELETE(_pAtomAllocators);
      // �ͷ��������ݿ�
      FEntryStorage<E>::Dispose();
   }
public:
   //------------------------------------------------------------
   A* AllocatorAlloc(){
      A* pAllocator = MO_CREATE(A, this);
      _pAtomAllocators->Push(pAllocator);
      return pAllocator;
   }
   //------------------------------------------------------------
   void AllocatorFree(A* pAllocator){
      MO_ASSERT(pAllocator);
      _pAtomAllocators->Remove(pAllocator);
      MO_DELETE(pAllocator);
   }
};

//============================================================
template <typename T>
struct SAtomEntry{
   SAtomEntry* pPrior;
   SAtomEntry* pNext;
   T value;
};

//============================================================
// <T>ԭ�Ӷ���洢����</T>
//
// @class
// @history 100119 MAOCY ����
//============================================================
template <typename T>
class FAtomStorage : public FObject{
public:
   typedef SAtomEntry<T> SEntry;
protected:
   TThreadSection _locker;
   FBlockAllocator* _pEntryAllocator;
   SEntry* _pFree;
   SEntry* _pUnused;
public:
   //------------------------------------------------------------
   FAtomStorage(){
      _pEntryAllocator = RAllocator::BlockAllocatorAlloc(sizeof(SEntry));
      MO_CLEAR(_pFree);
      MO_CLEAR(_pUnused);
   }
   //------------------------------------------------------------
   ~FAtomStorage(){
      RAllocator::BlockAllocatorFree(_pEntryAllocator);
   }
public:
   //------------------------------------------------------------
   SEntry* EntryAlloc(){
      // ���δʹ�õĽڵ�
      SEntry* pEntry = NULL;
      if(NULL != _pUnused){
         pEntry = _pUnused;
         _pUnused = _pUnused->pNext;
      }else{
         //pEntry = _pEntryAllocator->Alloc("SEntry", sizeof(SEntry), __FILE__, __LINE__);
      }
      // ���ýڵ�
      pEntry->pNext = NULL;
      return pEntry;
   }
   //------------------------------------------------------------
   void EntryFree(SEntry* pEntry){
      pEntry->pNext = _pFree;
      _pFree = pEntry;
   }
   //------------------------------------------------------------
   void EntryUnused(SEntry* pEntry){
      pEntry->pNext = _pUnused;
      _pUnused = pEntry;
   }
protected:
   MO_VIRTUAL T AtomCreate() = 0;
   MO_VIRTUAL void AtomDelete(T value) = 0;
public:
   //------------------------------------------------------------
   // �ռ������
   MO_ABSTRACT T Alloc(){
      // ���һ�����õ������ڴ�
      if(NULL != _pFree){
         T value = _pFree->value;
         SEntry* pNext = _pFree->pNext;
         EntryUnused(_pFree);
         _pFree = pNext;
         return value;
      }
      // �����ռ���Ԫ��
      return AtomCreate();
   }
   //------------------------------------------------------------
   // �ͷſ����
   MO_ABSTRACT void Free(T pValue){
      // �ռ��ڵ�
      SEntry* pEntry = EntryAlloc();
      // ������Ϣ
      pEntry->value = pValue;
      // �洢�ڵ�
      EntryFree(pEntry);
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_MEMORY_H__
