#include "MoCrNet.h"
#include "MoCrMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲���������ӵĿͻ��ˡ�</T>
//
// @return ��������ʵ��
//============================================================
FSharedNetSocketClient::FSharedNetSocketClient(){
   MO_CLEAR(_gClient);
}

//============================================================
// <T>���������������ӵĿͻ��ˡ�</T>
//============================================================
FSharedNetSocketClient::~FSharedNetSocketClient(){
}

//============================================================
// <T>���㹲���ڴ�ߴ硣</T>
//
// @return �����ڴ�ߴ�
//============================================================
TSize FSharedNetSocketClient::CalculateCapacity(){
   return sizeof(SNetSocketClient);
}

//============================================================
// <T>��ʼ�������ڴ档</T>
//============================================================
void FSharedNetSocketClient::OnSharedInitialize(){
   RType<SNetSocketClient>::Clear(_gClient);
   _gClient->id = -1;
}

//============================================================
// <T>���乲���ڴ档</T>
//
// @param segment �����ڴ��
//============================================================
void FSharedNetSocketClient::OnSharedLink(TShareSegment& segment){
   _gClient = segment.TypeAlloc<SNetSocketClient>();
}

//============================================================
// <T>��ù����ڴ�ߴ硣</T>
//
// @return �����ڴ�ߴ�
//============================================================
TSize FSharedNetSocketClient::SharedCapacity(){
   return sizeof(SNetSocketClient);
}

//============================================================
// <T>�������Ӵ���</T>
//
// @return ������
//============================================================
TBool FSharedNetSocketClient::OnSocketConnect(){
   return MNetSocketLinker::OnSocketConnect();
}

//============================================================
// <T>����Ͽ�����</T>
//
// @return ������
//============================================================
TBool FSharedNetSocketClient::OnSocketDisconnect(){
   return MNetSocketLinker::OnSocketDisconnect();
}

//============================================================
// <T>�������ӡ�</T>
//
// @param pTransfer �������
//============================================================
void FSharedNetSocketClient::LinkTransfer(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   TNetTransferHead& head = pTransfer->TransferHead();
   _gClient->connected = ETrue;
   _gClient->socketTarget.Set(head.Socket());
}

//============================================================
// <T>�������ݡ�</T>
//============================================================
void FSharedNetSocketClient::Reset(){
   RType<SNetSocketClient>::Clear(_gClient);
}

//============================================================
// <T>�Ͽ����ӡ�</T>
//============================================================
void FSharedNetSocketClient::Unlink(){
   RType<SNetSocketClient>::Clear(_gClient);
}

//============================================================
// <T>�������ʱ��Ϣ��</T>
//
// @param pDump �������
// @param capacity �������
// @return ������Ϣ
//============================================================
TCharC* FSharedNetSocketClient::DumpSocket(TChar* pDump, TSize capacity){
   TStringRefer dump(pDump, capacity);
   dump.AppendFormat(TC("host=%s:%d, socket=%d:%d"),
         (TCharC*)_gClient->host, _gClient->port,
         _gClient->socketTarget.Index(), _gClient->socketTarget.Serial());
   return (TCharC*)dump;
}

MO_NAMESPACE_END
