#ifndef __MO_CM_LIST_H__
#define __MO_CM_LIST_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

#define MO_COMPLIST_THRESHOLD 8

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ľڵ㶨�塣</T>
//
// @struct
//============================================================
template <typename T>
struct SListEntry{
   /// @attribute ǰһ�����
   SListEntry* priorPtr;
   /// @attribute ��һ�����
   SListEntry* nextPtr;
   /// @attribute ��������
   T value;
};

//============================================================
// <T>�ڴ������ࡣ</T>
//
// @tool
// @class E �������
// @class T ��������
// @history 100318 MAOCY ����
//============================================================
template <typename E, typename T>
class RList{
public:
   typedef TInt (*HComparer)(T source, T target);
protected:
   //------------------------------------------------------------
   // <T>˫������Ŀ�������</T>
   static MO_INLINE E* InnerPartion(E* pLeft, E* pRight, HComparer hComparer = NULL){
      T value = pLeft->value;
      while(pLeft != pRight){
         //�Ӻ�����ǰ��
         while((pLeft != pRight) && (hComparer(pRight->value, value) >= 0)){
            pRight = pRight->priorPtr;
         }
         // ����λ��
         T temp1 = pLeft->value;
         pLeft->value = pRight->value;
         pRight->value = temp1;
         //��ǰ����
         while((pLeft != pRight) && (hComparer(pLeft->value, value) <= 0)){
            pLeft = pLeft->nextPtr;
         }
         // ����λ��
         T temp2 = pLeft->value;
         pLeft->value = pRight->value;
         pRight->value = temp2;
      }
      return pLeft;
   }
public:
   //------------------------------------------------------------
   // <T>˫������Ŀ�������</T>
   static void Sort(E* pLeft, E* pRight, HComparer hComparer = NULL){
      E* pTemp = NULL;
      pTemp = InnerPartion(pLeft, pRight, hComparer);
      if(pLeft != pTemp){
         Sort(pLeft, pTemp->priorPtr, hComparer);
      }
      if(pRight != pTemp){
         Sort(pTemp->nextPtr, pRight, hComparer);
      }
   }
};

//============================================================
// <T>ֻ������ĵ�������</T>
//
// @tool
//============================================================
template <typename T>
class TListIteratorC{
public:
   typedef SListEntry<T> SEntry;
protected:
   SEntry* _pStart;
   SEntry* _pEntry;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TListIteratorC(){
      MO_CLEAR(_pStart);
      MO_CLEAR(_pEntry);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TListIteratorC(const TListIteratorC& iterator){
      _pStart = iterator._pStart;
      _pEntry = iterator._pEntry;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TListIteratorC(SEntry* pEntry){
      _pStart = pEntry;
      _pEntry = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& operator *() const{
      MO_ASSERT(_pEntry);
      return _pEntry->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T operator->() const{
      MO_ASSERT(_pEntry);
      return _pEntry->value;
   }
public:
   //------------------------------------------------------------
   // <T>��ÿ�ʼ�ڵ㡣</T>
   MO_INLINE SEntry* Start() const{
      return _pStart;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰ�ڵ㡣</T>
   MO_INLINE SEntry* Entry() const{
      return _pEntry;
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
      return (NULL == _pEntry) ? (NULL != _pStart) : (NULL != _pEntry->nextPtr);
   }
   //------------------------------------------------------------
   //<T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->nextPtr;
      return (NULL != _pEntry);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return (NULL == _pEntry) ? (NULL != _pStart) : (NULL != _pEntry->priorPtr);
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->priorPtr;
      return (NULL != _pEntry);
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _pEntry = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T value){
      MO_ASSERT(_pEntry);
      return _pEntry->value == value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T Get(){
      MO_ASSERT(_pEntry);
      return _pEntry->value;
   }
};

//============================================================
// <T>��д����ĵ�������</T>
//
// @tool
//============================================================
template <typename T>
class TListIterator{
public:
   typedef SListEntry<T> SEntry;
protected:
   SEntry* _pStart;
   SEntry* _pEntry;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TListIterator(){
      MO_CLEAR(_pStart);
      MO_CLEAR(_pEntry);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TListIterator(const TListIteratorC<T>& iterator){
      _pStart = iterator.Start();
      _pEntry = iterator.Entry();
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TListIterator(const TListIterator& iterator){
      _pStart = iterator._pStart;
      _pEntry = iterator._pEntry;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TListIterator(SEntry* pEntry){
      _pStart = pEntry;
      _pEntry = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& operator *() const{
      MO_ASSERT(_pEntry);
      return _pEntry->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T operator->() const{
      MO_ASSERT(_pEntry);
      return _pEntry->value;
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
      return (NULL == _pEntry) ? (NULL != _pStart) : (NULL != _pEntry->nextPtr);
   }
   //------------------------------------------------------------
   //<T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->nextPtr;
      return (NULL != _pEntry);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return (NULL == _pEntry) ? (NULL != _pStart) : (NULL != _pEntry->priorPtr);
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->priorPtr;
      return (NULL != _pEntry);
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _pEntry = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T value){
      MO_ASSERT(_pEntry);
      return _pEntry->value == value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T Get(){
      MO_ASSERT(_pEntry);
      return _pEntry->value;
   }
   //------------------------------------------------------------
   // <T>���õ�ǰλ�õ��������ơ�</T>
   MO_INLINE void Set(T value) const{
      MO_ASSERT(_pEntry);
      _pEntry->value = value;
   }
};

//============================================================
// <T>˫������</T>
//
// @history 091208 MAOCY ����
//============================================================
template <typename T>
class MList{
public:
   typedef TInt (*HComparer)(T source, T target);
   typedef SListEntry<T> SEntry;
   typedef TListIteratorC<T> TIteratorC;
   typedef TListIterator<T> TIterator;
protected:
   TInt _count;
   SEntry* _pFirst;
   SEntry* _pLast;
   SEntry* _pUnused;
public:
   //------------------------------------------------------------
   // <T>����˫������</T>
   MList(){
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      MO_CLEAR(_pUnused);
   }
   //------------------------------------------------------------
   // <T>����˫������</T>
   MO_ABSTRACT ~MList(){
   }
protected:
   MO_VIRTUAL SEntry* EntryCreate() = 0;
   MO_VIRTUAL void EntryRelease(SEntry* pEntry) = 0;
protected:
   //------------------------------------------------------------
   // <T>�ռ�һ��δʹ�õĽڵ㡣</T>
   MO_INLINE SEntry* EntryAlloc(){
      SEntry* pEntry = NULL;
      // �鿴δʹ�ýڵ����Ƿ������ɽڵ�
      if(NULL != _pUnused){
         // �ռ�δʹ�õĽڵ�
         pEntry = _pUnused;
         _pUnused = _pUnused->nextPtr;
      }else{
         // �ռ��½ڵ�
         pEntry = this->EntryCreate();
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ����ʹ�õĽڵ㡣</T>
   MO_INLINE void EntryFree(SEntry* pEntry){
      MO_ASSERT(pEntry);
      pEntry->nextPtr = _pUnused;
      _pUnused = pEntry;
   }
   //------------------------------------------------------------
   // <T>������ڵ�ѹ����λ�á�</T>
   MO_INLINE SEntry* EntryGet(TInt index) const{
      MO_ASSERT_RANGE(index, 0, _count);
      // ��õ�һ��
      if(0 == index){
         return _pFirst;
      }
      // ���ָ��λ������
      SEntry* pEntry = _pFirst;
      while(--index >= 0){
         pEntry = pEntry->nextPtr;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>������ڵ�ѹ����λ�á�</T>
   MO_INLINE void EntryUnshift(SEntry* pEntry){
      MO_ASSERT(pEntry);
      if(NULL == _pFirst){
         _pLast = pEntry;
      }else{
         _pFirst->priorPtr = pEntry;
      }
      pEntry->priorPtr = NULL;
      pEntry->nextPtr = _pFirst;
      _pFirst = pEntry;
      _count++;
   }
   //------------------------------------------------------------
   // <T>����������׽ڵ㡣</T>
   MO_INLINE SEntry* EntryShift(){
      SEntry* pEntry = _pFirst;
      if(NULL != pEntry){
         // ��ָ��ָ����һ��λ��
         _pFirst = _pFirst->nextPtr;
         if(NULL == _pFirst){
            _pLast = NULL;
         }else{
            _pFirst->priorPtr = NULL;
         }
         // ��������
         _count--;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>������ڵ�ѹ��βλ�á�</T>
   MO_INLINE void EntryPush(SEntry* pEntry){
      MO_ASSERT(pEntry);
      if(NULL == _pLast){
         _pFirst = pEntry;
      }else{
         _pLast->nextPtr = pEntry;
      }
      pEntry->priorPtr = _pLast;
      pEntry->nextPtr = NULL;
      _pLast = pEntry;
      _count++;
   }
   //------------------------------------------------------------
   // <T>���������β�ڵ㡣</T>
   MO_INLINE SEntry* EntryPop(){
      SEntry* pEntry = _pLast;
      if(NULL != pEntry){
         _pLast = _pLast->priorPtr;
         if(NULL == _pLast){
            _pFirst = NULL;
         }else{
            _pLast->nextPtr = NULL;
         }
         // ��������
         _count--;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>��ָ������ڵ�����һ��������ڵ㡣</T>
   MO_INLINE void EntryInsert(SEntry* pPrior, SEntry* pEntry){
      MO_ASSERT(pPrior);
      MO_ASSERT(pEntry);
      SEntry* pNext = pPrior->nextPtr;
      pPrior->nextPtr = pEntry;
      pEntry->priorPtr = pPrior;
      if(NULL == pNext){
         pEntry->nextPtr = NULL;
         _pLast = pEntry;
      }else{
         pNext->priorPtr = pEntry;
         pEntry->nextPtr = pNext;
      }
   }
   //------------------------------------------------------------
   // <T>��������ɾ������ڵ㡣</T>
   MO_INLINE void EntryRemove(SEntry* pEntry){
      MO_ASSERT(pEntry);
      SEntry* pPrior = pEntry->priorPtr;
      SEntry* pNext = pEntry->nextPtr;
      // ����ǰ�ڵ�
      if(NULL == pPrior){
         _pFirst = pNext;
      }else{
         pPrior->nextPtr = pNext;
      }
      // �����ڵ�
      if(NULL == pNext){
         _pLast = pPrior;
      }else{
         pNext->priorPtr = pPrior;
      }
      // ��������
      _count--;
   }
public:
   //------------------------------------------------------------
   // <T>�жϵ�ǰ�����ָ���������������������Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const MList<T>& list) const{
      return Equals(&list);
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ�����ָ���������������������Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const MList<T>& list) const{
      return !Equals(&list);
   }
   //------------------------------------------------------------
   // <T>׷��һ�����ݵ���ǰ�����С�</T>
   MO_INLINE void operator+=(T value){
      Push(value);
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ������ɾ��һ�����ݡ�</T>
   MO_INLINE void operator-=(T value){
      Remove(value);
   }
   //------------------------------------------------------------
   // <T>׷��һ��������ǰ�����С�</T>
   MO_INLINE void operator+=(const MList<T>* pList){
      Append(pList);
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Count() const{
      return _count;
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ�����ָ�������Ƿ���ȡ�</T>
   TBool Equals(const MList<T>* pList) const{
      MO_ASSERT(pList);
      // �Ƚ�����
      if(_count != pList->Count()){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      SEntry* pEntry = _pFirst;
      TIteratorC iterator = pList->IteratorC();
      while((NULL != pEntry) && iterator.Next()){
         if(!iterator.Equals(pEntry->value)){
            return EFalse;
         }
         pEntry = pEntry->nextPtr;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�����λ�õ����ݡ�</T>
   T First() const{
      return (NULL != _pFirst) ? _pFirst->value : NULL;
   }
   //------------------------------------------------------------
   // <T>���βλ�õ����ݡ�</T>
   T Last() const{
      return (NULL != _pLast) ? _pLast->value : NULL;
   }
   //------------------------------------------------------------
   // <T>�����λ�õ�ֻ�����ݵ�������</T>
   TIteratorC IteratorC() const{
      return TIteratorC(_pFirst);
   }
   //------------------------------------------------------------
   // <T>���βλ�õ�ֻ�����ݵ�������</T>
   TIteratorC LastIteratorC() const{
      return TIteratorC(_pLast);
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�������Ƿ���ָ�����ݡ�</T>
   TBool Contains(T value) const{
      if(_count > 0){
         // �Ƚ�������Ŀ
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            if(pEntry->value == value){
               return ETrue;
            }
            pEntry = pEntry->nextPtr;
         }
      }
      return EFalse;
   }
public:
   //------------------------------------------------------------
   // <T>����ָ��λ�õ����ݡ�</T>
   T FindByIndex(TInt index) const{
      SEntry* pEntry = EntryGet(index);
      return (NULL != pEntry) ? pEntry->value : NULL;
   }
   //------------------------------------------------------------
   // <T>���ָ��λ�õ����ݡ�</T>
   T GetByIndex(TInt index) const{
      SEntry* pEntry = EntryGet(index);
      return pEntry->value;
   }
   //------------------------------------------------------------
   // <T>�ڵ�ǰ�����в���ָ�����ݡ�</T>
   TIteratorC FindC(T value) const{
      if(_count > 0){
         // �Ƚ�������Ŀ
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            if(pEntry->value == value){
               return TIteratorC(pEntry);
            }
            pEntry = pEntry->nextPtr;
         }
      }
      return TIteratorC();
   }
   //------------------------------------------------------------
   // <T>��ָ������������в���ָ�����ݡ�</T>
   TBool FindC(TIteratorC& iterator, T value) const{
      while(iterator.Next()){
         if(iterator.Equals(value)){
            return ETrue;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>���ƶ����ⲿ���顣</T>
   TInt CopyTo(T* pBuffer, TInt capacity) const{
      TInt count = MO_LIB_MIN(_count, capacity);
      if(count > 0){
         TInt n = 0;
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            pBuffer[n++] = pEntry->value;
            pEntry = pEntry->nextPtr;
         }
      }
      return count;
   }
public:
   //------------------------------------------------------------
   // <T>�����λ�õ�ֻ�����ݵ�������</T>
   TIterator Iterator(){
      return TIterator(_pFirst);
   }
   //------------------------------------------------------------
   // <T>���βλ�õ�ֻ�����ݵ�������</T>
   TIterator LastIterator(){
      return TIterator(_pLast);
   }
   //------------------------------------------------------------
   // <T>�ڵ�ǰ�����в���ָ�����ݡ�</T>
   TIterator Find(T value){
      if(_count > 0){
         SEntry* pFind = _pFirst;
         while(NULL != pFind){
            if(pFind->value == value){
               return TIterator(pFind);
            }
            pFind = pFind->nextPtr;
         }
      }
      return TIterator();
   }
public:
   //------------------------------------------------------------
   // <T>����һ��������ǰ�����С�</T>
   void Assign(const MList<T>* pList){
      MO_ASSERT(pList);
      Clear();
      Append(pList);
   }
   //------------------------------------------------------------
   // <T>����һ��������ǰ�����С�</T>
   void Assign(TIteratorC& iterator){
      Clear();
      Append(iterator);
   }
   //------------------------------------------------------------
   // <T>׷��һ��������ǰ�����С�</T>
   void Append(const MList<T>* pList){
      MO_ASSERT(pList);
      TIteratorC iterator = pList->IteratorC();
      while(iterator.Next()){
         Push(*iterator);
      }
   }
   //------------------------------------------------------------
   // <T>׷��һ��������ǰ�����С�</T>
   void Append(TIteratorC& iterator){
      while(iterator.Next()){
         Push(*iterator);
      }
   }
   //------------------------------------------------------------
   // <T>������ѹ����λ�á�</T>
   void Unshift(T value){
      // �ռ�һ��δʹ�õýڵ�
      SEntry* pEntry = EntryAlloc();
      // ���ڵ�ѹ��β��
      pEntry->value = value;
      EntryUnshift(pEntry);
   }
   //------------------------------------------------------------
   // <T>��������������ݡ�</T>
   T Shift(){
      SEntry* pEntry = EntryShift();
      MO_ASSERT(pEntry);
      T value = pEntry->value;
      EntryFree(pEntry);
      return value;
   }
   //------------------------------------------------------------
   // <T>������ѹ��βλ�á�</T>
   void Push(T value){
      // �ռ�һ��δʹ�õýڵ�
      SEntry* pEntry = EntryAlloc();
      // ���ڵ�ѹ��β��
      pEntry->value = value;
      EntryPush(pEntry);
   }
   //------------------------------------------------------------
   // <T>���������β���ݡ�</T>
   T Pop(){
      SEntry* pEntry = EntryPop();
      MO_ASSERT(pEntry);
      T value = pEntry->value;
      EntryFree(pEntry);
      return value;
   }
   //------------------------------------------------------------
   // <T>��������ɾ�����ݡ�</T>
   void Remove(T value){
      if(_count > 0){
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            SEntry* pNext = pEntry->nextPtr;
            if(pEntry->value == value){
               // �Ƴ��ڵ�
               EntryRemove(pEntry);
               // �ͷŽڵ�
               EntryFree(pEntry);
            }
            pEntry = pNext;
         }
      }
   }
   //------------------------------------------------------------
   // <T>ʹ���������Լ��϶����������</T>
   void Sort(HComparer hComparer){
      MO_ASSERT(hComparer);
      if((_count > 1) && _pFirst && _pLast) {
         RList<SEntry, T>::Sort(_pFirst, _pLast, hComparer);
      }
   }
   //------------------------------------------------------------
   // <T>����������ݡ�</T>
   void Clear(){
      if(_count > 0){
         // ���ýڵ�
         _pLast->nextPtr = _pUnused;
         _pUnused = _pFirst;
      }
      // ��������
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
   }
   //------------------------------------------------------------
   // <T>�ͷŴ���</T>
   void Release(){
      // �����нڵ�����Ϊδʹ��
      if(_count > 0){
         _pLast->nextPtr = _pUnused;
         _pUnused = _pFirst;
      }
      // ɾ�����нڵ�
      SEntry* pFind = _pUnused;
      while(NULL != pFind){
         SEntry* pNext = pFind->nextPtr;
         EntryRelease(pFind);
         pFind = pNext;
      }
      // ��������
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      MO_CLEAR(_pUnused);
   }
};

//============================================================
// <T>�䳤ջ��д����</T>
//
// @tool
//============================================================
template <typename T>
class TList : public MList<T>{
public:
   typedef SListEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   TList(){
   }
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   TList(const TList<T>& list){
      Append(&list);
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   MO_ABSTRACT ~TList(){
      this->Release();
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      SEntry* pEntry = MO_TYPE_ALLOC(SEntry);
      MO_ASSERT(pEntry);
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ���ڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      MO_FREE(pEntry);
   }
public:
   //------------------------------------------------------------
   // <T>׷��һ��������ǰ�����С�</T>
   MO_INLINE void operator=(const MList<T>& list){
      Assign(&list);
   }
};

//============================================================
// <T>�䳤�Ѷ�д����</T>
//
// @tool
//============================================================
template <typename T>
class FList :
      public FObject,
      public MList<T>{
public:
   typedef SListEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   FList(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   MO_ABSTRACT ~FList(){
      this->Release();
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      SEntry* pEntry = MO_TYPE_ALLOC(SEntry);
      MO_ASSERT(pEntry);
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ���ڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      MO_FREE(pEntry);
   }
public:
   //------------------------------------------------------------
   // <T>׷��һ��������ǰ�����С�</T>
   MO_INLINE void operator=(const MList<T>& list){
      this->Assign(list.IteratorC());
   }
};

//============================================================
// <T>�䳤�Ѷ�д����</T>
//
// @tool
//============================================================
template <typename T>
class FFreeList :
      public FFree,
      public MList<T>{
public:
   typedef SListEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   FFreeList(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   MO_ABSTRACT ~FFreeList(){
      this->Release();
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      SEntry* pEntry = MO_MEM_CREATE(SEntry);
      MO_ASSERT(pEntry);
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ���ڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      MO_MEM_DELETE(pEntry);
   }
public:
   //------------------------------------------------------------
   // <T>׷��һ��������ǰ�����С�</T>
   MO_INLINE void operator=(const MList<T>& list){
      this->Assign(list.IteratorC());
   }
};

//============================================================
// <T>������д����</T>
//
// @template
// @type T �ڵ�����
// @param S ���ݳ���
//============================================================
template<typename T, TInt S>
class TFixList : public MList<T>{
public:
   typedef SListEntry<T> SEntry;
protected:
   TInt _alloc;
   SEntry _entries[S];
public:
   //------------------------------------------------------------
   // <T>���춨����д����</T>
   TFixList(){
      _alloc = 0;
   }
   //------------------------------------------------------------
   // <T>���춨����д����</T>
   TFixList(const MList<T>& list){
      _alloc = 0;
      this->Assign(&list);
   }
   //------------------------------------------------------------
   // <T>����������д����</T>
   MO_ABSTRACT ~TFixList(){
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      MO_ASSERT(_alloc < S);
      return &_entries[_alloc++];
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ���ڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
   }
public:
   //------------------------------------------------------------
   // <T>׷��һ��������ǰ�����С�</T>
   MO_INLINE void operator=(const MList<T>& list){
      this->Assign(&list);
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_LIST_H__
