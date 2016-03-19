//============================================================
// <T>��������</T>
// <P>��ν����ָ��������нڵ㹲��һ���ڴ�����</P>
// <P>   FSharedEntryAllocator������ڵ��ڴ�����</P>
// <P>   TSharedList��ʹ����������Ľڵ��ڴ����������������ṹ�����������ռ�ڴ档</P>
//============================================================
#ifndef __MO_CM_SHAREDLIST_H__
#define __MO_CM_SHAREDLIST_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_SHARED_H__
#include "MoCmShared.h"
#endif // __MO_CM_SHARED_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ڵ㶨�塣</T>
//
// @struct
// @history 100328 MAOCY ����
//============================================================
struct SSharedListEntry{
   // �б�����
   TInt32 list;
   // �ڵ�����
   TInt32 index;
   // ǰ�ڵ�����
   TInt32 prior;
   // ��ڵ�����
   TInt32 next;
   // ����
   TInt32 code;
};

//============================================================
// <T>��������ͷ���塣</T>
//
// @struct
// @history 100330 MAOCY ����
//============================================================
struct SSharedListHead{
   // ����
   TInt32 count;
   // �ڵ�����
   TInt32 index;
   // �׽ڵ�����
   TInt32 first;
   // β�ڵ�����
   TInt32 last;
   // ǰ�ڵ�����
   TInt32 prior;
   // ��ڵ�����
   TInt32 next;
};

//============================================================
// <T>��������ڵ��ռ�����</T>
// <P>�ڴ�ṹ��[Head][SSharedListHead*capacity][SSharedEntry*entryCapacity]</P>
//
// @template
// @type E entry �ڵ�����
// @history 100326 MAOCY ����
//============================================================
class MO_CM_DECLARE FSharedListAllocator :
      public FObject,
      public MShared,
      public MNamed{
public:
   struct SHead{
      TInt32 listCount;   // ��������
      TInt32 listUnused;  // ����δʹ������
      TInt32 entryCount;  // �ڵ�����
      TInt32 entryUnused; // �ڵ�δʹ������
   };
protected:
   TInt32 _capacity;
   TInt32 _entryCapacity;
   SHead* _gHead;
   SSharedListHead* _gLists;
   SSharedListEntry* _gEntries;
public:
   FSharedListAllocator();
public:
   void SetCapacity(TInt capacity);
   void SetEntryCapacity(TInt entryCapacity);
   void OnSharedInitialize();
   void OnSharedLink(TShareSegment& segment);
   TSize SharedCapacity();
public:
   //------------------------------------------------------------
   // �����������ָ��
   MO_INLINE SSharedListHead* Lists(){
      return _gLists;
   }
   //------------------------------------------------------------
   // ��ýڵ�ָ��
   MO_INLINE SSharedListEntry* Entries(){
      return _gEntries;
   }
public:
   SSharedListHead* AllocList();
   void FreeList(SSharedListHead* pList);
   SSharedListEntry& AllocEntry();
   void FreeEntry(SSharedListEntry& entry);
   void FreeEntries(SSharedListHead* pList);
};

//============================================================
// <T>ֻ�����������������</T>
//
// @class
// @history 100326 MAOCY ����
//============================================================
class MO_CM_DECLARE TSharedListIteratorC{
protected:
   SSharedListEntry* _pEntries;
   TInt _start;
   TBool _skip;
   TInt _next;
   TInt _current;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedListIteratorC(){
      _pEntries = NULL;
      _start = -1;
      _skip = EFalse;
      _current = -1;
      _next = -1;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedListIteratorC(const TSharedListIteratorC& iterator){
      _pEntries = iterator._pEntries;
      _start = iterator._start;
      _skip = EFalse;
      _current = iterator._current;
      _next = -1;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedListIteratorC(SSharedListEntry* pEntries, TInt start){
      _pEntries = pEntries;
      _start = start;
      _skip = EFalse;
      _current = -1;
      _next = -1;
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline TInt32 operator *() const{
      MO_ASSERT(_current >= 0);
      return _pEntries[_current].code;
   }
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline TInt32 operator ->() const{
      MO_ASSERT(_current >= 0);
      return _pEntries[_current].code;
   }
public:
   //------------------------------------------------------------
   // ����λ��
   inline void Reset(){
      _current = -1;
      _next = -1;
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Next(){
      if(_skip){
         _current = _next;
         _skip = EFalse;
      }else{
         _current = (_current < 0) ? _start : _pEntries[_current].next;
      }
      return (_current >= 0);
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Prior(){
      if(_skip){
         _current = _next;
         _skip = EFalse;
      }else{
         _current = (_current < 0) ? _start : _pEntries[_current].prior;
      }
      return (_current >= 0);
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline TInt Get() const{
      MO_ASSERT(_current >= 0);
      return _pEntries[_current].code;
   }
};

//============================================================
// <T>���������������</T>
//
// @class
// @history 101111 MAOCY ����
//============================================================
class TSharedList;
class MO_CM_DECLARE TSharedListIterator : public TSharedListIteratorC{
public:
   friend class TSharedList;
protected:
   TSharedList* _pList;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedListIterator(){
      MO_CLEAR(_pList);
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedListIterator(const TSharedListIteratorC& iterator) :
         TSharedListIteratorC(iterator){
      MO_CLEAR(_pList);
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedListIterator(TSharedList* pList, SSharedListEntry* pEntries, TInt start) :
         TSharedListIteratorC(pEntries, start){
      _pList = pList;
   }
public:
   //------------------------------------------------------------
   TBool Delete();
};

//============================================================
// <T>��������</T>
//
// @struct
// @type E:entry �ڵ�����
// @history 100326 MAOCY ����
//============================================================
class MO_CM_DECLARE TSharedList{
public:
   typedef TSharedListIteratorC TIteratorC;
public:
   FSharedListAllocator* _pAllocator;
   SSharedListHead* _gHead;
   SSharedListEntry* _gEntries;
public:
   void Initialize(FSharedListAllocator* pAllocator);
   void Release();
public:
   TBool operator==(const TSharedList& list) const;
   TBool operator!=(const TSharedList& list) const;
   void operator+=(const TSharedList& list);
public:
   TBool IsEmpty() const;
   TInt Count() const;
   TBool Equals(const TSharedList& list) const;
   TBool Contains(TInt32 code);
   TSharedListIteratorC IteratorC() const;
   TSharedListIteratorC LastIteratorC() const;
public:
   void Assign(const TSharedList& list);
   void Append(const TSharedList& list);
   void Unshift(TInt32 code);
   TInt32 Shift();
   void Push(TInt32 code);
   TInt Pop();
   TInt32 Delete(TInt index);
   TInt32 Delete(TSharedListIterator& iterator);
   TBool Remove(TInt32 code);
   void Clear();
};

MO_NAMESPACE_END

#endif // __MO_CM_SHAREDLIST_H__
