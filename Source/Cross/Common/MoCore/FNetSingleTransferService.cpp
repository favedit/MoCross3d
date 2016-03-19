#include "MoCrNetTransferSingle.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_WINDOWS

//============================================================
// <T>�����ص��˿ڷ���</T>
//============================================================
FNetSingleTransferService::FNetSingleTransferService(){
}

//============================================================
// <T>�����ص��˿ڷ���</T>
//============================================================
FNetSingleTransferService::~FNetSingleTransferService(){
}

//============================================================
// <T>���������������ݴ��䡣</T>
//
// @return ������
//============================================================
TResult FNetSingleTransferService::OnStartup(){
   // �������Ӽ����߳�
   TInt serverCount = _config.hosts.Count();
   for(TInt n = 0; n < serverCount; n++){
      // ���������߳�
      FNetSingleTransferServerThread* pServerThread = MO_CREATE(FNetSingleTransferServerThread);
      pServerThread->SetService(this);
      pServerThread->SetHost(_config.hosts[n]);
      _pServerThreads->Push(pServerThread);
      // �����߳���
      _pThreadGroup->Push(pServerThread);
   }
   // �����������ݷ����߳�
   _pSendThread = MO_CREATE(FNetSingleTransferSendThread);
   _pSendThread->SetService(this);
   _pThreadGroup->Push(_pSendThread);
   // �����߳���
   _pThreadGroup->Start();
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
FNetBufferedSocket* FNetSingleTransferService::InnerAddSocket(SNetSocketInfo& info){
   TInt limitSocketCount = _config.limitSocketCount;
   // �������
   if(limitSocketCount > 0){
      TInt socketCount = _pSocketsModule->Pool()->UsingCount();
      if(socketCount + 1 > limitSocketCount){
         MO_WARN(TC("Socket pool is full. (count=%d, limit=%d)"), socketCount, limitSocketCount);
         SendLimitNotify(info);
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
   // ��������
   _pSocketsModule->OpenSocket(pSocket);
   MO_DEBUG_INFO(TC("Add net socket. (socket=0x%08X, host=%s:%d, handle=%d, index=%d:%d)"),
         pSocket, info.host, info.port, info.handle, pSocket->Index(), pSocket->Serial());
   // ���������߳�
   FNetSingleSocketReceiveThread* pReceiveThread = MO_CREATE(FNetSingleSocketReceiveThread);
   pReceiveThread->SetService(this);
   pReceiveThread->SetSocket(pSocket);
   pReceiveThread->Start();
   // ���������߳�
   FNetSingleSocketSendThread* pSendThread = MO_CREATE(FNetSingleSocketSendThread);
   pSendThread->SetService(this);
   pSendThread->SetSocket(pSocket);
   pSendThread->Start();
   // ���Ͷ˿�������Ϣ
   SendConnectNotify(pSocket, info.host, info.port);
   return pSocket;
}

#endif // _MO_WINDOWS

MO_NAMESPACE_END
