#include "MoCrNetTransferIocp.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����׽���ģ�����</T>
//
// @return ��ǰ����ָ�롣
//============================================================
FNetIocpSocketModule::FNetIocpSocketModule(){
}

//============================================================
// <T>�����׽���ģ�����</T>
//
// @return �޷���ֵ
//============================================================
FNetIocpSocketModule::~FNetIocpSocketModule(){
}

//============================================================
// <T>��ʼ������</T>
//
// @return ������
//============================================================
TResult FNetIocpSocketModule::OnInitialize(){
   // ��ùܵ��ֿ��ռ���
   FBufferedPipeBlockAllocator* pAllocator = RNetPipeBlockPoolModule::Instance().Alloc(_blockCapacity);
   // �����˿ڶ���
   _sectionPool.Enter();
   for(TInt n = 0; n < _socketCount; n++){
      // �������Ӷ���
      FNetIocpSocket* pSocket = MO_CREATE(FNetIocpSocket);
      // �洢����
      TInt index = _pPool->Store(pSocket);
      pSocket->SetIndex((TUint16)index);
      pSocket->NetInfo()->receiveBufferSize = (TUint32)_socketReceiveBuffer;
      pSocket->NetInfo()->sendBufferSize = (TUint32)_socketSendBuffer;
      pSocket->LinkAllocator(_socketCapacity, pAllocator);
   }
   _sectionPool.Leave();
   return ESuccess;
}


MO_NAMESPACE_END
