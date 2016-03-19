#include "MoCmFile.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���������</T>
//============================================================
FByteString::FByteString(){
   _position = 0;
}

//============================================================
// <T>�����ַ���������</T>
//============================================================
FByteString::~FByteString(){
}

//============================================================
// <T>���λ�á�</T>
//
// @return λ��
//============================================================
TInt FByteString::Position(){
   return _position;
}

//============================================================
// <T>����λ�á�</T>
//
// @param position λ��
//============================================================
void FByteString::SetPosition(TInt position){
   MO_ASSERT(position < _length);
   _position = position;
}

//============================================================
// <T>���λ���ڴ档</T>
//
// @return λ���ڴ�
//============================================================
TByte* FByteString::PositionMemory(){
   return _pMemory + _position;
}

//============================================================
// <T>����ָ�����ȵ��ڴ档</T>
//
// @param length ����
//============================================================
void FByteString::Skip(TInt length){
   MO_ASSERT(_position + length <= _length);
   _position += length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��ָ�����ȵ����ݡ�</T>
//
// @param pData �ֽ�����
// @param length ���ݳ���
// @return ��ȡ����
//============================================================
TInt FByteString::Read(TChar* pData, TInt capacity){
   MO_ASSERT(_position + capacity <= _length);
   TChar* pMemory = (TChar*)(_pMemory + _position);
   MO_LIB_MEMORY_COPY(pData, sizeof(TChar) * capacity, pMemory, sizeof(TChar) * capacity);
   _position += capacity;
   return capacity;
}

//============================================================
// <T>���ֽ����ж�ȡһ������ֵ��</T>
// <P>ռ��һ���ֽڣ�Ϊ1��ʾ�棬Ϊ0��ʾ�١�</P>
//
// @return ����ֵ
//============================================================
TBool FByteString::ReadBool(){
   MO_ASSERT(_position + (TInt)sizeof(TByte) <= _length);
   TByte value = *(TByte*)(_pMemory + _position);
   _position += sizeof(TByte);
   return (value > 0);
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���������</T>
//
// @return �з�������
//============================================================
TInt FByteString::ReadInt(){
   MO_ASSERT(_position + (TInt)sizeof(TInt) <= _length);
   TInt value = *(TInt*)(_pMemory + _position);
   _position += sizeof(TInt);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���8λ������</T>
//
// @return �з���8λ����
//============================================================
TInt8 FByteString::ReadInt8(){
   MO_ASSERT(_position + (TInt)sizeof(TInt8) <= _length);
   TInt8 value = *(TInt8*)(_pMemory + _position);
   _position += sizeof(TInt8);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���16λ������</T>
//
// @return �з���16λ����
//============================================================
TInt16 FByteString::ReadInt16(){
   MO_ASSERT(_position + (TInt)sizeof(TInt16) <= _length);
   TInt16 value = *(TInt16*)(_pMemory + _position);
   _position += sizeof(TInt16);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���32λ������</T>
//
// @return �з���32λ����
//============================================================
TInt32 FByteString::ReadInt32(){
   MO_ASSERT(_position + (TInt)sizeof(TInt32) <= _length);
   TInt32 value = *(TInt32*)(_pMemory + _position);
   _position += sizeof(TInt32);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���з���64λ������</T>
//
// @return �з���64λ����
//============================================================
TInt64 FByteString::ReadInt64(){
   MO_ASSERT(_position + (TInt)sizeof(TInt64) <= _length);
   TInt64 value = *(TInt64*)(_pMemory + _position);
   _position += sizeof(TInt64);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���������</T>
//
// @return �޷�������
//============================================================
TUint FByteString::ReadUint(){
   MO_ASSERT(_position + (TInt)sizeof(TUint) <= _length);
   TUint value = *(TUint*)(_pMemory + _position);
   _position += sizeof(TUint);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���8λ������</T>
//
// @return �޷���8λ����
//============================================================
TUint8 FByteString::ReadUint8(){
   MO_ASSERT(_position + (TInt)sizeof(TUint8) <= _length);
   TUint8 value = *(TUint8*)(_pMemory + _position);
   _position += sizeof(TUint8);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���16λ������</T>
//
// @return �޷���16λ����
//============================================================
TUint16 FByteString::ReadUint16(){
   MO_ASSERT(_position + (TInt)sizeof(TUint16) <= _length);
   TUint16 value = *(TUint16*)(_pMemory + _position);
   _position += sizeof(TUint16);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ���޷���32λ������</T>
//
// @return �޷���32λ����
//============================================================
TUint32 FByteString::ReadUint32(){
   MO_ASSERT(_position + (TInt)sizeof(TUint32) <= _length);
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
TUint64 FByteString::ReadUint64(){
   MO_ASSERT(_position + (TInt)sizeof(TUint64) <= _length);
   TUint64 value = *(TUint64*)(_pMemory + _position);
   _position += sizeof(TUint64);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ��32λ��������</T>
//
// @return 32λ������
//============================================================
TFloat FByteString::ReadFloat(){
   MO_ASSERT(_position + (TInt)sizeof(TFloat) <= _length);
   TFloat value = *(TFloat*)(_pMemory + _position);
   _position += sizeof(TFloat);
   return value;
}

//============================================================
// <T>���ֽ����ж�ȡһ��64λ��������</T>
//
// @return 64λ������
//============================================================
TDouble FByteString::ReadDouble(){
   MO_ASSERT(_position + (TInt)sizeof(TDouble) <= _length);
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
TInt FByteString::ReadString8(TChar8* pValue, TInt capacity){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   MO_ASSERT(_position + (TInt)sizeof(TUint16) + length <= _length);
   if(length > 0){
      MO_LIB_MEMORY_COPY(pValue, capacity, _pMemory + _position + sizeof(TUint16), length);
   }
   pValue[length] = 0;
   _position += sizeof(TUint16) + length;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��16λ�ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt FByteString::ReadString16(TChar16* pValue, TInt capacity){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   TInt byteLength = sizeof(TChar16) * length;
   MO_ASSERT(_position + (TInt)sizeof(TUint16) + byteLength <= _length);
   if(length > 0){
      MO_LIB_MEMORY_COPY(pValue, capacity, _pMemory + _position + sizeof(TUint16), byteLength);
   }
   pValue[length] = 0;
   _position += sizeof(TUint16) + byteLength;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��32λ�ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt FByteString::ReadString32(TChar32* pValue, TInt capacity){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   TInt byteLength = sizeof(TChar32) * length;
   MO_ASSERT(_position + (TInt)sizeof(TUint16) + byteLength <= _length);
   if(length > 0){
      MO_LIB_MEMORY_COPY(pValue, capacity, _pMemory + _position + sizeof(TUint16), byteLength);
   }
   pValue[length] = 0;
   _position += sizeof(TUint16) + byteLength;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ����
// @return ��ȡ����
//============================================================
TInt FByteString::ReadString(TChar* pValue, TInt capacity){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   TInt byteLength = sizeof(TChar) * length;
   MO_ASSERT(_position + (TInt)sizeof(TUint16) + byteLength <= _length);
   if(length > 0){
      MO_LIB_MEMORY_COPY(pValue, capacity, _pMemory + _position + sizeof(TUint16), byteLength);
   }
   pValue[length] = 0;
   _position += sizeof(TUint16) + byteLength;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ��8λ�ַ�����</T>
//
// @return �ַ���
//============================================================
TString8 FByteString::ReadString8(){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   MO_ASSERT(_position + (TInt)sizeof(TUint16) + length <= _length);
   TString8 result;
   if(length > 0){
      result.ForceSize(length + 1);
      MO_LIB_MEMORY_COPY(result.Memory(), length, _pMemory + _position + sizeof(TUint16), length);
      result.SetLength(length);
   }
   _position += sizeof(TUint16) + length;
   return result;
}

//============================================================
// <T>���ֽ����ж�ȡһ��16λ�ַ�����</T>
//
// @return �ַ���
//============================================================
TString16 FByteString::ReadString16(){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   TInt byteLength = sizeof(TChar16) * length;
   MO_ASSERT(_position + (TInt)sizeof(TUint16) + byteLength <= _length);
   TString16 result;
   if(length > 0){
      result.ForceSize(length + 1);
      MO_LIB_MEMORY_COPY(result.Memory(), byteLength, _pMemory + _position + sizeof(TUint16), byteLength);
      result.SetLength(length);
   }
   _position += sizeof(TUint16) + byteLength;
   return result;
}

//============================================================
// <T>���ֽ����ж�ȡһ��32λ�ַ�����</T>
//
// @return �ַ���
//============================================================
TString32 FByteString::ReadString32(){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   TInt byteLength = sizeof(TChar32) * length;
   MO_ASSERT(_position + (TInt)sizeof(TUint16) + byteLength <= _length);
   TString32 result;
   if(length > 0){
      result.ForceSize(length + 1);
      MO_LIB_MEMORY_COPY(result.Memory(), byteLength, _pMemory + _position + sizeof(TUint16), byteLength);
      result.SetLength(length);
   }
   _position += sizeof(TUint16) + byteLength;
   return result;
}

//============================================================
// <T>���ֽ����ж�ȡһ���ַ�����</T>
//
// @return �ַ���
//============================================================
TString FByteString::ReadString(){
   TUint16 length = *(TUint16*)(_pMemory + _position);
   TInt byteLength = sizeof(TChar) * length;
   MO_ASSERT(_position + (TInt)sizeof(TUint16) + byteLength <= _length);
   TString result;
   if(length > 0){
      result.ForceSize(length + 1);
      MO_LIB_MEMORY_COPY(result.Memory(), byteLength, _pMemory + _position + sizeof(TUint16), byteLength);
      result.SetLength(length);
   }
   _position += sizeof(TUint16) + byteLength;
   return result;
}

//============================================================
TInt FByteString::ReadLine8(TChar8* pValue, TInt capacity){
   return 0;
}

//============================================================
TInt FByteString::ReadLine16(TChar16* pValue, TInt capacity){
   return 0;
}

//============================================================
TInt FByteString::ReadLine32(TChar32* pValue, TInt capacity){
   return 0;
}

//============================================================
TInt FByteString::ReadLine(TChar* pValue, TInt capacity){
   TCharC* pData = (TCharC*)(_pMemory + _position);
   TInt length = RChars::IndexOf(pData, capacity - 1, '\n');
   if(length > 0){
      MO_LIB_MEMORY_COPY(pValue, sizeof(TChar) * capacity, pData, sizeof(TChar) * length);
      if(pValue[length - 1] == '\r'){
         pValue[--length] = 0;
      }else{
         pValue[length] = 0;
      }
   }
   return length;
}

//============================================================
TInt FByteString::ReadLine(MString* pValue){
   MO_CHECK(pValue, return ENull);
   TChar* pData = pValue->Memory();
   TInt dataSize = pValue->Capacity();
   TCharC* pReader = (TCharC*)(_pMemory + _position);
   TInt length = RChars::IndexOf(pReader, dataSize, '\n');
   if(length > 0){
      // ����λ��
      _position += length + 1;
      // ��ȡ����
      MO_LIB_MEMORY_COPY(pData, sizeof(TChar) * dataSize, pReader, sizeof(TChar) * length);
      if(pData[length - 1] == '\r'){
         pValue->SetLength(--length);
      }else{
         pValue->SetLength(length);
      }
   }
   return length;
}

//============================================================
// <T>���ֽ�����д��һ���з���������</T>
//
// @param pData �ֽ�����
// @param length ���ݳ���
// @return д�볤��
//============================================================
TInt FByteString::Write(TCharC* pData, TInt length){
   MO_CHECK(pData, return -1);
   if(length == -1){
      length = RChars::Length(pData);
   }
   EnsureSize(_position + length);
   TByte* pMemory = (TByte*)(_pMemory + _position);
   MO_LIB_MEMORY_COPY(pMemory, sizeof(TChar) * _capacity, pData, sizeof(TChar) * length);
   _position += length;
   // ��������
   if(_position > _length){
      _length = _position;
   }
   return length;
}

//============================================================
// <T>���ֽ�����д���ֽ����ݡ�</T>
//
// @param pData �ֽ�����
// @param length ���ݳ���
// @return д�볤��
//============================================================
TInt FByteString::WriteBytes(TAny* pData, TInt length){
   EnsureSize(_position + length);
   TByte* pMemory = (TByte*)(_pMemory + _position);
   MO_LIB_MEMORY_COPY(pMemory, _capacity - _position, pData, length);
   _position += length;
   // ��������
   if(_position > _length){
      _length = _position;
   }
   return length;
}

//============================================================
// <T>���ֽ�����д��һ������ֵ��</T>
// <P>ռ��һ���ֽڣ�Ϊ1��ʾ�棬Ϊ0��ʾ�١�</P>
//
// @param value ����ֵ
//============================================================
void FByteString::WriteBool(TBool value){
   EnsureSize(_position + sizeof(TByte));
   *(TByte*)(_pMemory + _position) = value ? 1 : 0;
   _position += sizeof(TByte);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���з���������</T>
//
// @param value �з�������
//============================================================
void FByteString::WriteInt(TInt value){
   EnsureSize(_position + sizeof(TInt));
   *(TInt*)(_pMemory + _position) = value;
   _position += sizeof(TInt);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���з���8λ������</T>
//
// @param value �з���8λ����
//============================================================
void FByteString::WriteInt8(TInt8 value){
   EnsureSize(_position + sizeof(TInt8));
   *(TInt8*)(_pMemory + _position) = value;
   _position += sizeof(TInt8);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���з���16λ������</T>
//
// @param value �з���16λ����
//============================================================
void FByteString::WriteInt16(TInt16 value){
   EnsureSize(_position + sizeof(TInt16));
   *(TInt16*)(_pMemory + _position) = value;
   _position += sizeof(TInt16);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���з���32λ������</T>
//
// @param value �з���32λ����
//============================================================
void FByteString::WriteInt32(TInt32 value){
   EnsureSize(_position + sizeof(TInt32));
   *(TInt32*)(_pMemory + _position) = value;
   _position += sizeof(TInt32);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���з���64λ������</T>
//
// @param value �з���64λ����
//============================================================
void FByteString::WriteInt64(TInt64 value){
   EnsureSize(_position + sizeof(TInt64));
   *(TInt64*)(_pMemory + _position) = value;
   _position += sizeof(TInt64);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���޷���������</T>
//
// @param value �޷�������
//============================================================
void FByteString::WriteUint(TUint value){
   EnsureSize(_position + sizeof(TUint));
   *(TUint*)(_pMemory + _position) = value;
   _position += sizeof(TUint);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���޷���8λ������</T>
//
// @param value �޷���8λ����
//============================================================
void FByteString::WriteUint8(TUint8 value){
   EnsureSize(_position + sizeof(TUint8));
   *(TUint8*)(_pMemory + _position) = value;
   _position += sizeof(TUint8);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���޷���16λ������</T>
//
// @param value �޷���16λ����
//============================================================
void FByteString::WriteUint16(TUint16 value){
   EnsureSize(_position + sizeof(TUint16));
   *(TUint16*)(_pMemory + _position) = value;
   _position += sizeof(TUint16);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���޷���32λ������</T>
//
// @param value �޷���32λ����
//============================================================
void FByteString::WriteUint32(TUint32 value){
   EnsureSize(_position + sizeof(TUint32));
   *(TUint32*)(_pMemory + _position) = value;
   _position += sizeof(TUint32);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���޷���64λ������</T>
//
// @param value �޷���64λ����
//============================================================
void FByteString::WriteUint64(TUint64 value){
   EnsureSize(_position + sizeof(TUint64));
   *(TUint64*)(_pMemory + _position) = value;
   _position += sizeof(TUint64);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ��32λ��������</T>
//
// @param value 32λ������
//============================================================
void FByteString::WriteFloat(TFloat value){
   EnsureSize(_position + sizeof(TFloat));
   *(TFloat*)(_pMemory + _position) = value;
   _position += sizeof(TFloat);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ��64λ��������</T>
//
// @param value 64λ������
//============================================================
void FByteString::WriteDouble(TDouble value){
   EnsureSize(_position + sizeof(TDouble));
   *(TDouble*)(_pMemory + _position) = value;
   _position += sizeof(TDouble);
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ��8λ�ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void FByteString::WriteString8(TChar8C* pValue, TInt length){
   if(length < 0){
      length = RString8::Length(pValue);
   }
   EnsureSize(_position + sizeof(TUint16) + length);
   *(TUint16*)(_pMemory + _position) = length;
   _position += sizeof(TUint16);
   if(length > 0){
      MO_LIB_MEMORY_COPY(_pMemory + _position, _capacity - _position, pValue, sizeof(TChar8) * length);
   }
   _position += sizeof(TChar8) * length;
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ��16λ�ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void FByteString::WriteString16(TChar16C* pValue, TInt length){
   if(length < 0){
      length = RString16::Length(pValue);
   }
   EnsureSize(_position + sizeof(TUint16) + length);
   *(TUint16*)(_pMemory + _position) = length;
   _position += sizeof(TUint16);
   if(length > 0){
      MO_LIB_MEMORY_COPY(_pMemory + _position, _capacity - _position, pValue, sizeof(TChar16) * length);
   }
   _position += sizeof(TChar16) * length;
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ��32λ�ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void FByteString::WriteString32(TChar32C* pValue, TInt length){
   if(length < 0){
      length = RString32::Length(pValue);
   }
   EnsureSize(_position + sizeof(TUint16) + length);
   *(TUint16*)(_pMemory + _position) = length;
   _position += sizeof(TUint16);
   if(length > 0){
      MO_LIB_MEMORY_COPY(_pMemory + _position, _capacity - _position, pValue, sizeof(TChar32) * length);
   }
   _position += sizeof(TChar32) * length;
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ֽ�����д��һ���ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void FByteString::WriteString(TCharC* pValue, TInt length){
   if(length < 0){
      length = RString::Length(pValue);
   }
   EnsureSize(_position + sizeof(TUint16) + length);
   *(TUint16*)(_pMemory + _position) = length;
   _position += sizeof(TUint16);
   if(length > 0){
      MO_LIB_MEMORY_COPY(_pMemory + _position, _capacity - _position, pValue, sizeof(TChar) * length);
   }
   _position += sizeof(TChar) * length;
   // ��������
   if(_position > _length){
      _length = _position;
   }
}

//============================================================
// <T>���ô���</T>
//============================================================
void FByteString::Reset(){
   _position = 0;
}

MO_NAMESPACE_END
