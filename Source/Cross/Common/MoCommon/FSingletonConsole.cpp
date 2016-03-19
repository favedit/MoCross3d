#include "MoCmSingleton.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ψһ�������̨��</T>
//
// @return ����̨
//============================================================
FSingletonConsole::FSingletonConsole(){
   _pSingletons = MO_PTR_CREATE(FSingletonList);
}

//============================================================
// <T>����Ψһ�������̨��</T>
//============================================================
FSingletonConsole::~FSingletonConsole(){
   MO_PTR_DELETE(_pSingletons);
}

//============================================================
// <T>���Ψһ�����б�</T>
//
// @return Ψһ�����б�
//============================================================
FSingletonList* FSingletonConsole::Singletons(){
   return _pSingletons;
}

//============================================================
// <T>ע��Ψһ����</T>
//
// @param pSingleton Ψһ�����б�
//============================================================
void FSingletonConsole::Register(ISingleton* pSingleton){
   _pSingletons->Push(pSingleton);
}

//============================================================
// <T>ע��Ψһ�����б�</T>
//
// @param pSingleton Ψһ�����б�
//============================================================
void FSingletonConsole::Unregister(ISingleton* pSingleton){
   _pSingletons->Remove(pSingleton);
}

MO_NAMESPACE_END
