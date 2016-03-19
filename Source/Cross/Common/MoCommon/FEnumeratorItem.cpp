#include "MoCmEnumerator.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEnumeratorItem, FInstance);

//============================================================
// <T>����ö����Ŀ��</T>
//============================================================
FEnumeratorItem::FEnumeratorItem(){
   _code = -1;
}

//============================================================
// <T>����ö����Ŀ��</T>
//============================================================
FEnumeratorItem::~FEnumeratorItem(){
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param pDump ��Ϣ
// @return ������
//============================================================
TResult FEnumeratorItem::Dump(MString* pDump){
   pDump->AppendFormat(TC("%4d=%s"), _code, (TCharC*)_name);
   if(!_description.IsEmpty()){
      pDump->AppendFormat(TC(" [%s]"), (TCharC*)_description);
   }
   return ESuccess;
}

MO_NAMESPACE_END
