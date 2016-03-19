#ifndef __MO_CR_NET_COLLECTION_H__
#define __MO_CR_NET_COLLECTION_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣ�������͡�</T>
//wenti 
// @history 100318 MAOCY ����
//============================================================
template <typename T, TInt S>
class TFsNetTypes : public TStackTypes<T, S>{
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Count(){
      return this->_length;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰ������</T>
   MO_INLINE TSize Capacity(){
      TSize capacity = sizeof(TUint16);
      capacity += sizeof(T) * this->_length;
      return capacity;
   }
   //------------------------------------------------------------
   // <T>���л��ڲ����ݵ���������</T>
   TInt Serialize(TAny* pMemory){
      TByte* pPtr = (TByte*)pMemory;
      *(TUint16*)pPtr = (TUint16)this->_length;
      TInt total = sizeof(T) * this->_length;
      MO_LIB_MEMORY_COPY(pPtr + sizeof(TUint16), total, this->_memory, total);
      return sizeof(TUint16) + total;
   }
   //------------------------------------------------------------
   // <T>�����л����������ڲ����ݡ�</T>
   TInt Unserialize(TAnyC* pMemory){
      TByteC* pPtr = (TByteC*)pMemory;
      // ��鳤��
      TInt length = *(TUint16*)pPtr;
      if(this->_length > S){
         MO_ERROR(TC("Unserialize net types not enough memory. (size=%d, length=%d)"), S, this->_length);
         return -1;
      }
      this->_length = length;
      // ��������
      TInt total = sizeof(T) * length;
      if(total > 0){
         MO_LIB_MEMORY_COPY(this->_memory, sizeof(T) * S, pPtr + sizeof(TUint16), total);
      }
      return sizeof(TUint16) + total;
   }
   //------------------------------------------------------------
   // <T>������ݵ��ַ�����</T>
   TBool Pack(MPack* pPack){
      MO_FATAL_UNSUPPORT();
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>����ַ������ڲ����ݡ�</T>
   TBool Unpack(MPack* pPack){
      MO_FATAL_UNSUPPORT();
      return EFalse;
   }
public:
   //------------------------------------------------------------
   // <T>�����ڲ����ݡ�</T>
   TCharC* Track(MString* pTrack){
      MO_ASSERT(pTrack);
      pTrack->AppendFormat(TC("[length=%d]"), this->_length);
      return pTrack->MemoryC();
   }
};

//============================================================
// <T>������Ϣ�ַ�����</T>
//
// @history 100902 MAOCY ����
//============================================================
template <TInt S>
class TFsNetBytes : public TFsNetTypes<TByte, S>{
public:
   //------------------------------------------------------------
   // <T>���������ַ�����</T>
   TFsNetBytes(){
   }
public:
   //------------------------------------------------------------
   // <T>�����ڲ����ݡ�</T>
   TCharC* Track(MString* pTrack, TInt level){
      MO_ASSERT(pTrack);
      TInt trackLength = MO_MIN(this->_length, 32);
      pTrack->AppendFormat("[length=%d] %s",
            this->_length,
            RByte::FormatDisplay(this->_memory, trackLength, (TChar*)TFsText(), TFsText::Size()));
      return pTrack->MemoryC();
   }
};

//============================================================
// <T>������Ϣ�ַ�����</T>
//
// @history 100902 MAOCY ����
//============================================================
template <TInt S>
class TFsNetString : public TFsNetTypes<TChar, S>{
public:
   //------------------------------------------------------------
   // <T>���������ַ�����</T>
   TFsNetString(){
      Set(NULL);
   }
   //------------------------------------------------------------
   // <T>���������ַ�����</T>
   TFsNetString(TCharC* pValue){
      Set(pValue);
   }
public:
   //------------------------------------------------------------
   MO_INLINE void operator=(TCharC* pValue){
      Set(pValue);
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰ�ݻ�������һ��β�����ַ���</T>
   MO_INLINE TSize Capacity(){
      TSize capacity = sizeof(TUint16) + 1;
      capacity += sizeof(TChar) * this->_length;
      return capacity;
   }
   //------------------------------------------------------------
   // <T>�Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(TCharC* pMemory, TInt length = -1){
      MO_ASSERT(pMemory);
      if(length <= 0){
         length = RString::Length(pMemory);
      }
      if(this->_length != length){
         return EFalse;
      }
      return RTypes<TCharC>::Equals((TCharC*)this->_memory, pMemory, length);
   }
   //------------------------------------------------------------
   // <T>������Ϣ���Լ��ڲ���</T>
   MO_INLINE void Assign(const TFsNetString<S>& value){
      Set((TCharC*)value._memory);
      this->_length = value._length;
   }
   // ------------------------------------------------------------
   // ׷��һ����ʽ�ַ���
   void AssignFormat(TCharC* pFormat, va_list& params){
      this->Clear();
#ifdef _MO_WINDOWS
#else
      TChar buffer[MO_FS_SPRINT_LENGTH];
      TInt length = vsnprintf(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
      buffer[length] = 0;
      Append(buffer);
#endif
   }
   //------------------------------------------------------------
   // <T>׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
   // <P>�������С��0�����Զ�����ָ������ݳ��ȡ�</P>
   void Append(TCharC* pValue, TInt length = -1){
      // ���ָ��
      if(NULL == pValue){
         return;
      }
      // ��ȡ����
      if(length <= 0){
         length = RTypes<TChar>::IndexOf(pValue, 0);
      }
      // ��鳤��
      if(this->_length + length >= S){
         MO_FATAL(TC("Append string length invalid. (length=%d, size=%d, value=%d:%s)"), this->_length, S, length, pValue);
         length = S - this->_length - 1;
      }
      // ��������
      if(length > 0){
         TChar* pMemory = (TChar*)this->_memory;
         MO_LIB_MEMORY_COPY(pMemory + this->_length, S - this->_length, pValue, sizeof(TChar) * length);
         this->_length += length;
         pMemory[this->_length] = 0;
      }
   }
   //------------------------------------------------------------
   // <T>׷��һ����ʽ���ַ���������β����</T>
   void AppendFormat(TCharC* pFormat, ...){
      // ��ʽ���ɱ�����ַ�����Ϣ
      va_list params;
      va_start(params, pFormat);
      // �����־��Ϣ
   #ifdef _MO_WINDOWS
      TInt length = MO_LIB_STRING_FORMAT_LENGTH(pFormat, params);
      MO_ASSERT_RANGE(this->_length + length + 1, 0, S);
      length = MO_LIB_STRING_FORMAT((TChar*)_memory + _length, length + 1, pFormat, params);
      this->_length += length;
   #else
      TChar buffer[MO_FS_SPRINT_LENGTH];
      TInt length = vsnprintf(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
      buffer[length] = 0;
      Append(buffer);
   #endif // _MO_WINDOWS
      va_end(params);
   }
   // ------------------------------------------------------------
   // ׷��һ����ʽ�ַ���
   void AppendFormat(TCharC* pFormat, va_list& params){
#ifdef _MO_WINDOWS
      TInt length = MO_LIB_STRING_FORMAT_LENGTH(pFormat, params);
      MO_ASSERT_RANGE(this->_length + length + 1, 0, S);
      length = MO_LIB_STRING_FORMAT((TChar*)_memory + _length, length + 1, pFormat, params);
      this->_length += length;
#else
      TChar buffer[MO_FS_SPRINT_LENGTH];
      TInt length = vsnprintf(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
      buffer[length] = 0;
      Append(buffer);
#endif // _MO_WINDOWS
   }
   //------------------------------------------------------------
   // <T>�����ڲ����ݡ�</T>
   MO_INLINE void Set(TCharC* pValue){
      TInt length = 0;
      if(NULL != pValue){
         length = RTypes<TChar>::IndexOf(pValue, 0);
         if(length >= S){
            MO_FATAL(TC("Set string length invalid. (size=%d, value=%d:%s)"), S, length, pValue);
            length = S - 1;
         }
         if(length > 0){
            MO_LIB_MEMORY_COPY(this->_memory, sizeof(TChar) * S, pValue, sizeof(TChar) * length);
         }
      }
      this->_length = length;
      this->_memory[this->_length] = 0;
   }
   //------------------------------------------------------------
   // <T>���л��ڲ����ݵ���������</T>
   // <P>�ౣ��һ����β���ַ���</P>
   MO_INLINE TInt Serialize(TAny* pMemory){
      TByte* pPtr = (TByte*)pMemory;
      *(TUint16*)pPtr = (TUint16)this->_length;
      TInt total = sizeof(TChar) * this->_length;
      MO_LIB_MEMORY_COPY(pPtr + sizeof(TUint16), total, this->_memory, total);
      return sizeof(TUint16) + total;
   }
   //------------------------------------------------------------
   // <T>�����л����������ڲ����ݡ�</T>
   MO_INLINE TInt Unserialize(TAnyC* pMemory){
      TByteC* pPtr = (TByteC*)pMemory;
      TInt length = *(TUint16*)pPtr;
      // ��鳤��
      if(length >= S){
         MO_ERROR(TC("Unserialize net string not enough memory. (size=%d, length=%d)"), S, length);
         return -1;
      }
      this->_length = length;
      // �����ڴ�����
      TInt total = sizeof(TChar) * length;
      if(total > 0){
         MO_LIB_MEMORY_COPY(this->_memory, sizeof(TChar) * S, pPtr + sizeof(TUint16), total);
      }
      this->_memory[length] = 0;
      return sizeof(TUint16) + total;
   }
   //------------------------------------------------------------
   // <T>����ڲ����ݵ��ⲿ��</T>
   MO_INLINE TCharC* ToDisplay(TChar* pValue, TInt capacity){
      MO_ASSERT(pValue);
      MO_ASSERT(capacity > this->_length + 1);
      TStringRefer refer(pValue, capacity);
      if(this->_length > 0){
         refer.AppendFormat(TC("%d:\"%s\""), this->_length, this->_memory);
      }else{
         refer.Append(TC("0:\"\""));
      }
      return pValue;
   }
   //------------------------------------------------------------
   // <T>����ڲ����ݵ��ⲿ��</T>
   MO_INLINE TCharC* ToString(TChar* pValue, TInt capacity){
      MO_ASSERT(pValue);
      MO_ASSERT(this->_length + 1 < capacity);
      memcpy(pValue, this->_memory, sizeof(TChar) * (this->_length + 1));
      pValue[this->_length] = 0;
      return pValue;
   }
};

//============================================================
// <T>������Ϣ��������</T>
//
// @history 100318 MAOCY ����
//============================================================
template <typename T, TInt S>
class TFsNetObjects : public TStackObjects<T, S>{
public:
   //------------------------------------------------------------
   // <T>��õ�ǰ�ݻ���</T>
   TSize Capacity(){
      TInt offset = sizeof(TUint16);
      T* pItems = (T*)this->_items;
      for(TInt n = 0; n < this->_count; n++){
         offset += pItems[n].Capacity();
      }
      return offset;
   }
   //------------------------------------------------------------
   // <T>���л��ڲ����ݵ���������</T>
   TInt Serialize(TAny* pMemory){
      TByte* pPtr = (TByte*)pMemory;
      // д�볤��
      *(TUint16*)pMemory = (TUint16)this->_count;
      TInt offset = sizeof(TUint16);
      // д�����ж���
      T* pItems = (T*)this->_items;
      for(TInt n = 0; n < this->_count; n++){
         offset += pItems[n].Serialize(pPtr + offset);
      }
      return offset;
   }
   //------------------------------------------------------------
   // <T>�����л����������ڲ����ݡ�</T>
   TInt Unserialize(TAnyC* pMemory){
      TByteC* pPtr = (TByteC*)pMemory;
      // ��ȡ����
      TInt count = *(TUint16*)pPtr;
      if(count > S){
         MO_FATAL("Unserialize net objects not enough memory. (size=%d, count=%d)", S, count);
         return -1;
      }
      this->_count = count;
      // ��ȡ����
      TInt offset = sizeof(TUint16);
      T* pItems = (T*)this->_items;
      // ����ڴ�
      MO_LIB_MEMORY_CLEAR(pItems, sizeof(T) * count);
      for(TInt n = 0; n < count; n++){
         TInt result = pItems[n].Unserialize(pPtr + offset);
         if(-1 == result){
            return result;
         }
         offset += result;
      }
      return offset;
   }
   //------------------------------------------------------------
   // <T>������ݵ��ַ�����</T>
   TBool Pack(MPack* pPack){
      MO_ASSERT(pPack);
      // д�볤��
      TBool result = pPack->WriteCollectionBegin(this->_count);
      // д�����ж���
      T* pItems = (T*)this->_items;
      if(result){
         for(TInt n = 0; n < this->_count; n++){
            pItems[n].Pack(pPack);
         }
         result = pPack->WriteCollectionEnd();
      }
      return result;
   }
   //------------------------------------------------------------
   // <T>����ַ������ڲ����ݡ�</T>
   TBool Unpack(MPack* pPack){
      MO_ASSERT(pPack);
      TInt count = 0;
      TBool result = pPack->ReadCollectionBegin(&count);
      if(result){
         // ��鳤��
         if(count > S){
            MO_FATAL("Unserialize net objects not enough memory. (size=%d, count=%d)", S, count);
            return EFalse;
         }
         this->_count = count;
         // ����ڴ�
         T* pItems = (T*)this->_items;
         MO_LIB_MEMORY_CLEAR(pItems, sizeof(T) * count);
         // ��ȡ���ж���
         for(TInt n = 0; n < count; n++){
            TBool result = pItems[n].Unpack(pPack);
            if(!result){
               return result;
            }
         }
         result = pPack->ReadCollectionEnd();
      }
      return result;
   }
public:
   //------------------------------------------------------------
   // <T>�����ڲ����ݡ�</T>
   TCharC* Track(TChar* pTrack, TSize length){
      T* pItems = (T*)this->_items;
      TStringRefer track(pTrack, length);
      track.AppendFormat("[count=%d]", this->_count);
      for(TInt n=0; n<this->_count; n++){
         TChar buffer[MO_FS_TRACK_LENGTH];
         pItems[n].Track(buffer, MO_FS_TRACK_LENGTH);
         track.AppendFormat("\n   - %s", buffer);
      }
      return pTrack;
   }
};

MO_NAMESPACE_END

#endif // __MO_CR_NET_COLLECTION_H__
