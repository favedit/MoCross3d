#include "MoCmEnumerator.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ʋ���һ��ö������</T>
//
// @param pName ����
// @return ö����
//============================================================
FEnumerator* REnumeratorManager::Find(TCharC* pName){
   return _pInstance->Find(pName);
}

MO_NAMESPACE_END
