#ifndef __MO_CR_MONITOR_H__
#define __MO_CR_MONITOR_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_STATISTICS_H__
#include "MoCrStatistics.h"
#endif // __MO_CR_STATISTICS_H__

#ifndef __MO_CR_SERVICE_H__
#include "MoCrService.h"
#endif // __MO_CR_SERVICE_H__

MO_NAMESPACE_BEGIN

//============================================================
class TThreadSection;
class IMonitor;
class FMonitorMachine;

//============================================================
// <T>�����������ࡣ</T>
//
// @history 100301 MAOCY ����
//============================================================
class MO_CR_DECLARE FMonitorService :
      public FService,
      public IStatisticsTrigger{
protected:
   FMonitorMachine* _pMachine;
public:
   FMonitorService();
   MO_ABSTRACT ~FMonitorService();
public:
   MO_OVERRIDE TResult OnLoadConfig(FXmlNode* pConfig);
   MO_OVERRIDE TResult OnStartup();
   MO_OVERRIDE TResult OnProcess();
public:
   FMonitorMachine* Machine();
   void SetSection(IThreadLocker* pLocker);
   void Execute();
public:
   void Register(IMonitor* pMonitor);
   void Unregister(IMonitor* pMonitor);
public:
   //------------------------------------------------------------
   // <T>ע��</T>
   template <typename T>
   void Register(){
      Register(MO_CREATE(T));
   }
public:
   MO_OVERRIDE TResult StatisticsRefresh();
};

//============================================================
// <T>��������������</T>
//
// @history 100301 MAOCY ����
//============================================================
class MO_CR_DECLARE RMonitorService : public RServiceSingleton<FMonitorService>{
};

MO_NAMESPACE_END

#endif // __MO_CR_MONITOR_H__
