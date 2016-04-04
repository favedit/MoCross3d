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
   // �������
   _position.Serialize(pOutput);
   _rotation.Serialize(pOutput);
   _scale.Serialize(pOutput);
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
   FXmlNode* pMatrix = pConfig->CreateNode(TC("Matrix"));
   pMatrix->SetFloat(TC("tx"), _position.x);
   pMatrix->SetFloat(TC("ty"), _position.y);
   pMatrix->SetFloat(TC("tz"), _position.z);
   pMatrix->SetFloat(TC("qx"), _rotation.x);
   pMatrix->SetFloat(TC("qy"), _rotation.y);
   pMatrix->SetFloat(TC("qz"), _rotation.z);
   pMatrix->SetFloat(TC("qw"), _rotation.w);
   pMatrix->SetFloat(TC("sx"), _scale.x);
   pMatrix->SetFloat(TC("sy"), _scale.y);
   pMatrix->SetFloat(TC("sz"), _scale.z);
   return ESuccess;
}

MO_NAMESPACE_END;
