#include "MoCrNetTransferEpoll.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_LINUX

//============================================================
// <T>�����������Ӽ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetEpollTransferServerThread::FNetEpollTransferServerThread(){
}

//============================================================
// <T>�����������Ӽ����߳�ʵ����</T>
//============================================================
FNetEpollTransferServerThread::~FNetEpollTransferServerThread(){
   MO_DELETE(_pServerSocket);
   MO_DELETE(_pCatcher);
}
//============================================================
// <T>�������Ӽ�������</T>
//
// @return ִ�н��
//============================================================
TInt FNetEpollTransferServerThread::Process(){
   MO_ASSERT(_pService);
   // ���Ӷ˿�
   _pServerSocket->SetHost(_host.host);
   _pServerSocket->SetPort(_host.port);
   _pServerSocket->Connect();
   _pServerSocket->SetNonBlock();
   MO_DEBUG("Create tcp server. (host=%s:%d, handle=%d)",
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
            if(_pServerSocket->Accept(info)){
               infos.Push(info);
            }else{
               break;
            }
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

#endif // _MO_LINUX

MO_NAMESPACE_END
