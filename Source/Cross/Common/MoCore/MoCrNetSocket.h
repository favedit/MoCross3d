#ifndef __MO_CR_NET_SOCKET_H__
#define __MO_CR_NET_SOCKET_H__

#ifndef __MO_CM_NET_H__
#include <MoCmNet.h>
#endif // __MO_CM_NET_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_MODULE_H__
#include "MoCrModule.h"
#endif // __MO_CR_MODULE_H__

#ifndef __MO_CR_NET_PIPE_H__
#include "MoCrNetPipe.h"
#endif // __MO_CR_NET_PIPE_H__

#define MO_SVC_SOCKET_RECEIVE 1024*64
#define MO_SVC_SOCKET_SEND    1024*64

MO_NAMESPACE_BEGIN

//============================================================
typedef TUint32 TNetSerial;
typedef TUint32 TNetTick;

//============================================================
class FSharedNetPipe;
class FNetBufferedQueueConnection;

//============================================================
// <T>��������������Ϣ��</T>
//
// @history 100309 MAOCY ����
//============================================================
struct MO_CR_DECLARE SNetBufferedSocket : public SNetSocketInfo{
   TUint16   index;                       // �˿�����
   TUint16   serial;                      // �˿�����
   TUint32   receiveCount;                // ���մ���
   TUint32   receiveSerial;               // ��������
   TTimeTick receiveTick;                 // ����ʱ��
   TUint32   receiveBufferSize;           // ���ջ���ߴ�
   TUint32   sendCount;                   // ���ʹ���
   TTimeTick sendTick;                    // ����ʱ��
   TUint32   sendSerial;                  // ��������
   TUint32   sendBufferSize;              // ���ͻ���ߴ�
   TBool     udpSupport;                  // �Ƿ�֧�ֹ㲥Э��
   TChar     udpHost[MoNetHostLength];    // �㲥����
   TUint32   udpAddress;                  // �㲥��ַ
   TUint16   udpPort;                     // �㲥�˿�
};

//============================================================
// <T>�����������ӡ�</T>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetBufferedSocket :
      public FObject,
      public MNetSocket{
protected:
   SNetBufferedSocket _info;
   TBool _processing;
   INetSocketPool* _pReceivePool;
   INetSocketPool* _pSendPool;
   FNetBufferedPipe* _pInputPipe;
   FNetBufferedPipe* _pOutputPipe;
public:
   FNetBufferedSocket();
   MO_ABSTRACT ~FNetBufferedSocket();
public:
   MO_OVERRIDE SNetSocketInfo* Info();
public:
   void LinkAllocator(TInt capacity, FBufferedPipeBlockAllocator* pAllocator);
public:
   //------------------------------------------------------------
   // <T>���������Ϣ��</T>
   MO_INLINE SNetBufferedSocket* NetInfo(){
      return &_info;
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TUint16 Index(){
      return _info.index;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void SetIndex(TUint16 index){
      _info.index = index;
   }
   //------------------------------------------------------------
   // <T>������С�</T>
   MO_INLINE TUint16 Serial(){
      return _info.serial;
   }
   //------------------------------------------------------------
   // <T>�������С�</T>
   MO_INLINE void SetSerial(TUint16 serial){
      _info.serial = serial;
   }
   //------------------------------------------------------------
   // <T>���UDPЭ��֧�֡�</T>
   MO_INLINE TBool IsUdpSupport(){
      return _info.udpSupport;
   }
   //------------------------------------------------------------
   // <T>����UDPЭ��֧�֡�</T>
   MO_INLINE void SetUdpSupport(TBool udpSupport){
      _info.udpSupport = udpSupport;
   }
   //------------------------------------------------------------
   // <T>���UDP��ַ��</T>
   MO_INLINE TUint32 UdpAddress(){
      return _info.udpAddress;
   }
   //------------------------------------------------------------
   // <T>����UDP��ַ��</T>
   MO_INLINE void SetUdpAddress(TUint32 udpAddress){
      _info.udpAddress = udpAddress;
   }
   //------------------------------------------------------------
   // <T>���UDP�˿ڡ�</T>
   MO_INLINE TUint16 UdpPort(){
      return _info.udpPort;
   }
   //------------------------------------------------------------
   // <T>����UDP��ַ��</T>
   MO_INLINE void SetUdpPort(TUint16 udpPort){
      _info.udpPort = udpPort;
   }
   //------------------------------------------------------------
   // <T>��ý������С�</T>
   MO_INLINE TNetSerial ReceiveSerial(){
      return _info.receiveSerial;
   }
   //------------------------------------------------------------
   // <T>���ý������С�</T>
   MO_INLINE void SetReceiveSerial(TNetSerial serial){
      _info.receiveSerial = serial;
   }
   //------------------------------------------------------------
   // <T>��ý���ʱ�̡�</T>
   MO_INLINE TNetTick ReceiveTick(){
      return (TNetTick)_info.receiveTick;
   }
   //------------------------------------------------------------
   // <T>��ý���ʱ�̡�</T>
   MO_INLINE void SetReceiveTick(TNetTick tick){
      _info.receiveTick = tick;
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ���ִ���С�</T>
   MO_INLINE TBool IsProcessing(){
      return _processing;
   }
   //------------------------------------------------------------
   // <T>��ý��ջ��塣</T>
   MO_INLINE INetSocketPool* ReceivePool(){
      return _pReceivePool;
   }
   //------------------------------------------------------------
   // <T>���ý��ջ��塣</T>
   MO_INLINE void SetReceivePool(INetSocketPool* pPool){
      _pReceivePool = pPool;
   }
   //------------------------------------------------------------
   // <T>��÷��ͻ��塣</T>
   MO_INLINE INetSocketPool* SendPool(){
      return _pSendPool;
   }
   //------------------------------------------------------------
   // <T>���÷��ͻ��塣</T>
   MO_INLINE void SetSendPool(INetSocketPool* pPool){
      _pSendPool = pPool;
   }
   //------------------------------------------------------------
   // <T>�������ܵ���</T>
   MO_INLINE INetPipe* InputPipe(){
      return _pInputPipe;
   }
   //------------------------------------------------------------
   // <T>�������ܵ���</T>
   MO_INLINE INetPipe* OutputPipe(){
      return _pOutputPipe;
   }
public:
   void SetInfo(SNetSocketInfo* pInfo);
public:
   TInt DoBufferReceive();
   TInt DoBufferSend();
public:
   TBool Update();
public:
   MO_ABSTRACT TBool Startup();
   MO_ABSTRACT TBool Shutdown();
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FVector<FNetBufferedSocket*> FNetBufferedSocketVector;
typedef MO_CR_DECLARE FSet<TUint32, FNetBufferedSocket*> FNetBufferedSocketSet;
typedef MO_CR_DECLARE FStoragePool<FNetBufferedSocket*> FNetBufferedSocketPool;

//============================================================
// <T>�����������ӹ���ģ�顣</T>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetBufferedSocketModule :
      public FModule,
      public IMonitorTrigger,
      public IStatisticsTrigger{
protected:
   TInt _socketCount;
   TInt _socketCapacity;
   TInt _socketReceiveBuffer;
   TInt _socketSendBuffer;
   TInt64 _socketSerial;
   TInt _blockCapacity;
   FNetBufferedSocketSet* _pHandles;
   TThreadSection _sectionSet;
   FNetBufferedSocketPool* _pPool;
   TThreadSection _sectionPool;
   TTimeSpan _sendTimeout;
   TTimeSpan _receiveTimeout;
public:
   FNetBufferedSocketModule();
   MO_ABSTRACT ~FNetBufferedSocketModule();
public:
   //------------------------------------------------------------
   // <T>��þ�����ϡ�</T>
   MO_INLINE FNetBufferedSocketSet* Handles(){
      return _pHandles;
   }
   //------------------------------------------------------------
   // <T>��û��弯�ϡ�</T>
   MO_INLINE FNetBufferedSocketPool* Pool(){
      return _pPool;
   }
   //------------------------------------------------------------
   // <T>��÷ֿ�������</T>
   MO_INLINE TInt BlockCapacity(){
      return _blockCapacity;
   }
   //------------------------------------------------------------
   // <T>��÷ֿ�������</T>
   MO_INLINE void SetBlockCapacity(TInt blockCapacity){
      _blockCapacity = blockCapacity;
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Capacity(){
      return _socketCount;
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE void SetCapacity(TInt capacity){
      _socketCount = capacity;
   }
   //------------------------------------------------------------
   // <T>��÷��ͳ�ʱ��</T>
   MO_INLINE TTimeSpan SendTimeout(){
      return _sendTimeout;
   }
   //------------------------------------------------------------
   // <T>���÷��ͳ�ʱ��</T>
   MO_INLINE void SetSendTimeout(TTimeSpan sendTimeout){
      _sendTimeout = sendTimeout;
   }
   //------------------------------------------------------------
   // <T>��ý��ճ�ʱ��</T>
   MO_INLINE TTimeSpan ReceiveTimeout(){
      return _receiveTimeout;
   }
   //------------------------------------------------------------
   // <T>���ý��ճ�ʱ��</T>
   MO_INLINE void SetReceiveTimeout(TTimeSpan receiveTimeout){
      _receiveTimeout = receiveTimeout;
   }
public:
   MO_OVERRIDE TResult OnLoadConfig(FXmlNode* pConfig);
   MO_OVERRIDE TResult OnInitialize();
public:
   FNetBufferedSocket* LinkHandle(TUint32 handle);
   FNetBufferedSocket* FindHandle(TUint32 handle);
   FNetBufferedSocket* FindIndex(TUint16 index);
public:
   void OpenSocket(FNetBufferedSocket* pSocket);
   void CloseSocket(FNetBufferedSocket* pSocket);
public:
   MO_OVERRIDE TResult TriggerRefresh(TTimeTick currentTick);
   MO_OVERRIDE TResult StatisticsRefresh();
};
//------------------------------------------------------------
class MO_CR_DECLARE RNetSocketsModule : public RModuleSingleton<FNetBufferedSocketModule>{
};

//============================================================
// <T>�����������ӹ���ģ�顣</T>
//
// @history 100413 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetClientBufferedSocketModule : public FNetBufferedSocketModule{
public:
   FNetClientBufferedSocketModule();
   MO_ABSTRACT ~FNetClientBufferedSocketModule();
};
//------------------------------------------------------------
class MO_CR_DECLARE RNetClientSocketsModule : public RModuleSingleton<FNetClientBufferedSocketModule>{
};

MO_NAMESPACE_END

#endif // __MO_CR_NET_SOCKET_H__
