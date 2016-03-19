#include "MoModelParser.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>����FBX��������</T>
//============================================================
FModelManager::FModelManager(){
   //MO_CLEAR(_pFbxManager);
   //MO_CLEAR(_pFbxIoSettings);
}

//============================================================
// <T>����FBX��������</T>
//============================================================
FModelManager::~FModelManager() {
   //MO_DESTORY(_pFbxIoSettings);
   //MO_DESTORY(_pFbxManager);
}

//============================================================
// <T>��һ���ļ�������</T>
//============================================================
FModelScene* FModelManager::OpenScene(TCharC* pFileName){
   FModelScene* pScene = MO_CREATE(FModelScene);
   pScene->SetManager(this);
   pScene->LoadFile(pFileName);
   return pScene;
}

//============================================================
// <T>����һ���ļ�������</T>
//============================================================
TResult FModelManager::CloseScene(FModelScene* pScene){
   return ESuccess;
}

//Mesh processMesh(aiMesh* mesh, const aiScene* scene)
//{
//   vector<Vertex> vertices;
//   vector<int> indices;
//   vector<Texture> textures;
//
//   for(int i = 0; i < mesh->mNumVertices; i++)
//   {
//      Vertex vertex;
//      // Process vertex positions, normals and texture coordinates
//      glm::vec3 vector;
//      vector.x = mesh->mVertices[i].x;
//      vector.y = mesh->mVertices[i].y;
//      vector.z = mesh->mVertices[i].z;
//      vertex.Position = vector;
//
//      vector.x = mesh->mNormals[i].x;
//      vector.y = mesh->mNormals[i].y;
//      vector.z = mesh->mNormals[i].z;
//      vertex.Normal = vector;
//
//
//      if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates? assimp�������8����������ֻ�õ�һ������;
//      {
//         glm::vec2 vec;
//         vec.x = mesh->mTextureCoords[0][i].x;
//         vec.y = mesh->mTextureCoords[0][i].y;
//         vertex.TexCoords = vec;
//      }
//      else
//      {
//         vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//      }
//
//      vertices.push_back(vertex);
//   }
//   // Process indices
//   for(int i = 0; i < mesh->mNumFaces; i++)
//   {
//      aiFace face = mesh->mFaces[i];
//      for(int j = 0; j < face.mNumIndices; j++)
//      {
//         indices.push_back(face.mIndices[j]);
//      }
//   }
//
//   // Process material
//   if(mesh->mMaterialIndex >= 0)
//   {
//      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//      vector<Texture> diffuseMaps = this->loadMaterialTextures(material,
//         aiTextureType_DIFFUSE, TextureType::Texture_Diffuse);
//      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//
//
//      vector<Texture> specularMaps = this->loadMaterialTextures(material,
//         aiTextureType_SPECULAR, TextureType::Texture_Specular);
//      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//   }
//
//   return Mesh(vertices, indices, textures);
//}
//
//vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType texturetype)
//{
//   vector<Texture> textures;
//   for(int i = 0; i < mat->GetTextureCount(type); i++)
//   {
//      aiString str;
//      mat->GetTexture(type, i, &str);
//
//      Texture texture;
//      texture.id = 0;// TextureFromFile(str.C_Str(), this->directory);
//      texture.texturetype = texturetype;
//
//      memcpy(texture.path, str.data, str.length + 1);
//      textures.push_back(texture);
//   }
//   return textures;
//}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FModelManager::Setup(){
   //Assimp::Importer import;
   //const aiScene* scene = import.ReadFile("D:/Resource/xiong/xiong.fbx", aiProcess_Triangulate | aiProcess_FlipUVs);
   //processNode(scene, scene->mRootNode);

   // ����������
   //_pFbxManager = FbxManager::Create();
   //MO_ASSERT_POINTER(_pFbxManager);
   //// �������ò���
   //_pFbxIoSettings = FbxIOSettings::Create(_pFbxManager, IOSROOT);
   //_pFbxManager->SetIOSettings(_pFbxIoSettings);
   //// ������չ·��
   //FbxString path = FbxGetApplicationDirectory();
   //FbxString extension = "dll";
   //_pFbxManager->LoadPluginsDirectory(path.Buffer(), extension.Buffer());
   //// ��ð汾��
   //FbxManager::GetFileFormatVersion(_version.major, _version.minor, _version.revision);
   return TResult();
}

MO_NAMESPACE_END; 
