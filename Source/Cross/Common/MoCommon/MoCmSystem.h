#ifndef __MO_CM_SYSTEM_H__
#define __MO_CM_SYSTEM_H__
//------------------------------------------------------------
#ifdef _MO_WINDOWS
#include <Windows.h>
#endif

#ifdef _MO_LINUX
#ifndef __CYGWIN__
#include <execinfo.h>
#endif
#include <signal.h>
#include <setjmp.h>
#endif
//------------------------------------------------------------
#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_LIST_H__
#include "MoCmList.h"
#endif // __MO_CM_LIST_H__

#ifndef __MO_CM_SINGLETON_H__
#include "MoCmSingleton.h"
#endif // __MO_CM_SINGLETON_H__

#ifndef __MO_CM_FILE_H__
#include "MoCmFile.h"
#endif // __MO_CM_FILE_H__

#ifndef __MO_CM_THREAD_H__
#include "MoCmThread.h"
#endif // __MO_CM_THREAD_H__

#ifndef __MO_CM_TASK_H__
#include "MoCmTask.h"
#endif // __MO_CM_TASK_H__

#define MO_SYS_STACK_MAXCNT   256
#define MO_TRAP_ACTION_MAXCNT 256
#define MO_TRAP_MAXCNT        16

#ifdef _MO_WINDOWS
#define MO_TRAP_CATCHER(C) ETrue
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
#define MO_TRAP_CATCHER(C) (0==sigsetjmp(C->JumpPointer(), 1))
#endif // _MO_LINUX

MO_NAMESPACE_BEGIN

//============================================================
const TInt  MoLoggerMaxCode = 1024;
const TUint MoCpuFrequency = 2930000000UL;

//============================================================
class MApplicationListeners;

//============================================================
// <T>ϵͳ��Ϣ��</T>
//============================================================
struct MO_CM_DECLARE SSystemInfo{
public:
   TFloat cpuRate;
   TInt64 memory;
public:
   SSystemInfo(){
      cpuRate = 0;
      memory = 0;
   }
};

//============================================================
// <T>�ٶȼ������</T>
//============================================================
class MO_CM_DECLARE TSpeedTracker{
public:
   TTimeTick tickBegin;
   TTimeTick tickEnd;
   TTimeSpan tickSpan;
public:
   //------------------------------------------------------------
   // <T>�����ٶȼ������</T>
   TSpeedTracker(TBool flag = ETrue){
      if(flag){
         tickBegin = RTimeTick::Current();
      }else{
         tickBegin = 0;
      }
      tickEnd = 0;
      tickSpan = 0;
   }
public:
   //------------------------------------------------------------
   // <T>��ʼ����</T>
   MO_INLINE void Begin(){
      tickBegin = RTimeTick::Current();
      tickEnd = 0;
      tickSpan = 0;
   }
   //------------------------------------------------------------
   // <T>��������</T>
   MO_INLINE void End(){
      tickEnd = RTimeTick::Current();
      tickSpan = tickEnd - tickBegin;
   }
   //------------------------------------------------------------
   // <T>���㴦��</T>
   MO_INLINE TTimeSpan Calculate(){
      End();
      return tickSpan;
   }
};

//============================================================
// <T>�¼���</T>
//============================================================
class MO_CM_DECLARE SEvent{
public:
   TAny* ownerPtr;
   TAny* senderPtr;
public:
   //------------------------------------------------------------
   // <T>�����¼���</T>
   SEvent(TAny* pSender){
      MO_CLEAR(ownerPtr);
      senderPtr = pSender;
   }
};

//============================================================
// <T>���������͡�</T>
//============================================================
enum EListenerType{
   EListenerType_Any,
   EListenerType_Static,
   EListenerType_Delegate,
};

//============================================================
// <T>����������</T>
//============================================================
enum EListenerManage{
   EListenerManage_Free,
   EListenerManage_Auto,
};

//============================================================
// <T>�������ӿڡ�</T>
//============================================================
class MO_CM_DECLARE IListener{
public:
   //------------------------------------------------------------
   // <T>����������ӿڡ�</T>
   MO_ABSTRACT ~IListener(){
   }
public:
   MO_VIRTUAL EListenerType TypeCd() = 0;
   MO_VIRTUAL EListenerManage ManageCd() = 0;
public:
   MO_VIRTUAL TBool Process(TAny* pEvent) = 0;
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<IListener*> FListenerList;

//============================================================
// <T>����������</T>
//============================================================
class MO_CM_DECLARE FListener :
      public FObject,
      public IListener{
protected:
   EListenerType _typeCd;
   EListenerManage _manageCd;
public:
   FListener();
   MO_ABSTRACT ~FListener();
public:
   MO_OVERRIDE EListenerType TypeCd();
   MO_OVERRIDE EListenerManage ManageCd();
public:
   MO_OVERRIDE TBool Process(TAny* pParameters = NULL);
};

//============================================================
// <T>��������</T>
//============================================================
template <typename P>
class FStaticListener : public FListener{
public:
   typedef TResult (*HProcessor)(P*);
protected:
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����������</T>
   FStaticListener(TResult (*pProcesser)(P*)){
      _typeCd = EListenerType_Static;
      _manageCd = EListenerManage_Auto;
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
   MO_OVERRIDE TBool Process(TAny* pParameters = NULL){
      return _pProcesser((P*)pParameters);
   }
};
//------------------------------------------------------------
#define MO_CREATE_STATIC_EVENT(M, P) new FStaticListener<P>(&M)

//============================================================
// <T>��������</T>
//============================================================
template <typename T, typename P>
class FDelegateListener : public FListener{
public:
   typedef TResult (T::*HProcessor)(P*);
protected:
   T* _pOwner;
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����������</T>
   FDelegateListener(T* pOwner, TResult (T::*pProcesser)(P*)){
      _typeCd = EListenerType_Delegate;
      _manageCd = EListenerManage_Auto;
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
   MO_OVERRIDE TBool Process(TAny* pParameters){
      // ����ӵ����
      if(pParameters != NULL){
         SEvent* pEvent = (SEvent*)pParameters;
         pEvent->ownerPtr = _pOwner;
      }
      // ִ�д���
      return (_pOwner->*_pProcesser)((P*)pParameters);
   }
};
//------------------------------------------------------------
#define MO_CREATE_EVENT(O, C, M, P) new FDelegateListener<C, P>(O, &C::M)

//============================================================
// <T>���������ϡ�</T>
//============================================================
class MO_CM_DECLARE MListeners{
protected:
   FListenerList* _pListeners;
public:
   MListeners();
   MO_ABSTRACT ~MListeners();
public:
   //------------------------------------------------------------
   // <T>����Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (_pListeners != NULL) ? _pListeners->IsEmpty() : ETrue;
   }
public:
   void Push(IListener* pListener);
   void Remove(IListener* pListener);
public:
   MO_ABSTRACT TBool Process(TAny* pParameters = NULL);
public:
   void Clear();
};

//============================================================
// <T>���������ϡ�</T>
//============================================================
class MO_CM_DECLARE FListeners :
      public FObject,
      public MListeners{
};

//============================================================
// <T>���������ϡ�</T>
//============================================================
template <typename P>
class TListeners : public MListeners{
public:
   //------------------------------------------------------------
   // <T>ע��һ����̬��������</T>
   IListener* Find(TResult (*pProcesser)(P*)){
      if(_pListeners != NULL){
         TListIteratorC<IListener*> iterator = _pListeners->IteratorC();
         while(iterator.Next()){
            IListener* pListener = *iterator;
            if(pListener->TypeCd() == EListenerType_Static){
               FStaticListener<P>* pStaticListener = (FStaticListener<P>*)pListener;
               if(pStaticListener->Processer() == pProcesser){
                  return pStaticListener;
               }
            }
         }
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>ע��һ����̬��������</T>
   template <typename C>
   IListener* Find(C* pOwner, TResult (C::*pProcesser)(P*)){
      if(_pListeners != NULL){
         TListIteratorC<IListener*> iterator = _pListeners->IteratorC();
         while(iterator.Next()){
            IListener* pListener = *iterator;
            if(pListener->TypeCd() == EListenerType_Delegate){
               FDelegateListener<C, P>* pDelegateListener = (FDelegateListener<C, P>*)pListener;
               if((pDelegateListener->Owner() == pOwner) && (pDelegateListener->Processer() == pProcesser)){
                  return pDelegateListener;
               }
            }
         }
      }
      return NULL;
   }
public:
   //------------------------------------------------------------
   // <T>ע��һ����̬��������</T>
   void Register(TResult (*pProcesser)(P*)){
      FStaticListener<P>* pListener = new FStaticListener<P>(pProcesser);
      Push(pListener);
   }
   //------------------------------------------------------------
   // <T>ע��һ����������</T>
   template <typename C>
   void Register(C* pOwner, TResult (C::*pProcesser)(P*)){
      FDelegateListener<C, P>* pListener = new FDelegateListener<C, P>(pOwner, pProcesser);
      Push(pListener);
   }
public:
   //------------------------------------------------------------
   // <T>ע��һ����̬��������</T>
   void Unregister(TResult (*pProcesser)(P*)){
      IListener* pListener = Find(pProcesser);
      Remove(pListener);
   }
   //------------------------------------------------------------
   // <T>ע��һ����������</T>
   template <typename C>
   void Unregister(C* pOwner, TResult (C::*pProcesser)(P*)){
      IListener* pListener = Find<C>(pOwner, pProcesser);
      Remove(pListener);
   }
};

//============================================================
// <T>����Ȩ�ޡ�</T>
//
// @enum
// @history 091211 MAOCY ����
//============================================================
enum EProcessPrivileges{
   EProcessPrivileges_LockMemory,
   EProcessPrivileges_Debug,
   EProcessPrivileges_Shutdown
};

//============================================================
// <T>Ӧ�ó���������͡�</T>
//============================================================
enum EApplicationListener{
   EApplicationListener_Unknown,
   EApplicationListener_Interrrupt,
   EApplicationListener_Reload,
   EApplicationListener_Unload,
   EApplicationListener_Shutdown,
};

//============================================================
// <T>Ӧ�ó��������</T>
//
// @class
// @history 140327 MAOCY ����
//============================================================
class MO_CM_DECLARE FApplicationParameter : public FInstance{
protected:
   TString _name;
   TString _value;
public:
   FApplicationParameter();
   MO_ABSTRACT ~FApplicationParameter();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����ơ�</T>
   MO_INLINE TBool IsName(TCharC* pName){
      return _name.Equals(pName);
   }
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�������ݡ�</T>
   MO_INLINE TBool IsValue(TCharC* pValue){
      return _value.Equals(pValue);
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE TCharC* Value(){
      return _value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void SetValue(TCharC* pValue){
      _value = pValue;
   }
public:
   TResult Parse(TCharC* pSource, TInt length = -1);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FObjects<FApplicationParameter*> FApplicationParameterCollection;

//============================================================
// <T>Ӧ�ó���������ϡ�</T>
//
// @class
// @history 140327 MAOCY ����
//============================================================
class MO_CM_DECLARE FApplicationParameters : public FInstance{
protected:
   FApplicationParameterCollection* _pParameters;
public:
   FApplicationParameters();
   MO_ABSTRACT ~FApplicationParameters();
public:
   //------------------------------------------------------------
   // <T>��ò������ϡ�</T>
   MO_INLINE FApplicationParameterCollection* Parameters(){
      return _pParameters;
   }
public:
   TResult Setup(TCharC* pCommandLine);
   TResult Setup(TCharC** ppArguments, TInt count);
public:
   TInt Count();
   FApplicationParameter* GetParameter(TInt index);
   FApplicationParameter* FindParameter(TCharC* pName);
   TBool ConstainsValue(TCharC* pValue);
   TCharC* GetValue(TInt index);
   TCharC* FindValue(TCharC* pName);
};

//============================================================
// <T>Ӧ�ó������</T>
//
// @reference
// @history 091210 MAOCY ����
//============================================================
class MO_CM_DECLARE FApplication : public MSingleton{
protected:
   static FListeners* _pInterrruptListeners;
   static FListeners* _pReloadListeners;
   static FListeners* _pUnloadListeners;
   static FListeners* _pShutdownListeners;
protected:
   FApplicationParameters* _pParameters;
#ifdef _MO_WINDOWS
   TInstance _hInstance;
   TInt _commandShow;
#endif // _MO_WINDOWS
public:
   FApplication();
   MO_ABSTRACT ~FApplication();
public:
   //------------------------------------------------------------
   // <T>��ò������ϡ�</T>
   MO_INLINE FApplicationParameters* Parameters(){
      return _pParameters;
   }
public:
   FListeners* InterruptListeners();
   FListeners* ReloadListeners();
   FListeners* UnloadListeners();
   FListeners* ShutdownListeners();
public:
#ifdef _MO_LINUX
   static void OnCapture(int signum, siginfo_t* info, TAny* ptr);
   static void OnReload(int signum, siginfo_t* info, TAny* ptr);
   static void OnUnload(int signum, siginfo_t* info, TAny* ptr);
   static void OnTerminate(int signum, siginfo_t* info, TAny* ptr);
#endif // _MO_LINUX
#ifdef _MO_WINDOWS
   TInstance Hinstance();
   void SetHinstance(HINSTANCE hinstance);
   TInt CommandShow();
   void SetCommandShow(TInt commandShow);
#endif // _MO_WINDOWS
public:
   TInt InstallCatcher();
   TInt UninstallCatcher();
   TInt InstallDaemon();
};

//============================================================
// <T>Ӧ�ó����������</T>
//============================================================
class MO_CM_DECLARE RApplication : public RSingleton<FApplication>{
public:
   static TFsPath GetCurrentDirectory();
   static TFsPath GetExecuteDirectory();
public:
#ifdef _MO_WINDOWS
   static TInstance Hinstance();
   static TInt CommandShow();
#endif // _MO_WINDOWS
public:
   static TInt InstallCatcher();
   static TInt InstallDaemon();
};

//============================================================
// <T>Ӧ�ü�������</T>
//============================================================
class FApplicationListener : public FListener{
protected:
   EApplicationListener _listenerCd;
   MApplicationListeners* _pListeners;
public:
   FApplicationListener();
   MO_ABSTRACT ~FApplicationListener();
public:
   //------------------------------------------------------------
   // <T>��ü������͡�</T>
   MO_INLINE EApplicationListener ListenerCd(){
      return _listenerCd;
   }
   //------------------------------------------------------------
   // <T>���ü������͡�</T>
   MO_INLINE void SetListenerCd(EApplicationListener listenerCd){
      _listenerCd = listenerCd;
   }
   //------------------------------------------------------------
   // <T>��ü������ϡ�</T>
   MO_INLINE MApplicationListeners* Listeners(){
      return _pListeners;
   }
   //------------------------------------------------------------
   // <T>���ü������ϡ�</T>
   MO_INLINE void SetListeners(MApplicationListeners* pListeners){
      _pListeners = pListeners;
   }
public:
   MO_OVERRIDE TBool Process();
};

//============================================================
// <T>Ӧ�ü��������ϡ�</T>
//
// @history 120427 MAOCY ����
//============================================================
class MO_CM_DECLARE MApplicationListeners{
protected:
   FApplicationListener* _pInterruptListener;
   FApplicationListener* _pReloadListener;
   FApplicationListener* _pUnloadListener;
   FApplicationListener* _pShutdownListener;
public:
   MApplicationListeners();
   MO_ABSTRACT ~MApplicationListeners();
public:
   //------------------------------------------------------------
   // <T>����жϼ�������</T>
   MO_INLINE FApplicationListener* InterruptListener(){
      return _pInterruptListener;
   }
   //------------------------------------------------------------
   // <T>������ؼ�������</T>
   MO_INLINE FApplicationListener* ReloadListener(){
      return _pReloadListener;
   }
   //------------------------------------------------------------
   // <T>���ж�ؼ�������</T>
   MO_INLINE FApplicationListener* UnloadListener(){
      return _pUnloadListener;
   }
   //------------------------------------------------------------
   // <T>���ж�ؼ�������</T>
   MO_INLINE FApplicationListener* ShutdownListener(){
      return _pShutdownListener;
   }
public:
   MO_ABSTRACT TResult Interrupt();
   MO_ABSTRACT TResult Reload();
   MO_ABSTRACT TResult Unload();
   MO_ABSTRACT TResult Shutdown();
};


//============================================================
// <T>������Ϣ�ࡣ</T>
//
// @reference
// @history 091210 MAOCY ����
//============================================================
class MO_CM_DECLARE RProcess{
public:
   static TInt CurrentId(void);
   static TBool AdjustProcessPrivileges(EProcessPrivileges privileges);
   static TInt GetTotalMemory();
};

//============================================================
// <T>���������ࡣ</T>
//
// @reference
// @history 100402 MAOCY ����
//============================================================
class MO_CM_DECLARE REnvironment{
public:
   static TFsPath MappingPath(TCharC* pPath, ...);
};

//============================================================
// <T>��־����ӿڡ�</T>
//
// @face
// @history 100416 MAOCY ����
//============================================================
class MO_CM_DECLARE ILoggerWriter{
public:
   //------------------------------------------------------------
   // <T>������־����ӿڡ�</T>
   MO_ABSTRACT ~ILoggerWriter(){
   }
public:
   MO_VIRTUAL TInt Code() = 0;
public:
   MO_VIRTUAL TResult Open() = 0;
   MO_VIRTUAL TResult Create() = 0;
   MO_VIRTUAL TResult Write(TDateTime time, TCharC* pMessage, TInt length) = 0;
   MO_VIRTUAL TResult Flush() = 0;
   MO_VIRTUAL TResult Refresh() = 0;
   MO_VIRTUAL TResult Close() = 0;
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<ILoggerWriter*> FLoggerWriterList;

//============================================================
// <T>��־д������</T>
//
// @class
//============================================================
class MO_CM_DECLARE FLoggerWriter :
      public FObject,
      public ILoggerWriter{
protected:
   TInt _code;
   TInt _fileCount;
   TSize _capacity;
   TSize  _length;
   TFsName _name;
   TFsPath _path;
   TDateTime _today;
   FChars** _pBuffer;
   FFileStream* _pStream;
   TThreadLocker _locker;
   TBool _forceToFlush;
public:
   FLoggerWriter();
   MO_ABSTRACT ~FLoggerWriter();
public:
   TInt GetCountFromName(TCharC* pName);
   void SetCode(TInt code);
   void SetName(TCharC* pName);
   void SetPath(TCharC* pPath);
   void SetCapacity(TSize capacity);
   void SetForceToFlush(TBool isForceFlush);
public:
   MO_OVERRIDE TInt Code();
public:
   MO_OVERRIDE TResult Open();
   MO_OVERRIDE TResult Create();
   MO_OVERRIDE TResult Write(TDateTime time, TCharC* pMessage, TInt length);
   MO_OVERRIDE TResult Flush();
   MO_OVERRIDE TResult Refresh();
   MO_OVERRIDE TResult Close();
};

//============================================================
// <T>��־ˢ���̡߳�</T>
//
// @class
//============================================================
class MO_CM_DECLARE FLoggerThread : public FThread{
protected:
   TTimeSpan _interval;
   FLoggerWriterList* _pWriters;
   TThreadLocker _locker;
public:
   FLoggerThread();
   MO_ABSTRACT ~FLoggerThread();
public:
   //------------------------------------------------------------
   // <T>��ü��ʱ�̡�</T>
   MO_INLINE TTimeSpan Interval(){
      return _interval;
   }
   //------------------------------------------------------------
   // <T>���ü��ʱ�̡�</T>
   MO_INLINE void SetInterval(TTimeSpan interval){
      _interval = interval;
   }
   //------------------------------------------------------------
   // <T>���д�������ϡ�</T>
   MO_INLINE FLoggerWriterList* Writers(){
      return _pWriters;
   }
   //------------------------------------------------------------
   // <T>����д�������ϡ�</T>
   MO_INLINE void SetWriters(FLoggerWriterList* pWriters){
      _pWriters = pWriters;
   }
   //------------------------------------------------------------
   // <T>���ͬ������</T>
   MO_INLINE TThreadLocker& Section(){
      return _locker;
   }
public:
   MO_OVERRIDE TResult Process();
};

//============================================================
// <T>��־����̨��</T>
//
// @class
// @history 091209 MAOCY ����
//============================================================
class MO_CM_DECLARE FLoggerConsole :
      public FConsole,
      public MApplicationListeners,
      public ILoggerConsole{
protected:
   TFsLabel _format;
   TBool _closed;
   TBool _useLogger;
   TBool _useViewer;
   TThreadLocker _locker;
   ELoggerLevel _levelCd;
   FLoggerWriterList* _pWriters;
   FLoggerThread* _pThread;
public:
   FLoggerConsole();
   MO_ABSTRACT ~FLoggerConsole();
public:
   TChar FormatLevelChar(ELoggerLevel levelCd);
   void Format(TFsLogger& result, TDateTime current, ELoggerLevel levelCd, TAnyC* pSender, TCharC* pMethod, TTimeSpan span, TCharC* pMessage, va_list& params);
   void FormatTrack(TFsLogger& result, ELoggerLevel levelCd, TAnyC* pSender, TCharC* pMethod, TTimeSpan span, TDateTime current, TCharC* pMessage, va_list& params);
public:
   MO_OVERRIDE TBool Output(TInt code, ELoggerLevel level, TAnyC* pSender, TCharC* pMethod, TTimeTick start, TCharC* pMessage, va_list& params);
public:
   TBool UseLogger();
   void SetUseLogger(TBool useLogger);
   TBool UseViewer();
   void SetUseViewer(TBool useViewer);
   ELoggerLevel LevelCd();
   void SetLevelCd(ELoggerLevel levelCd);
public:
   ILoggerWriter* FindWriter(TInt code);
public:
   TResult Register(ILoggerWriter* pWriter);
   TResult Unregister(ILoggerWriter* pWriter);
protected:
   TResult InnerFlush();
   TResult InnerClose();
public:
   TResult Startup();
   TResult Flush();
   MO_OVERRIDE TResult Interrupt();
   MO_OVERRIDE TResult Reload();
   MO_OVERRIDE TResult Unload();
   MO_OVERRIDE TResult Shutdown();
};
//------------------------------------------------------------
class MO_CM_DECLARE RLoggerManager : public RSingleton<FLoggerConsole>{
};

//============================================================
// <T>�ڴ�����鶨�塣</T>
//============================================================
struct MO_CM_DECLARE FTrapBlock{
public:
   TChar8C* pClassName;
   TAny* pMemory;
   TUint Size;
   TChar8C* pFileName;
   TInt Line;
public:
   FTrapBlock(){
   }
   ~FTrapBlock(){
   }
};
// ------------------------------------------------------------
typedef MO_CM_DECLARE FSet<TInt, FTrapBlock*> FTrapBlockSet;

//============================================================
// <T>�������</T>
//============================================================
class MO_CM_DECLARE FTrap{
protected:
   FTrap* _pParent;
   FTrapBlockSet* _pBlocks;
public:
   FTrap();
   ~FTrap();
public:
   FTrap* Parent();
   void SetParent(FTrap* parent);
public:
   TAny* Alloc(TInt size);
   TAny* Alloc(TChar8C* pClassName, TInt size, TChar8C* pFileName, TInt line);
   void Remove(TAny* pMemory);
   void Free(TAny* pMemory);
   void Check();
};

//============================================================
// <T>�߳��������</T>
//============================================================
class MO_CM_DECLARE FThreadTrap{
public:
   TInt _threadId;
   FTrap* _pUsed;
   FTrap* _pUnused;
public:
   FThreadTrap(TInt threadId=0);
   ~FThreadTrap();
public:
   TInt ThreadId();
   TBool IsEmpty();
   FTrap* CurrentTrap();
   void Push();
   void Pop();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FSet<TInt, FThreadTrap*> FThreadTrapSet;

//============================================================
// <T>����������</T>
//============================================================
class MO_CM_DECLARE RTrap{
private:
   static RTrap _instance;
public:
   static RTrap& Static();
private:
   RTrap(void);
   ~RTrap(void);
public:
   FThreadTrap* CurrentThreadTrap();
   FTrap* CurrentTrap();
   FThreadTrap* Link();
   void Unlink(FThreadTrap* pThreadTrap);
};

//============================================================
// <T>�ڴ�����鶨�塣</T>
//============================================================
class MO_CM_DECLARE TTrapper{
private:
   FThreadTrap* _pThreadTrap;
   FTrap* _pTrap;
public:
   TTrapper();
   ~TTrapper();
};

//============================================================
// <T>��׽����</T>
//============================================================
class MO_CM_DECLARE FCatcher : public FObject{
public:
   TFsName _name;      // ����
   TCharC* _pInfo;     // ��Ϣ
   FCatcher* _pParent; // ������
   TInt _threadCode;   // �̴߳���
   TBool _installed;   // ��װ��־
   TBool _recorded;    // ��¼��־
   TBool _valid;       // ��Ч��־
   TBool _jumping;     // ��ת��־
   TInt _jumpCount;
#ifdef _MO_LINUX
   sigjmp_buf _jmpbuf;
#endif // _LINUX
   TBool _actions[MO_TRAP_ACTION_MAXCNT];
public:
   FCatcher();
   MO_ABSTRACT ~FCatcher();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>�����Ϣ��</T>
   MO_INLINE TCharC* Info(){
      return _pInfo;
   }
   //------------------------------------------------------------
   // <T>������Ϣ��</T>
   MO_INLINE void LinkInfo(TCharC* pInfo){
      _pInfo = pInfo;
   }
   //------------------------------------------------------------
   // <T>��ø�����</T>
   MO_INLINE FCatcher* Parent(){
      return _pParent;
   }
   //------------------------------------------------------------
   // <T>���ø�����</T>
   MO_INLINE void SetParent(FCatcher* pCatcher){
      _pParent = pCatcher;
   }
   //------------------------------------------------------------
   // <T>����̱߳�š�</T>
   MO_INLINE TInt ThreadCode(){
      return _threadCode;
   }
   //------------------------------------------------------------
   // <T>�����̱߳�š�</T>
   MO_INLINE void SetThreadCode(TInt threadCode){
      _threadCode = threadCode;
   }
   //------------------------------------------------------------
   // <T>���ø�����</T>
   MO_INLINE TBool IsValid(){
      return _valid;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ת�С�</T>
   MO_INLINE TBool IsJumping(){
      return _jumping;
   }
   //------------------------------------------------------------
   // <T>�����ת������</T>
   MO_INLINE TInt JumpCount(){
      return _jumpCount;
   }
#ifdef _MO_LINUX
   //------------------------------------------------------------
   // <T>���ø�����</T>
   MO_INLINE sigjmp_buf& JumpPointer(){
      return _jmpbuf;
   }
#endif // _LINUX
public:
   TBool IsRegistered(TInt code);
   TBool Register(TInt code);
   TBool Unregister(TInt code);
public:
   MO_ABSTRACT TBool Install();
   MO_ABSTRACT TBool Uninstall();
public:
   TBool Enter();
   TBool Leave();
public:
   TBool Record();
   TBool Recorded();
   TBool Jump();
   TBool JumpFinish();
};
//------------------------------------------------------------
typedef FVector<FCatcher*> FCatcherVector;
typedef FList<FCatcher*> FCatcherList;

//============================================================
// <T>�̲߳�׽����</T>
//
// @class
// @history 120128 MAOCY ����
//============================================================
class MO_CM_DECLARE FThreadCatcher : public FObject{
protected:
   TInt _threadCode;
   FCatcher* _pActiveCatcher;
   FCatcher* _pJumpCatcher;
   FCatcherVector* _pCatchers;
   TThreadLocker _lockerActive;
   TThreadLocker _lockerJump;
public:
   FThreadCatcher();
   MO_ABSTRACT ~FThreadCatcher();
public:
   //------------------------------------------------------------
   // <T>����̱߳�š�</T>
   MO_INLINE TInt ThreadCode(){
      return _threadCode;
   }
   //------------------------------------------------------------
   // <T>�����̱߳�š�</T>
   MO_INLINE void SetThreadCode(TInt threadCode){
      _threadCode = threadCode;
   }
   //------------------------------------------------------------
   // <T>��ò�׽����</T>
   MO_INLINE FCatcher* ActiveCatcher(){
      return _pActiveCatcher;
   }
   //------------------------------------------------------------
   // <T>��ò�׽�����ϡ�</T>
   MO_INLINE FCatcherVector* Catchers(){
      return _pCatchers;
   }
public:
   TBool Enter(FCatcher* pCatcher);
   TBool Leave(FCatcher* pCatcher);
public:
   void Track(FCatcher* pCatcher, TInt code);
public:
   TBool Jump(TInt code);
   TBool JumpFinish(FCatcher* pCatcher);
};
//------------------------------------------------------------
typedef FVector<FThreadCatcher*> FThreadCatcherVector;
typedef FList<FThreadCatcher*> FThreadCatcherList;

//============================================================
// <T>��׽���ṹ��</T>
//============================================================
class MO_CM_DECLARE SCatcher{
public:
   TBool installed;
#ifdef _MO_LINUX
   struct sigaction origin;
   struct sigaction source;
#endif // _LINUX
};

//============================================================
// <T>��׽������̨��</T>
//
// @class
// @history 120128 MAOCY ����
//============================================================
class MO_CM_DECLARE FCatcherConsole : public FConsole{
protected:
   TThreadLocker _locker;
   TThreadLocker _lockerInstall;
#ifdef _MO_LINUX
   SCatcher _catchers[MO_TRAP_ACTION_MAXCNT];
#endif // _LINUX
   FThreadCatcherVector* _pThreadCatchers;
public:
   FCatcherConsole();
   MO_ABSTRACT ~FCatcherConsole();
public:
   TBool IsRegistered(TInt code);
   TBool Register(TInt code);
   TBool Unregister(TInt code);

public:
   FThreadCatcher* FindThreadCatcher(TInt threadCode);
   FThreadCatcher* SyncThreadCatcher(TInt threadCode);
   FThreadCatcher* CurrentThreadCatcher();
public:
   TBool Enter(FCatcher* pCatcher);
   TBool Leave(FCatcher* pCatcher);
public:
   TBool Jump(TInt code);
   TBool JumpFinish(FCatcher* pCatcher);
};

//============================================================
// <T>��׽����������</T>
//============================================================
class MO_CM_DECLARE RCatcherManager : public RSingleton<FCatcherConsole>{
};

//============================================================
// <T>��Դ��Ϣ�ࡣ</T>
//
// @reference
// @history 091210 MAOCY ����
//============================================================
class MO_CM_DECLARE RResource{
public:
   static TChar* GetString(TInt id);
};

//============================================================
// <T>�ɸ��ƶ���ӿڡ�</T>
//============================================================
template <typename T>
class MClone{
public:
   MO_VIRTUAL T* Clone() = 0;
};

//============================================================
// <T>�����ٶȲ��ԡ�</T>
//============================================================
class MO_CM_DECLARE TSpeedTest{
protected:
   TTimeTick _beginTick;
   TTimeTick _endTick;
   TFsText _description;
public:
   TSpeedTest();
   TSpeedTest(TCharC* pDescription);
public:
   //------------------------------------------------------------
   // <T>��ÿ�ʼʱ�̡�</T>
   MO_INLINE TTimeTick BeginTick(){
      return _beginTick;
   }
   //------------------------------------------------------------
   // <T>��ý���ʱ�̡�</T>
   MO_INLINE TTimeTick EndTick(){
      return _endTick;
   }
   //------------------------------------------------------------
   // <T>���ʱ��Ρ�</T>
   MO_INLINE TTimeSpan TimeSpan(){
      return _endTick - _beginTick;
   }
public:
   //------------------------------------------------------------
   // <T>��¼��¼ʱ�䡣</T>
   MO_INLINE TTimeSpan Record(){
      _endTick = RTimeTick::Current();
      return TimeSpan();
   }
public:
   void Track();
};

//============================================================
// <T>����Ч�ʲ��ԡ�</T>
//============================================================
class MO_CM_DECLARE TSpeedStatistics{
protected:
   // @attribtue ����
   TInt _code;
   // @attribtue ����
   TInt _count;
   // @attribtue ʧ�ܴ���
   TInt _failureCount;
   // @attribtue ִ��������
   TInt _slowCount;
   // @attribtue ��ʼʱ��
   TTimeTick _beginTick;
   // @attribtue ����ʱ��
   TTimeTick _endTick;
   // @attribtue ��Сʱ��
   TTimeSpan _minTick;
   // @attribtue ���ʱ��
   TTimeSpan _maxTick;
   // @attribtue ����ʱ��ͳ��
   TTimeSpan _countTick;
public:
   //------------------------------------------------------------
   // <T>������Ϣͳ�����ݡ�</T>
   TSpeedStatistics(){
      Reset();
   }
public:
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE TInt Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>���ô��롣</T>
   MO_INLINE void SetCode(TInt code){
      _code = code;
   }
   //------------------------------------------------------------
   // <T>��ô�����</T>
   MO_INLINE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>��ô�����</T>
   MO_INLINE TInt FailureCount(){
      return _failureCount;
   }
   //------------------------------------------------------------
   // <T>���ִ����������</T>
   MO_INLINE TInt SlowCount(){
      return _slowCount;
   }
   //------------------------------------------------------------
   // <T>��ÿ�ʼʱ�̡�</T>
   MO_INLINE TTimeTick BeginTick(){
      return _beginTick;
   }
   //------------------------------------------------------------
   // <T>��ý���ʱ�̡�</T>
   MO_INLINE TTimeTick EndTick(){
      return _endTick;
   }
   //------------------------------------------------------------
   // <T>�����Сʱ�Ρ�</T>
   MO_INLINE TTimeSpan MinTick(){
      return _minTick;
   }
   //------------------------------------------------------------
   // <T>������ʱ�Ρ�</T>
   MO_INLINE TTimeSpan MaxTick(){
      return _maxTick;
   }
   //------------------------------------------------------------
   // <T>��ô���ʱ��ͳ�ơ�</T>
   MO_INLINE TTimeTick CountTick(){
      return _countTick;
   }
   //------------------------------------------------------------
   // <T>���ƽ��ִ��ʱ�̡�</T>
   MO_INLINE TTimeTick AverageTick(){
      if(_count > 0){
         return _countTick / _count;
      }
      return 0;
   }
public:
   //------------------------------------------------------------
   // <T>��ʼ����</T>
   MO_INLINE void Begin(){
      _beginTick = RTimeTick::Current();
   }
   //------------------------------------------------------------
   // <T>��������</T>
   MO_INLINE void End(){
      _endTick = RTimeTick::Current();
   }
   //------------------------------------------------------------
   // <T>���´���</T>
   TTimeSpan Update(TBool result){
      _count++;
      if(!result){
         _failureCount++;
      }
      TTimeSpan span = _endTick - _beginTick;
      // ������Сʱ��
      if(0 == _minTick){
         _minTick = span;
      }else if(span < _minTick){
         _minTick = span;
      }
      // �������ʱ��
      if(0 == _maxTick){
         _maxTick = span;
      }else if(span > _maxTick){
         _maxTick = span;
      }
      // ���ִ���ٶ� (10����)
      if(span > 10000){
         _slowCount++;
      }
      // ������ʱ��
      _countTick += span;
      return span;
   }
   //------------------------------------------------------------
   // <T>���ô���</T>
   void Reset(){
      _code = 0;
      _count = 0;
      _failureCount = 0;
      _slowCount = 0;
      _beginTick = 0;
      _endTick = 0;
      _minTick = 0;
      _maxTick = 0;
      _countTick = 0;
   }
};

//============================================================
// <T>CPU�����ࡣ</T>
//
// @manager
// @source RCpu.cpp
// @history 100128 MAOCY ����
//============================================================
class MO_CM_DECLARE RCpu{
public:
   static TUint64 CurrentCycleCount();
   static TUint64 GetTime(TThreadProcessId pid);
   static double GetRate(TUint64 proc, TUint64 proc2, TUint64 real, TUint64 real2);
   static TFloat GetLoadFactor();
   static TInt GetCpuCount();
   static TInt64 GetCpuRate();
   static TInt64 GetCpuHz();
};

//============================================================
// <T>ϵͳ�����ࡣ</T>
//
// @manager
//============================================================
class MO_CM_DECLARE RSystem{
public:
   static TBool FetchInfo(SSystemInfo* pInfo, TInt processId = -1, TInt threadId = -1);
   static TBool FetchStackSimple(MString* pData);
   static TBool FetchStackDetail(MString* pData);
   static TBool FetchStack(MString* pData);
public:
   static void Dump(MString* pDump = NULL);
};

MO_NAMESPACE_END

#endif // __MO_CM_SYSTEM_H__
