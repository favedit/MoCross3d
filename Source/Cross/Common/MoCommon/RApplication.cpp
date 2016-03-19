#ifdef _MO_WINDOWS
#endif
#ifdef _MO_LINUX
#ifndef __CYGWIN__
#include <execinfo.h>
#include <ucontext.h>
#endif
#include <sys/file.h>
#include <unistd.h>
#include <dlfcn.h>
#ifndef NO_CPP_DEMANGLE
#include <cxxabi.h>
#endif
#ifdef REG_RIP
#define SIGSEGV_STACK_IA64
#elif defined(REG_EIP)
#define SIGSEGV_STACK_X86
#else
#define SIGSEGV_STACK_GENERIC
#endif
#endif
#include "MoCmSystem.h"

#define MO_BACKTRACE_MAXCOUNT 64

MO_NAMESPACE_BEGIN

//============================================================
// <T>���ϵͳ��ǰ·��</T>
//
// @return ϵͳ��ǰ·��
//============================================================
TFsPath RApplication::GetCurrentDirectory(){
   TFsPath path;
#ifdef _MO_WINDOWS
   ::GetCurrentDirectory(path.Size(), path.Memory());
#else
   TChar* pResult = getcwd(path.Memory(), path.Size());
   MO_ASSERT(pResult);
#endif
   path.Fix();
   return path;
}

//============================================================
// <T>��ÿ�ִ���ļ��ĵ�ǰ·����</T>
//
// @return ��ǰ·��
//============================================================
TFsPath RApplication::GetExecuteDirectory(){
   TFsPath path;
#ifdef _MO_WINDOWS
   // TODO:
#else
   TInt length = readlink("//proc/self/exe", path.Memory(), path.Size());
   MO_ASSERT(length < path.Size());
   path.SetLength(length);
#endif
   return path;
}

#ifdef _MO_WINDOWS
//============================================================
// <T>��õ�ǰӦ�ó���ľ����</T>
//
// @history 100424 MAOCY ����
//============================================================
TInstance RApplication::Hinstance(){
   return _pInstance->Hinstance();
}

//============================================================
TInt RApplication::CommandShow(){
   return _pInstance->CommandShow();
}
#endif

//============================================================
// <T>��װ��׽����</T>
//
// @return ������
//============================================================
 TInt RApplication::InstallCatcher(){
   return _pInstance->InstallCatcher();
}

//============================================================
// <T>��ÿ�ִ���ļ��ĵ�ǰ·����</T>
//
// @history 100302 MAOCY ����
//============================================================
TInt RApplication::InstallDaemon(){
   return _pInstance->InstallDaemon();
}

MO_NAMESPACE_END
