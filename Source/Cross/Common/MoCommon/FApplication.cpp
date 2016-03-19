#ifdef _MO_WINDOWS
#endif
#ifdef _MO_LINUX
#ifndef __CYGWIN__
#include <execinfo.h>
#include <ucontext.h>
#endif
#ifndef NO_CPP_DEMANGLE
#include <cxxabi.h>
#endif
#include <sys/file.h>
#include <unistd.h>
#include <dlfcn.h>
#ifdef REG_RIP
#define SIGSEGV_STACK_IA64
#elif defined(REG_EIP)
#define SIGSEGV_STACK_X86
#else
#define SIGSEGV_STACK_GENERIC
#endif
#endif
#include "MoCmSystem.h"

#define MO_BACKTRACE_MAXCOUNT 64

MO_NAMESPACE_BEGIN

//============================================================
FListeners* FApplication::_pInterrruptListeners = NULL;
FListeners* FApplication::_pReloadListeners = NULL;
FListeners* FApplication::_pUnloadListeners = NULL;
FListeners* FApplication::_pShutdownListeners = NULL;

//============================================================
// <T>����Ӧ�ó������</T>
//============================================================
FApplication::FApplication(){
   _pParameters = MO_PTR_CREATE(FApplicationParameters);
#ifdef _MO_WINDOWS
   _hInstance = NULL;
   _commandShow = 0;
#endif
}

//============================================================
// <T>����Ӧ�ó������</T>
//============================================================
FApplication::~FApplication(){
   MO_PTR_DELETE(_pParameters);
   MO_PTR_DELETE(_pInterrruptListeners);
   MO_PTR_DELETE(_pReloadListeners);
   MO_PTR_DELETE(_pUnloadListeners);
   MO_PTR_DELETE(_pShutdownListeners);
}

#ifdef _MO_WINDOWS
//============================================================
// <T>��õ�ǰӦ�ó���ľ����</T>
//
// @history 100424 MAOCY ����
//============================================================
TInstance FApplication::Hinstance(){
   return _hInstance;
}

//============================================================
void FApplication::SetHinstance(HINSTANCE instance){
   _hInstance = instance;
}

//============================================================
TInt FApplication::CommandShow(){
   return _commandShow;
}

//============================================================
void FApplication::SetCommandShow(TInt commandShow){
   _commandShow = commandShow;
}
#endif

//============================================================
// <T>���������źš�</T>
//
// @param signum �жϺ�
// @param info ��Ϣ
// @param ptr ָ��
//============================================================
#ifdef _MO_LINUX
void FApplication::OnCapture(int signum, siginfo_t* info, TAny* ptr){
   // �����ӽ���״̬�ı��ź�
   if(SIGCLD == signum){
      MO_STATIC_ERROR(TC("Application capture signal. (code=%d:%s)"), signum, strsignal(signum));
      MO_STATIC_DUMP(TC("Application capture signal. (code=%d:%s)"), signum, strsignal(signum));
#ifndef __CYGWIN__
      wait();
#endif
      return;
   }
   //............................................................
   TFsDump dump;
   dump.Append(TC("Application failure being. -----------------------------------------------------\n"));
   RSystem::Dump(&dump);
   //............................................................
   // ��ò���
#ifndef __CYGWIN__
   // ������Ϣ
   dump.AppendFormat("System crash. [ *>o<* ] you are die!!!\n");
   dump.AppendFormat("Signal failure. (code=%d:%s)\n", signum, strsignal(signum));
   dump.AppendFormat("   info.si_signo = %d\n", info->si_signo);
   dump.AppendFormat("   info.si_errno = %d\n", info->si_errno);
   dump.AppendFormat("   info.si_code  = %d\n", info->si_code);
   dump.AppendFormat("   info.si_addr  = %p\n", info->si_addr);
   // �Ĵ�����Ϣ
   ucontext_t* pUcontext = (ucontext_t*)ptr;
   TInt columnCount = 5;
   TInt rowCount = NGREG / columnCount;
   if(NGREG % columnCount != 0){
      rowCount++;
   }
   if(rowCount > 0){
      TInt n = 0;
      for(TInt y = 0; y < rowCount; y++){
         dump.Append("   -- ");
         for(TInt x = 0; x < columnCount; x++){
            dump.AppendFormat("reg[%02" MO_FMT_INT "] = 0x%16" MO_FMT_HEX, n, pUcontext->uc_mcontext.gregs[n]);
            if(x != columnCount - 1){
               dump.Append("  |  ");
            }
            n++;
         }
         dump.Append("\n");
      }
   }
#endif
   //............................................................
   // ��ʾ��ջ
   dump.Append("Stack trace begin.\n");
   RSystem::FetchStackDetail(&dump);
   dump.Append("Stack trace end.\n");
   dump.Append(TC("Application failure end. -------------------------------------------------------"));
   MO_STATIC_ERROR(TC("Application capture.\n%s"), (TCharC*)dump);
   MO_STATIC_DUMP(TC("Application capture.\n%s"), (TCharC*)dump);
   // ˢ����־
   RLoggerManager::Instance().Flush();
   //............................................................
   // ж�������ź�
   RApplication::Instance().UninstallCatcher();
   //............................................................
   // �����ն˼���
   if(NULL != _pInterrruptListeners){
      _pInterrruptListeners->Process();
      _pInterrruptListeners->Clear();
   }
   // ˢ����־
   RLoggerManager::Instance().Flush();
   //............................................................
   // ����رռ���
   if(NULL != _pShutdownListeners){
      _pShutdownListeners->Process();
      _pShutdownListeners->Clear();
   }
   //............................................................
   // ��������������core�ļ���
   abort();
}
#endif // _MO_LINUX

//============================================================
// <T>���������źš�</T>
//
// @param signum �жϺ�
// @param info ��Ϣ
// @param ptr ָ��
//============================================================
#ifdef _MO_LINUX
void FApplication::OnReload(int signum, siginfo_t* info, TAny* ptr){
   // ˢ����־
   RLoggerManager::Instance().Flush();
   MO_STATIC_INFO("Reload application begin. ------------------------------------------------------");
   if(NULL != _pReloadListeners){
      _pReloadListeners->Process();
   }
   MO_STATIC_INFO("Reload application end. --------------------------------------------------------");
   // ˢ����־
   RLoggerManager::Instance().Flush();
}
#endif

//============================================================
// <T>���������źš�</T>
//
// @param signum �жϺ�
// @param info ��Ϣ
// @param ptr ָ��
//============================================================
#ifdef _MO_LINUX
void FApplication::OnUnload(int signum, siginfo_t* info, TAny* ptr){
   // ˢ����־
   RLoggerManager::Instance().Flush();
   MO_STATIC_INFO("Unload application begin. ------------------------------------------------------");
   if(NULL != _pUnloadListeners){
      _pUnloadListeners->Process();
   }
   MO_STATIC_INFO("Unload application end. --------------------------------------------------------");
   // ˢ����־
   RLoggerManager::Instance().Flush();
   // �����˳�
   exit(0);
}
#endif

//============================================================
// <T>��������źš�</T>
//
// @param signum �жϺ�
// @param info ��Ϣ
// @param ptr ָ��
//============================================================
#ifdef _MO_LINUX
void FApplication::OnTerminate(int signum, siginfo_t* info, TAny* ptr){
   // ˢ����־
   RLoggerManager::Instance().Flush();
   // ж�������ź�
   RApplication::Instance().UninstallCatcher();
   //............................................................
   // ��ֹ����
   MO_STATIC_INFO("Terminate application begin. ---------------------------------------------------");
   if(NULL != _pUnloadListeners){
      _pUnloadListeners->Process();
      _pUnloadListeners->Clear();
   }
   MO_STATIC_INFO("Terminate application end. -----------------------------------------------------");
   RLoggerManager::Instance().Flush();
   //............................................................
   // ����رռ���
   if(NULL != _pShutdownListeners){
      _pShutdownListeners->Process();
      _pShutdownListeners->Clear();
   }
   //............................................................
   // �뿪����
   exit(ESuccess);
}
#endif

//============================================================
// <T>����жϼ��������ϡ�</T>
//
// @return ����������
//============================================================
FListeners* FApplication::InterruptListeners(){
   if(NULL == _pInterrruptListeners){
      _pInterrruptListeners = MO_PTR_CREATE(FListeners);
   }
   return _pInterrruptListeners;
}

//============================================================
// <T>������¼��ؼ��������ϡ�</T>
//
// @return ����������
//============================================================
FListeners* FApplication::ReloadListeners(){
   if(NULL == _pReloadListeners){
      _pReloadListeners = MO_PTR_CREATE(FListeners);
   }
   return _pReloadListeners;
}

//============================================================
// <T>���ж�ؼ��������ϡ�</T>
//
// @return ����������
//============================================================
FListeners* FApplication::UnloadListeners(){
   if(NULL == _pUnloadListeners){
      _pUnloadListeners = MO_PTR_CREATE(FListeners);
   }
   return _pUnloadListeners;
}

//============================================================
// <T>��ùرռ��������ϡ�</T>
//
// @return ����������
//============================================================
FListeners* FApplication::ShutdownListeners(){
   if(NULL == _pShutdownListeners){
      _pShutdownListeners = MO_PTR_CREATE(FListeners);
   }
   return _pShutdownListeners;
}

//============================================================
// <T>������Ч�ڴ����</T>
//
// @history 100412 MAOCY ����
//============================================================
TInt FApplication::InstallCatcher(){
   // ��װ�źŲ�׽��
#ifdef _MO_LINUX
   struct sigaction action;
   memset(&action, 0, sizeof(struct sigaction));
#ifndef __CYGWIN__
   action.sa_flags = SA_SIGINFO;
   action.sa_sigaction = OnCapture;
#endif
   // 1:���ź����û��ն�����(�����������)����ʱ����,
   if(sigaction(SIGHUP, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 3: ���û����ն��ϰ��˳�����һ�����Ctrl-/��ʱ���������źţ�������ǰ̨�������е����н��̡�
   //    ���źŲ�����ֹǰ̨�����飨��SIGINT��������������ͬʱ����һ��core�ļ���
   if(sigaction(SIGQUIT, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 4: ���ź�ָʾ������ִ��һ���Ƿ�Ӳ��ָ�
   if(sigaction(SIGILL, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 5:ָʾһ��ʵ�ֶ����Ӳ�����ϡ�
   if(sigaction(SIGTRAP, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 6:����Abort����ʱ�������ź�
   if(sigaction(SIGABRT, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 7:ָʾһ��ʵ�ֶ����Ӳ������
   if(sigaction(SIGBUS, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 8:���źű�ʾһ�����������쳣���������0����������ȡ�
   if(sigaction(SIGFPE, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 9:���������������������. ���źŲ��ܱ�����������ͺ��ԡ�
   // �������Ա����ĳ��������ֹ���ˣ��ɳ��Է�������źš�
   //if(sigaction(SIGKILL, &action, NULL) < 0){
   //   perror("sigaction");
   //   return EError;
   //}
   // 11:ָʾ���̽�����һ����Ч�Ĵ洢���ʡ�
   if(sigaction(SIGSEGV, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 13:���Թܵ������ź�
   signal(SIGPIPE, SIG_IGN);
   // 14:ʱ�Ӷ�ʱ�ź�, �������ʵ�ʵ�ʱ���ʱ��ʱ��. alarm����ʹ�ø��ź�.
   //if(sigaction(SIGALRM, &action, NULL) < 0){
   //   perror("sigaction");
   //   return EError;
   //}
#ifndef __CYGWIN__
   // 16:��ջ��
   if(sigaction(SIGSTKFLT, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
#endif
   // 18:��һ��ֹͣ(stopped)�Ľ��̼���ִ��. ���źŲ��ܱ�������
   // if(sigaction(SIGCONT, &action, NULL) < 0){
   //    perror("sigaction");
   //    return EError;
   // }
   // 20:ֹͣ���̵�����, �����źſ��Ա�����ͺ��ԡ��������նˣ�tty���ϰ���ֹͣ�� ��
   signal(SIGTSTP, SIG_IGN);
   // 23:��"����"���ݻ�out-of-band���ݵ���socketʱ����.
   signal(SIGURG, SIG_IGN);
   // 20:�ӽ��̽���ʱ, �����̻��յ�����źš�
   if(sigaction(SIGCHLD, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 21:����̨��ҵҪ���û��ն˶�����ʱ, ����ҵ�е����н��̻��յ�SIGTTIN�ź�. ȱʡʱ��Щ���̻�ִֹͣ��.
   signal(SIGTTIN, SIG_IGN);
   // 22:������SIGTTIN, ����д�ն�(���޸��ն�ģʽ)ʱ�յ���
   signal(SIGTTOU, SIG_IGN);
   // 24:����CPUʱ����Դ����. ������ƿ�����getrlimit/setrlimit����ȡ/�ı䡣
   if(sigaction(SIGXCPU, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 25:��������ͼ�����ļ������ڳ����ļ���С��Դ���ơ�
   if(sigaction(SIGXFSZ, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 29:�ļ�������׼������, ���Կ�ʼ��������/�������.
   if(sigaction(SIGIO, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 30:Power failure
   if(sigaction(SIGPWR, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 31:�Ƿ���ϵͳ���á�
   if(sigaction(SIGSYS, &action, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   //............................................................
   // 2:������ֹ(interrupt)�ź�, ���û�����INTR�ַ�(ͨ����Ctrl-C)ʱ����������֪ͨǰ̨��������ֹ���̡�
   struct sigaction actionInt;
   memset(&actionInt, 0, sizeof(struct sigaction));
#ifndef __CYGWIN__
   actionInt.sa_flags = SA_SIGINFO;
   actionInt.sa_sigaction = OnTerminate;
#endif
   if(sigaction(SIGINT, &actionInt, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   // 15:�������(terminate)�ź�, ��SIGKILL��ͬ���Ǹ��źſ��Ա������ʹ���
   //    ͨ������Ҫ������Լ������˳���shell����killȱʡ��������źš�
   //    ���������ֹ���ˣ����ǲŻ᳢��SIGKILL��
   struct sigaction actionTerm;
   memset(&actionTerm, 0, sizeof(struct sigaction));
#ifndef __CYGWIN__
   actionTerm.sa_flags = SA_SIGINFO;
   actionTerm.sa_sigaction = OnTerminate;
#endif
   if(sigaction(SIGTERM, &actionTerm, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   //............................................................
   // ��װUser1�ź�Ϊ����
   struct sigaction actionUser1;
   memset(&actionUser1, 0, sizeof(struct sigaction));
#ifndef __CYGWIN__
   actionUser1.sa_flags = SA_SIGINFO;
   actionUser1.sa_sigaction = OnReload;
#endif
   if(sigaction(SIGUSR1, &actionUser1, NULL) < 0){
      perror("sigaction");
      return EError;
   }
   //............................................................
   // 31:��װUser2�ź�Ϊж��
   struct sigaction actionUser2;
   memset(&actionUser2, 0, sizeof(struct sigaction));
#ifndef __CYGWIN__
   actionUser2.sa_flags = SA_SIGINFO;
   actionUser2.sa_sigaction = OnUnload;
#endif
   if(sigaction(SIGUSR2, &actionUser2, NULL) < 0){
      perror("sigaction");
      return EError;
   }
#endif
   return ESuccess;
}

//============================================================
// <T>������Ч�ڴ����</T>
//
// @history 100412 MAOCY ����
//============================================================
TInt FApplication::UninstallCatcher(){
#ifdef _MO_LINUX
   // 1:���ź����û��ն�����(�����������)����ʱ����,
   signal(SIGHUP, SIG_DFL);
   // 2:������ֹ(interrupt)�ź�, ���û�����INTR�ַ�(ͨ����Ctrl-C)ʱ����������֪ͨǰ̨��������ֹ���̡�
   signal(SIGINT, SIG_DFL);
   // 3: ���û����ն��ϰ��˳�����һ�����Ctrl-/��ʱ���������źţ�������ǰ̨�������е����н��̡�
   //    ���źŲ�����ֹǰ̨�����飨��SIGINT��������������ͬʱ����һ��core�ļ���
   signal(SIGQUIT, SIG_DFL);
   // 4: ���ź�ָʾ������ִ��һ���Ƿ�Ӳ��ָ�
   signal(SIGILL, SIG_DFL);
   // 5:ָʾһ��ʵ�ֶ����Ӳ�����ϡ�
   signal(SIGTRAP, SIG_DFL);
   // 6:����Abort����ʱ�������ź�
   signal(SIGABRT, SIG_DFL);
   // 7:ָʾһ��ʵ�ֶ����Ӳ������
   signal(SIGBUS, SIG_DFL);
   // 8:���źű�ʾһ�����������쳣���������0����������ȡ�
   signal(SIGFPE, SIG_DFL);
   // 9:���������������������. ���źŲ��ܱ�����������ͺ��ԡ�
   // �������Ա����ĳ��������ֹ���ˣ��ɳ��Է�������źš�
   // 11:ָʾ���̽�����һ����Ч�Ĵ洢���ʡ�
   signal(SIGSEGV, SIG_DFL);
   // 13:���Թܵ������ź�
   signal(SIGPIPE, SIG_IGN);
   // 14:ʱ�Ӷ�ʱ�ź�, �������ʵ�ʵ�ʱ���ʱ��ʱ��. alarm����ʹ�ø��ź�.
   signal(SIGALRM, SIG_DFL);
   // 15:�������(terminate)�ź�, ��SIGKILL��ͬ���Ǹ��źſ��Ա������ʹ���
   //    ͨ������Ҫ������Լ������˳���shell����killȱʡ��������źš�
   //    ���������ֹ���ˣ����ǲŻ᳢��SIGKILL��
   signal(SIGTERM, SIG_DFL);
#ifndef __CYGWIN__
   // 16:��ջ��
   signal(SIGSTKFLT, SIG_DFL);
#endif
   // 18:��һ��ֹͣ(stopped)�Ľ��̼���ִ��. ���źŲ��ܱ�������
   signal(SIGCONT, SIG_DFL);
   // 20:ֹͣ���̵�����, �����źſ��Ա�����ͺ��ԡ��������նˣ�tty���ϰ���ֹͣ�� ��
   signal(SIGTSTP, SIG_DFL);
   // 23:��"����"���ݻ�out-of-band���ݵ���socketʱ����.
   signal(SIGURG, SIG_DFL);
   // 20:�ӽ��̽���ʱ, �����̻��յ�����źš�
   signal(SIGCHLD, SIG_DFL);
   // 21:����̨��ҵҪ���û��ն˶�����ʱ, ����ҵ�е����н��̻��յ�SIGTTIN�ź�. ȱʡʱ��Щ���̻�ִֹͣ��.
   signal(SIGTTIN, SIG_DFL);
   // 22:������SIGTTIN, ����д�ն�(���޸��ն�ģʽ)ʱ�յ���
   signal(SIGTTOU, SIG_DFL);
   // 24:����CPUʱ����Դ����. ������ƿ�����getrlimit/setrlimit����ȡ/�ı䡣
   signal(SIGXCPU, SIG_DFL);
   // 25:��������ͼ�����ļ������ڳ����ļ���С��Դ���ơ�
   signal(SIGXFSZ, SIG_DFL);
   // 29:�ļ�������׼������, ���Կ�ʼ��������/�������.
   signal(SIGIO, SIG_DFL);
   // 30:Power failure
   signal(SIGPWR, SIG_DFL);
   // 31:�Ƿ���ϵͳ���á�
   signal(SIGSYS, SIG_DFL);
   //............................................................
   signal(SIGUSR1, SIG_DFL);
   signal(SIGUSR2, SIG_DFL);
#endif // _MO_LINUX
   return ESuccess;
}

//============================================================
// <T>��ÿ�ִ���ļ��ĵ�ǰ·����</T>
//
// @history 100302 MAOCY ����
//============================================================
TInt FApplication::InstallDaemon(){
#ifdef _MO_LINUX
   /*TFsPath path = RApplication::GetCurrentDirectory();
   // ����ָ���ļ���ʱ������Ϊ��ǰʱ��
   system("touch application");
   // ���ļ�
   TInt handle = open("./application.lock", O_RDWR | O_CREAT, 0640);
   if(handle < 0){
      MO_STATIC_PFATAL(open);
   }
   // �����ļ�
   TInt result = flock(handle, LOCK_EX | LOCK_NB);
   if(result < 0){
      MO_STATIC_PFATAL(flock);
   }
   // ��¡����
   pid_t pid = fork();
   if(ESuccess != pid){
      exit(ESuccess);
   }
   // �����ź�
   setsid();
   signal(SIGHUP, SIG_IGN);
   signal(SIGINT, SIG_IGN);
   signal(SIGQUIT, SIG_IGN);
   signal(SIGCHLD, SIG_IGN);
   signal(SIGTERM, SIG_IGN);
   struct sigaction sig;
   sig.sa_handler = SIG_IGN;
   sig.sa_flags = 0;
   sigemptyset(&sig.sa_mask);
   sigaction(SIGHUP, &sig, NULL);
   // ��¡����
   pid = fork();
   if(ESuccess != pid){
      exit(ESuccess);
   }
   // ���Ը���·��
   if(chdir(path.MemoryC())){
      MO_STATIC_DEBUG("Can't change run dir to %s after initialize daemon.", path.MemoryC());
      exit(2);
   }
   // ���ú����ļ�Ȩ��
   umask(0);
   // ���ý�����
   setpgrp();*/
#endif // _MO_LINUX
   return ESuccess;
}

MO_NAMESPACE_END
