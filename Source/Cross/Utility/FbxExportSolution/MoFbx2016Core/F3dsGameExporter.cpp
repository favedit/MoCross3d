#include "MoFbxParser.h"

MO_NAMESPACE_BEGIN;

/*
//============================================================
// <T>������Ϸ��������</T>
//============================================================
F3dsGameExporter::F3dsGameExporter(IScene* piScene, TimeValue time, Interface* piInterface) :
      M3dsExporter(piScene, time, piInterface){
   _pNodes = MO_CREATE(FGameNodeVector, 1024);
   _pMaterials = MO_CREATE(FGameMaterialVector, 256);
   _pBones = MO_CREATE(FGameBoneVector, 256);
   _pGeometrys = MO_CREATE(FGameGeometryVector);
   _pGeometrySet = MO_CREATE(FGameGeometrySet);
}

//============================================================
// <T>������Ϸ��������</T>
//============================================================
F3dsGameExporter::~F3dsGameExporter(){
   MO_DELETE(_pNodes);
   MO_DELETE(_pMaterials);
   MO_DELETE(_pBones);
   MO_DELETE(_pGeometrys);
   MO_DELETE(_pGeometrySet);
}

//============================================================
void F3dsGameExporter::ErrorProc(IGameError error){
   FXmlNode* pErrorNode = _pLoggerNode->CreateNode(TC("Error"));
   TFsLogger logger;
   TCharC* pMessage = GetLastIGameErrorText();
   logger.AppendFormat(TC("Raise error. (code=%d, message=%s)"), error, pMessage);
   pErrorNode->SetText(logger);
}

//============================================================
IGameScene* F3dsGameExporter::GameScene(){
   return _piGameScene;
}

//============================================================
IGameConversionManager* F3dsGameExporter::GameConversionManager(){
   return _piGameConversionManager;
}

//============================================================
FGameNodeVector* F3dsGameExporter::GameNodes(){
   return _pNodes;
}

//============================================================
FGameMaterialVector* F3dsGameExporter::GameMaterials(){
   return _pMaterials;
}

//============================================================
FGameBoneVector* F3dsGameExporter::GameBones(){
   return _pBones;
}

//============================================================
// <T>�洢���нڵ�ṹ��</T>
// <P>����ڵ�ӿ�û�л�ù�Object�ӿڣ����޷����Control�ӿڡ�</P>
//
// @param pNode ���ýڵ�
// @param piNode ��Ϸ�ڵ�
//============================================================
void F3dsGameExporter::ConvertStruct(FXmlNode* pNode, IGameNode* piNode){
   // �洢�ڵ㼯��
   TInt nodeId = piNode->GetNodeID();
   _pNodes->ExtendSet(nodeId, piNode);
   // �����Ϸ����
   INode* piMaxNode = piNode->GetMaxNode();
   // �洢��������
   pNode->SetInt(TC("id"), nodeId);
   if(NULL != piMaxNode){
      TInt buffId = piMaxNode->GetGBufID();
      if(buffId > 0){
         pNode->SetInt(TC("g_buff_id"), buffId);
      }
   }
   TFsName name = piNode->GetName();
   pNode->Set(TC("name"), name);
   if(piNode->IsTarget()){
      pNode->SetBool(TC("target"), true);
   }
   if(piNode->IsGroupOwner()){
      pNode->SetBool(TC("is_group"), true);
   }
   if(piNode->IsNodeHidden()){
      pNode->SetBool(TC("is_hidden"), true);
   }
   // �Ƿ������
   if(name.StartsWith(TC("cl_"))){
      _pBones->Push(piNode);
   }
   // ���������ӽڵ�
   TInt32 count = piNode->GetChildCount();
   if(count > 0){
      for(TInt32 n = 0; n < count; n++){
         IGameNode* piChildren = piNode->GetNodeChild(n);
         if(NULL != piChildren){
            ConvertStruct(pNode->CreateNode(TC("Node")), piChildren);
         }
      }
   }
}

//============================================================
void F3dsGameExporter::ConvertSubTexture(FXmlNode* pTextureNode, IGameMaterial* piMaterial, Texmap* pTexmap){
   //CStr className;
   //pTexmap->GetClassName(className);
   //pTextureNode->Set(TC("class"), className);
   pTextureNode->Set(TC("name"), pTexmap->GetName());
   pTextureNode->Set(TC("node_name"), pTexmap->NodeName());
   pTextureNode->Set(TC("full_name"), pTexmap->GetFullName());
   // ��ѯ�ӽڵ�
   //int count = pTexmap->NumSubTexmaps();
   //pTextureNode->SetInt("count", count);
   /*if(count > 0){
      FXmlNode* pSubTextureListNode = pTextureNode->CreateNode("TextureList");
      for(int n = 0; n < count; n++){
         Texmap* pSubTexmap = pTexmap->GetSubTexmap(n);
         FXmlNode* pSubTextureNode = pSubTextureListNode->CreateNode("Texture");
         ConvertSubTexture(pSubTextureNode, piMaterial, pSubTexmap);
      }
   }*
}

//============================================================
// <T>ת��������ͼ��</T>
//
// @param pTextureNode ����ڵ�
// @param piMaterial ���ʽӿ�
// @param piTextureMap ����ӿ�
//============================================================
void F3dsGameExporter::ConvertTexture(FXmlNode* pTextureNode, IGameMaterial* piMaterial, IGameTextureMap* piTextureMap){
   TInt32 slotIndex = piTextureMap->GetStdMapSlot();
   TFsName className = piTextureMap->GetClassName();
   // ������������
   pTextureNode->Set(TC("class"), className);
   pTextureNode->Set(TC("name"), (TCharC*)piTextureMap->GetMaxTexmap()->GetName());
   pTextureNode->Set(TC("slot_name"), (TCharC*)piMaterial->GetMaxMaterial()->GetSubTexmapSlotName(slotIndex));
   pTextureNode->Set(TC("texture_name"), piTextureMap->GetTextureName());
   pTextureNode->Set(TC("texture_class"), piTextureMap->GetTextureClass());
   pTextureNode->SetInt(TC("map_channel"), piTextureMap->GetMapChannel());
   pTextureNode->SetInt(TC("std_map_slot"), piTextureMap->GetStdMapSlot());
   // �����ļ�����
   if(className.Equals(TC("Bitmap"))){
      pTextureNode->Set(TC("file"), piTextureMap->GetBitmapFileName());
   }
   // ��ü�����
   if(piTextureMap->IsEntitySupported()){
      // ��ü�����(ClipU)
      IGameProperty* piClipU = piTextureMap->GetClipUData();
      if(NULL != piClipU){
         R3dsExporter::StoreProperty(pTextureNode->CreateNode(TC("ClipU")), TC("value"), piClipU);
      }
      // ��ü�����(ClipV)
      IGameProperty* piClipV = piTextureMap->GetClipVData();
      if(NULL != piClipV){
         R3dsExporter::StoreProperty(pTextureNode->CreateNode(TC("ClipV")), TC("value"), piClipV);
      }
      // ��ü�����(ClipW)
      IGameProperty* piClipW = piTextureMap->GetClipWData();
      if(NULL != piClipW){
         R3dsExporter::StoreProperty(pTextureNode->CreateNode(TC("ClipW")), TC("value"), piClipW);
      }
      // ��ü�����(ClipH)
      IGameProperty* piClipH = piTextureMap->GetClipHData();
      if(NULL != piClipH){
         R3dsExporter::StoreProperty(pTextureNode->CreateNode(TC("ClipH")), TC("value"), piClipH);
      }
   }
   // ��ȡ����
   IPropertyContainer* piPropertyContainer = piTextureMap->GetIPropertyContainer();
   if(NULL != piPropertyContainer){
      R3dsExporter::StoreProperties(pTextureNode, TC("PropertyList"), piPropertyContainer);
   }
   Texmap* pTexmap = piTextureMap->GetMaxTexmap();
   if(NULL != pTexmap){
      int count = pTexmap->NumSubTexmaps();
      if(count > 0){
         FXmlNode* pSubTextureListNode = pTextureNode->CreateNode(TC("TextureList"));
         pSubTextureListNode->SetInt(TC("count"), count);
         for(int n = 0; n < count; n++){
            Texmap* pSubTexmap = pTexmap->GetSubTexmap(n);
            if(NULL != pSubTexmap){
               FXmlNode* pSubTextureNode = pSubTextureListNode->CreateNode(TC("Texture"));
               ConvertSubTexture(pSubTextureNode, piMaterial, pSubTexmap);
            }
         }
      }
   }
}

//============================================================
// <T>ת��������Ϣ��</T>
//
// @param pMaterialNode ���ʽڵ�
// @param piMaterial ������Ϣ
//============================================================
void F3dsGameExporter::ConvertMaterial(FXmlNode* pMaterialNode, IGameMaterial* piMaterial){
   // ׷�Ӳ���
   _pMaterials->Push(piMaterial);
   // ��ò���
   //pMaterialNode->SetInt("id", _pMaterials->IndexOf(piMaterial));
   pMaterialNode->Set(TC("class"), piMaterial->GetMaterialClass());
   pMaterialNode->Set(TC("name"), piMaterial->GetMaterialName());
   // �洢���Լ���
   IPropertyContainer* piPropertyContainer = piMaterial->GetIPropertyContainer();
   if(NULL != piPropertyContainer){
      R3dsExporter::StoreProperties(pMaterialNode, TC("PropertyList"), piPropertyContainer);
   }
   // �����������ɫ
   IGameProperty* piDiffuse = piMaterial->GetDiffuseData();
   if(NULL != piDiffuse){
      R3dsExporter::StoreColorProperty(pMaterialNode->CreateNode(TC("Diffuse")), piDiffuse);
   }
   // ��û�����ɫ
   IGameProperty* piAmbient = piMaterial->GetAmbientData();
   if(NULL != piAmbient){
      R3dsExporter::StoreColorProperty(pMaterialNode->CreateNode(TC("Ambient")), piAmbient);
   }
   // ��ø߹���ɫ
   IGameProperty* piSpecular = piMaterial->GetSpecularData();
   if(NULL != piSpecular){
      R3dsExporter::StoreColorProperty(pMaterialNode->CreateNode(TC("Specular")), piSpecular);
   }
   IGameProperty* piSpecularLevel = piMaterial->GetSpecularLevelData();
   if(NULL != piSpecularLevel){
      R3dsExporter::StoreProperty(pMaterialNode->CreateNode(TC("SpecularLevel")), TC("value"), piSpecularLevel);
   }
   // ����Է�����ɫ
   IGameProperty* piEmissive = piMaterial->GetEmissiveData();
   if(NULL != piEmissive){
      R3dsExporter::StoreColorProperty(pMaterialNode->CreateNode(TC("Emissive")), piEmissive);
   }
   IGameProperty* piEmissiveAmt = piMaterial->GetEmissiveAmtData();
   if(NULL != piEmissiveAmt){
      R3dsExporter::StoreProperty(pMaterialNode->CreateNode(TC("EmissiveAmt")), TC("value"), piEmissiveAmt);
   }
   // ��ù����
   IGameProperty* piGlossiness = piMaterial->GetGlossinessData();
   if(NULL != piGlossiness){
      R3dsExporter::StoreProperty(pMaterialNode->CreateNode(TC("Glossiness")), TC("value"), piGlossiness);
   }
   // ��ò�͸���� (�ٷֱ�)
   IGameProperty* piOpacity = piMaterial->GetOpacityData();
   if(NULL != piOpacity){
      R3dsExporter::StoreProperty(pMaterialNode->CreateNode(TC("Opacity")), TC("value"), piOpacity);
   }
   // ��ȡ�����б�
   TInt32 textureCount = piMaterial->GetNumberOfTextureMaps();
   if(textureCount > 0){
      FXmlNode* pTexturesNode = pMaterialNode->CreateNode(TC("Textures"));
      for(TInt32 n = 0; n < textureCount; n++){
         IGameTextureMap* piTextureMap = piMaterial->GetIGameTextureMap(n);
         if(NULL != piTextureMap){
            FXmlNode* pTextureNode = pTexturesNode->CreateNode(TC("Texture"));
            pTextureNode->SetInt(TC("id"), n);
            ConvertTexture(pTextureNode, piMaterial, piTextureMap);
         }
      }
   }
   // ��ö���ʲ���
   if(piMaterial->IsMultiType()){
      TInt32 subCount = piMaterial->GetSubMaterialCount();
      for(TInt32 n = 0; n < subCount; n++){
         IGameMaterial* piSubMaterial = piMaterial->GetSubMaterial(n);
         if(NULL != piSubMaterial){
            FXmlNode* pSubMaterialNode = pMaterialNode->CreateNode(TC("Material"));
            pSubMaterialNode->SetInt(TC("id"), n);
            ConvertMaterial(pSubMaterialNode, piSubMaterial);
         }
      }
   }
}

//============================================================
// <T>�������в�����Ϣ��</T>
//============================================================
void F3dsGameExporter::ConvertMaterials(FXmlNode* pMaterialsNode){
   TInt32 count = _piGameScene->GetRootMaterialCount();
   pMaterialsNode->SetInt(TC("count"), count);
   for(TInt32 n = 0; n < count; n++){
      IGameMaterial* piMaterial = _piGameScene->GetRootMaterial(n);
      if(NULL != piMaterial){
         FXmlNode* pMaterialNode = pMaterialsNode->CreateNode(TC("Material"));
         ConvertMaterial(pMaterialNode, piMaterial);
      }
   }
}

//============================================================
// <T>ת��������Ϣ��</T>
//
// @param pMeshNode ����ڵ�
//============================================================
void F3dsGameExporter::ConvertMesh(FXmlNode* pMeshNode){
   Tab<IGameNode*> piMeshNodes = _piGameScene->GetIGameNodeByType(IGameObject::IGAME_MESH);
   //............................................................
   // �����Ч���񼯺�
   TInt32 count = piMeshNodes.Count();
   for(TInt32 n = 0; n < count; n++){
      IGameNode* piGameNode = piMeshNodes[n];
      // ��ù�������
      IGameObject* piObject = piGameNode->GetIGameObject();
      if(piObject == NULL){
         continue;
      }
      if(!piObject->IsRenderable()){
         continue;
      }
      // �������
      IGameMesh* piSubMesh = (IGameMesh*)piObject;
      if(!piSubMesh->InitializeData()){
         continue;
      }
      if(!piSubMesh->InitializeBinormalData()){
         continue;
      }
      // ����Ƿ�Ϊ����������
      TFsText nodeName = piGameNode->GetName();
      if(nodeName.StartsWith(MO_MESH_BONE_FIX)){
         continue;
      }
      // �Ż����㷨��
      piSubMesh->SetCreateOptimizedNormalList();
      // �洢�ڵ�
      TInt32 nodeId = piGameNode->GetNodeID();
      if(!_pGeometrys->Contains(piGameNode)){
         _pGeometrys->Push(piGameNode);
         _pGeometrySet->Set(nodeId, piGameNode);
      }
   }
   //............................................................
   // �����Ч���񼯺�
   TInt validCount = _pGeometrys->Count();
   pMeshNode->SetInt(TC("count"), validCount);
   _pFileStream->WriteInt32((TInt32)validCount);
   for(TInt n = 0; n < validCount; n++){
      IGameNode* piGameNode = _pGeometrys->Get(n);
      IGameMesh* piSubMesh = (IGameMesh*)piGameNode->GetIGameObject();
      // �洢������Ϣ
      F3dsGeometryExporter* pGeometryExporter = MO_CREATE(F3dsGeometryExporter, this, piGameNode, piSubMesh);
      pGeometryExporter->Convert(pMeshNode->CreateNode(TC("Geometry")));
      pGeometryExporter->Serialize(_pFileStream);
      MO_DELETE(pGeometryExporter);
   }
}

//============================================================
// <T>ת�����������</T>
//
// @param pParentNode ���ڵ�
// @param piNode ��Ϸ�ڵ�
//============================================================
void F3dsGameExporter::ConvertSkeleton(FXmlNode* pParentNode, IGameNode* piNode){
   FXmlNode* pBoneNode = pParentNode;
   // ��������ڵ�
   if(_pBones->Contains(piNode)){
      pBoneNode = pParentNode->CreateNode(TC("Bone"));
      TInt nodeId = piNode->GetNodeID();
      pBoneNode->SetInt(TC("bone_id"), nodeId);
      pBoneNode->Set(TC("name"), piNode->GetName());
   }
   // ���������ӽڵ�
   TInt32 count = piNode->GetChildCount();
   for(TInt32 n = 0; n < count; n++){
      // ����ӽڵ�
      IGameNode* piChild = piNode->GetNodeChild(n);
      if(piChild != NULL){
         ConvertSkeleton(pBoneNode, piChild);
      }
   }
}

//============================================================
// <T>�洢������Ϣ��</T>
//
// @param pScene ���ýڵ�
//============================================================
void F3dsGameExporter::ConvertScene(FXmlNode* pScene){
   // �洢������Ϣ
   TInt32 topCount = _piGameScene->GetTopLevelNodeCount();
   pScene->SetInt(TC("start_time"), _piGameScene->GetSceneStartTime());
   pScene->SetInt(TC("end_time"), _piGameScene->GetSceneEndTime());
   pScene->SetInt(TC("tick"), _piGameScene->GetSceneTicks());
   pScene->Set(TC("file"), _piGameScene->GetSceneFileName());
   // �洢������Ϣ
   ConvertMaterials(_pMaterialsNode);
   // �洢������Ϣ
   ConvertMesh(_pMeshNode);
   // �洢������Ϣ
   _pSkeletonNode->SetInt(TC("bone_count"), _pBones->Count());
   for(TInt32 n = 0; n < topCount; n++){
      IGameNode* piNode = _piGameScene->GetTopLevelNode(n);
      if(piNode != NULL){
         ConvertSkeleton(_pSkeletonNode, piNode);
      }
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
      TVectorIteratorC<IGameNode*> iterator = _pBones->IteratorC();
      while(iterator.Next()){
         F3dsGameTrackExporter* pTrackExporter = MO_CREATE(F3dsGameTrackExporter, this, *iterator);
         pTrackExporter->Convert(_pAnimationNode->CreateNode(TC("Track")));
         MO_DELETE(pTrackExporter);
      }
   }
}

//============================================================
// <T>ת������Ϊ���ýڵ㡣</T>
//
// @param pConfig ���ýڵ�
//============================================================
void F3dsGameExporter::Convert(){
   // ��������ļ���
   TInt find = _fileName.LastFind(TC("."));
   TFsFileName fileName = _fileName;
   fileName.SetLength(find);
   fileName.Append(TC(".msh"));
   MO_INFO(TC("Mesh data file export. (file_name=%s)"), (TCharC*)fileName);
   // ���ô���ص�
   //SetErrorCallBack(this);
   // ��������ϵ
   _piGameConversionManager = GetConversionManager();
   _piGameConversionManager->SetCoordSystem(IGameConversionManager::IGAME_D3D);
   // ��ʼ����Ϸ����
   _piGameScene = GetIGameInterface();
   _piGameScene->InitialiseIGame(_piRootNode, true);
   _piGameScene->SetStaticFrame(0);
   TInt32 topCount = _piGameScene->GetTopLevelNodeCount();
   // �洢�ڵ�ṹ
   TInt32 total = _piGameScene->GetTotalNodeCount();
   _pStructNode->SetInt(TC("total"), total);
   for(TInt32 n = 0; n < topCount; n++){
      IGameNode* piNode = _piGameScene->GetTopLevelNode(n);
      if(piNode != NULL){
         ConvertStruct(_pStructNode->CreateNode(TC("Node")), piNode);
      }
   }
   // �洢������Ϣ
   ConvertScene(_pSceneNode);
   // �ر��ļ���
   _pFileStream->SaveFile(fileName);
   // �ͷ��ڴ�
   _piGameScene->ReleaseIGame();
   MO_CLEAR(_piGameScene);
}
*/
MO_NAMESPACE_END;
