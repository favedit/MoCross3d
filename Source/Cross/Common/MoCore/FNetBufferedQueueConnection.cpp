#include "MoCrNetPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ӷ��󣬲���Ҫ������</T>
// <P>�Ժ�ʹ��ǰ��Ҫ������������ܵ���С��</P>
//
// @return ��ǰʵ��ָ��
//============================================================
FNetBufferedQueueConnection::FNetBufferedQueueConnection(){
   _pInputQueue = MO_CREATE(FNetBufferedQueue);
   _pOutputQueue = MO_CREATE(FNetBufferedQueue);
}

//============================================================
// <T>�������Ӷ���</T>
//============================================================
FNetBufferedQueueConnection::~FNetBufferedQueueConnection(){
   MO_DELETE(_pInputQueue);
   MO_DELETE(_pOutputQueue);
}

//============================================================
// <T>���ô���</T>
//
// @param capacity ����
// @param pAllocator �ռ���
//============================================================
void FNetBufferedQueueConnection::Setup(TInt capacity, FBufferedQueueBlockAllocator* pAllocator){
   MO_ASSERT(capacity > 0);
   // ����������
   _pInputQueue->SetLockCd(EStreamLock_Lock);
   _pInputQueue->Pool()->SetCapacity(capacity);
   _pInputQueue->SetAllocator(pAllocator);
   // ���������
   _pOutputQueue->SetLockCd(EStreamLock_Lock);
   _pOutputQueue->Pool()->SetCapacity(capacity);
   _pOutputQueue->SetAllocator(pAllocator);
}

//============================================================
// <T>��ʾ����ʱ��Ϣ��</T>
//
// @param capacity ����
// @param pAllocator �ռ���
//============================================================
void FNetBufferedQueueConnection::Dump(){
   // �������ܵ���Ϣ
   SQueueInfo inputInfo;
   _pInputQueue->FetchInfo(&inputInfo);
   MO_INFO(TC("Dump input queue info.  (length=%8d:%8d, push=%8lld:%24s, pop=%8lld:%24s)"),
         inputInfo.count, inputInfo.length,
         inputInfo.countPush, RInt::FormatCapacity(inputInfo.lengthPush, TFsCode(), TFsCode::Size()),
         inputInfo.countPop, RInt::FormatCapacity(inputInfo.lengthPop, TFsCode(), TFsCode::Size()));
   // �������ܵ���Ϣ
   SQueueInfo outputInfo;
   _pOutputQueue->FetchInfo(&outputInfo);
   MO_INFO(TC("Dump output queue info. (length=%8d:%8d, push=%8lld:%24s, pop=%8lld:%24s)"),
         outputInfo.count, outputInfo.length,
         outputInfo.countPush, RInt::FormatCapacity(outputInfo.lengthPush, TFsCode(), TFsCode::Size()),
         outputInfo.countPop, RInt::FormatCapacity(outputInfo.lengthPop, TFsCode(), TFsCode::Size()));
}

MO_NAMESPACE_END
