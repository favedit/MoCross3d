#include "MoCmThread.h"
#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>ִ���̴߳���(WINDOW)��</T>
//
// @param pParam ����ָ��
// @return ������
//============================================================
#ifdef _MO_SYS_WINDOWS
TDword MO_STDCALL __MO_THREAD_CALLBACK(TAny* pParam){
   // ����̶߳���
   FThread* pThread = (FThread*)pParam;
   MO_ASSERT(pThread);
   // ִ���̴߳���
   TInt result = EFailure;
   if(pThread->OnStart()){
      try{
         MO_TRAP( result = pThread->Process() );
      }catch(TInt code){
         pThread->OnCancel(code);
      }
      pThread->OnFinish(result);
   }
   // �ͷ��߳���Դ����������߳��飬�����߳��鸺���ͷ��̡߳�
   if(NULL == pThread->ThreadGroup()){
      MO_PTR_DELETE(pThread);
   }
   return result;
}
#endif // _MO_SYS_WINDOWS

//============================================================
// <T>ִ���̴߳���(LINUX)��</T>
//
// @param pParam ����ָ��
// @return ������
//============================================================
#ifdef _MO_SYS_LINUX
TAny* MO_STDCALL __MO_THREAD_CALLBACK(TAny* pParam){
   // ����̶߳���
   FThread* pThread = (FThread*)pParam;
   MO_ASSERT(pThread);
   // ���Լ������̹߳�������
   RThreadManager::Instance().Register(pThread);
   // ִ���̴߳���
   TInt result = EFailure;
   if(pThread->OnStart()){
#ifdef _MO_ANDROID
      result = pThread->Process();
#else
      try{
         MO_TRAP( result = pThread->Process() );
      }catch(TInt code){
         pThread->OnCancel(code);
      }
#endif // _MO_ANDROID
      pThread->OnFinish(result);
   }
   // �ͷ��߳���Դ
   pthread_exit((TAny*)result);
   MO_PTR_DELETE(pThread);
   return (TAny*)result;
}
#endif // _MO_SYS_LINUX

//============================================================
// <T>�����̴߳���</T>
//============================================================
FThread::FThread(){
   _typeCd = EThread_Thread;
   _flag = 0;
   _index = 1;
   _code = TC("WRK");
   _name = TC("Work Thread");
   _handle = 0;
   _status = EThreadStatus_Initialize;
   // ����߳���
   MO_CLEAR(_pThreadGroup);
   // �����߳�����
   _pThreadTrap = MO_PTR_CREATE(FThreadTrap);
   // �����߳��ڴ�
   _pThreadMemory = MO_PTR_CREATE(FThreadMemory);
#ifdef _MO_LINUX
   // ��ʼ��������
   pthread_mutex_init(&_mutex, NULL);
   // ��ʼ����������
   pthread_cond_init(&_condition, NULL);
#endif
}

//============================================================
// <T>��ֹ�̴߳���</T>
//============================================================
FThread::~FThread(){
#ifdef _MO_WINDOWS
   // �ر��߳̾��
   if(NULL != _handle){
      CloseHandle(_handle);
      _handle = NULL;
   }
#else
   pthread_mutex_destroy(&_mutex);
   pthread_cond_destroy(&_condition);
#endif
   // �ͷ�����
   MO_PTR_DELETE(_pThreadTrap);
   // �ͷ��ڴ�
   MO_PTR_DELETE(_pThreadMemory);
   // ���Լ����̹߳�������ע��
   if(NULL != RThreadManager::InstancePtr()){
      RThreadManager::Instance().Unregister(this);
   }
}

//============================================================
// <T>����߳����ȼ���</T>
//
// @return �߳����ȼ�
//============================================================
TThreadHandle FThread::Handle() const{
   return _handle;
}

//============================================================
// <T>����߳����ȼ���</T>
//
// @return �߳����ȼ�
//============================================================
TThreadId FThread::ThreadId() const{
#ifdef _MO_WINDOWS
   return _threadId;
#else
   return _handle;
#endif
}

//============================================================
// <T>����߳����ȼ���</T>
//
// @return �߳����ȼ�
//============================================================
EThreadPriority FThread::Priority() const{
   return _priority;
}

//============================================================
// <T>�����߳����ȼ���</T>
//
// @param priority �߳����ȼ�
//============================================================
void FThread::SetPriority(EThreadPriority priority){
   _priority = priority;
}

//============================================================
// <T>�ж��Ƿ��߳�״̬��</T>
//
// @param status ״̬
// @return �Ƿ��߳�״̬
//============================================================
TBool FThread::IsStatus(EThreadStatus status) const{
   return (_status == status);
}

//============================================================
// <T>����߳�״̬��</T>
//
// @return �߳�״̬
//============================================================
EThreadStatus FThread::Status() const{
   return _status;
}

//============================================================
// <T>�ж��߳��Ƿ�ֹͣ��</T>
//
// @return �Ƿ�ֹͣ
//============================================================
TBool FThread::IsStop() const{
   if(EThreadStatus_Running == _status){
      return EFalse;
   }else if(EThreadStatus_Suspend == _status){
      return EFalse;
   }else if(EThreadStatus_Wait == _status){
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>����߳��顣</T>
//
// @return �߳���
//============================================================
FThreadGroup* FThread::ThreadGroup(){
   return _pThreadGroup;
}

//============================================================
// <T>�����߳��顣</T>
//
// @param pThreadGroup �߳���
//============================================================
void FThread::SetThreadGroup(FThreadGroup* pThreadGroup){
   _pThreadGroup = pThreadGroup;
}

//============================================================
// <T>����߳����塣</T>
//
// @return �߳����ȼ�
//============================================================
FThreadTrap* FThread::ThreadTrap(){
   return _pThreadTrap;
}

//============================================================
// <T>����߳��ڴ档</T>
//
// @return �߳����ȼ�
//============================================================
FThreadMemory* FThread::ThreadMemory(){
   return _pThreadMemory;
}

//============================================================
// <T>�߳̿�ʼ����</T>
//============================================================
TBool FThread::OnStart(){
   _status = EThreadStatus_Running;
#ifdef _MO_LINUX
#ifndef __CYGWIN__
   TInt threadPid = syscall(__NR_gettid);
   MO_INFO(TC("Execute thread start (name=%s, handle=%lu, tid=%d)"),
         (TCharC*)_name, _handle, threadPid);
#endif
#else
   MO_INFO(TC("Execute thread start (name=%s, handle=%lu)"),
         (TCharC*)_name, _handle);
#endif
   return ETrue;
}

//============================================================
// <T>�߳�ȡ������</T>
//============================================================
TBool FThread::OnCancel(TInt code){
   _status = EThreadStatus_Cancel;
   MO_ERROR(TC("Execute thread cancel (name=%s, code=%d)"), (TCharC*)_name, code);
   return ETrue;
}

//============================================================
// <T>�߳̽�������</T>
//============================================================
TBool FThread::OnFinish(TInt result){
   _status = EThreadStatus_Finish;
   MO_INFO(TC("Execute thread finish (name=%s, result=%d)"), (TCharC*)_name, result);
   return ETrue;
}

//============================================================
// <T>�����̴߳���</T>
//
// @return ������
//============================================================
TResult FThread::Start(){
#ifdef _MO_SYS_WINDOWS
   MO_ASSERT(NULL == _handle);
   // �����ȴ��߳�
   _handle = CreateThread(NULL, 0, __MO_THREAD_CALLBACK, this, CREATE_SUSPENDED, &_threadId);
   MO_ASSERT(_handle);
   // ���Լ������̹߳�������
   RThreadManager::Instance().Register(this);
   // ��ʼִ���߳�
   ResumeThread(_handle);
#endif // _MO_SYS_WINDOWS
#ifdef _MO_SYS_LINUX
   TInt result = pthread_create(&_handle, NULL, __MO_THREAD_CALLBACK, this);
   if(ESuccess != result){
      MO_PFATAL("pthread_create");
   }
#endif // _MO_SYS_LINUX
   return ESuccess;
}

//============================================================
// <T>����ִ��һ�Ρ�</T>
//
// @return ������
//============================================================
TResult FThread::Idle(){
   MO_LIB_IDLE();
   return ESuccess;
}

//============================================================
// <T>�����̴߳���</T>
//
// @return ������
//============================================================
TResult FThread::Suspend(){
   MO_ASSERT(_handle);
   MO_DEBUG(TC("Thread suspend begin.(thread=0x%08X)"), this);
   _status = EThreadStatus_Suspend;
#ifdef _MO_WINDOWS
   SuspendThread(_handle);
#else
   pthread_mutex_lock(&_mutex);
   pthread_cond_wait(&_condition, &_mutex);
   pthread_mutex_unlock(&_mutex);
#endif
   MO_DEBUG(TC("Thread suspend end.(thread=0x%08X)"), this);
   return ESuccess;
}

//============================================================
// <T>�����̴߳���</T>
//
// @return ������
//============================================================
TResult FThread::Resume(){
   MO_ASSERT(_handle);
   MO_DEBUG(TC("Thread resume begin.(thread=0x%08X)"), this);
#ifdef _MO_WINDOWS
   ResumeThread(_handle);
#else
   pthread_mutex_lock(&_mutex);
   pthread_cond_signal(&_condition);
   pthread_mutex_unlock(&_mutex);
#endif
   _status = EThreadStatus_Running;
   MO_DEBUG(TC("Thread resume end.(thread=0x%08X)"), this);
   return ESuccess;
}

//============================================================
// <T>�ȴ������߳̽�����</T>
//
// @return ������
//============================================================
TResult FThread::Join(IThread* pThread){
#ifdef _MO_WINDOWS
   MO_ASSERT(_handle);
   WaitForSingleObject(pThread->Handle(), INFINITE);
#else
   TAny* pResult;
   pthread_join(pThread->Handle(), (TAny**)&pResult);
#endif
   return ESuccess;
}

//============================================================
// <T>�ȴ������߳̽�����</T>
//============================================================
TAny* FThread::Wait(){
   // ֹͣʱֱ�ӷ���
   MO_ASSERT(_handle);
   TAny* pResult = NULL;
#ifdef _MO_WINDOWS
   WaitForSingleObject(_handle, INFINITE);
#else
   pthread_join(_handle, (TAny**)&pResult);
#endif // _MO_WINDOWS
   return pResult;
}

//============================================================
// <T>ֹͣ�̴߳���</T>
// <P>ֻ��һ����־λ���������</P>
//
// @return ������
//============================================================
TResult FThread::Stop(){
   MO_ASSERT(_handle);
   _status = EThreadStatus_Stop;
   return ESuccess;
}

//============================================================
// <T>ֹͣ�̴߳���</T>
//
// @return ������
//============================================================
TResult FThread::Terminate(){
#ifdef _MO_WINDOWS
   MO_ASSERT(_handle);
   TerminateThread(_handle, 0);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   pthread_cancel(_handle);
#endif // _MO_LINUX
#ifdef _MO_FLASCC
   pthread_cancel(_handle);
#endif // _MO_FLASCC
#ifdef _MO_ANDROID
   // MO_FATAL_UNSUPPORT();
#endif // _MO_ANDROID
   return ESuccess;
}

//============================================================
// <T>��ǰ�߳�˯�ߴ���</T>
//
// @param interval ���
//============================================================
void FThread::Sleep(TInt interval){
   MO_LIB_SLEEP(interval);
}

//============================================================
// <T>��ǰ�߳�˯�ߴ���</T>
//
// @param interval ���
//============================================================
void FThread::SleepMicro(TInt interval){
   MO_LIB_MICRO_SLEEP(interval);
}

MO_NAMESPACE_END
