#ifndef __MO_CM_TASK_H__
#define __MO_CM_TASK_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_CLASS_H__
#include "MoCmClass.h"
#endif // __MO_CM_CLASS_H__

#ifndef __MO_CM_THREAD_H__
#include "MoCmThread.h"
#endif // __MO_CM_THREAD_H__

#ifndef __MO_CM_SYSTEM_H__
#include "MoCmSystem.h"
#endif // __MO_CM_SYSTEM_H__

MO_NAMESPACE_BEGIN

//============================================================
class FTaskConsole;

//============================================================
// <T>����ӿڡ�</T>
//============================================================
class MO_CM_DECLARE ITask{
public:
   // ------------------------------------------------------------
   // <T>��������ӿڡ�</T>
   MO_ABSTRACT ~ITask(){
   }
public:
   MO_VIRTUAL TBool HasRefer() = 0;
public:
   MO_VIRTUAL TResult TaskProcess() = 0;
};

//============================================================
// <T>����</T>
//============================================================
class MO_CM_DECLARE FTask : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FTask, FInstance);
public:
   FTask();
   MO_ABSTRACT ~FTask();
public:
   MO_ABSTRACT TResult Process();
};
// ------------------------------------------------------------
typedef MO_CM_DECLARE FList<FTask*> FTaskList;

//============================================================
// <T>������á�</T>
//============================================================
class MO_CM_DECLARE FTaskInvoker : public FTask
{
   MO_CLASS_DECLARE_INHERITS(FTaskInvoker, FTask);
protected:
   ITask* _pTask;
public:
   FTaskInvoker();
   MO_ABSTRACT ~FTaskInvoker();
public:
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE ITask* Task(){
      return _pTask;
   }
   //------------------------------------------------------------
   // <T>��������</T>
   MO_INLINE void SetTask(ITask* pTask){
      _pTask = pTask;
   }
public:
   MO_ABSTRACT TResult Process();
};

//============================================================
// <T>��̬����</T>
//============================================================
class FStaticTask : public FTask{
public:
   typedef TResult (*HProcessor)();
protected:
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����������</T>
   FStaticTask(TResult (*pProcesser)()){
      _pProcesser = pProcesser;
   }
public:
   //------------------------------------------------------------
   // <T>��ô���ָ�롣</T>
   MO_INLINE HProcessor Processer(){
      return _pProcesser;
   }
public:
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_OVERRIDE TResult Process(){
      return _pProcesser();
   }
};

//============================================================
// <T>�ص�����</T>
//============================================================
template <typename T>
class FDelegateTask : public FTask{
public:
   typedef TResult (T::*HProcessor)();
protected:
   T* _pOwner;
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����������</T>
   FDelegateTask(T* pOwner, TResult (T::*pProcesser)()){
      _pOwner = pOwner;
      _pProcesser = pProcesser;
   }
public:
   //------------------------------------------------------------
   // <T>���ӵ����ָ�롣</T>
   MO_INLINE T* Owner(){
      return _pOwner;
   }
   //------------------------------------------------------------
   // <T>��ô���ָ�롣</T>
   MO_INLINE HProcessor Processer(){
      return _pProcesser;
   }
public:
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_OVERRIDE TResult Process(){
      return (_pOwner->*_pProcesser)();
   }
};

//============================================================
// <T>�����̡߳�</T>
//
// @class
// @history 140411 MAOCY ����
//============================================================
class MO_CM_DECLARE FTaskThread : public FThread{
protected:
   FTaskConsole* _pConsole;
   TInt _interval;
   FTask* _pTask;
public:
   FTaskThread();
   MO_ABSTRACT ~FTaskThread();
public:
   // ------------------------------------------------------------
   // <T>��ÿ���̨��</T>
   MO_INLINE FTaskConsole* Console(){
      return _pConsole;
   }
   // ------------------------------------------------------------
   // <T>��ÿ���̨��</T>
   MO_INLINE void SetConsole(FTaskConsole* pConsole){
      _pConsole = pConsole;
   }
   // ------------------------------------------------------------
   // <T>���ͳ����Ϣ��</T>
   MO_INLINE FTask* Task(){
      return _pTask;
   }
   // ------------------------------------------------------------
   // <T>���ͳ����Ϣ��</T>
   MO_INLINE void SetTask(FTask* pTask){
      _pTask = pTask;
   }
public:
   MO_OVERRIDE TResult Process();
};
// ------------------------------------------------------------
typedef MO_CM_DECLARE FObjects<FTaskThread*> FTaskThreadCollection;

//============================================================
// <T>�������̨��</T>
//
// @class
// @history 140411 MAOCY ����
//============================================================
class MO_CM_DECLARE FTaskConsole : public FConsole
{
   MO_CLASS_DECLARE_INHERITS(FTaskConsole, FConsole);
protected:
   TThreadLocker _locker;
   FTaskList* _pTasks;
   FTaskThreadCollection* _pThreads;
   TInt _threadCount;
public:
   FTaskConsole();
   MO_ABSTRACT ~FTaskConsole();
public:
   //------------------------------------------------------------
   // <T>��������б�</T>
   MO_INLINE FTaskList* Tasks(){
      return _pTasks;
   }
   //------------------------------------------------------------
   // <T>����̼߳��ϡ�</T>
   MO_INLINE FTaskThreadCollection* Threads(){
      return _pThreads;
   }
   //------------------------------------------------------------
   // <T>����̸߳�����</T>
   MO_INLINE TInt ThreadCount(){
      return _threadCount;
   }
   //------------------------------------------------------------
   // <T>�����̸߳�����</T>
   MO_INLINE void ThreadCount(TInt thread){
      _threadCount = thread;
   }
protected:
   MO_ABSTRACT FTask* PopTask();
   MO_ABSTRACT TResult PushTask(ITask* pTask);
public:
   MO_ABSTRACT TResult PushTask(FTask* pTask);
public:
   //------------------------------------------------------------
   // <T>����һ����̬����</T>
   void PushTask(TResult (*pProcesser)()){
      FStaticTask* pListener = new FStaticTask(pProcesser);
      PushTask(pListener);
   }
   //------------------------------------------------------------
   // <T>����һ���ص�����</T>
   template <typename C>
   void PushTask(C* pOwner, TResult (C::*pProcesser)()){
      FDelegateTask<C>* pListener = new FDelegateTask<C>(pOwner, pProcesser);
      PushTask(pListener);
   }
public:
   MO_ABSTRACT TResult Startup();
   MO_ABSTRACT TResult Shutdown();
public:
   friend class FTaskThread;
};

//============================================================
// <T>�����������</T>
//============================================================
class MO_CM_DECLARE RTaskManager : public RSingleton<FTaskConsole>{
};

MO_NAMESPACE_END

#endif // __MO_CM_TASK_H__
