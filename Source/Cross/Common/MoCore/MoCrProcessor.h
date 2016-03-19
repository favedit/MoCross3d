#ifndef __MO_CR_PROCESSOR_H__
#define __MO_CR_PROCESSOR_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������ġ�</T>
//============================================================
class SProcessContext{
public:
   TTimeTick currentTick;
   FInstance* senderPtr;
public:
   //------------------------------------------------------------
   // <T>���촦�������ġ�</T>
   SProcessContext(){
      currentTick = 0;
      MO_CLEAR(senderPtr);
   }
};

MO_NAMESPACE_END

#endif // __MO_CR_PROCESSOR_H__
