#include "MoCmClass.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ʋ���һ�������</T>
//
// @param pClassName ������
// @return �����
//============================================================
FClass* RClassManager::FindClass(TCharC* pClassName){
   FClassConsole* pClassConsole = SafeInstancePtr();
   return pClassConsole->FindClass(pClassName);
}

//============================================================
// <T>ע��һ�������</T>
//
// @param pClass �����
// @return �����
//============================================================
FClass* RClassManager::Register(FClass* pClass){
   FClassConsole* pClassConsole = SafeInstancePtr();
   return pClassConsole->Register(pClass);
}

//============================================================
// <T>����ʵ��������Ƿ���ָ�����������</T>
//
// @param pInstanceClass ʵ�������
// @param pClass �����
// @return �Ƿ�����
//============================================================
TBool RClassManager::TestInherit(FClass* pInstanceClass, FClass* pClass){
   FClass* pFindClass = pInstanceClass;
   while(pFindClass != NULL){
      if(pFindClass == pClass){
         return ETrue;
      }
      pFindClass = pFindClass->ParentClass();
   }
   return EFalse;
}

//============================================================
// <T>����ʵ��������Ƿ���ָ�����������</T>
//
// @param pInstanceClass ʵ�������
// @param pClass �����
// @return �Ƿ�����
//============================================================
TBool RClassManager::TestInherit(FInstance* pInstance, FClass* pClass){
   MO_ASSERT(pInstance);
   FClass* pInstanceClass = pInstance->GetClass();
   MO_ASSERT(pInstanceClass);
   return TestInherit(pInstanceClass, pClass);
}

//============================================================
// <T>���ָ�����Ƿ�Ӹ���̳С�</T>
//
// @param pInstanceClass ʵ�������
// @param pClass �����
// @return ������
//============================================================
TResult RClassManager::CheckInherit(FClass* pInstanceClass, FClass* pClass){
   MO_CHECK(pInstanceClass, return ENull);
   MO_CHECK(pClass, return ENull);
   // �������
   FClass* pFindClass = pInstanceClass;
   while(pFindClass != NULL){
      if(pFindClass == pClass){
         return ESuccess;
      }
      pFindClass = pFindClass->ParentClass();
   }
   // ����ʧ��
   MO_STATIC_FATAL(TC("Instance class is not inherit class. (instance_class=%s, class=%s)"),
      pInstanceClass->Name(), pClass->Name());
   return EFailure;
}

//============================================================
// <T>���ָ�����Ƿ�Ӹ���̳С�</T>
//
// @param pInstanceClass ʵ�������
// @param pClass �����
// @return ������
//============================================================
TResult RClassManager::CheckInherit(FInstance* pInstance, FClass* pClass){
   MO_ASSERT(pInstance);
   FClass* pInstanceClass = pInstance->GetClass();
   MO_ASSERT(pInstanceClass);
   return CheckInherit(pInstanceClass, pClass);
}

//============================================================
// <T>���ָ�����Ƿ����ת����</T>
// <P>����ת����ȫ��������ֻ�ܱ�֤�м̳й�ϵ��ת���п��ܲ���ȫ��</P>
//
// @param pInstanceClass ʵ�������
// @param pClass �����
// @return ������
//============================================================
TResult RClassManager::CheckConvert(FClass* pInstanceClass, FClass* pClass){
   MO_CHECK(pInstanceClass, return ENull);
   MO_CHECK(pClass, return ENull);
   // �������
   FClass* pFindClass = pInstanceClass;
   while(pFindClass != NULL){
      if(pFindClass == pClass){
         return ESuccess;
      }
      pFindClass = pFindClass->ParentClass();
   }
   // �������
   pFindClass = pClass;
   while(pFindClass != NULL){
      if(pFindClass == pInstanceClass){
         return ESuccess;
      }
      pFindClass = pFindClass->ParentClass();
   }
   // ����ʧ��
   MO_STATIC_FATAL(TC("Instance class can not convert target class. (instance_class=%s, class=%s)"),
      pInstanceClass->Name(), pClass->Name());
   return EFailure;
}

//============================================================
// <T>���ָ�����Ƿ����ת����</T>
//
// @param pInstanceClass ʵ�������
// @param pClass �����
// @return ������
//============================================================
TResult RClassManager::CheckConvert(FInstance* pInstance, FClass* pClass){
   MO_ASSERT(pInstance);
   FClass* pInstanceClass = pInstance->GetClass();
   MO_ASSERT(pInstanceClass);
   return CheckConvert(pInstanceClass, pClass);
}

MO_NAMESPACE_END
