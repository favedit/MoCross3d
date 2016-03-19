#include "MoCmFile.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ȡTBool��������</T>
//
// @return ����TBool��������
//============================================================
TBool FByteFileStream::ReadBool(){
   TBool value;
   TUint result = fread(&value, sizeof(TBool), 1, _handle);
   if(result > 0){
      return value;
   }
   return EFalse;
}

//============================================================
// <T>��ȡTUint��������</T>
//
// @return ����TUint������������
//============================================================
TUint FByteFileStream::ReadUint(){
   TUint value;
   TUint result = fread(&value, sizeof(TUint), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡTInt��������</T>
//
// @return ����TInt������������
//============================================================
TInt FByteFileStream::ReadInt(){
   TInt value;
   TUint result = fread(&value, sizeof(TInt), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡTUint8��������</T>
//
// @return ����TUint8������������
//============================================================
TUint8 FByteFileStream::ReadUint8(){
   TUint8 value;
   TUint result = fread(&value, sizeof(TUint8), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}
//============================================================
// <T>��ȡTInt8��������</T>
//
// @return ����TInt������������
//============================================================
TInt8 FByteFileStream::ReadInt8(){
   TInt8 value;
   TUint result = fread(&value, sizeof(TInt8), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡTUint16��������</T>
//
// @return ����TUint16������������
//============================================================
TUint16 FByteFileStream::ReadUint16(){
   TUint16 value;
   TUint result = fread(&value, sizeof(TUint16), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
   return value;
}
//============================================================
// <T>��ȡTInt16��������</T>
//
// @return ����TInt������������
//============================================================
TInt16 FByteFileStream::ReadInt16(){
   TInt16 value;
   TUint result = fread(&value, sizeof(TInt16), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
   return value;
}

//============================================================
// <T>��ȡTUint32��������</T>
//
// @return ����TUint32������������
//============================================================
TUint32 FByteFileStream::ReadUint32(){
   TUint32 value;
   TUint result = fread(&value, sizeof(TUint32), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡTInt32��������</T>
//
// @return ����TInt������������
//============================================================
TInt32 FByteFileStream::ReadInt32(){
   TInt32 value;
   TUint result = fread(&value, sizeof(TInt32), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡTUint64��������</T>
//
// @return ����TUint64������������
//============================================================
TUint64 FByteFileStream::ReadUint64(){
   TInt64 value;
   TUint result = fread(&value, sizeof(TUint64), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡTInt64��������</T>
//
// @return ����TInt������������
//============================================================
TInt64 FByteFileStream::ReadInt64(){
   TInt64 value;
   TUint result = fread(&value, sizeof(TInt64), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡTFloat��������</T>
//
// @return ����TFoalt������������
//============================================================
TFloat FByteFileStream::ReadFloat(){
   TFloat value;
   TUint result = fread(&value, sizeof(TFloat), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡTDouble��������</T>
//
// @return ����TDouble������������
//============================================================
TDouble FByteFileStream::ReadDouble(){
   TDouble value;
   TUint result = fread(&value, sizeof(TDouble), 1, _handle);
   if(result > 0){
      return value;
   }
   return 0;
}

//============================================================
// <T>��ȡ�ַ����������ݣ��ȶ����ȣ�������ݡ�</T>
//
// @param pBuffer ��Ŷ�ȡ�������ݵ��ڴ��ָ�롣
// @param length �ڴ��ĳ��ȡ�
//============================================================
TInt FByteFileStream::ReadString(TChar8C* pBuffer, TInt length){
   TInt readed = 0;
   TUint result = fread(&readed, sizeof(TInt),1,_handle);
   if(result == sizeof(TUint32)){
      if(readed > 0){
         MO_ASSERT(readed <= length);
         result = fread((TAny*)pBuffer, sizeof(TChar8C) * readed, 1, _handle);
      }
   }
   return readed;
}

//============================================================
// <T>��ȡ�ַ����������ݣ��ȶ����ȣ��������,���ַ��汾��</T>
//
// @param pBuffer ��Ŷ�ȡ�������ݵ��ڴ��ָ�롣
// @param length �ڴ��ĳ��ȡ�
//============================================================
TInt FByteFileStream::ReadString(TChar16C* pBuffer, TInt length){
   TInt readed = 0;
   TUint result = fread(&readed, sizeof(TInt),1,_handle);
   if(result == sizeof(TInt)){
      if(readed > 0){
         MO_ASSERT(readed <= length);
         result = fread((TAny*)pBuffer, sizeof(TChar16C) * readed , 1, _handle);
      }
   }
   return readed;
}
//============================================================
// <T>д��Tbool��������</T>
//============================================================
void FByteFileStream::WriteBoolean(TBool value){
   fwrite(&value, sizeof(TBool), 1, _handle);
}

//============================================================
// <T>д��TUint��������</T>
//============================================================
void FByteFileStream::WriteUInt(TUint value){
   fwrite(&value, sizeof(TUint), 1, _handle);
}
//============================================================
// <T>д��TInt��������</T>
//============================================================
void FByteFileStream::WriteInt(TInt value){
   fwrite(&value, sizeof(TInt), 1, _handle);
}

//============================================================
// <T>д��TUint8��������</T>
//============================================================
void FByteFileStream::WriteUInt8(TUint8 value){
   fwrite(&value, sizeof(TUint8), 1, _handle);
}
//============================================================
// <T>д��TInt8��������</T>
//============================================================
void FByteFileStream::WriteInt8(TInt8 value){
   fwrite(&value, sizeof(TInt8), 1, _handle);
}

//============================================================
// <T>д��TUint16��������</T>
//============================================================
void FByteFileStream::WriteUInt16(TUint16 value){
   fwrite(&value, sizeof(TUint16), 1, _handle);
}
//============================================================
// <T>д��TInt16��������</T>
//============================================================
void FByteFileStream::WriteInt16(TInt16 value){
   fwrite(&value, sizeof(TInt16), 1, _handle);
}

//============================================================
// <T>д��TUint32��������</T>
//============================================================
void FByteFileStream::WriteUInt32(TUint32 value){
   fwrite(&value, sizeof(TUint32), 1, _handle);
}

//============================================================
// <T>д��TInt32��������</T>
//============================================================
void FByteFileStream::WriteInt32(TInt32 value){
   fwrite(&value, sizeof(TInt32), 1, _handle);
}

//============================================================
//<T>д��TUint64��������</T>
//============================================================
void FByteFileStream::WriteUInt64(TUint64 value){
   fwrite(&value, sizeof(TUint64), 1, _handle);
}

//============================================================
//<T>д��TInt64��������</T>
//============================================================
void FByteFileStream::WriteInt64(TInt64 value){
   fwrite(&value, sizeof(TInt64), 1, _handle);
}

//============================================================
//<T>д��TFloat��������</T>
//============================================================
void FByteFileStream::WriteFloat(TFloat value){
   fwrite(&value , sizeof(TFloat), 1, _handle);
}

//============================================================
// <T>д��TDouble��������</T>
//============================================================
void FByteFileStream::WriteDouble(TDouble value){
   fwrite(&value, sizeof(TDouble), 1, _handle);
}

//============================================================
// <T>д���ַ����������ݣ���д���ȣ�������ݡ�</T>
//
// @param pBuffer  д�����ݵ�ָ��
// @param length д�����ݳ���
//============================================================
void FByteFileStream::WriteString(TChar8C* pBuffer, TInt length){
   fwrite(&length, sizeof(TUint32), 1, _handle);
   if(length > 0){
      fwrite(pBuffer, sizeof(TChar8C) * length, 1, _handle);
   }
}

//============================================================
// <T>д���ַ����������ݣ���д���ȣ�������ݡ�</T>
//
// @param pBuffer  д�����ݵ�ָ��
// @param length д�����ݳ���
//============================================================
void FByteFileStream::WriteStringA16(TChar8C* pBuffer, TInt length){
   TInt16 len = (TInt16)length;
   if(len < 0){
      len = strlen(pBuffer);
   }
   fwrite(&len, sizeof(TUint16), 1, _handle);
   if(len > 0){
      fwrite(pBuffer, sizeof(TChar8C) * len, 1, _handle);
   }
}

//============================================================
// <T>д���ַ����������ݣ���д���ȣ��������,���ַ��汾��</T>
//
// @param pBuffer  д�����ݵ�ָ��
// @param length д�����ݳ���
//============================================================
void FByteFileStream::WriteString(TChar16C* pBuffer, TInt length){
   fwrite(&length, sizeof(TUint32), 1, _handle);
   if(length > 0){
      fwrite(pBuffer, sizeof(TChar16C) * length, 1, _handle);
   }
}

MO_NAMESPACE_END
