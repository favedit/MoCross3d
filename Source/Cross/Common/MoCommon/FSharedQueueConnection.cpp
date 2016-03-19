#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ӷ��󣬲���Ҫ������</T>
// <P>�Ժ�ʹ��ǰ��Ҫ������������ܵ���С��</P>
//
// @return ��ǰʵ��ָ��
//============================================================
FSharedQueueConnection::FSharedQueueConnection(){
   _pInputQueue = MO_CREATE(FSharedQueue);
   _pOutputQueue = MO_CREATE(FSharedQueue);
}

//============================================================
// <T>�������Ӷ���</T>
//
// @param inputCapacity ����ܵ�������
// @param outputCapacity ����ܵ�������
// @return ��ǰʵ��ָ��
//============================================================
FSharedQueueConnection::FSharedQueueConnection(TSize inputCapacity, TSize outputCapacity){
   _pInputQueue = MO_CREATE(FSharedQueue, inputCapacity);
   _pOutputQueue = MO_CREATE(FSharedQueue, outputCapacity);
}

//============================================================
// <T>�������Ӷ���</T>
//============================================================
FSharedQueueConnection::~FSharedQueueConnection(){
   MO_DELETE(_pInputQueue);
   MO_DELETE(_pOutputQueue);
}

//============================================================
// <T>ָ����д�ܵ��ĳ��ȡ�</T>
//
// @param capacity ������еĳ���
//============================================================
void FSharedQueueConnection::SetInputCapacity(TSize capacity){
   _pInputQueue->SetCapacity(capacity);
}

//============================================================
// <T>ָ����д�ܵ��ĳ��ȡ�</T>
//
// @param capacity ������еĳ���
//============================================================
void FSharedQueueConnection::SetOutputCapacity(TSize capacity){
   _pOutputQueue->SetCapacity(capacity);
}

//============================================================
// <T>�������ڴ�η��ɸ����ӡ�</T>
//
// @param segment �����ڴ�εĶ���
//============================================================
void FSharedQueueConnection::OnSharedLink(TShareSegment& segment){
   segment.SharedLink(_pInputQueue);
   segment.SharedLink(_pOutputQueue);
}

//============================================================
// <T>�����������Ĺ����ڴ��С��</T>
//
// @return ��������Ĺ����ڴ��С��
//============================================================
TSize FSharedQueueConnection::SharedCapacity(){
   TSize intputSize = _pInputQueue->SharedCapacity();
   TSize outputSize = _pOutputQueue->SharedCapacity();
   TSize capacity = intputSize + outputSize;
   return capacity;
}

//============================================================
// <T>����ն��е�ָ�롣</T>
//
// @return �ն��е�ָ�롣
//============================================================
FSharedQueue* FSharedQueueConnection::InputQueue(){
   return _pInputQueue;
}

//============================================================
// <T>���д���е�ָ�롣</T>
//
// @return д���е�ָ�롣
//============================================================
FSharedQueue* FSharedQueueConnection::OutputQueue(){
   return _pOutputQueue;
}

MO_NAMESPACE_END
