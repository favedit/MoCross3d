#ifndef __MO_CM_VECTOR_H__
#define __MO_CM_VECTOR_H__

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
class TVectorIteratorC{
protected:
   T* _pMemory;
   TInt _count;
   TInt _index;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TVectorIteratorC(){
      MO_CLEAR(_pMemory);
      _count = 0;
      _index = -1;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TVectorIteratorC(const TVectorIteratorC& iterator){
      _pMemory = iterator._pMemory;
      _count = iterator._count;
      _index = iterator._index;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TVectorIteratorC(T* pMemory, TInt count, TInt index = -1){
      _pMemory = pMemory;
      _count = count;
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
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T value){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _count);
      return _pMemory[_index] == value;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      return (_count > 0) ? _index + 1 < _count : EFalse;
   }
   //------------------------------------------------------------
   //<T> �ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      if(_count > 0 && (_index + 1 < _count)){
         _index++;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return (_count > 0) ? _index - 1 >= 0 : EFalse;
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      if(_count > 0 && (_index + 1 < _count)){
         _index--;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& GetC() const{
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _count);
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
class TVectorIterator{
protected:
   T* _pMemory;
   TInt* _pCount;
   TInt _index;
   TBool _changed;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TVectorIterator(){
      MO_CLEAR(_pMemory);
      MO_CLEAR(_pCount);
      _index = -1;
      _changed = EFalse;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TVectorIterator(const TVectorIterator& iterator){
      _pMemory = iterator._pMemory;
      _pCount = iterator._pCount;
      _index = iterator._index;
      _changed = iterator._changed;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TVectorIterator(T* pMemory, TInt* pCount, TInt index = -1){
      _pMemory = pMemory;
      _pCount = pCount;
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
      return (0 == *_pCount);
   }
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T value){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, *_pCount);
      MO_ASSERT(!_changed);
      return _pMemory[_index] == value;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      TInt count = *_pCount;
      if(count > 0){
         if(_changed){
            return _index < count;
         }else{
            return (_index + 1) < count;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   //<T> �ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      TInt count = *_pCount;
      if(count > 0){
         if(_changed){
            _changed = EFalse;
            return _index < count;
         }else if(_index + 1 < count){
            _index++;
            return ETrue;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      TInt count = *_pCount;
      if(count > 0){
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
      TInt count = *_pCount;
      if(count > 0){
         if(_changed){
            _changed = EFalse;
            return _index < count;
         }else if(_index + 1 < count){
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
      MO_ASSERT_RANGE(_index, 0, *_pCount);
      MO_ASSERT(!_changed);
      return _pMemory[_index];
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T& Get(){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, *_pCount);
      MO_ASSERT(!_changed);
      return _pMemory[_index];
   }
public:
   //------------------------------------------------------------
   // <T>ɾ����ǰλ�����ݡ�</T>
   MO_INLINE T Delete(){
      TInt count = *_pCount;
      MO_ASSERT_RANGE(_index, 0, count);
      T value = _pMemory[_index];
      if(_index != count - 1){
         RTypes<T>::Move(_pMemory + _index, _pMemory + _index + 1, count - _index);
      }
      *_pCount = count - 1;
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
class MVector{
public:
   typedef TInt (*HComparer)(const T& source, const T& target);
   typedef TInt (*HComparerObject)(const T& source, const T& target, TAny* pCondition);
   typedef TInt (*HComparerValue)(T source, T target, TAny* pCondition);
   typedef TVectorIteratorC<T> TIteratorC;
   typedef TVectorIterator<T> TIterator;
protected:
   // @attribute ����ָ��
   T* _pMemory;
   // @attribute ���ݳ���
   TInt _count;
   // @attribute ��������
   TInt _capacity;
protected:
   //------------------------------------------------------------
   // <T>����������顣</T>
   MVector(){
      MO_CLEAR(_pMemory);
      _count = 0;
      _capacity = 0;
   }
   //------------------------------------------------------------
   // <T>�����������顣</T>
   MO_ABSTRACT ~MVector(){
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_VIRTUAL void InnerResize(TInt size, TBool copy, TBool extends, TBool force) = 0;
public:
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   MO_INLINE TBool operator==(const MVector<T>& values) const{
      return RTypes<T>::Equals(_pMemory, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   MO_INLINE TBool operator!=(const MVector<T>& values) const{
      return !RTypes<T>::Equals(_pMemory, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ�С��ָ���������������ݡ�
   MO_INLINE TBool operator<(const MVector<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _count, values.MemoryC(), values.Count()) < 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ����ָ���������������ݡ�
   MO_INLINE TBool operator>(const MVector<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _count, values.MemoryC(), values.Count()) > 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ�С�ڵ���ָ���������������ݡ�
   MO_INLINE TBool operator<=(const MVector<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _count, values.MemoryC(), values.Count()) <= 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ���ڵ���ָ���������������ݡ�
   MO_INLINE TBool operator>=(const MVector<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _count, values.MemoryC(), values.Count()) >= 0;
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
      MO_ASSERT_RANGE(index, 0, _count);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>����ָ��λ�õ��������ݡ�</T>
   MO_INLINE T& operator[](TInt index){
      MO_ASSERT_RANGE(index, 0, _count);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>׷��һ�����ݵ���ǰ����β����</T>
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
   MO_INLINE void operator+=(const MVector<T>& values){
      Append(values.MemoryC(), values.Count());
   }   
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>�ж������Ƿ�������</T>
   MO_INLINE TBool IsFull() const{
      return (_count == _capacity);
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
   // <T>������ݸ�����</T>
   MO_INLINE TInt Count() const{
      return _count;
   }
   //------------------------------------------------------------
   // <T>�������������</T>
   MO_INLINE TInt Capacity() const{
      return _capacity;
   }
   //------------------------------------------------------------
   // <T>�������������TODO��������ǰ����ʱ��������</T>
   MO_INLINE TInt Size() const{
      return _capacity;
   }
public:
   //------------------------------------------------------------
   // ��ǰ�������Ƿ��ָ��������ȡ�
   MO_INLINE TBool Equals(const MVector<T>& values) const{
      return RTypes<T>::Equals(_pMemory, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // ����ָ�������Ƿ�����ڵ�ǰ����Ŀ�ʼλ�á�
   MO_INLINE TBool StartsWith(const MVector<T>& values) const{
      return RTypes<T>::StartsWith(_pMemory, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // ����ָ�������Ƿ�����ڵ�ǰ����Ľ���λ�á�
   MO_INLINE TBool EndsWith(const MVector<T>& values) const{
      return RTypes<T>::EndsWith(_pMemory, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // ��ǰ�����к�ָ������Ĵ�С��
   MO_INLINE TInt Compare(const MVector<T>& values) const{
      return RTypes<T>::Compare(_pMemory, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�������Ƿ���ָ�����ݡ�</T>
   MO_INLINE TBool Contains(T value) const{
      TInt result = RTypes<T>::IndexOf(_pMemory, _count, value);
      return (ENotFound != result);
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����в���ָ��ֵ���ֵ�����λ�á�
   MO_INLINE TInt IndexOf(T value) const{
      return RTypes<T>::IndexOf(_pMemory, _count, value);
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����У���ָ��λ��֮�����ָ��ֵ���ֵ�����λ�á�
   MO_INLINE TInt IndexOf(T value, TInt offset) const{
      MO_ASSERT_RANGE(offset, 0, _count);
      TInt result = RTypes<T>::IndexOf(_pMemory + offset, _count - offset, value);
      return (ENotFound == result) ? result : offset + result;
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����в��������ֵ�����λ�á�
   MO_INLINE TInt LastIndexOf(T value) const{
      return RTypes<T>::LastIndexOf(_pMemory, _count, value);
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����в��������ֵ�����λ�á�
   MO_INLINE TInt LastIndexOf(T value, TInt offset) const{
      MO_ASSERT_RANGE(offset, 0, _count);
      return RTypes<T>::LastIndexOf(_pMemory, _count - offset, value);
   }
public:
   //------------------------------------------------------------
   // <T>��ȡֻ����������</T>
   MO_INLINE TIteratorC IteratorC(){
      return TIteratorC(_pMemory, _count);
   }
   //------------------------------------------------------------
   // <T>��ȡֻ����������</T>
   MO_INLINE TIteratorC IteratorC(TInt index){
      return TIteratorC(_pMemory + index, _count - index);
   }
   //------------------------------------------------------------
   // <T>��ȡ��������</T>
   MO_INLINE TIterator Iterator(){
      return TIterator(_pMemory, &_count);
   }
   //------------------------------------------------------------
   // <T>��ȡ��������</T>
   MO_INLINE TIterator Iterator(TInt index){
      return TIterator(_pMemory + index, &_count - index);
   }
   //------------------------------------------------------------
   // <T>��ȡ��һ������</T>
   MO_INLINE T& First(){
      MO_ASSERT(_count > 0);
      return _pMemory[0];
   }
   //------------------------------------------------------------
   // <T>��ȡ���һ������</T>
   MO_INLINE T& Last(){
      MO_ASSERT(_count > 0);
      return _pMemory[_count - 1];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE const T& GetC(TInt index) const{
      MO_ASSERT_RANGE(index, 0, _count);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE const T& GetC(TInt index, const T& value) const{
      if((index >= 0) && (index < _count)){
         return _pMemory[index];
      }
      return value;
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE T& Get(TInt index){
      MO_ASSERT_RANGE(index, 0, _count);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE T& Get(TInt index, T& value){
      if((index >= 0) && (index < _count)){
         return _pMemory[index];
      }
      return value;
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE T Nvl(TInt index, T defaultValue){
      if((index >= 0) && (index < _count)){
         return _pMemory[index];
      }
      return defaultValue;
   }
public:
   //------------------------------------------------------------
   // <T>���ֻ������ָ�롣</T>
   MO_INLINE TPtrC<T> PtrC() const{
      return TPtrC<T>(_pMemory, _count);
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE TPtr<T> Ptr(){
      return TPtr<T>(_pMemory, &_count, _capacity);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����е���߲�����������á�
   MO_INLINE TPtrC<T> LeftPtrC(TInt count) const{
      MO_ASSERT_BETWEEN(count, 0, _count);
      return TPtrC<T>(_pMemory, count);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����е��ұ߲�����������á�
   MO_INLINE TPtrC<T> RightPtrC(TInt count) const{
      MO_ASSERT_BETWEEN(count, 0, _count);
      return TPtrC<T>(_pMemory + (_count - count), count);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĿ�ʼ����β�����á�
   MO_INLINE TPtrC<T> MidPtrC(TInt offset) const{
      MO_ASSERT_BETWEEN(offset, 0, _count);
      return TPtrC<T>(_pMemory + offset, _count - offset);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĲ�����������á�
   MO_INLINE TPtrC<T> MidPtrC(TInt offset, TInt count) const{
      MO_ASSERT_BETWEEN(offset, 0, _count);
      MO_ASSERT_BETWEEN(count, 0, _count - offset);
      return TPtrC<T>(_pMemory + offset, count);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĲ�����������á�
   MO_INLINE TPtrC<T> SubPtrC(TInt begin, TInt end) const{
      MO_ASSERT_BETWEEN(begin, 0, _count);
      MO_ASSERT_BETWEEN(end, 0, _count);
      MO_ASSERT(begin <= end);
      return TPtrC<T>(_pMemory + begin, end - begin);
   }
public:
   //------------------------------------------------------------
   // ����ָ����������ڵ�ǰ���������ֵ�����λ�á�
   MO_INLINE TInt Find(const T* pValue, TInt count) const{
      return RTypes<T>::Find(_pMemory, _count, pValue, count);
   }
   //------------------------------------------------------------
   // ����ָ����������ڵ�ǰ���������ֵ�����λ�á�
   MO_INLINE TInt Find(const MVector<T>& values) const{
      return RTypes<T>::Find(_pMemory, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // ����ָ����������ڵ�ǰ���������ֵ�����λ�á�
   MO_INLINE TInt LastFind(const T* pValue, TInt count) const{
      return RTypes<T>::LastFind(_pMemory, _count, pValue, count);
   }
   //------------------------------------------------------------
   // ����ָ����������ڵ�ǰ���������ֵ�����λ�á�
   MO_INLINE TInt LastFind(const MVector<T>& values) const{
      return RTypes<T>::LastFind(_pMemory, _count, values.MemoryC(), values.Count());
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
   MO_INLINE void Assign(const T* pValues, TInt count){
      // ������
      Clear();
      // ��������
      if((pValues != NULL) && (count >= 0)){
         InnerResize(count, EFalse, EFalse, EFalse);
         if((_pMemory != pValues) && (count > 0)){
            RTypes<T>::Copy(_pMemory, pValues, count);
         }
         _count = count;
      }
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void Assign(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void Assign(const MVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void Assign(const MVector<T>* pValues){
      if(pValues != NULL){
         Assign(pValues->MemoryC(), pValues->Count());
      }
   }
   //------------------------------------------------------------
   // <T>׷��һ������ָ�뵽��ǰ����β����</T>
   MO_INLINE void Append(const T* pValues, TInt count){
      // ��������
      if((pValues != NULL) && (count >= 0)){
         InnerResize(_count + count, ETrue, ETrue, EFalse);
         if((_pMemory != pValues) && (count > 0)){
            RTypes<T>::Copy(_pMemory + _count, pValues, count);
         }
         _count += count;
      }
   }
   //------------------------------------------------------------
   // <T>׷��һ���䳤������󵽵�ǰ����β����</T>
   MO_INLINE void Append(const TPtrC<T>& ptr){
      Append(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>׷��һ���䳤������󵽵�ǰ����β����</T>
   MO_INLINE void Append(const MVector<T>& values){
      Append(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>׷��һ���䳤������󵽵�ǰ����β����</T>
   MO_INLINE void AppendPointer(const MVector<T>* pValues){
      if(pValues != NULL){
         Append(pValues->MemoryC(), pValues->Count());
      }
   }
   //------------------------------------------------------------
   // <T>����һ��������ָ��λ�á�</T>
   MO_INLINE void Insert(TInt index, T value){
      MO_ASSERT_BETWEEN(index, 0, _count);
      InnerResize(_count + 1, ETrue, ETrue, EFalse);
      RTypes<T>::Move(_pMemory + index + 1, _pMemory + index, _count - index);
      _pMemory[index] = value;
      _count++;
   }
   //------------------------------------------------------------
   // <T>����һ������ָ����ָ��λ�á�</T>
   MO_INLINE void Insert(TInt index, const T* pValues, TInt count){
      // ������
      MO_ASSERT_BETWEEN(index, 0, _count);
      MO_ASSERT(pValues);
      MO_ASSERT(count >= 0);
      // ��������
      if((index >= 0) && (index <= _count) && (NULL != pValues) && (count >= 0)){
         InnerResize(_count + count, ETrue, ETrue, EFalse);
         if(_count - index > 0){
            RTypes<T>::Move(_pMemory + index + count, _pMemory + index, _count - index);
         }
         if(count > 0){
            RTypes<T>::Copy(_pMemory + index, pValues, count);
         }
         _count += count;
      }
   }
   //------------------------------------------------------------
   // <T>����һ��������ָ��λ�á�</T>
   MO_INLINE void Insert(TInt index, const MVector<T>& values){
      Insert(index, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>���ײ�����һ�����ݡ�</T>
   MO_INLINE T Shift(){
      MO_ASSERT(_count > 0);
      T value = _pMemory[0];
      _count--;
      RTypes<T>::Move(_pMemory, _pMemory + 1, _count);
      return value;
   }
   //------------------------------------------------------------
   // <T>���ײ�ѹ��һ�����ݡ�</T>
   MO_INLINE void Unshift(const T& value){
      InnerResize(_count + 1, ETrue, ETrue, EFalse);
      RTypes<T>::Move(_pMemory + 1, _pMemory, _count);
      _pMemory[0] = value;
      _count++;
   }
   //------------------------------------------------------------
   // <T>��β������һ�����ݡ�</T>
   MO_INLINE T Pop(){
      MO_ASSERT(_count);
      return _pMemory[--_count];
   }
   //------------------------------------------------------------
   // <T>׷��һ�����ݵ���ǰ����β����</T>
   MO_INLINE void Push(T value){
      InnerResize(_count + 1, ETrue, ETrue, EFalse);
      _pMemory[_count++] = value;
   }
   //------------------------------------------------------------
   // <T>׷��һ��Ψһ���ݵ���ǰ����β����</T>
   MO_INLINE void PushUnique(T value){
      if(!Contains(value)){
         Push(value);
      }
   }
   //------------------------------------------------------------
   // <T>ʹ��ָ��������䵱ǰ���顣</T>
   MO_INLINE void Fill(T value){
      RTypes<T>::Fill(_pMemory, _count, value);
   }
   //------------------------------------------------------------
   // <T>ʹ��ָ�����ݺ�ָ��������䵱ǰ���顣</T>
   MO_INLINE void Fill(T value, TInt count){
      MO_ASSERT_RANGE(count, 0, count)
      RTypes<T>::Fill(_pMemory, count, value);
   }
   //------------------------------------------------------------
   // <T>ʹ��ָ�����ݺ�ָ��������ָ��λ����䵱ǰ���顣</T>
   MO_INLINE void Fill(T value, TInt offset, TInt count){
      MO_ASSERT_RANGE(count, 0, _count - offset)
      RTypes<T>::Fill(_pMemory + offset, count, value);
   }
   //------------------------------------------------------------
   // <T>��Դ�����滻ΪĿ�����ݡ�</T>
   MO_INLINE void Replace(T source, T target){
      RTypes<T>::Replace(_pMemory, _count, source, target);
   }
   //------------------------------------------------------------
   // <T>TODO:��Դ�����滻ΪĿ�����顣</T>
   MO_INLINE void Replace(const MVector<T>& source, const MVector<T>& target){
      TInt sourceCount = source.Count();
      TInt targetCount = target.Count();
      T* pWriter = _pMemory;
      T* pReader = _pMemory;
      if(sourceCount >= target.Count()){
         // �滻Ŀ�����С����Դ����ʱ
         TInt count = 0;
         while(ETrue){
            TInt find = RTypes<T>::Find(pReader, _count, source.MemoryC(), sourceCount);
            if(ENotFound != find){
               RTypes<T>::Move(pWriter, pReader, find);
               RTypes<T>::Copy(pWriter + find, target.MemoryC(), targetCount);
               pReader += find + sourceCount;
               pWriter += find + targetCount;
               count++;
            }else{
               RTypes<T>::Move(pWriter, pReader, _count - (pReader - _pMemory));
            }
         }
         _count += (targetCount - sourceCount) * count;
      }else{
         // ���㳤��
         TInt count = RTypes<T>::Count(_pMemory, _count, source.MemoryC(), source.Count());
         TInt size = _count + (targetCount - sourceCount) * count;
         InnerResize(size, ETrue, ETrue, EFalse);
         // �滻Ŀ�����С����Դ����ʱ
         TInt position = _count;
         while(ETrue){
            TInt find = RTypes<T>::LastFind(pReader, position, source.MemoryC(), sourceCount);
            if(ENotFound != find){
               RTypes<T>::Move(pWriter, pReader, find);
               RTypes<T>::Copy(pWriter + find, target.MemoryC(), targetCount);
               pReader += find + sourceCount;
               pWriter += find + targetCount;
               count++;
            }else{
               RTypes<T>::Move(pWriter, pReader, _count - (pReader - _pMemory));
            }
            position += targetCount - sourceCount;
         }
         _count = size;
      }
   }
   //------------------------------------------------------------
   // <T>������ǰ����������λ�õ�ֵ��</T>
   MO_INLINE void Swap(TInt index1, TInt index2){
      MO_ASSERT_RANGE(index1, 0, _count);
      MO_ASSERT_RANGE(index2, 0, _count);
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
      MO_ASSERT_RANGE(index, 0, _count);
      // ɾ������
      if((index >= 0) && (index < _count)){
         // ��������
         if(NULL != pValue){
            MO_LIB_MEMORY_COPY(pValue, sizeof(T), _pMemory + index, sizeof(T));
         }
         // �����ڴ�
         if((_count - index) > 0){
            RTypes<T>::Move(_pMemory + index, _pMemory + index + 1, _count - index);
         }
         _count--;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>ɾ��ָ��λ����ĳ��ȵ����ݡ�</T>
   // <P>������ȳ�������ɾ��ָ��λ�õ�����λ��֮�������</P>
   MO_INLINE TBool DeleteSegment(TInt offset, TInt count){
      MO_ASSERT_RANGE(offset, 0, _count);
      MO_ASSERT_RANGE(count, 0, _count - offset);
      if((offset >= 0) && (offset < _count) && (count >= 0) && (count < (_count - offset))){
         TInt last = _count - offset - count;
         if(last > 0){
            TInt copy = MO_LIB_MIN(last, count);
            RTypes<T>::Move(_pMemory + offset, _pMemory + offset + count, copy);
         }
         _count -= count;
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
      while(++n < _count){
         if(_pMemory[n] != value){
            _pMemory[position++] = _pMemory[n];
         }
      }
      _count = position;
   }
   //------------------------------------------------------------
   // <T>����ָ������λ�õ����ݡ�</T>
   MO_INLINE void Set(TInt index, T value){
      MO_ASSERT_RANGE(index, 0, _count);
      _pMemory[index] = value;
   }
   //------------------------------------------------------------
   // <T>����ָ������λ�õ����ݣ�λ�ò���ʱ�������С��</T>
   MO_INLINE void ExtendSet(TInt index, T value){
      if(index >= _count){
         InnerResize(index + 1, ETrue, ETrue, EFalse);
         _count = index + 1;
      }
      _pMemory[index] = value;
   }
   //------------------------------------------------------------
   // <T>�������ݸ�������������ǰ���ݡ�</T>
   MO_INLINE void ForceCount(TInt count){
      InnerResize(count, EFalse, EFalse, EFalse);
      _count = count;
   }
   //------------------------------------------------------------
   // <T>�������ݸ�����</T>
   // <P>���ȱ�С�󣬶�������ݽ���ʧ������洢����ָ�룬һ��Ҫ�Լ����ͷŶ���Ķ��������С���ȡ�
   MO_INLINE void SetCount(TInt count){
      InnerResize(count, ETrue, EFalse, EFalse);
      _count = count;
   }
   //------------------------------------------------------------
   // <T>�������ݳ��ȣ���ָ�����ȵĲ��ֵ���������Ϊָ�����ݡ�</T>
   MO_INLINE void SetCount(TInt count, T value){
      InnerResize(count, EFalse, EFalse, EFalse);
      _count = count;
      for(TInt n = 0; n < count; n++){
         _pMemory[n] = value;
      }
   }
   //------------------------------------------------------------
   // <T>�������ݳ��ȡ�</T>
   // <P>���ȱ�С�󣬶�������ݽ���ʧ������洢����ָ�룬һ��Ҫ�Լ����ͷŶ���Ķ��������С���ȡ�
   MO_INLINE void EnsureCount(TInt count){
      InnerResize(count, ETrue, EFalse, EFalse);
      this->_count = count;
   }
   //------------------------------------------------------------
   // <T>ʹ���������Լ��϶����������</T>
   MO_INLINE void Sort(HComparer hComparer){
      MO_ASSERT(hComparer);
      if((NULL != _pMemory) && (_count > 1)){
         RTypes<T>::SortQuick(_pMemory, _count, hComparer);
      }
   }
   //------------------------------------------------------------
   // <T>ʹ���������Լ��϶����������</T>
   MO_INLINE void SortObject(HComparerObject hComparer, TAny* pCondition = NULL){
      MO_ASSERT(hComparer);
      if((NULL != _pMemory) && (_count > 1)){
         RTypes<T>::SortQuickObject(_pMemory, _count, hComparer, pCondition);
      }
   }
   //------------------------------------------------------------
   // <T>ʹ���������Լ��϶����������</T>
   MO_INLINE void SortValue(HComparerValue hComparer, TAny* pCondition = NULL){
      MO_ASSERT(hComparer);
      if((NULL != _pMemory) && (_count > 1)){
         RTypes<T>::SortQuickValue(_pMemory, _count, hComparer, pCondition);
      }
   }
   //------------------------------------------------------------
   // <T>����������ݡ�</T>
   // <P>ע�Ȿ���������ݲ����κδ�������洢ָ�룬һ��Ҫ���Լ��ͷš�ֻ�ǽ�������Ϊ�գ��������·����ݡ�</P>
   MO_INLINE void Clear(){
      _count = 0;
   }
   //------------------------------------------------------------
   // <T>�ͷ��������ݡ�</T>
   MO_INLINE void Free(){
      InnerResize(0, EFalse, EFalse, EFalse);
      _count = 0;
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
class TVector : public MVector<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TVector(){
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TVector(TInt capacity){
      InnerResize(capacity, EFalse, EFalse, EFalse);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TVector(const T* pValues, TInt count){
      Assign(pValues, count);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TVector(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TVector(const MVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   TVector(const TVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�����䳤���顣</T>
   MO_ABSTRACT ~TVector(){
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
   MO_INLINE void operator=(const MVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ��������ݡ�</T>
   MO_INLINE void operator=(const TVector& values){
      Assign(values.MemoryC(), values.Count());
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
         capacity = RTypes<T>::CalculateObjectCapacity(this->_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      T* pAlloc = MO_TYPES_ALLOC(T, capacity);
      MO_ASSERT(pAlloc);
      RTypes<T>::Clear(pAlloc, capacity);
      // ���������ǰ�ڴ�
      if(NULL != this->_pMemory){
         // �������С�ڴ棬���鳤��
         if(this->_count > capacity){
            this->_count = capacity;
         }
         // ������Ч����
         if(copy && (this->_count > 0)){
            MO_LIB_TYPES_COPY(T, pAlloc, capacity, this->_pMemory, this->_count);
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
// <T>�䳤�����顣</T>
//
// @tool
// @type T ��������
// @history 091225 MAOCY ����
//============================================================
template <typename T>
class FVector :
      public FObject,
      public MVector<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FVector(){
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FVector(TInt capacity){
      InnerResize(capacity, EFalse, EFalse, EFalse);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FVector(const T* pValues, TInt count){
      Assign(pValues, count);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FVector(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FVector(const MVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FVector(const FVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�����䳤���顣</T>
   MO_ABSTRACT ~FVector(){
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
   MO_INLINE void operator=(const MVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const FVector<T>& values){
      Assign(values.MemoryC(), values.Count());
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
         capacity = RTypes<T>::CalculateObjectCapacity(this->_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      T* pAlloc = MO_TYPES_ALLOC(T, capacity);
      MO_ASSERT(pAlloc);
      RTypes<T>::Clear(pAlloc, capacity);
      // ���������ǰ�ڴ�
      if(NULL != this->_pMemory){
         // �������С�ڴ棬���鳤��
         if(this->_count > capacity){
            this->_count = capacity;
         }
         // ������Ч����
         if(copy && (this->_count > 0)){
            MO_LIB_TYPES_COPY(T, pAlloc, capacity, this->_pMemory, this->_count);
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
// <T>�䳤�����顣</T>
//
// @tool
// @type T ��������
// @history 091225 MAOCY ����
//============================================================
template <typename T>
class FFreeVector :
      public FFree,
      public MVector<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FFreeVector(){
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FFreeVector(TInt capacity){
      InnerResize(capacity, EFalse, EFalse, EFalse);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FFreeVector(const T* pValues, TInt count){
      Assign(pValues, count);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FFreeVector(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FFreeVector(const MVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FFreeVector(const FVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�����䳤���顣</T>
   MO_ABSTRACT ~FFreeVector(){
      MO_MEM_FREE(this->_pMemory);
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ������ָ�롣</T>
   MO_INLINE void operator=(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const MVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const FFreeVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force){
      // �ͷ��ڴ�
      if(size == 0){
         this->_capacity = 0;
         MO_MEM_FREE(this->_pMemory);
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
         capacity = RTypes<T>::CalculateObjectCapacity(this->_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      T* pAlloc = (T*)MO_MEM_ALLOC(sizeof(T) * capacity);
      MO_ASSERT(pAlloc);
      RTypes<T>::Clear(pAlloc, capacity);
      // ���������ǰ�ڴ�
      if(NULL != this->_pMemory){
         // �������С�ڴ棬���鳤��
         if(this->_count > capacity){
            this->_count = capacity;
         }
         // ������Ч����
         if(copy && (this->_count > 0)){
            MO_LIB_TYPES_COPY(T, pAlloc, capacity, this->_pMemory, this->_count);
         }
         // �ͷ���ǰ�ڴ�
         MO_MEM_FREE(this->_pMemory);
      }
      // �����µ��ڴ�
      this->_pMemory = pAlloc;
      this->_capacity = capacity;
   }
};

//============================================================
// <T>�������顣</T>
//
// @tool
// @type T ��������
// @param S ���ݳ���
// @history 091207 MAOCY ����
//============================================================
template <typename T, TInt S>
class TFixVector : public MVector<T>{
protected:
   T _memory[S];
public:
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixVector(){
      InnerInitialize();
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixVector(const TPtrC<T>& ptr){
      InnerInitialize();
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixVector(const MVector<T>& values){
      InnerInitialize();
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixVector(const TFixVector<T, S>& values){
      InnerInitialize();
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�����������顣</T>
   MO_ABSTRACT ~TFixVector(){
   }
protected:
   //------------------------------------------------------------
   // <T>��ʼ���ڴ档</T>
   MO_INLINE void InnerInitialize(){
      this->_pMemory = _memory;
      this->_capacity = S;
   }
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
   MO_INLINE void operator=(const MVector<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�趨��ǰ���ݺ�ָ������ָ����ȡ�</T>
   MO_INLINE void operator=(const TFixVector<T, S>& values){
      Assign(values.MemoryC(), values.Count());
   }
};

//============================================================
// <T>�������顣</T>
//
// @tool
// @type T ��������
// @param S ���ݳ���
// @history 091207 MAOCY ����
//============================================================
template <typename T, TInt S>
class TFixPtrVector : public MVector<T>{
protected:
   T _memory[S];
   T* _pPtrs[S];
public:
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixPtrVector(){
      this->InnerInitialize();
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixPtrVector(const TPtrC<T>& ptr){
      this->InnerInitialize();
      this->Append(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixPtrVector(const MVector<T>& values){
      this->InnerInitialize();
      this->Append(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   TFixPtrVector(const TFixPtrVector<T, S>& values){
      this->InnerInitialize();
      this->Append(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�����������顣</T>
   MO_ABSTRACT ~TFixPtrVector(){
   }
protected:
   //------------------------------------------------------------
   // <T>��ʼ���ڴ档</T>
   MO_INLINE void InnerInitialize(){
      this->_pMemory = _memory;
      this->_count = 0;
      this->_capacity = S;
      // ����ָ��
      for(TInt n = 0; n < S; n++){
         _pPtrs[n] = &_memory[n];
      }
   }
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
   MO_INLINE void operator=(const TFixPtrVector<T, S>& values){
      Assign(values.MemoryC(), values.Count());
   }
public:
   //------------------------------------------------------------
   // <T>�趨��ǰ���ݺ�ָ������ָ����ȡ�</T>
   MO_INLINE T** Ptrs(){
      return _pPtrs;
   }
};

//============================================================
// <T>ʵ�����ϡ�</T>
//
// @history 130401 MAOCY ����
//============================================================
template <typename T>
class MInstancedVector{
protected:
   TInt _count;
   T* _pItems;
public:
   //------------------------------------------------------------
   // <T>����ʵ�����ϡ�</T>
   MInstancedVector(){
      _count = 0;
      MO_CLEAR(_pItems);
   }
   //------------------------------------------------------------
   // <T>����ʵ�����ϡ�</T>
   MO_ABSTRACT ~MInstancedVector(){
      Release();
   }
public:
   //------------------------------------------------------------
   // <T>ǿ��������</T>
   MO_INLINE void ForceCount(TInt count){
      MO_ASSERT(count > 0);
      // �ͷž��ڴ�
      MO_FREE(_pItems);
      // �ռ��ڴ�
      _pItems = MO_TYPES_ALLOC(T, count);
      MO_ASSERT(_pItems);
      RTypes<T>::Clear(_pItems, count);
      // ��ʼ������
      for(TInt n = 0; n < count; n++){
         T& item = _pItems[n];
         new(&item)T();
      }
      // ��������
      _count = count;
   }
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>����������ö���</T>
   MO_INLINE T* Find(TInt index){
      if((index >= 0) && (index < _count)){
         T& item = _pItems[index];
         return &item;
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����������ö���</T>
   MO_INLINE T* Get(TInt index){
      MO_ASSERT_RANGE(index, 0, _count);
      T& item = _pItems[index];
      return &item;
   }
public:
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�������Ƿ���ָ�����ݡ�</T>
   MO_INLINE TBool Contains(T* pItem) const{
      for(TInt n = 0; n < _count; n++){
         T& item = _pItems[n];
         if(&item == pItem){
            return ETrue;
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ͷ����ж���</T>
   MO_INLINE void Release(){
      // �ͷ����ж���
      for(TInt n = 0; n < _count; n++){
         T& item = _pItems[n];
         item.~T();
      }
      MO_FREE(_pItems);
      // ��������
      _count = 0;
   }
public:
   //------------------------------------------------------------
   // <T>��ʾ������Ϣ��</T>
   MO_INLINE void Dump(){
      TInt itemCapacity = sizeof(T);
      TInt capacity = itemCapacity * _count;
      MO_DEBUG("Instanced vector. (capacity=%d, item_capacity=%d, entry_size=%d)",
            capacity, itemCapacity, _count);
   }
};

//============================================================
// <T>ʵ�����ϡ�</T>
//
// @tool
//============================================================
template <typename T>
class TInstancedVector :
      public MInstancedVector<T>{
public:
   //------------------------------------------------------------
   // <T>����ʵ�����ϡ�</T>
   TInstancedVector(){
   }
   //------------------------------------------------------------
   // <T>����ʵ�����ϡ�</T>
   MO_ABSTRACT ~TInstancedVector(){
   }
};

//============================================================
// <T>ʵ�����ϡ�</T>
//
// @class
//============================================================
template <typename T>
class FInstancedVector :
      public FObject,
      public MInstancedVector<T>{
public:
   //------------------------------------------------------------
   // <T>����ʵ�����ϡ�</T>
   FInstancedVector(){
   }
   //------------------------------------------------------------
   // <T>����ʵ�����ϡ�</T>
   MO_ABSTRACT ~FInstancedVector(){
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_VECTOR_H__
