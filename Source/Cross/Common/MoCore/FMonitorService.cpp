#include <MoCmMonitor.h>
#include "MoCrMonitor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������������</T>
//============================================================
FMonitorService::FMonitorService(){
   _name = TC("Service.Monitor");
   _pMachine = MO_CREATE(FMonitorMachine);
}

//============================================================
// <T>��������������</T>
//============================================================
FMonitorService::~FMonitorService(){
   MO_DELETE(_pMachine);
}

//============================================================
// <T>���������������¼���</T>
//
// @param pConfig ������Ϣ
// @return ������
//============================================================
TResult FMonitorService::OnLoadConfig(FXmlNode* pConfig){
   _pMachine->LoadConfig(pConfig);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FMonitorService::OnStartup(){
   _pMachine->Startup();
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FMonitorService::OnProcess(){
   _pMachine->Process();
   return ESuccess;
}

//============================================================
// <T>����ͬ������</T>
//
// @param pSection ͬ����
//============================================================
void FMonitorService::SetSection(IThreadLocker* pLocker){
   _pMachine->SetLocker(pLocker);
}

//============================================================
// <T>ִ�д���</T>
//============================================================
void FMonitorService::Execute(){
   _pMachine->Execute();
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pMonitor ������
//============================================================
void FMonitorService::Register(IMonitor* pMonitor){
   _pMachine->Register(pMonitor);
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pMonitor ������
//============================================================
void FMonitorService::Unregister(IMonitor* pMonitor){
   _pMachine->Unregister(pMonitor);
}

//============================================================
// <T>ͳ��ˢ�¡�</T>
//
// @return ������
//============================================================
TResult FMonitorService::StatisticsRefresh(){
   // ��Ϣִ��ͳ��
   TFsDump dump;
   FMonitorList::TIteratorC iterator = _pMachine->Monitors()->IteratorC();
   while(iterator.Next()){
      FMonitor* pMonitor = (FMonitor*)*iterator;
      if(NULL != pMonitor){
         TSpeedStatistics& statistics = pMonitor->Statistics();
         dump.AppendFormat(TC("\n   ") MO_FMT_OBJECT_NAME TC(" count=%8d, tick=(%8d - %-8d) - %8d (failure=%16lld, slow=%16lld)"),
               pMonitor->Name(), statistics.Count(), statistics.MinTick(), statistics.MaxTick(),
               statistics.AverageTick(), statistics.FailureCount(), statistics.SlowCount());
      }
   }
   MO_INFO(TC("Monitor statistics. (count=%d)%s"), _pMachine->Monitors()->Count(), (TCharC*)dump);
   return ESuccess;
}

MO_NAMESPACE_END
