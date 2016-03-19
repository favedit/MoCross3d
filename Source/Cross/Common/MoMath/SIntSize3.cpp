#include "MoMtSize.h"

MO_NAMESPACE_BEGIN

//============================================================
//<T>�����ַ������ݡ�</T>
// 
// @param pValue �ַ���
// @return �Ƿ�����ɹ�
//============================================================
TBool SIntSize3::Parse(TCharC* pValue){
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
   width = RInt::Parse(temp.MemoryC());
   // �ָ�����
   begin = index + 1;
   index = value.IndexOf(',', begin);
   if(ENotFound == index){
      MO_ERROR(TC("Splite value failure."));
      return EFalse;
   }
   // ��������Y
   temp.Assign(value.SubStrC(begin, index));
   height = RInt::Parse(temp.MemoryC());
   // ��������Z
   temp.Assign(value.SubStrC(index + 1, length));
   deep = RInt::Parse(temp.MemoryC());
   return ETrue;
}

//============================================================
// <T>��ʽ������Ϊ��ʾ���ݡ�</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SIntSize3::Format(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AssignFormat(TC("width=%d, height=%d, deep=%d"), width, height, deep);
   return pBuffer;
}

//============================================================
// <T>��ʽ������Ϊ�ַ�����</T>
//
// @param pBuffer ����ָ��
// @param capacity ���峤��
// @return �ַ���
//============================================================
TCharC* SIntSize3::ToString(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AppendFormat(TC("%d,%d,%d"), width, height, deep);
   return pBuffer;
}

MO_NAMESPACE_END
