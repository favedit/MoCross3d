#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����Ƿ�Ϊ���֡�</T>
//
// @param pSource �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RUint16::Test(TCharC* pSource){
   return RNumber<TUint16>::IsUnsignInteger<TChar>(pSource);
}

//============================================================
// <T>����ʮ����8λ�ַ���Ϊ�޷���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���16λ����
//============================================================
TUint16 RUint16::Parse8(TChar8C* pSource){
   return RNumber<TUint16>::ParseUnsign<TChar8>(pSource);
}

//============================================================
// <T>����ʮ����16λ�ַ���Ϊ�޷���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���16λ����
//============================================================
TUint16 RUint16::Parse16(TChar16C* pSource){
   return RNumber<TUint16>::ParseUnsign<TChar16>(pSource);
}

//============================================================
// <T>����ʮ����32λ�ַ���Ϊ�޷���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���16λ����
//============================================================
TUint16 RUint16::Parse32(TChar32C* pSource){
   return RNumber<TUint16>::ParseUnsign<TChar32>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�޷���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���16λ����
//============================================================
TUint16 RUint16::Parse(TCharC* pSource){
   return RNumber<TUint16>::ParseUnsign<TChar>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�޷���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �޷���16λ����
//============================================================
TUint16 RUint16::ParseNvl(TCharC* pSource, TUint16 defaultValue){
   if(NULL != pSource){
      return RNumber<TUint16>::ParseSign<TChar>(pSource, 0);
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
TUint16 RUint16::ParseHex(TCharC* pSource, TInt length){
   MO_ASSERT(pSource);
   TUint16 v0 = ((TUint16)RByte::HEX_BYTES[(TInt)pSource[0]]) << 12;
   TUint16 v1 = ((TUint16)RByte::HEX_BYTES[(TInt)pSource[1]]) <<  8;
   TUint16 v2 = ((TUint16)RByte::HEX_BYTES[(TInt)pSource[2]]) <<  4;
   TUint16 v3 = ((TUint16)RByte::HEX_BYTES[(TInt)pSource[3]])      ;
   return v0 | v1 | v2 | v3;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TUint16 RUint16::ParseHexNvl(TCharC* pSource, TInt length){
   if(NULL != pSource){
      return ParseHex(pSource, length);
   }
   return 0;
}

//============================================================
// <T>���޷���16λ����������ʮ�����ַ�����</T>
//
// @param pBuffer �����ַ���
// @param capacity �����ַ�������
// @param value �޷���16λ����
// @return ʮ�����ַ���    
//============================================================
TCharC* RUint16::ToString(TUint16 value, TChar* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   return RNumber<TUint16>::ToUnsignString<TChar>(pBuffer, capacity, value);
}

//============================================================
// <T>��16λ�޷���������ʽ��Ϊ16�����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RUint16::ToHexString(TUint16 value, TChar* pBuffer, TInt capacity){
   pBuffer[0] = RByte::HEX_CHARS[(value >> 12) & 0x0F];
   pBuffer[1] = RByte::HEX_CHARS[(value >>  8) & 0x0F];
   pBuffer[2] = RByte::HEX_CHARS[(value >>  4) & 0x0F];
   pBuffer[3] = RByte::HEX_CHARS[(value      ) & 0x0F];
   return pBuffer;
}

MO_NAMESPACE_END
