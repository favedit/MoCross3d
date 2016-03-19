#include "MoCmClass.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������̨��</T>
//============================================================
FClassConsole::FClassConsole(){
   _looperLimit = 16;
}

//============================================================
// <T>���������̨��</T>
//============================================================
FClassConsole::~FClassConsole(){
}

//============================================================
// <T>ע�������</T>
//
// @param pClass �����
// @return �����
//============================================================
FClass* FClassConsole::Register(FClass* pClass){
   MO_ASSERT(pClass);
   // ���������
   TCharC* pClassName = pClass->Name();
   if(_classes.Contains(pClassName)){
      MO_STATIC_FATAL(TC("Class is already exists. (class_name=%s)"), pClassName);
   }
   // ���������
   _classes.Set(pClassName, pClass);
   _looper.Push(pClass);
   return pClass;
}

//============================================================
// <T>���������</T>
//
// @param pClassName ������
// @return �����
//============================================================
FClass* FClassConsole::FindClass(TCharC* pClassName){
   FClass* pClass = NULL;
   if(pClassName != NULL){
      pClass = _classes.Find(pClassName);
   }
   return pClass;
}

//============================================================
// <T>������ʵ����</T>
//
// @param pClassName ������
// @return ��ʵ��
//============================================================
FInstance* FClassConsole::InstanceCreate(TCharC* pClassName){
   FClass* pClass = FindClass(pClassName);
   return InstanceCreate(pClass);
}

//============================================================
// <T>������ʵ����</T>
//
// @param pClass �����
// @return ��ʵ��
//============================================================
FInstance* FClassConsole::InstanceCreate(FClass* pClass){
   MO_ASSERT(pClass);
   FInstance* pInstance = pClass->InstanceCreate();
   return pInstance;
}

//============================================================
// <T>�ռ���ʵ����</T>
//
// @param pClassName ������
// @return ��ʵ��
//============================================================
FInstance* FClassConsole::InstanceAlloc(TCharC* pClassName){
   FClass* pClass = FindClass(pClassName);
   return InstanceCreate(pClass);
}

//============================================================
// <T>�ռ���ʵ����</T>
//
// @param pClass �����
// @return ��ʵ��
//============================================================
FInstance* FClassConsole::InstanceAlloc(FClass* pClass){
   MO_ASSERT(pClass);
   FInstance* pInstance = pClass->InstanceAlloc();
   return pInstance;
}

//============================================================
// <T>�ͷ���ʵ����</T>
//
// @param pInstance ��ʵ��
//============================================================
void FClassConsole::InstanceFree(FInstance* pInstance){
   MO_ASSERT(pInstance);
   FClass* pClass = pInstance->GetClass();
   pClass->InstanceFree(pInstance);
}

//============================================================
// <T>ɾ����ʵ����</T>
//
// @param pInstance ��ʵ��
//============================================================
void FClassConsole::InstanceDelete(FInstance* pInstance){
   MO_ASSERT(pInstance);
   FClass* pClass = pInstance->GetClass();
   pClass->InstanceDelete(pInstance);
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FClassConsole::Process(){
   _looper.Record();
   for(TInt n = 0; n < _looperLimit; n++){
      FClass* pClass = _looper.Next();
      if(pClass == NULL){
         break;
      }
      pClass->Process();
   }
   return ESuccess;
}

//============================================================
// <T>���ټ�����Ϣ��</T>
//============================================================
void FClassConsole::TrackActive(){
   TInt count = _classes.Count();
   MO_DEBUG(TC("Class track. (count=%d)"));
   TDictionaryIteratorC<FClass*> iterator = _classes.IteratorC();
   while(iterator.Next()){
      FClass* pClass = *iterator;
      if(pClass->ActiveCount() > 0){
         TFsDump dump;
         pClass->Dump(dump.Memory(), dump.Size());
         MO_DEBUG(TC("   %s"), (TCharC*)dump);
      }
   }
}

//============================================================
// <T>����ȫ����Ϣ��</T>
//============================================================
void FClassConsole::TrackAll(){
   TInt count = _classes.Count();
   MO_DEBUG(TC("Class track. (count=%d)"));
   TDictionaryIteratorC<FClass*> iterator = _classes.IteratorC();
   while(iterator.Next()){
      FClass* pClass = *iterator;
      TFsDump dump;
      pClass->Dump(dump.Memory(), dump.Size());
      MO_DEBUG(TC("   %s"), (TCharC*)dump);
   }
}

MO_NAMESPACE_END
