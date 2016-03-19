#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����Ƿ�Ϊ���֡�</T>
//
// @param pSource �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RUint8::Test(TCharC* pSource){
   return RNumber<TUint8>::IsUnsignInteger<TChar>(pSource);
}

//============================================================
// <T>����ʮ����8λ�ַ���Ϊ�޷���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���8λ����
//============================================================
TUint8 RUint8::Parse8(TChar8C* pSource){
   return RNumber<TUint8>::ParseUnsign<TChar8>(pSource);
}

//============================================================
// <T>����ʮ����16λ�ַ���Ϊ�޷���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���8λ����
//============================================================
TUint8 RUint8::Parse16(TChar16C* pSource){
   return RNumber<TUint8>::ParseUnsign<TChar16>(pSource);
}

//============================================================
// <T>����ʮ����32λ�ַ���Ϊ�޷���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���8λ����
//============================================================
TUint8 RUint8::Parse32(TChar32C* pSource){
   return RNumber<TUint8>::ParseUnsign<TChar32>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�޷���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���8λ����
//============================================================
TUint8 RUint8::Parse(TCharC* pSource){
   return RNumber<TUint8>::ParseUnsign<TChar>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�޷���8λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���8λ����
//============================================================
TUint8 RUint8::ParseNvl(TCharC* pSource){
   if(NULL != pSource){
      return RNumber<TUint8>::ParseUnsign<TChar>(pSource, 0);
   }
   return 0;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TUint8 RUint8::ParseHex(TCharC* pSource, TInt length){
   MO_ASSERT(pSource);
   TUint8 v0 = ((TUint8)RByte::HEX_BYTES[(TInt)pSource[0]]) << 4;
   TUint8 v1 = ((TUint8)RByte::HEX_BYTES[(TInt)pSource[1]])     ;
   return v0 | v1;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TUint8 RUint8::ParseHexNvl(TCharC* pSource, TInt length){
   if(NULL != pSource){
      return ParseHex(pSource, length);
   }
   return 0;
}

//============================================================
TCharC* RUint8::ToString(TUint8 value, TChar* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   return RNumber<TUint8>::ToUnsignString<TChar>(pBuffer, capacity, value);
}

//============================================================
// <T>��8λ�޷���������ʽ��Ϊ16�����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RUint8::ToHexString(TUint8 value, TChar* pBuffer, TInt capacity){
   pBuffer[0] = RByte::HEX_CHARS[(value >>  4) & 0x0F];
   pBuffer[1] = RByte::HEX_CHARS[(value      ) & 0x0F];
   return pBuffer;
}

MO_NAMESPACE_END
