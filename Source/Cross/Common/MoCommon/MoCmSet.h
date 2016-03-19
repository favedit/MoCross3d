#ifndef __MO_CM_SET_H__
#define __MO_CM_SET_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

#ifndef __MO_CM_ENTRY_H__
#include "MoCmEntry.h"
#endif // __MO_CM_ENTRY_H__

MO_NAMESPACE_BEGIN

#define MO_COMPSET_THRESHOLD 8

//============================================================
// <T>���Ͻڵ�Ķ��塣</T>
//
// @struct
//============================================================
template <typename N, typename V>
struct SSetEntry{
public:
   // @attribute ����ָ��
   SSetEntry* linkPtr;
   // @attribute ǰһ��ָ��
   SSetEntry* priorPtr;
   // @attribute ��һ��ָ��
   SSetEntry* nextPtr;
   // @attribute ����
   N code;
   // @attribute ����
   V value;
};

//============================================================
// <T>�ڴ������ࡣ</T>
//
// @tool
// @history 100318 MAOCY ����
//============================================================
template <typename E, typename T>
class RSet{
public:
   typedef TInt (*HComparer) (const T&, const T&);
private:
   //------------------------------------------------------------
   // <T>����˫�������ͷβָ�롣</T>
   static void AdjustHeadTail(E*& h, E*& t, E* p1, E* p2) {
      if(p1 == h){
         h = p2;
      }else if(p2 == h){
         h = p1;
      }if(p1 == t){
         t = p2;
      }else if(p2 == t){
         t = p1;
      }
   }
   //------------------------------------------------------------
   // <T>Set������ָ�뽻����</T>
   static void ItemSwap(E*& h, E*& t, E* p1, E* p2) {
      E *tmp;
      if(p1 && p2 && p1 != p2) {
         if(p1->pNext != p2 && p1->pPrior != p2) {
            AdjustHeadTail(h, t, p1, p2);
            MO_SORT_SWAP(tmp, p1->pNext, p2->pNext);
            if(p1->pNext){
               p1->pNext->pPrior = p1;
            }
            if(p2->pNext){
               p2->pNext->pPrior = p2;
            }
            MO_SORT_SWAP(tmp, p1->pPrior, p2->pPrior);
            if(p1->pPrior){
               p1->pPrior->pNext = p1;
            }
            if(p2->pPrior){
               p2->pPrior->pNext = p2;
            }
         } else if(p1->pNext == p2) {
            AdjustHeadTail(h, t, p1, p2);
            p1->pNext = p2->pNext;
            if(p1->pNext){
               p1->pNext->pPrior = p1;
            }
            p2->pPrior = p1->pPrior;
            if(p2->pPrior){
               p2->pPrior->pNext = p2;
            }
            p1->pPrior = p2;
            p2->pNext = p1;
         } else {
            MO_SORT_SWAP(tmp, p1, p2);
            ItemSwap(h, t, p1, p2);
         }
      }
   }
public:
   //------------------------------------------------------------
   // <T>����Ԫ�رȽ��ٵ�˫������Ĳ�������</T>
   static void InsertSort(E *&pHead, E *&pTail, HComparer hComparer) {
      if(pHead != pTail) {
         for(E *p = pHead->pNext; p != pTail->pNext; p = p->pNext) {
            for(E *pp = p; pp != pHead; pp = pp->pPrior) {
               if(hComparer(pp->code, pp->pPrior->code) < 0) {
                   ItemSwap(pHead, pTail, pp, pp->pPrior);
                 } else {
                     break;
                 }
            }
         }
      }
   }
   //------------------------------------------------------------
   // <T>����Ԫ�رȽ϶��˫������Ŀ�������</T>
   static void QuickSort(E *&pHead, E *&pTail, HComparer hComparer){
      if(pHead != pTail) {
         T data = pHead->code;
         E *last = pHead;
         E *tmp;
         for(E *p = pHead->pNext; p != pTail->pNext; p = p->pNext) {
            if(hComparer(p->code, data) < 0) {
               last = last->pNext;
               ItemSwap(pHead, pTail, last, p);
               MO_SORT_SWAP(tmp, last, p);
            }
         }
         tmp = pHead;
         ItemSwap(pHead, pTail, tmp, last);
         last = tmp;
         if(last != pHead){
            last = last->pPrior;
            QuickSort(pHead, last, hComparer);
         }
         if(tmp != pTail){
            tmp = tmp->pNext;
            QuickSort(tmp, pTail, hComparer);
         }
      }
   }
};

//============================================================
// <T>ֻ����������</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TSetIteratorC{
public:
   typedef SSetEntry<N, V> SEntry;
protected:
   SEntry* _pStart;
   SEntry* _pEntry;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TSetIteratorC(){
      this->InnerInitialize((SEntry*)NULL);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TSetIteratorC(const TSetIteratorC& iterator){
      this->InnerInitialize(iterator._pStart);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TSetIteratorC(SEntry* pEntry){
      this->InnerInitialize(pEntry);
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(SEntry* pEntry){
      _pStart = pEntry;
      _pEntry = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const V& operator *() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const V operator->() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->value;
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
public:
   //------------------------------------------------------------
   // <T>�жϴ����Ƿ���ͬ��</T>
   MO_INLINE TBool IsCode(N code) const{
      MO_ASSERT(this->_pEntry);
      return (code == this->_pEntry->code);
   }
   //------------------------------------------------------------
   // <T>�ж������Ƿ���ͬ��</T>
   MO_INLINE TBool IsValue(V value) const{
      MO_ASSERT(this->_pEntry);
      return (value == this->_pEntry->value);
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ơ�</T>
   MO_INLINE N Code() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->code;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE V Value() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->value;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _pEntry = NULL;
   }
};

//============================================================
// <T>��д��������</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TSetIterator : public TSetIteratorC<N, V>{
private:
   typedef SSetEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // <T>�����д��������</T>
   TSetIterator(){
   }
   //------------------------------------------------------------
   // <T>�����д��������</T>
   TSetIterator(const TSetIteratorC<N, V>& iterator) :
         TSetIteratorC<N, V>(iterator){
   }
   //------------------------------------------------------------
   // <T>�����д��������</T>
   TSetIterator(SEntry* pEntry) :
         TSetIteratorC<N, V>(pEntry){
   }
public:
   //------------------------------------------------------------
   // <T>���õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE void SetValue(V value) const{
      MO_ASSERT(this->_pEntry);
      this->_pEntry->value = value;
   }
};

//============================================================
// <T>��ϣ����</T>
//
// @manager
// @typename N ��������
// @typename V ��������
// @history 100427 MAOCY
//============================================================
template <typename N, typename V>
class MSet{
public:
   typedef TInt (*HComparer) (const N&, const N&);
   typedef SSetEntry<N, V>     SEntry;
   typedef TSetIteratorC<N, V> TIteratorC;
   typedef TSetIterator<N, V>  TIterator;
protected:
   TInt _count;
   SEntry* _pFirst;
   SEntry* _pLast;
   SEntry* _pUnused;
   TInt _entryCount;
   SEntry** _ppEntries;
public:
   //------------------------------------------------------------
   // <T>�����ϣ���ϡ�</T>
   MSet(){
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      MO_CLEAR(_pUnused);
      _entryCount = 0;
      MO_CLEAR(_ppEntries);
   }
   //------------------------------------------------------------
   // <T>������ϣ���ϡ�</T>
   MO_ABSTRACT ~MSet(){
   }
protected:
   MO_VIRTUAL SEntry* EntryCreate() = 0;
   MO_VIRTUAL void EntryRelease(SEntry* pEntry) = 0;
   MO_VIRTUAL void EnsureSize(TInt size) = 0;
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
   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ�������������������Ƿ���ȡ�</T>
   TBool operator==(const MSet<N, V>& set) const{
      return Equals(&set);
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ�������������������Ƿ���ȡ�</T>
   TBool operator!=(const MSet<N, V>& set) const{
      return !Equals(&set);
   }
   //------------------------------------------------------------
   // <T>���ָ��������������ݡ�</T>
   V operator[](N code){
      SEntry* pEntry = EntryFind(code);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
   //------------------------------------------------------------
   // ׷��һ��������ǰ�����С�
   void operator+=(const MSet<N, V>& set){
      Append(&set);
   }
protected:
   //------------------------------------------------------------
   // <T>���ɴ����������</T>
   MO_INLINE TInt MakeIndex(N code) const{
      TInt index = (TInt)code;
      index %= this->_entryCount;
      if(index < 0){
         index = -index;;
      }
      return index;
   }
   //------------------------------------------------------------
   // <T>����ָ�����Ƶ�����λ�á�</T>
   MO_INLINE SEntry* EntryFind(N code) const{
      // ���ݴ���ʱ
      if(this->_count > 0){
         // �������Ƶ�����λ��
         TInt index = MakeIndex(code);
         SEntry* pEntry = _ppEntries[index];
         while(NULL != pEntry){
            if(pEntry->code == code){
               return pEntry;
            }
            pEntry = pEntry->linkPtr;
         }
      }
      // δ�ҵ�ʱ���ؽ��
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����ָ�����Ƶ�����λ�á�</T>
   MO_INLINE SEntry* EntryFindValue(V value) const{
      // ���ݴ���ʱ
      if(this->_count > 0){
         TInt n = 0;
         while(++n < _entryCount){
            SEntry* pEntry = _ppEntries[n];
            while(NULL != pEntry){
               if(pEntry->value == value){
                  return pEntry;
               }
               pEntry = pEntry->linkPtr;
            }
         }
      }
      // δ�ҵ�ʱ���ؽ��
      return NULL;
   }
   //------------------------------------------------------------
   // �������������ʹ���еĽڵ㣬����δʹ��������ѭ��ʹ��
   MO_INLINE void EntryClear(){
      // ������
      for(TInt n=0; n<_entryCount; n++){
         _ppEntries[n] = NULL;
      }
      // �������
      // �������
      _count = 0;
      _pFirst = NULL;
      _pLast = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ��ϣ���϶����Ƿ�Ϊ�ա�</T>
   TBool IsEmpty() const{
      return (0 == this->_count);
   }
   //------------------------------------------------------------
   // <T>������ݸ�����</T>
   TInt Count() const{
      return this->_count;
   }
   //------------------------------------------------------------
   // <T>�ж�ָ�������Ƿ���ڡ�</T>
   TBool Contains(N code) const{
      return (NULL != EntryFind(code));
   }
   //------------------------------------------------------------
   // <T>�ж�ָ�������Ƿ���ڡ�</T>
   TBool ContainsValue(V value) const{
      return (NULL != EntryFindValue(value));
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ���������Ƿ���ȡ�</T>
   TBool Equals(const MSet<N, V>* pSet) const{
      MO_ASSERT(pSet);
      // �Ƚ�����
      if(this->_count != pSet->_count){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      TIteratorC iterator = pSet->IteratorC();
      while(iterator.Next()){
         N code = iterator.Code();
         SEntry* pEntry = this->EntryFind(code);
         if(NULL == pEntry){
            return EFalse;
         }
         if(!iterator.IsValue(pEntry->value)){
            return EFalse;
         }
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�����λ�õ����ݡ�</T>
   V First() const{
      return (NULL != this->_pFirst) ? this->_pFirst->value : NULL;
   }
   //------------------------------------------------------------
   // <T>���βλ�õ����ݡ�</T>
   V Last() const{
      return (NULL != this->_pLast) ? this->_pLast->value : NULL;
   }
   //------------------------------------------------------------
   // <T>���ֻ����������</T>
   TIteratorC IteratorC(){
      return TIteratorC(this->_pFirst);
   }
   //------------------------------------------------------------
   // <T>��ý�βֻ����������</T>
   TIteratorC LastIteratorC(){
      return TIteratorC(this->_pLast);
   }
public:
   //------------------------------------------------------------
   // <T>���ָ����������ݡ�</T>
   V Get(N code) const{
      SEntry* pEntry = EntryFind(code);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
   //------------------------------------------------------------
   // <T>���ָ����������ݡ�</T>
   V Find(N code) const{
      SEntry* pEntry = EntryFind(code);
      return (NULL != pEntry) ? pEntry->value : (V)NULL;
   }
   //------------------------------------------------------------
   // <T>���ָ�����ݵĴ��롣</T>
   N Search(V value) const{
      SEntry* pEntry = EntryFindValue(value);
      return (NULL != pEntry) ? pEntry->code : (N)NULL;
   }
   //------------------------------------------------------------
   // <T>���ƶ����ⲿ���顣</T>
   TInt CopyTo(V* pBuffer, TInt capacity) const{
      TInt count = MO_LIB_MIN(this->_count, capacity);
      if(count > 0){
         TInt n = 0;
         SEntry* pEntry = this->_pFirst;
         while(NULL != pEntry){
            pBuffer[n++] = pEntry->value;
            pEntry = pEntry->nextPtr;
         }
      }
      return count;
   }
protected:
   //------------------------------------------------------------
   // <T>���䵱ǰ����Ĺ�ϣֵ���顣</T>
   MO_INLINE void EntriesResize(SEntry** ppEntries, TInt size){
      // ѭ��ȡ���ɵĽڵ��б����ݣ��Ƶ��µĽڵ��б���
      TInt n = -1;
      while(++n < this->_entryCount){
         SEntry* pEntry = this->_ppEntries[n];
         while(NULL != pEntry){
            // ���浱ǰ�ڵ����һ���ڵ�ָ��
            SEntry* pLink = pEntry->linkPtr;
            // ����ǰ�ڵ�洢���½��Ľڵ��б���ȥ
            TInt index = (TInt)pEntry->code;
            index %= size;
            if(index < 0){
               index = -index;
            }
            pEntry->linkPtr = ppEntries[index];
            ppEntries[index] = pEntry;
            // ��ñ������һ���ڵ�ָ��
            pEntry = pLink;
         }
      }
   }
public:
   //------------------------------------------------------------
   // <T>��ÿ�д��������</T>
   TIterator Iterator(){
      return TIterator(this->_pFirst);
   }
   //------------------------------------------------------------
   // <T>��ý�β��д��������</T>
   TIterator LastIterator(){
      return TIterator(this->_pLast);
   }
public:
   //------------------------------------------------------------
   // <T>���Ƽ����ڵ�ȫ�����ݡ�</T>
   void Assign(const MSet<N, V>* pSet){
      MO_ASSERT(pSet);
      Clear();
      Append(pSet);
   }
   //------------------------------------------------------------
   // <T>׷�Ӽ����ڵ�ȫ�����ݡ�</T>
   void Append(const MSet<N, V>* pSet){
      MO_ASSERT(pSet);
      TIteratorC iterator = pSet->IteratorC();
      while(iterator.Next()){
         Set(iterator.Code(), iterator.Value());
      }
   }
   //------------------------------------------------------------
   // <T>���������������ݡ�</T>
   void Set(N code, V value){
      // �������ݳ��ֵ�λ��
      TInt index = this->MakeIndex(code);
      SEntry* pEntry = this->_ppEntries[index];
      while(NULL != pEntry) {
         if(pEntry->code == code){
            pEntry->value = value;
            return;
         }
         pEntry = pEntry->linkPtr;
      }
      // ������Ʋ����ڣ�Ϊ�½��ڵ����ڴ�
      pEntry = EntryAlloc();
      // ��С���ܸı䣬���¼�������λ��
      index = this->MakeIndex(code);
      pEntry->linkPtr = this->_ppEntries[index];
      pEntry->code = code;
      pEntry->value = value;
      this->_ppEntries[index] = pEntry;
      // ׷�ӵ�����β��
      this->EntryPush(pEntry);
   }
   //------------------------------------------------------------
   // <T>�Ƴ�ָ�����Ƶ����ݡ�</T>
   V Remove(N code){
      TInt index = this->MakeIndex(code);
      // �������ݳ��ֵ�λ��
      V value;
      memset(&value, 0, sizeof(V));
      SEntry* pPrior = this->_ppEntries[index];
      SEntry* pEntry = pPrior;
      while(NULL != pEntry){
         if(pEntry->code == code){
            value = pEntry->value;
            if(pEntry == pPrior){
               // ��ǰ�����ǵ�һ������ʱ
               this->_ppEntries[index] = pEntry->linkPtr;
            }else{
               // ��ǰ�����ǵ�һ������ʱ
               pPrior->linkPtr = pEntry->linkPtr;
            }
            // ɾ����ǰ�ڵ�
            this->EntryRemove(pEntry);
            // �ͷŵ�ǰ�ڵ�
            this->EntryFree(pEntry);
            break;
         }
         pPrior = pEntry;
         pEntry = pEntry->linkPtr;
      }
      return value;
   }
   //------------------------------------------------------------
   // <T>ʹ���������Լ��϶����������</T>
   void Sort(HComparer hComparer){
      MO_ASSERT(hComparer);
      if(this->_pFirst && this->_pLast && this->_count > 1) {
         if(MO_COMPLIST_THRESHOLD > this->_count){
            RSet<SEntry, N>::InsertSort(this->_pFirst, this->_pLast, hComparer);
         } else{
            RSet<SEntry, N>::QuickSort(this->_pFirst, this->_pLast, hComparer);
         }
      }
   }
   //------------------------------------------------------------
   // <T>��յ�ǰ��ϣ����ȫ�����ݡ�</T>
   void Clear(){
      if(this->_count > 0){
         this->_pLast->nextPtr = this->_pUnused;
         this->_pUnused = this->_pFirst;
      }
      this->EntryClear();
   }
};

//============================================================
// <T>�䳤ջ���ϡ�</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TSet : public MSet<N, V>{
public:
   typedef SSetEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // <T>�����ϣ���϶���</T>
   TSet(){
      this->InnerInitialize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>�����ϣ���϶���</T>
   TSet(const MSet<N, V>& set){
      this->InnerInitialize(set.Count());
      this->Append(&set);
   }
   //------------------------------------------------------------
   // <T>�����ϣ���϶���</T>
   TSet(TInt capacity){
      this->InnerInitialize(capacity);
   }
   //------------------------------------------------------------
   // <T>������ϣ���϶���</T>
   MO_ABSTRACT ~TSet(){
      // �ͷŽڵ㼯��
      if(this->_count > 0){
         this->_pLast->nextPtr = this->_pUnused;
         this->_pUnused = this->_pFirst;
      }
      // ɾ�����нڵ�
      SEntry* pFind = this->_pUnused;
      while(NULL != pFind){
         SEntry* pNext = pFind->nextPtr;
         MO_FREE(pFind);
         pFind = pNext;
      }
      // ɾ���ڵ�����
      MO_FREE(this->_ppEntries);
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(TInt size){
      this->_entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
      this->_ppEntries = MO_TYPES_ALLOC(SEntry*, this->_entryCount);
      RTypes<SEntry*>::Clear(this->_ppEntries, this->_entryCount);
   }
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      EnsureSize(this->_count + 1);
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
   // <T>�������ݵ������ڲ���</T>
   MO_INLINE void operator=(const MSet<N, V>& set){
      this->Assign(&set);
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
   MO_OVERRIDE void EnsureSize(TInt size){
      if (size > (this->_entryCount << 3)) {
         // �����ڴ�ʱ����
         size = this->_entryCount + (MO_LIB_MAX(this->_entryCount, size) >> 1);
         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
         SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
         RTypes<SEntry*>::Clear(ppEntries, size);
         EntriesResize(ppEntries, size);
         // �ͷžɽڵ��ڴ�
         MO_FREE(this->_ppEntries);
         // �����µĽڵ��б�
         this->_ppEntries = ppEntries;
         this->_entryCount = size;
      }
   }
};

//============================================================
// <T>�䳤�Ѽ��ϡ�</T>
//
// @tool
//============================================================
template <typename N, typename V>
class FSet :
      public FObject,
      public MSet<N, V>{
public:
   typedef SSetEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // <T>���켯�϶���</T>
   FSet(){
      this->InnerInitialize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>���켯�϶���</T>
   FSet(TInt capacity){
      this->InnerInitialize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>���켯�϶���</T>
   FSet(const MSet<N, V>& set){
      this->InnerInitialize(set.Count());
      this->Append(&set);
   }
   //------------------------------------------------------------
   // <T>�������϶���</T>
   MO_ABSTRACT ~FSet(){
      // �ͷŽڵ㼯��
      if(this->_count > 0){
         // �����нڵ�����Ϊδʹ��
         this->_pLast->nextPtr = this->_pUnused;
         this->_pUnused = this->_pFirst;
      }
      // ɾ�����нڵ�
      SEntry* pFind = this->_pUnused;
      while(NULL != pFind){
         SEntry* pNext = pFind->nextPtr;
         MO_FREE(pFind);
         pFind = pNext;
      }
      // ɾ���ڵ�����
      MO_FREE(this->_ppEntries);
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(TInt size){
      this->_entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
      this->_ppEntries = MO_TYPES_ALLOC(SEntry*, this->_entryCount);
      RTypes<SEntry*>::Clear(this->_ppEntries, this->_entryCount);
   }
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      EnsureSize(this->_count + 1);
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
   // <T>�������ݵ������ڲ���</T>
   MO_INLINE void operator=(const MSet<N, V>& set){
      this->Assign(&set);
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
   MO_OVERRIDE void EnsureSize(TInt size){
      if (size > (this->_entryCount << 3)) {
         // �����ڴ�ʱ����
         size = this->_entryCount + (MO_LIB_MAX(this->_entryCount, size) >> 1);
         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
         SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
         RTypes<SEntry*>::Clear(ppEntries, size);
         this->EntriesResize(ppEntries, size);
         // �ͷžɽڵ��ڴ�
         MO_FREE(this->_ppEntries);
         // �����µĽڵ��б�
         this->_ppEntries = ppEntries;
         this->_entryCount = size;
      }
   }
};

//============================================================
// <T>�䳤�Ѽ��ϡ�</T>
//
// @tool
//============================================================
template <typename N, typename V>
class FFreeSet :
      public FFree,
      public MSet<N, V>{
public:
   typedef SSetEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // <T>���켯�϶���</T>
   FFreeSet(){
      this->InnerInitialize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>���켯�϶���</T>
   FFreeSet(TInt capacity){
      this->InnerInitialize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>���켯�϶���</T>
   FFreeSet(const MSet<N, V>& set){
      this->InnerInitialize(set.Count());
      this->Append(&set);
   }
   //------------------------------------------------------------
   // <T>�������϶���</T>
   MO_ABSTRACT ~FFreeSet(){
      // �ͷŽڵ�
      if(this->_count > 0){
         // �����нڵ�����Ϊδʹ��
         this->_pLast->nextPtr = this->_pUnused;
         this->_pUnused = this->_pFirst;
         // ɾ�����нڵ�
         SEntry* pFind = this->_pUnused;
         while(NULL != pFind){
            SEntry* pNext = pFind->nextPtr;
            MO_FREE(pFind);
            pFind = pNext;
         }
      }
      // �ͷŽڵ�����
      MO_FREE(this->_ppEntries);
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(TInt size){
      this->_entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
      this->_ppEntries = MO_TYPES_ALLOC(SEntry*, this->_entryCount);
      RTypes<SEntry*>::Clear(this->_ppEntries, this->_entryCount);
   }
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      this->EnsureSize(this->_count + 1);
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
   // <T>�������ݵ������ڲ���</T>
   MO_INLINE void operator=(const MSet<N, V>& set){
      this->Assign(&set);
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
   MO_OVERRIDE void EnsureSize(TInt size){
      if (size > (this->_entryCount << 3)) {
         // �����ڴ�ʱ����
         size = this->_entryCount + (MO_LIB_MAX(this->_entryCount, size) >> 1);
         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
         SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
         RTypes<SEntry*>::Clear(ppEntries, size);
         this->EntriesResize(ppEntries, size);
         // �ͷžɽڵ��ڴ�
         MO_FREE(this->_ppEntries);
         // �����µĽڵ��б�
         this->_ppEntries = ppEntries;
         this->_entryCount = size;
      }
   }
};

//============================================================
// <T>��ϣ�����</T>
//
// @template
// @type N ��������
// @type V ��������
// @param S ���ݳ���
//============================================================
template<typename N, typename V, TInt S>
class TFixSet : public MSet<N, V>{
public:
   typedef SSetEntry<N, V> SEntry;
protected:
   SEntry* _memoryEntries[S];
   TInt _alloc;
   SEntry _allocEntries[S];
public:
   //------------------------------------------------------------
   // <T>����̶����ȵĹ�ϣ��</T>
   TFixSet(){
      this->InnerInitialize();
   }
   //------------------------------------------------------------
   // <T>����̶����ȵĹ�ϣ��</T>
   TFixSet(const MSet<N, V>& set){
      this->InnerInitialize();
      this->Append(&set);
   }
   //------------------------------------------------------------
   // <T>�������̶����ȵĹ�ϣ��</T>
   MO_ABSTRACT ~TFixSet(){
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(){
      this->_entryCount = S;
      this->_ppEntries = _memoryEntries;
      this->_alloc = 0;
   }
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      MO_ASSERT(_alloc < S);
      return &_allocEntries[_alloc++];
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ���ڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
   }
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   MO_OVERRIDE void EnsureSize(TInt size){
      MO_ASSERT(size <= S);
   }
public:
   //------------------------------------------------------------
   // <T>����һ�����ϵ���ǰ�����С�</T>
   MO_INLINE void operator=(const MSet<N, V>& set){
      Assign(&set);
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_SET_H__
