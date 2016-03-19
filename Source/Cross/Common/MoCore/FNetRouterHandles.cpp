#include "MoCrNetConnection.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣ����ص������ϡ�</T>
//============================================================
FNetRouterHandles::FNetRouterHandles(){
   _pProcessors = MO_CREATE(FNetRouterHandleList);
}

//============================================================
// <T>������Ϣ����ص������ϡ�</T>
//============================================================
FNetRouterHandles::~FNetRouterHandles(){
   MO_DELETE(_pProcessors);
};

//============================================================
// <T>ִ����Ϣ����</T>
//============================================================
TBool FNetRouterHandles::Process(FObject* pSender, TNetRouter* pRouter){
   TBool result = ETrue;
   if(!_pProcessors->IsEmpty()){
      TListIteratorC<FNetRouterHandle*> iterator = _pProcessors->IteratorC();
      while(iterator.Next()){
         FNetRouterHandle* pHandle = *iterator;
         result = pHandle->Process(pSender, pRouter);
         if(result){
            MO_DEBUG(TC("Process router hanle success. (message=%s, invoker=%s)"),
                  pRouter->MessageInfo()->Name(), pHandle->InvokerName());
         }else{
            MO_ERROR(TC("Process router hanle failure. (message=%s, invoker=%s)"),
                  pRouter->MessageInfo()->Name(), pHandle->InvokerName());
         }
      }
   }
   return ETrue;
}

MO_NAMESPACE_END
