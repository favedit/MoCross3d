#include "MoCmSystem.h"
#include <stdio.h>

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������</T>
//============================================================
FTrap::FTrap(){
   MO_CLEAR(_pParent);
   _pBlocks = MO_PTR_CREATE(FTrapBlockSet);
}

//============================================================
// <T>�ͷ��������</T>
//============================================================
FTrap::~FTrap(){
   MO_PTR_DELETE(_pBlocks);
}

//============================================================
// <T>��ø��������</T>
//
// @return ���������
//============================================================
FTrap* FTrap::Parent(){
   return _pParent;
}

//============================================================
// <T>���ø��������</T>
//
// @param pParent ���������
//============================================================
void FTrap::SetParent(FTrap* pParent){
   _pParent = pParent;
}

//============================================================
// <T>�ռ��ڴ�顣</T>
//
// @return ���ռ����ڴ�
//============================================================
TAny* FTrap::Alloc(TInt size){
   return Alloc(NULL, size, NULL, 0);
}

//============================================================
// <T>�ռ��ڴ�顣</T>
//
// @param pClassName ������
// @param size �����С
// @param pFileName �����ļ�
// @param line ��������
// @return ����ʵ��ָ��
//============================================================
TAny* FTrap::Alloc(TChar8C* pClassName, TInt size, TChar8C* pFileName, TInt line){
   // �����ڴ�ṹ
   FTrapBlock* pBlock = new FTrapBlock();
   pBlock->pClassName = pClassName;
   pBlock->pMemory = MO_ALLOC(size);
   pBlock->Size = size;
   pBlock->pFileName = pFileName;
   pBlock->Line = line;
   // ��������
   _pBlocks->Set((TInt)pBlock->pMemory, pBlock);
   return pBlock->pMemory;
}

//============================================================
// <T>ɾ���ڴ�顣</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FTrap::Remove(TAny* pMemory){
   FTrapBlock* pBlock = _pBlocks->Get((TInt)pMemory);
   if(NULL != pBlock){
      _pBlocks->Set((TInt)pMemory, NULL);
      MO_PTR_DELETE(pBlock);
   }
}

//============================================================
// <T>�ͷ��ڴ�顣</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FTrap::Free(TAny* pMemory){
   FTrapBlock* pBlock = _pBlocks->Get((TInt)pMemory);
   if(NULL != pBlock){
      _pBlocks->Set((TInt)pMemory, NULL);
      MO_PTR_DELETE(pBlock);
   }
   MO_FREE(pMemory);
}

//============================================================
// <T>����ڴ�顣</T>
// <P>�������δ���յ��ڴ�飬���ӡ���ڴ�й©����</P>
//============================================================
void FTrap::Check(){
   if(!_pBlocks->IsEmpty()){
      // ���δ�ͷŵ�ָ��
      TBool hasLeak = EFalse;
      TSetIteratorC<TInt, FTrapBlock*> iterator = _pBlocks->IteratorC();
      while(iterator.Next()){
         FTrapBlock* pBlock = iterator.Value();
         if(NULL != pBlock){
            hasLeak = ETrue;
            //MO_FATAL(TC("Memory leak. (instance=%s@0x%08X, size=%08d, file=%s(%d))"),
            //      (TCharC*)TFsName(pBlock->pClassName), pBlock->pMemory, pBlock->Size, (TCharC*)TFsFileName(pBlock->pFileName), pBlock->Line);
         }
      }
      // ������ڴ�й¶�����׳�����
      if(hasLeak){
         MO_FATAL(TC("Has memory leak."));
      }
   }
}

MO_NAMESPACE_END
