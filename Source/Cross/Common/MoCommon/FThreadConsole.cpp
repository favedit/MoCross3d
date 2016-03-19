#ifdef _MO_LINUX
#include <unistd.h>
#endif
#include "MoCmThread.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����̹߳�������</T>
//============================================================
FThreadConsole::FThreadConsole(){
   _index = 0;
   _pThreads = MO_PTR_CREATE(FThreadSet);
}

//============================================================
// <T>�ͷ��̹߳�������</T>
//============================================================
FThreadConsole::~FThreadConsole(){
   MO_PTR_DELETE(_pThreads);
}

//============================================================
// <T>ע���̶߳���</T>
//
// @param pThread �̶߳���
//============================================================
void FThreadConsole::Register(FThread* pThread){
   MO_ASSERT(pThread);
   // ����̱߳�ʶ
   TThreadId threadId = pThread->ThreadId();
   // ����Ƿ��ظ�
   _locker.Enter();
   if(_pThreads->Contains(threadId)){
      MO_THROW("Thread id duplicate.");
   }
   // �洢�߳�
   _pThreads->Set(threadId, pThread);
   pThread->SetIndex(++_index);
   _locker.Leave();
}

//============================================================
// <T>ע���̶߳���</T>
//
// @param pThread �̶߳���
//============================================================
void FThreadConsole::Unregister(FThread* pThread){
   MO_ASSERT(pThread);
   TThreadId threadId = pThread->ThreadId();
   // ����Ƿ��ظ�
   if(!_pThreads->Contains(threadId)){
      MO_THROW("Thread id is not founded.");
   }
   _locker.Enter();
   _pThreads->Remove(threadId);
   _locker.Leave();
}

//============================================================
// <T>��õ�ǰ�̶߳���</T>
//
// @param threadId �̱߳�ʶ
//============================================================
FThread* FThreadConsole::Current(){
   TThreadId threadId = RThread::CurrentId();
   return Find(threadId);
}

//============================================================
// <T>�����̱߳�ʶ����̶߳���</T>
//
// @param threadId �̱߳�ʶ
// @return �̶߳���
//============================================================
FThread* FThreadConsole::Get(TThreadId threadId){
   FThread* pThread = NULL;
   _locker.Enter();
   pThread = _pThreads->Get(threadId);
   MO_ASSERT(pThread);
   _locker.Leave();
   return pThread;
}

//============================================================
// <T>�����̱߳�ʶ����̶߳���</T>
//
// @param threadId �̱߳�ʶ
// @return �̶߳���
//============================================================
FThread* FThreadConsole::Find(TThreadId threadId){
   FThread* pThread = NULL;
   _locker.Enter();
   pThread = _pThreads->Find(threadId);
   _locker.Leave();
   return pThread;
}

//============================================================
/*void RThreadManager::Track(){
   if(NULL == _pTrackThread){
      _pTrackThread = MO_CREATE(FThreadMemoryTrackThread);
      _pTrackThread->Start();
   }
}*/

MO_NAMESPACE_END
