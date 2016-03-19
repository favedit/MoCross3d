#include "MoCmXml.h"
#include "MoCmFormat.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FXmlBuilder, FConfigBuilder);

//============================================================
// <T>�������ù�������</T>
//============================================================
FXmlBuilder::FXmlBuilder(){
}

//============================================================
// <T>�������ù�������</T>
//============================================================
FXmlBuilder::~FXmlBuilder(){
}

//============================================================
// <T>�������ơ�</T>
//
// @param pInstance ʵ��
// @param pName ����
// @return ������
//============================================================
TResult FXmlBuilder::SetName(FInstance* pInstance, TCharC* pName){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pName, return ENull);
   FXmlNode* pNode = pInstance->Convert<FXmlNode>();
   pNode->SetName(pName);
   return ESuccess;
}

//============================================================
// <T>�������ݡ�</T>
//
// @param pInstance ʵ��
// @param pText ����
// @return ������
//============================================================
TResult FXmlBuilder::SetText(FInstance* pInstance, TCharC* pText){
   MO_CHECK(pInstance, return ENull);
   if(pText != NULL){
      FXmlNode* pNode = pInstance->Convert<FXmlNode>();
      pNode->SetText(pText);
   }
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
TResult FXmlBuilder::Set(FInstance* pInstance, TCharC* pName, TCharC* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pName, return ENull);
   FXmlNode* pNode = pInstance->Convert<FXmlNode>();
   pNode->Set(pName, pValue);
   return ESuccess;
}

//============================================================
// <T>����һ�������ýڵ㡣</T>
//
// @param pInstance ʵ��
// @param pChildInstance ��ʵ��
// @return ������
//============================================================
TResult FXmlBuilder::Push(FInstance* pInstance, FInstance* pChildInstance){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pChildInstance, return ENull);
   FXmlNode* pNode = pInstance->Convert<FXmlNode>();
   FXmlNode* pChildNode = pChildInstance->Convert<FXmlNode>();
   pNode->Push(pChildNode);
   return ESuccess;
}

MO_NAMESPACE_END
