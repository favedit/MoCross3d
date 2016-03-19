#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����Ƿ�Ϊ���֡�</T>
//
// @param pSource �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RUint64::Test(TCharC* pSource){
   return RNumber<TUint64>::IsUnsignInteger<TChar>(pSource);
}

//============================================================
// <T>����ʮ����8λ�ַ���Ϊ�޷���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���64λ����
//============================================================
TUint64 RUint64::Parse8(TChar8C* pSource){
   return RNumber<TUint64>::ParseUnsign<TChar8>(pSource);
}

//============================================================
// <T>����ʮ����16λ�ַ���Ϊ�޷���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���64λ����
//============================================================
TUint64 RUint64::Parse16(TChar16C* pSource){
   return RNumber<TUint64>::ParseUnsign<TChar16>(pSource);
}

//============================================================
// <T>����ʮ����32λ�ַ���Ϊ�޷���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���64λ����
//============================================================
TUint64 RUint64::Parse32(TChar32C* pSource){
   return RNumber<TUint64>::ParseUnsign<TChar32>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�޷���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���64λ����
//============================================================
TUint64 RUint64::Parse(TCharC* pSource){
   return RNumber<TUint64>::ParseUnsign<TChar>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�޷���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���64λ����
//============================================================
TUint64 RUint64::ParseNvl(TCharC* pSource){
   if(NULL != pSource){
      return RNumber<TUint64>::ParseUnsign<TChar>(pSource, 0);
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
TUint64 RUint64::ParseHex(TCharC* pSource, TInt length){
   MO_ASSERT(pSource);
   TUint64 v0 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 0]]) << 60;
   TUint64 v1 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 1]]) << 56;
   TUint64 v2 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 2]]) << 52;
   TUint64 v3 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 3]]) << 48;
   TUint64 v4 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 4]]) << 44;
   TUint64 v5 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 5]]) << 40;
   TUint64 v6 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 6]]) << 36;
   TUint64 v7 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 7]]) << 32;
   TUint64 v8 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 8]]) << 28;
   TUint64 v9 = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[ 9]]) << 24;
   TUint64 va = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[10]]) << 20;
   TUint64 vb = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[11]]) << 16;
   TUint64 vc = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[12]]) << 12;
   TUint64 vd = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[13]]) <<  8;
   TUint64 ve = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[14]]) <<  4;
   TUint64 vf = ((TUint64)RByte::HEX_BYTES[(TInt)pSource[15]])      ;
   return v0 | v1 | v2 | v3 | v4 | v5 | v6 | v7 | v8 | v9 | va | vb | vc | vd | ve | vf;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TUint64 RUint64::ParseHexNvl(TCharC* pSource, TInt length){
   if(NULL != pSource){
      return ParseHex(pSource, length);
   }
   return 0;
}

//============================================================
// <T>���Ǹ��������任Ϊ8λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar8C* RUint64::ToString8(TUint64 value, TChar8* pBuffer, TInt capacity){
   return RNumber<TUint64>::ToUnsignString<TChar8>(pBuffer, capacity, value);
}

//============================================================
// <T>���Ǹ��������任Ϊ16λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar16C* RUint64::ToString16(TUint64 value, TChar16* pBuffer, TInt capacity){
   return RNumber<TUint64>::ToUnsignString<TChar16>(pBuffer, capacity, value);
}

//============================================================
// <T>���Ǹ��������任Ϊ32λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar32C* RUint64::ToString32(TUint64 value, TChar32* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   return RNumber<TUint64>::ToUnsignString<TChar32>(pBuffer, capacity, value);
}

//============================================================
// <T>���Ǹ��������任Ϊ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TCharC* RUint64::ToString(TUint64 value, TChar* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   return RNumber<TUint64>::ToUnsignString<TChar>(pBuffer, capacity, value);
}

//============================================================
// <T>��64λ�޷���������ʽ��Ϊ16�����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RUint64::ToHexString(TUint64 value, TChar* pBuffer, TInt capacity){
   pBuffer[ 0] = RByte::HEX_CHARS[(value >> 60) & 0x0F];
   pBuffer[ 1] = RByte::HEX_CHARS[(value >> 56) & 0x0F];
   pBuffer[ 2] = RByte::HEX_CHARS[(value >> 52) & 0x0F];
   pBuffer[ 3] = RByte::HEX_CHARS[(value >> 48) & 0x0F];
   pBuffer[ 4] = RByte::HEX_CHARS[(value >> 44) & 0x0F];
   pBuffer[ 5] = RByte::HEX_CHARS[(value >> 40) & 0x0F];
   pBuffer[ 6] = RByte::HEX_CHARS[(value >> 36) & 0x0F];
   pBuffer[ 7] = RByte::HEX_CHARS[(value >> 32) & 0x0F];
   pBuffer[ 8] = RByte::HEX_CHARS[(value >> 28) & 0x0F];
   pBuffer[ 9] = RByte::HEX_CHARS[(value >> 24) & 0x0F];
   pBuffer[10] = RByte::HEX_CHARS[(value >> 20) & 0x0F];
   pBuffer[11] = RByte::HEX_CHARS[(value >> 16) & 0x0F];
   pBuffer[12] = RByte::HEX_CHARS[(value >> 12) & 0x0F];
   pBuffer[13] = RByte::HEX_CHARS[(value >>  8) & 0x0F];
   pBuffer[14] = RByte::HEX_CHARS[(value >>  4) & 0x0F];
   pBuffer[15] = RByte::HEX_CHARS[(value      ) & 0x0F];
   return pBuffer;
}

MO_NAMESPACE_END
