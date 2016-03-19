#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����Ƿ�Ϊ���֡�</T>
//
// @param pSource �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RInt16::Test(TCharC* pSource){
   return RNumber<TInt16>::IsSignInteger<TChar>(pSource);
}

//============================================================
// <T>����ʮ����8λ�ַ���Ϊ�з���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���16λ����
//============================================================
TInt16 RInt16::Parse8(TChar8C* pSource){
   return RNumber<TInt16>::ParseSign<TChar8>(pSource);
}

//============================================================
// <T>����ʮ����16λ�ַ���Ϊ�з���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���16λ����
//============================================================
TInt16 RInt16::Parse16(TChar16C* pSource){
   return RNumber<TInt16>::ParseSign<TChar16>(pSource);
}

//============================================================
// <T>����ʮ����32λ�ַ���Ϊ�з���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���16λ����
//============================================================
TInt16 RInt16::Parse32(TChar32C* pSource){
   return RNumber<TInt16>::ParseSign<TChar32>(pSource);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�з���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @param defaultValue Ĭ������
// @return �з���16λ����
//============================================================
TInt16 RInt16::Parse(TCharC* pSource, TInt16 defaultValue){
   return RNumber<TInt16>::ParseSign<TChar>(pSource, defaultValue);
}

//============================================================
// <T>����ʮ�����ַ���Ϊ�з���16λ������</T>
//
// @param pSource ʮ�����ַ���
// @return �з���16λ����
//============================================================
TInt16 RInt16::ParseNvl(TCharC* pSource){
   if(NULL != pSource){
      return RNumber<TInt16>::ParseSign<TChar>(pSource, 0);
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
TInt16 RInt16::ParseHex(TCharC* pSource, TInt length){
   MO_ASSERT(pSource);
   TInt16 v0 = ((TInt16)RByte::HEX_BYTES[(TInt)pSource[0]]) << 12;
   TInt16 v1 = ((TInt16)RByte::HEX_BYTES[(TInt)pSource[1]]) <<  8;
   TInt16 v2 = ((TInt16)RByte::HEX_BYTES[(TInt)pSource[2]]) <<  4;
   TInt16 v3 = ((TInt16)RByte::HEX_BYTES[(TInt)pSource[3]])      ;
   return v0 | v1 | v2 | v3;
}

//============================================================
// <T>����16�����ַ�����</T>
//
// @param pSource ��Դ
// @param length ����
// @return ����
//============================================================
TInt16 RInt16::ParseHexNvl(TCharC* pSource, TInt length){
   if(NULL != pSource){
      return ParseHex(pSource, length);
   }
   return 0;
}

//============================================================
// <T>16λ���������������ࡣ</T>
//============================================================
TCharC* RInt16::ToString(TInt16 value, TChar* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   return RNumber<TInt16>::ToSignString<TChar, TUint16>(pBuffer, capacity, value);
}

//============================================================
// <T>��16λ������ʽ��Ϊ16�����ַ�����</T>
//
// @param value ����
// @param pBuffer �ַ�������
// @param capacity �ַ�������
//============================================================
TCharC* RInt16::ToHexString(TInt16 value, TChar* pBuffer, TInt capacity){
   pBuffer[0] = RByte::HEX_CHARS[(value >> 12) & 0x0F];
   pBuffer[1] = RByte::HEX_CHARS[(value >>  8) & 0x0F];
   pBuffer[2] = RByte::HEX_CHARS[(value >>  4) & 0x0F];
   pBuffer[3] = RByte::HEX_CHARS[(value      ) & 0x0F];
   return pBuffer;
}

MO_NAMESPACE_END
