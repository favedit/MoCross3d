#include "MoCmSharedList.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲������ڵ��ռ�����</T>
//============================================================
TBool TSharedListIterator::Delete(){
   if((NULL != _pList) && (_current >= 0)){
      // ָ�����
      _skip = ETrue;
      _next = _pEntries[_current].next;
      // ɾ��λ��
      _pList->Delete(_current);
      // ���Ϊ�����ܼ���
      if(_pList->IsEmpty()){
         _start = -1;
      }
      return ETrue;
   }
   return EFalse;
}

MO_NAMESPACE_END
