#include "MoCrNetConnection.h"

MO_NAMESPACE_BEGIN

//============================================================
FNetRouterProcessor::FNetRouterProcessor(){
   _pHandless = MO_CREATE(FNetRouterHandlesVector, MO_NETMESSAGE_COUNT);
}

//============================================================
FNetRouterProcessor::~FNetRouterProcessor(){
   MO_DELETE(_pHandless);
}

//============================================================
// <T>��ô��������ϡ�</T>
//============================================================
FNetRouterHandles* FNetRouterProcessor::SyncHandles(TInt code){
   FNetRouterHandles* pHandles = _pHandless->Nvl(code, NULL);
   if(NULL == pHandles){
      pHandles = MO_CREATE(FNetRouterHandles);
      _pHandless->ExtendSet(code, pHandles);
   }
   return pHandles;
}

//============================================================
TBool FNetRouterProcessor::Dispatch(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ������Ϣ
   TInt code = pRouter->MessageHead().Code();
   FNetRouterHandles* pProcessors = _pHandless->Nvl(code, NULL);
   if(NULL != pProcessors){
      // ��ע�����Ϣ���������
      pProcessors->Process(NULL, pRouter);
      return ETrue;
   }
   return EFalse;
}

//============================================================
TBool FNetRouterProcessor::Dispatch(FObject* pSender, TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ������Ϣ
   TInt code = pRouter->MessageHead().Code();
   FNetRouterHandles* pProcessors = _pHandless->Nvl(code, NULL);
   if(NULL != pProcessors){
      // ��ע�����Ϣ���������
      pProcessors->Process(pSender, pRouter);
      return ETrue;
   }
   return EFalse;
}

MO_NAMESPACE_END
