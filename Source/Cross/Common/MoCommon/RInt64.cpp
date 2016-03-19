#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����Ƿ�Ϊ���֡�</T>
//
// @param pSource �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RInt64::Test(TCharC* pSource){
   return RNumber<TInt64>::IsSignInteger<TChar>(pSource);
}

//============================================================
// <T>����ʮ����8λ�ַ���Ϊ�з���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���64λ����
//============================================================
TInt64 RInt64::Parse8(TChar8C* pSource){
   return RNumber<TInt64>::ParseSign<TChar8>(pSource);
}

//============================================================
// <T>����ʮ����16λ�ַ���Ϊ�з���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���64λ����
//============================================================
TInt64 RInt64::Parse16(TChar16C* pSource){
   return RNumber<TInt64>::ParseSign<TChar16>(pSource);
}

//============================================================
// <T>����ʮ����32λ�ַ���Ϊ�з���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���64λ����
//============================================================
TInt64 RInt64::Parse32(TChar32C* pSource){
   return RNumber<TInt64>::ParseSign<TChar32>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�з���64λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���64λ����
//============================================================
TInt64 RInt64::Parse(TCharC* pSource){
   return RNumber<TInt64>::ParseSign<TChar>(pSource);
}

//============================================================
// <T>���ַ����任Ϊ��������</T>
//
// @param pValue �ַ���
// @return ������
//============================================================
TInt64 RInt64::ParseNvl(TCharC* pSource){
   if(NULL != pSource){
      return RNumber<TInt64>::ParseSign<TChar>(pSource, 0);
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
TInt64 RInt64::ParseHex(TCharC* pSource, TInt length){
   MO_ASSERT(pSource);
   TInt64 v0 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 0]]) << 60;
   TInt64 v1 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 1]]) << 56;
   TInt64 v2 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 2]]) << 52;
   TInt64 v3 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 3]]) << 48;
   TInt64 v4 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 4]]) << 44;
   TInt64 v5 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 5]]) << 40;
   TInt64 v6 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 6]]) << 36;
   TInt64 v7 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 7]]) << 32;
   TInt64 v8 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 8]]) << 28;
   TInt64 v9 = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[ 9]]) << 24;
   TInt64 va = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[10]]) << 20;
   TInt64 vb = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[11]]) << 16;
   TInt64 vc = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[12]]) << 12;
   TInt64 vd = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[13]]) <<  8;
   TInt64 ve = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[14]]) <<  4;
   TInt64 vf = ((TInt64)RByte::HEX_BYTES[(TInt)pSource[15]])      ;
   return v0 | v1 | v2 | v3 | v4 | v5 | v6 | v7 | v8 | v9 | va | vb | vc | vd | ve | vf;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TInt64 RInt64::ParseHexNvl(TCharC* pSource, TInt length){
   if(NULL != pSource){
      return ParseHex(pSource, length);
   }
   return 0;
}

//============================================================
// <T>���������任Ϊ8λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar8C* RInt64::ToString8(TInt64 value, TChar8* pBuffer, TInt capacity){
   return RNumber<TInt64>::ToSignString<TChar8, TUint64>(pBuffer, capacity, value);
}

//============================================================
// <T>���������任Ϊ16λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar16C* RInt64::ToString16(TInt64 value, TChar16* pBuffer, TInt capacity){
   return RNumber<TInt64>::ToSignString<TChar16, TUint64>(pBuffer, capacity, value);
}

//============================================================
// <T>���������任Ϊ32λ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar32C* RInt64::ToString32(TInt64 value, TChar32* pBuffer, TInt capacity){
   return RNumber<TInt64>::ToSignString<TChar32, TUint64>(pBuffer, capacity, value);
}

//============================================================
// <T>���������任Ϊ�ַ�����</T>
//
// @param value ������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TCharC* RInt64::ToString(TInt64 value, TChar* pBuffer, TInt capacity){
   return RNumber<TInt64>::ToSignString<TChar, TUint64>(pBuffer, capacity, value);
}

//============================================================
// <T>��64λ�з���������ʽ��Ϊ16�����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RInt64::ToHexString(TInt64 value, TChar* pBuffer, TInt capacity){
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
