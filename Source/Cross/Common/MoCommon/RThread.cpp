#include "MoCmThread.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����̱߳�ʶ��</T>
//
// @static
// @return �̱߳�ʶ
//============================================================
TInt RThread::CurrentCode(){
   TInt id = 0;
#ifdef _MO_SYS_WINDOWS
   id = GetCurrentThreadId();
#endif // _MO_SYS_WINDOWS
#ifdef _MO_LINUX
#ifndef __CYGWIN__
   id = syscall(__NR_gettid);
#endif // __CYGWIN__
#endif // _MO_LINUX
   return id;
}

//============================================================
// <T>����̱߳�ʶ��</T>
//
// @static
// @return �̱߳�ʶ
//============================================================
TThreadId RThread::CurrentId(){
#ifdef _MO_SYS_WINDOWS
   TThreadId id = GetCurrentThreadId();
#endif // _MO_SYS_WINDOWS
#ifdef _MO_SYS_LINUX
   TThreadId id = pthread_self();
#endif // _MO_SYS_LINUX
   return id;
}

//============================================================
// <T>���߳�������ָ��������</T>
//
// @static
// @param cRunable �����к���
//============================================================
IThread* RThread::Process(TRunableHandle cRunable){
   FThreadRunable* pThread = MO_CREATE(FThreadRunable, cRunable);
   pThread->Start();
   return pThread;
}

MO_NAMESPACE_END
