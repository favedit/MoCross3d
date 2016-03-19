#ifndef __MO_CM_THREAD_H__
#define __MO_CM_THREAD_H__
//------------------------------------------------------------
#ifdef _MO_WINDOWS
#include <Windows.h>
#endif

#ifdef _MO_LINUX
#include <pthread.h>
#endif
//------------------------------------------------------------
#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_MEMORY_H__
#include "MoCmMemory.h"
#endif // __MO_CM_MEMORY_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

#ifndef __MO_CM_MODULE_H__
#include "MoCmModule.h"
#endif // __MO_CM_MODULE_H__

MO_NAMESPACE_BEGIN

//============================================================
// �߳̾������
#ifdef _MO_WINDOWS
typedef TDword    TThreadId;
typedef TAny*     TThreadHandle;
#else
typedef pthread_t TThreadId;
typedef pthread_t TThreadHandle;
#endif // _MO_WINDOWS

//============================================================
class FThread;
class FThreadTrap;
class FThreadGroup;

//============================================================
// <T>�߳����͡�</T>
//============================================================
enum EThread{
   EThread_Unknown     = 0,
   EThread_Thread      = 1,
   EThread_Worker      = 2,
};

//============================================================
// <T>�߳����ȼ���</T>
//============================================================
enum EThreadPriority{
   EThreadPriority_Idle,
   EThreadPriority_Lowest,
   EThreadPriority_Lower,
   EThreadPriority_Normal,
   EThreadPriority_Higher,
   EThreadPriority_Highest,
   EThreadPriority_TimeCritical
};

//============================================================
// <T>�߳�״̬��</T>
//============================================================
enum EThreadStatus{
   EThreadStatus_Initialize,
   EThreadStatus_Running,
   EThreadStatus_Suspend,
   EThreadStatus_Wait,
   EThreadStatus_Cancel,
   EThreadStatus_Stop,
   EThreadStatus_Finish,
};

//============================================================
// <T>�߳̽ӿڡ�</T>
//============================================================
class MO_CM_DECLARE IThread{
public:
   //------------------------------------------------------------
   // <T>�����߳̽ӿڡ�</T>
   MO_ABSTRACT ~IThread(){
   }
public:
   MO_VIRTUAL TThreadHandle Handle() const = 0;
   MO_VIRTUAL TThreadId ThreadId() const = 0;
   MO_VIRTUAL EThreadPriority Priority() const = 0;
   MO_VIRTUAL TBool IsStatus(EThreadStatus status) const = 0;
   MO_VIRTUAL EThreadStatus Status() const = 0;
   MO_VIRTUAL TBool IsStop() const = 0;
public:
   MO_VIRTUAL TResult Start() = 0;
   MO_VIRTUAL TResult Suspend() = 0;
   MO_VIRTUAL TResult Resume() = 0;
   MO_VIRTUAL TResult Join(IThread* pThread) = 0;
   MO_VIRTUAL TAny* Wait() = 0;
   MO_VIRTUAL TResult Stop() = 0;
   MO_VIRTUAL TResult Terminate() = 0;
};

//============================================================
// <T>�̶߳���</T>
//============================================================
class MO_CM_DECLARE FThread :
      public FObject,
      public IThread{
protected:
   EThread _typeCd;
   TInt _flag;
   TInt _index;
   TFsCode _code;
   TFsName _name;
   TThreadHandle _handle;
#ifdef _MO_SYS_LINUX
   pthread_mutex_t _mutex;
   pthread_cond_t _condition;
#endif // _MO_SYS_LINUX
   TThreadId _threadId;
   EThreadPriority _priority;
   EThreadStatus _status;
   FThreadGroup* _pThreadGroup;
   FThreadTrap* _pThreadTrap;
   FThreadMemory* _pThreadMemory;
public:
   FThread();
   MO_ABSTRACT ~FThread();
public:
   //------------------------------------------------------------
   // <T>����߳����͡�</T>
   MO_INLINE EThread TypeCd(){
      return _typeCd;
   }
   //------------------------------------------------------------
   // <T>�����߳����͡�</T>
   MO_INLINE void SetTypeCd(EThread typeCd){
      _typeCd = typeCd;
   }
   //------------------------------------------------------------
   // <T>���Ա�־��</T>
   MO_INLINE TBool TestFlag(TInt flag){
      return (_flag & flag) == flag;
   }
   //------------------------------------------------------------
   // <T>��ñ�־��</T>
   MO_INLINE TInt Flag(){
      return _flag;
   }
   //------------------------------------------------------------
   // <T>���ñ�־��</T>
   MO_INLINE void SetFlag(TInt flag){
      _flag = flag;
   }
   //------------------------------------------------------------
   // <T>����߳�������</T>
   MO_INLINE TInt Index(){
      return _index;
   }
   //------------------------------------------------------------
   // <T>�����߳�������</T>
   MO_INLINE void SetIndex(TInt index){
      _index = index;
   }
   //------------------------------------------------------------
   // <T>����̴߳��롣</T>
   MO_INLINE TCharC* Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>�����̴߳��롣</T>
   MO_INLINE void SetCode(TCharC* pCode){
      _code = pCode;
   }
   //------------------------------------------------------------
   // <T>����߳����ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�����߳����ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
public:
   MO_OVERRIDE TThreadHandle Handle() const;
   MO_OVERRIDE TThreadId ThreadId() const;
   MO_OVERRIDE EThreadPriority Priority() const;
   void SetPriority(EThreadPriority priority);
   MO_OVERRIDE TBool IsStatus(EThreadStatus status) const;
   MO_OVERRIDE EThreadStatus Status() const;
   MO_OVERRIDE TBool IsStop() const;
   FThreadGroup* ThreadGroup();
   void SetThreadGroup(FThreadGroup* pThreadGroup);
   FThreadTrap* ThreadTrap();
   FThreadMemory* ThreadMemory();
public:
   MO_ABSTRACT TBool OnStart();
   MO_ABSTRACT TBool OnCancel(TInt code);
   MO_ABSTRACT TBool OnFinish(TInt result);
public:
   MO_VIRTUAL TResult Process() = 0;
public:
   MO_OVERRIDE TResult Start();
   MO_OVERRIDE TResult Idle();
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Join(IThread* pThread);
   MO_OVERRIDE TAny* Wait();
   MO_OVERRIDE TResult Stop();
   MO_OVERRIDE TResult Terminate();
public:
   void Sleep(TInt interval);
   void SleepMicro(TInt interval);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FThread*> FThreadList;
typedef MO_CM_DECLARE FSet<TThreadId, FThread*> FThreadSet;

//============================================================
class MO_CM_DECLARE FThreadGroup : public FObject{
protected:
   TThreadLocker _locker;
   FThreadList* _pThreads;
public:
   FThreadGroup();
   MO_ABSTRACT ~FThreadGroup();
public:
   FThreadList* Threads();
   TBool Push(FThread* pThread);
   TBool Remove(FThread* pThread);
public:
   TBool Start();
   TBool Suspend();
   TBool Resume();
   TBool Wait();
   TBool Stop();
};

//============================================================
// <T>�����ж���</T>
//============================================================
typedef TInt (*TRunableHandle)(TAny* pParameter);

//============================================================
// <T>�������̶߳���</T>
//============================================================
class MO_CM_DECLARE FThreadRunable : public FThread{
protected:
   TRunableHandle _runableHandle;
public:
   FThreadRunable();
   FThreadRunable(TRunableHandle handle);
public:
   void SetRunable(TRunableHandle handle);
   MO_OVERRIDE TResult Process();
};

//============================================================
// <T>�̳߳صĽӿڡ�</T>
//============================================================
class MO_CM_DECLARE IThreadRunablePool : public IDispose{
};

//============================================================
// <T>�̳߳صĹ�������</T>
//============================================================
class MO_CM_DECLARE FThreadRunableWorker : public FThreadRunable{
protected:
   IThreadRunablePool* _pPool;
   TBool _stop;
public:
   FThreadRunableWorker(IThreadRunablePool* pPool);
public:
   MO_OVERRIDE TResult Process();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FThreadRunableWorker*> FThreadRunableWorkerList;

//============================================================
// <T>�̳߳ض���</T>
//============================================================
class MO_CM_DECLARE FThreadRunablePool : public IThreadRunablePool{
protected:
   TThreadLocker _locker;
   FThreadRunableWorkerList* _pUsedWorks;
   FThreadRunableWorkerList* _pUnusedWorks;
   TInt _incrementCapacity;
   TThreadSection _eventStop;
public:
   FThreadRunablePool();
   MO_OVERRIDE ~FThreadRunablePool();
public:
   TInt ActiveCount();
   TInt SleepCount();
   void NotifyFree(FThreadRunableWorker& worker);
   void NotifyTimeout(FThreadRunableWorker& worker);
   void Process(TRunableHandle runable);
};

//============================================================
// <T>�̳߳صĽӿڡ�</T>
//============================================================
class FThreadWorker;
class MO_CM_DECLARE IThreadPool : public IDispose{
public:
   //------------------------------------------------------------
   // <T>�ͷ��̳߳صĽӿڡ�</T>
   MO_ABSTRACT ~IThreadPool(){
   }
public:
   MO_VIRTUAL TBool DoInitialize(FThreadWorker* pWorker) = 0;
   MO_VIRTUAL TBool DoBusy(FThreadWorker* pWorker) = 0;
   MO_VIRTUAL TBool DoWait(FThreadWorker* pWorker) = 0;
public:
   MO_VIRTUAL TBool Refresh() = 0;
};

//============================================================
// <T>��������־��</T>
//============================================================
enum EWorkerFlag{
   EWorkerFlag_Unknown = 0x00,
   EWorkerFlag_Data    = 0x01,
   EWorkerFlag_Message = 0x02,
   EWorkerFlag_Logic   = 0x04,
};

//============================================================
// <T>�̳߳صĹ�������</T>
//============================================================
class MO_CM_DECLARE FThreadWorker : public FThread{
protected:
   IThreadPool* _pPool;
   TBool _busy;
   TBool _stop;
   TTimeSpan _interval;
   TTimeSpan _timeout;
   TDateTime _freeDate;
public:
   FThreadWorker();
public:
   //------------------------------------------------------------
   // <T>����̹߳���������ء�</T>
   MO_INLINE IThreadPool* Pool(){
      return _pPool;
   }
   //------------------------------------------------------------
   // <T>�����̹߳���������ء�</T>
   MO_INLINE void SetPool(IThreadPool* pPool){
      _pPool = pPool;
   }
   //------------------------------------------------------------
   // <T>����̹߳�����æ��־��</T>
   MO_INLINE TBool IsBusy(){
      return _busy;
   }
   //------------------------------------------------------------
   // <T>�����̹߳�����æ��־��</T>
   MO_INLINE void SetBusy(TBool busy){
      _busy = busy;
   }
   //------------------------------------------------------------
   // <T>��ü����</T>
   MO_INLINE TTimeSpan Interval(){
      return _interval;
   }
   //------------------------------------------------------------
   // <T>���ü����</T>
   MO_INLINE void SetInterval(TTimeSpan interval){
      _interval = interval;
   }
   //------------------------------------------------------------
   // <T>��ó�ʱ��</T>
   MO_INLINE TTimeSpan Timeout(){
      return _timeout;
   }
   //------------------------------------------------------------
   // <T>���ó�ʱ��</T>
   MO_INLINE void SetTimeout(TTimeSpan timeout){
      _timeout = timeout;
   }
public:
   MO_ABSTRACT TBool TestTimeout(TDateTime current);
public:
   MO_ABSTRACT TResult OnProcess();
public:
   MO_OVERRIDE TResult Process();
public:
   MO_ABSTRACT TBool Track(MString* pTrack);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FThreadWorker*> FThreadWorkerList;

//============================================================
// <T>�̳߳ض���</T>
//============================================================
class MO_CM_DECLARE FThreadPool :
      public FObject,
      public IThreadPool{
protected:
   TThreadLocker _eventStop;
   TThreadLocker _lockerInitialize;
   FThreadWorkerList* _pInitializeWorkers;
   TThreadLocker _lockerBusy;
   FThreadWorkerList* _pBusyWorkers;
   TThreadLocker _lockerFree;
   FThreadWorkerList* _pFreeWorkers;
   TInt64 _busyTotal;
   TInt64 _waitTotal;
   TTimeSpan _refreshInterval;
   TDateTime _refreshDate;
   TInt64 _refreshTotal;
public:
   FThreadPool();
   MO_OVERRIDE ~FThreadPool();
public:
   TInt InitializeCount();
   TInt BusyCount();
   TInt FreeCount();
public:
   //------------------------------------------------------------
   // <T>��ó�ʼ�����������ϡ�</T>
   MO_INLINE FThreadWorkerList* InitializeWorkers(){
      return _pInitializeWorkers;
   }
   //------------------------------------------------------------
   // <T>��ù����й��������ϡ�</T>
   MO_INLINE FThreadWorkerList* BusyWorkers(){
      return _pBusyWorkers;
   }
   //------------------------------------------------------------
   // <T>��ÿ����й��������ϡ�</T>
   MO_INLINE FThreadWorkerList* FreeWorkers(){
      return _pFreeWorkers;
   }
   //------------------------------------------------------------
   // <T>���æ������</T>
   MO_INLINE TInt64 BusyTotal(){
      return _busyTotal;
   }
   //------------------------------------------------------------
   // <T>��õȴ�������</T>
   MO_INLINE TInt64 WaitTotal(){
      return _waitTotal;
   }
   //------------------------------------------------------------
   // <T>���ˢ��������</T>
   MO_INLINE TInt64 RefreshTotal(){
      return _refreshTotal;
   }
public:
   void Register(FThreadWorker* pWorker);
   FThreadWorker* AllocFree();
public:
   MO_OVERRIDE TBool DoInitialize(FThreadWorker* pWorker);
   MO_OVERRIDE TBool DoBusy(FThreadWorker* pWorker);
   MO_OVERRIDE TBool DoWait(FThreadWorker* pWorker);
public:
   MO_OVERRIDE TBool Refresh();
   MO_ABSTRACT TBool Track(MString* pTrack);
};

//============================================================
// <T>�߳̿���̨�ӿڡ�</T>
//
// @face
// @history 091214 MAOCY ����
//============================================================
class MO_CM_DECLARE IThreadConsole{
public:
   //------------------------------------------------------------
   // <T>�����߳̿���̨�ӿڡ�</T>
   MO_ABSTRACT ~IThreadConsole(){
   }
public:
   MO_VIRTUAL void Register(FThread* pThread) = 0;
   MO_VIRTUAL void Unregister(FThread* pThread) = 0;
   MO_VIRTUAL FThread* Current() = 0;
   MO_VIRTUAL FThread* Get(TThreadId threadId) = 0;
   MO_VIRTUAL FThread* Find(TThreadId threadId=0) = 0;
};

//============================================================
// <T>�߳���Ϣ�ࡣ</T>
//
// @reference
// @history 091210 MAOCY ����
//============================================================
class MO_CM_DECLARE RThread{
public:
   static TInt CurrentCode();
   static TThreadId CurrentId();
   static IThread* Process(TRunableHandle cRunable);
};

//============================================================
// <T>�̹߳�������</T>
//
// @console
// @history 091214 MAOCY ����
//============================================================
class MO_CM_DECLARE FThreadConsole :
      public FConsole,
      public IThreadConsole{
protected:
   TInt _index;
   TThreadLocker _locker;
   FThreadSet* _pThreads;
public:
   FThreadConsole();
   MO_ABSTRACT ~FThreadConsole();
public:
   MO_OVERRIDE void Register(FThread* pThread);
   MO_OVERRIDE void Unregister(FThread* pThread);
   MO_OVERRIDE FThread* Current();
   MO_OVERRIDE FThread* Get(TThreadId threadId = 0);
   MO_OVERRIDE FThread* Find(TThreadId threadId = 0);
};
//------------------------------------------------------------
class MO_CM_DECLARE RThreadManager : public RSingleton<FThreadConsole>{
};

MO_NAMESPACE_END

#endif // __MO_CM_THREAD_H__
