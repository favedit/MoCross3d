#include "MoCmShared.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲���顣</T>
//============================================================
FSharedGroup::FSharedGroup(){
   _key = 0;
   _pShareds = MO_CREATE(FSharedList);
   _pAllocator = NULL;
}

//============================================================
// <T>���������顣</T>
//============================================================
FSharedGroup::~FSharedGroup(){
   MO_DELETE(_pShareds);
   MO_DELETE(_pAllocator);
}

//============================================================
// <T>���㹲���ڴ��С��</T>
//
// @return �ڴ��С
//============================================================
TSize FSharedGroup::SharedCapacity(){
   TListIteratorC<MShared*> iterator = _pShareds->IteratorC();
   TSize total = 0;
   while(iterator.Next()){
      // ��ù������
      TSize capacity = iterator->SharedCapacity();
      if(capacity > 0){
         total += capacity;
      }
      // MO_INFO("Calculate shared capacity. (capacity=%d, total=%d, count=%d)", capacity, total, _pShareds->Count());
   }
   return total;
}

//============================================================
// <T>���㹲���ڴ��С��</T>
//
// @return �ڴ��С
//============================================================
TBool FSharedGroup::SharedLink(TShareSegment segment){
   TListIteratorC<MShared*> iterator = _pShareds->IteratorC();
   while(iterator.Next()){
      // ��ù������
      TSize capacity = iterator->SharedCapacity();
      if(capacity > 0){
         iterator->SharedLink(segment.CreateSegment(capacity));
      }
   }
   return ETrue;
}

//============================================================
// <T>ע�Ṳ��顣</T>
//
// @param pShared �����
//============================================================
void FSharedGroup::Register(MShared* pShared){
   MO_ASSERT(pShared);
   _pShareds->Push(pShared);
}

//============================================================
// <T>ע������顣</T>
//
// @param pShared �����
//============================================================
void FSharedGroup::Unregister(MShared* pShared){
   MO_ASSERT(pShared);
   _pShareds->Remove(pShared);
}

//============================================================
// <T>�����ڴ档</T>
//
// @return ������
//============================================================
TBool FSharedGroup::Create(){
   // ������Ҫ�����ڴ��С
   TSize capacity = SharedCapacity();
   // �ռ������ڴ�
   MO_ASSERT(NULL == _pAllocator);
   FShareMemory* pShareMemory = MO_CREATE(FShareMemory);
   pShareMemory->SetKey(_key);
   pShareMemory->SetKeyName(_keyName);
   pShareMemory->SetCapacity(capacity);
   pShareMemory->Create();
   _pAllocator = pShareMemory;
   // ���乲���ڴ�
   return SharedLink(_pAllocator->CreateSegment(capacity));
}

//============================================================
// <T>ֻ����ʽ�����ڴ档</T>
//
// @return ������
//============================================================
TBool FSharedGroup::Connect(){
   // ������Ҫ�����ڴ��С
   TSize capacity = SharedCapacity();
   // �ռ������ڴ�
   MO_ASSERT(NULL == _pAllocator);
   FShareMemory* pShareMemory = MO_CREATE(FShareMemory);
   pShareMemory->SetKey(_key);
   pShareMemory->SetKeyName(_keyName);
   pShareMemory->SetCapacity(capacity);
   pShareMemory->Connect();
   if(!pShareMemory->IsLinked()){
      MO_FATAL(TC("Connect share memory error. (key=%d, key_name=%s)"), _key, (TCharC*)_keyName);
   }
   _pAllocator = pShareMemory;
   // ���乲���ڴ�
   return SharedLink(_pAllocator->CreateSegment(capacity));
}

//============================================================
// <T>��д��ʽ�����ڴ档</T>
//
// @return ������
//============================================================
TBool FSharedGroup::Link(){
   // ������Ҫ�����ڴ��С
   TSize capacity = SharedCapacity();
   // �ռ������ڴ�
   MO_ASSERT(NULL == _pAllocator);
   FShareMemory* pShareMemory = MO_CREATE(FShareMemory);
   pShareMemory->SetKey(_key);
   pShareMemory->SetKeyName(_keyName);
   pShareMemory->SetCapacity(capacity);
   pShareMemory->Connect();
   if(!pShareMemory->IsLinked()){
      MO_FATAL(TC("Link share memory error. (key=%d, key_name=%s)"), _key, (TCharC*)_keyName);
   }
   _pAllocator = pShareMemory;
   // ���乲���ڴ�
   return SharedLink(_pAllocator->CreateSegment(capacity));
}

//============================================================
// <T>�鿴�����ڴ������Ϣ��</T>
//
// @return ������
//============================================================
TBool FSharedGroup::Dump(){
   TInt size = 0;
   MO_INFO(TC("Name                                     |              Total |  Head    Data"));
   MO_INFO(MO_DUMP_SHARED_LA);
   TListIteratorC<MShared*> iterator = _pShareds->IteratorC();
   while(iterator.Next()){
      // ��ù������
      TSize capacity = iterator->SharedCapacity();
      if(capacity > 0){
         size += capacity;
         iterator->DumpShared();
      }
   }
   MO_INFO(MO_DUMP_SHARED_LA);
   TChar format[MO_MEMORY_FORMATLENGTH];
   MO_INFO(TC("                                         | %18s |"),
         RInt::FormatCapacity(size, format, MO_MEMORY_FORMATLENGTH));
   return ETrue;
}

MO_NAMESPACE_END
