#include "MoCrNetPipe.h"
#include "MoCrNetSocket.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����׽���ģ�����</T>
//
// @return ��ǰ����ָ�롣
//============================================================
FNetBufferedSocketModule::FNetBufferedSocketModule(){
   // ��ʼ�����ж���
   _name = TC("Module.NetSockets");
   _socketCount = 0;
   _socketCapacity = 1024 * 1024 * 4;
   _socketReceiveBuffer = 1024 * 64;
   _socketSendBuffer = 1024 * 64;
   _socketSerial = 0;
   _blockCapacity = 0;
   _pHandles = MO_CREATE(FNetBufferedSocketSet);
   _pPool = MO_CREATE(FNetBufferedSocketPool);
   _sendTimeout = 0;
   _receiveTimeout = 0;
}

//============================================================
// <T>�����׽���ģ�����</T>
//
// @return �޷���ֵ
//============================================================
FNetBufferedSocketModule::~FNetBufferedSocketModule(){
   MO_DELETE(_pHandles);
   if(NULL != _pPool){
      _pPool->Release();
      MO_DELETE(_pPool);
   }
}

//============================================================
// <T>����������Ϣ��</T>
//
// @return ������
//============================================================
TResult FNetBufferedSocketModule::OnLoadConfig(FXmlNode* pConfig){
   // ��ȡ����
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next(TC("Property"))){
      FXmlNode* pNode = *iterator;
      if(pNode->IsAttribute(TC("name"), TC("socket_count"))){
         _socketCount = pNode->TextAsInt();
         MO_DEBUG(TC("Load module(%s) property. (socket_count=%d)"), (TCharC*)_name, _socketCount);
      }else if(pNode->IsAttribute(TC("name"), TC("socket_capacity"))){
         _socketCapacity = pNode->TextAsInt();
         MO_DEBUG(TC("Load module(%s) property. (socket_capacity=%d)"), (TCharC*)_name, _socketCapacity);
      }else if(pNode->IsAttribute(TC("name"), TC("socket_receive_buffer"))){
         _socketReceiveBuffer = pNode->TextAsInt();
         MO_DEBUG(TC("Load module(%s) property. (socket_receive_buffer=%d)"), (TCharC*)_name, _socketReceiveBuffer);
      }else if(pNode->IsAttribute(TC("name"), TC("socket_send_buffer"))){
         _socketSendBuffer = pNode->TextAsInt();
         MO_DEBUG(TC("Load module(%s) property. (socket_send_buffer=%d)"), (TCharC*)_name, _socketSendBuffer);
      }else if(pNode->IsAttribute(TC("name"), TC("block_capacity"))){
         _blockCapacity = pNode->TextAsInt();
         MO_DEBUG(TC("Load module(%s) property. (block_capacity=%d)"), (TCharC*)_name, _blockCapacity);
      }
   }
   return ESuccess;
}

//============================================================
// <T>��ʼ������</T>
//
// @return ������
//============================================================
TResult FNetBufferedSocketModule::OnInitialize(){
   // ��ùܵ��ֿ��ռ���
   FBufferedPipeBlockAllocator* pAllocator = RNetPipeBlockPoolModule::Instance().Alloc(_blockCapacity);
   // �����˿ڶ���
   _sectionPool.Enter();
   for(TInt n = 0; n < _socketCount; n++){
      // �������Ӷ���
      FNetBufferedSocket* pSocket = MO_CREATE(FNetBufferedSocket);
      // �洢����
      TInt index = _pPool->Store(pSocket);
      pSocket->SetIndex((TUint16)index);
      pSocket->NetInfo()->receiveBufferSize = (TUint32)_socketReceiveBuffer;
      pSocket->NetInfo()->sendBufferSize = (TUint32)_socketSendBuffer;
      pSocket->LinkAllocator(_socketCapacity, pAllocator);
   }
   _sectionPool.Leave();
   return ESuccess;
}

//============================================================
// <T>���ݾ������һ���������ӡ�</T>
// <P>��������������򷵻ؿ�ָ�롣</P>
//
// @param handle ���
// @return �������Ӷ���
//============================================================
FNetBufferedSocket* FNetBufferedSocketModule::LinkHandle(TUint32 handle){
   FNetBufferedSocket* pSocket = NULL;
   // ���Ҷ���
   _sectionSet.Enter();
   pSocket = _pHandles->Find(handle);
   _sectionSet.Leave();
   // ��������
   if(NULL == pSocket){
      // �ռ�����
      _sectionPool.Enter();
      if(_pPool->HasFreeItem()){
         pSocket = _pPool->AllocFirst();
      }
      _sectionPool.Leave();
      // �洢����
      if(NULL != pSocket){
         _sectionSet.Enter();
         _pHandles->Set(handle, pSocket);
         _sectionSet.Leave();
      }else{
         MO_ERROR(TC("Alloc socket failure. (count=%d, useing_count=%d, free_count=%d)"),
               _pPool->Count(), _pPool->UsingCount(), _pPool->FreeCount());
      }
   }
   return pSocket;
}

//============================================================
// <T>���ݴ��룬�����������</T>
//
// @param handle ���
// @return �������Ӷ���
//============================================================
FNetBufferedSocket* FNetBufferedSocketModule::FindHandle(TUint32 handle){
   FNetBufferedSocket* pSocket = NULL;
   // ���ݾ���������˿�
   _sectionSet.Enter();
   pSocket = _pHandles->Find(handle);
   _sectionSet.Leave();
   // ����Ƿ���������������˿�
   if(NULL != pSocket){
      if(!pSocket->IsProcessing()){
         pSocket = NULL;
      }
   }
   return pSocket;
}

//============================================================
// <T>��������λ�ã������������</T>
//
// @param index ����λ��
// @return �������Ӷ���
//============================================================
FNetBufferedSocket* FNetBufferedSocketModule::FindIndex(TUint16 index){
   FNetBufferedSocket* pSocket = NULL;
   // ���������������˿�
   _sectionPool.Enter();
   pSocket = _pPool->Storage()->Nvl(index, NULL);
   _sectionPool.Leave();
   // ����Ƿ���������������˿�
   if(NULL != pSocket){
      if(!pSocket->IsProcessing()){
         pSocket = NULL;
      }
   }
   return pSocket;
}

//============================================================
// <T>���������ӡ�</T>
//
// @param pSocket ��������
//============================================================
void FNetBufferedSocketModule::OpenSocket(FNetBufferedSocket* pSocket){
   MO_ASSERT(pSocket);
   // ��������
   _socketSerial++;
   pSocket->Startup();
   pSocket->SetSerial((TUint16)_socketSerial);
}

//============================================================
// <T>�ر��������ӡ�</T>
//
// @param pSocket ��������
//============================================================
void FNetBufferedSocketModule::CloseSocket(FNetBufferedSocket* pSocket){
   MO_ASSERT(pSocket);
   // �ر�����
   TUint32 handle = pSocket->Handle();
   pSocket->Shutdown();
   // �ͷž��
   _sectionSet.Enter();
   MO_ASSERT(_pHandles->Get(handle) == pSocket);
   _pHandles->Remove(handle);
   _sectionSet.Leave();
   // �ͷŶ���
   _sectionPool.Enter();
   MO_ASSERT(_pPool->Storage()->Get(pSocket->Index()) == pSocket);
   _pPool->FreeLast(pSocket);
   _sectionPool.Leave();
}

//============================================================
// <T>ˢ�´���</T>
//
// @return ������
//============================================================
TResult FNetBufferedSocketModule::TriggerRefresh(TTimeTick currentTick){
   // ���˿ڣ��鿴�Ƿ��зǷ���Ϣ
//   TDateTime current = RDateTime::Current();
//   TListIteratorC<FNetBufferedSocket*> iterator = _pPool->UsingItems()->IteratorC();
//   while(iterator.Next()){
//      FNetBufferedSocket* pSocket = *iterator;
//      SNetSocketInfo* pInfo = pSocket->Info();
//      // ��鷢�ͳ�ʱ
//      if(_sendTimeout > 0){
//         TTimeTick sendTick = current - pInfo->sendDateTime;
//         if(sendTick > _sendTimeout){
//            MO_WARN("   Socket send timeout. (socket=0x%08X, send_timeout=%d, send_tick=%d)", pSocket, _sendTimeout, sendTick);
//         }
//      }
//      // �����ճ�ʱ
//      if(_receiveTimeout > 0){
//         TTimeTick receiveTick = current - pInfo->receiveDateTime;
//         if(receiveTick > _receiveTimeout){
//            MO_WARN("   Socket receive timeout. (socket=0x%08X, send_timeout=%d, send_tick=%d)", pSocket, _receiveTimeout, receiveTick);
//         }
//      }
//   }
   return ESuccess;
}

//============================================================
// <T>ͳ��ˢ�´���</T>
//
// @return ������
//============================================================
TResult FNetBufferedSocketModule::StatisticsRefresh(){
   // ��ʾһ����Ϣ
   TInt count = _pPool->Count();
   TInt usingCount = _pPool->UsingCount();
   TInt freeCount = _pPool->FreeCount();
   MO_INFO(TC("Buffered socket statistics. (name=%s, count=%d, using_count=%d, free_count=%d)"), (TCharC*)_name, count, usingCount, freeCount);
   // ���˿ڣ��鿴�Ƿ��зǷ���Ϣ
   TDateTime current = RDateTime::Current();
   TListIteratorC<FNetBufferedSocket*> iterator = _pPool->UsingItems()->IteratorC();
   while(iterator.Next()){
      FNetBufferedSocket* pSocket = *iterator;
      SNetSocketInfo* pInfo = pSocket->Info();
      // ��鷢�ͳ�ʱ
      if(_sendTimeout > 0){
         TTimeTick sendTick = current - pInfo->sendDateTime;
         if(sendTick > _sendTimeout){
            MO_WARN(TC("   Socket send timeout. (socket=0x%08X, send_timeout=%d, send_tick=%d)"), pSocket, _sendTimeout, sendTick);
         }
      }
      // �����ճ�ʱ
      if(_receiveTimeout > 0){
         TTimeTick receiveTick = current - pInfo->receiveDateTime;
         if(receiveTick > _receiveTimeout){
            MO_WARN(TC("   Socket receive timeout. (socket=0x%08X, send_timeout=%d, send_tick=%d)"), pSocket, _receiveTimeout, receiveTick);
         }
      }
   }
   return ESuccess;
}

MO_NAMESPACE_END
