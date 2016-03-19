#include "MoMtVector.h"

MO_NAMESPACE_BEGIN

//============================================================
//<T>�����ַ������ݡ�</T>
// 
// @param pValue �ַ���
// @return �Ƿ�����ɹ�
//============================================================
TBool SFloatVector4::Parse(TCharC* pValue){
   // ��鳤��
   TStringRefer value(pValue);
   TInt length = value.Length();
   if(length == 0){
      MO_ERROR(TC("It is invalid length."));
      return EFalse;
   }
   // �ָ�����
   TFsText temp;
   TInt begin = 0;
   TInt index = value.IndexOf(',', begin);
   if(ENotFound  == index){
      MO_ERROR(TC("Splite value failure."));
      return EFalse;
   }
   // ��������X
   temp.Assign(value.SubStrC(begin, index));
   x = RFloat::Parse(temp.MemoryC());
   // �ָ�����
   begin = index + 1;
   index = value.IndexOf(',', begin);
   if(ENotFound == index){
      MO_ERROR(TC("Splite value failure."));
      return EFalse;
   }
   // ��������Y
   temp.Assign(value.SubStrC(begin, index));
   y = RFloat::Parse(temp.MemoryC());
   // �ָ�����
   begin = index + 1;
   index = value.IndexOf(',', begin);
   if(ENotFound == index){
      MO_ERROR(TC("Splite value failure."));
      return EFalse;
   }
   // ��������Z
   temp.Assign(value.SubStrC(begin, index));
   z = RFloat::Parse(temp.MemoryC());
   // ��������W
   temp.Assign(value.SubStrC(index + 1, length));
   w = RFloat::Parse(temp.MemoryC());
   return ETrue;
}

//============================================================
// <T>��ʽ������Ϊ��ʾ���ݡ�</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SFloatVector4::Format(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AssignFormat(TC("x=%f, y=%f, z=%f, w=%f"), x, y, z, w);
   return pBuffer;
}

//============================================================
// <T>��ʽ������Ϊ�ַ�����</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SFloatVector4::ToString(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AppendFormat(TC("%f,%f,%f,%f"), x, y, z, w);
   return pBuffer;
}

MO_NAMESPACE_END
