#include "MoModelParser.h"

MO_NAMESPACE_BEGIN;
//MO_NAMESPACE_USING(FBXSDK_NAMESPACE);

//============================================================
// <T>����FBX��������</T>
//============================================================
FModelMesh::FModelMesh() {
   MO_CLEAR(_pScene);
   MO_CLEAR(_pAiNode);
   MO_CLEAR(_pAiMesh);
   _pVertexs = MO_CREATE(FModelVertexs);
   _pFaces = MO_CREATE(FModelFaces);
   _vertexAttributeCount = 0;
   RBools::Clear(_vertexAttributes, EFbxVertexAttribute_Count);
}

//============================================================
// <T>����FBX��������</T>
//============================================================
FModelMesh::~FModelMesh() {
   MO_CLEAR(_pScene);
   //MO_DESTORY(_pFbxMesh);
   MO_DELETE(_pVertexs);
   MO_DELETE(_pFaces);
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FModelMesh::Setup(){
   MO_ASSERT_POINTER(_pAiMesh);
   // �����Ϣ
   _code = _pAiMesh->mName.C_Str();
   TInt vertexCount = _pAiMesh->mNumVertices;
   TInt faceCount = _pAiMesh->mNumFaces;
   TInt boneCount = _pAiMesh->mNumBones;
   TBool hasColor = _pAiMesh->HasVertexColors(0);
   TBool hasUv0 = _pAiMesh->HasTextureCoords(0);
   TBool hasUv1 = _pAiMesh->HasTextureCoords(1);
   TBool hasNormal = _pAiMesh->HasNormals();
   TBool hasTangent = _pAiMesh->HasTangentsAndBitangents();
   MO_DEBUG(TC("Read mesh. (node=%s, code=%s, point=%d, color=%d, uv0=%d|%d, normal=%d, tangent=%d, face=%d, bone=%d)"),
      _pAiNode->mName.C_Str(), (TCharC*)_code, vertexCount, hasColor, hasUv0, hasUv1, hasNormal, hasTangent, faceCount, boneCount);
   // ����������
   _vertexAttributeCount = 1;
   if(hasColor){
      _vertexAttributeCount++;
      _vertexAttributes[EFbxVertexAttribute_Color0] = ETrue;
   }
   if(hasUv0){
      _vertexAttributeCount++;
      _vertexAttributes[EFbxVertexAttribute_Coord0] = ETrue;
   }
   if(hasUv1){
      _vertexAttributeCount++;
      _vertexAttributes[EFbxVertexAttribute_Coord1] = ETrue;
   }
   if(hasNormal){
      _vertexAttributeCount++;
      _vertexAttributes[EFbxVertexAttribute_Normal] = ETrue;
   }
   if(hasTangent){
      _vertexAttributeCount++;
      _vertexAttributes[EFbxVertexAttribute_Binormal] = ETrue;
   }
   if(hasTangent){
      _vertexAttributeCount++;
      _vertexAttributes[EFbxVertexAttribute_Tangent] = ETrue;
   }
   // ����������Ϣ
   for(TInt32 i = 0; i < vertexCount; i++){
      SModelVertex* pVertex = new SModelVertex();
      aiVector3D& aiPosition = _pAiMesh->mVertices[i];
      // ��ȡ����
      SFloatPoint3& position = pVertex->position;
      position.x = aiPosition.x;
      position.y = aiPosition.y;
      position.z = aiPosition.z;
      // ��ȡ��ɫ
      if(hasColor){
         aiColor4D& aiColor = _pAiMesh->mColors[0][i];
         SFloatColor4& color = pVertex->color;
         color.red = aiColor.r;
         color.green = aiColor.g;
         color.blue = aiColor.b;
         color.alpha = aiColor.a;
      }
      // ��ȡ����0
      if(hasUv0){
         aiVector3D& aiCoord = _pAiMesh->mTextureCoords[0][i];
         SFloatPoint2& coord = pVertex->coord;
         coord.x = aiCoord.x;
         coord.y = aiCoord.y;
      }
      // ��ȡ����
      if(hasNormal){
         aiVector3D& aiNormal = _pAiMesh->mNormals[i];
         SFloatVector3& normal = pVertex->normal;
         normal.x = aiNormal.x;
         normal.y = aiNormal.y;
         normal.z = aiNormal.z;
      }
      // ��ȡ������
      if(hasTangent){
         aiVector3D& aiNormal = _pAiMesh->mBitangents[i];
         SFloatVector3& binormal = pVertex->binormal;
         binormal.x = aiNormal.x;
         binormal.y = aiNormal.y;
         binormal.z = aiNormal.z;
      }
      // ��ȡ����
      if(hasTangent){
         aiVector3D& aiTangent = _pAiMesh->mTangents[i];
         SFloatVector3& tangent = pVertex->tangent;
         tangent.x = aiTangent.x;
         tangent.y = aiTangent.y;
         tangent.z = aiTangent.z;
      }
      // ���Ӷ���
      _pVertexs->Push(pVertex);
   }
   // ����������Ϣ
   for(TInt i = 0; i < faceCount; i++){
      aiFace& aiFace = _pAiMesh->mFaces[i];
      SModelFace* pFace = new SModelFace();
      pFace->corners[0] = aiFace.mIndices[0];
      pFace->corners[1] = aiFace.mIndices[1];
      pFace->corners[2] = aiFace.mIndices[2];
      // ������
      _pFaces->Push(pFace);
   }
   return ESuccess;
}

//============================================================
// <T>���л����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FModelMesh::Serialize(IDataOutput* pOutput){
   MO_ASSERT_POINTER(pOutput);
   // д�붥������
   TInt vertexCount = _pVertexs->Count();
   pOutput->WriteInt32((TInt32)vertexCount);
   for(TInt32 vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++){
      SModelVertex* pVertex = _pVertexs->Get(vertexIndex);
      SFloatPoint3& position = pVertex->position;
      pOutput->WriteFloat(position.x);
      pOutput->WriteFloat(position.y);
      pOutput->WriteFloat(position.z);
   }
   // д��������
   TInt faceCount = _pFaces->Count();
   pOutput->WriteInt32((TInt32)faceCount);
   for(TInt32 faceIndex = 0; faceIndex < faceCount; faceIndex++){
      SModelFace* pFace = _pFaces->Get(faceIndex);
      TInt* pCorners = pFace->corners;
      pOutput->WriteUint32((TUint32)pCorners[0]);
      pOutput->WriteUint32((TUint32)pCorners[1]);
      pOutput->WriteUint32((TUint32)pCorners[2]);
   }
   return ESuccess;
}


//============================================================
// <T>���л��ڲ����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FModelMesh::Store(FFbxResModelMesh* pResMesh){
   FModelVertexs* pVertexs = _pVertexs;
   TInt vertexCount = pVertexs->Count();
   FModelFaces* pFaces = _pFaces;
   TInt faceCount = pFaces->Count();
   // ��������
   pResMesh->SetCode(_code);
   // д�붥������������
   FFbxResStream* pPositionStream = MO_CREATE(FFbxResStream);
   pPositionStream->SetCode(TC("position"));
   pPositionStream->SetDataCount(vertexCount);
   pPositionStream->SetDataStride(sizeof(TFloat) * 3);
   pPositionStream->SetElementCount(3);
   pPositionStream->SetElementDataCd(EFbxData_Float32);
   FByteStream* pPositionData = pPositionStream->Data();
   for(TInt vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++){
      SModelVertex* pVertex = pVertexs->Get(vertexIndex);
      SFloatPoint3& position = pVertex->position;
      pPositionData->WriteFloat(position.x);
      pPositionData->WriteFloat(position.y);
      pPositionData->WriteFloat(position.z);
   }
   pResMesh->VertexStreams()->Push(pPositionStream);
   // д����������������
   if(ContainsAttribute(EFbxVertexAttribute_Coord0)){
      FFbxResStream* pNormalStream = MO_CREATE(FFbxResStream);
      pNormalStream->SetCode(TC("coord"));
      pNormalStream->SetDataCount(vertexCount);
      pNormalStream->SetDataStride(sizeof(TFloat) * 2);
      pNormalStream->SetElementCount(2);
      pNormalStream->SetElementDataCd(EFbxData_Float32);
      FByteStream* pData = pNormalStream->Data();
      for(TInt vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++){
         SModelVertex* pVertex = pVertexs->Get(vertexIndex);
         SFloatPoint2& coord = pVertex->coord;
         pData->WriteFloat(coord.x);
         pData->WriteFloat(coord.y);
      }
      pResMesh->VertexStreams()->Push(pNormalStream);
   }
   // д�붥�㷨��������
   if(ContainsAttribute(EFbxVertexAttribute_Normal)){
      FFbxResStream* pNormalStream = MO_CREATE(FFbxResStream);
      pNormalStream->SetCode(TC("normal"));
      pNormalStream->SetDataCount(vertexCount);
      pNormalStream->SetDataStride(sizeof(TByte) * 4);
      pNormalStream->SetElementCount(4);
      pNormalStream->SetElementDataCd(EFbxData_Uint8);
      FByteStream* pNormalData = pNormalStream->Data();
      for(TInt vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++){
         SModelVertex* pVertex = pVertexs->Get(vertexIndex);
         SFloatVector3& normal = pVertex->normal;
         pNormalData->WriteUint8((TUint8)((normal.x + 1.0f) * 0.5f * 255.0f));
         pNormalData->WriteUint8((TUint8)((normal.y + 1.0f) * 0.5f * 255.0f));
         pNormalData->WriteUint8((TUint8)((normal.z + 1.0f) * 0.5f * 255.0f));
         pNormalData->WriteUint8((TUint8)255);
      }
      pResMesh->VertexStreams()->Push(pNormalStream);
   }
   //............................................................
   // д��������������
   FFbxResStream* pIndexStream = MO_CREATE(FFbxResStream);
   FByteStream* pIndexData = pIndexStream->Data();
   pIndexStream->SetCode(TC("index16"));
   pIndexStream->SetDataCount(faceCount);
   pIndexStream->SetDataStride(sizeof(TUint16) * 3);
   pIndexStream->SetElementCount(3);
   pIndexStream->SetElementDataCd(EFbxData_Uint16);
   for(TInt faceIndex = 0; faceIndex < faceCount; faceIndex++){
      SModelFace* pFace = pFaces->Get(faceIndex);
      TInt* pCorners = pFace->corners;
      pIndexData->WriteUint16((TUint16)pCorners[0]);
      pIndexData->WriteUint16((TUint16)pCorners[1]);
      pIndexData->WriteUint16((TUint16)pCorners[2]);
   }
   pResMesh->IndexStreams()->Push(pIndexStream);
   return ESuccess;
}

MO_NAMESPACE_END;
