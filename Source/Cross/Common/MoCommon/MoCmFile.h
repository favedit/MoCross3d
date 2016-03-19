#ifndef __MO_CM_FILE_H__
#define __MO_CM_FILE_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_STREAM_H__
#include "MoCmPipe.h"
#endif // __MO_CM_STREAM_H__

MO_NAMESPACE_BEGIN

const TInt MoDirMaxLayer = 32;

//============================================================
typedef FILE* TFileHandle;

//============================================================
// <T>�ļ�Ŀ¼������</T>
//
// @history 100114 MAOCY ����
//============================================================
enum TFileAccessMode{
   EFileAccessMode_Read = 0,      // r   ���ı��ļ������ڶ���������λ���ļ��Ŀ�ʼ��
   EFileAccessMode_ReadWrite,     // r+  ���ı��ļ������ڶ�д��������λ���ļ��Ŀ�ʼ��
   EFileAccessMode_Write,         // w   ���ļ����Ƚض�Ϊ�㣬���ߴ����ı��ļ�������д��������λ���ļ��Ŀ�ʼ��
   EFileAccessMode_WriteRead,     // w+  ���ı��ļ������ڶ�д������ļ������ھʹ����������򽫽ض�����������λ���ļ��Ŀ�ʼ��
   EFileAccessMode_Append,        // a   ���ı��ļ�������׷�� (���ļ�βд)������ļ������ھʹ�������������λ���ļ���ĩβ��
   EFileAccessMode_AppendWrite,   // a+  ���ı��ļ�������׷�� (���ļ�βд)������ļ������ھʹ����������ļ��ĳ�ʼλ�����ļ��Ŀ�ʼ������������Ǳ�׷�ӵ��ļ���ĩβ��
   EFileAccessMode_Count,
};

//============================================================
// <T>�ļ�Ŀ¼������</T>
//
// @history 100114 MAOCY ����
//============================================================
class MO_CM_DECLARE RFile{
public:
   static TCharC* FILE_MODE_STR[EFileAccessMode_Count];
public:
   static TBool ExistPath(TCharC* pPath);
   static TBool IsPathReadable(TCharC* pPath);
   static TBool IsPathWritable(TCharC* pPath);
   static TBool IsPathExcutable(TCharC* pPath);
   static TBool ExistFile(TCharC* pFileName);
   static TInt FileSize(TCharC* pFileName);
   static TBool CreateFullDirectory(TCharC* pPath);
   static TInt ListAll( TCharC* pDirectory);
   static TBool CopyTo(TCharC* pSourceName, TCharC* pTargetName);
};

//============================================================
// <T>�ļ���Ϣ��</T>
//
// @history 100527 MAOCY ����
//============================================================
class MO_CM_DECLARE TFileInfo{
protected:
   TFsFileName _fileName;
   TFsName _driver;
   TFsName _extension;
   TFsPath _path;
   TFsName _code;
   TFsName _name;
	TFsFileName _fullName;
public:
   TFileInfo();
   TFileInfo(TCharC* pFileName);
   ~TFileInfo();
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void operator=(TCharC* pFileName){
      _fileName.Assign(pFileName);
      Parse(_fileName);
   }
public:
   MO_SOURCE_GETTER(TCharC*, FileName, _fileName);
   MO_SOURCE_GETTER(TCharC*, Driver, _driver);
   MO_SOURCE_GETTER(TCharC*, Path, _path);
   MO_SOURCE_GETTER(TCharC*, Code, _code);
   MO_SOURCE_GETTER(TCharC*, Name, _name);
   MO_SOURCE_GETTER(TCharC*, Extension, _extension);
   MO_SOURCE_GETTER(TCharC*, FullName, _fullName);
public:
   //------------------------------------------------------------
   // <T>�����ļ����ơ�</T>
   MO_INLINE TResult SetFileName(TCharC* pFileName){
      _fileName.Assign(pFileName);
      return Parse(_fileName);
   }
public:
   TInt Size();
   TInt64 LargeSize();
   TDateTime CreateDate();
   TDateTime UpdateDate();
public:
   TBool IsFile();
   TBool IsDirectory();
public:
   TResult Parse(TCharC* pFileName);
};

//============================================================
// <T>�ļ���������</T>
//
// @history 100113 MAOCY ����
//============================================================
class MO_CM_DECLARE FFileStream :
      public FObject,
      public IInput,
      public IOutput{
protected:
   TFsFileName _filename;
   TBool _opened;
   TFileHandle _handle;
public:
   FFileStream();
   FFileStream(TCharC* pFileName, TFileAccessMode modeCd = EFileAccessMode_WriteRead);
   MO_ABSTRACT ~FFileStream();
public:
   TCharC* FileName();
   TInt Length();
   TInt Position();
   TBool Seek(TInt position);
   TInt SeekEnd(TInt position);
public:
   MO_OVERRIDE TInt Read(TAny* pData, TInt capacity);
   MO_OVERRIDE TInt Write(TAnyC* pData, TInt length);
public:
   TBool Create(TCharC* pFileName);
   TBool Open(TCharC* pFileName, TFileAccessMode modeCd = EFileAccessMode_WriteRead);
   TBool OpenAppend(TCharC* pFileName);
   TBool Flush();
   TBool SaveAs(TCharC* pFileName);
   TBool Close();
};

//============================================================
// <T>�������ļ���������</T>
//
// @history 100113 MAOCY ����
//============================================================
class MO_CM_DECLARE FByteFileStream :
      public FFileStream,
      public IDataInput,
      public IDataOutput{
public:
   TBool ReadBool();
   TInt ReadInt();
   TInt8 ReadInt8();
   TInt16 ReadInt16();
   TInt32 ReadInt32();
   TUint ReadUint();
   TInt64 ReadInt64();
   TUint8 ReadUint8();
   TUint16 ReadUint16();
   TUint32 ReadUint32();
   TUint64 ReadUint64();
   TFloat ReadFloat();
   TDouble ReadDouble();
   TInt ReadString(TChar8C* buffer, TInt length);
   TInt ReadString(TChar16C* buffer, TInt length);
public:
   void WriteBoolean(TBool value);
   void WriteUInt(TUint value);
   void WriteInt(TInt value);
   void WriteUInt8(TUint8 value);
   void WriteInt8(TInt8 value);
   void WriteUInt16(TUint16 value);
   void WriteInt16(TInt16 value);
   void WriteUInt32(TUint32 value);
   void WriteInt32(TInt32 value);
   void WriteUInt64(TUint64 value);
   void WriteInt64(TInt64 value);
   void WriteFloat(TFloat value);
   void WriteDouble(TDouble value);
   void WriteString(TChar8C* pBuffer, TInt length);
   void WriteString(TChar16C* pBuffer, TInt length);
   void WriteStringA16(TChar8C* pBuffer, TInt length = -1);
};

//============================================================
// <T>�ַ����ļ���������</T>
//
// @history 100113 MAOCY ����
//============================================================
class MO_CM_DECLARE FFileStringStream : public FByteFileStream{
public:
   TString ReadString(TInt size);
   TString ReadLine();
   TInt ReadLine(TChar* pBuffer, TInt bufferLength);
   void WriteString(TCharC* pValue);
   void WriteLine(TCharC* pLine);
};

//============================================================
// <T>�ļ���������</T>
//
// @history 100113 MAOCY ����
//============================================================
#ifdef _MO_WINDOWS
class MO_CM_DECLARE FFileMapping :
      public FObject,
      public IInput,
      public IOutput{
protected:
   TFsFileName _filename;
   HANDLE _hFile;
   HANDLE _hMapping;
   TUint64 _position;
   TUint32 _bytesInBlock;
   TByte* _pMemory;
public:
   FFileMapping();
   FFileMapping(TCharC* pFileName);
   MO_ABSTRACT( ~FFileMapping() );
public:
   TCharC* FileName();
   TUint64 Length();
   TUint64 Position();
public:
   TBool Create(TCharC* pFileName);
   TBool Open(TCharC* pFileName);
   TBool Seek(TInt position);
   MO_OVERRIDE TInt Read(TAny* pData, TSize size);
   MO_OVERRIDE TInt Write(TAnyC* pData, TSize size);
   TBool Close();
};
#endif // _WINDOWS

//============================================================
// <T>�ֽ������ļ���</T>
//
// @history 100526 MAOCY ����
//============================================================
class MO_CM_DECLARE FByteFile : public FByteStream{
protected:
   TFsPath _fileName;
public:
   FByteFile();
   FByteFile(TCharC* pFileName);
   MO_ABSTRACT ~FByteFile();
public:
   TBool LoadFile(TCharC* pFileName);
   TBool SaveFile(TCharC* pFileName);
   TBool Store();
};

//============================================================
// <T>�ļ�ANSI�ַ�����</T>
//
// @history 100526 MAOCY ����
//============================================================
class MO_CM_DECLARE FFileString8 : public FString8{
protected:
   TFsPath _fileName;
public:
   FFileString8();
   FFileString8(TCharC* pFileName);
   MO_ABSTRACT ~FFileString8();
public:
   TBool LoadFile(TCharC* pFileName);
   TBool Store();
   TBool SaveFile(TCharC* pFileName);
};

//============================================================
// <T>�ļ�UNICODE�ַ�����</T>
//
// @history 100526 MAOCY ����
//============================================================
class MO_CM_DECLARE FFileString16 : public FString16{
protected:
   TFsPath _fileName;
public:
   FFileString16();
   FFileString16(TCharC* pFileName);
   FFileString16(TCharC* pFileName, TCharC* pCharSet);
   MO_ABSTRACT ~FFileString16();
public:
   TBool LoadFile(TCharC* pFileName);
   TBool LoadFile(TCharC* pFileName, TCharC* pCharSet);
   TBool Store();
   TBool SaveFile(TCharC* pFileName);
   TBool SaveFile(TCharC* pFileName, TCharC* pCharSet);
};

//============================================================
// <T>�ļ�UNICODE�ַ�����</T>
//
// @history 100526 MAOCY ����
//============================================================
class MO_CM_DECLARE FFileString32 : public FString32{
protected:
   TFsPath _fileName;
public:
   FFileString32();
   FFileString32(TCharC* pFileName);
   FFileString32(TCharC* pFileName, TCharC* pCharSet);
   MO_ABSTRACT ~FFileString32();
public:
   TBool LoadFile(TCharC* pFileName);
   TBool LoadFile(TCharC* pFileName, TCharC* pCharSet);
   TBool Store();
   TBool SaveFile(TCharC* pFileName);
   TBool SaveFile(TCharC* pFileName, TCharC* pCharSet);
};

//============================================================
#ifndef _UNICODE
#define FFileString FFileString8
#else
#ifdef _MO_WINDOWS
#define FFileString FFileString16
#else
#define FFileString FFileString32
#endif
#endif

//============================================================
// <T>�ļ��м��ϡ�</T>
//============================================================
class MO_CM_DECLARE FFileLines : public FObject{
protected:
   FStringVector* _pLines;
   TFsPath _fileName;
public:
   FFileLines();
   FFileLines(TCharC* pFileName);
   MO_ABSTRACT ~FFileLines();
public:
   FString* operator[](TInt index);
public:
   FStringVector* Lines();
   FString* Line(TInt index);
   void Push(TCharC* pLine);
public:
   void Clear();
   TBool LoadFile(TCharC* pFileName);
   TBool Store();
   TBool SaveFile(TCharC* pFileName);
};

//============================================================
template <typename E>
class IEntityStore{
public:
   MO_VIRTUAL TBool WriteEntry(E* pEntry) = 0;
};

//============================================================
// <T>ʵ��ܵ���</T>
//
// @history 100114 MAOCY ����
//============================================================
template <typename E>
class FEntryPipe{
protected:
   TThreadLocker _locker;
   TInt _count;
   E* _pRead;
   E* _pWrite;
public:
   //------------------------------------------------------------
   // <T>����ܵ���</T>
   FEntryPipe(){
      _count = 0;
      MO_CLEAR(_pRead);
      MO_CLEAR(_pWrite);
   }
   //------------------------------------------------------------
   // <T>�����ܵ���</T>
   MO_ABSTRACT ~FEntryPipe(){
   }
protected:
   //------------------------------------------------------------
   // <T>����һ�����ӽڵ㡣</T>
   inline E* EntryShift(){
      E* pEntry = _pRead;
      if(NULL != _pRead){
         // ��ָ��ָ����һ��λ��
         _pRead = _pRead->pNext;
         if(NULL == _pRead){
            _pWrite = NULL;
         }else{
            _pRead->pPrior = NULL;
         }
         // ��������
         _count--;
         pEntry->pPrior = NULL;
         pEntry->pNext = NULL;
      }
      return pEntry;
   }
   //------------------------------------------------------------
   // <T>ѹ��һ�����ӽڵ㡣</T>
   inline void EntryPush(E* pEntry){
      MO_ASSERT(pEntry);
      if(NULL == _pWrite){
         _pRead = pEntry;
      }else{
         _pWrite->pNext = pEntry;
      }
      // ��������
      _count++;
      pEntry->pPrior = _pWrite;
      pEntry->pNext = NULL;
      // ����β�ڵ�
      _pWrite = pEntry;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����ӽڵ㡣</T>
   inline void EntryRemove(E* pEntry){
      MO_ASSERT(pEntry);
      // ����ǰ�ڵ�
      E* pPrior = pEntry->pPrior;
      if(NULL == pPrior){
         MO_ASSERT(pEntry == _pRead);
         _pRead = pEntry->pNext;
         if(NULL != _pRead){
            _pRead->pPrior = NULL;
         }
      }else{
         pPrior->pNext = pEntry->pNext;
      }
      // �����ڵ�
      E* pNext = pEntry->pNext;
      if(NULL == pNext){
         MO_ASSERT(pEntry == _pWrite);
         _pWrite = pEntry->pPrior;
         if(NULL != _pWrite){
            _pWrite->pNext = NULL;
         }
      }else{
         pNext->pPrior = pEntry->pPrior;
      }
      // ��������
      _count--;
      pEntry->pPrior = NULL;
      pEntry->pNext = NULL;
   }
public:
   //------------------------------------------------------------
   TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>�����ܵ���</T>
   void Lock(){
      _locker.Enter();
   }
   //------------------------------------------------------------
   // <T>�����ܵ���</T>
   void Unlock(){
      _locker.Leave();
   }
   //------------------------------------------------------------
   E* Read(){
      E* pEntry = NULL;
      _locker.Enter();
      // �洢�ڵ�
      pEntry = EntryShift();
      // �뿪
      _locker.Leave();
      return pEntry;
   }
   //------------------------------------------------------------
   TBool Write(E* pEntry){
      MO_ASSERT(pEntry);
      _locker.Enter();
      // �洢�ڵ�
      EntryPush(pEntry);
      // �뿪
      _locker.Leave();
      return ETrue;
   }
   //------------------------------------------------------------
   TBool Flip(TInt& count, E** ppRead, E** ppWrite){
      TBool result = EFalse;
      _locker.Enter();
      if(NULL != _pRead){
         // ��ȡ����
         count = _count;
         *ppRead = _pRead;
         *ppWrite = _pWrite;
         // �������
         _count = 0;
         _pRead = NULL;
         _pWrite = NULL;
         result = ETrue;
      }
      _locker.Leave();
      return result;
   }
   //------------------------------------------------------------
   // <T>д��һ���ڵ㡣</T>
   TBool Flush(TInt count, E* pRead, E* pWrite){
      MO_ASSERT(pRead);
      MO_ASSERT(pWrite);
      _locker.Enter();
      // ���Ӽ���
      _count += count;
      // �������һ���ڵ�
      if(NULL == _pWrite){
         _pRead = pRead;
      }else{
         _pWrite->pNext = pRead;
         pRead->pPrior = _pWrite;
      }
      _pWrite = pWrite;
      _locker.Leave();
      return ETrue;
   }
};

//============================================================
// <T>ʵ��ܵ�д������</T>
//
// @history 100114 MAOCY ����
//============================================================
template <typename E>
class FEntryPipeReader : public IDispose{
protected:
   FEntryPipe<E>* _pPipe;
   TInt _count;
   E* _pRead;
   E* _pWrite;
public:
   //------------------------------------------------------------
   // <T>����ܵ�д������</T>
   FEntryPipeReader(FEntryPipe<E>* pPipe){
      _pPipe = pPipe;
      _count = 0;
      MO_CLEAR(_pRead);
      MO_CLEAR(_pWrite);
   }
   //------------------------------------------------------------
   // <T>�����ܵ�д������</T>
   MO_ABSTRACT ~FEntryPipeReader(){
   }
public:
   //------------------------------------------------------------
   FEntryPipe<E> Pipe(){
      return _pPipe;
   }
   //------------------------------------------------------------
   TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   E* Read(){
      // ��ȡ�׸�����
      E* pRead = _pRead;
      if(NULL != pRead){
         _pRead = pRead->pNext;
         if(NULL == _pRead){
            _pWrite = NULL;
         }
         // ��������
         _count--;
         pRead->pPrior = NULL;
         pRead->pNext = NULL;
      }
      return pRead;
   }
   //------------------------------------------------------------
   TBool Flip(){
      // �ӹܵ��л�ȡ����
      TBool result = EFalse;
      TInt count = 0;
      E* pRead = NULL;
      E* pWrite = NULL;
      if(_pPipe->Flip(count, &pRead, &pWrite)){
         _count += count;
         if(NULL == _pWrite){
            _pRead = pRead;
         }else{
            _pWrite->pNext = pRead;
            pRead->pPrior = _pWrite;
         }
         _pWrite = pWrite;
         result = ETrue;
      }
      return result;
   }
   //------------------------------------------------------------
   E* FlipRead(){
      // �ӹܵ��л�ȡ����
      if(NULL == _pRead){
         _pPipe->Flip(_count, &_pRead, &_pWrite);
      }
      // ��ȡ�׸�����
      E* pRead = _pRead;
      if(NULL != pRead){
         _pRead = pRead->pNext;
         if(NULL == _pRead){
            _pWrite = NULL;
         }
         // ��������
         _count--;
         pRead->pPrior = NULL;
         pRead->pNext = NULL;
      }
      return pRead;
   }
};

//============================================================
// <T>ʵ��ܵ�д������</T>
//
// @history 100114 MAOCY ����
//============================================================
template <typename E>
class FEntryPipeWriter : public IDispose{
protected:
   FEntryPipe<E>* _pPipe;
   TInt _count;
   E* _pRead;
   E* _pWrite;
public:
   //------------------------------------------------------------
   // <T>����ܵ�д������</T>
   FEntryPipeWriter(FEntryPipe<E>* pPipe){
      _pPipe = pPipe;
      _count = 0;
      MO_CLEAR(_pRead);
      MO_CLEAR(_pWrite);
   }
   //------------------------------------------------------------
   // <T>�����ܵ�д������</T>
   MO_ABSTRACT ~FEntryPipeWriter(){
   }
public:
   //------------------------------------------------------------
   FEntryPipe<E> Pipe(){
      return _pPipe;
   }
   //------------------------------------------------------------
   // <T>���д��������</T>
   TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>ѹ��һ�����ӽڵ㡣</T>
   void Write(E* pEntry){
      MO_ASSERT(pEntry);
      if(NULL == _pWrite){
         _pRead = pEntry;
      }else{
         _pWrite->pNext = pEntry;
      }
      // ��������
      _count++;
      pEntry->pPrior = _pWrite;
      pEntry->pNext = NULL;
      // ����β�ڵ�
      _pWrite = pEntry;
   }
   //------------------------------------------------------------
   // <T>ˢ�»�������</T>
   void Flush(){
      if(NULL != _pRead){
         // д�����нڵ�
         _pPipe->Flush(_count, _pRead, _pWrite);
         // �������
         _count = 0;
         _pRead = NULL;
         _pWrite = NULL;
      }
   }
};

//============================================================
// <T>ʵ��ܵ���</T>
//
// @history 100114 MAOCY ����
//============================================================
template <typename R, typename W, typename E>
class FEntryBufferedPipe : public FEntryPipe<E>{
public:
   typedef FList<R*> FReaderList;
   typedef FList<W*> FWriterList;
protected:
   FReaderList* _pReaders;
   FWriterList* _pWriters;
public:
   //------------------------------------------------------------
   FEntryBufferedPipe(){
      _pReaders = MO_CREATE(FReaderList);
      _pWriters = MO_CREATE(FWriterList);
   }
   //------------------------------------------------------------
   MO_ABSTRACT ~FEntryBufferedPipe(){
      // �ͷ����ж�ȡ��
      if(!_pReaders->IsEmpty()){
         TListIteratorC<R*> iterator = _pReaders->IteratorC();
         while(iterator.Next()){
            R* pReader = iterator.Get();
            MO_DELETE(pReader);
         }
      }
      MO_DELETE(_pReaders);
      // �ͷ�����д����
      if(!_pWriters->IsEmpty()){
         TListIteratorC<W*> iterator = _pWriters->IteratorC();
         while(iterator.Next()){
            W* pWriter = iterator.Get();
            MO_DELETE(pWriter);
         }
      }
      MO_DELETE(_pWriters);
      FEntryPipe<E>::Dispose();
   }
public:
   //------------------------------------------------------------
   FReaderList* Readers(){
      return _pReaders;
   }
   //------------------------------------------------------------
   R* ReaderAlloc(){
      R* pReader = MO_CREATE(R, this);
      MO_ASSERT(pReader);
      _pReaders->Push(pReader);
      return pReader;
   }
   //------------------------------------------------------------
   void ReaderFree(R* pReader){
      MO_ASSERT(pReader);
      _pReaders->Remove(pReader);
      MO_DELETE(pReader);
   }
   //------------------------------------------------------------
   FWriterList* Writers(){
      return _pWriters;
   }
   //------------------------------------------------------------
   W* WriterAlloc(){
      W* pWriter = MO_CREATE(W, this);
      MO_ASSERT(pWriter);
      _pWriters->Push(pWriter);
      return pWriter;
   }
   //------------------------------------------------------------
   void WriterFree(W* pWriter){
      MO_ASSERT(pWriter);
      _pWriters->Remove(pWriter);
      MO_DELETE(pWriter);
   }
};

//============================================================
// <T>ʵ��ܵ�д������</T>
//
// @history 100114 MAOCY ����
//============================================================
class MO_CM_DECLARE TFileFinder{
protected:
   TFsPath _path;
   TFsPath _cpath;
   TFsPath _cfile;
   TFsPath _cfull;
#ifdef _MO_WINDOWS
   HANDLE _dir;
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   struct dirent **_dents;
   TInt _cur;
   TInt _dcount;
#endif // _MO_LINUX
public:
   TFileFinder(TCharC* pDirectory);
   ~TFileFinder();
protected:
   TBool OsWalk();
   void OsClose();
#ifdef _MO_LINUX
   static int Filter(const struct dirent *);
#endif
public:
   TCharC* FullName();
   TCharC* FileName();
   TCharC* Path();
   TBool Reset();
   void Restart();
   TBool Next();
};

MO_NAMESPACE_END

#endif // __MO_CM_FILE_H__
