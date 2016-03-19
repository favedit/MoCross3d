//============================================================
// <T>��������</T>
// <P>��ν����ָ��������нڵ㹲��һ���ڴ�����</P>
// <P>   FSharedEntryAllocator������ڵ��ڴ�����</P>
// <P>   TSharedArray��ʹ����������Ľڵ��ڴ����������������ṹ�����������ռ�ڴ档</P>
//============================================================
#ifndef __MO_CM_SHAREDARRAY_H__
#define __MO_CM_SHAREDARRAY_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_SHARED_H__
#include "MoCmShared.h"
#endif // __MO_CM_SHARED_H__

#ifndef __MO_CM_LANGUAGE_H__
#include "MoCmLanguage.h"
#endif // __MO_CM_LANGUAGE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>ֻ�����������������</T>
//
// @template
// @type E:entry �ڵ�����
// @history 100326 MAOCY ����
//============================================================
template <class T>
class TSharedArrayIteratorC{
protected:
   T* _pEntries;
   TInt _start;
   TInt _count;
   TInt _current;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedArrayIteratorC(){
      _pEntries = NULL;
      _start = -1;
      _current = -1;
	  _count = 0;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedArrayIteratorC(const TSharedArrayIteratorC<T>& iterator){
      _pEntries = iterator._pEntries;
      _start = iterator._start;
      _current = iterator._current;
	  _count = iterator._count;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedArrayIteratorC(T* pEntries, TInt start, TInt length){
      _pEntries = pEntries;
      _start = start;
	  _count = length;
      _current = -1;
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline T operator *() const{
      MO_ASSERT(_current >= 0);
      return _pEntries[_current];
   }
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline const T* operator ->() const{
      MO_ASSERT(_current >= 0);
      return &_pEntries[_current];
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
      _current = _current < 0 ? _start : _current + 1;
	  //++_current;
      return (_current < _count && _current >= 0);
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Prior(){
	  _current = _current < 0 ? _start : _current - 1;
      return (_current >= 0 && _current < _count);
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline T Get(){
      MO_ASSERT(_current >= 0 && _current < _count);
      return _pEntries[_current];
   }
};

//============================================================
// <T>��������</T>
//
// @struct
// @type E:entry �ڵ�����
// @history 100326 MAOCY ����
//============================================================
template <typename T>
class MO_CM_DECLARE TSharedArray : public MShared{
public:
   struct SSharedArrayHead {
      TUint32 _count;
   };
public:
   typedef TSharedArrayIteratorC<T> TIteratorC;
private:
   T* _gEntries;
   SSharedArrayHead *_gHead;
   TUint32 _size;
public:
   //============================================================
   void OnSharedInitialize(){
      memset(_gEntries, 0, sizeof(T) * _size);
      _gHead->_count = 0;
   }
   //============================================================
   void OnSharedLink(TShareSegment& segment){
      MO_ASSERT(_size > 0);
      _gHead = segment.TypeAlloc<SSharedArrayHead>();
      _gEntries = segment.TypeAlloc<T>(_size);
   }
   //============================================================
   void SetCapacity(TUint32 capacity){
      _size = capacity;
   }
   
   //============================================================
   TSize SharedCapacity(){
      return _size * sizeof(T) + sizeof(SSharedArrayHead);
   }
   
public:
   //============================================================
   // �õ�ָ��Ԫ��, ���ɸ���
   //============================================================
   T& operator[](TUint32 index){
      MO_ASSERT(index < _gHead->_count);
      return _gEntries[index];
   }
   
   //============================================================
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   //============================================================
   TBool operator==(const TSharedArray<T>& array) const{
      return Equals(array);
   }
   
   //============================================================
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   //============================================================
   TBool operator!=(const TSharedArray<T>& array) const{
      return !Equals(array);
   }
   
   //============================================================
   // ׷��һ��������ǰ�����С�
   //============================================================
   void operator+=(const TSharedArray<T>& array){
      Append(array);
   }
   void operator=(const TSharedArray<T>& array){
	   Assign(array);
   }
public:
   //============================================================
   // ����Ƿ�Ϊ��
   //============================================================
   TBool IsEmpty() const{
      return (0 == _gHead->_count);
   }
   
   //============================================================
   // �������
   //============================================================
   TUint32 Count() const{
      return _gHead->_count;
   }
   
   //============================================================
   // �жϵ�ǰ�����ָ�������Ƿ����
   //============================================================
   TBool Equals(const TSharedArray<T>& array) const{
      // �Ƚ�����
      if(_gHead->_count != array._gHead->_count){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      TInt current = 0;
      TIteratorC iterator = array.IteratorC();
      while(iterator.Next()){
         if(_gEntries[current] != *iterator){
            return EFalse;
         }
         ++current;
      }
      return ETrue;
   }
   
   //============================================================
   // �����λ�õ�ֻ�����ݵ�����
   //============================================================
   TSharedArrayIteratorC<T> IteratorC() const{
      return TIteratorC(_gEntries, 0, _gHead->_count);
   }
   
   //============================================================
   // ���βλ�õ�ֻ�����ݵ�����
   //============================================================
   TSharedArrayIteratorC<T> LastIteratorC() const{
      return TIteratorC(_gEntries, _gHead->_count-1, _gHead->_count);
   }
   
   //============================================================
   // �õ�ָ��Ԫ��
   //============================================================
   T Get(TUint32 index) const{
      MO_ASSERT_RANGE(index, 0, _gHead->_count);
      return _gEntries[index];
   }
   
   //============================================================
   // ����һ��������ǰ�����С�
   //============================================================
   void Assign(const TSharedArray<T>& array){
      Clear();
      Append(array);
   }
   
   //============================================================
   // ׷��һ��������ǰ�����С�
   //============================================================
   void Append(const TSharedArray<T>& array){
      TIteratorC iterator = array.IteratorC();
      while(iterator.Next()){
         Push(*iterator);
      }
   }

   //============================================================
   // ����Ԫ��
   //============================================================
   void Insert(TUint32 idx, const T& value){
      MO_ASSERT(_gHead->_count < _size);
      MO_ASSERT(idx <= _gHead->_count);

      TUint32 pos = _gHead->_count++;
      for(TUint32 i = pos - 1; pos > idx; --i, --pos)
         _gEntries[pos] = _gEntries[i];
      
      _gEntries[idx] = value;
   }

   //============================================================
   // ������Ԫ��
   //============================================================
   void Insert(TUint32 idx, const T* buf, TUint32 len){
      MO_ASSERT(_gHead->_count + len <= _size);
      MO_ASSERT(idx <= _gHead->_count);
   
      TUint32 src = _gHead->_count - 1;
      _gHead->_count += len;
      TUint32 dst = _gHead->_count - 1;
      TUint32 stop = idx + len - 1;
      for(TUint32 i = src, j = dst; j > stop; --j, --i)
   	   _gEntries[j] = _gEntries[i];
   
      memcpy(&_gEntries[idx], buf, sizeof(T) * len);
   }
   
   //============================================================
   // ������ѹ����λ��
   //============================================================
   void Unshift(const T& value){
      // ����ǰ�ڵ�ѹ���׽ڵ�
	  Insert(0, value);
   }
   
   //============================================================
   // ���������������
   //============================================================
   T Shift(){
      MO_ASSERT(_gHead->_count > 0);
      T v = _gEntries[0];
      // ��������
      TInt32 end = _gHead->_count--;
      for(int i = 0, j = 1; j < end; ++i, ++j) {
   	   _gEntries[i] = _gEntries[j];
      }
      return v;
   }
   
   //============================================================
   // ������ѹ��βλ��
   //============================================================
   void Push(const T& v){
      // �ռ�һ��δʹ�õĽڵ�
      MO_ASSERT(_gHead->_count < _size);
      TInt32 pos = _gHead->_count++;
      _gEntries[pos] = v;
   }
   
   //============================================================
   // ���������β����
   //============================================================
   T Pop(){
      MO_ASSERT(_gHead->_count > 0);
      TInt pos = --_gHead->_count;
      // ���ؽڵ�
      return _gEntries[pos];
   }
   
   //============================================================
   // ��������ɾ������ڵ�
   //============================================================
   T Delete(TUint32 index){
      MO_ASSERT(index < _gHead->_count);
      T v = _gEntries[index];
   
      for(int i = index, j = i + 1; j < _gHead->_count; ++i, ++j) {
   	   _gEntries[i] = _gEntries[j];
      }
   
      _gHead->_count--;
      return v;
   }
   
   //============================================================
   // ��������ɾ������ڵ�, ��ɾ�����
   //============================================================
   void Remove(const T& v){
   	for(TUint32 i = 0; i < _gHead->_count; ++i) {
         if(_gEntries[i] == v) {
            Delete(i);
			--i;
         }
      }
   }
   
   //============================================================
   // �����������
   //============================================================
   void Clear(){
      // �ͷ�ȫ���б�
      _gHead->_count = 0;
   }
   
};

MO_NAMESPACE_END

#endif // __MO_CM_SHAREDLIST_H__

