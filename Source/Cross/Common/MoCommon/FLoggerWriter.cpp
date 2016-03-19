#include <sys/types.h>
#include <sys/stat.h>
#ifdef _MO_LINUX
#include <dirent.h>
#endif
#include "MoCmFormat.h"
#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������־����������</T>
//
// @return ��־д���������ָ�롣
//============================================================
 FLoggerWriter::FLoggerWriter(){
   _code  = 0;
   _fileCount = 0;
   _length = 0;
   _capacity = 0;
   _pStream = MO_CREATE(FFileStream);
   _today = RDateTime::Current() / (TDateTime)MO_DATA_DAY_US;
   _forceToFlush = EFalse;
}

//============================================================
// <T>������־����������</T>
//============================================================
FLoggerWriter::~FLoggerWriter(){
   MO_DELETE(_pStream);
}

//============================================================
// <T>�����־�ļ��ı�š�</T>
//
// @param TCharC* pName  ��־�ļ����ļ�����
// @return ��־�ļ��ı�š�
//============================================================
TInt FLoggerWriter::GetCountFromName(TCharC* pName){
   TInt count = -1;
   TFsName name = pName;
   TInt dateStart = name.IndexOf('_');
   if(ENotFound == dateStart){
      return count;
   }
   dateStart++;
   TInt dateEnd = name.IndexOf('_', dateStart);
   if(ENotFound == dateEnd){
      return count;
   }
   TFsDateTime dateString = name.SubStrC(dateStart, dateEnd);
   TFsDateTime fsDate = _today * (TDateTime)MO_DATA_DAY_US;
   fsDate.Format(TC("%y%m%d"));
   TCharC* pTodayStr = (TCharC*)fsDate;
   TCharC* pDateStr = (TCharC*)dateString;
   if(!RString::Equals(pTodayStr, pDateStr)){
      return count;
   }
   TInt offset1 = name.LastIndexOf('_');
   TInt offset2 = name.LastIndexOf('.');
   if((ENotFound != offset1) && (offset2 > offset1)){
      TFsName mid = name.SubStrC(offset1 + 1, offset2);
      count = RInt::Parse(mid);
   }
   return count;
}
//============================================================
// <T>������־д�����ı�š�</T>
//
// @param TInt code Ҫ���õı�š�
//============================================================
void FLoggerWriter::SetCode(TInt code){
   _code = code;
}

//============================================================
// <T>������־д�����Ķ�Ӧ�ļ�����</T>
//
// @param TCharC* pName д����־���ļ�����
//============================================================
void FLoggerWriter::SetName(TCharC* pName){
   _name = pName;
}

//============================================================
// <T>������־�ļ�Ŀ¼��</T>
//
// @param TCharC* pPath ��־�ļ���ŵ�Ŀ¼��
//============================================================
void FLoggerWriter::SetPath(TCharC* pPath){
   _path = pPath;
}

//============================================================
// <T>������־�ļ�������С��</T>
//
// @param TSize capacity �ļ��Ĵ�С��
//============================================================
void FLoggerWriter::SetCapacity(TSize capacity){
   _capacity = capacity;
}

//============================================================
// <T>�Ƿ�ǿ��ˢ�µ��ļ���</T>
//
// @param TBool isForceFlush �Ƿ�ǿ��ˢ�¡�
//============================================================
void FLoggerWriter::SetForceToFlush(TBool isForceFlush){
   _forceToFlush = isForceFlush;
}

//============================================================
// <T>�����־д�����ı�š�</T>
//
// @return ��־д�����ı�š�
//============================================================
TInt FLoggerWriter::Code(){
   return _code;
}

//============================================================
// <T>����־д������</T>
//
// @return �շ�򿪳ɹ���
//============================================================
TResult FLoggerWriter::Open(){
   _locker.Enter();
   if(!RFile::ExistPath(_path)){
      RFile::CreateFullDirectory((TCharC*)_path);
   }
   TResult resultCd = ESuccess;
#ifdef _MO_LINUX
   _fileCount = 1;
   TFsDateTime fsDate = RDateTime::Current();
   TFsName pathPrefix;
   pathPrefix.Append(_path);
   pathPrefix.Append("/");
   pathPrefix.Append(_name);
   pathPrefix.Append("_");
   pathPrefix.Append(fsDate.Format("%y%m%d"));
   pathPrefix.Append("_");
   TFsName fullName;
   fullName.Append(pathPrefix);
   fullName.AppendFormat("%04d.log", _fileCount);
   // ������000max
   if(RFile::ExistFile(fullName)){
      struct dirent* pDir;
      DIR* pDirBase = opendir(_path);
      while(NULL != (pDir = readdir(pDirBase))){
         //if((strcmp(pDir->d_name, ".") == 0) || (strcmp(pDir->d_name,".."))) {
           // continue;
         //
         TInt count = GetCountFromName((TCharC*)pDir->d_name);
         if(count > _fileCount){
            _fileCount = count;
         }
      }
      closedir(pDirBase);
      fullName.Clear();
      fullName.Append(pathPrefix);
      fullName.AppendFormat("%04d.log", _fileCount);
      struct stat st;
      if(stat((TCharC*)fullName,&st)){
         MO_ERROR("Stat file:%s failed, errno:%d.",(TCharC*)fullName , errno);
         return EFalse;
      }else{
         if((TSize)st.st_size >= _capacity){ //д��
            _fileCount++;
            fullName.Clear();
            fullName.Append(pathPrefix);
            fullName.AppendFormat("%04d.log", _fileCount);
            ret = _pStream->Create((TCharC*)fullName);
         }else{
            ret = _pStream->OpenAppend((TCharC*)fullName);
            _length = st.st_size;
         }
      }
   }else{
      ret = _pStream->Create((TCharC*)fullName);
   }
#endif
   _locker.Leave();
   return resultCd;
}

//============================================================
// <T>����һ���µ���־�ļ���</T>
//
// @return �Ƿ񴴽��ɹ���
//============================================================
TResult FLoggerWriter::Create(){
   _locker.Enter();
   //TInt count = GetCountFromName(_pStream->FileName());
   _fileCount++;
   TDateTime curDay = RDateTime::Current() / (TDateTime)MO_DATA_DAY_US;
   if(_today < curDay){
      _fileCount = 1;
      _today = curDay;
   }
   TDateTime currentTime = RDateTime::Current();
   //TChar buffer[256];
   //RDateTime::ToString(buffer, 256, currentTime, "%y%m%d");
   //_today = currentTime / (TDateTime)MO_DATA_DAY_US;
   TFsDateTime fsDate = currentTime;
   TFsName fullName;
   fullName.Append(_path);
   fullName.Append('/');
   fullName.Append(_name);
   fullName.Append('_');
   fullName.Append(fsDate.Format(TC("%y%m%d")));
   //fullName.Append(buffer);
   fullName.Append('_');
   fullName.AppendFormat(TC("%04d.log"), _fileCount);
   _pStream->Close();
   _pStream->Open((TCharC*)fullName);
   _length = 0;
   _locker.Leave();
   return ESuccess;
}

//============================================================
// <T>��һ����Ϣ��¼����־�С�</T>
//
// @param TCharC* pMessage ��Ϣ�����ݡ�
// @param TSize length ��Ϣ�ĳ��ȡ�
// @return �Ƿ��¼�ɹ���
//============================================================
TResult FLoggerWriter::Write(TDateTime time, TCharC* pMessage, TInt length){
   time /= (TDateTime)MO_DATA_DAY_US;
   // ����ļ��Ƿ���Ҫ�л�
   _length += length;
   if((_length > _capacity) || (_today < time)){
      Create();
   }
   // д����־
   TResult resultCd = EFailure;
   _locker.Enter();
   // д������
   TInt lengthWrite = _pStream->Write(pMessage, length);
   if(lengthWrite == length){
      resultCd = ESuccess;
   }
   // д�뻻��
   if(resultCd == ESuccess){
      lengthWrite = _pStream->Write(TC("\n"), sizeof(TChar));
      if(lengthWrite == sizeof(TChar)){
         resultCd = ESuccess;
      }
   }
   // �Ƿ�Ҫǿ��ˢ��
   if(resultCd){
      if(_forceToFlush){
         _pStream->Flush();
      }
   }
   _locker.Leave();
   return resultCd;
}

//============================================================
// <T>ˢ�����ݡ�</T>
//
// @return ������
//============================================================
TResult FLoggerWriter::Flush(){
   TResult result = ESuccess;
   _locker.Enter();
   result = _pStream->Flush();
   _locker.Leave();
   return result;
}

//============================================================
// <T>�ر���־д������</T>
//
// @return �ر��Ƿ�ɹ���
//============================================================
TResult FLoggerWriter::Close(){
   TResult result = ESuccess;
   _locker.Enter();
   result = _pStream->Close();
   _locker.Leave();
   return result;
}

//============================================================
// <T>�ر���־д������</T>
//
// @return ������
//============================================================
TResult FLoggerWriter::Refresh(){
   return ESuccess;
}

MO_NAMESPACE_END
