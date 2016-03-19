#include "MoCrNetConnection.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣ����ص������ϡ�</T>
//============================================================
FNetTransferHandles::FNetTransferHandles(){
   _pRouterProcessors = MO_CREATE(FNetRouterHandleList);
   _pTransferProcessors = MO_CREATE(FNetTransferHandleList);
   MO_CLEAR(_pCatcher);
}

//============================================================
// <T>������Ϣ����ص������ϡ�</T>
//============================================================
FNetTransferHandles::~FNetTransferHandles(){
   MO_DELETE(_pRouterProcessors);
   MO_DELETE(_pTransferProcessors);
};

//============================================================
// <T>����·������</T>
//
// @param pHandle ���
// @param pSender ������
// @param pTransfer ������
// @return ������
//============================================================
TBool FNetTransferHandles::ProcessRouter(FNetRouterHandle* pHandle, FObject* pSender, TNetTransfer* pTransfer){
   TBool result = ETrue;
#ifdef _MO_ANDROID
   if(!pHandle->Process(pSender, pTransfer)){
      result = EFalse;
   }
#else
   if(NULL != _pCatcher){
      _pCatcher->LinkInfo(pHandle->InvokerName());
      _pCatcher->Enter();
      if(MO_TRAP_CATCHER(_pCatcher)){
         _pCatcher->Recorded();
         if(!pHandle->Process(pSender, pTransfer)){
            result = EFalse;
         }
      }else{
         _pCatcher->JumpFinish();
         result = EFalse;
      }
      _pCatcher->Leave();
   }else{
      if(!pHandle->Process(pSender, pTransfer)){
         result = EFalse;
      }
   }
#endif // _MO_ANDROID
   return result;
}

//============================================================
// <T>����������</T>
//
// @param pHandle ���
// @param pSender ������
// @param pTransfer ������
// @return ������
//============================================================
TBool FNetTransferHandles::ProcessTransfer(FNetTransferHandle* pHandle, FObject* pSender, TNetTransfer* pTransfer){
   TBool result = ETrue;
#ifdef _MO_ANDROID
   if(!pHandle->Process(pSender, pTransfer)){
      result = EFalse;
   }
#else
   if(NULL != _pCatcher){
      _pCatcher->LinkInfo(pHandle->InvokerName());
      _pCatcher->Enter();
      if(MO_TRAP_CATCHER(_pCatcher)){
         _pCatcher->Recorded();
         if(!pHandle->Process(pSender, pTransfer)){
            result = EFalse;
         }
      }else{
         _pCatcher->JumpFinish();
         result = EFalse;
      }
      _pCatcher->Leave();
   }else{
      if(!pHandle->Process(pSender, pTransfer)){
         result = EFalse;
      }
   }
#endif // _MO_ANDROID
   return result;
}

//============================================================
// <T>ִ����Ϣ����</T>
// @param pSender ������
// @param pTransfer ������
// @return ������
//============================================================
TBool FNetTransferHandles::Process(FObject* pSender, TNetTransfer* pTransfer){
   TBool result = ETrue;
   // ����·����
   if(result && !_pRouterProcessors->IsEmpty()){
      TListIteratorC<FNetRouterHandle*> iterator = _pRouterProcessors->IteratorC();
      while(iterator.Next()){
         FNetRouterHandle* pHandle = *iterator;
         MO_DEBUG(TC("Process router handle. (invoker=%s)"), pHandle->InvokerName());
         TBool processResult = ProcessRouter(pHandle, pSender, pTransfer);
         if(!processResult){
            result = EFalse;
            break;
         }
      }
   }
   // ��������
   if(result && !_pTransferProcessors->IsEmpty()){
      TListIteratorC<FNetTransferHandle*> iterator = _pTransferProcessors->IteratorC();
      while(iterator.Next()){
         FNetTransferHandle* pHandle = *iterator;
         MO_DEBUG(TC("Process transfer handle. (invoker=%s)"), pHandle->InvokerName());
         TBool processResult = ProcessTransfer(pHandle, pSender, pTransfer);
         if(!processResult){
            result = EFalse;
            break;
         }
      }
   }
   return result;
}

MO_NAMESPACE_END
