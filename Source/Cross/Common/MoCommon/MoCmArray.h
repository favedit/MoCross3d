#ifndef __MO_CM_ARRAY_H__
#define __MO_CM_ARRAY_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>ֻ���ڵ��������</T>
//
// @tool
// @history 100318 MAOCY ����
//============================================================
template <typename T>
class TArrayIteratorC{
protected:
   T* _pMemory;
   TInt _length;
   TInt _index;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TArrayIteratorC(){
      MO_CLEAR(_pMemory);
      _length = 0;
      _index = -1;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TArrayIteratorC(const TArrayIteratorC& iterator){
      _pMemory = iterator._pMemory;
      _length = iterator._length;
      _index = iterator._index;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TArrayIteratorC(T* pMemory, TInt length, TInt index = -1){
      _pMemory = pMemory;
      _length = length;
      _index = index;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& operator *() const{
      return GetC();
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& operator->() const{
      return GetC();
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return (0 == _length);
   }
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T value){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _length);
      return _pMemory[_index] == value;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      return (_length > 0) ? _index + 1 < _length : EFalse;
   }
   //------------------------------------------------------------
   //<T> �ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      if(_length > 0 && (_index + 1 < _length)){
         _index++;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return (_length > 0) ? _index - 1 >= 0 : EFalse;
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      if(_length > 0 && (_index + 1 < _length)){
         _index--;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& GetC() const{
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _length);
      return _pMemory[_index];
   }
public:
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _index = -1;
   }
};

//============================================================
// <T>ֻ���ڵ��������</T>
//
// @tool
// @history 100318 MAOCY ����
//============================================================
template <typename T>
class TArrayIterator{
protected:
   T* _pMemory;
   TInt* _pLength;
   TInt _index;
   TBool _changed;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TArrayIterator(){
      MO_CLEAR(_pMemory);
      MO_CLEAR(_pLength);
      _index = -1;
      _changed = EFalse;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TArrayIterator(const TArrayIterator& iterator){
      _pMemory = iterator._pMemory;
      _pLength = iterator._pLength;
      _index = iterator._index;
      _changed = iterator._changed;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TArrayIterator(T* pMemory, TInt* pLength, TInt index = -1){
      _pMemory = pMemory;
      _pLength = pLength;
      _index = index;
      _changed = EFalse;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& operator *() const{
      return GetC();
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T& operator *(){
      return Get();
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& operator->() const{
      return GetC();
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T& operator->(){
      return Get();
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return (0 == *_pLength);
   }
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T value){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, *_pLength);
      MO_ASSERT(!_changed);
      return _pMemory[_index] == value;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      TInt length = *_pLength;
      if(length > 0){
         if(_changed){
            return _index < length;
         }else{
            return (_index + 1) < length;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   //<T> �ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      TInt length = *_pLength;
      if(length > 0){
         if(_changed){
            _changed = EFalse;
            return _index < length;
         }else if(_index + 1 < length){
            _index++;
            return ETrue;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      TInt length = *_pLength;
      if(length > 0){
         if(_changed){
            return _index >= 0;
         }else{
            return (_index - 1) >= 0;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      TInt length = *_pLength;
      if(length > 0){
         if(_changed){
            _changed = EFalse;
            return _index < length;
         }else if(_index + 1 < length){
            _index--;
            return ETrue;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& GetC() const{
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, *_pLength);
      MO_ASSERT(!_changed);
      return _pMemory[_index];
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T& Get(){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, *_pLength);
      MO_ASSERT(!_changed);
      return _pMemory[_index];
   }
public:
   //------------------------------------------------------------
   // <T>ɾ����ǰλ�����ݡ�</T>
   MO_INLINE T Delete(){
      TInt length = *_pLength;
      MO_ASSERT_RANGE(_index, 0, length);
      T value = _pMemory[_index];
      if(_index != length - 1){
         RTypes<T>::Move(_pMemory + _index, _pMemory + _index + 1, length - _index);
      }
      *_pLength = length - 1;
      _changed = ETrue;
      return value;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _index = -1;
      _changed = EFalse;
   }
};

//============================================================
// <T>�������顣</T>
// <P>���ݵĹ���ṹ�����漰�ڴ������ͷš�</P>
//
// @manager
// @type T ��������
// @history 130416 MAOCY ����
//============================================================
template <typename T>
class MArray{
public:
   typedef TInt (*HComparer)(const T& source, const T& target, TAny* pCondition);
   typedef TInt (*HComparerValue)(T source, T target, TAny* pCondition);
   typedef TArrayIteratorC<T> TIteratorC;
   typedef TArrayIterator<T> TIterator;
protected:
   // @attribute ����ָ��
   T* _pMemory;
   // @attribute ���ݳ���
   TInt _length;
   // @attribute ��������
   TInt _capacity;
protected:
   //------------------------------------------------------------
   // <T>�����������顣</T>
   MArray(){
      MO_CLEAR(_pMemory);
      _length = 0;
      _capacity = 0;
   }
   //------------------------------------------------------------
   // <T>�����������顣</T>
   MO_ABSTRACT ~MArray(){
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_VIRTUAL void InnerResize(TInt size, TBool copy, TBool extends, TBool force) = 0;
public:
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   MO_INLINE TBool operator==(const MArray<T>& values) const{
      return RTypes<T>::Equals(_pMemory, _length, values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   MO_INLINE TBool operator!=(const MArray<T>& values) const{
      return !RTypes<T>::Equals(_pMemory, _length, values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ�С��ָ���������������ݡ�
   MO_INLINE TBool operator<(const MArray<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _length, values.MemoryC(), values.Length()) < 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ����ָ���������������ݡ�
   MO_INLINE TBool operator>(const MArray<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _length, values.MemoryC(), values.Length()) > 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ�С�ڵ���ָ���������������ݡ�
   MO_INLINE TBool operator<=(const MArray<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _length, values.MemoryC(), values.Length()) <= 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ���ڵ���ָ���������������ݡ�
   MO_INLINE TBool operator>=(const MArray<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _length, values.MemoryC(), values.Length()) >= 0;
   }
   //------------------------------------------------------------
   // <T>���ֻ���������ݡ�</T>
   MO_INLINE operator const T*() const{
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>�����������</T>
   MO_INLINE operator T*(){
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>���ָ��λ�õ�ֻ���������ݡ�</T>
   MO_INLINE const T& operator[](TInt index) const{
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>����ָ��λ�õ��������ݡ�</T>
   MO_INLINE T& operator[](TInt index){
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>׷��һ���Ⱦݵ���ǰ����β����</T>
   MO_INLINE void operator+=(T value){
      Push(value);
   }
   //------------------------------------------------------------
   // <T>׷��һ�����鵽��ǰ����β����</T>
   MO_INLINE void operator+=(const TPtrC<T>& ptr){
      Append(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>׷��һ�����鵽��ǰ����β����</T>
   MO_INLINE void operator+=(const MArray<T>& values){
      Append(values.MemoryC(), values.Length());
   }   
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == _length);
   }
   //------------------------------------------------------------
   // <T>�ж������Ƿ�ǿա�</T>
   MO_INLINE TBool IsNotEmpty() const{
      return (_length > 0);
   }
   //------------------------------------------------------------
   // <T>�ж������Ƿ�������</T>
   MO_INLINE TBool IsFull() const{
      return (_length == _capacity);
   }
   //------------------------------------------------------------
   // <T>�ж������Ƿ�δ����</T>
   MO_INLINE TBool IsNotFull() const{
      return (_length < _capacity);
   }
   //------------------------------------------------------------
   // <T>���ֻ������ָ�롣</T>
   MO_INLINE const T* MemoryC() const{
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE T* Memory(){
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TInt Length() const{
      return _length;
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TInt ByteLength() const{
      return sizeof(T) * _length;
   }
   //------------------------------------------------------------
   // <T>�������������</T>
   MO_INLINE TInt Capacity() const{
      return _capacity;
   }
   //------------------------------------------------------------
   // <T>�������������TODO��������ǰ����ʱ��������</T>
   //MO_INLINE TInt Size() const{
   //   return _capacity;
   //}
public:
   //------------------------------------------------------------
   // ��ǰ�������Ƿ��ָ��������ȡ�
   MO_INLINE TBool Equals(const MArray<T>& values) const{
      return RTypes<T>::Equals(_pMemory, _length, values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // ����ָ�������Ƿ�����ڵ�ǰ����Ŀ�ʼλ�á�
   MO_INLINE TBool StartsWith(const MArray<T>& values) const{
      return RTypes<T>::StartsWith(_pMemory, _length, values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // ����ָ�������Ƿ�����ڵ�ǰ����Ľ���λ�á�
   MO_INLINE TBool EndsWith(const MArray<T>& values) const{
      return RTypes<T>::EndsWith(_pMemory, _length, values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // ��ǰ�����к�ָ������Ĵ�С��
   MO_INLINE TInt Compare(const MArray<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _length, values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�������Ƿ���ָ�����ݡ�</T>
   MO_INLINE TBool Contains(T value) const{
      TInt result = RTypes<T>::IndexOf(_pMemory, _length, value);
      return (ENotFound != result);
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����в���ָ��ֵ���ֵ�����λ�á�
   MO_INLINE TInt IndexOf(T value) const{
      return RTypes<T>::IndexOf(_pMemory, _length, value);
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����У���ָ��λ��֮�����ָ��ֵ���ֵ�����λ�á�
   MO_INLINE TInt IndexOf(T value, TInt offset) const{
      MO_ASSERT_RANGE(offset, 0, _length);
      TInt result = RTypes<T>::IndexOf(_pMemory + offset, _length - offset, value);
      return (ENotFound == result) ? result : offset + result;
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����в��������ֵ�����λ�á�
   MO_INLINE TInt LastIndexOf(T value) const{
      return RTypes<T>::LastIndexOf(_pMemory, _length, value);
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����в��������ֵ�����λ�á�
   MO_INLINE TInt LastIndexOf(T value, TInt offset) const{
      MO_ASSERT_RANGE(offset, 0, _length);
      return RTypes<T>::LastIndexOf(_pMemory, _length - offset, value);
   }
public:
   //------------------------------------------------------------
   // <T>��ȡֻ����������</T>
   MO_INLINE TIteratorC IteratorC(){
      return TIteratorC(_pMemory, _length);
   }
   //------------------------------------------------------------
   // <T>��ȡֻ����������</T>
   MO_INLINE TIteratorC IteratorC(TInt index){
      return TIteratorC(_pMemory + index, _length - index);
   }
   //------------------------------------------------------------
   // <T>��ȡ��������</T>
   MO_INLINE TIterator Iterator(){
      return TIterator(_pMemory, &_length);
   }
   //------------------------------------------------------------
   // <T>��ȡ��������</T>
   MO_INLINE TIterator Iterator(TInt index){
      return TIterator(_pMemory + index, &_length - index);
   }
   //------------------------------------------------------------
   // <T>��ȡ��һ�����͡�</T>
   MO_INLINE T& First(){
      MO_ASSERT(_length > 0);
      return _pMemory[0];
   }
   //------------------------------------------------------------
   // <T>��ȡ���һ�����͡�</T>
   MO_INLINE T& Last(){
      MO_ASSERT(_length > 0);
      return _pMemory[_length - 1];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE const T& GetC(TInt index) const{
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE const T& GetC(TInt index, const T& value) const{
      if((index >= 0) && (index < _length)){
         return _pMemory[index];
      }
      return value;
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE T& Get(TInt index){
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE T& Get(TInt index, T& value){
      if((index >= 0) && (index < _length)){
         return _pMemory[index];
      }
      return value;
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE T Nvl(TInt index, T defaultValue){
      if((index >= 0) && (index < _length)){
         return _pMemory[index];
      }
      return defaultValue;
   }
public:
   //------------------------------------------------------------
   // <T>���ֻ������ָ�롣</T>
   MO_INLINE TPtrC<T> PtrC() const{
      return TPtrC<T>(_pMemory, _length);
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE TPtr<T> Ptr(){
      return TPtr<T>(_pMemory, &_length, _capacity);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����е���߲�����������á�
   MO_INLINE TPtrC<T> LeftPtrC(TInt length) const{
      MO_ASSERT_BETWEEN(length, 0, _length);
      return TPtrC<T>(_pMemory, length);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����е��ұ߲�����������á�
   MO_INLINE TPtrC<T> RightPtrC(TInt length) const{
      MO_ASSERT_BETWEEN(length, 0, _length);
      return TPtrC<T>(_pMemory + (_length - length), length);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĿ�ʼ����β�����á�
   MO_INLINE TPtrC<T> MidPtrC(TInt offset) const{
      MO_ASSERT_BETWEEN(offset, 0, _length);
      return TPtrC<T>(_pMemory + offset, _length - offset);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĲ�����������á�
   MO_INLINE TPtrC<T> MidPtrC(TInt offset, TInt length) const{
      MO_ASSERT_BETWEEN(offset, 0, _length);
      MO_ASSERT_BETWEEN(length, 0, _length - offset);
      return TPtrC<T>(_pMemory + offset, length);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĲ�����������á�
   MO_INLINE TPtrC<T> SubPtrC(TInt begin, TInt end) const{
      MO_ASSERT_BETWEEN(begin, 0, _length);
      MO_ASSERT_BETWEEN(end, 0, _length);
      MO_ASSERT(begin <= end);
      return TPtrC<T>(_pMemory + begin, end - begin);
   }
public:
   //------------------------------------------------------------
   // ����ָ�����������ڵ�ǰ�������ͳ��ֵ�����λ�á�
   MO_INLINE TInt Find(const T* pValue, TInt length) const{
      return RTypes<T>::Find(_pMemory, _length, pValue, length);
   }
   //------------------------------------------------------------
   // ����ָ�����������ڵ�ǰ�������ͳ��ֵ�����λ�á�
   MO_INLINE TInt Find(const MArray<T>& values) const{
      return RTypes<T>::Find(_pMemory, _length, values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // ����ָ�����������ڵ�ǰ�������ͳ��ֵ�����λ�á�
   MO_INLINE TInt LastFind(const T* pValue, TInt length) const{
      return RTypes<T>::LastFind(_pMemory, _length, pValue, length);
   }
   //------------------------------------------------------------
   // ����ָ�����������ڵ�ǰ�������ͳ��ֵ�����λ�á�
   MO_INLINE TInt LastFind(const MArray<T>& values) const{
      return RTypes<T>::LastFind(_pMemory, _length, values.MemoryC(), values.Length());
   }
public:
   //------------------------------------------------------------
   // <T>��֤�ڴ��С����������ǰ���ݡ�</T>
   MO_INLINE void ForceSize(TInt size){
      InnerResize(size, ETrue, EFalse, EFalse);
   }
   //------------------------------------------------------------
   // <T>��֤�ڴ��С��������ǰ���ݡ�</T>
   MO_INLINE void EnsureSize(TInt size){
      InnerResize(size, ETrue, ETrue, EFalse);
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void Assign(const T* pValues, TInt length){
      // ������
      MO_ASSERT(pValues);
      MO_ASSERT(length >= 0);
      // ��������
      if((NULL != pValues) && (length >= 0)){
         InnerResize(length, EFalse, EFalse, EFalse);
         if((_pMemory != pValues) && (length > 0)){
            RTypes<T>::Copy(_pMemory, pValues, length);
         }
         _length = length;
      }
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void Assign(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void Assign(const MArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void AssignArray(const MArray<T>* pValues){
      MO_ASSERT(pValues);
      Assign(pValues->MemoryC(), pValues->Length());
   }
   //------------------------------------------------------------
   // <T>׷��һ������ָ�뵽��ǰ����β����</T>
   MO_INLINE void Append(const T* pValues, TInt length){
      // ������
      MO_ASSERT(pValues);
      MO_ASSERT(length >= 0);
      // ��������
      if((NULL != pValues) && (length >= 0)){
         InnerResize(_length + length, ETrue, ETrue, EFalse);
         if((_pMemory != pValues) && (length > 0)){
            RTypes<T>::Copy(_pMemory + _length, pValues, length);
         }
         _length += length;
      }
   }
   //------------------------------------------------------------
   // <T>׷��һ���䳤�������͵���ǰ����β����</T>
   MO_INLINE void Append(const TPtrC<T>& ptr){
      Append(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>׷��һ���䳤�������͵���ǰ����β����</T>
   MO_INLINE void Append(const MArray<T>& values){
      Append(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>׷��һ���䳤�������͵���ǰ����β����</T>
   MO_INLINE void AppendArray(const MArray<T>* pValues){
      MO_ASSERT(pValues);
      Append(pValues->MemoryC(), pValues->Length());
   }
   //------------------------------------------------------------
   // <T>����һ���Ⱦ���ָ��λ�á�</T>
   MO_INLINE void Insert(TInt index, T value){
      MO_ASSERT_BETWEEN(index, 0, _length);
      InnerResize(_length + 1, ETrue, ETrue, EFalse);
      RTypes<T>::Move(_pMemory + index + 1, _pMemory + index, _length - index);
      _pMemory[index] = value;
      _length++;
   }
   //------------------------------------------------------------
   // <T>����һ���Ⱦ�ָ����ָ��λ�á�</T>
   MO_INLINE void Insert(TInt index, const T* pValues, TInt length){
      // ������
      MO_ASSERT_BETWEEN(index, 0, _length);
      MO_ASSERT(pValues);
      MO_ASSERT(length >= 0);
      // ��������
      if((index >= 0) && (index <= _length) && (NULL != pValues) && (length >= 0)){
         InnerResize(_length + length, ETrue, ETrue, EFalse);
         if(_length - index > 0){
            RTypes<T>::Move(_pMemory + index + length, _pMemory + index, _length - index);
         }
         if(length > 0){
            RTypes<T>::Copy(_pMemory + index, pValues, length);
         }
         _length += length;
      }
   }
   //------------------------------------------------------------
   // <T>����һ��������ָ��λ�á�</T>
   MO_INLINE void Insert(TInt index, const MArray<T>& values){
      Insert(index, values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>���ײ�����һ���Ⱦݡ�</T>
   MO_INLINE T Shift(){
      MO_ASSERT(_length > 0);
      T value = _pMemory[0];
      _length--;
      RTypes<T>::Move(_pMemory, _pMemory + 1, _length);
      return value;
   }
   //------------------------------------------------------------
   // <T>���ײ�ѹ��һ���Ⱦݡ�</T>
   MO_INLINE void Unshift(const T& value){
      InnerResize(_length + 1, ETrue, ETrue, EFalse);
      RTypes<T>::Move(_pMemory + 1, _pMemory, _length);
      _pMemory[0] = value;
      _length++;
   }
   //------------------------------------------------------------
   // <T>��β������һ���Ⱦݡ�</T>
   MO_INLINE T Pop(){
      MO_ASSERT(_length);
      return _pMemory[--_length];
   }
   //------------------------------------------------------------
   // <T>׷��һ���Ⱦݵ���ǰ����β����</T>
   MO_INLINE void Push(const T& value){
      InnerResize(_length + 1, ETrue, ETrue, EFalse);
      _pMemory[_length++] = value;
   }
   //------------------------------------------------------------
   // <T>ʹ��ָ��������䵱ǰ���顣</T>
   MO_INLINE void Fill(T value){
      RTypes<T>::Fill(_pMemory, _length, value);
   }
   //------------------------------------------------------------
   // <T>ʹ��ָ�����ݺ�ָ��������䵱ǰ���顣</T>
   MO_INLINE void Fill(T value, TInt length){
      MO_ASSERT_RANGE(length, 0, _length)
      RTypes<T>::Fill(_pMemory, length, value);
   }
   //------------------------------------------------------------
   // <T>ʹ��ָ�����ݺ�ָ�����ȴ�ָ��λ����䵱ǰ���顣</T>
   MO_INLINE void Fill(T value, TInt offset, TInt length){
      MO_ASSERT_RANGE(length, 0, _length - offset)
      RTypes<T>::Fill(_pMemory + offset, length, value);
   }
   //------------------------------------------------------------
   // <T>��Դ�����滻ΪĿ�����ݡ�</T>
   MO_INLINE void Replace(T source, T target){
      RTypes<T>::Replace(_pMemory, _length, source, target);
   }
   //------------------------------------------------------------
   // <T>TODO:��Դ�����滻ΪĿ�����顣</T>
   MO_INLINE void Replace(const MArray<T>& source, const MArray<T>& target){
      TInt sourceLength = source.Length();
      TInt targetLength = target.Length();
      T* pWriter = _pMemory;
      T* pReader = _pMemory;
      if(sourceLength >= target.Length()){
         // �滻Ŀ�����С����Դ����ʱ
         TInt count = 0;
         while(ETrue){
            TInt find = RTypes<T>::Find(pReader, _length, source.MemoryC(), sourceLength);
            if(ENotFound != find){
               RTypes<T>::Move(pWriter, pReader, find);
               RTypes<T>::Copy(pWriter + find, target.MemoryC(), targetLength);
               pReader += find + sourceLength;
               pWriter += find + targetLength;
               count++;
            }else{
               RTypes<T>::Move(pWriter, pReader, _length - (pReader - _pMemory));
            }
         }
         _length += (targetLength - sourceLength) * count;
      }else{
         // ���㳤��
         TInt count = RTypes<T>::Count(_pMemory, _length, source.MemoryC(), source.Length());
         TInt size = _length + (targetLength - sourceLength) * count;
         InnerResize(size, ETrue, ETrue, EFalse);
         // �滻Ŀ�����С����Դ����ʱ
         TInt position = _length;
         while(ETrue){
            TInt find = RTypes<T>::LastFind(pReader, position, source.MemoryC(), sourceLength);
            if(ENotFound != find){
               RTypes<T>::Move(pWriter, pReader, find);
               RTypes<T>::Copy(pWriter + find, target.MemoryC(), targetLength);
               pReader += find + sourceLength;
               pWriter += find + targetLength;
               count++;
            }else{
               RTypes<T>::Move(pWriter, pReader, _length - (pReader - _pMemory));
            }
            position += targetLength - sourceLength;
         }
         _length = size;
      }
   }
   //------------------------------------------------------------
   // <T>������ǰ����������λ�õ�ֵ��</T>
   MO_INLINE void Swap(TInt index1, TInt index2){
      MO_ASSERT_RANGE(index1, 0, _length);
      MO_ASSERT_RANGE(index2, 0, _length);
      if(index1 != index2){
         T value = _pMemory[index1];
         _pMemory[index1] = _pMemory[index2];
         _pMemory[index2] = value;
      }
   }
   //------------------------------------------------------------
   // <T>ɾ��ָ��λ�õ����ݡ�</T>
   MO_INLINE TBool Delete(TInt index, T* pValue = NULL){
      // ������
      MO_ASSERT_RANGE(index, 0, _length);
      // ɾ������
      if((index >= 0) && (index < _length)){
         // ��������
         if(NULL != pValue){
            MO_LIB_MEMORY_COPY(pValue, sizeof(T), _pMemory + index, sizeof(T));
         }
         // �����ڴ�
         if((_length - index) > 0){
            RTypes<T>::Move(_pMemory + index, _pMemory + index + 1, _length - index);
         }
         _length--;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>ɾ��ָ��λ����ĳ��ȵ����ݡ�</T>
   // <P>������ȳ�������ɾ��ָ��λ�õ�����λ��֮�������</P>
   MO_INLINE TBool DeleteSegment(TInt offset, TInt length){
      MO_ASSERT_RANGE(offset, 0, _length);
      MO_ASSERT_BETWEEN(length, 0, _length - offset);
      if((offset >= 0) && (offset < _length) && (length >= 0) && (length <= (_length - offset))){
         TInt movied = _length - (offset + length);
         if(movied > 0){
            TInt copy = MO_LIB_MIN(movied, length);
            RTypes<T>::Move(_pMemory + offset, _pMemory + offset + length, copy);
         }
         _length -= length;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�Ƴ�ָ�����ݡ�</T>
   // <P>���ܻ��Ƴ������ͬ�����ݡ�</P>
   MO_INLINE void Remove(T value){
      TInt n = -1;
      TInt position = 0;
      while(++n < _length){
         if(_pMemory[n] != value){
            _pMemory[position++] = _pMemory[n];
         }
      }
      _length = position;
   }
   //------------------------------------------------------------
   // <T>����ָ������λ�õ����ݡ�</T>
   MO_INLINE void Set(TInt index, T value){
      MO_ASSERT_RANGE(index, 0, _length);
      _pMemory[index] = value;
   }
   //------------------------------------------------------------
   // <T>����ָ������λ�õ����ݣ�λ�ò���ʱ�������С��</T>
   MO_INLINE void ExtendSet(TInt index, T value){
      if(index >= _length){
         InnerResize(index + 1, ETrue, ETrue, EFalse);
         _length = index + 1;
      }
      _pMemory[index] = value;
   }
   //------------------------------------------------------------
   // <T>�������ݳ��ȣ���������ǰ���ݡ�</T>
   MO_INLINE void ForceLength(TInt length){
      InnerResize(length, EFalse, EFalse, ETrue);
      _length = length;
   }
   //------------------------------------------------------------
   // <T>�������ݳ��ȡ�</T>
   // <P>���ȱ�С�󣬶�������ݽ���ʧ������洢����ָ�룬һ��Ҫ�Լ����ͷŶ�������ͺ�����С���ȡ�
   MO_INLINE void SetLength(TInt length){
      InnerResize(length, ETrue, EFalse, EFalse);
      _length = length;
   }
   //------------------------------------------------------------
   // <T>ʹ���������Լ������ͽ�������</T>
   MO_INLINE void Sort(HComparer hComparer, TAny* pCondition = NULL){
      MO_ASSERT(hComparer);
      if((NULL != _pMemory) && (_length > 1)){
         RTypes<T>::SortQuickObject(_pMemory, _length, hComparer, pCondition);
      }
   }
   //------------------------------------------------------------
   // <T>ʹ���������Լ������ͽ�������</T>
   MO_INLINE void SortValue(HComparerValue hComparer, TAny* pCondition = NULL){
      MO_ASSERT(hComparer);
      if((NULL != _pMemory) && (_length > 1)){
         RTypes<T>::SortQuickValue(_pMemory, _length, hComparer, pCondition);
      }
   }
   //------------------------------------------------------------
   // <T>����������ݡ�</T>
   // <P>ע�Ȿ���������ݲ����κδ�������洢ָ�룬һ��Ҫ���Լ��ͷš�ֻ�ǽ�������Ϊ�գ��������·����ݡ�</P>
   MO_INLINE void Clear(){
      _length = 0;
   }
   //------------------------------------------------------------
   // <T>�ͷ��������ݡ�</T>
   MO_INLINE void Free(){
      InnerResize(0, EFalse, EFalse, EFalse);
      _length = 0;
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE MArray<TAny>    MAnys;
typedef MO_CM_DECLARE MArray<TBool>   MBools;
typedef MO_CM_DECLARE MArray<TByte>   MBytes;
typedef MO_CM_DECLARE MArray<TChar8>  MChar8s;
typedef MO_CM_DECLARE MArray<TChar16> MChar16s;
typedef MO_CM_DECLARE MArray<TInt>    MInts;
typedef MO_CM_DECLARE MArray<TInt16>  MInt16s;
typedef MO_CM_DECLARE MArray<TInt32>  MInt32s;
typedef MO_CM_DECLARE MArray<TInt64>  MInt64s;
typedef MO_CM_DECLARE MArray<TUint>   MUints;
typedef MO_CM_DECLARE MArray<TUint16> MUint16s;
typedef MO_CM_DECLARE MArray<TUint32> MUint32s;
typedef MO_CM_DECLARE MArray<TUint64> MUint64s;
typedef MO_CM_DECLARE MArray<TFloat>  MFloats;
typedef MO_CM_DECLARE MArray<TDouble> MDoubles;
#ifdef _UNICODE
typedef MO_CM_DECLARE MChar16s MChars;
#else
typedef MO_CM_DECLARE MChar8s MChars;
#endif // _UNICODE

//============================================================
// <T>�䳤�����顣</T>
//
// @tool
// @type T ��������
// @history 091225 MAOCY ����
//============================================================
template <typename T>
class MArrayData : public MArray<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   MArrayData(){
   }
   //------------------------------------------------------------
   // <T>�����䳤���顣</T>
   MO_ABSTRACT ~MArrayData(){
      MO_FREE(this->_pMemory);
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ������ָ�롣</T>
   MO_INLINE void operator=(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const MArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const MArrayData<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force){
      // �ͷ��ڴ�
      if(size == 0){
         this->_capacity = 0;
         MO_FREE(this->_pMemory);
         return;
      }
      // ����С
      if(!force){
         if(size <= this->_capacity){
            return;
         }
      }
      // ���ڴ治��ʱ�����¼����ڴ�����
      TInt capacity = size;
      if(extends){
         capacity = RTypes<T>::CalculateTypeCapacity(this->_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      T* pAlloc = MO_TYPES_ALLOC(T, capacity);
      MO_ASSERT(pAlloc);
      RTypes<T>::Clear(pAlloc, capacity);
      // ���������ǰ�ڴ�
      if(NULL != this->_pMemory){
         // �������С�ڴ棬���鳤��
         if(this->_length > capacity){
            this->_length = capacity;
         }
         // ������Ч����
         if(copy && (this->_length > 0)){
            MO_LIB_TYPES_COPY(T, pAlloc, capacity, this->_pMemory, this->_length);
         }
         // �ͷ���ǰ�ڴ�
         MO_FREE(this->_pMemory);
      }
      // �����µ��ڴ�
      this->_pMemory = pAlloc;
      this->_capacity = capacity;
   }
};

//============================================================
// <T>�䳤ջ���顣</T>
//
// @tool
// @type T ��������
// @history 130416 MAOCY ����
//============================================================
template <typename T>
class TArray : public MArray<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TArray(){
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TArray(TInt capacity){
      InnerResize(capacity, EFalse, EFalse, EFalse);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TArray(const T* pValues, TInt length){
      Assign(pValues, length);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TArray(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TArray(const MArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TArray(const TArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>�����䳤���顣</T>
   MO_ABSTRACT ~TArray(){
      MO_FREE(this->_pMemory);
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ��������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ��������ݡ�</T>
   MO_INLINE void operator=(const MArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ��������ݡ�</T>
   MO_INLINE void operator=(const TArray& values){
      Assign(values.MemoryC(), values.Length());
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force){
      // �ͷ��ڴ�
      if(size == 0){
         this->_capacity = 0;
         MO_FREE(this->_pMemory);
         return;
      }
      // ����С
      if(!force){
         if(size <= this->_capacity){
            return;
         }
      }
      // ���ڴ治��ʱ�����¼����ڴ�����
      TInt capacity = size;
      if(extends){
         capacity = RTypes<T>::CalculateTypeCapacity(this->_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      T* pAlloc = MO_TYPES_ALLOC(T, capacity);
      MO_ASSERT(pAlloc);
      RTypes<T>::Clear(pAlloc, capacity);
      // ���������ǰ�ڴ�
      if(NULL != this->_pMemory){
         // �������С�ڴ棬���鳤��
         if(this->_length > capacity){
            this->_length = capacity;
         }
         // ������Ч����
         if(copy && (this->_length > 0)){
            MO_LIB_TYPES_COPY(T, pAlloc, capacity, this->_pMemory, this->_length);
         }
         // �ͷ���ǰ�ڴ�
         MO_FREE(this->_pMemory);
      }
      // �����µ��ڴ�
      this->_pMemory = pAlloc;
      this->_capacity = capacity;
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE TArray<TAny*>   TPtrs;
typedef MO_CM_DECLARE TArray<TBool>   TBools;
typedef MO_CM_DECLARE TArray<TByte>   TBytes;
typedef MO_CM_DECLARE TArray<TChar>   TChars;
typedef MO_CM_DECLARE TArray<TChar8>  TChar8s;
typedef MO_CM_DECLARE TArray<TChar16> TChar16s;
typedef MO_CM_DECLARE TArray<TInt>    TInts;
typedef MO_CM_DECLARE TArray<TInt8>   TInt8s;
typedef MO_CM_DECLARE TArray<TInt16>  TInt16s;
typedef MO_CM_DECLARE TArray<TInt32>  TInt32s;
typedef MO_CM_DECLARE TArray<TInt64>  TInt64s;
typedef MO_CM_DECLARE TArray<TUint>   TUints;
typedef MO_CM_DECLARE TArray<TUint8>  TUint8s;
typedef MO_CM_DECLARE TArray<TUint16> TUint16s;
typedef MO_CM_DECLARE TArray<TUint32> TUint32s;
typedef MO_CM_DECLARE TArray<TUint64> TUint64s;
typedef MO_CM_DECLARE TArray<TFloat>  TFloats;
typedef MO_CM_DECLARE TArray<TDouble> TDoubles;
#ifdef _UNICODE
typedef MO_CM_DECLARE TChar16s        TChars;
#else
typedef MO_CM_DECLARE TChar8s         TChars;
#endif // _UNICODE

//============================================================
// <T>�䳤�����顣</T>
//
// @tool
// @type T ��������
// @history 091225 MAOCY ����
//============================================================
template <typename T>
class FArray :
      public FObject,
      public MArray<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FArray(){
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FArray(TInt capacity){
      InnerResize(capacity, EFalse, EFalse, EFalse);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FArray(const T* pValues, TInt length){
      Assign(pValues, length);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FArray(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FArray(const MArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FArray(const FArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>�����䳤���顣</T>
   MO_ABSTRACT ~FArray(){
      MO_FREE(this->_pMemory);
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ������ָ�롣</T>
   MO_INLINE void operator=(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const MArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const FArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force){
      // �ͷ��ڴ�
      if(size == 0){
         this->_capacity = 0;
         MO_FREE(this->_pMemory);
         return;
      }
      // ����С
      if(!force){
         if(size <= this->_capacity){
            return;
         }
      }
      // ���ڴ治��ʱ�����¼����ڴ�����
      TInt capacity = size;
      if(extends){
         capacity = RTypes<T>::CalculateTypeCapacity(this->_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      T* pAlloc = MO_TYPES_ALLOC(T, capacity);
      MO_ASSERT(pAlloc);
      RTypes<T>::Clear(pAlloc, capacity);
      // ���������ǰ�ڴ�
      if(NULL != this->_pMemory){
         // �������С�ڴ棬���鳤��
         if(this->_length > capacity){
            this->_length = capacity;
         }
         // ������Ч����
         if(copy && (this->_length > 0)){
            MO_LIB_TYPES_COPY(T, pAlloc, capacity, this->_pMemory, this->_length);
         }
         // �ͷ���ǰ�ڴ�
         MO_FREE(this->_pMemory);
      }
      // �����µ��ڴ�
      this->_pMemory = pAlloc;
      this->_capacity = capacity;
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FArray<TAny*>   FPtrs;
typedef MO_CM_DECLARE FArray<TBool>   FBools;
typedef MO_CM_DECLARE FArray<TByte>   FBytes;
typedef MO_CM_DECLARE FArray<TChar>   FChars;
typedef MO_CM_DECLARE FArray<TChar8>  FChar8s;
typedef MO_CM_DECLARE FArray<TChar16> FChar16s;
typedef MO_CM_DECLARE FArray<TInt>    FInts;
typedef MO_CM_DECLARE FArray<TInt8>   FInt8s;
typedef MO_CM_DECLARE FArray<TInt16>  FInt16s;
typedef MO_CM_DECLARE FArray<TInt32>  FInt32s;
typedef MO_CM_DECLARE FArray<TInt64>  FInt64s;
typedef MO_CM_DECLARE FArray<TUint>   FUints;
typedef MO_CM_DECLARE FArray<TUint8>  FUint8s;
typedef MO_CM_DECLARE FArray<TUint16> FUint16s;
typedef MO_CM_DECLARE FArray<TUint32> FUint32s;
typedef MO_CM_DECLARE FArray<TUint64> FUint64s;
typedef MO_CM_DECLARE FArray<TFloat>  FFloats;
typedef MO_CM_DECLARE FArray<TDouble> FDoubles;
#ifdef _UNICODE
typedef MO_CM_DECLARE FChar16s        FChars;
#else
typedef MO_CM_DECLARE FChar8s         FChars;
#endif // _UNICODE

//============================================================
// <T>�������顣</T>
//
// @tool
// @type T ��������
// @param S ���ݳ���
// @history 091207 MAOCY ����
//============================================================
template <typename T, TInt S>
class TFixArray : public MArray<T>{
protected:
   T _memory[S];
public:
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixArray(){
      this->_pMemory = _memory;
      this->_capacity = S;
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixArray(const TPtrC<T>& ptr){
      this->_pMemory = _memory;
      this->_capacity = S;
      this->Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixArray(const MArray<T>& values){
      this->_pMemory = _memory;
      this->_capacity = S;
      this->Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixArray(const TFixArray<T, S>& values){
      this->_pMemory = _memory;
      this->_capacity = S;
      this->Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>�����������顣</T>
   MO_ABSTRACT ~TFixArray(){
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force){
      MO_ASSERT(size <= S);
   }
public:
   //------------------------------------------------------------
   // <T>�趨��ǰ���ݺ�ָ������ָ����ȡ�</T>
   MO_INLINE void operator=(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>�趨��ǰ���ݺ�ָ������ָ����ȡ�</T>
   MO_INLINE void operator=(const MArray<T>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>�趨��ǰ���ݺ�ָ������ָ����ȡ�</T>
   MO_INLINE void operator=(const TFixArray<T, S>& values){
      Assign(values.MemoryC(), values.Length());
   }
};
//------------------------------------------------------------
#define MO_BCD_TFIXARRAY(C, T) template <TInt S> \
class MO_CM_DECLARE C : public TFixArray<T, S>{ \
public: \
   C(){ \
   } \
   C(const T* pValues, TInt length){ \
      this->Assign(pValues, length); \
   } \
   C(const TPtrC<T>& ptr){ \
      this->Assign(ptr); \
   } \
   C(const C<S>& value){ \
      this->Assign(value); \
   } \
   MO_ABSTRACT ~C(){ \
   } \
public: \
   MO_INLINE void operator=(const TPtrC<T>& ptr){ \
      this->Assign(ptr.MemoryC(), ptr.Length()); \
   } \
   MO_INLINE void operator=(const MArray<T>& values){ \
      this->Assign(values.MemoryC(), values.Length()); \
   } \
   MO_INLINE void operator=(const C<S>& values){ \
      this->Assign(values.MemoryC(), values.Length()); \
   } \
};
//------------------------------------------------------------
MO_BCD_TFIXARRAY(TFixAnys,    TAny*);
MO_BCD_TFIXARRAY(TFixBools,   TBool);
MO_BCD_TFIXARRAY(TFixChar8s,  TChar8);
MO_BCD_TFIXARRAY(TFixChar16s, TChar16);
MO_BCD_TFIXARRAY(TFixInts,    TInt);
MO_BCD_TFIXARRAY(TFixInt16s,  TInt16);
MO_BCD_TFIXARRAY(TFixInt32s,  TInt32);
MO_BCD_TFIXARRAY(TFixInt64s,  TInt64);
MO_BCD_TFIXARRAY(TFixUints,   TUint);
MO_BCD_TFIXARRAY(TFixUint16s, TUint16);
MO_BCD_TFIXARRAY(TFixUint32s, TUint32);
MO_BCD_TFIXARRAY(TFixUint64s, TUint64);
MO_BCD_TFIXARRAY(TFixFloats,  TFloat);
MO_BCD_TFIXARRAY(TFixDoubles, TDouble);
#ifdef _UNICODE
#define TFixChar16s TFixChars;
#else
#define TFixChar8s TFixChars;
#endif // _UNICODE

//============================================================
// <T>�����ֽ�����</T>
//============================================================
template <TInt S>
class TFixBytes : public TFixArray<TByte, S>{
public:
   //------------------------------------------------------------
   // <T>���춨���ֽ�����</T>
   TFixBytes(){
   }
   //------------------------------------------------------------
   // <T>���춨���ֽ�����</T>
   TFixBytes(const TByte* pValues, TInt length){
      this->Append(pValues, length);
   }
   //------------------------------------------------------------
   // <T>���춨���ֽ�����</T>
   TFixBytes(const TPtrC<TByte>& ptr){
      this->Append(ptr);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<TByte>& ptr){
      this->Assign(ptr);
   }
public:
   //------------------------------------------------------------
   // <T>��ʽ����������Ϊʮ�������ַ�����</T>
   MO_INLINE TCharC* Format(TChar* pSource, TSize capacity){
      return RByte::Format(this->_memory, this->_length, pSource, capacity);
   }
   //------------------------------------------------------------
   // <T>����ʮ�������ַ���Ϊ�������ݡ�</T>
   MO_INLINE TInt Parse(TCharC* pSource, TInt length = -1){
      if(length < 0){
         length = RChars::Length(pSource);
      }
      TInt count = RByte::Parse(pSource, length, this->_memory, S);
      this->_length = count;
      return count;
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_ARRAY_H__
