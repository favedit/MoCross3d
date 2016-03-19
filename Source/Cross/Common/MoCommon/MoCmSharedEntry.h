#ifndef __MO_CM_SHAREDENTRY_H__
#define __MO_CM_SHAREDENTRY_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_SHARED_H__
#include "MoCmShared.h"
#endif // __MO_CM_SHARED_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��������ڵ��ռ���ͷ���塣</T>
//
// @struct
// @history 100326 MAOCY ����
//============================================================
struct SSharedEntryAllocatorHead{
   TInt count;
   TInt unused;
};

//============================================================
// <T>��������ڵ��ռ�����</T>
//
// @template
// @type E entry �ڵ�����
// @history 100326 MAOCY ����
//============================================================
template <typename E>
class FSharedEntryAllocator : public MShared{
protected:
   TInt _capacity;
   SSharedEntryAllocatorHead* _gHead;
   E* _gEntries;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   FSharedEntryAllocator(){
      _capacity = 0;
      _gHead = NULL;
      _gEntries = NULL;
   }
public:
   //------------------------------------------------------------
   // ��������
   void SetCapacity(TInt capacity){
      _capacity = capacity;
   }
   //------------------------------------------------------------
   // ���㹲���ڴ��С
   TSize SharedCapacity(){
      TSize size = sizeof(SSharedEntryAllocatorHead);
      size += sizeof(E) * _capacity;
      return size;
   }
   //------------------------------------------------------------
   // ���乲���ڴ�
   void SharedLink(TShareSegment segment){
      _gHead = segment.TypeAlloc<SSharedEntryAllocatorHead>();
      _gEntries = segment.TypeAlloc<E>(_capacity);
      MShared::SharedLink(segment);
   }
   //------------------------------------------------------------
   // �����ڴ��ʼ��
   void SharedInitialize(){
      _gHead->count = 0;
      if(_capacity > 0){
         for(TInt n=0; n<_capacity; n++){
            if(0 == n){
               _gEntries[n].prior = -1;
               _gEntries[n].next = n + 1;
            }else if(_capacity - 1 == n){
               _gEntries[n].prior = n - 1;
               _gEntries[n].next = -1;
            }else{
               _gEntries[n].prior = n - 1;
               _gEntries[n].next = n + 1;
            }
         }
         _gHead->unused = 0;
      }else{
         _gHead->unused = -1;
      }
   }
public:
   //------------------------------------------------------------
   // ����ȡֵ������
   E* operator *(){
      return _gEntries;
   }
   //------------------------------------------------------------
   // �������������
   E& operator [](TInt index){
      MO_ASSERT_RANGE(index, 0, _capacity);
      return _gEntries[index];
   }
public:
   //------------------------------------------------------------
   // ��ýڵ�ָ��
   E* Entries(){
      return _gEntries;
   }
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   E& Get(TInt index){
      MO_ASSERT_RANGE(index, 0, _capacity);
      return _gEntries[index];
   }
public:
   //------------------------------------------------------------
   // �ռ�һ������λ��
   TInt Alloc(){
      // ���δʹ�õ�����
      TInt index = _gHead->unused;
      MO_ASSERT_RANGE(index, 0, _capacity);
      _gHead->unused = _gEntries[index].next;
      _gHead->count++;
      return index;
   }
   //------------------------------------------------------------
   // �ռ�һ������λ��
   E& Alloc(TInt& index){
      // ���δʹ�õ�����
      index = _gHead->unused;
      MO_ASSERT_RANGE(index, 0, _capacity);
      _gHead->unused = _gEntries[index].next;
      _gHead->count++;
      return _gEntries[index];
   }
   //------------------------------------------------------------
   // �ͷ�һ������λ��
   void Free(TInt index){
      MO_ASSERT_RANGE(index, 0, _capacity);
      _gEntries[index].next = _gHead->unused;
      _gHead->unused = index;
      _gHead->count--;
   }
   //------------------------------------------------------------
   // �ͷ�һ������λ��
   void Free(TInt count, TInt first, TInt last){
      MO_ASSERT_RANGE(first, 0, _capacity);
      MO_ASSERT_RANGE(last, 0, _capacity);
      _gEntries[last].next = _gHead->unused;
      _gHead->unused = first;
      _gHead->count -= count;
   }
};

//============================================================
// <T>ֻ�����������������</T>
//
// @template
// @type E entry �ڵ�����
// @history 100326 MAOCY ����
//============================================================
template <typename E>
class TSharedEntryIteratorC{
protected:
   E* _pEntries;
   TInt _start;
   TInt _current;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedEntryIteratorC(){
      _pEntries = NULL;
      _start = -1;
      _current = -1;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedEntryIteratorC(const TSharedEntryIteratorC<E>& iterator){
      _pEntries = iterator._pEntries;
      _start = iterator._start;
      _current = iterator._current;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedEntryIteratorC(E* pEntries, TInt start){
      _pEntries = pEntries;
      _start = start;
      _current = -1;
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline E operator *() const{
      return _pEntries[_current];
   }
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline E operator ->() const{
      return _pEntries[_current];
   }
public:
   //------------------------------------------------------------
   // ����λ��
   inline void Reset(){
      _current = -1;
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Next(){
      _current = (_current < 0) ? _start : _pEntries[_current].next;
      return (_current >= 0);
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Prior(){
      _current = (_current < 0) ? _start : _pEntries[_current].prior;
      return (_current >= 0);
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline E& Get(){
      return _pEntries[_current];
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_SHAREDENTRY_H__
