#include "MoCrMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣ�߼���ʵ����</T>
//
// @return ʵ������
//============================================================
FMessageLogic::FMessageLogic(){
   _pProcessor = MO_CREATE(FNetTransferProcessor);
   MO_CLEAR(_pStatisticsMachine);
}

//============================================================
// <T>������Ϣ�߼���ʵ����</T>
//============================================================
FMessageLogic::~FMessageLogic(){
   MO_DELETE(_pProcessor);
   MO_DELETE(_pStatisticsMachine);
}

//============================================================
// <T>����δ֪��Ϣ��</T>
//
// @return ������
//============================================================
TBool FMessageLogic::OnUnknownRouter(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // δ֪��Ϣ
   TChar dump[MO_FS_DUMP_LENGTH];
   TChar format[MO_FS_DUMP_LENGTH];
   MO_ERROR(TC("Unknown message. (%s)\n%s"),
         pRouter->Dump(dump, MO_FS_DUMP_LENGTH),
         pRouter->DumpMemory(format, MO_FS_DUMP_LENGTH));
   return EFalse;
}

//============================================================
// <T>ע�����д�������</T>
//
// @return ������
//============================================================
TBool FMessageLogic::RegisterAllProcessors(){
   return ETrue;
}

//============================================================
// <T>ע�����д�������</T>
//
// @return ������
//============================================================
TBool FMessageLogic::UnregisterAllProcessors(){
   return ETrue;
}

//============================================================
// <T>������Ϣ��������</T>
//
// @parma pTransfer ������
// @return ������
//============================================================
TBool FMessageLogic::ProcessTransfer(TNetTransfer* pTransfer){
   return ETrue;
}

//============================================================
// <T>�׷���Ϣ��������</T>
//
// @parma pTransfer ������
// @return ������
//============================================================
TBool FMessageLogic::DispatchTransfer(TNetTransfer* pTransfer){
   TBool result = EFalse;
   TTimeSpan span = 0;
   TInt code = pTransfer->MessageHead().Code();
   // �ַ�����
   FNetMessageStatistics* pStatistics = NULL;
   if(NULL != _pStatisticsMachine){
      pStatistics = _pStatisticsMachine->Get(code);
      pStatistics->DoBegin();
      result = _pProcessor->Dispatch(pTransfer);
      if(result){
         pStatistics->DoEnd();
         span = pStatistics->Update(result);
      }
   }else{
      // ��ʼ��ʱ
      TTimeTick beginTick = RTimeTick::Current();
      result = _pProcessor->Dispatch(pTransfer);
      TTimeTick endTick = RTimeTick::Current();
      span = endTick - beginTick;
   }
   // ��־���� (û����Ϣͳ������ʱ����������������Ϣͳ����ͳ��)
   if(NULL == pStatistics){
      if(span >= MO_NET_MESSAGE_SLOW_TICK){
         MO_WARN(TC("Dispatch messge slow. plase check logic. (message=%s, tick=%ld)"), pTransfer->MessageHead().CodeName(), span);
      }
   }
   return result;
}

MO_NAMESPACE_END
