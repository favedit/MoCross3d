#include "MoCmSystem.h"

#define MO_SY_STACK_TRACK_MAXCNT 64

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����̲߳�׽����</T>
//============================================================
FThreadCatcher::FThreadCatcher(){
   _threadCode = 0;
   MO_CLEAR(_pActiveCatcher);
   MO_CLEAR(_pJumpCatcher);
   _pCatchers = MO_CREATE(FCatcherVector);
}

//============================================================
// <T>�ͷ��̲߳�׽����</T>
//============================================================
FThreadCatcher::~FThreadCatcher(){
   MO_DELETE(_pCatchers);
}

//============================================================
// <T>������׽������Ч��Χ��</T>
//
// @param pCatcher ��׽��
// @return ������
//============================================================
TBool FThreadCatcher::Enter(FCatcher* pCatcher){
   _lockerActive.Enter();
   pCatcher->SetParent(_pActiveCatcher);
#ifdef _MO_DEBUG
   if(_pCatchers->Contains(pCatcher)){
      MO_FATAL(TC("Catcher is already exists. (catcher=0x%08X:%s)"), pCatcher, pCatcher->Name());
   }
#endif // _MO_DEBUG
   _pCatchers->Push(pCatcher);
   _pActiveCatcher = pCatcher;
   _lockerActive.Leave();
   return ETrue;
}

//============================================================
// <T>�뿪��׽������Ч��Χ��</T>
//
// @param pCatcher ��׽��
// @return ������
//============================================================
TBool FThreadCatcher::Leave(FCatcher* pCatcher){
   _lockerActive.Enter();
   _pActiveCatcher = pCatcher->Parent();
   FCatcher* pEnterCatcher = _pCatchers->Pop();
   if(pCatcher != pEnterCatcher){
      MO_FATAL(TC("Enter and leave catcher is not same. (enter=0x%08X:%s, leave=0x%08X:%s)"),
            pEnterCatcher, pEnterCatcher->Name(), pCatcher, pCatcher->Name());
   }
   _lockerActive.Leave();
   return ETrue;
}

//============================================================
// <T>���ٲ�׽����</T>
//
// @param pCatcher ��׽��
//============================================================
void FThreadCatcher::Track(FCatcher* pCatcher, TInt code){
   TFsDump info;
#ifdef _MO_LINUX
   TCharC* pCodeName = strsignal(code);
#else
   TCharC* pCodeName = TC("Unknown");
#endif // _LINUX
   //............................................................
   info.Append(TC("System rais error."));
   info.Append(TC("\n-- Crash track info begin ----------------------------------"));
   if(NULL != pCatcher){
      info.AppendFormat(TC("\n Catch success. (name=%s@0x%08X, code=%d:%s, info=%s)"),
         pCatcher->Name(), pCatcher, code, pCodeName, pCatcher->Info());
   }else{
      info.AppendFormat(TC("\n Catch failure. (pointer=0x%08X, code=%d:%s)"),
         pCatcher, code, pCodeName);
   }
   //............................................................
   // �����װ�Ĳ�׽��
   TInt countCatcher = _pCatchers->Count();
   for(TInt n = 0; n < countCatcher; n++){
      FCatcher* pFind  = _pCatchers->Get(n);
      info.AppendFormat(TC("\n   Installed (%2d = %s@0x%08X (jump_count=%4d) - %s)"),
         n++, pFind->Name(), pFind, pFind->JumpCount(), pFind->Info());
   }
   //............................................................
   info.Append(TC("\n Crash track info [ BS you begin]"));
   RSystem::FetchStack(&info);
   info.Append(TC("\n Crash track info [ BS you end]"));
   info.Append(TC("\n-- Crash track info end ------------------------------------"));
   MO_DUMP_STACK((TCharC*)info);
   RLoggerManager::Instance().Flush();
}

//============================================================
// <T>ע��һ����׽����</T>
//
// @param code ����
// @return ������
//============================================================
TBool FThreadCatcher::Jump(TInt code){
   // �Ƿ�ע������׽��
   if(NULL == _pActiveCatcher){
      MO_ERROR(TC("Active catcher is not exists."));
      MO_THROW(TC("Uncatcher exception."));
      return EFalse;
   }
   // ����ϲ�
   _pJumpCatcher = _pActiveCatcher;
   while(NULL != _pJumpCatcher){
      if(_pJumpCatcher->IsRegistered(code)){
         break;
      }
      // �����������
      FCatcher* pCatcher = _pCatchers->Pop();
      if(pCatcher == _pJumpCatcher){
         MO_FATAL(TC("Pop catcher and jump not same. (jump_captcher=%s:0x%08X, captcher=%s:0x%08X)"),
               _pJumpCatcher->Name(), _pJumpCatcher, pCatcher->Name(), pCatcher);
      }
      _pJumpCatcher = _pJumpCatcher->Parent();
   }
   // ������
   if(NULL == _pJumpCatcher){
      MO_FATAL(TC("Not any catcher catch this code. (code=%d)"), code);
   }
   _pActiveCatcher = _pJumpCatcher;
   // ���ٲ�׽��
   Track(_pJumpCatcher, code);
   // ��ʼ��ת
   _lockerJump.Enter();
   _pJumpCatcher->Jump();
   return ETrue;
}

//============================================================
// <T>��ת��������</T>
//
// @return ������
//============================================================
TBool FThreadCatcher::JumpFinish(FCatcher* pCatcher){
   MO_ASSERT(pCatcher);
   // ����Ƿ���ڼ���
   if(NULL == _pJumpCatcher){
      MO_ERROR(TC("Catcher long jump failure, lost jump captcher. (jump_catcher=0x%08X, catcher=0x%08X)"), _pJumpCatcher, pCatcher);
      return EFalse;
   }
   // �����ת��
   if(_pJumpCatcher != pCatcher){
      MO_ERROR(TC("Catcher long jump failure, jump and active not same. (jump_catcher=%s@0x%08X, catcher=%s@0x%08X)"),
            _pJumpCatcher->Name(), _pJumpCatcher, pCatcher->Name(), pCatcher);
   }
   // ���ñ�־
   MO_WARN(TC("Trap catcher long jump success. (catcher=%s@0x%08X, jumping=%d, valid=%d)"),
         _pJumpCatcher->Name(), _pJumpCatcher, _pJumpCatcher->IsJumping(), _pJumpCatcher->IsValid());
   MO_CLEAR(_pJumpCatcher);
   // ��ת���
   _lockerJump.Leave();
   return ETrue;
}

MO_NAMESPACE_END
