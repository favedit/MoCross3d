#include "MoFbxResource.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>����FBX������</T>
//============================================================
FFbxResModelMesh::FFbxResModelMesh() {
   _typeName = TC("ModelMesh");
   _guid = RGuid::Generate();
   _pVertexStreams = MO_CREATE(FFbxResStreams);
   _pIndexStreams = MO_CREATE(FFbxResStreams);
}

//============================================================
// <T>����FBX������</T>
//============================================================
FFbxResModelMesh::~FFbxResModelMesh() {
   MO_DELETE(_pVertexStreams);
   MO_DELETE(_pIndexStreams);
}

//============================================================
// <T>���л��ڲ����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FFbxResModelMesh::Serialize(IDataOutput* pOutput){
   FFbxResourceComponent::Serialize(pOutput);
   // �����������������
   TInt vertexStreamCount = _pVertexStreams->Count();
   pOutput->WriteInt32((TInt32)vertexStreamCount);
   for(TInt n = 0; n < vertexStreamCount; n++){
      FFbxResStream* pStream = _pVertexStreams->Get(n);
      pStream->Serialize(pOutput);
   }
   // �����������������
   TInt indexStreamCount = _pIndexStreams->Count();
   pOutput->WriteInt32((TInt32)indexStreamCount);
   for(TInt n = 0; n < indexStreamCount; n++){
      FFbxResStream* pStream = _pIndexStreams->Get(n);
      pStream->Serialize(pOutput);
   }
   return ESuccess;
}

//============================================================
// <T>�����ڲ����ݵ����ýڵ㡣</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FFbxResModelMesh::SaveConfig(FXmlNode* pConfig){
   FFbxResourceComponent::SaveConfig(pConfig);
   // ������񼯺�
   //TInt meshCount = _pMeshs->Count();
   //pOutput->WriteInt32((TInt32)meshCount);
   //for(TInt n = 0; n < meshCount; n++){
   //   FFbxResMesh* pMesh = _pMeshs->Get(n);
   //   pMesh->Serialize(pOutput);
   //}
   return ESuccess;
}

MO_NAMESPACE_END;
