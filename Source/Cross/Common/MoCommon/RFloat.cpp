#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����ǲ������֡�</T>
//
// @param pValue �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RFloat::IsFloat(TCharC* pValue){
   TInt length = RChars::Length(pValue);
   TInt count = 0;
   for(TInt n = 0; n < length; n++){
      TChar value = pValue[n];
      if(('.' == value) && (0 == count)){
         count++;
         continue;
      }else if((('-' == value) || ('+' == value)) && (0 == n)){
         continue;
      }else if((value >= '0') && (value <= '9')){
         continue;
      }
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>�ж������Ƿ��ڷ�Χ�С�</T>
//
// @param value ����
// @param min ��Сֵ
// @param max ���ֵ
// @return �Ƿ��ڷ�Χ��
//============================================================
TFloat RFloat::InRange(TFloat value, TFloat min, TFloat max){
   if(value < min){
      return min;
   }
   if(value > max){
      return max;
   }
   return value;
}

//============================================================
// <T>��8λ�ַ����任Ϊ��������</T>
//
// @param pValue �ַ���
// @return ������
//============================================================
TFloat RFloat::Parse8(TChar8C* pValue){
   MO_ASSERT(pValue);
   return (TFloat)atof(pValue);
}

//============================================================
// <T>��16λ�ַ����任Ϊ��������</T>
//
// @param pValue �ַ���
// @return ������
//============================================================
TFloat RFloat::Parse16(TChar16C* pValue){
   MO_ASSERT(pValue);
#ifdef _MO_WINDOWS
   return (TFloat)_wtof(pValue);
#else
   return 0;
#endif // _MO_WINDOWS
}

//============================================================
// <T>��32λ�ַ����任Ϊ��������</T>
//
// @param pValue �ַ���
// @return ������
//============================================================
TFloat RFloat::Parse32(TChar32C* pValue){
   MO_ASSERT(pValue);
#ifdef _MO_WINDOWS
   return (TFloat)_wtof(pValue);
#else
   return 0;
#endif // _MO_WINDOWS
}

//============================================================
// <T>���ַ����任Ϊ��������</T>
//
// @param pValue �ַ���
// @return ������
//============================================================
TFloat RFloat::Parse(TCharC* pValue){
   MO_ASSERT(pValue);
#ifdef _UNICODE
   return (TFloat)_wtof(pValue);
#else
   return (TFloat)atof(pValue);
#endif // _UNICODE
}

//============================================================
// <T>���ַ����任Ϊ��������</T>
//
// @param pValue �ַ���
// @return ������
//============================================================
TFloat RFloat::ParseNvl(TCharC* pValue){
#ifdef _UNICODE
   return (NULL == pValue) ? 0.0f : (TFloat)_wtof(pValue);
#else
   return (NULL == pValue) ? 0.0f : (TFloat)atof(pValue);
#endif
}

//============================================================
// <T>��16�����ַ����任Ϊ��������</T>
//
// @param pValue �ַ���
// @return ������
//============================================================
TFloat RFloat::ParseHex(TCharC* pValue){
   MO_ASSERT(pValue);
   TByte result[sizeof(TFloat)];
   // ��ȡ�ַ���
   TInt size = sizeof(TFloat);
   for(TInt n = 0; n < size; n++){
      // ��ȡ��4λ
      TChar hbyte = *pValue++;
      if(hbyte >= '0' && hbyte <= '9'){
         hbyte = hbyte - '0';
      }else if(hbyte >= 'a' && hbyte <= 'f'){
         hbyte = hbyte - 'a' + 10;
      }else if(hbyte >= 'A' && hbyte <= 'F'){
         hbyte = hbyte - 'A' + 10;
      }else{
         MO_THROW("Unknown float format.");
      }
      // ��ȡ��4λ
      TChar lbyte = *pValue++;
      if(lbyte >= '0' && lbyte <= '9'){
         lbyte = lbyte - '0';
      }else if(lbyte >= 'a' && lbyte <= 'f'){
         lbyte = lbyte - 'a' + 10;
      }else if(lbyte >= 'A' && lbyte <= 'F'){
         lbyte = lbyte - 'A' + 10;
      }else{
         MO_THROW("Unknown float format.");
      }
      // ��������
      result[n] = (hbyte << 4) + lbyte;
   }
   return *(TFloat*)result;
}

//============================================================
// <T>��16�����ַ����任Ϊ��������</T>
//
// @param pValue �ַ���
// @return ������
//============================================================
TFloat RFloat::ParseHexNvl(TCharC* pValue){
   return (NULL == pValue) ? 0.0f : ParseHex(pValue);
}

//============================================================
// <T>���������任Ϊ8λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ��������
// @return �ַ���
//============================================================
TChar8C* RFloat::ToString8(TFloat value, TChar8* pBuffer, TInt capacity){
   MO_LIB_STRING_FORMAT8(pBuffer, capacity, "%f", value);
   return pBuffer;
}

//============================================================
// <T>���������任Ϊ16λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ��������
// @return �ַ���
//============================================================
TChar16C* RFloat::ToString16(TFloat value, TChar16* pBuffer, TInt capacity){
   // ��ʽ������
   TChar8 buffer[MO_FS_FLOAT_LENGTH];
   MO_LIB_STRING_FORMAT8(buffer, MO_FS_FLOAT_LENGTH, "%f", value);
   // ��������
   for(TInt n = 0; n < MO_FS_FLOAT_LENGTH; n++){
      TChar16 value = buffer[n];
      pBuffer[n] = value;
      if(value == 0){
         break;
      }
   }
   return pBuffer;
}

//============================================================
// <T>���������任Ϊ32λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ��������
// @return �ַ���
//============================================================
TChar32C* RFloat::ToString32(TFloat value, TChar32* pBuffer, TInt capacity){
   // ��ʽ������
   TChar8 buffer[MO_FS_FLOAT_LENGTH];
   MO_LIB_STRING_FORMAT8(buffer, MO_FS_FLOAT_LENGTH, "%f", value);
   // ��������
   for(TInt n = 0; n < MO_FS_FLOAT_LENGTH; n++){
      TChar32 value = buffer[n];
      pBuffer[n] = value;
      if(value == 0){
         break;
      }
   }
   return pBuffer;
}

//============================================================
// <T>���������任Ϊ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ��������
// @return �ַ���
//============================================================
TCharC* RFloat::ToString(TFloat value, TChar* pBuffer, TInt capacity){
#ifdef _MO_UNICODE
   // ��ʽ������
   TChar8 buffer[MO_FS_FLOAT_LENGTH];
   MO_LIB_STRING_FORMAT8(buffer, MO_FS_FLOAT_LENGTH, "%f", value);
   // ��������
   for(TInt n = 0; n < MO_FS_FLOAT_LENGTH; n++){
      TChar value = buffer[n];
      pBuffer[n] = value;
      if(value == 0){
         break;
      }
   }
#else
   MO_LIB_STRING_FORMAT(pBuffer, capacity, TC("%f"), value);
#endif // _MO_UNICODE
   return pBuffer;
}

//============================================================
// <T>���������任Ϊ16�����ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ��������
// @return �ַ���
//============================================================
TCharC* RFloat::ToHexString(TFloat value, TChar* pBuffer, TInt capacity){
   TByte* pValue = (TByte*)&value;
   TChar* pWrite = pBuffer;
   // ����ַ���
   TInt size = sizeof(TFloat);
   for(TInt n = 0; n < size; n++){
      TChar ch = pValue[n];
      TInt byte = (ch >= 0) ? ch : 0x100 + ch;
      *pWrite++ = RByte::HEX_CHARS[byte >> 4];
      *pWrite++ = RByte::HEX_CHARS[byte & 0x0F];
   }
   // ���ý����ַ�
   *pWrite = 0;
   return pBuffer;
}

MO_NAMESPACE_END
