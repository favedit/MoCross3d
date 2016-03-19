#ifndef __MO_CM_SHAREDMAP_H__
#define __MO_CM_SHAREDMAP_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_SHARED_H__
#include "MoCmShared.h"
#endif // __MO_CM_SHARED_H__


MO_NAMESPACE_BEGIN

#define HASH_MAP(hash, size)	((hash) % (size) + 1)

//============================================================
template <class K, class T>
struct SSharedMapEntry {
   TUint32 nlink;
   TUint32 plink;
   TUint32 next;
   TUint32 hash;
   K key;
   T data;
};

//============================================================
// <T>ֻ�����������������</T>
//
// @template
// @type E:entry �ڵ�����
// @history 100326 MAOCY ����
//============================================================
template <class K, class T>
class TSharedMapIteratorC {
protected:
   SSharedMapEntry<K, T>* _pEntries;
   TUint32 _current;
   TUint32 _head;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedMapIteratorC(){
      _pEntries = 0;
      _current = 0;
      _head = 0;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedMapIteratorC(const TSharedMapIteratorC<K, T>& iterator){
      _pEntries = iterator._pEntries;
      _current = iterator._current;
      _head = iterator._head;
   }
   //------------------------------------------------------------
   // ����ֻ��������
   TSharedMapIteratorC(SSharedMapEntry<K, T>* pEntries, TUint32 head){
      _pEntries = pEntries;
      _current = 0;
      _head = head;
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline const T& operator *() const{
      MO_ASSERT(_current > 0);
      return _pEntries[_current].data;
   }
   //------------------------------------------------------------
   // ��õ�ǰ�ڵ�
   inline const T* operator ->() const{
      MO_ASSERT(_current > 0);
      return &_pEntries[_current].data;
   }
public:
   //------------------------------------------------------------
   // ����λ��
   inline void Reset(){
      _current = 0;
   }
   //------------------------------------------------------------
   inline const SSharedMapEntry<K, T>* GetEntry() const{
      MO_ASSERT(_current > 0);
      return &_pEntries[_current];
   }
   //------------------------------------------------------------
   // �ƶ�����һ��λ��
   inline TBool Next(){
      _current = !_current ? _head : _pEntries[_current].nlink;
      return _current;
   }
public:
   //------------------------------------------------------------
   // ��õ�ǰλ�õ���������
   inline const T& Get() const {
      MO_ASSERT(_pEntries[_current].hash > 0);
      return _pEntries[_current].data;
   }
};

//============================================================
template <class K, class T>
class MO_CM_DECLARE TSharedMap : public MShared{
public:
   struct SSharedMapHead {
      TUint32 _count;
   };
public:
   typedef TSharedMapIteratorC<K, T> TIteratorC;
private:
   SSharedMapEntry<K, T> * _gEntries;
   SSharedMapHead *_gHead;
   TUint32 *_slot;
   TUint32 _size;
   TUint32 _capacity;
   TUint32 _head;
   TUint32 _empty;
protected:
   //------------------------------------------------------------
   // ���ڴ�ط���Ԫ�أ��Թ�ʹ��
   TUint32 InnerPop(){
      TUint32 ret = 0;
      if(_empty) {
         ret = _empty;
         _empty = _gEntries[_empty].nlink;
         _gEntries[ret].next = 0;
         _gEntries[ret].nlink = _head;
         _gEntries[ret].plink = 0;
         if(_head) {
            _gEntries[_head].plink = ret;
         }
         _head = ret;
      }
      MO_ASSERT(ret > 0);
      return ret;
   }
   //------------------------------------------------------------
   // Ԫ�ع黹�ڴ��
   void InnerPush(TUint32 n){
      TUint32 tmp = _gEntries[n].nlink;
      if(tmp) {
         _gEntries[tmp].plink = _gEntries[n].plink;
	  }

      tmp = _gEntries[n].plink;
      if(tmp) {
         _gEntries[tmp].nlink = _gEntries[n].nlink;
	  } else {
         _head = _gEntries[n].nlink;
	  }

      _gEntries[n].nlink = _empty;
      _gEntries[n].plink = 0;
      _empty = n;
   }
   //------------------------------------------------------------
   // ��Delete����ʹ�ã�����ɾ��һ��Ԫ��
   inline void Remove(TUint32 slot, TUint32 prev, TUint32 pos){
      if(prev) {
         _gEntries[prev].next = _gEntries[pos].next;
      } else {
         _slot[slot] = _gEntries[pos].next;
      }
   }
public:
   //------------------------------------------------------------
   void OnSharedInitialize(){
     Clear();
   }
   //------------------------------------------------------------
   void OnSharedLink(TShareSegment& segment){
      MO_ASSERT(_size > 0);
      MO_ASSERT(_capacity > 0)
      _gHead = segment.TypeAlloc<SSharedMapHead>();
      _gEntries = segment.TypeAlloc<SSharedMapEntry<K, T> >(_capacity + 1);
      _slot = segment.TypeAlloc<TUint32>(_size + 1);
   }
   //------------------------------------------------------------
   void SetCapacity(TUint32 capacity, TUint32 slot){
      _size = slot;
     _capacity = capacity;
   }
   //------------------------------------------------------------
   TSize SharedCapacity(){
      return (_capacity + 1) * sizeof(SSharedMapEntry<K, T>)
           + sizeof(SSharedMapHead) + sizeof(TUint32) * (_size + 1);
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   TBool operator==(const TSharedMap<K, T>& array) const{
      return Equals(array);
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ���������������������Ƿ���ȡ�
   TBool operator!=(const TSharedMap<K, T>& array) const{
      return !Equals(array);
   }
   //------------------------------------------------------------
   // ׷��һ��������ǰ�����С�
   void operator+=(const TSharedMap<K, T>& array){
      Append(array);
   }
   //------------------------------------------------------------
   void operator=(const TSharedMap<K, T>& array){
      Clear();
      Append(array);
   }
   //------------------------------------------------------------
   // ����Ƿ�Ϊ��
   inline TBool IsEmpty() const{
      return (0 == _gHead->_count);
   }
   //------------------------------------------------------------
   // �������
   inline TUint32 Count() const{
      return _gHead->_count;
   }
   //------------------------------------------------------------
   // �жϵ�ǰ�����ָ�������Ƿ����
   TBool Equals(const TSharedMap<K, T>& array) const{
      // �Ƚ�����
      if(_gHead->_count != array._gHead->_count){
         return EFalse;
      }
      // �Ƚ�������Ŀ
      TIteratorC iterator = array.IteratorC();
      while(iterator.Next()){
         if(!Find(iterator.GetEntry()->key)) {
            return EFalse;
         }
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // �����λ�õ�ֻ�����ݵ�����
   TSharedMapIteratorC<K, T> IteratorC() const{
      return TIteratorC(_gEntries, _head);
   }
   //------------------------------------------------------------
   // ����һ��������ǰ�����С�
   void Assign(const TSharedMap<K, T>& array){
      Clear();
      Append(array);
   }
   //------------------------------------------------------------
   // ׷��һ��������ǰ�����С�
   void Append(const TSharedMap<K, T>& array){
      TIteratorC iterator = array.IteratorC();
      while(iterator.Next()){
         Set(iterator.GetEntry()->key, iterator.GetEntry()->data);
      }
   }
   //------------------------------------------------------------
   // ��������ɾ������ڵ�
   bool Delete(K key){
      //TUint32 hash = _hashfun->HashFun(key);
      TUint32 hash = 0;
      TUint32 slot = HASH_MAP(hash, _size);
      if(!_slot[slot]) {
         return false;
      }
      for(TUint32 pos = _slot[slot], prev = 0; pos; prev = pos, pos = _gEntries[pos].next) {
         if(_gEntries[pos].hash == hash && _gEntries[pos].key == key) {
            Remove(slot, prev, pos);
            InnerPush(pos);
            --_gHead->_count;
            return true;
         }
      }
      return false;
   }
   //------------------------------------------------------------
   // �����������
   void Clear(){
      // �ͷ�ȫ���б�
      memset(_gEntries, 0, sizeof(SSharedMapEntry<K, T>) * (_capacity + 1));
      memset(_slot, 0, sizeof(TUint32) * (_size + 1));
      _gHead->_count = 0;
      _empty = 1;
      _head = 0;
      TUint32 len = _capacity + 1;
      for(TUint32 i = 1; i < len; ++i) {
         _gEntries[i].plink = (i - 1) % len;
         _gEntries[i].nlink = (i + 1) % len;
      }
   }
   //------------------------------------------------------------
   // ��������λ��
   TUint32 Find(K key){
      //TUint32 hash = _hashfun->HashFun(key);
      TUint32 hash = 0;
      TUint32 pos = _slot[HASH_MAP(hash, _size)];
      for(; pos; pos = _gEntries[pos].next) {
         if(_gEntries[pos].hash == hash
				 && _gEntries[pos].key == key) {
            return pos;
		 }
      }
      return 0;
   }
   //------------------------------------------------------------
   // ��������
   bool Search(K key, T& data){
      TUint32 pos;
      if((pos = Find(key))) {
         data = _gEntries[pos].data;
         return true;
      }
      return false;
   }
   //------------------------------------------------------------
   // �õ�����
   inline T Get(TUint32 key){
      T data;
      MO_ASSERT(Search(key, data));
      return data;
   }
   //------------------------------------------------------------
   // ��������
   inline void Set(TUint32 key, const T& data){
      MO_ASSERT(_hashfun);
      TUint32 pos;
      if((pos = Find(key))) {
         _gEntries[pos].data = data;
      } else {
         MO_ASSERT(_gHead->_count < _capacity);
         TUint32 hash = _hashfun->HashFun(key);
         TUint32 slot = HASH_MAP(hash, _size);
         pos = InnerPop();
         _gEntries[pos].hash = hash;
         _gEntries[pos].data = data;
         _gEntries[pos].key = key;
         _gEntries[pos].next = _slot[slot];
         _slot[slot] = pos;
         ++_gHead->_count;
      }
   }
   //------------------------------------------------------------
   // ����Ԫ���Ƿ����
   inline bool Contains(const K &key){
      return Find(key);
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_SHAREDSET_H__

