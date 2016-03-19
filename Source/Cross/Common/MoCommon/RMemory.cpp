#include "MoCmRuntime.h"

MO_NAMESPACE_BEGIN

//------------------------------------------------------------
// �洢��
IMemoryStorage* RMemory::_pStorage = NULL;

//============================================================
// <T>��ô洢����</T>
//
// @return �洢��
//============================================================
IMemoryStorage* RMemory::Storage(){
   return _pStorage;
}

//============================================================
// <T>�����洢����</T>
//
// @param pStorage �洢��
//============================================================
void RMemory::LinkStorage(IMemoryStorage* pStorage){
   _pStorage = pStorage;
}

//============================================================
// <T>�洢���ռ��ڴ档</T>
// <P>ÿ���ڴ�ǰ���һ������ָ��λ�ã�ָ��Ϊ�ձ�ʾû��������Ϣ��</P>
//
// @param pOwnerName ӵ��������
// @param pTypeName ��������
// @param size ��С
// @param pFileName �ļ�����
// @param lineNumber �к�
// @return �ڴ�ָ��
//============================================================
TAny* RMemory::Alloc(TChar8C* pOwnerName, TChar8C* pTypeName, TSize size, TChar8C* pFileName, TInt lineNumber){
#ifdef _MO_DEBUG
   if(NULL != _pStorage){
      return _pStorage->Alloc(pOwnerName, pTypeName, (TInt)size, pFileName, lineNumber);
   }else{
      TAny* pAlloc = malloc(sizeof(TAny*) + size);
      *(TInt*)pAlloc = 0;
      return (TByte*)pAlloc + sizeof(TAny*);
   }
#else
   return malloc(size);
#endif // _DEBUG
}

//============================================================
// <T>�洢���ͷ��ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void RMemory::Free(TAny* pMemory){
   MO_CHECK(pMemory, return);
#ifdef _MO_DEBUG
   if(NULL != _pStorage){
      _pStorage->Free(pMemory);
   }else{
      TAny* pAlloc = (TByte*)pMemory - sizeof(TAny*);
      free(pAlloc);
   }
#else
   free(pMemory);
#endif // _DEBUG
}

//============================================================
// <T>���ָ�����ڴ�����</T>
//
// @param pMemory �������ڴ�
// @param value ���ֵ
// @param size ָ����С
//============================================================
void RMemory::Fill(TAny* pMemory, TUint size, TInt value){
   MO_ASSERT(pMemory);
   memset(pMemory, value, size);
}

//============================================================
// <T>�����ڴ�����ָ��λ�á�</T>
//
// @param pSource Դ�ڴ�
// @param pTarget Ŀ���ڴ�
// @param size ָ����С
//============================================================
void RMemory::Copy(const TAny* pSource, TAny* pTarget, TUint size){
   MO_ASSERT(pSource);
   MO_ASSERT(pTarget);
   memcpy(pTarget, pSource, size);
}

//============================================================
// <T>����ָ�����ڴ�����</T>
// <P>��ǰ�ڴ���ȫ����0������䡣</P>
//
// @param pMemory �������ڴ�
// @param size ָ����С
//============================================================
void RMemory::Clear(TAny* pMemory, TUint size){
   MO_ASSERT(pMemory);
   memset(pMemory, 0, size);
}

MO_NAMESPACE_END
