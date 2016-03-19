#include "MoCmThread.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����̻߳���ء�</T>
//
// @return �̻߳����
//============================================================
FThreadRunablePool::FThreadRunablePool(){
   //_pUsedWorks = MO_CREATE(FThreadWorkerPoolList);
   //_pUnusedWorks = MO_CREATE(FThreadWorkerPoolList);
   _incrementCapacity = 1;
}

//============================================================
// <T>�����̻߳���ء�</T>
//============================================================
FThreadRunablePool::~FThreadRunablePool(){
   MO_PTR_DELETE(_pUsedWorks);
   MO_PTR_DELETE(_pUnusedWorks);
}

//============================================================
// <T>��ü��������</T>
//
// @return �������
//============================================================
TInt FThreadRunablePool::ActiveCount(){
   TInt count = 0;
   _locker.Enter();
   count = _pUsedWorks->Count();
   _locker.Leave();
   return count;
}

//============================================================
// <T>������߸�����</T>
//
// @return ���߸���
//============================================================
TInt FThreadRunablePool::SleepCount(){
   TInt count = 0;
   _locker.Enter();
   count = _pUnusedWorks->Count();
   _locker.Leave();
   return count;
}

//============================================================
void FThreadRunablePool::NotifyFree(FThreadRunableWorker& worker){
   _locker.Enter();
   _pUsedWorks->Remove(&worker);
   _pUnusedWorks->Push(&worker);
   _locker.Leave();
   MO_DEBUG(TC("Process thread (active=%d, sleep=%d)"), _pUsedWorks->Count(), _pUnusedWorks->Count());
}

//============================================================
//void FThreadPool::NotifyTimeout(FThreadRunableWorker& worker){
//}

//============================================================
// <T>ִ�д���</T>
//
// @param runable ��������
//============================================================
void FThreadRunablePool::Process(TRunableHandle runable){
   //FThreadPoolWorker* pWorker = NULL;
   //_locker.Enter();
   //if(_pUnusedWorks->IsEmpty()){
   //   pWorker = MO_CREATE(FThreadWorker, this);
   //   pWorker->Start();
   //   _pUsedWorks->Push(pWorker);
   //}else{
   //   pWorker = _pUnusedWorks->Shift();
   //}
   //pWorker->SetRunable(runable);
   //_pUsedWorks->Push(pWorker);
   //pWorker->Resume();
   //_locker.Leave();
}

MO_NAMESPACE_END
