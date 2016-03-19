#include "MoCmXml.h"
#include "MoCmMonitor.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMonitorMachine, FInstance);

//============================================================
// <T>����������������</T>
//============================================================
FMonitorMachine::FMonitorMachine(){
   _interval = 1000;
   _trackTick = 0;
   MO_CLEAR(_pLocker);
   _pCatcher = MO_CREATE(FMonitorCatcher);
   _pMonitors = MO_CREATE(FMonitorList);
   _pLooper = MO_CREATE(FMonitorLooper);
}

//============================================================
// <T>�����������������</T>
//============================================================
FMonitorMachine::~FMonitorMachine(){
   MO_DELETE(_pCatcher);
   MO_DELETE(_pMonitors);
   MO_DELETE(_pLooper);
}

//============================================================
// <T>�������Ʋ��Ҽ�������</T>
//
// @param pName ����
// @return ������
//============================================================
IMonitor* FMonitorMachine::FindByName(TCharC* pName){
   TListIteratorC<IMonitor*> iterator = _pMonitors->IteratorC();
   while(iterator.Next()){
      IMonitor* pMonitor = *iterator;
      if(pMonitor->IsName(pName)){
         return pMonitor;
      }
   }
   return NULL;
}

//============================================================
// <T>ע���������</T>
//
// @param pMonitor ������
//============================================================
TResult FMonitorMachine::Register(IMonitor* pMonitor){
   MO_CHECK(pMonitor, return ENull);
   _pMonitors->Push(pMonitor);
   _pLooper->Push(pMonitor);
   return ESuccess;
}

//============================================================
// <T>ע����������</T>
//
// @param pMonitor ������
//============================================================
TResult FMonitorMachine::Unregister(IMonitor* pMonitor){
   MO_CHECK(pMonitor, return ENull);
   _pMonitors->Remove(pMonitor);
   _pLooper->Remove(pMonitor);
   return ESuccess;
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param pConfig ������Ϣ
// @return ������
//============================================================
TBool FMonitorMachine::LoadConfig(FXmlNode* pConfig){
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      if(pNode->IsName(TC("Monitor"))){
         // ���Ҽ�����
         TCharC* pName = pNode->Get(TC("name"));
         MO_ASSERT(pName);
         IMonitor* pMonitor = FindByName(pName);
         // ��������
         if(NULL != pMonitor){
            pMonitor->LoadConfig(pNode);
         }
      }
   }
   return ETrue;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FMonitorMachine::Startup(){
   // ��װ��׽��
   _pCatcher->Install();
   // ����������
   TListIteratorC<IMonitor*> iterator = _pMonitors->IteratorC();
   while(iterator.Next()){
      iterator->SetCatcher(_pCatcher);
   }
   return ESuccess;
}

//============================================================
// <T>ִ�д���</T>
//
// @return ������
//============================================================
TResult FMonitorMachine::Execute(){
   TDateTime currentTime = RDateTime::Current();
   TListIteratorC<IMonitor*> iterator = _pMonitors->IteratorC();
   while(iterator.Next()){
      IMonitor* pMonitor = *iterator;
      // ִ�д���
      if(NULL != _pLocker){
         _pLocker->Enter();
         pMonitor->Execute(currentTime);
         _pLocker->Leave();
      }else{
         pMonitor->Execute(currentTime);
      }
   }
   return ESuccess;
}

//============================================================
// <T>ѭ������</T>
//
// @return ������
//============================================================
TResult FMonitorMachine::Process(){
   // �������м�����
   TInt count = _pLooper->Count();
   for(TInt n = 0; n < count; n++){
      IMonitor* pMonitor = _pLooper->Next();
      if(NULL != pMonitor){
         TTimeTick currentTick = RTimeTick::Current();
         if(pMonitor->Test(currentTick)){
            // ִ�д���
            // MO_DEBUG("Monitor porocess. (name=%s, interval=%lld)", pMonitor->Name(), pMonitor->Interval());
            if(NULL != _pLocker){
               _pLocker->Enter();
               pMonitor->Execute(currentTick);
               _pLocker->Leave();
            }else{
               pMonitor->Execute(currentTick);
            }
            // ��ʱ����
            break;
         }
      }
   }
   return ESuccess;
}

MO_NAMESPACE_END
