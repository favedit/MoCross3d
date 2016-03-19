//============================================================
// <T>ϵͳ����ö�ٶ��塣</T>
//
// @version 1.0.1
// @auto ����������Ĵ��룬�����޸������ֶ��޸ı���ĵط��޸ġ�
//============================================================
#include "MoCrConstant.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ�����������Э��ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetProtocol REnumNetProtocol::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetProtocol)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�λ��
   if(text.Equals(TC("Unknown"))){
      return ENetProtocol_Unknown;
   }
   // �ж��Ƿ�����
   if(text.Equals(TC("Data"))){
      return ENetProtocol_Data;
   }
   // �ж��Ƿ���Ϣ
   if(text.Equals(TC("Message"))){
      return ENetProtocol_Message;
   }
   // �ж��Ƿ�·��
   if(text.Equals(TC("Router"))){
      return ENetProtocol_Router;
   }
   // �ж��Ƿ���
   if(text.Equals(TC("Transfer"))){
      return ENetProtocol_Transfer;
   }
   // �ж��Ƿ����ݰ�
   if(text.Equals(TC("Package"))){
      return ENetProtocol_Package;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetProtocol, value=%s)"), pValue);
   return (ENetProtocol)0;
}

//============================================================
// <T>���ݴ����������Э��ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetProtocol REnumNetProtocol::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetProtocol, code=%s)"), pCode);
   return (ENetProtocol)0;
}

//============================================================
// <T>���������Э��ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetProtocol::ToCode(ENetProtocol value){
   return TC("Unknown");
}

//============================================================
// <T>���������Э��ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetProtocol::ToString(ENetProtocol value){
   // ���λ��
   if(ENetProtocol_Unknown == value){
      return TC("Unknown");
   }
   // �������
   if(ENetProtocol_Data == value){
      return TC("Data");
   }
   // �����Ϣ
   if(ENetProtocol_Message == value){
      return TC("Message");
   }
   // ���·��
   if(ENetProtocol_Router == value){
      return TC("Router");
   }
   // ��ô���
   if(ENetProtocol_Transfer == value){
      return TC("Transfer");
   }
   // ������ݰ�
   if(ENetProtocol_Package == value){
      return TC("Package");
   }
   return TC("Unknown");
}

//============================================================
// <T>�������������</T>
//
// @return ��ʽ���ַ���
//============================================================
TSize TNetSignSet::Capacity(){
   return sizeof(TUint32);
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetSignSet::Assign(TNetSignSet& set){
   _value = set.Get();
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetSignSet::Parse(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals(TC("Unknown"))){
         SetBit(ENetSign_Unknown);
         continue;
      }
      if(code.Equals(TC("Valid"))){
         SetBit(ENetSign_Valid);
         continue;
      }
      if(code.Equals(TC("Client"))){
         SetBit(ENetSign_Client);
         continue;
      }
      if(code.Equals(TC("Debug"))){
         SetBit(ENetSign_Debug);
         continue;
      }
      if(code.Equals(TC("Analysis"))){
         SetBit(ENetSign_Analysis);
         continue;
      }
      if(code.Equals(TC("Track"))){
         SetBit(ENetSign_Track);
         continue;
      }
   }
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetSignSet::ParseValue(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals(TC("0"))){
         SetBit(ENetSign_Unknown);
         continue;
      }
      if(code.Equals(TC("1"))){
         SetBit(ENetSign_Valid);
         continue;
      }
      if(code.Equals(TC("2"))){
         SetBit(ENetSign_Client);
         continue;
      }
      if(code.Equals(TC("3"))){
         SetBit(ENetSign_Debug);
         continue;
      }
      if(code.Equals(TC("4"))){
         SetBit(ENetSign_Analysis);
         continue;
      }
      if(code.Equals(TC("5"))){
         SetBit(ENetSign_Track);
         continue;
      }
   }
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ���ݳ���
// @return ��ʽ���ַ���
//============================================================
TChar* TNetSignSet::ToString(TChar* pValue, TSize capacity){
   TStringRefer text(pValue, capacity);
   text.Append(GetBit(ENetSign_Unknown) ? TC("") : TC("_"));
   text.Append(GetBit(ENetSign_Valid) ? TC("") : TC("_"));
   text.Append(GetBit(ENetSign_Client) ? TC("") : TC("_"));
   text.Append(GetBit(ENetSign_Debug) ? TC("") : TC("_"));
   text.Append(GetBit(ENetSign_Analysis) ? TC("") : TC("_"));
   text.Append(GetBit(ENetSign_Track) ? TC("") : TC("_"));
   return pValue;
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @return ��ʽ���ַ���
//============================================================
TFsText TNetSignSet::ToString(){
   TFsText text;
   ToString(text.Memory(), text.Size());
   return text;
}

//============================================================
// <T>�����ַ�������������־ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetSign REnumNetSign::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetSign)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals(TC("Unknown"))){
      return ENetSign_Unknown;
   }
   // �ж��Ƿ���Ч
   if(text.Equals(TC("Valid"))){
      return ENetSign_Valid;
   }
   // �ж��Ƿ�ͻ�
   if(text.Equals(TC("Client"))){
      return ENetSign_Client;
   }
   // �ж��Ƿ����
   if(text.Equals(TC("Debug"))){
      return ENetSign_Debug;
   }
   // �ж��Ƿ����
   if(text.Equals(TC("Analysis"))){
      return ENetSign_Analysis;
   }
   // �ж��Ƿ����
   if(text.Equals(TC("Track"))){
      return ENetSign_Track;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetSign, value=%s)"), pValue);
   return (ENetSign)0;
}

//============================================================
// <T>���ݴ������������־ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetSign REnumNetSign::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetSign, code=%s)"), pCode);
   return (ENetSign)0;
}

//============================================================
// <T>�����������־ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetSign::ToCode(ENetSign value){
   return TC("Unknown");
}

//============================================================
// <T>�����������־ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetSign::ToString(ENetSign value){
   // ���δ֪
   if(ENetSign_Unknown == value){
      return TC("Unknown");
   }
   // �����Ч
   if(ENetSign_Valid == value){
      return TC("Valid");
   }
   // ��ÿͻ�
   if(ENetSign_Client == value){
      return TC("Client");
   }
   // ��õ���
   if(ENetSign_Debug == value){
      return TC("Debug");
   }
   // ��÷���
   if(ENetSign_Analysis == value){
      return TC("Analysis");
   }
   // ��ø���
   if(ENetSign_Track == value){
      return TC("Track");
   }
   return TC("Unknown");
}

//============================================================
// <T>�����ַ��������Ϣ����ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetMessage REnumNetMessage::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetMessage)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals(TC("Unknown"))){
      return ENetMessage_Unknown;
   }
   // �ж��Ƿ�����
   if(text.Equals(TC("Request"))){
      return ENetMessage_Request;
   }
   // �ж��Ƿ�Ӧ��
   if(text.Equals(TC("Response"))){
      return ENetMessage_Response;
   }
   // �ж��Ƿ�֪ͨ
   if(text.Equals(TC("Notify"))){
      return ENetMessage_Notify;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetMessage, value=%s)"), pValue);
   return (ENetMessage)0;
}

//============================================================
// <T>���ݴ�������Ϣ����ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetMessage REnumNetMessage::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetMessage, code=%s)"), pCode);
   return (ENetMessage)0;
}

//============================================================
// <T>������Ϣ����ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetMessage::ToCode(ENetMessage value){
   return TC("Unknown");
}

//============================================================
// <T>������Ϣ����ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetMessage::ToString(ENetMessage value){
   // ���δ֪
   if(ENetMessage_Unknown == value){
      return TC("Unknown");
   }
   // �������
   if(ENetMessage_Request == value){
      return TC("Request");
   }
   // ���Ӧ��
   if(ENetMessage_Response == value){
      return TC("Response");
   }
   // ���֪ͨ
   if(ENetMessage_Notify == value){
      return TC("Notify");
   }
   return TC("Unknown");
}

//============================================================
// <T>�������������</T>
//
// @return ��ʽ���ַ���
//============================================================
TSize TNetMessageSignSet::Capacity(){
   return sizeof(TUint32);
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetMessageSignSet::Assign(TNetMessageSignSet& set){
   _value = set.Get();
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetMessageSignSet::Parse(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals(TC("Unknown"))){
         SetBit(ENetMessageSign_Unknown);
         continue;
      }
      if(code.Equals(TC("Tcp"))){
         SetBit(ENetMessageSign_Tcp);
         continue;
      }
      if(code.Equals(TC("Udp"))){
         SetBit(ENetMessageSign_Udp);
         continue;
      }
      if(code.Equals(TC("Thread"))){
         SetBit(ENetMessageSign_Thread);
         continue;
      }
   }
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetMessageSignSet::ParseValue(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals(TC("0"))){
         SetBit(ENetMessageSign_Unknown);
         continue;
      }
      if(code.Equals(TC("1"))){
         SetBit(ENetMessageSign_Tcp);
         continue;
      }
      if(code.Equals(TC("2"))){
         SetBit(ENetMessageSign_Udp);
         continue;
      }
      if(code.Equals(TC("3"))){
         SetBit(ENetMessageSign_Thread);
         continue;
      }
   }
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ���ݳ���
// @return ��ʽ���ַ���
//============================================================
TChar* TNetMessageSignSet::ToString(TChar* pValue, TSize capacity){
   TStringRefer text(pValue, capacity);
   text.Append(GetBit(ENetMessageSign_Unknown) ? TC("") : TC("_"));
   text.Append(GetBit(ENetMessageSign_Tcp) ? TC("") : TC("_"));
   text.Append(GetBit(ENetMessageSign_Udp) ? TC("") : TC("_"));
   text.Append(GetBit(ENetMessageSign_Thread) ? TC("") : TC("_"));
   return pValue;
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @return ��ʽ���ַ���
//============================================================
TFsText TNetMessageSignSet::ToString(){
   TFsText text;
   ToString(text.Memory(), text.Size());
   return text;
}

//============================================================
// <T>�����ַ��������Ϣ��־ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetMessageSign REnumNetMessageSign::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetMessageSign)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals(TC("Unknown"))){
      return ENetMessageSign_Unknown;
   }
   // �ж��Ƿ�TCP֧��
   if(text.Equals(TC("Tcp"))){
      return ENetMessageSign_Tcp;
   }
   // �ж��Ƿ�UDP֧��
   if(text.Equals(TC("Udp"))){
      return ENetMessageSign_Udp;
   }
   // �ж��Ƿ��߳�֧��
   if(text.Equals(TC("Thread"))){
      return ENetMessageSign_Thread;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetMessageSign, value=%s)"), pValue);
   return (ENetMessageSign)0;
}

//============================================================
// <T>���ݴ�������Ϣ��־ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetMessageSign REnumNetMessageSign::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetMessageSign, code=%s)"), pCode);
   return (ENetMessageSign)0;
}

//============================================================
// <T>������Ϣ��־ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetMessageSign::ToCode(ENetMessageSign value){
   return TC("Unknown");
}

//============================================================
// <T>������Ϣ��־ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetMessageSign::ToString(ENetMessageSign value){
   // ���δ֪
   if(ENetMessageSign_Unknown == value){
      return TC("Unknown");
   }
   // ���TCP֧��
   if(ENetMessageSign_Tcp == value){
      return TC("Tcp");
   }
   // ���UDP֧��
   if(ENetMessageSign_Udp == value){
      return TC("Udp");
   }
   // ����߳�֧��
   if(ENetMessageSign_Thread == value){
      return TC("Thread");
   }
   return TC("Unknown");
}

//============================================================
// <T>�����ַ������������Ϣ��������ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetMessageService REnumNetMessageService::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetMessageService)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ��߼�
   if(text.Equals(TC("Logic"))){
      return ENetMessageService_Logic;
   }
   // �ж��Ƿ��¼
   if(text.Equals(TC("Login"))){
      return ENetMessageService_Login;
   }
   // �ж��Ƿ�ˢ��
   if(text.Equals(TC("Refresh"))){
      return ENetMessageService_Refresh;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetMessageService, value=%s)"), pValue);
   return (ENetMessageService)0;
}

//============================================================
// <T>���ݴ�����������Ϣ��������ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetMessageService REnumNetMessageService::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetMessageService, code=%s)"), pCode);
   return (ENetMessageService)0;
}

//============================================================
// <T>����������Ϣ��������ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetMessageService::ToCode(ENetMessageService value){
   return TC("Unknown");
}

//============================================================
// <T>����������Ϣ��������ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetMessageService::ToString(ENetMessageService value){
   // ����߼�
   if(ENetMessageService_Logic == value){
      return TC("Logic");
   }
   // ��õ�¼
   if(ENetMessageService_Login == value){
      return TC("Login");
   }
   // ���ˢ��
   if(ENetMessageService_Refresh == value){
      return TC("Refresh");
   }
   return TC("Unknown");
}

//============================================================
// <T>�����ַ�����������ն�ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetTerminal REnumNetTerminal::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetTerminal)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals(TC("Unknown"))){
      return ENetTerminal_Unknown;
   }
   // �ж��Ƿ�ͻ���
   if(text.Equals(TC("Client"))){
      return ENetTerminal_Client;
   }
   // �ж��Ƿ����������
   if(text.Equals(TC("ServerTransfer"))){
      return ENetTerminal_ServerTransfer;
   }
   // �ж��Ƿ�ȫ�ִ���
   if(text.Equals(TC("GlobalTransfer"))){
      return ENetTerminal_GlobalTransfer;
   }
   // �ж��Ƿ�ȫ�ִ���
   if(text.Equals(TC("GlobalProxy"))){
      return ENetTerminal_GlobalProxy;
   }
   // �ж��Ƿ�ȫ������
   if(text.Equals(TC("GlobalDomain"))){
      return ENetTerminal_GlobalDomain;
   }
   // �ж��Ƿ�ȫ�ֵ�½
   if(text.Equals(TC("GlobalLogin"))){
      return ENetTerminal_GlobalLogin;
   }
   // �ж��Ƿ�ȫ������
   if(text.Equals(TC("GlobalGate"))){
      return ENetTerminal_GlobalGate;
   }
   // �ж��Ƿ�ȫ�ִ洢
   if(text.Equals(TC("GlobalStorage"))){
      return ENetTerminal_GlobalStorage;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GameProxy"))){
      return ENetTerminal_GameProxy;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GameDomain"))){
      return ENetTerminal_GameDomain;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GameGate"))){
      return ENetTerminal_GameGate;
   }
   // �ж��Ƿ���Ϸ��¼
   if(text.Equals(TC("GameLogin"))){
      return ENetTerminal_GameLogin;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GameScene"))){
      return ENetTerminal_GameScene;
   }
   // �ж��Ƿ���Ϸս��
   if(text.Equals(TC("GameBattle"))){
      return ENetTerminal_GameBattle;
   }
   // �ж��Ƿ���Ϸ�洢
   if(text.Equals(TC("GameStorage"))){
      return ENetTerminal_GameStorage;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GameChat"))){
      return ENetTerminal_GameChat;
   }
   // �ж��Ƿ���Ϸ��־
   if(text.Equals(TC("GameLogger"))){
      return ENetTerminal_GameLogger;
   }
   // �ж��Ƿ������Խӷ�����
   if(text.Equals(TC("GameWebInterface"))){
      return ENetTerminal_GameWebInterface;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetTerminal, value=%s)"), pValue);
   return (ENetTerminal)0;
}

//============================================================
// <T>���ݴ����������ն�ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetTerminal REnumNetTerminal::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   // �ж��Ƿ�δ֪
   if(text.Equals(TC("UNK"))){
      return ENetTerminal_Unknown;
   }
   // �ж��Ƿ�ͻ���
   if(text.Equals(TC("CLT"))){
      return ENetTerminal_Client;
   }
   // �ж��Ƿ����������
   if(text.Equals(TC("STS"))){
      return ENetTerminal_ServerTransfer;
   }
   // �ж��Ƿ�ȫ�ִ���
   if(text.Equals(TC("ATS"))){
      return ENetTerminal_GlobalTransfer;
   }
   // �ж��Ƿ�ȫ�ִ���
   if(text.Equals(TC("APX"))){
      return ENetTerminal_GlobalProxy;
   }
   // �ж��Ƿ�ȫ������
   if(text.Equals(TC("ADM"))){
      return ENetTerminal_GlobalDomain;
   }
   // �ж��Ƿ�ȫ�ֵ�½
   if(text.Equals(TC("ALG"))){
      return ENetTerminal_GlobalLogin;
   }
   // �ж��Ƿ�ȫ������
   if(text.Equals(TC("AGT"))){
      return ENetTerminal_GlobalGate;
   }
   // �ж��Ƿ�ȫ�ִ洢
   if(text.Equals(TC("ASR"))){
      return ENetTerminal_GlobalStorage;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GPX"))){
      return ENetTerminal_GameProxy;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GDM"))){
      return ENetTerminal_GameDomain;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GGT"))){
      return ENetTerminal_GameGate;
   }
   // �ж��Ƿ���Ϸ��¼
   if(text.Equals(TC("GLG"))){
      return ENetTerminal_GameLogin;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GSC"))){
      return ENetTerminal_GameScene;
   }
   // �ж��Ƿ���Ϸս��
   if(text.Equals(TC("GBT"))){
      return ENetTerminal_GameBattle;
   }
   // �ж��Ƿ���Ϸ�洢
   if(text.Equals(TC("GSR"))){
      return ENetTerminal_GameStorage;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals(TC("GCT"))){
      return ENetTerminal_GameChat;
   }
   // �ж��Ƿ���Ϸ��־
   if(text.Equals(TC("GLO"))){
      return ENetTerminal_GameLogger;
   }
   // �ж��Ƿ������Խӷ�����
   if(text.Equals(TC("GWI"))){
      return ENetTerminal_GameWebInterface;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetTerminal, code=%s)"), pCode);
   return (ENetTerminal)0;
}

//============================================================
// <T>���������ն�ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetTerminal::ToCode(ENetTerminal value){
   // ���δ֪
   if(ENetTerminal_Unknown == value){
      return TC("UNK");
   }
   // ��ÿͻ���
   if(ENetTerminal_Client == value){
      return TC("CLT");
   }
   // ��÷���������
   if(ENetTerminal_ServerTransfer == value){
      return TC("STS");
   }
   // ���ȫ�ִ���
   if(ENetTerminal_GlobalTransfer == value){
      return TC("ATS");
   }
   // ���ȫ�ִ���
   if(ENetTerminal_GlobalProxy == value){
      return TC("APX");
   }
   // ���ȫ������
   if(ENetTerminal_GlobalDomain == value){
      return TC("ADM");
   }
   // ���ȫ�ֵ�½
   if(ENetTerminal_GlobalLogin == value){
      return TC("ALG");
   }
   // ���ȫ������
   if(ENetTerminal_GlobalGate == value){
      return TC("AGT");
   }
   // ���ȫ�ִ洢
   if(ENetTerminal_GlobalStorage == value){
      return TC("ASR");
   }
   // �����Ϸ����
   if(ENetTerminal_GameProxy == value){
      return TC("GPX");
   }
   // �����Ϸ����
   if(ENetTerminal_GameDomain == value){
      return TC("GDM");
   }
   // �����Ϸ����
   if(ENetTerminal_GameGate == value){
      return TC("GGT");
   }
   // �����Ϸ��¼
   if(ENetTerminal_GameLogin == value){
      return TC("GLG");
   }
   // �����Ϸ����
   if(ENetTerminal_GameScene == value){
      return TC("GSC");
   }
   // �����Ϸս��
   if(ENetTerminal_GameBattle == value){
      return TC("GBT");
   }
   // �����Ϸ�洢
   if(ENetTerminal_GameStorage == value){
      return TC("GSR");
   }
   // �����Ϸ����
   if(ENetTerminal_GameChat == value){
      return TC("GCT");
   }
   // �����Ϸ��־
   if(ENetTerminal_GameLogger == value){
      return TC("GLO");
   }
   // ��������Խӷ�����
   if(ENetTerminal_GameWebInterface == value){
      return TC("GWI");
   }
   return TC("Unknown");
}

//============================================================
// <T>���������ն�ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetTerminal::ToString(ENetTerminal value){
   // ���δ֪
   if(ENetTerminal_Unknown == value){
      return TC("Unknown");
   }
   // ��ÿͻ���
   if(ENetTerminal_Client == value){
      return TC("Client");
   }
   // ��÷���������
   if(ENetTerminal_ServerTransfer == value){
      return TC("ServerTransfer");
   }
   // ���ȫ�ִ���
   if(ENetTerminal_GlobalTransfer == value){
      return TC("GlobalTransfer");
   }
   // ���ȫ�ִ���
   if(ENetTerminal_GlobalProxy == value){
      return TC("GlobalProxy");
   }
   // ���ȫ������
   if(ENetTerminal_GlobalDomain == value){
      return TC("GlobalDomain");
   }
   // ���ȫ�ֵ�½
   if(ENetTerminal_GlobalLogin == value){
      return TC("GlobalLogin");
   }
   // ���ȫ������
   if(ENetTerminal_GlobalGate == value){
      return TC("GlobalGate");
   }
   // ���ȫ�ִ洢
   if(ENetTerminal_GlobalStorage == value){
      return TC("GlobalStorage");
   }
   // �����Ϸ����
   if(ENetTerminal_GameProxy == value){
      return TC("GameProxy");
   }
   // �����Ϸ����
   if(ENetTerminal_GameDomain == value){
      return TC("GameDomain");
   }
   // �����Ϸ����
   if(ENetTerminal_GameGate == value){
      return TC("GameGate");
   }
   // �����Ϸ��¼
   if(ENetTerminal_GameLogin == value){
      return TC("GameLogin");
   }
   // �����Ϸ����
   if(ENetTerminal_GameScene == value){
      return TC("GameScene");
   }
   // �����Ϸս��
   if(ENetTerminal_GameBattle == value){
      return TC("GameBattle");
   }
   // �����Ϸ�洢
   if(ENetTerminal_GameStorage == value){
      return TC("GameStorage");
   }
   // �����Ϸ����
   if(ENetTerminal_GameChat == value){
      return TC("GameChat");
   }
   // �����Ϸ��־
   if(ENetTerminal_GameLogger == value){
      return TC("GameLogger");
   }
   // ��������Խӷ�����
   if(ENetTerminal_GameWebInterface == value){
      return TC("GameWebInterface");
   }
   return TC("Unknown");
}

//============================================================
// <T>�������������</T>
//
// @return ��ʽ���ַ���
//============================================================
TSize TNetRouterFlagSet::Capacity(){
   return sizeof(TUint32);
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetRouterFlagSet::Assign(TNetRouterFlagSet& set){
   _value = set.Get();
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetRouterFlagSet::Parse(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals(TC("Valid"))){
         SetBit(ENetRouterFlag_Valid);
         continue;
      }
      if(code.Equals(TC("Disconnect"))){
         SetBit(ENetRouterFlag_Disconnect);
         continue;
      }
   }
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetRouterFlagSet::ParseValue(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals(TC("0"))){
         SetBit(ENetRouterFlag_Valid);
         continue;
      }
      if(code.Equals(TC("1"))){
         SetBit(ENetRouterFlag_Disconnect);
         continue;
      }
   }
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ���ݳ���
// @return ��ʽ���ַ���
//============================================================
TChar* TNetRouterFlagSet::ToString(TChar* pValue, TSize capacity){
   TStringRefer text(pValue, capacity);
   text.Append(GetBit(ENetRouterFlag_Valid) ? TC("") : TC("_"));
   text.Append(GetBit(ENetRouterFlag_Disconnect) ? TC("") : TC("_"));
   return pValue;
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @return ��ʽ���ַ���
//============================================================
TFsText TNetRouterFlagSet::ToString(){
   TFsText text;
   ToString(text.Memory(), text.Size());
   return text;
}

//============================================================
// <T>�����ַ������·�ɱ�־ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetRouterFlag REnumNetRouterFlag::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetRouterFlag)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ���Ч
   if(text.Equals(TC("Valid"))){
      return ENetRouterFlag_Valid;
   }
   // �ж��Ƿ�Ͽ�����
   if(text.Equals(TC("Disconnect"))){
      return ENetRouterFlag_Disconnect;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetRouterFlag, value=%s)"), pValue);
   return (ENetRouterFlag)0;
}

//============================================================
// <T>���ݴ�����·�ɱ�־ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetRouterFlag REnumNetRouterFlag::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ENetRouterFlag, code=%s)"), pCode);
   return (ENetRouterFlag)0;
}

//============================================================
// <T>����·�ɱ�־ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetRouterFlag::ToCode(ENetRouterFlag value){
   return TC("Unknown");
}

//============================================================
// <T>����·�ɱ�־ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetRouterFlag::ToString(ENetRouterFlag value){
   // �����Ч
   if(ENetRouterFlag_Valid == value){
      return TC("Valid");
   }
   // ��öϿ�����
   if(ENetRouterFlag_Disconnect == value){
      return TC("Disconnect");
   }
   return TC("Unknown");
}

//============================================================
// <T>�����ַ�������ռ�ģʽö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ECrAllocMode REnumCrAllocMode::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ECrAllocMode)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�̬����
   if(text.Equals(TC("Create"))){
      return ECrAllocMode_Create;
   }
   // �ж��Ƿ�̬����
   if(text.Equals(TC("Link"))){
      return ECrAllocMode_Link;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ECrAllocMode, value=%s)"), pValue);
   return (ECrAllocMode)0;
}

//============================================================
// <T>���ݴ������ռ�ģʽö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ECrAllocMode REnumCrAllocMode::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=ECrAllocMode, code=%s)"), pCode);
   return (ECrAllocMode)0;
}

//============================================================
// <T>�����ռ�ģʽö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumCrAllocMode::ToCode(ECrAllocMode value){
   return TC("Unknown");
}

//============================================================
// <T>�����ռ�ģʽö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumCrAllocMode::ToString(ECrAllocMode value){
   // ��ö�̬����
   if(ECrAllocMode_Create == value){
      return TC("Create");
   }
   // ��þ�̬����
   if(ECrAllocMode_Link == value){
      return TC("Link");
   }
   return TC("Unknown");
}

//============================================================
// <T>�����ַ�����ö���״̬ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
EGmObjectStatus REnumGmObjectStatus::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (EGmObjectStatus)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals(TC("Unknown"))){
      return EGmObjectStatus_Unknown;
   }
   // �ж��Ƿ���Ч
   if(text.Equals(TC("Valid"))){
      return EGmObjectStatus_Valid;
   }
   // �ж��Ƿ񼤻�
   if(text.Equals(TC("Active"))){
      return EGmObjectStatus_Active;
   }
   // �ж��Ƿ񶳽�
   if(text.Equals(TC("Frozen"))){
      return EGmObjectStatus_Frozen;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=EGmObjectStatus, value=%s)"), pValue);
   return (EGmObjectStatus)0;
}

//============================================================
// <T>���ݴ����ö���״̬ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
EGmObjectStatus REnumGmObjectStatus::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=EGmObjectStatus, code=%s)"), pCode);
   return (EGmObjectStatus)0;
}

//============================================================
// <T>���ݶ���״̬ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumGmObjectStatus::ToCode(EGmObjectStatus value){
   return TC("Unknown");
}

//============================================================
// <T>���ݶ���״̬ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumGmObjectStatus::ToString(EGmObjectStatus value){
   // ���δ֪
   if(EGmObjectStatus_Unknown == value){
      return TC("Unknown");
   }
   // �����Ч
   if(EGmObjectStatus_Valid == value){
      return TC("Valid");
   }
   // ��ü���
   if(EGmObjectStatus_Active == value){
      return TC("Active");
   }
   // ��ö���
   if(EGmObjectStatus_Frozen == value){
      return TC("Frozen");
   }
   return TC("Unknown");
}

//============================================================
// <T>�����ַ�����ø��ĸ���ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
EGmObjectChange REnumGmObjectChange::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (EGmObjectChange)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals(TC("Unknown"))){
      return EGmObjectChange_Unknown;
   }
   // �ж��Ƿ�δ����
   if(text.Equals(TC("Unchanged"))){
      return EGmObjectChange_Unchanged;
   }
   // �ж��Ƿ񴴽�
   if(text.Equals(TC("Create"))){
      return EGmObjectChange_Create;
   }
   // �ж��Ƿ�ɾ��
   if(text.Equals(TC("Delete"))){
      return EGmObjectChange_Delete;
   }
   // �ж��Ƿ����
   if(text.Equals(TC("Change"))){
      return EGmObjectChange_Change;
   }
   // �ж��Ƿ���
   if(text.Equals(TC("Receive"))){
      return EGmObjectChange_Receive;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=EGmObjectChange, value=%s)"), pValue);
   return (EGmObjectChange)0;
}

//============================================================
// <T>���ݴ����ø��ĸ���ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
EGmObjectChange REnumGmObjectChange::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=EGmObjectChange, code=%s)"), pCode);
   return (EGmObjectChange)0;
}

//============================================================
// <T>���ݸ��ĸ���ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumGmObjectChange::ToCode(EGmObjectChange value){
   return TC("Unknown");
}

//============================================================
// <T>���ݸ��ĸ���ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumGmObjectChange::ToString(EGmObjectChange value){
   // ���δ֪
   if(EGmObjectChange_Unknown == value){
      return TC("Unknown");
   }
   // ���δ����
   if(EGmObjectChange_Unchanged == value){
      return TC("Unchanged");
   }
   // ��ô���
   if(EGmObjectChange_Create == value){
      return TC("Create");
   }
   // ���ɾ��
   if(EGmObjectChange_Delete == value){
      return TC("Delete");
   }
   // ��ø���
   if(EGmObjectChange_Change == value){
      return TC("Change");
   }
   // ��û��
   if(EGmObjectChange_Receive == value){
      return TC("Receive");
   }
   return TC("Unknown");
}

//============================================================
// <T>�������������</T>
//
// @return ��ʽ���ַ���
//============================================================
TSize TGmObjectFlagSet::Capacity(){
   return sizeof(TUint32);
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TGmObjectFlagSet::Assign(TGmObjectFlagSet& set){
   _value = set.Get();
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TGmObjectFlagSet::Parse(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals(TC("Create"))){
         SetBit(EGmObjectFlag_Create);
         continue;
      }
      if(code.Equals(TC("Valid"))){
         SetBit(EGmObjectFlag_Valid);
         continue;
      }
      if(code.Equals(TC("Lock"))){
         SetBit(EGmObjectFlag_Lock);
         continue;
      }
   }
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TGmObjectFlagSet::ParseValue(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals(TC("0"))){
         SetBit(EGmObjectFlag_Create);
         continue;
      }
      if(code.Equals(TC("1"))){
         SetBit(EGmObjectFlag_Valid);
         continue;
      }
      if(code.Equals(TC("2"))){
         SetBit(EGmObjectFlag_Lock);
         continue;
      }
   }
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ���ݳ���
// @return ��ʽ���ַ���
//============================================================
TChar* TGmObjectFlagSet::ToString(TChar* pValue, TSize capacity){
   TStringRefer text(pValue, capacity);
   text.Append(GetBit(EGmObjectFlag_Create) ? TC("C") : TC("_"));
   text.Append(GetBit(EGmObjectFlag_Valid) ? TC("V") : TC("_"));
   text.Append(GetBit(EGmObjectFlag_Lock) ? TC("L") : TC("_"));
   return pValue;
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @return ��ʽ���ַ���
//============================================================
TFsText TGmObjectFlagSet::ToString(){
   TFsText text;
   ToString(text.Memory(), text.Size());
   return text;
}

//============================================================
// <T>�����ַ�����ö����־ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
EGmObjectFlag REnumGmObjectFlag::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (EGmObjectFlag)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ񴴽�
   if(text.Equals(TC("Create"))){
      return EGmObjectFlag_Create;
   }
   // �ж��Ƿ���Ч
   if(text.Equals(TC("Valid"))){
      return EGmObjectFlag_Valid;
   }
   // �ж��Ƿ�����
   if(text.Equals(TC("Lock"))){
      return EGmObjectFlag_Lock;
   }
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=EGmObjectFlag, value=%s)"), pValue);
   return (EGmObjectFlag)0;
}

//============================================================
// <T>���ݴ����ö����־ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
EGmObjectFlag REnumGmObjectFlag::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL(TC("Unknown enum value. (enum=EGmObjectFlag, code=%s)"), pCode);
   return (EGmObjectFlag)0;
}

//============================================================
// <T>���ݶ����־ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumGmObjectFlag::ToCode(EGmObjectFlag value){
   return TC("Unknown");
}

//============================================================
// <T>���ݶ����־ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumGmObjectFlag::ToString(EGmObjectFlag value){
   // ��ô���
   if(EGmObjectFlag_Create == value){
      return TC("Create");
   }
   // �����Ч
   if(EGmObjectFlag_Valid == value){
      return TC("Valid");
   }
   // �������
   if(EGmObjectFlag_Lock == value){
      return TC("Lock");
   }
   return TC("Unknown");
}

MO_NAMESPACE_END
