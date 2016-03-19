#include "MoCrStatistics.h"
#include "MoCrMonitor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ͳ����Ϣ����̨��</T>
//============================================================
FStatisticsConsole::FStatisticsConsole(){
   _pStatisticsDictionary = MO_CREATE(FStatisticsDictionary);
   _pStatisticsSet = MO_CREATE(FStatisticsSet);
   _pStatisticsTriggers = MO_CREATE(FStatisticsTriggerList);
   _pMonitor = MO_CREATE(FStatisticsMonitor);
}

//============================================================
// <T>����ͳ����Ϣ����̨��</T>
//============================================================
FStatisticsConsole::~FStatisticsConsole(){
   MO_DELETE(_pStatisticsDictionary);
   MO_DELETE(_pStatisticsSet);
   MO_DELETE(_pStatisticsTriggers);
   MO_DELETE(_pMonitor);
}

//============================================================
// <T>��������ͬ��ͳ����Ϣ��</T>
//
// @param pName ����
// @param pClass �����
// @return ͳ����
//============================================================
FStatistics* FStatisticsConsole::SyncByName(TCharC* pName, FClass* pClass){
   MO_ASSERT(pName);
   FStatistics* pStatistics = _pStatisticsDictionary->Find(pName);
   if(pStatistics == NULL){
      if(pClass == NULL){
         pClass = FStatistics::Class();
      }
      pStatistics = (FStatistics*)pClass->InstanceAlloc();
      pStatistics->SetName(pName);
      _pStatisticsDictionary->Set(pName, pStatistics);
   }
   return pStatistics;
}

//============================================================
// <T>����ͳ�Ʊ�Ų���һ��ͳ������</T>
//
// @param code ͳ�Ʊ��
// @return ͳ����
//============================================================
IStatistics* FStatisticsConsole::StatisticsFind(TStatisticsId code){
   return _pStatisticsSet->Find(code);
}

//============================================================
// <T>���ݷ����ź���Ŀ��Ų���һ��ͳ������</T>
//
// @param groupId ������
// @param itemId ��Ŀ���
// @return ͳ����
//============================================================
IStatistics* FStatisticsConsole::StatisticsFind(TInt groupId, TInt itemId){
   SStatisticsId code((TUint16)groupId, (TUint16)itemId);
   return _pStatisticsSet->Find(code);
}

//============================================================
// <T>����ͳ�Ʊ�Ų���һ��ͬ��ͳ������</T>
//
// @param code ͳ�Ʊ��
// @return ͳ����
//============================================================
IStatistics* FStatisticsConsole::StatisticsSync(TStatisticsId code){
   // ��������
   IStatistics* pStatistics = StatisticsFind(code);
   if(pStatistics == NULL){
      // ��������
      FStatistics* pAlloc = MO_CREATE(FStatistics);
      pAlloc->SetCode(code);
      _pStatisticsSet->Set(code, pAlloc);
      // ��������
      pStatistics = pAlloc;
   }
   return pStatistics;
}

//============================================================
// <T>���ݷ����ź���Ŀ���ͬ��һ��ͳ������</T>
//
// @param groupId ������
// @param itemId ��Ŀ���
// @return ͳ����
//============================================================
IStatistics* FStatisticsConsole::StatisticsSync(TInt groupId, TInt itemId){
   SStatisticsId code((TUint16)groupId, (TUint16)itemId);
   return StatisticsSync(code);
}

//============================================================
// <T>ע��һ��ͳ������</T>
//
// @param pStatistics ͳ����
// @return ������
//============================================================
TResult FStatisticsConsole::StatisticsRegister(IStatistics* pStatistics){
   MO_CHECK(pStatistics, return ENull);
   TStatisticsId code = pStatistics->Code();
   if(_pStatisticsSet->Contains(code)){
      MO_FATAL("Statistics has registered. (code=%d, statistics=" MO_FMT_POINTER ")", code, pStatistics);
      return EDuplicate;
   }
   _pStatisticsSet->Set(code, pStatistics);
   return ESuccess;
}

//============================================================
// <T>ע��һ��ͳ������</T>
//
// @param pStatistics ͳ����
// @return ������
//============================================================
TResult FStatisticsConsole::StatisticsUnregister(IStatistics* pStatistics){
   MO_CHECK(pStatistics, return ENull);
   TStatisticsId code = pStatistics->Code();
   if(!_pStatisticsSet->Contains(code)){
      MO_FATAL("Statistics has not registered. (code=%d, statistics=" MO_FMT_POINTER ")", code, pStatistics);
      return EDuplicate;
   }
   _pStatisticsSet->Set(code, pStatistics);
   return ESuccess;
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pTrigger ������
// @return ������
//============================================================
TResult FStatisticsConsole::TriggerRegister(IStatisticsTrigger* pTrigger){
   MO_CHECK(pTrigger, return ENull);
   if(_pStatisticsTriggers->Contains(pTrigger)){
      MO_FATAL("Trigger has registered. (trigger=" MO_FMT_POINTER ")", pTrigger);
      return EDuplicate;
   }
   _pStatisticsTriggers->Push(pTrigger);
   return ESuccess;
}

//============================================================
// <T>ע��ͳ�ƴ�������</T>
//
// @param pTrigger ������
// @return ������
//============================================================
TResult FStatisticsConsole::TriggerUnregister(IStatisticsTrigger* pTrigger){
   MO_CHECK(pTrigger, return ENull);
   if(!_pStatisticsTriggers->Contains(pTrigger)){
      MO_FATAL("Statistics has not registered. (trigger=" MO_FMT_POINTER ")", pTrigger);
      return ENotExists;
   }
   _pStatisticsTriggers->Remove(pTrigger);
   return ESuccess;
}

//============================================================
// <T>������������</T>
//
// @return ������
//============================================================
TResult FStatisticsConsole::StartupMonitor(){
   // ע�������
   _pMonitor->SetConsole(this);
   RMonitorService::Instance().Register(_pMonitor);
   return ESuccess;
}

//============================================================
// <T>������ˢ�´���</T>
//
// @param currentTick ��ǰʱ��
// @return ������
//============================================================
TResult FStatisticsConsole::TriggerRefresh(TTimeTick currentTick){
   MO_INFO(TC("Statistics begin: ------------------------------------------------------------"));
   // �ڴ�ͳ��
   RSystem::Dump();
   // �ڴ�洢ͳ��
   IMemoryStorage* pStorage = RMemory::Storage();
   if(NULL != pStorage){
      if(pStorage->IsAble()){
         pStorage->Dump();
      }
   }
   // ͳ��������
   TListIteratorC<IStatisticsTrigger*> iterator = _pStatisticsTriggers->IteratorC();
   while(iterator.Next()){
      iterator->StatisticsRefresh();
   }
   MO_INFO(TC("Statistics end:   ------------------------------------------------------------"));
   return ESuccess;
}

//============================================================
// <T>������������</T>
//
// @return ������
//============================================================
TResult FStatisticsConsole::Reset(){
   FStatisticsDictionary::TIteratorC iterator = _pStatisticsDictionary->IteratorC();
   while(iterator.Next()){
      FStatistics* pStatistics = *iterator;
      pStatistics->Reset();
   }
   return ESuccess;
}

//============================================================
// <T>��ʾ������Ϣ��</T>
//
// @return ������
//============================================================
TResult FStatisticsConsole::Track(){
   MO_INFO(TC("Statistics begin: ------------------------------------------------------------"));
   // ͳ��������
   FStatisticsDictionary::TIteratorC iterator = _pStatisticsDictionary->IteratorC();
   while(iterator.Next()){
      FStatistics* pStatistics = *iterator;
      pStatistics->Track();
   }
   MO_INFO(TC("Statistics end:   ------------------------------------------------------------"));
   return ESuccess;
}

MO_NAMESPACE_END
