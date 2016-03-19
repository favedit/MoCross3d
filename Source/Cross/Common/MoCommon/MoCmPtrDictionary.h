#ifndef __MO_CM_PTR_DICTIONARY_H__
#define __MO_CM_PTR_DICTIONARY_H__

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
struct SPtrDictionaryEntry{
public:
   SPtrDictionaryEntry* linkPtr;
   SPtrDictionaryEntry* priorPtr;
   SPtrDictionaryEntry* nextPtr;
   THashCode hash;
   TString name;
   GPtr<T> value;
public:
   //------------------------------------------------------------
   // <T>�����ϣ�ֵ�ڵ�</T>
   SPtrDictionaryEntry(){
      MO_CLEAR(linkPtr);
      MO_CLEAR(priorPtr);
      MO_CLEAR(nextPtr);
      hash = 0;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ���ȡ�</T>
   MO_INLINE TBool IsName(TCharC* pName){
      return name.Equals(pName);
   }
   //------------------------------------------------------------
   // <T>�жϲ����ִ�Сд�����Ƿ���ȡ�</T>
   MO_INLINE TBool IsNameIgnoreCase(TCharC* pName){
      return name.EqualsIgnoreCase(pName);
   }
   //------------------------------------------------------------
   // <T>����ַ������ơ�</T>
   MO_INLINE TCharC* Name(){
      return name;
   }
   //------------------------------------------------------------
   // <T>�����ַ������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      name = pName;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      MO_CLEAR(linkPtr);
      MO_CLEAR(priorPtr);
      MO_CLEAR(nextPtr);
      hash = 0;
      name = NULL;
      value = NULL;
   }
};

//============================================================
// <T>ֻ����������</T>
//
// @tool
//============================================================
template <typename T>
class GPtrDictionaryIteratorC{
public:
   typedef SPtrDictionaryEntry<T> SEntry;
protected:
   SEntry* _pStart;
   SEntry* _pEntry;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrDictionaryIteratorC(){
      InnerInitialize((SEntry*)NULL);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrDictionaryIteratorC(const GPtrDictionaryIteratorC<T>& iterator){
      InnerInitialize(iterator._pStart);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrDictionaryIteratorC(SEntry* pEntry){
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
   MO_INLINE const T* operator *() const{
      MO_ASSERT(_pEntry);
      return (T*)_pEntry->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T* operator->() const{
      MO_ASSERT(_pEntry);
      return (T*)_pEntry->value;
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
   MO_INLINE TBool IsValue(T* pValue){
      MO_ASSERT(_pEntry);
      return _pEntry->value == pValue;
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   MO_INLINE TCharC* Name() const{
      MO_ASSERT(_pEntry);
      return _pEntry->Name();
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   MO_INLINE T* Value() const{
      MO_ASSERT(_pEntry);
      return _pEntry->value;
   }
};

//============================================================
// <T>ָ���ֵ��������</T>
//
// @tool
//============================================================
template <typename T>
class GPtrDictionaryIterator : public GPtrDictionaryIteratorC<T>{
public:
   typedef SPtrDictionaryEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>����ָ���ֵ��������</T>
   GPtrDictionaryIterator(){
   }
   //------------------------------------------------------------
   // <T>����ָ���ֵ��������</T>
   GPtrDictionaryIterator(const GPtrDictionaryIteratorC<T>& iterator) :
         GPtrDictionaryIteratorC<T>(iterator){
   }
   //------------------------------------------------------------
   // <T>����ָ���ֵ��������</T>
   GPtrDictionaryIterator(SEntry** ppEntries, TInt entryCount) :
         GPtrDictionaryIteratorC<T>(ppEntries, entryCount){
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator *(){
      MO_ASSERT(this->_pEntry);
      return (T*)this->_pEntry->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator->(){
      MO_ASSERT(this->_pEntry);
      return (T*)this->_pEntry->value;
   }
public:
   //------------------------------------------------------------
   // <T>���õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE void SetValue(T* pValue) const{
      MO_ASSERT(this->_pEntry);
      this->_pEntry->value = pValue;
   }
};

//============================================================
// <T>��ϣ�ֵ�</T>
//============================================================
template <typename T>
class MPtrDictionary{
public:
   typedef SPtrDictionaryEntry<T> SEntry;
   typedef GPtrDictionaryIteratorC<T> TIteratorC;
   typedef GPtrDictionaryIterator<T> TIterator;
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
   MPtrDictionary(){
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      MO_CLEAR(_pUnused);
      _entryCount = 0;
      MO_CLEAR(_ppEntries);
   }
   //------------------------------------------------------------
   // <T>������ϣ�ֵ䡣</T>
   MO_ABSTRACT ~MPtrDictionary(){
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
         pEntry = EntryCreate();
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ����ʹ�õĽڵ㡣</T>
   MO_INLINE void EntryFree(SEntry* pEntry){
      MO_ASSERT(pEntry);
      pEntry->Reset();
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
   MO_INLINE TBool operator==(const MPtrDictionary<T>& dictionary) const{
      return Equals(&dictionary);
   }
   //------------------------------------------------------------
   // <T>�жϵ�ǰ��ϣ���Ϻ�ָ����ϣ�������������������Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const MPtrDictionary<T>& dictionary) const{
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
   MO_INLINE SEntry* EntryFindValue(T* pValue) const{
      // ���ݴ���ʱ
      if(_count > 0){
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            if(pEntry->value == pValue){
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
   TBool Equals(const MPtrDictionary<T>* pPtrDictionary) const{
      MO_ASSERT(pPtrDictionary);
      // �Ƚ�����
      if(_count != pPtrDictionary->_count){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      TIteratorC iterator = pPtrDictionary->IteratorC();
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
   const GPtrDictionaryIteratorC<T> IteratorC() const{
      return GPtrDictionaryIteratorC<T>(_pFirst);
   }
   //------------------------------------------------------------
   // <T>���ֻ����������</T>
   const GPtrDictionaryIteratorC<T> LastIteratorC() const{
      return GPtrDictionaryIteratorC<T>(_pLast);
   }
public:
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   T* Get(TCharC* pName) const{
      MO_ASSERT(pName);
      SEntry* pEntry = EntryFind(pName);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   T* Find(TCharC* pName) const{
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
   TCharC* Search(T* pValue) const{
      SEntry* pEntry = EntryFindValue(pValue);
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
   MO_INLINE TIteratorC Iterator(){
      return TIterator(_pFirst);
   }
   //------------------------------------------------------------
   // <T>��ý�β��д��������</T>
   MO_INLINE TIterator LastIterator(){
      return TIterator(_pLast);
   }
public:
   //------------------------------------------------------------
   // <T>����Դ��ϣ���ڵ�ȫ�����ݡ�</T>
   void Assign(const MPtrDictionary<T>& dictionary){
      Clear();
      Append(dictionary);
   }
   //------------------------------------------------------------
   // <T>׷��Դ��ϣ���ڵ�ȫ�����ݡ�</T>
   void Append(const MPtrDictionary<T>& dictionary){
      GPtrDictionaryIteratorC<T> iterator = dictionary.IteratorC();
      while(iterator.Next()){
         Set(iterator.Name(), iterator.Value());
      }
   }
   //------------------------------------------------------------
   // <T>���������������ݡ�</T>
   void Set(TCharC* pName, T* pValue){
      THashCode hash = RString::MakeHashCode(pName);
      TInt index = hash % _entryCount;
      // �������ݳ��ֵ�λ��
      SEntry* pEntry = _ppEntries[index];
      while(NULL != pEntry) {
         if(pEntry->hash == hash){
            if(pEntry->IsName(pName)){
               pEntry->value = pValue;
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
      pEntry->value = pValue;
      _ppEntries[index] = pEntry;
      // ׷�ӵ�����β��
      EntryPush(pEntry);
   }
   //------------------------------------------------------------
   // <T>�Ƴ�ָ�����Ƶ����ݡ�</T>
   T* Remove(TCharC* pName){
      THashCode hash = RString::MakeHashCode(pName);
      TInt index = hash % _entryCount;
      // �������ݳ��ֵ�λ��
      T* pValue = NULL;
      SEntry* pPrior = NULL;
      SEntry* pEntry = _ppEntries[index];
      while(NULL != pEntry){
         if(pEntry->hash == hash){
            if(pEntry->IsName(pName)){
               pValue = pEntry->value;
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
      return pValue;
   }
   //------------------------------------------------------------
   // <T>��յ�ǰ��ϣ��ȫ�����ݣ���ϣ������ٴα����á�</T>
   void Clear(){
      // ��սڵ�����
      SEntry* pEntry = _pFirst;
      while(pEntry != NULL){
         pEntry->Reset();
         pEntry = pEntry->nextPtr;
      }
      // ���սڵ㼯��
      if(_count > 0){
         // �����нڵ�����Ϊδʹ��
         _pLast->nextPtr = _pUnused;
         _pUnused = _pFirst;
      }
      // �������
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      for(TInt n = 0; n < _entryCount; n++){
         _ppEntries[n] = NULL;
      }
   }
   //------------------------------------------------------------
   // <T>�ͷŹ�ϣ�����</T>
   void Release(){
      // �������
      Clear();
      // ɾ�����нڵ�
      SEntry* pFind = _pUnused;
      while(pFind != NULL){
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
class GPtrDictionary : public MPtrDictionary<T>{
public:
   typedef SPtrDictionaryEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   GPtrDictionary(){
      this->EnsureSize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   GPtrDictionary(TInt capacity){
      this->EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   GPtrDictionary(const MPtrDictionary<T>& dictionary){
      this->EnsureSize(dictionary.Count());
      this->Append(dictionary);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   GPtrDictionary(const GPtrDictionary<T>& dictionary){
      this->EnsureSize(dictionary.Count());
      this->Append(dictionary);
   }
   //------------------------------------------------------------
   // <T>�����ֵ����</T>
   MO_ABSTRACT ~GPtrDictionary(){
      this->Release();
   }
public:
   //------------------------------------------------------------
   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
   MO_INLINE void operator=(const MPtrDictionary<T>& dictionary){
      Assign(dictionary);
   }
   //------------------------------------------------------------
   // <T>������һ���ֵ�����ȫ�����ݡ�</T>
   MO_INLINE void operator=(const GPtrDictionary<T>& dictionary){
      Assign(dictionary);
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ��δʹ�õĽڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      this->EnsureSize(this->_count + 1);
      return MO_TYPE_CREATE(SEntry);
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ��ָ���Ľڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      MO_TYPE_DELETE(pEntry);
   }
   //------------------------------------------------------------
   // <T>�ռ��ڵ��б��ڴ档</T>
   MO_OVERRIDE SEntry** EntryFlatCreate(TInt size){
      SEntry** ppEntities = MO_TYPES_ALLOC(SEntry*, size);
      RTypes<SEntry*>::Clear(ppEntities, size);
      return ppEntities;
   }
   //------------------------------------------------------------
   // <T>�ͷŽڵ��б��ڴ档</T>
   MO_OVERRIDE void EntryFlatRelease(SEntry** ppEntries){
      MO_ASSERT(ppEntries);
      MO_FREE(ppEntries);
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // <P>����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
   MO_OVERRIDE void EnsureSize(TInt size){
      if(this->_ppEntries == NULL) {
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

MO_NAMESPACE_END

#endif // __MO_CM_PTR_DICTIONARY_H__
