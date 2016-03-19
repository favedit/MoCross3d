#include "MoCrNetIocp.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_WINDOWS

//============================================================
// <T>�����ص��˿ڷ���</T>
//============================================================
FNetIocp::FNetIocp(){
   MO_CLEAR(_pHandle);
   _count = 0;
}

//============================================================
// <T>�����ص��˿ڷ���</T>
//============================================================
FNetIocp::~FNetIocp(){
}

//============================================================
// <T>��þ����</T>
//
// @return ���
//============================================================
TInt FNetIocp::Handle(){
   return 0;
}

//============================================================
// <T>��ø�����</T>
//
// @return ����
//============================================================
TInt FNetIocp::Count(){
   return _count;
}

//============================================================
// <T>���ô���</T>
//============================================================
void FNetIocp::Setup(){
   MO_INFO(TC("Iocp server setup."));
   // �������߳���
   //SYSTEM_INFO systemInfo;
   //GetSystemInfo(&systemInfo);
   //TInt threadCount = MO_MIN(systemInfo.dwNumberOfProcessors, 1
   //TInt threadCount = 1;
   // �����˿�
   _pHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
}

//============================================================
// <T>���������������á�</T>
//
// @param pSocket ����˿�
// @param flag ��־
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetIocp::Add(INetSocket* pSocket, TUint flag){
   // ��þ��
   MO_ASSERT(_pHandle);
   MO_ASSERT(pSocket);
   FNetIocpSocket* pIocpSocket = (FNetIocpSocket*)pSocket;
   TSocket handle = pIocpSocket->Handle();
   TAny* pHandle = CreateIoCompletionPort((TAny*)handle, _pHandle, (ULONG_PTR)pIocpSocket, 1); 
   _count++;
   return ETrue;
}

//============================================================
// <T>�޸������������á�</T>
//
// @param pSocket ����˿�
// @param flag ��־
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetIocp::Modify(INetSocket* pSocket, TUint flag){
   return ETrue;
}

//============================================================
// <T>ɾ�������������á�</T>
//
// @param pSocket ����˿�
// @param flag ��־
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetIocp::Remove(INetSocket* pSocket, TUint flag){
   _count--;
   return ETrue;
}

////============================================================
//// <T>�����������๤����</T>
////
//// @return �๤��
////============================================================
//INetServerFactory* FNetIocp::Factory(){
//   return _pFactory;
//}
//
////============================================================
//// <T>�����ɶ˿ڡ�</T>
////
//// @return ��ɶ˿�
////============================================================
//FCompletionPort* FNetIocp::CompletionPort(){
//   return _pCompletionPort;
//}
//
////============================================================
//// <T>��÷������ӡ�</T>
////
//// @return ��������
////============================================================
//FNetServerSocket* FNetIocp::ServerSocket(){
//   return _pServerSocket;
//}
//
////============================================================
//// <T>��÷����̡߳�</T>
////
//// @return �����߳�
////============================================================
//FThread* FNetIocp::ServerThread(){
//   return _pServerThread;
//}
//
////============================================================
//// <T>������ݴ���ӿڡ�</T>
////
//// @return ���ݴ���ӿ�
////============================================================
//INetDataProcessor* FNetIocp::DataProcessor(){
//   return _pDataProcessor;
//}
//
////============================================================
//// <T>����һ���µ��������ӡ�</T>
////============================================================
//void FNetIocp::DoAccept(FNetSocket* pSocket){
//   _pSockets->Push((FNetIocpSocket*)pSocket);
//   // ׷�ӵ���ɶ˿���
//   _pCompletionPort->Append((PPtr)pSocket->NativeSocket());
//}
//
////============================================================
//// <T>��ʼ����</T>
////============================================================
//void FNetIocp::Start(){
//   // ������������
//   _pServerSocket = _pFactory->CreateServerSocket(this);
//   _pServerSocket->Bind(_port);
//   _pServerSocket->Listen();
//   MO_DEBUG(this, _T("Start net IOCP server. (port=%d, query=%d)"), _port, threadCount);
//   // �������ݴ����
//   _pDataProcessor = _pFactory->CreateDataProcessor(this);
//   // ������ɶ˿�
//   _pCompletionPort = MO_CREATE(FCompletionPort, threadCount);
//   _pCompletionPort->Append((PPtr)_pServerSocket->NativeSocket());
//   // ���������߳�
//   _pServerThread = (FNetIocpThread*)_pFactory->CreateServerThread(this);
//   _pServerThread->Start();
//   // ���������߳�
//   while(--threadCount >= 0){
//      FNetIocpQueryThread* pThread = (FNetIocpQueryThread*)_pFactory->CreateQueryThread(this);
//      pThread->Start();
//   }
//}
//
////============================================================
//// <T>��������</T>
////============================================================
//void FNetIocp::Stop(){
//}
//
////============================================================
//void FNetIocp::SetDataProcessor(INetDataProcessor* pDataProcessor){
//   _pDataProcessor = pDataProcessor;
//}

#endif // _MO_WINDOWS

MO_NAMESPACE_END
