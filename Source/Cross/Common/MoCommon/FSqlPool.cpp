#include "MoCmData.h"
#include "MoCmMemory.h"
#include "MoCmPool.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������ַ������塣</T>
//============================================================
FSqlPool::FSqlPool(){
}

//============================================================
// <T>���������ַ������塣</T>
//============================================================
FSqlPool::~FSqlPool(){
}

//============================================================
// <T>�ռ�һ�������ַ�����</T>
//
// @return �����ַ���
//============================================================
FSql* FSqlPool::Alloc(){
   FSql* pSql = NULL;
   _locker.Enter();
   if(!HasFreeItem()){
      Store(MO_CREATE(FSql));
   }
   pSql = AllocFirst();
   _locker.Leave();
   return pSql;
}

//============================================================
// <T>�ͷ�һ�������ַ�����</T>
//
// @param pSql �����ַ���
//============================================================
void FSqlPool::Free(FSql* pSql){
   _locker.Enter();
   FreeLast(pSql);
   _locker.Leave();
}

MO_NAMESPACE_END
