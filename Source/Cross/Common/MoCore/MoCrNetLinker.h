#ifndef __MO_CR_NET_LINKER_H__
#define __MO_CR_NET_LINKER_H__

#ifndef __MO_CM_NET_H__
#include <MoCmNet.h>
#endif // __MO_CM_NET_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_MODULE_H__
#include "MoCrModule.h"
#endif // __MO_CR_MODULE_H__

MO_NAMESPACE_BEGIN

//============================================================
class TNetRouter;
class TNetTransfer;

//============================================================
// <T>�˿��������ӿڡ�</T>
//
// @history 120413 MAOCY ����
//============================================================
class MO_CR_DECLARE INetSocketLinker{
public:
   MO_ABSTRACT ~INetSocketLinker(){
   }
public:
   MO_VIRTUAL TBool OnSocketConnect() = 0;
   MO_VIRTUAL TBool OnSocketDisconnect() = 0;
public:
   MO_VIRTUAL TInt SocketType() = 0;
};

//============================================================
// <T>�˿������������ࡣ</T>
//
// @history 120413 MAOCY ����
//============================================================
class MO_CR_DECLARE MNetSocketLinker : public INetSocketLinker{
protected:
   TInt _socketType;
   TInt _port;
public:
   MNetSocketLinker();
   MO_ABSTRACT ~MNetSocketLinker() = 0;
public:
   MO_OVERRIDE TBool OnSocketConnect() = 0;
   MO_OVERRIDE TBool OnSocketDisconnect() = 0;
public:
   MO_ABSTRACT TCharC* SocketName() = 0;
   MO_OVERRIDE TInt SocketType() = 0;
};

//============================================================
// <T>�˿���������</T>
//
// @history 100312 MAOCY ����
//============================================================
class MO_CR_DECLARE SNetSocketLinker{
protected:
   TBool _connected;
   INetSocketLinker* _pLinker;
public:
   //------------------------------------------------------------
   // <T>����˿���������</T>
   SNetSocketLinker(){
      _connected = EFalse;
      MO_CLEAR(_pLinker);
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ����ӡ�</T>
   MO_INLINE TBool IsConnected(){
      return _connected;
   }
   //------------------------------------------------------------
   // <T>�����Ƿ����ӡ�</T>
   MO_INLINE void SetConnected(TBool connected){
      _connected = connected;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ��������������</T>
   MO_INLINE TBool HasLinker(){
      return (NULL != _pLinker);
   }
   //------------------------------------------------------------
   // <T>��������������</T>
   MO_INLINE INetSocketLinker* Get(){
      return _pLinker;
   }
public:
   //------------------------------------------------------------
   // <T>���������������</T>
   TBool Link(INetSocketLinker* pLinker){
      MO_ASSERT(pLinker);
      // ��������
      _connected = ETrue;
      // ��������
      TBool result = pLinker->OnSocketConnect();
      _pLinker = pLinker;
      return result;
   }
   //------------------------------------------------------------
   // <T>�Ͽ������������</T>
   TBool Unlink(){
      // ��������
      _connected = EFalse;
      // �Ͽ�����
      TBool result = EFalse;
      if(NULL != _pLinker){
         result = _pLinker->OnSocketDisconnect();
      }
      MO_CLEAR(_pLinker);
      return result;
   }
};

//============================================================
// <T>�˿����Ӵ洢����</T>
// <P>ʹ�ö˿ڽ���������</P>
//
// @history 100312 MAOCY ����
// @history 100722 MAOCY ʹ�ö˿ڽ�������
//============================================================
class MO_CR_DECLARE FNetSocketLinkerStorage : public FModule{
protected:
   SNetSocketLinker _linkers[MO_NET_SOCKET_MAX_COUNT];
public:
   FNetSocketLinkerStorage();
   MO_ABSTRACT ~FNetSocketLinkerStorage();
public:
   SNetSocketLinker* Get(TInt index);
public:
   SNetSocketLinker* Link(TInt index);
   SNetSocketLinker* LinkTransfer(TNetTransfer* pTransfer);
   SNetSocketLinker* Unlink(TInt index);
   SNetSocketLinker* UnlinkTransfer(TNetTransfer* pTransfer);
};

//============================================================
// <T>�˿����Ӵ洢ģ�顣</T>
//
// @history 100312 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetSocketLinkerModule : public FNetSocketLinkerStorage{
public:
   FNetSocketLinkerModule();
   MO_ABSTRACT( ~FNetSocketLinkerModule() );
};

//============================================================
// <T>�˿����Ӵ洢��������</T>
//============================================================
class MO_CR_DECLARE RNetSocketLinkerModule : public RModuleSingleton<FNetSocketLinkerModule>{
};

MO_NAMESPACE_END

#endif // __MO_CR_NET_LINKER_H__
