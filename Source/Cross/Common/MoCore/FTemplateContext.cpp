#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateContext, FInstance);

//============================================================
// <T>����ģ�廷����</T>
//============================================================
FTemplateContext::FTemplateContext(){
   _config = FXmlNode::InstanceCreate();
   _mergeConfig = FXmlNode::InstanceCreate();
   _pSource = MO_CREATE(FStringBuffer);
   _trimOnceFlag = EFalse;
   _trimBeginLine = ETrue;
   _trimEmptyLine = EFalse;
   _trimEndLine = EFalse;
   _trimCommentLine = EFalse;
}

//============================================================
// <T>����ģ�廷����</T>
//============================================================
FTemplateContext::~FTemplateContext(){
   MO_DELETE(_pSource);
}

//============================================================
// <T>���ÿհױ�־һ�Ρ�</T>
//============================================================
void FTemplateContext::SetTrimOnceFlag(){
   _trimOnceFlag = ETrue;
}

//============================================================
// <T>�հ����һ�С�</T>
//============================================================
void FTemplateContext::TrimLastLine(){
   TInt length = _pSource->Length();
   if(length == 0){
      return;
   }
   TCharC* pSource = _pSource->MemoryC();
   if((length > 1) && (pSource[length - 2] == '\r') && (pSource[length - 1] == '\n')){
      _pSource->SetLength(length - 2);
   }else if((pSource[length - 1] == '\r') || (pSource[length - 1] == '\n')){
      _pSource->SetLength(length - 1);
   }
}

//============================================================
// <T>�������ƻ�ö���Ĳ���ֵ��</T>
//
// @param pName ����
// @param defaultValue Ĭ������
// @return ����ֵ
//============================================================
TBool FTemplateContext::GetDefineAsBool(TCharC* pName, TBool defaultValue){
   TBool value = _config->GetAsBool(pName, defaultValue);
   return value;
}

//============================================================
// <T>�������ƻ�ö����������</T>
//
// @param pName ����
// @param defaultValue Ĭ������
// @return ����
//============================================================
TInt FTemplateContext::GetDefineAsInt(TCharC* pName, TInt defaultValue){
   TInt value = _config->GetAsInt(pName, defaultValue);
   return value;
}

//============================================================
// <T>�������ƻ�ö�����ַ�����</T>
//
// @param pName ����
// @param defaultValue Ĭ������
// @return �ַ���
//============================================================
TCharC* FTemplateContext::GetDefineAsString(TCharC* pName, TCharC* pDefaultValue){
   TCharC* pValue = _config->Get(pName, pDefaultValue);
   return pValue;
}

//============================================================
// <T>����һ������ֵ��</T>
//
// @param pName ����
// @param value ����
//============================================================
void FTemplateContext::DefineBool(TCharC* pName, TBool value){
   MO_INFO(TC("Template define bool value. (name=%s, value=%d)"), pName, value);
   _config->SetBool(pName, value);
}

//============================================================
// <T>����һ��������</T>
//
// @param pName ����
// @param value ����
//============================================================
void FTemplateContext::DefineInt(TCharC* pName, TInt value){
   MO_INFO(TC("Template define int value. (name=%s, value=%d)"), pName, value);
   _config->SetInt(pName, value);
}

//============================================================
// <T>����һ���ַ�����</T>
//
// @param pName ����
// @param pValue �ַ���
//============================================================
void FTemplateContext::DefineString(TCharC* pName, TCharC* pValue){
   MO_INFO(TC("Template define string value. (name=%s, value=%s)"), pName, pValue);
   _config->Set(pName, pValue);
}

//============================================================
// <T>��ô����ڴ档</T>
//
// @return �����ڴ�
//============================================================
TCharC* FTemplateContext::SourceMemory(){
   return _pSource->MemoryC();
}

//============================================================
// <T>�������á�</T>
//============================================================
void FTemplateContext::SourceReset(){
   _pSource->Clear();
}

//============================================================
// <T>д��������ݡ�</T>
//============================================================
void FTemplateContext::SourceWrite(TCharC* pSource){
   // ������
   if(pSource == NULL){
      return;
   }
   TInt length = RString::Length(pSource);
   if(length == 0){
      return;
   }
   // �������
   TCharC* pWrite = pSource;
   if(_trimOnceFlag){
      // ɾ��ǰ�ո�
      if((length > 1) && (pWrite[0] == '\r') && (pWrite[1] == '\n')){
         pWrite += 2;
      }else if((pWrite[0] == '\r') || (pWrite[0] == '\n')){
         pWrite++;
      }
      _trimOnceFlag = EFalse;
   }
   _pSource->Append(pWrite);
}

//============================================================
// <T>�����ʽ����</T>
//============================================================
void FTemplateContext::SourceFormat(){
   TChar* pMemory = _pSource->Memory();
   TInt length = _pSource->Length();
   TInt position = 0;
   TBool start = !_trimBeginLine;
   TBool line = ETrue;
   // ɨ���ַ���
   for(TInt n = 0; n < length; n++){
      TChar value = pMemory[n];
      // ɨ�軻�з�
      if(value == '\r'){
         continue;
      }
      if(_trimEmptyLine && (value == '\n')){
         if(!start){
            continue;
         }
         if(line){
            line = EFalse;
         }else{
            continue;
         }
      }else{
         start = ETrue;
         line = ETrue;
      }
      // ɨ��ע����(���ں���//��ɾ����ǰ��)
      //if(_trimCommentLine && (value == '\n')){
      //   TCharC* pFind = pMemory + n + 1;
      //   TInt find = RChars::IndexOf(pFind, length - n - 1, '\n');
      //   if(find != -1){
      //      TInt findComment = RChars::Find(pFind, find, "//", 2);
      //      if(findComment != -1){
      //         n += find;
      //      }
      //   }
      //}
      // ׷������
      pMemory[position++] = value;
   }
   // ��ȡβ����
   if(_trimEndLine && (pMemory[position - 1] == '\n')){
      position--;
   }
   _pSource->SetLength(position);
}

MO_NAMESPACE_END
