#ifdef _MO_LINUX
#include <unistd.h>
#endif
#include "MoCrNetConnection.h"

MO_NAMESPACE_BEGIN

//============================================================
FNetMessageMachine::FNetMessageMachine(){
   // ��������
   _pConnection = MO_CREATE(FNetMessageConnection);
   _pConnection->Create();
   // ���������߳�
   _pReceiveThread = MO_CREATE(FNetMessageReceiveThread);
   // ����������
   _pHanldess = MO_CREATE(FNetMessageHandlesVector, MO_NETMESSAGE_COUNT);
   _pHanldess->SetCount(MO_NETMESSAGE_COUNT);
   // ע������
   _pReceiveThread->Register(_pConnection);
}

//============================================================
FNetMessageMachine::~FNetMessageMachine(){
   _pConnection->Disconnect();
   MO_DELETE(_pConnection);
   // ɾ�����д���������
   if(!_pHanldess->IsEmpty()){
      TVectorIteratorC<FNetMessageHandles*> iterator = _pHanldess->IteratorC();
      while(iterator.Next()){
         FNetMessageHandles* pHandles = *iterator;
         MO_DELETE(pHandles);
      }
   }
   MO_DELETE(_pHanldess);
};

//============================================================
FNetMessageConnection* FNetMessageMachine::Connection(){
   return _pConnection;
}

//============================================================
FNetMessageReceiveThread* FNetMessageMachine::ReceiveThread(){
   return _pReceiveThread;
}

//============================================================
TBool FNetMessageMachine::MessageUnregister(TInt code){
   FNetMessageHandles* pHandles = _pHanldess->Get(code);
   if(NULL == pHandles){
      return EFalse;
   }
   _pHanldess->Set(code, NULL);
   MO_DELETE(pHandles);
   return ETrue;
}

//============================================================
TBool FNetMessageMachine::Connect(TCharC* pHost, TUint16 port){
   return _pConnection->Connect(pHost, port);
}

//============================================================
TBool FNetMessageMachine::PushMessage(TNetMessage* pMessage){
   return _pConnection->PushMessage(pMessage);
}

//============================================================
TBool FNetMessageMachine::Startup(){
   _pReceiveThread->Start();
   return ETrue;
}

//============================================================
TBool FNetMessageMachine::ProcessMessage(){
   TNetMessageBuffer message;
   if(_pConnection->PopupMessage(&message)){
      // ������Ϣ
      TInt code = message.MessageHead().Code();
      FNetMessageHandles* pHandles = _pHanldess->Get(code);
      if(NULL != pHandles){
         // ��ע�����Ϣ���������
         pHandles->Process(_pConnection, &message);
      }else{
         // δ������Ϣ
         TChar dump[MO_FS_DUMP_LENGTH];
         MO_ERROR(TC("Unknown message. (%s)"), message.Dump(dump, MO_FS_DUMP_LENGTH));
      }
      return ETrue;
   }
   return ETrue;
}

//============================================================
TBool FNetMessageMachine::Process(){
   while(ETrue){
      ProcessMessage();
      MO_LIB_SLEEP(1);
   }
   return ETrue;
}

//============================================================
TBool FNetMessageMachine::Shutdown(){
   _pReceiveThread->Stop();
   return ETrue;
}

MO_NAMESPACE_END
