#ifndef __MO_CM_DICTIONARY_H__
#define __MO_CM_DICTIONARY_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ϣ�ֵ�ڵ�</T>
//
// @struct
//============================================================
template <typename T>
struct SDictionaryEntry{
public:
   SDictionaryEntry* linkPtr;
   SDictionaryEntry* priorPtr;
   SDictionaryEntry* nextPtr;
   THashCode hash;
   FString* namePtr;
   T value;
public:
   //------------------------------------------------------------
   // <T>�����ϣ�ֵ�ڵ�</T>
   SDictionaryEntry(){
      MO_CLEAR(linkPtr);
      MO_CLEAR(priorPtr);
      MO_CLEAR(nextPtr);
      hash = 0;
      MO_CLEAR(namePtr);
   }
   //------------------------------------------------------------
   // <T>������ϣ�ֵ�ڵ�</T>
   ~SDictionaryEntry(){
      MO_DELETE(namePtr);
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ���ȡ�</T>
   MO_INLINE TBool IsName(TCharC* pName){
      if(NULL == namePtr){
         return EFalse;
      }
      return namePtr->Equals(pName);
   }
   //------------------------------------------------------------
   // <T>�жϲ����ִ�Сд�����Ƿ���ȡ�</T>
   MO_INLINE TBool IsNameIgnoreCase(TCharC* pName){
      if(NULL == namePtr){
         return EFalse;
      }
      return namePtr->EqualsIgnoreCase(pName);
   }
   //------------------------------------------------------------
   // <T>����ַ������ơ�</T>
   MO_INLINE TCharC* Name(){
      if(NULL == namePtr){
         return NULL;
      }
      return namePtr->MemoryC();
   }
   //------------------------------------------------------------
   // <T>�����ַ������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      if(NULL == namePtr){
         namePtr = MO_CREATE(FString);
      }
      namePtr->Assign(pName);
   }
public:
   //------------------------------------------------------------
   // <T>�ͷ����ݡ�</T>
   MO_INLINE void Release(){
      MO_DELETE(namePtr);
   }
};

//============================================================
// <T>ֻ����������</T>
//
// @tool
//============================================================
template <typename T>
class TDictionaryIteratorC{
public:
   typedef SDictionaryEntry<T> SEntry;
protected:
   SEntry* _pStart;
   SEntry* _pEntry;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TDictionaryIteratorC(){
      InnerInitialize((SEntry*)NULL);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TDictionaryIteratorC(const TDictionaryIteratorC<T>& iterator){
      InnerInitialize(iterator._pStart);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TDictionaryIteratorC(SEntry* pEntry){
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
   MO_INLINE TBool IsName(TCharC* pName){
      MO_ASSERT(_pEntry);
      return _pEntry->IsName(pName);
   }
   //------------------------------------------------------------
   MO_INLINE TBool IsValue(T value){
      MO_ASSERT(_pEntry);
      return _pEntry->value == value;
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   MO_INLINE TCharC* Name() const{
      MO_ASSERT(_pEntry);
      return _pEntry->Name();
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   MO_INLINE T Value() const{
      MO_ASSERT(_pEntry);
      return _pEntry->value;
   }
};

//============================================================
// <T>ֻ����������</T>
//
// @tool
//============================================================
template <typename T>
class TDictionaryIterator : public TDictionaryIteratorC<T>{
public:
   typedef SDictionaryEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TDictionaryIterator(){
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TDictionaryIterator(const TDictionaryIteratorC<T>& iterator) :
         TDictionaryIteratorC<T>(iterator){
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TDictionaryIterator(SEntry** ppEntries, TInt entryCount) :
         TDictionaryIteratorC<T>(ppEntries, entryCount){
   }
public:
   //------------------------------------------------------------
   // ���õ�ǰλ�õ���������
   MO_INLINE void SetValue(T value) const{
      MO_ASSERT(this->_pEntry);
      this->_pEntry->value = value;
   }
};

//============================================================
// <T>��ϣ�ֵ�</T>
//============================================================
template <typename T>
class MDictionary{
public:
   typedef SDictionaryEntry<T> SEntry;
   typedef TDictionaryIteratorC<T> TIteratorC;
   typedef TDictionaryIterator<T> TIterator;
protected:
   TInt _count;
   SEntry* _pFirst;
   SEntry* _pLast;
   SEntry* _pUnused;
   TInt _entryCount;
   SEntry** _ppEntries;
protected:
   //------------------------------------------------------------
   // <T>�����ϣ�ֵ䡣</T>
   MDictionary(){
      _count = 0;
      _pFirst = NULL;
      _pLast = NULL;
      _pUnused = NULL;
      _entryCount = 0;
      _ppEntries = NULL;
   }
   //------------------------------------------------------------
   // <T>������ϣ�ֵ䡣</T>
   MO_ABSTRACT ~MDictionary(){
   }
protected:
   MO_VIRTUAL SEntry* EntryCreate() = 0;
   MO_VIRTUAL void EntryRelease(SEntry* pEntry) = 0;
   MO_VIRTUAL SEntry** EntryFlatCreate(TInt size) = 0;
   MO_VIRTUAL void EntryFlatRelease(SEntry** ppEntries) = 0;
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
   //------------------------------------------------------------
   // <T>�������ʹ���еĽڵ㡣</T>
   MO_INLINE void EntryClear(){
      // ������
      for(TInt n = 0; n < _entryCount; n++){
         _ppEntries[n] = NULL;
      }
      // �������
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
   }
public:
   //------------------------------------------------------------
   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ�������������������Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const MDictionary<T>& dictionary) const{
      return Equals(&dictionary);
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ�������������������Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const MDictionary<T>& dictionary) const{
      return !Equals(&dictionary);
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   MO_INLINE const T operator[](TCharC* pName) const{
      MO_ASSERT(pName);
      SEntry* pEntry = EntryFind(pName);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
protected:
   //------------------------------------------------------------
   // <T>����ָ�����Ƶ�����λ�á�</T>
   MO_INLINE SEntry* EntryFind(TCharC* pName) const{
      // ���ݴ���ʱ
      if(_count > 0){
         THashCode hash = RString::MakeHashCode(pName);
         // �������Ƶ�����λ��
         SEntry* pEntry = _ppEntries[hash % _entryCount];
         while(NULL != pEntry){
            if(pEntry->hash == hash){
               if(pEntry->IsName(pName)){
                  return pEntry;
               }
            }
            pEntry = pEntry->linkPtr;
         }
      }
      // δ�ҵ�ʱ���ؽ��
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����ָ�����Ƶ�����λ�á�</T>
   MO_INLINE SEntry* EntryFindValue(T value) const{
      // ���ݴ���ʱ
      if(_count > 0){
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            if(pEntry->value == value){
               return pEntry;
            }
            pEntry = pEntry->nextPtr;
         }
      }
      // δ�ҵ�ʱ���ؽ��
      return NULL;
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
   TBool Contains(TCharC* pName) const{
      MO_ASSERT(pName);
      return (NULL != EntryFind(pName));
   }
   //------------------------------------------------------------
   // <T>�ж�ָ�������Ƿ���ڡ�</T>
   TBool ContainsValue(T value) const{
      return (NULL != EntryFindValue(value));
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ���������Ƿ���ȡ�</T>
   TBool Equals(const MDictionary<T>* pDictionary) const{
      MO_ASSERT(pDictionary);
      // �Ƚ�����
      if(_count != pDictionary->_count){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      TIteratorC iterator = pDictionary->IteratorC();
      while(iterator.Next()){
         SEntry* pEntry = EntryFind(iterator.Name());
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
   // <T>���ֻ����������</T>
   const TDictionaryIteratorC<T> IteratorC() const{
      return TDictionaryIteratorC<T>(_pFirst);
   }
   //------------------------------------------------------------
   // <T>���ֻ����������</T>
   const TDictionaryIteratorC<T> LastIteratorC() const{
      return TDictionaryIteratorC<T>(_pLast);
   }
public:
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   T Get(TCharC* pName) const{
      MO_ASSERT(pName);
      SEntry* pEntry = EntryFind(pName);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   T Find(TCharC* pName) const{
      if(NULL != pName){
         SEntry* pEntry = EntryFind(pName);
         if(NULL != pEntry){
            return pEntry->value;
         }
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   TCharC* Search(T value) const{
      SEntry* pEntry = EntryFindValue(value);
      return (NULL != pEntry) ? pEntry->Name() : NULL;
   }
public:
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   T& operator[](TCharC* pName){
      MO_ASSERT(pName);
      SEntry* pEntry = EntryFind(pName);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
protected:
   //------------------------------------------------------------
   // <T>���䵱ǰ����Ĺ�ϣֵ���顣</T>
   MO_INLINE void EntriesResize(SEntry** ppEntries, TInt size){
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
   TIteratorC Iterator(){
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
   void Assign(const MDictionary<T>& dictionary){
      Clear();
      Append(dictionary);
   }
   //------------------------------------------------------------
   // <T>׷��Դ��ϣ���ڵ�ȫ�����ݡ�</T>
   void Append(const MDictionary<T>& dictionary){
      TDictionaryIteratorC<T> iterator = dictionary.IteratorC();
      while(iterator.Next()){
         Set(iterator.Name(), iterator.Value());
      }
   }
   //------------------------------------------------------------
   // <T>���������������ݡ�</T>
   void Set(TCharC* pName, T value){
      THashCode hash = RString::MakeHashCode(pName);
      TInt index = hash % _entryCount;
      // �������ݳ��ֵ�λ��
      SEntry* pEntry = _ppEntries[index];
      while(NULL != pEntry) {
         if(pEntry->hash == hash){
            if(pEntry->IsName(pName)){
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
      pEntry->SetName(pName);
      pEntry->value = value;
      _ppEntries[index] = pEntry;
      // ׷�ӵ�����β��
      EntryPush(pEntry);
   }
   //------------------------------------------------------------
   // <T>�Ƴ�ָ�����Ƶ����ݡ�</T>
   T Remove(TCharC* pName){
      THashCode hash = RString::MakeHashCode(pName);
      TInt index = hash % _entryCount;
      // �������ݳ��ֵ�λ��
      T value = NULL;
      SEntry* pPrior = NULL;
      SEntry* pEntry = _ppEntries[index];
      while(NULL != pEntry){
         if(pEntry->hash == hash){
            if(pEntry->IsName(pName)){
               value = pEntry->value;
               if(NULL == pPrior){
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
   // <T>��յ�ǰ��ϣ��ȫ�����ݣ��ǹ�ϣ������ٴα����á�</T>
   void Clear(){
      EntryClear();
   }
   //------------------------------------------------------------
   // <T>�ͷŹ�ϣ�����</T>
   void Release(){
      // �ͷŽڵ�
      if(_count > 0){
         // �����нڵ�����Ϊδʹ��
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
      // �ͷŽڵ�����
      EntryFlatRelease(_ppEntries);
   }
};

//============================================================
// <T>�ֵ����</T>
//============================================================
template <typename T>
class TDictionary : public MDictionary<T>{
public:
   typedef SDictionaryEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   TDictionary(){
      this->EnsureSize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   TDictionary(TInt capacity){
      this->EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   TDictionary(const MDictionary<T>& dictionary){
      this->EnsureSize(dictionary.Count());
      this->Append(dictionary);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   TDictionary(const TDictionary<T>& dictionary){
      this->EnsureSize(dictionary.Count());
      this->Append(dictionary);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   MO_ABSTRACT ~TDictionary(){
      this->Release();
   }
public:
   //------------------------------------------------------------
   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
   MO_INLINE void operator=(const MDictionary<T>& dictionary){
      Assign(dictionary);
   }
   //------------------------------------------------------------
   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
   MO_INLINE void operator=(const TDictionary<T>& dictionary){
      Assign(dictionary);
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ��δʹ�õĽڵ㡣</T>
   MO_INLINE SEntry* EntryCreate(){
      this->EnsureSize(this->_count + 1);
      return MO_TYPE_CREATE(SEntry);
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ��ָ���Ľڵ㡣</T>
   MO_INLINE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      MO_TYPE_DELETE(pEntry);
   }
   //------------------------------------------------------------
   // <T>�ռ��ڵ��б��ڴ档</T>
   MO_INLINE SEntry** EntryFlatCreate(TInt size){
      SEntry** ppEntities = MO_TYPES_ALLOC(SEntry*, size);
      RTypes<SEntry*>::Clear(ppEntities, size);
      return ppEntities;
   }
   //------------------------------------------------------------
   // <T>�ͷŽڵ��б��ڴ档</T>
   MO_INLINE void EntryFlatRelease(SEntry** pEntries){
      MO_ASSERT(pEntries);
      MO_FREE(pEntries);
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
   MO_OVERRIDE void EnsureSize(TInt size){
      if(NULL == this->_ppEntries) {
         this->_entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
         // ��һ���½�ʱ�����ɹ�ϣ��
         this->_ppEntries = EntryFlatCreate(this->_entryCount);
      } else if (size > (this->_entryCount << 3)) {
         // �����ڴ�ʱ����
         size = this->_entryCount + (MO_LIB_MAX(this->_entryCount, size) >> 1);
         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
         SEntry** ppEntries = EntryFlatCreate(size);
         this->EntriesResize(ppEntries, size);
         // �ͷžɽڵ��ڴ�
         EntryFlatRelease(this->_ppEntries);
         // �����µĽڵ��б�
         this->_ppEntries = ppEntries;
         this->_entryCount = size;
      }
   }
};

//============================================================
// <T>�ֵ����</T>
//============================================================
template <typename T>
class FDictionary :
      public FObject,
      public MDictionary<T>{
public:
   typedef SDictionaryEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   FDictionary(){
      this->EnsureSize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   FDictionary(TInt capacity){
      this->EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   FDictionary(const MDictionary<T>& dictionary){
      this->EnsureSize(dictionary.Count());
      this->Append(dictionary);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   FDictionary(const FDictionary<T>& dictionary){
      this->EnsureSize(dictionary.Count());
      this->Append(dictionary);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   MO_ABSTRACT ~FDictionary(){
      this->Release();
   }
public:
   //------------------------------------------------------------
   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
   MO_INLINE void operator=(const MDictionary<T>& dictionary){
      Assign(dictionary);
   }
   //------------------------------------------------------------
   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
   MO_INLINE void operator=(const FDictionary<T>& dictionary){
      Assign(dictionary);
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ��δʹ�õĽڵ㡣</T>
   MO_INLINE SEntry* EntryCreate(){
      this->EnsureSize(this->_count + 1);
      return MO_TYPE_CREATE(SEntry);
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ��ָ���Ľڵ㡣</T>
   MO_INLINE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      MO_TYPE_DELETE(pEntry);
   }
   //------------------------------------------------------------
   // <T>�ռ��ڵ��б��ڴ档</T>
   MO_INLINE SEntry** EntryFlatCreate(TInt size){
      SEntry** ppEntities = MO_TYPES_ALLOC(SEntry*, size);
      RTypes<SEntry*>::Clear(ppEntities, size);
      return ppEntities;
   }
   //------------------------------------------------------------
   // <T>�ͷŽڵ��б��ڴ档</T>
   MO_INLINE void EntryFlatRelease(SEntry** ppEntries){
      MO_ASSERT(ppEntries);
      MO_FREE(ppEntries);
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
   MO_OVERRIDE void EnsureSize(TInt size){
      if(NULL == this->_ppEntries) {
         this->_entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
         // ��һ���½�ʱ�����ɹ�ϣ��
         this->_ppEntries = EntryFlatCreate(this->_entryCount);
      } else if (size > (this->_entryCount << 3)) {
         // �����ڴ�ʱ����
         size = this->_entryCount + (MO_LIB_MAX(this->_entryCount, size) >> 1);
         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
         SEntry** ppEntries = EntryFlatCreate(size);
         this->EntriesResize(ppEntries, size);
         // �ͷžɽڵ��ڴ�
         EntryFlatRelease(this->_ppEntries);
         // �����µĽڵ��б�
         this->_ppEntries = ppEntries;
         this->_entryCount = size;
      }
   }
};

////============================================================
//// <T>�������ַ���Сд�Ĺ�ϣ�ֵ����</T>
////============================================================
//template <typename T>
//class MNcDictionaryC : public MEntriesC< SDictionaryEntry<T> >{
//private:
//   typedef SDictionaryEntry<T> SEntry;
//   typedef TDictionaryIteratorC<T> TIteratorC;
//protected:
//   TInt _entryCount;
//   SEntry** _ppEntries;
//protected:
//   //------------------------------------------------------------
//   // <T>�ڲ���ʼ����</T>
//   inline void InnerInitialize(){
//      MEntriesC<SEntry>::InnerInitialize();
//      _entryCount = 0;
//      _ppEntries = NULL;
//   }
//public:
//   //------------------------------------------------------------
//   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ�������������������Ƿ���ȡ�</T>
//   TBool operator==(const MNcDictionaryC<T>& dictionary) const{
//      return Equals(&dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ�������������������Ƿ���ȡ�</T>
//   TBool operator!=(const MNcDictionaryC<T>& dictionary) const{
//      return !Equals(&dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>���ָ�����Ƶ����ݡ�</T>
//   const T operator[](TCharC* pName) const{
//      MO_ASSERT(pName);
//      SEntry* pEntry = EntryFind(pName);
//      MO_ASSERT(pEntry);
//      return pEntry->value;
//   }
//protected:
//   //------------------------------------------------------------
//   // <T>����ָ�����Ƶ�����λ�á�</T>
//   inline SEntry* EntryFind(TCharC* pName) const{
//      // ���ݴ���ʱ
//      if(_count > 0){
//         THashCode hash = RString::MakeNocaseHashCode(pName);
//         // �������Ƶ�����λ��
//         SEntry* pEntry = _ppEntries[hash % _entryCount];
//         while(NULL != pEntry){
//            if(pEntry->hash == hash){
//               if(pEntry->IsNameIgnoreCase(pName)){
//                  return pEntry;
//               }
//            }
//            pEntry = pEntry->linkPtr;
//         }
//      }
//      // δ�ҵ�ʱ���ؽ��
//      return NULL;
//   }
//   //------------------------------------------------------------
//   // <T>����ָ�����Ƶ�����λ�á�</T>
//   inline SEntry* EntryFindValue(T value) const{
//      // ���ݴ���ʱ
//      if(_count > 0){
//         SEntry* pEntry = _pFirst;
//         while(NULL != pEntry){
//            if(pEntry->value == value){
//               return pEntry;
//            }
//            pEntry = pEntry->pNext;
//         }
//      }
//      // δ�ҵ�ʱ���ؽ��
//      return NULL;
//   }
//   //------------------------------------------------------------
//   // �������������ʹ���еĽڵ㣬����δʹ��������ѭ��ʹ��
//   inline void EntryClear(){
//      // ������
//      for(TInt n=0; n<_entryCount; n++){
//         _ppEntries[n] = NULL;
//      }
//      // �������
//      MEntriesC<SEntry>::EntryClear();
//   }
//public:
//   //------------------------------------------------------------
//   // <T>��ǰ��ϣ���϶����Ƿ�Ϊ�ա�</T>
//   TBool IsEmpty() const{
//      return (0 == _count);
//   }
//   //------------------------------------------------------------
//   // <T>������ݸ�����</T>
//   TInt Count() const{
//      return _count;
//   }
//   //------------------------------------------------------------
//   // <T>�ж�ָ�������Ƿ���ڡ�</T>
//   TBool Contains(TCharC* pName) const{
//      MO_ASSERT(pName);
//      return (NULL != EntryFind(pName));
//   }
//   //------------------------------------------------------------
//   // <T>�ж�ָ�������Ƿ���ڡ�</T>
//   TBool ContainsValue(T value) const{
//      return (NULL != EntryFindValue(value));
//   }
//   //------------------------------------------------------------
//   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ���������Ƿ���ȡ�</T>
//   TBool Equals(const MNcDictionaryC<T>* pDictionary) const{
//      MO_ASSERT(pDictionary);
//      // �Ƚ�����
//      if(_count != pDictionary->_count){
//         return EFalse;
//      }
//      // �Ƚ�������Ŀ
//      TIteratorC iterator = pDictionary->IteratorC();
//      while(iterator.Next()){
//         SEntry* pEntry = EntryFind(iterator.Name());
//         if(NULL == pEntry){
//            return EFalse;
//         }
//         if(!iterator.IsValue(pEntry->value)){
//            return EFalse;
//         }
//      }
//      return ETrue;
//   }
//   //------------------------------------------------------------
//   // <T>���ֻ����������</T>
//   const TDictionaryIteratorC<T> IteratorC() const{
//      return TDictionaryIteratorC<T>(_pFirst);
//   }
//   //------------------------------------------------------------
//   // <T>���ֻ����������</T>
//   const TDictionaryIteratorC<T> LastIteratorC() const{
//      return TDictionaryIteratorC<T>(_pLast);
//   }
//public:
//   //------------------------------------------------------------
//   // <T>���ָ�����Ƶ����ݡ�</T>
//   T Get(TCharC* pName) const{
//      MO_ASSERT(pName);
//      SEntry* pEntry = EntryFind(pName);
//      MO_ASSERT(pEntry);
//      return pEntry->value;
//   }
//   //------------------------------------------------------------
//   // <T>���ָ�����Ƶ����ݡ�</T>
//   T Find(TCharC* pName) const{
//      if(NULL != pName){
//         SEntry* pEntry = EntryFind(pName);
//         if(NULL != pEntry){
//            return pEntry->value;
//         }
//      }
//      return NULL;
//   }
//   //------------------------------------------------------------
//   // <T>���ָ�����Ƶ����ݡ�</T>
//   TCharC* Search(T value) const{
//      SEntry* pEntry = EntryFindValue(value);
//      return (NULL != pEntry) ? pEntry->pName->MemoryC() : NULL;
//   }
//};
//
////============================================================
//// <T>�������ַ���Сд�Ĺ�ϣ���϶���</T>
////============================================================
//template <typename A, typename T>
//class MNcDictionary : public MNcDictionaryC<T>{
//public:
//   typedef SDictionaryEntry<T> SEntry;
//   typedef TDictionaryIteratorC<T> TIteratorC;
//   typedef TDictionaryIterator<T> TIterator;
//protected:
//   SEntry* _pUnused;
//private:
//   //------------------------------------------------------------
//   // <T>����ڲ�����ָ�롣</T>
//   inline A* InnerCast(){
//      return static_cast<A*>(this);
//   }
//protected:
//   //------------------------------------------------------------
//   // �ڲ���ʼ��
//   inline void InnerInitialize(TInt size){
//      MNcDictionaryC<T>::InnerInitialize();
//      _pUnused = NULL;
//      InnerCast()->A::EnsureSize(size);
//   }
//   //------------------------------------------------------------
//   // <T>�ͷŹ�ϣ�����</T>
//   void Release(){
//      A* pInstance = InnerCast();
//      // �ͷŽڵ�
//      if(_count > 0){
//         // �����нڵ�����Ϊδʹ��
//         _pLast->pNext = _pUnused;
//         _pUnused = _pFirst;
//         // ɾ�����нڵ�
//         SEntry* pFind = _pUnused;
//         while(NULL != pFind){
//            SEntry* pNext = pFind->pNext;
//            pInstance->EntryRelease(pFind);
//            pFind = pNext;
//         }
//      }
//      // �ͷŽڵ�����
//      pInstance->EntryFlatRelease(_ppEntries);
//   }
//   //------------------------------------------------------------
//   // <T>�ռ�һ��δʹ�õĽڵ㡣</T>
//   inline SEntry* EntryAlloc(){
//      SEntry* pEntry = NULL;
//      // �鿴δʹ�ýڵ����Ƿ������ɽڵ�
//      if(NULL != _pUnused){
//         // �ռ�δʹ�õĽڵ�
//         pEntry = _pUnused;
//         _pUnused = _pUnused->pNext;
//      }else{
//         // �ռ��½ڵ�
//         pEntry = InnerCast()->A::EntryCreate();
//      }
//      return pEntry;
//   }
//   //------------------------------------------------------------
//   // <T>�ͷ�һ����ʹ�õĽڵ㡣</T>
//   inline void EntryFree(SEntry* pEntry){
//      MO_ASSERT(pEntry);
//      pEntry->pNext = _pUnused;
//      _pUnused = pEntry;
//   }
//public:
//   //------------------------------------------------------------
//   // <T>���ָ�����Ƶ����ݡ�</T>
//   T& operator[](TCharC* pName){
//      MO_ASSERT(pName);
//      SEntry* pEntry = EntryFind(pName);
//      MO_ASSERT(pEntry);
//      return pEntry->value;
//   }
//protected:
//   //------------------------------------------------------------
//   // <T>���䵱ǰ����Ĺ�ϣֵ���顣</T>
//   inline void EntriesResize(SEntry** ppEntries, TInt size){
//      // ѭ��ȡ���ɵĽڵ��б����ݣ��Ƶ��µĽڵ��б���
//      TInt n = -1;
//      while(++n < _entryCount){
//         SEntry* pEntry = _ppEntries[n];
//         while(NULL != pEntry){
//            // ���浱ǰ�ڵ����һ���ڵ�ָ��
//            SEntry* pLink = pEntry->linkPtr;
//            // ����ǰ�ڵ�洢���½��Ľڵ��б���ȥ
//            TInt index = pEntry->Hash() % size;
//            pEntry->linkPtr = ppEntries[index];
//            ppEntries[index] = pEntry;
//            // ��ñ������һ���ڵ�ָ��
//            pEntry = pLink;
//         }
//      }
//   }
//public:
//   //------------------------------------------------------------
//   // <T>��ÿ�д��������</T>
//   TIteratorC Iterator(){
//      return TIterator(_pFirst);
//   }
//   //------------------------------------------------------------
//   // <T>��ý�β��д��������</T>
//   TIterator LastIterator(){
//      return TIterator(_pLast);
//   }
//public:
//   //------------------------------------------------------------
//   // <T>����Դ��ϣ���ڵ�ȫ�����ݡ�</T>
//   void Assign(const MNcDictionaryC<T>& dictionary){
//      Clear();
//      Append(dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>׷��Դ��ϣ���ڵ�ȫ�����ݡ�</T>
//   void Append(const MNcDictionaryC<T>& dictionary){
//      TDictionaryIteratorC<T> iterator = dictionary.IteratorC();
//      while(iterator.Next()){
//         Set(iterator.Name(), iterator.Value());
//      }
//   }
//   //------------------------------------------------------------
//   // <T>���������������ݡ�</T>
//   void Set(TCharC* pName, T value){
//      THashCode hash = RString::MakeNocaseHashCode(pName);
//      TInt index = hash % _entryCount;
//      // �������ݳ��ֵ�λ��
//      SEntry* pEntry = _ppEntries[index];
//      while(NULL != pEntry) {
//         if(pEntry->hash == hash){
//            if(pEntry->IsNameIgnoreCase(pName)){
//               pEntry->value = value;
//               return;
//            }
//         }
//         pEntry = pEntry->pNext;
//      }
//      // ������Ʋ����ڣ�Ϊ�½��ڵ����ڴ�
//      pEntry = EntryAlloc();
//      index = hash % _entryCount;
//      pEntry->linkPtr = _ppEntries[index];
//      pEntry->hash = hash;
//      pEntry->SetName(pName);
//      pEntry->value = value;
//      _ppEntries[index] = pEntry;
//      // ׷�ӵ�����β��
//      EntryPush(pEntry);
//   }
//   //------------------------------------------------------------
//   // <T>�Ƴ�ָ�����Ƶ����ݡ�</T>
//   T Remove(TCharC* pName){
//      THashCode hash = RString::MakeNocaseHashCode(pName);
//      TInt index = hash % _entryCount;
//      // �������ݳ��ֵ�λ��
//      T value = NULL;
//      SEntry* pPrior = _ppEntries[index];
//      SEntry* pEntry = pPrior;
//      while(NULL != pEntry){
//         if(pEntry->hash == hash){
//            if(pEntry->IsNameIgnoreCase(pName)){
//               value = pEntry->value;
//               if(pEntry == pPrior){
//                  // ��ǰ�����ǵ�һ������ʱ
//                  _ppEntries[index] = pEntry->pNext;
//               }else{
//                  // ��ǰ�����ǵ�һ������ʱ
//                  pPrior->pNext = pEntry->pNext;
//               }
//               // ɾ����ǰ�ڵ�
//               EntryRemove(pEntry);
//               break;
//            }
//         }
//         pPrior = pEntry;
//         pEntry = pEntry->pNext;
//      }
//      return value;
//   }
//   //------------------------------------------------------------
//   // <T>��յ�ǰ��ϣ��ȫ�����ݣ��ǹ�ϣ������ٴα����á�</T>
//   void Clear(){
//      EntryClear();
//   }
//};
//
////============================================================
//// <T>�������ַ���Сд���ֵ����</T>
////============================================================
//template <typename T>
//class TNcDictionary : public MNcDictionary<TNcDictionary<T>, T>{
//public:
//   friend class MNcDictionary< TNcDictionary<T>, T >;
//   typedef SDictionaryEntry<T> SEntry;
//public:
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   TNcDictionary(){
//      InnerInitialize(MO_OBJECT_CAPACITY);
//   }
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   TNcDictionary(TInt capacity){
//      InnerInitialize(capacity);
//   }
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   TNcDictionary(const MNcDictionaryC<T>& dictionary){
//      InnerInitialize(dictionary.Count());
//      Append(dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   TNcDictionary(const TNcDictionary<T>& dictionary){
//      InnerInitialize(dictionary.Count());
//      Append(dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   ~TNcDictionary(){
//      InnerRelease();
//   }
//public:
//   //------------------------------------------------------------
//   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
//   void operator=(const MNcDictionaryC<T>& dictionary){
//      Assign(dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
//   void operator=(const TNcDictionary<T>& dictionary){
//      Assign(dictionary);
//   }
//   protected:
////------------------------------------------------------------
//   // <T>�½�һ��δʹ�õĽڵ㡣</T>
//   inline SEntry* EntryCreate(){
//      EnsureSize(_count + 1);
//      return MO_CREATE(SEntry);
//   }
//   //------------------------------------------------------------
//   // <T>�ͷ�һ��ָ���Ľڵ㡣</T>
//   inline void EntryRelease(SEntry* pEntry){
//      MO_ASSERT(pEntry);
//      MO_DELETE(pEntry);
//   }
//   //------------------------------------------------------------
//   // <T>�ռ��ڵ��б��ڴ档</T>
//   inline SEntry** EntryFlatCreate(TInt size){
//      SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
//      RType<SEntry*>::Clear(ppEntries, size);
//      return ppEntries;
//   }
//   //------------------------------------------------------------
//   // <T>�ͷŽڵ��б��ڴ档</T>
//   inline void EntryFlatRelease(SEntry** ppEntries){
//      MO_ASSERT(ppEntries);
//      MO_FREE(ppEntries);
//   }
//public:
//   //------------------------------------------------------------
//   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
//   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
//   void EnsureSize(TInt size){
//      if(NULL == _ppEntries) {
//         _entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
//         // ��һ���½�ʱ�����ɹ�ϣ��
//         _ppEntries = EntryFlatCreate(_entryCount);
//      } else if (size > (_entryCount << 3)) {
//         // �����ڴ�ʱ����
//         size = _entryCount + (MO_LIB_MAX(_entryCount, size) >> 1);
//         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
//         SEntry** ppEntries = EntryFlatCreate(size);
//         EntriesResize(ppEntries, size);
//         // �ͷžɽڵ��ڴ�
//         EntryFlatRelease(_ppEntries);
//         // �����µĽڵ��б�
//         _ppEntries = ppEntries;
//         _entryCount = size;
//      }
//   }
//};
////------------------------------------------------------------
//typedef MO_CM_DECLARE TNcDictionary<TAny*> TPtrNcDictionary;
//
////============================================================
//// <T>�������ַ���Сд���ֵ����</T>
////============================================================
//template <typename T>
//class FNcDictionary : public MNcDictionary<FNcDictionary<T>, T>{
//public:
//   friend class MNcDictionary< FNcDictionary<T>, T >;
//   typedef SDictionaryEntry<T> SEntry;
//public:
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   FNcDictionary(){
//      InnerInitialize(MO_OBJECT_CAPACITY);
//   }
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   FNcDictionary(TInt capacity){
//      InnerInitialize(capacity);
//   }
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   FNcDictionary(const MDictionaryC<T>& dictionary){
//      InnerInitialize(dictionary.Count());
//      Append(dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>�����ֵ����</T>
//   FNcDictionary(const FDictionary<T>& dictionary){
//      InnerInitialize(dictionary.Count());
//      Append(dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>�ͷ��ֵ����</T>
//   ~FNcDictionary(){
//      InnerRelease();
//   }
//public:
//   //------------------------------------------------------------
//   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
//   void operator=(const MNcDictionaryC<T>& dictionary){
//      Assign(dictionary);
//   }
//   //------------------------------------------------------------
//   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
//   void operator=(const FNcDictionary<T>& dictionary){
//      Assign(dictionary);
//   }
//protected:
//   //------------------------------------------------------------
//   // <T>�½�һ��δʹ�õĽڵ㡣</T>
//   inline SEntry* EntryCreate(){
//      EnsureSize(_count + 1);
//      return MO_CREATE(SEntry);
//   }
//   //------------------------------------------------------------
//   // <T>�ͷ�һ��ָ���Ľڵ㡣</T>
//   inline void EntryRelease(SEntry* pEntry){
//      MO_ASSERT(pEntry);
//      MO_DELETE(pEntry);
//   }
//   //------------------------------------------------------------
//   // <T>�ռ��ڵ��б��ڴ档</T>
//   inline SEntry** EntryFlatCreate(TInt size){
//      SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
//      RTypes<SEntry*>::Clear(ppEntries, size);
//      return ppEntries;
//   }
//   //------------------------------------------------------------
//   // <T>�ͷŽڵ��б��ڴ档</T>
//   inline void EntryFlatRelease(SEntry** ppEntries){
//      MO_ASSERT(ppEntries);
//      MO_FREE(ppEntries);
//   }
//public:
//   //------------------------------------------------------------
//   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
//   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
//   void EnsureSize(TInt size){
//      if(NULL == _ppEntries) {
//         _entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
//         // ��һ���½�ʱ�����ɹ�ϣ��
//         _ppEntries = EntryFlatCreate(_entryCount);
//      } else if (size > (_entryCount << 3)) {
//         // �����ڴ�ʱ����
//         size = _entryCount + (MO_LIB_MAX(_entryCount, size) >> 1);
//         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
//         SEntry** ppEntries = EntryFlatCreate(size);
//         EntriesResize(ppEntries, size);
//         // �ͷžɽڵ��ڴ�
//         EntryFlatRelease(_ppEntries);
//         // �����µĽڵ��б�
//         _ppEntries = ppEntries;
//         _entryCount = size;
//      }
//   }
//};
////------------------------------------------------------------
//typedef MO_CM_DECLARE FNcDictionary<TAny*> FPtrNcDictionary;

MO_NAMESPACE_END

#endif // __MO_CM_DICTIONARY_H__
