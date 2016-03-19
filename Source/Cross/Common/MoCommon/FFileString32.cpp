#include "MoCmFile.h"

MO_NAMESPACE_BEGIN

//============================================================
FFileString32::FFileString32(){
}

//============================================================
FFileString32::FFileString32(TCharC* pFileName){
   LoadFile(pFileName);
}

//============================================================
FFileString32::~FFileString32(){
}

//============================================================
TBool FFileString32::LoadFile(TCharC* pFileName){
   // ���ļ�
   TFileHandle handle;
#ifdef _MO_WINDOWS
   MO_LIB_FILE_OPEN(&handle, pFileName, TC("rb"));
#else
   handle = fopen(pFileName, TC("rb"));
#endif
   if(NULL == handle){
      MO_PERROR(fopen);
      return EFalse;
   }
   // ��ó���
   if(ESuccess != fseek(handle, 0, SEEK_END)){
      MO_PERROR(fseek);
      return EFalse;
   }
   TInt length = ftell(handle);
   EnsureSize(length);
   // �ӿ�ʼλ�ö�ȡ
   if(ESuccess != fseek(handle, 0, SEEK_SET)){
      MO_PERROR(fseek);
      return EFalse;
   }
   TInt readed = fread(_pMemory, length, 1, handle);
   if(1 != readed){
      MO_PFATAL(fread);
   }
   _length = length;
   // �ر��ļ�
   if(ESuccess != fclose(handle)){
      MO_PFATAL(fclose);
   }
   return ETrue;
}

//============================================================
TBool FFileString32::Store(){
   return SaveFile(_fileName.MemoryC());
}

//============================================================
TBool FFileString32::SaveFile(TCharC* pFileName){
   // ���ļ�
   TFileHandle handle;
#ifdef _MO_WINDOWS
   MO_LIB_FILE_OPEN(&handle, pFileName, TC("wb"));
#else
   handle = fopen(pFileName, "wb");
#endif
   if(NULL == handle){
      MO_PERROR(fopen);
      return EFalse;
   }
   // �ӿ�ʼλ��д��
   if(ESuccess != fseek(handle, 0, SEEK_SET)){
      MO_PERROR(fseek);
      return EFalse;
   }
   TInt writted = fwrite(_pMemory, _length, 1, handle);
   if(writted != _length){
      MO_PFATAL(fwrite);
   }
   // �ر��ļ�
   if(ESuccess != fclose(handle)){
      MO_PFATAL(fclose);
      return EFalse;
   }
   return ETrue;
}

MO_NAMESPACE_END
