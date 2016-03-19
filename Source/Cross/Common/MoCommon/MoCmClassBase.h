//============================================================
// <T>�߳���������</T>
//============================================================
#ifndef __MO_CM_CLASSBASE_H__
#define __MO_CM_CLASSBASE_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_LOOPER_H__
#include "MoCmLooper.h"
#endif // __MO_CM_LOOPER_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

#ifndef __MO_CM_DICTIONARY_H__
#include "MoCmDictionary.h"
#endif // __MO_CM_DICTIONARY_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ඨ�塣</T>
class FClass;
class FInstance;
typedef MO_CM_DECLARE TList<FInstance*> TInstanceList;
typedef MO_CM_DECLARE TLooper<FInstance*> TInstanceLooper;
typedef MO_CM_DECLARE FDictionary<FInstance*> FInstanceDictionary;

//============================================================
// <T>����Ϣ���塣</T>
// <P>������ʽ��N2MO21FConfigurationConsoleE��</P>
//============================================================
class MO_CM_DECLARE TClassInfo{
protected:
   TFsName _space;
   TFsName _name;
   TFsName _fullName;
public:
   TClassInfo();
   TClassInfo(TChar8C* pValue);
   TClassInfo(TChar16C* pValue);
   MO_ABSTRACT ~TClassInfo();
public:
   //------------------------------------------------------------
   // <T>��������ռ䡣</T>
   MO_INLINE TCharC* Space(){
      return _space;
   }
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>���ȫ�ơ�</T>
   MO_INLINE TCharC* FullName(){
      return _fullName.MemoryC();
   }
public:
   TBool Parse(TCharC* pValue);
};

//============================================================
// <T>�����</T>
//
// @class
// @history 140217 MAOCY ����
//============================================================
class MO_CM_DECLARE FClass : public FBase{
protected:
   TInt _looperLimit;
   TCharC* _pParentClassName;
   FClass* _pParentClass;
   TCharC* _pName;
   TInt _memorySize;
   TInt64 _activeCount;
   TInt64 _allocTotal;
   TInstanceList _pool;
   TInstanceLooper _looper;
public:
   FClass();
   MO_ABSTRACT ~FClass();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����ơ�</T>
   MO_INLINE TBool IsName(TCharC* pName){
      return RString::Equals(_pName, pName);
   }
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _pName;
   }
   //------------------------------------------------------------
   // <T>����ڴ��С��</T>
   MO_INLINE TInt MemorySize(){
      return _memorySize;
   }
   //------------------------------------------------------------
   // <T>��ü��������</T>
   MO_INLINE TInt64 ActiveCount(){
      return _activeCount;
   }
   //------------------------------------------------------------
   // <T>����ռ�������</T>
   MO_INLINE TInt64 AllocTotal(){
      return _allocTotal;
   }
   //------------------------------------------------------------
   // <T>���ʵ�����ϡ�</T>
   MO_INLINE TInstanceList& Pool(){
      return _pool;
   }
   //------------------------------------------------------------
   // <T>���ʵ�����ϡ�</T>
   MO_INLINE TInstanceLooper& Looper(){
      return _looper;
   }
public:
   FClass* ParentClass();
public:
   TBool IsInheritsFrom(TCharC* pClassName);
   TBool IsInheritsFrom(FClass* pClass);
public:
   MO_VIRTUAL FInstance* InstanceCreate() = 0;
   MO_VIRTUAL FInstance* InstanceAlloc() = 0;
   MO_VIRTUAL void InstanceFree(FInstance* pInstance) = 0;
   MO_VIRTUAL void InstanceDelete(FInstance* pInstance) = 0;
public:
   FInstance* InstanceInheritCreate(FClass* pClass);
   template <class T>
   T* InstanceInheritCreate(){
      return (T*)InstanceInheritCreate(T::Class());
   }
public:
   MO_ABSTRACT TResult Process();
   MO_OVERRIDE TCharC* Dump(TChar* pDump, TInt capacity);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FVector<FClass*> FClassCollection;
typedef MO_CM_DECLARE TLooper<FClass*> TClassLooper;
typedef MO_CM_DECLARE FDictionary<FClass*> FClassDictionary;
typedef MO_CM_DECLARE TDictionary<FClass*> TClassDictionary;

//============================================================
// <T>��ģ�����</T>
//
// @class
// @history 140217 MAOCY ����
//============================================================
template <class T>
class FClassTemplate : public FClass{
public:
   //------------------------------------------------------------
   // <T>������ʵ����</T>
   FClassTemplate(TCharC* pName, TCharC* pParentName, TInt memorySize){
      _pName = pName;
      _pParentClassName = pParentName;
      _memorySize = memorySize;
   }
public:
   //------------------------------------------------------------
   // <T>������ʵ����</T>
   MO_OVERRIDE FInstance* InstanceCreate(){
      FInstance* pInstance = MO_CREATE(T);
      // _looper.Push(pInstance);
      _activeCount++;
      _allocTotal++;
      return pInstance;
   }
   //------------------------------------------------------------
   // <T>�ռ���ʵ����</T>
   MO_OVERRIDE FInstance* InstanceAlloc(){
      _activeCount++;
      _allocTotal++;
      T* pInstance = NULL;
      if(_pool.IsEmpty()){
         pInstance = MO_CREATE(T);
         // _looper.Push(pInstance);
      }else{
         pInstance = (T*)_pool.Shift();
      }
      return pInstance;
   }
   //------------------------------------------------------------
   // <T>�ͷ���ʵ����</T>
   MO_OVERRIDE void InstanceFree(FInstance* pInstance){
      MO_ASSERT(pInstance);
      _activeCount--;
      _pool.Push(pInstance);
   }
   //------------------------------------------------------------
   // <T>ɾ����ʵ����</T>
   MO_OVERRIDE void InstanceDelete(FInstance* pInstance){
      MO_ASSERT(pInstance);
      _activeCount--;
      T* pFreeable = (T*)pInstance;
      MO_DELETE(pFreeable);
   }
};

//============================================================
// <T>����ģ�����</T>
//
// @class
// @history 140217 MAOCY ����
//============================================================
template <class T>
class FClassAbstractTemplate : public FClass{
public:
   //------------------------------------------------------------
   // <T>��������ģ�����</T>
   FClassAbstractTemplate(TCharC* pName, TCharC* pParentName, TInt memorySize){
      _pName = pName;
      _pParentClassName = pParentName;
      _memorySize = memorySize;
   }
public:
   //------------------------------------------------------------
   // <T>������ʵ����</T>
   MO_OVERRIDE FInstance* InstanceCreate(){
      MO_FATAL(TC("Abstract class disable instance create"));
      return NULL;
   }
   //------------------------------------------------------------
   // <T>�ռ���ʵ����</T>
   MO_OVERRIDE FInstance* InstanceAlloc(){
      MO_FATAL(TC("Abstract class disable instance alloc"));
      return NULL;
   }
   //------------------------------------------------------------
   // <T>�ͷ���ʵ����</T>
   MO_OVERRIDE void InstanceFree(FInstance* pInstance){
      MO_FATAL(TC("Abstract class disable instance free"));
   }
   //------------------------------------------------------------
   // <T>ɾ����ʵ����</T>
   MO_OVERRIDE void InstanceDelete(FInstance* pInstance){
      MO_FATAL(TC("Abstract class disable instance delete"));
   }
};

//============================================================
// <T>ȫ��ָ�롣</T>
//
// @template
//============================================================
template <typename T>
class GPtr{
protected:
   T* _pInstance;
public:
   //------------------------------------------------------------
   // <T>����ȫ��ָ�롣</T>
   MO_INLINE GPtr(){
      MO_CLEAR(_pInstance);
   }
   //------------------------------------------------------------
   // <T>����ȫ��ָ�롣</T>
   MO_INLINE GPtr(T* pInstance){
      _pInstance = pInstance;
      if(_pInstance != NULL){
         _pInstance->ReferIncrease();
      }
   }
   //------------------------------------------------------------
   // <T>����ȫ��ָ�롣</T>
   MO_INLINE GPtr(const GPtr<T>& instance){
      _pInstance = instance._pInstance;
      if(_pInstance != NULL){
         _pInstance->ReferIncrease();
      }
   }
   //------------------------------------------------------------
   // <T>����ȫ��ָ�롣</T>
   MO_INLINE ~GPtr(){
      if(_pInstance != NULL){
         _pInstance->ReferDecrease();
      }
   }
public:
   //------------------------------------------------------------
   // <T>��ȡ�����ַ��</T>
   MO_INLINE T& operator *(){
      return *_pInstance;
   }
   //------------------------------------------------------------
   // <T>��ȡ����ָ�롣</T>
   MO_INLINE T* operator ->(){
      MO_ASSERT(_pInstance);
      return _pInstance;
   }
   //------------------------------------------------------------
   // <T>ת��Ϊ����ֵ��</T>
   MO_INLINE operator TBool() const{
	   return (_pInstance != NULL);
   }
   //------------------------------------------------------------
   // <T>ת��Ϊ���͡�</T>
   MO_INLINE operator T*() const{
      return _pInstance;
   }
public:
   //------------------------------------------------------------
   // <T>����ȫ��ָ�롣</T>
   MO_INLINE void operator = (T* pInstance){
      Set(pInstance);
   }
   //------------------------------------------------------------
   // <T>����ȫ��ָ�롣</T>
   MO_INLINE void operator = (const GPtr<T>& instance){
      Set(instance._pInstance);
   }
public:
   //------------------------------------------------------------
   // <T>�ж�ָ���Ƿ���ȡ�</T>
   MO_INLINE TBool operator == (const T* pInstance) const{
       return (_pInstance == pInstance);
   }
   //------------------------------------------------------------
   // <T>�ж�ָ���Ƿ���ȡ�</T>
   MO_INLINE TBool operator == (T* pInstance) const{
       return (_pInstance == pInstance);
   }
   //------------------------------------------------------------
   // <T>�ж�ָ���Ƿ���ȡ�</T>
   MO_INLINE TBool operator == (const GPtr<T>& instance) const{
      return (_pInstance == instance._pInstance);
   }
   //------------------------------------------------------------
   // <T>�ж�ָ���Ƿ���ȡ�</T>
   MO_INLINE TBool operator != (const T* pInstance) const{
      return (_pInstance != pInstance);
   }
   //------------------------------------------------------------
   // <T>�ж�ָ���Ƿ���ȡ�</T>
   MO_INLINE TBool operator != (T* pInstance) const{
      return (_pInstance != pInstance);
   }
   //------------------------------------------------------------
   // <T>�ж�ָ���Ƿ���ȡ�</T>
   MO_INLINE TBool operator != (const GPtr<T>& instance) const{
      return (_pInstance != instance._pInstance);
   }
   //------------------------------------------------------------
   // <T>�ж�ָ���Ƿ�С�ڡ�</T>
   MO_INLINE TBool operator < (const GPtr<T>& instance) const{
      return (_pInstance < instance._pInstance);
   }
   //------------------------------------------------------------
   // <T>�ж�ָ���Ƿ���ڡ�</T>
   MO_INLINE TBool operator > (const GPtr<T>& instance) const{
      return (_pInstance > instance._pInstance);
   }
public:
   //------------------------------------------------------------
   // <T>���ȫ��ָ�롣</T>
   MO_INLINE T* Get() const{
      return _pInstance;
   }
   //------------------------------------------------------------
   // <T>��ȫת��Ϊָ�����͡�</T>
   template<class C>
   const C* Convert() const{
#ifdef _MO_DEBUG
      C* pInstance = NULL;
      if(_pInstance != NULL){
         pInstance = _pInstance->Convert<C>();
      }
      return pInstance;
#else
      return (C*)_pInstance;
#endif // _MO_DEBUG
   }
   //------------------------------------------------------------
   // <T>��ȫת��Ϊָ���������͡�</T>
   template<class C>
   const C* ConvertParent() const{
#ifdef _MO_DEBUG
      RClassManager::CheckInherit(T::Class(), C::Class());
#endif // _MO_DEBUG
      return (C*)_pInstance;
   }
   //------------------------------------------------------------
   // <T>��ȫת��Ϊָ���������͡�</T>
   template<class C>
   const C* CastInherit() const{
#ifdef _MO_DEBUG
      RClassManager::CheckInherit(C::Class(), T::Class());
#endif // _MO_DEBUG
      return (C*)_pInstance;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���Ч��</T>
   MO_INLINE TBool IsValid() const{
      return (_pInstance != NULL);
   }
   //------------------------------------------------------------
   // <T>������ô�����</T>
   MO_INLINE TInt ReferCount(){
      TInt referCount = 0;
      if(_pInstance != NULL){
         referCount = _pInstance->ReferCount();
      }
      return referCount;
   }
   //------------------------------------------------------------
   // <T>����һ�����á�</T>
   MO_INLINE void ReferIncrease(){
      if(_pInstance != NULL){
         _pInstance->ReferIncrease();
      }
   }
   //------------------------------------------------------------
   // <T>����һ�����á�</T>
   MO_INLINE TResult ReferDecrease(){
      TResult resultCd = ESuccess;
      if(_pInstance != NULL){
         resultCd = _pInstance->ReferDecrease();
         if(resultCd == ERelease){
            MO_CLEAR(_pInstance);
         }
      }
      return resultCd;
   }
   //------------------------------------------------------------
   // <T>����ָ�롣</T>
   MO_INLINE void Set(T* pInstance){
      if(_pInstance != pInstance){
         // �ڲ�������
         if(_pInstance != NULL){
            TResult resultCd = _pInstance->ReferDecrease();
            if(resultCd == ERelease){
               MO_CLEAR(_pInstance);
            }
         }
         // �ⲿ������
         _pInstance = pInstance;
         if(_pInstance != NULL){
            _pInstance->ReferIncrease();
         }
      }
   }
   //------------------------------------------------------------
   // <T>����ָ�롣</T>
   MO_INLINE void Set(const GPtr<T>& instance){
      Set(instance._pInstance);
   }
   //------------------------------------------------------------
   // <T>����ȫ��ָ�롣</T>
   MO_INLINE void Swap(GPtr<T>& instance) {
      T* pTempInstance = instance._pInstance;
      instance._pInstance = _pInstance;
	   _pInstance = pTempInstance;
   }
   //------------------------------------------------------------
   // <T>���ض��󣬵��ǲ��޸����á�</T>
   MO_INLINE T* Flip(){
      T* pInstance = _pInstance;
      _pInstance = NULL;
      return pInstance;
   }
   //------------------------------------------------------------
   // <T>���ö���</T>
   MO_INLINE void Reset(){
      if(_pInstance != NULL){
         _pInstance->ReferDecrease();
         MO_CLEAR(_pInstance);
      }
   }
   //------------------------------------------------------------
   // <T>�ͷŶ���</T>
   MO_INLINE void Release(){
      if(_pInstance != NULL){
         _pInstance->Release();
         MO_CLEAR(_pInstance);
      }
   }
};

//============================================================
// <T>������������</T>
// <P>�����Instance��������������</P>
//============================================================
#define MO_CLASS_DECLARE(T) \
private: \
   static FClass* _pClass; \
public: \
   static MO_INLINE FClass* Class(){ \
      MO_ASSERT(_pClass); \
      return _pClass; \
   } \
   static MO_INLINE T* InstanceCreate(){ \
      MO_ASSERT(_pClass); \
      T* pInstance = (T*)_pClass->InstanceCreate(); \
      return pInstance; \
   } \
   static MO_INLINE T* InstanceAlloc(){ \
      MO_ASSERT(_pClass); \
      T* pInstance = (T*)_pClass->InstanceAlloc(); \
      return pInstance; \
   } \
   static MO_INLINE void InstanceFree(T* pInstance){ \
      MO_ASSERT(_pClass); \
      return _pClass->InstanceFree(pInstance); \
   } \
   static MO_INLINE void InstanceDelete(T* pInstance){ \
      MO_ASSERT(_pClass); \
      return _pClass->InstanceDelete(pInstance); \
   } \
public: \
   MO_ABSTRACT FClass* GetClass(); \

//============================================================
// <T>������̳�������</T>
// <P>�����Instance��������������</P>
//============================================================
#define MO_CLASS_DECLARE_INHERITS(T, B) \
   MO_CLASS_DECLARE(T) \
private: \
   static FClass* _pParentClass; \
public: \
   static MO_INLINE FClass* ParentClass(){ \
      if(_pParentClass == NULL){ \
         _pParentClass = _pClass->ParentClass(); \
      } \
      return _pParentClass; \
   } \
public: \
   MO_ABSTRACT FClass* GetParentClass(); \

//============================================================
// <T>��������������</T>
// <P>�����Instance��������������</P>
//============================================================
#define MO_CLASS_ABSTRACT_DECLARE(T) \
private: \
   static FClass* _pClass; \
public: \
   static MO_INLINE FClass* Class(){ \
      return _pClass; \
   } \
public: \
   MO_ABSTRACT FClass* GetClass(); \

//============================================================
// <T>������̳�������</T>
// <P>�����Instance��������������</P>
//============================================================
#define MO_CLASS_ABSTRACT_DECLARE_INHERITS(T, B) \
   MO_CLASS_ABSTRACT_DECLARE(T) \
private: \
   static FClass* _pParentClass; \
public: \
   static MO_INLINE FClass* ParentClass(){ \
      if(_pParentClass == NULL){ \
         _pParentClass = _pClass->ParentClass(); \
      } \
      return _pParentClass; \
   } \
public: \
   MO_ABSTRACT FClass* GetParentClass(); \

//============================================================
// <T>ʵ������</T>
//============================================================
class MO_CM_DECLARE FInstance : public FObject
{
   MO_CLASS_DECLARE(FInstance);
protected:
    volatile TInt _referCount;
public:
   FInstance();
   MO_ABSTRACT ~FInstance();
public:
   //------------------------------------------------------------
   // <T>������ô�����</T>
   MO_INLINE TInt ReferCount(){
      return _referCount;
   }
   //------------------------------------------------------------
   // <T>����һ�����á�</T>
   MO_INLINE void ReferIncrease(){
      _referCount++;
   }
   //------------------------------------------------------------
   // <T>����һ�����á�</T>
   MO_INLINE TResult ReferDecrease(){
      MO_ASSERT(_referCount > 0);
      // ��������
      _referCount--;
      // �ͷŶ���
      if(_referCount == 0){
         Release();
         return ERelease;
      }
      return ESuccess;
   }
   //------------------------------------------------------------
   // <T>�ͷŶ���</T>
   MO_INLINE void Release(){
      _referCount = 0;
      InstanceDelete(this);
   }
public:
   TBool IsInstanceOf(TCharC* pClassName);
   TBool IsInstanceOf(FClass* pClass);
   TBool IsInheritsFrom(TCharC* pClassName);
   TBool IsInheritsFrom(FClass* pClass);
   FInstance* Convert(FClass* pClass);
public:
   //------------------------------------------------------------
   // <T>ת�����͡�</T>
   template <class T>
   MO_INLINE T* Convert(){
#ifdef _MO_DEBUG
      return (T*)Convert(T::Class());
#else
      return (T*)this;
#endif // _MO_DEBUG
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE GPtr<FInstance> GInstancePtr;

//============================================================
// <T>�๤����</T>
//
// @class
// @history 140308 MAOCY ����
//============================================================
class MO_CM_DECLARE FClassFactory : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FClassFactory, FInstance);
protected:
   FClassDictionary* _pClasses;
public:
   FClassFactory();
   MO_ABSTRACT ~FClassFactory();
public:
   //------------------------------------------------------------
   // <T>����ඨ�弯�ϡ�</T>
   MO_INLINE FClassDictionary* Classes(){
      return _pClasses;
   }
public:
   TResult Register(FClass* pClass);
   TResult Register(TCharC* pName, FClass* pClass);
   TResult Unregister(TCharC* pName);
public:
   TBool Contains(TCharC* pName);
   FInstance* Create(TCharC* pName);
   FInstance* Alloc(TCharC* pName);
   void Free(FInstance* pInstance);
   void Delete(FInstance* pInstance);
public:
   //------------------------------------------------------------
   // <T>���������ʵ����</T>
   template <class T>
   MO_INLINE T* Create(TCharC* pName){
      FInstance* pInstance = this->Create(pName);
      return pInstance->Convert<T>();
   }
   //------------------------------------------------------------
   // <T>�ռ������ʵ����</T>
   template <class T>
   MO_INLINE T* Alloc(TCharC* pName){
      FInstance* pInstance = this->Alloc(pName);
      return pInstance->Convert<T>();
   }
public:
   TCharC* Dump(TChar* pDump, TInt capacity);
};

//============================================================
// <T>ʵ���๤����</T>
//
// @class
// @history 140315 MAOCY ����
//============================================================
class MO_CM_DECLARE FClassInstanceFactory : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FClassInstanceFactory, FInstance);
protected:
   FClass* _pDefaultClass;
   FClassDictionary* _pClasses;
   GInstancePtr _defaultInstance;
   FInstanceDictionary* _pInstances;
public:
   FClassInstanceFactory();
   MO_ABSTRACT ~FClassInstanceFactory();
public:
   //------------------------------------------------------------
   // <T>���Ĭ���ࡣ</T>
   MO_INLINE FClass* DefaultClass(){
      return _pDefaultClass;
   }
   //------------------------------------------------------------
   // <T>����Ĭ���ࡣ</T>
   MO_INLINE void SetDefaultClass(FClass* pClass){
      _pDefaultClass = pClass;
   }
   //------------------------------------------------------------
   // <T>������ֵ䡣</T>
   MO_INLINE FClassDictionary* Classes(){
      return _pClasses;
   }
   //------------------------------------------------------------
   // <T>���ʵ���ֵ䡣</T>
   MO_INLINE FInstanceDictionary* Instances(){
      return _pInstances;
   }
public:
   TResult Register(TCharC* pName, FClass* pClass);
   TResult Unregister(TCharC* pName);
public:
   FInstance* Find(TCharC* pName);
   FInstance* Get(TCharC* pName);
   TResult Free(TCharC* pName);
public:
   TCharC* Dump(TChar* pDump, TInt capacity);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE GPtr<FClassInstanceFactory> GClassInstanceFactoryPtr;
   
MO_NAMESPACE_END

#endif // __MO_CM_CLASSBASE_H__
