#include "MoCmInterface.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ռ��ڴ洴������</T>
//
// @param size ��С
// @return �ڴ�ָ��
//============================================================
TAny* FBase::operator new(TSize size){
   return MO_MEM_ALLOC(size);
}

//============================================================
// <T>�ռ��ڴ洴������</T>
//
// @param size ��С
// @param pClassName ������
// @param pFileName �ļ�����
// @param lineNumber �к�
// @return �ڴ�ָ��
//============================================================
TAny* FBase::operator new(TSize size, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber){
   return MO_MEM_ALLOC(size);
}

//============================================================
// <T>�ռ��ڴ洴������</T>
//
// @param size ��С
// @param pMemory �ڴ�ָ��
// @return �ڴ�ָ��
//============================================================
TAny* FBase::operator new(TSize size, TAny* pMemory){
   return pMemory;
}

//============================================================
// <T>�ռ��ڴ洴������</T>
//
// @param size ��С
// @param pMemory �ڴ�ָ��
// @param pClassName ������
// @param pFileName �ļ�����
// @param lineNumber �к�
// @return �ڴ�ָ��
//============================================================
TAny* FBase::operator new(TSize size, TAny* pMemory, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber){
   return pMemory;
}

//============================================================
// <T>�ͷŶ����ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FBase::operator delete(TAny* pMemory){
   MO_MEM_FREE(pMemory);
}

//============================================================
// <T>�ͷŶ����ڴ档</T>
//
// @param pMemory �ڴ�ָ��
// @param pAlloc �ռ��ڴ�
//============================================================
void FBase::operator delete(TAny* pMemory, TAny* pAlloc){
}

//============================================================
// <T>�ͷŶ����ڴ档</T>
//
// @param pMemory �ڴ�ָ��
// @param pClassName ������
// @param pFileName �ļ�����
// @param lineNumber �к�
//============================================================
void FBase::operator delete(TAny* pMemory, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber){
   MO_MEM_FREE(pMemory);
}

MO_NAMESPACE_END
