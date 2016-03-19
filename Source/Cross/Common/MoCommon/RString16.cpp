#include "MoCmString16.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���ַ�����</T>
//============================================================
TChar16C* RString16::EmptyPtr = L"";
TString16 RString16::EmptyString;

//============================================================
// <T>��ȡ�ַ����ĳ��ȡ�</T>
//
// @param pValue �ַ���
// @return ����
//============================================================
TInt RString16::Length(TChar16C* pValue){
   return (pValue != NULL) ? wcslen(pValue) : 0;
}

//============================================================
// <T>�ж���Դ�ַ������Ƿ���ָ���ַ�����</T>
//
// @param pSource ��Դ�ַ���
// @param pValue ָ���ַ���
// @return �Ƿ���
//============================================================
TBool RString16::Constains(TChar16C* pSource, TChar16C* pValue){
   TInt sourceLength = Length(pSource);
   TInt valueLength = Length(pValue);
   TInt index = RChar16s::Find(pSource, sourceLength, pValue, valueLength);
   return (ENotFound != index);
}

//============================================================
// <T>�ж������ַ����Ƿ���ȡ�</T>
//
// @param pSource ��Դ�ַ���
// @param pTarget Ŀ���ַ���
// @return �Ƿ����
//============================================================
TBool RString16::Equals(TChar16C* pSource, TChar16C* pTarget){
   // ���ȶ�Ϊ0��ʱ����Ϊ���
   TInt sourceLength = 0;
   if(pSource != NULL){
      sourceLength = MO_LIB_STRING_LENGTH16(pSource);
   }
   TInt targetLength = 0;
   if(pTarget != NULL){
      targetLength = MO_LIB_STRING_LENGTH16(pTarget);
   }
   if((sourceLength == 0) && (targetLength == 0)){
      return ETrue;
   }
   // �κ�һ��Ϊ����Ϊ�����
   if((pSource == NULL) || (pTarget == NULL)){
      return EFalse;
   }
   // �Ƚ�����
   TInt result = MO_LIB_STRING_COMPARE16(pSource, pTarget);
   return (result == 0);
}

//============================================================
// <T>������Դ�ַ�����ָ���ַ���������λ�á�</T>
//
// @param pSource ��Դ�ַ���
// @param pValue ָ���ַ���
// @return ����λ��
//============================================================
TInt RString16::Find(TChar16C* pSource, TChar16C* pValue){
   TInt sourceLength = Length(pSource);
   TInt valueLength = Length(pValue);
   TInt index = RChar16s::Find(pSource, sourceLength, pValue, valueLength);
   return index;
}

//============================================================
// <T>�����ַ����Ĺ�ϣֵ��</T>
//
// @param pValue �ַ���
// @return ��ϣֵ
//============================================================
THashCode RString16::MakeHashCode(TChar16C* pValue){
   THashCode code = 0;
   if(pValue != NULL){
      TInt length = wcslen(pValue);
      code = RTypes<TChar16>::MakeHashCode(pValue, length);
   }
   return code;
}

//============================================================
// <T>�����ַ����Ĳ����ִ�Сд�Ĺ�ϣֵ��</T>
//
// @param pValue �ַ���
// @return ��ϣֵ
//============================================================
THashCode RString16::MakeNocaseHashCode(TChar16C* pValue){
   THashCode code = 0;
   if(pValue != NULL){
      TInt length = wcslen(pValue);
      while(--length >= 0){
         code += (code << 4) + (code << 3) + (code << 2) + (code << 1) + tolower(pValue[length]);
      }
   }
   return code;
}

////============================================================
//// <T>��ȡANSI�ַ����Ĺ�ϣֵ��</T>
////
//// @param ptr ANSI�ַ���ָ��
//// @return ��ϣֵ
////============================================================
//TBool RString16::AllocCopy(TChar16C* pValues, TChar16** ppTarget){
//   if(NULL != pValues){
//      TSize length = wcslen(pValues) + 1;
//      TChar16* pAlloc = RTypeMemory<TChar16>::Alloc(length);
//      MO_ASSERT(pAlloc);
//      MO_LIB_MEMCPY(pAlloc, length, pValues, length);
//      *ppTarget = pAlloc;
//   }
//   return ETrue;
//}
//
////============================================================
//TBool RString16::AllocFree(TChar16* pValues){
//   RTypeMemory<TChar16>::Free(pValues);
//   return ETrue;
//}

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
TInt RString16::SafeCopy(TChar16* pTarget, TSize size, TChar8C* pValue){
   if((NULL != pTarget) && (size > 0) && (NULL != pValue)){
      TSize length = strlen(pValue);
      if(length > 0){
         if(length >= size){
            length = size - 1;
         }
         for(TInt n = 0; n < length; n++){
            *pTarget++ = *pValue++;
         }
         *pTarget = 0;
      }else{
         pTarget[0] = 0;
      }
      return length;
   }
   return 0;
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
TInt RString16::SafeCopy(TChar16* pTarget, TSize size, TChar16C* pValue){
   if((NULL != pTarget) && (size > 0) && (NULL != pValue)){
      TSize length = wcslen(pValue);
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

////============================================================
//// <T>ǿ�Ƹ����ַ�����Ŀ���ַ�����</T>
//// <P>���Ŀ���ַ���Ϊ�գ��������⡣</P>
//// <P>���ֵ�ַ���Ϊ�գ����سɹ���</P>
//// <P>���Ŀ���ַ������Ȳ��㣬�������⡣</P>
//// <P>���ƺ�ĩβ�ַ��������ա�</P>
////
//// @param pTarget Ŀ���ַ���ָ��
//// @param size Ŀ���ַ��ܳ���
//// @param pValue ֵ�ַ���ָ��
//// @return ���Ƴ���
////============================================================
//TInt RString16::ForceCopy(TChar16* pTarget, TSize size, TChar16C* pValue){
//   MO_ASSERT(pTarget);
//   MO_ASSERT(size > 0);
//   if(NULL != pValue){
//      TSize length = wcslen(pValue);
//      if(length > 0){
//         MO_ASSERT(length < size);
//         memcpy(pTarget, pValue, length);
//         pTarget[length] = 0;
//         return length;
//      }
//   }
//   return 0;
//}
//
////============================================================
//// <T>��һ���ַ����У��滻��Դ�ַ���ΪĿ���ַ�����</T>
////
//// @param str1 Ҫ�鵽���ַ���
//// @param str2 �ַ����ļ��
//// @return ���Ƴ���
////============================================================
//TInt RString16::ReplaceAll(TChar16* pValue, TChar16* pSource, TChar16* pTarget, TChar16* pBuffer, TInt bufferLength){
//   MO_ASSERT(pValue);
//   MO_ASSERT(pSource);
//   MO_ASSERT(pTarget);
//   MO_ASSERT(pBuffer);
//   TInt length = wcslen(pValue);
//   TInt sourceLength = wcslen(pSource);
//   TInt targetLength = wcslen(pTarget);
//   return RTypes<TChar16>::ReplaceAll(pValue, length, pSource, sourceLength, pTarget, targetLength, pBuffer, bufferLength);
//}

//============================================================
// <T>��ý��ַ���ת��Ϊ8λ�ַ�������Ҫ�ĳ���</T>
//
// @param pValue ��ת���ַ���
// @return ����Ҫ����
//============================================================
TInt RString16::ConvertToString8(TChar16C* pValue){
   MO_ASSERT(pValue);
   TSize length = MO_LIB_STRING_LENGTH16(pValue);
#ifdef _MO_WINDOWS
   TInt result = WideCharToMultiByte(CP_ACP, 0, pValue, length, NULL, 0, NULL, NULL);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   TInt result = sizeof(TChar16) * length;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   TInt result = length;
#endif // _MO_ANDROID
   return result;
}

//============================================================
// <T>���ַ���ת��Ϊ8λ�ַ���</T>
//
// @param pTargetת������ַ���
// @param size pTarget����
// @param pValue ��ת���ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RString16::ConvertToString8(TChar8* pTarget, TInt size, TChar16C* pValue){
   MO_ASSERT(pTarget);
   MO_ASSERT(pValue);
   TSize length = MO_LIB_STRING_LENGTH16(pValue);
#ifdef _MO_WINDOWS
   TInt result = WideCharToMultiByte(CP_ACP, 0, pValue, length, pTarget, size, NULL, NULL);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   iconv_t code = iconv_open("GBK", "UTF-8");
   if(NULL == code){
      MO_STATIC_FATAL("Iconv open failure.");
   }
   TChar8* pInput = (TChar8*)pValue;
   TSize inputLength = length;
   TSize outputLength = size;
   TInt result = iconv(code, &pInput, &inputLength, &pTarget, &outputLength);
   if(-1 == result){
      MO_STATIC_FATAL("Iconv convert failure.");
      return -1;
   }
   iconv_close(code);
   pTarget[outputLength] = 0;
#endif // _MO_LINUX
#ifdef _MO_ANDROID
   TInt result = length;
   // g_lpdlIcuuc = dlopen("/system/lib/libicuuc.so", RTLD_LAZY);
#endif // _MO_ANDROID
   return result;
}

//============================================================
// <T>��ý��ַ���ת��Ϊ16λ�ַ�������Ҫ�ĳ���</T>
//
// @param pValue ��ת���ַ���
// @return ����Ҫ����
//============================================================
TInt RString16::ConvertToString16(TChar16C* pValue){
   MO_ASSERT(pValue);
   return MO_LIB_STRING_LENGTH16(pValue);
}

//============================================================
// <T>���ַ���ת��Ϊ16λ�ַ���</T>
//
// @param pTargetת������ַ���
// @param size pTarget����
// @param pValue ��ת���ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RString16::ConvertToString16(TChar16* pTarget, TInt size, TChar16C* pValue){
   MO_ASSERT(pTarget);
   MO_ASSERT(pValue);
   TSize length = MO_LIB_STRING_LENGTH16(pValue);
   MO_LIB_MEMORY_COPY(pTarget, sizeof(TChar16) * length, pValue, sizeof(TChar16) * length);
   return length;
}

//============================================================
// <T>��ý��ַ���ת��Ϊ32λ�ַ�������Ҫ�ĳ���</T>
//
// @param pValue ��ת���ַ���
// @return ����Ҫ����
//============================================================
TInt RString16::ConvertToString32(TChar16C* pValue){
   return 0;
}

//============================================================
// <T>���ַ���ת��Ϊ16λ�ַ���</T>
//
// @param pTargetת������ַ���
// @param size pTarget����
// @param pValue ��ת���ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RString16::ConvertToString32(TChar32* pTarget, TInt size, TChar16C* pValue){
   return 0;
}

MO_NAMESPACE_END
