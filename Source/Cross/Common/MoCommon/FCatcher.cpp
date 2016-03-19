#include "MoCmSystem.h"
#include "MoCmThread.h"

#define MO_CM_CATCHER_INFO TC("None")

MO_NAMESPACE_BEGIN

//============================================================
// <T>���첶׽����</T>
//============================================================
FCatcher::FCatcher(){
   _name = TC("Unknown");
   _pInfo = MO_CM_CATCHER_INFO;
   MO_CLEAR(_pParent);
   _installed = EFalse;
   _recorded = EFalse;
   _valid = ETrue;
   _jumping = EFalse;
   _jumpCount = 0;
#ifdef _MO_LINUX
   memset(&_jmpbuf, 0, sizeof(jmp_buf));
#endif // _LINUX
   RBools::Clear(_actions, MO_TRAP_ACTION_MAXCNT);
}

//============================================================
// <T>������׽����</T>
//============================================================
FCatcher::~FCatcher(){
}

//============================================================
// <T>�Ƿ�ע���˴��롣</T>
//
// @param code ����
//============================================================
TBool FCatcher::IsRegistered(TInt code){
   MO_ASSERT_RANGE(code, 0, MO_TRAP_ACTION_MAXCNT);
   return _actions[code];
}

//============================================================
// <T>ע����롣</T>
//
// @param code ����
//============================================================
TBool FCatcher::Register(TInt code){
   MO_ASSERT_RANGE(code, 0, MO_TRAP_ACTION_MAXCNT);
   TBool result = EFalse;
   if(_actions[code] == EFalse){
      _actions[code] = ETrue;
      // �������а�װ��׽��
      if(!RCatcherManager::Instance().IsRegistered(code)){
         result = RCatcherManager::Instance().Register(code);
      }else{
         result = ETrue;
      }
   }
   return result;
}

//============================================================
// <T>ע�����롣</T>
//
// @param code ����
//============================================================
TBool FCatcher::Unregister(TInt code){
   MO_ASSERT_RANGE(code, 0, MO_TRAP_ACTION_MAXCNT);
   TBool result = EFalse;
   if(_actions[code] == ETrue){
      _actions[code] = EFalse;
      // ��������ж�ز�׽��
      if(RCatcherManager::Instance().IsRegistered(code)){
         result = RCatcherManager::Instance().Unregister(code);
      }else{
         result = ETrue;
      }
   }
   return result;
}

//============================================================
// <T>��װ����</T>
//============================================================
TBool FCatcher::Install(){
   return ETrue;
}

//============================================================
// <T>ж�ش���</T>
//============================================================
TBool FCatcher::Uninstall(){
   return ETrue;
}

//============================================================
// <T>���벶׽��Χ����</T>
//
// @return ������
//============================================================
TBool FCatcher::Enter(){
   // ���ñ�־
   _valid = ETrue;
   _recorded = EFalse;
   _jumping = EFalse;
   // ���봦��
   TBool result = RCatcherManager::Instance().Enter(this);
   return result;
}

//============================================================
// <T>�뿪��׽��Χ����</T>
//
// @return ������
//============================================================
TBool FCatcher::Leave(){
   // �뿪����
   TBool result = RCatcherManager::Instance().Leave(this);
   // ���ñ�־
   _valid = EFalse;
   _recorded = EFalse;
   _jumping = EFalse;
   return result;
}

//============================================================
// <T>��¼��ǰ������Ϣ��</T>
//
// @return �Ƿ��ִ��
//============================================================
TBool FCatcher::Record(){
   TBool valid = ETrue;
#ifdef _MO_LINUX
   // �洢������Ϣ
   TInt result = sigsetjmp(_jmpbuf, 1);
   if(0 == result){
      // ��װ��ת��
      if(_jumping){
         valid = EFalse;
         MO_ERROR("Already in jumping, install captcher failure. (catcher=%s@0x%08X, jumping=%d, result=%d)",
               (TCharC*)_name, this, _jumping, result);
      }else{
         _recorded = ETrue;
      }
   }else{
      // �������ط���ת�� (thisָ�벻�����Լ�)
      RCatcherManager::Instance().JumpFinish(this);
      valid = EFalse;
   }
#endif // _LINUX
   return valid;
}

//============================================================
// <T>��¼��ǰ������Ϣ��</T>
//
// @return �Ƿ��ִ��
//============================================================
TBool FCatcher::Recorded(){
   _recorded = ETrue;
   return ETrue;
}

//============================================================
// <T>��ת����¼������Ϣ��</T>
//============================================================
TBool FCatcher::Jump(){
   // ����Ƿ��¼
   if(!_recorded){
      MO_WARN(TC("Trap catcher is not record. (catcher=%s@0x%08X, valid=%d, record=%d, info=%s)"),
            (TCharC*)_name, this, _valid, _recorded, _pInfo);
      return EFalse;
   }
   // ���ñ�־
   _jumping = ETrue;
   _valid = EFalse;
   MO_WARN(TC("Trap catcher long jump start. (catcher=%s@0x%08X, valid=%d, jumping=%d, info=%s)"),
         (TCharC*)_name, this, _valid, _jumping, _pInfo);
#ifdef _MO_LINUX
   // ��ת����
   siglongjmp(_jmpbuf, 1);
#endif // _LINUX
   return ETrue;
}

//============================================================
// <T>��������</T>
//============================================================
TBool FCatcher::JumpFinish(){
   // ����Ƿ�������׽
   if(!_jumping){
      MO_ERROR(TC("Catcher long jump failure, unknown active jumper. (catcher=%s@0x%08X, jumping=%d, valid=%d)"),
            (TCharC*)_name, this, _jumping, _valid);
      return EFalse;
   }
   // ���ñ�־
   _jumping = EFalse;
   _jumpCount++;
   // ��ת���
   return RCatcherManager::Instance().JumpFinish(this);
}

MO_NAMESPACE_END
