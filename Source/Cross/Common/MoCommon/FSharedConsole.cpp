#include "MoCmShared.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲���������</T>
//============================================================
FSharedConsole::FSharedConsole(){
   _pShareds = MO_CREATE(FSharedSet);
   _pGroups = MO_CREATE(FSharedGroupList);
}

//============================================================
// <T>���������������</T>
//============================================================
FSharedConsole::~FSharedConsole(){
   MO_DELETE(_pShareds);
   MO_DELETE(_pGroups);
}

//============================================================
TSize FSharedConsole::SharedCapacity(){
   TListIteratorC<ISingleton*> iterator = RSingletonManager::Instance().Singletons()->IteratorC();
   TSize total = 0;
   while(iterator.Next()){
      /*if(ESingleton_Shared == iterator->SingletonType()){
         // ��ù������
         IShared* pShared = (IShared*)iterator.Get();
         TSize capacity = pShared->SharedCapacity()
         if(capacity > 0){
            MO_DEBUG("Calculate [%s] shared capacity. (capacity=%d)", pShared->Name(), capacity);
              total += pShared->SharedCapacity();
         }
      }*/
   }
   return total;
}

//============================================================
void FSharedConsole::SharedLink(TShareSegment segment){
   TListIteratorC<ISingleton*> iterator = RSingletonManager::Instance().Singletons()->IteratorC();
   while(iterator.Next()){
      /*if(ESingleton_Shared == iterator->SingletonType()){
         // ��ù������
         IShared* pShared = (IShared*)iterator.Get();
         TSize capacity = pShared->SharedCapacity();
         if(capacity > 0){
            pShared->SharedLink(segment.CreateSegment(capacity));
         }
      }*/
   }
}

//============================================================
MShared* FSharedConsole::Get(TInt code){
   return _pShareds->Get(code);
}

//============================================================
MShared* FSharedConsole::Find(TInt code){
   return _pShareds->Find(code);
}

//============================================================
void FSharedConsole::Register(MShared* pShared){
   //_pShareds->Set(pShared->Code(), pShared);
}

//============================================================
void FSharedConsole::Unregister(MShared* pShared){
   //_pShareds->Remove(pShared->Code());
}

//============================================================
// <T>�����������ҹ��������顣</T>
//
// @param key ����
// @param pKeyName ��������
// @return ������
//============================================================
FSharedGroup* FSharedConsole::FindGroup(TShareKey key, TCharC* pKeyName){
   TListIteratorC<FSharedGroup*> iterator = _pGroups->IteratorC();
   while(iterator.Next()){
      FSharedGroup* pGroup = *iterator;
      if((pGroup->Key() == key) && RString::Equals(pGroup->KeyName(), pKeyName)){
         return pGroup;
      }
   }
   return NULL;
}

//============================================================
// <T>���������顣</T>
//
// @param key ����
// @param pKeyName ��������
// @return ������
//============================================================
FSharedGroup* FSharedConsole::LinkGroup(TShareKey key, TCharC* pKeyName){
   // ���ҹ�����
   FSharedGroup* pGroup = FindGroup(key, pKeyName);
   // ����������
   if(NULL == pGroup){
      pGroup = MO_CREATE(FSharedGroup);
      pGroup->SetKey(key);
      pGroup->SetKeyName(pKeyName);
      _pGroups->Push(pGroup);
   }
   return pGroup;
}

MO_NAMESPACE_END
