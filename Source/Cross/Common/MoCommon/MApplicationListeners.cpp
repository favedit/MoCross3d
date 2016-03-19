#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ӧ�ü��������ϡ�</T>
//============================================================
MApplicationListeners::MApplicationListeners(){
   // �����жϼ�����
   _pInterruptListener = MO_CREATE(FApplicationListener);
   _pInterruptListener->SetListenerCd(EApplicationListener_Interrrupt);
   _pInterruptListener->SetListeners(this);
   // �������ؼ�����
   _pReloadListener = MO_CREATE(FApplicationListener);
   _pReloadListener->SetListenerCd(EApplicationListener_Reload);
   _pReloadListener->SetListeners(this);
   // ����ж�ؼ�����
   _pUnloadListener = MO_CREATE(FApplicationListener);
   _pUnloadListener->SetListenerCd(EApplicationListener_Unload);
   _pUnloadListener->SetListeners(this);
   // �����رռ�����
   _pShutdownListener = MO_CREATE(FApplicationListener);
   _pShutdownListener->SetListenerCd(EApplicationListener_Shutdown);
   _pShutdownListener->SetListeners(this);
}

//============================================================
// <T>����Ӧ�ü��������ϡ�</T>
//============================================================
MApplicationListeners::~MApplicationListeners(){
   MO_DELETE(_pInterruptListener);
   MO_DELETE(_pReloadListener);
   MO_DELETE(_pUnloadListener);
   MO_DELETE(_pShutdownListener);
}

//============================================================
// <T>�жϴ���</T>
//
// @return ������
//============================================================
TResult MApplicationListeners::Interrupt(){
   return ESuccess;
}

//============================================================
// <T>���¼��ش���</T>
//
// @return ������
//============================================================
TResult MApplicationListeners::Reload(){
   return ESuccess;
}

//============================================================
// <T>ж�ش���</T>
//
// @return ������
//============================================================
TResult MApplicationListeners::Unload(){
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult MApplicationListeners::Shutdown(){
   return ESuccess;
}

MO_NAMESPACE_END
