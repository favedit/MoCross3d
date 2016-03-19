#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���컺����п顣</T>
//============================================================
FStreamBlockPool::FStreamBlockPool(){
   _capacity = 0;
   _blockCapacity = 0;
   MO_CLEAR(_pAllocator);
   _pBlocks = MO_CREATE(FStreamBlockList);
}

//============================================================
// <T>����������п顣</T>
//
// @param capacity ��������
//============================================================
FStreamBlockPool::~FStreamBlockPool(){
   Reset();
   MO_DELETE(_pBlocks);
}

//============================================================
// <T>�ռ�һ���ܵ��顣</T>
//
// @return �ܵ���
//============================================================
FStreamBlock* FStreamBlockPool::Alloc(){
   FStreamBlock* pBlock = NULL;
   //............................................................
   _locker.Enter();
   // ���������
   TInt blockCount = _pBlocks->Count() + 1;
   TInt capacity = _blockCapacity * (blockCount + 1);
   if(capacity > _capacity){
      MO_ERROR(TC("Capacity is too small. (capacity=%d, block_capacity=%d, block_count=%d, block_alloc=%d)"), _capacity, _blockCapacity, blockCount, capacity);
   }else{
      // �ռ�һ���ֿ����
      pBlock = _pAllocator->Alloc();
      _pBlocks->Push(pBlock);
   }
   _locker.Leave();
   //............................................................
   return pBlock;
}

//============================================================
// <T>�ͷ�һ���ܵ��顣</T>
//
// @param pBlock �ܵ���
//============================================================
void FStreamBlockPool::Free(FStreamBlock* pBlock){
   MO_ASSERT(pBlock);
   //............................................................
   _locker.Enter();
   // �ͷŷֿ�
   if(_pBlocks->Contains(pBlock)){
      _pBlocks->Remove(pBlock);
      _pAllocator->Free(pBlock);
   }else{
      MO_ERROR(TC("Free block is not exists. (capacity=%d, block_capacity=%d, block_count=%d)"), _capacity, _blockCapacity, _pBlocks->Count());
   }
   _locker.Leave();
   //............................................................
}

//============================================================
// <T>�������ݡ�</T>
//
// @return ������
//============================================================
TBool FStreamBlockPool::Reset(){
   _locker.Enter();
   // �ͷ������ڴ��
   TListIteratorC<FStreamBlock*> iterator = _pBlocks->IteratorC();
   while(iterator.Next()){
      FStreamBlock* pBlock = *iterator;
      _pAllocator->Free(pBlock);
   }
   _pBlocks->Clear();
   _locker.Leave();
   return ETrue;
}

//============================================================
// <T>������Ϣ��</T>
//
// @param pTrack ��������
//============================================================
void FStreamBlockPool::Track(MString* pTrack){
   pTrack->AppendFormat(TC("Buffered queue dump. (capacity=%d\n"), _capacity);
   TListIteratorC<FStreamBlock*> iterator = _pBlocks->IteratorC();
   while(iterator.Next()){
      FStreamBlock* pBlock = *iterator;
      pTrack->Append(TC("   "));
      pBlock->Track(pTrack);
      pTrack->Append(TC("\n"));
   }
}

MO_NAMESPACE_END
