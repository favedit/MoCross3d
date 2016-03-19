#ifndef __MO_CR_NET_IOCP_H__
#define __MO_CR_NET_IOCP_H__
//------------------------------------------------------------
#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_NET_SOCKET_H__
#include "MoCrNetSocket.h"
#endif // __MO_CR_NET_SOCKET_H__

MO_NAMESPACE_BEGIN

#ifdef _MO_WINDOWS

class FNetIocpSocket;

////============================================================
//#define MO_IOCP_BUFFER_MAX_SIZE 8192

//============================================================
// <T>��ɶ˿ڲ�������ö�١�</T>
//
// @history 091218 MAOCY ����
//============================================================
enum ENetIocpOperate{
   ENetIocpOperate_Accept = 1,
   ENetIocpOperate_Read = 2,
   ENetIocpOperate_Write = 3,
};

//============================================================
// <T>��ɶ˿ڲ�ѯ��Ϣ��</T>
//============================================================
struct SIocpData{
   // Ԥ����ͷ
   OVERLAPPED Overlapped;
   // �˿ھ��
   FNetIocpSocket* pSocket;
   char *buff; // I/O����ʹ�õĻ����� 
   int nLen; // buff��������ʹ�õģ���С 
   ULONG nSequenceNumber; // ��I/O�����к� 
   ENetIocpOperate OperateCode; // �������� 
   SIocpData *pNextData; 
   //TByte Buffer[MO_IOCP_BUFFER_MAX_SIZE];
   //WSABUF WsaBuffer;
   //TInt TotalBytes;
   //TInt SendBytes;
   ////ENetIocpOperate OperateCode;
   //PPtr ClientSocket;
   //FNetSocket* pSocket;
};

//============================================================
// <T>��ɶ˿ڵĿͻ��������ӡ�</T>
//
// @history 091218 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetIocpSocket : public FNetBufferedSocket{
protected:
   SIocpData _data;
public:
   FNetIocpSocket();
public:
   SIocpData& Data();
public:
   MO_OVERRIDE TBool Startup();
   MO_OVERRIDE TBool Shutdown();
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FNetIocpSocket*> FNetIocpSocketList;

//============================================================
// <T>�����������ӡ�</T>
//
// @class
// @source MNetSocket.cpp
// @history 091231 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetIocpServerSocket : public FNetServerSocket{
public:
   FNetIocpServerSocket();
   MO_ABSTRACT ~FNetIocpServerSocket();
public:
   MO_OVERRIDE TResult Bind();
   MO_OVERRIDE TResult Listen();
   MO_OVERRIDE TResult Connect();
   MO_OVERRIDE TResult Accept(SNetSocketInfo& info);
   MO_OVERRIDE TResult Disconnect();
};

//============================================================
// <T>������ɶ˿ڷ�������</T>
//
// @history 091218 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetIocp :
      public FObject,
      public INetSocketPool{
protected:
   TAny* _pHandle;
   TInt _count;
public:
   FNetIocp();
   MO_ABSTRACT ~FNetIocp();
public:
   void Setup();
public:
   TAny* NativeHandle(){
      return _pHandle;
   }
public: // Inherits: INetSocketPool
   MO_OVERRIDE TInt Handle();
   MO_OVERRIDE TInt Count();
   MO_OVERRIDE TBool Add(INetSocket* pSocket, TUint flag);
   MO_OVERRIDE TBool Modify(INetSocket* pSocket, TUint flag);
   MO_OVERRIDE TBool Remove(INetSocket* pSocket, TUint flag);
};

////============================================================
//// <T>������ɶ˿ڷ�������</T>
////
//// @history 091218 MAOCY ����
////============================================================
//class MO_CR_DECLARE FNetIocpServerThread :
//      public FThread{
//protected:
//   INetServer* _pNetServer;
//public:
//   MO_OVERRIDE( FNetIocpServerThread(INetServer* pNetServer) );
//public:
//   MO_OVERRIDE( TInt Process() );
//};
//
////============================================================
//// <T>��ɶ˿ڷ����̡߳�</T>
////
//// @history 091217 MAOCY ����
////============================================================
//class MO_CR_DECLARE FNetIocpQueryThread :
//      public FThread{
//protected:
//   INetServer* _pNetServer;
//public:
//   MO_OVERRIDE( FNetIocpQueryThread(INetServer* pNetServer) );
//public:
//   void SetServer(INetServer* pNetServer);
//   MO_OVERRIDE( TInt Process() );
//};
//
////============================================================
//// <T>��ɶ˿ڷ����̡߳�</T>
////
//// @history 091217 MAOCY ����
////============================================================
//class MO_CR_DECLARE FNetIocpSendThread :
//      public FThread{
//protected:
//   INetServer* _pNetServer;
//   //PULONG_PTR _completionKey;
//   //OVERLAPPED* _pOverlap;
//   SIocpOverlapped* _pIocpOverlap;
//public:
//   MO_OVERRIDE( FNetIocpSendThread(INetServer* pNetServer) );
//public:
//   void SetServer(INetServer* pNetServer);
//   MO_OVERRIDE( TInt Process() );
//};

#endif // _MO_WINDOWS

MO_NAMESPACE_END

#endif // __MO_CR_NET_IOCP_H__
