#include "MoCmInterface.h"
#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������ࡣ</T>
//============================================================
FObject::FObject(){
}

//============================================================
// <T>����������ࡣ</T>
//============================================================
FObject::~FObject(){
}

//============================================================
// <T>�ռ�һ���ڴ档</T>
//
// @param size ��С
// @return �ڴ�ָ��
//============================================================
TAny* FObject::operator new(TSize size){
   return RAllocator::TypeAlloc(size);
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
TAny* FObject::operator new(TSize size, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber){
   return RAllocator::TypeAlloc(pClassName, size, pFileName, lineNumber);
}

//============================================================
// <T>�ռ��ڴ洴������</T>
//
// @param size ��С
// @param pMemory �ڴ�ָ��
// @return �ڴ�ָ��
//============================================================
TAny* FObject::operator new(TSize size, TAny* pMemory){
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
TAny* FObject::operator new(TSize size, TAny* pMemory, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber){
   return pMemory;
}

//============================================================
// <T>�ͷ�һ���ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FObject::operator delete(TAny* pMemory){
   RAllocator::TypeFree(pMemory);
}

//============================================================
// <T>�ͷŶ����ڴ档</T>
//
// @param pMemory �ڴ�ָ��
// @param pAlloc �ռ��ڴ�
//============================================================
void FObject::operator delete(TAny* pMemory, TAny* pAlloc){
}

//============================================================
// <T>�ͷŶ����ڴ档</T>
//
// @param pMemory �ڴ�ָ��
// @param pClassName ������
// @param pFileName �ļ�����
// @param lineNumber �к�
//============================================================
void FObject::operator delete(TAny* pMemory, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber){
   RAllocator::TypeFree(pMemory);
}

//============================================================
// <T>�����Ĺ�ϣֵ��</T>
//
// @return ��ϣֵ
//============================================================
THashCode FObject::HashCode() const{
   TInt hashcode = (TInt)this;
   return (THashCode)hashcode;
}

MO_NAMESPACE_END
