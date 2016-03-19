//============================================================
// <T>������Ϣ���塣</T>
// <P>1 - ���ݻ�����</P>
// <P>SNetPackage���������ݰ�</P>
// <P>TNetTypes�������������ͣ������͵ļ��ϡ�</P>
// <P>TNetObjects��������󼯺ϣ�ÿһ������Ҫ�����л��ͷ����л���</P>
// <P>2 - ���������</P>
// <P>TNetData���������ݡ�</P>
// <P> - TNetHead����������ͷ��Ϣ��</P>
// <P>   - SNetHead����������ͷ���ݽṹ����</P>
// <P> - MemoryC��Я�����ݿ顣</P>
// <P>TNetMessage��������Ϣ����һ��ͷ��Ϣ��һ����Ϣ�幹�ɡ�</P>
// <P> - TNetMessageHead����Ϣͷ��Ϣ��</P>
// <P>   - SNetMessageHead����Ϣͷ���ݽṹ����</P>
// <P> - MemoryC��Я����Ϣ�塣</P>
// <P>TNetRouter����Ϣ·�ɣ�������Ϣ��Խ���������͡�</P>
// <P> - TNetRouterHead����Ϣ·��ͷ��Ϣ��</P>
// <P>   - SNetRouterHead����Ϣ·��ͷ���ݽṹ����</P>
// <P> - MemoryC��Я����Ϣ�壬��һ��TNetMessage����������Լ���ͷ���塣</P>
// <P>TNetTransfer����Ϣ���䣬������Ϣ��Խ���������̴��͡�</P>
// <P> - TNetTransferHead����Ϣ����ͷ��Ϣ��</P>
// <P>   - SNetTransferHead����Ϣ����ͷ���ݽṹ����</P>
// <P> - MemoryC��Я����Ϣ�壬��һ��TNetMessage����������Լ���ͷ���塣</P>
//
// @history 100318 MAOCY ����
//============================================================
#ifndef __MO_CR_NET_MESSAGE_H__
#define __MO_CR_NET_MESSAGE_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_CONSTANT_H__
#include "MoCrConstant.h"
#endif // __MO_CR_CONSTANT_H__

#ifndef __MO_CR_NET_SOCKET_H__
#include "MoCrNetSocket.h"
#endif // __MO_CR_NET_SOCKET_H__

#ifndef __MO_CR_NET_COLLECTION_H__
#include "MoCrNetCollection.h"
#endif // __MO_CR_NET_COLLECTION_H__

//============================================================
/// @define ��Ϣ����
#define MO_NET_SIGN_COMPRESS             0x0001
#define MO_NET_SIGN_MASK                 0x0002
#define MO_NETMESSAGE_COUNT              0x10000
#define MO_NETMESSAGE_COMPRESS_LIMIT     64
#define MO_NETMESSAGE_MAXLENGTH          1024*512
#define MO_NETMESSAGE_MAXTARGET          256
#define MO_NETMESSAGE_BYTEDUMP_MAXLENGTH 1024
#define MO_NETROUTER_MAXTARGET           16
#define MO_NETROUTER_FLAG_INVALID        0x0001
#define MO_NETROUTER_FLAG_DISCONNECT     0x0002
#define MO_FS_SOCKETTARGET_MAXLEN        64

MO_NAMESPACE_BEGIN

//============================================================
typedef TUint32 TNetLength;
typedef TUint32 TNetHash;
typedef TUint32 TNetGenerator;
typedef TUint32 TNetSessionId;
typedef TUint16 TNetPort;
typedef TUint16 TNetVersion;

//============================================================
// <T>����Ŀ�꣨64λ����</T>
// ��[32Bit]��Ŀ���������Ϣ
//  - Flag      [ 8Bit]  = 256   ��־λ
//  - Type      [ 8Bit]  = 256   ����(��1��ʼ)
//  - Groupid   [ 8Bit]  = 256   Ŀ���������(��0��ʼ)
//  - ServerId  [ 8Bit]  = 256   Ŀ����������(��0��ʼ)
// ��[32Bit]�������Ϣ
//  - NetIndex  [ 16Bit] = 65535 Ŀ��������(��0��ʼ)
//  - NetSerial [ 16Bit] = 65535 Ŀ��������(��0��ʼ)
//============================================================
#pragma pack(2)
struct MO_CR_DECLARE SNetSocketTarget{
public:
   union{
      TUint32 handle;
      struct{
         TUint16 index;
         TUint16 serial;
      } items;
   } Data;
public:
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   SNetSocketTarget(){
      Data.handle = 0;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(SNetSocketTarget& value){
      return Equals(value);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ񲻵ȡ�</T>
   MO_INLINE TBool operator!=(SNetSocketTarget& value){
      return !Equals(value);
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void operator=(TUint32 handle){
      Data.handle = handle;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void operator=(const SNetSocketTarget& target){
      Data.handle = target.Data.handle;
   }
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TUint16 Index() const{
      return Data.items.index;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void SetIndex(TUint16 index){
      Data.items.index = index;
   }
   //------------------------------------------------------------
   // <T>������С�</T>
   MO_INLINE TUint16 Serial() const{
      return Data.items.serial;
   }
   //------------------------------------------------------------
   // <T>�������С�</T>
   MO_INLINE void SetSerial(TUint16 serial){
      Data.items.serial = serial;
   }
public:
   //------------------------------------------------------------
   // <T>��þ����</T>
   MO_INLINE TUint32 Get(){
      return Data.handle;
   }
   //------------------------------------------------------------
   // <T>���þ����</T>
   MO_INLINE void Set(TUint32 handle){
      Data.handle = handle;
   }
   //------------------------------------------------------------
   // <T>�������������С�</T>
   MO_INLINE void Set(TUint16 index, TUint16 serial){
      Data.items.index = index;
      Data.items.serial = serial;
   }
   //------------------------------------------------------------
   // <T>����Ŀ�ꡣ</T>
   MO_INLINE void Set(SNetSocketTarget target){
      Data.handle = target.Data.handle;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(SNetSocketTarget& value){
      return (Data.handle == value.Data.handle);
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      Data.handle = 0;
   }
public:
   //------------------------------------------------------------
   // <T>�����ʾ�ַ�����</T>
   TCharC* ToDisplay(TChar* pValue, TSize capacity){
      TStringRefer refer(pValue, capacity);
      refer.AssignFormat(TC("%04X:%04X"), Data.items.index, Data.items.serial);
      return pValue;
   }
   //------------------------------------------------------------
   // <T>��ø����ַ�����</T>
   TCharC* Track(TChar* pTrack, TSize capacity, TInt level){
      TStringRefer track(pTrack, capacity);
      track.AppendFormat(TC("%d:%d"), Data.items.index, Data.items.serial);
      return pTrack;
   }
};
#pragma pack()

//============================================================
// <T>����Ŀ���ַ�����</T>
//============================================================
class MO_CR_DECLARE TFsNetSocketTarget : public TFixString<MO_FS_SOCKETTARGET_MAXLEN>{
protected:
   SNetSocketTarget _value;
public:
   TFsNetSocketTarget();
   TFsNetSocketTarget(const SNetSocketTarget& value);
public:
   void operator=(const TFsNetSocketTarget& value);
   void operator=(TCharC* pValue);
   void operator=(const SNetSocketTarget& value);
   void operator=(const TStringPtrC& value);
public:
   SNetSocketTarget Value() const;
   void SetValue(SNetSocketTarget value);
   TCharC* Format();
};

//============================================================
// <T>����Ŀ�꣨64λ����</T>
// ��[32Bit]��Ŀ����������
//  - ServerHandle    [32Bit] ���������
//     - GroupId      [16Bit] = 0-65535 ��������� (��1��ʼ,0Ϊ��Ч)
//     - Server       [16Bit]
//        - Type      [ 8Bit] = 0-255   ���������� (��0��ʼ)
//        - Id        [ 8Bit] = 0-255   ��������� (��1��ʼ,0ΪΨһ)
// ��[32Bit]��Ŀ�������
//  - ObjectHandle    [32Bit] = ��������ͬʱ��ΪSessionId
//     - Index        [16Bit] = 0-65535 ����λ�� (��0��ʼ����Socket������λ������)
//     - Serial       [16Bit] = 0-65535 ����(Socket��֤ʹ�ã�ȷ��Ϊͬһ���ͻ���)
//============================================================
typedef TUint64 TNetTargetHandle;
#pragma pack(2)
struct MO_CR_DECLARE SNetTarget{
public:
   //------------------------------------------------------------
   // ���ݶ���
   union{
      TUint64 Handle;
      struct{
         TUint32 ServerHandle;
         TUint32 ObjectHandle;
      } Handles;
      struct{
         TUint16 GroupId;
         TUint8  ServerType;
         TUint8  ServerId;
         TUint16 ObjectIndex;
         TUint16 ObjectSerial;
      } Items;
   } Data;
public:
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   SNetTarget(){
      Data.Handle = 0;
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   SNetTarget(const SNetTarget& target){
      Data.Handle = target.Data.Handle;
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   SNetTarget(TNetTargetHandle handle){
      Data.Handle = handle;
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   SNetTarget(TUint16 groupId, TUint8 serverType, TUint8 serverId){
      Data.Items.GroupId = groupId;
      Data.Items.ServerType = serverType;
      Data.Items.ServerId = serverId;
      Data.Handles.ObjectHandle = 0;
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   SNetTarget(TUint8 groupId, TUint8 serverType, TUint8 serverId, TUint16 objectHandle){
      Data.Items.GroupId = groupId;
      Data.Items.ServerType = serverType;
      Data.Items.ServerId = serverId;
      Data.Handles.ObjectHandle = objectHandle;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SNetTarget& value){
      return Equals(value);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ񲻵ȡ�</T>
   MO_INLINE TBool operator!=(const SNetTarget& value){
      return !Equals(value);
   }
   //------------------------------------------------------------
   // <T>��ֵ����</T>
   MO_INLINE void operator=(const SNetTarget& value){
      Data.Handle = value.Data.Handle;
   }
public:
   //------------------------------------------------------------
   // <T>��þ����</T>
   MO_INLINE TNetTargetHandle Handle() const{
      return Data.Handle;
   }
   //------------------------------------------------------------
   // <T>���þ����</T>
   MO_INLINE void SetHandle(TNetTargetHandle handle){
      Data.Handle = handle;
   }
   //------------------------------------------------------------
   // <T>��÷����������</T>
   MO_INLINE TUint32 ServerHandle() const{
      return Data.Handles.ServerHandle;
   }
   //------------------------------------------------------------
   // <T>���÷����������</T>
   MO_INLINE void SetServerHandle(TUint32 handle){
      Data.Handles.ServerHandle = handle;
   }
   //------------------------------------------------------------
   // <T>��ö�������</T>
   MO_INLINE TUint32 ObjectHandle() const{
      return Data.Handles.ObjectHandle;
   }
   //------------------------------------------------------------
   // <T>���ö�������</T>
   MO_INLINE void SetObjectHandle(TUint32 handle){
      Data.Handles.ObjectHandle = handle;
   }
   //------------------------------------------------------------
   // <T>��÷�������</T>
   MO_INLINE TUint16 GroupId() const{
      return Data.Items.GroupId;
   }
   //------------------------------------------------------------
   // <T>���÷�������</T>
   MO_INLINE void SetGroupId(TUint16 groupId){
      Data.Items.GroupId = groupId;
   }
   //------------------------------------------------------------
   // <T>��÷��������͡�</T>
   MO_INLINE TUint8 ServerType() const{
      return Data.Items.ServerType;
   }
   //------------------------------------------------------------
   // <T>���÷��������͡�</T>
   MO_INLINE void SetServerType(TUint8 type){
      Data.Items.ServerType = type;
   }
   //------------------------------------------------------------
   // <T>��÷�������š�</T>
   MO_INLINE TUint8 ServerId() const{
      return Data.Items.ServerId;
   }
   //------------------------------------------------------------
   // <T>���÷�������š�</T>
   MO_INLINE void SetServerId(TUint8 serverId){
      Data.Items.ServerId = serverId;
   }
   //------------------------------------------------------------
   // <T>��ö���������</T>
   MO_INLINE TUint16 ObjectIndex() const{
      return Data.Items.ObjectIndex;
   }
   //------------------------------------------------------------
   // <T>���ö���������</T>
   MO_INLINE void SetObjectIndex(TUint16 index){
      Data.Items.ObjectIndex = index;
   }
   //------------------------------------------------------------
   // <T>��ö���������</T>
   MO_INLINE TUint8 ObjectSerial() const{
      return (TUint8)Data.Items.ObjectSerial;
   }
   //------------------------------------------------------------
   // <T>���ö���������</T>
   MO_INLINE void SetObjectSerial(TUint16 serial){
      Data.Items.ObjectSerial = serial;
   }
public:
   //------------------------------------------------------------
   // <T>��þ����</T>
   MO_INLINE TNetTargetHandle Get(){
      return Data.Handle;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TNetTargetHandle handle){
      Data.Handle = handle;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(const SNetTarget& target){
      Data.Handle = target.Data.Handle;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TUint32 serverHandle, TUint32 objectHandle){
      Data.Handles.ServerHandle = serverHandle;
      Data.Handles.ObjectHandle = objectHandle;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TUint16 groupId, TUint8 serverType, TUint8 serverId, TUint32 objectHandle){
      Data.Items.GroupId = groupId;
      Data.Items.ServerType = serverType;
      Data.Items.ServerId = serverId;
      Data.Handles.ObjectHandle = objectHandle;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TUint16 groupId, TUint8 serverType, TUint8 serverId, TUint16 objectIndex, TUint16 objectSerial){
      Data.Items.GroupId = groupId;
      Data.Items.ServerType = serverType;
      Data.Items.ServerId = serverId;
      Data.Items.ObjectIndex = objectIndex;
      Data.Items.ObjectSerial = objectSerial;
   }
   //------------------------------------------------------------
   // <T>���÷���</T>
   MO_INLINE void SetServer(SNetTarget& target){
      Data.Handles.ServerHandle = target.Data.Handles.ServerHandle;
      Data.Handles.ObjectHandle = 0;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(const SNetTarget& value){
      return (Data.Handle == value.Data.Handle);
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      Data.Handle = 0;
   }
public:
   //------------------------------------------------------------
   // <T>��ʾ���ݡ�</T>
   TCharC* ToDisplay(TChar* pValue, TSize capacity){
      TStringRefer refer(pValue, capacity);
      refer.AppendFormat(TC("(%d)-(%d,%d)-(%d,%d)"),
            Data.Items.GroupId, Data.Items.ServerType, Data.Items.ServerId,
            Data.Items.ObjectIndex, Data.Items.ObjectSerial);
      return pValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   TCharC* Track(TChar* pTrack, TSize capacity){
      TStringRefer track(pTrack, capacity);
      track.AppendFormat(TC("(%d)-(%d,%d)-(%d,%d)"),
            Data.Items.GroupId, Data.Items.ServerType, Data.Items.ServerId,
            Data.Items.ObjectIndex, Data.Items.ObjectSerial);
      return pTrack;
   }
};
#pragma pack()

//============================================================
// <T>����Ŀ�꼯��</T>
//
// @history 100318 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetTargets{
protected:
   TUint16 _count;
   TByte _targets[sizeof(SNetTarget) * MO_NETMESSAGE_MAXTARGET];
public:
   //------------------------------------------------------------
   // <T>��������Ŀ�꼯�ϡ�</T>
   TNetTargets(){
      _count = 0;
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�꼯�ϡ�</T>
   TNetTargets(const TNetTargets& targets){
      Assign(targets);
   }
public:
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE const SNetTarget& operator[](TInt index) const{
      MO_ASSERT_RANGE(index, 0, MO_NETMESSAGE_MAXTARGET);
      SNetTarget* pTargets = (SNetTarget*)_targets;
      return pTargets[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE SNetTarget& operator[](TInt index){
      MO_ASSERT_RANGE(index, 0, MO_NETMESSAGE_MAXTARGET);
      SNetTarget* pTargets = (SNetTarget*)_targets;
      return pTargets[index];
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>�����Ƿ�Ϊ����</T>
   MO_INLINE TBool IsFull(){
      return (MO_NETMESSAGE_MAXTARGET == _count);
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>���Ŀ��ָ�롣</T>
   MO_INLINE SNetTarget* Targets(){
      return (SNetTarget*)_targets;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰ�ݻ���</T>
   MO_INLINE TSize Capacity(){
      return sizeof(TUint16) + sizeof(SNetTarget) * _count;
   }
   //------------------------------------------------------------
   // <T>���õ���Ŀ�ꡣ</T>
   MO_INLINE void Assign(const TNetTargets& targets){
      _count = targets._count;
      MO_LIB_MEMORY_COPY(_targets, sizeof(SNetTarget) * MO_NETMESSAGE_MAXTARGET, targets._targets, sizeof(SNetTarget) * _count);
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE SNetTarget& Get(TInt index){
      MO_ASSERT_RANGE(index, 0, MO_NETMESSAGE_MAXTARGET);
      SNetTarget* pTargets = (SNetTarget*)_targets;
      return pTargets[index];
   }
   //------------------------------------------------------------
   // <T>���õ���Ŀ�ꡣ</T>
   MO_INLINE void Set(const SNetTarget& target){
      SNetTarget* pTargets = (SNetTarget*)_targets;
      pTargets[0] = target;
      _count = 1;
   }
   //------------------------------------------------------------
   // <T>����Ŀ�ꡣ</T>
   MO_INLINE void Push(const SNetTarget& target){
      SNetTarget* pTargets = (SNetTarget*)_targets;
      pTargets[_count++] = target;
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE void Clear(){
      _count = 0;
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ���ָ�������������</T>
   TBool ContainsServerHandle(TUint32 ServerHandle){
      SNetTarget* pTargets = (SNetTarget*)_targets;
      for(TInt n = 0; n<_count; n++){
         if(pTargets[n].Data.Handles.ServerHandle == ServerHandle){
            return ETrue;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>��ȡȫ��Ψһ����</T>
   void FetchServers(TNetTargets& servers){
      SNetTarget* pTargets = (SNetTarget*)_targets;
      for(TInt n = 0; n < _count; n++){
         SNetTarget& target = pTargets[n];
         TUint32 serverHandle = target.ServerHandle();
         if(!servers.ContainsServerHandle(serverHandle)){
            servers.Push(target);
         }
      }
   }
   //------------------------------------------------------------
   // <T>��ȡȫ��ָ������������Ŀ���б�</T>
   void FetchServerTargets(TNetTargets& servers, TUint32 serverHandle){
      SNetTarget* pTargets = (SNetTarget*)_targets;
      for(TInt n = 0; n < _count; n++){
         SNetTarget& target = pTargets[n];
         if(target.ServerHandle() == serverHandle){
            servers.Push(target);
         }
      }
   }
public:
   //------------------------------------------------------------
   // <T>���л��ڲ����ݵ���������</T>
   TInt Serialize(TAny* pMemory){
      TByte* pPtr = (TByte*)pMemory;
      // ��������
      *(TUint16*)pPtr = _count;
      // ��������
      TInt total = 0;
      if(_count > 0){
         total = sizeof(SNetTarget) * _count;
         MO_LIB_MEMORY_COPY(pPtr + sizeof(TUint16), total, _targets, total);
      }
      return sizeof(TUint16) + total;
   }
   //------------------------------------------------------------
   // <T>�����л����������ڲ����ݡ�</T>
   TInt Unserialize(TAnyC* pMemory){
      TByteC* pPtr = (TByteC*)pMemory;
      // �������
      _count = *(TUint16*)pPtr;
      if(_count > MO_NETMESSAGE_MAXTARGET){
         MO_DEBUG_FATAL(TC("Unserialize net targets not enough memory. (size=%d, count=%d)"), MO_NETMESSAGE_MAXTARGET, this->_count);
         return -1;
      }
      // ��������
      TInt total = 0;
      if(_count > 0){
         total = sizeof(SNetTarget) * _count;
         MO_LIB_MEMORY_COPY(_targets, total, pPtr + sizeof(TUint16), total);
      }
      return sizeof(TUint16) + total;
   }
   //------------------------------------------------------------
   // <T>�����ڲ����ݡ�</T>
   void Reset(){
      _count = 0;
   }
};

//============================================================
// <T>��������ͷ���塣</T>
// <P>6�ֽڡ�</P>
//
// @history 100402 MAOCY ����
//============================================================
#pragma pack(1)
struct MO_CR_DECLARE SNetHead{
   TNetLength length;   // ���ݳ��� (����������)
   TUint8     protocol; // ������� (Data/Message/Router/Transfer/Package)
   TUint8     sign;     // �������
   TNetHash   hash;     // ����ǩ��
};
#pragma pack()

//============================================================
// <T>��������ͷ��Ϣ</T>
//
// @history 101014 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetHead{
protected:
   SNetHead _data;
public:
   TNetHead();
public:
   //------------------------------------------------------------
   // <T>����������ݡ�</T>
   MO_INLINE SNetHead& Data(){
      return _data;
   }
   //------------------------------------------------------------
   // <T>���ͷ��С��</T>
   MO_INLINE TInt Capacity(){
      return sizeof(SNetHead);
   }
public:
   //------------------------------------------------------------
   // <T>��ó��ȡ�</T>
   MO_INLINE TNetLength Length(){
      return _data.length;
   }
   //------------------------------------------------------------
   // <T>���ó��ȡ�</T>
   MO_INLINE void SetLength(TNetLength length){
      _data.length = length;
   }
   //------------------------------------------------------------
   // <T>���Э�顣</T>
   MO_INLINE TUint8 Protocol(){
      return _data.protocol;
   }
   //------------------------------------------------------------
   // <T>����Э�顣</T>
   MO_INLINE void SetProtocol(TUint8 protocol){
      _data.protocol = protocol;
   }
   //------------------------------------------------------------
   // <T>��ñ�־��</T>
   MO_INLINE TUint8 Sign(){
      return _data.sign;
   }
   //------------------------------------------------------------
   // <T>���ñ�־��</T>
   MO_INLINE void SetSign(TUint8 sign){
      _data.sign = sign;
   }
   //------------------------------------------------------------
   // <T>���ѹ����־��</T>
   MO_INLINE TBool SignCompress(){
      return (_data.sign & MO_NET_SIGN_COMPRESS);
   }
   //------------------------------------------------------------
   // <T>����ѹ����־��</T>
   MO_INLINE void SetSignCompress(TBool compress){
      if(compress){
         _data.sign |= MO_NET_SIGN_COMPRESS;
      }else{
         _data.sign &= ~MO_NET_SIGN_COMPRESS;
      }
   }
   //------------------------------------------------------------
   // <T>����ڵ���־��</T>
   MO_INLINE TBool SignMask(){
      return (_data.sign & MO_NET_SIGN_MASK);
   }
   //------------------------------------------------------------
   // <T>�����ڵ���־��</T>
   MO_INLINE void SetSignMask(TBool mask){
      if(mask){
         _data.sign |= MO_NET_SIGN_MASK;
      }else{
         _data.sign &= ~MO_NET_SIGN_MASK;
      }
   }
   //------------------------------------------------------------
   // <T>��ù�ϣֵ��</T>
   MO_INLINE TNetHash Hash(){
      return _data.hash;
   }
   //------------------------------------------------------------
   // <T>���ù�ϣֵ��</T>
   MO_INLINE void SetHash(TNetHash hash){
      _data.hash = hash;
   }
public:
   void Assign(TNetHead& head);
   TInt Serialize(TAny* pMemory);
   TInt Unserialize(TAnyC* pMemory);
};

//============================================================
// <T>��������ͷ��Ϣ</T>
//
// @history 101014 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetData{
protected:
   TNetHead _netHead;
   TByteC* _pData;
   TInt _dataLength;
public:
   TNetData();
   MO_ABSTRACT ~TNetData();
public:
   //------------------------------------------------------------
   // <T>�������ͷ��Ϣ��</T>
   MO_INLINE TNetHead& NetHead(){
      return _netHead;
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TBool HasData(){
      return (NULL != _pData) && (_dataLength > 0);
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE TByteC* DataC() const{
      return _pData;
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TInt DataLength(){
      return _dataLength;
   }
protected:
   static TNetHash CalculateHash(TNetSerial serial, TNetTick date, TByteC* pMemory, TInt length);
   static TBool MaskData(TByte* pDate, TInt capacity, TByteC* pInput, TInt length, TNetHash hash);
public:
   MO_ABSTRACT TInt Capacity();
public:
   MO_ABSTRACT TBool Assign(TNetData* pData);
public:
   MO_ABSTRACT TBool SerializeData(TAny* pMemory, TInt size, TInt* length);
   MO_ABSTRACT TBool UnserializeData(TAnyC* pMemory, TInt size, TInt* length);
   MO_ABSTRACT TBool Serialize(TAny* pMemory, TInt size, TInt* length);
   MO_ABSTRACT TBool Unserialize(TAnyC* pMemory, TInt size, TInt* length);
public:
   TInt Store(TAny* pMemory);
   TInt Restore(TAnyC* pMemory);
public:
   MO_ABSTRACT TCharC* DumpData(TChar* pDump, TSize capacity);
   MO_ABSTRACT TCharC* DumpMemory(TChar* pDump, TSize capacity);
   MO_ABSTRACT TCharC* Dump(TChar* pDump, TSize capacity);
};

//============================================================
// <T>�������ݻ��塣</T>
//
// @history 110516 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetBuffer{
protected:
   TByte _buffer[MO_NETMESSAGE_MAXLENGTH];
public:
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE operator TByte*(){
      return _buffer;
   }
public:
   //------------------------------------------------------------
   // <T>����ڴ档</T>
   MO_INLINE TByte* Memory(){
      return _buffer;
   }
   //------------------------------------------------------------
   // <T>��óߴ硣</T>
   MO_INLINE TSize Size(){
      return MO_NETMESSAGE_MAXLENGTH;
   }
};

//============================================================
// <T>������Ϣͷ��Ϣ�Ķ��塣</T>
//
// @history 101020 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetMessageInfo{
public:
   TCharC* _pName;          // ����
   TUint32 _sign;           // ��־ (TCP/UDP/THREAD)
   TNetVersion _version;    // �汾
   TUint32 _sourceTerminal; // Դ�ն�����
   TUint32 _targetTerminal; // Դ�ն�����
   TUint32 _serviceCd;      // ��������
public:
   //------------------------------------------------------------
   // <T>����������Ϣͷ��Ϣ�Ķ��塣</T>
   TNetMessageInfo(TCharC* pName, TUint32 sign, TNetVersion version, TUint32 sourceTerminal, TUint32 targetTerminal, TUint32 serviceCd){
      _pName = pName;
      _sign = sign;
      _version = version;
      _sourceTerminal = sourceTerminal;
      _targetTerminal = targetTerminal;
      _serviceCd = serviceCd;
   }
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _pName;
   }
   //------------------------------------------------------------
   // <T>��ñ�־��</T>
   MO_INLINE TUint32 Sign(){
      return _sign;
   }
   //------------------------------------------------------------
   // <T>��ð汾��</T>
   MO_INLINE TNetVersion Version(){
      return _version;
   }
   //------------------------------------------------------------
   // <T>����ն���Դ��</T>
   MO_INLINE TUint32 SourceTerminal(){
      return _sourceTerminal;
   }
   //------------------------------------------------------------
   // <T>����ն�Ŀ�ꡣ</T>
   MO_INLINE TUint32 TargetTerminal(){
      return _targetTerminal;
   }
   //------------------------------------------------------------
   // <T>��÷������͡�</T>
   MO_INLINE TUint32 ServiceCd(){
      return _serviceCd;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�֧��TCPЭ�顣</T>
   MO_INLINE TBool IsTcpSupport(){
      TUint32 sign = 1 << ENetMessageSign_Tcp;
      return _sign & sign;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�֧��UDPЭ�顣</T>
   MO_INLINE TBool IsUdpSupport(){
      TUint32 sign = 1 << ENetMessageSign_Udp;
      return _sign & sign;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�֧���̡߳�</T>
   MO_INLINE TBool IsThreadSupport(){
      TUint32 sign = 1 << ENetMessageSign_Thread;
      return _sign & sign;
   }
};

//============================================================
// <T>������Ϣͷ��Ϣ�Ķ��塣</T>
// <P>4�ֽڡ�</P>
//
// @history 100401 MAOCY ����
//============================================================
#pragma pack(2)
struct MO_CR_DECLARE SNetMessageHead{
   TUint8  type;        // ��Ϣ���ͣ�Request/Response/Notify��
   TUint8  command;     // ��Ϣ����
   TUint16 code;        // ��Ϣ����
   TNetVersion version; // ��Ϣ�汾
   TNetSerial serial;   // ��Ϣ����
   TNetTick tick;       // ��Ϣʱ��
};
#pragma pack()

//============================================================
// <T>������Ϣͷ��Ϣ</T>
//
// @history 100401 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetMessageHead{
protected:
   SNetMessageHead _data;
public:
   TNetMessageHead();
public:
   //------------------------------------------------------------
   // <T>����������ݡ�</T>
   MO_INLINE SNetMessageHead& Data(){
      return _data;
   }
   //------------------------------------------------------------
   // <T>�����Ϣ��С��</T>
   MO_INLINE TSize Capacity(){
      return sizeof(SNetMessageHead);
   }
public:
   //------------------------------------------------------------
   // <T>������͡�</T>
   MO_INLINE TUint8 Type(){
      return _data.type;
   }
   //------------------------------------------------------------
   // <T>�������͡�</T>
   MO_INLINE void SetType(TUint8 type){
      _data.type = type;
   }
   //------------------------------------------------------------
   // <T>������</T>
   MO_INLINE TUint8 Command(){
      return _data.command;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void SetCommand(TUint8 command){
      _data.command = command;
   }
   //------------------------------------------------------------
   // <T>��÷��顣</T>
   MO_INLINE TUint16 CodeGroup(){
      return _data.code & 0xFF00;
   }
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE TUint16 Code(){
      return _data.code;
   }
   //------------------------------------------------------------
   // <T>���ô��롣</T>
   MO_INLINE void SetCode(TUint16 code){
      _data.code = code;
   }
   //------------------------------------------------------------
   // <T>��ð汾��</T>
   MO_INLINE TNetVersion Version(){
      return _data.version;
   }
   //------------------------------------------------------------
   // <T>���ð汾��</T>
   MO_INLINE void SetVersion(TNetVersion version){
      _data.version = version;
   }
   //------------------------------------------------------------
   // <T>������С�</T>
   MO_INLINE TNetSerial Serial(){
      return _data.serial;
   }
   //------------------------------------------------------------
   // <T>�������С�</T>
   MO_INLINE void SetSerial(TNetSerial serial){
      _data.serial = serial;
   }
   //------------------------------------------------------------
   // <T>���ʱ�̡�</T>
   MO_INLINE TNetTick Tick(){
      return _data.tick;
   }
   //------------------------------------------------------------
   // <T>����ʱ�̡�</T>
   MO_INLINE void SetTick(TNetTick tick){
      _data.tick = tick;
   }
public:
   TCharC* CodeName();
public:
   void Continue(TNetMessageHead& head);
   void Response(TNetMessageHead& head);
public:
   void Assign(TNetMessageHead& head);
   TInt Serialize(TAny* pMemory);
   TInt Unserialize(TAnyC* pMemory);
};

//============================================================
// <T>������Ϣ��</T>
//
// @history 100401 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetMessage : public TNetData{
protected:
   TNetMessageHead _messageHead;
public:
   TNetMessage();
   TNetMessage(TNetMessage* pMessage);
   MO_ABSTRACT ~TNetMessage(){
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void operator=(TNetMessage* pMessage){
      Assign(pMessage);
   }
public:
   //------------------------------------------------------------
   // <T>�����Ϣ��Ϣ��</T>
   MO_INLINE TNetMessageHead& MessageHead(){
      return _messageHead;
   }
public:
   MO_OVERRIDE TInt Capacity();
   MO_ABSTRACT TNetMessageInfo* MessageInfo();
public:
   MO_OVERRIDE TBool Assign(TNetMessage* pMessage);
public:
   TBool SerializeMessage(TAny* pMemory, TInt size, TInt* pLength);
   TBool UnserializeMessage(TAnyC* pMemory, TInt size, TInt* pLength);
   TBool CompressMessage(TAny* pMemory, TInt size, TInt* pLength);
   MO_OVERRIDE TBool Serialize(TAny* pMemory, TInt size, TInt* pLength);
   MO_OVERRIDE TBool Unserialize(TAnyC* pMemory, TInt size, TInt* pLength);
public:
   TCharC* DumpMessage(TChar* pDump, TSize capacity);
   TCharC* DumpMessageMemory(TChar* pDump, TSize capacity);
   MO_OVERRIDE TCharC* Dump(TChar* pDump, TSize capacity);
};

//============================================================
// <T>������Ϣ��</T>
//
// @history 100401 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetMessageBuffer : public TNetMessage{
protected:
   TByte _buffer[MO_NETMESSAGE_MAXLENGTH];
public:
   TNetMessageBuffer();
   TNetMessageBuffer(TAnyC* pMemory);
   MO_ABSTRACT ~TNetMessageBuffer(){
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void operator=(TAnyC* pMemory){
      Restore(pMemory);
   }
public:
   //------------------------------------------------------------
   // <T>����ڴ档</T>
   MO_INLINE TByte* Memory(){
      return _buffer;
   }
public:
   void AssignData(TByteC* pData, TInt length);
   void Update();
public:
   MO_OVERRIDE TBool Serialize(TAny* pMemory, TInt size, TInt* length);
   MO_OVERRIDE TBool Unserialize(TAnyC* pMemory, TInt size, TInt* length);
   TBool UnserializeMask(TAnyC* pMemory, TInt size, TInt* length);
   TBool UnserializeUncheck(TAnyC* pMemory, TInt size, TInt* length);
   TBool Compress(TAny* pMemory, TInt size, TInt* length);
   TBool Uncompress(TAnyC* pMemory, TInt size, TInt* length, TBool masked = EFalse, TBool checked = ETrue);
public:
   MO_OVERRIDE TCharC* Dump(TChar* pDump, TSize capacity);
};

//============================================================
// <T>����·�ɽṹ��</T>
// <P>20�ֽڡ�</P>
//
//  - flag      [16Bit]      ·�ɱ�־
//  - origin    [32Bit]      ����ԭʼ��Դ
//  - source    [32Bit]      ������Դ
//  - target    [32Bit]      ����Ŀ��
//  - serial    [32Bit]      ·������
//  - targets   [32Bitx1024] ����Ŀ���б�
// @history 091220 MAOCY ����
//============================================================
#pragma pack(2)
struct MO_CR_DECLARE SNetRouterHead{
   TUint16    Flag;
   SNetTarget Origin;
   SNetTarget Source;
   SNetTarget Target;
   TNetSerial Serial;
};
#pragma pack()

//============================================================
class MO_CR_DECLARE TNetRouterHead{
protected:
   SNetRouterHead _data;
   TNetTargets _targets;
public:
   TNetRouterHead();
public:
   //------------------------------------------------------------
   // <T>����������ݡ�</T>
   MO_INLINE SNetRouterHead& Data(){
      return _data;
   }
   //------------------------------------------------------------
   // <T>�����Ϣ��С��</T>
   MO_INLINE TSize Capacity(){
      return sizeof(SNetRouterHead) + _targets.Capacity();
   }
public:
   //------------------------------------------------------------
   // <T>��ñ�־��</T>
   MO_INLINE TUint16 Flag(){
      return _data.Flag;
   }
   //------------------------------------------------------------
   // <T>���ñ�־��</T>
   MO_INLINE void SetFlag(TUint16 flag){
      _data.Flag = flag;
   }
   //------------------------------------------------------------
   // <T>��÷Ƿ���־��</T>
   MO_INLINE TBool FlagInvalid(){
      return (_data.Flag & MO_NETROUTER_FLAG_INVALID);
   }
   //------------------------------------------------------------
   // <T>���÷Ƿ���־��</T>
   MO_INLINE void SetFlagInvalid(TBool invalid){
      if(invalid){
         _data.Flag |= MO_NETROUTER_FLAG_INVALID;
      }else{
         _data.Flag &= ~MO_NETROUTER_FLAG_INVALID;
      }
   }
   //------------------------------------------------------------
   // <T>��öϿ���־��</T>
   MO_INLINE TBool FlagDisconnect(){
      return (_data.Flag & MO_NETROUTER_FLAG_DISCONNECT);
   }
   //------------------------------------------------------------
   // <T>���öϿ���־��</T>
   MO_INLINE void SetFlagDisconnect(TBool disconnect){
      if(disconnect){
         _data.Flag |= MO_NETROUTER_FLAG_DISCONNECT;
      }else{
         _data.Flag &= ~MO_NETROUTER_FLAG_DISCONNECT;
      }
   }
   //------------------------------------------------------------
   // <T>���������Դ��</T>
   MO_INLINE SNetTarget& Origin(){
      return _data.Origin;
   }
   //------------------------------------------------------------
   // <T>����������Դ��</T>
   MO_INLINE void SetOrigin(SNetTarget& origin){
      _data.Origin = origin;
   }
   //------------------------------------------------------------
   // <T>��ûỰ��š�</T>
   MO_INLINE TUint32 SessionId(){
      return _data.Origin.ObjectHandle();
   }
   //------------------------------------------------------------
   // <T>���ûỰ��š�</T>
   MO_INLINE void SetSessionId(TUint32 sessionId){
      _data.Origin.SetObjectHandle(sessionId);
   }
   //------------------------------------------------------------
   // <T>���������Դ��</T>
   MO_INLINE SNetTarget& Source(){
      return _data.Source;
   }
   //------------------------------------------------------------
   // <T>����������Դ��</T>
   MO_INLINE void SetSource(SNetTarget& source){
      _data.Source = source;
   }
   //------------------------------------------------------------
   // <T>�����Դ���͡�</T>
   MO_INLINE TUint8 SourceType(){
      return _data.Source.ServerType();
   }
   //------------------------------------------------------------
   // <T>������Դ���͡�</T>
   MO_INLINE void SetSourceType(TUint8 type){
      _data.Source.SetServerType(type);
   }
   //------------------------------------------------------------
   // <T>�������Ŀ�ꡣ</T>
   MO_INLINE SNetTarget& Target(){
      return _data.Target;
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   MO_INLINE void SetTarget(SNetTarget& target){
      _data.Target = target;
   }
   //------------------------------------------------------------
   // <T>�������Ŀ�����͡�</T>
   MO_INLINE TUint8 TargetType(){
      return _data.Target.ServerType();
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�����͡�</T>
   MO_INLINE void SetTargetType(TUint8 type){
      _data.Target.SetServerType(type);
   }
   //------------------------------------------------------------
   // <T>������С�</T>
   MO_INLINE TNetSerial Serial(){
      return _data.Serial;
   }
   //------------------------------------------------------------
   // <T>�������С�</T>
   MO_INLINE void SetSerial(TNetSerial serial){
      _data.Serial = serial;
   }
   //------------------------------------------------------------
   // <T>�������Ŀ�꼯�ϡ�</T>
   MO_INLINE TNetTargets& Targets(){
      return _targets;
   }
public:
   void Continue(TNetRouterHead& head);
   void Response(TNetRouterHead& head);
public:
   void Assign(TNetRouterHead& head);
   TInt Serialize(TAny* pMemory);
   TInt Unserialize(TAnyC* pMemory);
public:
   TCharC* Dump(TChar* pDump, TSize length);
};

//============================================================
// <T>������Ϣ������</T>
//
// @history 091220 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetRouter : public TNetMessage{
protected:
   TNetRouterHead _routerHead;
   TByte _buffer[MO_NETMESSAGE_MAXLENGTH];
public:
   TNetRouter();
   TNetRouter(TNetMessage* pMessage);
   MO_ABSTRACT ~TNetRouter();
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void operator=(TNetMessage* pMessage){
      LinkMessage(pMessage);
   }
public:
   //------------------------------------------------------------
   // <T>���·��ͷ��</T>
   MO_INLINE TNetRouterHead& RouterHead(){
      return _routerHead;
   }
   //------------------------------------------------------------
   // <T>�������Ŀ�꼯�ϡ�</T>
   MO_INLINE TNetTargets& Targets(){
      return _routerHead.Targets();
   }
public:
   MO_OVERRIDE TInt Capacity();
public:
   void LinkMessage(TNetMessage* pMessage);
   void ContinueFrom(TNetRouter* pRouter);
   void ResponseFrom(TNetRouter* pRouter);
public:
   MO_OVERRIDE TBool Assign(TNetRouter* pRouter);
   TBool StoreMessage(TNetMessageBuffer& buffer);
   TBool SerializeRouter(TAny* pMemory, TInt size, TInt* length);
   TBool UnserializeRouter(TAnyC* pMemory, TInt size, TInt* length);
   MO_OVERRIDE TBool Serialize(TAny* pMemory, TInt size, TInt* length);
   MO_OVERRIDE TBool Unserialize(TAnyC* pMemory, TInt size, TInt* length);
public:
   TCharC* DumpRouter(TChar* pDump, TSize capacity);
   TCharC* DumpRouterMemory(TChar* pDump, TSize capacity);
   MO_OVERRIDE TCharC* Dump(TChar* pDump, TSize capacity);
};

//============================================================
// <T>���紫��ṹ��</T>
//
//  - Handle [32Bit] ������
//  - Ip     [32Bit] ��ַ
//  - Port   [16Bit] �˿�
//  - socket [32Bit] ��������
// @history 091220 MAOCY ����
//============================================================
#pragma pack(2)
struct MO_CR_DECLARE SNetTransferHead{
   TUint32 Handle;
   TUint32 Ip;
   TUint16 Port;
   SNetSocketTarget socket;
};
#pragma pack()

//============================================================
#pragma pack(2)
class MO_CR_DECLARE TNetTransferHead{
protected:
   SNetTransferHead _data;
public:
   TNetTransferHead();
public:
   //------------------------------------------------------------
   // <T>����������ݡ�</T>
   MO_INLINE SNetTransferHead& Data(){
      return _data;
   }
   //------------------------------------------------------------
   // <T>�����Ϣ��С��</T>
   MO_INLINE TSize Capacity(){
      return sizeof(SNetTransferHead);
   }
public:
   //------------------------------------------------------------
   // <T>��þ����</T>
   MO_INLINE TUint32 Handle(){
      return _data.Handle;
   }
   //------------------------------------------------------------
   // <T>���þ����</T>
   MO_INLINE void SetHandle(TUint32 handle){
      _data.Handle = handle;
   }
   //------------------------------------------------------------
   // <T>��������ַ��</T>
   MO_INLINE TUint32 Ip(){
      return _data.Ip;
   }
   //------------------------------------------------------------
   // <T>���������ַ��</T>
   MO_INLINE void SetIp(TUint32 ip){
      _data.Ip = ip;
   }
   //------------------------------------------------------------
   // <T>�������˿ڡ�</T>
   MO_INLINE TUint16 Port(){
      return _data.Port;
   }
   //------------------------------------------------------------
   // <T>��������˿ڡ�</T>
   MO_INLINE void SetPort(TUint16 port){
      _data.Port = port;
   }
   //------------------------------------------------------------
   // <T>�������������</T>
   MO_INLINE void SetHost(TUint32 ip, TUint16 port){
      _data.Ip = ip;
      _data.Port = port;
   }
   //------------------------------------------------------------
   // <T>�������Ŀ�ꡣ</T>
   MO_INLINE SNetSocketTarget& Socket(){
      return _data.socket;
   }
   //------------------------------------------------------------
   // <T>�������������</T>
   MO_INLINE TUint16 SocketIndex(){
      return _data.socket.Index();
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   MO_INLINE void SetSocket(TUint16 index, TUint16 serial){
      _data.socket.Set(index, serial);
   }
   //------------------------------------------------------------
   // <T>��������Ŀ�ꡣ</T>
   MO_INLINE void SetSocket(SNetSocketTarget socket){
      _data.socket = socket;
   }
   //------------------------------------------------------------
   // <T>������������</T>
   MO_INLINE void SetSocketHandle(TUint32 handle){
      _data.socket.Set(handle);
   }
public:
   void Assign(TNetTransferHead& head);
   TInt Serialize(TAny* pMemory);
   TInt Unserialize(TAnyC* pMemory);
   TBool Pack(MPack* pPack);
   TBool Unpack(MPack* pPack);
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      _data.Handle = 0;
      _data.Ip = 0;
      _data.Port = 0;
      _data.socket.Reset();      
   }
public:
   TCharC* Dump(TChar* pDump, TSize length);
public:
   //------------------------------------------------------------
   // <T>������Ϣ��</T>
   MO_INLINE TChar* Track(MString* pTrack, TInt level){
      return NULL;
   }
};
#pragma pack()

//============================================================
// <T>���紫������</T>
//
// @history 091220 MAOCY ����
//============================================================
class MO_CR_DECLARE TNetTransfer : public TNetRouter{
public:
   enum EMode{
      EMode_Unknown,
      EMode_Continue,
      EMode_Response,
   };
protected:
   TNetTransferHead _transferHead;
public:
   TNetTransfer();
   TNetTransfer(TNetMessage* pMessage);
   TNetTransfer(TNetMessage* pMessage, EMode modeCd, TNetRouter* pRouter);
   TNetTransfer(TNetMessage* pMessage, EMode modeCd, TNetTransfer* pTransfer);
   TNetTransfer(TNetRouter* pRouter);
   MO_ABSTRACT ~TNetTransfer();
public:
   //------------------------------------------------------------
   // <T>����������Ϣ��</T>
   MO_INLINE void operator=(TNetMessage* pMessage){
      LinkMessage(pMessage);
   }
   //------------------------------------------------------------
   // <T>��������·�ɡ�</T>
   MO_INLINE void operator=(TNetRouter* pRouter){
      LinkRouter(pRouter);
   }
public:
   //------------------------------------------------------------
   // <T>��ô���ͷ��</T>
   MO_INLINE TNetTransferHead& TransferHead(){
      return _transferHead;
   }
public:
   MO_OVERRIDE TInt Capacity();
public:
   void ContinueFrom(TNetRouter* pRouter);
   void ContinueFrom(TNetTransfer* pTransfer);
   void ResponseFrom(TNetRouter* pRouter);
   void ResponseFrom(TNetTransfer* pTransfer);
   void LinkMessage(TNetMessage* pMessage);
   void LinkRouter(TNetRouter* pRouter);
public:
   MO_OVERRIDE TBool Assign(TNetTransfer* pRouter);
   MO_OVERRIDE TBool Serialize(TAny* pMemory, TInt size, TInt* length);
   MO_OVERRIDE TBool Unserialize(TAnyC* pMemory, TInt size, TInt* length);
public:
   TCharC* DumpTransfer(TChar* pDump, TSize capacity);
   MO_OVERRIDE TCharC* DumpSimple(TChar* pDump, TSize capacity);
   MO_OVERRIDE TCharC* Dump(TChar* pDump, TSize capacity);
};

//============================================================
// <T>�������ݰ����塣</T>
// <P>�ӿͻ��˽�������з������ڣ��ܵ��ڵ��׽ṹ��</P>
//
// @history 100401 MAOCY ����
//============================================================
struct MO_CR_DECLARE SNetPackageHead{
   TUint16 type;
   TUint16 code;
};

//============================================================
// <T>�����ͷ���塣</T>
//============================================================
class MO_CR_DECLARE TNetPackageHead{
   SNetPackageHead _data;
};

//============================================================
// <T>��������塣</T>
//============================================================
class MO_CR_DECLARE TNetPackage : public TNetData{
public:
   TNetPackageHead _head;
public:
   //------------------------------------------------------------
   // <T>������������塣</T>
   MO_ABSTRACT ~TNetPackage(){
   }
};

//============================================================
// <T>��Ϣ�����ӿڡ�</T>
//============================================================
class MO_CR_DECLARE INetMessageFactory{
public:
   //------------------------------------------------------------
   // <T>������Ϣ�����ӿڡ�</T>
   MO_ABSTRACT ~INetMessageFactory(){
   }
public:
   MO_VIRTUAL TCharC* CodeName(TInt code) = 0;
   MO_VIRTUAL TNetMessageInfo* CodeInfo(TInt code) = 0;
   MO_VIRTUAL TCharC* DumpData(TNetMessage* pMessage, MString* pTrack) = 0;
};

//============================================================
// <T>��Ϣ������</T>
//============================================================
class MO_CR_DECLARE RNetMessageFactory{
protected:
   static INetMessageFactory* _pFactory;
public:
   //------------------------------------------------------------
   // <T>�����Ϣ������</T>
   static INetMessageFactory* Factory(){
      return _pFactory;
   }
   //------------------------------------------------------------
   // <T>������Ϣ������</T>
   static void SetFactory(INetMessageFactory* pFactory){
      MO_ASSERT(pFactory);
      _pFactory = pFactory;
   }
public:
   //------------------------------------------------------------
   // <T>������Ϣ��������Ϣ���ơ�</T>
   static TCharC* CodeName(TInt code){
      return _pFactory->CodeName(code);
   }
   //------------------------------------------------------------
   // <T>������Ϣ��������Ϣ��Ϣ��</T>
   static TNetMessageInfo* CodeInfo(TInt code){
      return _pFactory->CodeInfo(code);
   }
   //------------------------------------------------------------
   // <T>�����Ϣ���ݡ�</T>
   static TCharC* DumpData(TNetMessage* pMessage, MString* pTrack){
      return _pFactory->DumpData(pMessage, pTrack) ;
   }
};

MO_NAMESPACE_END

#endif // __MO_CR_NET_MESSAGE_H__
