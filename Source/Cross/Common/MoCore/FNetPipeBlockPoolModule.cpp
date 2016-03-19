#include "MoCrNetPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ݶ��зֿ黺���ģ�顣</T>
//============================================================
FNetPipeBlockPoolModule::FNetPipeBlockPoolModule(){
   _name = TC("Module.NetPipe.Pool");
   _blockLimit = 0;
   _pAllocators = MO_CREATE(FBufferedPipeBlockAllocatorVector);
}

//============================================================
// <T>�������ݶ��зֿ黺���ģ�顣</T>
//============================================================
FNetPipeBlockPoolModule::~FNetPipeBlockPoolModule(){
   MO_DELETE(_pAllocators);
}

//============================================================
// <T>����������Ϣ��</T>
//
// @return ������
//============================================================
TResult FNetPipeBlockPoolModule::LoadConfig(FXmlNode* pConfig){
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
         FBufferedPipeBlockAllocator* pAlloc = MO_CREATE(FBufferedPipeBlockAllocator);
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
FBufferedPipeBlockAllocator* FNetPipeBlockPoolModule::Alloc(TInt blockCapacity){
   MO_ASSERT(blockCapacity > 0);
   // ���Ҷ���
   TInt count = _pAllocators->Count();
   for(TInt n = 0; n < count; n++){
      FBufferedPipeBlockAllocator* pFind = _pAllocators->Get(n);
      if(pFind->BlockCapacity() == blockCapacity){
         return pFind;
      }
   }
   // ��������
   FBufferedPipeBlockAllocator* pAlloc = MO_CREATE(FBufferedPipeBlockAllocator);
   pAlloc->SetBlockCapacity(blockCapacity);
   pAlloc->SetBlockLimit(_blockLimit);
   _pAllocators->Push(pAlloc);
   return pAlloc;
}

//============================================================
// <T>�ͷ����ݶ��зֿ黺��ء�</T>
//============================================================
void FNetPipeBlockPoolModule::Free(FBufferedPipeBlockAllocator* pPool){
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
TResult FNetPipeBlockPoolModule::StatisticsRefresh(){
   TFsDump dump;
   TInt count = _pAllocators->Count();
   for(TInt n = 0; n < count; n++){
      FBufferedPipeBlockAllocator* pAllocator = _pAllocators->Get(n);
      pAllocator->Track(&dump);
   }
   MO_INFO(TC("Pipe block pool statistics.%s"), (TCharC*)dump);
   return ESuccess;
}

MO_NAMESPACE_END
