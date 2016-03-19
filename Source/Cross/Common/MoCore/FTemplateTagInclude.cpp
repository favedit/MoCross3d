#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateTagInclude, FTemplateTag);

//============================================================
// <T>����ģ������߼���ǩ��</T>
//============================================================
FTemplateTagInclude::FTemplateTagInclude(){
   MO_CLEAR(_pTemplate);
   MO_CLEAR(_pSource);
   MO_CLEAR(_pIncludeTags);
}

//============================================================
// <T>����ģ������߼���ǩ��</T>
//============================================================
FTemplateTagInclude::~FTemplateTagInclude(){
   MO_DELETE(_pTemplate);
   MO_DELETE(_pSource);
   MO_DELETE(_pIncludeTags);
}

//============================================================
// <T>��ʼ��ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagInclude::OnBegin(FTemplateContext* pContext){
   _pTemplate->Parse(pContext, _segment);
   return ETemplateTagResult_None;
}

//============================================================
// <T>������ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagInclude::OnEnd(FTemplateContext* pContext){
   return ETemplateTagResult_None;
}

//============================================================
// <T>����һ�����ԡ�</T>
//
// @param pName ��������
// @param pValue ��������
// @return ������
//============================================================
TResult FTemplateTagInclude::SetAttribute(TCharC* pName, TCharC* pValue){
   if(RString::Equals(pName, TC("source"))){
      _source = pValue;
   }else if(RString::Equals(pName, TC("segment"))){
      _segment = pValue;
   }else{
      MO_FATAL(TC("Unknown attribute. (name=%s, value=%s)"), pName, pValue);
   }
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @param pBuilder ������
// @return ������
//============================================================
TResult FTemplateTagInclude::Setup(FTemplateBuilder* pBuilder){
   // ������
   MO_CHECK(pBuilder, return ENull);
   MO_CHECK(!_source.IsEmpty(), return EFailure);
   MO_CHECK(!_segment.IsEmpty(), return EFailure);
   // ��������
   TResult resultCd = FTemplateTag::Setup(pBuilder);
   FTemplateConsole* pConsole = pBuilder->Console();
   FTemplateContext* pContext = pBuilder->Context();
   FTemplate* pTemplate = pBuilder->Template();
   pTemplate->IncludeTags()->Push(this);
   // ������Դ
   MO_ASSERT(!_pTemplate);
   _pTemplate = pConsole->Load(pContext, _source);
   return resultCd;
}

MO_NAMESPACE_END
