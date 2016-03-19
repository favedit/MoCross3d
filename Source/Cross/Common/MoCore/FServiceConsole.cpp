#include "MoCrService.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������̨��</T>
//
// @return �������̨
//============================================================
FServiceConsole::FServiceConsole(){
   _pServices = MO_CREATE(FServiceList);
}

//============================================================
// <T>�����������̨��</T>
//============================================================
FServiceConsole::~FServiceConsole(){
   MO_DELETE(_pServices);
}

//============================================================
// <T>��÷����б�</T>
//
// @return ����ģ���б�
//============================================================
FServiceList* FServiceConsole::Services(){
   return _pServices;
}

//============================================================
// <T>ע�����</T>
//
// @param pModule ����ģ��
//============================================================
void FServiceConsole::Register(IService* pService){
   _pServices->Push(pService);
}

//============================================================
// <T>ע������</T>
//
// @param pModule ����ģ��
//============================================================
void FServiceConsole::Unregister(IService* pService){
   _pServices->Remove(pService);
}

MO_NAMESPACE_END
