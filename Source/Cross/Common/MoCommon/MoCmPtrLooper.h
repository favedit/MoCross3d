#ifndef __MO_CM_PTR_LOOPER_H__
#define __MO_CM_PTR_LOOPER_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_ENTRY_H__
#include "MoCmEntry.h"
#endif // __MO_CM_ENTRY_H__

#define MO_COMPLIST_THRESHOLD 8

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ľڵ㶨�塣</T>
//
// @struct
//============================================================
template <typename T>
struct SPtrLooperEntry
{
public:
   SPtrLooperEntry* priorPtr;
   SPtrLooperEntry* nextPtr;
   GPtr<T> value;
public:
   //------------------------------------------------------------
   // <T>��������Ľڵ㶨�塣</T>
   MO_INLINE SPtrLooperEntry(){
      MO_CLEAR(priorPtr);
      MO_CLEAR(nextPtr);
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      MO_CLEAR(priorPtr);
      MO_CLEAR(nextPtr);
      value = NULL;
   }
};

//============================================================
// <T>ֻ������ĵ�������</T>
//
// @tool
//============================================================
template <typename T>
class TPtrLooperIteratorC{
public:
   typedef SPtrLooperEntry<T> SEntry;
protected:
   TInt _position;
   TInt _count;
   SEntry* _pPtrLooper;
   SEntry* _pCurrent;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TPtrLooperIteratorC(){
      _position = -1;
      _count = 0;
      MO_CLEAR(_pPtrLooper);
      MO_CLEAR(_pCurrent);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TPtrLooperIteratorC(const TPtrLooperIteratorC& iterator){
      _position = iterator._position;
      _count = iterator._count;
      _pPtrLooper = iterator._pPtrLooper;
      _pCurrent = iterator._pCurrent;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TPtrLooperIteratorC(TInt count, SEntry* pCurrent){
      _position = -1;
      _count = count;
      _pPtrLooper = pCurrent;
      MO_CLEAR(_pCurrent);
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T& operator *() const{
      MO_ASSERT(this->_pCurrent);
      return this->_pCurrent->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T operator->() const{
      MO_ASSERT(this->_pCurrent);
      return this->_pCurrent->value;
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return (0 == this->_count);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      if(this->_count > 0){
         return (this->_position < this->_count);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   //<T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      if(this->_position < this->_count){
         if(NULL == this->_pCurrent){
            this->_pCurrent = this->_pPtrLooper;
         }else{
            this->_pCurrent = this->_pCurrent->pNext;
         }
         this->_position++;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      if(this->_count > 0){
         return (this->_position < this->_count);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      if(this->_position < this->_count){
         if(NULL == this->_pCurrent){
            this->_pCurrent = this->_pPtrLooper;
         }else{
            this->_pCurrent = this->_pCurrent->pPrior;
         }
         this->_position++;
         return ETrue;
      }
      return EFalse;
   }
public:
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T value){
      MO_ASSERT(this->_pCurrent);
      return this->_pCurrent->value == value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T GetC() const{
      MO_ASSERT(this->_pCurrent);
      return this->_pCurrent->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T Get(){
      MO_ASSERT(this->_pCurrent);
      return this->_pCurrent->value;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   template <typename C>
   MO_INLINE C Get(){
      MO_ASSERT(this->_pCurrent);
      return (C)this->_pCurrent->value;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      this->_position = -1;
      this->_pCurrent = NULL;
   }
};

//============================================================
// <T>��д����ĵ�������</T>
//
// @tool
//============================================================
template <typename T>
class TPtrLooperIterator : public TPtrLooperIteratorC<T>{
public:
   typedef SPtrLooperEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>���������������</T>
   TPtrLooperIterator(){
   }
   //------------------------------------------------------------
   // <T>���������������</T>
   TPtrLooperIterator(const TPtrLooperIteratorC<T>& iterator) :
         TPtrLooperIteratorC<T>(iterator){
   }
   //------------------------------------------------------------
   // <T>���������������</T>
   TPtrLooperIterator(SEntry* pEntry) :
         TPtrLooperIteratorC<T>(pEntry){
   }
public:
   //------------------------------------------------------------
   // <T>���õ�ǰλ�õ��������ơ�</T>
   MO_INLINE void Set(T value) const{
      MO_ASSERT(this->_pCurrent);
      this->_pCurrent->value = value;
   }
};

//============================================================
// <T>ѭ������</T>
//
// @history 121229 MAOCY ����
//================ ============================================
template <typename T>
class MPtrLooper{
public:
   typedef SPtrLooperEntry<T> SEntry;
   typedef TPtrLooperIteratorC<T> TIteratorC;
protected:
   TInt _version;
   TInt _count;
   TInt _recordCount;
   SEntry* _pCurrent;
   SEntry* _pUnused;
public:
   //------------------------------------------------------------
   // <T>����ѭ������</T>
   MPtrLooper(){
      _version = 0;
      _count = 0;
      _recordCount = -1;
      MO_CLEAR(_pCurrent);
      MO_CLEAR(_pUnused);
   }
   //------------------------------------------------------------
   // <T>����ѭ������</T>
   ~MPtrLooper(){
   }
public:
   //------------------------------------------------------------
   // <T>��ñ��ذ汾��</T>
   MO_INLINE TInt NativeVersion(){
      return _version;
   }
   //------------------------------------------------------------
   // <T>��ñ��ؽڵ㡣</T>
   MO_INLINE SEntry* NativeCurrent(){
      return _pCurrent;
   }
protected:
   //------------------------------------------------------------
   // <T>����һ����ڶ���</T>
   SEntry* InnerCreate(){
      SEntry* pEntry = _pUnused;
      if(pEntry == NULL){
         pEntry = MO_TYPE_CREATE(SEntry);
      }else{
         _pUnused = pEntry->nextPtr;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>ɾ��һ����ڡ�</T>
   void InnerFree(SEntry* pEntry){
      if(pEntry != NULL){
         pEntry->Reset();
         pEntry->nextPtr = _pUnused;
         _pUnused = pEntry;
      }
   }
   //------------------------------------------------------------
   // <T>ɾ��һ����ڡ�</T>
   void InnerDelete(SEntry* pEntry){
      if(pEntry != NULL){
         MO_DELETE(pEntry);
      }
   }
   //------------------------------------------------------------
   // <T>����һ����ڵ���ǰ�б�</T>
   void InnerPush(SEntry* pEntry){
      if(pEntry != NULL){
         if(_pCurrent != NULL){
            SEntry* pPrior = _pCurrent->priorPtr;
            pEntry->priorPtr = pPrior;
            pEntry->nextPtr = _pCurrent;
            pPrior->nextPtr = pEntry;
            _pCurrent->priorPtr = pEntry;
         }else{
            pEntry->priorPtr = pEntry;
            pEntry->nextPtr = pEntry;
            _pCurrent = pEntry;
         }
         _count++;
      }
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�б�ɾ��һ����ڡ�</T>
   void InnerRemove(SEntry* pEntry){
      if(pEntry != NULL){
         // ɾ�����
         SEntry* pPrior = pEntry->priorPtr;
         SEntry* pNext = pEntry->nextPtr;
         pPrior->nextPtr = pNext;
         pNext->priorPtr = pPrior;
         // ��������
         _count--;
         if(_count > 0){
            _pCurrent = pNext;
         }else{
            _pCurrent = NULL;
         }
         // �ͷ����
         this->InnerFree(pEntry);
      }
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�б��Ƴ���ǰ���ݡ�</T>
   T* InnerRemoveCurrent(){
      T* pValue = NULL;
      if(_count > 0){
         // �������
         pValue = _pCurrent->value;
         // �Ƴ��ڵ�
         InnerRemove(_pCurrent);
      }
      return pValue;
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�б��Ƴ�һ�����ݡ�</T>
   void InnerRemoveValue(T* pValue){
      if(_count > 0){
         // ɾ���׸�����
         if(_pCurrent->value == pValue){
            InnerRemoveCurrent();
            return;
         }
         // ɾ����������
         SEntry* pCurrent = _pCurrent; 
         SEntry* pNext = _pCurrent->pNext;
         while(pNext != pCurrent){
            if(pNext->value == pValue){
               this->InnerRemove(pNext);
               // ���õ�ԭʼλ��
               _pCurrent = pCurrent;
               return;
            }
            pNext = pNext->pNext;
         }
      }
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�����Ƿ�Ϊ��</T>
   MO_INLINE TBool isEmpty(){
      return (0 == this->_count);
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Count() const{
      return this->_count;
   }
   //------------------------------------------------------------
   // <T>��¼��ǰ��¼�㡣</T>
   MO_INLINE void Record(){
      this->_recordCount = this->_count;
   }
   //------------------------------------------------------------
   // <T>������ǰ��¼�㡣</T>
   MO_INLINE void Unrecord(){
      this->_recordCount = -1;
   }
public:
   //------------------------------------------------------------
   // <T>�����λ�õ�ֻ�����ݵ�������</T>
   MO_INLINE TIteratorC IteratorC() const{
      return TIteratorC(this->_count, this->_pCurrent);
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ����ָ�����Ƶ�ֵ��</T>
   TBool Contains(T* pValue){
      if(_pCurrent){
         SEntry* pEntry = _pCurrent;
         for(TInt n = 0; n < _count; n++){
            if(pEntry->value == pValue){
               return ETrue;
            }
            pEntry = pEntry->pNext;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>��������ĵ�ǰλ�õ����ݡ�</T>
   T* Current(){
      if(_pCurrent != NULL){
         return _pCurrent->value;
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����������һ�����ݡ�</T>
   T* Next(){
      // �ƶ���ǰ��
      if(_pCurrent != NULL){
         _pCurrent = _pCurrent->nextPtr;
      }
      // ����¼�㣨��ֻ��һ��Ԫ��ʱ����¼����Ч��
      if(_recordCount > 0){
         _recordCount--;
      }else if(_recordCount == 0){
         return NULL;
      }
      // ��������
      if(NULL != _pCurrent){
         return _pCurrent->value;
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����һ�����ݵ�β����</T>
   void Push(T* pValue){
      _version++;
      SEntry* pEntry = this->InnerCreate();
      pEntry->value = pValue;
      this->InnerPush(pEntry);
   }
   //------------------------------------------------------------
   // <T>����һ��Ψһ���ݵ�β����</T>
   void PushUnique(T* pValue){
      if(pValue != NULL){
         TBool exists = Contains(pValue);
         if(!exists){
            Push(pValue);
         }
      }
   }
   //------------------------------------------------------------
   // <T>�Ƴ���ǰ��Ԫ�أ������ظ�Ԫ�ص����ݡ�</T>
   T* RemoveCurrent(){
      _version++;
      return this->InnerRemoveCurrent();
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�б��Ƴ�һ�����ݡ�</T>
   void Remove(T* pValue){
      _version++;
      this->InnerRemoveValue(pValue);
   }
   //------------------------------------------------------------
   // <T>���ѭ����������Ԫ�ء�</T>
   void Clear(){
      _version++;
      if(_pCurrent){
         _pCurrent->priorPtr->nextPtr = NULL;
         _pCurrent->priorPtr = this->_pUnused;
         this->_pUnused = _pCurrent;
         _pCurrent = NULL;
      }
      _count = 0;
   }
};

//============================================================
// <T>�䳤ջ��д����</T>
//
// @tool
//============================================================
template <typename T>
class GPtrLooper : public MPtrLooper<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   GPtrLooper(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   ~GPtrLooper(){
   }
};

//============================================================
// <T>�䳤ջ��д����</T>
//
// @tool
//============================================================
template <typename T>
class TPtrLooper : public MPtrLooper<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   TPtrLooper(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   ~TPtrLooper(){
   }
};

//============================================================
// <T>�䳤ջ��д����</T>
//
// @tool
//============================================================
template <typename T>
class FPtrLooper : public MPtrLooper<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   FPtrLooper(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   ~FPtrLooper(){
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_PTR_LOOPER_H__
