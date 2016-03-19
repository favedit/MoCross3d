#include "MoCmFile.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ȡ������</T>
//
// @return ����size���ȵ�����
//============================================================
TString FFileStringStream::ReadString(TInt size){
   TString str;
   // fread(&str, size, 1, _handle);
   return str;
}

//============================================================
// <T>д��ȡһ������</T>
//
// @return ����һ������
//============================================================
TString FFileStringStream::ReadLine(){
   TString str;
   TChar *buff = NULL;
   TInt size;
   size = Length();
#ifdef _UNICODE
   str = fgetws(buff, size, _handle);
#else
   str = fgets(buff, size, _handle);
#endif
   return str;
}

//============================================================
// <T>д��ȡһ������</T>
//
// @param pBuffer �����ݻ���
// @param bufferLength �����С
// @return �������ݵĳ���
//============================================================
 TInt FFileStringStream::ReadLine(TChar* pBuffer, TInt bufferLength){
#ifdef _UNICODE
    TChar* pLine = fgetws(pBuffer, bufferLength, _handle);
#else
    TChar* pLine = fgets(pBuffer, bufferLength, _handle);
#endif
    if(NULL == pLine){
      if(feof(_handle)){
         return 0;
      }else{
         MO_ERROR(TC("fgets error"));
         return -1;
      }
    }
    return RString::Length(pLine);
 }

//============================================================
// <T>д������</T>
//
// @param value Ҫд�������
//============================================================
void FFileStringStream::WriteString(const TCharC* pValue){
#ifdef _UNICODE
   // TODO: ���ܲ���ȷ
   fwrite(pValue, RString::Length(pValue), 1, _handle);
#else
   fwrite(pValue, RString::Length(pValue), 1, _handle);
#endif
}

//============================================================
// <T>д��һ������</T>
//
// @param line Ҫд�������
//============================================================
void FFileStringStream::WriteLine(const TCharC* pLine){
#ifdef _UNICODE
   // TODO: ���ܲ���ȷ
   fwrite(pLine, RString::Length(pLine), 1, _handle);
#else
   fwrite(pLine, RString::Length(pLine), 1, _handle);
#endif
   fputs("\n", _handle);
}

MO_NAMESPACE_END
