#include <MoCmSystem.h>
#include "MoCrNetMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������������ͷ��Ϣ��</T>
//============================================================
TNetData::TNetData(){
   _netHead.SetProtocol(ENetProtocol_Data);
   MO_CLEAR(_pData);
   _dataLength = 0;
}

//============================================================
// <T>������������ͷ��Ϣ��</T>
//============================================================
TNetData::~TNetData(){
}

//============================================================
// <T>�������ݲ��ֵĹ�ϣֵ��</T>
//
// @param pMessage ��Ϣ����
//============================================================
TNetHash TNetData::CalculateHash(TNetSerial serial, TNetTick date, TByteC* pMemory, TInt length){
   TInt32 hash = serial;
   // ����ڴ�
   if(NULL != pMemory){
      if(length > 0){
         // �����ϣ
         for(TInt n = 0; n < length; n++){
            hash = (31 * hash) + pMemory[n];
         }
      }
   }
   TNetHash result = (TNetHash)hash;
   result = result ^ date;
   return result;
}

//============================================================
// <T>�������ݲ��ֵ��ڵ���</T>
//
// @param pDate ��������
// @param capacity ����
// @param pInput ����
// @param length ����
// @param hash ��ϣ
//============================================================
TBool TNetData::MaskData(TByte* pDate, TInt capacity, TByteC* pInput, TInt length, TNetHash hash){
   // ��������
   TByte v1 = (hash >>  0) & 0xFF;
   TByte v2 = (hash >>  8) & 0xFF;
   TByte v3 = (hash >> 16) & 0xFF;
   TByte v4 = (hash >> 24) & 0xFF;
   // ���ֽ��ڸ�
   for(TInt n = 0; n < length; n++){
      // ѡ������
      TByte v = 0;
      switch(n & 0x03){
         case 0:
            v = v1;
            break;
         case 1:
            v = v3;
            break;
         case 2:
            v = v2;
            break;
         case 3:
            v = v4;
            break;
      }
      // �ڸ��ֽ�
      pDate[n] = v ^ pInput[n];
   }
   return ETrue;
}

//============================================================
// <T>���������</T>
//
// @return ����
//============================================================
TInt TNetData::Capacity(){
   TSize capacity = _netHead.Capacity();
   capacity += _dataLength;
   return capacity;
}

//============================================================
// <T>����ָ����Ϣ�ڵ��������ݡ�</T>
//
// @param pMessage ��Ϣ����
//============================================================
TBool TNetData::Assign(TNetData* pData){
   MO_ASSERT(pData);
   // ����ͷ��Ϣ
   _netHead.Assign(pData->NetHead());
   // ��������
   _pData = pData->DataC();
   _dataLength = pData->DataLength();
   return ETrue;
}

//============================================================
TBool TNetData::SerializeData(TAny* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByte* pPtr = (TByte*)pMemory;
   if((NULL != _pData) && (_dataLength > 0)){
      memcpy(pPtr, _pData, _dataLength);
   }
   *length = _dataLength;
   return ETrue;
}

//============================================================
TBool TNetData::UnserializeData(TAnyC* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   _pData = (TByte*)pMemory;
   _dataLength = size;
   *length = _dataLength;
   return ETrue;
}

//============================================================
// <T>���л��ڲ����ݵ���������</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param [out] length ���ݳ���
// @return ������
//============================================================
TBool TNetData::Serialize(TAny* pMemory, TInt size, TInt* length){
   TByte* pPtr = (TByte*)pMemory;
   TInt capacity = Capacity();
   MO_ASSERT(capacity <= size);
   // ���л�ͷ��Ϣ
   _netHead.SetLength((TNetLength)capacity);
   TInt offset = _netHead.Serialize(pPtr);
   // ���л�����
   SerializeData(pPtr + offset, size - offset, &_dataLength);
   *length = capacity;
   return ETrue;
}

//============================================================
// <T>�����л����������ڲ����ݡ�</T>
//
// @param pMemory ����ָ��
// @param size ���ݴ�С
// @param [out] length ���ݳ���
// @return ������
//============================================================
TBool TNetData::Unserialize(TAnyC* pMemory, TInt size, TInt* length){
   MO_ASSERT(pMemory);
   TByteC* pPtr = (TByteC*)pMemory;
   // ����ͷ��Ϣ
   _netHead.Unserialize(pPtr);
   TInt headCapacity = _netHead.Capacity();
   TInt capacity = _netHead.Length();
   MO_ASSERT(capacity <= size);
   // ��������
   UnserializeData(pPtr + headCapacity, capacity - headCapacity, &_dataLength);
   *length = capacity;
   return ETrue;
}

//============================================================
TInt TNetData::Store(TAny* pMemory){
   TInt length = 0;
   Serialize(pMemory, MO_NETMESSAGE_MAXLENGTH, &length);
   return length;
}

//============================================================
TInt TNetData::Restore(TAnyC* pMemory){
   TInt length = 0;
   Unserialize(pMemory, MO_NETMESSAGE_MAXLENGTH, &length);
   return length;
}

//============================================================
TCharC* TNetData::DumpData(TChar* pDump, TSize capacity){
   return pDump;
}

//============================================================
// <T>����������ݿ������������Ϣ��</T>
//
// @param pDump �����Ϣָ��
// @param capacity �����Ϣ��С
// @return ������
//============================================================
TCharC* TNetData::DumpMemory(TChar* pDump, TSize capacity){
   // ���л�����
   TInt length;
   TByte buffer[MO_NETMESSAGE_MAXLENGTH];
   if(!Serialize(buffer, MO_NETMESSAGE_MAXLENGTH, &length)){
      return pDump;
   }
   // ���ɵ�����Ϣ
   TInt size = MO_LIB_MIN(length, MO_NETMESSAGE_BYTEDUMP_MAXLENGTH);
   RByte::Dump(buffer, size, pDump, capacity);
   return pDump;
}

//============================================================
TCharC* TNetData::Dump(TChar* pDump, TSize capacity){
   // ��ȡ������Ϣ
   TNetLength length = _netHead.Length();
   TUint16 protocol = _netHead.Protocol();
   TNetHash hash = _netHead.Hash();
   // ����������Ϣ
   TFsTrack dataTrack;
   DumpData(dataTrack.Memory(), dataTrack.Size());
   // ������Ϣ
   MO_LIB_STRING_FORMAT(pDump, capacity,
      TC("Net     : length=0x%04X(%d), protocol=%d, hash=0x%08X\n"
         "--------------------------------------------------------------------------------\n"
         "%s"),
         length, length, protocol, hash,
         (TCharC*)dataTrack);
   return pDump;
}

MO_NAMESPACE_END
