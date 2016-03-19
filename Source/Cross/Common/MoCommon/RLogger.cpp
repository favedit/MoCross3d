#include "MoCmRuntime.h"

MO_NAMESPACE_BEGIN

//============================================================
ILoggerConsole* RLogger::_pConsole = NULL;

//============================================================
// <T>������־�������</T>
//
// @param pConsole ��־�����
//============================================================
void RLogger::Link(ILoggerConsole* pConsole){
   _pConsole = pConsole;
}

//============================================================
// <T>�����־����̨��</T>
//
// @return ��־����̨
//============================================================
ILoggerConsole* RLogger::Console(){
   return _pConsole;
}

//============================================================
// <T>�����Ϣ��</T>
//
// @param type ��Ϣ����
// @param level ��Ϣ����
// @param pSender ������
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Output(TInt type, ELoggerLevel level, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, va_list& params){
   if(_pConsole != NULL){
      // ʹ�ù����������Ϣ
#ifdef _MO_UNICODE
      TChar method[MO_FS_NAME_LENGTH];
      if(pMethod != NULL){
         TInt n = 0;
         for(; n < MO_FS_NAME_LENGTH - 1; n++){
            method[n] = *pMethod++;
         }
         method[n] = 0;
      }
      _pConsole->Output(type, level, pSender, method, start, pMessage, params);
#else
      _pConsole->Output(type, level, pSender, pMethod, start, pMessage, params);
#endif // _MO_UNICODE
   }else{
//      // ֱ�������Ϣ
//#ifdef _UNICODE
//      vwprintf(pMessage, params);
//#else
//      vprintf(pMessage, params);
//#endif // _UNICODE
   }
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Debug(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Debug, pSender, pMethod, 0, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Debug(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Debug, pSender, pMethod, start, pMessage, params);
   va_end(params);
}

//============================================================
// <T>�����ʾ��Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Info(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Info, pSender, pMethod, 0, pMessage, params);
   va_end(params);
}

//============================================================
// <T>�����ʾ��Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Info(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Info, pSender, pMethod, start, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Warn(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Warn, pSender, pMethod, 0, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Warn(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Warn, pSender, pMethod, start, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Error(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Error, pSender, pMethod, 0, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Error(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Error, pSender, pMethod, start, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���ϵͳ������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Fatal(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Fatal, pSender, pMethod, 0, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���ϵͳ������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Fatal(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Fatal, pSender, pMethod, start, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���ϵͳ������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Crash(TInt type, TAnyC* pSender, TChar8C* pMethod, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Crash, pSender, pMethod, 0, pMessage, params);
   va_end(params);
}

//============================================================
// <T>���ϵͳ������Ϣ��</T>
//
// @param type ��Ϣ����
// @param pSender ������
// @param pMethod ���ú���
// @param start ��ʼʱ��
// @param pMessage ��Ϣ����
// @param ... ��Ϣ����
//============================================================
void RLogger::Crash(TInt type, TAnyC* pSender, TChar8C* pMethod, TTimeTick start, TCharC* pMessage, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pMessage);
   // �����־��Ϣ
   Output(type, ELoggerLevel_Crash, pSender, pMethod, start, pMessage, params);
   va_end(params);
}

MO_NAMESPACE_END
