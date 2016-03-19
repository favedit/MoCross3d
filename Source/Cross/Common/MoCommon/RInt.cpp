#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ����ǲ������֡�</T>
//
// @param pValue �ַ���
// @return �Ƿ�Ϊ����
//============================================================
TBool RInt::IsInteger(TCharC* pValue){
   TInt length = RString::Length(pValue);
   for(TInt n = 0; n < length; n++){
      TChar value = pValue[n];
      if((('-' == value) || ('+' == value)) && (0 == n)){
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
TInt RInt::InRange(TInt value, TInt min, TInt max){
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
TInt RInt::InBetween(TInt value, TInt min, TInt max){
   if(value < min){
      return min;
   }
   if(value > max){
      return max;
   }
   return value;
}

//============================================================
// <T>��8λ�ַ����任Ϊ������</T>
//
// @param pValue �ַ���
// @return ����
//============================================================
TInt RInt::Parse8(TChar8C* pValue){
   return RNumber<TInt>::ParseSign<TChar8>(pValue);
}

//============================================================
// <T>��16λ�ַ����任Ϊ������</T>
//
// @param pValue �ַ���
// @return ����
//============================================================
TInt RInt::Parse16(TChar16C* pValue){
   return RNumber<TInt>::ParseSign<TChar16>(pValue);
}

//============================================================
// <T>��32λ�ַ����任Ϊ������</T>
//
// @param pValue �ַ���
// @return ����
//============================================================
TInt RInt::Parse32(TChar32C* pValue){
   return RNumber<TInt>::ParseSign<TChar32>(pValue);
}

//============================================================
// <T>���ַ����任Ϊ������</T>
//
// @param pValue �ַ���
// @return ����
//============================================================
TInt RInt::Parse(TCharC* pValue){
   return RNumber<TInt>::ParseSign<TChar>(pValue);
}

//============================================================
// <T>���ַ����任Ϊ������</T>
//
// @param pValue �ַ���
// @return ����
//============================================================
TInt RInt::ParseNvl(TCharC* pValue){
   return RNumber<TInt>::ParseSign<TChar>(pValue, 0);
}

//============================================================
// <T>�����ָ�ʽ��Ϊ8λ�ַ�����</T>
//
// @param value ����
// @param pBuffer ����ַ���
// @param capacity �������
// @return ����ַ���
//============================================================
TChar8C* RInt::ToString8(TInt value, TChar8* pBuffer, TInt capacity){
   return RNumber<TInt>::ToSignString<TChar8, TUint>(pBuffer, capacity, value);
}

//============================================================
// <T>�����ָ�ʽ��Ϊ16λ�ַ�����</T>
//
// @param value ����
// @param pBuffer ����ַ���
// @param capacity �������
// @return ����ַ���
//============================================================
TChar16C* RInt::ToString16(TInt value, TChar16* pBuffer, TInt capacity){
   return RNumber<TInt>::ToSignString<TChar16, TUint>(pBuffer, capacity, value);
}

//============================================================
// <T>�����ָ�ʽ��Ϊ32λ�ַ�����</T>
//
// @param value ����
// @param pBuffer ����ַ���
// @param capacity �������
// @return ����ַ���
//============================================================
TChar32C* RInt::ToString32(TInt value, TChar32* pBuffer, TInt capacity){
   return RNumber<TInt>::ToSignString<TChar32, TUint>(pBuffer, capacity, value);
}

//============================================================
// <T>�����ָ�ʽ��Ϊ�ַ�����</T>
//
// @param value ����
// @param pBuffer ����ַ���
// @param capacity �������
// @return ����ַ���
//============================================================
TCharC* RInt::ToString(TInt value, TChar* pBuffer, TInt capacity){
   return RNumber<TInt>::ToSignString<TChar, TUint>(pBuffer, capacity, value);
}

//============================================================
// <T>�����ָ�ʽ��Ϊ16�����ַ�����</T>
//
// @param value ����
// @param pBuffer ����ַ���
// @param capacity �������
// @return ����ַ���
//============================================================
TCharC* RInt::ToHexString(TInt value, TChar* pBuffer, TInt capacity){
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
   pResult[n + 1] = 0;
   return pBuffer;
}

//============================================================
// <T>��ʽ��Ϊ�ڴ��С��</T>
//
// @param size �ߴ�
// @param pBuffer ����ַ���
// @param capacity �������
// @return ����ַ���
//============================================================
TCharC* RInt::FormatCapacity(TInt64 size, TChar* pBuffer, TInt capacity){
   TFsCode format;
   // ��ʽ������
   TInt gBytes = (TInt)(size >> 30);
   if(gBytes > 0){
      format.AppendFormat(TC("%2dG."), gBytes);
   }
   TInt mBytes = (TInt)(size >> 20) % 1024;
   if(gBytes || mBytes){
      if(gBytes){
         format.AppendFormat(TC("%04dM."), mBytes);
      }else{
         format.AppendFormat(TC("%4dM."), mBytes);
      }
   }
   TInt kBytes = (TInt)(size >> 10) % 1024;
   if(gBytes || mBytes || kBytes){
      if(gBytes || mBytes){
         format.AppendFormat(TC("%04dK."), kBytes);
      }else{
         format.AppendFormat(TC("%4dK."), kBytes);
      }
   }
   if(gBytes || mBytes || kBytes){
      format.AppendFormat(TC("%04dB"), size % 1024);
   }else{
      format.AppendFormat(TC("%4dB"), size % 1024);
   }
   // ��������
   TInt copied = MO_LIB_MIN(format.Length() + 1, capacity - 1);
   memcpy(pBuffer, (TCharC*)format, copied);
   return pBuffer;
}

//============================================================
// <T>����һ�������ж���λ��</T>
//
// @param value ����
// @return λ��
//============================================================
TInt RInt::CountDigit(TInt value){
   TInt result = 0;
   while(value){
      ++result;
      value /= 10;
   }
   return result;
}
MO_NAMESPACE_END

