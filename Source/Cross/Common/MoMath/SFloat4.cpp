#include "MoMtFloat.h"

MO_NAMESPACE_BEGIN
   
//============================================================
// <T>���л��������ݵ��������</T>
// 
// @param pOutput �����
// @return ������
//============================================================
TResult SFloat4::Serialize(IDataOutput* pOutput){
   MO_CHECK(pOutput, return ENull);
   pOutput->WriteFloat(data[0]);
   pOutput->WriteFloat(data[1]);
   pOutput->WriteFloat(data[2]);
   pOutput->WriteFloat(data[3]);
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
// 
// @param pInput ������
// @return ������
//============================================================
TResult SFloat4::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   data[0] = pInput->ReadFloat();
   data[1] = pInput->ReadFloat();
   data[2] = pInput->ReadFloat();
   data[3] = pInput->ReadFloat();
   return ESuccess;
}

//============================================================
//<T>�����ַ������ݡ�</T>
// 
// @param pValue �ַ���
// @return �Ƿ�����ɹ�
//============================================================
TResult SFloat4::Parse(TCharC* pValue){
   // ��鳤��
   TStringRefer value(pValue);
   TInt length = value.Length();
   if(length == 0){
      MO_ERROR(TC("It is invalid length."));
      return EFailure;
   }
   TFsText temp;
   TInt begin = 0;
   // ��������1
   TInt index = value.IndexOf(',', begin);
   if(ENotFound  == index){
      MO_ERROR(TC("Splite value failure."));
      return EFailure;
   }
   temp.Assign(value.SubStrC(begin, index));
   data[0] = RFloat::Parse(temp.MemoryC());
   value = value.RightStrC(value.Length() - index - 1);
   // ��������2
   index = value.IndexOf(',', begin);
   if(ENotFound  == index){
      MO_ERROR(TC("Splite value failure."));
      return EFailure;
   }
   temp.Assign(value.SubStrC(begin, index));
   data[1] = RFloat::Parse(temp.MemoryC());
   value = value.RightStrC(value.Length() - index - 1);
   // ��������3
   index = value.IndexOf(',', begin);
   if(ENotFound  == index){
      MO_ERROR(TC("Splite value failure."));
      return EFailure;
   }
   temp.Assign(value.SubStrC(begin, index));
   data[2] = RFloat::Parse(temp.MemoryC());
   // ��������4
   temp.Assign(value.SubStrC(index + 1, length));
   data[3] = RFloat::Parse(temp.MemoryC());
   return ESuccess;
}

//============================================================
// <T>��ʽ������Ϊ��ʾ���ݡ�</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SFloat4::Format(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AssignFormat(TC("x=%f, y=%f, z=%f, w=%f"), data[0], data[1], data[2], data[3]);
   return pBuffer;
}

//============================================================
// <T>��ʽ������Ϊ�ַ�����</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SFloat4::ToString(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AppendFormat(TC("%f,%f,%f,%f"), data[0], data[1], data[2], data[3]);
   return pBuffer;
}

MO_NAMESPACE_END
