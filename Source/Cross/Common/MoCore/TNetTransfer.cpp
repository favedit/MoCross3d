#include "MoCrNetMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������紫������</T>
//============================================================
TNetTransfer::TNetTransfer(){
   _netHead.SetProtocol(ENetProtocol_Transfer);
}

//============================================================
// <T>�������紫������</T>
//
// @param pMessage ��Ϣ
//============================================================
TNetTransfer::TNetTransfer(TNetMessage* pMessage){
   _netHead.SetProtocol(ENetProtocol_Transfer);
   LinkMessage(pMessage);
}

//============================================================
// <T>�������紫������</T>
//
// @param pRouter ·����
//============================================================
TNetTransfer::TNetTransfer(TNetRouter* pRouter){
   _netHead.SetProtocol(ENetProtocol_Transfer);
   LinkRouter(pRouter);
}

//============================================================
// <T>�������紫������</T>
//============================================================
TNetTransfer::~TNetTransfer(){
}

//============================================================
// <T>�������紫������</T>
//
// @param pMessage ��Ϣ
// @param modeCd ģʽ����
// @param pRouter ·����
//============================================================
TNetTransfer::TNetTransfer(TNetMessage* pMessage, EMode modeCd, TNetRouter* pRouter){
   _netHead.SetProtocol(ENetProtocol_Transfer);
   LinkMessage(pMessage);
   switch(modeCd){
      case EMode_Unknown:
         break;
      case EMode_Continue:
         ContinueFrom(pRouter);
         break;
      case EMode_Response:
         ResponseFrom(pRouter);
         break;
   }
}

//============================================================
// <T>�������紫������</T>
//
// @param pMessage ��Ϣ
// @param modeCd ģʽ����
// @param pTransfer ������
//============================================================
TNetTransfer::TNetTransfer(TNetMessage* pMessage, EMode modeCd, TNetTransfer* pTransfer){
   _netHead.SetProtocol(ENetProtocol_Transfer);
   LinkMessage(pMessage);
   switch(modeCd){
      case EMode_Unknown:
         break;
      case EMode_Continue:
         ContinueFrom(pTransfer);
         break;
      case EMode_Response:
         ResponseFrom(pTransfer);
         break;
   }
}

//============================================================
// <T>���������</T>
//
// @return ����
//============================================================
TInt TNetTransfer::Capacity(){
   TInt netCapacity = _netHead.Capacity();
   TInt messageCapacity = _messageHead.Capacity();
   TInt routerCapacity = _routerHead.Capacity();
   TInt transferCapacity = _transferHead.Capacity();
   TInt capacity = netCapacity + messageCapacity + routerCapacity + transferCapacity + _dataLength;
   return capacity;
}

//============================================================
// <T>��ָ��·��������Ӧ��·�����ݡ�</T>
//
// @param pRouter ·�ɶ���
//============================================================
void TNetTransfer::ContinueFrom(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   _messageHead.Continue(pRouter->MessageHead());
   _routerHead.Continue(pRouter->RouterHead());
}

//============================================================
// <T>��ָ�����������ݼ���Ӧ��·�����ݡ�</T>
//
// @param pTransfer ������
//============================================================
void TNetTransfer::ContinueFrom(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   _messageHead.Continue(pTransfer->MessageHead());
   _routerHead.Continue(pTransfer->RouterHead());
   _transferHead.Assign(pTransfer->TransferHead());
}

//============================================================
// <T>��ָ��·��������Ӧ��·�����ݡ�</T>
//
// @param pRouter ·����
//============================================================
void TNetTransfer::ResponseFrom(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   _messageHead.Response(pRouter->MessageHead());
   _routerHead.Response(pRouter->RouterHead());
}

//============================================================
// <T>��ָ����������������Ӧ�������ݡ�</T>
//
// @param pTransfer ������
//============================================================
void TNetTransfer::ResponseFrom(TNetTransfer* pTransfer){
   MO_ASSERT(pTransfer);
   _messageHead.Response(pTransfer->MessageHead());
   _routerHead.Response(pTransfer->RouterHead());
   _transferHead.Assign(pTransfer->TransferHead());
}

//============================================================
// <T>������Ϣ��Ϣ��</T>
//
// @param pMessage ��Ϣ��Ϣ
//============================================================
void TNetTransfer::LinkMessage(TNetMessage* pMessage){
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
// <T>����·����Ϣ��</T>
//
// @param pRouter ·����Ϣ
//============================================================
void TNetTransfer::LinkRouter(TNetRouter* pRouter){
   MO_ASSERT(pRouter);
   // ����ͷ��Ϣ
   TNetHead& netHead = pRouter->NetHead();
   _netHead.SetSign(netHead.Sign());
   _netHead.SetHash(netHead.Hash());
   _messageHead.Assign(pRouter->MessageHead());
   _routerHead.Assign(pRouter->RouterHead());
   // ��������
   pRouter->SerializeData(_buffer, MO_NETMESSAGE_MAXLENGTH, &_dataLength);
}

//============================================================
// <T>����·����Ϣ��</T>
//
// @param pRouter ·����Ϣ
//============================================================
TBool TNetTransfer::Assign(TNetTransfer* pRouter){
   MO_ASSERT(pRouter);
   // ����ͷ��Ϣ
   _netHead.Assign(pRouter->NetHead());
   _messageHead.Assign(pRouter->MessageHead());
   _routerHead.Assign(pRouter->RouterHead());
   _transferHead.Assign(pRouter->TransferHead());
   // ��������
   _dataLength = pRouter->DataLength();
   if(pRouter->HasData()){
      memcpy(_buffer, pRouter->DataC(), _dataLength);
   }
   return ETrue;
}

//============================================================
// <T>���л��������ݵ���������</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetTransfer::Serialize(TAny* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByte* pPtr = (TByte*)pMemory;
   // ��ȡͷ��С
   TInt netCapacity = _netHead.Capacity();
   TInt messageCapacity = _messageHead.Capacity();
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   TInt routerCapacity = _routerHead.Capacity();
   TInt transferCapacity = _transferHead.Capacity();
   TInt headCapacity = netCapacity + messageCapacity + routerCapacity + transferCapacity;
   TInt capacity = headCapacity + _dataLength;
   TByte* pData = pPtr + headCapacity;
   // ����ͷ��Ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, _pData, _dataLength);
   _netHead.SetLength((TNetLength)capacity);
   _netHead.SetProtocol(ENetProtocol_Transfer);
   _netHead.SetHash(hash);
   // ���л�ͷ����
   TInt offset = 0;
   offset += _netHead.Serialize(pPtr);
   offset += _messageHead.Serialize(pPtr + offset);
   offset += _routerHead.Serialize(pPtr + offset);
   offset += _transferHead.Serialize(pPtr + offset);
   if(_dataLength > 0){
      memcpy(pData, _pData, _dataLength);
   }
   // �������л����С
   MO_ASSERT(capacity <= size);
   *length = capacity;
   return ETrue;
}

//============================================================
// <T>�����л����������������ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetTransfer::Unserialize(TAnyC* pMemory, TInt size, TInt* length){
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
   if(ENetProtocol_Transfer == (ENetProtocol_Transfer & protocol)){
      offset += _transferHead.Unserialize(pPtr + offset);
   }
   _netHead.SetProtocol(ENetProtocol_Transfer);
   TInt capacity = _netHead.Length();
   // ��������
   TByteC* pData = pPtr + offset;
   TInt dataLength = capacity - offset;
   // ��֤��ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, pData, dataLength);
   if(_netHead.Hash() != hash){
      MO_ERROR(TC("Unserialize transfer invalid hash. (head_hash=0x%08X, data_hash=0x%08X)"), _netHead.Hash(), hash);
      return EFalse;
   }
   // ���÷���
   if(dataLength > 0){
      memcpy(_buffer, pData, dataLength);
   }
   _dataLength = dataLength;
   // ���÷����л����С
   if(capacity != size){
      MO_ERROR(TC("Unserialize transfer invalid length. (size=%d, length=%d)"), size, capacity);
      return EFalse;
   }
   *length = capacity;
   return ETrue;
}

//============================================================
// <T>��õ�ǰ�ڲ�״̬��Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetTransfer::DumpTransfer(TChar* pDump, TSize capacity){
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
   // ��ȡ·����Ϣ
   TUint32 handle = _transferHead.Handle();
   TUint16 port = _transferHead.Port();
   TUint16 index = _transferHead.Socket().Index();
   TUint16 serial = _transferHead.Socket().Serial();
   // ����������Ϣ
   TFsTrack dataTrack;
   TCharC* pDataTrack = RNetMessageFactory::DumpData(this, &dataTrack);
   // ������Ϣ
   MO_LIB_STRING_FORMAT(pDump, capacity,
      TC("[ %s ] - 0x%08X:%d\n"
         "--------------------------------------------------------------------------------\n"
         "-- Net      : length=0x%04X(%d), protocol=%d, hash=0x%04X\n"
         "-- Message  : code=(%02X:%04X), command=%d, sender=%s(0x%02X), target=%s(0x%02X)\n"
         "-- Router   : orgin=%s(%02X-%02X-%08X), source=%s(%02X-%02X-%08X), target=%s(%02X-%02X-%08X), targets=%" MO_FMT_INT "[%s]\n"
         "-- Transfer : handle=%d, port=%d, index=%d, serial=%d\n"
         "--------------------------------------------------------------------------------\n"
         "%s"),
         pName, sessionId, sessionId,
         length, length, protocol, hash,
         type, code, command, pSourceType, sourceType, pTargetType, targetType,
         pOriginTypeCode, origin.GroupId(), origin.ServerId(), origin.ObjectHandle(),
         pSourceTypeCode, source.GroupId(), source.ServerId(), source.ObjectHandle(),
         pTargetTypeCode, target.GroupId(), target.ServerId(), target.ObjectHandle(),
         count, (TCharC*)targetDump,
         handle, port, index, serial,
         pDataTrack);
   return pDump;
}

//============================================================
// <T>��õ�ǰ�ڲ���״̬��Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetTransfer::DumpSimple(TChar* pDump, TSize capacity){
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
   // ��ȡ·����Ϣ
   TUint32 handle = _transferHead.Handle();
   TUint16 port = _transferHead.Port();
   TUint16 index = _transferHead.Socket().Index();
   TUint16 serial = _transferHead.Socket().Serial();
   // ������Ϣ
   MO_LIB_STRING_FORMAT(pDump, capacity,
      TC("[ %s ] - 0x%08X:%d\n"
         "--------------------------------------------------------------------------------\n"
         "-- Net      : length=0x%04X(%d), protocol=%d, hash=0x%04X\n"
         "-- Message  : code=(%02X:%04X), command=%d, sender=%s(0x%02X), target=%s(0x%02X)\n"
         "-- Router   : orgin=%s(%02X-%02X-%08X), source=%s(%02X-%02X-%08X), target=%s(%02X-%02X-%08X), targets=%" MO_FMT_INT "[%s]\n"
         "-- Transfer : handle=%d, port=%d, index=%d, serial=%d\n"),
         pName, sessionId, sessionId,
         length, length, protocol, hash,
         type, code, command, pSourceType, sourceType, pTargetType, targetType,
         pOriginTypeCode, origin.GroupId(), origin.ServerId(), origin.ObjectHandle(),
         pSourceTypeCode, source.GroupId(), source.ServerId(), source.ObjectHandle(),
         pTargetTypeCode, target.GroupId(), target.ServerId(), target.ObjectHandle(),
         count, (TCharC*)targetDump,
         handle, port, index, serial);
   return pDump;
}

//============================================================
// <T>��õ�ǰ�ڲ�״̬��Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetTransfer::Dump(TChar* pDump, TSize capacity){
   return DumpTransfer(pDump, capacity);
}

MO_NAMESPACE_END
