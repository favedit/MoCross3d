#ifndef __MO_CM_LOOPER_H__
#define __MO_CM_LOOPER_H__

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
struct SLooperEntry{
   SLooperEntry* pPrior;
   SLooperEntry* pNext;
   T value;
};

//===========================================================./cc
// <T>ֻ������ĵ�������</T>
//
// @tool
//============================================================
template <typename T>
class TLooperIteratorC{
public:
   typedef SLooperEntry<T> SEntry;
protected:
   TInt _position;
   TInt _count;
   SEntry* _pLooper;
   SEntry* _pCurrent;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TLooperIteratorC(){
      _position = -1;
      _count = 0;
      MO_CLEAR(_pLooper);
      MO_CLEAR(_pCurrent);
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TLooperIteratorC(const TLooperIteratorC& iterator){
      _position = iterator._position;
      _count = iterator._count;
      _pLooper = iterator._pLooper;
      _pCurrent = iterator._pCurrent;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TLooperIteratorC(TInt count, SEntry* pCurrent){
      _position = -1;
      _count = count;
      _pLooper = pCurrent;
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
            this->_pCurrent = this->_pLooper;
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
            this->_pCurrent = this->_pLooper;
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
class TLooperIterator : public TLooperIteratorC<T>{
public:
   typedef SLooperEntry<T> SEntry;
public:
   //------------------------------------------------------------
   // <T>���������������</T>
   TLooperIterator(){
   }
   //------------------------------------------------------------
   // <T>���������������</T>
   TLooperIterator(const TLooperIteratorC<T>& iterator) :
         TLooperIteratorC<T>(iterator){
   }
   //------------------------------------------------------------
   // <T>���������������</T>
   TLooperIterator(SEntry* pEntry) :
         TLooperIteratorC<T>(pEntry){
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
class MLooper{
public:
   typedef SLooperEntry<T> SEntry;
   typedef TLooperIteratorC<T> TIteratorC;
protected:
   TInt _version;
   TInt _count;
   TInt _recordCount;
   SEntry* _pCurrent;
   SEntry* _pUnused;
public:
   //------------------------------------------------------------
   // <T>����ѭ������</T>
   MLooper(){
      _version = 0;
      _count = 0;
      _recordCount = -1;
      MO_CLEAR(_pCurrent);
      MO_CLEAR(_pUnused);
   }
   //------------------------------------------------------------
   // <T>����ѭ������</T>
   ~MLooper(){
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
      if(NULL == pEntry){
         pEntry = MO_TYPE_ALLOC(SEntry);
      }else{
         _pUnused = pEntry->pNext;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>ɾ��һ����ڡ�</T>
   void InnerFree(SEntry* pEntry){
      if(NULL != pEntry){
         pEntry->pNext = _pUnused;
         _pUnused = pEntry;
      }
   }
   //------------------------------------------------------------
   // <T>ɾ��һ����ڡ�</T>
   void InnerDelete(SEntry* pEntry){
      if(NULL != pEntry){
         MO_FREE(pEntry);
      }
   }
   //------------------------------------------------------------
   // <T>����һ����ڵ���ǰ�б�</T>
   void InnerPush(SEntry* pEntry){
      if(NULL != pEntry){
         if(NULL != _pCurrent){
            SEntry* pPrior = _pCurrent->pPrior;
            pEntry->pPrior = pPrior;
            pEntry->pNext = _pCurrent;
            pPrior->pNext = pEntry;
            _pCurrent->pPrior = pEntry;
         }else{
            pEntry->pPrior = pEntry;
            pEntry->pNext = pEntry;
            _pCurrent = pEntry;
         }
         _count++;
      }
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�б�ɾ��һ����ڡ�</T>
   void InnerRemove(SEntry* pEntry){
      if(NULL != pEntry){
         // ɾ�����
         SEntry* pPrior = pEntry->pPrior;
         SEntry* pNext = pEntry->pNext;
         pPrior->pNext = pNext;
         pNext->pPrior = pPrior;
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
   T InnerRemoveCurrent(){
      T value = NULL;
      if(_count > 0){
         // �������
         value = _pCurrent->value;
         // �Ƴ��ڵ�
         InnerRemove(_pCurrent);
      }
      return value;
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�б��Ƴ�һ�����ݡ�</T>
   void InnerRemoveValue(T value){
      if(_count > 0){
         // ɾ���׸�����
         if(_pCurrent->value == value){
            InnerRemoveCurrent();
            return;
         }
         // ɾ����������
         SEntry* pCurrent = _pCurrent; 
         SEntry* pNext = _pCurrent->pNext;
         while(pNext != pCurrent){
            if(pNext->value == value){
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
   TIteratorC IteratorC() const{
      return TIteratorC(this->_count, this->_pCurrent);
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ����ָ�����Ƶ�ֵ��</T>
   TBool Contains(T value){
      if(_pCurrent){
         SEntry* pEntry = _pCurrent;
         for(TInt n = 0; n < _count; n++){
            if(pEntry->value == value){
               return ETrue;
            }
            pEntry = pEntry->pNext;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>��������ĵ�ǰλ�õ����ݡ�</T>
   T Current(){
      if(NULL != _pCurrent){
         return _pCurrent->value;
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����������һ�����ݡ�</T>
   T Next(){
      // �ƶ���ǰ��
      if(NULL != _pCurrent){
         _pCurrent = _pCurrent->pNext;
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
   void Push(T value){
      _version++;
      SEntry* pEntry = this->InnerCreate();
      pEntry->value = value;
      this->InnerPush(pEntry);
   }
   //------------------------------------------------------------
   // <T>����һ��Ψһ���ݵ�β����</T>
   void PushUnique(T value){
      if(NULL != value){
         TBool exists = Contains(value);
         if(!exists){
            Push(value);
         }
      }
   }
   //------------------------------------------------------------
   // <T>�Ƴ���ǰ��Ԫ�أ������ظ�Ԫ�ص����ݡ�</T>
   T RemoveCurrent(){
      _version++;
      return this->InnerRemoveCurrent();
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�б��Ƴ�һ�����ݡ�</T>
   void Remove(T value){
      _version++;
      this->InnerRemoveValue(value);
   }
   //------------------------------------------------------------
   // <T>���ѭ����������Ԫ�ء�</T>
   void Clear(){
      _version++;
      if(_pCurrent){
         _pCurrent->pPrior->pNext = NULL;
         _pCurrent->pPrior = this->_pUnused;
         this->_pUnused = _pCurrent;
         _pCurrent = NULL;
      }
      _count = 0;
   }
};

//===========================================================./cc
// <T>ֻ������ĵ�������</T>
//
// @tool
//============================================================
template <typename T>
class TLooperRefer{
public:
   typedef SLooperEntry<T> SEntry;
   friend class MLooper<T>;
protected:
   MLooper<T>* _pLooper;
   TInt _version;
   SEntry* _pCurrent;
   TInt _recordCount;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TLooperRefer(){
      MO_CLEAR(_pLooper);
      _version = 0;
      MO_CLEAR(_pCurrent);
      _recordCount = -1;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TLooperRefer(MLooper<T>* pLooper){
      Link(pLooper);
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���顣</T>
   MO_INLINE void InnerCheck(){
      TInt version = this->_pLooper->NativeVersion();
      if(this->_version != version){
         this->_version = version;
         this->_pCurrent = this->_pLooper->NativeCurrent();
         this->_recordCount = this->_pLooper->Count();
      }
   }
public:
   //------------------------------------------------------------
   // <T>����ѭ������</T>
   MO_INLINE void Link(MLooper<T>* pLooper){
      MO_ASSERT(pLooper);
      this->_pLooper = pLooper;
      this->_version = pLooper->NativeVersion();
      this->_pCurrent = pLooper->NativeCurrent();
      this->_recordCount = -1;
   }
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      MO_ASSERT(this->_pLooper);
      return this->_pLooper->isEmpty();
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Count() const{
      MO_ASSERT(this->_pLooper);
      return this->_pLooper->Count();
   }
   //------------------------------------------------------------
   // <T>��¼��ǰ��¼�㡣</T>
   MO_INLINE void Record(){
      // �ڲ����
      InnerCheck()();
      // ��¼λ��
      this->_recordCount = this->_pLooper->Count();
   }
   //------------------------------------------------------------
   // <T>������ǰ��¼�㡣</T>
   MO_INLINE void Unrecord(){
      this->_recordCount = -1;
   }
public:
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE T Current(){
      // ��ö���
      if(NULL != _pCurrent){
         return _pCurrent->value;
      }
      return NULL;
   }
   //------------------------------------------------------------
   //<T>�ƶ�����һ��λ�á�</T>
   MO_INLINE T Next(){
      // �ƶ���ǰ��
      if(NULL != _pCurrent){
         _pCurrent = _pCurrent->pNext;
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
};

//============================================================
// <T>�䳤ջ��д����</T>
//
// @tool
//============================================================
template <typename T>
class TLooper : public MLooper<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   TLooper(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   ~TLooper(){
   }
};

//============================================================
// <T>�䳤�Ѷ�д����</T>
//
// @tool
//============================================================
template <typename T>
class FLooper :
      public FObject,
      public MLooper<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤��д����</T>
   FLooper(){
   }
   //------------------------------------------------------------
   // <T>�����䳤��д����</T>
   ~FLooper(){
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_LOOPER_H__
