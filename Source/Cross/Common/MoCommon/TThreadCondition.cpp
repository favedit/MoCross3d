#include "MoCmLock.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����߳��¼���</T>
//============================================================
TThreadCondition::TThreadCondition(){
#ifdef _MO_WINDOWS
#else
   // ������
   TInt result = pthread_mutex_init(&_mutex, NULL);
   if(ESuccess != result){
      // EBUSY����ʵ���Ѽ�⵽ϵͳ�������³�ʼ�� mp �����õĶ��󣬼���ǰ���й���ʼ���� ��δ���ٵĻ�������
      // EINVAL��mattr ����ֵ��Ч����������δ�޸ġ�
      // EFAULT��mp ��ָ��Ļ������ĵ�ַ��Ч��
      MO_PFATAL(pthread_mutex_init);
   }
   // ��������
   result = pthread_cond_init(&_condition, NULL);
   if(ESuccess != result){
      // EINVAL��cattr ָ����ֵ��Ч��
      // EBUSY��������������ʹ��״̬��
      // EAGAIN����Ҫ����Դ�����á�
      // ENOMEM���ڴ治�㣬�޷���ʼ������������
      MO_PFATAL(pthread_cond_init);
   }
#endif // _MO_WINDOWS
}

//============================================================
// <T>�ͷ��߳��¼���</T>
//============================================================
TThreadCondition::~TThreadCondition(){
#ifdef _MO_WINDOWS
#else
   TInt result = pthread_cond_destroy(&_condition);
   if(ESuccess != result){
      // EINVAL��cv ָ����ֵ��Ч��
      MO_PFATAL(pthread_cond_destroy);
   }
#endif // _MO_WINDOWS
}

//============================================================
// <T>������</T>
//============================================================
void TThreadCondition::Lock(){
#ifdef _MO_WINDOWS
#else
   TInt result = pthread_mutex_lock(&_mutex);
   if(ESuccess != result){
      MO_PFATAL(pthread_mutex_lock);
   }
#endif // _MO_WINDOWS
}

//============================================================
// <T>������</T>
//============================================================
void TThreadCondition::Unlock(){
#ifdef _MO_WINDOWS
#else
   TInt result = pthread_mutex_unlock(&_mutex);
   if(ESuccess != result){
      MO_PFATAL(pthread_mutex_unlock);
   }
#endif // _MO_WINDOWS
}

//============================================================
// <T>�ȴ�������</T>
//============================================================
void TThreadCondition::Wait(){
#ifdef _MO_WINDOWS
#else
   TInt result = pthread_cond_wait(&_condition, &_mutex);
   if(ESuccess != result){
      // EINVAL��cv �� mp ָ����ֵ��Ч��
      MO_PFATAL(pthread_cond_wait);
   }
#endif // _MO_WINDOWS
}

//============================================================
// <T>�ȴ�������</T>
//============================================================
void TThreadCondition::Wait(TInt msecond){
#ifdef _MO_WINDOWS
#else
   time_t now = time(NULL);
   timespec abstime;
   abstime.tv_nsec = now + (msecond/1000);
   abstime.tv_nsec = (msecond % 1000) * 1000 * 1000;
   TInt result = pthread_cond_timedwait(&_condition, &_mutex, &abstime);
   if(ESuccess != result){
      // EINVAL��cv �� abstime ָ��ĵ�ַ�Ƿ���
      // ETIMEDOUT��abstime ָ����ʱ���ѹ���
      MO_PFATAL(pthread_cond_timedwait);
   }
#endif // _MO_WINDOWS
}

//============================================================
// <T>���ͽ����źš�</T>
//============================================================
void TThreadCondition::Signal(){
#ifdef _MO_WINDOWS
#else
   TInt result = pthread_cond_signal(&_condition);
   if(ESuccess != result){
      // EINVAL��cv ָ��ĵ�ַ�Ƿ���
      MO_PFATAL(pthread_cond_signal);
   }
#endif // _MO_WINDOWS
}

//============================================================
// <T>֪ͨ�������</T>
//============================================================
void TThreadCondition::Notify(){
   // ����
   Lock();
   // ����
   Signal();
   // �������
   Unlock();
}

//============================================================
// <T>�㲥�����������</T>
//============================================================
void TThreadCondition::Broadcast(){
#ifdef _MO_WINDOWS
#else
   TInt result = pthread_cond_broadcast(&_condition);
   if(ESuccess != result){
      // EINVAL��cv ָʾ�ĵ�ַ�Ƿ���
      MO_PFATAL(pthread_cond_broadcast);
   }
#endif // _MO_WINDOWS
}

MO_NAMESPACE_END
