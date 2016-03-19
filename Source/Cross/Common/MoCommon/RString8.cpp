#ifdef _MO_WINDOWS
#include <Windows.h>
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
#include <ctype.h>
#include <iconv.h>
#endif // _MO_LINUX
#ifdef _MO_ANDROID
// #include <dlfcn.h>
#endif // _MO_ANDROID
#include "MoCmString8.h"
#include "MoCmString.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���ַ�����</T>
//============================================================
TChar8C* RString8::EmptyPtr = "";
TString8 RString8::EmptyString;

//============================================================
// <T>��ȡANSI�ַ����ĳ��ȡ�</T>
//
// @param pSource ANSI�ַ���
// @return ����
//============================================================
TInt RString8::Length(TChar8C* pValue){
   if(pValue == NULL){
      return 0;
   }
   return strlen(pValue);
}

//============================================================
// <T>�ж������ַ����Ƿ���ȡ�</T>
//
// @param pSource �Ƚ�Դ�ַ���
// @param pTarget �Ƚ�Ŀ���ַ���
// @return �Ƿ����
//============================================================
TBool RString8::Equals(TChar8C* pSource, TChar8C* pTarget){
   // ���ȶ�Ϊ0��ʱ����Ϊ���
   TInt sourceLength = 0;
   if(pSource != NULL){
      sourceLength = MO_LIB_STRING_LENGTH8(pSource);
   }
   TInt targetLength = 0;
   if(pTarget != NULL){
      targetLength = MO_LIB_STRING_LENGTH8(pTarget);
   }
   if((sourceLength == 0) && (targetLength == 0)){
      return ETrue;
   }
   // �κ�һ��Ϊ����Ϊ�����
   if((pSource == NULL) || (pTarget == NULL)){
      return EFalse;
   }
   // �Ƚ�����
   TInt result = MO_LIB_STRING_COMPARE8(pSource, pTarget);
   return (result == 0);
}

//============================================================
// <T>�ж���Դ�ַ������Ƿ���ָ���ַ�����</T>
//
// @param pSource ��Դ�ַ���
// @param pValue ָ���ַ���
// @return �Ƿ���
//============================================================
TBool RString8::Constains(TChar8C* pSource, TChar8C* pValue){
   TInt sourceLength = Length(pSource);
   TInt valueLength = Length(pValue);
   TInt index = RChar8s::Find(pSource, sourceLength, pValue, valueLength);
   return (ENotFound != index);
}

//============================================================
// <T>������Դ�ַ�����ָ���ַ���������λ�á�</T>
//
// @param pSource ��Դ�ַ���
// @param pValue ָ���ַ���
// @return ����λ��
//============================================================
TInt RString8::Find(TChar8C* pSource, TChar8C* pValue){
   TInt sourceLength = Length(pSource);
   TInt valueLength = Length(pValue);
   TInt index = RChar8s::Find(pSource, sourceLength, pValue, valueLength);
   return index;
}

//============================================================
// <T>��ȡANSI�ַ����Ĺ�ϣֵ��</T>
//
// @param pValues ANSI�ַ���
// @return ��ϣֵ
//============================================================
THashCode RString8::MakeHashCode(TChar8C* pValues){
   MO_ASSERT(pValues);
   return RTypes<TChar8>::MakeHashCode(pValues, strlen(pValues));
}

//============================================================
// <T>��ȡANSI�ַ����Ĳ����ִ�Сд�Ĺ�ϣֵ��</T>
//
// @param pValues ANSI�ַ���
// @return ��ϣֵ
//============================================================
THashCode RString8::MakeNocaseHashCode(TChar8C* pValues){
   MO_ASSERT(pValues);
   THashCode hash = 0;
   TInt length = strlen(pValues);
   while(--length >= 0){
      hash += (hash << 4) + (hash << 3) + (hash << 2) + (hash << 1) + tolower(pValues[length]);
   }
   return hash;
}

//============================================================
// <T>��ȡANSI�ַ����Ĺ�ϣֵ��</T>
//
// @param ptr ANSI�ַ���ָ��
// @return ��ϣֵ
//============================================================
TBool RString8::AllocCopy(TChar8C* pValues, TChar8** ppTarget){
   if(NULL != pValues){
      TSize length = strlen(pValues) + 1;
      TChar8* pAlloc = MO_STATIC_TYPES_ALLOC(TChar8, length);
      MO_ASSERT(pAlloc);
      MO_LIB_MEMORY_COPY(pAlloc, length, pValues, length);
      *ppTarget = pAlloc;
   }
   return ETrue;
}

//============================================================
TBool RString8::AllocFree(TChar8* pValues){
   MO_FREE(pValues);
   return ETrue;
}

//============================================================
// <T>��ȫ�����ַ�����Ŀ���ַ�����</T>
// <P>���Ŀ���ַ�����ֵ�ַ���Ϊ�գ��򲻽��и��ơ�</P>
// <P>���Ŀ���ַ������Ȳ��㣬��ֻ�����ܸ��ƵĲ������ݡ�</P>
// <P>���ƺ�ĩβ�ַ��������ա�</P>
//
// @param pTarget Ŀ���ַ���ָ��
// @param size Ŀ���ַ��ܳ���
// @param pValue ֵ�ַ���ָ��
// @return ���Ƴ���
//============================================================
TInt RString8::SafeCopy(TChar8* pTarget, TSize size, TChar8C* pValue){
   if((NULL != pTarget) && (size > 0) && (NULL != pValue)){
      TSize length = strlen(pValue);
      if(length > 0){
         if(length >= size){
            length = size - 1;
         }
         memcpy(pTarget, pValue, length);
         pTarget[length] = 0;
      }else{
         pTarget[0] = 0;
      }
      return length;
   }
   return 0;
}

//============================================================
// <T>ǿ�Ƹ����ַ�����Ŀ���ַ�����</T>
// <P>���Ŀ���ַ���Ϊ�գ��������⡣</P>
// <P>���ֵ�ַ���Ϊ�գ����سɹ���</P>
// <P>���Ŀ���ַ������Ȳ��㣬�������⡣</P>
// <P>���ƺ�ĩβ�ַ��������ա�</P>
//
// @param pTarget Ŀ���ַ���ָ��
// @param size Ŀ���ַ��ܳ���
// @param pValue ֵ�ַ���ָ��
// @return ���Ƴ���
//============================================================
TInt RString8::ForceCopy(TChar8* pTarget, TSize size, TChar8C* pValue){
   MO_ASSERT(pTarget);
   MO_ASSERT(size > 0);
   if(NULL != pValue){
      TSize length = strlen(pValue);
      if(length > 0){
         MO_ASSERT(length < size);
         memcpy(pTarget, pValue, length);
         pTarget[length] = 0;
         return length;
      }
   }
   return 0;
}

//============================================================
// <T>��һ���ַ����У��滻��Դ�ַ���ΪĿ���ַ�����</T>
//
// @param str1 Ҫ�鵽���ַ���
// @param str2 �ַ����ļ��
// @return ���Ƴ���
//============================================================
TInt RString8::ReplaceAll(TChar8* pValue, TChar8* pSource, TChar8* pTarget, TChar8* pBuffer, TInt bufferLength){
   MO_ASSERT(pValue);
   MO_ASSERT(pSource);
   MO_ASSERT(pTarget);
   MO_ASSERT(pBuffer);
   TInt length = strlen(pValue);
   TInt sourceLength = strlen(pSource);
   TInt targetLength = strlen(pTarget);
   return RTypes<TChar8>::Replace(pValue, length, pSource, sourceLength, pTarget, targetLength, pBuffer, bufferLength);
}

//============================================================
// <T>��ý��ַ���ת��Ϊ8λ�ַ�������Ҫ�ĳ���</T>
//
// @param pValue ��ת���ַ���
// @return ����Ҫ����
//============================================================
TInt RString8::ConvertToString8(TChar8C* pValue){
   MO_ASSERT(pValue);
   return MO_LIB_STRING_LENGTH8(pValue);
}

//============================================================
// <T>���ַ���ת��Ϊ8λ�ַ���</T>
//
// @param pTargetת������ַ���
// @param size pTarget����
// @param pValue ��ת���ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RString8::ConvertToString8(TChar8* pTarget, TInt size, TChar8C* pValue){
   MO_ASSERT(pTarget);
   MO_ASSERT(pValue);
   TSize length = MO_LIB_STRING_LENGTH8(pValue);
   MO_LIB_MEMORY_COPY(pTarget, sizeof(TChar8) * length, pValue, sizeof(TChar8) * length);
   return length;
}

//============================================================
// <T>��ý��ַ���ת��Ϊ16λ�ַ�������Ҫ�ĳ���</T>
//
// @param pValue ��ת���ַ���
// @return ����Ҫ����
//============================================================
TInt RString8::ConvertToString16(TChar8C* pValue){
   if(pValue == NULL){
      return 0;
   }
   TInt result = 0;
   TSize length = MO_LIB_STRING_LENGTH8(pValue);
#ifdef _MO_WINDOWS
   result = MultiByteToWideChar(CP_UTF8, 0, pValue, length, NULL, 0);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   result = sizeof(TChar16) * length;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   result = sizeof(TChar32) * length;
#endif // _MO_ANDROID
   return result;
}

//============================================================
// <T>���ַ���ת��Ϊ16λ�ַ���</T>
//
// @param pTargetת������ַ���
// @param size pTarget����
// @param pValue ��ת���ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RString8::ConvertToString16(TChar16* pTarget, TInt size, TChar8C* pValue){
   MO_CHECK(pTarget, return 0);
   MO_CHECK(pValue, return 0);
   TInt result = 0;
   TSize length = MO_LIB_STRING_LENGTH8(pValue);
#ifdef _MO_WINDOWS
   result = MultiByteToWideChar(CP_UTF8, 0, pValue, length, pTarget, size);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   iconv_t code = iconv_open("UTF-8", "GBK");
   if(NULL == code){
      MO_STATIC_FATAL("Iconv open failure.");
   }
   TChar8* pInput = (TChar8*)pValue;
   TSize inputLength = length;
   TChar8* pOutput = (TChar8*)pTarget;
   TSize outputLength = size;
   result = iconv(code, &pInput, &inputLength, &pOutput, &outputLength);
   if(-1 == result){
      MO_STATIC_FATAL("Iconv convert failure.");
      return -1;
   }
   iconv_close(code);
   pTarget[outputLength] = 0;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   for(TInt n = 0; n < length; n++){
      *pTarget++ = *pValue++;
   }
   pTarget[length] = 0;
   result = length;
   // g_lpdlIcuuc = dlopen("/system/lib/libicuuc.so", RTLD_LAZY);
#endif // _MO_ANDROID
   return result;
}

//============================================================
// <T>��ý��ַ���ת��Ϊ32λ�ַ�������Ҫ�ĳ���</T>
//
// @param pValue ��ת���ַ���
// @return ����Ҫ����
//============================================================
TInt RString8::ConvertToString32(TChar8C* pValue){
   MO_CHECK(pValue, return 0);
   TInt result = 0;
   TSize length = MO_LIB_STRING_LENGTH8(pValue);
#ifdef _MO_WINDOWS
   result = MultiByteToWideChar(CP_UTF8, 0, pValue, length, NULL, 0);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   result = sizeof(TChar16) * length;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   result = sizeof(TChar32) * length;
#endif // _MO_ANDROID
   return result;
}

//============================================================
// <T>���ַ���ת��Ϊ16λ�ַ���</T>
//
// @param pTargetת������ַ���
// @param size pTarget����
// @param pValue ��ת���ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RString8::ConvertToString32(TChar32* pTarget, TInt size, TChar8C* pValue){
   MO_CHECK(pTarget, return 0);
   MO_CHECK(pValue, return 0);
   TInt result = 0;
   TSize length = MO_LIB_STRING_LENGTH8(pValue);
#ifdef _MO_WINDOWS
   result = MultiByteToWideChar(CP_UTF8, 0, pValue, length, pTarget, size);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   iconv_t code = iconv_open("UTF-8", "GBK");
   if(NULL == code){
      MO_STATIC_FATAL("Iconv open failure.");
   }
   TChar8* pInput = (TChar8*)&pValue;
   TSize inputLength = length;
   TChar8* pOutput = (TChar8*)pTarget;
   TSize outputLength = size;
   result = iconv(code, &pInput, &inputLength, &pOutput, &outputLength);
   if(-1 == result){
      MO_STATIC_FATAL("Iconv convert failure.");
      return -1;
   }
   iconv_close(code);
   pTarget[outputLength] = 0;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   for(TInt n = 0; n < length; n++){
      *pTarget++ = *pValue++;
   }
   pTarget[length] = 0;
   result = length;
#endif // _MO_ANDROID
   return result;
}

MO_NAMESPACE_END
