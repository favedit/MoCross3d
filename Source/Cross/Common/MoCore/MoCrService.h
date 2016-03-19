#ifndef __MO_CR_SERVICE_H__
#define __MO_CR_SERVICE_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_CONFIGURATION_H__
#include "MoCrConfigruation.h"
#endif // __MO_CR_CONFIGURATION_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ӿڡ�</T>
//
// @history 100301 MAOCY ����
//============================================================
class MO_CR_DECLARE IService :
      public ISingleton,
      public IConfiguration{
public:
   MO_VIRTUAL TResult DoStatus(TInt status) = 0;
   MO_VIRTUAL TResult DoCommand(TInt command, TAny* pArguments) = 0;
public:
   MO_VIRTUAL TResult Startup() = 0;
   MO_VIRTUAL TResult Suspend() = 0;
   MO_VIRTUAL TResult Resume() = 0;
   MO_VIRTUAL TResult Process() = 0;
   MO_VIRTUAL TResult Shutdown() = 0;
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<IService*> FServiceList;
typedef MO_CR_DECLARE FSet<TInt, IService*> FServiceSet;

//============================================================
// <T>���������ࡣ</T>
//
// @history 100301 MAOCY ����
//============================================================
class MO_CR_DECLARE FService :
      public FObject,
      public IService{
protected:
   TInt _code;
   TFsName _name;
public:
   FService();
   MO_ABSTRACT ~FService();
public:
   MO_OVERRIDE TResult Construct();
   MO_OVERRIDE TResult Dispose();
public:
   MO_ABSTRACT TResult OnLoadConfig(FXmlNode* pConfig);
   MO_ABSTRACT TResult OnStatus(TInt status);
   MO_ABSTRACT TResult OnCommand(TInt command, TAny* pArguments);
   MO_ABSTRACT TResult OnStartup();
   MO_ABSTRACT TResult OnSuspend();
   MO_ABSTRACT TResult OnResume();
   MO_ABSTRACT TResult OnProcess();
   MO_ABSTRACT TResult OnShutdown();
public:
   MO_OVERRIDE ESingleton SingletonType();
   MO_OVERRIDE TInt Code();
   MO_OVERRIDE TCharC* Name();
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
public:
   MO_OVERRIDE TResult LoadConfig(FXmlNode* pConfig);
   MO_OVERRIDE TResult DoStatus(TInt status);
   MO_OVERRIDE TResult DoCommand(TInt command, TAny* pArguments);
public:
   MO_OVERRIDE TResult Startup();
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Process();
   MO_OVERRIDE TResult Shutdown();
};

//============================================================
// <T>���������ࡣ</T>
//
// @history 100301 MAOCY ����
//============================================================
class MO_CR_DECLARE FServiceConsole : public FConsole{
protected:
   FServiceList* _pServices;
public:
   FServiceConsole();
   MO_ABSTRACT( ~FServiceConsole() );
public:
   FServiceList* Services();
   void Register(IService* pService);
   void Unregister(IService* pService);
public:
   /*
   void Initialize();
   void Release();
   void DoStatus(TInt status);
   void DoCommand(TInt command, ...);
   void Suspend();
   void Resume();
   void Destory();
   void LoadConfig(FXmlNode* pConfig);*/
};
//------------------------------------------------------------
class MO_CR_DECLARE RServiceManager : public RSingleton<FServiceConsole>{
};

//============================================================
// <T>����Ψһ����ģ���ࡣ</T>
//
// @history 100317 MAOCY ����
//============================================================
template <typename T>
class RServiceSingleton : public RSingleton<T>{
public:
   //------------------------------------------------------------
   // <T>��ʼ�������ʵ����</T>
   static void Create(T* pInstance = NULL){
      RSingleton<T>::Create(pInstance);
      RConfigurationManager::Instance().Register(RSingleton<T>::InstancePtr());
      RServiceManager::Instance().Register(RSingleton<T>::InstancePtr());
   }
   //------------------------------------------------------------
   // <T>�ͷŶ����ʵ����</T>
   static void Destroy(){
      RServiceManager::Instance().Unregister(RSingleton<T>::InstancePtr());
      RConfigurationManager::Instance().Unregister(RSingleton<T>::InstancePtr());
      RSingleton<T>::Destroy();
   }
};

MO_NAMESPACE_END

#endif // __MO_CR_SERVICE_H__
