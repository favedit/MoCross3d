#include "MoCrStatistics.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ͳ����Ϣ��������</T>
//============================================================
FStatisticsMonitor::FStatisticsMonitor(){
   _name = TC("Core.Statistics.Monitor");
   MO_CLEAR(_pConsole);
}

//============================================================
// <T>����ͳ����Ϣ��������</T>
//============================================================
FStatisticsMonitor::~FStatisticsMonitor(){
}

//============================================================
// <T>ˢ�´���</T>
//
// @return ������
//============================================================
TResult FStatisticsMonitor::Process(){
   TResult result = ESuccess;
   if(_pConsole != NULL){
      result = _pConsole->TriggerRefresh(_currentTimeTick);
   }
   return result;
}

MO_NAMESPACE_END
