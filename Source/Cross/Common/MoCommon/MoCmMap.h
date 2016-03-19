#ifndef __MO_CM_MAP_H__
#define __MO_CM_MAP_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ϣֵ�ļ��㡣</T>
//
// @struct
//============================================================
class RHashCode{
public:
   friend inline THashCode MakeHashCode(TInt8 value){
      return value;
   }
   friend inline THashCode MakeHashCode(TInt16 value){
      return value;
   }
   friend inline THashCode MakeHashCode(TInt32 value){
      return value;
   }
   friend inline THashCode MakeHashCode(TInt64 value){
      return value;
   }
   friend inline THashCode MakeHashCode(TUint8 value){
      return value;
   }
   friend inline THashCode MakeHashCode(TUint16 value){
      return value;
   }
   friend inline THashCode MakeHashCode(TUint32 value){
      return value;
   }
   friend inline THashCode MakeHashCode(TUint64 value){
      return value;
   }
};

//============================================================
// <T>��ϣ��ڵ�</T>
//
// @struct
//============================================================
template <typename N, typename V>
struct SMapEntry {
   SMapEntry* linkPtr;
   SMapEntry* priorPtr;
   SMapEntry* nextPtr;
   THashCode hash;
   N name;
   V value;
};

//============================================================
// <T>ֻ����������</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TMapIteratorC{
public:
   typedef SMapEntry<N, V> SEntry;
protected:
   SEntry* _pStart;
   SEntry* _pEntry;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TMapIteratorC(){
      InnerInitialize((SEntry*)NULL);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TMapIteratorC(const TMapIteratorC& iterator){
      InnerInitialize(iterator._pStart);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TMapIteratorC(SEntry* pEntry){
      InnerInitialize(pEntry);
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
   MO_INLINE const V* operator->() const{
      MO_ASSERT(this->_pEntry);
      return &(this->_pEntry->value);
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
   // <T>�ж������Ƿ���ͬ��</T>
   MO_INLINE TBool IsName(N name) const{
      MO_ASSERT(this->_pEntry);
      return (name == this->_pEntry->name);
   }
   //------------------------------------------------------------
   // <T>�ж������Ƿ���ͬ��</T>
   MO_INLINE TBool IsValue(V value) const{
      MO_ASSERT(this->_pEntry);
      return (value == this->_pEntry->value);
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ơ�</T>
   MO_INLINE N Name() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->name;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE V Value() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->value;
   }
};

//============================================================
// <T>��д��������</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TMapIterator : public TMapIteratorC<N, V>{
public:
   typedef SMapEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // <T>�����д��������</T>
   TMapIterator(){
   }
   //------------------------------------------------------------
   // <T>�����д��������</T>
   TMapIterator(const TMapIteratorC<N, V>& iterator) :
         TMapIteratorC<N, V>(iterator){
   }
   //------------------------------------------------------------
   // <T>�����д��������</T>
   TMapIterator(SEntry* pEntry) :
         TMapIteratorC<N, V>(pEntry){
   }
public:
   //------------------------------------------------------------
   // <T>���õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE void SetValue(V value){
      MO_ASSERT(this->_pEntry);
      this->_pEntry->value = value;
   }
};

//============================================================
// <T>ֻ����ϣ�����</T>
//
// @manager
// @history 100427 MAOCY
//============================================================
template <typename N, typename V>
class MMap{
public:
   typedef SMapEntry<N, V> SEntry;
   typedef TMapIteratorC<N, V> TIteratorC;
   typedef TMapIterator<N, V>  TIterator;
protected:
   TInt _count;
   SEntry* _pFirst;
   SEntry* _pLast;
   SEntry* _pUnused;
   TInt _entryCount;
   SEntry** _ppEntries;
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MMap(){
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      MO_CLEAR(_pUnused);
      _entryCount = 0;
      MO_CLEAR(_ppEntries);
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
   // <T>�жϵ�ǰ��ϣ���ָ����ϣ�����������������Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const MMap<N, V>& map) const{
      return Equals(&map);
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ��ϣ���ָ����ϣ�����������������Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const MMap<N, V>& map) const{
      return !Equals(&map);
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ��������ݡ�</T>
   MO_INLINE V operator[](N name){
      SEntry* pEntry = EntryFind(name);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
protected:
   //------------------------------------------------------------
   // <T>����ָ�����Ƶ�����λ�á�</T>
   MO_INLINE SEntry* EntryFind(N name) const{
      // ���ݴ���ʱ
      if(_count > 0){
         THashCode hash = MakeHashCode(name);
         // �������Ƶ�����λ��
         SEntry* pEntry = _ppEntries[hash % _entryCount];
         while(NULL != pEntry){
            if(pEntry->hash == hash){
               if(name == pEntry->name){
                  return pEntry;
               }
            }
            pEntry = pEntry->nextPtr;
         }
      }
      // δ�ҵ�ʱ���ؽ��
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����ָ�����Ƶ�����λ�á�</T>
   MO_INLINE SEntry* EntryFindValue(V value) const{
      // ���ݴ���ʱ
      if(_count > 0){
         TInt n = 0;
         while(++n < _entryCount){
            SEntry* pEntry = _ppEntries[n];
            while(NULL != pEntry){
               if(pEntry->value == value){
                  return pEntry;
               }
               pEntry = pEntry->nextPtr;
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
      TInt n = -1;
      while(++n < _entryCount){
         _ppEntries[n] = NULL;
      }
      // �������
      _count = 0;
      _pFirst = NULL;
      _pLast = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ��ϣ���϶����Ƿ�Ϊ�ա�</T>
   TBool IsEmpty() const{
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>������ݸ�����</T>
   TInt Count() const{
      return _count;
   }
   //------------------------------------------------------------
   // <T>�ж�ָ�������Ƿ���ڡ�</T>
   EBoolean Contains(N name) const{
      return (NULL != EntryFind(name));
   }
   //------------------------------------------------------------
   // <T>�ж�ָ�������Ƿ���ڡ�</T>
   EBoolean ContainsValue(V value) const{
      return (NULL != EntryFindValue(value));
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ��ϣ���ָ����ϣ���ϱ��Ƿ���ȡ�</T>
   TBool Equals(const MMap<N, V>* pMap) const{
      MO_ASSERT(pMap);
      // �Ƚ�����
      if(_count != pMap->Count()){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      SEntry* pEntry = _pFirst;
      TIteratorC iterator = pMap->IteratorC();
      while(iterator.Next()){
         N& name = iterator.Name();
         SEntry* pEntry = EntryFind(name);
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
      return (NULL != _pFirst) ? _pFirst->value : NULL;
   }
   //------------------------------------------------------------
   // <T>���βλ�õ����ݡ�</T>
   V Last() const{
      return (NULL != _pLast) ? _pLast->value : NULL;
   }
   //------------------------------------------------------------
   // <T>���ֻ����������</T>
   TIteratorC IteratorC(){
      return TIteratorC(_pFirst);
   }
   //------------------------------------------------------------
   // <T>��ý�βֻ����������</T>
   TIteratorC LastIteratorC(){
      return TIteratorC(_pLast);
   }
public:
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   V Get(N name) const{
      SEntry* pEntry = EntryFind(name);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   V Find(N name) const{
      SEntry* pEntry = EntryFind(name);
      return (NULL != pEntry) ? pEntry->value : (V)NULL;
   }
   //------------------------------------------------------------
   // <T>���ָ�����ݵ����ơ�</T>
   N Search(V value) const{
      SEntry* pEntry = EntryFindValue(value);
      return (NULL != pEntry) ? pEntry->name : (N)NULL;
   }
   //------------------------------------------------------------
   // <T>���ƶ����ⲿ���顣</T>
   TInt CopyTo(V* pBuffer, TInt capacity) const{
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
protected:
   //------------------------------------------------------------
   // <T>�ڲ��ͷš�</T>
   inline void InnerRelease(){
      // �ͷŽڵ㼯��
      if(_count > 0){
         // �����нڵ�����Ϊδʹ��
         _pLast->nextPtr = _pUnused;
         _pUnused = _pFirst;
      }
      // ɾ�����нڵ�
      SEntry* pFind = _pUnused;
      while(NULL != pFind){
         SEntry* pNext = pFind;
         EntryRelease(pFind);
         pFind = pNext;
      }
      // ɾ���ڵ�����
      EntryFlatFree(_ppEntries);
   }
protected:
   //------------------------------------------------------------
   // <T>���䵱ǰ����Ĺ�ϣֵ���顣</T>
   inline void EntriesResize(SEntry** ppEntries, TInt size){
      // ѭ��ȡ���ɵĽڵ��б����ݣ��Ƶ��µĽڵ��б���
      TInt n = -1;
      while(++n < _entryCount){
         SEntry* pEntry = _ppEntries[n];
         while(NULL != pEntry){
            // ���浱ǰ�ڵ����һ���ڵ�ָ��
            SEntry* pLink = pEntry->linkPtr;
            // ����ǰ�ڵ�洢���½��Ľڵ��б���ȥ
            TInt index = pEntry->hash % size;
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
      return TIterator(_pFirst);
   }
   //------------------------------------------------------------
   // <T>��ý�β��д��������</T>
   TIterator LastIterator(){
      return TIterator(_pLast);
   }
public:
   //------------------------------------------------------------
   // <T>����Դ��ϣ���ڵ�ȫ�����ݡ�</T>
   void Assign(const MMap<N, V>* pMap){
      MO_ASSERT(pMap);
      Clear();
      Append(pMap);
   }
   //------------------------------------------------------------
   // <T>׷��Դ��ϣ���ڵ�ȫ�����ݡ�</T>
   void Append(const MMap<N, V>* pMap){
      MO_ASSERT(pMap);
      TIteratorC iterator = pMap->IteratorC();
      while(iterator.Next()){
         Set(iterator.Name(), iterator.Value());
      }
   }
   //------------------------------------------------------------
   // <T>���������������ݡ�</T>
   void Set(N name, V value){
      THashCode hash = MakeHashCode(name);
      TInt index = hash % _entryCount;
      // �������ݳ��ֵ�λ��
      SEntry* pEntry = _ppEntries[index];
      while(NULL != pEntry) {
         if(pEntry->hash == hash){
            if(name->Equals(pEntry->name)){
               pEntry->value = value;
               return;
            }
         }
         pEntry = pEntry->linkPtr;
      }
      // ������Ʋ����ڣ�Ϊ�½��ڵ����ڴ�
      pEntry = EntryAlloc();
      // ��С���ܸı䣬���¼�������λ��
      index = hash % _entryCount;
      pEntry->linkPtr = _ppEntries[index];
      pEntry->hash = hash;
      pEntry->name = name;
      pEntry->value = value;
      _ppEntries[index] = pEntry;
      // ׷�ӵ�����β��
      EntryPush(pEntry);
   }
   //------------------------------------------------------------
   // <T>�Ƴ�ָ�����Ƶ����ݡ�</T>
   V Remove(N name){
      THashCode hash = MakeHashCode(name);
      TInt index = hash % _entryCount;
      // �������ݳ��ֵ�λ��
      V value = NULL;
      SEntry* pPrior = _ppEntries[index];
      SEntry* pEntry = pPrior;
      while(NULL != pEntry){
         if(pEntry->hash == hash){
            if(name->Equals(pEntry->name)){
               value = pEntry->value;
               if(pEntry == pPrior){
                  // ��ǰ�����ǵ�һ������ʱ
                  _ppEntries[index] = pEntry->linkPtr;
               }else{
                  // ��ǰ�����ǵ�һ������ʱ
                  pPrior->linkPtr = pEntry->linkPtr;
               }
               // ɾ����ǰ�ڵ�
               EntryRemove(pEntry);
               // �ͷŵ�ǰ�ڵ�
               EntryFree(pEntry);
               break;
            }
         }
         pPrior = pEntry;
         pEntry = pEntry->linkPtr;
      }
      return value;
   }
   //------------------------------------------------------------
   // <T>��յ�ǰ��ϣ��ȫ�����ݡ�</T>
   void Clear(){
      EntryClear();
   }
};

//============================================================
// <T>�䳤ջ��ϣ��</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TMap : public MMap<N, V>{
public:
   typedef SMapEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // <T>������ϣ�����</T>
   TMap(){
   }
   //------------------------------------------------------------
   // <T>������ϣ�����</T>
   TMap(TInt capacity){
      this->EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>������ϣ�����</T>
   TMap(const MMap<N, V>& map){
      this->EnsureSize(map.Count());
      this->Append(&map);
   }
   //------------------------------------------------------------
   // <T>������ϣ�����</T>
   MO_ABSTRACT ~TMap(){
      this->InnerRelease();
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ��δʹ�õĽڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      EnsureSize(this->_count + 1);
      return MO_TYPE_CREATE(SEntry);
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ��ָ���Ľڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      MO_FREE(pEntry);
   }
   //------------------------------------------------------------
   // <T>�ռ��ڵ��б��ڴ档</T>
   MO_OVERRIDE SEntry** EntryFlatCreate(TInt size){
      SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
      RTypes<SEntry*>::Clear(ppEntries, size);
      return ppEntries;
   }
   //------------------------------------------------------------
   // <T>�ͷŽڵ��б��ڴ档</T>
   MO_OVERRIDE void EntryFlatRelease(SEntry** pEntries){
      MO_ASSERT(pEntries);
      MO_FREE(pEntries);
   }
public:
   //------------------------------------------------------------
   // <T>�������ݵ������ڲ���</T>
   MO_INLINE void operator=(const MMap<N, V>& map){
      this->Assign(&map);
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
   MO_OVERRIDE void EnsureSize(TInt size){
      if(NULL == this->_ppEntries) {
         this->_entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
         // ��һ���½�ʱ�����ɹ�ϣ��
         this->_ppEntries = MO_TYPES_ALLOC(SEntry*, this->_entryCount);
      } else if (size > (this->_entryCount << 3)) {
         // �����ڴ�ʱ����
         size = this->_entryCount + (MO_LIB_MAX(this->_entryCount, size) >> 1);
         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
         SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
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
// <T>�䳤�ѹ�ϣ��</T>
//
// @class
//============================================================
template <typename N, typename V>
class FMap : public MMap<N, V>{
public:
   typedef SMapEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // <T>�����ϣ�����</T>
   FMap(){
   }
   //------------------------------------------------------------
   // <T>�����ϣ�����</T>
   FMap(TInt capacity){
      this->EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�����ϣ�����</T>
   FMap(const MMap<N, V>& map){
      this->EnsureSize(map.Count());
      this->Append(&map);
   }
   //------------------------------------------------------------
   // <T>������ϣ�����</T>
   MO_ABSTRACT ~FMap(){
      this->InnerRelease();
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ��δʹ�õĽڵ㡣</T>
   MO_INLINE SEntry* EntryCreate(){
      EnsureSize(this->_count + 1);
      return MO_TYPE_ALLOC(SEntry);
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ��ָ���Ľڵ㡣</T>
   MO_INLINE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      MO_FREE(pEntry);
   }
   //------------------------------------------------------------
   // <T>�ռ��ڵ��б��ڴ档</T>
   MO_OVERRIDE SEntry** EntryFlatCreate(TInt size){
      SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
      RTypes<SEntry*>::Clear(ppEntries, size);
      return ppEntries;
   }
   //------------------------------------------------------------
   // <T>�ͷŽڵ��б��ڴ档</T>
   MO_OVERRIDE void EntryFlatRelease(SEntry** pEntries){
      MO_ASSERT(pEntries);
      MO_FREE(pEntries);
   }
public:
   //------------------------------------------------------------
   // <T>�������ݵ������ڲ���</T>
   void operator=(const MMap<N, V>& map){
      this->Assign(&map);
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
   void EnsureSize(TInt size){
      if(NULL == this->_ppEntries) {
         this->_entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
         // ��һ���½�ʱ�����ɹ�ϣ��
         this->_ppEntries = MO_TYPES_ALLOC(SEntry*, this->_entryCount);
      } else if (size > (this->_entryCount << 3)) {
         // �����ڴ�ʱ����
         size = this->_entryCount + (MO_LIB_MAX(this->_entryCount, size) >> 1);
         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
         SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
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
// <T>��ϣ�����</T>
//
// @template
// @type N ��������
// @type V ��������
// @param S ���ݳ���
//============================================================
template<typename N, typename V, TInt S>
class TFixMap : public MMap<N, V>{
public:
   typedef SMapEntry<N, V> SEntry;
protected:
   TInt _alloc;
   SEntry _entries[S];
public:
   //------------------------------------------------------------
   // ��ʼ���̶����ȵĹ�ϣ��
   TFixMap(){
      this->InnerInitialize(S);
   }
   //------------------------------------------------------------
   // ��ʼ���̶����ȵĹ�ϣ��
   TFixMap(const MMap<N, V>& map){
      this->InnerInitialize(map.Count());
      Append(&map);
   }
public:
   //------------------------------------------------------------
   // <T>��ʼ����</T>
   void Initialize(){
      this->InnerInitialize(S);
   }
protected:
   //------------------------------------------------------------
   // �ڲ���ʼ��
   MO_OVERRIDE void InnerInitialize(TInt size){
      MMap<N, V>::InnerInitialize(size);
      this->_alloc = 0;
   }
   //------------------------------------------------------------
   // <T>�½�һ��δʹ�õĽڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      MO_ASSERT(this->_alloc < S);
      return &this->_entries[this->_alloc++];
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ��ָ���Ľڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
   }
   //------------------------------------------------------------
   // <T>�ռ��ڵ��б��ڴ档</T>
   MO_INLINE SEntry** EntryFlatCreate(TInt size){
      MO_ASSERT(size <= S);
      return this->_pEntries;
   }
   //------------------------------------------------------------
   // <T>�ͷŽڵ��б��ڴ档</T>
   MO_INLINE void EntryFlatRelease(SEntry** pEntries){
   }
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   MO_OVERRIDE void EnsureSize(TInt size){
      MO_ASSERT(size <= S);
      if(NULL == this->_pMemory){
         this->_entryCount = S;
         this->_ppEntries = _entries;
      }
   }
public:
   //------------------------------------------------------------
   // <T>����һ����ϣ����ǰ��ϣ���С�</T>
   MO_INLINE void operator=(const MMap<N, V>& map){
      Assign(&map);
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_MAP_H__
