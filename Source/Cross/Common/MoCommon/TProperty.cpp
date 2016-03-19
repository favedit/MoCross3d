#include "MoCmProperty.h"

MO_NAMESPACE_BEGIN

//============================================================
TProperty::TProperty(){
   MO_CLEAR(_pInfo);
   MO_CLEAR(_pData);
   _modifyCd = EModify_None;
}

//============================================================
TProperty::TProperty(SPropertyInfo* pInfo){
   _pInfo = pInfo;
   MO_CLEAR(_pData);
   _modifyCd = EModify_None;
}

//============================================================
TProperty::TProperty(SPropertyInfo* pInfo, TAny* pValue){
   _pInfo = pInfo;
   _pData = pValue;
   _modifyCd = EModify_None;
}

//============================================================
TProperty::TProperty(SPropertyInfo* pInfo, EModify modifyCd, TAny* pValue){
   _pInfo = pInfo;
   _pData = pValue;
   _modifyCd = modifyCd;
}

//============================================================
TBool TProperty::Attach(TProperty& property){
   return ETrue;
}

//============================================================
TBool TProperty::Assign(const TProperty* pProperty){
   return ETrue;
}

//============================================================
TBool TProperty::Modify(const TProperty* pProperty, EPropertyModify modifyCd){
   return ETrue;
}

//============================================================
TBool TProperty::IsValid(){
   return (NULL != _pInfo);
}

//============================================================
SPropertyInfo* TProperty::Info(){
   return _pInfo;
}

//============================================================
void TProperty::SetInfo(SPropertyInfo* pInfo){
   _pInfo = pInfo;
}

//============================================================
TAnyC* TProperty::GetC(){
   return _pData;
}

//============================================================
TAny* TProperty::Get(){
   return _pData;
}

//============================================================
void TProperty::Set(TAny* pValue){
   _pData = pValue;
}

//============================================================
void TProperty::Set(SPropertyInfo* pInfo, TAny* pValue){
   _pInfo = pInfo;
   _pData = pValue;
}

//============================================================
// <T>������ת��Ϊ�������͡�</T>
//
// @return ת���������
//============================================================
TBool TProperty::AsBool(){
   TBool result = EFalse;
   if(NULL != _pInfo){
      //RTypeConverter::ToBool(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�з���8λ�������͡�</T>
//
// @return ת���������
//============================================================
TInt8 TProperty::AsInt8(){
   TInt8 result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToInt8(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�з���16λ�������͡�</T>
//
// @return ת���������
//============================================================
TInt16 TProperty::AsInt16(){
   TInt16 result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToInt16(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�з���32λ�������͡�</T>
//
// @return ת���������
//============================================================
TInt32 TProperty::AsInt32(){
   TInt32 result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToInt32(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�з���64λ�������͡�</T>
//
// @return ת���������
//============================================================
TInt64 TProperty::AsInt64(){
   TInt64 result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToInt64(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�޷���8λ�������͡�</T>
//
// @return ת���������
//============================================================
TUint8 TProperty::AsUint8(){
   TUint8 result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToUint8(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�޷���16λ�������͡�</T>
//
// @return ת���������
//============================================================
TUint16 TProperty::AsUint16(){
   TUint16 result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToUint16(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�޷���32λ�������͡�</T>
//
// @return ת���������
//============================================================
TUint32 TProperty::AsUint32(){
   TUint32 result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToUint32(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�޷���64λ�������͡�</T>
//
// @return ת���������
//============================================================
TUint64 TProperty::AsUint64(){
   TUint64 result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToUint64(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
TFloat TProperty::AsFloat(){
   TFloat result = 0;
   return result;
}

//============================================================
TDouble TProperty::AsDouble(){
   TDouble result = 0;
   return result;
}

//============================================================
// <T>������ת��Ϊ���� (32λ - ��)���͡�</T>
//
// @return ת���������
//============================================================
TDate TProperty::AsDate(){
   TDate result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToDate(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊʱ�� (32λ - ��)���͡�</T>
//
// @return ת���������
//============================================================
TTime TProperty::AsTime(){
   TTime result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToTime(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�̶� (32λ - ��)���͡�</T>
//
// @return ת���������
//============================================================
TTick TProperty::AsTick(){
   TTick result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToTick(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊʱ�� (32λ - ��)���͡�</T>
//
// @return ת���������
//============================================================
TSpan TProperty::AsSpan(){
   TSpan result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToSpan(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ����ʱ�� (64λ - ��)���͡�</T>
//
// @return ת���������
//============================================================
TDateTime TProperty::AsDateTime(){
   TDateTime result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToDateTime(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊʱ��̶� (64λ - ��)���͡�</T>
//
// @return ת���������
//============================================================
TTimeTick TProperty::AsTimeTick(){
   TTimeTick result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToTimeTick(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊʱ��� (64λ - ��)���͡�</T>
//
// @return ת���������
//============================================================
TTimeSpan TProperty::AsTimeSpan(){
   TTimeSpan result = 0;
   if(NULL != _pInfo){
      //RTypeConverter::ToTimeSpan(_pInfo->TypeCd(), _pData, result);
   }
   return result;
}

//============================================================
// <T>������ת��Ϊ�䳤�ַ�ָ�����͡�</T>
//
// @return ת���������
//============================================================
TCharC* TProperty::AsString(){
   TCharC** result = NULL;
   if(NULL != _pInfo){
      //RTypeConverter::ToString(_pInfo->TypeCd(), _pData, result);
   }
   return *result;
}

MO_NAMESPACE_END
