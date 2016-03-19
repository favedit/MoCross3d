#include "MoCmClassBase.h"
#include "MoCmClass.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT(FInstance);

//============================================================
// <T>����ʵ������</T>
//============================================================
FInstance::FInstance(){
   _referCount = 0;
}

//============================================================
// <T>����ʵ������</T>
//============================================================
FInstance::~FInstance(){
}

//============================================================
// <T>�жϵ�ǰʵ���Ƿ���ָ�������ơ�</T>
//
// @param pClassName ������
// @return �Ƿ�Ϊ��
//============================================================
TBool FInstance::IsInstanceOf(TCharC* pClassName){
   FClass* pFindClass = RClassManager::Instance().FindClass(pClassName);
   return (_pClass == pFindClass);
}

//============================================================
// <T>�жϵ�ǰʵ���Ƿ���ָ�������</T>
//
// @param pClass �����
// @return �Ƿ�Ϊ��
//============================================================
TBool FInstance::IsInstanceOf(FClass* pClass){
   FClass* pInstanceClass = GetClass();
   return RClassManager::TestInherit(pInstanceClass, pClass);
}

//============================================================
// <T>�жϵ�ǰʵ���Ƿ�̳�ָ�������ơ�</T>
//
// @param pClassName ������
// @return �Ƿ�Ϊ��
//============================================================
TBool FInstance::IsInheritsFrom(TCharC* pClassName){
   return _pClass->IsInheritsFrom(pClassName);
}

//============================================================
// <T>�жϵ�ǰʵ���Ƿ�̳�ָ�������</T>
//
// @param pClass �����
// @return �Ƿ�Ϊ��
//============================================================
TBool FInstance::IsInheritsFrom(FClass* pClass){
   return _pClass->IsInheritsFrom(pClass);
}

//============================================================
// <T>ת�����͡�</T>
//
// @param pClass �����
// @return ת����ָ��
//============================================================
FInstance* FInstance::Convert(FClass* pClass){
#ifdef _MO_DEBUG
   RClassManager::CheckConvert(_pClass, pClass);
#endif // _MO_DEBUG
   return this;
}

MO_NAMESPACE_END
