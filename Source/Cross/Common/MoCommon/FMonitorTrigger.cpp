#include "MoCmMonitor.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMonitorTrigger, FMonitor);

//============================================================
// <T>��������������ʵ����</T>
//
// @return ��ǰʵ��ָ��
//============================================================
FMonitorTrigger::FMonitorTrigger(){
   _name = TC("Monitor.Trigger");
   MO_CLEAR(_pTrigger);
}

//============================================================
// <T>���������������ʵ����</T>
//
// @return ��ǰʵ��ָ��
//============================================================
FMonitorTrigger::~FMonitorTrigger(){
}

//============================================================
// <T>ˢ�´���</T>
//
// @return ������
//============================================================
TResult FMonitorTrigger::Process(){
   MO_ASSERT(_pTrigger);
   return _pTrigger->TriggerRefresh(_currentTimeTick);
}

MO_NAMESPACE_END
