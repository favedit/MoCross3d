#include "MoCrNetIocp.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_WINDOWS

//============================================================
// <T>������ɶ˿��̡߳�</T>
//============================================================
//FNetIocpQueryThread::FNetIocpQueryThread(INetServer* pNetServer){
//   _pNetServer = pNetServer;
//}
//
////============================================================
//// <T>�����̡߳�</T>
////
//// @return ������
////============================================================
//TInt FNetIocpQueryThread::Process(){
//   MO_INFO(_T("Iocp query thread process."));
//   FNetIocpServer* pNetServer = (FNetIocpServer*)_pNetServer;
//   FCompletionPort* pCompletionPort = pNetServer->CompletionPort();
//   INetDataProcessor* pDataProcessor = pNetServer->DataProcessor();
//   PPtr pHandle = pCompletionPort->Handle();
//   // ѭ������
//   while(!_stop){
//      TUint32 transdBytes = 0;
//      TBool result = GetQueuedCompletionStatus(pHandle, &transdBytes, (PULONG_PTR)&_completionKey, &_pOverlap, INFINITE);
//      MO_DEBUG(_T("Get queued completion status. (result=%d)"), result);
//      // ��������
//      if(EFalse == result){
//         continue;
//      }
//      // �����¼�
//      if(NULL != pDataProcessor){
//         _pIocpOverlap = CONTAINING_RECORD(_pOverlap, SIocpOverlapped, Overlapped);
//         switch(_pIocpOverlap->OperateCode){
//            case ENetIocpOperate_Read:
//               // ����������¼�
//               pDataProcessor->DoRead(_pIocpOverlap->pSocket, _pIocpOverlap->Buffer, transdBytes);
//              break;
//            case ENetIocpOperate_Write:
//               // ����д�����¼�
//               pDataProcessor->DoWrite(_pIocpOverlap->pSocket, _pIocpOverlap->Buffer, transdBytes);
//               break;
//         }
//      }
//   }
//   return ESuccess;
//}

#endif // _MO_WINDOWS

MO_NAMESPACE_END
