#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateTagCounter, FTemplateTag);

//============================================================
// <T>����ģ���������ǩ��</T>
//============================================================
FTemplateTagCounter::FTemplateTagCounter(){
   _operator = TC("add");
   _value = TC("1");
}

//============================================================
// <T>����ģ���������ǩ��</T>
//============================================================
FTemplateTagCounter::~FTemplateTagCounter(){
}

//============================================================
// <T>��ʼ��ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagCounter::OnBegin(FTemplateContext* pContext){
   MO_CHECK(pContext, return ETemplateTagResult_Failure);
   TCharC* pSource = pContext->Config()->Get(_source, NULL);
   if(pSource != NULL){
      // ��������
      TInt source = RInt::Parse(pSource);
      TInt value = RInt::Parse(_value);
      if(RString::Equals((TCharC*)_operator, TC("add"))){
         source += value;
      }else if(RString::Equals((TCharC*)_operator, TC("sub"))){
         source -= value;
      }else if(RString::Equals((TCharC*)_operator, TC("mul"))){
         source *= value;
      }else if(RString::Equals((TCharC*)_operator, TC("div"))){
         source /= value;
      }else{
         MO_FATAL(TC("Unknown operator. (operator=%s)"), (TCharC*)_operator);
      }
      // д������
      TFsText sourceValue;
      sourceValue.AppendInt(source);
      pContext->SourceWrite(sourceValue);
      // ����ԭʼ����
      pContext->Config()->Set(_source, sourceValue);
      // ���¶�������
      if(!_define.IsEmpty()){
         pContext->Config()->Set(_define, sourceValue);
      }
   }
   return ETemplateTagResult_Continue;
}

//============================================================
// <T>������ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagCounter::OnEnd(FTemplateContext* pContext){
   return ETemplateTagResult_None;
}

//============================================================
// <T>����һ�����ԡ�</T>
//
// @param pName ��������
// @param pValue ��������
// @return ������
//============================================================
TResult FTemplateTagCounter::SetAttribute(TCharC* pName, TCharC* pValue){
   if(RString::Equals(pName, TC("source"))){
      _source = pValue;
   }else if(RString::Equals(pName, TC("operator"))){
      _operator = pValue;
   }else if(RString::Equals(pName, TC("value"))){
      _value = pValue;
   }else if(RString::Equals(pName, TC("define"))){
      _define = pValue;
   }
   return ESuccess;
}

MO_NAMESPACE_END
