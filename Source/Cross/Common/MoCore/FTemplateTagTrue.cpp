#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateTagTrue, FTemplateTag);

//============================================================
// <T>����ģ�����߼���ǩ��</T>
//============================================================
FTemplateTagTrue::FTemplateTagTrue(){
   _nowrapRight = ETrue;
}

//============================================================
// <T>����ģ�����߼���ǩ��</T>
//============================================================
FTemplateTagTrue::~FTemplateTagTrue(){
}

//============================================================
// <T>��ʼ��ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagTrue::OnBegin(FTemplateContext* pContext){
   TBool result = ETrue;
   TInt length = _source.Length();
   // ������
   TFsText value;
   TChar spliter = 0;
   TInt position = 0;
   while(position < length){
      TInt find = RChars::IndexsOf((TCharC*)_source + position, TC("|&"));
      if(find != ENotFound){
         spliter = _source.Get(position + find);
         value = _source.SubStrC(position, position + find);
         position += find + 1;
      }else{
         value = _source.SubStrC(position, length);
         position = length;
      }
      // ��������
      TBool flag = pContext->Config()->GetAsBool(value);
      if(spliter == '|'){
         if(flag){
            result = ETrue;
         }
      }else if(spliter == '&'){
         if(!result){
            break;
         }
         if(!flag){
            result = EFalse;
            break;
         }
      }else{
         result = flag;
      }
   }
   // ���ؽ��
   if(result){
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
ETemplateTagResult FTemplateTagTrue::OnEnd(FTemplateContext* pContext){
   return ETemplateTagResult_Stop;
}

//============================================================
// <T>����һ�����ԡ�</T>
//
// @param pName ��������
// @param pValue ��������
// @return ������
//============================================================
TResult FTemplateTagTrue::SetAttribute(TCharC* pName, TCharC* pValue){
   if(RString::Equals(pName, TC("source"))){
      _source = pValue;
   }
   return ESuccess;
}

MO_NAMESPACE_END
