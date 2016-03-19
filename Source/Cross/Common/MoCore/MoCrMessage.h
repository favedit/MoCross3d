#ifndef __MO_CR_MESSAGE_H__
#define __MO_CR_MESSAGE_H__

#ifndef __MO_CM_SHARED_H__
#include <MoCmShared.h>
#endif // __MO_CM_SHARED_H__

#ifndef __MO_CM_SYSTEM_H__
#include <MoCmSystem.h>
#endif // __MO_CM_SYSTEM_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_NET_MESSAGE_H__
#include "MoCrNetMessage.h"
#endif // __MO_CR_NET_MESSAGE_H__

#ifndef __MO_CR_NET_LINKER_H__
#include "MoCrNetLinker.h"
#endif // __MO_CR_NET_LINKER_H__

#ifndef __MO_CR_NET_CONNECTION_H__
#include "MoCrNetConnection.h"
#endif // __MO_CR_NET_CONNECTION_H__

#define MO_ARG_HOME             "-home"
#define MO_ARG_CONFIG           "-config"
#define MO_ARG_LOGGER           "-logger"
#define MO_ARG_MEMORY           "-memory"
#define MO_ARG_MEMORY_CREATE    "create"
#define MO_ARG_MEMORY_CONNECT   "connect"
#define MO_LOGGER_DEBUG         "debug"
#define MO_LOGGER_INFO          "info"
#define MO_LOGGER_ERROR         "error"
#define MO_LOGGER_WARN          "warn"
#define MO_LOGGER_FATAL         "fatal"
#define MO_MD_SERVER_SHAREDCODE 80

MO_NAMESPACE_BEGIN

//============================================================
template class MO_CR_DECLARE TFsNetString<MO_FS_LABEL_LENGTH>;

//============================================================
// <T>�������ӽṹ�ṹ���塣</T>
//
// @struct
//============================================================
struct MO_CR_DECLARE SNetSocketClient{
public:
   // @property ���
   TInt32 id;
   // @property ��ѯ��־
   TBool queried;
   // @property ���ӱ�־
   TBool connected;
   // @property ע���־
   TBool registered;
   // @property ��������
   TFsNetString<MO_FS_LABEL_LENGTH> name;
   // @property ������ַ
   TFsNetString<MO_FS_LABEL_LENGTH> host;
   // @property �˿�
   TUint16 port;
   // @property Զ��������ַ
   TFsNetString<MO_FS_LABEL_LENGTH> remoteHost;
   // @property Զ�̶˿�
   TUint16 remotePort;
   // @property �����ַ�����ص�ַ��
   SNetTarget target;
   // @property �˿ڵ�ַ
   SNetSocketTarget socketTarget;
   // @property �㲥��ַ
   TFsNetString<MO_FS_LABEL_LENGTH> udpHost;
   // @property �㲥�˿�
   TUint16 udpPort;
   // @property �㲥����Ŀ��
   SNetTarget udpTarget;
};

//============================================================
class MO_CR_DECLARE FSharedNetSocketClient :
      public FBase,
      public MShared,
      public MInstancedPoolObject,
      public MNetSocketLinker{
public:
   SNetSocketClient* _gClient;
public:
   FSharedNetSocketClient();
   MO_ABSTRACT ~FSharedNetSocketClient();
public:
   static TSize CalculateCapacity();
   MO_OVERRIDE void OnSharedInitialize();
   MO_OVERRIDE void OnSharedLink(TShareSegment& segment);
   MO_OVERRIDE TSize SharedCapacity();
public:
   //------------------------------------------------------------
   MO_INLINE SNetSocketClient* NetClient(){
      return _gClient;
   }
   //------------------------------------------------------------
   MO_INLINE TInt32 NetId(){
      return _gClient->id;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetId(TInt32 id){
      _gClient->id = id;
   }
   //------------------------------------------------------------
   MO_INLINE TBool IsNetQueried(){
      return _gClient->queried;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetQueried(TBool queried){
      _gClient->queried = queried;
   }
   //------------------------------------------------------------
   MO_INLINE TBool IsNetConnected(){
      return _gClient->connected;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetConnected(TBool connected){
      _gClient->connected = connected;
   }
   //------------------------------------------------------------
   MO_INLINE TBool IsNetRegistered(){
      return _gClient->registered;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetRegistered(TBool registered){
      _gClient->registered = registered;
   }
   //------------------------------------------------------------
   MO_INLINE TCharC* NetName(){
      return _gClient->name;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetName(TCharC* pName){
      _gClient->name = pName;
   }
   //------------------------------------------------------------
   MO_INLINE TCharC* NetHost(){
      return _gClient->host;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetHost(TCharC* pHost){
      _gClient->host.Set(pHost);
   }
   //------------------------------------------------------------
   MO_INLINE TUint NetPort(){
      return _gClient->port;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetPort(TUint port){
      _gClient->port = (TUint16)port;
   }
   //------------------------------------------------------------
   MO_INLINE TCharC* NetRemoteHost(){
      return _gClient->remoteHost;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetRemoteHost(TCharC* pRemoteHost){
      _gClient->remoteHost.Set(pRemoteHost);
   }
   //------------------------------------------------------------
   MO_INLINE TUint NetRemotePort(){
      return _gClient->remotePort;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetRemotePort(TUint remotePort){
      _gClient->remotePort = (TUint16)remotePort;
   }
   //------------------------------------------------------------
   MO_INLINE SNetTarget& NetTarget(){
      return _gClient->target;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetTarget(const SNetTarget& target){
      _gClient->target = target;
   }
   //------------------------------------------------------------
   MO_INLINE SNetSocketTarget& NetSocketTarget(){
      return _gClient->socketTarget;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetSocketTarget(const SNetSocketTarget& target){
      _gClient->socketTarget = target;
   }
   //------------------------------------------------------------
   MO_INLINE SNetTarget& NetUdpTarget(){
      return _gClient->udpTarget;
   }
   //------------------------------------------------------------
   MO_INLINE TUint NetUdpPort(){
      return _gClient->udpPort;
   }
   //------------------------------------------------------------
   MO_INLINE void SetNetUdpPort(TUint udpPort){
      _gClient->udpPort = (TUint16)udpPort;
      _gClient->udpTarget.Reset();
      // _gClient->udpTarget.SetObjectIndex(udpPort);
   }
public:
   MO_OVERRIDE TBool OnSocketConnect();
   MO_OVERRIDE TBool OnSocketDisconnect();
public:
   MO_ABSTRACT void Reset();
public:
   MO_ABSTRACT void LinkTransfer(TNetTransfer* pTransfer);
   void Unlink();
   TCharC* DumpSocket(TChar* pDump, TSize capacity);
};

//============================================================
// <T>����ͻ���ģ�顣</T>
//============================================================
template <typename T>
class FSharedClientModule : public FSharedModule{
protected:
   T* _pItem;
public:
   //------------------------------------------------------------
   FSharedClientModule(){
      _pItem = MO_CREATE(T);
   }
   //------------------------------------------------------------
   MO_ABSTRACT ~FSharedClientModule(){
      MO_DELETE(_pItem);
   }
public:
   //------------------------------------------------------------
   // <T>��ö���</T>
   T* Get(){
      return _pItem;
   }
   //------------------------------------------------------------
   MO_ABSTRACT T* LinkTransfer(TNetTransfer* pTransfer){
      MO_ASSERT(pTransfer);
      // ������Ӷ�Ӧ�����ط�����
      SNetSocketLinker* pLinker = RNetSocketLinkerModule::Instance().LinkTransfer(pTransfer);
      if(!pLinker->HasLinker()){
         // �ռ��û�
         _pItem->LinkTransfer(pTransfer);
         pLinker->Link(_pItem);
      }
      return _pItem;
   }
public:
   //------------------------------------------------------------
   // <T>��������ڴ������Ϣ��</T>
   void DumpShared(){
      TChar format[MO_MEMORY_FORMATLENGTH];
      TInt capacity = T::CalculateCapacity();
      TInt total = capacity;
      MO_INFO(MO_DUMP_SHARED_FMT "%4d + %4d",
            (TCharC*)this->_name,
            RInt::FormatCapacity(total, format, MO_MEMORY_FORMATLENGTH),
            0, capacity);
   }
};

//============================================================
// <T>����ͻ��˼���ģ�顣</T>
//============================================================
template <typename T>
class FSharedClientCollectionModule :
      public FSharedModule,
      public MAllocatorPool<T>{
protected:
   TInt _capacity;
public:
   //------------------------------------------------------------
   FSharedClientCollectionModule(){
      _capacity = 0;
   }
   //------------------------------------------------------------
   MO_ABSTRACT ~FSharedClientCollectionModule(){
      MAllocatorPool<T>::InnerReleaseAll();
   }
public:
   //------------------------------------------------------------
   // <T>��ö����������</T>
   TInt Capacity(){
      return _capacity;
   }
public:
   //------------------------------------------------------------
   // <T>��������λ�ã���ö���</T>
   MO_ABSTRACT T FindByIndex(TInt index){
      return this->_pStorage->Nvl(index, NULL);
   }
   //------------------------------------------------------------
   // <T>�������Ӷ˿ڣ����Ҷ���</T>
   MO_ABSTRACT T FindByPort(TInt port){
      SNetSocketLinker* pLinker = RNetSocketLinkerModule::Instance().Get(port);
      if(!pLinker->IsConnected()){
         return NULL;
      }
      return (T)pLinker->Get();
   }
   //------------------------------------------------------------
   // <T>������Ϣ���󣬲��Ҷ���</T>
   MO_ABSTRACT T FindByRouter(TNetRouter* pRouter){
      MO_ASSERT(pRouter);
      TUint16 index = pRouter->RouterHead().Origin().ObjectIndex();
      SNetSocketLinker* pLinker = RNetSocketLinkerModule::Instance().Get(index);
      if(!pLinker->IsConnected()){
         return NULL;
      }
      return (T)pLinker->Get();
   }
public:
   //------------------------------------------------------------
   // <T>�ͷŶ���</T>
   MO_ABSTRACT T Alloc(){
      return this->InnerAlloc();
   }
   //------------------------------------------------------------
   // <T>�ͷŶ���</T>
   MO_ABSTRACT T Alloc(TInt index){
      return this->InnerAlloc(index);
   }
   //------------------------------------------------------------
   // <T>�ͷŶ���</T>
   MO_ABSTRACT TBool Free(T pItem){
      MO_ASSERT(pItem);
      // ��������
      pItem->Reset();
      // �ͷŶ���
      this->InnerFree(pItem);
      return ETrue;
   }
public:
   //------------------------------------------------------------
   MO_ABSTRACT T LinkRouter(TNetRouter* pRouter){
      MO_ASSERT(pRouter);
      TUint index = pRouter->RouterHead().Origin().ObjectIndex();
      // ������Ӷ�Ӧ����������
      SNetSocketLinker* pLinker = RNetSocketLinkerModule::Instance().Get(index);
      if(!pLinker->HasLinker()){
         // �ռ�����
         //T pItem = Alloc(index);
         //pItem->LinkRouter(pRouter);
         // ��������
         //pLinker->Link(pItem);
      }
      return (T)pLinker->Get();
   }
   //------------------------------------------------------------
   MO_ABSTRACT T LinkTransfer(TNetTransfer* pTransfer){
      MO_ASSERT(pTransfer);
      TUint index = pTransfer->TransferHead().Socket().Index();
      // ������Ӷ�Ӧ����������
      SNetSocketLinker* pLinker = RNetSocketLinkerModule::Instance().Get(index);
      if(!pLinker->HasLinker()){
         // �ռ�����
         T pItem = Alloc();
         pItem->LinkTransfer(pTransfer);
         // ��������
         pLinker->Link(pItem);
      }
      return (T)pLinker->Get();
   }
   //------------------------------------------------------------
   MO_ABSTRACT T LinkTransfer(TNetTransfer* pTransfer, TInt index){
      MO_ASSERT(pTransfer);
      TUint port = pTransfer->RouterHead().SessionId();
      // ������Ӷ�Ӧ����������
      SNetSocketLinker* pLinker = RNetSocketLinkerModule::Instance().Get(port);
      if(!pLinker->HasLinker()){
         // �ռ�����
         T pItem = Alloc(index);
         pItem->LinkTransfer(pTransfer);
         // ��������
         pLinker->Link(pItem);
      }
      return (T)pLinker->Get();
   }
   //------------------------------------------------------------
   MO_ABSTRACT TBool Link(T pItem){
      MO_ASSERT(pItem);
      return ETrue;
   }
   //------------------------------------------------------------
   MO_ABSTRACT TBool Unlink(T pItem){
      MO_ASSERT(pItem);
      // �Ͽ���������
      TUint port = pItem->NetPort();
      SNetSocketLinker* pLinker = RNetSocketLinkerModule::Instance().Get(port);
      MO_ASSERT(pLinker->Get() == pItem);
      return pLinker->Unlink();
   }
};

//============================================================
// <T>�����߼����ࡣ</T>
//
// @history 100311 MAOCY ����
//============================================================
class MO_CR_DECLARE FMessageLogic : public FConsole{
public:
   FNetTransferProcessor* _pProcessor;
   FNetMessageStatisticsMachine* _pStatisticsMachine;
public:
   FMessageLogic();
   MO_ABSTRACT ~FMessageLogic();
public:
   //------------------------------------------------------------
   // <T>�����Ϣ�������</T>
   MO_INLINE FNetTransferProcessor* TransferProcessor(){
      return _pProcessor;
   }
   //------------------------------------------------------------
   // <T>�����Ϣͳ�ƻ���</T>
   MO_INLINE FNetMessageStatisticsMachine* StatisticsMachine(){
      if(NULL == _pStatisticsMachine){
         _pStatisticsMachine = MO_CREATE(FNetMessageStatisticsMachine);
         _pStatisticsMachine->SetName(_name);
      }
      return _pStatisticsMachine;
   }
public:
   TBool OnUnknownRouter(TNetRouter* pRouter);
public:
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���</T>
   template <typename T>
   TBool RegisterRouter(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetRouter* pRouter)){
      return _pProcessor->RegisterRouter<T>(pOwner, code, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���</T>
   template <typename T>
   TBool RegisterRouter(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetRouter* pRouter)){
      return _pProcessor->RegisterRouter<T>(pOwner, code, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��</T>
   template <typename T>
   TBool RegisterTransfer(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetTransfer* pTransfer)){
      return _pProcessor->RegisterTransfer<T>(pOwner, code, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��</T>
   template <typename T>
   TBool RegisterTransfer(T* pOwner, TInt code, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetTransfer* pTransfer)){
      return _pProcessor->RegisterTransfer<T>(pOwner, code, command, pInvokeName, pProcesser);
   }
public:
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���ȫ��������</T>
   template <typename T>
   TBool RegisterRouterAll(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetRouter* pRouter)){
      return _pProcessor->RegisterRouterAll<T>(pOwner, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ��·�ɴ���ȫ��������</T>
   template <typename T>
   TBool RegisterRouterAll(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetRouter* pRouter)){
      return _pProcessor->RegisterRouterAll<T>(pOwner, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��ȫ��������</T>
   template <typename T>
   TBool RegisterTransferAll(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(TNetTransfer* pTransfer)){
      return _pProcessor->RegisterTransferAll<T>(pOwner, command, pInvokeName, pProcesser);
   }
   //------------------------------------------------------------
   // <T>ע��һ�����䴦��ȫ��������</T>
   template <typename T>
   TBool RegisterTransferAll(T* pOwner, TInt command, TCharC* pInvokeName, TBool (T::*pProcesser)(FObject*, TNetTransfer* pTransfer)){
      return _pProcessor->RegisterTransferAll<T>(pOwner, command, pInvokeName, pProcesser);
   }
public:
   MO_ABSTRACT TBool RegisterAllProcessors();
   MO_ABSTRACT TBool UnregisterAllProcessors();
public:
   MO_ABSTRACT TBool ProcessTransfer(TNetTransfer* pTransfer);
   MO_ABSTRACT TBool DispatchTransfer(TNetTransfer* pTransfer);
};

//============================================================
// <T>��ϼ�������</T>
//============================================================
class MO_CR_DECLARE FInterruptListener : public FListener{
public:
   MO_OVERRIDE TBool Process();
};

MO_NAMESPACE_END

#endif // __MO_CR_MESSAGE_H__
