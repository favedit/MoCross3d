#include "MoFbxResource.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>������Դ����</T>
//============================================================
FFbxResourceComponent::FFbxResourceComponent() {
}

//============================================================
// <T>������Դ����</T>
//============================================================
FFbxResourceComponent::~FFbxResourceComponent() {
}

//============================================================
// <T>���л��ڲ����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FFbxResourceComponent::Serialize(IDataOutput * pOutput){
   FFbxResourceObject::Serialize(pOutput);
   pOutput->WriteString(_guid);
   pOutput->WriteString(_code);
   pOutput->WriteString(_label);
   return ESuccess;
}

//============================================================
// <T>�����ڲ����ݵ����ýڵ㡣</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FFbxResourceComponent::SaveConfig(FXmlNode* pConfig){
   pConfig->SetName(_typeName);
   pConfig->SetNvl(TC("guid"), _guid);
   pConfig->SetNvl(TC("code"), _code);
   pConfig->SetNvl(TC("label"), _label);
   return ESuccess;
}

MO_NAMESPACE_END;
