#include "MoCmTask.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTaskInvoker, FTask);

//============================================================
// <T>����������á�</T>
//============================================================
FTaskInvoker::FTaskInvoker(){
   MO_CLEAR(_pTask);
}

//============================================================
// <T>����������á�</T>
//============================================================
FTaskInvoker::~FTaskInvoker(){
}

//============================================================
// <T>ִ�д���</T>
//
// @return ������
//============================================================
TResult FTaskInvoker::Process(){
   MO_CHECK(_pTask, return ENull);
   TResult resultCd = _pTask->TaskProcess();
   return resultCd;
}

MO_NAMESPACE_END
