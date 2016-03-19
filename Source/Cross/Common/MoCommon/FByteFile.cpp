#include "MoCmFile.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ֽ������ļ���</T>
//============================================================
FByteFile::FByteFile(){
   _position = 0;
}

//============================================================
// <T>�����ֽ������ļ���</T>
//
// @param pFileName �ļ�����
//============================================================
FByteFile::FByteFile(TCharC* pFileName){
   _position = 0;
   LoadFile(pFileName);
}

//============================================================
// <T>�����ֽ������ļ���</T>
//============================================================
FByteFile::~FByteFile(){
}

//============================================================
// <T>����ָ�����Ƶ������ļ���</T>
//
// @param pFileName �ļ�����
// @return ������
//============================================================
TBool FByteFile::LoadFile(TCharC* pFileName){
   // ���ļ�
   TFileHandle handle;
#ifdef _MO_WINDOWS
   errno_t error = MO_LIB_FILE_OPEN(&handle, pFileName, TC("rb"));
   if(error != 0){
      MO_ERROR(TC("Open file failure. (error=%d, file_name=%s)"), error, pFileName);
      return EFalse;
   }
#else
   handle = fopen(pFileName, "rb");
#endif // _MO_WINDOWS
   if(handle == NULL){
      MO_PERROR(fopen);
      return EFalse;
   }
   // ��ó���
   if(ESuccess != fseek(handle, 0, SEEK_END)){
      MO_PERROR(fseek);
      return EFalse;
   }
   TInt length = ftell(handle);
   ForceSize(length);
   _length = length;
   // �ӿ�ʼλ�ö�ȡ
   if(ESuccess != fseek(handle, 0, SEEK_SET)){
      MO_PERROR(fseek);
      return EFalse;
   }
   TInt readed = fread(_pMemory, length, 1, handle);
   if(readed != 1){
      MO_PFATAL(fread);
   }
   // �ر��ļ�
   if(ESuccess != fclose(handle)){
      MO_PFATAL(fclose);
   }
   return ETrue;
}

//============================================================
// <T>�洢ָ�����Ƶ������ļ���</T>
//
// @param pFileName �ļ�����
// @return ������
//============================================================
TBool FByteFile::SaveFile(TCharC* pFileName){
   TBool result = ETrue;
   // ���ļ�
   TFileHandle handle;
#ifdef _MO_WINDOWS
   errno_t error = MO_LIB_FILE_OPEN(&handle, pFileName, TC("wb"));
   if(error != 0){
      MO_ERROR(TC("Open file failure. (error=%d, file_name=%s)"), error, pFileName);
      return EFalse;
   }
#else
   handle = fopen(pFileName, "w+");
#endif // _MO_WINDOWS
   if(handle == NULL){
      MO_PERROR(fopen);
      return EFalse;
   }
   // �ӿ�ʼλ��д��
   if(ESuccess != fseek(handle, 0, SEEK_SET)){
      MO_PERROR(fseek);
      return EFalse;
   }
   TInt writted = fwrite(_pMemory, _length, 1, handle);
   if(writted != 1){
      MO_ERROR(TC("Write file data failure. (handle=%d, memory=%08X, length=%d, writted=%d)"), handle, _pMemory, _length, writted);
      result = EFalse;
   }
   // �ر��ļ�
   if(ESuccess != fclose(handle)){
      MO_PFATAL(fclose);
      return EFalse;
   }
   return result;
}

//============================================================
// <T>�洢ָ�����Ƶ������ļ���</T>
//
// @return ������
//============================================================
TBool FByteFile::Store(){
   return SaveFile(_fileName.MemoryC());
}

MO_NAMESPACE_END
