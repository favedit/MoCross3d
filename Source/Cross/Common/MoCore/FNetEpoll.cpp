#include "MoCrNetEpoll.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����EPOLL�˿ڳء�</T>
//
// @return EPOLL�˿ڳ�
//============================================================
FNetEpoll::FNetEpoll(){
   _processSize = 0;
   _timeout = 0;
   _handle = 0;
   _count = 0;
#ifdef _MO_LINUX
#ifndef __CYGWIN__
   MO_CLEAR(_pEvents);
#endif
#endif
}

//============================================================
// <T>����EPOLL�˿ڳء�</T>
//============================================================
FNetEpoll::~FNetEpoll(){
}

//============================================================
// <T>��þ����</T>
//
// @return ���
//============================================================
TInt FNetEpoll::Handle(){
   return _handle;
}

//============================================================
// <T>��ø�����</T>
//
// @return ����
//============================================================
TInt FNetEpoll::Count(){
   return _count;
}

//============================================================
// <T>���������������á�</T>
//
// @param pSocket ����˿�
// @param flag ��־
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetEpoll::Add(INetSocket* pSocket, TUint flag){
   // ��þ��
   MO_ASSERT(pSocket);
#ifdef _MO_LINUX
#ifndef __CYGWIN__
   TSocket handle = pSocket->Handle();
   // �����¼�
   epoll_event event;
   RType<epoll_event>::Clear(&event);
   event.events = flag;
   event.data.ptr = pSocket;
   // �����¼�
   TInt result = epoll_ctl(_handle, EPOLL_CTL_ADD, handle, &event);
   if(result < 0){
      MO_ERROR("Epoll add socket error. (epoll=%d, socket=0x%08X, handle=%d)",
            _handle, pSocket, pSocket->Handle());
      MO_PFATAL(epoll_ctl);
      return EFalse;
   }
#endif
#endif
   _count++;
   return ETrue;
}

//============================================================
// <T>�޸������������á�</T>
//
// @param pSocket ����˿�
// @param flag ��־
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetEpoll::Modify(INetSocket* pSocket, TUint flag){
#ifdef _MO_LINUX
   // ��þ��
   MO_ASSERT(pSocket);
   // �����¼�
#ifndef __CYGWIN__
   TSocket handle = pSocket->Handle();
   epoll_event event;
   RType<epoll_event>::Clear(&event);
   event.events = flag;
   event.data.ptr = pSocket;
   // �޸��¼�
   TInt result = epoll_ctl(_handle, EPOLL_CTL_MOD, handle, &event);
   if(result < 0){
      MO_ERROR("Epoll modify socket error. (epoll=%d, socket=0x%08X, handle=%d)",
            _handle, pSocket, pSocket->Handle());
      MO_PFATAL(epoll_ctl);
      return EFalse;
   }
#endif
#endif
   return ETrue;
}

//============================================================
// <T>ɾ�������������á�</T>
//
// @param pSocket ����˿�
// @param flag ��־
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetEpoll::Remove(INetSocket* pSocket, TUint flag){
#ifdef _MO_LINUX
   // ��þ��
   MO_ASSERT(pSocket);
   // �����¼�
#ifndef __CYGWIN__
   TSocket handle = pSocket->Handle();
   epoll_event event;
   RType<epoll_event>::Clear(&event);
   event.events = flag;
   event.data.ptr = pSocket;
   // ɾ���¼�
   TInt result = epoll_ctl(_handle, EPOLL_CTL_DEL, handle, &event);
   if(result < 0){
      MO_ERROR("Epoll remove socket error. (epoll=%d, socket=0x%08X, handle=%d)",
            _handle, pSocket, pSocket->Handle());
      MO_PFATAL(epoll_ctl);
      return EFalse;
   }
#endif
#endif
   _count--;
   return ETrue;
}

//============================================================
// <T>������ɶ˿ڡ�</T>
//
// @param size �����С
// @return
//    <L value='ETrue'>�ɹ�</L>
//    <L value='EFalse'>ʧ��</L>
//============================================================
TBool FNetEpoll::Create(TInt size){
#ifdef _MO_LINUX
   _processSize = size;
#ifndef __CYGWIN__
   _handle = epoll_create(size);
   if(EError == _handle){
      MO_PERROR(epoll_create);
      return EFalse;
   }
#endif
#endif
   return ETrue;
}

MO_NAMESPACE_END
