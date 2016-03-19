#include "MoCmSystem.h"
#include "MoCmThread.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��׽����������</T>
//============================================================
void FCatcherConsole_Process(TInt32 code){
   RCatcherManager::Instance().Jump(code);
}

//============================================================
// <T>������׽������̨��</T>
//============================================================
FCatcherConsole::FCatcherConsole(){
#ifdef _MO_LINUX
   RTypes<SCatcher>::Clear(_catchers, MO_TRAP_ACTION_MAXCNT);
#endif // _LINUX
   _pThreadCatchers = MO_CREATE(FThreadCatcherVector);
}

//============================================================
// <T>�ͷŲ�׽������̨��</T>
//============================================================
FCatcherConsole::~FCatcherConsole(){
   MO_DELETE(_pThreadCatchers);
}

//============================================================
// <T>��ָ������ע�Ჶ׽����</T>
//
// @param code ����
// @return ������
//============================================================
TBool FCatcherConsole::IsRegistered(TInt code){
   MO_ASSERT_RANGE(code, 0, MO_TRAP_ACTION_MAXCNT);
   TBool result = EFalse;
   //............................................................
   // ����Ƿ��Ѿ���װ
   _lockerInstall.Enter();
#ifdef _MO_LINUX
   result = _catchers[code].installed;
#endif // _LINUX
   _lockerInstall.Leave();
   return result;
}

//============================================================
// <T>��ָ������ע�Ჶ׽����</T>
//
// @param code ����
// @return ������
//============================================================
TBool FCatcherConsole::Register(TInt code){
   MO_ASSERT_RANGE(code, 0, MO_TRAP_ACTION_MAXCNT);
   TBool result = EFalse;
   //............................................................
   // ����Ƿ��Ѿ���װ
   _lockerInstall.Enter();
#ifdef _MO_LINUX
   SCatcher& catcher = _catchers[code];
   if(catcher.installed){
      MO_ERROR("Has already install catcher. (code=%2d:%s)", code, strsignal(code));
   }else{
      // ��װ������
      struct sigaction& action = catcher.source;
      action.sa_handler = FCatcherConsole_Process;
      action.sa_flags = 0;
      sigemptyset(&action.sa_mask);
      TInt actionResult = sigaction(code, &action, &catcher.origin);
      if(ESuccess != actionResult){
         MO_PFATAL(sigaction);
         result = EFalse;
      }else{
         catcher.installed = ETrue;
         result = ETrue;
      }
      MO_INFO("Install catcher action. (code=%2d:%s, handle=0x%08X, mask=0x%08X, flags=0x%08X, result=%d)",
            code, strsignal(code), action.sa_handler, action.sa_mask, action.sa_flags, actionResult);
   }
#endif // _LINUX
   _lockerInstall.Leave();
   return result;
}

//============================================================
// <T>��ָ������ע����׽����</T>
//
// @param code ����
// @return ������
//============================================================
TBool FCatcherConsole::Unregister(TInt code){
   MO_ASSERT_RANGE(code, 0, MO_TRAP_ACTION_MAXCNT);
   TBool result = EFalse;
   //............................................................
   // ����Ƿ��Ѿ���װ
   _lockerInstall.Enter();
#ifdef _MO_LINUX
   SCatcher& catcher = _catchers[code];
   if(catcher.installed){
      // ж�ش�����
      TInt actionResult = sigaction(code, &catcher.origin, NULL);
      if(ESuccess != actionResult){
         MO_PFATAL(sigaction);
         result = EFalse;
      }else{
         catcher.installed = EFalse;
         result = ETrue;
      }
      MO_INFO("Uninstall catcher action. (code=%2d:%s, result=%d)", code, strsignal(code), actionResult);
   }else{
      MO_ERROR("Not install any catcher. (code=%2d:%s)", code, strsignal(code));
   }
#endif // _LINUX
   _lockerInstall.Leave();
   return result;
}

//============================================================
// <T>����ָ���̵߳Ĳ�׽����</T>
//
// @param threadCode �̴߳���
// @return ��׽��
//============================================================
FThreadCatcher* FCatcherConsole::FindThreadCatcher(TInt threadCode){
   FThreadCatcher* pThreadCatcher = NULL;
   _locker.Enter();
   TInt count = _pThreadCatchers->Count();
   for(TInt n = 0; n < count; n++){
      FThreadCatcher* pFind = _pThreadCatchers->Get(n);
      if(pFind->ThreadCode() == threadCode){
         pThreadCatcher = pFind;
         break;
      }
   }
   _locker.Leave();
   return pThreadCatcher;
}

//============================================================
// <T>ͬ��ָ���̵߳Ĳ�׽����</T>
//
// @param threadCode �̴߳���
// @return ��׽��
//============================================================
FThreadCatcher* FCatcherConsole::SyncThreadCatcher(TInt threadCode){
   FThreadCatcher* pThreadCatcher = FindThreadCatcher(threadCode);
   if(NULL == pThreadCatcher){
      pThreadCatcher = MO_CREATE(FThreadCatcher);
      pThreadCatcher->SetThreadCode(threadCode);
      _locker.Enter();
      _pThreadCatchers->Push(pThreadCatcher);
      _locker.Leave();
   }
   return pThreadCatcher;
}

//============================================================
// <T>��õ�ǰ�̵߳Ĳ�׽����</T>
//
// @return ��׽��
//============================================================
FThreadCatcher* FCatcherConsole::CurrentThreadCatcher(){
   TInt threadCode = RThread::CurrentCode();
   FThreadCatcher* pThreadCatcher = SyncThreadCatcher(threadCode);
   return pThreadCatcher;
}

//============================================================
// <T>ע����׽����</T>
//
// @param pCatcher ��׽��
//============================================================
TBool FCatcherConsole::Enter(FCatcher* pCatcher){
   FThreadCatcher* pThreadCatcher = CurrentThreadCatcher();
   MO_ASSERT(pThreadCatcher);
   return pThreadCatcher->Enter(pCatcher);
}

//============================================================
// <T>ע����׽����</T>
//
// @param pCatcher ��׽��
//============================================================
TBool FCatcherConsole::Leave(FCatcher* pCatcher){
   FThreadCatcher* pThreadCatcher = CurrentThreadCatcher();
   MO_ASSERT(pThreadCatcher);
   return pThreadCatcher->Leave(pCatcher);
}

//============================================================
// <T>��ת����</T>
//
// @param code ����
// @return ������
//============================================================
TBool FCatcherConsole::Jump(TInt code){
   FThreadCatcher* pThreadCatcher = CurrentThreadCatcher();
   MO_ASSERT(pThreadCatcher);
   return pThreadCatcher->Jump(code);
}

//============================================================
// <T>��ת��ɴ���</T>
//
// @param pCatcher ��׽��
// @return ������
//============================================================
TBool FCatcherConsole::JumpFinish(FCatcher* pCatcher){
   FThreadCatcher* pThreadCatcher = CurrentThreadCatcher();
   MO_ASSERT(pThreadCatcher);
   return pThreadCatcher->JumpFinish(pCatcher);
}

MO_NAMESPACE_END
