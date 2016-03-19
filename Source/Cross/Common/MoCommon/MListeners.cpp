#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������������ϡ�</T>
//============================================================
MListeners::MListeners(){
   MO_CLEAR(_pListeners);
}

//============================================================
// <T>�������������ϡ�</T>
//============================================================
MListeners::~MListeners(){
   Clear();
   MO_DELETE(_pListeners);
}

//============================================================
// <T>����һ����������</T>
//
// @param pListener ������
//============================================================
void MListeners::Push(IListener* pListener){
   if(_pListeners == NULL){
      _pListeners = MO_CREATE(FListenerList);
   }
   _pListeners->Push(pListener);
}

//============================================================
// <T>�Ƴ�һ����������</T>
//
// @param pListener ������
//============================================================
void MListeners::Remove(IListener* pListener){
   // ������
   if(pListener == NULL){
      MO_ERROR(TC("Remove listener is null. (listener=0x%08X)"), pListener);
      return;
   }
   // �Ƴ�������
   if(_pListeners != NULL){
      if(_pListeners->Contains(pListener)){
         _pListeners->Remove(pListener);
      }else{
         MO_ERROR(TC("Remove listener is not exists. (listener=0x%08X)"), pListener);
      }
   }
   // ɾ��������
   if(pListener->ManageCd() == EListenerManage_Auto){
      MO_DELETE(pListener);
   }
}

//============================================================
// <T>���ô���</T>
//
// @param pParameters ��������
// @return ������
//============================================================
TBool MListeners::Process(TAny* pParameters){
   TBool result = ETrue;
   if(_pListeners != NULL){
      TListIteratorC<IListener*> iterator = _pListeners->IteratorC();
      while(iterator.Next()){
         if(!iterator->Process(pParameters)){
            result = EFalse;
         }
      }
   }
   return result;
}

//============================================================
// <T>��ռ��������ϡ�</T>
//============================================================
void MListeners::Clear(){
   if(_pListeners == NULL){
      return;
   }
   TListIteratorC<IListener*> iterator = _pListeners->IteratorC();
   while(iterator.Next()){
      IListener* pListener = *iterator;
      if(pListener->ManageCd() == EListenerManage_Auto){
         MO_DELETE(pListener);
      }
   }
   _pListeners->Clear();
}

MO_NAMESPACE_END
