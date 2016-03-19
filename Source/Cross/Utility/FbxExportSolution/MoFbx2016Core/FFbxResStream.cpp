#include "MoFbxResource.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>������Դ��������</T>
//============================================================
FFbxResStream::FFbxResStream(){
   _typeName = TC("Stream");
   _pData = MO_CREATE(FByteStream);
}

//============================================================
// <T>������Դ��������</T>
//============================================================
FFbxResStream::~FFbxResStream(){
   MO_DELETE(_pData);
}

//============================================================
// <T>���л��ڲ����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FFbxResStream::Serialize(IDataOutput * pOutput){
   FFbxResourceObject::Serialize(pOutput);
   // �������
   pOutput->WriteString(_code);
   pOutput->WriteUint8((TUint8)_elementDataCd);
   pOutput->WriteUint8((TUint8)_elementCount);
   pOutput->WriteBool(EFalse);
   pOutput->WriteUint8((TUint8)_dataStride);
   pOutput->WriteUint32((TUint32)_dataCount);
   // �������
   pOutput->Write(_pData->MemoryC(), _pData->Length());
   return ESuccess;
}

MO_NAMESPACE_END;
