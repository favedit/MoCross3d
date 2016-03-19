#include "MoCmFile.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FByteStream, FInstance);

//============================================================
// <T>�����ֽ���������</T>
//============================================================
FByteStream::FByteStream(){
   _position = 0;
}

//============================================================
// <T>�����ֽ���������</T>
//============================================================
FByteStream::~FByteStream(){
}

//============================================================
// <T>���λ�á�</T>
//
// @return λ��
//============================================================
TInt FByteStream::Position(){
   return _position;
}

//============================================================
// <T>����λ�á�</T>
//
// @param position λ��
//============================================================
void FByteStream::SetPosition(TInt position){
   MO_ASSERT(position <= _length);
   _position = position;
}

//============================================================
// <T>���λ���ڴ档</T>
//
// @return λ���ڴ�
//============================================================
TByte* FByteStream::PositionMemory(){
   return _pMemory + _position;
}

//============================================================
// <T>����ָ�����ȵ��ڴ档</T>
//
// @param length ����
//============================================================
void FByteStream::Skip(TInt length){
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
TInt FByteStream::Read(TAny* pData, TInt length){
   MO_ASSERT(_position + length <= _length);
   TByte* pMemory = (TByte*)(_pMemory + _position);
   MO_LIB_MEMORY_COPY(pData, length, pMemory, length);
   _position += length;
   return length;
}

//============================================================
// <T>���ֽ����ж�ȡһ������ֵ��</T>
// <P>ռ��һ���ֽڣ�Ϊ1��ʾ�棬Ϊ0��ʾ�١�</P>
//
// @return ����ֵ
//============================================================
TBool FByteStream::ReadBool(){
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
TInt FByteStream::ReadInt(){
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
TInt8 FByteStream::ReadInt8(){
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
TInt16 FByteStream::ReadInt16(){
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
TInt32 FByteStream::ReadInt32(){
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
TInt64 FByteStream::ReadInt64(){
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
TUint FByteStream::ReadUint(){
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
TUint8 FByteStream::ReadUint8(){
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
TUint16 FByteStream::ReadUint16(){
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
TUint32 FByteStream::ReadUint32(){
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
TUint64 FByteStream::ReadUint64(){
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
TFloat FByteStream::ReadFloat(){
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
TDouble FByteStream::ReadDouble(){
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
TInt FByteStream::ReadString8(TChar8* pValue, TInt capacity){
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
TInt FByteStream::ReadString16(TChar16* pValue, TInt capacity){
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
TInt FByteStream::ReadString32(TChar32* pValue, TInt capacity){
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
TInt FByteStream::ReadString(TChar* pValue, TInt capacity){
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
TString8 FByteStream::ReadString8(){
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
TString16 FByteStream::ReadString16(){
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
TString32 FByteStream::ReadString32(){
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
TString FByteStream::ReadString(){
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
// <T>���ֽ�����д��һ���з���������</T>
//
// @param pData �ֽ�����
// @param length ���ݳ���
// @return д�볤��
//============================================================
TInt FByteStream::Write(TAnyC* pData, TInt length){
   EnsureSize(_position + length);
   TByte* pMemory = (TByte*)(_pMemory + _position);
   MO_LIB_MEMORY_COPY(pMemory, _capacity, pData, length);
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
void FByteStream::WriteBool(TBool value){
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
void FByteStream::WriteInt(TInt value){
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
void FByteStream::WriteInt8(TInt8 value){
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
void FByteStream::WriteInt16(TInt16 value){
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
void FByteStream::WriteInt32(TInt32 value){
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
void FByteStream::WriteInt64(TInt64 value){
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
void FByteStream::WriteUint(TUint value){
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
void FByteStream::WriteUint8(TUint8 value){
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
void FByteStream::WriteUint16(TUint16 value){
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
void FByteStream::WriteUint32(TUint32 value){
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
void FByteStream::WriteUint64(TUint64 value){
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
void FByteStream::WriteFloat(TFloat value){
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
void FByteStream::WriteDouble(TDouble value){
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
void FByteStream::WriteString8(TChar8C* pValue, TInt length){
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
void FByteStream::WriteString16(TChar16C* pValue, TInt length){
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
void FByteStream::WriteString32(TChar32C* pValue, TInt length){
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
void FByteStream::WriteString(TCharC* pValue, TInt length){
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
void FByteStream::Reset(){
   _position = 0;
}

MO_NAMESPACE_END
