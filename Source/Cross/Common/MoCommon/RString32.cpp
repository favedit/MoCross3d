#include "MoCmString32.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���ַ�����</T>
//============================================================
TChar32C* RString32::EmptyPtr = L"";
TString32 RString32::EmptyString;

//============================================================
// <T>��ȡANSI�ַ����ĳ��ȡ�</T>
//
// @param pSource ANSI�ַ���
// @return ����
//============================================================
TInt RString32::Length(TChar32C* pValues){
   MO_ASSERT(pValues);
   return wcslen(pValues);
}

//============================================================
// <T>�ж���Դ�ַ������Ƿ���ָ���ַ�����</T>
//
// @param pSource ��Դ�ַ���
// @param pValue ָ���ַ���
// @return �Ƿ���
//============================================================
TBool RString32::Constains(TChar32C* pSource, TChar32C* pValue){
   TInt sourceLength = Length(pSource);
   TInt valueLength = Length(pValue);
   TInt index = RChar32s::Find(pSource, sourceLength, pValue, valueLength);
   return (ENotFound != index);
}

//============================================================
// <T>�ж������ַ����Ƿ���ȡ�</T>
//
// @param pSource ��Դ�ַ���
// @param pTarget Ŀ���ַ���
// @return �Ƿ����
//============================================================
TBool RString32::Equals(TChar32C* pSource, TChar32C* pTarget){
   // ���ȶ�Ϊ0��ʱ����Ϊ���
   TInt sourceLength = 0;
   if(pSource != NULL){
      sourceLength = MO_LIB_STRING_LENGTH32(pSource);
   }
   TInt targetLength = 0;
   if(pTarget != NULL){
      targetLength = MO_LIB_STRING_LENGTH32(pTarget);
   }
   if((sourceLength == 0) && (targetLength == 0)){
      return ETrue;
   }
   // �κ�һ��Ϊ����Ϊ�����
   if((pSource == NULL) || (pTarget == NULL)){
      return EFalse;
   }
   // �Ƚ�����
   TInt result = MO_LIB_STRING_COMPARE32(pSource, pTarget);
   return (result == 0);
}

//============================================================
// <T>������Դ�ַ�����ָ���ַ���������λ�á�</T>
//
// @param pSource ��Դ�ַ���
// @param pValue ָ���ַ���
// @return ����λ��
//============================================================
TInt RString32::Find(TChar32C* pSource, TChar32C* pValue){
   TInt sourceLength = Length(pSource);
   TInt valueLength = Length(pValue);
   TInt index = RChar32s::Find(pSource, sourceLength, pValue, valueLength);
   return index;
}

////============================================================
//// <T>��ȡANSI�ַ����Ĺ�ϣֵ��</T>
////
//// @param pValues ANSI�ַ���
//// @return ��ϣֵ
////============================================================
//THashCode RString32::MakeHashCode(TChar32C* pValues){
//   MO_ASSERT(pValues);
//   return RTypes<TChar32>::MakeHashCode(pValues, wcslen(pValues));
//}
//
////============================================================
//// <T>��ȡANSI�ַ����Ĳ����ִ�Сд�Ĺ�ϣֵ��</T>
////
//// @param pValues ANSI�ַ���
//// @return ��ϣֵ
////============================================================
//THashCode RString32::MakeNocaseHashCode(TChar32C* pValues){
//   MO_ASSERT(pValues);
//   THashCode hash = 0;
//   TInt length = wcslen(pValues);
//   while(--length >= 0){
//      hash += (hash << 4) + (hash << 3) + (hash << 2) + (hash << 1) + towlower(pValues[length]);
//   }
//   return hash;
//}
//
////============================================================
//// <T>��ȡANSI�ַ����Ĺ�ϣֵ��</T>
////
//// @param ptr ANSI�ַ���ָ��
//// @return ��ϣֵ
////============================================================
//TBool RString32::AllocCopy(TChar32C* pValues, TChar32** ppTarget){
//   if(NULL != pValues){
//      TSize length = wcslen(pValues) + 1;
//      TChar32* pAlloc = MO_STATIC_TYPES_ALLOC(TChar32, length);
//      MO_LIB_MEMCPY(pAlloc, length, pValues, length);
//      *ppTarget = pAlloc;
//   }
//   return ETrue;
//}
//
////============================================================
//TBool RString32::AllocFree(TChar32* pValues){
//   MO_FREE(pValues);
//   return ETrue;
//}
//
////============================================================
//// <T>��ȫ�����ַ�����Ŀ���ַ�����</T>
//// <P>���Ŀ���ַ�����ֵ�ַ���Ϊ�գ��򲻽��и��ơ�</P>
//// <P>���Ŀ���ַ������Ȳ��㣬��ֻ�����ܸ��ƵĲ������ݡ�</P>
//// <P>���ƺ�ĩβ�ַ��������ա�</P>
////
//// @param pTarget Ŀ���ַ���ָ��
//// @param size Ŀ���ַ��ܳ���
//// @param pValue ֵ�ַ���ָ��
//// @return ���Ƴ���
////============================================================
//TInt RString32::SafeCopy(TChar32* pTarget, TSize size, TChar32C* pValue){
//   if((NULL != pTarget) && (size > 0) && (NULL != pValue)){
//      TSize length = wcslen(pValue);
//      if(length > 0){
//         if(length >= size){
//            length = size - 1;
//         }
//         memcpy(pTarget, pValue, length);
//         pTarget[length] = 0;
//      }else{
//         pTarget[0] = 0;
//      }
//      return length;
//   }
//   return 0;
//}
//
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
//TInt RString32::ForceCopy(TChar32* pTarget, TSize size, TChar32C* pValue){
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

//============================================================
// <T>��ý��ַ���ת��Ϊ8λ�ַ�������Ҫ�ĳ���</T>
//
// @param pValue ��ת���ַ���
// @return ����Ҫ����
//============================================================
TInt RString32::ConvertToString8(TChar32C* pValue){
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
TInt RString32::ConvertToString8(TChar8* pTarget, TInt size, TChar32C* pValue){
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
TInt RString32::ConvertToString16(TChar32C* pValue){
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
TInt RString32::ConvertToString16(TChar16* pTarget, TInt size, TChar32C* pValue){
   return 0;
}

//============================================================
// <T>��ý��ַ���ת��Ϊ32λ�ַ�������Ҫ�ĳ���</T>
//
// @param pValue ��ת���ַ���
// @return ����Ҫ����
//============================================================
TInt RString32::ConvertToString32(TChar32C* pValue){
   MO_ASSERT(pValue);
   return MO_LIB_STRING_LENGTH32(pValue);
}

//============================================================
// <T>���ַ���ת��Ϊ16λ�ַ���</T>
//
// @param pTargetת������ַ���
// @param size pTarget����
// @param pValue ��ת���ַ���
// @return ����Ҫ���ȣ����ʧ�ܷ���-1
//============================================================
TInt RString32::ConvertToString32(TChar32* pTarget, TInt size, TChar32C* pValue){
   MO_ASSERT(pTarget);
   MO_ASSERT(pValue);
   TSize length = MO_LIB_STRING_LENGTH32(pValue);
   MO_LIB_MEMORY_COPY(pTarget, sizeof(TChar32) * length, pValue, sizeof(TChar32) * length);
   return length;
}

MO_NAMESPACE_END
