#ifdef _MO_LINUX
#include <unistd.h>
#endif
#include <MoCmFormat.h>
#include "MoCrNetEpoll.h"
#include "MoCrNetPipe.h"
#include "MoCrNetTransfer.h"

#define MO_TAG_PROPERTY  TC("Property")
#define MO_PTR_NAME      TC("name")
#define MO_VAL_SHARE_KEY TC("share_key")

MO_NAMESPACE_BEGIN

//============================================================
// <T>��������ͨѶ�����ʵ����</T>
//
// @return ����ͨѶ�����ʵ��Clo
//============================================================s
FNetTransferService::FNetTransferService(){
   _name = TC("Service.Transfer");
   // ����Э��
   _config.protocol = ENetProtocol_Router;
#ifdef _MO_WINDOWS
   // ����������ɶ˿ڻ����
   FNetIocp* pEpoll = MO_CREATE(FNetIocp);
   pEpoll->Setup();
   _pReceivePool = pEpoll;
   MO_CLEAR(_pSendPool);
#endif
#ifdef _MO_LINUX
   // ����������ɶ˿ڻ����
   FNetEpoll* pEpoll = MO_CREATE(FNetEpoll);
   pEpoll->Create(MO_MD_NTS_SOCKETPOLL);
   _pReceivePool = pEpoll;
   // ����������ɶ˿ڻ����
   FNetEpoll* pSendEpoll = MO_CREATE(FNetEpoll);
   pSendEpoll->Create(MO_MD_NTS_SOCKETPOLL);
   _pSendPool = pSendEpoll;
#endif
   // ��ʼ������
   _pServerThreads = MO_CREATE(FNetTransferServerThreadVector);
   MO_CLEAR(_pSocketsModule);
   MO_CLEAR(_pQueueStorage);
   MO_CLEAR(_pInputQueue);
   // ��ʼ���߳�
   MO_CLEAR(_pReceiveThread);
   MO_CLEAR(_pSendThread);
   _pReceiveNodeQueue = MO_CREATE(FQueue, MO_MD_NTS_RECEIVE_PIPE_CAPACITY);
   _pThreadGroup = MO_CREATE(FThreadGroup);
   _currentReceiveIndex = 0;
}

//============================================================
// <T>��������ͨѶ�����ʵ����</T>
//============================================================
FNetTransferService::~FNetTransferService(){
   MO_DELETE(_pReceivePool);
   MO_DELETE(_pSendPool);
   MO_DELETE(_pServerThreads);
   MO_DELETE(_pReceiveNodeQueue);
   MO_DELETE(_pThreadGroup);
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param pConfig ������Ϣ
// @return ������
//============================================================
TResult FNetTransferService::LoadConfig(FXmlNode* pConfig){
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      if(pNode->IsName(TC("Property"))){
         // ��ȡ����
         if(pNode->IsAttribute(MO_PTR_NAME, TC("mode"))){
            // ��ȡ������ʽ
            TCharC* pMode = pNode->Text();
            if(RString::Equals(TC("multipool"), pMode)){
               MO_DEBUG(TC("Load module(%s) property. (mode=%s)"), (TCharC*)_name, TC("multipool"));
               _config.multiMode = ETrue;
            }
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("protocol"))){
            // ��ȡ������ʽ
            TCharC* pProtocol = pNode->Text();
            if(RString::Equals(TC("message"), pProtocol)){
               MO_DEBUG(TC("Load module(%s) property. (protocol=%s)"), (TCharC*)_name, TC("message"));
               _config.protocol = ENetProtocol_Message;
            }else if(RString::Equals(TC("router"), pProtocol)){
               MO_DEBUG(TC("Load module(%s) property. (protocol=%s)"), (TCharC*)_name, TC("router"));
               _config.protocol = ENetProtocol_Router;
            }
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("link_type"))){
            // ��ȡ������������ʽ
            TCharC* pLinkType = pNode->Text();
            if(RString::Equals(TC("create"), pLinkType)){
               MO_DEBUG(TC("Load module(%s) property. (link_type=%s)"), (TCharC*)_name, TC("create"));
            }else if(RString::Equals(TC("connect"), pLinkType)){
               MO_DEBUG(TC("Load module(%s) property. (link_type=%s)"), (TCharC*)_name, TC("connect"));
            }
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("data_check"))){
            // ��ȡ�����鷽ʽ
            _config.dataCheck = pNode->TextAsBool();
            MO_DEBUG(TC("Load module(%s) property. (data_check=%d)"), (TCharC*)_name, _config.dataCheck);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("data_compress"))){
            // ��ȡ����ѹ����ʽ
            _config.dataCompress = pNode->TextAsBool();
            MO_DEBUG(TC("Load module(%s) property. (data_compress=%d)"), (TCharC*)_name, _config.dataCompress);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("data_mask"))){
            // ��ȡ������ܷ�ʽ
            _config.dataMask = pNode->TextAsBool();
            MO_DEBUG(TC("Load module(%s) property. (data_mask=%d)"), (TCharC*)_name, _config.dataMask);
         }else if(pNode->IsAttribute(MO_PTR_NAME, MO_VAL_SHARE_KEY)){
            // ��ȡ�������ļ�·��
            pNode->GetText(_config.shareKeyFile, MO_FS_FILENAME_LENGTH);
            MO_DEBUG(TC("Load module(%s) property. (share_key=%s)"), (TCharC*)_name, _config.shareKeyFile);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("udp_support"))){
            // ��ȡ�Ƿ�֧�ֹ㲥
            _config.udpSupport = RBool::IsTrue(pNode->Text());
            MO_DEBUG(TC("Load module(%s) property. (udp_support=%d)"), (TCharC*)_name, _config.udpSupport);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("udp_host"))){
            // ��ȡ�㲥��������
            pNode->GetText(_config.udpHost, sizeof(_config.udpHost));
            MO_DEBUG(TC("Load module(%s) property. (udp_host=%s)"), (TCharC*)_name, _config.udpHost);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("udp_port"))){
            // ��ȡ�㲥�����˿�
            _config.udpPort = (TUint16)pNode->TextAsInt();
            MO_DEBUG(TC("Load module(%s) property. (udp_port=%d)"), (TCharC*)_name, _config.udpPort);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("limit_socket_count"))){
            // ��ȡ������������
            _config.limitSocketCount = pNode->TextAsInt();
            MO_DEBUG(TC("Load module(%s) property. (limit_socket_count=%d)"), (TCharC*)_name, _config.limitSocketCount);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("limit_client_count"))){
            // ��ȡ�ͻ�����������
            _config.limitClientCount = pNode->TextAsInt();
            MO_DEBUG(TC("Load module(%s) property. (limit_socket_count=%d)"), (TCharC*)_name, _config.limitSocketCount);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("receive_first_timeout"))){
            // ��ȡ�����״ν��ճ�ʱ
            _config.receiveFirstTimeout = pNode->TextAsInt() * 1000;
            MO_DEBUG(TC("Load module(%s) property. (receive_first_timeout=%d)"), (TCharC*)_name, _config.receiveFirstTimeout);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("receive_timeout"))){
            // ��ȡ������ճ�ʱ
            _config.receiveTimeout = pNode->TextAsInt() * 1000;
            MO_DEBUG(TC("Load module(%s) property. (receive_timeout=%d)"), (TCharC*)_name, _config.receiveTimeout);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("send_timeout"))){
            // ��ȡ���緢�ͳ�ʱ
            _config.sendTimeout = pNode->TextAsInt() * 1000;
            MO_DEBUG(TC("Load module(%s) property. (send_timeout=%d)"), (TCharC*)_name, _config.sendTimeout);
         }else if(pNode->IsAttribute(MO_PTR_NAME, TC("receive_thread_count"))){
            // ��ȡ�����߳�����
            _config.receiveThreadCount = pNode->TextAsInt();
            MO_DEBUG(TC("Load module(%s) property. (receive_thread_count=%d)"), (TCharC*)_name, _config.receiveThreadCount);
         }
      }else if(pNode->IsName(TC("Host"))){
         // ��ȡ������������
         SNetHost host;
         host.host = pNode->Get(TC("host"));
         host.port = (TUint16)pNode->GetAsInt(TC("port"));
         _config.hosts.Push(host);
         MO_DEBUG(TC("Load module(%s) property. (host=%s, port=%d)"), (TCharC*)_name, (TCharC*)host.host, host.port);
      }
   }
   // ���ù�������
   if(_pSocketsModule != NULL){
      _pSocketsModule->SetSendTimeout(_config.sendTimeout);
      _pSocketsModule->SetReceiveTimeout(_config.receiveTimeout);
   }
   return ESuccess;
}

//============================================================
INetSocketPool* FNetTransferService::SocketPool(){
   return _pReceivePool;
}

//============================================================
INetSocketPool* FNetTransferService::SendPool(){
   return _pSendPool;
}

//============================================================
FQueue* FNetTransferService::ReceiveNodeQueue(){
    return _pReceiveNodeQueue;
}

//============================================================
void FNetTransferService::SetSocketsModule(FNetBufferedSocketModule* pStorage){
   MO_ASSERT(pStorage);
   _pSocketsModule = pStorage;
}

//============================================================
void FNetTransferService::SetQueueStorage(FSharedNetQueueStorage* pStorage){
   MO_ASSERT(pStorage);
   _pQueueStorage = pStorage;
   _pInputQueue = pStorage->Connection()->InputQueue();
}

//============================================================
// <T>���������������ݴ��䡣</T>
//============================================================
TResult FNetTransferService::OnStartup(){
   // �������Ӽ����߳�
   TInt serverCount = _config.hosts.Count();
   for(TInt n = 0; n < serverCount; n++){
      // ���������߳�
      FNetTransferServerThread* pServerThread = MO_CREATE(FNetTransferServerThread);
      pServerThread->SetService(this);
      pServerThread->SetHost(_config.hosts[n]);
      _pServerThreads->Push(pServerThread);
      // �����߳���
      _pThreadGroup->Push(pServerThread);
   }
   // �����������ݵȴ��߳�
   _pReceiveThread = MO_CREATE(FNetTransferReceiveThread);
   _pReceiveThread->SetService(this);
   _pThreadGroup->Push(_pReceiveThread);
   // �����������ݷ����߳�
   _pSendThread = MO_CREATE(FNetTransferSendThread);
   _pSendThread->SetService(this);
   _pThreadGroup->Push(_pSendThread);
   // �����߳���
   _pThreadGroup->Start();
   return ESuccess;
}

//============================================================
// <T>ֹͣ�����������ݴ��䡣</T>
//============================================================
TResult FNetTransferService::OnShutdown(){
   // �ر��߳���
   _pThreadGroup->Stop();
   // �رռ���
   TInt count = _pServerThreads->Count();
   for(TInt n = 0; n < count; n++){
      FNetTransferServerThread* pServerThread = _pServerThreads->Get(n);
      pServerThread->Socket()->Disconnect();
   }
   return ESuccess;
}

//============================================================
// <T>����һ���������ӡ�</T>
// <P>����������Ч���ݣ�
//     - handle: ���
//     - ip:     ��ַ
//     - port:   �˿�
//     - host:   ����
//     - index:  ����
//     - serial: ����
// </P>
//
// @param info ����������Ϣ
//============================================================
FNetBufferedSocket* FNetTransferService::InnerAddSocket(SNetSocketInfo& info){
   TInt limitSocketCount = _config.limitSocketCount;
   // �������
   if(limitSocketCount > 0){
      TInt socketCount = _pSocketsModule->Pool()->UsingCount();
      if(socketCount + 1 > limitSocketCount){
         MO_WARN(TC("Socket pool is full. (count=%d, limit=%d)"), socketCount, limitSocketCount);
         _pCommander->SendLimitNotify(info);
         return NULL;
      }
   }
   // ���Ӷ˿�
   FNetBufferedSocket* pSocket = _pSocketsModule->LinkHandle(info.handle);
   // ������Ӷ���ʧ�ܣ��رվ�����ܾ�����
   if(NULL == pSocket){
      RNetSocket::Disconnect(info);
      return NULL;
   }
   // ������Ϣ
   pSocket->SetInfo(&info);
   pSocket->SetNonBlock();
   pSocket->SetSendBufferSize(0);
   // ���ӵ�����˿�
   pSocket->SetReceivePool(_pReceivePool);
   pSocket->SetSendPool(_pSendPool);
   // ��������
   _pSocketsModule->OpenSocket(pSocket);
   MO_DEBUG_INFO(TC("Add net socket. (socket=0x%08X, poll=0x%04X(%d)|0x%04X(%d), host=%s:%d, handle=%d, index=%d:%d)"),
         pSocket,
         pSocket->ReceivePool()->Handle(), pSocket->ReceivePool()->Count(),
         pSocket->SendPool()->Handle(), pSocket->SendPool()->Count(),
         info.host, info.port, info.handle, pSocket->Index(), pSocket->Serial());
   // ���Ͷ˿�������Ϣ
   _pCommander->SendConnectNotify(pSocket, info.host, info.port);
   return pSocket;
}

//============================================================
// <T>����һ���������ӡ�</T>
//
// @param info ����������Ϣ
//============================================================
FNetBufferedSocket* FNetTransferService::AddSocket(SNetSocketInfo& info){
   _section.Enter();
   FNetBufferedSocket* pSocket = InnerAddSocket(info);
   _section.Leave();
   return pSocket;
}

//============================================================
// <T>���Ӷ���������ӡ�</T>
//
// @param infos �������Ӽ���
//============================================================
TBool FNetTransferService::AddSockets(TFsNetSocketInfoVector& infos){
   TBool result = ETrue;
   _section.Enter();
   TInt count = infos.Count();
   for(TInt n = 0; n < count; n++){
      // ���������Ϣ
      SNetSocketInfo& info = infos.Get(n);
      FNetBufferedSocket* pSocket = InnerAddSocket(info);
      if(NULL == pSocket){
         result = EFalse;
         break;;
      }
   }
   _section.Leave();
   return result;
}

//============================================================
// <T>�ر�ͨѶ�˿ڣ����ҷ���һ���Ͽ�֪ͨ</T>
//
// @param pSocket �˿�
// @return ������
//============================================================
TBool FNetTransferService::CloseSocketWithNotify(FNetBufferedSocket* pSocket){
   MO_ASSERT(pSocket);
   // ���������Ϣ
   TCharC* pHost = pSocket->Host();
   TUint port = pSocket->Port();
   TInt handle = pSocket->Handle();
   // �ر�����
   _section.Enter();
   TBool connected = pSocket->IsConnected();
   if(connected){
      // ���Ͷ˿ڹر���Ϣ
      _pCommander->SendDisconnectNotify(pSocket, pHost, (TUint16)port);
      // �Ͽ�����
      TInt receivePoolHandle = 0;
      TInt receivePoolCount = 0;
      INetSocketPool* pReceivePool = pSocket->ReceivePool();
      if(pReceivePool != NULL){
         receivePoolHandle = pReceivePool->Handle();
         receivePoolCount = pReceivePool->Count();
      }
      TInt sendPoolHandle = 0;
      TInt sendPoolCount = 0;
      INetSocketPool* pSendPool = pSocket->SendPool();
      if(pSendPool != NULL){
         sendPoolHandle = pSendPool->Handle();
         sendPoolCount = pSendPool->Count();
      }
      MO_DEBUG_INFO(TC("Remove client soclet. (socket=0x%08X, poll=0x%04X(%d)|0x%04X(%d), host=%s:%d, handle=%d(%s))"),
            pSocket, receivePoolHandle, receivePoolCount, sendPoolHandle, sendPoolCount,
            pHost, port, handle, TFsDateTime(pSocket->CreateDateTime()).Format());
      _pSocketsModule->CloseSocket(pSocket);
   }
   _section.Leave();
   return EFalse;
}

//============================================================
// <T>�ر�ͨѶ�˿ڣ����ҷ���һ���Ͽ�֪ͨ</T>
//
// @param pSocket �˿�
// @return ������
//============================================================
TBool FNetTransferService::CloseSocketWithoutNotify(FNetBufferedSocket* pSocket){
   MO_ASSERT(pSocket);
   // ���������Ϣ
   TCharC* pHost = pSocket->Host();
   TUint port = pSocket->Port();
   TInt handle = pSocket->Handle();
   // �ر�����
   _section.Enter();
   TBool connected = pSocket->IsConnected();
   if(connected){
      // �Ͽ�����
      MO_DEBUG_INFO(TC("Remove client soclet. (socket=0x%08X, poll=0x%04X|0x%04X, host=%s:%d, handle=%d(%s))"),
            pSocket, pSocket->ReceivePool()->Handle(), pSocket->SendPool()->Handle(),
            pHost, port, handle, TFsDateTime(pSocket->CreateDateTime()).Format());
      _pSocketsModule->CloseSocket(pSocket);
   }
   _section.Leave();
   return EFalse;
}

//============================================================
// <T>����һ������·�ɡ�</T>
//
// @param pSocket ����˿�
// @param pRouter ����·��
// @return ������
//============================================================
TBool FNetTransferService::SendSocketRouter(FNetBufferedSocket* pSocket, TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ������Ϣ
   TNetTransfer transfer(pRouter);
   TNetTransferHead& head = transfer.TransferHead();
   if(NULL != pSocket){
      head.SetHandle(pSocket->Handle());
      head.SetHost(pSocket->Ip(), pSocket->Port());
      head.SetSocket(pSocket->Index(), pSocket->Serial());
   }
   if(!_pInputQueue->PushRouter(&transfer)){
#ifdef _MO_DEBUG
      TChar dump[MO_FS_DUMP_LENGTH];
      TChar format[MO_FS_DUMP_LENGTH];
      MO_FATAL(TC("Send transfer socket message failure.\n%s%s"),
            pRouter->Dump(dump, MO_FS_DUMP_LENGTH),
            pRouter->DumpMemory(format, MO_FS_DUMP_LENGTH));
#endif
      return EFalse;
   }
   MO_DEBUG(TC("Send socket router. (length=%d)"), transfer.NetHead().Length());
   return ETrue;
}

//============================================================
// <T>����һ�����紫�䡣</T>
//
// @param pSocket ����˿�
// @param pTransfer ���紫��
// @return ������
//============================================================
TBool FNetTransferService::SendSocketTransfer(FNetBufferedSocket* pSocket, TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   // ������Ϣ
   TNetTransferHead& head = pTransfer->TransferHead();
   if(NULL != pSocket){
      head.SetHandle(pSocket->Handle());
      head.SetHost(pSocket->Ip(), pSocket->Port());
      head.SetSocket(pSocket->Index(), pSocket->Serial());
   }
   if(!_pInputQueue->PushRouter(pTransfer)){
#ifdef _MO_DEBUG
      TChar dump[MO_FS_DUMP_LENGTH];
      TChar format[MO_FS_DUMP_LENGTH];
      MO_FATAL(TC("Send transfer socket message failure.\n%s%s"),
            pTransfer->Dump(dump, MO_FS_DUMP_LENGTH),
            pTransfer->DumpMemory(format, MO_FS_DUMP_LENGTH));
#endif
      return EFalse;
   }
   MO_DEBUG(TC("Send socket transfer. (length=%d)"), pTransfer->NetHead().Length());
   return ETrue;
}

//============================================================
// <T>����һ�����紫�䡣</T>
//
// @param pTransfer ���紫��
// @return ������
//============================================================
TResult FNetTransferService::ProcessTransfer(TNetTransfer* pTransfer){
   return _pCommander->ProcessTransfer(pTransfer);
}

//============================================================
// <T>�ȴ������������</T>
//
// @return ������
//============================================================
TBool FNetTransferService::Wait(){
   _pThreadGroup->Wait();
   return ETrue;
}

//============================================================
// <T>ͳ��ˢ�¡�</T>
//
// @return ������
//============================================================
TResult FNetTransferService::StatisticsRefresh(){
   TFsDump dump;
   if(_pSendThread != NULL){
      dump.AppendFormat(TC("\n   Send    total=%24s"), RInt::FormatCapacity(_pSendThread->SendTotal(), TFsCode(), TFsCode::Size()));
   }
   if(_pReceiveThread != NULL){
      dump.AppendFormat(TC("\n   Receive total=%24s"), RInt::FormatCapacity(_pReceiveThread->ReceiveTotal(), TFsCode(), TFsCode::Size()));
   }
   MO_INFO(TC("Transfer service statistics."), (TCharC*)dump);
   return ESuccess;
}

MO_NAMESPACE_END
