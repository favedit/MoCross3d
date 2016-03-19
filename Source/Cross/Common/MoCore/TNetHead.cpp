#include "MoCrNetMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������������ͷ��</T>
//============================================================
TNetHead::TNetHead(){
   RType<SNetHead>::Clear(&_data);
}

//============================================================
// <T>����ͷ��Ϣ��</T>
//
// @param head ͷ��Ϣ
//============================================================
void TNetHead::Assign(TNetHead& head){
   _data = head.Data();
}

//============================================================
// <T>���л��ڲ����ݵ���������</T>
//
// @param pMemory ����ָ��
// @return ���л������ݴ�С
//============================================================
TInt TNetHead::Serialize(TAny* pMemory){
   memcpy(pMemory, &_data, sizeof(SNetHead));
   return sizeof(SNetHead);
}

//============================================================
// <T>�����л����������ڲ����ݡ�</T>
//
// @param pMessage ��Ϣ����
// @return �����л������ݴ�С
//============================================================
TInt TNetHead::Unserialize(TAnyC* pMemory){
   memcpy(&_data, pMemory, sizeof(SNetHead));
   return sizeof(SNetHead);
}

MO_NAMESPACE_END
