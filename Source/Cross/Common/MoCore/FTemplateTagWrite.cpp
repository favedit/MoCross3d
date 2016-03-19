#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateTagWrite, FTemplateTag);

//============================================================
// <T>����ģ������߼���ǩ��</T>
//============================================================
FTemplateTagWrite::FTemplateTagWrite(){
}

//============================================================
// <T>����ģ������߼���ǩ��</T>
//============================================================
FTemplateTagWrite::~FTemplateTagWrite(){
}

//============================================================
// <T>��ʼ��ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagWrite::OnBegin(FTemplateContext* pContext){
   MO_CHECK(pContext, return ETemplateTagResult_Failure);
   TCharC* pValue = pContext->Config()->Get(_source, NULL);
   if(pValue != NULL){
      pContext->SourceWrite(pValue);
   }
   return ETemplateTagResult_Continue;
}

//============================================================
// <T>����һ�����ԡ�</T>
//
// @param pName ��������
// @param pValue ��������
// @return ������
//============================================================
TResult FTemplateTagWrite::SetAttribute(TCharC* pName, TCharC* pValue){
   if(RString::Equals(pName, TC("source"))){
      _source = pValue;
   }
   return ESuccess;
}

MO_NAMESPACE_END
