//============================================================
// <T>��������</T>
// <P>��ν����ָ��������нڵ㹲��һ���ڴ�����</P>
// <P>   FSharedEntryAllocator������ڵ��ڴ�����</P>
// <P>   TSharedVector��ʹ����������Ľڵ��ڴ����������������ṹ�����������ռ�ڴ档</P>
//============================================================
#ifndef __MO_CM_SHAREDVECTOR_H__
#define __MO_CM_SHAREDVECTOR_H__

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
class TSharedVectorIteratorC{
protected:
   T* _pEntries;
   TInt _start;
   TInt _length;
   TInt _current;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedVectorIteratorC(){
      _pEntries = NULL;
      _start = -1;
      _current = -1;
	  _length = 0;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedVectorIteratorC(const TSharedVectorIteratorC<T>& iterator){
      _pEntries = iterator._pEntries;
      _start = iterator._start;
      _current = iterator._current;
	  _length = iterator._length;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedVectorIteratorC(T* pEntries, TInt start, TInt length){
      _pEntries = pEntries;
      _start = start;
	  _length = length;
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
      return (_current < _length && _current >= 0);
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Prior(){
	  _current = _current < 0 ? _start : _current - 1;
      return (_current >= 0 && _current < _length);
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline T Get(){
      MO_ASSERT(_current >= 0 && _current < _length);
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

struct SSharedVecHead {
   TUint32 _length;
};

template <typename T>
class MO_CM_DECLARE TSharedVector : public MShared{
public:
   struct SSharedVecHead {
      TUint32 _length;
   };
public:
   typedef TSharedVectorIteratorC<T> TIteratorC;
private:
   T* _gEntries;
   SSharedVecHead *_gHead;
   TUint32 _size;
public:
   //============================================================
   void OnSharedLink(TShareSegment& segment){
      MO_ASSERT(_size > 0);
      _gEntries = segment.TypeAlloc<T>(_size);
      _gHead = segment.TypeAlloc<SSharedVecHead>();
   }
   
   //============================================================
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   //============================================================
   TBool operator==(const TSharedVector<T>& vec) const{
      return Equals(vec);
   }
   
   //============================================================
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   //============================================================
   TBool operator!=(const TSharedVector<T>& vec) const{
      return !Equals(vec);
   }
   
   //============================================================
   // ׷��һ��������ǰ�����С�
   //============================================================
   void operator+=(const TSharedVector<T>& vec){
      Append(vec);
   }
   void operator=(const TSharedVector<T>& vec){
	   Assign(vec);
   }
   //============================================================
   // ����Ƿ�Ϊ��
   //============================================================
   
   TBool IsEmpty() const{
      return (0 == _gHead->_length);
   }
   
   //============================================================
   // �������
   //============================================================
   TUint32 Length() const{
      return _gHead->_length;
   }
   
   //============================================================
   // �жϵ�ǰ�����ָ�������Ƿ����
   //============================================================
   TBool Equals(const TSharedVector<T>& vec) const{
      // �Ƚ�����
      if(_gHead->_length != vec._gHead->_length){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      TInt current = 0;
      TIteratorC iterator = vec.IteratorC();
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
   TSharedVectorIteratorC<T> IteratorC() const{
      return TIteratorC(_gEntries, 0, _gHead->_length);
   }
   
   //============================================================
   // ���βλ�õ�ֻ�����ݵ�����
   //============================================================
   TSharedVectorIteratorC<T> LastIteratorC() const{
      return TIteratorC(_gEntries, _gHead->_length-1, _gHead->_length);
   }
   
   //============================================================
   // ����һ��������ǰ�����С�
   //============================================================
   void Assign(const TSharedVector<T>& vec){
      Clear();
      Append(vec);
   }
   
   //============================================================
   // ׷��һ��������ǰ�����С�
   //============================================================
   void Append(const TSharedVector<T>& vec){
      TIteratorC iterator = vec.IteratorC();
      while(iterator.Next()){
         Push(*iterator);
      }
   }
   
   //============================================================
   // ����Ԫ��
   //============================================================
   void Insert(TUint32 idx, const T &value){
      MO_ASSERT(_gHead->_length < _size);
      MO_ASSERT(idx <= _gHead->_length);

      TUint32 pos = _gHead->_length++;
      for(TUint32 i = pos - 1; pos > idx; --i, --pos)
         _gEntries[pos] = _gEntries[i];
      
      _gEntries[idx] = value;
   }

   //============================================================
   // ������Ԫ��
   //============================================================
   void Insert(TUint32 idx, const T* buf, TUint32 len){
      MO_ASSERT(_gHead->_length + len <= _size);
      MO_ASSERT(idx <= _gHead->_length);
   
      TUint32 src = _gHead->_length - 1;
      _gHead->_length += len;
      TUint32 dst = _gHead->_length - 1;
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
      MO_ASSERT(_gHead->_length > 0);
      T v = _gEntries[0];
      // ��������
      TInt32 end = _gHead->_length--;
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
      MO_ASSERT(_gHead->_length < _size);
      TInt32 pos = _gHead->_length++;
      _gEntries[pos] = v;
   }
   
   //============================================================
   // ���������β����
   //============================================================
   T Pop(){
      MO_ASSERT(_gHead->_length > 0);
      TInt pos = --_gHead->_length;
      // ���ؽڵ�
      return _gEntries[pos];
   }
   
   //============================================================
   // ��������ɾ������ڵ�
   //============================================================
   T Delete(TUint32 index){
      MO_ASSERT(index < _gHead->_length);
      T v = _gEntries[index];
   
      for(int i = index, j = i + 1; j < _gHead->_length; ++i, ++j) {
         _gEntries[i] = _gEntries[j];
      }

      _gHead->_length--;
      return v;
   }
   
   //============================================================
   // ��������ɾ������ڵ�, ��ɾ�����
   //============================================================
   void Remove(const T& v){
   	for(TUint32 i = 0; i < _gHead->_length; ++i) {
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
      _gHead->_length = 0;
   }
   
   //============================================================
   void SetCapacity(TUint32 capacity){
      _size = capacity;
   }
   
   //============================================================
   TSize SharedCapacity(){
      return _size * sizeof(T) + sizeof(SSharedVecHead);
   }
   
   //============================================================
   // ��ʼ��
   //============================================================
   void OnSharedInitialize(){
      memset(_gEntries, 0, sizeof(T) * _size);
      _gHead->_length = 0;
   }

   //============================================================
   // �õ�ָ��Ԫ��
   //============================================================
   T Get(TUint32 index) const{
      MO_ASSERT(index < _gHead->_length);
      return _gEntries[index];
   }
   
   //============================================================
   // �õ�ָ��Ԫ��, ���ɸ���
   //============================================================
   T& operator[](TUint32 index){
      MO_ASSERT(index < _gHead->_length);
      return _gEntries[index];
   }
};


MO_NAMESPACE_END

#endif // __MO_CM_SHAREDLIST_H__

