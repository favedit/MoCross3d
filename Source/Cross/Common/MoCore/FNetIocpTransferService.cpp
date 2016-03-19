#include "MoCrNetTransferIocp.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_WINDOWS

//============================================================
// <T>�����ص��˿ڷ���</T>
//============================================================
FNetIocpTransferService::FNetIocpTransferService(){
}

//============================================================
// <T>�����ص��˿ڷ���</T>
//============================================================
FNetIocpTransferService::~FNetIocpTransferService(){
}

//============================================================
// <T>���������������ݴ��䡣</T>
//
// @return ������
//============================================================
TResult FNetIocpTransferService::OnStartup(){
   // �������Ӽ����߳�
   //TInt serverCount = _config.hosts.Count();
   //for(TInt n = 0; n < serverCount; n++){
   // ���������߳�
   FNetIocpTransferServerThread* pServerThread = MO_CREATE(FNetIocpTransferServerThread);
   pServerThread->SetService(this);
   //pServerThread->SetHost(_config.hosts[n]);
   SNetHost host;
   host.host = TC("*");
   host.port = 900;
   pServerThread->SetHost(host);
   _pServerThreads->Push(pServerThread);
   // �����߳���
   _pThreadGroup->Push(pServerThread);
   //}
   // �����������ݵȴ��߳�
   _pReceiveThread = MO_CREATE(FNetIocpTransferReceiveThread);
   _pReceiveThread->SetService(this);
   _pThreadGroup->Push(_pReceiveThread);
   // �����߳���
   _pThreadGroup->Start();
   return ESuccess;
}

//============================================================
// <T>����һ����������</T>
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
TBool FNetIocpTransferService::AddSockets(TFsNetSocketInfoVector& infos){
   _section.Enter();
   TInt limitSocketCount = _config.limitSocketCount;
   TInt count = infos.Count();
   for(TInt n = 0; n < count; n++){
      // ���������Ϣ
      SNetSocketInfo& info = infos.Get(n);
      // �������
      if(limitSocketCount > 0){
         TInt socketCount = _pSocketsModule->Pool()->UsingCount();
         if(socketCount + 1 > limitSocketCount){
            MO_WARN(TC("Socket pool is full. (count=%d, limit=%d)"), socketCount, limitSocketCount);
            SendLimitNotify(info);
            continue;
         }
      }
      // ���Ӷ˿�
      FNetBufferedSocket* pSocket = _pSocketsModule->LinkHandle(info.handle);
      // ������Ӷ���ʧ�ܣ��رվ�����ܾ�����
      if(NULL == pSocket){
         RNetSocket::Disconnect(info);
         continue;
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
      MO_DEBUG_INFO(TC("Add net socket. (socket=0x%08X, poll=0x%04X(%d), host=%s:%d, handle=%d, index=%d:%d)"),
         pSocket,
         pSocket->ReceivePool()->Handle(), pSocket->ReceivePool()->Count(),
         info.host, info.port, info.handle, pSocket->Index(), pSocket->Serial());
      // ���Ͷ˿�������Ϣ
      SendConnectNotify(pSocket, info.host, info.port);
   }
   _section.Leave();
   return ETrue;
}

#endif // _MO_WINDOWS

MO_NAMESPACE_END
