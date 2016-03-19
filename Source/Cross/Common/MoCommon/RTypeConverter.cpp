#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ת��Ϊ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToBool(EType typeCd, TAny* pValue, TBool& value){
   MO_ASSERT(pValue);
   switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         value = *(TBool*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 result = *(TInt8*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 result = *(TInt16*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 result = *(TInt32*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 result = *(TInt64*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt result = *(TInt*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 result = *(TUint8*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 result = *(TUint16*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 result = *(TUint32*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 result = *(TUint64*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint result = *(TUint*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat result = *(TFloat*)pValue;
         value = (0.0f == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble result = *(TDouble*)pValue;
         value = (0.0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime result = *(TDateTime*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick result = *(TTimeTick*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan result = *(TTimeSpan*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 result = *(TChar8*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 result = *(TChar16*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 result = *(TChar32*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar result = *(TChar*)pValue;
         value = (0 == result)?EFalse:ETrue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RBool::IsTrue(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�з���8λ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToInt8(EType typeCd, TAny* pValue, TInt8& value){
    MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         value = *(TInt8*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TInt8)tempValue;         
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TInt8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RInt8::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�з���16λ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToInt16(EType typeCd, TAny* pValue, TInt16& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         value = *(TInt16*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TInt16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RInt16::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�з���32λ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToInt32(EType typeCd, TAny* pValue, TInt32& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TInt32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RInt32::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�з���64λ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToInt64(EType typeCd, TAny* pValue, TInt64& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         value = *(TInt64*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TInt64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RInt64::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�޷���8λ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToUint8(EType typeCd, TAny* pValue, TUint8& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         value = *(TUint8*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TUint8)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RUint8::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�޷���16λ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToUint16(EType typeCd, TAny* pValue, TUint16& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         value = *(TUint16*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TUint16)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RUint16::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�޷���32λ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToUint32(EType typeCd, TAny* pValue, TUint32& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         value = *(TUint32*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TUint32)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RUint32::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�޷���64λ�������͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToUint64(EType typeCd, TAny* pValue, TUint64& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         value = *(TUint64*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TUint64)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RUint64::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
TBool RTypeConverter::ToFloat(EType typeCd, TAny* pValue, TFloat& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result ? 1.0f : 0.0f;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         value = *(TFloat*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TFloat)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RFloat::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
TBool RTypeConverter::ToDouble(EType typeCd, TAny* pValue, TDouble& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         value = *(TDouble*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TDouble)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RDouble::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ���� (32λ - ��)���͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToDate(EType typeCd, TAny* pValue, TDate& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TDate)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊʱ�� (32λ - ��)���͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToTime(EType typeCd, TAny* pValue, TTime& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�̶� (32λ - ��)���͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToTick(EType typeCd, TAny* pValue, TTick& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         //TCharC* result = (TCharC*)pValue;
//         value = RTick::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊʱ�� (32λ - ��)���͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToSpan(EType typeCd, TAny* pValue, TSpan& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         //TCharC* result = (TCharC*)pValue;
//         TSpan = RSpan::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ����ʱ�� (64λ - ��)���͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToDateTime(EType typeCd, TAny* pValue, TDateTime& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         value = *(TDateTime*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TDateTime)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         value = RDateTime::Parse(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊʱ��̶� (64λ - ��)���͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToTimeTick(EType typeCd, TAny* pValue, TTimeTick& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         value = *(TTimeTick*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         TTimeSpan tempValue = *(TTimeSpan*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TTimeTick)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         //TCharC* result = (TCharC*)pValue;
//         value = RTimeTick::(result);
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊʱ��� (64λ - ��)���͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToTimeSpan(EType typeCd, TAny* pValue, TTimeSpan& value){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Bool:{
         TBool result = *(TBool*)pValue;
         value = result?ETrue:EFalse;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         TInt8 tempValue = *(TInt8*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         TInt16 tempValue = *(TInt16*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         TInt32 tempValue = *(TInt32*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         TInt64 tempValue = *(TInt64*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         TUint8 tempValue = *(TUint8*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         TUint16 tempValue = *(TUint16*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         TUint32 tempValue = *(TUint32*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         TUint64 tempValue = *(TUint64*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
         TFloat tempValue = *(TFloat*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
         TDouble tempValue = *(TDouble*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         TDateTime tempValue = *(TDateTime*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         TTimeTick tempValue = *(TTimeTick*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         value = *(TTimeSpan*)pValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         TChar8 tempValue = *(TChar8*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         TChar16 tempValue = *(TChar16*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         TChar32 tempValue = *(TChar32*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         TChar tempValue = *(TChar*)pValue;
         value = (TTimeSpan)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         //TCharC* result = (TCharC*)pValue;
//         value = RTimeSpan::
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
// <T>��������ת��Ϊ�䳤�ַ�ָ�����͡�</T>
//
// @param typeCd ����ö��
// @param pValue ����ָ��
// @param value ����ֵ
// @return ������
//============================================================
TBool RTypeConverter::ToString(EType typeCd, TAny* pValue, TCharC** ppValue){
   MO_ASSERT(pValue);
    switch(typeCd){
      // �ж��Ƿ�Ϊ�������ͣ���ת��
//      case EType_Bool:{
//         TBool result = *(TBool*)pValue;
//         **ppValue = result?ETrue:EFalse;
//         return ETrue;
//      }
      // �ж��Ƿ�Ϊ�з���8λ�������ͣ���ת��
      case EType_Int8:{
         //TInt8 tempValue = *(TInt8*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���16λ�������ͣ���ת��
      case EType_Int16:{
         //TInt16 tempValue = *(TInt16*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���32λ�������ͣ���ת��
      case EType_Int32:{
         //TInt32 tempValue = *(TInt32*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�з���64λ�������ͣ���ת��
      case EType_Int64:{
         //TInt64 tempValue = *(TInt64*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�з����������ͣ���ת��
      case EType_Int:{
         TInt tempValue = *(TInt*)pValue;
         *ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���8λ�������ͣ���ת��
      case EType_Uint8:{
         //TUint8 tempValue = *(TUint8*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���16λ�������ͣ���ת��
      case EType_Uint16:{
         //TUint16 tempValue = *(TUint16*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���32λ�������ͣ���ת��
      case EType_Uint32:{
         //TUint32 tempValue = *(TUint32*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�޷���64λ�������ͣ���ת��
      case EType_Uint64:{
         //TUint64 tempValue = *(TUint64*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�޷����������ͣ���ת��
      case EType_Uint:{
         TUint tempValue = *(TUint*)pValue;
         *ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�����ȸ����� (32λ)���ͣ���ת��
      case EType_Float:{
//         TFloat tempValue = *(TFloat*)pValue;
//         *ppValue = (TCharC*)tempValue;
//         return ETrue;
      }
      // �ж��Ƿ�Ϊ˫���ȸ����� (64λ)���ͣ���ת��
      case EType_Double:{
//         TDouble tempValue = *(TDouble*)pValue;
//         *ppValue = (TCharC*)tempValue;
//         return ETrue;
      }
      // �ж��Ƿ�Ϊ����ʱ�� (64λ - ΢��)���ͣ���ת��
      case EType_DateTime:{
         //TDateTime tempValue = *(TDateTime*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��̶� (64λ - ΢��)���ͣ���ת��
      case EType_TimeTick:{
         //TTimeTick tempValue = *(TTimeTick*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊʱ��� (64λ - ΢��)���ͣ���ת��
      case EType_TimeSpan:{
         //TTimeSpan tempValue = *(TTimeSpan*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ8λ�ַ����ͣ���ת��
      case EType_Char8:{
         //TChar8 tempValue = *(TChar8*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ16λ�ַ����ͣ���ת��
      case EType_Char16:{
         //TChar16 tempValue = *(TChar16*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ32λ�ַ����ͣ���ת��
      case EType_Char32:{
         //TChar32 tempValue = *(TChar32*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ����ͣ���ת��
      case EType_Char:{
         //TChar tempValue = *(TChar*)pValue;
         //*ppValue = (TCharC*)tempValue;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�䳤�ַ�ָ�����ͣ���ת��
      case EType_String:{
         TCharC* result = (TCharC*)pValue;
         *ppValue = (TCharC*)result;
         return ETrue;
      }
      // �ж��Ƿ�Ϊ�ṹ���ͣ���ת��
      case EType_Struct:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ�������ͣ���ת��
      case EType_Object:{
         return EFalse;
      }
      // �ж��Ƿ�Ϊ����ָ�����ͣ���ת��
      case EType_Ptr:{
         return EFalse;
      }
      // δ����
      default:
         break;
   }
   return EFalse;
}

//============================================================
TBool RTypeConverter::Convert(EType sourceTypeCd, TAny* pSource, EType targetTypeCd, TAny** ppTarget){
   return ETrue;
}

MO_NAMESPACE_END
