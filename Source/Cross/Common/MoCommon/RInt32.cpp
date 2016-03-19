#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����Ƿ�Ϊ���֡�</T>
//
// @param pValue �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RInt32::Test(TCharC* pValue){
   return RNumber<TInt32>::IsSignInteger<TChar>(pValue);
}

//============================================================
// <T>����ʮ����8λ�ַ���Ϊ�з���32λ������</T>
//
// @param pValue ʮ�����ַ���
// @return �з���32λ����
//============================================================
TInt32 RInt32::Parse8(TChar8C* pValue){
   return RNumber<TInt32>::ParseSign<TChar8>(pValue);
}

//============================================================
// <T>����ʮ����16λ�ַ���Ϊ�з���32λ������</T>
//
// @param pValue ʮ�����ַ���
// @return �з���32λ����
//============================================================
TInt32 RInt32::Parse16(TChar16C* pValue){
   return RNumber<TInt32>::ParseSign<TChar16>(pValue);
}

//============================================================
// <T>����ʮ����32λ�ַ���Ϊ�з���32λ������</T>
//
// @param pValue ʮ�����ַ���
// @return �з���32λ����
//============================================================
TInt32 RInt32::Parse32(TChar32C* pValue){
   return RNumber<TInt32>::ParseSign<TChar32>(pValue);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�з���32λ������</T>
//
// @param pValue ʮ�����ַ���
// @return �з���32λ����
//============================================================
TInt32 RInt32::Parse(TCharC* pValue){
   return RNumber<TInt32>::ParseSign<TChar>(pValue);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�з���32λ������</T>
//
// @param pValue ʮ�����ַ���
// @return �з���32λ����
//============================================================
TInt32 RInt32::ParseNvl(TCharC* pSource){
   if(NULL != pSource){
      return RNumber<TInt32>::ParseSign<TChar>(pSource, 0);
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
TInt32 RInt32::ParseHex(TCharC* pSource, TInt length){
   MO_ASSERT(pSource);
   TInt32 v0 = ((TInt32)RByte::HEX_BYTES[(TInt)pSource[0]]) << 28;
   TInt32 v1 = ((TInt32)RByte::HEX_BYTES[(TInt)pSource[1]]) << 24;
   TInt32 v2 = ((TInt32)RByte::HEX_BYTES[(TInt)pSource[2]]) << 20;
   TInt32 v3 = ((TInt32)RByte::HEX_BYTES[(TInt)pSource[3]]) << 16;
   TInt32 v4 = ((TInt32)RByte::HEX_BYTES[(TInt)pSource[4]]) << 12;
   TInt32 v5 = ((TInt32)RByte::HEX_BYTES[(TInt)pSource[5]]) <<  8;
   TInt32 v6 = ((TInt32)RByte::HEX_BYTES[(TInt)pSource[6]]) <<  4;
   TInt32 v7 = ((TInt32)RByte::HEX_BYTES[(TInt)pSource[7]])      ;
   return v0 | v1 | v2 | v3 | v4 | v5 | v6 | v7;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TInt32 RInt32::ParseHexNvl(TCharC* pSource, TInt length){
   if(NULL != pSource){
      return ParseHex(pSource, length);
   }
   return 0;
}

//============================================================
// <T>���з���32λ����������ʮ�����ַ�����</T>
//
// @param pBuffer �����ַ���
// @param capacity �����ַ�������
// @param value �з���32λ����
// @return ʮ�����ַ���    
//============================================================
TCharC* RInt32::ToString(TInt32 value, TChar* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   return RNumber<TInt32>::ToSignString<TChar, TUint32>(pBuffer, capacity, value);
}

//============================================================
// <T>��32λ������ʽ��Ϊ16�����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RInt32::ToHexString(TInt32 value, TChar* pBuffer, TInt capacity){
   pBuffer[0] = RByte::HEX_CHARS[(value >> 28) & 0x0F];
   pBuffer[1] = RByte::HEX_CHARS[(value >> 24) & 0x0F];
   pBuffer[2] = RByte::HEX_CHARS[(value >> 20) & 0x0F];
   pBuffer[3] = RByte::HEX_CHARS[(value >> 16) & 0x0F];
   pBuffer[4] = RByte::HEX_CHARS[(value >> 12) & 0x0F];
   pBuffer[5] = RByte::HEX_CHARS[(value >>  8) & 0x0F];
   pBuffer[6] = RByte::HEX_CHARS[(value >>  4) & 0x0F];
   pBuffer[7] = RByte::HEX_CHARS[(value      ) & 0x0F];
   return pBuffer;
}

MO_NAMESPACE_END
