#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���컺����п顣</T>
//============================================================
FStreamBlockAllocator::FStreamBlockAllocator(){
   _blockCapacity = 0;
   _blockLimit = 4;
}

//============================================================
// <T>����������п顣</T>
//
// @param capacity ��������
//============================================================
FStreamBlockAllocator::~FStreamBlockAllocator(){
   // ɾ������ʹ�ö���
   if(!_pUsingItems->IsEmpty()){
      TListIteratorC<FStreamBlock*> iterator = _pUsingItems->IteratorC();
      while(iterator.Next()){
         Delete(*iterator);
      }
      _pUsingItems->Clear();
   }
   // ɾ���������ɶ���
   if(!_pFreeItems->IsEmpty()){
      TListIteratorC<FStreamBlock*> iterator = _pFreeItems->IteratorC();
      while(iterator.Next()){
         Delete(*iterator);
      }
      _pFreeItems->Clear();
   }
}

//============================================================
// <T>ɾ���ܵ��顣</T>
//
// @param pBlock �ܵ���
//============================================================
void FStreamBlockAllocator::Delete(FStreamBlock* pBlock){
   MO_DELETE(pBlock);
}

//============================================================
// <T>�ռ�һ���ܵ��顣</T>
//
// @return �ܵ���
//============================================================
FStreamBlock* FStreamBlockAllocator::Alloc(){
   FStreamBlock* pBlock = NULL;
   //............................................................
   _locker.Enter();
   // ����Ƿ��п��ж���
   if(_pFreeItems->IsEmpty()){
      FStreamBlock* pAlloc = Create();
      pAlloc->ForceCapacity(_blockCapacity);
      Store(pAlloc);
   }
   // �ռ�һ���ֿ�
   pBlock = AllocFirst();
   _locker.Leave();
   //............................................................
   // ����Ϊд����
   pBlock->FlipForWrite();
   return pBlock;
}

//============================================================
// <T>�ͷ�һ���ܵ��顣</T>
//
// @param pBlock �ܵ���
//============================================================
void FStreamBlockAllocator::Free(FStreamBlock* pBlock){
   MO_ASSERT(pBlock);
   FStreamBlock* pFree = NULL;
   //............................................................
   _locker.Enter();
   // �ͷŷֿ�
   FreeLast(pBlock);
   // �������
   TInt freeCount = _pFreeItems->Count();
   if(freeCount > 0){
      if(freeCount > _blockLimit){
         pFree = _pFreeItems->Shift();
      }
   }
   _locker.Leave();
   //............................................................
   // ɾ������
   if(NULL != pFree){
      Delete(pFree);
   }
}

//============================================================
// <T>������Ϣ��</T>
//
// @param pTrack ��������
//============================================================
void FStreamBlockAllocator::Track(MString* pTrack){
   // ������Ϣ
   //TFsDump dump;
   //TInt index = 0;
   //............................................................
   TInt usingCount = _pUsingItems->Count();
   TInt64 lengthRead = 0;
   TInt64 lengthWrite = 0;
   TListIteratorC<FStreamBlock*> iteratorUsing = _pUsingItems->IteratorC();
   while(iteratorUsing.Next()){
      FStreamBlock* pBlock = *iteratorUsing;
      lengthRead += pBlock->LengthTotalRead();
      lengthWrite += pBlock->LengthTotalWrite();
      //if(index > 0){
      //   dump.Append("\n");
      //}
      //dump.AppendFormat("   %4d - U:", index);
      //pBlock->Track(&dump);
      //index++;
   }
   //............................................................
   TInt freeCount = _pFreeItems->Count();
   //TListIteratorC<FStreamBlock*> iteratorFree = _pFreeItems->IteratorC();
   //while(iteratorFree.Next()){
      //FStreamBlock* pBlock = *iteratorFree;
      //if(index > 0){
      //   dump.Append("\n");
      //}
      //dump.AppendFormat("   %4d - F:", index);
      //pBlock->Track(&dump);
      //index++;
   //}
   //............................................................
   // ׷����Ϣ
   TInt count = usingCount + freeCount;
   pTrack->AppendFormat(TC("\n   ") MO_FMT_OBJECT_NAME TC(" block_capacity=%d, count=%d, using_count=%d, free_count=%d, read_length=%ld, write_length=%ld"),
         TC("Buffered stream block"), _blockCapacity, count, usingCount, freeCount, lengthRead, lengthWrite);
   //if(count > 0){
   //   pTrack->AppendFormat("\n%s", (TCharC*)dump);
   //}
}

MO_NAMESPACE_END
