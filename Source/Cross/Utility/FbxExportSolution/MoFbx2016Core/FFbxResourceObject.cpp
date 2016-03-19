#include "MoFbxResource.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>������Դ����</T>
//============================================================
FFbxResourceObject::FFbxResourceObject() {
   _version = 1;
}

//============================================================
// <T>������Դ����</T>
//============================================================
FFbxResourceObject::~FFbxResourceObject() {
}

//============================================================
// <T>���л��ڲ����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FFbxResourceObject::Serialize(IDataOutput * pOutput){
   pOutput->WriteString(_typeName);
   pOutput->WriteInt32((TInt32)_version);
   return ESuccess;
}

MO_NAMESPACE_END;
