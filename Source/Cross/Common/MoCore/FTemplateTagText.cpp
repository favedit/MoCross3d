#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateTagText, FTemplateTag);

//============================================================
// <T>����ģ���ı���ǩ��</T>
//============================================================
FTemplateTagText::FTemplateTagText(){
   _name = TC("text");
}

//============================================================
// <T>����ģ���ı���ǩ��</T>
//============================================================
FTemplateTagText::~FTemplateTagText(){
}

//============================================================
// <T>��ʼ��ǩ����</T>
//
// @param pContext ��ǩ����
// @return ������
//============================================================
ETemplateTagResult FTemplateTagText::OnBegin(FTemplateContext* pContext){
   pContext->SourceWrite(_text);
   return ETemplateTagResult_Continue;
}

MO_NAMESPACE_END
