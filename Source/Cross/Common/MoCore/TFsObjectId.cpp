#include "MoCrCommon.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������ַ�����</T>
//============================================================
TFsObjectId::TFsObjectId(){
}

//============================================================
// <T>����������ַ�����</T>
//
// @param value ����
//============================================================
TFsObjectId::TFsObjectId(const SObjectId& value){
   _value = value;
}

//============================================================
// <T>���ַ���ת��Ϊ�����š�</T>
//
// @param pValue �ַ���
// @param length ����
// @return ������
//============================================================
TObjectId TFsObjectId::Decode(TCharC* pValue, TInt length){
   return RUint32::ParseHex(pValue, length);
}

//============================================================
// <T>��������ת��Ϊ�ַ�����</T>
//
// @param value ������
// @param pBuffer �ַ�������
// @param capacity �ַ�������
// @return �ַ���
//============================================================
TCharC* TFsObjectId::Encode(TObjectId value, TChar* pBuffer, TInt capacity){
   RUint32::ToHexString(value, pBuffer, capacity);
   pBuffer[8] = 0;
   return pBuffer;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsObjectId::operator=(const SObjectId& value){
   _value = value;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsObjectId::operator=(TCharC* pValue){
   this->Assign(pValue);
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsObjectId::operator=(const TStringPtrC& value){
   this->Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsObjectId::operator=(const TFsObjectId& value){
   this->Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>����������ݡ�</T>
//
// @return ����
//============================================================
SObjectId TFsObjectId::Value() const{
   return _value;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void TFsObjectId::SetValue(SObjectId value){
   _value = value;
}

//============================================================
// <T>�������Ϊ�ַ�����</T>
//
// @return �ַ���
//============================================================
TCharC* TFsObjectId::Pack(){
   return Encode(_value, _pMemory, _capacity);
}

//============================================================
// <T>��ʽ��Ϊ�ַ�����</T>
//
// @return �ַ���
//============================================================
TCharC* TFsObjectId::Format(){
   AssignFormat(TC("%02X-%02X-%04X(%d)"),
         _value.data.items.type, _value.data.items.group, _value.data.items.index,
         _value.Handle());
   return MemoryC();
}

MO_NAMESPACE_END
