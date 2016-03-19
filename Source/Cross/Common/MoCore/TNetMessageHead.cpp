#include "MoCrNetMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����Ϣ���ơ�</T>
//
// @return ��Ϣ����
//============================================================
TNetMessageHead::TNetMessageHead(){
   RType<SNetMessageHead>::Clear(&_data);
}

//============================================================
TCharC* TNetMessageHead::CodeName(){
   return RNetMessageFactory::CodeName(_data.code);
}

//============================================================
void TNetMessageHead::Continue(TNetMessageHead& head){
   _data.command = head.Command();
}

//============================================================
void TNetMessageHead::Response(TNetMessageHead& head){
   _data.command = head.Command();
}

//============================================================
// <T>����ָ����Ϣ�ڵ��������ݡ�</T>
//
// @param pMessage ��Ϣ����
//============================================================
void TNetMessageHead::Assign(TNetMessageHead& head){
   _data = head.Data();
}

//============================================================
// <T>���л��ڲ����ݵ���������</T>
//
// @param pMessage ��Ϣ����
//============================================================
TInt TNetMessageHead::Serialize(TAny* pMemory){
   memcpy(pMemory, &_data, sizeof(SNetMessageHead));
   return sizeof(SNetMessageHead);
}

//============================================================
// <T>�����л����������ڲ����ݡ�</T>
//
// @param pMessage ��Ϣ����
//============================================================
TInt TNetMessageHead::Unserialize(TAnyC* pMemory){
   memcpy(&_data, pMemory, sizeof(SNetMessageHead));
   return sizeof(SNetMessageHead);
}

MO_NAMESPACE_END
