#include "MoFbxResource.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>������Դ����</T>
//============================================================
FFbxResource::FFbxResource() {
}

//============================================================
// <T>������Դ����</T>
//============================================================
FFbxResource::~FFbxResource() {
}

//============================================================
// <T>���л��ڲ����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FFbxResource::Serialize(IDataOutput * pOutput){
   FFbxResourceComponent::Serialize(pOutput);
   return ESuccess;
}

//============================================================
// <T>�����ڲ����ݵ����ýڵ㡣</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FFbxResource::SaveConfig(FXmlNode* pConfig){
   FFbxResourceComponent::SaveConfig(pConfig);
   return ESuccess;
}

MO_NAMESPACE_END;
