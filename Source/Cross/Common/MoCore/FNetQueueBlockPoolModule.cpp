#include "MoCrNetPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ݶ��зֿ黺���ģ�顣</T>
//============================================================
FNetQueueBlockPoolModule::FNetQueueBlockPoolModule(){
   _name = TC("Module.NetQueue.Pool");
   _blockLimit = 0;
   _pAllocators = MO_CREATE(FBufferedQueueBlockAllocatorVector);
}

//============================================================
// <T>�������ݶ��зֿ黺���ģ�顣</T>
//============================================================
FNetQueueBlockPoolModule::~FNetQueueBlockPoolModule(){
   MO_DELETE(_pAllocators);
}

//============================================================
// <T>����������Ϣ��</T>
//
// @return ������
//============================================================
TResult FNetQueueBlockPoolModule::LoadConfig(FXmlNode* pConfig){
   // ����������Ϣ
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      if(pNode->IsAttribute(TC("name"), TC("block_limit"))){
         // ���طֿ�����
         _blockLimit = pNode->TextAsInt();
         MO_ASSERT(_blockLimit > 0);
         MO_DEBUG(TC("Load module(%s) property. (block_limit=%d)"), (TCharC*)_name, _blockLimit);
      }else if(pNode->IsName(TC("Allocator"))){
         // �������
         TInt blockCapacity = pNode->GetAsInt(TC("block_capacity"));
         MO_ASSERT(blockCapacity > 0);
         TInt blockLimit = pNode->GetAsInt(TC("block_limit"));
         MO_ASSERT(blockLimit > 0);
         // ��������
         FBufferedQueueBlockAllocator* pAlloc = MO_CREATE(FBufferedQueueBlockAllocator);
         pAlloc->SetBlockCapacity(blockCapacity);
         pAlloc->SetBlockLimit(blockLimit);
         _pAllocators->Push(pAlloc);
      }
   }
   return ESuccess;
}

//============================================================
// <T>���ݷֿ������ռ�һ�����ݶ��зֿ黺��ء�</T>
//
// @param blockCapacity �ֿ�����
// @return ���ݶ��зֿ黺���
//============================================================
FBufferedQueueBlockAllocator* FNetQueueBlockPoolModule::Alloc(TInt blockCapacity){
   MO_ASSERT(blockCapacity > 0);
   // ���Ҷ���
   TInt count = _pAllocators->Count();
   for(TInt n = 0; n < count; n++){
      FBufferedQueueBlockAllocator* pFind = _pAllocators->Get(n);
      if(pFind->BlockCapacity() == blockCapacity){
         return pFind;
      }
   }
   // ��������
   FBufferedQueueBlockAllocator* pAlloc = MO_CREATE(FBufferedQueueBlockAllocator);
   pAlloc->SetBlockCapacity(blockCapacity);
   pAlloc->SetBlockLimit(_blockLimit);
   _pAllocators->Push(pAlloc);
   return pAlloc;
}

//============================================================
// <T>�ͷ����ݶ��зֿ黺��ء�</T>
//============================================================
void FNetQueueBlockPoolModule::Free(FBufferedQueueBlockAllocator* pPool){
   MO_ASSERT(pPool);
   if(_pAllocators->Contains(pPool)){
      _pAllocators->Remove(pPool);
      MO_DELETE(pPool);
   }else{
      MO_FATAL(TC("Free pool object is not exists."));
   }
}

//============================================================
// <T>ͳ��ˢ�´���</T>
//
// @return ������
//============================================================
TResult FNetQueueBlockPoolModule::StatisticsRefresh(){
   TFsDump dump;
   TInt count = _pAllocators->Count();
   for(TInt n = 0; n < count; n++){
      FBufferedQueueBlockAllocator* pAllocator = _pAllocators->Get(n);
      pAllocator->Track(&dump);
   }
   MO_INFO(TC("Queue block pool statistics.%s"), (TCharC*)dump);
   return ESuccess;
}

MO_NAMESPACE_END
