#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
TThreadLocker RActivator::_locker;

//============================================================
// <T>��ʼ����Դ��</T>
//============================================================
void RActivator::Initialize(){
}

//============================================================
// <T>�ͷ���Դ��</T>
//============================================================
void RActivator::Release(){
}

//============================================================
// <T>����һ�������ʵ����</T>
//
// @param pClassName ������
// @param size �����С
// @param pFileName �����ļ�
// @param line ��������
// @return ����ʵ��ָ��
//============================================================
TAny* RActivator::Create(TChar8C* pClassName, TInt size, TChar8C* pFileName, TInt line){
   // ��õ�ǰ�̵߳�����ӿ�
   //FThreadTrap* pThreadTrap = RThread::Static().Console()->Current()->ThreadTrap();
   //FTrap* pTrap = pThreadTrap->CurrentTrap();
   // �ռ�ָ����С���ڴ�
   //return pTrap->Alloc(pClassName, size, pFileName, line);
   return NULL;
}

//============================================================
// <T>�Ƴ�һ�������ʵ����</T>
//
// @param pObject ����ʵ��ָ��
//============================================================
void RActivator::Remove(TAny* pObject){
   // ��õ�ǰ�̵߳�����ӿ�
   //FThreadTrap* pThreadTrap = RThread::Static().Console()->Current()->ThreadTrap();
   //FTrap* pTrap = pThreadTrap->CurrentTrap();
   // �ͷ�ָ����С���ڴ�
   //pTrap->Remove(pObject);
}

//============================================================
// <T>ɾ��һ�������ʵ����</T>
//
// @param pObject ����ʵ��ָ��
//============================================================
void RActivator::Destroy(TAny* pObject){
   // ��õ�ǰ�̵߳�����ӿ�
   //FTrap* pTrap = RTrap::Static().CurrentTrap();
   // �ͷ�ָ����С���ڴ�
   //pTrap->Free(pObject);
}

//============================================================
// <T>��Դ������</T>
//============================================================
void RActivator::Lock(){
   _locker.Enter();
}

//============================================================
// <T>��Դ������</T>
//============================================================
void RActivator::Unlock(){
   _locker.Leave();
}

MO_NAMESPACE_END
