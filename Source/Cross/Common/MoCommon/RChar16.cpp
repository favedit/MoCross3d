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
TBool RChar16::IsAlphaNumber(TChar16 value){
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
TBool RChar16::IsAlpha(TChar16 value){
#ifdef _MO_WINDOWS
   return iswalpha(value);
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
// <T>�ж�һ���ַ��Ƿ�Ϊ�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar16::IsControl(TChar16 value){
#ifdef _MO_WINDOWS
   return iswcntrl(value);
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
// <T>�ж�һ���ַ��Ƿ�Ϊ�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar16::IsDigit(TChar16 value){
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
// <T>�ж�һ���ַ��Ƿ�Ϊ16�����ַ���</T>
//
// @param value �ַ�
// @return
//    <L value='ETrue'>��</L>
//    <L value='EFalse'>��</L>
//============================================================
TBool RChar16::IsDigitX(TChar16 value){
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
TBool RChar16::IsLower(TChar16 value){
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
TBool RChar16::IsUpper(TChar16 value){
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
TBool RChar16::IsGraphics(TChar16 value){
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
TBool RChar16::IsPrint(TChar16 value){
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
TBool RChar16::IsPunct(TChar16 value){
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
TBool RChar16::IsSpace(TChar16 value){
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
TInt RChar16::CompareIgnoreCase(TChar16C* pSource, TChar16C* pTarget){
#ifdef _MO_WINDOWS
   return _wcsicmp(pSource, pTarget);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   return wcscmp(pSource, pTarget);
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   return wcscmp(pSource, pTarget);
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
   return EFalse;
#endif // _MO_FLASCC
}

//============================================================
// <T>���ڲ��ַ���ת��ΪСд��</T>
//
// @param pSource �ַ���ָ��
// @param length �ַ�������
//============================================================
void RChar16::ToLower(TChar16* pValues, TInt length){
#ifdef _MO_WINDOWS
   while(--length >= 0){
      pValues[length] = towlower(pValues[length]);
   }
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
#endif // _MO_LINUX
#ifdef _MO_ANDROID
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
#endif // _MO_FLASCC
}

//============================================================
// <T>���ڲ��ַ���ת��Ϊ��д��</T>
//
// @param pSource �ַ���ָ��
// @param length �ַ�������
//============================================================
void RChar16::ToUpper(TChar16* pValues, TInt length){
#ifdef _MO_WINDOWS
   while(--length >= 0){
      pValues[length] = towupper(pValues[length]);
   }
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
#endif // _MO_LINUX
#ifdef _MO_ANDROID
#endif // _MO_ANDROID
#ifdef _MO_FLASCC
#endif // _MO_FLASCC
}

//============================================================
// <T>���㽫16λ�ַ���ת��Ϊ8λ�ַ�������Ҫ�ĳ��ȡ�</T>
//
// @param pValue 16λ�ַ���
// @return ����Ҫ����
//============================================================
TInt RChar16::ConvertTo8(TChar16C* pValue){
   MO_ASSERT(pValue);
   TSize length = wcslen(pValue);
#ifdef _MO_WINDOWS
   TSize tempLen = length;
   WideCharToMultiByte(CP_ACP, 0, pValue, tempLen, NULL, 0, NULL, FALSE);
#else
   MO_STATIC_FATAL("Unimplemented.");
#endif // _MO_WINDOWS
   return length;
}

//============================================================
// <T>��16λ�ַ���ת��Ϊ8λ�ַ�����</T>
//
// @param pOutput ����ַ���
// @param size ����ַ�������
// @param pValue �����ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RChar16::ConvertTo8(TChar8* pOutput, TSize size, TChar16C* pValue){
   MO_ASSERT(pOutput);
   MO_ASSERT(pValue);
#ifdef _MO_WINDOWS
   TSize length = wcslen(pValue);
   return WideCharToMultiByte(CP_ACP, 0, pValue, length, pOutput, size, NULL, FALSE);
#else
   MO_STATIC_FATAL("Unimplemented.");
#endif // _MO_WINDOWS
   return 0;
}

//============================================================
// <T>���㽫16λ�ַ���ת��Ϊ32λ�ַ�������Ҫ�ĳ��ȡ�</T>
//
// @param pValue 16λ�ַ���
// @return ����Ҫ����
//============================================================
TInt RChar16::ConvertTo32(TChar16C* pValue){
   return 0;
}

//============================================================
// <T>��16λ�ַ���ת��Ϊ32λ�ַ�����</T>
//
// @param pOutput ����ַ���
// @param size ����ַ�������
// @param pValue �����ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RChar16::ConvertTo32(TChar32* pOutput, TSize size, TChar16C* pValue){
   return 0;
}

//============================================================
// <T>���㽫16λ�ַ���ת��ΪUTF8λ�ַ�������Ҫ�ĳ��ȡ�</T>
//
// @param pValue 16λ�ַ���
// @return ����Ҫ����
//============================================================
TInt RChar16::ConvertToUtf8(TChar16C* pValue){
   MO_ASSERT(pValue);
   TSize length = wcslen(pValue);
#ifdef _MO_WINDOWS
   TSize tempLen = length;
   WideCharToMultiByte(CP_UTF8, 0, pValue, tempLen, NULL, 0, NULL, FALSE);
#else
   MO_STATIC_FATAL("Unimplemented.");
#endif // _MO_WINDOWS
   return length;
}

//============================================================
// <T>��16λ�ַ���ת��ΪUTF8λ�ַ�����</T>
//
// @param pOutput ����ַ���
// @param size ����ַ�������
// @param pValue �����ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RChar16::ConvertToUtf8(TChar8* pOutput, TSize size, TChar16C* pValue){
   MO_ASSERT(pOutput);
   MO_ASSERT(pValue);
#ifdef _MO_WINDOWS
   TSize length = wcslen(pValue);
   return WideCharToMultiByte(CP_UTF8, 0, pValue, length, pOutput, size, NULL, FALSE);
#else
   MO_STATIC_FATAL("Unimplemented.");
#endif // _MO_WINDOWS
   return 0;
}

MO_NAMESPACE_END
