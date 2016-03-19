#include "MoCmClassBase.h"
#include "MoCmClass.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������</T>
//============================================================
FClass::FClass(){
   _looperLimit = 64;
   MO_CLEAR(_pName);
   MO_CLEAR(_pParentClassName);
   MO_CLEAR(_pParentClass);
   _memorySize = 0;
   _activeCount = 0;
   _allocTotal = 0;
}

//============================================================
// <T>���������</T>
//============================================================
FClass::~FClass(){
}

//============================================================
// <T>��ø������</T>
//
// @return �����
//============================================================
FClass* FClass::ParentClass(){
   if(_pParentClass == NULL){
      if(_pParentClassName != NULL){
         _pParentClass = RClassManager::Instance().FindClass(_pParentClassName);
      }
   }
   return _pParentClass;
}

//============================================================
// <T>�жϵ�ǰʵ���Ƿ�̳�ָ�������ơ�</T>
//
// @param pClassName ������
// @return �Ƿ�Ϊ��
//============================================================
TBool FClass::IsInheritsFrom(TCharC* pClassName){
   FClass* pFindClass = RClassManager::Instance().FindClass(pClassName);
   return IsInheritsFrom(pFindClass);
}

//============================================================
// <T>�жϵ�ǰʵ���Ƿ�̳�ָ�������</T>
//
// @param pClass �����
// @return �Ƿ�Ϊ��
//============================================================
TBool FClass::IsInheritsFrom(FClass* pClass){
   MO_ASSERT(pClass);
   FClass* pFindClass = this;
   while(pFindClass != NULL){
      if(pFindClass == pClass){
         return ETrue;
      }
      pFindClass = pFindClass->ParentClass();
   }
   return EFalse;
}

//============================================================
// <T>����һ��ʵ�������ұ�֤ʵ���Ǵ�ָ���������̳С�</T>
//
// @param pClass �������
// @return ʵ��
//============================================================
FInstance* FClass::InstanceInheritCreate(FClass* pClass){
   FInstance* pInstance = InstanceCreate();
   RClassManager::CheckInherit(pInstance, pClass);
   return pInstance;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FClass::Process(){
   _looper.Record();
   for(TInt n = 0; n < _looperLimit; n++){
      FInstance* pInstance = _looper.Next();
      if(pInstance == NULL){
         break;
      }
      // �ͷ�ΨһӦ�ö���
      if(pInstance->ReferCount() == 1){
         _looper.RemoveCurrent();
         pInstance->ReferDecrease();
      }
   }
   return ESuccess;
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param pDump ��������
// @param capacity ����
// @return ������Ϣ
//============================================================
TCharC* FClass::Dump(TChar* pDump, TInt capacity){
   TStringRefer dump(pDump, capacity);
   dump.AppendFormat(TC("name=%s"), _pName);
   // ������Ϣ
   if(_pParentClass != NULL){
      dump.Append(TC(" parent=("));
      FClass* pParentClass = _pParentClass;
      while(pParentClass != NULL){
         dump.Append(pParentClass->Name());
         pParentClass = pParentClass->ParentClass();
         if(pParentClass != NULL){
            dump.Append(TC("->"));
         }
      }
      dump.Append(TC(")"));
   }
   dump.AppendFormat(TC(" size=%d, count=%lld/%lld"), _memorySize, _activeCount, _allocTotal);
   return pDump;
}

MO_NAMESPACE_END
