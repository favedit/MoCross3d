#include "MoCmLanguage.h"
#include "MoCmFormat.h"
#include "MoCmSystem.h"
#include "MoCmThread.h"

#define MO_LOGGER_PAD_LENGTH 86

MO_NAMESPACE_BEGIN

//============================================================
// <T>������־����̨��</T>
//
// @return ��־����̨
//============================================================
FLoggerConsole::FLoggerConsole(){
   _name = TC("common.logger.console");
   _closed = EFalse;
   _useLogger = ETrue;
   _useViewer = ETrue;
   _format = TC("%y%m%d-%H%M%S.%s");
   _levelCd = ELoggerLevel_Debug;
   _pWriters = MO_CREATE(FLoggerWriterList);
   _pThread = MO_CREATE(FLoggerThread);
   _pThread->SetWriters(_pWriters);
}

//============================================================
// <T>������־����̨��</T>
//============================================================
FLoggerConsole::~FLoggerConsole(){
}

//============================================================
// <T>��ʽ������</T>
//
// @param levelCd ��Ϣ����
// @return ����
//============================================================
TChar FLoggerConsole::FormatLevelChar(ELoggerLevel levelCd){
   switch(levelCd){
      case ELoggerLevel_Debug:
         return 'D';
      case ELoggerLevel_Info:
         return 'I';
      case ELoggerLevel_Warn:
         return 'W';
      case ELoggerLevel_Error:
         return 'E';
      case ELoggerLevel_Fatal:
         return 'F';
      case ELoggerLevel_Crash:
         return 'C';
   }
   return 'U';
}

//============================================================
// <T>��ʽ�������Ϣ��</T>
//
// @param result ��ʽ�����
// @param level ��Ϣ����
// @param pSender ������
// @param pMethod ��������
// @param start ��ʼʱ��
// @param current ��ǰʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void FLoggerConsole::Format(TFsLogger& result, TDateTime current, ELoggerLevel levelCd, TAnyC* pSender, TCharC* pMethod, TTimeSpan span, TCharC* pMessage, va_list& params){
#ifndef _MO_ANDROID
   // ������ڿ�ʼʱ�䣬���ȼ��㻨��ʱ��
   TFsName datetime;
   RDateTime::ToString(datetime.Memory(), datetime.Size(), current, _format);
   // ��ʽ����־ʱ��
   result.Append(datetime.MemoryC());
   result.Append('|');
   result.Append(FormatLevelChar(levelCd));
   result.Append('.');
   // ��ʽ���߳���Ϣ
   FThread* pThread = RThreadManager::Instance().Current();
   if(NULL != pThread){
      TCharC* pThreadCode = pThread->Code();
      result.AppendFormat(TC("%s-%04d"), pThreadCode, pThread->Index());
   }else{
      TThreadId threadId = RThread::CurrentId();
      result.AppendFormat(TC("%08X"), threadId);
   }
   // ��ʽ������������Ϣ
   result.Append(TC(" [ "));
   result.Append(pMethod);
   if(NULL != pSender){
      result.Append('@');
      result.AppendFormat(TC("%08X"), pSender);
   }
   if(span > 0){
      // ��ʾ����ʱ�䣬��ȷ������
      TFsNumber number;
      number.AppendFormat(TC("%lldus"), span);
      result.PadRight(' ', MO_LOGGER_PAD_LENGTH - number.Length());
      result.Append(number);
   }else{
      // �Զ�����
      result.PadRight(' ', MO_LOGGER_PAD_LENGTH);
   }
   result.Append(TC(" ] "));
#endif // _MO_ANDROID
   // ��ʽ���ɱ�����ַ�����Ϣ
   TChar message[MO_FS_LOGGER_LENGTH];
#ifdef _MO_WINDOWS
#ifdef _UNICODE
   wvsprintf(message, pMessage, params);
#else
   vsprintf_s(message, MO_FS_LOGGER_LENGTH, pMessage, params);
#endif // _UNICODE
#else
   vsnprintf(message, MO_FS_LOGGER_LENGTH, pMessage, params);
#endif // _MO_WINDOWS
   message[MO_FS_LOGGER_LENGTH - 1] = 0;
   result.Append(message);
}

//============================================================
// <T>��ʽ�������Ϣ��</T>
//
// @param result ��ʽ�����
// @param level ��Ϣ����
// @param pSender ������
// @param pMethod ��������
// @param start ��ʼʱ��
// @param current ��ǰʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void FLoggerConsole::FormatTrack(TFsLogger& result, ELoggerLevel levelCd, TAnyC* pSender, TCharC* pMethod, TTimeSpan span, TDateTime current, TCharC* pMessage, va_list& params){
   // ��ʽ����־����
   result.Append(TC("MO."));
   result.Append(FormatLevelChar(levelCd));
   result.Append(TC("> "));
   // ��ʽ���߳���Ϣ
   TThreadId threadId = RThread::CurrentId();
   result.AppendFormat(TC("%08X"), threadId);
   // ��ʽ������������Ϣ
   result.Append(TC(" [ "));
   result.Append(pMethod);
   if(NULL != pSender){
      result.Append('@');
      result.AppendFormat(TC("%08X"), pSender);
   }
   if(span > 0){
      // ��ʾ����ʱ�䣬��ȷ������
      TFsInteger number;
      number.AppendFormat(TC("%lldus"), span);
      result.PadRight(' ', MO_LOGGER_PAD_LENGTH - number.Length());
      result.Append(number);
   }else{
      // �Զ�����
      result.PadRight(' ', MO_LOGGER_PAD_LENGTH);
   }
   result.Append(TC(" ] "));
   // ��ʽ���ɱ�����ַ�����Ϣ
   TChar message[MO_FS_LOGGER_LENGTH];
#ifdef _MO_WINDOWS
#ifdef _UNICODE
   wvsprintf(message, pMessage, params);
#else
   vsprintf_s(message, MO_FS_LOGGER_LENGTH, pMessage, params);
#endif
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   vsnprintf(message, MO_FS_LOGGER_LENGTH, pMessage, params);
#endif
#ifdef _MO_ANDROID
   vsnprintf(message, MO_FS_LOGGER_LENGTH, pMessage, params);
#endif
   message[MO_FS_LOGGER_LENGTH - 1] = 0;
   result.Append(message);
}

//============================================================
// <T>���������Ϣ��</T>
// <P>��ʾ��ʽ:0��Ĭ��ֵ��,1��������,22���Ǵ��壩,4���»��ߣ�,24�����»��ߣ�,5����˸��,25������˸��,7�����ԣ�,27���Ƿ��ԣ�</P>
// <P>ǰ��ɫ:30����ɫ��,31����ɫ��,32����ɫ��,33����ɫ��,34����ɫ��,35����죩,36����ɫ��,37����ɫ��</P>
// <P>����ɫ:40����ɫ��,41����ɫ��,42����ɫ��,43����ɫ��,44����ɫ��,45����죩,46����ɫ��,47����ɫ��</P>
//
// @param code ��Ϣ����
// @param levelCd ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
TBool FLoggerConsole::Output(TInt code, ELoggerLevel levelCd, TAnyC* pSender, TCharC* pMethod, TTimeTick start, TCharC* pMessage, va_list& params){
   // ����������
   if(levelCd < _levelCd){
      return EFalse;
   }
   // ������
   TDateTime current = RDateTime::Current();
   TTimeSpan span = 0;
   if(start > 0){
      span = RTimeTick::Current() - start;
   }
   // ��ú�������
   TFsText line = pMethod;
   TInt left = 0;
   if(line.StartsWith(TC("static "))){
      left = 7;
   }
   if(line.StartsWith(TC("virtual "))){
      left = 8;
   }
   left = MO_LIB_MAX(line.IndexOf(' ', left) + 1, 0);
   TInt right = line.IndexOf('(');
   if(-1 == right){
      right = line.Length();
   }
   TFsName method = line.SubStrC(left, right);
   TInt spaceFlag = method.Find(TC("MO::"));
   if(ENotFound != spaceFlag){
      left = spaceFlag + 4;
   }else{
      left = 0;
   }
   TFsName name = method.SubStrC(left, method.Length());
#ifdef _MO_ANDROID
   // ׷�ӷ�����
   if(NULL != pSender){
      name.Append('@');
      name.AppendFormat(TC("%08X"), pSender);
   }
   // ׷�ӻ���ʱ��
   if(span > 0){
      // ��ʾ����ʱ�䣬��ȷ������
      name.AppendFormat(TC("-%lldus"), span);
   }
#endif // _MO_ANDROID
   // ��ʽ����־
   TFsLogger logger;
   Format(logger, current, levelCd, pSender, (TCharC*)name, span, pMessage, params);
   // ׷��������Ϣ
#ifndef _MO_ANDROID
   if(ELoggerLevel_Fatal == levelCd){
      logger.Append(TC("\n-- Track info begin ----------------------------------------"));
      RSystem::FetchStackSimple(&logger);
      logger.Append(TC("\n-- Track info end ------------------------------------------"));
   }
#endif // _MO_ANDROID
   // �����Ϣ
   if(levelCd != ELoggerLevel_Crash){
      //............................................................
#ifdef _MO_WINDOWS
#ifdef _MO_DEBUG
      if(_useLogger){
         logger.Append(TC("\r\n"));
         MO_LIB_STRING_PRINT(TC("%s"), (TCharC*)logger);
      }
      if(_useViewer){
         OutputDebugString((TCharC*)logger);
      }
#else
      if(_useLogger){
         MO_LIB_STRING_PRINT(TC("%s"), (TCharC*)logger);
      }
#endif // _MO_DEBUG
#endif // _MO_WINDOWS
      //............................................................
#ifdef _MO_LINUX
      if(_useLogger){
         switch(levelCd){
            case ELoggerLevel_Debug:
               printf("%s\n", (TCharC*)logger);
               break;
            case ELoggerLevel_Info:
               printf("\033[0;32;49m%s\033[0m\n", (TCharC*)logger);
               break;
            case ELoggerLevel_Warn:
               printf("\033[0;33;49m%s\033[0m\n", (TCharC*)logger);
               break;
            case ELoggerLevel_Error:
               printf("\033[0;31;49m%s\033[0m\n", (TCharC*)logger);
               break;
            case ELoggerLevel_Fatal:
            case ELoggerLevel_Crash:
               printf("\033[1;31;49m%s\033[0m\n", (TCharC*)logger);
               break;
            default:
               printf("%s\n", (TCharC*)logger);
               break;
         }
      }
#endif // _MO_LINUX
      //............................................................
#ifdef _MO_ANDROID
      if(_useLogger){
         switch(levelCd){
            case ELoggerLevel_Debug:
               __android_log_write(ANDROID_LOG_DEBUG, (TCharC*)name, (TCharC*)logger);
               break;
            case ELoggerLevel_Info:
               __android_log_write(ANDROID_LOG_INFO, (TCharC*)name, (TCharC*)logger);
               break;
            case ELoggerLevel_Warn:
               __android_log_write(ANDROID_LOG_WARN, (TCharC*)name, (TCharC*)logger);
               break;
            case ELoggerLevel_Error:
               __android_log_write(ANDROID_LOG_ERROR, (TCharC*)name, (TCharC*)logger);
               break;
            case ELoggerLevel_Fatal:
            case ELoggerLevel_Crash:
               __android_log_write(ANDROID_LOG_FATAL, (TCharC*)name, (TCharC*)logger);
               break;
            default:
               __android_log_write(ANDROID_LOG_DEBUG, (TCharC*)name, (TCharC*)logger);
               break;
         }
      }
#endif // _MO_ANDROID
   }
   //............................................................
   // ������Ѿ��رգ��������
   if(_closed){
      return EFalse;
   }
   //............................................................
   // �����־��д����
   ILoggerWriter* pWriter = FindWriter(code);
   if(NULL != pWriter){
      pWriter->Write(current, logger, logger.Length());
   }
   return ETrue;
}

//============================================================
// <T>���ʹ����־��</T>
//
// @return ʹ����־
//============================================================
TBool FLoggerConsole::UseLogger(){
   return _useLogger;
}

//============================================================
// <T>����ʹ����־��</T>
//
// @param useLogger ʹ����־
//============================================================
void FLoggerConsole::SetUseLogger(TBool useLogger){
   _useLogger = useLogger;
}

//============================================================
// <T>���ʹ���ӽǡ�</T>
//
// @return ʹ���ӽ�
//============================================================
TBool FLoggerConsole::UseViewer(){
   return _useViewer;
}

//============================================================
// <T>����ʹ���ӽǡ�</T>
//
// @param useViewer ʹ���ӽ�
//============================================================
void FLoggerConsole::SetUseViewer(TBool useViewer){
   _useViewer = useViewer;
}

//============================================================
// <T>��ü������͡�</T>
//
// @return ��������
//============================================================
ELoggerLevel FLoggerConsole::LevelCd(){
   return _levelCd;
}

//============================================================
// <T>���ü������͡�</T>
//
// @param levelCd ��������
//============================================================
void FLoggerConsole::SetLevelCd(ELoggerLevel levelCd){
   _levelCd = levelCd;
}

//============================================================
// <T>����һ��д������</T>
//
// @param code ����
// @return д����
//============================================================
ILoggerWriter* FLoggerConsole::FindWriter(TInt code){
   TListIteratorC<ILoggerWriter*> iterator = _pWriters->IteratorC();
   while(iterator.Next()){
      ILoggerWriter* pWriter = *iterator;
      if(pWriter->Code() == code){
         return pWriter;
      }
   }
   return NULL;
}

//============================================================
// <T>ע��һ����־д������</T>
//
// @param pWriter ��־д����
// @return ������
//============================================================
TResult FLoggerConsole::Register(ILoggerWriter* pWriter){
   // ������
   MO_ASSERT(pWriter);
   if(NULL != FindWriter(pWriter->Code())){
      MO_FATAL(TC("Logger writer code is already exists. (code=%d)"), pWriter->Code());
      return EFailure;
   }
   // ����־
   if(!pWriter->Open()){
      MO_ERROR(TC("Register logger writer failure. (code=%d)"), pWriter->Code());
      return EFailure;
   }
   // ע����־
   _pThread->Section().Enter();
   _pWriters->Push(pWriter);
   _pThread->Section().Leave();
   return ESuccess;
}

//============================================================
// <T>ע��һ����־д������</T>
//
// @param pWriter ��־д����
// @return ������
//============================================================
TResult FLoggerConsole::Unregister(ILoggerWriter* pWriter){
   // ������
   MO_ASSERT(pWriter);
   if(NULL == FindWriter(pWriter->Code())){
      MO_FATAL(TC("Logger writer code is not exists. (code=%d)"), pWriter->Code());
      return EFailure;
   }
   // �ر���־
   if(!pWriter->Close()){
      MO_FATAL(TC("Unregister logger writer failure. (code=%d)"), pWriter->Code());
      return EFailure;
   }
   // ע����־
   _pThread->Section().Enter();
   _pWriters->Remove(pWriter);
   _pThread->Section().Leave();
   return ESuccess;
}

//============================================================
// <T>�ڲ�ˢ�´���</T>
//
// @return ������
//============================================================
TResult FLoggerConsole::InnerFlush(){
   TListIteratorC<ILoggerWriter*> iterator = _pWriters->IteratorC();
   while(iterator.Next()){
      iterator->Flush();
   }
   return ESuccess;
}

//============================================================
// <T>�ڲ��رմ���</T>
//
// @return ������
//============================================================
TResult FLoggerConsole::InnerClose(){
   TListIteratorC<ILoggerWriter*> iterator = _pWriters->IteratorC();
   while(iterator.Next()){
      ILoggerWriter* pWriter = *iterator;
      pWriter->Close();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FLoggerConsole::Startup(){
   _pThread->Start();
   return ESuccess;
}

//============================================================
// <T>ˢ�´���</T>
//
// @return ������
//============================================================
TResult FLoggerConsole::Flush(){
   MO_INFO(TC("Logger console flush."));
   return InnerFlush();
}

//============================================================
// <T>���⴦��</T>
//
// @return ������
//============================================================
TResult FLoggerConsole::Interrupt(){
   MO_INFO(TC("Logger console interrupt."));
   return InnerFlush();
}

//============================================================
// <T>���¼�������ģ�顣</T>
//
// @return ������
//============================================================
TResult FLoggerConsole::Reload(){
   MO_INFO(TC("Logger console reload."));
   return InnerFlush();
}

//============================================================
// <T>ж������ģ�顣</T>
//
// @return ������
//============================================================
TResult FLoggerConsole::Unload(){
   MO_INFO(TC("Logger console unload."));
   return InnerFlush();
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FLoggerConsole::Shutdown(){
   MO_INFO(TC("Logger console shutdown."));
   _closed = ETrue;
   // ˢ�´���
   InnerFlush();
   InnerClose();
   return ESuccess;
}

MO_NAMESPACE_END
