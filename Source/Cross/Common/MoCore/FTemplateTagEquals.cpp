#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateTagEquals, FTemplateTag);

//============================================================
// <T>����ģ������߼���ǩ��</T>
//============================================================
FTemplateTagEquals::FTemplateTagEquals(){
}

//============================================================
// <T>����ģ������߼���ǩ��</T>
//============================================================
FTemplateTagEquals::~FTemplateTagEquals(){
}

//============================================================
// <T>��ʼ��ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagEquals::OnBegin(FTemplateContext* pContext){
   return ETemplateTagResult_None;
}

//============================================================
// <T>������ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagEquals::OnEnd(FTemplateContext* pContext){
   return ETemplateTagResult_None;
}

//============================================================
// <T>����һ�����ԡ�</T>
//
// @param pName ��������
// @param pValue ��������
// @return ������
//============================================================
TResult FTemplateTagEquals::SetAttribute(TCharC* pName, TCharC* pValue){
   if(RString::Equals(pName, TC("source"))){
      _source = pValue;
   }
   return ESuccess;
}

MO_NAMESPACE_END
