#ifndef __MO_CM_ATTRIBUTES_H__
#define __MO_CM_ATTRIBUTES_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

#ifndef __MO_CM_COLLECTION_H__
#include "MoCmCollection.h"
#endif // __MO_CM_COLLECTION_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>���Ա�ڵ�</T>
//
// @struct
//============================================================
struct SAttributesEntry{
public:
   SAttributesEntry* linkPtr;
   SAttributesEntry* priorPtr;
   SAttributesEntry* nextPtr;
   THashCode hash;
   FString* namePtr;
   FString* valuePtr;
public:
   //------------------------------------------------------------
   // <T>�������Ա�ڵ�</T>
   SAttributesEntry(){
      MO_CLEAR(linkPtr);
      MO_CLEAR(priorPtr);
      MO_CLEAR(nextPtr);
      hash = 0;
      MO_CLEAR(namePtr);
      MO_CLEAR(valuePtr);
   }
   //------------------------------------------------------------
   // <T>�������Ա�ڵ�</T>
   ~SAttributesEntry(){
      MO_DELETE(namePtr);
      MO_DELETE(valuePtr);
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ���ȡ�</T>
   MO_INLINE TBool IsName(TCharC* pName) const{
      if((NULL != namePtr) && (NULL != pName)){
         return namePtr->Equals(pName);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�жϲ����ִ�Сд�����Ƿ���ȡ�</T>
   MO_INLINE TBool IsNameIgnoreCase(TCharC* pName) const{
      if((NULL != namePtr) && (NULL != pName)){
         return namePtr->EqualsIgnoreCase(pName);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>����ַ������ơ�</T>
   MO_INLINE TCharC* Name() const{
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
   //------------------------------------------------------------
   // <T>����ַ������ݡ�</T>
   MO_INLINE TCharC* Value() const{
      if(NULL == valuePtr){
         return NULL;
      }
      return valuePtr->MemoryC();
   }
   //------------------------------------------------------------
   // <T>�����ַ������ݡ�</T>
   MO_INLINE void SetValue(TCharC* pValue){
      if(NULL == valuePtr){
         valuePtr = MO_CREATE(FString);
      }
      valuePtr->Assign(pValue);
   }
public:
   //------------------------------------------------------------
   // <T>�ͷ����ݡ�</T>
   MO_INLINE void Release(){
      MO_DELETE(namePtr);
      MO_DELETE(valuePtr);
   }
};

//============================================================
// <T>ֻ�������������</T>
//
// @tool
//============================================================
class MO_CM_DECLARE TAttributesIteratorC{
public:
   typedef SAttributesEntry SEntry;
protected:
   SEntry* _pStart;
   SEntry* _pEntry;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TAttributesIteratorC(){
      MO_CLEAR(_pStart);
      MO_CLEAR(_pEntry);
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TAttributesIteratorC(const TAttributesIteratorC& iterator){
      _pStart = iterator._pStart;
      _pEntry = iterator._pEntry;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TAttributesIteratorC(SEntry* pEntry){
      _pStart = pEntry;
      MO_CLEAR(_pEntry);
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const FString& operator *() const{
      MO_ASSERT(_pEntry);
      return *(_pEntry->namePtr);
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const FString* operator->() const{
      MO_ASSERT(_pEntry);
      return _pEntry->valuePtr;
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
   MO_INLINE TBool IsName(TCharC* pName) const{
      MO_ASSERT(_pEntry);
      return _pEntry->namePtr->Equals(pName);
   }
   //------------------------------------------------------------
   // <T>�ж������Ƿ���ͬ��</T>
   MO_INLINE TBool IsValue(TCharC* pValue) const{
      MO_ASSERT(_pEntry);
      return _pEntry->valuePtr->Equals(pValue);
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ơ�</T>
   MO_INLINE TCharC* Name() const{
      MO_ASSERT(_pEntry);
      return _pEntry->namePtr->MemoryC();
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE TCharC* Value() const{
      MO_ASSERT(_pEntry);
      return _pEntry->valuePtr->MemoryC();
   }
};

//============================================================
// <T>��д�����������</T>
//
// @tool
//============================================================
class MO_CM_DECLARE TAttributesIterator : public TAttributesIteratorC{
public:
   typedef SAttributesEntry SEntry;
public:
   //------------------------------------------------------------
   // �������������
   TAttributesIterator(){
   }
   //------------------------------------------------------------
   // �������������
   TAttributesIterator(const TAttributesIteratorC& iterator) :
         TAttributesIteratorC(iterator){
   }
   //------------------------------------------------------------
   // �������������
   TAttributesIterator(SEntry* pEntry) :
         TAttributesIteratorC(pEntry){
   }
public:
   //------------------------------------------------------------
   // ���õ�ǰλ�õ���������
   inline void SetValue(TCharC* pValue) const{
      MO_ASSERT(_pEntry);
      _pEntry->valuePtr->Assign(pValue);
   }
};

//============================================================
// <T>���Ա���ֵ�����ݶ�Ϊ�ַ����Ĺ�ϣ����</T>
//
// @manager
// @history 091207 MAOCY ����
//============================================================
class MO_CM_DECLARE MAttributes{
public:
   typedef SAttributesEntry SEntry;
   typedef TAttributesIteratorC TIteratorC;
   typedef TAttributesIterator TIterator;
protected:
   TInt _count;
   SEntry* _pFirst;
   SEntry* _pLast;
   SEntry* _pUnused;
   TInt _entryCount;
   SEntry** _ppEntries;
protected:
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   MAttributes(){
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      MO_CLEAR(_pUnused);
      _entryCount = 0;
      MO_CLEAR(_ppEntries);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   MO_ABSTRACT ~MAttributes(){
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
   //------------------------------------------------------------
   // <T>����ָ�����Ƶ�����λ�á�</T>
   SEntry* EntryFind(TCharC* pName) const{
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
   SEntry* EntryFindValue(TCharC* pValue) const{
      // ���ݴ���ʱ
      if(_count > 0){
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            if(pEntry->valuePtr->Equals(pValue)){
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
   TCharC* operator[](TCharC* pName){
      SEntry* pEntry = EntryFind(pName);
      MO_ASSERT(pEntry);
      return pEntry->Value();
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
   // <T>������Ա�ֻ����������</T>
   TIteratorC IteratorC() const{
      return TAttributesIteratorC(_pFirst);
   }
   //------------------------------------------------------------
   // <T>�ж�ָ�������Ƿ���ڡ�</T>
   TBool Contains(TCharC* pName) const{
      return (NULL != EntryFind(pName));
   }
   //------------------------------------------------------------
   // <T>�ж�ָ�������Ƿ���ڡ�</T>
   TBool ContainsValue(TCharC* pValue) const{
      return (NULL != EntryFindValue(pValue));
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   TCharC* Find(TCharC* pName) const{
      SEntry* pEntry = EntryFind(pName);
      if(NULL != pEntry){
         return pEntry->Value();
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   TCharC* FindNvl(TCharC* pName, TCharC* pDefault) const{
      SEntry* pEntry = EntryFind(pName);
      if(NULL != pEntry){
         return pEntry->Value();
      }
      return pDefault;
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   TCharC* Get(TCharC* pName) const{
      SEntry* pEntry = EntryFind(pName);
      MO_ASSERT(pEntry);
      return pEntry->Value();
   }
   //------------------------------------------------------------
   // <T>���ָ�����Ƶ����ݡ�</T>
   TCharC* Search(TCharC* pValue) const{
      SEntry* pEntry = EntryFindValue(pValue);
      if(NULL != pEntry){
         return pEntry->Name();
      }
      return NULL;
   }
public:
   //------------------------------------------------------------
   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
   // ����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����Ϊ��ǰָ����С��</P>
   void EnsureSize(TInt size){
      if(NULL == _ppEntries) {
         _entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
         // ��һ���½�ʱ�����ɹ�ϣ��
         _ppEntries = MO_TYPES_ALLOC(SEntry*, _entryCount);
         RTypes<SEntry*>::Clear(_ppEntries, _entryCount);
      } else if (size > (_entryCount << 3)) {
         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
         SEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
         RTypes<SEntry*>::Clear(ppEntries, size);
         // ѭ��ȡ���ɵĽڵ��б����ݣ��Ƶ��µĽڵ��б���
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            // ����ǰ�ڵ�洢���½��Ľڵ��б���ȥ
            TInt index = pEntry->hash % size;
            pEntry->linkPtr = ppEntries[index];
            ppEntries[index] = pEntry;
            // ��ñ������һ���ڵ�ָ��
            pEntry = pEntry->nextPtr;
         }
         // �ͷžɽڵ��ڴ�
         MO_FREE(_ppEntries);
         // �����µĽڵ��б�
         _ppEntries = ppEntries;
         _entryCount = size;
      }
   }
   //------------------------------------------------------------
   // <T>����Դ��ϣ���ڵ�ȫ�����ݡ�</T>
   void Assign(const MAttributes& attributes){
      Clear();
      Append(attributes);
   }
   //------------------------------------------------------------
   // <T>׷��Դ��ϣ���ڵ�ȫ�����ݡ�</T>
   void Append(const MAttributes& attributes){
      TAttributesIterator iterator = attributes.IteratorC();
      while(iterator.Next()){
         Set(iterator.Name(), iterator.Value());
      }
   }
   //------------------------------------------------------------
   // <T>���������������ݡ�</T>
   void Set(TCharC* pName, TCharC* pValue){
      THashCode hash = RString::MakeHashCode(pName);
      TInt index = hash % _entryCount;
      // �������ݳ��ֵ�λ��
      SEntry* pEntry = _ppEntries[index];
      while(NULL != pEntry) {
         if(pEntry->hash == hash){
            if(pEntry->IsName(pName)){
               pEntry->valuePtr->Assign(pValue);
               return;
            }
         }
         pEntry = pEntry->linkPtr;
      }
      // ������Ʋ����ڣ�Ϊ�½��ڵ����ڴ�
      EnsureSize(_count + 1);
      pEntry = EntryAlloc();
      index = hash % _entryCount;
      pEntry->hash = hash;
      pEntry->linkPtr = _ppEntries[index];
      pEntry->SetName(pName);
      pEntry->SetValue(pValue);
      _count++;
      _ppEntries[index] = pEntry;
      // ׷�ӵ�����β��
      EntryPush(pEntry);
   }
   //------------------------------------------------------------
   TString Remove(TCharC* pName){
      THashCode hash = RString::MakeHashCode(pName);
      TInt index = hash % _entryCount;
      // �������ݳ��ֵ�λ��
      TString value;
      SEntry* pPrior = _ppEntries[index];
      SEntry* pEntry = pPrior;
      while(NULL != pEntry){
         if(pEntry->hash == hash){
            if(pEntry->IsName(pName)){
               value.AssignPointer(pEntry->valuePtr);
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
   // <T>������ݡ�</T>
   void Clear(){
      // �����нڵ�����Ϊδʹ��
      if(_count > 0){
         _pLast->nextPtr = _pUnused;
         _pUnused = _pFirst;
      }
      // ������
      MO_LIB_TYPES_CLEAR(SEntry*, _ppEntries, _entryCount);
      // �������
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
   }
   //------------------------------------------------------------
   // <T>�ͷ����ݡ�</T>
   void Release(){
      // �����нڵ�����Ϊδʹ��
      if(_count > 0){
         _pLast->nextPtr = _pUnused;
         _pUnused = _pFirst;
      }
      // ɾ�����нڵ�
      SEntry* pEntry = _pUnused;
      while(NULL != pEntry){
         SEntry* pNext = pEntry->nextPtr;
         this->EntryRelease(pEntry);
         pEntry = pNext;
      }
      // �������
      _count = 0;
      MO_CLEAR(_pFirst);
      MO_CLEAR(_pLast);
      MO_CLEAR(_pUnused);
      // �ͷŽڵ�����
      _entryCount = 0;
      MO_FREE(_ppEntries);
   }
   //------------------------------------------------------------
   // <T>��ö�������ʱ��Ϣ��</T>
   TString Dump() const{
      TString dump = TC("MAttributes{");
      dump.AppendInt(_count);
      if(_count > 0){
         SEntry* pEntry = _pFirst;
         while(NULL != pEntry){
            dump.Append(*pEntry->namePtr);
            dump.Append(TC("="));
            dump.Append(*pEntry->valuePtr);
            // ������һ��
            pEntry = pEntry->nextPtr;
            if(NULL != pEntry){
               dump.Append(',');
            }
         }
      }
      return dump;
   }
};

//============================================================
// <T>���Ա�</T>
//============================================================
class MO_CM_DECLARE TAttributes : public MAttributes{
public:
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   TAttributes(){
      EnsureSize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   TAttributes(TInt capacity){
      EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   MO_ABSTRACT ~TAttributes(){
      Release();
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      SEntry* pEntry = MO_TYPE_ALLOC(SEntry);
      MO_ASSERT(pEntry);
      MO_LIB_TYPE_CLEAR(SEntry, pEntry);
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ���ڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      if(NULL != pEntry){
         pEntry->Release();
      }
      MO_FREE(pEntry);
   }
};

//============================================================
// <T>���Ա�</T>
//============================================================
class MO_CM_DECLARE FAttributes :
      public FObject,
      public MAttributes{
public:
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FAttributes(){
      EnsureSize(MO_OBJECT_CAPACITY);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FAttributes(TInt capacity){
      EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   MO_ABSTRACT ~FAttributes(){
      Release();
   }
protected:
   //------------------------------------------------------------
   // <T>�½�һ���ڵ㡣</T>
   MO_OVERRIDE SEntry* EntryCreate(){
      SEntry* pEntry = MO_TYPE_ALLOC(SEntry);
      MO_ASSERT(pEntry);
      MO_LIB_TYPE_CLEAR(SEntry, pEntry);
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ���ڵ㡣</T>
   MO_OVERRIDE void EntryRelease(SEntry* pEntry){
      MO_ASSERT(pEntry);
      if(NULL != pEntry){
         pEntry->Release();
      }
      MO_FREE(pEntry);
   }
};

////============================================================
//// <T>ֻ�����Ա���ֵ�����ݶ�Ϊ�ַ����Ĺ�ϣ����</T>
////
//// @manager
//// @history 091207 MAOCY ����
////============================================================
//class MO_CM_DECLARE MNcAttributesC : public MEntriesC<SAttributesEntry>{
//public:
//   typedef SAttributesEntry SEntry;
//   typedef TAttributesIteratorC TIteratorC;
//protected:
//   TInt _entryCount;
//   SAttributesEntry** _ppEntries;
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
//   TCharC* operator[](TCharC* pName){
//      SAttributesEntry* pEntry = EntryFind(pName);
//      MO_ASSERT(pEntry);
//      return pEntry->Value();
//   }
//protected:
//   //------------------------------------------------------------
//   // <T>����ָ�����Ƶ�����λ�á�</T>
//   SAttributesEntry* EntryFind(TCharC* pName) const{
//      // ���ݴ���ʱ
//      if(_count > 0){
//         THashCode hash = RString::MakeNocaseHashCode(pName);
//         // �������Ƶ�����λ��
//         SAttributesEntry* pEntry = _ppEntries[hash % _entryCount];
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
//   SAttributesEntry* EntryFindValue(TCharC* pValue) const{
//      // ���ݴ���ʱ
//      if(_count > 0){
//         SAttributesEntry* pEntry = _pFirst;
//         while(NULL != pEntry){
//            if(pEntry->valuePtr->Equals(pValue)){
//               return pEntry;
//            }
//            pEntry = pEntry->nextPtr;
//         }
//      }
//      // δ�ҵ�ʱ���ؽ��
//      return NULL;
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
//      return (NULL != EntryFind(pName));
//   }
//   //------------------------------------------------------------
//   TBool ContainsValue(TCharC* pValue) const{
//      return (NULL != EntryFindValue(pValue));
//   }
//   //------------------------------------------------------------
//   // <T>���ָ�����Ƶ����ݡ�</T>
//   TCharC* Get(TCharC* pName) const{
//      SAttributesEntry* pEntry = EntryFind(pName);
//      MO_ASSERT(pEntry);
//      return pEntry->valuePtr->MemoryC();
//   }
//   //------------------------------------------------------------
//   // <T>����ָ�����Ƶ����ݡ�</T>
//   TCharC* Find(TCharC* pName) const{
//      SAttributesEntry* pEntry = EntryFind(pName);
//      if(NULL != pEntry){
//         return pEntry->valuePtr->MemoryC();
//      }
//      return NULL;
//   }
//   //------------------------------------------------------------
//   // <T>���ָ�����Ƶ����ݡ�</T>
//   TCharC* FindNvl(TCharC* pName, TCharC* pDefault) const{
//      SAttributesEntry* pEntry = EntryFind(pName);
//      if(NULL != pEntry){
//         return pEntry->valuePtr->MemoryC();
//      }
//      return pDefault;
//   }
//   //------------------------------------------------------------
//   // <T>���ָ�����Ƶ����ݡ�</T>
//   TCharC* Search(TCharC* pValue) const{
//      SAttributesEntry* pEntry = EntryFindValue(pValue);
//      if(NULL != pEntry){
//         return pEntry->namePtr->MemoryC();
//      }
//      return NULL;
//   }
//   //------------------------------------------------------------
//   // <T>������Ա�ֻ����������</T>
//   TAttributesIteratorC IteratorC() const{
//      return TAttributesIteratorC(_pFirst);
//   }
//   //------------------------------------------------------------
//   // <T>��ö�������ʱ��Ϣ��</T>
//   TString Dump() const{
//      TString dump = TC("MNcAttributesC{");
//      dump.AppendInt(_count);
//      if(_count > 0){
//         SAttributesEntry* pEntry = _pFirst;
//         while(NULL != pEntry){
//            dump.Append(*pEntry->namePtr);
//            dump.Append(TC("="));
//            dump.Append(*pEntry->valuePtr);
//            // ������һ��
//            pEntry = pEntry->nextPtr;
//            if(NULL != pEntry){
//               dump.Append(',');
//            }
//         }
//      }
//      return dump;
//   }
//};
//
////============================================================
//// ���Լ��ϣ���ֵ�����ݶ�Ϊ�ַ����Ĺ�ϣ��
////
//// @manager
//// @history 091207 MAOCY ����
////============================================================
//class MO_CM_DECLARE MNcAttributes : public MNcAttributesC{
//public:
//   typedef SAttributesEntry SEntry;
//protected:
//   SEntry* _pUnused;
//protected:
//   //------------------------------------------------------------
//   // <T>�ڲ���ʼ����</T>
//   inline void InnerInitialize(TInt size){
//      MNcAttributesC::InnerInitialize();
//      _pUnused = NULL;
//      EnsureSize(size);
//   }
//   //------------------------------------------------------------
//   // <T>�ڲ��ͷš�</T>
//   inline void InnerRelease(){
//      // �ͷŽڵ�
//      if(_count > 0){
//         // �����нڵ�����Ϊδʹ��
//         _pLast->pNext = _pUnused;
//         _pUnused = _pFirst;
//         // ɾ�����нڵ�
//         SEntry* pFind = _pUnused;
//         while(NULL != pFind){
//            SEntry* pNext = pFind;
//            MO_DELETE(pFind);
//            pFind = pNext;
//         }
//      }
//      // �ͷŽڵ�����
//      MO_FREE(_ppEntries);
//   }
//public:
//   //------------------------------------------------------------
//   // <T>ȷ����ǰ�����������ָ����С�����ݡ�</T>
//   // ����ϣ���Ǿɱ��8��ʱ��ʼ���䣬����2����</P>
//   void EnsureSize(TInt size){
//      if(NULL == _ppEntries) {
//         _entryCount = MO_LIB_MAX(size, MO_OBJECT_CAPACITY);
//         // ��һ���½�ʱ�����ɹ�ϣ��
//         _ppEntries = MO_TYPES_ALLOC(SEntry*, _entryCount);
//         RTypes<SEntry*>::Clear(_ppEntries, _entryCount);
//      } else if (size > (_entryCount << 3)) {
//         // �����ڴ�ʱ����
//         size = _entryCount + ((MO_LIB_MAX(_entryCount, size)) >> 1);
//         // ���������ڽڵ��б���8��ʱ����������ڵ��б�
//         SAttributesEntry** ppEntries = MO_TYPES_ALLOC(SEntry*, size);
//         RTypes<SEntry*>::Clear(ppEntries, size);
//         // ѭ��ȡ���ɵĽڵ��б����ݣ��Ƶ��µĽڵ��б���
//         SAttributesEntry* pEntry = _pFirst;
//         while(NULL == pEntry){
//            // ����ǰ�ڵ�洢���½��Ľڵ��б���ȥ
//            TInt index = pEntry->hash % size;
//            pEntry->linkPtr = ppEntries[index];
//            ppEntries[index] = pEntry;
//               // ��ñ������һ���ڵ�ָ��
//            pEntry = pEntry->linkPtr;
//         }
//         // �ͷžɽڵ��ڴ�
//         MO_FREE(_ppEntries);
//         // �����µĽڵ��б�
//         _ppEntries = ppEntries;
//         _entryCount = size;
//      }
//   }
//   //------------------------------------------------------------
//   // <T>����Դ��ϣ���ڵ�ȫ�����ݡ�</T>
//   void Assign(const MNcAttributesC& attributes){
//      Clear();
//      Append(attributes);
//   }
//   //------------------------------------------------------------
//   // <T>׷��Դ��ϣ���ڵ�ȫ�����ݡ�</T>
//   void Append(const MNcAttributesC& attributes){
//      TAttributesIterator iterator = attributes.IteratorC();
//      while(iterator.Next()){
//         Set(iterator.Name(), iterator.Value());
//      }
//   }
//   //------------------------------------------------------------
//   // <T>���������������ݡ�</T>
//   void Set(TCharC* pName, TCharC* pValue){
//      THashCode hash = RString::MakeNocaseHashCode(pName);
//      TInt index = hash % _entryCount;
//      // �������ݳ��ֵ�λ��
//      SEntry* pEntry = _ppEntries[index];
//      while(NULL != pEntry) {
//         if(pEntry->hash == hash){
//            if(pEntry->IsNameIgnoreCase(pName)){
//               pEntry->valuePtr->Assign(pValue);
//               return;
//            }
//         }
//         pEntry = pEntry->linkPtr;
//      }
//      // ������Ʋ����ڣ�Ϊ�½��ڵ����ڴ�
//      EnsureSize(_count + 1);
//      pEntry = MO_TYPE_ALLOC(SEntry);
//      index = hash % _entryCount;
//      pEntry->hash = hash;
//      pEntry->linkPtr = _ppEntries[index];
//      pEntry->namePtr->Assign(pName);
//      pEntry->valuePtr->Assign(pValue);
//      _count++;
//      _ppEntries[index] = pEntry;
//      // ׷�ӵ�����β��
//      EntryPush(pEntry);
//   }
//   //------------------------------------------------------------
//   // <T>�Ƴ�ָ�����Ƶ����ݡ�</T>
//   TString Remove(TCharC* pName){
//      THashCode hash = RString::MakeNocaseHashCode(pName);
//      TInt index = hash % _entryCount;
//      // �������ݳ��ֵ�λ��
//      TString value;
//      SAttributesEntry* pPrior = _ppEntries[index];
//      SAttributesEntry* pEntry = pPrior;
//      while(NULL != pEntry){
//         if(pEntry->hash == hash){
//            if(pEntry->IsNameIgnoreCase(pName)){
//               value.AssignPointer(pEntry->valuePtr);
//               if(pEntry == pPrior){
//                  // ��ǰ�����ǵ�һ������ʱ
//                  _ppEntries[index] = pEntry->linkPtr;
//               }else{
//                  // ��ǰ�����ǵ�һ������ʱ
//                  pPrior->pLink = pEntry->linkPtr;
//               }
//               // ɾ����ǰ�ڵ�
//               EntryRemove(pEntry);
//               break;
//            }
//         }
//         pPrior = pEntry;
//         pEntry = pEntry->linkPtr;
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
//// <T>���Ա����</T>
////============================================================
//class MO_CM_DECLARE TNcAttributes : public MNcAttributes{
//public:
//   //------------------------------------------------------------
//   // <T>�������Ա����</T>
//   TNcAttributes(){
//      InnerInitialize(MO_OBJECT_CAPACITY);
//   }
//   //------------------------------------------------------------
//   // <T>�������Ա����</T>
//   TNcAttributes(TInt capacity){
//      InnerInitialize(capacity);
//   }
//};
//
////============================================================
//// <T>���Ա����</T>
////============================================================
//class MO_CM_DECLARE FNcAttributes : public MNcAttributes{
//public:
//   //------------------------------------------------------------
//   // <T>�������Ա�</T>
//   FNcAttributes(){
//      InnerInitialize(MO_OBJECT_CAPACITY);
//   }
//   //------------------------------------------------------------
//   // <T>�������Ա�</T>
//   FNcAttributes(TInt capacity){
//      InnerInitialize(capacity);
//   }
//};

MO_NAMESPACE_END

#endif // __MO_CM_ATTRIBUTES_H__
