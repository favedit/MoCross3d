#ifndef __MO_CR_NET_TRANSFER_IOCP_H__
#define __MO_CR_NET_TRANSFER_IOCP_H__
//------------------------------------------------------------
#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

#ifndef __MO_CR_NET_IOCP_H__
#include "MoCrNetIocp.h"
#endif // __MO_CR_NET_IOCP_H__

#ifndef __MO_CR_NET_TRANSFER_H__
#include "MoCrNetTransfer.h"
#endif // __MO_CR_NET_TRANSFER_H__

MO_NAMESPACE_BEGIN

#ifdef _MO_WINDOWS

//============================================================
// <T>�����������ӹ���ģ�顣</T>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetIocpSocketModule : public FNetBufferedSocketModule{
public:
   FNetIocpSocketModule();
   MO_ABSTRACT ~FNetIocpSocketModule();
public:
   MO_OVERRIDE TResult OnInitialize();
};

//============================================================
// <T>�������Ӽ����̡߳�</T>
//
// @history 100312 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetIocpTransferServerThread : public FNetTransferServerThread{
public:
   FNetIocpTransferServerThread();
   MO_ABSTRACT ~FNetIocpTransferServerThread();
public:
   MO_OVERRIDE TResult Process();
};

//============================================================
// <T>�������ݽ����̡߳�</T>
//
// @history 100312 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetIocpTransferReceiveThread : public FNetTransferReceiveThread{
public:
   FNetIocpTransferReceiveThread();
   MO_ABSTRACT ~FNetIocpTransferReceiveThread();
public:
   MO_OVERRIDE TResult Process();
};

//============================================================
// <T>���紫�����</T>
//
// @history 100312 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetIocpTransferService : public FNetTransferService{
public:
   FNetIocpTransferService();
   MO_ABSTRACT( ~FNetIocpTransferService() );
public:
   MO_OVERRIDE TResult OnStartup();
public:
   MO_OVERRIDE TBool AddSockets(TFsNetSocketInfoVector& infos);
public:
   TBool SendLimitNotify(SNetSocketInfo& info){return EFalse;}
   TBool SendConnectNotify(FNetBufferedSocket* pSocket, TCharC* pHost, TUint16 port){return EFalse;}
   TBool SendDisconnectNotify(FNetBufferedSocket* pSocket, TCharC* pHost, TUint16 port){return EFalse;}
   TBool SendInvalidUnknownNotify(FNetBufferedSocket* pSocket){return EFalse;}
   TBool SendInvalidVersionNotify(FNetBufferedSocket* pSocket){return EFalse;}
   TBool SendInvalidSerialNotify(FNetBufferedSocket* pSocket){return EFalse;}
   TBool SendInvalidUnserialNotify(FNetBufferedSocket* pSocket){return EFalse;}
   TBool SendInvalidFullNotify(FNetBufferedSocket* pSocket){return EFalse;}
};

#endif // _MO_WINDOWS

MO_NAMESPACE_END

#endif // __MO_CR_NET_TRANSFER_IOCP_H__
