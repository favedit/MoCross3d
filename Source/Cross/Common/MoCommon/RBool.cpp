#include "MoCmType.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ж��ַ������Ƿ�Ϊ��ֵ��</T>
//
// @param value �ַ�
// @return �Ƿ�Ϊ��ֵ
//============================================================
TBool RBool::IsTrue(TChar value){
   return Parse(value);
}

//============================================================
// <T>�ж��ַ��������Ƿ�Ϊ��ֵ��</T>
//
// @param pValue �ַ���
// @param defaultValue Ĭ�ϲ���ֵ
// @return �Ƿ�Ϊ��ֵ
//============================================================
TBool RBool::IsTrue(TCharC* pValue, TBool defaultValue){
   return Parse(pValue, defaultValue);
}

//============================================================
// <T>�����ַ�Ϊ����ֵ��</T>
//
// @param value �ַ�
// @return ����ֵ
//============================================================
TBool RBool::Parse(TChar value){
   switch(value){
      case '1':
      case 'Y':
      case 'y':
      case 'T':
      case 't':
      case 'O':
      case 'o':{
         return ETrue;
      }
      default:{
         break;
      }
   }
   return EFalse;
}

//============================================================
// <T>�����ַ���Ϊ����ֵ��</T>
//
// @param pValue �ַ���
// @param defaultValue Ĭ�ϲ���ֵ
// @return ����ֵ
//============================================================
TBool RBool::Parse(TCharC* pValue, TBool defaultValue){
   if(NULL != pValue){
      TInt length = RChars::Length(pValue);
      if(length > 0){
         switch(length){
            case 1:{
               // ����Ϊ1�����
               TChar value = pValue[0];
               switch(value){
                  case '1':
                  case 'Y':
                  case 'y':
                  case 'T':
                  case 't':
                  case 'O':
                  case 'o':{
                     return ETrue;
                  }
                  default:{
                     break;
                  }
               }
               break;
            }
            case 2:{
               // ����Ϊ2�����
               if(RChars::Equals(pValue, TC("OK")) || RChars::Equals(pValue, TC("Ok")) || RChars::Equals(pValue, TC("ok"))){
                  return ETrue;
               }
               break;
            }
            case 3:{
               // ����Ϊ3�����
               if(RChars::Equals(pValue, TC("YES")) || RChars::Equals(pValue, TC("Yes")) || RChars::Equals(pValue, TC("yes"))){
                  return ETrue;
               }
               break;
            }
            case 4:{
               // ����Ϊ4�����
               if(RChars::Equals(pValue, TC("TRUE")) || RChars::Equals(pValue, TC("True")) || RChars::Equals(pValue, TC("true"))){
                  return ETrue;
               }
               break;
            }
            default:{
               break;
            }
         }
      }
   }
   return defaultValue;
}

//============================================================
// <T>�����ַ���Ϊ����ֵ��</T>
//
// @param pValue �ַ���
// @param defaultValue Ĭ�ϲ���ֵ
// @return ����ֵ
//============================================================
TBool RBool::ParseNvl(TCharC* pValue, TBool defaultValue){
   if(NULL != pValue){
      return Parse(pValue, defaultValue);
   }
   return defaultValue;
}

//============================================================
// <T>������ֵ�任Ϊ�ַ���</T>
//
// @param value ����ֵ
// @return �ַ�
//============================================================
TChar RBool::ToChar(TBool value){
   return value ? MO_TYPE_BOOL_TRUE_CHAR : MO_TYPE_BOOL_FALSE_CHAR;
}

//============================================================
// <T>������ֵ�任Ϊ�ַ�����</T>
//
// @param value ����ֵ
// @return �ַ���
//============================================================
TCharC* RBool::ToString(TBool value){
   return value ? MO_TYPE_BOOL_TRUE_STRING : MO_TYPE_BOOL_FALSE_STRING;
}

//============================================================
// <T>������ֵ�任Ϊ��ʾ�ַ�����</T>
//
// @param value ����ֵ
// @return ��ʾ�ַ���
//============================================================
TCharC* RBool::ToDisplay(TBool value){
   return value ? MO_TYPE_BOOL_TRUE_DISPLAY : MO_TYPE_BOOL_FALSE_DISPLAY;
}

MO_NAMESPACE_END
