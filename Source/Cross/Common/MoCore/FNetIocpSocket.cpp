#include "MoCrNetIocp.h"

MO_NAMESPACE_BEGIN

#ifdef _MO_WINDOWS

//============================================================
// <T>����ͻ����ӡ�</T>
//============================================================
FNetIocpSocket::FNetIocpSocket(){
   RMemory::Clear(&_data, sizeof(SIocpData));
   _data.pSocket = this;
}

//============================================================
// <T>����ͻ����ӡ�</T>
//============================================================
SIocpData& FNetIocpSocket::Data(){
   return _data;
}

//============================================================
// <T>��ʼ�������ӡ�</T>
//============================================================
TBool FNetIocpSocket::Startup(){
   // ����Ƿ�����
   if(_processing){
      return EFalse;
   }
   // ��������
   TDateTime tick = RDateTime::Current();
   _isConnected = ETrue;
   _info.createDateTime = tick;
   _info.updateDateTime = tick;
   _info.receiveSerial = 0;
   _info.receiveDateTime = tick;
   _info.receiveTick = 0;
   _info.sendSerial = 0;
   _info.sendDateTime = tick;
   // ���û����С
   SetReceiveBufferSize(_info.receiveBufferSize);
   SetSendBufferSize(_info.sendBufferSize);
   // ���ӵ�����
   MO_ASSERT(_pReceivePool);
   _pReceivePool->Add(this, 0);
   _processing = ETrue;
   return ETrue;
}

//============================================================
// <T>�ر��������ӡ�</T>
//============================================================
TBool FNetIocpSocket::Shutdown(){
   // ����Ƿ�����
   if(!_processing){
      return EFalse;
   }
   // �ӳ���ɾ��
   _pReceivePool->Remove(this, 0);
   MO_CLEAR(_pReceivePool);
   // ������Ϣ
   _pInputPipe->Reset();
   _pOutputPipe->Reset();
   // �رն���
   Close();
   _processing = EFalse;
   return ETrue;
}

#endif // _MO_WINDOWS

MO_NAMESPACE_END
