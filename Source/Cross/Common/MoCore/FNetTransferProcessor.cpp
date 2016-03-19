#include "MoCrNetConnection.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������紫�䴦������</T>
//============================================================
FNetTransferProcessor::FNetTransferProcessor(){
   _pHandlesList = MO_CREATE(FNetTransferHandlesList);
   _pHandless = MO_CREATE(FNetTransferHandlesVector, MO_NETMESSAGE_COUNT);
   // ��װ��׽��
   _pCatcher = MO_CREATE(FNetMessageCatcher);
   _pCatcher->Install();
}

//============================================================
// <T>���紫�䴦������</T>
//============================================================
FNetTransferProcessor::~FNetTransferProcessor(){
   MO_DELETE(_pHandlesList);
   MO_DELETE(_pHandless);
   MO_DELETE(_pCatcher);
}

//============================================================
// <T>ͬ��������������ϡ�</T>
//
// @param code ����
// @return �������������
//============================================================
FNetTransferHandles* FNetTransferProcessor::SyncHandles(TInt code){
   FNetTransferHandles* pHandles = _pHandless->Nvl(code, NULL);
   if(NULL == pHandles){
      pHandles = MO_CREATE(FNetTransferHandles);
      pHandles->SetCatcher(_pCatcher);
      _pHandlesList->Push(pHandles);
      _pHandless->ExtendSet(code, pHandles);
   }
   return pHandles;
}

//============================================================
// <T>�ַ��������߼���</T>
//
// @param pTransfer ������
// @return ������
//============================================================
TBool FNetTransferProcessor::Dispatch(TNetTransfer* pTransfer){
   // �����Ϣ����
   MO_ASSERT(pTransfer);
   TInt code = pTransfer->MessageHead().Code();
   // ������Ϣ
   TBool result = EFalse;
   FNetTransferHandles* pProcessors = _pHandless->Nvl(code, NULL);
   if(NULL != pProcessors){
      // ��ע�����Ϣ���������
      pProcessors->Process(NULL, pTransfer);
      result = ETrue;
   }
   return result;
}

//============================================================
// <T>�ַ��������߼���</T>
//
// @param pSender 
// @param pTransfer ������
// @return ������
//============================================================
TBool FNetTransferProcessor::Dispatch(FObject* pSender, TNetTransfer* pTransfer){
   // �����Ϣ����
   MO_ASSERT(pTransfer);
   TInt code = pTransfer->MessageHead().Code();
   // ������Ϣ
   TBool result = EFalse;
   FNetTransferHandles* pProcessors = _pHandless->Nvl(code, NULL);
   if(NULL != pProcessors){
      // ��ע�����Ϣ���������
      pProcessors->Process(pSender, pTransfer);
      result = ETrue;
   }
   return result;
}

MO_NAMESPACE_END
