#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ӧ�ó��������</T>
//============================================================
FApplicationParameter::FApplicationParameter(){
}

//============================================================
// <T>����Ӧ�ó��������</T>
//============================================================
FApplicationParameter::~FApplicationParameter(){
}

//============================================================
// <T>������Դ��</T>
//
// @param pSource ��Դ
// @param length ����
// @return ������
//============================================================
TResult FApplicationParameter::Parse(TCharC* pSource, TInt length){
   // ������
   MO_ASSERT(pSource);
   // ��ó���
   if(length == -1){
      length = RString::Length(pSource);
   }
   // �����з�
   TInt find = RChars::IndexOf(pSource, length, '=');
   if(find == ENotFound){
      _value = TStringPtrC(pSource, length);
   }else{
      _name = TStringPtrC(pSource, find);
      _value = TStringPtrC(pSource + find + 1, length - find - 1);
   }
   return ESuccess;
}

MO_NAMESPACE_END
