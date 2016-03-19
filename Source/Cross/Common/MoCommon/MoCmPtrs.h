#ifndef __MO_CM_PTRS_H__
#define __MO_CM_PTRS_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

#ifndef __MO_CM_CLASSBASE_H__
#include "MoCmClassBase.h"
#endif // __MO_CM_CLASSBASE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>ֻ���ڵ��������</T>
//
// @tool
// @history 140329 MAOCY ����
//============================================================
template <typename T>
class GPtrIteratorC{
protected:
   GPtr<T>* _pPtrs;
   TInt _count;
   TInt _index;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrIteratorC(){
      MO_CLEAR(_pPtrs);
      _count = 0;
      _index = -1;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrIteratorC(const GPtrIteratorC& iterator){
      _pPtrs = iterator._pPtrs;
      _count = iterator._count;
      _index = iterator._index;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrIteratorC(GPtr<T>* pMemory, TInt count, TInt index = -1){
      _pPtrs = pMemory;
      _count = count;
      _index = index;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator *() const{
      return Get();
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator->() const{
      return Get();
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T* pValue){
      MO_ASSERT(_pPtrs);
      MO_ASSERT_RANGE(_index, 0, _count);
      GPtr<T>& ptr = _pPtrs[_index];
      return (ptr == pValue);
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
   MO_INLINE T* Get() const{
      MO_ASSERT(_pPtrs);
      MO_ASSERT_RANGE(_index, 0, _count);
      return (T*)_pPtrs[_index];
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
class GPtrIterator{
protected:
   GPtr<T>* _pPtrs;
   TInt* _pCount;
   TInt _index;
   TBool _changed;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrIterator(){
      MO_CLEAR(_pPtrs);
      MO_CLEAR(_pCount);
      _index = -1;
      _changed = EFalse;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrIterator(const GPtrIterator& iterator){
      _pPtrs = iterator._pPtrs;
      _pCount = iterator._pCount;
      _index = iterator._index;
      _changed = iterator._changed;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   GPtrIterator(GPtr<T>* pMemory, TInt* pCount, TInt index = -1){
      _pPtrs = pMemory;
      _pCount = pCount;
      _index = index;
      _changed = EFalse;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator *(){
      return Get();
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T* operator->(){
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
   MO_INLINE TBool Equals(T* pValue){
      MO_ASSERT(_pPtrs);
      MO_ASSERT_RANGE(_index, 0, *_pCount);
      MO_ASSERT(!_changed);
      GPtr<T> ptr = _pPtrs[_index];
      return (ptr == pValue);
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
   MO_INLINE T* Get(){
      MO_ASSERT(_pPtrs);
      MO_ASSERT_RANGE(_index, 0, *_pCount);
      MO_ASSERT(!_changed);
      return (T*)_pPtrs[_index];
   }
public:
   //------------------------------------------------------------
   // <T>ɾ����ǰλ�����ݡ�</T>
   MO_INLINE T* Delete(){
      TInt count = *_pCount;
      MO_ASSERT_RANGE(_index, 0, count);
      GPtr<T>& ptr = _pPtrs[_index];
      T* pValue = ptr.Flip();
      if(_index != count - 1){
         RTypes< GPtr<T> >::Move(_pPtrs + _index, _pPtrs + _index + 1, count - _index);
      }
      *_pCount = count - 1;
      _changed = ETrue;
      return pValue;
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
class MPtrs{
public:
   typedef GPtrIteratorC<T> TIteratorC;
   typedef GPtrIterator<T> TIterator;
protected:
   // @attribute ����ָ��
   GPtr<T>* _pPtrs;
   // @attribute ���ݳ���
   TInt _count;
   // @attribute ��������
   TInt _capacity;
protected:
   //------------------------------------------------------------
   // <T>����������顣</T>
   MPtrs(){
      MO_CLEAR(_pPtrs);
      _count = 0;
      _capacity = 0;
   }
   //------------------------------------------------------------
   // <T>�����������顣</T>
   MO_ABSTRACT ~MPtrs(){
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_VIRTUAL void InnerResize(TInt size, TBool copy, TBool extends, TBool force) = 0;
public:
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   MO_INLINE TBool operator==(const MPtrs<T>& values) const{
      return RTypes<T>::Equals(_pPtrs, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   MO_INLINE TBool operator!=(const MPtrs<T>& values) const{
      return !RTypes<T>::Equals(_pPtrs, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ�С��ָ���������������ݡ�
   MO_INLINE TBool operator<(const MPtrs<T>& values) const{
      return RTypes<T>::Compare(_pPtrs, _count, values.MemoryC(), values.Count()) < 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ����ָ���������������ݡ�
   MO_INLINE TBool operator>(const MPtrs<T>& values) const{
      return RTypes<T>::Compare(_pPtrs, _count, values.MemoryC(), values.Count()) > 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ�С�ڵ���ָ���������������ݡ�
   MO_INLINE TBool operator<=(const MPtrs<T>& values) const{
      return RTypes<T>::Compare(_pPtrs, _count, values.MemoryC(), values.Count()) <= 0;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ���������������Ƿ���ڵ���ָ���������������ݡ�
   MO_INLINE TBool operator>=(const MPtrs<T>& values) const{
      return RTypes<T>::Compare(_pPtrs, _count, values.MemoryC(), values.Count()) >= 0;
   }
   //------------------------------------------------------------
   // <T>���ֻ���������ݡ�</T>
   MO_INLINE operator const GPtr<T>*() const{
      return _pPtrs;
   }
   //------------------------------------------------------------
   // <T>�����������</T>
   MO_INLINE operator GPtr<T>*(){
      return _pPtrs;
   }
   //------------------------------------------------------------
   // <T>���ָ��λ�õ�ֻ���������ݡ�</T>
   MO_INLINE const T* operator[](TInt index) const{
      MO_ASSERT(_pPtrs);
      MO_ASSERT_RANGE(index, 0, _count);
      return (T*)_pPtrs[index];
   }
   //------------------------------------------------------------
   // <T>����ָ��λ�õ��������ݡ�</T>
   MO_INLINE T* operator[](TInt index){
      MO_ASSERT_RANGE(index, 0, _count);
      return (T*)_pPtrs[index];
   }
   //------------------------------------------------------------
   // <T>׷��һ�����ݵ���ǰ����β����</T>
   MO_INLINE void operator+=(T* pValue){
      Push(pValue);
   }
   //------------------------------------------------------------
   // <T>׷��һ�����鵽��ǰ����β����</T>
   MO_INLINE void operator+=(const MPtrs<T>& values){
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
   MO_INLINE const GPtr<T>* MemoryC() const{
      return _pPtrs;
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE GPtr<T>* Memory(){
      return _pPtrs;
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
   MO_INLINE TBool Equals(const MPtrs<T>& values) const{
      return RTypes<T>::Equals(_pPtrs, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // ����ָ�������Ƿ�����ڵ�ǰ����Ŀ�ʼλ�á�
   MO_INLINE TBool StartsWith(const MPtrs<T>& values) const{
      return RTypes<T>::StartsWith(_pPtrs, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // ����ָ�������Ƿ�����ڵ�ǰ����Ľ���λ�á�
   MO_INLINE TBool EndsWith(const MPtrs<T>& values) const{
      return RTypes<T>::EndsWith(_pPtrs, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // ��ǰ�����к�ָ������Ĵ�С��
   MO_INLINE TInt Compare(const MPtrs<T>& values) const{
      return RTypes<T>::Compare(_pPtrs, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�ӵ�ǰ�������Ƿ���ָ�����ݡ�</T>
   MO_INLINE TBool Contains(T* pValue) const{
      TInt result = IndexOf(pValue);
      return (result != ENotFound);
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����в���ָ��ֵ���ֵ�����λ�á�
   MO_INLINE TInt IndexOf(T* pValue) const{
      for(TInt n = 0; n < _count; n++){
         GPtr<T>& ptr = _pPtrs[n];
         if(ptr.Get() == pValue){
            return n;
         }
      }
      return ENotFound;
   }
   //------------------------------------------------------------
   // �ӵ�ǰ�����в��������ֵ�����λ�á�
   MO_INLINE TInt LastIndexOf(T* pValue) const{
      for(TInt n = _count - 1; n >= 0; n--){
         GPtr<T>& ptr = _pPtrs[n];
         if(ptr.Get() == pValue){
            return n;
         }
      }
      return ENotFound;
   }
public:
   //------------------------------------------------------------
   // <T>��ȡֻ����������</T>
   MO_INLINE TIteratorC IteratorC(){
      return TIteratorC(_pPtrs, _count);
   }
   //------------------------------------------------------------
   // <T>��ȡֻ����������</T>
   MO_INLINE TIteratorC IteratorC(TInt index){
      return TIteratorC(_pPtrs + index, _count - index);
   }
   //------------------------------------------------------------
   // <T>��ȡ��������</T>
   MO_INLINE TIterator Iterator(){
      return TIterator(_pPtrs, &_count);
   }
   //------------------------------------------------------------
   // <T>��ȡ��������</T>
   MO_INLINE TIterator Iterator(TInt index){
      return TIterator(_pPtrs + index, &_count - index);
   }
   //------------------------------------------------------------
   // <T>��ȡ��һ������</T>
   MO_INLINE T* First(){
      MO_ASSERT(_count > 0);
      return (T*)_pPtrs[0];
   }
   //------------------------------------------------------------
   // <T>��ȡ���һ������</T>
   MO_INLINE T* Last(){
      MO_ASSERT(_count > 0);
      return (T*)_pPtrs[_count - 1];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE const T* GetC(TInt index) const{
      MO_ASSERT_RANGE(index, 0, _count);
      return (T*)_pPtrs[index];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE const T* GetC(TInt index, const T* pValue) const{
      if((index >= 0) && (index < _count)){
         return (T*)_pPtrs[index];
      }
      return pValue;
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE T* Get(TInt index){
      MO_ASSERT_RANGE(index, 0, _count);
      return (T*)_pPtrs[index];
   }
   //------------------------------------------------------------
   // <T>��ȡָ������λ�õ����ݡ�</T>
   MO_INLINE T* Get(TInt index, T* pValue){
      if((index >= 0) && (index < _count)){
         return (T*)_pPtrs[index];
      }
      return pValue;
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰ�����е���߲�����������á�
   MO_INLINE TPtrC< GPtr<T> > LeftPtrC(TInt count) const{
      MO_ASSERT_BETWEEN(count, 0, _count);
      return TPtrC< GPtr<T> >(_pPtrs, count);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����е��ұ߲�����������á�
   MO_INLINE TPtrC< GPtr<T> > RightPtrC(TInt count) const{
      MO_ASSERT_BETWEEN(count, 0, _count);
      return TPtrC< GPtr<T> >(_pPtrs + (_count - count), count);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĿ�ʼ����β�����á�
   MO_INLINE TPtrC< GPtr<T> > MidPtrC(TInt offset) const{
      MO_ASSERT_BETWEEN(offset, 0, _count);
      return TPtrC< GPtr<T> >(_pPtrs + offset, _count - offset);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĲ�����������á�
   MO_INLINE TPtrC< GPtr<T> > MidPtrC(TInt offset, TInt count) const{
      MO_ASSERT_BETWEEN(offset, 0, _count);
      MO_ASSERT_BETWEEN(count, 0, _count - offset);
      return TPtrC< GPtr<T> >(_pPtrs + offset, count);
   }
   //------------------------------------------------------------
   // ��õ�ǰ�����еĲ�����������á�
   MO_INLINE TPtrC< GPtr<T> > SubPtrC(TInt begin, TInt end) const{
      MO_ASSERT_BETWEEN(begin, 0, _count);
      MO_ASSERT_BETWEEN(end, 0, _count);
      MO_ASSERT(begin <= end);
      return TPtrC< GPtr<T> >(_pPtrs + begin, end - begin);
   }
public:
   //------------------------------------------------------------
   // ����ָ����������ڵ�ǰ���������ֵ�����λ�á�
   MO_INLINE TInt Find(const T* pValue, TInt count) const{
      return RTypes<T>::Find(_pPtrs, _count, pValue, count);
   }
   //------------------------------------------------------------
   // ����ָ����������ڵ�ǰ���������ֵ�����λ�á�
   MO_INLINE TInt Find(const MPtrs<T>& values) const{
      return RTypes<T>::Find(_pPtrs, _count, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // ����ָ����������ڵ�ǰ���������ֵ�����λ�á�
   MO_INLINE TInt LastFind(const T* pValue, TInt count) const{
      return RTypes<T>::LastFind(_pPtrs, _count, pValue, count);
   }
   //------------------------------------------------------------
   // ����ָ����������ڵ�ǰ���������ֵ�����λ�á�
   MO_INLINE TInt LastFind(const MPtrs<T>& values) const{
      return RTypes<T>::LastFind(_pPtrs, _count, values.MemoryC(), values.Count());
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
   MO_INLINE void Assign(const GPtr<T>* pValues, TInt count){
      // ������
      MO_ASSERT(pValues);
      MO_ASSERT(count >= 0);
      // ��������
      if((NULL != pValues) && (count >= 0)){
         InnerResize(count, EFalse, EFalse, EFalse);
         if((_pPtrs != pValues) && (count > 0)){
            RTypes< GPtr<T> >::Copy(_pPtrs, pValues, count);
         }
         _count = count;
      }
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void Assign(const TPtrC< GPtr<T> >& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void Assign(const MPtrs<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����һ������ָ�뵽��ǰ���顣</T>
   MO_INLINE void AssignPointer(const MPtrs<T>* pValues){
      MO_ASSERT(pValues);
      Assign(pValues->MemoryC(), pValues->Count());
   }
   //------------------------------------------------------------
   // <T>׷��һ������ָ�뵽��ǰ����β����</T>
   MO_INLINE void Append(const T* pValues, TInt count){
      // ������
      MO_ASSERT(pValues);
      MO_ASSERT(count >= 0);
      // ��������
      if((NULL != pValues) && (count >= 0)){
         InnerResize(_count + count, ETrue, ETrue, EFalse);
         if((_pPtrs != pValues) && (count > 0)){
            RTypes<T>::Copy(_pPtrs + _count, pValues, count);
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
   MO_INLINE void Append(const MPtrs<T>& values){
      Append(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>׷��һ���䳤������󵽵�ǰ����β����</T>
   MO_INLINE void Append(const MPtrs<T>* pValues){
      MO_ASSERT(pValues);
      Append(pValues->MemoryC(), pValues->Count());
   }
   //------------------------------------------------------------
   // <T>����һ��������ָ��λ�á�</T>
   MO_INLINE void Insert(TInt index, T* pValue){
      MO_ASSERT_BETWEEN(index, 0, _count);
      InnerResize(_count + 1, ETrue, ETrue, EFalse);
      RTypes<T>::Move(_pPtrs + index + 1, _pPtrs + index, _count - index);
      _pPtrs[index] = pValue;
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
            RTypes<T>::Move(_pPtrs + index + count, _pPtrs + index, _count - index);
         }
         if(count > 0){
            RTypes<T>::Copy(_pPtrs + index, pValues, count);
         }
         _count += count;
      }
   }
   //------------------------------------------------------------
   // <T>����һ��������ָ��λ�á�</T>
   MO_INLINE void Insert(TInt index, const MPtrs<T>& values){
      Insert(index, values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>���ײ�����һ�����ݡ�</T>
   MO_INLINE T* Shift(){
      MO_ASSERT(_count > 0);
      T value = _pPtrs[0];
      _count--;
      RTypes<T>::Move(_pPtrs, _pPtrs + 1, _count);
      return value;
   }
   //------------------------------------------------------------
   // <T>���ײ�ѹ��һ�����ݡ�</T>
   MO_INLINE void Unshift(T* pValue){
      InnerResize(_count + 1, ETrue, ETrue, EFalse);
      RTypes< GPtr<T> >::Move(_pPtrs + 1, _pPtrs, _count);
      _pPtrs[0] = pValue;
      _count++;
   }
   //------------------------------------------------------------
   // <T>��β������һ�����ݡ�</T>
   MO_INLINE T* Pop(){
      MO_ASSERT(_count);
      return _pPtrs[--_count];
   }
   //------------------------------------------------------------
   // <T>׷��һ�����ݵ���ǰ����β����</T>
   MO_INLINE void Push(T* value){
      InnerResize(_count + 1, ETrue, ETrue, EFalse);
      _pPtrs[_count++] = value;
   }
   //------------------------------------------------------------
   // <T>׷��һ��Ψһ���ݵ���ǰ����β����</T>
   MO_INLINE void PushUnique(T* value){
      if(!Contains(value)){
         Push(value);
      }
   }
   //------------------------------------------------------------
   // <T>��Դ�����滻ΪĿ�����ݡ�</T>
   MO_INLINE void Replace(T* pSource, T* pTarget){
      //RTypes<T>::Replace(_pPtrs, _count, source, target);
   }
   //------------------------------------------------------------
   // <T>������ǰ����������λ�õ�ֵ��</T>
   MO_INLINE void Swap(TInt index1, TInt index2){
      MO_ASSERT_RANGE(index1, 0, _count);
      MO_ASSERT_RANGE(index2, 0, _count);
      if(index1 != index2){
         T* pValue = _pPtrs[index1];
         _pPtrs[index1] = _pPtrs[index2];
         _pPtrs[index2] = pValue;
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
            MO_LIB_MEMORY_COPY(pValue, sizeof(T), _pPtrs + index, sizeof(T));
         }
         // �����ڴ�
         if((_count - index) > 0){
            RTypes< GPtr<T> >::Move(_pPtrs + index, _pPtrs + index + 1, _count - index);
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
            RTypes< GPtr<T> >::Move(_pPtrs + offset, _pPtrs + offset + count, copy);
         }
         _count -= count;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�Ƴ�ָ�����ݡ�</T>
   // <P>���ܻ��Ƴ������ͬ�����ݡ�</P>
   MO_INLINE void Remove(T* pValue){
      // ������ǰ��
      TInt n = -1;
      TInt position = 0;
      while(++n < _count){
         if(_pPtrs[n] != pValue){
            _pPtrs[position++] = _pPtrs[n];
         }
      }
      // ���β������
      for(TInt n = position; n < _count; n++){
         _pPtrs[n] = NULL;
      }
      // ���ø���
      _count = position;
   }
   //------------------------------------------------------------
   // <T>����ָ������λ�õ����ݡ�</T>
   MO_INLINE void Set(TInt index, T* pValue){
      MO_ASSERT_RANGE(index, 0, _count);
      _pPtrs[index] = pValue;
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
   // <T>�������ݳ��ȡ�</T>
   // <P>���ȱ�С�󣬶�������ݽ���ʧ������洢����ָ�룬һ��Ҫ�Լ����ͷŶ���Ķ��������С���ȡ�
   MO_INLINE void EnsureCount(TInt count){
      InnerResize(count, ETrue, EFalse, EFalse);
      _count = count;
   }
   //------------------------------------------------------------
   // <T>����������ݡ�</T>
   MO_INLINE void Clear(){
      if((_pPtrs != NULL) && (_count > 0)){
         for(TInt n = 0; n < _count; n++){
            GPtr<T>& ptr = _pPtrs[n];
            ptr = NULL;
         }
      }
      _count = 0;
   }
   //------------------------------------------------------------
   // <T>�ͷ��������ݡ�</T>
   MO_INLINE void Free(){
      Clear();
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
class GPtrs : public MPtrs<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   GPtrs(){
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   GPtrs(TInt capacity){
      InnerResize(capacity, EFalse, EFalse, EFalse);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   GPtrs(const T* pValues, TInt count){
      Assign(pValues, count);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   GPtrs(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   GPtrs(const MPtrs<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   GPtrs(const GPtrs<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�����䳤���顣</T>
   MO_ABSTRACT ~GPtrs(){
      this->Clear();
      MO_FREE(this->_pPtrs);
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ��������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<T>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ��������ݡ�</T>
   MO_INLINE void operator=(const MPtrs<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ��������ݡ�</T>
   MO_INLINE void operator=(const GPtrs& values){
      Assign(values.MemoryC(), values.Count());
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force){
      // �ͷ��ڴ�
      if(size == 0){
         this->_capacity = 0;
         MO_FREE(this->_pPtrs);
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
         capacity = RTypes< GPtr<T> >::CalculateObjectCapacity(this->_capacity, size);
      }
      // ����ռ����ɹ����򲻽��и������ݴ���
      GPtr<T>* pAlloc = MO_TYPES_ALLOC(GPtr<T>, capacity);
      MO_ASSERT(pAlloc);
      RTypes< GPtr<T> >::Clear(pAlloc, capacity);
      // ���������ǰ�ڴ�
      if(NULL != this->_pPtrs){
         // �������С�ڴ棬���鳤��
         if(this->_count > capacity){
            this->_count = capacity;
         }
         // ������Ч����
         if(copy && (this->_count > 0)){
            MO_LIB_TYPES_COPY(GPtr<T>, pAlloc, capacity, this->_pPtrs, this->_count);
         }
         // �ͷ���ǰ�ڴ�
         MO_FREE(this->_pPtrs);
      }
      // �����µ��ڴ�
      this->_pPtrs = pAlloc;
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
class GFixPtrs : public MPtrs<T>{
protected:
   T _memory[S];
public:
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   GFixPtrs(){
      InnerInitialize();
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   GFixPtrs(const TPtrC<T>& ptr){
      InnerInitialize();
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   GFixPtrs(const MPtrs<T>& values){
      InnerInitialize();
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>���춨�����顣</T>
   GFixPtrs(const GFixPtrs<T, S>& values){
      InnerInitialize();
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�����������顣</T>
   MO_ABSTRACT ~GFixPtrs(){
      this->Clear();
   }
protected:
   //------------------------------------------------------------
   // <T>��ʼ���ڴ档</T>
   MO_INLINE void InnerInitialize(){
      this->_pPtrs = _memory;
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
   MO_INLINE void operator=(const MPtrs<T>& values){
      Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�趨��ǰ���ݺ�ָ������ָ����ȡ�</T>
   MO_INLINE void operator=(const GFixPtrs<T, S>& values){
      Assign(values.MemoryC(), values.Count());
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_PTRS_H__
