#include "MoCmSharedList.h"

MO_NAMESPACE_BEGIN

//============================================================
void TSharedList::Initialize(FSharedListAllocator* pAllocator){
   _pAllocator = pAllocator;
   _gHead = pAllocator->AllocList();
   _gEntries = pAllocator->Entries();
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   MO_ASSERT(_gEntries);
}

//============================================================
void TSharedList::Release(){
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   _pAllocator->FreeList(_gHead);
}

//============================================================
// �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
//============================================================
TBool TSharedList::operator==(const TSharedList& list) const{
   return Equals(list);
}

//============================================================
// �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
//============================================================
TBool TSharedList::operator!=(const TSharedList& list) const{
   return !Equals(list);
}

//============================================================
// ׷��һ��������ǰ�����С�
//============================================================
void TSharedList::operator+=(const TSharedList& list){
   Append(list);
}

//============================================================
// ����Ƿ�Ϊ��
//============================================================
TBool TSharedList::IsEmpty() const{
   MO_ASSERT(_gHead);
   return (0 == _gHead->count);
}

//============================================================
// �������
//============================================================
TInt TSharedList::Count() const{
   MO_ASSERT(_gHead);
   return _gHead->count;
}

//============================================================
// �жϵ�ǰ�����ָ�������Ƿ����
//============================================================
TBool TSharedList::Equals(const TSharedList& list) const{
   MO_ASSERT(_gHead);
   MO_ASSERT(_gEntries);
   // �Ƚ�����
   if(_gHead->count != list._gHead->count){
      return EFalse;
   }
   // �Ƚ�������Ŀ
   TInt current = _gHead->first;
   TIteratorC iterator = list.IteratorC();
   while(current >= 0 && iterator.Next()){
      SSharedListEntry& entry = _gEntries[current];
      if(entry.code != *iterator){
         return EFalse;
      }
      current = entry.next;
   }
   return ETrue;
}

//============================================================
// <T>�жϵ�ǰ�����Ƿ���ָ�����롣</T>
//
// @param code ����
// @return �Ƿ���
//============================================================
TBool TSharedList::Contains(TInt32 code){
   MO_ASSERT(_gHead);
   MO_ASSERT(_gEntries);
   TInt current = _gHead->first;
   while(current >= 0){
      SSharedListEntry& entry = _gEntries[current];
      if(entry.code == code){
         return ETrue;
      }
      current = entry.next;
   }
   return EFalse;
}

//============================================================
// �����λ�õ�ֻ�����ݵ�����
//============================================================
TSharedListIteratorC TSharedList::IteratorC() const{
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   return TIteratorC(_pAllocator->Entries(), _gHead->first);
}

//============================================================
// ���βλ�õ�ֻ�����ݵ�����
//============================================================
TSharedListIteratorC TSharedList::LastIteratorC() const{
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   return TIteratorC(_pAllocator->Entries(), _gHead->last);
}

//============================================================
// ����һ��������ǰ�����С�
//============================================================
void TSharedList::Assign(const TSharedList& list){
   Clear();
   Append(list);
}

//============================================================
// ׷��һ��������ǰ�����С�
//============================================================
void TSharedList::Append(const TSharedList& list){
   TIteratorC iterator = list.IteratorC();
   while(iterator.Next()){
      Push(*iterator);
   }
}

//============================================================
// ������ѹ����λ��
//============================================================
void TSharedList::Unshift(TInt32 code){
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   // �ռ�һ��δʹ�õĽڵ�
   SSharedListEntry& entry = _pAllocator->AllocEntry();
   // ����ǰ�ڵ�ѹ���׽ڵ�
   if(_gHead->first < 0){
      _gHead->last = entry.index;
   }else{
      _gEntries[_gHead->first].prior = entry.index;
   }
   // ��������
   entry.prior = -1;
   entry.next = _gHead->first;
   entry.code = code;
   _gHead->first = entry.index;
   _gHead->count++;
}

//============================================================
// ���������������
//============================================================
TInt32 TSharedList::Shift(){
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   MO_ASSERT(_gHead->first >= 0);
   // �����׽ڵ�
   TInt index = _gHead->first;
   SSharedListEntry& entry = _gEntries[index];
   _gHead->first = entry.next;
   if(_gHead->first < 0){
      _gHead->last = -1;
   }else{
      _gEntries[_gHead->first].prior = -1;
   }
   // ��������
   _gHead->count--;
   // ���տ��нڵ�
   TInt32 code = entry.code;
   _pAllocator->FreeEntry(entry);
   // ���ؽڵ�
   return code;
}

//============================================================
// ������ѹ��βλ��
//============================================================
void TSharedList::Push(TInt32 code){
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   // �ռ�һ��δʹ�õĽڵ�
   SSharedListEntry& entry = _pAllocator->AllocEntry();
   // ����ǰ�ڵ����β�ڵ�
   if(_gHead->last < 0){
      _gHead->first = entry.index;
   }else{
      _gEntries[_gHead->last].next = entry.index;
   }
   // ��������
   entry.prior = _gHead->last;
   entry.next = -1;
   entry.code = code;
   _gHead->last = entry.index;
   _gHead->count++;
}

//============================================================
// ���������β����
//============================================================
TInt TSharedList::Pop(){
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   MO_ASSERT(_gHead->last >= 0);
   // ����β�ڵ�
   TInt index = _gHead->last;
   SSharedListEntry& entry = _gEntries[index];
   _gHead->last = entry.prior;
   if(_gHead->last < 0){
      _gHead->first = 0;
   }else{
      _gEntries[_gHead->last].next = 0;
   }
   // ��������
   _gHead->count--;
   // ���տ��нڵ�
   TInt32 code = entry.code;
   _pAllocator->FreeEntry(entry);
   // ���ؽڵ�
   return code;
}

//============================================================
// ��������ɾ������ڵ�
//============================================================
TInt32 TSharedList::Delete(TInt index){
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   // ��ýڵ�
   SSharedListEntry& entry = _gEntries[index];
   TInt prior = entry.prior;
   TInt next = entry.next;
   // ����ǰ�ڵ�
   if(prior < 0){
      _gHead->first = next;
   }else{
      _gEntries[prior].next = next;
   }
   // �����ڵ�
   if(next < 0){
      _gHead->last = prior;
   }else{
      _gEntries[next].prior = prior;
   }
   // ��������
   _gHead->count--;
   // ���տ��нڵ�
   TInt32 code = entry.code;
   _pAllocator->FreeEntry(entry);
   // ���ؽڵ�
   return code;
}

//============================================================
TInt32 TSharedList::Delete(TSharedListIterator& iterator){
   MO_ASSERT(_gEntries);
   TInt index = iterator._current;
   if(index >= 0){
      // ָ�����
      iterator._current  = _gEntries[index].next;
      // ɾ��λ��
      Delete(index);
      return ETrue;
   }
   return EFalse;
}

//============================================================
// ��������ɾ������ڵ�
//============================================================
TBool TSharedList::Remove(TInt32 code){
   MO_ASSERT(_gHead);
   MO_ASSERT(_gEntries);
   TBool result = EFalse;
   TInt32 current = _gHead->first;
   while(current >= 0){
      SSharedListEntry& entry = _gEntries[current];
      TInt next = entry.next;
      if(entry.code == code){
         result = ETrue;
         Delete(entry.index);
      }
      current = next;
   }
   return result;
}

//============================================================
// �����������
//============================================================
void TSharedList::Clear(){
   MO_ASSERT(_pAllocator);
   MO_ASSERT(_gHead);
   // �ͷ�ȫ���б�
   _pAllocator->FreeEntries(_gHead);
   // �����������
   _gHead->count = 0;
   _gHead->first = -1;
   _gHead->last = -1;
}

MO_NAMESPACE_END
