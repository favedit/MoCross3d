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
TBool RChar32::IsAlphaNumber(TChar32 value){
#ifdef _MO_WINDOWS
   return iswalnum(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�ΪӢ����ĸ�����֡�</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsAlpha(TChar32 value){
#ifdef _MO_WINDOWS
   return iswalpha(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsControl(TChar32 value){
#ifdef _MO_WINDOWS
   return iswcntrl(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsDigit(TChar32 value){
#ifdef _MO_WINDOWS
   return iswdigit(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ32�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsDigitX(TChar32 value){
#ifdef _MO_WINDOWS
   return iswxdigit(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�ΪСд�ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsLower(TChar32 value){
#ifdef _MO_WINDOWS
   return iswlower(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ��д�ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsUpper(TChar32 value){
#ifdef _MO_WINDOWS
   return iswupper(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�ɻ����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsGraphics(TChar32 value){
#ifdef _MO_WINDOWS
   return iswgraph(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�ɴ�ӡ�ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsPrint(TChar32 value){
#ifdef _MO_WINDOWS
   return iswprint(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�����š�</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsPunct(TChar32 value){
#ifdef _MO_WINDOWS
   return iswpunct(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�ж�һ���ַ��Ƿ�Ϊ�ո��ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar32::IsSpace(TChar32 value){
#ifdef _MO_WINDOWS
   return iswspace(value);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return EFalse;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return EFalse;
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>�Ƚ���Դ�ַ�����Ŀ���ַ�����С��</T>
//
// @param pSource ��Դ�ַ���ָ��
// @param pTarget Ŀ���ַ���ָ��
// @return �ַ�����С
//============================================================
TInt RChar32::CompareIgnoreCase(TChar32C* pSource, TChar32C* pTarget){
#ifdef _MO_WINDOWS
   return _wcsicmp(pSource, pTarget);
#else
   return wcscmp(pSource, pTarget);
#endif
}

//============================================================
// <T>���ڲ��ַ���ת��ΪСд��</T>
//
// @param pSource �ַ���ָ��
// @param length �ַ�������
//============================================================
void RChar32::ToLower(TChar32* pValues, TInt length){
#ifdef _MO_WINDOWS
   while(--length >= 0){
      pValues[length] = towlower(pValues[length]);
   }
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
#endif // _MO_LINUX
}

//============================================================
// <T>���ڲ��ַ���ת��Ϊ��д��</T>
//
// @param pSource �ַ���ָ��
// @param length �ַ�������
//============================================================
void RChar32::ToUpper(TChar32* pValues, TInt length){
#ifdef _MO_WINDOWS
   while(--length >= 0){
      pValues[length] = towupper(pValues[length]);
   }
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
#endif // _MO_LINUX
}

//============================================================
// <T>���㽫32λ�ַ���ת��Ϊ8λ�ַ�������Ҫ�ĳ��ȡ�</T>
//
// @param pValue 32λ�ַ���
// @return ����Ҫ����
//============================================================
TInt RChar32::ConvertTo8(TChar32C* pValue){
   MO_ASSERT(pValue);
   TSize length = wcslen(pValue) + 1;
   return length;
}

//============================================================
// <T>��32λ�ַ���ת��Ϊ8λ�ַ�����</T>
//
// @param pOutput ����ַ���
// @param size ����ַ�������
// @param pValue �����ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RChar32::ConvertTo8(TChar8* pOutput, TSize size, TChar32C* pValue){
   TInt result = 0;
#ifdef _MO_LINUX
   // ��ת����
   iconv_t cd = iconv_open("ASCII", "WCHAR_T");
   if(iconv_t(-1) == cd){
      MO_STATIC_ERROR("iconv_open fail!");
   }
   // ת���ַ���
   TChar8* pInput = (TChar8*)&pValue;
   TSize convertCount = 0;
   TSize length = wcslen(pValue);
   result = iconv(cd, &pInput, &length, &pOutput, &convertCount);
   if(-1 == result){
      MO_STATIC_ERROR("iconv error!");
   }
   pOutput[convertCount] = 0;
   // �ر�ת����
   iconv_close(cd);
#endif
   return result;
}

//============================================================
// <T>���㽫32λ�ַ���ת��Ϊ16λ�ַ�������Ҫ�ĳ��ȡ�</T>
//
// @param pValue 32λ�ַ���
// @return ����Ҫ����
//============================================================
TInt RChar32::ConvertTo16(TChar32C* pValue){
   return 0;
}

//============================================================
// <T>��32λ�ַ���ת��Ϊ16λ�ַ�����</T>
//
// @param pOutput ����ַ���
// @param size ����ַ�������
// @param pValue �����ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RChar32::ConvertTo16(TChar16* pOutput, TSize size, TChar32C* pValue){
   return 0;
}

MO_NAMESPACE_END
