#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateBuilder, FConfigBuilder);

//============================================================
// <T>�������ù�������</T>
//============================================================
FTemplateBuilder::FTemplateBuilder(){
   MO_CLEAR(_pConsole);
   MO_CLEAR(_pContext);
   MO_CLEAR(_pTemplate);
}

//============================================================
// <T>�������ù�������</T>
//============================================================
FTemplateBuilder::~FTemplateBuilder(){
}

//============================================================
// <T>�������ơ�</T>
//
// @param pInstance ʵ��
// @param pName ����
// @return ������
//============================================================
TResult FTemplateBuilder::SetName(FInstance* pInstance, TCharC* pName){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pName, return ENull);
   FTemplateTag* pTag = pInstance->Convert<FTemplateTag>();
   pTag->SetName(pName);
   return ESuccess;
}

//============================================================
// <T>�������ݡ�</T>
//
// @param pInstance ʵ��
// @param pText ����
// @return ������
//============================================================
TResult FTemplateBuilder::SetText(FInstance* pInstance, TCharC* pText){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pText, return ENull);
   FTemplateTagText* pTag = pInstance->Convert<FTemplateTagText>();
   pTag->SetText(pText);
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
TResult FTemplateBuilder::Set(FInstance* pInstance, TCharC* pName, TCharC* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pName, return ENull);
   FTemplateTag* pTag = pInstance->Convert<FTemplateTag>();
   pTag->SetAttribute(pName, pValue);
   return ESuccess;
}

//============================================================
// <T>����һ�������ýڵ㡣</T>
//
// @param pInstance ʵ��
// @param pChildInstance ��ʵ��
// @return ������
//============================================================
TResult FTemplateBuilder::Push(FInstance* pInstance, FInstance* pChildInstance){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pChildInstance, return ENull);
   FTemplateTag* pTag = pInstance->Convert<FTemplateTag>();
   FTemplateTag* pChildTag = pChildInstance->Convert<FTemplateTag>();
   pTag->Push(pChildTag);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @param pInstance ʵ��
// @return ������
//============================================================
TResult FTemplateBuilder::Setup(FInstance* pInstance){
   MO_CHECK(pInstance, return ENull);
   FTemplateTag* pTag = pInstance->Convert<FTemplateTag>();
   pTag->Setup(this);
   return ESuccess;
}

MO_NAMESPACE_END
