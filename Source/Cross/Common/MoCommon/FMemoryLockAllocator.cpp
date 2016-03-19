#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
FMemoryLockAllocator::FMemoryLockAllocator(){
}

//============================================================
FMemoryLockAllocator::~FMemoryLockAllocator(){
}

//============================================================
// <T>�ռ�һ�鶨�����ڴ档</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
TAny* FMemoryLockAllocator::Alloc(TInt size){
   MO_ASSERT(size > 0);
   _locker.Enter();
   TAny* pMemory = FMemoryAllocator::Alloc(size);
   _locker.Leave();
   return pMemory;
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param pOwnerName ӵ��������
// @param pTypeName ��������
// @param size �ڴ��С
// @param pFileName �ļ�����
// @param lineNumber �ļ�����
// @return �ڴ�ָ��
//============================================================
TAny* FMemoryLockAllocator::Alloc(TCharC* pOwnerName, TCharC* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber){
   _locker.Enter();
   TAny* pMemory = FMemoryAllocator::Alloc(pOwnerName, pTypeName, size, pFileName, lineNumber);
   _locker.Leave();
   return pMemory;
}

//============================================================
// <T>�ͷ��ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FMemoryLockAllocator::Free(TAny* pMemory){
   _locker.Enter();
   FMemoryAllocator::Free(pMemory);
   _locker.Leave();
}

MO_NAMESPACE_END
