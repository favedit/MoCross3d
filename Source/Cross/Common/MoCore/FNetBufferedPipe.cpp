#include "MoCrNetMessage.h"
#include "MoCrNetPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������绺����С�</T>
//============================================================
FNetBufferedPipe::FNetBufferedPipe(){
}

//============================================================
// <T>�������绺����С�</T>
//============================================================
FNetBufferedPipe::~FNetBufferedPipe(){
};

//============================================================
// <T>��ùܵ��ĳ��ȡ�</T>
//
// @return ���ݳ���
//============================================================
TInt FNetBufferedPipe::Length(){
   return FBufferedPipe::Length();
}

//============================================================
// <T>�ӹܵ��ڻ��һ�����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @param pLength ��ȡ����
// @return ������
//============================================================
EStreamResult FNetBufferedPipe::Peek(TAny* pData, TInt length, TInt* pLength){
   return FBufferedPipe::Peek(pData, length, pLength);
}

//============================================================
// <T>�ӹܵ��ڶ�ȡһ�����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @param pLength ��ȡ����
// @return ������
//============================================================
EStreamResult FNetBufferedPipe::Read(TAny* pData, TInt length, TInt* pLength){
   return FBufferedPipe::Read(pData, length, pLength);
}

//============================================================
// <T>��ܵ���д��һ�����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @param pLength ��ȡ����
// @return ������
//============================================================
EStreamResult FNetBufferedPipe::Write(TAnyC* pData, TInt length, TInt* pLength){
   return FBufferedPipe::Write(pData, length, pLength);
}

//============================================================
// <T>д��һ����Ϣ��</T>
//
// @param pMessage ��Ϣ
// @return ������
//============================================================
TBool FNetBufferedPipe::WriteMessage(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ���л�·������
   TInt length = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pMessage->SerializeMessage(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serialize message failure."));
      return EFalse;
   }
   // ����д������
   TInt lengthWrite = 0;
   if(EStreamResult_Success != FBufferedPipe::Write(buffer, length, &lengthWrite)){
      MO_ERROR(TC("Write message failure. (length=%d)"), length);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>д��һ��ѹ����Ϣ��</T>
//
// @param pMessage ��Ϣ
// @return ������
//============================================================
TBool FNetBufferedPipe::WriteMessageCompress(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ���л�·������
   TInt length = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pMessage->CompressMessage(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serialize message failure."));
      return EFalse;
   }
   // ����д������
   TInt lengthWrite = 0;
   if(EStreamResult_Success != FBufferedPipe::Write(buffer, length, &lengthWrite)){
      MO_ERROR(TC("Write message failure. (length=%d)"), length);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>д��һ��·�ɡ�</T>
//
// @param pMessage ��Ϣ
// @return ������
//============================================================
TBool FNetBufferedPipe::WriteRouter(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ���л�·������
   TInt length = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pRouter->SerializeRouter(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serialize router failure."));
      return EFalse;
   }
   // ����д������
   TInt lengthWrite = 0;
   if(EStreamResult_Success != FBufferedPipe::Write(buffer, length, &lengthWrite)){
      MO_ERROR(TC("Write router failure. (length=%d)"), length);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>д��һ��ѹ��·�ɡ�</T>
//
// @param pMessage ��Ϣ
// @return ������
//============================================================
TBool FNetBufferedPipe::WriteRouterCompress(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ���л�·������
   TInt length = 0;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!pRouter->SerializeRouter(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      MO_ERROR(TC("Serialize router failure."));
      return EFalse;
   }
   // ����д������
   TInt lengthWrite = 0;
   if(EStreamResult_Success != FBufferedPipe::Write(buffer, length, &lengthWrite)){
      MO_ERROR(TC("Write router failure. (length=%d)"), length);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>�������ݡ�</T>
//
// @return ������
//============================================================
TBool FNetBufferedPipe::Reset(){
   return FBufferedPipe::Reset();
}

MO_NAMESPACE_END
