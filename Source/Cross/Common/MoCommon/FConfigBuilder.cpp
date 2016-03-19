#include "MoCmConfig.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FConfigBuilder, FInstance);

//============================================================
// <T>�������ù�������</T>
//============================================================
FConfigBuilder::FConfigBuilder(){
}

//============================================================
// <T>�������ù�������</T>
//============================================================
FConfigBuilder::~FConfigBuilder(){
}

//============================================================
// <T>�������ơ�</T>
//
// @param pInstance ʵ��
// @param pName ����
// @return ������
//============================================================
TResult FConfigBuilder::SetName(FInstance* pInstance, TCharC* pName){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>�������ݡ�</T>
//
// @param pInstance ʵ��
// @param pText ����
// @return ������
//============================================================
TResult FConfigBuilder::SetText(FInstance* pInstance, TCharC* pText){
   return ESuccess;
}

//============================================================
// <T>�����������ƺ����ݡ�</T>
//
// @param pInstance ʵ��
// @param pName ��������
// @param pValue ��������
// @return ������
//============================================================
TResult FConfigBuilder::Set(FInstance* pInstance, TCharC* pName, TCharC* pValue){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>����һ�������ýڵ㡣</T>
//
// @param pInstance ʵ��
// @param pChildInstance ��ʵ��
// @return ������
//============================================================
TResult FConfigBuilder::Push(FInstance* pInstance, FInstance* pChildInstance){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @param pInstance ʵ��
// @return ������
//============================================================
TResult FConfigBuilder::Setup(FInstance* pInstance){
   return ESuccess;
}

MO_NAMESPACE_END
