#include "MoCmXml.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ֻ����������</T>
//============================================================
TXmlNodeIteratorC::TXmlNodeIteratorC(){
}

//============================================================
// <T>����ֻ����������</T>
//
// @param iterator ֻ��������
//============================================================
TXmlNodeIteratorC::TXmlNodeIteratorC(const TXmlNodeIteratorC& iterator){
   _pStart = iterator._pStart;
   MO_CLEAR(_pEntry);
}

//============================================================
// <T>����ֻ����������</T>
//
// @param pEntry ��ڶ���
//============================================================
TXmlNodeIteratorC::TXmlNodeIteratorC(SEntry* pEntry){
   _pStart = pEntry;
   MO_CLEAR(_pEntry);
}

//============================================================
// <T>�ƶ�����һ��λ�á�</T>
//
// @return �ƶ����
//============================================================
TBool TXmlNodeIteratorC::Next(){
   return TListIteratorC<FXmlNode*>::Next();
}

//============================================================
// <T>�ƶ�����һ��λ�á�</T>
//
// @param pName ����
// @return �ƶ����
//============================================================
TBool TXmlNodeIteratorC::Next(TCharC* pName){
   while(ETrue){
      // �����һ��λ��
      _pEntry = (NULL == _pEntry) ? _pStart : _pEntry->nextPtr;
      if(NULL == _pEntry){
         break;
      }
      // �ж��Ƿ���������
      if(_pEntry->value->IsName(pName)){
         break;
      }
   }
   return (NULL != _pEntry);
}

MO_NAMESPACE_END
