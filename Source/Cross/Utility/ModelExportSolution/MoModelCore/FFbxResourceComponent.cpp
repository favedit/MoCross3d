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
   TString16 guid;
   guid.Assign8(_guid);
   pOutput->WriteString16(guid);
   TString16 code;
   code.Assign8(_code);
   pOutput->WriteString16(code);
   TString16 label;
   label.Assign8(_label);
   pOutput->WriteString16(label);
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
