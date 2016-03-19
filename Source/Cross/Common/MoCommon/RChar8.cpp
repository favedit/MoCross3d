#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж�һ���ַ��Ƿ�ΪӢ����ĸ�����֡�</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsAlphaNumber(TChar8 value){
   return isalnum(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�ΪӢ����ĸ�����֡�</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsAlpha(TChar8 value){
   return isalpha(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsControl(TChar8 value){
   return iscntrl(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsDigit(TChar8 value){
   return isdigit(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ16�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsDigitX(TChar8 value){
   return isxdigit(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�ΪСд�ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsLower(TChar8 value){
   return islower(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ��д�ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsUpper(TChar8 value){
   return isupper(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�ɻ����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsGraphics(TChar8 value){
   return isgraph(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�ɴ�ӡ�ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsPrint(TChar8 value){
   return isprint(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�����š�</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsPunct(TChar8 value){
   return ispunct(value);
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�ո��ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar8::IsSpace(TChar8 value){
   return isspace(value);
}

//============================================================
// <T>�Ƚ���Դ�ַ�����Ŀ���ַ�����С��</T>
//
// @param pSource ��Դ�ַ���ָ��
// @param pTarget Ŀ���ַ���ָ��
// @return �ַ�����С
//============================================================
TInt RChar8::CompareIgnoreCase(TChar8C* pSource, TChar8C* pTarget){
#ifdef _MO_WINDOWS
   return _stricmp(pSource, pTarget);
#else
   return strcasecmp(pSource, pTarget);
#endif
}

//============================================================
// <T>���ڲ��ַ���ת��ΪСд��</T>
//
// @param pSource �ַ���ָ��
// @param length �ַ�������
//============================================================
void RChar8::ToLower(TChar8* pValues, TInt length){
   while(--length >= 0){
      pValues[length] = tolower(pValues[length]);
   }
}

//============================================================
// <T>���ڲ��ַ���ת��Ϊ��д��</T>
//
// @param pSource �ַ���ָ��
// @param length �ַ�������
//============================================================
void RChar8::ToUpper(TChar8* pValues, TInt length){
   while(--length >= 0){
      pValues[length] = toupper(pValues[length]);
   }
}

//============================================================
// <T>���㽫8λ�ַ���ת��Ϊ16λ�ַ�������Ҫ�ĳ��ȡ�</T>
//
// @param pValue 8λ�ַ���
// @return ����Ҫ����
//============================================================
TInt RChar8::ConvertTo16(TChar8C* pValue){
   MO_ASSERT(pValue);
   TInt length = 0;
#ifdef _MO_WINDOWS
   length = MultiByteToWideChar(CP_ACP, 0, pValue, -1, NULL, 0);
#endif
   return length;
}

//============================================================
// <T>��8λ�ַ���ת��Ϊ16λ�ַ�����</T>
//
// @param pOutput ����ַ���
// @param size ����ַ�������
// @param pValue �����ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RChar8::ConvertTo16(TChar16* pOutput, TSize size, TChar8C* pValue){
   MO_ASSERT(pOutput);
   MO_ASSERT(pValue);
   TInt length = 0;
#ifdef _MO_WINDOWS
   length = MultiByteToWideChar(CP_ACP, 0, pValue, -1, pOutput, size);
#endif
   return length;
}

//============================================================
// <T>���㽫8λ�ַ���ת��Ϊ32λ�ַ�������Ҫ�ĳ��ȡ�</T>
//
// @param pValue 8λ�ַ���
// @return ����Ҫ����
//============================================================
TInt RChar8::ConvertTo32(TChar8C* pValue){
   MO_ASSERT(pValue);
   TSize result = 0;
#ifdef _MO_LINUX
   result = strlen(pValue) + 1;
#endif // _MO_LINUX
   return result;
}

//============================================================
// <T>��8λ�ַ���ת��Ϊ32λ�ַ�����</T>
//
// @param pOutput ����ַ���
// @param size ����ַ�������
// @param pValue �����ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RChar8::ConvertTo32(TChar32* pOutput, TSize size, TChar8C* pValue){
   TUint result = 0;
#ifdef _MO_LINUX
//   TUint inLength = strlen(pValue);
//   result = inLength + 1;
//   TUint tempLength = inLength * 4; // iconv���һ��������ʾpOut���ֽ���������Ҫ����4
//   MO_ASSERT(size >= outLength);
//   TChar8* pIn = (TChar8*)&pValue;
//   TChar32* pOut = pOutput;
//   iconv_t cd = iconv_open("WCHAR_T", "ASSII");
//   if(iconv_t(-1) == cd){
//      MO_STATIC_ERROR("iconv_open fail!");
//   }
//   result = iconv(cd, &pIn, &inLength, (TChar8**)&pOut, &tempLength);
//   if(-1 == result){
//      MO_STATIC_ERROR("iconv error!");
//      return -1;
//   }
//   pOutput[outLength] = 0;
//   iconv_close(cd);
#endif // _MO_LINUX
   return result;
}

//============================================================
// <T>���㽫UTF8λ�ַ���ת��Ϊ16λ�ַ�������Ҫ�ĳ��ȡ�</T>
//
// @param pValue 8λ�ַ���
// @return ����Ҫ����
//============================================================
TInt RChar8::ConvertToUtf8(TChar8C* pValue){
   MO_ASSERT(pValue);
   TInt length = 0;
#ifdef _MO_WINDOWS
   length = MultiByteToWideChar(CP_UTF8, 0, pValue, -1, NULL, 0);
#endif
   return length;
}

//============================================================
// <T>��UTF8λ�ַ���ת��Ϊ16λ�ַ�����</T>
//
// @param pOutput ����ַ���
// @param size ����ַ�������
// @param pValue �����ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RChar8::ConvertToUtf8(TChar16* pOutput, TSize size, TChar8C* pValue){
   MO_ASSERT(pOutput);
   MO_ASSERT(pValue);
   TInt length = 0;
#ifdef _MO_WINDOWS
   length = MultiByteToWideChar(CP_UTF8, 0, pValue, -1, pOutput, size);
#endif
   return length;
}

MO_NAMESPACE_END
