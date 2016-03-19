
#ifdef _MO_LINUX
#include <unistd.h>
#endif
#include <MoCmStream.h>
#include <MoCmNet.h>
#include "MoCrNetConnection.h"

#define MO_MD_MESSAGE_WAIT_INTERVAL 1

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣͳ�ƿ���̨��</T>
//============================================================
FNetMessageStatisticsConsole::FNetMessageStatisticsConsole(){
   _pMachine = MO_CREATE(FNetMessageStatisticsMachine);
   _pMachines = MO_CREATE(FNetMessageStatisticsMachineList);
   _pMachines->Push(_pMachine);
}

//============================================================
// <T>������Ϣͳ�ƿ���̨��</T>
//============================================================
FNetMessageStatisticsConsole::~FNetMessageStatisticsConsole(){
   MO_DELETE(_pMachine);
   MO_DELETE(_pMachines);
};

//============================================================
// <T>ע����Ϣͳ�ƻ���</T>
//
// @param pMachine ��Ϣͳ�ƻ�
//============================================================
void FNetMessageStatisticsConsole::Register(FNetMessageStatisticsMachine* pMachine){
   _pMachines->Push(pMachine);
}

//============================================================
// <T>ע����Ϣͳ�ƻ���</T>
//
// @param pMachine ��Ϣͳ�ƻ�
//============================================================
void FNetMessageStatisticsConsole::Unregister(FNetMessageStatisticsMachine* pMachine){
   _pMachines->Remove(pMachine);
}

//============================================================
// <T>���ͳ����Ϣ��</T>
//
// @return ������
//============================================================
TResult FNetMessageStatisticsConsole::StatisticsRefresh(){
   // ��Ϣִ��ͳ��
   TFsDump dump;
   TListIteratorC<FNetMessageStatisticsMachine*> iterator = _pMachines->IteratorC();
   while(iterator.Next()){
      FNetMessageStatisticsMachine* pMachine = *iterator;
      pMachine->Dump(dump);
   }
   MO_INFO(TC("Message statistics.%s"), (TCharC*)dump);
   // ��Ϣ����ͳ��
   if(RNetQueueModule::IsValid()){
      RNetQueueModule::Instance().Connection()->Dump();
   }
   if(RNetClientQueueModule::IsValid()){
      RNetClientQueueModule::Instance().Connection()->Dump();
   }
   return ESuccess;
}
   
MO_NAMESPACE_END
