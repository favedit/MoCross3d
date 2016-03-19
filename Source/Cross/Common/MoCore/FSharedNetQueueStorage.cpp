#include "MoCrNetPipe.h"
#include "MoCrNetSocket.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ӷ��󣬲���Ҫ������</T>
// <P>�Ժ�ʹ��ǰ��Ҫ������������ܵ���С��</P>
//
// @return ��ǰʵ��ָ��
//============================================================
FSharedNetQueueStorage::FSharedNetQueueStorage(){
   _name = TC("Storage.NetQueue");
   // ��ʼ�����ж���
   _capacity = 0;
   _blockCapacity = 0;
   MO_CLEAR(_pAllocator);
   // �����ܵ�
   _pConnection = MO_CREATE(FNetBufferedQueueConnection);
}

//============================================================
// <T>�������Ӷ���</T>
//============================================================
FSharedNetQueueStorage::~FSharedNetQueueStorage(){
   MO_DELETE(_pConnection);
}

//============================================================
// <T>����������Ϣ��</T>
//
// @return ������
//============================================================
TResult FSharedNetQueueStorage::LoadConfig(FXmlNode* pConfig){
   // ����������Ϣ
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next(TC("Property"))){
      FXmlNode* pNode = *iterator;
      if(pNode->IsAttribute(TC("name"), TC("capacity"))){
         _capacity = pNode->TextAsInt();
         MO_ASSERT(_capacity > 0);
         MO_DEBUG(TC("Load module(%s) property. (capacity=%d)"), (TCharC*)_name, _capacity);
      }else if(pNode->IsAttribute(TC("name"), TC("block_capacity"))){
         _blockCapacity = pNode->TextAsInt();
         MO_ASSERT(_blockCapacity > 0);
         MO_DEBUG(TC("Load module(%s) property. (output_capacity=%d)"), (TCharC*)_name, _blockCapacity);
      }
   }
   // �ռ�һ���ռ���
   _pAllocator = RNetQueueBlockPoolModule::Instance().Alloc(_blockCapacity);
   // ���ùܵ�
   _pConnection->Setup(_capacity, _pAllocator);
   return ESuccess;
}

//============================================================
// <T>����ն��е�ָ�롣</T>
//
// @return �ն��е�ָ�롣
//============================================================
FNetBufferedQueueConnection* FSharedNetQueueStorage::Connection(){
   return _pConnection;
}

MO_NAMESPACE_END
