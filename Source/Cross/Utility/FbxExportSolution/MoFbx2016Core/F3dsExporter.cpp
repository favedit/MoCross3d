#include "MoFbxParser.h"

MO_NAMESPACE_BEGIN;

/*
//============================================================
F3dsExporter::F3dsExporter(IScene* piScene, TimeValue time, Interface* piInterface) :
      M3dsExporter(piScene, time, piInterface){
   _pBones = MO_CREATE(FBoneVector);
}

//============================================================
F3dsExporter::~F3dsExporter(){
   MO_DELETE(_pBones)
}

//============================================================
// <T>�жϽڵ��Ƿ�Ϊ����</T>
//============================================================
TBool F3dsExporter::IsMesh(INode* piNode){
   if(NULL == piNode){
      return EFalse;
   }
   ObjectState os = piNode->EvalWorldState(0);
   if(!os.obj){
      return EFalse;
   }
   return GEOMOBJECT_CLASS_ID == os.obj->SuperClassID();
}

//============================================================
// <T>�жϽڵ��Ƿ�Ϊ������</T>
//============================================================
TBool F3dsExporter::IsBone(INode* piNode){
   // �жϽڵ�
   if(NULL == piNode){
      return EFalse;
   }
   if(piNode->IsRootNode()){
      return EFalse;
   }
   TFsText name = piNode->GetName();
   // �ж��Ƿ����
   if(name.StartsWith(TC("cl_"))){
      return ETrue;
   }
   // �ж��Ƿ����
   if(name.StartsWith(TC("bn_"))){
      return ETrue;
   }
   // ������ö���
   ObjectState objectState = piNode->EvalWorldState(0);
   Object* pObject = objectState.obj;
   if(NULL == pObject){
      return EFalse;
   }
   SClass_ID superClassId = pObject->SuperClassID();
   Class_ID classId = pObject->ClassID();
   // �����ж�
   if(GEOMOBJECT_CLASS_ID == superClassId){
      return EFalse;
   }
   if(BONE_OBJ_CLASSID == classId){
      return ETrue;
   }
   if(Class_ID(BONE_CLASS_ID, 0) == classId){
      return ETrue;
   }
   if(Class_ID(DUMMY_CLASS_ID, 0) == classId){
      return EFalse;
   }
   // �ؼ�����
   Control* pControl = piNode->GetTMController();
   if(BIPSLAVE_CONTROL_CLASS_ID == pControl->ClassID() || BIPBODY_CONTROL_CLASS_ID == pControl->ClassID()){
      return ETrue;
   }
   return EFalse;
} 

//============================================================
ISkin* F3dsExporter::FindSkinModifier(INode* piNode){
   if(NULL == piNode){
      return NULL;
   }
   Object* pObject = piNode->GetObjectRef();
   if(NULL == pObject){
      return NULL;
   }
   while(pObject && (GEN_DERIVOB_CLASS_ID == pObject->SuperClassID())){
      IDerivedObject* pDerivedObject = (IDerivedObject*)(pObject);
      TInt32 count = pDerivedObject->NumModifiers();
      for(TInt32 n = 0; n < count; n++){
         Modifier* pModifier = pDerivedObject->GetModifier(n);
         if(SKIN_CLASSID == pModifier->ClassID()){
            return (ISkin*)pModifier->GetInterface(I_SKIN);
         }
      }
      pObject = pDerivedObject->GetObjRef();
   }
   return NULL;
}

//============================================================
Modifier* F3dsExporter::FindPhysiqueModifier(INode* piNode){
   if(NULL == piNode){
      return NULL;
   }
   Object* pObject = piNode->GetObjectRef();
   if(NULL == pObject){
      return NULL;
   }
   while(pObject && (GEN_DERIVOB_CLASS_ID == pObject->SuperClassID())){
      IDerivedObject* pDerivedObject = (IDerivedObject*)(pObject);
      TInt32 count = pDerivedObject->NumModifiers();
      for(TInt32 n = 0; n < count; n++){
         Modifier* pModifier = pDerivedObject->GetModifier(n);
         if(Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B) == pModifier->ClassID()){
            return pModifier;
         }
      }
      pObject = pDerivedObject->GetObjRef();
   }
   return NULL;
}

//============================================================
// <T>�洢������Ϣ��</T>
//
// @param piNode �ڵ�
// @param pTexturesNode ���ýڵ�
// @param pMtl ����
//============================================================
void F3dsExporter::ConvertTextures(INode* piNode, FXmlNode* pTexturesNode, Mtl* pMtl){
   // ��ȡ��������ʵ���ͼ
   TInt32 countSubTexmaps = pMtl->NumSubTexmaps();
   for(TInt32 n = 0; n < countSubTexmaps; n++){
      Texmap* pTexmap = pMtl->GetSubTexmap(n);
      if(NULL != pTexmap){
         Matrix3 uvTransform;
         pTexmap->GetUVTransform(uvTransform);
         // �����ͼ
         TInt index = pTexturesNode->Nodes()->Count();
         FXmlNode* pTexmapNode = pTexturesNode->CreateNode(TC("Texture"));
         pTexmapNode->SetInt(TC("index"), index);
         pTexmapNode->Set(TC("name"), (TCharC*)pTexmap->GetName());
         pTexmapNode->Set(TC("full_name"), (TCharC*)pTexmap->GetFullName());
         pTexmapNode->Set(TC("slot_name"), (TCharC*)pMtl->GetSubTexmapSlotName(n));
         // ���ͼƬ��ͼ
         if(Class_ID(BMTEX_CLASS_ID, 0x00) == pTexmap->ClassID()){
            BitmapTex* pBitmapTex = (BitmapTex*)pTexmap;
            FXmlNode* pBitmapNode = pTexmapNode->CreateNode(TC("Bitmap"));
            pBitmapNode->Set(TC("file_name"), pBitmapTex->GetMapName());
            //StdUVGen* pGen = pBitmapTex->GetUVGen();
            // ���ͼƬ
            Bitmap* pBitmap = pBitmapTex->GetBitmap(0);
            if(NULL != pBitmap){
               //TInt width = pBitmap->Width();
               //TInt height = pBitmap->Height();
               //pBitmapNode->SetInt("width", width);
               //pBitmapNode->SetInt("height", height);
            }
         }
      }
   }
}

//============================================================
// <T>�洢������Ϣ��</T>
//
// @param piNode �ڵ�
// @param pNode ���ýڵ�
// @param pMtl ����
//============================================================
void F3dsExporter::ConvertMaterial(INode* piNode, FXmlNode* pConfig, Mtl* pMtl){
   // ��ò���
   pConfig->Set(TC("name"), (TCharC*)pMtl->GetName());
   pConfig->Set(TC("full_name"), (TCharC*)pMtl->GetFullName());
   // �����������ɫ
   Color diffuse = pMtl->GetDiffuse();
   FXmlNode* pDiffuseNode = pConfig->CreateNode(TC("Diffuse"));
   R3dsExporter::StoreColor(pDiffuseNode, diffuse);
   // ��û�����ɫ
   Color ambient = pMtl->GetAmbient();
   FXmlNode* pAmbientNode = pConfig->CreateNode(TC("Ambient"));
   R3dsExporter::StoreColor(pAmbientNode, ambient);
   // ��ø߹���ɫ
   Color specular = pMtl->GetSpecular();
   FXmlNode* pSpecularNode = pConfig->CreateNode(TC("Specular"));
   R3dsExporter::StoreColor(pSpecularNode, specular);
   // ����Է�����ɫ
   if(pMtl->GetSelfIllumColorOn()){
      Color emissive = pMtl->GetSelfIllumColor();
      FXmlNode* pEmissiveNode = pConfig->CreateNode(TC("Emissive"));
      R3dsExporter::StoreColor(pEmissiveNode, emissive);
   }
   // ���͸����
   FXmlNode* pXParencyNode = pConfig->CreateNode(TC("XParency"));
   pXParencyNode->SetFloat(TC("value"), pMtl->GetXParency());
   // ��÷���� (�ٷֱ�)
   FXmlNode* pShininessNode = pConfig->CreateNode(TC("Shininess"));
   pShininessNode->SetFloat(TC("value"), pMtl->GetShininess());
   pShininessNode->SetFloat(TC("strength"), pMtl->GetShinStr());
   // ��ñ�׼����
   if(Class_ID(DMTL_CLASS_ID, 0) == pMtl->ClassID()){
      StdMat* pMat = (StdMat*)pMtl;
      pConfig->Set(TC("class"), TC("standard"));
      // ��ò�͸���� (�ٷֱ�)
      FXmlNode* pOpacityNode = pConfig->CreateNode(TC("Opacity"));
      pOpacityNode->SetFloat(TC("value"), pMat->GetOpacity(0));
   }
   // ��ö���ʲ���
   if(Class_ID(MULTI_CLASS_ID, 0) == pMtl->ClassID()){
      MultiMtl* pMulti = (MultiMtl*)pMtl;
      pConfig->Set(TC("class"), TC("multiple"));
      // ����Ӳ����б�
      TInt32 countSubMtls = pMtl->NumSubMtls();
      pConfig->SetInt(TC("submtls_count"), countSubMtls);
      for(TInt32 n = 0; n < countSubMtls; n++){
         Mtl* pSubMtl = pMtl->GetSubMtl(n);
         if(NULL != pSubMtl){
            FXmlNode* pSubMaterialNode = pConfig->CreateNode(TC("SubMaterial"));
            pSubMaterialNode->SetInt(TC("id"), n);
            ConvertMaterial(piNode, pSubMaterialNode, pSubMtl);
         }
      }
   }
   // ��ȡ��������ʵ���ͼ�б�
   TInt countSubTexmaps = pMtl->NumSubTexmaps();
   if(countSubTexmaps > 0){
      FXmlNode* pTexturesNode = pConfig->CreateNode(TC("Textures"));
      ConvertTextures(piNode, pTexturesNode, pMtl);
      pTexturesNode->SetInt(TC("count"), pTexturesNode->Nodes()->Count());
      pTexturesNode->SetInt(TC("sub_count"), countSubTexmaps);
   }
}

//============================================================
// <T>�洢������Ϣ��</T>
//
// @param piNode �ڵ�
// @param pTriObject �����ζ���
// @param pNode ���ýڵ�
//============================================================
void F3dsExporter::ConvertBone(INode* piNode){
   // ��������
   FXmlNode* pTrackNode = _pAnimationNode->CreateNode(TC("Track"));
   Interval range = _piInterface->GetAnimRange();
   TInt32 tick = GetTicksPerFrame();
   TInt32 frameCount = range.Duration() / tick;
   pTrackNode->Set(TC("name"), (TCharC*)piNode->GetName());
   pTrackNode->SetInt(TC("bone_id"), _pBones->IndexOf(piNode));
   // ��ó�ʼʱ��ľ���
   //Matrix3 initMatrix = piNode->GetNodeTM(0);
   //initMatrix.NoScale();
   //initMatrix.Invert();
   // �洢ÿһ�������
   for(TInt32 n = 0; n < frameCount; n++){
      TimeValue time = tick * n;
      // ���ָ��ʱ��ľ���
      Matrix3 nodeMatrix = piNode->GetNodeTM(time);
      //nodeMatrix.NoScale();
      //nodeMatrix.Invert();
      Matrix3 objectMatrix = piNode->GetObjectTM(time);
      // ������
      FXmlNode* pFrameNode = pTrackNode->CreateNode(TC("Frame"));
      pFrameNode->SetInt(TC("index"), n);
      R3dsExporter::StoreMatrix3(pFrameNode, TC("node"), nodeMatrix);
      if(!(nodeMatrix == objectMatrix)){
         R3dsExporter::StoreMatrix3(pFrameNode, TC("object"), objectMatrix);
      }
   }
}

//============================================================
// <T>�洢�����Ӧ������Ȩ����Ϣ��</T>
//============================================================
void F3dsExporter::ConvertMeshBones(INode* piNode, FXmlNode* pSkinNode, Mesh* pMesh, ISkin* piSkin){
   TInt vertexCount = pMesh->getNumVerts();
   ISkinContextData* piSkinContext = piSkin->GetContextInterface(piNode);
   // �洢���й����ڵ�
   TInt32 boneCount = piSkin->GetNumBones();
   pSkinNode->SetInt(TC("vertex_count"), vertexCount);
   pSkinNode->SetInt(TC("bone_count"), boneCount);
   for(TInt32 n=0; n<boneCount; n++){
      INode* piBoneNode = piSkin->GetBone(n);
      if(NULL != piBoneNode){
         if(!_pBones->Contains(piBoneNode)){
            _pBones->Push(piBoneNode);
         }
      }
   }
   // ��ù���Ȩ��
   for(TInt32 v=0; v<vertexCount; v++){
      TInt boneCount = piSkinContext->GetNumAssignedBones(v);
      if(boneCount > 0){
         FXmlNode* pVertexNode = pSkinNode->CreateNode(TC("Vertex"));
         pVertexNode->SetInt(TC("id"), v);
         for(TInt32 b = 0; b < boneCount; b++){
            FXmlNode* pBoneNode = pVertexNode->CreateNode(TC("Bone"));
            TInt32 boneId = piSkinContext->GetAssignedBone(v, b);
            INode* piBone = piSkin->GetBone(boneId);
            TFloat boneWeight = piSkinContext->GetBoneWeight(v, b);
            pBoneNode->SetInt(TC("id"), _pBones->IndexOf(piBone));
            pBoneNode->SetFloat(TC("weight"), boneWeight);
         }
      }
   }
}

//============================================================
// <T>�洢��������Ϣ��</T>
//
// @param piNode �ڵ�
// @param pTriObject �����ζ���
// @param pNode ���ýڵ�
//============================================================
void F3dsExporter::ConvertTriangleObject(INode* piNode, FXmlNode* pTriangleNode, TriObject* pTriObject){
   // �������
   TInt materialId = -1;
   Mtl* pMtl = piNode->GetMtl();
   if(NULL != pMtl){
      TUint materialAddress = (TUint)pMtl;
      materialId = _pMaterials->IndexOf(materialAddress);
      if(ENotFound == materialId){
         materialId = _pMaterials->Count();
         _pMaterials->Push(materialAddress);
         // �洢����
         FXmlNode* pMaterialNode= _pMaterialsNode->CreateNode(TC("Material"));
         pMaterialNode->SetInt(TC("id"), materialId);
         ConvertMaterial(piNode, pMaterialNode, pMtl);
      }
   }
   // ���������ͼԪ
   Mesh* pMesh = &pTriObject->GetMesh();
   MO_ASSERT(pMesh);
   pMesh->buildNormals();
   //MNMesh* pMnMesh = (MNMesh*)pMesh;
   // �洢������Ϣ
   TInt32 countMaps = pMesh->getNumMaps();
   pTriangleNode->SetInt(TC("material_id"), materialId);
   pTriangleNode->SetInt(TC("map_count"), countMaps);
   if(countMaps > 0){
      FXmlNode* pMapsNode = pTriangleNode->CreateNode(TC("Maps"));
      pMapsNode->SetInt(TC("count"), countMaps);
      for(TInt32 n = 0; n < countMaps; n++){
         MeshMap& map = pMesh->Map(n);
         FXmlNode* pMapNode = pMapsNode->CreateNode(TC("Map"));
         pMapNode->SetInt(TC("vertice_count"), map.getNumVerts());
         pMapNode->SetInt(TC("face_count"), map.getNumFaces());
      }
   }
   // �洢�������� (Vertex)
   TInt32 numVerts = pMesh->getNumVerts();
   pTriangleNode->SetInt(TC("vertex_count"), numVerts);
   pTriangleNode->SetInt(TC("normal_count"), pMesh->normalCount);
   FXmlNodeArray* pVertexNodes = MO_CREATE(FXmlNodeArray);
   if(numVerts > 0){
      MO_DEBUG(TC("Triangle mesh vertices. (mesh=0x%08X, vertices=%d)"), pMesh, numVerts);
      FXmlNode* pVerticesNode = pTriangleNode->CreateNode(TC("Vertexs"));
      pVerticesNode->SetInt(TC("count"), numVerts);
      for(TInt32 n = 0; n < numVerts; n++){
         FXmlNode* pVertexNode = pVerticesNode->CreateNode(TC("Vertex"));
         pVertexNode->SetInt(TC("id"), n);
         pVertexNodes->Push(pVertexNode);
         // �洢��
         Point3& vertex = pMesh->getVert(n);
         FXmlNode* pPositionNode = pVertexNode->CreateNode(TC("Position"));
         R3dsExporter::StorePoint3(pPositionNode, vertex);
         // TODO: ��ö���ķ��� (�Ͷ��������һ��)
         Point3& normal = pMesh->getNormal(n);
         FXmlNode* pNormalNode = pVertexNode->CreateNode(TC("Normal"));
         R3dsExporter::StorePoint3(pNormalNode, normal);
      }
   }
   // �洢������ɫ (Vertice Colors)
   TInt32 numVertCol = pMesh->getNumVertCol();
   pTriangleNode->SetInt(TC("color_count"), numVertCol);
   if(numVertCol > 0){
      MO_DEBUG(TC("Triangle mesh vertice colors. (meth=0x%08X, vertexColors=%d)"), pMesh, numVertCol);
      for(TInt32 n = 0; n < numVertCol; n++){
         FXmlNode* pVertexNode = pVertexNodes->Get(n);
         if(NULL != pVertexNode){
            VertColor& color = pMesh->vertCol[n];
            FXmlNode* pColorNode = pVertexNode->CreateNode(TC("Color"));
            R3dsExporter::StorePoint3(pColorNode, color);
         }
      }
   }
   // �洢�������� (Faces)
   TInt32 numFaces = pMesh->getNumFaces();
   pTriangleNode->SetInt(TC("face_count"), numFaces);
   pTriangleNode->SetInt(TC("uv_count"), pMesh->getNumTVerts());
   if(numFaces > 0){
      MO_DEBUG(TC("Triangle mesh faces. (meth=0x%08X, faces=%d)"), pMesh, numFaces);
      FXmlNode* pFacesNode = pTriangleNode->CreateNode(TC("Faces"));
      pFacesNode->SetInt(TC("count"), numFaces);
      for(TInt32 n = 0; n < numFaces; n++){
         FXmlNode* pFaceNode = pFacesNode->CreateNode(TC("Face"));
         pFaceNode->SetInt(TC("id"), n);
         // �洢������ĵ�����
         Face& face = pMesh->faces[n];
         FXmlNode* pIndexNode = pFaceNode->CreateNode(TC("Index"));
         pIndexNode->SetInt(TC("v0"), face.v[0]);
         pIndexNode->SetInt(TC("v1"), face.v[1]);
         pIndexNode->SetInt(TC("v2"), face.v[2]);
         // ���������ķ���
         Point3& normal = pMesh->getFaceNormal(n);
         FXmlNode* pNormalNode = pFaceNode->CreateNode(TC("Normal"));
         R3dsExporter::StorePoint3(pNormalNode, normal);
         // �洢����������ĵ�����(T0)
         TVFace& tvFace = pMesh->tvFace[n];
         FXmlNode* pVertexNode = pVertexNodes->Get(face.v[0]);
         if(NULL != pVertexNode){
            FXmlNode* pCoordNode = pVertexNode->FindNode(TC("Coord"));
            if(NULL == pCoordNode){
               pCoordNode = pVertexNode->CreateNode(TC("Coord"));
               R3dsExporter::StorePoint3(pCoordNode, pMesh->getTVert(tvFace.t[0]));
            }
         }
         // �洢����������ĵ�����(T1)
         pVertexNode = pVertexNodes->Get(face.v[1]);
         if(NULL != pVertexNode){
            FXmlNode* pCoordNode = pVertexNode->FindNode(TC("Coord"));
            if(NULL == pCoordNode){
               pCoordNode = pVertexNode->CreateNode(TC("Coord"));
               R3dsExporter::StorePoint3(pCoordNode, pMesh->getTVert(tvFace.t[1]));
            }
         }
         // �洢����������ĵ�����(T2)
         pVertexNode = pVertexNodes->Get(face.v[2]);
         if(NULL != pVertexNode){
            FXmlNode* pCoordNode = pVertexNode->FindNode(TC("Coord"));
            if(NULL == pCoordNode){
               pCoordNode = pVertexNode->CreateNode(TC("Coord"));
               R3dsExporter::StorePoint3(pCoordNode, pMesh->getTVert(tvFace.t[2]));
            }
         }
      }
   }
   //Tangents
   // ������Ƥ��Ӧ�Ĺ�������
   ISkin* piSkin = FindSkinModifier(piNode);
   if(NULL != piSkin){
      pTriangleNode->SetInt(TC("bone_count"), piSkin->GetNumBones());
      // �洢����Ȩ��
      FXmlNode* pSkinNode = pTriangleNode->CreateNode(TC("Skin"));
      ConvertMeshBones(piNode, pSkinNode, pMesh, piSkin);
   }
}

//============================================================
// <T>�洢��������Ϣ��</T>
//
// @param piNode �ڵ�
// @param pGeomObject ������
// @param pNode ���ýڵ�
//============================================================
void F3dsExporter::ConvertGeomObject(INode* piNode, FXmlNode* pNode, GeomObject* pGeomObject){
   pNode->Set(TC("name"), piNode->GetName());
   // ��ýڵ�
   if(pGeomObject->CanConvertToType(triObjectClassID)){
      // ���������ͼԪ
      TriObject* pTriObject = (TriObject*)pGeomObject->ConvertToType(_time, triObjectClassID);
      if(NULL != pTriObject){
         ConvertTriangleObject(piNode, pNode, pTriObject);
      }
   }
   // �����ϸ��ʶ
   /*Class_ID classId = pGeomObject->ClassID();
   if(EPOLYOBJ_CLASS_ID == classId){
      PolyObject* pPolyObject = (PolyObject*)pGeomObject;
      MNMesh* pMeth = &pPolyObject->GetMesh();
      if(NULL != pMeth){
         logger.Debug(this, _T("ConvertGeomObject"), _T("pMeth=0x%08X"), pMeth);
      }
      Mtl* pMtl = piNode->GetMtl();
      if(NULL != pMtl){
         TString mtlName((TChar8C*)pMtl->GetName().data());
         //pMtl->GetAmbient();
         //pMtl->GetDiffuse();
         logger.Debug(this, _T("ConvertGeomObject"), _T("Mtl=0x%08X, name=%s"), pMtl, mtlName.MemoryC());
      }
   }
   if(EDITTRIOBJ_CLASS == classId){
      TriObject* pTriObject = (TriObject*)pGeomObject;
      //if(NULL != pMeth){
      //   logger.Debug(this, _T("ConvertGeomObject"), _T("Object is EDITTRIOBJ pMeth=0x%08X"), pMeth);
      //}
   }
   if(TRIOBJ_CLASS == classId){
   }
   if(BOXOBJ_CLASS == classId){
      /*if(pObject->CanConvertToType(triID)){
         TriObject* pTriObject = (TriObject*)pObject->ConvertToType(0, triID);
         Mesh mesh = pTriObject->mesh;
         TInt numVerts = mesh.getNumVerts();
         _logger.Debug(this, _T("callback"), _T("Num verts %d."), numVerts);
      }
   }*
}

//============================================================
void F3dsExporter::ConvertSkeleton(INode* piNode, FXmlNode* pParentNode){
   FXmlNode* pBoneNode = pParentNode;
   if(_pBones->Contains(piNode)){
      pBoneNode = pParentNode->CreateNode(TC("Bone"));
      pBoneNode->SetInt(TC("id"), _pBones->IndexOf(piNode));
      pBoneNode->Set(TC("name"), piNode->GetName());
      pBoneNode->SetBool(TC("flag"), piNode->GetBoneNodeOnOff());
      pBoneNode->SetBool(TC("align"), piNode->GetBoneAutoAlign());
      pBoneNode->SetInt(TC("axis"), piNode->GetBoneAxis());
      pBoneNode->SetBool(TC("axis_flip"), piNode->GetBoneAxisFlip());
      pBoneNode->SetBool(TC("freeze"), piNode->GetBoneFreezeLen());
      pBoneNode->SetInt(TC("scale"), piNode->GetBoneScaleType());
   }
   // ���������ӽڵ�
   TInt32 count = piNode->NumberOfChildren();
   for(TInt32 n = 0; n < count; n++){
      // ����ӽڵ�
      INode* piChild = piNode->GetChildNode(n);
      if(NULL != piChild){
         ConvertSkeleton(piChild, pBoneNode);
      }
   }
}

//============================================================
void F3dsExporter::ConvertNode(INode* piNode, FXmlNode* pNode, TInt level){
   TUint32 superClassId = piNode->SuperClassID();
   TCharC* pNodeName = piNode->GetName();
   TInt32 count = piNode->NumberOfChildren();
   // ������
	ObjectState objectState = piNode->EvalWorldState(_time); 
   Object* pObject = objectState.obj;
   TCharC* pObjectName = TC("");
   Class_ID classId;
   if(NULL != pObject){
      superClassId = pObject->SuperClassID();
      classId = pObject->ClassID();
      pObjectName = pObject->GetObjectName();
   }
   TCharC* pSuperClassName = R3dsClass::GetSuperClassName(superClassId);
   TCharC* pClassName = R3dsClass::GetClassName(classId);
   pNode->Set(TC("name"), piNode->GetName());
   pNode->Set(TC("object_name"), pObjectName);
   pNode->Set(TC("super_type"), pSuperClassName);
   pNode->Set(TC("type"), pClassName);
   TFsDump levelSpace;
   levelSpace.Append(TC("   "), level);
   MO_DEBUG(TC("%sParse node=0x%08X, super=%s[0x%08X], type=%s[0x%08X-0x%08X], name=%s, child=%d, object=%s)"),
         levelSpace.MemoryC(), piNode, pSuperClassName, superClassId,
         pClassName, classId.PartA(), classId.PartB(), pNodeName, count, pObjectName);
   // ���ȡ��״̬
   if(_piInterface->GetCancel()){
      pNode->Set(TC("is_valid"), TC("false"));
   }
   // �ж��Ƿ�Ϊ����
   if(IsBone(piNode)){
      pNode->Set(TC("is_bone"), TC("true"));
   }
   // �ж��Ƿ�����Ƥ
   ISkin* piSkin = FindSkinModifier(piNode);
   if(NULL != piSkin){
      pNode->Set(TC("is_skin"), TC("true"));
   }
   // �Ƿ��б���
   Object* ptr = piNode->GetObjectRef();
   if(NULL != ptr){
      TCharC* pReferSuperClassName = R3dsClass::GetSuperClassName(ptr->SuperClassID());
      TCharC* pReferClassName = R3dsClass::GetClassName(ptr->ClassID());
      pNode->Set(TC("refer_super_type"), pReferSuperClassName);
      pNode->Set(TC("refer_type"), pReferClassName);
      Modifier* pModifier = FindPhysiqueModifier(piNode);
      if(NULL != pModifier){
         pNode->Set(TC("modifier"), (TCharC*)pModifier->GetName());
      }
   }
   // ����ָ�����͵Ľڵ�
   if(NULL != pObject){
      if(GEOMOBJECT_CLASS_ID == superClassId){
         TInt meshId = _pMeshNode->Nodes()->Count();
         FXmlNode* pSubMeshNode = _pMeshNode->CreateNode(TC("SubMesh"));
         pSubMeshNode->SetInt(TC("id"), meshId);
         ConvertGeomObject(piNode, pSubMeshNode, (GeomObject*)pObject);
      }
   }
   // ���������ӽڵ�
   for(TInt32 n = 0; n < count; n++){
      // ����ӽڵ�
      INode* piChild = piNode->GetChildNode(n);
      if(NULL != piChild){
         FXmlNode* pChild = pNode->CreateNode();
         ConvertNode(piChild, pChild, level + 1);
      }
   }
}

//============================================================
// <T>�洢������Ϣ��</T>
//
// @param pScene ���ýڵ�
//============================================================
void F3dsExporter::ConvertScene(FXmlNode* pScene){
   // ��ö���ʱ�䷶Χ
   Interval range = _piInterface->GetAnimRange();
   pScene->SetInt(TC("range_start"), range.Start());
   pScene->SetInt(TC("range_end"), range.End());
   // ��ö������
   TInt tick = GetTicksPerFrame();
   pScene->SetInt(TC("frame_tick"), tick);
   // ���֡��
   pScene->SetInt(TC("frame_count"), _piInterface->GetAnimRange().Duration() / tick);
   // ����ļ���
   pScene->Set(TC("file_path"), (TCharC*)_piInterface->GetCurFilePath());
   pScene->Set(TC("file_name"), (TCharC*)_piInterface->GetCurFileName());
}

//============================================================
// <T>ת������Ϊ���ýڵ㡣</T>
//
// @param pConfig ���ýڵ�
//============================================================
void F3dsExporter::Convert(){
   // ���񶯻���Ϣ
   //ConvertScene(_pSceneNode);
   // ת�����нڵ�
   INode* piRoot = _piInterface->GetRootNode();
   if(NULL != piRoot){
      ConvertNode(piRoot, _pStructNode, 0);
   }
   // ���ò����б���Ϣ
   _pMaterialsNode->SetInt(TC("count"), _pMaterialsNode->Nodes()->Count());
   // ���ɹ����ڵ�ṹ
   if(NULL != piRoot){
      ConvertSkeleton(piRoot, _pSkeletonNode);
   }
   // �洢���й�������
   Interval range = _piInterface->GetAnimRange();
   TInt tick = GetTicksPerFrame();
   TInt frameCount = range.Duration() / tick;
   _pAnimationNode->SetInt(TC("frame_tick"), tick);
   _pAnimationNode->SetInt(TC("frame_count"), frameCount);
   _pAnimationNode->SetInt(TC("frame_start"), range.Start());
   _pAnimationNode->SetInt(TC("frame_end"), range.End());
   _pAnimationNode->SetInt(TC("bone_count"), _pBones->Count());
   if(!_pBones->IsEmpty()){
      TVectorIteratorC<INode*> iterator = _pBones->IteratorC();
      while(iterator.Next()){
         ConvertBone(*iterator);
      }
   }
   // ���������б���Ϣ
   _pMeshNode->SetInt(TC("count"), _pMeshNode->Nodes()->Count());
}
*/
MO_NAMESPACE_END;