#ifndef __MO_CM_ENTRY_H__
#define __MO_CM_ENTRY_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>ʵ���ض���</T>
//
// @struct
//============================================================
enum EIteratorStatus{
   EIteratorStatus_Loop   = 0,
   EIteratorStatus_Finish = 1,
};

//============================================================
// <T>ʵ���ض���</T>
//
// @struct
//============================================================
enum EIteratorForward{
   EIteratorForward_Next  = 0,
   EIteratorForward_Prior = 1,
};

//============================================================
// <T>ԭ���ڴ��ռ����ӿڡ�</T>
//
// @face
//============================================================
template <typename T>
class IAtomAllocator : public IDispose{
public:
   MO_VIRTUAL T* Alloc() = 0;
   MO_VIRTUAL void Free(T* pAtom) = 0;
   MO_VIRTUAL T* MultiAlloc(TUint count) = 0;
   MO_VIRTUAL void MultiFree(TAny* pAtoms) = 0;
   MO_VIRTUAL T** MultiPtrAlloc(TUint count) = 0;
   MO_VIRTUAL void MultiPtrFree(T** ppAtomss) = 0;
};

//============================================================
// <T>ԭ���ڴ��ռ�����</T>
//
// @face
//============================================================
template <typename T>
class MAtomAllocator : public IAtomAllocator<T>{
public:
   //------------------------------------------------------------
   // ����ԭ���ڴ��ռ���
   MAtomAllocator(){
   }
   //------------------------------------------------------------
   // ����ԭ���ڴ��ռ���
   ~MAtomAllocator(){
   }
public:
   //------------------------------------------------------------
   // �ռ�һ��ԭ��
   MO_OVERRIDE T* Alloc(){
      return MO_TYPE_ALLOC(T);
   };
   //------------------------------------------------------------
   // �ͷ�һ��ԭ��
   MO_OVERRIDE void Free(T* pAtom){
      MO_FREE(pAtom);
   }
   //------------------------------------------------------------
   // �ռ����ԭ��
   MO_OVERRIDE T* MultiAlloc(TUint count){
      T* pAlloc = MO_TYPES_ALLOC(T, count);
      RTypes<T>::Clear(pAlloc, count);
      return pAlloc;
   }
   //------------------------------------------------------------
   // �ͷŶ��ԭ��
   MO_OVERRIDE void MultiFree(TAny* pAtoms){
      MO_FREE(pAtoms);
   }
   //------------------------------------------------------------
   // �ռ����ԭ��ָ��
   MO_OVERRIDE T** MultiPtrAlloc(TUint count){
      T** ppAlloc = MO_TYPES_ALLOC(T*, count);
      RTypes<T*>::Clear(ppAlloc, count);
      return ppAlloc;
   }
   //------------------------------------------------------------
   // �ͷŶ��ԭ��ָ��
   MO_OVERRIDE void MultiPtrFree(T** pAtoms){
      MO_FREE(pAtoms);
   }
};

//============================================================
template <typename T>
class FAllocatorStack{
public:
   T* _pUnused;
public:
   //------------------------------------------------------------
   FAllocatorStack(){
      MO_CLEAR(_pUnused);
   }
   //------------------------------------------------------------
   ~FAllocatorStack(){
   }
public:
   //------------------------------------------------------------
   T* Alloc(){
      T* pValue = NULL;
      if(NULL != _pUnused){
         pValue = _pUnused;
         _pUnused = _pUnused->pNext;
         pValue->pNext = NULL;
      }
      return pValue;
   }
   //------------------------------------------------------------
   void Free(T* pValue){
      MO_ASSERT(pValue);
      pValue->pNext = _pUnused;
      _pUnused = pValue;
   }
};

//============================================================
// <T>ֻ���ڵ��������</T>
//
// @tool
// @history 100318 MAOCY ����
//============================================================
template <typename E>
class MEntryIteratorC{
protected:
   E* _pStart;
   E* _pEntry;
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(E* pEntry){
      _pStart = pEntry;
      _pEntry = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return (NULL == _pEntry);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      return (NULL == _pEntry) ? (NULL != _pStart) : (NULL != _pEntry->pNext);
   }
   //------------------------------------------------------------
   //<T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->pNext;
      return (NULL != _pEntry);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return (NULL == _pEntry) ? (NULL != _pStart) : (NULL != _pEntry->pPrior);
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->pPrior;
      return (NULL != _pEntry);
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _pEntry = NULL;
   }
};

//============================================================
// <T>ֻ���ڵ��������</T>
//
// @tool
// @history 100202 MAOCY ����
//============================================================
template <typename E>
class TEntryIteratorC : public MEntryIteratorC<E>{
public:
   //------------------------------------------------------------
   // ����ֻ���ڵ������
   TEntryIteratorC(){
      Initialize((E)NULL);
   }
   //------------------------------------------------------------
   // ����ֻ���ڵ������
   TEntryIteratorC(const TEntryIteratorC& iterator){
      Initialize(iterator._pStart);
   }
   //------------------------------------------------------------
   // ����ֻ���ڵ������
   TEntryIteratorC(E pEntry){
      Initialize(pEntry);
   }
public:
   //------------------------------------------------------------
   // �жϵ�ǰ�ڵ��Ƿ����
   inline TBool operator==(const TEntryIteratorC& iterator) const{
      return this->_pEntry == iterator._pEntry;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�ڵ��Ƿ����
   inline TBool operator!=(const TEntryIteratorC& iterator) const{
      return this->_pEntry != iterator._pEntry;
   }
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline E& operator *() const{
      return this->_pEntry;
   }
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline E operator ->() const{
      return this->_pEntry;
   }
public:
   //------------------------------------------------------------
   // �ж����������Ƿ����
   inline TBool Equals(E pEntry){
      return this->_pEntry == pEntry;
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline E Get(){
      return this->_pEntry;
   }
};

//============================================================
// <T>�ڵ��ռ�����</T>
// <P>�ڵ��ϱ������pNextָ�롣</P>
//
// @tool
// @param E:entry �ڵ�����
//============================================================
template <typename E>
class TEntryStorage{
protected:
   E* _pUnused;
public:
   //------------------------------------------------------------
   // ����ڵ��ռ���
   TEntryStorage(){
      Initialize();
   }
   //------------------------------------------------------------
   // �����ڵ��ռ���
   ~TEntryStorage(){
      Release();
   }
public:
   //------------------------------------------------------------
   // ��ʼ������
   void Initialize(){
      _pUnused = NULL;
   }
   //------------------------------------------------------------
   // �ͷ�����
   void Release(){
      while(NULL != _pUnused){
         E* pEntry = _pUnused;
         MO_FREE(pEntry);
         _pUnused = pEntry;
      }
   }
public:
   //------------------------------------------------------------
   // �ռ�һ��δʹ�õĽڵ�
   E* Alloc(){
      E* pEntry = NULL;
      // �鿴δʹ�ýڵ����Ƿ������ɽڵ�
      if(NULL != _pUnused){
         // �ռ�δʹ�õĽڵ�
         pEntry = _pUnused;
         _pUnused = _pUnused->pNext;
      }else{
         // �ռ��½ڵ�
         pEntry = MO_TYPE_ALLOC(E);
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // �ͷ�һ����ʹ�õĽڵ�
   void Free(E* pEntry){
      MO_ASSERT(pEntry);
      pEntry->pNext = _pUnused;
      _pUnused = pEntry;
   }
   //------------------------------------------------------------
   // �ͷ�һ����ʹ�õĽڵ�
   void Free(E* pFirst, E* pLast){
      MO_ASSERT(pFirst);
      MO_ASSERT(pLast);
      pLast->pNext = _pUnused;
      _pUnused = pFirst;
   }
};

//============================================================
// <T>�ڵ��ռ�����</T>
// <P>�ڵ��ϱ������pNextָ�롣</P>
//
// @tool
// @param E:entry �ڵ�����
// @param C:capacity �������
//============================================================
template <typename E, TInt C>
class TFixEntryStorage{
protected:
   E* _pUnused;
   TInt _alloc;
   E _entries[C];
public:
   //------------------------------------------------------------
   // ����ڵ��ռ���
   TFixEntryStorage(){
      _pUnused = NULL;
      _alloc = 0;
   }
public:
   //------------------------------------------------------------
   // ��ʼ������
   void Initialize(){
      _pUnused = NULL;
      _alloc = 0;
   }
public:
   //------------------------------------------------------------
   // �ռ�һ��δʹ�õĽڵ�
   E* Alloc(){
      E* pEntry = NULL;
      // �鿴δʹ�ýڵ����Ƿ������ɽڵ�
      if(NULL != _pUnused){
         // �ռ�δʹ�õĽڵ�
         pEntry = _pUnused;
         _pUnused = _pUnused->pNext;
      }else{
         // �ռ��½ڵ�
         MO_ASSERT(_alloc < C);
         pEntry = &_entries[_alloc++];
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // �ͷ�һ����ʹ�õĽڵ�
   void Free(E* pEntry){
      MO_ASSERT(pEntry);
      pEntry->pNext = _pUnused;
      _pUnused = pEntry;
   }
   //------------------------------------------------------------
   // �ͷ�һ����ʹ�õĽڵ�
   void Free(E* pFirst, E* pLast){
      MO_ASSERT(pFirst);
      MO_ASSERT(pLast);
      pLast->pNext = _pUnused;
      _pUnused = pFirst;
   }
};


//============================================================
// <T>�ڵ��ռ�����</T>
// <P>�ڵ��ϱ������pNextָ�롣</P>
//
// @tool
// @param E:entry �ڵ�����
//============================================================
template <typename E>
class TEntryFlatStorage : public TEntryStorage<E>{
protected:
   E** _pMemory;
public:
   //------------------------------------------------------------
   // ����ڵ��ռ���
   TEntryFlatStorage(){
      Initialize();
   }
   //------------------------------------------------------------
   // �����ڵ��ռ���
   ~TEntryFlatStorage(){
      Release();
   }
public:
   //------------------------------------------------------------
   // ��ʼ������
   void Initialize(){
      TEntryStorage<E>::Initialize();
      _pMemory = NULL;
   }
   //------------------------------------------------------------
   // �ͷ�����
   void Release(){
      TEntryStorage<E>::Release();
      MO_FREE(_pMemory);
   }
public:
   //------------------------------------------------------------
   // �����ڵ�������С
   E** FlatAlloc(TInt size){
      E** ppEntities = MO_TYPES_ALLOC(E*, size);
      RTypes<E*>::Clear(ppEntities, size);
      return ppEntities;
   }
   //------------------------------------------------------------
   // �����ڵ�������С
   void FlatFree(E** pPtr){
      MO_FREE(pPtr);
   }
};

//============================================================
// <T>�ڵ��ռ�����</T>
// <P>�ڵ��ϱ������pNextָ�롣</P>
//
// @tool
// @param E:entry �ڵ�����
// @param C:capacity �������
//============================================================
template <typename E, TInt C>
class TFixEntryFlatStorage : public TFixEntryStorage<E, C>{
protected:
   E* _pEntries[C];
public:
   //------------------------------------------------------------
   // ����ڵ��ռ���
   TFixEntryFlatStorage(){
      RTypes<E*>::Clear(_pEntries, C);
   }
public:
   //------------------------------------------------------------
   // ��ʼ������
   void Initialize(){
      TFixEntryStorage<E, C>::Initialize();
      RTypes<E*>::Clear(_pEntries, C);
   }
public:
   //------------------------------------------------------------
   // �����ڵ�������С
   E** FlatAlloc(TInt size){
      MO_ASSERT(size < C);
      return _pEntries;
   }
   //------------------------------------------------------------
   // �����ڵ�������С
   void FlatFree(E** pPtr){
      MO_FREE(pPtr);
   }
};

//============================================================
// <T>ֻ������˫����</T>
// <P>E{E pPrior, E pNext, ...}</P>
//
// @base
//============================================================
template <typename E>
class MEntriesC{
protected:
   TInt _count;
   E* _pFirst;
   E* _pLast;
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(){
      _count = 0;
      _pFirst = NULL;
      _pLast = NULL;
   }
protected:
   //------------------------------------------------------------
   // <T>������ڵ�ѹ����λ�á�</T>
   MO_INLINE E* EntryGet(TInt index) const{
      MO_ASSERT_RANGE(index, 0, this->_count);
      // ��õ�һ��
      if(0 == index){
         return this->_pFirst;
      }
      // ���ָ��λ������
      E* pEntry = this->_pFirst;
      while(--index >= 0){
         pEntry = pEntry->pNext;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>������ڵ�ѹ����λ�á�</T>
   MO_INLINE void EntryUnshift(E* pEntry){
      MO_ASSERT(pEntry);
      if(NULL == _pFirst){
         _pLast = pEntry;
      }else{
         _pFirst->pPrior = pEntry;
      }
      pEntry->pPrior = NULL;
      pEntry->pNext = _pFirst;
      _pFirst = pEntry;
      _count++;
   }
   //------------------------------------------------------------
   // <T>����������׽ڵ㡣</T>
   MO_INLINE E* EntryShift(){
      E* pEntry = _pFirst;
      if(NULL != pEntry){
         // ��ָ��ָ����һ��λ��
         _pFirst = _pFirst->pNext;
         if(NULL == _pFirst){
            _pLast = NULL;
         }else{
            _pFirst->pPrior = NULL;
         }
         // ��������
         _count--;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>������ڵ�ѹ��βλ�á�</T>
   MO_INLINE void EntryPush(E* pEntry){
      MO_ASSERT(pEntry);
      if(NULL == _pLast){
         _pFirst = pEntry;
      }else{
         _pLast->pNext = pEntry;
      }
      pEntry->pPrior = _pLast;
      pEntry->pNext = NULL;
      _pLast = pEntry;
      _count++;
   }
   //------------------------------------------------------------
   // <T>���������β�ڵ㡣</T>
   MO_INLINE E* EntryPop(){
      E* pEntry = _pLast;
      if(NULL != pEntry){
         _pLast = _pLast->pPrior;
         if(NULL == _pLast){
            _pFirst = NULL;
         }else{
            _pLast->pNext = NULL;
         }
         // ��������
         _count--;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>��ָ������ڵ�����һ��������ڵ㡣</T>
   MO_INLINE void EntryInsert(E* pPrior, E* pEntry){
      MO_ASSERT(pPrior);
      MO_ASSERT(pEntry);
      E* pNext = pPrior->pNext;
      pPrior->pNext = pEntry;
      pEntry->pPrior = pPrior;
      if(NULL == pNext){
         pEntry->pNext = NULL;
         _pLast = pEntry;
      }else{
         pNext->pPrior = pEntry;
         pEntry->pNext = pNext;
      }
   }
   //------------------------------------------------------------
   // <T>��������ɾ������ڵ㡣</T>
   MO_INLINE void EntryRemove(E* pEntry){
      MO_ASSERT(pEntry);
      E* pPrior = pEntry->pPrior;
      E* pNext = pEntry->pNext;
      // ����ǰ�ڵ�
      if(NULL == pPrior){
         _pFirst = pNext;
      }else{
         pPrior->pNext = pNext;
      }
      // �����ڵ�
      if(NULL == pNext){
         _pLast = pPrior;
      }else{
         pNext->pPrior = pPrior;
      }
      // ��������
      _count--;
   }
   //------------------------------------------------------------
   // <T>�������ʹ���еĽڵ㡣</T>
   MO_INLINE void EntryClear(){
      // �������
      _count = 0;
      _pFirst = NULL;
      _pLast = NULL;
   }
};

//============================================================
// <T>ֻ���ڵ��������</T>
//
// @tool
// @history 100202 MAOCY ����
//============================================================
template <typename E>
class MLinkedIteratorC{
protected:
   E _pStart;
   E _pEntry;
protected:
   //------------------------------------------------------------
   // �ڲ���ʼ��
   inline void Initialize(E pEntry){
      _pStart = pEntry;
      _pEntry = NULL;
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline E& operator *() const{
      return this->_pEntry;
   }
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline E operator ->() const{
      return this->_pEntry;
   }
public:
   //------------------------------------------------------------
   // ����λ��
   inline void Reset(){
      _pEntry = NULL;
   }
   //------------------------------------------------------------
   // �ж��Ƿ������һ��λ��
   inline TBool HasNext(){
      return (NULL == _pEntry) ? (NULL != _pStart) : (NULL == _pEntry->pNext);
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Next(){
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->pNext;
      return (NULL != _pEntry);
   }
   //------------------------------------------------------------
   // �ж��Ƿ������һ��λ��
   inline TBool HasPrior(){
      return (NULL == _pEntry) ? (NULL != _pStart) : (NULL == _pEntry->pPrior);
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Prior(){
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->pPrior;
      return (NULL != _pEntry);
   }
};

//============================================================
// <T>ֻ���ڵ��������</T>
//
// @tool
// @history 100202 MAOCY ����
//============================================================
template <typename E>
class TLinkedIteratorC : public MLinkedIteratorC<E>{
public:
   //------------------------------------------------------------
   // ����ֻ���ڵ������
   TLinkedIteratorC(){
      Initialize((E)NULL);
   }
   //------------------------------------------------------------
   // ����ֻ���ڵ������
   TLinkedIteratorC(const MLinkedIteratorC<E>& iterator){
      Initialize(iterator._pStart);
   }
   //------------------------------------------------------------
   // ����ֻ���ڵ������
   TLinkedIteratorC(E pEntry){
      Initialize(pEntry);
   }
public:
   //------------------------------------------------------------
   // �жϵ�ǰ�ڵ��Ƿ����
   inline TBool operator==(const MLinkedIteratorC<E>& iterator) const{
      return this->_pEntry == iterator._pEntry;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�ڵ��Ƿ����
   inline TBool operator!=(const MLinkedIteratorC<E>& iterator) const{
      return this->_pEntry != iterator._pEntry;
   }
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline operator const E() const{
      return this->_pEntry;
   }
public:
   //------------------------------------------------------------
   // �ж����������Ƿ����
   inline TBool Equals(E pEntry){
      return this->_pEntry == pEntry;
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline E Get(){
      return this->_pEntry;
   }
};

//============================================================
// <T>ֻ������˫����</T>
// <P>E{E pPrior, E pNext}</P>
//
// @base
//============================================================
template <typename E>
class MLinkedEntryC{
protected:
   TInt _count;
   E _pFirst;
   E _pLast;
   E _pUnused;
protected:
   //------------------------------------------------------------
   // �ڲ���ʼ��
   inline void Initialize(){
      _count = 0;
      _pFirst = NULL;
      _pLast = NULL;
      _pUnused = NULL;
   }
protected:
   //------------------------------------------------------------
   // ������ڵ�ѹ����λ��
   inline void EntryUnshift(E pEntry){
      MO_ASSERT(pEntry);
      // ѹ����λ��
      if(NULL == _pFirst){
         _pLast = pEntry;
      }else{
         _pFirst->pPrior = pEntry;
      }
      pEntry->pNext = _pFirst;
      _pFirst = pEntry;
      // ��������
      _count++;
      pEntry->pPrior = NULL;
   }
   //------------------------------------------------------------
   // ����������׽ڵ�
   inline E EntryShift(){
      E pEntry = _pFirst;
      if(NULL != _pFirst){
         // ��ָ��ָ����һ��λ��
         _pFirst = _pFirst->pNext;
         if(NULL == _pFirst){
            _pLast = NULL;
         }else{
            _pFirst->pPrior = NULL;
         }
         // ��������
         _count--;
         EntryFree(pEntry);
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // ������ڵ�ѹ��βλ��
   inline void EntryPush(E pEntry){
      MO_ASSERT(pEntry);
      if(NULL == _pLast){
         _pFirst = pEntry;
      }else{
         _pLast->pNext = pEntry;
      }
      pEntry->pPrior = _pLast;
      _pLast = pEntry;
      // ��������
      _count++;
      pEntry->pNext = NULL;
   }
   //------------------------------------------------------------
   // ���������β�ڵ�
   inline E EntryPop(){
      E pEntry = _pLast;
      if(NULL != _pLast){
         _pLast = _pLast->pPrior;
         if(NULL == _pLast){
            _pFirst = NULL;
         }else{
            _pLast->pNext = NULL;
         }
         // ��������
         _count--;
         EntryFree(pEntry);
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // ��ָ������ڵ�����һ��������ڵ�
   inline void EntryInsert(E pPrior, E pEntry){
      MO_ASSERT(pPrior);
      MO_ASSERT(pEntry);
      E pNext = pPrior->pNext;
      pPrior->pNext = pEntry;
      pEntry->pPrior = pPrior;
      if(NULL == pNext){
         pEntry->pNext = NULL;
         _pLast = pEntry;
      }else{
         pNext->pPrior = pEntry;
         pEntry->pNext = pNext;
      }
   }
   //------------------------------------------------------------
   // ��������ɾ������ڵ�
   inline void EntryRemove(E pEntry){
      MO_ASSERT(pEntry);
      E pPrior = pEntry->pPrior;
      E pNext = pEntry->pNext;
      // ����ǰ�ڵ�
      if(NULL == pPrior){
         _pFirst = pNext;
      }else{
         pPrior->pNext = pNext;
      }
      // �����ڵ�
      if(NULL == pNext){
         _pLast = pPrior;
      }else{
         pNext->pPrior = pPrior;
      }
      // ��������
      _count--;
      EntryFree(pEntry);
   }
   //------------------------------------------------------------
   // ���ڵ����δʹ��λ��
   inline void EntryFree(E pEntry){
      MO_ASSERT(pEntry);
      pEntry->pNext = _pUnused;
      _pUnused = pEntry;
   }
   //------------------------------------------------------------
   // �������ʹ���еĽڵ㣬����δʹ��������ѭ��ʹ��
   inline void EntryClear(){
      if(_count > 0){
         // ��ʹ�ýڵ�ȫ��������սڵ�
         _pLast->pNext = _pUnused;
         _pUnused = _pFirst;
         // �������������
         _count = 0;
         _pFirst = NULL;
         _pLast = NULL;
      }
   }
};

//============================================================
// <T>ֻ������˫����</T>
// <P>T{T pPrior, T pNext}</P>
//
// @base
//============================================================
template <typename E>
class MEntryListC : public MLinkedEntryC<E>{
public:
   typedef MLinkedEntryC<E> MLinkedC;
   typedef TEntryIteratorC<E> TIteratorC;
public:
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   TBool operator==(const MEntryListC<E>& list) const{
      return Equals(list);
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   TBool operator!=(const MEntryListC<E>& list) const{
      return !Equals(list);
   }
public:
   //------------------------------------------------------------
   // ����Ƿ�Ϊ��
   TBool IsEmpty() const{
      return (0 == this->_count);
   }
   //------------------------------------------------------------
   // �������
   TInt Count() const{
      return this->_count;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ�������Ƿ����
   TBool Equals(const MEntryListC<E>& list) const{
      // �Ƚ�����
      if(this->_count != list._count){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      E pEntry = this->_pFirst;
      TIteratorC iterator = list.IteratorC();
      while(iterator.Next()){
         if(pEntry != iterator.Get()){
            return EFalse;
         }
         pEntry = pEntry->pNext;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // �����λ�õ�����
   E First() const{
      return this->_pFirst;
   }
   //------------------------------------------------------------
   // ���βλ�õ�����
   E Last() const{
      return this->_pLast;
   }
   //------------------------------------------------------------
   // �����λ�õ�ֻ�����ݵ�����
   TIteratorC IteratorC() const{
      return TIteratorC(this->_pFirst);
   }
   //------------------------------------------------------------
   // ���βλ�õ�ֻ�����ݵ�����
   TIteratorC LastIteratorC() const{
      return TIteratorC(this->_pLast);
   }
   //------------------------------------------------------------
   // ���ָ��λ�õ�����
   E Get(TInt index) const{
      MO_ASSERT_RANGE(index, 0, this->_count);
      // ��õ�һ��
      if(0 == index){
         return this->_pFirst;
      }
      // ���ָ��λ������
      E pEntry = this->_pFirst;
      while(--index >= 0){
         pEntry = pEntry->pNext;
      }
      return pEntry->value;
   }
   //------------------------------------------------------------
   // ��ָ������������в���ָ������
   TBool Find(const TIteratorC& iterator, E pEntry) const{
      while(iterator.Next()){
         if(iterator.Equals(pEntry)){
            return ETrue;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // �ڵ�ǰ�����в���ָ������
   TIteratorC FindC(E pEntry) const{
      TIteratorC& iterator = IteratorC();
      if(Find(iterator, pEntry)){
         return iterator;
      }
      return LastIteratorC();
   }
};

//============================================================
// <T>����˫����</T>
// <P>T{T pPrior, T pNext}</P>
//
// @base
//============================================================
template <typename E>
class MEntryList : public MEntryListC<E>{
public:
   typedef TEntryIteratorC<E> TIteratorC;
public:
   //------------------------------------------------------------
   MEntryList(){
   }
   //------------------------------------------------------------
   ~MEntryList(){
   }
public:
   //------------------------------------------------------------
   // ����һ��������ǰ�����С�
   void Assign(const MEntryList<E>& list){
      Clear();
      Append(list);
   }
   //------------------------------------------------------------
   // ׷��һ��������ǰ�����С�
   void Append(const MEntryListC<E>& list){
      TIteratorC iterator = list.IteratorC();
      while(iterator.Next()){
         Push(iterator.Get());
      }
   }
   //------------------------------------------------------------
   // ������ѹ����λ��
   void Unshift(E entry){
      EntryUnshift(entry);
   }
   //------------------------------------------------------------
   // ���������������
   E Shift(){
      return MEntryListC<E>::EntryShift();
   }
   //------------------------------------------------------------
   // ������ѹ��βλ��
   void Push(E entry){
      EntryPush(entry);
   }
   //------------------------------------------------------------
   // ���������β����
   E Pop(){
      return MEntryListC<E>::EntryPop();
   }
   //------------------------------------------------------------
   // ��������ɾ������
   void Remove(E entry){
      EntryRemove(entry);
   }
   //------------------------------------------------------------
   // �����������
   void Clear(){
      MEntryListC<E>::EntryClear();
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_ENTRY_H__

