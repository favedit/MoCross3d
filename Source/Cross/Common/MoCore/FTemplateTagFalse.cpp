#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateTagFalse, FTemplateTag);

//============================================================
// <T>����ģ����߼���ǩ��</T>
//============================================================
FTemplateTagFalse::FTemplateTagFalse(){
}

//============================================================
// <T>����ģ����߼���ǩ��</T>
//============================================================
FTemplateTagFalse::~FTemplateTagFalse(){
}

//============================================================
// <T>��ʼ��ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagFalse::OnBegin(FTemplateContext* pContext){
   TBool flag = pContext->Config()->GetAsBool(_source);
   if(!flag){
      return ETemplateTagResult_Include;
   }
   return ETemplateTagResult_Continue;
}

//============================================================
// <T>������ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagFalse::OnEnd(FTemplateContext* pContext){
   return ETemplateTagResult_None;
}

//============================================================
// <T>����һ�����ԡ�</T>
//
// @param pName ��������
// @param pValue ��������
// @return ������
//============================================================
TResult FTemplateTagFalse::SetAttribute(TCharC* pName, TCharC* pValue){
   if(RString::Equals(pName, TC("source"))){
      _source = pValue;
   }
   return ESuccess;
}

MO_NAMESPACE_END
