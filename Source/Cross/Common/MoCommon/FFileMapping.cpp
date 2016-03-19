#include "MoCmFile.h"

#ifdef _MO_WINDOWS

MO_NAMESPACE_BEGIN

//============================================================
// <T>���캯��</T>
//============================================================
FFileMapping::FFileMapping(){
   _hFile = NULL;
   _hMapping = NULL;
   _position = 0;
   _bytesInBlock = 32*1024;
   _pMemory = NULL;
}

//============================================================
// <T>���캯��</T>
//
// @param fileName �ļ�����
//============================================================
FFileMapping::FFileMapping(TCharC* pFileName){
   _filename = pFileName;
   Open(pFileName);
}

//============================================================
// <T>��������</T>
//============================================================
FFileMapping::~FFileMapping(){
   Close();
}

//============================================================
// <T>�����ļ���</T>
//
// @return �ļ���
//============================================================
TCharC* FFileMapping::FileName(){
   return _filename.MemoryC();
}

//============================================================
// <T>�����ļ�����</T>
//
// @return �ļ�����
//============================================================
TUint64 FFileMapping::Length(){
   // TODO: Unsupport
   return 0;
}

//============================================================
// <T>���ص�ǰ�ļ�ָ��</T>
//
// @return ��ǰ�ļ�ָ��
//============================================================
TUint64 FFileMapping::Position(){
   return _position;
}

//============================================================
// <T>�����ļ�,����ļ���������������ա�</T>
//
// @param fileName �ļ���
// @return ���ļ��ɹ�����ETrue,ʧ���򷵻�EFalse
//============================================================
TBool FFileMapping::Create(TCharC* pFileName){
   // ���ϵͳ��Ϣ
   SYSTEM_INFO info;
   GetSystemInfo(&info);
   _bytesInBlock = info.dwAllocationGranularity * 16;
   // ���ļ�
   _hFile = CreateFile(pFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if(INVALID_HANDLE_VALUE == _hFile){
      MO_FATAL(TC("Open file failure. (error=%d, file=%s)"), GetLastError(), pFileName);
   }
   // �����ļ�ӳ��
   _hMapping = CreateFileMapping(_hFile, NULL, PAGE_READWRITE, 0, 0x4000000, NULL);
   if(INVALID_HANDLE_VALUE == _hMapping){
      MO_FATAL(TC("Create file mapping failure. (error=%d, file=%s)"), GetLastError(), pFileName);
   }
   // ���ӳ���ڴ�ָ��
   _pMemory = (TByte*)MapViewOfFile(
      _hMapping,
      FILE_MAP_ALL_ACCESS,
      (TUint32)(_position >> 32),
      (TUint32)(_position & 0xFFFFFFFF),
      _bytesInBlock);
   // �ͷ��ļ��ں˶���
   CloseHandle(_hFile);
   return ETrue;
}

//============================================================
// <T>���ļ�</T>
//
// @param fileName �ļ���
// @return ���ļ��ɹ�����ETrue,ʧ���򷵻�EFalse
//============================================================
TBool FFileMapping::Open(TCharC* pFileName){
   // ���ϵͳ��Ϣ
   SYSTEM_INFO info;
   GetSystemInfo(&info);
   _bytesInBlock = info.dwAllocationGranularity * 16;
   // ���ļ�
   _hFile = CreateFile(pFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if(INVALID_HANDLE_VALUE == _hFile){
      MO_FATAL(TC("Open file failure. (error=%d, file=%s)"), GetLastError(), pFileName);
   }
   // �����ļ�ӳ��
   _hMapping = CreateFileMapping(_hFile, NULL, PAGE_READWRITE, 0, 0x4000000, NULL);
   if(INVALID_HANDLE_VALUE == _hMapping){
      MO_FATAL(TC("Create file mapping failure. (error=%d, file=%s)"), GetLastError(), pFileName);
   }
   // ���ӳ���ڴ�ָ��
   _pMemory = (TByte*)MapViewOfFile(
         _hMapping,
         FILE_MAP_ALL_ACCESS,
         (TUint32)(_position >> 32),
         (TUint32)(_position & 0xFFFFFFFF),
         _bytesInBlock);
   // �ͷ��ļ��ں˶���
   CloseHandle(_hFile);
   return ETrue;
}


//============================================================
// <T>�ض�λ���ϵ��ļ�ָ��</T>
//
// @param position ƫ���ֽ�λ��
//============================================================
TBool FFileMapping::Seek(TInt position){
   // ����λ��
   if(_position == position){
      return EFalse;
   }
   _position = position;
   // �Ͽ��ڴ�ӳ��
   if(!UnmapViewOfFile(_pMemory)){
      MO_FATAL(TC("Unmap file mapping failure."));
   }
   // ����ڴ�ӳ��
   _pMemory = (TByte*)MapViewOfFile(
         _hMapping,
         FILE_MAP_ALL_ACCESS,
         (TUint32)(_position >> 32),
         (TUint32)(_position & 0xFFFFFFFF),
         _bytesInBlock);
   return ETrue;
}

//============================================================
// <T>��λ��pData��ʼ��ȡsize���ȵ����ݴ���_buffer��</T>
//
// @param pData ��ȡ���ݵ���ʼλ��
// @param size ��ȡ���ݵĳ���
//============================================================
TInt FFileMapping::Read(TAny* pData, TSize size){
   MO_ASSERT(pData);
   TInt readed = 0;
   if(size > 0){
      //readed = fread(pData, size, 1, _handle);
   }
   return readed;
}

//============================================================
// <T>���ļ�д��size���ȵ�����</T>
//
// @param pData Ҫд�����ݵ���ʼλ��
// @param size Ҫд�����ݵĳ���
//============================================================
TInt FFileMapping::Write(TAnyC* pData, TSize size){
   MO_ASSERT(pData);
   TSize bytesWrite = -1;
   if(size > 0){
      //bytesWrite =fwrite(pData, size, 1, _handle);
   }
   return bytesWrite;
}

//============================================================
// <T>�ر��ļ�</T>
//
// @return ���ļ��ɹ�����ETrue,ʧ���򷵻�EFalse
//============================================================
TBool FFileMapping::Close(){
   if(!UnmapViewOfFile(_pMemory)){
      MO_FATAL(TC("Unmap file mapping failure."));
   }
   if(!CloseHandle(_hMapping)){
      MO_FATAL(TC("Close handle failure."));
   }
   return ETrue;
}

MO_NAMESPACE_END

#endif // _WINDOWS
