#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ӧ�ü�������</T>
//============================================================
FApplicationListener::FApplicationListener(){
   _listenerCd = EApplicationListener_Unknown;
   MO_CLEAR(_pListeners);
}

//============================================================
// <T>����Ӧ�ü�������</T>
//============================================================
FApplicationListener::~FApplicationListener(){
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TBool FApplicationListener::Process(){
   switch(_listenerCd){
      case EApplicationListener_Interrrupt:
         _pListeners->Interrupt();
         break;
      case EApplicationListener_Reload:
         _pListeners->Reload();
         break;
      case EApplicationListener_Unload:
         _pListeners->Unload();
         break;
      case EApplicationListener_Shutdown:
         _pListeners->Shutdown();
         break;
      default:
         MO_ERROR(TC("Unknown listener code. (listener_cd=%d)"), _listenerCd);
         break;
   }
   return ETrue;
}

MO_NAMESPACE_END
