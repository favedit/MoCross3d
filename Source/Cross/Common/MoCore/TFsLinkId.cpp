#include "MoCrCommon.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������ַ�����</T>
//============================================================
TFsLinkId::TFsLinkId(){
}

//============================================================
// <T>�����������ַ�����</T>
//
// @param value ����
//============================================================
TFsLinkId::TFsLinkId(const SLinkId& value){
   _value = value;
}

//============================================================
// <T>���ַ���ת��Ϊ������š�</T>
//
// @param pValue �ַ���
// @param length ����
// @return �������
//============================================================
TLinkId TFsLinkId::Decode(TCharC* pValue, TInt length){
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
TCharC* TFsLinkId::Encode(TLinkId value, TChar* pBuffer, TInt capacity){
   RUint64::ToHexString(value.high, pBuffer, capacity);
   RUint64::ToHexString(value.lower, pBuffer + 16, capacity);
   pBuffer[32] = 0;
   return pBuffer;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsLinkId::operator=(const SLinkId& value){
   _value = value;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param pValue ����
//============================================================
void TFsLinkId::operator=(TCharC* pValue){
   this->Assign(pValue);
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsLinkId::operator=(const TStringPtrC& value){
   this->Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsLinkId::operator=(const TFsLinkId& value){
   this->Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>����������ݡ�</T>
//
// @return ����
//============================================================
SLinkId TFsLinkId::Value() const{
   return _value;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsLinkId::SetValue(SLinkId value){
   _value = value;
}

//============================================================
// <T>�������Ϊ�ַ�����</T>
//
// @return �ַ���
//============================================================
TCharC* TFsLinkId::Pack(){
   return Encode(_value, _pMemory, _capacity);
}

//============================================================
// <T>��ʽ��Ϊ�ַ�����</T>
//
// @return �ַ���
//============================================================
TCharC* TFsLinkId::Format(){
   SObjectData& objectId = _value.data.items.objectId;
   AssignFormat("%02X-%02X-%04X(%d):%X:%016X(%" MO_FMT_INT64 ")",
         objectId.items.type, objectId.items.group, objectId.items.index,
         _value.Handle(),
         _value.data.items.flag, _value.data.items.code, _value.data.items.code);
   return _pMemory;
}

MO_NAMESPACE_END
