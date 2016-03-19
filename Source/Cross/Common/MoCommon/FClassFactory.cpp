#include "MoCmClassBase.h"
#include "MoCmClass.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FClassFactory, FInstance);

//============================================================
// <T>�����๤����</T>
//============================================================
FClassFactory::FClassFactory(){
   _pClasses = MO_CREATE(FClassDictionary);
}

//============================================================
// <T>�����๤����</T>
//============================================================
FClassFactory::~FClassFactory(){
   MO_DELETE(_pClasses);
}

//============================================================
// <T>ע��һ�������</T>
//
// @param pName ����
// @param pClass �����
// @return ������
//============================================================
TResult FClassFactory::Register(FClass* pClass){
   MO_ASSERT(pClass);
   _pClasses->Set(pClass->Name(), pClass);
   return ESuccess;
}

//============================================================
// <T>ע��һ�������</T>
//
// @param pName ����
// @param pClass �����
// @return ������
//============================================================
TResult FClassFactory::Register(TCharC* pName, FClass* pClass){
   MO_ASSERT(pName);
   MO_ASSERT(pClass);
   _pClasses->Set(pName, pClass);
   return ESuccess;
}

//============================================================
// <T>ע��һ�������</T>
//
// @param pName ����
// @return ������
//============================================================
TResult FClassFactory::Unregister(TCharC* pName){
   MO_ASSERT(pName);
   _pClasses->Remove(pName);
   return ESuccess;
}

//============================================================
// <T>�ж��Ƿ���ָ�����ơ�</T>
//
// @param pName ����
// @return �Ƿ���
//============================================================
TBool FClassFactory::Contains(TCharC* pName){
   MO_ASSERT(pName);
   return _pClasses->Contains(pName);
}

//============================================================
// <T>����һ��ʵ����</T>
//
// @param pName ����
// @return ʵ��
//============================================================
FInstance* FClassFactory::Create(TCharC* pName){
   MO_ASSERT(pName);
   FInstance* pInstance = NULL;
   FClass* pClass = _pClasses->Find(pName);
   if(pClass != NULL){
      pInstance = pClass->InstanceCreate();
   }
   return pInstance;
}

//============================================================
// <T>�ռ�һ��ʵ����</T>
//
// @param pName ����
// @return ʵ��
//============================================================
FInstance* FClassFactory::Alloc(TCharC* pName){
   MO_ASSERT(pName);
   FInstance* pInstance = NULL;
   FClass* pClass = _pClasses->Find(pName);
   if(pClass != NULL){
      pInstance = pClass->InstanceAlloc();
   }
   return pInstance;
}

//============================================================
// <T>�ͷ�һ��ʵ����</T>
//
// @param pClassName ������
// @return ʵ��
//============================================================
void FClassFactory::Free(FInstance* pInstance){
   MO_ASSERT(pInstance);
   pInstance->Class()->InstanceFree(pInstance);
}

//============================================================
// <T>ɾ��һ��ʵ����</T>
//
// @param pClassName ������
// @return ʵ��
//============================================================
void FClassFactory::Delete(FInstance* pInstance){
   MO_ASSERT(pInstance);
   pInstance->Class()->InstanceDelete(pInstance);
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param pDump ��������
// @param capacity ����
// @return ������Ϣ
//============================================================
TCharC* FClassFactory::Dump(TChar* pDump, TInt capacity){
   MO_ASSERT(pDump);
   MO_ASSERT(capacity > 0);
   TStringRefer dump(pDump, capacity);
   dump.AppendFormat(TC("count=%d"), _pClasses->Count());
   return pDump;
}

MO_NAMESPACE_END
