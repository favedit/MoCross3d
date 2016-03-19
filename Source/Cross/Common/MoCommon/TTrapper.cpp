#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������׽����</T>
//============================================================
TTrapper::TTrapper(){
   _pThreadTrap = RTrap::Static().Link();
   _pTrap = _pThreadTrap->CurrentTrap();
}

//============================================================
// <T>�ͷ�������׽����</T>
//============================================================
TTrapper::~TTrapper(){
   _pTrap->Check();
   RTrap::Static().Unlink(_pThreadTrap);
}

MO_NAMESPACE_END
