#ifdef _MO_LINUX
#include <unistd.h>
#endif
#include "MoCrNetTransfer.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������Ӽ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetTransferServerThread::FNetTransferServerThread(){
   _code = TC("STV");
   _name = TC("Thread.Transfer.Server");
   _pServerSocket = MO_CREATE(FNetServerSocket);
   _pCatcher = MO_CREATE(FNetTransferCatcher);
   MO_CLEAR(_pService);
}

//============================================================
// <T>�����������Ӽ����߳�ʵ����</T>
//============================================================
FNetTransferServerThread::~FNetTransferServerThread(){
   MO_DELETE(_pServerSocket);
   MO_DELETE(_pCatcher);
}

//============================================================
// <T>���ô������</T>
//
// @param pService �������
//============================================================
void FNetTransferServerThread::SetService(FNetTransferService* pService){
   MO_ASSERT(pService);
   _pService = pService;
}

//============================================================
// <T>���������</T>
//
// @return ����
//============================================================
SNetHost& FNetTransferServerThread::Host(){
   return _host;
}

//============================================================
// <T>����������</T>
//
// @param host ����
//============================================================
void FNetTransferServerThread::SetHost(const SNetHost& host){
   _host = host;
}

//============================================================
// <T>��ö˿ڡ�</T>
//
// @return �˿�
//============================================================
FNetServerSocket* FNetTransferServerThread::Socket(){
   return _pServerSocket;
}

//============================================================
// <T>�������Ӽ�������</T>
//
// @return ������
//============================================================
TResult FNetTransferServerThread::Process(){
   MO_ASSERT(_pService);
   // ���Ӷ˿�
   _pServerSocket->SetHost(_host.host);
   _pServerSocket->SetPort(_host.port);
   _pServerSocket->Connect();
   _pServerSocket->SetNonBlock();
   MO_DEBUG(TC("Create tcp server. (host=%s:%d, handle=%d)"),
         (TCharC*)_host.host, _host.port, _pServerSocket->Handle());
   // ������Ϣ
   TFsNetSocketInfoVector infos;
   TInt infoSize = infos.Size();
   // ��װ��׽��
   _pCatcher->Install();
   // ��������˿�
   while(!IsStop()){
      _pCatcher->Enter();
      if(MO_TRAP_CATCHER(_pCatcher)){
         _pCatcher->Recorded();
         //............................................................
         // ���ն������
         infos.Clear();
         for(TInt n = 0; n < infoSize; n++){
            SNetSocketInfo info;
            RType<SNetSocketInfo>::Clear(&info);
            //if(_pServerSocket->Accept(info)){
            //   infos.Push(info);
            //}else{
            //   break;
            //}
         }
         // ������������
         if(!infos.IsEmpty()){
            _pService->AddSockets(infos);
         }else{
            MO_LIB_MICRO_SLEEP(MO_MD_NTS_ACCEPT_INTERVAL);
         }
      }else{
         _pCatcher->JumpFinish();
      }
      _pCatcher->Leave();
   }
   return ESuccess;
}

MO_NAMESPACE_END
