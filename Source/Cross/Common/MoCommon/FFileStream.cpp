#include "MoCmFile.h"

MO_NAMESPACE_BEGIN
//============================================================
#define MO_FILE_BUFFER 16384

//============================================================
// <T>�����ļ���������</T>
//============================================================
FFileStream::FFileStream(){
   _opened = EFalse;
   _handle = 0;
}

//============================================================
// <T>�����ļ���������</T>
//
// @param fileName �ļ�����
// @param modeCd ģʽ����
//============================================================
FFileStream::FFileStream(TCharC* pFileName, TFileAccessMode modeCd){
   _filename = pFileName;
   _opened = EFalse;
   _handle = 0;
   Open(pFileName, modeCd);
}

//============================================================
// <T>�����ļ���������</T>
//============================================================
FFileStream::~FFileStream(){
   Close();
}

//============================================================
// <T>����ļ���</T>
//
// @return �ļ���
//============================================================
TCharC* FFileStream::FileName(){
   return _filename.MemoryZ();
}

//============================================================
// <T>����ļ�����</T>
//
// @return �ļ�����
//============================================================
TInt FFileStream::Length(){
   // ��õ�ǰλ��
   TInt position = ftell(_handle);
   // �ƶ���β��
   if(fseek(_handle, 0, SEEK_END)){
      MO_PERROR(fseek);
      return -1;
   }
   // ��ó���
   TInt length = ftell(_handle);
   // �ƶ���ԭ��λ��
   if(fseek(_handle, position, SEEK_SET)){
      MO_PERROR(fseek);
      return -1;
   }
   return length;
}

//============================================================
// <T>���ص�ǰ�ļ�λ�á�</T>
//
// @return ��ǰλ��
//============================================================
TInt FFileStream::Position(){
   return ftell(_handle);
}

//============================================================
// <T>�����ļ�,����ļ���������������ա�</T>
//
// @param fileName �ļ���
// @return ���ļ��ɹ�����ETrue,ʧ���򷵻�EFalse
//============================================================
TBool FFileStream::Create(TCharC* pFileName){
#ifdef _MO_WINDOWS
   TFsPath fullPath = pFileName;
   TInt index = fullPath.LastIndexOf('\\');
   if(-1 != index){
      TFsPath path = fullPath.LeftStrC(index);
      RFile::CreateFullDirectory(path.MemoryC());
   }
#ifdef _UNICODE
   _handle = _wfopen(pFileName, TC("wb"));
#else
   fopen_s(&_handle, pFileName, "wb");
#endif
#else
   _handle = fopen(pFileName, "wb");
#endif
   if(NULL == _handle){
      MO_ERROR(TC("Create file failure. (filename=%s)"), pFileName);
      MO_PERROR(fopen);
      return EFalse;
   }
   _opened = ETrue;
   _filename = pFileName;
   return ETrue;
}

//============================================================
// <T>���ļ�</T>
//
// @param fileName �ļ���
// @param modeCd ģʽ����
// @return ���ļ��ɹ�����ETrue,ʧ���򷵻�EFalse
//============================================================
TBool FFileStream::Open(const TCharC* pFileName, TFileAccessMode modeCd){
   TCharC* pMode = RFile::FILE_MODE_STR[modeCd];
#ifdef _MO_WINDOWS
#ifdef _UNICODE
   errno_t result = 0;
   _handle = _wfopen(pFileName, pMode);
#else
   errno_t result = fopen_s(&_handle, pFileName, pMode);
#endif
   if(0 != result){
      MO_ERROR(TC("Open file failure. (file_name=%s, mode=%s)"), pFileName, pMode);
      MO_PERROR(fopen_s);
   }
#else
   _handle = fopen(pFileName, pMode);
#endif
   // �����
   if(NULL == _handle){
      MO_ERROR(TC("Open file failure. (file_name=%s, mode=%s)"), pFileName, pMode);
      MO_PERROR(fopen);
      return EFalse;
   }
   // ������λ��
   Seek(0);
   _opened = ETrue;
   _filename = pFileName;
   return ETrue;
}

//============================================================
// <T>׷�ӷ�ʽ���ļ���</T>
//
// @param fileName �ļ���
// @return ������
//============================================================
TBool FFileStream::OpenAppend(TCharC* pFileName){
   return Open(pFileName, EFileAccessMode_AppendWrite);
}

//============================================================
// <T>�ض�λ���ϵ��ļ�ָ��</T>
//
// @param position ƫ���ֽ�λ��
// @return ������
//============================================================
TBool FFileStream::Seek(TInt position){
   if(fseek(_handle, position, SEEK_SET)){
      MO_PERROR(fseek);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>�ض�λ�ļ�λ�õ�β����</T>
//
// @param position ƫ���ֽ�λ��
// @return ������
//============================================================
TInt FFileStream::SeekEnd(TInt position){
   if(fseek(_handle, position, SEEK_END)){
      MO_PFATAL(fseek);
   }
   return Position();
}

//============================================================
// <T>��λ�ö�ȡָ�����ȵ����ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ��������
// @return ��ȡ����
//============================================================
TInt FFileStream::Read(TAny* pData, TInt capacity){
   MO_ASSERT(pData);
   TInt result = 0;
   if(capacity > 0){
      if(feof(_handle)){
         return 0;
      }
      result = fread(pData, 1, capacity, _handle);
   }
   return result;
}

//============================================================
// <T>�ӵ�ǰλ��д��ָ�����ȵ���������</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return д�볤��
//============================================================
TInt FFileStream::Write(TAnyC* pData, TInt length){
   MO_ASSERT(pData);
   TInt result = 0;
   if(length > 0){
	  result = fwrite(pData, length, 1, _handle);
   }
   return (1 == result) ? length : 0;
}

//============================================================
// <T>����ļ�������</T>
//
// @return ���ļ��ɹ�����ETrue,ʧ���򷵻�EFalse
//============================================================
TBool FFileStream::Flush(){
   if(ESuccess != fflush(_handle)){
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>�����ļ�</T>
//
// @param fileName Ҫ�����ļ����ļ���
//============================================================
TBool FFileStream::SaveAs(TCharC* pFileName){
   // ��ǰ�ļ�ָ��ָ����λ��
   TInt size = Length();
   rewind(_handle);
   // ��Ŀ���ļ�
#ifdef _MO_WINDOWS
   TFileHandle handle;
#ifdef _UNICODE
   handle = _wfopen(pFileName, TC("wb"));
#else
   fopen_s(&handle, pFileName, "wb");
#endif
#else
   TFileHandle handle = fopen(pFileName, "wb");
#endif
   if(NULL == handle){
      MO_PERROR(fopen);
      return EFalse;
   }
   // ������Ϣ��Ŀ���ļ�
   TBool result = ETrue;
   TByte buffer[MO_FILE_BUFFER];
   while(size > 0){
      TInt length = (size > MO_FILE_BUFFER) ? MO_FILE_BUFFER : size;
      // ��������
      TInt lengthRead = fread(buffer, length, 1, _handle);
      TInt lengthWrite = fwrite(buffer, lengthRead, 1, handle);
      // ���д������
      if(lengthRead != lengthWrite){
         MO_PERROR(fwrite);
         result = EFalse;
         break;
      }
      size = size - lengthRead;
   }
   // �ر�Ŀ���ļ�
   if(ESuccess != fclose(handle)){
      MO_PERROR(fclose);
      return EFalse;
   }
   return result;
}

//============================================================
// <T>�ر��ļ�</T>
//
// @return ���ļ��ɹ�����ETrue,ʧ���򷵻�EFalse
//============================================================
TBool FFileStream::Close(){
   if(_opened){
      // ˢ������
      Flush();
      // �ر�
      if(ESuccess != fclose(_handle)){
         return EFalse;
      }
      _opened = EFalse;
   }
   return ETrue;
}

MO_NAMESPACE_END
