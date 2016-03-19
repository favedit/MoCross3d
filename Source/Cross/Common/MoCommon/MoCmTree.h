#ifndef __MO_CM_TREE_H__
#define __MO_CM_TREE_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_ENTRY_H__
#include "MoCmEntry.h"
#endif // __MO_CM_ENTRY_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ϣ���϶���</T>
//============================================================
template <typename N, typename V>
struct STreeEntry{
   STreeEntry* pPrior;
   STreeEntry* pNext;
   STreeEntry** ppNodes;
   TBool exists;
   N code;
   V value;
};

//============================================================
// <T>ֻ�������������</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TTreeIteratorC : public MLinkedIteratorC< STreeEntry<N, V>* >{
public:
   typedef STreeEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TTreeIteratorC(){
      Initialize((SEntry*)NULL);
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TTreeIteratorC(const TTreeIteratorC& iterator){
      Initialize(iterator._pStart);
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TTreeIteratorC(SEntry* pEntry){
      Initialize(pEntry);
   }
public:
   //------------------------------------------------------------
   // �жϵ�ǰλ���Ƿ����
   inline EBoolean operator==(const TTreeIteratorC& iterator) const{
      if((NULL != this->_pEntry) && (NULL != iterator._pEntry)){
         return this->_pEntry->value == iterator._pEntry->value;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // �жϵ�ǰλ���Ƿ����
   inline EBoolean operator!=(const TTreeIteratorC& iterator) const{
      if((NULL != this->_pEntry) && (NULL != iterator._pEntry)){
         return this->_pEntry->value != iterator._pEntry->value;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline const V& operator *() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->value;
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline const V* operator->() const{
      MO_ASSERT(this->_pEntry);
      return &(this->_pEntry->value);
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline N Code() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->code;
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline V Value() const{
      MO_ASSERT(this->_pEntry);
      return this->_pEntry->value;
   }
};

//============================================================
// <T>��д�����������</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TTreeIterator : public TTreeIteratorC<N, V>{
public:
   typedef STreeEntry<N, V> SEntry;
public:
   //------------------------------------------------------------
   // �������������
   TTreeIterator(){
   }
   //------------------------------------------------------------
   // �������������
   TTreeIterator(const TTreeIterator& iterator) :
         TTreeIteratorC<N, V>(iterator){
   }
   //------------------------------------------------------------
   // �������������
   TTreeIterator(SEntry* pEntry) :
         TTreeIteratorC<N, V>(pEntry){
   }
public:
   //------------------------------------------------------------
   // ���õ�ǰλ�õ�����
   inline void SetValue(V value) const{
      MO_ASSERT(this->_pEntry);
      this->_pEntry->value = value;
   }
};

//============================================================
// <T>ֻ����Ŀ¼��</T>
// <P>Ϊ�˼������߲�������Ϊ��������</P>
//
// @history 100103 MAOCY ����
//============================================================
template <typename N, typename V>
class MTreeC : public MLinkedEntryC< STreeEntry<N, V>* >{
public:
   typedef STreeEntry<N, V> SEntry;
   typedef MLinkedEntryC<SEntry*> MLinkedC;
   typedef TTreeIteratorC<N, V> TIteratorC;
protected:
   TInt _level;
   SEntry* _pRoot;
protected:
   //------------------------------------------------------------
   // �ڲ���ʼ��
   inline void Initialize(TInt level){
      MO_ASSERT(level > 1);
      MLinkedC::Initialize();
      _level = level;
      _pRoot = NULL;
   }
public:
   //------------------------------------------------------------
   // <T>�Ƚϵ�ǰ�����ݺ�ָ�������д���������Ƿ���ȡ�</T>
   EBoolean operator==(const MTreeC<N, V>& tree) const{
      return Equals(tree);
   }
   //------------------------------------------------------------
   // <T>�Ƚϵ�ǰ�����ݺ�ָ�������д���������Ƿ���ȡ�</T>
   EBoolean operator!=(const MTreeC<N, V>& tree) const{
      return !Equals(tree);
   }
   //------------------------------------------------------------
   inline V operator[](N code) const{
      SEntry* pEntry = EntryFind(code);
      MO_ASSERT(pEntry);
      return pEntry->value;
   }
protected:
   //------------------------------------------------------------
   // ���ָ��λ�õ�����
   inline SEntry* EntryFind(N code) const{
      // ���ָ��λ������
      SEntry* pEntry = _pRoot;
      while(code > 0){
         pEntry = pEntry->ppNodes[code % (1<<_level)];
         if(NULL == pEntry){
            return NULL;
         }
         code = code >> _level;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // �������ʹ���еĽڵ㣬����δʹ��������ѭ��ʹ��
   inline void EntryClear(){
      // ������нڵ㣬�����ҵ����һ���ڵ�
      SEntry* pEntry = this->_pFirst;
      while(NULL != pEntry){
         if(NULL != pEntry->ppNodes){
            RTypes<SEntry*>::Clear(pEntry->ppNodes, 1 << _level);
         }
         pEntry = pEntry->pNext;
      }
      // ��ʹ�ýڵ�ȫ��������սڵ�
      MLinkedEntryC<SEntry*>::EntryClear();
      // �������������
      _pRoot = NULL;
   }
public:
   //------------------------------------------------------------
   // ��ò��С
   TInt Level() const{
      return _level;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ����ָ�����롣</T>
   TBool Constains(N code) const{
      SEntry* pEntry = EntryFind(code);
      return (NULL != pEntry) ? pEntry->exists : EFalse;
   }
   //------------------------------------------------------------
   // <T>�Ƚϵ�ǰ�����ݺ�ָ�������д���������Ƿ���ȡ�</T>
   TBool Equals(const MTreeC<N, V>& tree) const{
      // �Ƚ�����
      if(this->_count == tree._count){
         // �Ƚ�������Ŀ
         TIteratorC iterator = tree.IteratorC();
         while(iterator.Next()){
            SEntry* pEntry = EntryFind(iterator.Code());
            if(NULL == pEntry){
               return EFalse;
            }
            if(pEntry->value != iterator.value){
               return EFalse;
            }
         }
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>���ָ����������ݡ�</T>
   V Get(N code) const{
      SEntry* pEntry = EntryFind(code);
      MO_ASSERT(pEntry);
      MO_ASSERT(pEntry->exists);
      return pEntry->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰ����ֻ����������</T>
   TIteratorC IteratorC() const{
      return TIteratorC(this->_pFirst);
   }
};

//============================================================
// <T>��ϣ���϶���</T>
//============================================================
template <typename N, typename V>
class MTree : public MTreeC<N, V>{
public:
   typedef STreeEntry<N, V> SEntry;
   typedef TTreeIterator<N, V> TIterator;
protected:
   //------------------------------------------------------------
   // �ڲ���ʼ��
   inline void Initialize(TInt level){
      MTreeC<N, V>::Initialize(level);
      this->_level = level;
      this->_pRoot = EntryAlloc();
   }
protected:
   //------------------------------------------------------------
   // �ռ�
   SEntry* EntryAlloc(){
      SEntry* pEntry = this->_pUnused;
      if(NULL == pEntry){
         pEntry = MO_TYPE_ALLOC(SEntry);
      }else{
         this->_pUnused = pEntry->pNext;
      }
      pEntry->exists = EFalse;
      EntryPush(pEntry);
      return pEntry;
   }
   //------------------------------------------------------------
   // �ͷ����нڵ�
   void EntryRelease(){
      SEntry* pEntry = this->_pFirst;
      while(NULL != pEntry){
         // �ͷŵ�ǰ�ڵ�
         if(NULL != pEntry->ppNodes){
            MO_FREE(pEntry->ppNodes);
         }
         // ������һ���ڵ�
         SEntry* pNext = pEntry->pNext;
         delete pEntry;
         pEntry = pNext;
      }
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰ����ֻ����������</T>
   TIterator Iterator() const{
      return TIterator(this->_pFirst);
   }
   //------------------------------------------------------------------------
   // ����һ��������ǰ���С�
   void Assign(const MTreeC<N, V>& tree){
      Clear();
      Append(tree);
   }
   //------------------------------------------------------------------------
   // ׷��һ��������ǰ���С�
   void Append(const MTreeC<N, V>& tree){
      TTreeIteratorC<N, V> iterator = tree.IteratorC();
      while(iterator.Next()){
         Set(iterator.Code(), iterator.Value());
      }
   }
   //------------------------------------------------------------
   // ��ָ����������ݴ洢��ָ���ڵ�
   void Set(N code, V value){
      N find = code;
      SEntry* pFind = this->_pRoot;
      SEntry* pEntry = this->_pRoot;
      // ѭ������
      while(find > 0){
         TInt index = find % (1 << this->_level);
         find = find >> this->_level;
         // ���ڵ��ڲ�
         if(NULL == pEntry->ppNodes){
            TInt size = 1 << this->_level;
            pEntry->ppNodes = MO_TYPES_ALLOC(SEntry*, size);
            RTypes<SEntry*>::Clear(pEntry->ppNodes, size);
         }
         // ���Ӵ洢�ڵ�
         pFind = pEntry->ppNodes[index];
         if(NULL == pFind){
            pFind = EntryAlloc();
            pEntry->ppNodes[index] = pFind;
         }
         pEntry = pFind;
      }
      // ������������
      pFind->exists = ETrue;
      pFind->code = code;
      pFind->value = value;
   }
   //------------------------------------------------------------
   // ��ָ����������ݴ洢��ָ���ڵ�
   void Remove(N code){
      SEntry* pEntry = EntryFind(code);
      MO_ASSERT(pEntry);
      // ��ɾ���ڵ㣬�����ݱ�־����Ϊ��
      pEntry->exists = EFalse;
   }
   //------------------------------------------------------------
   // �����Ŀ¼���нڵ�
   void Clear(){
      this->EntryClear();
      this->_pRoot = EntryAlloc();
   }
};

//============================================================
// <T>�䳤ջ����</T>
//
// @tool
//============================================================
template <typename N, typename V>
class TTree : public MTree<N, V>{
public:
   //------------------------------------------------------------
   // ������
   TTree(TInt level){
      this->Initialize(level);
   }
   //------------------------------------------------------------
   // ������
   TTree(const MTreeC<N, V>& tree){
      this->Initialize(tree.Level());
      this->Append(tree);
   }
   //------------------------------------------------------------
   // ������
   ~TTree(){
      this->EntryRelease();
   }
public:
   //------------------------------------------------------------------------
   // ׷��һ��������ǰ�����С�
   void operator=(const MTreeC<N, V>& tree){
      this->Assign(tree);
   }
};

//============================================================
// <T>�䳤������</T>
//
// @tool
//============================================================
template <typename N, typename V>
class FTree : public MTree<N, V>{
public:
   //------------------------------------------------------------
   // ��������
   FTree(TInt level){
      this->Initialize(level);
   }
   //------------------------------------------------------------
   // ��������
   FTree(const MTreeC<N, V>& tree){
      this->Initialize(tree.Level());
      this->Append(tree);
   }
   //------------------------------------------------------------
   // ������
   ~FTree(){
   }
public:
   //------------------------------------------------------------------------
   // ׷��һ��������ǰ�����С�
   void operator=(const MTreeC<N, V>& tree){
      this->Assign(tree);
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_TREE_H__
