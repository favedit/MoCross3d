#include "MoCmXml.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���ֻ����������</T>
//
// @return ֻ��������
//============================================================
TXmlNodeIteratorC FXmlNodes::IteratorC(){
   return TXmlNodeIteratorC(_pFirst);
}

MO_NAMESPACE_END
