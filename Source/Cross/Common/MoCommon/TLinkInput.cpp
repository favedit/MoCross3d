#include "MoCmStream.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������������</T>
//============================================================
TLinkInput::TLinkInput(TAny* pInputData, TInt inputLength){
   _pMemory = (TByte*)pInputData;
   _length = inputLength;
   _position = 0;
}

//============================================================
// <T>�����ڴ档</T>
//============================================================
void TLinkInput::Link(TAny* pInputData, TInt inputLength){
   _pMemory = (TByte*)pInputData;
   _length = inputLength;
   _position = 0;
}

//============================================================
// <T>��õ�ǰλ�á�</T>
//
// @return ��ǰλ��
//============================================================
TInt TLinkInput::Position(){
   return _position;
}

//============================================================
// <T>��ó��ȡ�</T>
//
// @return ����
//============================================================
TInt TLinkInput::Length(){
   return _length;
}

//============================================================
// <T>����ڴ�ָ�롣</T>
//
// @return �ڴ�ָ��
//============================================================
TByteC* TLinkInput::MemoryC(){
   return _pMemory;
}

//============================================================
// <T>����ڴ�ָ�롣</T>
//
// @return �ڴ�ָ��
//============================================================
TByte* TLinkInput::Memory(){
   return _pMemory;
}

//============================================================
// <T>��õ�ǰλ�õ��ڴ�ָ�롣</T>
//
// @return �ڴ�ָ��
//============================================================
TByte* TLinkInput::PositionMemory(){
   return (_pMemory + _position);
}

//============================================================
// <T>����λ���ƶ�һ��λ�á�</T>
//
// @param length ����
//============================================================
void TLinkInput::Skip(TInt length){
   _position += length;
}

//============================================================
// <T>��ȡ���ݡ�</T>
//
// @param pData ����
// @param length ����
// @return ��ȡ����
//============================================================
TInt TLinkInput::Read(TAny* pData, TInt length){
   TByte* pMemory = (TByte*)(_pMemory + _position);
   MO_LIB_MEMORY_COPY(pData, length, pMemory, length);
   _position += length;
   return length;
}

//============================================================
// <T>�����ַ������ȡ�</T>
//
// @return ����
//============================================================
TInt TLinkInput::TestStringLength(){
   return *(TUint16*)(_pMemory + _position);
}

//============================================================
// <T>���ֽ����ж�ȡһ������ֵ��</T>
// <P>ռ��һ���ֽڣ�Ϊ1��ʾ�棬Ϊ0��ʾ�١�</P>
//
// @return ����ֵ
//============================================================
TBool TLinkInput::ReadBool(){
   TByte value = *(TByte*)(_pMemory + _position);
   _position += sizeof(TByte);
   return (value > 0);
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���������</T>
//
// @return �з�������
//============================================================
TInt TLinkInput::ReadInt(){
   TInt value = *(TInt*)(_pMemory + _position);
   _position += sizeof(TInt);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���8λ������</T>
//
// @return �з���8λ����
//============================================================
TInt8 TLinkInput::ReadInt8(){
   TInt8 value = *(TInt8*)(_pMemory + _position);
   _position += sizeof(TInt8);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���16λ������</T>
//
// @return �з���16λ����
//============================================================
TInt16 TLinkInput::ReadInt16(){
   TInt16 value = *(TInt16*)(_pMemory + _position);
   _position += sizeof(TInt16);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���32λ������</T>
//
// @return �з���32λ����
//============================================================
TInt32 TLinkInput::ReadInt32(){
   TInt32 value = *(TInt32*)(_pMemory + _position);
   _position += sizeof(TInt32);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���64λ������</T>
//
// @return �з���64λ����
//============================================================
TInt64 TLinkInput::ReadInt64(){
   TInt64 value = *(TInt64*)(_pMemory + _position);
   _position += sizeof(TInt64);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���������</T>
//
// @return �޷�������
//============================================================
TUint TLinkInput::ReadUint(){
   TUint value = *(TUint*)(_pMemory + _position);
   _position += sizeof(TUint);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���8λ������</T>
//
// @return �޷���8λ����
//============================================================
TUint8 TLinkInput::ReadUint8(){
   TUint8 value = *(TUint8*)(_pMemory + _position);
   _position += sizeof(TUint8);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���16λ������</T>
//
// @return �޷���16λ����
//============================================================
TUint16 TLinkInput::ReadUint16(){
   TUint16 value = *(TUint16*)(_pMemory + _position);
   _position += sizeof(TUint16);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���32λ������</T>
//
// @return �޷���32λ����
//============================================================
TUint32 TLinkInput::ReadUint32(){
   TUint32 value = *(TUint32*)(_pMemory + _position);
   _position += sizeof(TUint32);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���64λ������</T>
//
// @param p:value �޷���64λ����
// @return �޷���64λ����
//============================================================
TUint64 TLinkInput::ReadUint64(){
   TUint64 value = *(TUint64*)(_pMemory + _position);
   _position += sizeof(TUint64);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ��32λ��������</T>
//
// @return 32λ������
//============================================================
TFloat TLinkInput::ReadFloat(){
   TFloat value = *(TFloat*)(_pMemory + _position);
   _position += sizeof(TFloat);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ��64λ��������</T>
//
// @return 64λ������
//============================================================
TDouble TLinkInput::ReadDouble(){
   TDouble value = *(TDouble*)(_pMemory + _position);
   _position += sizeof(TDouble);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ��8λ�ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt TLinkInput::ReadString8(TChar8* pValue, TInt capacity){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   if(length > 0){
      memcpy(pValue, _pMemory + _position + sizeof(TUint16), sizeof(TChar8) * length);
   }
   pValue[length] = 0;
   _position += sizeof(TUint16) + sizeof(TChar8) * length;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��16λ�ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt TLinkInput::ReadString16(TChar16* pValue, TInt capacity){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   if(length > 0){
      memcpy(pValue, _pMemory + _position + sizeof(TUint16), sizeof(TChar16) * length);
   }
   pValue[length] = 0;
   _position += sizeof(TUint16) + sizeof(TChar16) * length;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��32λ�ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt TLinkInput::ReadString32(TChar32* pValue, TInt capacity){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   if(length > 0){
      memcpy(pValue, _pMemory + _position + sizeof(TUint16), sizeof(TChar32) * length);
   }
   pValue[length] = 0;
   _position += sizeof(TUint16) + sizeof(TChar32) * length;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt TLinkInput::ReadString(TChar* pValue, TInt capacity){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   if(length > 0){
      memcpy(pValue, _pMemory + _position + sizeof(TUint16), sizeof(TChar) * length);
   }
   pValue[length] = 0;
   _position += sizeof(TUint16) + sizeof(TChar) * length;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��8λ�ַ�����</T>
//
// @return �ַ���
//============================================================
TString8 TLinkInput::ReadString8(){
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
TString16 TLinkInput::ReadString16(){
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
TString32 TLinkInput::ReadString32(){
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
TString TLinkInput::ReadString(){
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

//============================================================
// <T>���ô���</T>
//============================================================
void TLinkInput::Reset(){
   _position = 0;
}

MO_NAMESPACE_END
