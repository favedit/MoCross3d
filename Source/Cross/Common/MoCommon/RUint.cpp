#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж������Ƿ��ڷ�Χ�С�</T>
//
// @param value ����
// @param min ��Сֵ
// @param max ���ֵ
// @return �Ƿ��ڷ�Χ��
//============================================================
TUint RUint::InRange(TUint value, TUint min, TUint max){
   if(value < min){
      return min;
   }
   if(value >= max){
      return max - 1;
   }
   return value;
}

//============================================================
// <T>�ж������Ƿ��ڷ�Χ�С�</T>
//
// @param value ����
// @param min ��Сֵ
// @param max ���ֵ
// @return �Ƿ��ڷ�Χ��
//============================================================
TUint RUint::InBetween(TUint value, TUint min, TUint max){
   if(value < min){
      return min;
   }
   if(value > max){
      return max;
   }
   return value;
}

//============================================================
// <T>��8λ�ַ����任Ϊ�޷�������,�ַ�����ʱ�������⡣</T>
//
// @param pValue �ַ���
// @return �޷�������
//============================================================
TUint RUint::Parse8(TChar8C* pValue){
   return RNumber<TUint>::ParseUnsign<TChar8>(pValue);
}

//============================================================
// <T>��16λ�ַ����任Ϊ�޷�������,�ַ�����ʱ�������⡣</T>
//
// @param pValue �ַ���
// @return �޷�������
//============================================================
TUint RUint::Parse16(TChar16C* pValue){
   return RNumber<TUint>::ParseUnsign<TChar16>(pValue);
}

//============================================================
// <T>��32λ�ַ����任Ϊ�޷�������,�ַ�����ʱ�������⡣</T>
//
// @param pValue �ַ���
// @return �޷�������
//============================================================
TUint RUint::Parse32(TChar32C* pValue){
   return RNumber<TUint>::ParseUnsign<TChar32>(pValue);
}

//============================================================
// <T>���ַ����任Ϊ�޷�������,�ַ�����ʱ�������⡣</T>
//
// @param pValue �ַ���
// @return �޷�������
//============================================================
TUint RUint::Parse(TCharC* pValue){
   return RNumber<TUint>::ParseUnsign<TChar>(pValue);
}

//============================================================
// <T>���ַ����任Ϊ�޷���������</T>
//
// @param pValue �ַ���
// @return �޷�������
//============================================================
TUint RUint::ParseNvl(TCharC* pValue){
   return RNumber<TUint>::ParseUnsign<TChar>(pValue, 0);
}

//============================================================
// <T>���޷��������任Ϊ8λ�ַ�����</T>
//
// @param value �޷�������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar8C* RUint::ToString8(TUint value, TChar8* pBuffer, TInt capacity){
   return RNumber<TUint>::ToUnsignString<TChar8>(pBuffer, capacity, value);
}

//============================================================
// <T>���޷��������任Ϊ16λ�ַ�����</T>
//
// @param value �޷�������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar16C* RUint::ToString16(TUint value, TChar16* pBuffer, TInt capacity){
   return RNumber<TUint>::ToUnsignString<TChar16>(pBuffer, capacity, value);
}

//============================================================
// <T>���޷��������任Ϊ32λ�ַ�����</T>
//
// @param value �޷�������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TChar32C* RUint::ToString32(TUint value, TChar32* pBuffer, TInt capacity){
   return RNumber<TUint>::ToUnsignString<TChar32>(pBuffer, capacity, value);
}

//============================================================
// <T>���޷��������任Ϊ�ַ�����</T>
//
// @param value �޷�������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TCharC* RUint::ToString(TUint value, TChar* pBuffer, TInt capacity){
   return RNumber<TUint>::ToUnsignString<TChar>(pBuffer, capacity, value);
}

//============================================================
// <T>���޷��������任Ϊ16�����ַ�����</T>
//
// @param value �޷�������
// @param pBuffer ������
// @param capacity ����������
// @return �ַ���
//============================================================
TCharC* RUint::ToHexString(TUint value, TChar* pBuffer, TInt capacity){
   MO_ASSERT(pBuffer);
   TInt n = -1;
   TChar* pResult = pBuffer;
   do{
      // ѭ��ת��ÿһ�����֣�ֱ������
      pResult[++n] = RByte::HEX_CHARS[value % 16];
      value /= 16;
   }while(value > 0);
   // ת���������ַ����Ƿ��ģ������һ��ĳ���
   TInt position = (n + 1) / 2;
   while(position-- > 0){
      // ���ַ������ַ���ת
      TChar temp = pResult[position];
      pResult[position] = pResult[n - position];
      pResult[n - position] = temp;
   }
   // �ý�����
   pResult[n + 1] = '\0';
   return pBuffer;
}

MO_NAMESPACE_END

