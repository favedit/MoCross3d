#include "MoFbxParser.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>����FBX��������</T>
//============================================================
FFbxManager::FFbxManager(){
   MO_CLEAR(_pFbxManager);
   MO_CLEAR(_pFbxIoSettings);
}

//============================================================
// <T>����FBX��������</T>
//============================================================
FFbxManager::~FFbxManager() {
   MO_DESTORY(_pFbxIoSettings);
   MO_DESTORY(_pFbxManager);
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FFbxManager::Setup(){
   // ����������
   _pFbxManager = FbxManager::Create();
   MO_ASSERT_POINTER(_pFbxManager);
   // �������ò���
   _pFbxIoSettings = FbxIOSettings::Create(_pFbxManager, IOSROOT);
   _pFbxManager->SetIOSettings(_pFbxIoSettings);
   // ������չ·��
   FbxString path = FbxGetApplicationDirectory();
   FbxString extension = "dll";
   _pFbxManager->LoadPluginsDirectory(path.Buffer(), extension.Buffer());
   // ��ð汾��
   FbxManager::GetFileFormatVersion(_version.major, _version.minor, _version.revision);
   return TResult();
}

MO_NAMESPACE_END; 
