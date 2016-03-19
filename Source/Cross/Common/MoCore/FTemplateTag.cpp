#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateTag, FInstance);

//============================================================
// <T>����ģ���ǩ��</T>
//============================================================
FTemplateTag::FTemplateTag(){
   _nowrapLeft = EFalse;
   _nowrapRight = EFalse;
   MO_CLEAR(_pChildren);
}

//============================================================
// <T>����ģ���ǩ��</T>
//============================================================
FTemplateTag::~FTemplateTag(){
   if(_pChildren != NULL){
      TInt count = _pChildren->Count();
      for(TInt n = 0; n < count; n++){
         FTemplateTag* pTag = _pChildren->Get(n);
         MO_DELETE(pTag);
      }
      _pChildren->Clear();
   }
   MO_DELETE(_pChildren);
}

//============================================================
// <T>��ʼ��ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTag::OnBegin(FTemplateContext* pContext){
   return ETemplateTagResult_Include;
}

//============================================================
// <T>ѭ����ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTag::OnLoop(FTemplateContext* pContext){
   return ETemplateTagResult_Stop;
}
 
//============================================================
// <T>������ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTag::OnEnd(FTemplateContext* pContext){
   return ETemplateTagResult_Stop;
}

//============================================================
// <T>����һ�����ԡ�</T>
//
// @param pName ��������
// @param pValue ��������
// @return ������
//============================================================
TResult FTemplateTag::SetAttribute(TCharC* pName, TCharC* pValue){
   return ESuccess;
}

//============================================================
// <T>����һ���ӱ�ǩ��</T>
//
// @param pTag �ӱ�ǩ
// @return ������
//============================================================
TResult FTemplateTag::Push(FTemplateTag* pTag){
   if(_pChildren == NULL){
      _pChildren = MO_CREATE(FTemplateTagCollection);
   }
   _pChildren->Push(pTag);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @param pBuilder ������
// @return ������
//============================================================
TResult FTemplateTag::Setup(FTemplateBuilder* pBuilder){
   MO_CHECK(pBuilder, return ENull);
   return ESuccess;
}

MO_NAMESPACE_END
