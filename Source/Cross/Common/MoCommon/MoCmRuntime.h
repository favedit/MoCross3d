//============================================================
// <T>�������Ͷ���</T>
//
// �������ĸ��
//   E -> ö���ࣺһ�����ݶ��塣
//   S -> �ṹ�ࣺ�ṹ���塣������struct������ࡣ
//   R -> �����ࣺ���о�̬���������ĳ������������½�ʵ����ֻ�ܱ���̬���ú�����
//   I -> �ӿ��ࣺ�����½���ֻ�ܱ��������ӿ�ʹ�ã��ڲ�ֻ�ܴ��ڴ��麯�������ܺ����κδ���
//   M -> �����ࣺ�����½���ֻ�ܱ��������ӿ�ʹ�ã��ڲ����Դ������ɴ���
//   T -> �����ࣺ��ȫ���������Ͳ����������½����󣬿������⸴�ƣ�����Ҫ�ͷŲ�����
//   F -> �����ࣺ����ʹ��(MO_CREATE)�괴������õ�������ֱ�Ӷ���ʹ�ã�����Ҫ�ͷš�
//   H -> ����ࣺ����ͨ���½�����õ�������ֱ�Ӷ���ʹ�ã������ͷš�
// ���ĩ��ĸ��
//   C -> ֻ���ࣺһ��Ϊ�ײ����ã������½���ֻ�����á�
//
// ��������ĸ��
//   C -> �ص������������Ķ��塣
// ����ĩ��ĸ������������ϣ���
//   M -> �ڴ棬���������ڴ��ռ����ͷŵĲ������뿪����ʱ���������ڴ�ƽ���ԡ�
//   L -> ���⣬�����ڲ����ܲ������⣬����ʱ����������⴦��
//   C -> ֻ����û�иı��κ��ڲ��ṹ��û���κ��ڴ�������������ܲ�������
//============================================================

#ifndef __MO_CM_RUNTIME_H__
#define __MO_CM_RUNTIME_H__

//============================================================
// ���Ա�־
#ifdef _MO_DEBUG
#ifndef _MO_DEBUG
#define _MO_DEBUG
#endif // _MO_DEBUG
#define _MO_MEMORY
#define _MO_LOGGER
#endif // _DEBUG
//............................................................
// Linux��־
#ifdef _MO_LINUX
#ifndef _MO_LINUX
#define _MO_LINUX
#endif // _MO_LINUX
#endif // _LINUX

//============================================================
// <T>����ƽ̨�� Windows X86</T>
//============================================================
#ifdef _MO_WINDOWS
#ifdef _MO_X86
#ifndef __MO_CM_WINDOWS_86_H__
#include "MoCmWindows86.h"
#endif // __MO_CM_WINDOWS_86_H__
#endif // _MO_X86
#endif // _MO_WINDOWS

//============================================================
// <T>����ƽ̨�� Windows X64</T>
//============================================================
#ifdef _MO_WINDOWS
#ifdef _MO_X64
#ifndef __MO_CM_WINDOWS_64_H__
#include "MoCmWindows64.h"
#endif // __MO_CM_WINDOWS_64_H__
#endif // _MO_X64
#endif // _MO_WINDOWS

//============================================================
// <T>����ƽ̨�� MinGW</T>
//============================================================
#ifdef _MO_MINGW
#ifdef _MO_X86
#ifndef __MO_CM_MINGW_H__
#include "MoCmMinGW.h"
#endif // __MO_CM_MINGW_H__
#endif // _MO_X86
#endif // _MO_MINGW

//============================================================
// <T>����ƽ̨�� Linux X86</T>
//============================================================
#ifdef _MO_LINUX
#ifdef _MO_X86
#ifndef __MO_CM_LINUX_32_H__
#include "MoCmLinux86.h"
#endif // __MO_CM_LINUX_32_H__
#endif // _MO_X86
#endif // _MO_LINUX

//============================================================
// <T>����ƽ̨�� Linux X64</T>
//============================================================
#ifdef _MO_LINUX
#ifdef _MO_X64
#ifndef __MO_CM_LINUX_64_H__
#include "MoCmLinux64.h"
#endif // __MO_CM_LINUX_64_H__
#endif // _MO_X64
#endif // _MO_LINUX

//============================================================
// <T>����ƽ̨�� Android (32bit)</T>
//============================================================
#ifdef _MO_ANDROID
#ifndef __MO_CM_ANDROID_H__
#include "MoCmAndroid.h"
#endif // __MO_CM_ANDROID_H__
#endif // _MO_ANDROID

//============================================================
// <T>����ƽ̨�� FlasCC (32bit)</T>
//============================================================
#ifdef _MO_FLASCC
#ifndef __MO_CM_FLASCC_H__
#include "MoCmFlasCC.h"
#endif // __MO_CM_FLASCC_H__
#endif // _MO_FLASCC

/// @define ��������
#ifdef _MO_CM_EXPORTS
#define MO_CM_DECLARE MO_EXPORT
#else
#define MO_CM_DECLARE MO_IMPORT
#endif

//============================================================
// <T>����׷�١�</T>
//============================================================
#define MO_PERFORMANCE_TRACK

//============================================================
// <T>���붨�塣</T>
//============================================================
#define TS(S) TStringPtr(S)
//------------------------------------------------------------
#ifdef _UNICODE
#define TC(S) L##S
#ifndef _MO_UNICODE
#define _MO_UNICODE
#endif // _MO_UNICODE
#else
#define TC(S) S
#endif

//============================================================
// <T>�ڴ�����塣</T>
//============================================================
/// @define ���ⶨ��
#ifdef _MO_ANDROID
#define MO_TYPENAME(T)         #T
#else
#define MO_TYPENAME(T)         typeid(T).name()
#endif // _MO_ANDROID
//------------------------------------------------------------
/// @define ���һ������ָ��
#define MO_CLEAR(P)            P=NULL
//------------------------------------------------------------
/// @define ����һ���ڴ�ָ��
#define MO_MEM_CREATE(T, ...)  new T(__VA_ARGS__)
/// @define �ռ�һ���ڴ�ָ��
#define MO_MEM_ALLOC(S)        malloc(S)
/// @define �ͷ�һ���ڴ�ָ��
#define MO_MEM_FREE(P)         if(P){free(P);P=NULL;}
/// @define ɾ��һ���ڴ�ָ��
#define MO_MEM_DELETE(P)       if(P){delete P;P=NULL;}
//------------------------------------------------------------
/// @define ����һ���ڴ�����
#define MO_MEM_CREATE_ARRAY(T, ...)  new T(__VA_ARGS__)[]
/// @define ɾ��һ���ڴ�����
#define MO_MEM_DELETE_ARRAY(P) if(P){delete[] P;P=NULL;}
//------------------------------------------------------------
/// @define ����һ���ڴ�ָ��
#define MO_PTR_CREATE(T, ...)  new T(__VA_ARGS__)
/// @define ɾ��һ���ڴ�ָ��
#define MO_PTR_DELETE(P)       if(P){delete P;P=NULL;}
//------------------------------------------------------------
/// @define �ͷ�һ������ӿ�
#define MO_PTR_RELEASE(P)      if(P){P->Release();P=NULL;}

//------------------------------------------------------------
/// @define �����ڴ����
#define MO_SHARE_CREATE(S, T, ...) new(S->MemoryC())T(__VA_ARGS__)
#define MO_SHARE_ALLOC(T, ...)     (T*)RShareMemory::Alloc(#T, sizeof(T), __FILE__, __LINE__)
#define MO_SHARE_FREE(P)           RShareMemory::Free(P)
#define MO_SHARE_DELETE(P)         P->Dispose();RShareMemory::Free(P)

//------------------------------------------------------------
/// @define �����ڴ����
#define MO_PROCESS_CREATE(T, ...) new (RProcessMemory::Alloc(#T, sizeof(T), __FILE__, __LINE__))T(__VA_ARGS__)
#define MO_PROCESS_ALLOC(T, ...)  (T*)RProcessMemory::Alloc(#T, sizeof(T), __FILE__, __LINE__)
#define MO_PROCESS_FREE(P)        RProcessMemory::Free(P)
#define MO_PROCESS_DELETE(P)      P->Dispose();RProcessMemory::Free(P)

//------------------------------------------------------------
/// @define �߳��ڴ����
#define MO_THREAD_CREATE(T, ...)  new (RThreadMemory::Alloc(#T, sizeof(T), __FILE__, __LINE__))T(__VA_ARGS__)
#define MO_THREAD_ALLOC(T, ...)   (T*)RThreadMemory::Alloc(#T, sizeof(T), __FILE__, __LINE__)
#define MO_THREAD_FREE(P)         RThreadMemory::Free(P)
#define MO_THREAD_DELETE(P)       P->Dispose();RThreadMemory::Free(P)

//------------------------------------------------------------
/// @define ����һ�������ʵ��
#ifdef _MO_MEMORY
#ifdef _MO_ANDROID
#define MO_CREATE(T, ...)           new (#T, __FILE__, __LINE__)T(__VA_ARGS__)
#else
#define MO_CREATE(T, ...)           new (typeid(T).name(), __FILE__, __LINE__)T(__VA_ARGS__)
#endif // _MO_ANDROID
#define MO_TYPE_CREATE(T, ...)      new T(__VA_ARGS__)
#else
#define MO_CREATE(T, ...)           new T(__VA_ARGS__)
#define MO_TYPE_CREATE(T, ...)      new T(__VA_ARGS__)
#endif
/// @define �ռ�һ�������ʵ��
#ifdef _MO_MEMORY
#define MO_ALLOC(S)                 RMemory::Alloc(NULL, NULL, S, __FILE__, __LINE__)
#define MO_TYPE_ALLOC(T)            (T*)RMemory::Alloc(MO_TYPENAME(this), MO_TYPENAME(T), sizeof(T), __FILE__, __LINE__)
#define MO_TYPES_ALLOC(T, S)        (T*)RMemory::Alloc(MO_TYPENAME(this), MO_TYPENAME(T), sizeof(T) * S, __FILE__, __LINE__)
#define MO_STATIC_ALLOC(S)          RMemory::Alloc(NULL, NULL, S, __FILE__, __LINE__)
#define MO_STATIC_TYPE_ALLOC(T)     (T*)RMemory::Alloc(NULL, MO_TYPENAME(T), sizeof(T), __FILE__, __LINE__)
#define MO_STATIC_TYPES_ALLOC(T, S) (T*)RMemory::Alloc(NULL, MO_TYPENAME(T), sizeof(T) * S, __FILE__, __LINE__)
#else
#define MO_ALLOC(S)                 malloc(S)
#define MO_TYPE_ALLOC(T)            (T*)malloc(sizeof(T))
#define MO_TYPES_ALLOC(T, S)        (T*)malloc(sizeof(T) * S)
#define MO_STATIC_ALLOC(S)          malloc(S)
#define MO_STATIC_TYPE_ALLOC(T)     (T*)malloc(sizeof(T))
#define MO_STATIC_TYPES_ALLOC(T, S) (T*)malloc(sizeof(T) * S)
#endif
/// @define �ͷ�һ�������ʵ��
#ifdef _MO_MEMORY
#define MO_FREE(P)                  if(P){RMemory::Free(P);P=NULL;}
#else
#define MO_FREE(P)                  if(P){free(P);P=NULL;}
#endif
/// @define ����һ�������ʵ��
#define MO_DELETE(P)                 if(P){delete P;P=NULL;}
#define MO_TYPE_DELETE(P)            if(P){delete P;P=NULL;}
/// @define �ͷ�һ���ӿڵ�ʵ��
#define MO_RELEASE(P)                if(P){P->Release();P=NULL;}
#define MO_DESPOSE(P)                if(P){P->Despose();P=NULL;}
#define MO_DESTORY(P)                if(P){P->Destroy();P=NULL;}

//------------------------------------------------------------
/// @define Ϊ���ú�������һ���ڴ����壬���뿪ʱ����������ڴ�й¶�����ϲ�������
#ifdef _MO_MEMORY
#define MO_TRAP(M) {TTrapper t; M;}
#else
#define MO_TRAP(M) M
#endif // _MO_MEMORY

//============================================================
// <T>������</T>
//============================================================
/// @define ת��������
#define MO_ERROR_GOTO()     goto ERROR_PROCESS
/// @define ��ʼһ��������飬һ������ֻ����һ���������
#define MO_ERROR_BEGIN      ERROR_PROCESS:{
/// @define �����������
#define MO_ERROR_END        }

//============================================================
// <T>������</T>
//============================================================
/// @define �Ƿ�ɹ�
#define MO_RS_SUCCEEDED(r)     (((HRESULT)(r)) >= 0)
/// @define �Ƿ�ʧ��
#define MO_RS_FAILED(r)        (((HRESULT)(r)) < 0)
//------------------------------------------------------------
/// @define ��̬ת�������������exdivssionת��Ϊtype-id���ͣ���û������ʱ���ͼ������֤ת���İ�ȫ�ԡ�
#define MO_CAST_STATIC(value, type)      static_cast<type>(value)
/// @define ��̬ת�������������exdivssionת����type-id���͵Ķ���
#define MO_CAST_DYNAMIC(value, type)     dynamic_cast<type>(value)
/// @define ��̬ת����type-id������һ��ָ�롢���á��������͡�����ָ����߳�Աָ��
#define MO_CAST_REINTERPRET(value, type) reinterpret_cast<type>(value)
/// @define ��̬ת����������������޸����͵�const��volatile����
#define MO_CAST_CONST(value, type)       const_cast<type>(value)
//------------------------------------------------------------
/// @define ����һ������Ϊ��������
#define MO_INLINE inline
/// @define ����һ������Ϊ�麯��
#define MO_ABSTRACT virtual
/// @define ����һ������Ϊ���麯��
#define MO_VIRTUAL virtual
/// @define ����һ������Ϊ�ɻص��Ĵ�����
#define MO_CALLBACK extern "C"
/// @define ����һ������Ϊ�ɸ��ǵ��¼�����
#define MO_EVENT virtual
/// @define ����һ������Ϊ���Ǻ���
#define MO_OVERRIDE
/// @define ����һ������Ϊ��ֹ���캯��
#define MO_EXPLCIT explicit
//------------------------------------------------------------
#ifdef _MO_WINDOWS
#define MO_INHERITS(M) using M
#else
#define MO_INHERITS(M)
#endif // _MO_WINDOWS
/// @define ��ʽ�����Ӹ���̳�һ�����캯��
#define MO_INHERIT_CONSTRUCT(M, P) M : P {};
/// @define ��ʽ�����Ӹ���̳�һ������
#define MO_INHERIT_METHOD(M, P) M { P; };
/// @define ��ʽ�����Ӹ���̳�һ������
#define MO_INHERIT_METHOD_RETURN(M, P, R) M { P; return R; };
/// @define ����һ��ջ��
//------------------------------------------------------------
#ifdef _MO_DEBUG
#define MO_CLASS_STATCK(C) \
protected: \
   PPtr operator new(TUint size){throw EError_Unsupport;} \
   TAny operator delete(PPtr pMemory){throw EError_Unsupport;}
#else
#define MO_CLASS_STATCK(C)
#endif // _MO_DEBUG
/// @define ����һ������
#ifdef _MO_DEBUG
#define MO_CLASS_HEAP(C) \
protected: \
   C(){throw EError_Unsupport;} \
   ~C(){throw EError_Unsupport;} \
   PPtr operator new(TUint size){throw EError_Unsupport;} \
   TAny operator delete(PPtr pMemory){throw EError_Unsupport;}
#else
#define MO_CLASS_HEAP(C)
#endif // _MO_DEBUG
//------------------------------------------------------------
/// @define ����δʵ�ֵĺ���
#ifdef _MO_DEBUG
#define MO_METHOD_UNSUPPORT(M)     M{throw EError_Unsupport;}
#define MO_METHOD_UNSUPPORT_NEW    PPtr operator new(TUint size){throw EError_Unsupport;}
#define MO_METHOD_UNSUPPORT_DELETE TAny operator delete(PPtr pMemory){throw EError_Unsupport;}
#else
#define MO_METHOD_UNSUPPORT(M)
#define MO_METHOD_UNSUPPORT_NEW
#define MO_METHOD_UNSUPPORT_DELETE
#endif // _MO_DEBUG

//============================================================
// <T>ϵͳ����</T>
//============================================================
#define MO_EXIT(code)   exit(code)
#define MO_PEXIT()      exit(errno)
//------------------------------------------------------------
/// @define ��������
#ifdef _MO_DEBUG
#define MO_THROW(s) MO_RAISE_DEBUG();MO_RAISE_DOWN();MO_RAISE_EXIT(0);
#else
#define MO_THROW(s) MO_RAISE_DOWN();MO_RAISE_EXIT(0);
#endif // _MO_DEBUG
//------------------------------------------------------------
/// @define ��ʼͬ����
#define MO_SYNCHRONIZED_BEGIN(L) L->Enter();
/// @define ����ͬ����
#define MO_SYNCHRONIZED_END(L)   L->Leave();

//============================================================
// <T>ϵͳ��־����</T>
//============================================================
#define MO_LOGGER_TYPE_SYSTEM 0
#define MO_LOGGER_TYPE_NET    1
#define MO_LOGGER_TYPE_STACK  3
#define MO_LOGGER_TYPE_ERROR  4

/// @define ������־�������Ŀ�ʼ
#define MO_LOGGER_BEGIN       if(true){
/// @define ������־�������Ľ���ʼ
#define MO_LOGGER_END         }
//------------------------------------------------------------
/// @define �����Ϣ
#define MO_PRINT(S) printf("%s\n--> %s\n--> %s(%d)\n", S, __PRETTY_FUNCTION__, __FILE__, __LINE__)
//------------------------------------------------------------
/// @define ���һ��������Ϣ
#ifdef _MO_LOGGER
#define MO_STATIC_DEBUG_BEGIN(M) RLogger::Error(MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, "----- %s - begin ------------------------------", #M)
#define MO_STATIC_DEBUG(M, ...)  RLogger::Debug(MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_STATIC_DEBUG_END(M)   RLogger::Error(MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, "----- %s - end --------------------------------", #M)
#define MO_DEBUG_BEGIN(M)        RLogger::Error(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, "----- %s - begin ------------------------------", #M)
#define MO_DEBUG(M, ...)         RLogger::Debug(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_DEBUG_END(M)          RLogger::Error(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, "----- %s - end --------------------------------", #M)
#define MO_DEBUG_DEEP(T, M, ...) RLogger::Debug(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, T, M, ##__VA_ARGS__)
#define MO_TRACK_DEFINE(M)       M
#define MO_TRACK(T, M, ...)      RLogger::Info(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, T, M, ##__VA_ARGS__)
#define MO_STATIC_TRACK(M, ...)  RLogger::Info (MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#else
#define MO_STATIC_DEBUG_BEGIN(M)
#define MO_STATIC_DEBUG(M, ...)
#define MO_STATIC_DEBUG_END(M)
#define MO_DEBUG_BEGIN(M)
#define MO_DEBUG(M, ...)
#define MO_DEBUG_END(M)
#define MO_DEBUG_DEEP(T, M, ...)
#define MO_TRACK_DEFINE(M)
#define MO_TRACK(T, M, ...)
#define MO_STATIC_TRACK(M, ...)
#endif // _MO_LOGGER
//------------------------------------------------------------
#define MO_STATIC_INFO(M, ...)              RLogger::Info (MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_STATIC_INFO_CHECK(R, P, M, ...)  if(!(R)){RLogger::Info (MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__); P;}
#define MO_STATIC_WARN(M, ...)              RLogger::Warn (MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_STATIC_WARN_CHECK(R, P, M, ...)  if(!(R)){RLogger::Warn (MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__); P;}
#define MO_STATIC_ERROR(M, ...)             RLogger::Error(MO_LOGGER_TYPE_ERROR, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_STATIC_ERROR_CHECK(R, P, M, ...) if(!(R)){RLogger::Error(MO_LOGGER_TYPE_ERROR, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__); P;}
#ifdef _MO_DEBUG
#define MO_STATIC_FATAL(M, ...)             RLogger::Fatal(MO_LOGGER_TYPE_STACK, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__);MO_THROW("Fatal")
#define MO_STATIC_FATAL_CHECK(R, P, M, ...) if(!(R)){RLogger::Fatal(MO_LOGGER_TYPE_STACK, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__);MO_THROW("Fatal"); P;}
#else
#define MO_STATIC_FATAL(M, ...)             RLogger::Fatal(MO_LOGGER_TYPE_STACK, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_STATIC_FATAL_CHECK(R, P, M, ...) if(!(R)){RLogger::Fatal(MO_LOGGER_TYPE_STACK, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__); P;}
#endif // _MO_DEBUG
#define MO_STATIC_DUMP(M, ...)              RLogger::Crash(MO_LOGGER_TYPE_STACK, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
//------------------------------------------------------------
#define MO_INFO(M, ...)              RLogger::Info (MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_INFO_CHECK(R, P, M, ...)  if(!(R)){RLogger::Info (MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__); P;}
#define MO_WARN(M, ...)              RLogger::Warn (MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_WARN_CHECK(R, P, M, ...)  if(!(R)){RLogger::Warn (MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__); P;}
#define MO_ERROR(M, ...)             RLogger::Error(MO_LOGGER_TYPE_ERROR, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_ERROR_CHECK(R, P, M, ...) if(!(R)){RLogger::Error(MO_LOGGER_TYPE_ERROR, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__); P;}
#ifdef _MO_DEBUG
#define MO_FATAL(M, ...)             RLogger::Fatal(MO_LOGGER_TYPE_STACK, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__);MO_THROW("Fatal");
#define MO_FATAL_CHECK(R, P, M, ...) if(!(R)){RLogger::Fatal(MO_LOGGER_TYPE_STACK, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__);MO_THROW("Fatal"); P;}
#else
#define MO_FATAL(M, ...)             RLogger::Fatal(MO_LOGGER_TYPE_ERROR, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_FATAL_CHECK(R, P, M, ...) if(!(R)){RLogger::Fatal(MO_LOGGER_TYPE_ERROR, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__); P;}
#endif // _MO_DEBUG
#define MO_STACK(M, ...)             RLogger::Crash(MO_LOGGER_TYPE_STACK, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_DUMP_STACK(M, ...)        RLogger::Crash(MO_LOGGER_TYPE_STACK, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
//------------------------------------------------------------
#ifdef _MO_DEBUG
#define MO_DEBUG_INFO(M, ...)  RLogger::Info (MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_DEBUG_WARN(M, ...)  RLogger::Warn (MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_DEBUG_ERROR(M, ...) RLogger::Error(MO_LOGGER_TYPE_ERROR, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_DEBUG_FATAL(M, ...) RLogger::Fatal(MO_LOGGER_TYPE_STACK, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__);MO_THROW("Fatal")
#else
#define MO_DEBUG_INFO(M, ...)
#define MO_DEBUG_WARN(M, ...)
#define MO_DEBUG_ERROR(M, ...)
#define MO_DEBUG_FATAL(M, ...)
#endif // _MO_DEBUG
//------------------------------------------------------------
#define MO_FATAL_UNSUPPORT() MO_STATIC_FATAL(TC("Call unsupport method."));
#define MO_FATAL_ABSTRACT()  MO_STATIC_FATAL(TC("Call abstract method."));
//------------------------------------------------------------
#ifdef _MO_WINDOWS
#define MO_STATIC_PWARN(M)  {TChar8 __mo_perror[1024];strerror_s(__mo_perror,8192,errno);RLogger::Warn( MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, TC("Call method '%s' error.(%d=%s) => %s(%d)"), TC(#M), errno, __mo_perror, __FILE__, __LINE__);}
#define MO_STATIC_PERROR(M) {TChar8 __mo_perror[1024];strerror_s(__mo_perror,8192,errno);RLogger::Error(MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, TC("Call method '%s' error.(%d=%s) => %s(%d)"), TC(#M), errno, __mo_perror, __FILE__, __LINE__);}
#define MO_STATIC_PFATAL(M) {TChar8 __mo_perror[1024];strerror_s(__mo_perror,8192,errno);RLogger::Fatal(MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, TC("Call method '%s' error.(%d=%s) => %s(%d)"), TC(#M), errno, __mo_perror, __FILE__, __LINE__);MO_THROW("Fatal");}
#define MO_PWARN(M)         {TChar8 __mo_perror[1024];strerror_s(__mo_perror,8192,errno);RLogger::Warn(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, TC("Call method '%s' error.(%d=%s) => %s(%d)"), TC(#M), errno, __mo_perror, __FILE__, __LINE__);}
#define MO_PERROR(M)        {TChar8 __mo_perror[1024];strerror_s(__mo_perror,8192,errno);RLogger::Error(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, TC("Call method '%s' error.(%d=%s) => %s(%d)"), TC(#M), errno, __mo_perror, __FILE__, __LINE__);}
#define MO_PFATAL(M)        {TChar8 __mo_perror[1024];strerror_s(__mo_perror,8192,errno);RLogger::Fatal(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, TC("Call method '%s' error.(%d=%s) => %s(%d)"), TC(#M), errno, __mo_perror, __FILE__, __LINE__);MO_THROW("Fatal");}
#else
#define MO_STATIC_PWARN(M)  RLogger::Warn( MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, "Call method '"#M"' error.(%d=%s) => %s(%d)", errno, strerror(errno), __FILE__, __LINE__)
#define MO_STATIC_PERROR(M) RLogger::Error(MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, "Call method '"#M"' error.(%d=%s) => %s(%d)", errno, strerror(errno), __FILE__, __LINE__)
#define MO_STATIC_PFATAL(M) RLogger::Fatal(MO_LOGGER_TYPE_SYSTEM, NULL, __PRETTY_FUNCTION__, "Call method '"#M"' fatal.(%d=%s) => %s(%d)", errno, strerror(errno), __FILE__, __LINE__);MO_THROW("Fatal")
#define MO_PWARN(M)         RLogger::Warn(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, "Call method '"#M"' error.(%d=%s) => %s(%d)", errno, strerror(errno), __FILE__, __LINE__)
#define MO_PERROR(M)        RLogger::Error(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, "Call method '"#M"' error.(%d=%s) => %s(%d)", errno, strerror(errno), __FILE__, __LINE__)
#define MO_PFATAL(M)        RLogger::Fatal(MO_LOGGER_TYPE_SYSTEM, this, __PRETTY_FUNCTION__, "Call method '"#M"' fatal.(%d=%s) => %s(%d)", errno, strerror(errno), __FILE__, __LINE__);MO_THROW("Fatal")
#endif // _MO_WINDOWS

//============================================================
// <T>���Զ���</T>
//============================================================
/// @define ������Ƿ�Ϊ�棬���Ϊ�٣����������
#define MO_ASSERT(R)                  if(!(R)){MO_STATIC_FATAL(TC("Assert result is invalid."));MO_RAISE_DOWN();}
#define MO_CHECK(R, P)                if(!(R)){MO_STATIC_FATAL(TC("Check result is invalid. (%s)"), TC(#R)); P;}
/// @define ��������Ƿ���ָ����Χ�ڣ����Ϊ�٣����������
#define MO_ASSERT_RANGE(R, S, E)      if((R < S) || (R >= E)){MO_STATIC_FATAL(TC("Range is invalid. (begin=%d, end=%d, current=%d)"), S, E, R);MO_RAISE_DOWN();}
#define MO_CHECK_RANGE(R, S, E, P)    if((R < S) || (R >= E)){MO_STATIC_FATAL(TC("Range is invalid. (begin=%d, end=%d, current=%d)"), S, E, R); P;}
/// @define ��������Ƿ���ָ����Χ��(�����߽�)�����Ϊ�٣����������
#define MO_ASSERT_BETWEEN(R, S, E)    if((R < S) || (R > E)){MO_STATIC_FATAL(TC("Between is invalid. (begin=%d, end=%d, current=%d)"), S, E, R);MO_RAISE_DOWN();}
#define MO_CHECK_BETWEEN(R, S, E, P)  if((R < S) || (R > E)){MO_STATIC_FATAL(TC("Between is invalid. (begin=%d, end=%d, current=%d)"), S, E, R); P;}
/// @define ���������Ƿ�ɹ������Ϊ�٣����������
#define MO_ASSERT_ERRNO(R)            if(0 != (R)){MO_STATIC_FATAL(TC("Error code is invalid. (code=%d)"), R);MO_RAISE_DOWN();}
#define MO_CHECK_ERRNO(R, P)          if(0 != (R)){MO_STATIC_FATAL(TC("Error code is invalid. (code=%d)"), R); P;}
/// @define ���һ��ָ���Ƿ�Ϊ�Ϸ�ָ�룬���Ϊ�գ����������
#define MO_ASSERT_POINTER(R)          if(NULL == (R)){MO_STATIC_FATAL(TC("Pointer is invalid."));MO_RAISE_DOWN();}
#define MO_CHECK_POINTER(R, P)        if((R) == NULL){MO_STATIC_FATAL(TC("Check pointer is null. (pointer=%s)"), TC(#R)); P;}

//============================================================
// <T>���붨��</T>
//============================================================
/// @define �Զ���ú���
#define MO_SOURCE_GETTER(T, N, V) \
   MO_INLINE T N() { \
      return V; \
   } \
/// @define �Զ����ú���
#define MO_SOURCE_SETTER(T, N, V) \
   MO_INLINE void Set##N(T value) { \
      V = value; \
   }
/// @define �Զ�������ú���
#define MO_SOURCE_GETSET(T, N, V) \
   MO_INLINE T N() { \
      return V; \
   } \
   MO_INLINE void Set##N(T value) { \
      V = value; \
   }

//============================================================
// <T>������������</T>
//============================================================
/// @define �ڴ��Ĭ���ռ���С
#define MO_MEMORY_CAPACITY        64
#define MO_MEMORY_EXTEND_CAPACITY 4096
/// @define ����Ĭ���ռ���С
#define MO_OBJECT_CAPACITY        16
#define MO_OBJECT_EXTEND_CAPACITY 1024
/// @define �ڴ��Ĭ���ռ���С
#define MO_MEMORY_BLOCK           4096

//============================================================
// <T>���ٳ�������</T>
//============================================================
#ifdef _MO_DEBUG
#define MO_TRACK_ITEMS_MAXCOUNT 16
#else
#define MO_TRACK_ITEMS_MAXCOUNT 16
#endif // _MO_DEBUG

//============================================================
// <T>������������</T>
//============================================================
#define MO_INT_MAXLENGTH      32
#define MO_FLOAT_MAXLENGTH    128
#define MO_DATE_MAXLENGTH     32
#define MO_TIME_MAXLENGTH     32
#define MO_DATETIME_MAXLENGTH 64
#define MO_TIMESPAN_MAXLENGTH 64
#define MO_ERROR_MAXLENGTH    1024*4
#define MO_DUMP_INDENT        TC("   ")
#define MO_DUMP_MAXLENGTH     1024*64

//------------------------------------------------------------
// �̶������ַ�
#define MO_FS_NUMBER_LENGTH     40
#define MO_FS_INTEGER_LENGTH    40
#define MO_FS_INTEGER64_LENGTH  60
#define MO_FS_FLOAT_LENGTH      40
#define MO_FS_DOUBLE_LENGTH     80
#define MO_FS_TIMETICK_LENGTH   40
#define MO_FS_DATETIME_LENGTH   40
#define MO_FS_CODE_LENGTH       128
#define MO_FS_NAME_LENGTH       128
#define MO_FS_LABEL_LENGTH      256
#define MO_FS_FILENAME_LENGTH   256
#define MO_FS_TEXT_LENGTH       4096
#define MO_FS_PATH_LENGTH       2048
#define MO_FS_NOTE_LENGTH       1024*4
#define MO_FS_COMMAND_LENGTH    1024*16
#define MO_FS_SQL_LENGTH        1024*256

//------------------------------------------------------------
// �ַ�����
#define MO_CP_ACP      0
#define MO_CPS_ASCII   "ASCII"
#define MO_CPS_UTF8    "UTF-8"
#define MO_CPS_GB2312  "GB2312"
#define MO_CPS_UCS4    "UCS-4"
#define MO_CPS_UNICODE "UNICODE"

//------------------------------------------------------------
// ʱ�䳣��
#define MO_DATA_DAY_US     86400000000ull
#define MO_DATA_DAY_MS     86400000ull
#define MO_DATA_DAY_SECOND 86400
#define MO_DATA_DAY_HOUR   24

//------------------------------------------------------------
// ��ѧ����
#define MO_PI       3.14159265358979323846
#define MO_PI_FLOAT 3.141593f

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ͷ��塣</T>
//============================================================
enum EObject{
   /// @enum ö������
   EEnum,
   /// @enum �����ࣨջ����
   ETools,
   /// @enum �������ͣ��Ѷ���
   EClass,
   /// @enum ���ɾ����
   EHandle,
   /// @enum ��̬������
   EReference,
   /// @enum ����̨��
   EConsole,
   /// @enum ��������
   EManager
};

//============================================================
// <T>�������Ͷ��塣</T>
//============================================================
enum EType{
   /// @enum ����
   EType_Any = 0,
   /// @enum ����ֵ����٣�
   EType_Bool = 1,
   /// @enum �з���8λ����
   EType_Int8 = 2,
   /// @enum �з���16λ����
   EType_Int16 = 3,
   /// @enum �з���32λ����
   EType_Int32 = 4,
   /// @enum �з���64λ����
   EType_Int64 = 5,
   /// @enum �䳤�з�������
   EType_Int = 6,
   /// @enum �޷���8λ����
   EType_Uint8 = 7,
   /// @enum �޷���16λ����
   EType_Uint16 = 8,
   /// @enum �޷���32λ����
   EType_Uint32 = 9,
   /// @enum �޷���64λ����
   EType_Uint64 = 10,
   /// @enum �䳤�޷�������
   EType_Uint = 11,
   /// @enum �����ȸ����� (32λ)
   EType_Float = 12,
   /// @enum ˫���ȸ����� (64λ)
   EType_Double = 13,
   /// @enum ʱ��̶� (64λ - ΢��)
   EType_TimeTick = 14,
   /// @enum ʱ��� (64λ - ΢��)
   EType_TimeSpan = 15,
   /// @enum ����ʱ�� (64λ - ΢��)
   EType_DateTime = 16,
   /// @enum 8λ�ַ�
   EType_Char8 = 17,
   /// @enum 16λ�ַ�
   EType_Char16 = 18,
   /// @enum 32λ�ַ�
   EType_Char32 = 19,
   /// @enum �䳤�ַ�
   EType_Char = 20,
   /// @enum �䳤�ַ�ָ��
   EType_String = 21,
   /// @enum ö��ֵ����ѡһ��
   EType_Enum = 22,
   /// @enum ����ֵ����ѡ�ࣩ
   EType_Set = 23,
   /// @enum ����ָ��
   EType_Ptr = 24,
   /// @enum ָ������
   EType_Type = 25,
   /// @enum �ṹ
   EType_Struct = 26,
   /// @enum ����
   EType_Object = 27,
   /// @enum �ֽڼ���
   EType_Bytes = 28,
   /// @enum ���󼯺�
   EType_Objects = 29,
   /// @enum �����
   EType_Class = 30,
   /// @enum �ֶζ���
   EType_Field = 31,
   /// @enum ���Զ���
   EType_Property = 32,
   /// @enum ��������
   EType_Method = 33,
};

//============================================================
// <T>�������塣</T>
//============================================================
enum EBoolean{
   // @member ��
   ETrue = true,
   // @member ��
   EFalse = false
};

//============================================================
// <T>�޸ķ�ʽ��</T>
//============================================================
enum EModify{
   // @member �޲���
   EModify_None,
   // @member ��ȡ
   EModify_Get,
   // @member ����
   EModify_Set,
   // @member �޸�
   EModify_Mod,
};

//============================================================
// <T>�ɹ�ֵ���塣</T>
//============================================================
enum EResult{
   // @member �ɹ�
   ESuccess = 0,
   // @member ����
   EContinue = 1,
   // @member �ͷ�
   ERelease = 1,
   // @member ʧ��
   EFailure = -1,
   // @member ��������
   EFatal = -2,
   // @member ����
   EError = -3,
   // @member ����
   EWarn = -4,
   // @member ��Ϣ
   EInfo = -5,
   // @member �ڴ����
   EMemory = -6,
   // @member �մ���
   ENull = -7,
   // @member �����ڴ���
   EExists  = -8,
   // @member ���ڴ���
   ENotExists  = -9,
   // @member �����ڴ���
   EOutRange = -10,
   // @member �ظ�����
   EDuplicate  = -11,
   // @member δ֧�ִ���
   EUnsupport = -12,
   // @member �Ƿ�����
   EInvalid = -13,
};

//============================================================
enum EFoundResult{
   // @member δ�ҵ�
   ENotFound = -1
};

//============================================================
// <T>����ֵ���塣</T>
//============================================================
enum ESystemError{
   /// @enum ϵͳδ֪����
   EError_Unknown = -1,
   /// @enum ϵͳУ������
   EError_Assert = -2,
   /// @enum �ڴ治�����
   EError_NoMemory = -3,
   /// @enum �ڴ�й¶����
   EError_MemoryLeak = -4,
   /// @enum ϵͳУ������
   EError_Unsupport = -5,
   /// @enum ��Χ�������
   EError_OutRange = -6,
   /// @enum �����ظ�
   EError_Duplicate = -7,
   /// @enum δ�ҵ�
   EError_NotFound = -8
};

//============================================================
// <T>����ֵ���塣</T>
//============================================================
enum EWarn{
};

//============================================================
// <T>��ʾֵ���塣</T>
//============================================================
enum EInfo{
};

//============================================================
// <T>��ͬ�������Ͷ��塣</T>
//============================================================
/// @type ֻ����������
typedef const void TAnyC;
/// @type ��������
typedef void TAny;
/// @type ֻ���ֽ�
typedef const unsigned char TByteC;
/// @type �ֽ�
typedef unsigned char TByte;
/// @type ֻ��ANSI�ַ�
typedef const char TChar8C;
typedef const unsigned char TUchar8C;
/// @type ANSI�ַ�
typedef char TChar8;
typedef unsigned char TUchar8;
/// @type ֻ��UNICODE�ַ�
typedef const wchar_t TChar16C;
/// @type ֻ��UNICODE�ַ�
typedef const wchar_t TChar32C;
/// @type UNICODE�ַ�
typedef wchar_t TChar16;
/// @type UNICODE�ַ�
typedef wchar_t TChar32;
/// @type ֻ��8λ����
typedef const char TInt8C;
/// @type 8λ����
typedef char TInt8;
/// @type ֻ��16λ����
typedef const short TInt16C;
/// @type 16λ����
typedef short TInt16;
/// @type ֻ��8λ�޷�������
typedef const unsigned char TUint8C;
/// @type 8λ�޷�������
typedef unsigned char TUint8;
/// @type ֻ��16λ�޷�������
typedef const unsigned short TUint16C;
/// @type 16λ�޷�������
typedef unsigned short TUint16;
/// @type ֻ��������
typedef const float TFloatC;
/// @type ������ (4�ֽڣ�����1bit��ָ��8bit��β��23bit)
typedef float TFloat;
/// @type ֻ��˫������
typedef const double TDoubleC;
/// @type ˫������ (8�ֽڣ�����1bit��ָ��11bit��β��52bit)
typedef double TDouble;
//------------------------------------------------------------
/// @type ֻ���ַ�
#if _UNICODE
typedef TChar16C TCharC;
#else
typedef TChar8C TCharC;
typedef TUchar8C TUcharC;
#endif
/// @type �ַ�
#if _UNICODE
typedef TChar16 TChar;
#else
typedef TChar8 TChar;
#endif
//------------------------------------------------------------
/// @type ֻ����������ָ��
typedef TAnyC* PPtrC;
/// @type ��������ָ��
typedef TAny* PPtr;
/// @type ֻ���ֽ�ָ��
typedef TByteC* PByteC;
/// @type �ֽ�ָ��
typedef TByte* PByte;
/// @type ֻ��ANSI�ַ�ָ��
typedef TChar8C* PChar8C;
/// @type ANSI�ַ�ָ��
typedef TChar8* PChar8;
/// @type ֻ��UNICODE�ַ�ָ��
typedef TChar16C* PChar16C;
/// @type UNICODE�ַ�ָ��
typedef TChar16* PChar16;
/// @type ֻ���ַ�ָ��
typedef TCharC* PCharC;
/// @type �ַ�ָ��
typedef TChar* PChar;
/// @type ֻ������ָ��
typedef TIntC* PIntC;
/// @type ����ָ��
typedef TInt* PInt;
/// @type ֻ��8λ����ָ��
typedef TInt8C* PInt8C;
/// @type 8λ����ָ��
typedef TInt8* PInt8;
/// @type ֻ��16λ����ָ��
typedef TInt16C* PInt16C;
/// @type 16λ����ָ��
typedef TInt16* PInt16;
/// @type ֻ��32λ����ָ��
typedef TInt32C* PInt32C;
/// @type 32λ����ָ��
typedef TInt32* PInt32;
/// @type ֻ��64λ����ָ��
typedef TInt64C* PInt64C;
/// @type 64λ����ָ��
typedef TInt64* PInt64;
/// @type ֻ���޷�������ָ��
typedef TUintC* PUintC;
/// @type �޷�������ָ��
typedef TUint* PUint;
/// @type ֻ��8λ�޷�������ָ��
typedef TUint8C* PUint8C;
/// @type 8λ�޷�������ָ��
typedef TUint8* PUint8;
/// @type ֻ��16λ�޷�������ָ��
typedef TUint16C* PUint16C;
/// @type 16λ�޷�������ָ��
typedef TUint16* PUint16;
/// @type ֻ��32λ�޷�������ָ��
typedef TUint32C* PUint32C;
/// @type 32λ�޷�������ָ��
typedef TUint32* PUint32;
/// @type ֻ��64λ�޷�������ָ��
typedef TUint64C* PUint64C;
/// @type 64λ�޷�������ָ��
typedef TUint64* PUint64;
/// @type ֻ��������ָ��
typedef TFloatC* PFloatC;
/// @type ������ָ��
typedef TFloat* PFloat;
/// @type ֻ��˫������ָ��
typedef TDoubleC* PDoubleC;
/// @type ˫������ָ��
typedef TDouble* PDouble;

//============================================================
// <T>�����������Ͷ��塣</T>
//============================================================
/// @type ����ֵ
typedef TInt TBool;
/// @type ��������
typedef TInt32 TIndex;
/// @type ���ݳ���
typedef TInt32 TLength;
/// @type ����λ��
typedef TUint32 TOffset;
/// @type ���ݴ�С
typedef size_t TSize;
/// @type ���� (��)
typedef TUint32 TDate;
/// @type ʱ�� (��)
typedef TUint32 TTime;
/// @type �̶� (��)
typedef TUint32 TTick;
/// @type ʱ�� (��)
typedef TUint32 TSpan;
/// @type ����ʱ�� (΢�� 10^-6)
typedef TUint64 TDateTime;
/// @type ʱ��� (΢�� 10^-6)
typedef TInt64 TTimeSpan;
/// @type ʱ��̶� (΢�� 10^-6)
typedef TInt64 TTimeTick;
/// @type ��ϣɢ������(�޷���64λ����)
typedef TUint64 THashCode;
/// @type ö������
typedef TInt TEnum;
/// @type ִ�н��
typedef TInt32 TResult;
//------------------------------------------------------------
/// @type 128λ�޷�����������
struct SUint128Base{
public:
   TUint64 high;
   TUint64 lower;
public:
   //------------------------------------------------------------
   // <T>�ж���Ȳ�����</T>
   MO_INLINE TBool operator==(const SUint128Base& value){
      return (high == value.high) && (lower == value.lower);
   };
   //------------------------------------------------------------
   // <T>�жϲ���Ȳ�����</T>
   MO_INLINE TBool operator!=(const SUint128Base& value){
      return (high != value.high) || (lower != value.lower);
   };
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (high == 0) && (lower == 0);
   };
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsNotEmpty(){
      return (high != 0) || (lower != 0);
   };
   //------------------------------------------------------------
   // <T>��մ���</T>
   MO_INLINE void Clear(){
      high = 0;
      lower = 0;
   };
};
//------------------------------------------------------------
/// @type 128λ�޷�������
struct SUint128 : public SUint128Base{
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   SUint128(){
      high = 0;
      lower = 0;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   SUint128(TInt value){
#ifdef _MO_DEBUG
      if(0 != value){
         MO_THROW("Invalid value");
      }
#endif
      high = value;
      lower = value;
   }
public:
   //------------------------------------------------------------
   friend TBool operator==(TInt value1, const SUint128& value2){
#ifdef _MO_DEBUG
      if(0 != value1){
         MO_THROW("Invalid value");
      }
#endif
      return (value2.high == (TUint64)value1) && (value2.lower == (TUint64)value1);
   }
   //------------------------------------------------------------
   friend TBool operator!=(TInt value1, const SUint128& value2){
#ifdef _MO_DEBUG
      if(0 != value1){
         MO_THROW("Invalid value");
      }
#endif
      return (value2.high != (TUint64)value1) || (value2.lower != (TUint64)value1);
   }
public:
   //------------------------------------------------------------
   // <T>�ж���Ȳ�����TODO:��ʱ����</T>
   MO_INLINE void operator=(TInt value){
#ifdef _MO_DEBUG
      if(0 != value){
         MO_THROW("Invalid value");
      }
#endif
      high = (TUint64)value;
      lower = (TUint64)value;
   };
public:
   //------------------------------------------------------------
   // <T>�ж���Ȳ�����TODO:��ʱ����</T>
   MO_INLINE TBool operator==(TInt64 value){
#ifdef _MO_DEBUG
      if(0 != value){
         MO_THROW("Invalid value");
      }
#endif
      return (high == (TUint64)value) && (lower == (TUint64)value);
   };
   //------------------------------------------------------------
   // <T>�ж���Ȳ�����TODO:��ʱ����</T>
   MO_INLINE TBool operator!=(TInt64 value){
#ifdef _MO_DEBUG
      if(0 != value){
         MO_THROW("Invalid value");
      }
#endif
      return (high != (TUint64)value) || (lower != (TUint64)value);
   };
public:
   //------------------------------------------------------------
   // <T>�ж���Ȳ�����</T>
   MO_INLINE TBool operator==(const SUint128& value){
      return (high == value.high) && (lower == value.lower);
   };
   //------------------------------------------------------------
   // <T>�жϲ���Ȳ�����</T>
   MO_INLINE TBool operator!=(const SUint128& value){
      return (high != value.high) || (lower != value.lower);
   };
};
typedef SUint128 TUint128;

//============================================================
/// @type ���
typedef struct SHandle{
   /// @attribute �������
   TEnum typeCd;
   /// @attribute �������
   TIndex Index;
   /// @attribute ��־��Ϣ
   TUint Flag;
} THandle;
//------------------------------------------------------------
/// @type ��Դ���
typedef struct SResource{
   /// @attribute ��Դ����
   TUint Type;
   /// @attribute ��Դ����
   TUint Index;
   /// @attribute ��־��Ϣ
   TUint Flag;
} TResource;

//============================================================
// <T>�����ݶ���</T>
// <P>���Ա�ʾ�����Ƿ�Ϊ�ա�</P>
//============================================================
template <typename T>
struct SValue{
protected:
   TBool _null;
   T _value;
public:
   //------------------------------------------------------------
   // ���������ݶ���
   SValue() {
      _null = ETrue;
   }
   //------------------------------------------------------------
   // ����ָ�����ݵĿ����ݶ���
   SValue(T value) {
      _null = EFalse;
      _value = value;
   }
public:
   //------------------------------------------------------------
   // ����������ݡ�
   MO_INLINE operator const T() const{
      return _value;
   }
public:
   //------------------------------------------------------------
   // �ж����������Ƿ�Ϊ�ա�
   MO_INLINE TBool IsNull() const{
      return _null;
   }
   //------------------------------------------------------------
   // ����������ݡ�
   MO_INLINE T Get() const{
      return _value;
   }
   //------------------------------------------------------------
   // ������������Ϊָ���������ݡ�
   MO_INLINE void Set(T value) {
      _null = EFalse;
      _value = value;
   }
   //------------------------------------------------------------
   // ������������Ϊ�ա�
   MO_INLINE void Clear() {
      _null = ETrue;
   }
};
//------------------------------------------------------------
typedef SValue<TBool> SBool;
typedef SValue<TByte> SByte;
typedef SValue<TChar> SChar;
typedef SValue<TChar8> SChar8;
typedef SValue<TChar16> SChar16;
typedef SValue<TInt> SInt;
typedef SValue<TInt8> SInt8;
typedef SValue<TInt16> SInt16;
typedef SValue<TInt32> SInt32;
typedef SValue<TInt64> SInt64;
typedef SValue<TUint> SUint;
typedef SValue<TUint8> SUint8;
typedef SValue<TUint16> SUint16;
typedef SValue<TUint32> SUint32;
typedef SValue<TUint64> SUint64;
typedef SValue<TFloat> SFloat;
typedef SValue<TDouble> SDouble;

//============================================================
// ǿ��ת��������ָ��ǿ��ת����ģ�庯��
//============================================================
template<class S, class T>
T MO_CAST_FORCE(S value){
   union{
      T Target;
      S Source;
   } _transfer;
   _transfer.Source = value;
   return _transfer.Target;
}

//============================================================
// <T>�ڴ���Ϣ��</T>
//============================================================
struct MO_CM_DECLARE SMemoryInfo{
public:
   TInt64 lengthAlloc;
   TInt64 lengthFree;
};

//============================================================
// <T>�ڴ����̨�ӿڡ�</T>
//
// @face
// @history 130331 MAOCY ����
//============================================================
class MO_CM_DECLARE IMemoryStorage{
public:
   //------------------------------------------------------------
   // <T>�����ڴ����̨�ӿڡ�</T>
   MO_ABSTRACT ~IMemoryStorage(){
   }
public:
   MO_VIRTUAL TBool FetchInfo(SMemoryInfo* pInfo) = 0;
public:
   MO_VIRTUAL TBool IsAble() = 0;
   MO_VIRTUAL void Enable() = 0;
   MO_VIRTUAL void Disable(TBool detail = EFalse) = 0;
public:
   MO_VIRTUAL TAny* Alloc(TChar8C* pOwnerName, TChar8C* pTypeName, TInt size, TChar8C* pFileName = NULL, TInt lineNumber = 0) = 0;
   MO_VIRTUAL void Free(TAny* pMemory) = 0;
public:
   MO_VIRTUAL void Reset() = 0;
   MO_VIRTUAL void Dump(TBool detail = EFalse) = 0;
};

//============================================================
// <T>�ڴ�������ࡣ</T>
//============================================================
class MO_CM_DECLARE RMemory{
protected:
   static IMemoryStorage* _pStorage;
public:
   static IMemoryStorage* Storage();
   static void LinkStorage(IMemoryStorage* pStorage);
public:
   static TAny* Alloc(TChar8C* pOwnerName, TChar8C* pTypeName, TSize size, TChar8C* pFileName = NULL, TInt lineNumber = 0);
   static void Free(TAny* pMemory);
public:
   static void Fill(TAny* pMemory, TUint size, TInt value);
   static void Copy(const TAny* pSource, TAny* pTarget, TUint size);
   static void Clear(TAny* pMemory, TUint size);
};

//============================================================
// <T>��־����</T>
//
// @enum
// @history 091204 MAOCY ����
//============================================================
enum ELoggerLevel{
   ELoggerLevel_Debug,
   ELoggerLevel_Info,
   ELoggerLevel_Warn,
   ELoggerLevel_Error,
   ELoggerLevel_Fatal,
   ELoggerLevel_Crash,
};

//============================================================
// <T>��־����̨�ӿڡ�</T>
//
// @class
// @history 091209 MAOCY ����
//============================================================
class MO_CM_DECLARE ILoggerConsole{
public:
   //------------------------------------------------------------
   // <T>��־����̨�ӿڡ�</T>
   MO_ABSTRACT ~ILoggerConsole(){
   }
public:
   MO_VIRTUAL TBool Output(TInt type, ELoggerLevel level, TAnyC* pSender, TCharC* pMethod, TTimeTick start, TCharC* pMessage, va_list& params) = 0;
};

//============================================================
// <T>��־�����ࡣ</T>
//
// @class
// @history 091209 MAOCY ����
//============================================================
class MO_CM_DECLARE RLogger{
protected:
   static ILoggerConsole* _pConsole;
public:
   static void Link(ILoggerConsole* pConsole);
   static ILoggerConsole* Console();
public:
   static void Output(TInt type, ELoggerLevel level, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, va_list& params);
   //------------------------------------------------------------
   static void Debug(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...);
   static void Debug(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...);
   static void Info (TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...);
   static void Info (TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...);
   static void Warn (TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...);
   static void Warn (TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...);
   static void Error(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...);
   static void Error(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...);
   static void Fatal(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...);
   static void Fatal(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...);
   static void Crash(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...);
   static void Crash(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...);
};

//============================================================
// <T>ָ�����͵�ֻ������ָ�롣</T>
// <P>����ᱣ֤��ǰ����ָ���������κ�ʱ�򲻻ᱻ�޸ġ�</P>
//
// @template
//============================================================
template <typename T>
class TPtrC{
protected:
   // @attribute ֻ������ָ��
   const T* _pMemory;
   // @attribute ���ݳ���
   TSize _length;
protected:
   //------------------------------------------------------------
   // <T>����ֻ��ָ�����</T>
   TPtrC(){
   }
public:
   //------------------------------------------------------------
   // <T>����ֻ��ָ�����</T>
   TPtrC(const T* pMemory, TSize length){
      Set(pMemory, length);
   }
   //------------------------------------------------------------
   // <T>����ֻ��ָ�����</T>
   TPtrC(const TPtrC<T>& ptr){
      Set(ptr);
   }
public:
   //------------------------------------------------------------
   // <T>����ָ�븴�Ʋ�����</T>
   void operator=(const TPtrC<T>& ptr){
      Set(ptr);
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   const T* operator[](TInt index) const{
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
public:
   //------------------------------------------------------------
   // <T>���ֻ������ָ�롣</T>
   MO_INLINE const T* MemoryC() const{
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TSize Length() const{
      return _length;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == _length);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const T* pMemory, TSize length){
      MO_ASSERT(pMemory);
      _pMemory = pMemory;
      _length = length;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const TPtrC<T>& ptr){
      _pMemory = ptr._pMemory;
      _length = ptr._length;
   }
};
//------------------------------------------------------------
typedef TPtrC<TAny>    TAnyPtrC;
typedef TPtrC<TBool>   TBoolPtrC;
typedef TPtrC<TByte>   TBytePtrC;
typedef TPtrC<TChar>   TCharPtrC;
typedef TPtrC<TChar8>  TChar8PtrC;
typedef TPtrC<TChar16> TChar16PtrC;
typedef TPtrC<TChar32> TChar32PtrC;
typedef TPtrC<TInt>    TIntPtrC;
typedef TPtrC<TInt8>   TInt8PtrC;
typedef TPtrC<TInt16>  TInt16PtrC;
typedef TPtrC<TInt32>  TInt32PtrC;
typedef TPtrC<TInt64>  TInt64PtrC;
typedef TPtrC<TUint>   TUintPtrC;
typedef TPtrC<TUint8>  TUint8PtrC;
typedef TPtrC<TUint16> TUint16PtrC;
typedef TPtrC<TUint32> TUint32PtrC;
typedef TPtrC<TUint64> TUint64PtrC;
typedef TPtrC<TFloat>  TFloatPtrC;
typedef TPtrC<TDouble> TDoublePtrC;

//============================================================
// <T>ָ�����͵�����ָ�롣</T>
// <P>������ԸĶ�����ָ������ݡ�</P>
//
// @template
//============================================================
template <typename T>
class TPtr{
protected:
   // @attribute ֻ������ָ��
   T* _pMemory;
   // @attribute ���ݳ���
   TInt* _pLength;
   // @attribute ��������
   TInt _capacity;
protected:
   //------------------------------------------------------------
   // <T>����ָ�����</T>
   TPtr(){
   }
public:
   //------------------------------------------------------------
   // <T>��������ָ�롣</T>
   TPtr(T* pMemory, TInt* pLength){
      Set(pMemory, pLength);
   }
   //------------------------------------------------------------
   // <T>��������ָ�롣</T>
   TPtr(T* pMemory, TInt* pLength, TInt capacity){
      Set(pMemory, pLength, capacity);
   }
   //------------------------------------------------------------
   // <T>��������ָ�롣</T>
   TPtr(const TPtr<T>& ptr){
      Set(ptr);
   }
public:
   //------------------------------------------------------------
   // <T>����ָ�븴�Ʋ�����</T>
   void operator=(const TPtr<T>& ptr) {
      Set(ptr);
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   T operator[](TInt index){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(index, 0, *_pLength);
      return _pMemory[index];
   }
public:
   //------------------------------------------------------------
   // <T>���ֻ������ָ�롣</T>
   MO_INLINE const T* MemoryC() const{
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE T* Memory() const{
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE TInt Length(){
      return *_pLength;
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE void SetLength(TInt length){
      MO_ASSERT_RANGE(length, 0, _capacity);
      *_pLength = length;
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE TSize Capacity(){
      return _capacity;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == *_pLength);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(T* pMemory, TInt* pLength){
      MO_ASSERT(pMemory);
      MO_ASSERT(pLength);
      _pMemory = pMemory;
      _pLength = pLength;
      _capacity = *pLength;
   }
   //------------------------------------------------------------
   // <T>����ָ�����ݡ�</T>
   MO_INLINE void Set(T* pMemory, TInt* pLength, TInt capacity){
      MO_ASSERT(pMemory);
      MO_ASSERT(pLength);
      _pMemory = pMemory;
      _pLength = pLength;
      _capacity = capacity;
   }
   //------------------------------------------------------------
   // <T>����ָ�����ݡ�</T>
   MO_INLINE void Set(const TPtr<T>& ptr){
      _pMemory = ptr._pMemory;
      _pLength = ptr._pLength;
      _capacity = ptr._capacity;
   }
};
//------------------------------------------------------------
typedef TPtr<TAny> TAnyPtr;
typedef TPtr<TBool> TBoolPtr;
typedef TPtr<TByte> TBytePtr;
typedef TPtr<TChar> TCharPtr;
typedef TPtr<TChar8> TChar8Ptr;
typedef TPtr<TChar16> TChar16Ptr;
typedef TPtr<TChar32> TChar32Ptr;
typedef TPtr<TInt> TIntPtr;
typedef TPtr<TInt8> TInt8Ptr;
typedef TPtr<TInt16> TInt16Ptr;
typedef TPtr<TInt32> TInt32Ptr;
typedef TPtr<TInt64> TInt64Ptr;
typedef TPtr<TUint> TUintPtr;
typedef TPtr<TUint8> TUint8Ptr;
typedef TPtr<TUint16> TUint16Ptr;
typedef TPtr<TUint32> TUint32Ptr;
typedef TPtr<TUint64> TUint64Ptr;
typedef TPtr<TFloat> TFloatPtr;
typedef TPtr<TDouble> TDoublePtr;

//============================================================
// <T>�Զ�����ָ�롣</T>
// <P>����������psXXX</P>
//
// @template
//============================================================
template <typename T>
class TSharedPtr{
protected:
   T* _pObject;
   TInt _refer;
protected:
   //------------------------------------------------------------
   // <T>����ָ�롣</T>
   TSharedPtr(){
      _pObject = NULL;
      _refer = 0;
   }
   //------------------------------------------------------------
   // <T>����ָ�롣</T>
   TSharedPtr(T* pObject){
      _pObject = pObject;
      _refer = 0;
   }
   //------------------------------------------------------------
   // <T>��������ָ�롣</T>
   ~TSharedPtr(){
      Decrease();
   }
public:
   //------------------------------------------------------------
   // <T>��ȡ����ָ�롣</T>
   MO_INLINE T& operator *(){
      return _pObject;
   }
   //------------------------------------------------------------
   // <T>��ȡ����ָ�롣</T>
   MO_INLINE T operator->(){
      MO_ASSERT(_pObject);
      return _pObject;
   }
   //------------------------------------------------------------
   // <T>��ȡ����ָ�롣</T>
   MO_INLINE void operator=(TSharedPtr& ptr){
      _pObject = *ptr;
      _refer = ptr.Refer();
      ptr.Reset();
   }
public:
   //------------------------------------------------------------
   // <T>������ô�����</T>
   TInt Refer(){
      return _refer;
   }
   //------------------------------------------------------------
   // <T>�������ô�����</T>
   void Increase(){
      _refer++;
   }
   //------------------------------------------------------------
   // <T>�������ô�����</T>
   void Decrease(){
      _refer--;
      if(_refer <= 0){
         //MO_DELETE(_pObject);
      }
   }
   //------------------------------------------------------------
   // <T>���ö���</T>
   void Reset(){
      _pObject = NULL;
      _refer++;
   }
   //------------------------------------------------------------
   // <T>ǿ���ͷŶ���</T>
   void Release(){
      if(NULL != _pObject){
         //MO_DELETE(_pObject);
      }
      _pObject = NULL;
      _refer++;
   }
};

//============================================================
// <P>����������pwXXX</P>
template <typename T>
class TWeekPtr{
};

//============================================================
// <P>����������ptXXX</P>
template <typename T>
class TIntrusivePtr{
};

MO_NAMESPACE_END

#endif // __MO_CM_RUNTIME_H__
