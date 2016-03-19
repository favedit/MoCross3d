#include "MoCmStream.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ֽ���������</T>
//============================================================
TLinkOutput::TLinkOutput(TAny* pOutputData, TInt outputCapacity){
   _pMemory = (TByte*)pOutputData;
   _capacity = outputCapacity;
   _position = 0;
   _length = 0;
}

//============================================================
// <T>�����ڴ档</T>
//============================================================
void TLinkOutput::Link(TAny* pOutputData, TInt outputCapacity){
   _pMemory = (TByte*)pOutputData;
   _capacity = outputCapacity;
   _position = 0;
   _length = 0;
}

//============================================================
// <T>��õ�ǰλ�á�</T>
//
// @return ��ǰλ��
//============================================================
TInt TLinkOutput::Position(){
   return _position;
}

//============================================================
// <T>��ó��ȡ�</T>
//
// @return ����
//============================================================
TInt TLinkOutput::Length(){
   return _length;
}

//============================================================
// <T>���������</T>
//
// @return ����
//============================================================
TInt TLinkOutput::Capacity(){
   return _capacity;
}

//============================================================
// <T>����ڴ�ָ�롣</T>
//
// @return �ڴ�ָ��
//============================================================
TByteC* TLinkOutput::MemoryC(){
   return _pMemory;
}

//============================================================
// <T>����ڴ�ָ�롣</T>
//
// @return �ڴ�ָ��
//============================================================
TByte* TLinkOutput::Memory(){
   return _pMemory;
}

//============================================================
// <T>��õ�ǰλ�õ��ڴ�ָ�롣</T>
//
// @return �ڴ�ָ��
//============================================================
TByte* TLinkOutput::PositionMemory(){
   return (_pMemory + _position);
}

//============================================================
// <T>����λ���ƶ�һ��λ�á�</T>
//
// @param length ����
//============================================================
void TLinkOutput::Skip(TInt length){
   _position += length;
}

//============================================================
// <T>�������ݳ��ȡ�</T>
//============================================================
TBool TLinkOutput::SetLength(TInt inputLength){
   if(inputLength > _capacity){
      return EFalse;
   }
   if(_length < inputLength){
      _length = inputLength;
   }
   return ETrue;
}

//============================================================
// <T>д�����ݡ�</T>
//
// @param pData ����
// @param length ����
// @return д�볤��
//============================================================
TInt TLinkOutput::Write(TAnyC* pData, TInt length){
   TBool result = SetLength(_position + length);
   if(result){
      TByte* pMemory = (TByte*)(_pMemory + _position);
      MO_LIB_MEMORY_COPY(pMemory, _capacity, pData, length);
      _position += length;
      return length;
   }
   return -1;
}

//============================================================
// <T>д��һ������ֵ��</T>
//============================================================
void TLinkOutput::WriteBool(TBool value){
   TBool result = SetLength(_position + sizeof(TByte));
   if(result){
      *(TByte*)(_pMemory + _position) = value;
      _position += sizeof(TByte);
   }
}

//============================================================
// <T>д��һ��������</T>
//============================================================
void TLinkOutput::WriteInt(TInt value){
   TBool result = SetLength(_position + sizeof(TInt));
   if(result){
      *(TInt*)(_pMemory + _position) = value;
      _position += sizeof(TInt);
   }
}

//============================================================
// <T>д��һ��һ�ֽ�������</T>
//============================================================
void TLinkOutput::WriteInt8(TInt8 value){
   TBool result = SetLength(_position + sizeof(TInt8));
   if(result){
      *(TInt8*)(_pMemory + _position) = value;
      _position += sizeof(TInt8);
   }
}

//============================================================
// <T>д��һ�����ֽ�������</T>
//============================================================
void TLinkOutput::WriteInt16(TInt16 value){
   TBool result = SetLength(_position + sizeof(TInt16));
   if(result){
      *(TInt16*)(_pMemory + _position) = value;
      _position += sizeof(TInt16);
   }
}

//============================================================
// <T>д��һ�����ֽ�������</T>
//============================================================
void TLinkOutput::WriteInt32(TInt32 value){
   TBool result = SetLength(_position + sizeof(TInt32));
   if(result){
      *(TInt32*)(_pMemory + _position) = value;
      _position += sizeof(TInt32);
   }
}

//============================================================
// <T>д��һ�����ֽ�������</T>
//============================================================
void TLinkOutput::WriteInt64(TInt64 value){
   TBool result = SetLength(_position + sizeof(TInt64));
   if(result){
      *(TInt64*)(_pMemory + _position) = value;
      _position += sizeof(TInt64);
   }
}

//============================================================
// <T>д��һ��һ�ֽ��޷���������</T>
//============================================================
void TLinkOutput::WriteUint(TUint value){
   TBool result = SetLength(_position + sizeof(TUint));
   if(result){
      *(TUint*)(_pMemory + _position) = value;
      _position += sizeof(TUint);
   }
}

//============================================================
// <T>д��һ��һ�ֽ��޷���������</T>
//============================================================
void TLinkOutput::WriteUint8(TUint8 value){
   TBool result = SetLength(_position + sizeof(TUint8));
   if(result){
      *(TUint8*)(_pMemory + _position) = value;
      _position += sizeof(TUint8);
   }
}

//============================================================
// <T>д��һ�����ֽ��޷���������</T>
//============================================================
void TLinkOutput::WriteUint16(TUint16 value){
   TBool result = SetLength(_position + sizeof(TUint16));
   if(result){
      *(TUint16*)(_pMemory + _position) = value;
      _position += sizeof(TUint16);
   }
}

//============================================================
// <T>д��һ�����ֽ��޷���������</T>
//============================================================
void TLinkOutput::WriteUint32(TUint32 value){
   TBool result = SetLength(_position + sizeof(TUint32));
   if(result){
      *(TUint32*)(_pMemory + _position) = value;
      _position += sizeof(TUint32);
   }
}

//============================================================
// <T>д��һ�����ֽ��޷���������</T>
//============================================================
void TLinkOutput::WriteUint64(TUint64 value){
   TBool result = SetLength(_position + sizeof(TUint64));
   if(result){
      *(TUint64*)(_pMemory + _position) = value;
      _position += sizeof(TUint64);
   }
}

//============================================================
// <T>д��һ�����ֽڸ�������</T>
//============================================================
void TLinkOutput::WriteFloat(TFloat value){
   TBool result = SetLength(_position + sizeof(TFloat));
   if(result){
      *(TFloat*)(_pMemory + _position) = value;
      _position += sizeof(TFloat);
   }
}

//============================================================
// <T>д��һ�����ֽڸ�������</T>
//============================================================
void TLinkOutput::WriteDouble(TDouble value){
   TBool result = SetLength(_position + sizeof(TDouble));
   if(result){
      *(TDouble*)(_pMemory + _position) = value;
      _position += sizeof(TDouble);
   }
}

//============================================================
// <T>д��һ��8λ�ַ�����</T>
//============================================================
void TLinkOutput::WriteString8(TChar8C* pValue, TInt length){
   if(length < 0){
      length = RString8::Length(pValue);
   }
   TBool result = SetLength(_position + sizeof(TUint16) + length);
   if(result){
      *(TUint16*)(_pMemory + _position) = length;
      _position += sizeof(TUint16);
      MO_LIB_MEMORY_COPY(_pMemory + _position, _capacity - _position, pValue, length);
      _position += length;
   }
}

//============================================================
// <T>д��һ��16λ�ַ�����</T>
//============================================================
void TLinkOutput::WriteString16(TChar16C* pValue, TInt length){
	if(length < 0){
		length = RString16::Length(pValue);
	}
	TBool result = SetLength(_position + sizeof(TUint16) + length);
	if(result){
		*(TUint16*)(_pMemory + _position) = length;
		_position += sizeof(TUint16);
		MO_LIB_MEMORY_COPY(_pMemory + _position, _capacity - _position, pValue, length);
		_position += length;
	}
}

//============================================================
// <T>д��һ��32λ�ַ�����</T>
//============================================================
void TLinkOutput::WriteString32(TChar32C* pValue, TInt length){
	if(length < 0){
		length = RChar32s::Length(pValue);
	}
	TBool result = SetLength(_position + sizeof(TUint16) + length);
	if(result){
		*(TUint16*)(_pMemory + _position) = length;
		_position += sizeof(TUint16);
		MO_LIB_MEMORY_COPY(_pMemory + _position, _capacity - _position, pValue, length);
		_position += length;
	}
}

//============================================================
// <T>д��һ���ַ�����</T>
//============================================================
void TLinkOutput::WriteString(TCharC* pValue, TInt length){
   if(length < 0){
      length = RString::Length(pValue);
   }
   TBool result = SetLength(_position + sizeof(TUint16) + length);
   if(result){
      *(TUint16*)(_pMemory + _position) = length;
      _position += sizeof(TUint16);
      MO_LIB_MEMORY_COPY(_pMemory + _position, _capacity - _position, pValue, length);
      _position += length;
   }
}

//============================================================
// <T>���á�</T>
//============================================================
void TLinkOutput::Reset(){
   _position = 0;
   _length = 0;
}

MO_NAMESPACE_END
