#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����߳��������</T>
//============================================================
FThreadTrap::FThreadTrap(TInt threadId){
   _threadId = threadId;
   MO_CLEAR(_pUsed);
   MO_CLEAR(_pUnused);
}

//============================================================
// <T>�ͷ��߳��������</T>
//============================================================
FThreadTrap::~FThreadTrap(){
   // ɾ��������ʹ�õ��������
   while(NULL != _pUsed){
      FTrap* pUsed = _pUsed;
      _pUsed = _pUsed->Parent();
      delete pUsed;
   }
   // ɾ������δʹ�õ��������
   while(NULL != _pUnused){
      FTrap* pUsed = _pUnused;
      _pUnused = _pUnused->Parent();
      delete pUsed;
   }
}

//============================================================
// <T>����̱߳�ʶ��</T>
//
// @return �̱߳�ʶ
//============================================================
TInt FThreadTrap::ThreadId(){
   return _threadId;
}

//============================================================
// <T>�Ƿ�Ϊ�ա�</T>
//
// @return �Ƿ�Ϊ��
//============================================================
TBool FThreadTrap::IsEmpty(){
   return (NULL == _pUsed);
}

//============================================================
// <T>��õ�ǰ�������</T>
//
// @return ��ǰ�������
//============================================================
FTrap* FThreadTrap::CurrentTrap(){
   return _pUsed;
}

//============================================================
// <T>ѹ���������</T>
//============================================================
void FThreadTrap::Push(){
   // ���һ�����õ�ʵ��
   FTrap* pTrap = NULL;
   if(NULL == _pUnused){
      pTrap = new FTrap();
   }else{
      pTrap = _pUnused;
      _pUnused = pTrap->Parent();
   }
   // ѹ��ʹ���еĶ���
   pTrap->SetParent(_pUsed);
   _pUsed = pTrap;
}

//============================================================
// <T>�����������</T>
//============================================================
void FThreadTrap::Pop(){
   MO_ASSERT(_pUsed);
   // ��õ�ǰʹ�õ�ʵ��
   FTrap* pTrap = _pUsed;
   _pUsed = pTrap->Parent();
   // ѹ��δʹ�õĶ���
   pTrap->SetParent(_pUnused);
   _pUnused = pTrap;
}

MO_NAMESPACE_END
