#include "MoFbxParser.h"

MO_NAMESPACE_BEGIN;

/*
//============================================================
F3dsGeometryExporter::F3dsGeometryExporter(F3dsGameExporter* pExporter, IGameNode* piNode, IGameMesh* piSubMesh){
   _pExporter = pExporter;
   _piNode = piNode;
   _piSubMesh = piSubMesh;
}

//============================================================
F3dsGeometryExporter::~F3dsGeometryExporter(){
}

//============================================================
// <T>�洢����������</T>
//
// @param pTrackNode ������Ϣ
//============================================================
TBool F3dsGeometryExporter::SerializeTrack(IDataOutput* pOutput){
   // ��������
   R3dsExporter::SerializeMatrix(pOutput, _piNode->GetObjectTM(0));
   R3dsExporter::SerializeMatrix(pOutput, _piNode->GetLocalTM(0));
   R3dsExporter::SerializeMatrix(pOutput, _piNode->GetWorldTM(0));
   // ��ÿؼ�
   TBool hasFrame = EFalse;
   IGameControl* piControl = _piNode->GetIGameControl();
   if(NULL != piControl){
      // ��ÿ�����Ϣ
      bool positionAnimated = piControl->IsAnimated(IGAME_POS);
      int keyPositionCount = piControl->GetIGameKeyCount(IGAME_POS);
      bool rotationAnimated = piControl->IsAnimated(IGAME_ROT);
      int keyRotationCount = piControl->GetIGameKeyCount(IGAME_ROT);
      bool scaleAnimated = piControl->IsAnimated(IGAME_SCALE);
      int keyScaleCount = piControl->GetIGameKeyCount(IGAME_SCALE);
      // ����Ƿ��ж���
      //if(positionAnimated || rotationAnimated || scaleAnimated){
         // ����Ĭ�ϵ�������
         IGameKeyTab keys;
         if(piControl->GetFullSampledKeys(keys, 1, IGAME_TM, false)){
            TInt32 count = keys.Count();
            pOutput->WriteInt32(count);
            for(TInt n = 0; n < count; n++){
               // ����һ֡��Ϣ
               IGameKey& key = keys[n];
               pOutput->WriteInt32(key.t);
               // ���ö������
               R3dsExporter::SerializeMatrix(pOutput, _piNode->GetObjectTM(key.t));
               R3dsExporter::SerializeMatrix(pOutput, _piNode->GetLocalTM(key.t));
               R3dsExporter::SerializeMatrix(pOutput, _piNode->GetWorldTM(key.t));
            }
            hasFrame = ETrue;
         }
      //}
   }
   if(!hasFrame){
      pOutput->WriteInt32(0);
   }
   return ETrue;
}

//============================================================
// <T>�洢��Ƥ�ĵ��Ӧ��Ȩ�ء�</T>
// <P>ʹ�÷��ߵ㣬��ʹ�ö��㡣</P>
//
// @param pSkinNode ���ýڵ�
// @param piSkin Ƥ���ӿ�
//============================================================
TBool F3dsGeometryExporter::SerializeSkin(IDataOutput* pOutput, IGameSkin* piSkin){
   // ��û�������
   TInt vertexCount = _piSubMesh->GetNumberOfVerts();
   TInt32 boneCount = piSkin->GetTotalBoneCount();
   pOutput->WriteInt32(boneCount);
   pOutput->WriteInt32(piSkin->GetTotalSkinBoneCount());
   //------------------------------------------------------------
   // ������Ƥ�����Ķ�������
   TInt32 validCount = 0;
   for(TInt32 n = 0; n < vertexCount; n++){
      // ���ù���Ȩ��
      TInt boneCount = piSkin->GetNumberOfBones(n);
      if(boneCount > 0){
         validCount++;
         // �洢����Ȩ��
         for(TInt32 i = 0; i < boneCount; i++){
            // ��ù�����Ϣ
            TInt boneId = piSkin->GetBoneID(n, i);
            IGameNode* piBone = _pExporter->GameNodes()->Get(boneId);
            if(!_pExporter->GameBones()->Contains(piBone)){
               _pExporter->GameBones()->Push(piBone);
            }
         }
      }
   }
   //------------------------------------------------------------
   // �洢�����б�
   pOutput->WriteInt32(validCount);
   for(TInt32 n = 0; n < vertexCount; n++){
      // ���ù���Ȩ��
      TInt32 boneCount = piSkin->GetNumberOfBones(n);
      if(boneCount > 0){
         // �洢����Ȩ��
         pOutput->WriteInt32(n);
         pOutput->WriteInt32(boneCount);
         for(TInt32 i = 0; i < boneCount; i++){
            // ��ù�����Ϣ
            TInt32 boneId = piSkin->GetBoneID(n, i);
            TFloat weight = piSkin->GetWeight(n, i);
            pOutput->WriteInt32(boneId);
            pOutput->WriteFloat(weight);
         }
      }
   }
   return ETrue;
}

//============================================================
// <T>���л�������Ϣ��</T>
//
// @param pOutput �����
//============================================================
TBool F3dsGeometryExporter::Serialize(IDataOutput* pOutput){
   // �������
   TCharC* pName = _piNode->GetName();
   FByteFile* pFile = (FByteFile*)pOutput;
   TFsName8 name;
   name.Assign16(_piNode->GetName());
   name.Serialize(pOutput);
   // �洢�������� (Vertex)
   TInt32 vertexCount = _piSubMesh->GetNumberOfVerts();
   pOutput->WriteInt32(vertexCount);
   for(TInt32 n = 0; n < vertexCount; n++){
      Point3 point;
      if(_piSubMesh->GetVertex(n, point)){
         pOutput->WriteFloat(point.x);
         pOutput->WriteFloat(point.y);
         pOutput->WriteFloat(point.z);
      }
   }
   // ������ɫ (Color)
   TInt32 colorCount = _piSubMesh->GetNumberOfColorVerts();
   pOutput->WriteInt32(colorCount);
   for(TInt32 n = 0; n < colorCount; n++){
      Point3 point;
      if(_piSubMesh->GetColorVertex(n, point)){
         pOutput->WriteFloat(point.x);
         pOutput->WriteFloat(point.y);
         pOutput->WriteFloat(point.z);
      }
   }
   // ����͸�� (Alpha)
   TInt32 alphaCount = _piSubMesh->GetNumberOfAlphaVerts();
   pOutput->WriteInt32(alphaCount);
   for(TInt32 n = 0; n < alphaCount; n++){
	   TFloat alpha = 0.0f;
	   if(_piSubMesh->GetAlphaVertex(n, alpha)){
		   pOutput->WriteFloat(alpha);
	   }
   }
   // �洢��ͼ���� (Coord)
   TInt32 coordCount = _piSubMesh->GetNumberOfTexVerts();
   pOutput->WriteInt32(coordCount);
   for(TInt32 n = 0; n < coordCount; n++){
      Point2 point;
      if(_piSubMesh->GetTexVertex(n, point)){
         pOutput->WriteFloat(point.x);
         pOutput->WriteFloat(point.y);
      }
   }
   // �洢�������� (Normal)
   TInt32 normalCount = _piSubMesh->GetNumberOfNormals();
   pOutput->WriteInt32(normalCount);
   for(TInt32 n = 0; n < normalCount; n++){
      Point3 point;
      if(_piSubMesh->GetNormal(n, point)){
         pOutput->WriteFloat(point.x);
         pOutput->WriteFloat(point.y);
         pOutput->WriteFloat(point.z);
      }
   }
   // ���ö��㸱���� (binormal = normal * tangent)
   TInt32 binormalCount = _piSubMesh->GetNumberOfBinormals();
   pOutput->WriteInt32(binormalCount);
   for(TInt32 n = 0; n < binormalCount; n++){
      Point3 point;
      if(_piSubMesh->GetBinormal(n, point)){
         pOutput->WriteFloat(point.x);
         pOutput->WriteFloat(point.y);
         pOutput->WriteFloat(point.z);
      }
   }
   // ���ö������� (tangent)
   TInt32 tangentCount = _piSubMesh->GetNumberOfTangents();
   pOutput->WriteInt32(tangentCount);
   for(TInt32 n = 0; n < tangentCount; n++){
      Point3 point;
      if(_piSubMesh->GetTangent(n, point)){
         pOutput->WriteFloat(point.x);
         pOutput->WriteFloat(point.y);
         pOutput->WriteFloat(point.z);
      }
   }
   // ���ö������� (Illum)
   TInt32 illumCount = _piSubMesh->GetNumberOfIllumVerts();
   pOutput->WriteInt32(illumCount);
   for(TInt32 n = 0; n < illumCount; n++){
	   float illum;
	   if(_piSubMesh->GetIllumVertex(n, illum)){
		   pOutput->WriteFloat(illum);
	   }
   }
   // �洢�������� (Faces)��ʹ������Ϣ�����ö��������ͷ�����Ϣ
   TInt32 faceCount = _piSubMesh->GetNumberOfFaces();
   pOutput->WriteInt32(faceCount);
   for(TInt32 n = 0; n < faceCount; n++){
      FaceEx* pFace = _piSubMesh->GetFace(n);
      IGameMaterial* piMaterial = _piSubMesh->GetMaterialFromFace(pFace);
      TInt32 materialIndex = (TInt32)_materials.IndexOf(piMaterial);
      // �������Ϣ
      pOutput->WriteInt32(pFace->meshFaceIndex);
	   pOutput->WriteInt32(pFace->flags);
      //pOutput->WriteInt32(pFace->matID);
      pOutput->WriteInt32(materialIndex);
      pOutput->WriteInt32(pFace->smGrp);
      // �洢������Ķ�������
      if(vertexCount > 0){
         pOutput->WriteInt32(pFace->vert[0]);
         pOutput->WriteInt32(pFace->vert[1]);
         pOutput->WriteInt32(pFace->vert[2]);
      }
      // �洢������Ķ�����ɫ����
      if(colorCount > 0){
         pOutput->WriteInt32(pFace->color[0]);
         pOutput->WriteInt32(pFace->color[1]);
         pOutput->WriteInt32(pFace->color[2]);
      }
	  // �洢������Ķ���͸������
	  if(alphaCount > 0){
		  pOutput->WriteInt32(pFace->alpha[0]);
		  pOutput->WriteInt32(pFace->alpha[1]);
		  pOutput->WriteInt32(pFace->alpha[2]);
	  }
      // �洢������Ķ�����ͼ����
      if(coordCount > 0){
         pOutput->WriteInt32(pFace->texCoord[0]);
         pOutput->WriteInt32(pFace->texCoord[1]);
         pOutput->WriteInt32(pFace->texCoord[2]);
      }
      // �洢������Ķ��㷨������
      if(normalCount > 0){
         pOutput->WriteInt32(pFace->norm[0]);
         pOutput->WriteInt32(pFace->norm[1]);
         pOutput->WriteInt32(pFace->norm[2]);
      }
      // �洢�����θ����ߺ���������
      if((binormalCount > 0) || (tangentCount > 0)){
         pOutput->WriteInt32(_piSubMesh->GetFaceVertexTangentBinormal(n, 0));
         pOutput->WriteInt32(_piSubMesh->GetFaceVertexTangentBinormal(n, 1));
         pOutput->WriteInt32(_piSubMesh->GetFaceVertexTangentBinormal(n, 2));
      }
	   // �洢������Ķ�����������
	   if(illumCount > 0){
		   pOutput->WriteInt32(pFace->illum[0]);
		   pOutput->WriteInt32(pFace->illum[1]);
		   pOutput->WriteInt32(pFace->illum[2]);
	   }
      // �洢�����α��߿ɼ���
      pOutput->WriteInt32(pFace->edgeVis[0]);
      pOutput->WriteInt32(pFace->edgeVis[1]);
      pOutput->WriteInt32(pFace->edgeVis[2]);
   }
   MO_INFO(TC("Serialize geometry. (name=%s, vertex=%d, face=%d)"), pName, vertexCount, faceCount);
   // �洢������Ϣ
   SerializeTrack(pOutput);
   // �洢��Ƥ��Ϣ
   IGameSkin* piSkin = _piSubMesh->GetIGameSkin();
   if(NULL != piSkin){
      pOutput->WriteInt32(1);
      SerializeSkin(pOutput, piSkin);
   }else{
      pOutput->WriteInt32(0);
   }
   return ETrue;
}

//============================================================
// <T>�洢��Ƥ�ĵ��Ӧ��Ȩ�ء�</T>
// <P>ʹ�÷��ߵ㣬��ʹ�ö��㡣</P>
//
// @param pSkinNode ���ýڵ�
// @param piSkin Ƥ���ӿ�
//============================================================
TBool F3dsGeometryExporter::ConvertSkin(FXmlNode* pSkinNode, IGameSkin* piSkin){
   // ��û�������
   pSkinNode->Set(TC("class_name"), piSkin->GetClassName());
   TInt vertexCount = _piSubMesh->GetNumberOfVerts();
   if(vertexCount > 0){
      pSkinNode->SetInt(TC("vertex_count"), vertexCount);
   }
   TInt32 boneCount = piSkin->GetTotalBoneCount();
   pSkinNode->SetInt(TC("bone_count"), boneCount);
   pSkinNode->SetInt(TC("skin_bone_count"), piSkin->GetTotalSkinBoneCount());
   //// �����Ƥ����
   //GMatrix matrix;
   //piSkin->GetInitSkinTM(matrix);
   //R3dsExporter::StoreGameMatrixSimple(pSkinNode->CreateNode("Matrix"), matrix);
   //// �洢�����б�
   //FXmlNode* pBoneListNode = pSkinNode->CreateNode("BoneList");
   //for(TInt n = 0; n < boneCount; n++){
   //   INode* piBoneNode = piSkin->GetBone(n);
   //   IGameNode* piGameNode =_pExporter->GameScene()->GetIGameNode(piBoneNode);
   //   FXmlNode* pBoneNode = pBoneListNode->CreateNode("Bone");
   //   pBoneNode->SetInt("bone_id", piGameNode->GetNodeID());
   //   GMatrix boneMatrix;
   //   piSkin->GetInitBoneTM(piGameNode, boneMatrix);
   //   R3dsExporter::StoreGameMatrixSimple(pBoneNode->CreateNode("Matrix"), boneMatrix);
   //}
   // �洢�����б�
   FXmlNode* pVertexListNode = pSkinNode->CreateNode(TC("VertexCollection"));
   pVertexListNode->SetInt(TC("count"), vertexCount);
   for(TInt32 n = 0; n < vertexCount; n++){
      // ���ù���Ȩ��
      TInt32 boneCount = piSkin->GetNumberOfBones(n);
      if(boneCount > 0){
         // �洢�ڵ�
         FXmlNode* pVertexNode = pVertexListNode->CreateNode(TC("Vertex"));
         pVertexNode->SetInt(TC("id"), n);
         // �洢����Ȩ��
         for(TInt32 i = 0; i < boneCount; i++){
            // ��ù�����Ϣ
            TInt boneId = piSkin->GetBoneID(n, i);
            IGameNode* piBone = _pExporter->GameNodes()->Get(boneId);
            if(!_pExporter->GameBones()->Contains(piBone)){
               _pExporter->GameBones()->Push(piBone);
            }
            // �洢�ڵ����
            FXmlNode* pBoneNode = pVertexNode->CreateNode(TC("Bone"));
            TFloat weight = piSkin->GetWeight(n, i);
            pBoneNode->SetInt(TC("bone_id"), boneId);
            pBoneNode->SetFloat(TC("weight"), weight);
         }
      }
   }
   return ETrue;
}

//============================================================
// <T>����������Ķ��㡣</T>
//
// @param pVertexNode ������Ϣ
// @param face ����Ϣ
// @param corner �ս���Ϣ
//============================================================
TBool F3dsGeometryExporter::ConvertVertex(FXmlNode* pVertexNode, TInt32 face, TInt32 corner){
   // �������Ϣ
   FaceEx* pFace = _piSubMesh->GetFace(face);
   TInt32 tbIndex = _piSubMesh->GetFaceVertexTangentBinormal(face, corner);
   // ���ö�������
   FXmlNode* pPositionNode = pVertexNode->FindNode(TC("Position"));
   if(NULL == pPositionNode){
      Point3 point;
      if(_piSubMesh->GetVertex(pFace->vert[corner], point)){
         pPositionNode = pVertexNode->CreateNode(TC("Position"));
         R3dsExporter::StorePoint3(pPositionNode, point);
      }
   }
   // ���ö�����ͼ����
   TInt32 uvCount = _piSubMesh->GetNumberOfTexVerts();
   if(uvCount > 0){
      FXmlNode* pCoordNode = pVertexNode->FindNode(TC("Coord"));
      if(NULL == pCoordNode){
         Point2 coord;
         if(_piSubMesh->GetTexVertex(pFace->texCoord[corner], coord)){
            pCoordNode = pVertexNode->CreateNode(TC("Coord"));
            R3dsExporter::StorePoint2(pCoordNode, coord);
         }
      }
   }
   // ���ö�����ɫ
   TInt32 colorCount = _piSubMesh->GetNumberOfColorVerts();
   if(colorCount > 0){
      FXmlNode* pColorNode = pVertexNode->FindNode(TC("Color"));
      if(NULL == pColorNode){
         Point3 color;
         if(_piSubMesh->GetColorVertex(pFace->color[corner], color)){
            pColorNode = pVertexNode->CreateNode(TC("Color"));
            R3dsExporter::StorePoint3(pColorNode, color);
         }
      }
   }
   // ���ö��㷨�� (normal)
   FXmlNode* pNormalNode = pVertexNode->FindNode(TC("Normal"));
   if(NULL == pNormalNode){
      Point3 normal;
      if(_piSubMesh->GetNormal(pFace, corner, normal)){
         pNormalNode = pVertexNode->CreateNode(TC("Normal"));
         R3dsExporter::StorePoint3(pNormalNode, normal);
      }
   }
   // ���ö��㸱���� (binormal = normal * tangent)
   FXmlNode* pBinormalNode = pVertexNode->FindNode(TC("Binormal"));
   if(NULL == pBinormalNode){
      Point3 binormal;
      if(_piSubMesh->GetBinormal(tbIndex, binormal)){
         pBinormalNode = pVertexNode->CreateNode(TC("Binormal"));
         R3dsExporter::StorePoint3(pBinormalNode, binormal);
      }
   }
   // ���ö������� (tangent)
   FXmlNode* pTangentNode = pVertexNode->FindNode(TC("Tangent"));
   if(NULL == pTangentNode){
      Point3 tangent;
      if(_piSubMesh->GetTangent(tbIndex, tangent)){
         pTangentNode = pVertexNode->CreateNode(TC("Tangent"));
         R3dsExporter::StorePoint3(pTangentNode, tangent);
      }
   }
   // ���ö���͸����
   TInt32 alphaCount = _piSubMesh->GetNumberOfAlphaVerts();
   if(alphaCount > 0){
      FXmlNode* pAlphaNode = pVertexNode->FindNode(TC("Alpha"));
      if(NULL == pAlphaNode){
         TFloat alpha;
         if(_piSubMesh->GetAlphaVertex(pFace->alpha[corner], alpha)){
            pAlphaNode = pVertexNode->CreateNode(TC("Alpha"));
            pAlphaNode->SetFloat(TC("value"), alpha);
         }
      }
   }
   // ���ö��㷢���
   TInt32 illumCount = _piSubMesh->GetNumberOfIllumVerts();
   if(illumCount > 0){
      FXmlNode* pIllumNode = pVertexNode->FindNode(TC("Illum"));
      if(NULL == pIllumNode){
         TFloat illum;
         if(_piSubMesh->GetIllumVertex(pFace->illum[corner], illum)){
            pIllumNode = pVertexNode->CreateNode(TC("Illum"));
            pIllumNode->SetFloat(TC("value"), illum);
         }
      }
   }
   return ETrue;
}

//============================================================
TBool F3dsGeometryExporter::ConvertControlType(FXmlNode* pTypeNode, IGameControl* piControl, TCharC* pName, IGameControlType keyType){
   int keyCount = piControl->GetIGameKeyCount(keyType);
   pTypeNode->Set(TC("name"), pName);
   pTypeNode->Set(TC("type"), R3dsClass::GetControlType(piControl->GetControlType(keyType)));
   pTypeNode->SetInt(TC("key_count"), keyCount);
   pTypeNode->SetBool(TC("is_animated"), piControl->IsAnimated(keyType));
   pTypeNode->SetBool(TC("is_leaf"), piControl->IsLeaf(keyType));
   return ETrue;
}

//============================================================
// <T>�洢����������</T>
//
// @param pTrackNode ������Ϣ
//============================================================
TBool F3dsGeometryExporter::ConvertTrack(FXmlNode* pTrackNode){
   // ��ýڵ���Ϣ
   TInt nodeId = _piNode->GetNodeID();
   // ��������
   pTrackNode->Set(TC("owner"), TC("geometry"));
   pTrackNode->Set(TC("name"), _piNode->GetName());
   GMatrix objectTm = _piNode->GetObjectTM(0);
   R3dsExporter::StoreGameMatrixSimple(pTrackNode->CreateNode(TC("ObjectMatrix")), objectTm);
   GMatrix localTm = _piNode->GetLocalTM(0);
   R3dsExporter::StoreGameMatrixSimple(pTrackNode->CreateNode(TC("LocalMatrix")), localTm);
   GMatrix worldTm = _piNode->GetWorldTM(0);
   R3dsExporter::StoreGameMatrixSimple(pTrackNode->CreateNode(TC("WorldMatrix")), worldTm);
   // ��ÿؼ�
   IGameControl* piControl = _piNode->GetIGameControl();
   if(NULL == piControl){
      return EFalse;
   }
   // ��ô洢����
   FXmlNode* pTypesNode = pTrackNode->CreateNode(TC("Types"));
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("float"), IGAME_FLOAT);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point"), IGAME_POS);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point3"), IGAME_POINT3);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point4"), IGAME_POINT4);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("rotation"), IGAME_ROT);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("scale"), IGAME_SCALE);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("matrix"), IGAME_TM);
   // ��ÿ�����Ϣ
   bool positionAnimated = piControl->IsAnimated(IGAME_POS);
   int keyPositionCount = piControl->GetIGameKeyCount(IGAME_POS);
   bool rotationAnimated = piControl->IsAnimated(IGAME_ROT);
   int keyRotationCount = piControl->GetIGameKeyCount(IGAME_ROT);
   bool scaleAnimated = piControl->IsAnimated(IGAME_SCALE);
   int keyScaleCount = piControl->GetIGameKeyCount(IGAME_SCALE);
   // ����Ƿ��ж���
   if(positionAnimated || rotationAnimated || scaleAnimated){
      // ����Ĭ�ϵ�������
      IGameKeyTab keys;
      if(piControl->GetFullSampledKeys(keys, 1, IGAME_TM, false)){
         TInt count = keys.Count();
         if(count > 0){
            FXmlNode* pFramesNode = pTrackNode->CreateNode(TC("Frames"));
            pFramesNode->SetInt(TC("count"), count);
            for(TInt n=0; n<count; n++){
               // ����һ֡��Ϣ
               IGameKey& key = keys[n];
               FXmlNode* pFrameNode = pFramesNode->CreateNode(TC("Frame"));
               pFrameNode->SetInt(TC("time"), key.t);
               // ���ö������
               FXmlNode* pObjectTmNode = pFrameNode->CreateNode(TC("ObjectMatrix"));
               GMatrix objectTm = _piNode->GetObjectTM(key.t);
               R3dsExporter::StoreGameMatrixSimple(pObjectTmNode, objectTm);
               FXmlNode* pLocalTmNode = pFrameNode->CreateNode(TC("LocalMatrix"));
               GMatrix localTm = _piNode->GetLocalTM(key.t);
               R3dsExporter::StoreGameMatrixSimple(pLocalTmNode, localTm);
               FXmlNode* pWorldTmNode = pFrameNode->CreateNode(TC("WorldMatrix"));
               GMatrix worldTm = _piNode->GetWorldTM(key.t);
               R3dsExporter::StoreGameMatrixSimple(pWorldTmNode, worldTm);
            }
         }
      }
   }
   return ETrue;
}

//============================================================
// <T>�洢������Ϣ��</T>
// <P>1. �Զ��㷨����ĿΪ��������������һ�������ж�����㷨�ߵ������
//       ��ʱ��Ϊ��ǰ���ߵĶ���Ϊ��������⼸������������һ�µġ�
//    2. ��Ϊ�������࣬��Ƥ��Ȩ�ض���Ҳ���ֿ�����</P>
//
// @param pSubMeshNode ������Ϣ
//============================================================
TBool F3dsGeometryExporter::Convert(FXmlNode* pConfig){
   TFsText meshName =  _piNode->GetName();
   // �����Ϣ
   pConfig->Set(TC("class"), _piSubMesh->GetClassName());
   pConfig->Set(TC("name"), meshName);
   TInt vertexCount = _piSubMesh->GetNumberOfVerts();
   if(vertexCount > 0){
      pConfig->SetInt(TC("vertex_count"), vertexCount);
   }
   TInt colorCount = _piSubMesh->GetNumberOfColorVerts();
   if(colorCount > 0){
      pConfig->SetInt(TC("color_count"), colorCount);
   }
   TInt alphaCount = _piSubMesh->GetNumberOfAlphaVerts();
   if(alphaCount > 0){
      pConfig->SetInt(TC("alpha_count"), alphaCount);
   }
   TInt illumCount = _piSubMesh->GetNumberOfIllumVerts();
   if(illumCount > 0){
      pConfig->SetInt(TC("illum_count"), illumCount);
   }
   TInt normalCount = _piSubMesh->GetNumberOfNormals();
   if(normalCount > 0){
      pConfig->SetInt(TC("normal_count"), normalCount);
   }
   TInt binormalCount = _piSubMesh->GetNumberOfBinormals();
   if(binormalCount > 0){
      pConfig->SetInt(TC("binormal_count"), binormalCount);
   }
   TInt tangentCount = _piSubMesh->GetNumberOfTangents();
   if(tangentCount > 0){
      pConfig->SetInt(TC("tangent_count"), tangentCount);
   }
   TInt faceCount = _piSubMesh->GetNumberOfFaces();
   if(faceCount > 0){
      pConfig->SetInt(TC("face_count"), faceCount);
   }
   TInt coordCount = _piSubMesh->GetNumberOfTexVerts();
   if(coordCount > 0){
      pConfig->SetInt(TC("coord_count"), coordCount);
   }
   // ��������б�
   IPropertyContainer* piPropertyContainer = _piSubMesh->GetIPropertyContainer();
   if(NULL != piPropertyContainer){
      R3dsExporter::StoreProperties(pConfig, TC("Properties"), piPropertyContainer);
   }
   // ��ñ任����
   FXmlNode* pMatrixNode = pConfig->CreateNode(TC("Matrix"));
   GMatrix objectTm = _piNode->GetObjectTM(0);
   R3dsExporter::StoreGameMatrixSimple(pMatrixNode->CreateNode(TC("ObjectMatrix")), objectTm);
   GMatrix localTm = _piNode->GetLocalTM(0);
   R3dsExporter::StoreGameMatrixSimple(pMatrixNode->CreateNode(TC("LocalMatrix")), localTm);
   GMatrix worldTm = _piNode->GetWorldTM(0);
   R3dsExporter::StoreGameMatrixSimple(pMatrixNode->CreateNode(TC("WorldMatrix")), worldTm);
   // ��ò���б�
   // Tab<TInt> maps = _piSubMesh->GetActiveMapChannelNum();
   // TInt mapCount = maps.Count();
   // if(mapCount > 0){
   //    pSubMeshNode->SetInt("map_count", mapCount);
   //    // �������
   //    FXmlNode* pMapsNode = pSubMeshNode->CreateNode("MapCollection");
   //    pMapsNode->SetInt("count", mapCount);
   //    for(TInt n = 0; n < mapCount; n++){
   //       FXmlNode* pMapNode = pMapsNode->CreateNode("Map");
   //       TInt mapId = maps[n];
   //       pMapNode->SetInt("id", mapId);
   //       pMapNode->SetInt("vertex_count", _piSubMesh->GetNumberOfMapVerts(mapId));
   //       pMapNode->SetInt("tangent_count", _piSubMesh->GetNumberOfTangents(mapId));
   //       pMapNode->SetInt("binormal_count", _piSubMesh->GetNumberOfBinormals(mapId));
   //    }
   // }
   // ��ù��������б�
   if(faceCount > 0){
      for(TInt32 n = 0; n < faceCount; n++){
         FaceEx* pFace = _piSubMesh->GetFace(n);
         IGameMaterial* piMaterial = _piSubMesh->GetMaterialFromFace(pFace);
         if(piMaterial != NULL){
            if(!_materials.Contains(piMaterial)){
               _materials.Push(piMaterial);
            }
         }
      }
   }
   if(!_materials.IsEmpty()){
      FXmlNode* pMaterialsNode = pConfig->CreateNode(TC("MaterialCollection"));
      TInt32 materialCount = (TInt32)_materials.Count();
      pMaterialsNode->SetInt(TC("count"), materialCount);
      for(TInt32 n = 0; n < materialCount; n++){
         IGameMaterial* piMaterial = _materials[n];
         FXmlNode* pMaterialNode = pMaterialsNode->CreateNode(TC("Material"));
         pMaterialNode->SetInt(TC("id"), _pExporter->GameMaterials()->IndexOf(piMaterial));
         pMaterialNode->Set(TC("name"), piMaterial->GetMaterialName());
      }
   }
   // ��ñ�����
   TInt32 modifiersCount = _piSubMesh->GetNumModifiers();
   if(modifiersCount > 0){
      FXmlNode* pModifiersNode = pConfig->CreateNode(TC("ModifierCollection"));
      pModifiersNode->SetInt(TC("count"), modifiersCount);
      for(TInt32 n = 0; n < modifiersCount; n++){
         IGameModifier* piModifier = _piSubMesh->GetIGameModifier(n);
         FXmlNode* pModifierNode = pModifiersNode->CreateNode(TC("Modifier"));
         pModifierNode->Set(TC("class"), piModifier->GetClassName());
         pModifierNode->Set(TC("name"), piModifier->GetInternalName());
      }
   }
   // �����Ƥ
   IGameSkin* piSkin = _piSubMesh->GetIGameSkin();
   if(NULL != piSkin){
      FXmlNode* pSkinNode = pConfig->CreateNode(TC("Skin"));
      TInt32 totalBoneCount = piSkin->GetTotalBoneCount();
      TInt32 totalSkinBoneCount = piSkin->GetTotalSkinBoneCount();
      pSkinNode->Set(TC("class"), piSkin->GetClassName());
      pSkinNode->Set(TC("internal_name"), piSkin->GetInternalName());
      pSkinNode->SetInt(TC("bone_count"), totalBoneCount);
      pSkinNode->SetInt(TC("skin_bone_count"), totalSkinBoneCount);
   }
   // �������񶥵㶯��
   IGameControl* piControl = _piNode->GetIGameControl();
   if(NULL == piControl){
	   return EFalse;
   }
   FXmlNode* pTrackNode = pConfig->CreateNode(TC("Track"));
   // ��ô洢����
   FXmlNode* pTypesNode = pTrackNode->CreateNode(TC("Types"));
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("float"), IGAME_FLOAT);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point"), IGAME_POS);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point3"), IGAME_POINT3);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point4"), IGAME_POINT4);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("rotation"), IGAME_ROT);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("scale"), IGAME_SCALE);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("matrix"), IGAME_TM);
   // ��ÿ�����Ϣ
   bool positionAnimated = piControl->IsAnimated(IGAME_POS);
   int keyPositionCount = piControl->GetIGameKeyCount(IGAME_POS);
   bool rotationAnimated = piControl->IsAnimated(IGAME_ROT);
   int keyRotationCount = piControl->GetIGameKeyCount(IGAME_ROT);
   bool scaleAnimated = piControl->IsAnimated(IGAME_SCALE);
   int keyScaleCount = piControl->GetIGameKeyCount(IGAME_SCALE);
   // ����Ƿ��ж���
   //if(positionAnimated || rotationAnimated || scaleAnimated){
	   // ����Ĭ�ϵ�������
	   IGameKeyTab keys;
	   if(piControl->GetFullSampledKeys(keys, 1, IGAME_TM, false)){
		   pTrackNode->SetInt(TC("count"), keys.Count());
	   }
   //}
   return ETrue;
}

//============================================================
// <T>�洢������Ϣ��</T>
// <P>1. �Զ��㷨����ĿΪ��������������һ�������ж�����㷨�ߵ������
//       ��ʱ��Ϊ��ǰ���ߵĶ���Ϊ��������⼸������������һ�µġ�
//    2. ��Ϊ�������࣬��Ƥ��Ȩ�ض���Ҳ���ֿ�����</P>
//
// @param pSubMeshNode ������Ϣ
//============================================================
TBool F3dsGeometryExporter::ConvertFile(FXmlNode* pConfig){
   TFsText meshName =  _piNode->GetName();
   pConfig->Set(TC("name"), meshName);
   pConfig->Set(TC("class"), _piSubMesh->GetClassName());
   TInt32 vertexCount = _piSubMesh->GetNumberOfVerts();
   if(vertexCount > 0){
      pConfig->SetInt(TC("vertex_count"), vertexCount);
   }
   TInt32 colorCount = _piSubMesh->GetNumberOfColorVerts();
   if(colorCount > 0){
      pConfig->SetInt(TC("color_count"), colorCount);
   }
   TInt32 alphaCount = _piSubMesh->GetNumberOfAlphaVerts();
   if(alphaCount > 0){
      pConfig->SetInt(TC("alpha_count"), alphaCount);
   }
   TInt32 illumCount = _piSubMesh->GetNumberOfIllumVerts();
   if(illumCount > 0){
      pConfig->SetInt(TC("illum_count"), illumCount);
   }
   TInt32 normalCount = _piSubMesh->GetNumberOfNormals();
   if(normalCount > 0){
      pConfig->SetInt(TC("normal_count"), normalCount);
   }
   TInt32 binormalCount = _piSubMesh->GetNumberOfBinormals();
   if(binormalCount > 0){
      pConfig->SetInt(TC("binormal_count"), binormalCount);
   }
   TInt32 tangentCount = _piSubMesh->GetNumberOfTangents();
   if(tangentCount > 0){
      pConfig->SetInt(TC("tangent_count"), tangentCount);
   }
   TInt32 faceCount = _piSubMesh->GetNumberOfFaces();
   if(faceCount > 0){
      pConfig->SetInt(TC("face_count"), faceCount);
   }
   TInt32 coordCount = _piSubMesh->GetNumberOfTexVerts();
   if(coordCount > 0){
      pConfig->SetInt(TC("coord_count"), coordCount);
   }
   // ��������б�
   IPropertyContainer* piPropertyContainer = _piSubMesh->GetIPropertyContainer();
   if(NULL != piPropertyContainer){
      R3dsExporter::StoreProperties(pConfig, TC("Properties"), piPropertyContainer);
   }
   // ��ñ任����
   FXmlNode* pMatrixNode = pConfig->CreateNode(TC("Matrix"));
   GMatrix objectTm = _piNode->GetObjectTM(0);
   R3dsExporter::StoreGameMatrixSimple(pMatrixNode->CreateNode(TC("ObjectMatrix")), objectTm);
   GMatrix localTm = _piNode->GetLocalTM(0);
   R3dsExporter::StoreGameMatrixSimple(pMatrixNode->CreateNode(TC("LocalMatrix")), localTm);
   GMatrix worldTm = _piNode->GetWorldTM(0);
   R3dsExporter::StoreGameMatrixSimple(pMatrixNode->CreateNode(TC("WorldMatrix")), worldTm);
   // ��ò���б�
   // Tab<TInt> maps = _piSubMesh->GetActiveMapChannelNum();
   // TInt mapCount = maps.Count();
   // if(mapCount > 0){
   //    pSubMeshNode->SetInt("map_count", mapCount);
   //    // �������
   //    FXmlNode* pMapsNode = pSubMeshNode->CreateNode("MapCollection");
   //    pMapsNode->SetInt("count", mapCount);
   //    for(TInt n = 0; n < mapCount; n++){
   //       FXmlNode* pMapNode = pMapsNode->CreateNode("Map");
   //       TInt mapId = maps[n];
   //       pMapNode->SetInt("id", mapId);
   //       pMapNode->SetInt("vertex_count", _piSubMesh->GetNumberOfMapVerts(mapId));
   //       pMapNode->SetInt("tangent_count", _piSubMesh->GetNumberOfTangents(mapId));
   //       pMapNode->SetInt("binormal_count", _piSubMesh->GetNumberOfBinormals(mapId));
   //    }
   // }
   // ��ù��������б�
   if(faceCount > 0){
      _materials.Clear();
      for(TInt32 n = 0; n < faceCount; n++){
         FaceEx* pFace = _piSubMesh->GetFace(n);
         IGameMaterial* piMaterial = _piSubMesh->GetMaterialFromFace(pFace);
         if(piMaterial != NULL){
            if(!_materials.Contains(piMaterial)){
               _materials.Push(piMaterial);
            }
         }
      }
   }
   if (!_materials.IsEmpty()){
      FXmlNode* pMaterialsNode = pConfig->CreateNode(TC("MaterialCollection"));
      TInt32 materialCount = (TInt32)_materials.Count();
      pMaterialsNode->SetInt(TC("count"), materialCount);
      for(TInt32 n = 0; n < materialCount; n++){
         IGameMaterial* piMaterial = _materials[n];
         FXmlNode* pMaterialNode = pMaterialsNode->CreateNode(TC("Material"));
         pMaterialNode->SetInt(TC("id"), _pExporter->GameMaterials()->IndexOf(piMaterial));
         pMaterialNode->SetInt(TC("material_id"), piMaterial->GetMaterialID(0));
         pMaterialNode->Set(TC("name"), piMaterial->GetMaterialName());
      }
   }
   //------------------------------------------------------------
   //// �洢�������� (Vertex)
   //if(vertexCount > 0){
   //   FXmlNode* pVertexListNode = pConfig->CreateNode(TC("VertexCollection"));
   //   pVertexListNode->SetInt(TC("count"), vertexCount);
   //   for(TInt32 n = 0; n < vertexCount; n++){
   //      FXmlNode* pVertexNode = pVertexListNode->CreateNode(TC("Vertex"));
   //      Point3 point;
   //      if(_piSubMesh->GetVertex(n, point)){
   //         R3dsExporter::StorePoint3(pVertexNode, point);
   //      }
   //   }
   //}
   //// ������ɫ (Color)
   //if(colorCount > 0){
   //   FXmlNode* pColorListNode = pConfig->CreateNode(TC("ColorCollection"));
   //   pColorListNode->SetInt(TC("count"), colorCount);
   //   for(TInt32 n = 0; n < colorCount; n++){
   //      FXmlNode* pColorNode = pColorListNode->CreateNode(TC("Color"));
   //      Point3 point;
   //      if(_piSubMesh->GetColorVertex(n, point)){
   //         R3dsExporter::StorePoint3(pColorNode, point);
   //      }
   //   }
   //}
   //// �洢��ͼ���� (Coord)
   //if(coordCount > 0){
   //   FXmlNode* pCoordListNode = pConfig->CreateNode(TC("CoordCollection"));
   //   pCoordListNode->SetInt(TC("count"), coordCount);
   //   for(TInt32 n = 0; n < coordCount; n++){
   //      FXmlNode* pCoordNode = pCoordListNode->CreateNode(TC("Coord"));
   //      Point2 point;
   //      if(_piSubMesh->GetTexVertex(n, point)){
   //         R3dsExporter::StorePoint2(pCoordNode, point);
   //      }
   //   }
   //}
   //// �洢�������� (Normal)
   //if(normalCount > 0){
   //   FXmlNode* pNormalListNode = pConfig->CreateNode("NormalCollection");
   //   pNormalListNode->SetInt("count", normalCount);
   //   for(TInt n = 0; n < normalCount; n++){
   //      FXmlNode* pNormalNode = pNormalListNode->CreateNode("Normal");
   //      Point3 point;
   //      if(_piSubMesh->GetNormal(n, point)){
   //         R3dsExporter::StorePoint3(pNormalNode, point);
   //      }
   //   }
   //}
   //// ���ö��㸱���� (binormal = normal * tangent)
   //if(binormalCount > 0){
   //   FXmlNode* pBinormalListNode = pConfig->CreateNode("BinormalCollection");
   //   pBinormalListNode->SetInt("count", binormalCount);
   //   for(TInt n = 0; n < binormalCount; n++){
   //      FXmlNode* pBinormalNode = pBinormalListNode->CreateNode("Binormal");
   //      Point3 binormal;
   //      if(_piSubMesh->GetBinormal(n, binormal)){
   //         R3dsExporter::StorePoint3(pBinormalNode, binormal);
   //      }
   //   }
   //}
   //// ���ö������� (tangent)
   //if(tangentCount > 0){
   //   FXmlNode* pTangentListNode = pConfig->CreateNode("TangentCollection");
   //   pTangentListNode->SetInt("count", tangentCount);
   //   for(TInt n = 0; n < tangentCount; n++){
   //      FXmlNode* pTangentNode = pTangentListNode->CreateNode("Tangent");
   //      Point3 tangent;
   //      if(_piSubMesh->GetTangent(n, tangent)){
   //         R3dsExporter::StorePoint3(pTangentNode, tangent);
   //      }
   //   }
   //}
   //// �洢�������� (Faces)��ʹ������Ϣ�����ö��������ͷ�����Ϣ
   //if(faceCount > 0){
   //   FXmlNode* pFacesNode = pConfig->CreateNode("FaceCollection");
   //   pFacesNode->SetInt("count", faceCount);
   //   for(TInt n = 0; n < faceCount; n++){
   //      FXmlNode* pFaceNode = pFacesNode->CreateNode("Face");
   //      FaceEx* pFace = _piSubMesh->GetFace(n);
   //      pFaceNode->SetInt("flags", pFace->flags);
   //      pFaceNode->SetInt("material_id", pFace->matID);
   //      pFaceNode->SetInt("smoothing_group", pFace->smGrp);
   //      // �洢������Ķ�������
   //      if(vertexCount > 0){
   //         TFsText value;
   //         value.AppendFormat("%d,%d,%d", pFace->vert[0], pFace->vert[1], pFace->vert[2]);
   //         pFaceNode->Set("vertex", value);
   //      }
   //      //// �洢������Ķ�����ɫ����
   //      if(colorCount > 0){
   //         TFsText value;
   //         value.AppendFormat("%d,%d,%d", pFace->color[0], pFace->color[1], pFace->color[2]);
   //         pFaceNode->Set("color", value);
   //      }
   //      // �洢������Ķ�����ͼ����
   //      if(coordCount > 0){
   //         TFsText value;
   //         value.AppendFormat("%d,%d,%d", pFace->texCoord[0], pFace->texCoord[1], pFace->texCoord[2]);
   //         pFaceNode->Set("coord", value);
   //      }
   //      // �洢������Ķ��㷨������
   //      if(normalCount > 0){
   //         TFsText value;
   //         value.AppendFormat("%d,%d,%d", pFace->norm[0], pFace->norm[1], pFace->norm[2]);
   //         pFaceNode->Set("normal", value);
   //      }
   //      // �洢�����θ����ߺ���������
   //      if(tangentCount > 0){
   //         TFsText value;
   //         value.AppendFormat("%d,%d,%d", _piSubMesh->GetFaceVertexTangentBinormal(n, 0), _piSubMesh->GetFaceVertexTangentBinormal(n, 1), _piSubMesh->GetFaceVertexTangentBinormal(n, 2));
   //         pFaceNode->Set("tangent_binormal", value);
   //      }
   //      // �洢�����α��߿ɼ���
   //      FXmlNode* pEdgeNode = pFaceNode->CreateNode("Visible");
   //      pEdgeNode->SetInt("v1", pFace->edgeVis[0]);
   //      pEdgeNode->SetInt("v2", pFace->edgeVis[1]);
   //      pEdgeNode->SetInt("v3", pFace->edgeVis[2]);
   //   }
   //}
   //// ��ñ�����
   //TInt modifiersCount = _piSubMesh->GetNumModifiers();
   //if(modifiersCount > 0){
   //   FXmlNode* pModifiersNode = pConfig->CreateNode("ModifierCollection");
   //   pModifiersNode->SetInt("count", modifiersCount);
   //   for(TInt n = 0; n < modifiersCount; n++){
   //      IGameModifier* piModifier = _piSubMesh->GetIGameModifier(n);
   //      FXmlNode* pModifierNode = pModifiersNode->CreateNode("Modifier");
   //      pModifierNode->Set("class", piModifier->GetClassName());
   //      pModifierNode->Set("name", piModifier->GetInternalName());
   //   }
   //}
   //// �����Ƥ
   //IGameSkin* piSkin = _piSubMesh->GetIGameSkin();
   //if(NULL != piSkin){
   //   FXmlNode* pSkinNode = pConfig->CreateNode("Skin");
   //   TInt totalBoneCount = piSkin->GetTotalBoneCount();
   //   TInt totalSkinBoneCount = piSkin->GetTotalSkinBoneCount();
   //   pSkinNode->Set("class", piSkin->GetClassName());
   //   pSkinNode->Set("internal_name", piSkin->GetInternalName());
   //   pSkinNode->SetInt("bone_count", totalBoneCount);
   //   pSkinNode->SetInt("skin_bone_count", totalSkinBoneCount);
   //   // �洢��Ƥ��Ϣ
   //   ConvertSkin(pSkinNode, piSkin);
   //}
   // �������񶥵㶯��
   //FXmlNode* pTrackNode = pConfig->CreateNode(TC("Track"));
   //ConvertTrack(pTrackNode);
   return ETrue;
}
*/

MO_NAMESPACE_END;
