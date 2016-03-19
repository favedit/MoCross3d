#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ڴ�ԭ��ʵ����</T>
//
// @param pAllocator �ڴ��ռ���
//============================================================
SMemoryEntry::SMemoryEntry(IAllocator* pAllocator){
   // ��ʼ���ṹ
   this->pAllocator = pAllocator;
   MO_CLEAR(pPrior);
   MO_CLEAR(pNext);
   MO_CLEAR(pAlloc);
   MO_CLEAR(pMemory);
   size = 0;
   // ��ʼ��λ��
   MO_CLEAR(pTypeName);
   MO_CLEAR(pFileName);
   fileLine = 0;
   // ��ʼ������
   allocCount = 0;
   freeCount = 0;
   //createDateTime = RDateTime::Current();
   usedDateTime = 0;
}

//============================================================
// <T>�����ڴ�ԭ��ʵ����</T>
//============================================================
SMemoryEntry::~SMemoryEntry(){
}

//============================================================
// <T>����������</T>
//
// @param pClassName ����
//============================================================
void SMemoryEntry::SetTypeName(TCharC* pTypeName){
   this->pTypeName = pTypeName;
}

//============================================================
// <T>�����ļ���Ϣ��</T>
//
// @param pFileName �ļ�����
// @param line �ļ��к�
//============================================================
void SMemoryEntry::SetFileInfo(TChar8C* pFileName, TInt fileLine){
   this->pFileName = pFileName;
   this->fileLine = fileLine;
}

//============================================================
// <T>�����ڴ�ʵ����</T>
//
// @param size �ڴ��С
// @param pMemory �Ѿ��ռ����ڴ�
//============================================================
void SMemoryEntry::Link(TByte* pData, TUint size){
   // ��ʼ������
   size = size;
   // �ռ������ڴ�
   pAlloc = (TInt*)pData;
   // ��һ��λ�ô洢��ǰ����ָ��
   pAlloc[0] = (TInt)this;
   // �ڶ���λ��ΪҪ�ռ����ڴ�
   pMemory = pAlloc + 1;
}

//============================================================
// <T>�ռ��ڴ档</T>
//============================================================
void SMemoryEntry::Alloc(){
   ++allocCount;
   //usedDateTime = RDateTime::Current();
}

//============================================================
// <T>�ͷ��ڴ档</T>
//============================================================
void SMemoryEntry::Free(){
   ++freeCount;
}

MO_NAMESPACE_END
