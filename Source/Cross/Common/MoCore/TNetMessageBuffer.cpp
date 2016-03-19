#include "MoCrNetMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣ���塣</T>
//
// @return ��Ϣ����
//============================================================
TNetMessageBuffer::TNetMessageBuffer(){
   _pData = _buffer;
}

//============================================================
// <T>������Ϣ���塣</T>
//
// @return ��Ϣ����
//============================================================
TNetMessageBuffer::TNetMessageBuffer(TAnyC* pMemory){
   Restore(pMemory);
}

//============================================================
void TNetMessageBuffer::AssignData(TByteC* pData, TInt length){
   MO_ASSERT(pData);
   if(length > 0){
      memcpy(_buffer, pData, length);
   }
   _dataLength = length;
}

//============================================================
void TNetMessageBuffer::Update(){
   TInt capacity = Capacity();
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   TNetHash hash = CalculateHash(messageSerial, messageTick, _pData, _dataLength);
   _netHead.SetLength((TNetLength)capacity);
   _netHead.SetHash(hash);
}

//============================================================
// <T>���л��ڲ����ݵ���������</T>
//
// @param pMessage ��Ϣ����
//============================================================
TBool TNetMessageBuffer::Serialize(TAny* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByte* pPtr = (TByte*)pMemory;
   // ���ͷ����
   TInt netCapacity = _netHead.Capacity();
   TInt messageCapacity = _messageHead.Capacity();
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   TInt headCapacity = netCapacity + messageCapacity;
   TSize capacity = headCapacity + _dataLength;
   // ����ͷ��Ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, _pData, _dataLength);
   _netHead.SetLength((TNetLength)capacity);
   _netHead.SetHash(hash);
   // ����ͷ��Ϣ
   _netHead.Serialize(pPtr);
   _messageHead.Serialize(pPtr + headCapacity);
   // ���л�����
   if(_dataLength > 0){
      memcpy(pPtr + headCapacity, _pData, _dataLength);
   }
   // �������л����С
   *length = capacity;
   return ETrue;
}

//============================================================
// <T>�����л����������ڲ����ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݳ���
// @param [out] length ��ȡ����
//============================================================
TBool TNetMessageBuffer::Unserialize(TAnyC* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByteC* pPtr = (TByteC*)pMemory;
   // �����л�ͷ����
   TInt offset = 0;
   offset += _netHead.Unserialize(pPtr);
   offset += _messageHead.Unserialize(pPtr + offset);
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   // ��ȡ����
   TNetLength netLength = _netHead.Length();
   TByteC* pData = pPtr + offset;
   TInt dataLength = netLength - offset;
   // ����ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, pData, dataLength);
   if(_netHead.Hash() != hash){
      MO_WARN(TC("Unserialize message invalid hash. (head_hash=0x%08X, data_hash=0x%08X)"),
            _netHead.Hash(), hash);
      return EFalse;
   }
   // ��������
   if(dataLength > 0){
      memcpy(_buffer, pData, dataLength);
   }
   _dataLength = dataLength;
   *length = netLength;
   return ETrue;
}

//============================================================
// <T>�����л����������ڲ����ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݳ���
// @param [out] length ��ȡ����
//============================================================
TBool TNetMessageBuffer::UnserializeMask(TAnyC* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByteC* pPtr = (TByteC*)pMemory;
   // �����л�ͷ����
   TInt offset = 0;
   offset += _netHead.Unserialize(pPtr);
   TNetLength netLength = _netHead.Length();
   TNetHash netHash = _netHead.Hash();
   offset += _messageHead.Unserialize(pPtr + offset);
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   // ��ȡ����
   TByteC* pData = pPtr + offset;
   TInt dataLength = netLength - offset;
   // ��ԭ����
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   MaskData(buffer, MO_NETMESSAGE_MAXLENGTH, pData, dataLength, netHash);
   //TChar dump[MO_FS_DUMP_LENGTH];
   //MO_ERROR("Receive message data failure.\n%s",
   //      RByte::Dump(buffer, dataLength, dump, MO_FS_DUMP_LENGTH));
   // ����ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, buffer, dataLength);
   if(netHash != hash){
      MO_WARN(TC("Unserialize message invalid hash. (head_hash=0x%08X, data_hash=0x%08X)"), netHash, hash);
      return EFalse;
   }
   // ��������
   if(dataLength > 0){
      memcpy(_buffer, buffer, dataLength);
   }
   _dataLength = dataLength;
   *length = netLength;
   return ETrue;
}

//============================================================
// <T>�����л����������ڲ����ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݳ���
// @param [out] length ��ȡ����
//============================================================
TBool TNetMessageBuffer::UnserializeUncheck(TAnyC* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByteC* pPtr = (TByteC*)pMemory;
   // �����л�ͷ����
   TInt offset = 0;
   offset += _netHead.Unserialize(pPtr);
   offset += _messageHead.Unserialize(pPtr + offset);
   // ��ȡ����
   TNetLength netLength = _netHead.Length();
   TByteC* pData = pPtr + offset;
   TInt dataLength = netLength - offset;
   // ��������
   if(dataLength > 0){
      memcpy(_buffer, pData, dataLength);
   }
   _dataLength = dataLength;
   *length = netLength;
   return ETrue;
}

//============================================================
// <T>ѹ���ڲ����ݵ���������</T>
//
// @param pMemory ����ָ��
// @param size ���ݳ���
// @param [out] length ��ȡ����
//============================================================
TBool TNetMessageBuffer::Compress(TAny* pMemory, TInt size, TInt* pLength){
   MO_ASSERT(pMemory);
   TByte* pPtr = (TByte*)pMemory;
   // ���ͷ����
   TInt netCapacity = _netHead.Capacity();
   TInt messageCapacity = _messageHead.Capacity();
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   TInt headCapacity = netCapacity + messageCapacity;
   TSize capacity = headCapacity + _dataLength;
   // ����ͷ��Ϣ
   TNetHash hash = CalculateHash(messageSerial, messageTick, _pData, _dataLength);
   _netHead.SetLength((TNetLength)capacity);
   _netHead.SetHash(hash);
   // ����ͷ��Ϣ
   _netHead.Serialize(pPtr);
   _messageHead.Serialize(pPtr + headCapacity);
   // ѹ������
   TInt length = 0;
   if(!RCompress::CompressRLE(pPtr + headCapacity, size, _pData, _dataLength, &length)){
      return EFalse;
   }
   // �������л����С
   *pLength = headCapacity + length;
   return ETrue;
}

//============================================================
// <T>��ѹ�����������ڲ����ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݳ���
// @param [out] length ��ȡ����
//============================================================
TBool TNetMessageBuffer::Uncompress(TAnyC* pMemory, TInt size, TInt* pLength, TBool masked, TBool checked){
   MO_ASSERT(pMemory);
   TByteC* pPtr = (TByteC*)pMemory;
   // �����л�ͷ����
   TInt offset = 0;
   offset += _netHead.Unserialize(pPtr);
   offset += _messageHead.Unserialize(pPtr + offset);
   TNetHash netHash = _netHead.Hash();
   TBool compressed = _netHead.SignCompress();
   TNetSerial messageSerial = _messageHead.Serial();
   TNetTick messageTick = _messageHead.Tick();
   // ��ȡ����
   TNetLength netLength = _netHead.Length();
   TByteC* pData = pPtr + offset;
   TInt dataLength = netLength - offset;
   // ������ݳ���
   if((dataLength < 0) || (dataLength > MO_NETMESSAGE_MAXLENGTH)){
      return EFalse;
   }
   // ����ѹ��
   if(compressed){
      // ��ѹ������
      TInt length = 0;
      if(!RCompress::Inflate(_buffer, MO_NETMESSAGE_MAXLENGTH, pData, dataLength, &length)){
         MO_WARN(TC("Inflate message failure. (data_ptr=0x%08X, data_length=0x%08X)"), pData, dataLength);
         return EFalse;
      }
      _dataLength = length;
   }else{
      MO_LIB_MEMORY_COPY(_buffer, MO_NETMESSAGE_MAXLENGTH, pData, dataLength);
      _dataLength = dataLength;
   }
   // ��ԭ����
   if(masked){
      MaskData(_buffer, MO_NETMESSAGE_MAXLENGTH, _buffer, _dataLength, netHash);
   }
   // ����ϣ
   if(checked){
      TNetHash hash = CalculateHash(messageSerial, messageTick, _buffer, _dataLength);
      if(netHash != hash){
         MO_WARN(TC("Unserialize message invalid hash. (head_hash=0x%08X, data_hash=0x%08X)"), netHash, hash);
         return EFalse;
      }
   }
   *pLength = _dataLength;
   return ETrue;
}

//============================================================
TCharC* TNetMessageBuffer::Dump(TChar* pDump, TSize capacity){
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

MO_NAMESPACE_END
