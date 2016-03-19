#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����Ƿ�Ϊ���֡�</T>
//
// @param pSource �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RInt8::Test(TCharC* pSource){
   return RNumber<TInt8>::IsSignInteger<TChar>(pSource);
}

//============================================================
// <T>����ʮ����8λ�ַ���Ϊ�з���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���8λ����
//============================================================
TInt8 RInt8::Parse8(TChar8C* pSource){
   return RNumber<TInt8>::ParseSign<TChar8>(pSource);
}

//============================================================
// <T>����ʮ����16λ�ַ���Ϊ�з���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���8λ����
//============================================================
TInt8 RInt8::Parse16(TChar16C* pSource){
   return RNumber<TInt8>::ParseSign<TChar16>(pSource);
}

//============================================================
// <T>����ʮ����32λ�ַ���Ϊ�з���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���8λ����
//============================================================
TInt8 RInt8::Parse32(TChar32C* pSource){
   return RNumber<TInt8>::ParseSign<TChar32>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�з���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @param defaultValue Ĭ��ֵ
// @return �з���8λ����
//============================================================
TInt8 RInt8::Parse(TCharC* pSource, TInt8 defaultValue){
   return RNumber<TInt8>::ParseSign<TChar>(pSource, defaultValue);
}

//============================================================
// <T>����10�����ַ�����</T>
//
// @param pSource ��Դ
// @return ����
//============================================================
TInt8 RInt8::ParseNvl(TCharC* pSource){
   if(NULL != pSource){
      return RNumber<TInt8>::ParseSign<TChar>(pSource, 0);
   }
   return 0;
}

//============================================================
// <T>����10�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TInt8 RInt8::Parse2(TCharC* pSource){
   MO_ASSERT(pSource);
   TInt8 v0 = (pSource[0] - '0') * 10;
   TInt8 v1 = (pSource[1] - '0');
   return v0 + v1;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TInt8 RInt8::ParseHex(TCharC* pSource, TInt length){
   MO_ASSERT(pSource);
   TInt8 v0 = ((TInt8)RByte::HEX_BYTES[(TInt)pSource[0]]) << 4;
   TInt8 v1 = ((TInt8)RByte::HEX_BYTES[(TInt)pSource[1]])     ;
   return v0 | v1;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TInt8 RInt8::ParseHexNvl(TCharC* pSource, TInt length){
   if(NULL != pSource){
      return ParseHex(pSource, length);
   }
   return 0;
}

//============================================================
// <T>��8λ������ʽ��Ϊ10�����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RInt8::ToString(TInt8 value, TChar* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   return RNumber<TInt8>::ToSignString<TChar, TUint8>(pBuffer, capacity, value);
}

//============================================================
// <T>��8λ������ʽ��Ϊ10����2�ֽڳ����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RInt8::ToString2(TInt8 value, TChar* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   MO_ASSERT(capacity >= 2);
   pBuffer[0] = (value / 10) + '0';
   pBuffer[1] = (value % 10) + '0';
   return pBuffer;
}

//============================================================
// <T>��8λ������ʽ��Ϊ16�����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RInt8::ToHexString(TInt8 value, TChar* pBuffer, TInt capacity){
   pBuffer[0] = RByte::HEX_CHARS[(value >> 4) & 0x0F];
   pBuffer[1] = RByte::HEX_CHARS[(value     ) & 0x0F];
   return pBuffer;
}

MO_NAMESPACE_END
