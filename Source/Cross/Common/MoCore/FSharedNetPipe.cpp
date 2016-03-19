#include "MoCrNetMessage.h"
#include "MoCrNetPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲������ܵ���</T>
//============================================================
FSharedNetPipe::FSharedNetPipe(){
}

//============================================================
// <T>������������ܵ���</T>
//============================================================
FSharedNetPipe::~FSharedNetPipe(){
};

//============================================================
// <T>����д����Ϣ��</T>
//
// @param pMessage ��Ϣ
// @return ������
//============================================================
TBool FSharedNetPipe::TryWriteMessage(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ���л�·������
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pMessage->SerializeMessage(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serialize message failure."));
      return EFalse;
   }
   // ����д������
   if(!TryWrite(buffer, length)){
      MO_ERROR(TC("Write message failure. (length=%d)"), length);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>����д��ѹ����Ϣ��</T>
//
// @param pMessage ��Ϣ
// @return ������
//============================================================
TBool FSharedNetPipe::TryWriteMessageCompress(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ���л�·������
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pMessage->CompressMessage(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serialize message failure."));
      return EFalse;
   }
   // ����д������
   if(!TryWrite(buffer, length)){
      MO_ERROR(TC("Write message failure. (length=%d)"), length);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>����д��·�ɡ�</T>
//
// @param pMessage ��Ϣ
// @return ������
//============================================================
TBool FSharedNetPipe::TryWriteRouter(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ���л�·������
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pRouter->SerializeRouter(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serialize router failure."));
      return EFalse;
   }
   // ����д������
   if(!TryWrite(buffer, length)){
      MO_ERROR(TC("Write router failure. (length=%d)"), length);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>����д��ѹ��·�ɡ�</T>
//
// @param pMessage ��Ϣ
// @return ������
//============================================================
TBool FSharedNetPipe::TryWriteRouterCompress(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ���л�·������
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pRouter->SerializeRouter(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serialize router failure."));
      return EFalse;
   }
   // ����д������
   if(!TryWrite(buffer, length)){
      MO_ERROR(TC("Write router failure. (length=%d)"), length);
      return EFalse;
   }
   return ETrue;
}

MO_NAMESPACE_END
