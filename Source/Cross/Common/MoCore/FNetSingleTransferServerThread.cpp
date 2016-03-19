#include "MoCrNetTransferSingle.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����������Ӽ����߳�ʵ����</T>
//
// @return �߳�ʵ��
//============================================================
FNetSingleTransferServerThread::FNetSingleTransferServerThread(){
}

//============================================================
// <T>�����������Ӽ����߳�ʵ����</T>
//============================================================
FNetSingleTransferServerThread::~FNetSingleTransferServerThread(){
   MO_DELETE(_pServerSocket);
   MO_DELETE(_pCatcher);
}
//============================================================
// <T>�������Ӽ�������</T>
//
// @return ������
//============================================================
TResult FNetSingleTransferServerThread::Process(){
   MO_ASSERT(_pService);
   // ���Ӷ˿�
   _pServerSocket->SetHost(_host.host);
   _pServerSocket->SetPort(_host.port);
   _pServerSocket->Connect();
   MO_DEBUG(TC("Create tcp server. (host=%s:%d, handle=%d)"), (TCharC*)_host.host, _host.port, _pServerSocket->Handle());
   // ��װ��׽��
   _pCatcher->Install();
   // ��������˿�
   while(!IsStop()){
      _pCatcher->Enter();
      if(MO_TRAP_CATCHER(_pCatcher)){
         _pCatcher->Recorded();
         //............................................................
         // ���ն������
         SNetSocketInfo info;
         RType<SNetSocketInfo>::Clear(&info);
         //if(_pServerSocket->Accept(info)){
         //   _pService->AddSocket(info);
         //}else{
         //   MO_FATAL("Accep socket failre.");
         //}
      }else{
         _pCatcher->JumpFinish();
      }
      _pCatcher->Leave();
   }
   return ESuccess;
}

MO_NAMESPACE_END
