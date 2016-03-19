#include <MoCmSystem.h>
#include "MoCrNetMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����·�ɶ���</T>
//
// @return ʵ�����
//============================================================
TNetRouter::TNetRouter(){
   _pData = _buffer;
   _netHead.SetProtocol(ENetProtocol_Router);
}

//============================================================
// <T>����·�ɶ���</T>
//
// @param pMessage ��Ϣ����
// @return ʵ�����
//============================================================
TNetRouter::TNetRouter(TNetMessage* pMessage){
   _pData = _buffer;
   LinkMessage(pMessage);
}

//============================================================
// <T>����·�ɶ���</T>
//============================================================
TNetRouter::~TNetRouter(){
}

//============================================================
// <T>���ռ�ô�С��</T>
//
// @return ��С
//============================================================
TInt TNetRouter::Capacity(){
   TInt netCapacity = _netHead.Capacity();
   TInt messageCapacity = _messageHead.Capacity();
   TInt routerCapacity = _routerHead.Capacity();
   TInt capacity = netCapacity + messageCapacity + routerCapacity + _dataLength;
   return capacity;
}

//============================================================
// <T>������һ����Ϣ��ȫ�����ݡ�</T>
//
// @param pMessage ��Ϣ����
//============================================================
void TNetRouter::LinkMessage(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ��������ͷ��Ϣ
   TNetHead& netHead = pMessage->NetHead();
   _netHead.SetSign(netHead.Sign());
   _netHead.SetHash(netHead.Hash());
   // ������Ϣͷ��Ϣ
   _messageHead.Assign(pMessage->MessageHead());
   // ������Ϣ��Ϣ
   TNetMessageInfo* pMessageInfo = pMessage->MessageInfo();
   if(NULL != pMessageInfo){
      _routerHead.Source().SetServerType((TUint8)pMessageInfo->SourceTerminal());
      _routerHead.Target().SetServerType((TUint8)pMessageInfo->TargetTerminal());
   }
   // ��������
   pMessage->SerializeData(_buffer, MO_NETMESSAGE_MAXLENGTH, &_dataLength);
}

//============================================================
// <T>��ָ��·�����ݼ���Ӧ��·�����ݡ�</T>
//
// @param pRouter ·�ɶ���
//============================================================
void TNetRouter::ContinueFrom(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   _messageHead.Continue(pRouter->MessageHead());
   _routerHead.Continue(pRouter->RouterHead());
}

//============================================================
// <T>��ָ��·����������Ӧ��·�����ݡ�</T>
//
// @param pRouter ·�ɶ���
//============================================================
void TNetRouter::ResponseFrom(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   _messageHead.Response(pRouter->MessageHead());
   _routerHead.Response(pRouter->RouterHead());
}

//============================================================
// <T>������һ��·�ɵ�ȫ�����ݡ�</T>
//
// @param pRouter ·�ɶ���
//============================================================
TBool TNetRouter::Assign(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ����ͷ��Ϣ
   _netHead.Assign(pRouter->NetHead());
   _messageHead.Assign(pRouter->MessageHead());
   _routerHead.Assign(pRouter->RouterHead());
   // ��������
   _dataLength = pRouter->DataLength();
   if(pRouter->HasData()){
      memcpy(_buffer, pRouter->DataC(), _dataLength);
   }
   return ETrue;
}

//============================================================
// <T>�洢��Ϣ���ݵ�·�����ݡ�</T>
//
// @return ������
//============================================================
TBool TNetRouter::StoreMessage(TNetMessageBuffer& buffer){
   // ����ͷ��Ϣ
   TNetHead& netHead = buffer.NetHead();
   netHead.SetLength(_netHead.Length());
   netHead.SetSign(_netHead.Sign());
   netHead.SetHash(_netHead.Hash());
   buffer.MessageHead().Assign(_messageHead);
   // ��������
   if(_dataLength > 0){
      buffer.AssignData(_pData, _dataLength);
   }
   return ETrue;
}

//============================================================
// <T>���л�·�����ݵ���������</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetRouter::SerializeRouter(TAny* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByte* pPtr = (TByte*)pMemory;
   // ��ȡͷ��С
   TInt netCapacity = _netHead.Capacity();
   TInt messageCapacity = _messageHead.Capacity();
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   TInt routerCapacity = _routerHead.Capacity();
   TInt headCapacity = netCapacity + messageCapacity + routerCapacity;
   TInt capacity = headCapacity + _dataLength;
   TByte* pData = pPtr + headCapacity;
   // ����ͷ��Ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, _pData, _dataLength);
   _netHead.SetLength((TNetLength)capacity);
   _netHead.SetProtocol(ENetProtocol_Router);
   _netHead.SetHash(hash);
   // ���л�ͷ����
   TInt offset = 0;
   offset += _netHead.Serialize(pPtr);
   offset += _messageHead.Serialize(pPtr + offset);
   offset += _routerHead.Serialize(pPtr + offset);
   if(_dataLength > 0){
      memcpy(pData, _pData, _dataLength);
   }
   // �������л����С
   *length = capacity;
   return ETrue;
}

//============================================================
// <T>�����л���������·�����ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetRouter::UnserializeRouter(TAnyC* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByteC* pPtr = (TByteC*)pMemory;
   // �����л�ͷ����
   TInt offset = 0;
   offset += _netHead.Unserialize(pPtr);
   TUint protocol = _netHead.Protocol();
   TNetSerial messageSerial = 0;
   TNetTick messageTick = 0;
   if(ENetProtocol_Message == (ENetProtocol_Message & protocol)){
      offset += _messageHead.Unserialize(pPtr + offset);
      messageSerial = _messageHead.Serial();
      messageTick = _messageHead.Tick();
   }
   if(ENetProtocol_Router == (ENetProtocol_Router & protocol)){
      offset += _routerHead.Unserialize(pPtr + offset);
   }
   TNetLength capacity = _netHead.Length();
   // ��������
   TByteC* pData = pPtr + offset;
   TInt dataLength = capacity - offset;
   // ��֤��ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, pData, dataLength);
   if(_netHead.Hash() != hash){
      MO_ERROR(TC("Unserialize router invalid hash. (head_hash=0x%08X, data_hash=0x%08X)"),
            _netHead.Hash(), hash);
      return EFalse;
   }
   // ���÷���
   if(dataLength > 0){
      memcpy(_buffer, pData, dataLength);
   }
   _dataLength = dataLength;
   *length = capacity;
   return ETrue;
}

//============================================================
// <T>���л�·�����ݵ���������</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetRouter::Serialize(TAny* pMemory, TInt size, TInt* length){
   return SerializeRouter(pMemory, size, length);
}

//============================================================
// <T>�����л���������·�����ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetRouter::Unserialize(TAnyC* pMemory, TInt size, TInt* length){
   return UnserializeRouter(pMemory, size, length);
}

//============================================================
// <T>��õ�ǰ�ڲ�״̬��Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetRouter::DumpRouter(TChar* pDump, TSize capacity){
   // ��ȡ������Ϣ
   TNetLength length = _netHead.Length();
   TUint16 protocol = _netHead.Protocol();
   TNetHash hash = _netHead.Hash();
   // ��ȡ��Ϣ��Ϣ
   TUint8 type = _messageHead.Type();
   TUint8 command = _messageHead.Command();
   TUint16 code = _messageHead.Code();
   TCharC* pName = RNetMessageFactory::CodeName(code);
   // ��ȡOrgin��Ϣ
   SNetTarget& origin = _routerHead.Origin();
   TUint8 originType = origin.ServerType();
   TCharC* pOriginTypeCode = REnumNetTerminal::ToCode((ENetTerminal)originType);
   // ��ȡSource��Ϣ
   SNetTarget& source = _routerHead.Source();
   TUint8 sourceType = source.ServerType();
   TCharC* pSourceType = REnumNetTerminal::ToString((ENetTerminal)sourceType);
   TCharC* pSourceTypeCode = REnumNetTerminal::ToCode((ENetTerminal)sourceType);
   // ��ȡTarget��Ϣ
   SNetTarget& target = _routerHead.Target();
   TUint8 targetType = target.ServerType();
   TCharC* pTargetType = REnumNetTerminal::ToString((ENetTerminal)targetType);
   TCharC* pTargetTypeCode = REnumNetTerminal::ToCode((ENetTerminal)targetType);
   // ��ûỰ���
   TNetSessionId sessionId = _routerHead.SessionId();
   // ��ȡĿ�꼯��
   TFsDump targetDump;
   TNetTargets& targets = _routerHead.Targets();
   TInt count = targets.Count();
   for(TInt n = 0; n < count; n++){
      if(n > 0){
         targetDump.Append(',');
      }
      SNetTarget& netTarget = targets[n];
      targetDump.AppendFormat(TC("(%02X-%02X-%08X)"),
            netTarget.GroupId(), netTarget.ServerId(), netTarget.ObjectHandle());
   }
   // ����������Ϣ
   TFsTrack dataTrack;
   TCharC* pDataTrack = RNetMessageFactory::DumpData(this, &dataTrack);
   // ������Ϣ
   MO_LIB_STRING_FORMAT(pDump, capacity,
         "[ %s ] - 0x%08X:%d\n"
         "--------------------------------------------------------------------------------\n"
         "-- Net     : length=0x%04X(%d), protocol=%d, hash=0x%04X\n"
         "-- Message : code=(%02X:%04X), command=%d, sender=%s(0x%02X), target=%s(0x%02X)\n"
         "-- Router  : orgin=%s(%02X-%02X-%08X), source=%s(%02X-%02X-%08X), target=%s(%02X-%02X-%08X), targets=%" MO_FMT_INT "[%s]\n"
         "--------------------------------------------------------------------------------\n"
         "%s",
         pName, sessionId, sessionId,
         length, length, protocol, hash,
         type, code, command, pSourceType, sourceType, pTargetType, targetType,
         pOriginTypeCode, origin.GroupId(), origin.ServerId(), origin.ObjectHandle(),
         pSourceTypeCode, source.GroupId(), source.ServerId(), source.ObjectHandle(),
         pTargetTypeCode, target.GroupId(), target.ServerId(), target.ObjectHandle(),
         count, (TCharC*)targetDump,
         pDataTrack);
   return pDump;
}

//============================================================
// <T>���·�����ݵ�����������Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetRouter::DumpRouterMemory(TChar* pDump, TSize capacity){
   // ���л�����
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!SerializeRouter(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      return pDump;
   }
   // ���ɵ�����Ϣ
   TInt size = MO_LIB_MIN(length, MO_NETMESSAGE_BYTEDUMP_MAXLENGTH);
   RByte::Dump(buffer, size, pDump, capacity);
   return pDump;
}

//============================================================
// <T>��õ�ǰ�ڲ�״̬��Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetRouter::Dump(TChar* pDump, TSize capacity){
   return DumpRouter(pDump, capacity);
}

MO_NAMESPACE_END
