#include "MoCmLock.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����߳��ٽ�Ρ�</T>
//============================================================
TThreadSection::TThreadSection(){
   _enable = ETrue;
#ifdef _MO_WINDOWS
   InitializeCriticalSection(&_section);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   pthread_spin_init(&_section, PTHREAD_PROCESS_PRIVATE);
#endif // _MO_LINUX
#ifdef _MO_FLASCC
   MO_FATAL_UNSUPPORT();
#endif // _MO_FLASCC
#ifdef _MO_ANDROID
   MO_FATAL_UNSUPPORT();
#endif // _MO_ANDROID
}

//============================================================
// <T>�����߳��ٽ�Ρ�</T>
//============================================================
TThreadSection::~TThreadSection(){
#ifdef _MO_WINDOWS
   DeleteCriticalSection(&_section);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   pthread_spin_destroy(&_section);
#endif // _MO_LINUX
#ifdef _MO_FLASCC
   MO_FATAL_UNSUPPORT();
#endif // _MO_FLASCC
#ifdef _MO_ANDROID
   MO_FATAL_UNSUPPORT();
#endif // _MO_ANDROID
}

//============================================================
// <T>�����ٽ�Ρ�</T>
//============================================================
void TThreadSection::Enter(){
   if(_enable){
#ifdef _MO_WINDOWS
      EnterCriticalSection(&_section);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
      pthread_spin_lock(&_section);
#endif // _MO_LINUX
#ifdef _MO_FLASCC
      MO_FATAL_UNSUPPORT();
#endif // _MO_FLASCC
#ifdef _MO_ANDROID
      MO_FATAL_UNSUPPORT();
#endif // _MO_ANDROID
   }
}

//============================================================
// <T>���Խ����ٽ�Ρ�</T>
//============================================================
TBool TThreadSection::TryEnter(){
   TInt result = EFailure;
   if(_enable){
#ifdef _MO_WINDOWS
      MO_FATAL_UNSUPPORT();
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
      result = pthread_spin_trylock(&_section);
#endif // _MO_LINUX
#ifdef _MO_FLASCC
      MO_FATAL_UNSUPPORT();
#endif // _MO_FLASCC
#ifdef _MO_ANDROID
      MO_FATAL_UNSUPPORT();
#endif // _MO_ANDROID
   }
   return (ESuccess == result);
}

//============================================================
// <T>�뿪�ٽ�Ρ�</T>
//============================================================
void TThreadSection::Leave(){
   if(_enable){
#ifdef _MO_WINDOWS
      LeaveCriticalSection(&_section);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
      pthread_spin_unlock(&_section);
#endif // _MO_LINUX
#ifdef _MO_FLASCC
      MO_FATAL_UNSUPPORT();
#endif // _MO_FLASCC
#ifdef _MO_ANDROID
      MO_FATAL_UNSUPPORT();
#endif // _MO_ANDROID
   }
}

MO_NAMESPACE_END
