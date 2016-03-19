#include "MoCrAsset.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FAssetConsole, FConsole);

//============================================================
// <T>������Դ����̨��</T>
//============================================================
FAssetConsole::FAssetConsole(){
   _pSpaces = MO_CREATE(FAssetSpaceDictionary);
}

//============================================================
// <T>������Դ����̨��</T>
//============================================================
FAssetConsole::~FAssetConsole(){
   MO_DELETE(_pSpaces);
}

//============================================================
// <T>�������Ʋ�����Դ�ռ䡣</T>
//
// @param pName ����
// @return ��Դ�ռ�
//============================================================
FAssetSpace* FAssetConsole::FindSpace(TCharC* pName){
   MO_CHECK(pName, return NULL);
   return _pSpaces->Find(pName);
}

//============================================================
// <T>�������ƽ�����Դ�ռ䡣</T>
//
// @param pName ����
// @return ��Դ�ռ�
//============================================================
TCharC* FAssetConsole::ParseSpace(TCharC* pName){
   MO_CHECK(pName, return NULL);
   FAssetSpace* pSpace = _pSpaces->Find(pName);
   if(pSpace != NULL){
      return pSpace->Directory();
   }
   return NULL;
}

//============================================================
// <T>ע��һ����Դ�ռ䡣</T>
//
// @param pSpace ��Դ�ռ�
// @return ������
//============================================================
TResult FAssetConsole::RegisterSpace(FAssetSpace* pSpace){
   MO_CHECK(pSpace, return ENull);
   _pSpaces->Set(pSpace->Name(), pSpace);
   return ESuccess;
}

//============================================================
// <T>ע��һ����Դ�ռ䡣</T>
//
// @param pName ����
// @param pDirectory Ŀ¼
// @return ������
//============================================================
TResult FAssetConsole::RegisterSpace(TCharC* pName, TCharC* pDirectory){
   MO_CHECK(pName, return ENull);
   MO_CHECK(pDirectory, return ENull);
   FAssetSpace* pSpace = FAssetSpace::InstanceCreate();
   pSpace->SetName(pName);
   pSpace->SetDirectory(pDirectory);
   _pSpaces->Set(pName, pSpace);
   return ESuccess;
}

//============================================================
// <T>ע��һ����Դ�ռ䡣</T>
//
// @param pName ����
// @return ������
//============================================================
TResult FAssetConsole::UnregisterSpace(TCharC* pName){
   MO_CHECK(pName, return ENull);
   _pSpaces->Remove(pName);
   return ESuccess;
}

//============================================================
// <T>�������ƽ�����ԴĿ¼��</T>
//
// @param pResult ���
// @param pPath ����
// @return ��ԴĿ¼
//============================================================
TResult FAssetConsole::ParsePath(MString* pResult, TCharC* pPath){
   MO_CHECK(pResult, return ENull);
   MO_CHECK(pPath, return ENull);
   TStringRefer path = pPath;
   TInt splitIndex = path.IndexOf(':');
   if(splitIndex == ENotFound){
      pResult->Append(pPath);
   }else{
      TFsName spaceName = path.LeftStrC(splitIndex);
      TFsPath subPath = path.MidStrC(splitIndex + 1);
      TCharC* pDirectory = ParseSpace(spaceName);
      MO_FATAL_CHECK(pDirectory, return ENull, TC("Parse space failure. (space=%s)"), (TCharC*)spaceName);
      pResult->Append(pDirectory);
      if(!subPath.StartsWith(TC("/"))){
         pResult->Append('/');
      }
      pResult->Append(subPath);
   }
   return ESuccess;
}

//============================================================
// <T>��һ����ԴĿ¼��</T>
//
// @param pDirectory Ŀ¼����
// @return ��ԴĿ¼
//============================================================
FAssetDirectory* FAssetConsole::OpenDirectory(TCharC* pDirectory){
   return NULL;
}

//============================================================
// <T>�ر�һ����ԴĿ¼��</T>
//
// @param pDirectory ��ԴĿ¼
// @return ������
//============================================================
TResult FAssetConsole::CloseDirectory(FAssetDirectory* pDirectory){
   MO_DELETE(pDirectory);
   return ESuccess;
}

//============================================================
// <T>��һ����Դ��</T>
//
// @param pName ����
// @return ��Դ
//============================================================
FAsset* FAssetConsole::OpenAsset(TCharC* pName){
   return NULL;
}

//============================================================
// <T>��һ����Դ��</T>
//
// @param pFormat ��ʽ
// @param ... ����
// @return ��Դ
//============================================================
FAsset* FAssetConsole::OpenAssetFormat(TCharC* pFormat, ...){
   // �������
   TFsFileName format;
   va_list params;
   va_start(params, pFormat);
   format.AppendFormatParameters(pFormat, params);
   va_end(params);
   // ����Դ��
   return OpenAsset(format);
}

//============================================================
// <T>�ر�һ����Դ��</T>
//
// @param pAsset ��Դ
// @return ��Դ
//============================================================
TResult FAssetConsole::CloseAsset(FAsset* pAsset){
   MO_DELETE(pAsset);
   return ESuccess;
}

//============================================================
// <T>��һ���ı����ݡ�</T>
//
// @param pSource �ı�����
// @param pName ����
// @return ������
//============================================================
TResult FAssetConsole::OpenAssetString(MString* pSource, TCharC* pName){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>��һ����Դ����</T>
//
// @param pName ����
// @return ��Դ��
//============================================================
FAssetStream* FAssetConsole::OpenAssetStream(TCharC* pName){
   FAssetStream* pStream = MO_CREATE(FAssetStream);
   TResult resultCd = OpenData(pStream, pName);
   if(resultCd != ESuccess){
      MO_DELETE(pStream);
      return NULL;
   }
   return pStream;
}

//============================================================
// <T>��һ����Դ����</T>
//
// @param pFormat ��ʽ
// @param ... ����
// @return ��Դ��
//============================================================
FAssetStream* FAssetConsole::OpenAssetStreamFormat(TCharC* pFormat, ...){
   // �������
   TFsFileName format;
   va_list params;
   va_start(params, pFormat);
   format.AppendFormatParameters(pFormat, params);
   va_end(params);
   // ����Դ��
   return OpenAssetStream(format);
}

//============================================================
// <T>�ر�һ����Դ����</T>
//
// @param pAssetStream ��Դ��
// @return ��Դ
//============================================================
TResult FAssetConsole::CloseAssetStream(FAssetStream* pAssetStream){
   MO_DELETE(pAssetStream);
   return ESuccess;
}

//============================================================
// <T>��һ����Դ���ݡ�</T>
//
// @param pData ����
// @param pName ����
// @return ������
//============================================================
TResult FAssetConsole::OpenData(FByteStream* pData, TCharC* pName){
   return EUnsupport;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FAssetConsole::Setup(){
   return ESuccess;
}

MO_NAMESPACE_END
