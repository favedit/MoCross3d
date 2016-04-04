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
   //TString16 typeName;
   //typeName.Assign8(_typeName);
   //pOutput->WriteString16(typeName);
   pOutput->WriteString16(_typeName);
   pOutput->WriteInt32((TInt32)_version);
   return ESuccess;
}

MO_NAMESPACE_END;
