#include "MoMtVector.h"

MO_NAMESPACE_BEGIN

//============================================================
//<T>�����ַ������ݡ�</T>
// 
// @param pValue �ַ���
// @return �Ƿ�����ɹ�
//============================================================
TBool SFloatVector2::Parse(TCharC* pValue){
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
   // ��������Y
   temp.Assign(value.SubStrC(index + 1, length));
   y = RFloat::Parse(temp.MemoryC());
   return ETrue;
}

//============================================================
// <T>��ʽ������Ϊ��ʾ���ݡ�</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SFloatVector2::Format(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AssignFormat(TC("x=%f, y=%f"), x, y);
   return pBuffer;
}

//============================================================
// <T>��ʽ������Ϊ�ַ�����</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SFloatVector2::ToString(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AppendFormat(TC("%f,%f"), x, y);
   return pBuffer;
}

MO_NAMESPACE_END
