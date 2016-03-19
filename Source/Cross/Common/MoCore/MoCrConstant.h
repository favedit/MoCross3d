//============================================================
// <T>ϵͳ����ö�ٶ��塣</T>
//
// @version 1.0.1
// @auto ����������Ĵ��룬�����޸������ֶ��޸ı���ĵط��޸ġ�
//============================================================
#ifndef __MO_CR_CONSTANT_H__
#define __MO_CR_CONSTANT_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

MO_NAMESPACE_BEGIN

// ģ���ǩ��󳤶ȶ���
const TUint32 MO_CR_TPL_NAME_MAXLEN = 64;

// ģ���ǩ��󳤶ȶ���
const TUint32 MO_CR_TPL_LABEL_MAXLEN = 64;

// ģ��������󳤶ȶ���
const TUint32 MO_CR_TPL_NOTE_MAXLEN = 1024;

// �ڴ����������������
const TUint32 MO_CR_MEMORY_OBJECT_PROCESS_MAXCNT = 16;

//============================================================
// <T>�����Э��ö�ٶ��塣</T>
//
// @enum
//============================================================
enum ENetProtocol{
   ENetProtocol_Unknown        = 0x00, // λ��
   ENetProtocol_Data           = 0x01, // ����
   ENetProtocol_Message        = 0x03, // ��Ϣ
   ENetProtocol_Router         = 0x07, // ·��
   ENetProtocol_Transfer       = 0x0F, // ����
   ENetProtocol_Package        = 0x1F, // ���ݰ�
};

//============================================================
// <T>�����Э��ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumNetProtocol{
public:
   static ENetProtocol Parse(TCharC* pValue);
   static ENetProtocol ParseCode(TCharC* pValue);
   static TCharC* ToCode(ENetProtocol value);
   static TCharC* ToString(ENetProtocol value);
};

//============================================================
// <T>�������־ö�ٶ��塣</T>
//
// @enum
//============================================================
enum ENetSign{
   ENetSign_Unknown        = 0, // δ֪
   ENetSign_Valid          = 1, // ��Ч
   ENetSign_Client         = 2, // �ͻ�
   ENetSign_Debug          = 3, // ����
   ENetSign_Analysis       = 4, // ����
   ENetSign_Track          = 5, // ����
};

//============================================================
// <T>�������־ö���ࡣ</T>
//
// @class
//============================================================
struct MO_CR_DECLARE TNetSignSet : TBitSet<TUint32>{
public:
   //------------------------------------------------------------
   // <T>���δ֪��</T>
   MO_INLINE TBool IsUnknown(){
      return GetBit(ENetSign_Unknown);
   }
   //------------------------------------------------------------
   // <T>���δ֪��</T>
   MO_INLINE TBool IsNotUnknown(){
      return !GetBit(ENetSign_Unknown);
   }
   //------------------------------------------------------------
   // <T>����δ֪��</T>
   MO_INLINE void UnknownSet(){
      return SetBit(ENetSign_Unknown);
   }
   //------------------------------------------------------------
   // <T>��תδ֪��</T>
   MO_INLINE void UnknownInverse(){
      InverseBit(ENetSign_Unknown);
   }
   //------------------------------------------------------------
   // <T>�޸�δ֪��</T>
   MO_INLINE void UnknownModify(TBool flag){
      ModifyBit(ENetSign_Unknown, flag);
   }
   //------------------------------------------------------------
   // <T>���δ֪��</T>
   MO_INLINE void UnknownClear(){
      ClearBit(ENetSign_Unknown);
   }
public:
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE TBool IsValid(){
      return GetBit(ENetSign_Valid);
   }
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE TBool IsNotValid(){
      return !GetBit(ENetSign_Valid);
   }
   //------------------------------------------------------------
   // <T>������Ч��</T>
   MO_INLINE void ValidSet(){
      return SetBit(ENetSign_Valid);
   }
   //------------------------------------------------------------
   // <T>��ת��Ч��</T>
   MO_INLINE void ValidInverse(){
      InverseBit(ENetSign_Valid);
   }
   //------------------------------------------------------------
   // <T>�޸���Ч��</T>
   MO_INLINE void ValidModify(TBool flag){
      ModifyBit(ENetSign_Valid, flag);
   }
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE void ValidClear(){
      ClearBit(ENetSign_Valid);
   }
public:
   //------------------------------------------------------------
   // <T>��ÿͻ���</T>
   MO_INLINE TBool IsClient(){
      return GetBit(ENetSign_Client);
   }
   //------------------------------------------------------------
   // <T>��ÿͻ���</T>
   MO_INLINE TBool IsNotClient(){
      return !GetBit(ENetSign_Client);
   }
   //------------------------------------------------------------
   // <T>���ÿͻ���</T>
   MO_INLINE void ClientSet(){
      return SetBit(ENetSign_Client);
   }
   //------------------------------------------------------------
   // <T>��ת�ͻ���</T>
   MO_INLINE void ClientInverse(){
      InverseBit(ENetSign_Client);
   }
   //------------------------------------------------------------
   // <T>�޸Ŀͻ���</T>
   MO_INLINE void ClientModify(TBool flag){
      ModifyBit(ENetSign_Client, flag);
   }
   //------------------------------------------------------------
   // <T>����ͻ���</T>
   MO_INLINE void ClientClear(){
      ClearBit(ENetSign_Client);
   }
public:
   //------------------------------------------------------------
   // <T>��õ��ԡ�</T>
   MO_INLINE TBool IsDebug(){
      return GetBit(ENetSign_Debug);
   }
   //------------------------------------------------------------
   // <T>��õ��ԡ�</T>
   MO_INLINE TBool IsNotDebug(){
      return !GetBit(ENetSign_Debug);
   }
   //------------------------------------------------------------
   // <T>���õ��ԡ�</T>
   MO_INLINE void DebugSet(){
      return SetBit(ENetSign_Debug);
   }
   //------------------------------------------------------------
   // <T>��ת���ԡ�</T>
   MO_INLINE void DebugInverse(){
      InverseBit(ENetSign_Debug);
   }
   //------------------------------------------------------------
   // <T>�޸ĵ��ԡ�</T>
   MO_INLINE void DebugModify(TBool flag){
      ModifyBit(ENetSign_Debug, flag);
   }
   //------------------------------------------------------------
   // <T>������ԡ�</T>
   MO_INLINE void DebugClear(){
      ClearBit(ENetSign_Debug);
   }
public:
   //------------------------------------------------------------
   // <T>��÷�����</T>
   MO_INLINE TBool IsAnalysis(){
      return GetBit(ENetSign_Analysis);
   }
   //------------------------------------------------------------
   // <T>��÷�����</T>
   MO_INLINE TBool IsNotAnalysis(){
      return !GetBit(ENetSign_Analysis);
   }
   //------------------------------------------------------------
   // <T>���÷�����</T>
   MO_INLINE void AnalysisSet(){
      return SetBit(ENetSign_Analysis);
   }
   //------------------------------------------------------------
   // <T>��ת������</T>
   MO_INLINE void AnalysisInverse(){
      InverseBit(ENetSign_Analysis);
   }
   //------------------------------------------------------------
   // <T>�޸ķ�����</T>
   MO_INLINE void AnalysisModify(TBool flag){
      ModifyBit(ENetSign_Analysis, flag);
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE void AnalysisClear(){
      ClearBit(ENetSign_Analysis);
   }
public:
   //------------------------------------------------------------
   // <T>��ø��١�</T>
   MO_INLINE TBool IsTrack(){
      return GetBit(ENetSign_Track);
   }
   //------------------------------------------------------------
   // <T>��ø��١�</T>
   MO_INLINE TBool IsNotTrack(){
      return !GetBit(ENetSign_Track);
   }
   //------------------------------------------------------------
   // <T>���ø��١�</T>
   MO_INLINE void TrackSet(){
      return SetBit(ENetSign_Track);
   }
   //------------------------------------------------------------
   // <T>��ת���١�</T>
   MO_INLINE void TrackInverse(){
      InverseBit(ENetSign_Track);
   }
   //------------------------------------------------------------
   // <T>�޸ĸ��١�</T>
   MO_INLINE void TrackModify(TBool flag){
      ModifyBit(ENetSign_Track, flag);
   }
   //------------------------------------------------------------
   // <T>������١�</T>
   MO_INLINE void TrackClear(){
      ClearBit(ENetSign_Track);
   }
public:
   TSize Capacity();
   void Assign(TNetSignSet& set);
   void Parse(TCharC* pValue);
   void ParseValue(TCharC* pValue);
   TChar* ToString(TChar* pValue, TSize capacity);
   TFsText ToString();
};

//============================================================
// <T>�������־ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumNetSign{
public:
   static ENetSign Parse(TCharC* pValue);
   static ENetSign ParseCode(TCharC* pValue);
   static TCharC* ToCode(ENetSign value);
   static TCharC* ToString(ENetSign value);
};

//============================================================
// <T>��Ϣ����ö�ٶ��塣</T>
//
// @enum
//============================================================
enum ENetMessage{
   ENetMessage_Unknown        = 0, // δ֪
   ENetMessage_Request        = 1, // ����
   ENetMessage_Response       = 2, // Ӧ��
   ENetMessage_Notify         = 3, // ֪ͨ
};

//============================================================
// <T>��Ϣ����ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumNetMessage{
public:
   static ENetMessage Parse(TCharC* pValue);
   static ENetMessage ParseCode(TCharC* pValue);
   static TCharC* ToCode(ENetMessage value);
   static TCharC* ToString(ENetMessage value);
};

//============================================================
// <T>��Ϣ��־ö�ٶ��塣</T>
//
// @enum
//============================================================
enum ENetMessageSign{
   ENetMessageSign_Unknown        = 0, // δ֪
   ENetMessageSign_Tcp            = 1, // TCP֧��
   ENetMessageSign_Udp            = 2, // UDP֧��
   ENetMessageSign_Thread         = 3, // �߳�֧��
};

//============================================================
// <T>��Ϣ��־ö���ࡣ</T>
//
// @class
//============================================================
struct MO_CR_DECLARE TNetMessageSignSet : TBitSet<TUint32>{
public:
   //------------------------------------------------------------
   // <T>���δ֪��</T>
   MO_INLINE TBool IsUnknown(){
      return GetBit(ENetMessageSign_Unknown);
   }
   //------------------------------------------------------------
   // <T>���δ֪��</T>
   MO_INLINE TBool IsNotUnknown(){
      return !GetBit(ENetMessageSign_Unknown);
   }
   //------------------------------------------------------------
   // <T>����δ֪��</T>
   MO_INLINE void UnknownSet(){
      return SetBit(ENetMessageSign_Unknown);
   }
   //------------------------------------------------------------
   // <T>��תδ֪��</T>
   MO_INLINE void UnknownInverse(){
      InverseBit(ENetMessageSign_Unknown);
   }
   //------------------------------------------------------------
   // <T>�޸�δ֪��</T>
   MO_INLINE void UnknownModify(TBool flag){
      ModifyBit(ENetMessageSign_Unknown, flag);
   }
   //------------------------------------------------------------
   // <T>���δ֪��</T>
   MO_INLINE void UnknownClear(){
      ClearBit(ENetMessageSign_Unknown);
   }
public:
   //------------------------------------------------------------
   // <T>���TCP֧�֡�</T>
   MO_INLINE TBool IsTcp(){
      return GetBit(ENetMessageSign_Tcp);
   }
   //------------------------------------------------------------
   // <T>���TCP֧�֡�</T>
   MO_INLINE TBool IsNotTcp(){
      return !GetBit(ENetMessageSign_Tcp);
   }
   //------------------------------------------------------------
   // <T>����TCP֧�֡�</T>
   MO_INLINE void TcpSet(){
      return SetBit(ENetMessageSign_Tcp);
   }
   //------------------------------------------------------------
   // <T>��תTCP֧�֡�</T>
   MO_INLINE void TcpInverse(){
      InverseBit(ENetMessageSign_Tcp);
   }
   //------------------------------------------------------------
   // <T>�޸�TCP֧�֡�</T>
   MO_INLINE void TcpModify(TBool flag){
      ModifyBit(ENetMessageSign_Tcp, flag);
   }
   //------------------------------------------------------------
   // <T>���TCP֧�֡�</T>
   MO_INLINE void TcpClear(){
      ClearBit(ENetMessageSign_Tcp);
   }
public:
   //------------------------------------------------------------
   // <T>���UDP֧�֡�</T>
   MO_INLINE TBool IsUdp(){
      return GetBit(ENetMessageSign_Udp);
   }
   //------------------------------------------------------------
   // <T>���UDP֧�֡�</T>
   MO_INLINE TBool IsNotUdp(){
      return !GetBit(ENetMessageSign_Udp);
   }
   //------------------------------------------------------------
   // <T>����UDP֧�֡�</T>
   MO_INLINE void UdpSet(){
      return SetBit(ENetMessageSign_Udp);
   }
   //------------------------------------------------------------
   // <T>��תUDP֧�֡�</T>
   MO_INLINE void UdpInverse(){
      InverseBit(ENetMessageSign_Udp);
   }
   //------------------------------------------------------------
   // <T>�޸�UDP֧�֡�</T>
   MO_INLINE void UdpModify(TBool flag){
      ModifyBit(ENetMessageSign_Udp, flag);
   }
   //------------------------------------------------------------
   // <T>���UDP֧�֡�</T>
   MO_INLINE void UdpClear(){
      ClearBit(ENetMessageSign_Udp);
   }
public:
   //------------------------------------------------------------
   // <T>����߳�֧�֡�</T>
   MO_INLINE TBool IsThread(){
      return GetBit(ENetMessageSign_Thread);
   }
   //------------------------------------------------------------
   // <T>����߳�֧�֡�</T>
   MO_INLINE TBool IsNotThread(){
      return !GetBit(ENetMessageSign_Thread);
   }
   //------------------------------------------------------------
   // <T>�����߳�֧�֡�</T>
   MO_INLINE void ThreadSet(){
      return SetBit(ENetMessageSign_Thread);
   }
   //------------------------------------------------------------
   // <T>��ת�߳�֧�֡�</T>
   MO_INLINE void ThreadInverse(){
      InverseBit(ENetMessageSign_Thread);
   }
   //------------------------------------------------------------
   // <T>�޸��߳�֧�֡�</T>
   MO_INLINE void ThreadModify(TBool flag){
      ModifyBit(ENetMessageSign_Thread, flag);
   }
   //------------------------------------------------------------
   // <T>����߳�֧�֡�</T>
   MO_INLINE void ThreadClear(){
      ClearBit(ENetMessageSign_Thread);
   }
public:
   TSize Capacity();
   void Assign(TNetMessageSignSet& set);
   void Parse(TCharC* pValue);
   void ParseValue(TCharC* pValue);
   TChar* ToString(TChar* pValue, TSize capacity);
   TFsText ToString();
};

//============================================================
// <T>��Ϣ��־ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumNetMessageSign{
public:
   static ENetMessageSign Parse(TCharC* pValue);
   static ENetMessageSign ParseCode(TCharC* pValue);
   static TCharC* ToCode(ENetMessageSign value);
   static TCharC* ToString(ENetMessageSign value);
};

//============================================================
// <T>������Ϣ��������ö�ٶ��塣</T>
//
// @enum
//============================================================
enum ENetMessageService{
   ENetMessageService_Logic          = 0, // �߼�
   ENetMessageService_Login          = 1, // ��¼
   ENetMessageService_Refresh        = 2, // ˢ��
};

//============================================================
// <T>������Ϣ��������ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumNetMessageService{
public:
   static ENetMessageService Parse(TCharC* pValue);
   static ENetMessageService ParseCode(TCharC* pValue);
   static TCharC* ToCode(ENetMessageService value);
   static TCharC* ToString(ENetMessageService value);
};

//============================================================
// <T>�����ն�ö�ٶ��塣</T>
//
// @enum
//============================================================
enum ENetTerminal{
   ENetTerminal_Unknown        = 0, // δ֪
   ENetTerminal_Client         = 1, // �ͻ���
   ENetTerminal_ServerTransfer = 2, // ����������
   ENetTerminal_GlobalTransfer = 3, // ȫ�ִ���
   ENetTerminal_GlobalProxy    = 4, // ȫ�ִ���
   ENetTerminal_GlobalDomain   = 5, // ȫ������
   ENetTerminal_GlobalLogin    = 6, // ȫ�ֵ�½
   ENetTerminal_GlobalGate     = 7, // ȫ������
   ENetTerminal_GlobalStorage  = 8, // ȫ�ִ洢
   ENetTerminal_GameProxy      = 9, // ��Ϸ����
   ENetTerminal_GameDomain     = 10, // ��Ϸ����
   ENetTerminal_GameGate       = 11, // ��Ϸ����
   ENetTerminal_GameLogin      = 12, // ��Ϸ��¼
   ENetTerminal_GameScene      = 13, // ��Ϸ����
   ENetTerminal_GameBattle     = 14, // ��Ϸս��
   ENetTerminal_GameStorage    = 15, // ��Ϸ�洢
   ENetTerminal_GameChat       = 16, // ��Ϸ����
   ENetTerminal_GameLogger     = 17, // ��Ϸ��־
   ENetTerminal_GameWebInterface = 18, // �����Խӷ�����
   ENetTerminal_Count,
};

//============================================================
// <T>�����ն˴���ö�ٶ��塣</T>
//
// @enum
//============================================================
enum ENetTerminalCode{
   // @member δ֪
   ENetTerminal_UNK = ENetTerminal_Unknown,
   // @member �ͻ���
   ENetTerminal_CLT = ENetTerminal_Client,
   // @member ����������
   ENetTerminal_STS = ENetTerminal_ServerTransfer,
   // @member ȫ�ִ���
   ENetTerminal_ATS = ENetTerminal_GlobalTransfer,
   // @member ȫ�ִ���
   ENetTerminal_APX = ENetTerminal_GlobalProxy,
   // @member ȫ������
   ENetTerminal_ADM = ENetTerminal_GlobalDomain,
   // @member ȫ�ֵ�½
   ENetTerminal_ALG = ENetTerminal_GlobalLogin,
   // @member ȫ������
   ENetTerminal_AGT = ENetTerminal_GlobalGate,
   // @member ȫ�ִ洢
   ENetTerminal_ASR = ENetTerminal_GlobalStorage,
   // @member ��Ϸ����
   ENetTerminal_GPX = ENetTerminal_GameProxy,
   // @member ��Ϸ����
   ENetTerminal_GDM = ENetTerminal_GameDomain,
   // @member ��Ϸ����
   ENetTerminal_GGT = ENetTerminal_GameGate,
   // @member ��Ϸ��¼
   ENetTerminal_GLG = ENetTerminal_GameLogin,
   // @member ��Ϸ����
   ENetTerminal_GSC = ENetTerminal_GameScene,
   // @member ��Ϸս��
   ENetTerminal_GBT = ENetTerminal_GameBattle,
   // @member ��Ϸ�洢
   ENetTerminal_GSR = ENetTerminal_GameStorage,
   // @member ��Ϸ����
   ENetTerminal_GCT = ENetTerminal_GameChat,
   // @member ��Ϸ��־
   ENetTerminal_GLO = ENetTerminal_GameLogger,
   // @member �����Խӷ�����
   ENetTerminal_GWI = ENetTerminal_GameWebInterface,
};

//============================================================
// <T>�����ն�ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumNetTerminal{
public:
   static ENetTerminal Parse(TCharC* pValue);
   static ENetTerminal ParseCode(TCharC* pValue);
   static TCharC* ToCode(ENetTerminal value);
   static TCharC* ToString(ENetTerminal value);
};

//============================================================
// <T>·�ɱ�־ö�ٶ��塣</T>
//
// @enum
//============================================================
enum ENetRouterFlag{
   ENetRouterFlag_Valid          = 0, // ��Ч
   ENetRouterFlag_Disconnect     = 1, // �Ͽ�����
};

//============================================================
// <T>·�ɱ�־ö���ࡣ</T>
//
// @class
//============================================================
struct MO_CR_DECLARE TNetRouterFlagSet : TBitSet<TUint32>{
public:
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE TBool IsValid(){
      return GetBit(ENetRouterFlag_Valid);
   }
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE TBool IsNotValid(){
      return !GetBit(ENetRouterFlag_Valid);
   }
   //------------------------------------------------------------
   // <T>������Ч��</T>
   MO_INLINE void ValidSet(){
      return SetBit(ENetRouterFlag_Valid);
   }
   //------------------------------------------------------------
   // <T>��ת��Ч��</T>
   MO_INLINE void ValidInverse(){
      InverseBit(ENetRouterFlag_Valid);
   }
   //------------------------------------------------------------
   // <T>�޸���Ч��</T>
   MO_INLINE void ValidModify(TBool flag){
      ModifyBit(ENetRouterFlag_Valid, flag);
   }
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE void ValidClear(){
      ClearBit(ENetRouterFlag_Valid);
   }
public:
   //------------------------------------------------------------
   // <T>��öϿ����ӡ�</T>
   MO_INLINE TBool IsDisconnect(){
      return GetBit(ENetRouterFlag_Disconnect);
   }
   //------------------------------------------------------------
   // <T>��öϿ����ӡ�</T>
   MO_INLINE TBool IsNotDisconnect(){
      return !GetBit(ENetRouterFlag_Disconnect);
   }
   //------------------------------------------------------------
   // <T>���öϿ����ӡ�</T>
   MO_INLINE void DisconnectSet(){
      return SetBit(ENetRouterFlag_Disconnect);
   }
   //------------------------------------------------------------
   // <T>��ת�Ͽ����ӡ�</T>
   MO_INLINE void DisconnectInverse(){
      InverseBit(ENetRouterFlag_Disconnect);
   }
   //------------------------------------------------------------
   // <T>�޸ĶϿ����ӡ�</T>
   MO_INLINE void DisconnectModify(TBool flag){
      ModifyBit(ENetRouterFlag_Disconnect, flag);
   }
   //------------------------------------------------------------
   // <T>����Ͽ����ӡ�</T>
   MO_INLINE void DisconnectClear(){
      ClearBit(ENetRouterFlag_Disconnect);
   }
public:
   TSize Capacity();
   void Assign(TNetRouterFlagSet& set);
   void Parse(TCharC* pValue);
   void ParseValue(TCharC* pValue);
   TChar* ToString(TChar* pValue, TSize capacity);
   TFsText ToString();
};

//============================================================
// <T>·�ɱ�־ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumNetRouterFlag{
public:
   static ENetRouterFlag Parse(TCharC* pValue);
   static ENetRouterFlag ParseCode(TCharC* pValue);
   static TCharC* ToCode(ENetRouterFlag value);
   static TCharC* ToString(ENetRouterFlag value);
};

//============================================================
// <T>�ռ�ģʽö�ٶ��塣</T>
//
// @enum
//============================================================
enum ECrAllocMode{
   ECrAllocMode_Create         = 0, // ��̬����
   ECrAllocMode_Link           = 1, // ��̬����
};

//============================================================
// <T>�ռ�ģʽö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumCrAllocMode{
public:
   static ECrAllocMode Parse(TCharC* pValue);
   static ECrAllocMode ParseCode(TCharC* pValue);
   static TCharC* ToCode(ECrAllocMode value);
   static TCharC* ToString(ECrAllocMode value);
};

//============================================================
// <T>����״̬ö�ٶ��塣</T>
//
// @enum
//============================================================
enum EGmObjectStatus{
   EGmObjectStatus_Unknown        = 0, // δ֪
   EGmObjectStatus_Valid          = 1, // ��Ч
   EGmObjectStatus_Active         = 2, // ����
   EGmObjectStatus_Frozen         = 3, // ����
};

//============================================================
// <T>����״̬ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumGmObjectStatus{
public:
   static EGmObjectStatus Parse(TCharC* pValue);
   static EGmObjectStatus ParseCode(TCharC* pValue);
   static TCharC* ToCode(EGmObjectStatus value);
   static TCharC* ToString(EGmObjectStatus value);
};

//============================================================
// <T>���ĸ���ö�ٶ��塣</T>
//
// @enum
//============================================================
enum EGmObjectChange{
   EGmObjectChange_Unknown        = 0, // δ֪
   EGmObjectChange_Unchanged      = 1, // δ����
   EGmObjectChange_Create         = 2, // ����
   EGmObjectChange_Delete         = 3, // ɾ��
   EGmObjectChange_Change         = 4, // ����
   EGmObjectChange_Receive        = 5, // ���
};

//============================================================
// <T>���ĸ���ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumGmObjectChange{
public:
   static EGmObjectChange Parse(TCharC* pValue);
   static EGmObjectChange ParseCode(TCharC* pValue);
   static TCharC* ToCode(EGmObjectChange value);
   static TCharC* ToString(EGmObjectChange value);
};

//============================================================
// <T>�����־ö�ٶ��塣</T>
//
// @enum
//============================================================
enum EGmObjectFlag{
   EGmObjectFlag_Create         = 0, // ����
   EGmObjectFlag_Valid          = 1, // ��Ч
   EGmObjectFlag_Lock           = 2, // ����
};

//============================================================
// <T>�����־ö���ࡣ</T>
//
// @class
//============================================================
struct MO_CR_DECLARE TGmObjectFlagSet : TBitSet<TUint32>{
public:
   //------------------------------------------------------------
   // <T>��ô�����</T>
   MO_INLINE TBool IsCreate(){
      return GetBit(EGmObjectFlag_Create);
   }
   //------------------------------------------------------------
   // <T>��ô�����</T>
   MO_INLINE TBool IsNotCreate(){
      return !GetBit(EGmObjectFlag_Create);
   }
   //------------------------------------------------------------
   // <T>���ô�����</T>
   MO_INLINE void CreateSet(){
      return SetBit(EGmObjectFlag_Create);
   }
   //------------------------------------------------------------
   // <T>��ת������</T>
   MO_INLINE void CreateInverse(){
      InverseBit(EGmObjectFlag_Create);
   }
   //------------------------------------------------------------
   // <T>�޸Ĵ�����</T>
   MO_INLINE void CreateModify(TBool flag){
      ModifyBit(EGmObjectFlag_Create, flag);
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE void CreateClear(){
      ClearBit(EGmObjectFlag_Create);
   }
public:
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE TBool IsValid(){
      return GetBit(EGmObjectFlag_Valid);
   }
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE TBool IsNotValid(){
      return !GetBit(EGmObjectFlag_Valid);
   }
   //------------------------------------------------------------
   // <T>������Ч��</T>
   MO_INLINE void ValidSet(){
      return SetBit(EGmObjectFlag_Valid);
   }
   //------------------------------------------------------------
   // <T>��ת��Ч��</T>
   MO_INLINE void ValidInverse(){
      InverseBit(EGmObjectFlag_Valid);
   }
   //------------------------------------------------------------
   // <T>�޸���Ч��</T>
   MO_INLINE void ValidModify(TBool flag){
      ModifyBit(EGmObjectFlag_Valid, flag);
   }
   //------------------------------------------------------------
   // <T>�����Ч��</T>
   MO_INLINE void ValidClear(){
      ClearBit(EGmObjectFlag_Valid);
   }
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TBool IsLock(){
      return GetBit(EGmObjectFlag_Lock);
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TBool IsNotLock(){
      return !GetBit(EGmObjectFlag_Lock);
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void LockSet(){
      return SetBit(EGmObjectFlag_Lock);
   }
   //------------------------------------------------------------
   // <T>��ת������</T>
   MO_INLINE void LockInverse(){
      InverseBit(EGmObjectFlag_Lock);
   }
   //------------------------------------------------------------
   // <T>�޸�������</T>
   MO_INLINE void LockModify(TBool flag){
      ModifyBit(EGmObjectFlag_Lock, flag);
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE void LockClear(){
      ClearBit(EGmObjectFlag_Lock);
   }
public:
   TSize Capacity();
   void Assign(TGmObjectFlagSet& set);
   void Parse(TCharC* pValue);
   void ParseValue(TCharC* pValue);
   TChar* ToString(TChar* pValue, TSize capacity);
   TFsText ToString();
};

//============================================================
// <T>�����־ö���ࡣ</T>
//
// @reference
//============================================================
class MO_CR_DECLARE REnumGmObjectFlag{
public:
   static EGmObjectFlag Parse(TCharC* pValue);
   static EGmObjectFlag ParseCode(TCharC* pValue);
   static TCharC* ToCode(EGmObjectFlag value);
   static TCharC* ToString(EGmObjectFlag value);
};

MO_NAMESPACE_END

#endif // __MO_CR_CONSTANT_H__
