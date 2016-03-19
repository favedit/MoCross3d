#ifndef __MO_CM_SHARED_H__
#define __MO_CM_SHARED_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_SINGLETON_H__
#include "MoCmSingleton.h"
#endif // __MO_CM_SINGLETON_H__

#ifndef __MO_CM_MEMORY_H__
#include "MoCmMemory.h"
#endif // __MO_CM_MEMORY_H__

#ifndef __MO_CM_MODULE_H__
#include "MoCmModule.h"
#endif // __MO_CM_MODULE_H__

#define MO_DUMP_SHARED_LA  TC("==========================================================================================================")
#define MO_DUMP_SHARED_LA2 TC("----------------------------------------------------------------------------------------------------------")
#define MO_DUMP_SHARED_LB  TC("-----------------------------------------|--------------------|-------------------------------------------")
#define MO_DUMP_SHARED_LC  TC(".........................................|....................|...........................................")
#define MO_DUMP_SHARED_FMT TC("%-40s | %18s | ")

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ڴ����</T>
// <P>����û�з����ڴ棬ֻ�ǽ������ڴ��еĵ�ַ������Լ���</P>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CM_DECLARE MShared{
protected:
   TByte* _gMemory;
public:
   MShared();
   MO_ABSTRACT ~MShared();
public:
   MO_VIRTUAL void OnSharedLink(TShareSegment& segment) = 0;
   MO_ABSTRACT void OnSharedLinked();
   MO_ABSTRACT void OnSharedInitialize();
   MO_ABSTRACT void OnSharedResume();
   MO_ABSTRACT void OnSharedComplete();
public:
   MO_ABSTRACT TBool IsSharedLinked();
   MO_ABSTRACT TByte* SharedMemory();
   MO_VIRTUAL TSize SharedCapacity() = 0;
   MO_ABSTRACT void SharedLink(TShareSegment segment);
public:
   MO_ABSTRACT TBool SharedCreate();
   MO_ABSTRACT TBool SharedDestory();
public:
   MO_ABSTRACT void DumpShared();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<MShared*> FSharedList;
typedef MO_CM_DECLARE FSet<TInt, MShared*> FSharedSet;

//============================================================
// <T>�����顣</T>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CM_DECLARE FSharedGroup : public FObject{
protected:
   TShareKey _key;
   TFsPath _keyName;
   FSharedList* _pShareds;
   IShareAllocator* _pAllocator;
public:
   FSharedGroup();
   MO_ABSTRACT ~FSharedGroup();
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TShareKey Key(){
      return _key;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void SetKey(TShareKey key){
      _key = key;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* KeyName(){
      return _keyName;
   }
   //------------------------------------------------------------
   // <T>�����������ơ�</T>
   MO_INLINE void SetKeyName(TCharC* pKeyName){
      _keyName = pKeyName;
   }
public:
   TSize SharedCapacity();
   TBool SharedLink(TShareSegment segment);
public:
   void Register(MShared* pShared);
   void Unregister(MShared* pShared);
   TBool Create();
   TBool Connect();
   TBool Link();
   TBool Dump();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FSharedGroup*> FSharedGroupList;

//============================================================
// <T>�����ڴ����̨��</T>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CM_DECLARE FSharedConsole : public FConsole{
protected:
   FSharedSet* _pShareds;
   FSharedGroupList* _pGroups;
public:
   FSharedConsole();
   MO_ABSTRACT ~FSharedConsole();
public:
   TSize SharedCapacity();
   void SharedLink(TShareSegment segment);
   MShared* Get(TInt Code);
   MShared* Find(TInt Code);
   void Register(MShared* pShared);
   void Unregister(MShared* pShared);
public:
   FSharedGroup* FindGroup(TShareKey key, TCharC* pKeyName);
   FSharedGroup* LinkGroup(TShareKey key, TCharC* pKeyName);
};

//============================================================
// <T>�����ڴ��������</T>
//============================================================
class MO_CM_DECLARE RSharedManager : public RSingleton<FSharedConsole>{
};

//============================================================
// <T>����Ψһ������ࡣ</T>
//
// @history 100309 MAOCY ����
//============================================================
template <typename T>
class RSharedSingleton : public RSingleton<T>{
public:
   //------------------------------------------------------------
   // <T>��ʼ�������ʵ����</T>
   static T* Initialize(){
      RSingleton<T>::Initialize();
      RSingletonManager::Register(RSingleton<T>::_pInstance);
   }
   //------------------------------------------------------------
   // <T>�ͷŶ����ʵ����</T>
   static void Release(){
      RSingletonManager::Unregister(RSingleton<T>::_pInstance);
      RSingleton<T>::Release();
   }
   //------------------------------------------------------------
   // <T>������Ҫ�����ڴ�Ĵ�С��</T>
   static TSize SharedCapacity(){
      return RSingleton<T>::_pInstance->SharedCapacity();
   }
   //------------------------------------------------------------
   // <T>��ʼ�������ʵ����</T>
   static void SharedLink(TShareSegment segment){
      RSingleton<T>::_pInstance->SharedLink(segment);
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_SHARED_H__
