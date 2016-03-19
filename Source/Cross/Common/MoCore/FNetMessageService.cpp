#include "MoCrMessage.h"
#include "MoCrNetTransfer.h"

#define MO_TAG_PROPERTY TC("Property")
#define MO_PTR_NAME     TC("name")

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣ����</T>
//============================================================
FNetMessageService::FNetMessageService(){
   _groupId = 0;
   _serverId = 0;
   _workerCount = 0;
}

//============================================================
// <T>������Ϣ����</T>
//============================================================
FNetMessageService::~FNetMessageService(){
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FNetMessageService::LoadConfig(FXmlNode* pConfig){
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next(MO_TAG_PROPERTY)){
      FXmlNode* pNode = *iterator;
      if(pNode->IsAttribute(MO_PTR_NAME, TC("group_id"))){
         // ��ȡ��������
         _groupId = pNode->TextAsInt();
         MO_DEBUG(TC("Load service(%s) property. (group_id=%d)"), (TCharC*)_name, _groupId);
      }else if(pNode->IsAttribute(MO_PTR_NAME, TC("id"))){
         // ��ȡ����ı��
         _serverId = pNode->TextAsInt();
         MO_DEBUG(TC("Load service(%s) property. (id=%d)"), (TCharC*)_name, _serverId);
      }else if(pNode->IsAttribute(MO_PTR_NAME, TC("label"))){
         // ��ȡ���������
         _label = pNode->Text();
         MO_DEBUG(TC("Load service(%s) property. (label=%s)"), (TCharC*)_name, (TCharC*)_label);
      }else if(pNode->IsAttribute(MO_PTR_NAME, TC("worker_count"))){
         // ��ȡ����������
         _workerCount = pNode->TextAsInt();
         MO_DEBUG(TC("Load service(%s) property. (worker_count=%d)"), (TCharC*)_name, _workerCount);
      }
   }
   return ESuccess;
}

//============================================================
// <T>����δע�������Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return ������
//============================================================
TResult FNetMessageService::OnUnknownRouter(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // δ������Ϣ
#ifdef _MO_DEBUG
   TChar dump[MO_FS_DUMP_LENGTH];
   TChar format[MO_FS_DUMP_LENGTH];
   MO_ERROR(TC("Unknown process router.\n%s\n%s"),
         pRouter->Dump(dump, MO_FS_DUMP_LENGTH),
         pRouter->DumpMemory(format, MO_FS_DUMP_LENGTH));
#else
   TUint16 code = pRouter->MessageHead().Code();
   TCharC* pName = RNetMessageFactory::CodeName(code);
   TNetRouterHead& routerHead = pRouter->RouterHead();
   MO_ERROR(TC("Unknown process router. (name=%s, code=%d, source_type=%d, source_type=%d)"),
         pName, code, routerHead.SourceType(), routerHead.SourceType(), routerHead.TargetType());
#endif
   return ESuccess;
}

//============================================================
// <T>ע��������Ϣ��</T>
//
// @return ������
//============================================================
TResult FNetMessageService::RegisterAllProcessors(){
   return ESuccess;
}

//============================================================
// <T>ע��������Ϣ��</T>
//
// @return ������
//============================================================
TResult FNetMessageService::UnregisterAllProcessors(){
   return ESuccess;
}

//============================================================
// <T>������Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return ������
//============================================================
TResult FNetMessageService::ProcessTransfer(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   // ������Ϣ
   TChar dump[MO_FS_DUMP_LENGTH];
   TChar format[MO_FS_DUMP_LENGTH];
   MO_ERROR(TC("Process router.\n%s%s"),
         pTransfer->Dump(dump, MO_FS_DUMP_LENGTH),
         pTransfer->DumpMemory(format, MO_FS_DUMP_LENGTH));
   return ESuccess;
}

//============================================================
// <T>�׷���Ϣ��</T>
//
// @param pMessage ��Ϣ����
// @return ������
//============================================================
TResult FNetMessageService::DispatchTransfer(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   // �׷���Ϣ
   TChar dump[MO_FS_DUMP_LENGTH];
   TChar format[MO_FS_DUMP_LENGTH];
   MO_ERROR(TC("Dispatch router.\n%s%s"),
         pTransfer->Dump(dump, MO_FS_DUMP_LENGTH),
         pTransfer->DumpMemory(format, MO_FS_DUMP_LENGTH));
   return ESuccess;
}

MO_NAMESPACE_END
