#ifndef __MO_CM_NET_H__
#define __MO_CM_NET_H__
//------------------------------------------------------------
#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

#ifndef __MO_CM_CLASS_H__
#include "MoCmClass.h"
#endif // __MO_CM_CLASS_H__

#ifndef __MO_CM_MEMORY_H__
#include "MoCmMemory.h"
#endif // __MO_CM_MEMORY_H__

//============================================================
// <T>������־����</T>
//============================================================
#define MO_LOGGER_NET                1
//------------------------------------------------------------
/// @define ���һ��������Ϣ
#ifdef _MO_LOGGER
#define MO_STATIC_NET_DEBUG(M, ...) RLogger::Debug(MO_LOGGER_NET, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_NET_DEBUG(M, ...)        RLogger::Debug(MO_LOGGER_NET, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#else
#define MO_STATIC_NET_DEBUG(M, ...)
#define MO_NET_DEBUG(M, ...)
#endif
//------------------------------------------------------------
#define MO_STATIC_NET_TRACK(M, ...) RLogger::Info (MO_LOGGER_NET, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_STATIC_NET_INFO(M, ...)  RLogger::Info (MO_LOGGER_NET, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_STATIC_NET_WARN(M, ...)  RLogger::Warn (MO_LOGGER_NET, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_STATIC_NET_ERROR(M, ...) RLogger::Error(MO_LOGGER_NET, NULL, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_NET_TRACK(M, ...)        RLogger::Info (MO_LOGGER_NET, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_NET_INFO(M, ...)         RLogger::Info (MO_LOGGER_NET, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_NET_WARN(M, ...)         RLogger::Warn (MO_LOGGER_NET, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)
#define MO_NET_ERROR(M, ...)        RLogger::Error(MO_LOGGER_NET, this, __PRETTY_FUNCTION__, M, ##__VA_ARGS__)

#define MO_NET_HOST_LENGTH      80
#define MO_NET_SOCKET_BUFFER    65536
#define MO_NET_SOCKET_MAX_COUNT 65536

MO_NAMESPACE_BEGIN

//============================================================
#ifndef _MO_WINDOWS
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1u
#endif // INVALID_SOCKET
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif // SOCKET_ERROR
#endif // _MO_WINDOWS

const TInt MoNetHostLength = MO_NET_HOST_LENGTH;
const TInt MoNetSocketCount = 1024*64;
const TInt MoNetSocketMaxPort = 1024*64;
const TInt MoNetBlockSize = 1024*16;

//============================================================
typedef TUint32 TSocket;
MO_BCD_TFIXSTRING(TFsNetHost, TFixString<MoNetHostLength>);
typedef TUint16 TNetPort;

//============================================================
class INetObject;
class INetSocketChannelPipe;
class INetSocketChannel;
class INetSocket;
class INetSocketPool;
class INetConnection;

//============================================================
// <T>���������ࡣ</T>
//============================================================
class MO_CM_DECLARE RNetHost{
public:
   static TInt NetHostToInt(TChar* pHost);
   static TInt NetHostToChar(TInt host, TChar* pHost, TSize length);
};

//============================================================
// <T>����������</T>
//============================================================
struct MO_CM_DECLARE SNetHost{
public:
   TFsNetHost host; // ��������
   TUint16 port;    // �˿�
public:
   //------------------------------------------------------------
   // <T>��������������</T>
   SNetHost(){
   }
   //------------------------------------------------------------
   // <T>��������������</T>
   SNetHost(const SNetHost& value){
      host = (TCharC*)value.host;
      port = value.port;
   }
   //------------------------------------------------------------
   // <T>��������������</T>
   SNetHost(TCharC* pHost, TInt hostPort){
      host = pHost;
      port = (TUint16)hostPort;
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   void operator=(const SNetHost& value){ \
      host = (TCharC*)value.host;
      port = value.port;
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE TFixArray<SNetHost, 16> SNetHostArray;
typedef MO_CM_DECLARE TFixVector<SNetHost, 16> SNetHostVector;

//============================================================
// <T>����˿��¼����͡�</T>
//
// @enum
// @history 100112 MAOCY ����
//============================================================
enum ENetSocketEvent{
   // @member ����
   ENetSocketEvent_Accept = 1,
   // @member ��ȡ
   ENetSocketEvent_Read = 2,
   // @member д��
   ENetSocketEvent_Write = 3
};

//============================================================
// <T>����˿����͡�</T>
//
// @enum
// @history 100112 MAOCY ����
//============================================================
enum ENetSocketType{
   // @member ��������
   ENetSocketEvent_Server = 1,
   // @member �ͻ�����
   ENetSocketType_Client = 2,
   // @member ��������
   ENetSocketType_Accept = 3
};

//============================================================
// <T>����˿ڽ��ܱ�־���͡�</T>
//
// @enum
// @history 100112 MAOCY ����
//============================================================
enum ENetSocketReceiveFlag{
   // @member ���ͽ�ֹ
   ENetSocketReceiveFlag_Disable = 0,
   // @member ���Ϳ���
   ENetSocketReceiveFlag_Free = 1,
   // @member ����æ
   ENetSocketReceiveFlag_Busy = 2
};

//============================================================
// <T>����˿ڷ��ͱ�־���͡�</T>
//
// @enum
// @history 100112 MAOCY ����
//============================================================
enum ENetSocketSendFlag{
   // @member ���ͽ�ֹ
   ENetSocketSendFlag_Disable = 0,
   // @member ���Ϳ���
   ENetSocketSendFlagFree = 1,
   // @member ����æ
   ENetSocketSendFlag_Busy = 2
};

//============================================================
// <T>����˿���Ϣ��</T>
//
// @enum
// @history 100112 MAOCY ����
//============================================================
struct MO_CM_DECLARE SNetAcceptInfo{
   TUint32   handle;                // ���Ӿ��
   TChar     host[MoNetHostLength]; // ����
   TUint32   ip;                    // ��ַ
   TUint16   port;                  // �˿�
};

//============================================================
// <T>����˿���Ϣ��</T>
//
// @enum
// @history 100112 MAOCY ����
//============================================================
struct MO_CM_DECLARE SNetSocketInfo{
   TUint16   type;                  // �������� (ENetSocketType)
   TUint32   handle;                // ���Ӿ��
   TChar     host[MoNetHostLength]; // ����
   TUint32   ip;                    // ��ַ
   TUint16   port;                  // �˿�
   TUint32   remoteIp;              // Զ�˵�ַ
   TUint16   remotePort;            // Զ�˶˿�
   TUint32   receiveFlag;           // ���ձ�־
   TUint64   receiveTotal;          // �ܹ���ȡ���ݳ���
   TDateTime receiveDateTime;       // ������ʱ��
   TUint32   sendFlag;              // ���ͱ�־ (ENetSocketSendFlag)
   TUint64   sendTotal;             // �ܹ���ȡ���ݳ���
   TDateTime sendDateTime;          // �����ʱ��
   TDateTime createDateTime;        // ����ʱ��
   TDateTime updateDateTime;        // ����ʱ��
};

//============================================================
// <T>�������</T>
//
// @face
// @history 091217 MAOCY ����
//============================================================
class MO_CM_DECLARE INetObject{
};

//============================================================
//
// @face
// @history 100112 MAOCY ����
//============================================================
class MO_CM_DECLARE INetSocket{
public:
   //------------------------------------------------------------
   // <T>��������˿ڽӿڡ�</T>
   MO_ABSTRACT ~INetSocket(){
   }
public:
   MO_VIRTUAL INetConnection* Connection() = 0;
   MO_VIRTUAL TSocket Handle() = 0;
   MO_VIRTUAL TCharC* Host() = 0;
   MO_VIRTUAL TUint32 Ip() = 0;
   MO_VIRTUAL TUint16 Port() = 0;
   MO_VIRTUAL TBool IsConnected() = 0;
   MO_VIRTUAL TBool SetReuseAddress(TBool flag) = 0;
   MO_VIRTUAL TBool SetDontLinger(TBool flag) = 0;
   MO_VIRTUAL TBool SetLinger(TBool flag, TInt time = 0) = 0;
   MO_VIRTUAL TBool SetSendTimeout(TInt timeout) = 0;
   MO_VIRTUAL TBool SetReceiveTimeout(TInt timeout) = 0;
   MO_VIRTUAL TBool SetSendBufferSize(TInt size) = 0;
   MO_VIRTUAL TBool SetReceiveBufferSize(TInt size) = 0;
   MO_VIRTUAL TBool SetNonBlock() = 0;
   MO_VIRTUAL TInt Receive(TByte* pBuffer, TInt length) = 0;
   MO_VIRTUAL TInt Send(TByteC* pBuffer, TInt length) = 0;
   MO_VIRTUAL TBool Close() = 0;
};

//============================================================
// <T>����˿ڻ���ؽӿڡ�</T>
//
// @face
// @history 100112 MAOCY ����
//============================================================
class MO_CM_DECLARE INetSocketPool : public INetObject{
public:
   //------------------------------------------------------------
   // <T>��������˿ڻ���ؽӿڡ�</T>
   MO_ABSTRACT ~INetSocketPool(){
   }
public:
   MO_VIRTUAL TInt Handle() = 0;
   MO_VIRTUAL TInt Count() = 0;
   MO_VIRTUAL TBool Add(INetSocket* pSocket, TUint flag) = 0;
   MO_VIRTUAL TBool Modify(INetSocket* pSocket, TUint flag) = 0;
   MO_VIRTUAL TBool Remove(INetSocket* pSocket, TUint flag) = 0;
};

//============================================================
// <T>�������ӽӿڡ�</T>
//
// @face
// @history 100112 MAOCY ����
//============================================================
class MO_CM_DECLARE INetConnection : public INetObject{
public:
   //------------------------------------------------------------
   // <T>�����������ӽӿڡ�</T>
   MO_ABSTRACT ~INetConnection(){
   }
public:
   MO_VIRTUAL void Start() = 0;
   MO_VIRTUAL void Stop() = 0;
};

//============================================================
// <T>����˿ڵĻ��ࡣ</T>
//
// @base
// @history 100112 MAOCY ����
//============================================================
class MO_CM_DECLARE MNetSocket : public INetSocket{
protected:
   INetConnection* _pConnection;
   TFsNetHost _host;
   TBool _isConnected;
   TBool _isBlock;
public:
   MNetSocket();
   MO_ABSTRACT ~MNetSocket();
public:
   MO_VIRTUAL SNetSocketInfo* Info() = 0;
public: // Inherits: INetSocketChannel
   MO_OVERRIDE INetConnection* Connection();
   MO_OVERRIDE TSocket Handle();
   MO_OVERRIDE TCharC* Host();
   MO_OVERRIDE TUint32 Ip();
   MO_OVERRIDE TUint16 Port();
   MO_OVERRIDE TBool IsConnected();
   MO_OVERRIDE TBool SetReuseAddress(TBool flag);
   MO_OVERRIDE TBool SetDontLinger(TBool flag);
   MO_OVERRIDE TBool SetLinger(TBool flag, TInt timeout = 0);
   MO_OVERRIDE TBool SetSendTimeout(TInt timeout);
   MO_OVERRIDE TBool SetReceiveTimeout(TInt timeout);
   MO_OVERRIDE TBool SetSendBufferSize(TInt size);
   MO_OVERRIDE TBool SetReceiveBufferSize(TInt size);
   MO_OVERRIDE TBool SetNonBlock();
   MO_OVERRIDE TInt Receive(TByte* pBuffer, TInt length);
   MO_OVERRIDE TInt Send(TByteC* pBuffer, TInt length);
   MO_OVERRIDE TBool Close();
public:
   void SetConnection(INetConnection* pConnection);
   void SetHandle(TSocket handle);
   void SetHost(TCharC* pHost);
   void SetPort(TUint16 port);
   TBool SendFlag();
   void SetSendFlag(TBool flag);
   TDateTime CreateDateTime();
   void SetCreateDateTime(TDateTime datetime);
};

//============================================================
// <T>�������ӡ�</T>
//
// @class
// @source MNetSocket.cpp
// @history 091207 MAOCY ����
//============================================================
class MO_CM_DECLARE FNetSocket :
      public FInstance,
      public MNetSocket
{
   MO_CLASS_DECLARE_INHERITS(FNetSocket, FInstance);
protected:
   SNetSocketInfo _info;
public:
   FNetSocket();
   FNetSocket(TCharC* pHost, TInt port, TSocket handle);
   MO_ABSTRACT ~FNetSocket();
public:
   MO_OVERRIDE SNetSocketInfo* Info();
public:
   TResult Accept(SNetAcceptInfo* pInfo);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FNetSocket*> FNetSocketList;

//============================================================
// <T>����ͻ������ӡ�</T>
//
// @class
// @source MNetSocket.cpp
// @history 091231 MAOCY ����
//============================================================
class MO_CM_DECLARE FNetClientSocket :
      public FInstance,
      public MNetSocket
{
   MO_CLASS_DECLARE_INHERITS(FNetClientSocket, FInstance);
protected:
   SNetSocketInfo _info;
public:
   FNetClientSocket();
   FNetClientSocket(TCharC* pHost, TInt port);
   MO_OVERRIDE ~FNetClientSocket();
public:
   MO_OVERRIDE SNetSocketInfo* Info();
public:
   TResult Connect();
   TResult Connect(TCharC* pHost, TUint16 port);
   TResult Disconnect();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FNetClientSocket*> FNetClientSocketList;

//============================================================
// <T>�����������ӡ�</T>
//
// @class
// @source MNetSocket.cpp
// @history 091231 MAOCY ����
//============================================================
class MO_CM_DECLARE FNetServerSocket :
      public FInstance,
      public MNetSocket
{
   MO_CLASS_DECLARE_INHERITS(FNetServerSocket, FInstance);
protected:
   SNetSocketInfo _info;
public:
   FNetServerSocket();
   FNetServerSocket(TInt port);
   MO_OVERRIDE ~FNetServerSocket();
public:
   MO_OVERRIDE SNetSocketInfo* Info();
public:
   MO_ABSTRACT TResult Bind();
   MO_ABSTRACT TResult Listen();
   MO_ABSTRACT TResult Connect();
   MO_ABSTRACT TResult Accept(SNetAcceptInfo* pInfo);
   MO_ABSTRACT TResult Disconnect();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FNetServerSocket*> FNetServerSocketList;

//============================================================
// <T>�㲥����ͻ������ӡ�</T>
//
// @class
// @source MNetSocket.cpp
// @history 091231 MAOCY ����
//============================================================
class MO_CM_DECLARE FNetUdpClientSocket :
      public FObject,
      public MNetSocket{
protected:
   SNetSocketInfo _info;
public:
   FNetUdpClientSocket();
   FNetUdpClientSocket(TCharC* pHost, TInt port);
   MO_OVERRIDE ~FNetUdpClientSocket();
public:
   MO_OVERRIDE SNetSocketInfo* Info();
public:
   TBool Connect();
   TBool Connect(TCharC* pHost, TUint16 port);
   TBool Disconnect();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FNetClientSocket*> FNetClientSocketList;

//============================================================
// <T>�㲥�����������ӡ�</T>
//
// @class
// @source MNetSocket.cpp
// @history 091231 MAOCY ����
//============================================================
class MO_CM_DECLARE FNetUdpServerSocket :
      public FObject,
      public MNetSocket{
protected:
   SNetSocketInfo _info;
public:
   FNetUdpServerSocket();
   FNetUdpServerSocket(TInt port);
   MO_OVERRIDE ~FNetUdpServerSocket();
public:
   MO_OVERRIDE SNetSocketInfo* Info();
public:
   TBool Bind();
   TBool Connect();
   TBool Disconnect();
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FNetUdpServerSocket*> FNetUdpServerSocketList;

//============================================================
class MO_CM_DECLARE FNetSocketStorage : public FAtomStorage<INetSocket*>{
protected:
   FNetSocket* _pSockets[MoNetSocketCount];
public:
   FNetSocketStorage();
   ~FNetSocketStorage();
protected: // Inherits: FAtomStorage
   MO_OVERRIDE INetSocket* AtomCreate();
   MO_OVERRIDE void AtomDelete(INetSocket* pSocket);
public:
   INetSocket* Get(TSocket handle);
   INetSocket* Find(TSocket handle);
};

//============================================================
// <T>ֻ���������Ĺ���ӿڡ�</T>
// <P>������Ĺ����ӿڶ�����һ�����࣬��������ʵ����</P>
//
// @manager
// @type T ��������
// @history 091207 MAOCY ����
//============================================================
class MO_CM_DECLARE RNetSocket{
public:
   static void Startup();
   static void Cleanup();
   static TBool Connect(SNetSocketInfo& info);
   static TBool Disconnect(SNetSocketInfo& info);
};

MO_NAMESPACE_END

#endif // __MO_CM_NET_H__
