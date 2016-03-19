#include "MoCrNetConnection.h"

MO_NAMESPACE_BEGIN

//============================================================
FNetMessageProcessor::FNetMessageProcessor(){
   _pHandless = MO_CREATE(FNetMessageHandlesVector, MO_NETMESSAGE_COUNT);
}

//============================================================
FNetMessageProcessor::~FNetMessageProcessor(){
   MO_DELETE(_pHandless);
}

//============================================================
// <T>��ô��������ϡ�</T>
//============================================================
FNetMessageHandles* FNetMessageProcessor::SyncHandles(TInt code){
   FNetMessageHandles* pHandles = _pHandless->Nvl(code, NULL);
   if(NULL == pHandles){
      pHandles = MO_CREATE(FNetMessageHandles);
      _pHandless->ExtendSet(code, pHandles);
   }
   return pHandles;
}

//============================================================
TBool FNetMessageProcessor::Dispatch(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ������Ϣ
   TInt code = pMessage->MessageHead().Code();
   FNetMessageHandles* pProcessors = _pHandless->Nvl(code, NULL);
   if(NULL != pProcessors){
      // ��ע�����Ϣ���������
      pProcessors->Process(NULL, pMessage);
      return ETrue;
   }
   return EFalse;
}

//============================================================
TBool FNetMessageProcessor::Dispatch(FObject* pSender, TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ������Ϣ
   TInt code = pMessage->MessageHead().Code();
   FNetMessageHandles* pProcessors = _pHandless->Nvl(code, NULL);
   if(NULL != pProcessors){
      // ��ע�����Ϣ���������
      pProcessors->Process(pSender, pMessage);
      return ETrue;
   }
   return EFalse;
}

MO_NAMESPACE_END
