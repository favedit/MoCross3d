#pragma once

#include "MoFbxDefine.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>�������͡�</T>
//============================================================
enum EFbxData{
   EFbxData_Unknown,
   EFbxData_Boolean,
   EFbxData_Int8,
   EFbxData_Int16,
   EFbxData_Int32,
   EFbxData_Int64,
   EFbxData_Uint8,
   EFbxData_Uint16,
   EFbxData_Uint32,
   EFbxData_Uint64,
   EFbxData_Float16,
   EFbxData_Float32,
   EFbxData_Float64,
   EFbxData_String,
   EFbxData_Array,
   EFbxData_Struct,
   EFbxData_Structs,
   EFbxData_Object,
   EFbxData_Objects,
   EFbxData_Dictionary
};

//============================================================
// <T>��Դ����</T>
//============================================================
class MO_FBX_DECLARE FFbxResourceObject : public FObject{
protected:
   // ��������
   TString _typeName;
   // �汾
   TInt _version;
public:
   FFbxResourceObject();
   MO_ABSTRACT ~FFbxResourceObject();
public:
   MO_SOURCE_GETSET(TCharC*, TypeName, _typeName);
   MO_SOURCE_GETSET(TInt, Version, _version);
public:
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
};

//============================================================
// <T>��Դ�����</T>
//============================================================
class MO_FBX_DECLARE FFbxResourceComponent : public FFbxResourceObject{
protected:
   // Ψһ���
   TString _guid;
   // ����
   TString _code;
   // ��ǩ
   TString _label;
public:
   FFbxResourceComponent();
   MO_ABSTRACT ~FFbxResourceComponent();
public:
   MO_SOURCE_GETSET(TCharC*, Guid, _guid);
   MO_SOURCE_GETSET(TCharC*, Code, _code);
   MO_SOURCE_GETSET(TCharC*, Label, _label);
public:
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
   MO_ABSTRACT TResult SaveConfig(FXmlNode* pConfig);
};

//============================================================
// <T>��Դ����</T>
//============================================================
class MO_FBX_DECLARE FFbxResource : public FFbxResourceComponent{
public:
   FFbxResource();
   MO_ABSTRACT ~FFbxResource();
public:
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
   MO_ABSTRACT TResult SaveConfig(FXmlNode* pConfig);
};

//============================================================
// <T>��Դ��������</T>
//============================================================
class MO_FBX_DECLARE FFbxResStream : public FFbxResourceObject{
protected:
   // ����
   TString _code;
   // ����
   TInt _index;
   // Ԫ������
   TInt _elementDataCd;
   // Ԫ�ظ���
   TInt _elementCount;
   // ���ݿ��
   TInt _dataStride;
   // ���ݸ���
   TInt _dataCount;
   // ���ݳ���
   FByteStream* _pData; 
public:
   FFbxResStream();
   MO_ABSTRACT ~FFbxResStream();
public:
   MO_SOURCE_GETSET(TCharC*, Code, _code);
   MO_SOURCE_GETSET(TInt, Index, _index);
   MO_SOURCE_GETSET(TInt, ElementDataCd, _elementDataCd);
   MO_SOURCE_GETSET(TInt, ElementCount, _elementCount);
   MO_SOURCE_GETSET(TInt, DataStride, _dataStride);
   MO_SOURCE_GETSET(TInt, DataCount, _dataCount);
   MO_SOURCE_GETTER(FByteStream*, Data, _pData);
public:
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
};
//............................................................
typedef FObjects<FFbxResStream*> FFbxResStreams;

//============================================================
// <T>��Դ����</T>
//============================================================
class MO_FBX_DECLARE FFbxResModelMesh : public FFbxResourceComponent{
protected:
   // ����������
   FFbxResStreams* _pVertexStreams;
   FFbxResStreams* _pIndexStreams;
public:
   FFbxResModelMesh();
   MO_ABSTRACT ~FFbxResModelMesh();
public:
   MO_SOURCE_GETTER(FFbxResStreams*, VertexStreams, _pVertexStreams);
   MO_SOURCE_GETTER(FFbxResStreams*, IndexStreams, _pIndexStreams);
public:
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
   MO_ABSTRACT TResult SaveConfig(FXmlNode* pConfig);
};
//............................................................
typedef FObjects<FFbxResModelMesh*> FFbxResMeshs;

//============================================================
// <T>��Դģ�͡�</T>
//============================================================
class MO_FBX_DECLARE FFbxResModel : public FFbxResource{
protected:
   // ����������
   FFbxResMeshs* _pMeshs;
public:
   FFbxResModel();
   MO_ABSTRACT ~FFbxResModel();
public:
   MO_SOURCE_GETTER(FFbxResMeshs*, Meshs, _pMeshs);
public:
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
   MO_ABSTRACT TResult SaveConfig(FXmlNode* pConfig);
public:
   TResult SaveFile(TCharC* pFileName);
   TResult SaveConfigFile(TCharC* pFileName);
};

MO_NAMESPACE_END;
