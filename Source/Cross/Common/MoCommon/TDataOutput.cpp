#include "MoCmStream.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������������ʵ����</T>
//
// @return ʵ��ָ��
//============================================================
TDataOutput::TDataOutput(){
   _pOutput = NULL;
}

//============================================================
// <T>���������������ʵ����</T>
//
// @param pOutput ����ӿ�
//============================================================
TDataOutput::TDataOutput(IOutput* pOutput){
   _pOutput = pOutput;
}

//============================================================
// <T>���������������ʵ����</T>
//============================================================
TDataOutput::~TDataOutput(){
}

//============================================================
// <T>�������ӿڡ�</T>
//
// @return ����ӿ�
//============================================================
IOutput* TDataOutput::Output(){
   return _pOutput;
}

//============================================================
// <T>��������ӿڡ�</T>
//
// @param pOutput ����ӿ�
//============================================================
void TDataOutput::SetOutput(IOutput* pOutput){
   _pOutput = pOutput;
}

//============================================================
// <T>��������ӿڡ�</T>
//
// @param pOutput ����ӿ�
//============================================================
TByte* TDataOutput::PositionMemory(){
   MO_FATAL_UNSUPPORT();
   return NULL;
}

//============================================================
// <T>��������ӿڡ�</T>
//
// @param pOutput ����ӿ�
//============================================================
void TDataOutput::Skip(TInt length){
   MO_FATAL_UNSUPPORT();
}
   
//============================================================
// <T>���ֽ�����д��һ���з���������</T>
//
// @param pData �ֽ�����
// @param length ���ݳ���
// @return д�볤��
//============================================================
TInt TDataOutput::Write(TAnyC* pData, TInt length){
   return _pOutput->Write(pData, length);
}

//============================================================
// <T>���ֽ�����д��һ������ֵ��</T>
// <P>ռ��һ���ֽڣ�Ϊ1��ʾ�棬Ϊ0��ʾ�١�</P>
//
// @param value ����ֵ
//============================================================
void TDataOutput::WriteBool(TBool value){
   _pOutput->Write(&value, sizeof(TBool));
}

//============================================================
// <T>���ֽ�����д��һ���з���������</T>
//
// @param value �з�������
//============================================================
void TDataOutput::WriteInt(TInt value){
   _pOutput->Write(&value, sizeof(TInt));
}

//============================================================
// <T>���ֽ�����д��һ���з���8λ������</T>
//
// @param value �з���8λ����
//============================================================
void TDataOutput::WriteInt8(TInt8 value){
   _pOutput->Write(&value, sizeof(TInt8));
}

//============================================================
// <T>���ֽ�����д��һ���з���16λ������</T>
//
// @param value �з���16λ����
//============================================================
void TDataOutput::WriteInt16(TInt16 value){
   _pOutput->Write(&value, sizeof(TInt16));
}

//============================================================
// <T>���ֽ�����д��һ���з���32λ������</T>
//
// @param value �з���32λ����
//============================================================
void TDataOutput::WriteInt32(TInt32 value){
   _pOutput->Write(&value, sizeof(TInt32));
}

//============================================================
// <T>���ֽ�����д��һ���з���64λ������</T>
//
// @param value �з���64λ����
//============================================================
void TDataOutput::WriteInt64(TInt64 value){
   _pOutput->Write(&value, sizeof(TInt64));
}

//============================================================
// <T>���ֽ�����д��һ���޷���������</T>
//
// @param value �޷�������
//============================================================
void TDataOutput::WriteUint(TUint value){
   _pOutput->Write(&value, sizeof(TUint));
}

//============================================================
// <T>���ֽ�����д��һ���޷���8λ������</T>
//
// @param value �޷���8λ����
//============================================================
void TDataOutput::WriteUint8(TUint8 value){
   _pOutput->Write(&value, sizeof(TUint8));
}

//============================================================
// <T>���ֽ�����д��һ���޷���16λ������</T>
//
// @param value �޷���16λ����
//============================================================
void TDataOutput::WriteUint16(TUint16 value){
   _pOutput->Write(&value, sizeof(TUint16));
}

//============================================================
// <T>���ֽ�����д��һ���޷���32λ������</T>
//
// @param value �޷���32λ����
//============================================================
void TDataOutput::WriteUint32(TUint32 value){
   _pOutput->Write(&value, sizeof(TUint32));
}

//============================================================
// <T>���ֽ�����д��һ���޷���64λ������</T>
//
// @param value �޷���64λ����
//============================================================
void TDataOutput::WriteUint64(TUint64 value){
   _pOutput->Write(&value, sizeof(TUint64));
}

//============================================================
// <T>���ֽ�����д��һ��32λ��������</T>
//
// @param value 32λ������
//============================================================
void TDataOutput::WriteFloat(TFloat value){
   _pOutput->Write(&value , sizeof(TFloat));
}

//============================================================
// <T>���ֽ�����д��һ��64λ��������</T>
//
// @param value 64λ������
//============================================================
void TDataOutput::WriteDouble(TDouble value){
   _pOutput->Write(&value, sizeof(TDouble));
}

//============================================================
// <T>���ֽ�����д��һ��8λ�ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void TDataOutput::WriteString8(TChar8C* pValue, TInt length){
   if(length < 0){
      length = RString8::Length(pValue);
   }
   MO_ASSERT(length <= 0xFFFF);
   TUint16 size = (TUint16)length;
   _pOutput->Write(&size, sizeof(TUint16));
   if(length > 0){
      _pOutput->Write(pValue, sizeof(TChar8) * length);
   }
}

//============================================================
// <T>���ֽ�����д��һ��16λ�ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void TDataOutput::WriteString16(TChar16C* pValue, TInt length){
   if(length < 0){
      length = RString16::Length(pValue);
   }
   MO_ASSERT(length <= 0xFFFF);
   TUint16 size = (TUint16)length;
   _pOutput->Write(&size, sizeof(TUint16));
   if(length > 0){
      _pOutput->Write(pValue, sizeof(TChar16) * length);
   }
}

//============================================================
// <T>���ֽ�����д��һ��32λ�ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void TDataOutput::WriteString32(TChar32C* pValue, TInt length){
   if(length < 0){
      length = RString32::Length(pValue);
   }
   MO_ASSERT(length <= 0xFFFF);
   TUint16 size = (TUint16)length;
   _pOutput->Write(&size, sizeof(TUint16));
   if(length > 0){
      _pOutput->Write(pValue, sizeof(TChar32) * length);
   }
}

//============================================================
// <T>���ֽ�����д��һ���ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void TDataOutput::WriteString(TCharC* pValue, TInt length){
   if(length < 0){
      length = RString::Length(pValue);
   }
   MO_ASSERT(length <= 0xFFFF);
   TUint16 size = (TUint16)length;
   _pOutput->Write(&size, sizeof(TUint16));
   if(length > 0){
      _pOutput->Write(pValue, sizeof(TChar) * length);
   }
}

MO_NAMESPACE_END
