#include "MoMtSize.h"

MO_NAMESPACE_BEGIN

//============================================================
//<T>�����ַ������ݡ�</T>
// 
// @param pValue �ַ���
// @return �Ƿ�����ɹ�
//============================================================
TBool SFloatSize2::Parse(TCharC* pValue){
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
   width = RFloat::Parse(temp.MemoryC());
   // ��������Y
   temp.Assign(value.SubStrC(index + 1, length));
   height = RFloat::Parse(temp.MemoryC());
   return ETrue;
}

//============================================================
// <T>��ʽ������Ϊ��ʾ���ݡ�</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SFloatSize2::Format(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AssignFormat(TC("width=%f, height=%f"), width, height);
   return pBuffer;
}

//============================================================
// <T>��ʽ������Ϊ�ַ�����</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SFloatSize2::ToString(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AppendFormat(TC("%f,%f"), width, height);
   return pBuffer;
}

MO_NAMESPACE_END
