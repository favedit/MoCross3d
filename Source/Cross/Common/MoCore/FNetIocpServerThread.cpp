#include "MoCrNetIocp.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_WINDOWS
/*
//============================================================
// <T>�����ص��˿ڷ���</T>
//============================================================
FNetIocpServerThread::FNetIocpServerThread(INetServer* pNetServer){
   _pNetServer = pNetServer;
}

//============================================================
// <T>�����ص��˿ڷ���</T>
//============================================================
TInt FNetIocpServerThread::Process(){
   MO_LOGGER_LINK(_T("FNetIocpServerThread::Process"));
   INetServerFactory* pFactory = _pNetServer->Factory();
   FNetServerSocket* pServerSocket = _pNetServer->ServerSocket();
   while(!_stop){
      // ���տͻ�������
      FNetIocpSocket* pSocket = (FNetIocpSocket*)pFactory->CreateClientSocket(_pNetServer);
      if(!pServerSocket->Accept(pSocket)){
         MO_FREE(pSocket);
         continue;
      }
      MO_DEBUG(this, _T("Accept new socket (handle=0x%08X)"), pSocket->NativeSocket());
      // ��ֹ���ӻ�������
      pSocket->DisableBuffer();
      // ������ɶ˿�
      _pNetServer->DoAccept(pSocket);
      // ���ͽ��յ�����
      SIocpOverlapped& overlapped = pSocket->Overlapped();;
      ZeroMemory(&overlapped.Overlapped, sizeof(overlapped.Overlapped));
      ZeroMemory(&overlapped.Buffer, sizeof(overlapped.Buffer));
      overlapped.OperateCode = ENetIocpOperate_Read;
      overlapped.WsaBuffer.buf = overlapped.Buffer;
      overlapped.WsaBuffer.len = sizeof(overlapped.Buffer);
      overlapped.ClientSocket = (PPtr)pSocket->NativeSocket();
      // ���յ�һ������
      TUint32 recvNumBtes = 0;
      TUint32 flags = 0;
      TInt result = WSARecv(pSocket->NativeSocket(), &overlapped.WsaBuffer, 1, &recvNumBtes, &flags, &overlapped.Overlapped, NULL);
      if(SOCKET_ERROR == result && (ERROR_IO_PENDING != WSAGetLastError())){
         closesocket(pSocket->NativeSocket());
         MO_THROW(result);
      }
   }
   return ESuccess;
}
*/
#endif

MO_NAMESPACE_END
