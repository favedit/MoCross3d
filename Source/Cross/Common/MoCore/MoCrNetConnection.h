#ifndef __MO_CR_NET_CONNECTION_H__
#define __MO_CR_NET_CONNECTION_H__

#ifndef __MO_CM_THREAD_H__
#include <MoCmThread.h>
#endif // __MO_CM_THREAD_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_CORE_H__
#include "MoCrCore.h"
#endif // __MO_CR_CORE_H__

#ifndef __MO_CR_NET_MESSAGE_H__
#include "MoCrNetMessage.h"
#endif // __MO_CR_NET_MESSAGE_H__

// ��Ϣ������
#define MO_NET_MESSAGE_SLOW_TICK 10000

// ע����Ϣ����
#define MO_NET_MESSAGE_REGISTE(MSG, CLS, PRC)                      RegisterRouter<CLS>(this, MSG::CODE, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_MESSAGE_REFER_REGISTE(REF, MSG, CLS, PRC)           REF::Instance().RegisterRouter<CLS>(this, MSG::CODE, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_MESSAGE_CMD_REGISTE(MSG, CMD, CLS, PRC)             RegisterRouter<CLS>(this, MSG::CODE, CMD, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_MESSAGE_REFER_CMD_REGISTE(REF, MSG, CMD, CLS, PRC)  REF::Instance().RegisterRouter<CLS>(this, MSG::CODE, CMD, #CLS "::" #PRC, &CLS::PRC)
#define MO_MCH_MESSAGE_REGISTE(MSG, CLS, PRC)                      RNetMessageMachine::Instance().Register(MSG::CODE, 0, this, #CLS "::" #PRC, &CLS::PRC);

// ע����Ϣ���� (All)
#define MO_NET_MESSAGE_REGISTE_ALL(CLS, PRC)                       RegisterRouterAll<CLS>(this, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_MESSAGE_REFER_REGISTE_ALL(REF, CLS, PRC)            REF::Instance().RegisterRouterAll<CLS>(this, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_MESSAGE_CMD_REGISTE_ALL(MSG, CMD, CLS, PRC)         RegisterRouterAll<CLS>(this, CMD, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_MESSAGE_REFER_CMD_REGISTE_ALL(REF, CMD, CLS, PRC)   REF::Instance().RegisterRouterAll<CLS>(this, CMD, #CLS "::" #PRC, &CLS::PRC)
#define MO_MCH_MESSAGE_REGISTE_ALL(CLS, PRC)                       RNetMessageMachine::Instance().RegisterAll(0, this, #CLS "::" #PRC, &CLS::PRC);

// ע��·�ɶ���
#define MO_NET_ROUTER_REGISTE(MSG, CLS, PRC)                       RegisterRouter<CLS>(this, MSG::CODE, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_ROUTER_REFER_REGISTE(REF, MSG, CLS, PRC)            REF::Instance().RegisterRouter<CLS>(this, MSG::CODE, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_ROUTER_CMD_REGISTE(MSG, CMD, CLS, PRC)              RegisterRouter<CLS>(this, MSG::CODE, CMD, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_ROUTER_REFER_CMD_REGISTE(REF, MSG, CMD, CLS, PRC)   REF::Instance().RegisterRouter<CLS>(this, MSG::CODE, CMD, #CLS "::" #PRC, &CLS::PRC)

// ע��·�ɶ��� (All)
#define MO_NET_ROUTER_REGISTE_ALL(CLS, PRC)                        RegisterRouterAll<CLS>(this, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_ROUTER_REFER_REGISTE_ALL(REF, CLS, PRC)             REF::Instance().RegisterRouterAll<CLS>(this, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_ROUTER_CMD_REGISTE_ALL(CMD, CLS, PRC)               RegisterRouterAll<CLS>(this, CMD, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_ROUTER_REFER_CMD_REGISTE_ALL(REF, CMD, CLS, PRC)    REF::Instance().RegisterRouterAll<CLS>(this, CMD, #CLS "::" #PRC, &CLS::PRC)

// ע�ᴫ�䶨��
#define MO_NET_TRANSFER_REGISTE(MSG, CLS, PRC)                     RegisterTransfer<CLS>(this, MSG::CODE, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_TRANSFER_REFER_REGISTE(REF, MSG, CLS, PRC)          REF::Instance().RegisterTransfer<CLS>(this, MSG::CODE, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_TRANSFER_CMD_REGISTE(MSG, CMD, CLS, PRC)            RegisterTransfer<CLS>(this, MSG::CODE, CMD, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_TRANSFER_REFER_CMD_REGISTE(REF, MSG, CMD, CLS, PRC) REF::Instance().RegisterTransfer<CLS>(this, MSG::CODE, CMD, #CLS "::" #PRC, &CLS::PRC)

// ע�ᴫ�䶨�� (All)
#define MO_NET_TRANSFER_REGISTE_ALL(CLS, PRC)                      RegisterTransferAll<CLS>(this, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_TRANSFER_REFER_REGISTE_ALL(REF, CLS, PRC)           REF::Instance().RegisterTransferAll<CLS>(this, -1, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_TRANSFER_CMD_REGISTE_ALL(MSG, CLS, PRC)             RegisterTransferAll<CLS>(this, CMD, #CLS "::" #PRC, &CLS::PRC)
#define MO_NET_TRANSFER_REFER_CMD_REGISTE_ALL(REF, CMD, CLS, PRC)  REF::Instance().RegisterTransferAll<CLS>(this, CMD, #CLS "::" #PRC, &CLS::PRC)

MO_NAMESPACE_BEGIN

//============================================================
class FPipe;
class FQueue;
class FNetClientSocket;
class FNetUdpClientSocket;
class TNetMessage;
class FNetMessageStatisticsMachine;

//============================================================
// <T>������Ϣ������׽����</T>
//============================================================
class FNetMessageCatcher : public FCatcher{
public:
   FNetMessageCatcher();
public:
   MO_OVERRIDE TBool Install();
};

//============================================================
// <T>��Ϣ��������</T>
//============================================================
class MO_CR_DECLARE FNetMessageHandle : public FObject{
protected:
   TCharC* _pInvokeName;
   TInt _command;
public:
   FNetMessageHandle();
   MO_ABSTRACT ~FNetMessageHandle();
public:
   //------------------------------------------------------------
   inline TCharC* InvokerName(){
      return _pInvokeName;
   }
   //------------------------------------------------------------
   inline TInt Command(){
      return _command;
   }
public:
   MO_VIRTUAL TBool Process(FObject* pSender, TNetMessage* pMessage) = 0;
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FNetMessageHandle*> FNetMessageHandleList;

//============================================================
// <T>��Ϣ����ص�����</T>
//============================================================
template <typename T>
class FNetMessageHandleInvoker : public FNetMessageHandle{
protected:
   typedef TBool (T::*HProcessor)(TNetMessage*);
protected:
   T* _pOwner;
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����¼��ص�����ʵ����</T>
   FNetMessageHandleInvoker(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetMessage*)){
      _pOwner = pOwner;
      _command = command;
      _pInvokeName = pInvokeName;
      _pProcesser = pProcesser;
   }
public:
   //------------------------------------------------------------
   MO_OVERRIDE TBool Process(FObject* pSender, TNetMessage* pMessage){
      // �����ģʽ
      if(_command >= 0){
         TInt command = pMessage->MessageHead().Command();
         if(_command == command){
            return (_pOwner->*_pProcesser)(pMessage);
         }
         return ETrue;
      }
      // ��ͨ����ģʽ
      return (_pOwner->*_pProcesser)(pMessage);
   }
};

//============================================================
// <T>��Ϣ����ص�����</T>
//============================================================
template <typename T>
class FNetMessageHandleSenderInvoker : public FNetMessageHandle{
protected:
   typedef TBool (T::*HProcessor)(FObject*, TNetMessage*);
protected:
   T* _pOwner;
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����¼��ص�����ʵ����</T>
   FNetMessageHandleSenderInvoker(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetMessage*)){
      _pOwner = pOwner;
      _command = command;
      _pInvokeName = pInvokeName;
      _pProcesser = pProcesser;
   }
public:
   //------------------------------------------------------------
   MO_OVERRIDE TBool Process(FObject* pSender, TNetMessage* pMessage){
      // �����ģʽ
      if(_command >= 0){
         TInt command = pMessage->MessageHead().Command();
         if(_command == command){
            return (_pOwner->*_pProcesser)(pSender, pMessage);
         }
         return ETrue;
      }
      // ��ͨ����ģʽ
      return (_pOwner->*_pProcesser)(pSender, pMessage);
   }
};

//============================================================
// <T>��Ϣ����ص������ϡ�</T>
//============================================================
class MO_CR_DECLARE FNetMessageHandles : public FObject{
protected:
   FNetMessageHandleList* _pProcessors;
public:
   FNetMessageHandles();
   MO_ABSTRACT ~FNetMessageHandles();
public:
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetMessage* pMessage)){
      typedef FNetMessageHandleInvoker<T> FInvoker;
      FInvoker* pInvoker = MO_CREATE(FInvoker, pOwner, command, pInvokeName, pProcesser);
      _pProcessors->Push(pInvoker);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetMessage* pMessage)){
      typedef FNetMessageHandleSenderInvoker<T> FInvoker;
      FInvoker* pInvoker = MO_CREATE(FInvoker, pOwner, command, pInvokeName, pProcesser);
      _pProcessors->Push(pInvoker);
      return ETrue;
   }
public:
   TBool Process(FObject* pSender, TNetMessage* pMessage);
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FVector<FNetMessageHandles*> FNetMessageHandlesVector;

//============================================================
class MO_CR_DECLARE FNetMessageProcessor : public FObject{
protected:
   FNetMessageHandlesVector* _pHandless;
public:
   FNetMessageProcessor();
   MO_ABSTRACT ~FNetMessageProcessor();
public:
   FNetMessageHandles* SyncHandles(TInt code);
public:
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetMessage* pMessage)){
      return SyncHandles(code)->Register<T>(pOwner, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetMessage* pMessage)){
      return SyncHandles(code)->Register<T>(pOwner, command, pInvokeName, pProcesser);
   }
public:
   TBool Dispatch(TNetMessage* pMessage);
   TBool Dispatch(FObject* pSender, TNetMessage* pMessage);
};

//============================================================
// <T>·����Ϣ��������</T>
//============================================================
class MO_CR_DECLARE FNetRouterHandle : public FObject{
protected:
   TCharC* _pInvokeName;
   TInt _command;
public:
   FNetRouterHandle();
   MO_ABSTRACT ~FNetRouterHandle();
public:
   //------------------------------------------------------------
   MO_INLINE TCharC* InvokerName(){
      return _pInvokeName;
   }
   //------------------------------------------------------------
   MO_INLINE TInt Command(){
      return _command;
   }
public:
   MO_VIRTUAL TBool Process(FObject* pSender, TNetRouter* pRouter) = 0;
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FNetRouterHandle*> FNetRouterHandleList;

//============================================================
// <T>·����Ϣ����ص�����</T>
//============================================================
template <typename T>
class FNetRouterHandleInvoker : public FNetRouterHandle{
protected:
   typedef TBool (T::*HProcessor)(TNetRouter*);
protected:
   T* _pOwner;
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����¼��ص�����ʵ����</T>
   FNetRouterHandleInvoker(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetRouter*)){
      _pOwner = pOwner;
      _command = command;
      _pInvokeName = pInvokeName;
      _pProcesser = pProcesser;
   }
public:
   //------------------------------------------------------------
   MO_OVERRIDE TBool Process(FObject* pSender, TNetRouter* pRouter){
      // �����ģʽ
      if(_command >= 0){
         TInt command = pRouter->MessageHead().Command();
         if(_command == command){
            return (_pOwner->*_pProcesser)(pRouter);
         }
         return ETrue;
      }
      // ��ͨ����ģʽ
      return (_pOwner->*_pProcesser)(pRouter);
   }
};

//============================================================
// <T>·����Ϣ����ص�����</T>
//============================================================
template <typename T>
class FNetRouterHandleSenderInvoker : public FNetRouterHandle{
protected:
   typedef TBool (T::*HProcessor)(FObject*, TNetRouter*);
protected:
   T* _pOwner;
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����¼��ص�����ʵ����</T>
   FNetRouterHandleSenderInvoker(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetRouter*)){
      _pOwner = pOwner;
      _command = command;
      _pInvokeName = pInvokeName;
      _pProcesser = pProcesser;
   }
public:
   //------------------------------------------------------------
   MO_OVERRIDE TBool Process(FObject* pSender, TNetRouter* pRouter){
      // �����ģʽ
      if(_command >= 0){
         TInt command = pRouter->MessageHead().Command();
         if(_command == command){
            return (_pOwner->*_pProcesser)(pSender, pRouter);
         }
         return ETrue;
      }
      // ��ͨ����ģʽ
      return (_pOwner->*_pProcesser)(pSender, pRouter);
   }
};

//============================================================
// <T>��Ϣ����ص������ϡ�</T>
//============================================================
class MO_CR_DECLARE FNetRouterHandles : public FObject{
protected:
   FNetRouterHandleList* _pProcessors;
public:
   FNetRouterHandles();
   MO_ABSTRACT ~FNetRouterHandles();
public:
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetRouter* pRouter)){
      typedef FNetRouterHandleInvoker<T> FInvoker;
      FInvoker* pInvoker = MO_CREATE(FInvoker, pOwner, command, pInvokeName, pProcesser);
      _pProcessors->Push(pInvoker);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetRouter* pRouter)){
      typedef FNetRouterHandleSenderInvoker<T> FInvoker;
      FInvoker* pInvoker = MO_CREATE(FInvoker, pOwner, command, pInvokeName, pProcesser);
      _pProcessors->Push(pInvoker);
      return ETrue;
   }
public:
   TBool Process(FObject* pSender, TNetRouter* pRouter);
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FVector<FNetRouterHandles*> FNetRouterHandlesVector;

//============================================================
class MO_CR_DECLARE FNetRouterProcessor : public FObject{
protected:
   FNetRouterHandlesVector* _pHandless;
public:
   FNetRouterProcessor();
   MO_ABSTRACT ~FNetRouterProcessor();
public:
   FNetRouterHandles* SyncHandles(TInt code);
public:
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetRouter* pRouter)){
      return SyncHandles(code)->Register<T>(pOwner, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetRouter* pRouter)){
      return SyncHandles(code)->Register<T>(pOwner, command, pInvokeName, pProcesser);
   }
public:
   TBool Dispatch(TNetRouter* pRouter);
   TBool Dispatch(FObject* pSender, TNetRouter* pRouter);
};

//============================================================
// <T>������Ϣ��������</T>
//============================================================
class MO_CR_DECLARE FNetTransferHandle : public FObject{
protected:
   TCharC* _pInvokeName;
   TInt _command;
public:
   FNetTransferHandle();
   MO_ABSTRACT ~FNetTransferHandle();
public:
   //------------------------------------------------------------
   inline TCharC* InvokerName(){
      return _pInvokeName;
   }
   //------------------------------------------------------------
   inline TInt Command(){
      return _command;
   }
public:
   MO_VIRTUAL TBool Process(FObject* pSender, TNetTransfer* pTransfer) = 0;
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FNetTransferHandle*> FNetTransferHandleList;

//============================================================
// <T>·����Ϣ����ص�����</T>
//============================================================
template <typename T>
class FNetTransferHandleInvoker : public FNetTransferHandle{
protected:
   typedef TBool (T::*HProcessor)(TNetTransfer*);
protected:
   T* _pOwner;
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>���촫��ص�����ʵ����</T>
   FNetTransferHandleInvoker(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetTransfer*)){
      _pOwner = pOwner;
      _command = command;
      _pInvokeName = pInvokeName;
      _pProcesser = pProcesser;
   }
public:
   //------------------------------------------------------------
   MO_OVERRIDE TBool Process(FObject* pSender, TNetTransfer* pTransfer){
      // �����ģʽ
      if(_command >= 0){
         TInt command = pTransfer->MessageHead().Command();
         if(_command == command){
            return (_pOwner->*_pProcesser)(pTransfer);
         }
         return ETrue;
      }
      // ��ͨ����ģʽ
      return (_pOwner->*_pProcesser)(pTransfer);
   }
};

//============================================================
// <T>·����Ϣ����ص�����</T>
//============================================================
template <typename T>
class FNetTransferHandleSenderInvoker : public FNetTransferHandle{
protected:
   typedef TBool (T::*HProcessor)(FObject*, TNetTransfer*);
protected:
   T* _pOwner;
   HProcessor _pProcesser;
public:
   //------------------------------------------------------------
   // <T>�����¼��ص�����ʵ����</T>
   FNetTransferHandleSenderInvoker(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetTransfer*)){
      _pOwner = pOwner;
      _command = command;
      _pInvokeName = pInvokeName;
      _pProcesser = pProcesser;
   }
public:
   //------------------------------------------------------------
   MO_OVERRIDE TBool Process(FObject* pSender, TNetTransfer* pTransfer){
      // �����ģʽ
      if(_command >= 0){
         TInt command = pTransfer->MessageHead().Command();
         if(_command == command){
            return (_pOwner->*_pProcesser)(pSender, pTransfer);
         }
         return ETrue;
      }
      // ��ͨ����ģʽ
      return (_pOwner->*_pProcesser)(pSender, pTransfer);
   }
};

//============================================================
// <T>��Ϣ����ص������ϡ�</T>
//============================================================
class MO_CR_DECLARE FNetTransferHandles : public FObject{
protected:
   FNetRouterHandleList* _pRouterProcessors;
   FNetTransferHandleList* _pTransferProcessors;
   FCatcher* _pCatcher;
public:
   FNetTransferHandles();
   MO_ABSTRACT ~FNetTransferHandles();
public:
   //------------------------------------------------------------
   // <T>���·�ɴ�������</T>
   MO_INLINE FNetRouterHandleList* RouterProcessors(){
      return _pRouterProcessors;
   }
   //------------------------------------------------------------
   // <T>��ô��䴦������</T>
   MO_INLINE FNetTransferHandleList* TransferProcessors(){
      return _pTransferProcessors;
   }
   //------------------------------------------------------------
   // <T>��ò�׽����</T>
   MO_INLINE FCatcher* Catcher(){
      return _pCatcher;
   }
   //------------------------------------------------------------
   // <T>���ò�׽����</T>
   MO_INLINE void SetCatcher(FCatcher* pCatcher){
      _pCatcher = pCatcher;
   }
public:
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���</T>
   template <typename T>
   TBool RegisterRouter(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetRouter* pRouter)){
      typedef FNetRouterHandleInvoker<T> FInvoker;
      FInvoker* pInvoker = MO_CREATE(FInvoker, pOwner, command, pInvokeName, pProcesser);
      _pRouterProcessors->Push(pInvoker);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���</T>
   template <typename T>
   TBool RegisterRouter(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetRouter* pRouter)){
      typedef FNetRouterHandleSenderInvoker<T> FInvoker;
      FInvoker* pInvoker = MO_CREATE(FInvoker, pOwner, command, pInvokeName, pProcesser);
      _pRouterProcessors->Push(pInvoker);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��</T>
   template <typename T>
   TBool RegisterTransfer(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetTransfer* pTransfer)){
      typedef FNetTransferHandleInvoker<T> FInvoker;
      FInvoker* pInvoker = MO_CREATE(FInvoker, pOwner, command, pInvokeName, pProcesser);
      _pTransferProcessors->Push(pInvoker);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��</T>
   template <typename T>
   TBool RegisterTransfer(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetTransfer* pTransfer)){
      typedef FNetTransferHandleSenderInvoker<T> FInvoker;
      FInvoker* pInvoker = MO_CREATE(FInvoker, pOwner, command, pInvokeName, pProcesser);
      _pTransferProcessors->Push(pInvoker);
      return ETrue;
   }
public:
   TBool ProcessRouter(FNetRouterHandle* pHandle, FObject* pSender, TNetTransfer* pTransfer);
   TBool ProcessTransfer(FNetTransferHandle* pHandle, FObject* pSender, TNetTransfer* pTransfer);
   TBool Process(FObject* pSender, TNetTransfer* pTransfer);
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FNetTransferHandles*> FNetTransferHandlesList;
typedef MO_CR_DECLARE FVector<FNetTransferHandles*> FNetTransferHandlesVector;

//============================================================
// <T>���紫�䴦������</T>
//============================================================
class MO_CR_DECLARE FNetTransferProcessor : public FObject{
protected:
   FNetTransferHandlesList* _pHandlesList;
   FNetTransferHandlesVector* _pHandless;
   FNetMessageCatcher* _pCatcher;
public:
   FNetTransferProcessor();
   MO_ABSTRACT ~FNetTransferProcessor();
public:
   FNetTransferHandles* SyncHandles(TInt code);
public:
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���</T>
   template <typename T>
   TBool RegisterRouter(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetRouter* pRouter)){
      return SyncHandles(code)->RegisterRouter<T>(pOwner, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���</T>
   template <typename T>
   TBool RegisterRouter(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetRouter* pRouter)){
      return SyncHandles(code)->RegisterRouter<T>(pOwner, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��</T>
   template <typename T>
   TBool RegisterTransfer(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetTransfer* pTransfer)){
      return SyncHandles(code)->RegisterTransfer<T>(pOwner, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��</T>
   template <typename T>
   TBool RegisterTransfer(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetTransfer* pTransfer)){
      return SyncHandles(code)->RegisterTransfer<T>(pOwner, command, pInvokeName, pProcesser);
   }
public:
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���ȫ��������</T>
   template <typename T>
   TBool RegisterRouterAll(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetRouter* pRouter)){
      TListIterator<FNetTransferHandles*> iterator = _pHandlesList->IteratorC();
      while(iterator.Next()){
         FNetTransferHandles* pHandles = *iterator;
         pHandles->RegisterRouter<T>(pOwner, command, pInvokeName, pProcesser);
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���ȫ��������</T>
   template <typename T>
   TBool RegisterRouterAll(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetRouter* pRouter)){
      TListIterator<FNetTransferHandles*> iterator = _pHandlesList->IteratorC();
      while(iterator.Next()){
         FNetTransferHandles* pHandles = *iterator;
         pHandles->RegisterRouter<T>(pOwner, command, pInvokeName, pProcesser);
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��ȫ��������</T>
   template <typename T>
   TBool RegisterTransferAll(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetTransfer* pTransfer)){
      TListIterator<FNetTransferHandles*> iterator = _pHandlesList->IteratorC();
      while(iterator.Next()){
         FNetTransferHandles* pHandles = *iterator;
         pHandles->RegisterTransfer<T>(pOwner, command, pInvokeName, pProcesser);
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��ȫ��������</T>
   template <typename T>
   TBool RegisterTransferAll(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetTransfer* pTransfer)){
      TListIterator<FNetTransferHandles*> iterator = _pHandlesList->IteratorC();
      while(iterator.Next()){
         FNetTransferHandles* pHandles = *iterator;
         pHandles->RegisterTransfer<T>(pOwner, command, pInvokeName, pProcesser);
      }
      return ETrue;
   }
public:
   TBool Dispatch(TNetTransfer* pTransfer);
   TBool Dispatch(FObject* pSender, TNetTransfer* pTransfer);
};

//============================================================
// <T>��Ϣ�ܵ���</T>
//
// @history 100526 MAOCY ����
//============================================================
class MO_CR_DECLARE FNetMessageConnection : public FObject{
protected:
   TBool _isConnected;
   TBool _isUdpConnected;
   FNetClientSocket* _pSocket;
   FNetUdpClientSocket* _pUdpSocket;
   TInt _pipeLength;
   TInt _queueLength;
   FPipe* _pInputPipe;
   FQueue* _pInputQueue;
   FQueue* _pInputUdpQueue;
   FPipe* _pOutputPipe;
   FQueue* _pOuputQueue;
   TInt _clientId;
public:
   FNetMessageConnection();
   MO_ABSTRACT ~FNetMessageConnection();
public:
   //------------------------------------------------------------
   inline TInt PipeLength(){
      return _pipeLength;
   }
   //------------------------------------------------------------
   inline void SetPipeLength(TInt length){
      _pipeLength = length;
   }
   //------------------------------------------------------------
   inline TInt QueueLength(){
      return _queueLength;
   }
   //------------------------------------------------------------
   inline void SetQueueLength(TInt length){
      _queueLength = length;
   }
   //------------------------------------------------------------
   inline TBool IsConnected(){
      return _isConnected;
   }
   //------------------------------------------------------------
   inline TBool IsUdpConnected(){
      return _isUdpConnected;
   }
   //------------------------------------------------------------
   inline TInt ClientId(){
      return _clientId;
   }
   //------------------------------------------------------------
   inline void SetClientId(TInt clientId){
      _clientId = clientId;
   }
public:
   TBool Create();
   TBool Connect(TCharC* pHost, TUint16 port);
   TBool UdpConnect(TCharC* pHost, TUint16 port);
   TBool SetNonBlock();
   TBool SetUdpNonBlock();
   TBool Disconnect();
public:
   MO_ABSTRACT TBool OnStartup();
public:
   MO_ABSTRACT TBool ProcessTcpReceive();
   MO_ABSTRACT TBool ProcessUdpReceive();
   MO_ABSTRACT TBool ProcessReceive();
protected:
   TBool AbandonReceiveMessages();
public:
   TBool PushMessage(TNetMessage* pMessage);
   TBool PushUdpMessage(TNetMessage* pMessage);
   TBool PopupMessage(TNetMessage* pMessage);
   TBool PopupUdpMessage(TNetMessage* pMessage);
   TBool WaitMessage(TNetMessage* pMessage);
public:
   TBool ProcessWaitMessage(TNetMessage* pMessage);
public:
   TBool DoConnect();
   TBool DoUdpConnect();
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FNetMessageConnection*> FNetMessageConnectionList;

//============================================================
class MO_CR_DECLARE FNetMessageReceiveThread : public FThread{
protected:
   FNetMessageConnectionList* _pConnections;
public:
   FNetMessageReceiveThread();
   MO_ABSTRACT ~FNetMessageReceiveThread();
public:
   FNetMessageConnectionList* Connections();
public:
   TBool Register(FNetMessageConnection* pConnection);
   TBool Unregister(FNetMessageConnection* pConnection);
public:
   TBool ProcessStart();
   TBool ProcessReceive();
   MO_OVERRIDE TResult Process();
   MO_OVERRIDE TResult Stop();
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FNetMessageReceiveThread*> FNetMessageReceiveThreadList;

//============================================================
// <T>��Ⱦ�������̨��</T>
//============================================================
class MO_CR_DECLARE FNetMessageMachine : public FConsole{
protected:
   FNetMessageConnection* _pConnection;
   FNetMessageReceiveThread* _pReceiveThread;
   FNetMessageHandlesVector* _pHanldess;
public:
   FNetMessageMachine();
   MO_ABSTRACT ~FNetMessageMachine();
public:
   FNetMessageConnection* Connection();
   FNetMessageReceiveThread* ReceiveThread();
public:
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool Register(TInt code, TInt command, T* pOwner, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetMessage* pMessage)){
      // ��ô���������
      FNetMessageHandles* pHandles = _pHanldess->Get(code);
      if(NULL == pHandles){
         pHandles = MO_CREATE(FNetMessageHandles);
         _pHanldess->Set(code, pHandles);
      }
      // ע����Ϣ
      pHandles->Register<T>(pOwner, command, pInvokeName, pProcesser);
      return ETrue;
   }
   //------------------------------------------------------------
   TBool MessageUnregister(TInt code);
public:
   TBool Connect(TCharC* pHost, TUint16 port);
   TBool PushMessage(TNetMessage* pMessage);
public:
   TBool Startup();
   TBool ProcessMessage();
   TBool Process();
   TBool Shutdown();
};
//------------------------------------------------------------
class MO_CR_DECLARE RNetMessageMachine : public RSingleton<FNetMessageMachine>{
};

//============================================================
// <T>��Ⱦ�������̨��</T>
//============================================================
class MO_CR_DECLARE FNetMessageConsole : public FConsole{
protected:
   FNetMessageConnectionList* _pConnections;
   FNetMessageReceiveThread* _pReceiveThread;
   FNetMessageHandlesVector* _pHanldess;
public:
   FNetMessageConsole();
   MO_ABSTRACT ~FNetMessageConsole();
public:
   FNetMessageConnectionList* Connections();
   FNetMessageReceiveThread* ReceiveThread();
public:
   TBool ConnectionRegister(FNetMessageConnection* pConnection);
   TBool ConnectionUnregister(FNetMessageConnection* pConnection);
public:
   //------------------------------------------------------------
   // <T>ע��һ����Ϣ����</T>
   template <typename T>
   TBool MessageRegister(TInt code, T* pOwner, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetMessage* pMessage)){
      // ��ô���������
      FNetMessageHandles* pHandles = _pHanldess->Get(code);
      if(NULL == pHandles){
         pHandles = MO_CREATE(FNetMessageHandles);
         _pHanldess->Set(code, pHandles);
      }
      // ע����Ϣ
      pHandles->Register<T>(pOwner, pInvokeName, pProcesser);
      return ETrue;
   }
   //------------------------------------------------------------
   TBool MessageUnregister(TInt code);
public:
   TBool Startup();
   TBool ProcessConnection(FNetMessageConnection* pConnection);
   TBool ProcessConnectionAll(FNetMessageConnection* pConnection);
   TBool Process();
   TBool ProcessAll();
   TBool Shutdown();
};
//------------------------------------------------------------
class MO_CR_DECLARE RNetMessageManager : public RSingleton<FNetMessageConsole>{
};

//============================================================
// <T>��Ϣͳ�����ݡ�</T>
//============================================================
class MO_CR_DECLARE FNetMessageStatistics : public FObject{
protected:
   // @attribtue ����
   TInt _code;
   // @attribtue ����
   TInt _count;
   // @attribtue ʧ�ܴ���
   TInt _failureCount;
   // @attribtue ִ��������
   TInt _slowClose;
   // @attribtue ����ر�
   TInt _socketClose;
   // @attribtue ��ʼʱ��
   TTimeTick _beginTick;
   // @attribtue ����ʱ��
   TTimeTick _endTick;
   // @attribtue ��Сʱ��
   TTimeSpan _minTick;
   // @attribtue ���ʱ��
   TTimeSpan _maxTick;
   // @attribtue ����ʱ��ͳ��
   TTimeSpan _countTick;
public:
   //------------------------------------------------------------
   // <T>������Ϣͳ�����ݡ�</T>
   FNetMessageStatistics(){
      Reset();
   }
public:
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE TInt Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>���ô��롣</T>
   MO_INLINE void SetCode(TInt code){
      _code = code;
   }
   //------------------------------------------------------------
   // <T>��ô�����</T>
   MO_INLINE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>��ô�����</T>
   MO_INLINE TInt FailureCount(){
      return _failureCount;
   }
   //------------------------------------------------------------
   // <T>���ִ����������</T>
   MO_INLINE TInt SlowCount(){
      return _slowClose;
   }
   //------------------------------------------------------------
   // <T>�������رմ�����</T>
   MO_INLINE TInt SocketClose(){
      return _socketClose;
   }
   //------------------------------------------------------------
   // <T>��ÿ�ʼʱ�̡�</T>
   MO_INLINE TTimeTick BeginTick(){
      return _beginTick;
   }
   //------------------------------------------------------------
   // <T>��ý���ʱ�̡�</T>
   MO_INLINE TTimeTick EndTick(){
      return _endTick;
   }
   //------------------------------------------------------------
   // <T>�����Сʱ�Ρ�</T>
   MO_INLINE TTimeSpan MinTick(){
      return _minTick;
   }
   //------------------------------------------------------------
   // <T>������ʱ�Ρ�</T>
   MO_INLINE TTimeSpan MaxTick(){
      return _maxTick;
   }
   //------------------------------------------------------------
   // <T>��ô���ʱ��ͳ�ơ�</T>
   MO_INLINE TTimeTick CountTick(){
      return _countTick;
   }
   //------------------------------------------------------------
   // <T>���ƽ��ִ��ʱ�̡�</T>
   MO_INLINE TTimeTick AverageTick(){
      if(_count > 0){
         return _countTick / _count;
      }
      return 0;
   }
public:
   //------------------------------------------------------------
   // <T>��ʼ����</T>
   MO_INLINE void DoBegin(){
      //_beginTick = RCpu::CurrentCycleCount();
      _beginTick = RTimeTick::Current();
   }
   //------------------------------------------------------------
   // <T>��������</T>
   MO_INLINE void DoEnd(){
      //_endTick = RCpu::CurrentCycleCount();
      _endTick = RTimeTick::Current();
   }
   //------------------------------------------------------------
   // <T>����˿ڴ��������</T>
   MO_INLINE void DoSocketError(){
      _socketClose++;
   }
public:
   //------------------------------------------------------------
   // <T>���´���</T>
   TTimeSpan Update(TBool result){
      _count++;
      if(!result){
         _failureCount++;
      }
      TTimeSpan span = _endTick - _beginTick;
      // ������Сʱ��
      if(0 == _minTick){
         _minTick = span;
      }else if(span < _minTick){
         _minTick = span;
      }
      // �������ʱ��
      if(0 == _maxTick){
         _maxTick = span;
      }else if(span > _maxTick){
         _maxTick = span;
      }
      // ���ִ���ٶ� (10����)
      if(span > MO_NET_MESSAGE_SLOW_TICK){
         _slowClose++;
      }
      // ������ʱ��
      _countTick += span;
      return span;
   }
   //------------------------------------------------------------
   // <T>���ô���</T>
   void Reset(){
      _code = 0;
      _count = 0;
      _failureCount = 0;
      _slowClose = 0;
      _socketClose = 0;
      _beginTick = 0;
      _endTick = 0;
      _minTick = 0;
      _maxTick = 0;
      _countTick = 0;
   }
};
//------------------------------------------------------------
typedef MO_CR_DECLARE TFixVector<FNetMessageStatistics*, MO_NETMESSAGE_COUNT> TFsNetMessageStatisticsVector;

//============================================================
// <T>��Ϣͳ�ƻ���</T>
//============================================================
class MO_CR_DECLARE FNetMessageStatisticsMachine : public FObject{
protected:
   TFsName _name;
   TFsNetMessageStatisticsVector _statistics;
public:
   FNetMessageStatisticsMachine();
   MO_ABSTRACT ~FNetMessageStatisticsMachine();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
public:
   //------------------------------------------------------------
   // <T>���ͳ���б�</T>
   MO_INLINE TFsNetMessageStatisticsVector& Statisticses(){
      return _statistics;
   }
public:
   TInt ValidCount();
   FNetMessageStatistics* Get(TInt code);
   void Reset();
public:
   void Dump(TFsDump& dump);
};
//------------------------------------------------------------
typedef FList<FNetMessageStatisticsMachine*> FNetMessageStatisticsMachineList;

//============================================================
// <T>��Ϣͳ�ƿ���̨��</T>
//============================================================
class MO_CR_DECLARE FNetMessageStatisticsConsole :
      public FConsole,
      public IStatisticsTrigger{
protected:
   FNetMessageStatisticsMachine* _pMachine;
   FNetMessageStatisticsMachineList* _pMachines;
public:
   FNetMessageStatisticsConsole();
   MO_ABSTRACT ~FNetMessageStatisticsConsole();
public:
   //------------------------------------------------------------
   // <T>���Ĭ�ϵ�ͳ�ƻ���</T>
   MO_INLINE FNetMessageStatisticsMachine* Machine(){
      return _pMachine;
   }
   //------------------------------------------------------------
   // <T>���ͳ�ƻ��б�</T>
   MO_INLINE FNetMessageStatisticsMachineList* Machines(){
      return _pMachines;
   }
public:
   void Register(FNetMessageStatisticsMachine* pMachine);
   void Unregister(FNetMessageStatisticsMachine* pMachine);
public:
   MO_OVERRIDE TResult StatisticsRefresh();
};
//------------------------------------------------------------
class MO_CR_DECLARE RNetMessageStatisticsManager : public RSingleton<FNetMessageStatisticsConsole>{
};


MO_NAMESPACE_END

#endif // __MO_CR_NET_CONNECTION_H__
