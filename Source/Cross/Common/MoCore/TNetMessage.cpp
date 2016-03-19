#include <MoCmSystem.h>
#include "MoCrNetMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣ����</T>
//
// @return ʵ�����
//============================================================
TNetMessage::TNetMessage(){
   _netHead.SetProtocol(ENetProtocol_Message);
}

//============================================================
// <T>������Ϣ����</T>
//
// @param pMessage ��Ϣ����
// @return ʵ�����
//============================================================
TNetMessage::TNetMessage(TNetMessage* pMessage){
   Assign(pMessage);
}

//============================================================
// <T>���ռ�ô�С��</T>
//
// @return ��С
//============================================================
TInt TNetMessage::Capacity(){
   TInt capacity = _netHead.Capacity();
   capacity += _messageHead.Capacity();
   capacity += _dataLength;
   return capacity;
}

//============================================================
// <T>�����Ϣ��������</T>
//
// @return ��Ϣ��������
//============================================================
TNetMessageInfo* TNetMessage::MessageInfo(){
   TInt code = MessageHead().Code();
   TNetMessageInfo* pMessageInfo = RNetMessageFactory::CodeInfo(code);
   return pMessageInfo;
}

//============================================================
// <T>������һ����Ϣ��ȫ�����ݡ�</T>
//
// @param pMessage ��Ϣ����
//============================================================
TBool TNetMessage::Assign(TNetMessage* pMessage){
   MO_ASSERT(pMessage);
   // ��������ͷ
   _netHead.Assign(pMessage->NetHead());
   _messageHead.Assign(pMessage->MessageHead());
   // ��������
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(pMessage->SerializeData(buffer, MO_NETMESSAGE_MAXLENGTH, &_dataLength)){
      TBool result = UnserializeData(buffer, MO_NETMESSAGE_MAXLENGTH, &_dataLength);
      if(result){
         return ETrue;
      }
   }
   return EFalse;
}

//============================================================
// <T>���л���Ϣ���ݵ���������</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetMessage::SerializeMessage(TAny* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByte* pPtr = (TByte*)pMemory;
   // ���ͷ����
   TInt netCapacity = _netHead.Capacity();
   TInt messageCapacity = _messageHead.Capacity();
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   TInt headCapacity = netCapacity + messageCapacity;
   // ���л�����
   TByte* pData = pPtr + headCapacity;
   TInt dataLength;
   SerializeData(pData, size - headCapacity, &dataLength);
   // ����ͷ��Ϣ
   TSize capacity = headCapacity + dataLength;
   TNetHash hash = CalculateHash(messageSerial, messageTick, pData, dataLength);
   _netHead.SetLength((TNetLength)capacity);
   _netHead.SetHash(hash);
   // ���ô洢ͷ��Ϣ
   TNetHead netHead(_netHead);
   netHead.SetProtocol(ENetProtocol_Message);
   // ���л�����
   TInt offset = 0;
   offset += netHead.Serialize(pPtr);
   offset += _messageHead.Serialize(pPtr + offset);
   offset += dataLength;
   // �������л����С
   *length = offset;
   return ETrue;
}

//============================================================
// <T>�����л�����������Ϣ���ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetMessage::UnserializeMessage(TAnyC* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByteC* pPtr = (TByteC*)pMemory;
   // �����л�ͷ����
   TNetHead netHead;
   TInt netCapacity = netHead.Unserialize(pPtr);
   TInt messageCapacity = _messageHead.Unserialize(pPtr + netCapacity);
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   TInt headCapacity = netCapacity + messageCapacity;
   // ��������ͷ��Ϣ
   TNetLength netLength = _netHead.Length();
   _netHead.SetLength(netLength);
   _netHead.SetSign(netHead.Sign());
   _netHead.SetHash(netHead.Hash());
   // ��������
   TByteC* pData = pPtr + headCapacity;
   TInt dataLength = netLength - headCapacity;
   // �����ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, pData, dataLength);
   if(_netHead.Hash() != hash){
      MO_ERROR(TC("Unserial message invalid hash. (head_hash=0x%08X, data_hash=0x%08X)"),
            _netHead.Hash(), hash);
      return EFalse;
   }
   // ���÷���
   UnserializeData(pData, size - headCapacity, &dataLength);
   *length = netLength;
   return ETrue;
}

//============================================================
// <T>ѹ����Ϣ���ݵ���������</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetMessage::CompressMessage(TAny* pMemory, TInt size, TInt* pLength){
   MO_ASSERT(pMemory);
   TByte* pPtr = (TByte*)pMemory;
   // ���ͷ����
   TInt netCapacity = _netHead.Capacity();
   TInt messageCapacity = _messageHead.Capacity();
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   TInt headCapacity = netCapacity + messageCapacity;
   // ���л�����
   TByte data[MO_NETMESSAGE_MAXLENGTH];
   TInt dataLength = 0;
   SerializeData(data, size - headCapacity, &dataLength);
   // ѹ������
   TInt compressLength = 0;
   TByte* pData = pPtr + headCapacity;
   RCompress::CompressRLE(pData, size - headCapacity, data, dataLength, &compressLength);
   // ����ͷ��Ϣ
   TSize capacity = headCapacity + compressLength;
   TNetHash hash = CalculateHash(messageSerial, messageTick, pData, compressLength);
   _netHead.SetLength((TNetLength)capacity);
   _netHead.SetHash(hash);
   // ���ô洢ͷ��Ϣ
   TNetHead netHead(_netHead);
   netHead.SetProtocol(ENetProtocol_Message);
   // ���л�����
   TInt offset = 0;
   offset += netHead.Serialize(pPtr);
   offset += _messageHead.Serialize(pPtr + offset);
   offset += compressLength;
   // �������л����С
   *pLength = offset;
   return ETrue;
}

//============================================================
// <T>���л���Ϣ���ݵ���������</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetMessage::Serialize(TAny* pMemory, TInt size, TInt* length){
   return SerializeMessage(pMemory, size, length);
}

//============================================================
// <T>�����л�����������Ϣ���ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param length �����С
//============================================================
TBool TNetMessage::Unserialize(TAnyC* pMemory, TInt size, TInt* length){
   return UnserializeMessage(pMemory, size, length);
}

//============================================================
// <T>��õ�ǰ�ڲ�״̬��Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetMessage::DumpMessage(TChar* pDump, TSize capacity){
   // ��ȡ������Ϣ
   TNetLength length = _netHead.Length();
   TUint16 protocol = _netHead.Protocol();
   TNetHash hash = _netHead.Hash();
   // ��ȡ��Ϣ��Ϣ
   TUint8 type = _messageHead.Type();
   TUint8 command = _messageHead.Command();
   TUint16 code = _messageHead.Code();
   TNetMessageInfo* pMessageInfo = MessageInfo();
   TUint16 sourceTerminal = ENetTerminal_Unknown;
   TUint16 targetTerminal = ENetTerminal_Unknown;
   if(NULL != pMessageInfo){
      sourceTerminal = (TUint16)pMessageInfo->SourceTerminal();
      targetTerminal = (TUint16)pMessageInfo->TargetTerminal();
   }
   TCharC* pSourceTerminal = REnumNetTerminal::ToString((ENetTerminal)sourceTerminal);
   TCharC* pTargetTerminal = REnumNetTerminal::ToString((ENetTerminal)targetTerminal);
   // ����������Ϣ
   TFsTrack dataTrack;
   TCharC* pDataTrack = RNetMessageFactory::DumpData(this, &dataTrack);
   // ������Ϣ
   TCharC* pName = RNetMessageFactory::CodeName(code);
   MO_LIB_STRING_FORMAT(pDump, capacity,
      TC("[ %s ]\n"
         "--------------------------------------------------------------------------------\n"
         "-- Net     : length=0x%04X(%d), protocol=%d, hash=0x%08X\n"
         "-- Message : code=(%02X:%04X), command=%d, source=%s(0x%04X), target=%s(0x%04X)\n"
         "--------------------------------------------------------------------------------\n"
         "%s"),
         pName,
         length, length, protocol, hash,
         type, code, (TUint8)command, pSourceTerminal, sourceTerminal, pTargetTerminal, targetTerminal,
         pDataTrack);
   return pDump;
}

//============================================================
// <T>�����Ϣ������������Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetMessage::DumpMessageMemory(TChar* pDump, TSize capacity){
   // ���л�����
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!SerializeMessage(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
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
TCharC* TNetMessage::Dump(TChar* pDump, TSize capacity){
   return DumpMessage(pDump, capacity);
}

MO_NAMESPACE_END
