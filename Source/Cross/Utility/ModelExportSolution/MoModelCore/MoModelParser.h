#pragma once

#include <scene.h>
#include "MoFbxDefine.h"
#include "MoFbxResource.h"

MO_NAMESPACE_BEGIN;

class FModelMesh;
class FModelScene;
class FModelManager;

//============================================================
// <T>FBX枚举。</T>
//============================================================
enum EFbxVertexAttribute{
   EFbxVertexAttribute_Position,
   EFbxVertexAttribute_Color0,
   EFbxVertexAttribute_Color1,
   EFbxVertexAttribute_Color2,
   EFbxVertexAttribute_Color3,
   EFbxVertexAttribute_Normal,
   EFbxVertexAttribute_Binormal,
   EFbxVertexAttribute_Tangent,
   EFbxVertexAttribute_Coord0,
   EFbxVertexAttribute_Coord1,
   EFbxVertexAttribute_Coord2,
   EFbxVertexAttribute_Coord3,
   EFbxVertexAttribute_Count,
};

//============================================================
// <T>FBX顶点信息。</T>
//============================================================
struct SModelVertex{
public:
   TInt index;
   SFloatPoint3 position;
   SFloatColor4 color;
   SFloatVector3 normal;
   SFloatVector3 binormal;
   SFloatVector3 tangent;
   SFloatPoint2 coord;
public:
   SModelVertex(){
   }
};
//............................................................
typedef FObjects<SModelVertex*> FModelVertexs;

//============================================================
// <T>FBX面信息。</T>
//============================================================
struct SModelFace{
public:
   TInt corners[3];
public:
   SModelFace(){
   }
};
//............................................................
typedef FObjects<SModelFace*> FModelFaces;

//============================================================
// <T>FBX网格。</T>
//============================================================
class MO_FBX_DECLARE FModelMesh : public FObject {
protected:
   TString _code;
   FModelScene* _pScene;
   const aiNode* _pAiNode;
   const aiMesh* _pAiMesh;
   TInt _vertexAttributeCount;
   TBool _vertexAttributes[EFbxVertexAttribute_Count];
   FModelVertexs* _pVertexs;
   FModelFaces* _pFaces;
public:
   FModelMesh();
   MO_ABSTRACT ~FModelMesh();
public:
   MO_SOURCE_GETTER(TCharC*, Code, _code);
   MO_SOURCE_GETSET(FModelScene*, Scene, _pScene);
   MO_SOURCE_GETSET(const aiNode*, AiNode, _pAiNode);
   MO_SOURCE_GETSET(const aiMesh*, AiMesh, _pAiMesh);
   MO_SOURCE_GETTER(FModelVertexs*, Vertexs, _pVertexs);
   MO_SOURCE_GETTER(FModelFaces*, Faces, _pFaces);
public:
   TResult Setup();
public:
   MO_INLINE TBool ContainsAttribute(EFbxVertexAttribute attributeCd){
      return _vertexAttributes[attributeCd];
   }
public:
   TResult ReadVertexPosition(TInt vertexIndex, SFloatPoint3* pPosition);
   TResult ReadVertexColor(TInt vertexIndex, TInt vertexCounter, SFloatColor4* pColor);
   TResult ReadVertexNormal(TInt vertexIndex, TInt vertexCounter, SFloatVector3* pNormal);
   TResult ReadVertexBinormal(TInt vertexIndex, TInt vertexCounter, SFloatVector3* pBinormal);
   TResult ReadVertexTangent(TInt vertexIndex, TInt vertexCounter, SFloatVector3* pTangent);
   TResult ReadVertexCoord(TInt layer, TInt vertexIndex, TInt vertexCounter, SFloatPoint2* pCoord);
   SModelVertex* SyncVertex(SFloatPoint3* pPosition, SFloatColor4* pColor, SFloatVector3* pNormal, SFloatPoint2* pCoord);
   TResult Serialize(IDataOutput* pOutput);
public:
   TResult Store(FFbxResModelMesh* pResMesh);
};
//............................................................
typedef FObjects<FModelMesh*> FModelMeshs;

//============================================================
// <T>FBX场景。</T>
//============================================================
class MO_FBX_DECLARE FModelScene : public FObject{
protected:
   TString _code;
   FModelManager* _pManager;
   const aiScene* _pAiScene;
   FModelMeshs* _pMeshs;
public:
   FModelScene();
   MO_ABSTRACT ~FModelScene();
public:
   MO_SOURCE_GETTER(TCharC*, Code, _code);
   MO_SOURCE_GETSET(FModelManager*, Manager, _pManager);
   MO_SOURCE_GETSET(const aiScene*, AiScene, _pAiScene);
   MO_SOURCE_GETTER(FModelMeshs*, Meshs, _pMeshs);
public:
   TResult Setup();
public:
   TResult ProcessMesh(const aiScene* pAiScene, const aiNode* pAiNode, const aiMesh* pAiMesh);
   TResult ProcessNode(const aiScene* pAiScene, const aiNode* pAiNode);
public:
   TResult Store(FFbxResModel* pResModel);
public:
   TResult LoadFile(TCharC* pFileName);
};

//============================================================
// <T>模型管理器。</T>
//============================================================
class MO_FBX_DECLARE FModelManager : public FObject, public MSingleton{
public:
   FModelManager();
   MO_ABSTRACT ~FModelManager();
public:
   FModelScene* OpenScene(TCharC* pFileName);
   TResult CloseScene(FModelScene* pScene);
public:
   TResult Setup();
};
//------------------------------------------------------------
class MO_FBX_DECLARE RModelManager : public RSingleton<FModelManager>{
};

MO_NAMESPACE_END;
