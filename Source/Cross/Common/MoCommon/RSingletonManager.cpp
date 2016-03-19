#include "MoCmSingleton.h"

MO_NAMESPACE_BEGIN

//============================================================
TThreadLocker RSingletonManager::_locker;
FSingletonConsole* RSingletonManager::_pInstance = NULL;

//============================================================
// <T>��ʼ�������ʵ����</T>
//============================================================
void RSingletonManager::Create(){
   MO_ASSERT(!_pInstance);
   _pInstance = MO_PTR_CREATE(FSingletonConsole);
}

//============================================================
// <T>�ͷŶ����ʵ����</T>
//============================================================
void RSingletonManager::Destroy(){
   MO_ASSERT(_pInstance);
   MO_PTR_DELETE(_pInstance);
}

//============================================================
// <T>ע��Ψһ����</T>
//
// @param pSingleton Ψһ�����б�
//============================================================
void RSingletonManager::Register(ISingleton* pSingleton){
   FSingletonConsole* pSingletonConsole = SafeInstancePtr();
   pSingletonConsole->Register(pSingleton);
}

//============================================================
// <T>ע��Ψһ�����б�</T>
//
// @param pSingleton Ψһ�����б�
//============================================================
void RSingletonManager::Unregister(ISingleton* pSingleton){
   FSingletonConsole* pSingletonConsole = SafeInstancePtr();
   pSingletonConsole->Unregister(pSingleton);
}

MO_NAMESPACE_END
