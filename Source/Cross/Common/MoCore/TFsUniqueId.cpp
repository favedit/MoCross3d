#include "MoCrCommon.h"

MO_NAMESPACE_BEGIN

//============================================================
TFsUniqueId::TFsUniqueId(){
}

//============================================================
TFsUniqueId::TFsUniqueId(const SUniqueId& value){
   _value = value;
}

//============================================================
// <T>���ַ���ת��Ϊ������š�</T>
//
// @param pValue �ַ���
// @param length ����
// @return �������
//============================================================
TUniqueId TFsUniqueId::Decode(TCharC* pValue, TInt length){
   TLinkId value;
   value.high = RUint64::ParseHex(pValue, 16);
   value.lower = RUint64::ParseHex(pValue + 16, 16);
   return value;
}

//============================================================
// <T>���������ת��Ϊ�ַ�����</T>
//
// @param value �������
// @param pBuffer �ַ�������
// @param capacity �ַ�������
// @return �ַ���
//============================================================
TCharC* TFsUniqueId::Encode(TUniqueId value, TChar* pBuffer, TInt capacity){
   RUint64::ToHexString(value.high, pBuffer, capacity);
   RUint64::ToHexString(value.lower, pBuffer + 16, capacity);
   pBuffer[32] = 0;
   return pBuffer;
}

//============================================================
void TFsUniqueId::operator=(const SUniqueId& value){
   _value = value;
}

//============================================================
void TFsUniqueId::operator=(TCharC* pValue){
   this->Assign(pValue);
}

//============================================================
void TFsUniqueId::operator=(const TFsUniqueId& value){
   this->Assign(value.MemoryC(), value.Length());
}

//============================================================
void TFsUniqueId::operator=(const TStringPtrC& value){
   this->Assign(value.MemoryC(), value.Length());
}

//============================================================
SUniqueId TFsUniqueId::Value() const{
   return _value;
}

//============================================================
void TFsUniqueId::SetValue(SUniqueId value){
   _value = value;
}

//============================================================
// <T>�������Ϊ�ַ�����</T>
//
// @return �ַ���
//============================================================
TCharC* TFsUniqueId::Pack(){
   return Encode(_value, _pMemory, _capacity);
}

//============================================================
TCharC* TFsUniqueId::Format(){
   this->AssignFormat(TC("%02X:%02X-%02X:%02X %02X-%02X-%04X"),
         _value.data.items.groupId.items.groupType, _value.data.items.groupId.items.groupId,
         _value.data.items.groupId.items.itemType, _value.data.items.groupId.items.itemId,
         _value.data.items.objectId.items.type, _value.data.items.objectId.items.group,
         _value.data.items.objectId.items.index);
   return this->MemoryC();
}

MO_NAMESPACE_END
