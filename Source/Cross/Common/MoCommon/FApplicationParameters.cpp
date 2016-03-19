#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ӧ�ó���������ϡ�</T>
//============================================================
FApplicationParameters::FApplicationParameters(){
   _pParameters = MO_CREATE(FApplicationParameterCollection);
}

//============================================================
// <T>����Ӧ�ó���������ϡ�</T>
//============================================================
FApplicationParameters::~FApplicationParameters(){
   MO_DELETE(_pParameters);
}

//============================================================
// <T>���������С�</T>
//
// @param pCommandLine ������
// @return ������
//============================================================
TResult FApplicationParameters::Setup(TCharC* pCommandLine){
   // ������

   if(pCommandLine == NULL){
      return ENull;
   }
   // ���ɲ�������
   TInt position = 0;
   TInt length = RString::Length(pCommandLine);
   while(position < length){
      TCharC* pReader = pCommandLine + position;
      TInt find = RChars::IndexOf(pReader, length - position, TC(' '));
      // ��������
      FApplicationParameter* pParameter = MO_CREATE(FApplicationParameter);
      pParameter->Parse(pReader, find);
      _pParameters->Push(pParameter);
      // ����λ��
      if(find != ENotFound){
         position += find + 1;
      }else{
         break;
      }
   }
   return ESuccess;
}

//============================================================
// <T>���ò������ϡ�</T>
//
// @param ppArguments ��������
// @param count ��������
// @return ������
//============================================================
TResult FApplicationParameters::Setup(TCharC** ppArguments, TInt count){
   // ������
   if(ppArguments == NULL){
      return ENull;
   }
   if(count <= 0){
      return EFailure;
   }
   // ���ɲ�������
   for(TInt n = 0; n < count; n++){
      FApplicationParameter* pParameter = MO_CREATE(FApplicationParameter);
      TCharC* pSource = ppArguments[n];
      pParameter->Parse(pSource);
      _pParameters->Push(pParameter);
   }
   return ESuccess;
}

//============================================================
// <T>��ò���������</T>
//
// @return ��������
//============================================================
TInt FApplicationParameters::Count(){
   return _pParameters->Count();
}

//============================================================
// <T>����������ò�����</T>
//
// @param index ����
// @return ����
//============================================================
FApplicationParameter* FApplicationParameters::GetParameter(TInt index){
   return _pParameters->Get(index);
}

//============================================================
// <T>�������Ʋ��Ҳ�����</T>
//
// @param pName ����
// @return ����
//============================================================
FApplicationParameter* FApplicationParameters::FindParameter(TCharC* pName){
   TInt count = _pParameters->Count();
   for(TInt n = 0; n < count; n++){
      FApplicationParameter* pParameter = _pParameters->Get(n);
      if(pParameter->IsName(pName)){
         return pParameter;
      }
   }
   return NULL;
}

//============================================================
// <T>�ж��Ƿ���ָ�����ݡ�</T>
//
// @param pValue ����
// @return ����
//============================================================
TBool FApplicationParameters::ConstainsValue(TCharC* pValue){
   TInt count = _pParameters->Count();
   for(TInt n = 0; n < count; n++){
      FApplicationParameter* pParameter = _pParameters->Get(n);
      if(pParameter->IsValue(pValue)){
         return ETrue;
      }
   }
   return EFalse;
}

//============================================================
// <T>����������ò������ݡ�</T>
//
// @param index ����
// @return ��������
//============================================================
TCharC* FApplicationParameters::GetValue(TInt index){
   FApplicationParameter* pParameter = GetParameter(index);
   MO_ASSERT(pParameter);
   TCharC* pValue = pParameter->Value();
   return pValue;
}

//============================================================
// <T>�������Ʋ��Ҳ������ݡ�</T>
//
// @param pName ����
// @return ��������
//============================================================
TCharC* FApplicationParameters::FindValue(TCharC* pName){
   TCharC* pValue = NULL;
   FApplicationParameter* pParameter = FindParameter(pName);
   if(pParameter != NULL){
      pValue = pParameter->Value();
   }
   return pValue;
}

MO_NAMESPACE_END
