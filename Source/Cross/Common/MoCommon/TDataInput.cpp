#include "MoCmStream.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������������ʵ����</T>
//
// @return ʵ��ָ��
//============================================================
TDataInput::TDataInput(){
   _pInput = NULL;
}

//============================================================
// <T>����������������ʵ����</T>
//
// @param pInput ����ӿ�
//============================================================
TDataInput::TDataInput(IInput* pInput){
   _pInput = pInput;
}

//============================================================
// <T>����������������ʵ����</T>
//============================================================
TDataInput::~TDataInput(){
}

//============================================================
// <T>�������ӿڡ�</T>
//
// @return ����ӿ�
//============================================================
IInput* TDataInput::Input(){
   return _pInput;
}

//============================================================
// <T>��������ӿڡ�</T>
//
// @param pInput ����ӿ�
//============================================================
void TDataInput::SetInput(IInput* pInput){
   _pInput = pInput;
}

//============================================================
// <T>��ȡ����</T>
//
// @return ���ض�ȡ����
//============================================================
TInt TDataInput::Read(TAny* pData, TInt size){
   return _pInput->Read(pData, size);
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���������</T>
//
// @return �з�������
//============================================================
TInt TDataInput::ReadInt(){
   TInt value;
   _pInput->Read(&value, sizeof(TInt));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ������ֵ��</T>
// <P>ռ��һ���ֽڣ�Ϊ1��ʾ�棬Ϊ0��ʾ�١�</P>
//
// @return ����ֵ
//============================================================
TBool TDataInput::ReadBool(){
   TByte value = 0;
   _pInput->Read(&value, sizeof(TByte));
   return (value > 0) ? ETrue : EFalse;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���8λ������</T>
//
// @return �з���8λ����
//============================================================
TInt8 TDataInput::ReadInt8(){
   TInt8 value;
   _pInput->Read(&value, sizeof(TInt8));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���16λ������</T>
//
// @return �з���16λ����
//============================================================
TInt16 TDataInput::ReadInt16(){
   TInt16 value;
   _pInput->Read(&value, sizeof(TInt16));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���32λ������</T>
//
// @return �з���32λ����
//============================================================
TInt32 TDataInput::ReadInt32(){
   TInt32 value;
   _pInput->Read(&value, sizeof(TInt32));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���64λ������</T>
//
// @return �з���64λ����
//============================================================
TInt64 TDataInput::ReadInt64(){
   TInt64 value;
   _pInput->Read(&value, sizeof(TInt64));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���������</T>
//
// @return �޷�������
//============================================================
TUint TDataInput::ReadUint(){
   TUint value;
   _pInput->Read(&value, sizeof(TUint));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���8λ������</T>
//
// @return �޷���8λ����
//============================================================
TUint8 TDataInput::ReadUint8(){
   TUint8 value;
   _pInput->Read(&value, sizeof(TUint8));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���16λ������</T>
//
// @return �޷���16λ����
//============================================================
TUint16 TDataInput::ReadUint16(){
   TUint16 value;
   _pInput->Read(&value, sizeof(TUint16));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���32λ������</T>
//
// @return �޷���32λ����
//============================================================
TUint32 TDataInput::ReadUint32(){
   TUint32 value;
   _pInput->Read(&value, sizeof(TUint32));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���64λ������</T>
//
// @param p:value �޷���64λ����
// @return �޷���64λ����
//============================================================
TUint64 TDataInput::ReadUint64(){
   TUint64 value;
   _pInput->Read(&value, sizeof(TUint64));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ��32λ��������</T>
//
// @return 32λ������
//============================================================
TFloat TDataInput::ReadFloat(){
   TFloat value;
   _pInput->Read(&value, sizeof(TFloat));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ��64λ��������</T>
//
// @return 64λ������
//============================================================
TDouble TDataInput::ReadDouble(){
   TDouble value;
   _pInput->Read(&value, sizeof(TDouble));
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ��8λ�ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt TDataInput::ReadString8(TChar8* pValue, TInt capacity){
   TUint16 length;
   _pInput->Read(&length, sizeof(TUint16));
   if(length > 0){
      MO_ASSERT(length <= capacity);
      _pInput->Read(pValue, sizeof(TChar8) * length);
   }
   pValue[length] = 0;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��16λ�ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt TDataInput::ReadString16(TChar16* pValue, TInt capacity){
   TUint16 length;
   _pInput->Read(&length, sizeof(TUint16));
   if(length > 0){
      MO_ASSERT(length < capacity);
      _pInput->Read(pValue, sizeof(TChar16) * length);
   }
   pValue[length] = 0;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��32λ�ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt TDataInput::ReadString32(TChar32* pValue, TInt capacity){
   TUint16 length;
   _pInput->Read(&length, sizeof(TUint16));
   if(length > 0){
      MO_ASSERT(length < capacity);
      _pInput->Read(pValue, sizeof(TChar32) * length);
   }
   pValue[length] = 0;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt TDataInput::ReadString(TChar* pValue, TInt capacity){
   TUint16 length;
   _pInput->Read(&length, sizeof(TUint16));
   if(length > 0){
      MO_ASSERT(length < capacity);
      _pInput->Read(pValue, sizeof(TChar) * length);
   }
   pValue[length] = 0;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��8λ�ַ�����</T>
//
// @return �ַ���
//============================================================
TString8 TDataInput::ReadString8(){
   TString8 result;
   TUint16 length;
   Read(&length, sizeof(TUint16));
   if(length > 0){
      result.EnsureSize(length + 1);
      Read(result.Memory(), sizeof(TChar8) * length);
      result.SetLength(length);
   }
   return result;
}

//============================================================
// <T>���ֽ����ж�ȡһ��16λ�ַ�����</T>
//
// @return �ַ���
//============================================================
TString16 TDataInput::ReadString16(){
   TString16 result;
   TUint16 length;
   Read(&length, sizeof(TUint16));
   if(length > 0){
      result.EnsureSize(length + 1);
      Read(result.Memory(), sizeof(TChar16) * length);
      result.SetLength(length);
   }
   return result;
}

//============================================================
// <T>���ֽ����ж�ȡһ��32λ�ַ�����</T>
//
// @return �ַ���
//============================================================
TString32 TDataInput::ReadString32(){
   TString32 result;
   TUint16 length;
   Read(&length, sizeof(TUint16));
   if(length > 0){
      result.EnsureSize(length + 1);
      Read(result.Memory(), sizeof(TChar32) * length);
      result.SetLength(length);
   }
   return result;
}

//============================================================
// <T>���ֽ����ж�ȡһ���ַ�����</T>
//
// @return �ַ���
//============================================================
TString TDataInput::ReadString(){
   TString result;
   TUint16 length;
   Read(&length, sizeof(TUint16));
   if(length > 0){
      result.EnsureSize(length + 1);
      Read(result.Memory(), sizeof(TChar) * length);
      result.SetLength(length);
   }
   return result;
}

MO_NAMESPACE_END
