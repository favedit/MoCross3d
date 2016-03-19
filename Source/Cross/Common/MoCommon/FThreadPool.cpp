#include "MoCmThread.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����̻߳���ء�</T>
//
// @return �̻߳����
//============================================================
FThreadPool::FThreadPool(){
   _pInitializeWorkers = MO_CREATE(FThreadWorkerList);
   _pBusyWorkers = MO_CREATE(FThreadWorkerList);
   _pFreeWorkers = MO_CREATE(FThreadWorkerList);
   _busyTotal = 0;
   _waitTotal = 0;
   _refreshInterval = 10000000; // 10��ˢ��
   _refreshDate = 0;
   _refreshTotal = 0;
}

//============================================================
// <T>�����̻߳���ء�</T>
//============================================================
FThreadPool::~FThreadPool(){
   MO_PTR_DELETE(_pInitializeWorkers);
   MO_PTR_DELETE(_pBusyWorkers);
   MO_PTR_DELETE(_pFreeWorkers);
}

//============================================================
// <T>��ó�ʼ��������</T>
//
// @return ��ʼ������
//============================================================
TInt FThreadPool::InitializeCount(){
   TInt count = 0;
   _lockerInitialize.Enter();
   count = _pInitializeWorkers->Count();
   _lockerInitialize.Leave();
   return count;
}

//============================================================
// <T>��ù���������</T>
//
// @return ��������
//============================================================
TInt FThreadPool::BusyCount(){
   TInt count = 0;
   _lockerBusy.Enter();
   count = _pBusyWorkers->Count();
   _lockerBusy.Leave();
   return count;
}

//============================================================
// <T>������ɸ�����</T>
//
// @return ���ɸ���
//============================================================
TInt FThreadPool::FreeCount(){
   TInt count = 0;
   _lockerFree.Enter();
   count = _pFreeWorkers->Count();
   _lockerFree.Leave();
   return count;
}

//============================================================
// <T>ע��һ���̹߳�������</T>
//
// @param pWorker �̹߳�����
//============================================================
void FThreadPool::Register(FThreadWorker* pWorker){
   pWorker->SetPool(this);
   pWorker->Start();
}

//============================================================
// <T>�ռ�һ�����ɵ��̹߳�������</T>
//
// @return �̹߳�����
//============================================================
FThreadWorker* FThreadPool::AllocFree(){
   FThreadWorker* pWorker = NULL;
   _lockerFree.Enter();
   if(!_pFreeWorkers->IsEmpty()){
      pWorker = _pFreeWorkers->Shift();
   }
   _lockerFree.Leave();
   return pWorker;
}

//============================================================
// <T>��ʼ������</T>
//
// @param pWorker �̹߳�����
// @return ������
//============================================================
TBool FThreadPool::DoInitialize(FThreadWorker* pWorker){
   _lockerInitialize.Enter();
   _pInitializeWorkers->Push(pWorker);
   _lockerInitialize.Leave();
   return ETrue;
}

//============================================================
// <T>�����̹߳�������</T>
//
// @param pWorker �̹߳�����
// @return ������
//============================================================
TBool FThreadPool::DoBusy(FThreadWorker* pWorker){
   pWorker->SetBusy(ETrue);
   // ���������Ƴ�
   _lockerFree.Enter();
   _pFreeWorkers->Remove(pWorker);
   _lockerFree.Leave();
   // ���빤���߳�
   _lockerBusy.Enter();
   if(!_pBusyWorkers->Contains(pWorker)){
      _pBusyWorkers->Push(pWorker);
   }
   _lockerBusy.Leave();
   // ��ʼ����
   _busyTotal++;
   pWorker->Resume();
   return ETrue;
}

//============================================================
// <T>�����̹߳�������</T>
//
// @param pWorker �̹߳�����
// @return ������
//============================================================
TBool FThreadPool::DoWait(FThreadWorker* pWorker){
   pWorker->SetBusy(EFalse);
   // �ӹ������Ƴ�
   _lockerBusy.Enter();
   _pBusyWorkers->Remove(pWorker);
   _lockerBusy.Leave();
   // ���������߳�
   _lockerFree.Enter();
   if(!_pFreeWorkers->Contains(pWorker)){
      _pFreeWorkers->Push(pWorker);
   }
   _lockerFree.Leave();
   // �ӳ�ʼ�����Ƴ�
   _lockerInitialize.Enter();
   if(_pInitializeWorkers->Contains(pWorker)){
      _pInitializeWorkers->Remove(pWorker);
   }else{
      _waitTotal++;
   }
   _lockerInitialize.Leave();
   // ��ʼ�ȴ�
   pWorker->Suspend();
   return ETrue;
}

//============================================================
// <T>ˢ�´���</T>
//============================================================
TBool FThreadPool::Refresh(){
   TDateTime current = RDateTime::Current();
   TTimeSpan span = current - _refreshDate;
   if(span > _refreshInterval){
      // ���ճ�ʱ�߳�
      _lockerFree.Enter();
      TListIteratorC<FThreadWorker*> iterator = _pFreeWorkers->IteratorC();
      while(iterator.Next()){
         FThreadWorker* pWorker = *iterator;
         // ֹͣ��ʱ���߳�
         if(pWorker->TestTimeout(current)){
            _pFreeWorkers->Remove(pWorker);
            pWorker->Stop();
            break;
         }
      }
      _lockerFree.Leave();
      // ˢ�´���
      _refreshDate = current;
      _refreshTotal++;
   }
   return ETrue;
}

//============================================================
// <T>������Ϣ��</T>
//
// @param pTrack �ַ���
// @return ִ�н��
//============================================================
TBool FThreadPool::Track(MString* pTrack){
   pTrack->AppendFormat(TC("Thread pool. (initialize=%d, busy=%d, free=%d)"),
         _pInitializeWorkers->Count(), _pBusyWorkers->Count(), _pFreeWorkers->Count());
   return ETrue;
}

MO_NAMESPACE_END
