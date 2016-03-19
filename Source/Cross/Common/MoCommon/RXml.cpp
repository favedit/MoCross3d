#include "MoCmXml.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���ɽڵ��������ݡ�</T>
//
// @param pXml ��������
// @param pValue �ַ���
// @return ������
//============================================================
TBool RXml::MakeNodeAttribute(MString* pXml, TCharC* pValue){
   // ������
   if((pXml == NULL) || (pValue == NULL)){
      return EFalse;
   }
   // ��鳤��
   TInt length = RString::Length(pValue);
   if(length == 0){
      return EFalse;
   }
   // ׷������
   for(TInt n = 0; n < length; n++){
      TChar value = pValue[n];
      if('&' == value){
         pXml->Append(TC("&amp;"));
      }else if('"' == value){
         pXml->Append(TC("&quot;"));
      }else if('<' == value){
         pXml->Append(TC("&lt;"));
      }else if('>' == value){
         pXml->Append(TC("&gt;"));
      }else if('\r' == value){
         continue;
      }else if('\n' == value){
         pXml->Append(TC("\\n"));
      }else{
         pXml->Append(value);
      }
   }
   return ETrue;
}

//============================================================
// <T>���ɽڵ����ݡ�</T>
//
// @param pXml �ڵ�����
// @param pValue �ַ���
// @return ������
//============================================================
TBool RXml::MakeNodeText(MString* pXml, TCharC* pValue){
   // ������
   if((pXml == NULL) || (pValue == NULL)){
      return EFalse;
   }
   // ��鳤��
   TSize length = RString::Length(pValue);
   if(length == 0){
      return EFalse;
   }
   // ׷������
   for(TSize n = 0; n < length; n++){
      TChar value = pValue[n];
      if('&' == value){
         pXml->Append(TC("&amp;"));
      }else if('"' == value){
         pXml->Append(TC("&quot;"));
      }else if('<' == value){
         pXml->Append(TC("&lt;"));
      }else if('>' == value){
         pXml->Append(TC("&gt;"));
      }else if('\r' == value){
         continue;
      }else if('\n' == value){
         pXml->Append(TC("\\n"));
      }else{
         pXml->Append(value);
      }
   }
   return ETrue;
}

MO_NAMESPACE_END
