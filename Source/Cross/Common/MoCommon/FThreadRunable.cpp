#include "MoCmThread.h"

MO_NAMESPACE_BEGIN

//============================================================
FThreadRunable::FThreadRunable(){
   MO_CLEAR(_runableHandle);
}

//============================================================
// <T>����������̶߳���</T>
//
// @return �������̶߳���
//============================================================
FThreadRunable::FThreadRunable(TRunableHandle handle){
   _runableHandle = handle;
}

//============================================================
// <T>���ù���������</T>
//
// @param cRunable ��������
//============================================================
void FThreadRunable::SetRunable(TRunableHandle handle){
   _runableHandle = handle;
}

//============================================================
// <T>ִ�д���</T>
//
// @return ������
//============================================================
TResult FThreadRunable::Process(){
   if(NULL != _runableHandle){
      return (*_runableHandle)(this);
   }
   return ESuccess;
}

MO_NAMESPACE_END
