/*
 * File:   MoCmSystemTemp.h
 * Author: root
 *
 * Created on 2009��3��3��, ����1:35
 */

#ifndef _MOCMSYSTEMTEMP_H
#define	_MOCMSYSTEMTEMP_H

/*

// ************************************************************
// �����ڴ������
// ************************************************************
namespace{
   char cpp_handler_instructions[5];
   bool saved_handler_instructions = false;
}

// ------------------------------------------------------------
struct SExceptionTypeInfo;

typedef void (*MoExceptionCleanupFunction)();
//typedef std::vector<const etype_info*> TYPEINFOVEC;

struct SExceptionTypeInfoTable{
   TUint32 count;
   SExceptionTypeInfo* arr[1];
};

struct SExceptionInfo{
   TUint32 u1;
   TUint32 destructor;
   TUint32 u2;
   SExceptionTypeInfoTable* pTypeInfoTable;
};

struct SExceptionTypeInfo{
   TUint32 u1;
   type_info* ti;
   TUint32 u2[3];
   TUint32 size;
   TUint32 copyConstructor;
   EBool equal(const SExceptionTypeInfo* t){
      return EFalse;
      //if(t->ti == 0 || ti == 0)
      //return (t->ti == ti) ? ETrue: EFalse;
      //VC++ 6.0 returns type int and not bool
      //return (*t->ti == *ti) ? ETrue : EFalse;
   }
};

struct SExceptionRegistration{
   SExceptionRegistration* pPrior;
   TUint32 handler;
   TUint32 id;
   TUint32 ebp;
};

struct SExceptionCatchBlock{
   /// @attribute ��ֵ���ƻ����ø��Ƶı�־
   TUint32 valueOrReference;
   /// @attribute ������Ϣ
   type_info* pTypeInfo;
   /// @attribute ��ʼλ��
   int offset;
   /// @attribute ���⴦����ַ
   TUint32 catchBlockAddress;
};

struct SExceptionUnwind{
   TUint32 prior;
   MoExceptionCleanupFunction cleanupFunction;
};

struct SExceptionTryBlock{
   TUint32 beginId;
   TUint32 endId;
   TUint32 u1;
   TUint32 catchBlockCount;
   SExceptionCatchBlock* pCatchBlockTable;
};

struct SExceptionMethodInfo{
   /// @attribute ����ǩ��
   TUint32 signature;
   /// @attribute �ع�����
   TUint32 unwindCount;
   /// @attribute �ع�ָ���
   SExceptionUnwind* pUnwindTable;
   /// @attribute ���⴦�����
   TUint32 tryBlockCount;
   /// @attribute ���⴦��ָ���
   SExceptionTryBlock* pTryBlockTable;
};

// �Զ����Ĭ�ϵ����⺯�����
EXCEPTION_DISPOSITION __MoExceptionHandler(
      struct _EXCEPTION_RECORD* pExceptionRecord,
      TAny* pEstablisherFrame,
      struct _CONTEXT* pContextRecord,
      TAny* pDispatcherContext) throw();

// �Զ����Ĭ�ϵ������ͷž��
EXCEPTION_DISPOSITION __MoTerminateHandler(
      _EXCEPTION_RECORD* pExceptionRecord,
      TAny* pEstablisherFrame,
      struct _CONTEXT* pContextRecord,
      TAny* pDispatcherContext) throw();

// ------------------------------------------------------------
class MO_COMMON_DECLARE RException{
protected:
   static TChar8 _handlerStore[5];
   static EBool _handlerSaved;
public:
   static EBool InstallHandler();
   static EBool UninstallHandler();
};

// ************************************************************
// <T>�������Ĺ���ӿڡ�</T>
// ************************************************************
class MO_COMMON_DECLARE IHandleConsole :
      public IConsole{
public:
   MO_VIRTUAL( TAny* Open(THandle handle) );
   MO_VIRTUAL( void Close(THandle handle) );
   MO_VIRTUAL( void Release(THandle handle) );
   MO_VIRTUAL( void ReleaseAll() );
};

// ************************************************************
// <T>�������Ĺ���ӿڡ�</T>
// ************************************************************
class MO_COMMON_DECLARE IMemoryHandleConsole :
      public IHandleConsole{
public:
   THandle Create(TUint size);
};

// ************************************************************
// <T>�������Ĺ������</T>
// ************************************************************
class MO_COMMON_DECLARE FMemoryHandle{
public:
   TInt Refer;
   TAny* pMemory;
};

// ------------------------------------------------------------
typedef MO_COMMON_DECLARE FSet<FMemoryHandle*> FMemoryHandleSet;

// ------------------------------------------------------------
class MO_COMMON_DECLARE FMemoryHandleConsole :
      public IMemoryHandleConsole{
protected:
   FMemoryHandleSet* _pHandles;
public:
   FMemoryHandleConsole();
   ~FMemoryHandleConsole();
public:
   THandle Create(TUint size);
   MO_OVERRIDE( TAny* Open(THandle handle) );
   MO_OVERRIDE( void Close(THandle handle) );
   MO_OVERRIDE( TAny* Lock(THandle handle) );
   MO_OVERRIDE( void Unlock(THandle handle) );
   MO_OVERRIDE( void Release(THandle handle) );
   MO_OVERRIDE( void ReleaseAll() );
};

// ************************************************************
// <T>��Դ����Ĺ���ӿڡ�</T>
// ************************************************************
class IResourceConsole :
      public IConsole{
public:
   MO_VIRTUAL( TAny* Open(TResource resource) );
   MO_VIRTUAL( void Close(TResource resource) );
   MO_VIRTUAL( TAny* Lock(TResource resource) );
   MO_VIRTUAL( void Unlock(TResource resource) );
   MO_VIRTUAL( void Release(TResource resource) );
   MO_VIRTUAL( void ReleaseAll() );
};

// ************************************************************
// <T>��Դ����Ĺ������</T>
// ************************************************************
class FResourceConsole : public IResourceConsole{
public:
   //TResource Create(MStringC& name);
   //MO_OVERRIDE( TResource Create() );
   //MO_OVERRIDE( void Open(TResource resource) );
   //MO_OVERRIDE( void Close(TResource resource) );
   //MO_OVERRIDE( void Release(TResource resource) );
};*/

#endif	/* _MOCMSYSTEMTEMP_H */

