#include "Mo3dsDefine.h"
#include "Mo3dsExporter.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>���쳡����������</T>
//
// @param pDocument ����ĵ�
// @param piScene ����
// @param time ʱ��
// @param piInterface �ӿ�
// @return ����������
//============================================================
M3dsExporter::M3dsExporter(){
   // ���ñ���
   _piScene = NULL;
   _time = 0;
   _piInterface = NULL;
   _piRootNode = NULL;
   _pSceneNode = NULL;
   // ��������
   _pMaterials = MO_CREATE(FMaterialVector);
   // ��������ĵ�
   _pDocument = MO_CREATE(FXmlDocument);
   InnerInitialize(_pDocument->Root());
   // �����ļ���
   _pFileStream = MO_CREATE(FByteFile);
   _pFileStream->EnsureSize(1024*1024);
}

//============================================================
// <T>���쳡����������</T>
//
// @param pDocument ����ĵ�
// @param piScene ����
// @param time ʱ��
// @param piInterface �ӿ�
// @return ����������
//============================================================
M3dsExporter::M3dsExporter(IScene* piScene, TimeValue time, Interface* piInterface){
   // ���ñ���
   _piScene = piScene;
   _time = time;
   _piInterface = piInterface;
   _piRootNode = _piInterface->GetRootNode();
   // ��������
   _pMaterials = MO_CREATE(FMaterialVector);
   // ��������ĵ�
   _pDocument = MO_CREATE(FXmlDocument);
   _pFileStream = MO_CREATE(FByteFile);
   InnerInitialize(_pDocument->Root());
}

//============================================================
// <T>����������������</T>
//============================================================
M3dsExporter::~M3dsExporter(){
   MO_DELETE(_pMaterials);
   MO_DELETE(_pDocument);
   MO_DELETE(_pFileStream);
}

//============================================================
void M3dsExporter::InnerInitialize(FXmlNode* pConfig){
   // ���ø��ڵ�
   pConfig->SetName(TC("M3xExport"));
   pConfig->Set(TC("version"), TC("1.0"));
   // ��������
   _pSceneNode = pConfig->CreateNode(TC("Scene"));
   // �����б�ڵ�
   _pStructNode = _pSceneNode->CreateNode(TC("Struct"));
   // �����б�ڵ�
   _pMaterialsNode = _pSceneNode->CreateNode(TC("MaterialCollection"));
   // �����б�ڵ�
   _pMeshNode = _pSceneNode->CreateNode(TC("Mesh"));
   // �����ڵ�
   _pSkeletonNode = _pSceneNode->CreateNode(TC("Skeleton"));
   // �����ڵ�
   _pAnimationNode = _pSceneNode->CreateNode(TC("Animation"));
   // ��־�ڵ�
   _pLoggerNode = pConfig->CreateNode(TC("Logger"));
}

//============================================================
// <T>ת������Ϊ���ýڵ㡣</T>
//
// @param pConfig ���ýڵ�
//============================================================
void M3dsExporter::Convert(){
}

//============================================================
void M3dsExporter::SaveAs(TCharC* pFileName, TCharC* pEncoding){
   _pDocument->SetEncoding(pEncoding);
   _pDocument->SaveFile8(pFileName);
}

MO_NAMESPACE_END;