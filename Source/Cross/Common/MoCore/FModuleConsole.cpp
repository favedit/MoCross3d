#include "MoCrModule.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ģ�����̨��</T>
//
// @return ģ�����̨
//============================================================
FModuleConsole::FModuleConsole(){
   _pModules = MO_CREATE(FModuleList);
}

//============================================================
// <T>����ģ�����̨��</T>
//============================================================
FModuleConsole::~FModuleConsole(){
   MO_DELETE(_pModules);
}

//============================================================
// <T>���ģ���б�</T>
//
// @return ģ���б�
//============================================================
FModuleList* FModuleConsole::Modules(){
   return _pModules;
}

//============================================================
// <T>ע��ģ�顣</T>
//
// @param pModule ģ��
//============================================================
void FModuleConsole::Register(FModule* pModule){
   _pModules->Push(pModule);
}

//============================================================
// <T>ע��ģ�顣</T>
//
// @param pModule ģ��
//============================================================
void FModuleConsole::Unregister(FModule* pModule){
   _pModules->Remove(pModule);
}

//============================================================
// <T>��ʼ������ģ�顣</T>
//
// @return ������
//============================================================
TResult FModuleConsole::Initialize(){
   TListIteratorC<FModule*> iterator = _pModules->IteratorC();
   while(iterator.Next()){
      iterator->Initialize();
   }
   return ESuccess;
}

//============================================================
// <T>�ж�����ģ�顣</T>
//
// @return ������
//============================================================
TResult FModuleConsole::Interrupt(){
   TListIteratorC<FModule*> iterator = _pModules->IteratorC();
   while(iterator.Next()){
      iterator->Release();
   }
   return ESuccess;
}

//============================================================
// <T>���¼�������ģ�顣</T>
//
// @return ������
//============================================================
TResult FModuleConsole::Reload(){
   TListIteratorC<FModule*> iterator = _pModules->IteratorC();
   while(iterator.Next()){
      iterator->Reload();
   }
   return ESuccess;
}

//============================================================
// <T>ж������ģ�顣</T>
//
// @return ������
//============================================================
TResult FModuleConsole::Unload(){
   TListIteratorC<FModule*> iterator = _pModules->IteratorC();
   while(iterator.Next()){
      iterator->Unload();
   }
   return ESuccess;
}

//============================================================
// <T>�ͷ�����ģ�顣</T>
//
// @return ������
//============================================================
TResult FModuleConsole::Release(){
   TListIteratorC<FModule*> iterator = _pModules->IteratorC();
   while(iterator.Next()){
      iterator->Release();
   }
   return ESuccess;
}

MO_NAMESPACE_END
