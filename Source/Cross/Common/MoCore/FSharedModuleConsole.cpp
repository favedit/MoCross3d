#include "MoCrModule.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲��ģ�����̨��</T>
//
// @return ����ģ�����̨
//============================================================
FSharedModuleConsole::FSharedModuleConsole(){
   _pModules = MO_CREATE(FSharedModuleList);
}

//============================================================
// <T>��������ģ�����̨��</T>
//============================================================
FSharedModuleConsole::~FSharedModuleConsole(){
   MO_DELETE(_pModules);
}

//============================================================
// <T>��ù���ģ���б�</T>
//
// @return ����ģ���б�
//============================================================
FSharedModuleList* FSharedModuleConsole::Modules(){
   return _pModules;
}

//============================================================
// <T>ע�Ṳ��ģ�顣</T>
//
// @param pModule ����ģ��
//============================================================
void FSharedModuleConsole::Register(FSharedModule* pModule){
   _pModules->Push(pModule);
}

//============================================================
// <T>ע������ģ�顣</T>
//
// @param pModule ����ģ��
//============================================================
void FSharedModuleConsole::Unregister(FSharedModule* pModule){
   _pModules->Remove(pModule);
}

MO_NAMESPACE_END
