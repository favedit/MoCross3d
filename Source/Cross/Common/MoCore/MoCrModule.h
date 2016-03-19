#ifndef __MO_CR_MODULE_H__
#define __MO_CR_MODULE_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_CONFIGURATION_H__
#include "MoCrConfigruation.h"
#endif // __MO_CR_CONFIGURATION_H__

#define MO_CR_MEMORY_LIMIT_RATE 1.4f

MO_NAMESPACE_BEGIN

//============================================================
class FModule;
class FModuleConsole;

//============================================================
// <T>ģ�顣</T>
//
// @history 100312 MAOCY ����
//============================================================
class MO_CR_DECLARE FModule :
      public FObject,
      public ISingleton,
      public IConfiguration{
protected:
   TInt _code;
   TFsName _name;
public:
   FModule();
   MO_ABSTRACT ~FModule();
public:
   MO_OVERRIDE TResult Construct();
   MO_OVERRIDE TResult Dispose();
public:
   MO_ABSTRACT TResult OnLoadConfig(FXmlNode* pConfig);
   MO_ABSTRACT TResult OnInitialize() ;
   MO_ABSTRACT TResult OnReload();
   MO_ABSTRACT TResult OnUnload();
   MO_ABSTRACT TResult OnRelease();
   MO_ABSTRACT TResult OnSerialize();
   MO_ABSTRACT TResult OnUnserialize();
public:
   MO_OVERRIDE ESingleton SingletonType();
   MO_OVERRIDE TInt Code();
   MO_OVERRIDE TCharC* Name();
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
public:
   MO_OVERRIDE TResult LoadConfig(FXmlNode* pConfig);
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
public:
   TResult Initialize();
   TResult Reload();
   TResult Unload();
   TResult Release();
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FModule*> FModuleList;
typedef MO_CR_DECLARE FSet<TInt, FModule*> FModuleSet;

//============================================================
// <T>ģ�����̨��</T>
//
// @history 100301 MAOCY ����
//============================================================
class MO_CR_DECLARE FModuleConsole :
      public FConsole,
      public MApplicationListeners{
private:
   FModuleList* _pModules;
public:
   FModuleConsole();
   MO_ABSTRACT ~FModuleConsole();
public:
   FModuleList* Modules();
public:
   void Register(FModule* pModule);
   void Unregister(FModule* pModule);
public:
   MO_ABSTRACT TResult Initialize();
   MO_OVERRIDE TResult Interrupt();
   MO_OVERRIDE TResult Reload();
   MO_OVERRIDE TResult Unload();
   MO_ABSTRACT TResult Release();
};
//------------------------------------------------------------
class MO_CR_DECLARE RModuleManager : public RSingleton<FModuleConsole>{
};

//============================================================
// <T>ģ��Ψһ����ģ���ࡣ</T>
//
// @history 100312 MAOCY ����
//============================================================
template <typename T>
class RModuleSingleton : public RSingleton<T>{
public:
   //------------------------------------------------------------
   // <T>��ʼ�������ʵ����</T>
   static void Create(T* pInstance = NULL){
      RSingleton<T>::Create(pInstance);
      RConfigurationManager::Instance().Register(RSingleton<T>::_pInstance);
      RModuleManager::Instance().Register(RSingleton<T>::_pInstance);
   }
   //------------------------------------------------------------
   // <T>�ͷŶ����ʵ����</T>
   static void Destroy(){
      RModuleManager::Instance().Unregister(RSingleton<T>::_pInstance);
      RConfigurationManager::Instance().Unregister(RSingleton<T>::_pInstance);
      RSingleton<T>::Destroy();
   }
};

//============================================================
// <T>����ģ�顣</T>
//
// @history 100301 MAOCY ����
//============================================================
class MO_CR_DECLARE FSharedModule :
      public FModule,
      public MShared{
public:
   FSharedModule();
   MO_ABSTRACT ~FSharedModule();
};
//------------------------------------------------------------
typedef MO_CR_DECLARE FList<FSharedModule*> FSharedModuleList;
typedef MO_CR_DECLARE FSet<TInt, FSharedModule*> FSharedModuleSet;

//============================================================
// <T>��������ģ�顣</T>
//============================================================
template <typename T>
class FSharedTypeModule : public FSharedModule{
protected:
   T* _pObject;
public:
   //------------------------------------------------------------
   // ���칲������ģ�顣
   FSharedTypeModule(){
      _pObject = MO_CREATE(T);
   }
   //------------------------------------------------------------
   // ������������ģ�顣
   MO_ABSTRACT ~FSharedTypeModule(){
      MO_DELETE(_pObject);
   }
public:
   //------------------------------------------------------------
   // <T>��ö���</T>
   T* Get(){
      return _pObject;
   }
public:
   //------------------------------------------------------------
   // <T>����ڲ�����������</T>
   MO_OVERRIDE TSize SharedCapacity(){
      return T::CalculateCapacity();
   }
   //------------------------------------------------------------
   // <T>���乲���ڴ档</T>
   MO_OVERRIDE void OnSharedLink(TShareSegment& segment){
      // ��������
      segment.SharedLink(_pObject);
   }
public:
   //------------------------------------------------------------
   // <T>��������ڴ������Ϣ��</T>
   void DumpShared(){
      TChar format[MO_MEMORY_FORMATLENGTH];
      TInt capacity = T::CalculateCapacity();
      TInt total = capacity;
      MO_INFO(MO_DUMP_SHARED_FMT "%4d + %4d",
            (TCharC*)this->_name,
            RInt::FormatCapacity(total, format, MO_MEMORY_FORMATLENGTH),
            0, capacity);
   }
};

//============================================================
// <T>ȫ�ֹ������Ĺ�������</T>
//
// @history 100301 MAOCY ����
//============================================================
class MO_CR_DECLARE FSharedModuleConsole : public FConsole{
protected:
   FSharedModuleList* _pModules;
public:
   FSharedModuleConsole();
   MO_ABSTRACT ~FSharedModuleConsole();
public:
   FSharedModuleList* Modules();
   void Register(FSharedModule* pModule);
   void Unregister(FSharedModule* pModule);
};
//------------------------------------------------------------
class MO_CR_DECLARE RSharedModuleManager : public RSingleton<FSharedModuleConsole>{
};

//============================================================
// <T>����ģ��Ψһ����ģ���ࡣ</T>
//
// @history 100312 MAOCY ����
//============================================================
template <typename T>
class RSharedModuleSingleton : public RSingleton<T>{
public:
   //------------------------------------------------------------
   // <T>��ʼ�������ʵ����</T>
   static void Create(){
      RSingleton<T>::Create();
      RConfigurationManager::Instance().Register(RSingleton<T>::_pInstance);
      RModuleManager::Instance().Register(RSingleton<T>::_pInstance);
      RSharedModuleManager::Instance().Register(RSingleton<T>::_pInstance);
   }
   //------------------------------------------------------------
   // <T>�ͷŶ����ʵ����</T>
   static void Destroy(){
      RSharedModuleManager::Instance().Unregister(RSingleton<T>::_pInstance);
      RModuleManager::Instance().Unregister(RSingleton<T>::_pInstance);
      RConfigurationManager::Instance().Unregister(RSingleton<T>::_pInstance);
      RSingleton<T>::Destroy();
   }
};

//============================================================
// <T>�ռ�ģ��ӿ�</T>
//
// @history 100414 MAOCY ����
//============================================================
template <typename T>
class FTypeAllocator : public FList<T>{
protected:
   TInt _allocCount;
public:
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   FTypeAllocator(){
      _allocCount = 0;
   }
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   ~FTypeAllocator(){
   }
public:
   //------------------------------------------------------------
   TInt AllocCount(){
      return _allocCount;
   }
   //------------------------------------------------------------
   // <T>�ռ�����</T>
   T Alloc(){
      T pObject = this->Shift();
      MO_ASSERT(pObject);
      _allocCount++;
      return pObject;
   }
   //------------------------------------------------------------
   // <T>�ͷŶ���</T>
   void Free(T pObject){
      MO_ASSERT(pObject);
      this->Unshift(pObject);
      _allocCount--;
   }
   //------------------------------------------------------------
   // <T>�洢��</T>
   void Store(T pObject){
      MO_ASSERT(pObject);
      this->Push(pObject);
   }
};

//============================================================
// <T>�ռ�ģ��ӿ�</T>
//
// @history 100414 MAOCY ����
//============================================================
template <typename T>
class MAllocatorModule{
public:
   typedef FList<T*> FPtrList;
protected:
   FPtrList* _pItems;
   FPtrList* _pFrees;
   FPtrList* _pStorage;
public:
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MAllocatorModule(){
      _pItems = MO_CREATE(FPtrList);
      _pFrees = MO_CREATE(FPtrList);
      _pStorage = MO_CREATE(FPtrList);
   }
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   ~MAllocatorModule(){
      MO_DELETE(_pItems);
      MO_DELETE(_pFrees);
      MO_DELETE(_pStorage);
   }
protected:
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   void InnerStore(T* pItem){
      _pFrees->Push(pItem);
      _pStorage->Push(pItem);
   }
   //------------------------------------------------------------
   // <T>�ռ�һ������</T>
   T* InnerAlloc(){
      T* pItem = _pFrees->Shift();
      MO_ASSERT(pItem);
      _pItems->Push(pItem);
      return pItem;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ������</T>
   void InnerFree(T* pItem){
      MO_ASSERT(pItem);
      _pItems->Remove(pItem);
      _pFrees->Unshift(pItem);
   }
public:
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   FPtrList* Items(){
      return _pItems;
   }
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   FPtrList* Frees(){
      return _pFrees;
   }
   //------------------------------------------------------------
   // <T>��ô洢�б�</T>
   FPtrList* Storage(){
      return _pStorage;
   }
   //------------------------------------------------------------
   // <T>�ռ�����</T>
   T* Alloc(){
      T* pItem = _pStorage->Shift();
      MO_ASSERT(pItem);
      _pItems->Push(pItem);
      return pItem;
   }
   //------------------------------------------------------------
   // <T>�ͷŶ���</T>
   void Free(T* pItem){
      MO_ASSERT(pItem);
      _pItems->Remove(pItem);
      _pStorage->Unshift(pItem);
   }
};

//============================================================
// <T>�ռ�ģ��ӿ�</T>
//
// @history 100414 MAOCY ����
//============================================================
template <typename T>
class MAllocatorPool{
public:
   typedef FList<T> FItemList;
   typedef FVector<T> FItemVector;
protected:
   FItemList* _pItems;
   FItemList* _pFrees;
   FItemVector* _pStorage;
public:
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MAllocatorPool(){
      _pItems = MO_CREATE(FItemList);
      _pFrees = MO_CREATE(FItemList);
      _pStorage = MO_CREATE(FItemVector);
   }
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MO_ABSTRACT( ~MAllocatorPool() ){
      MO_DELETE(_pItems);
      MO_DELETE(_pFrees);
      MO_DELETE(_pStorage);
   }
protected:
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   T InnerStore(T pItem){
      // ������
      if(NULL != pItem){
         // ������������
         _pFrees->Push(pItem);
         // ����洢����
         _pStorage->Push(pItem);
      }
      return pItem;
   }
   //------------------------------------------------------------
   // <T>�ռ�һ������</T>
   T InnerAlloc(){
      T pItem = NULL;
      if(!_pFrees->IsEmpty()){
         pItem = _pFrees->Shift();
         _pItems->Push(pItem);
      }else{
         MO_FATAL("Free item is empty. alloc item failure. (total=%d, used=%d, free=%d)",
               _pStorage->Count(), _pItems->Count(), _pFrees->Count());
      }
      return pItem;
   }
   //------------------------------------------------------------
   // <T>�ռ�һ������</T>
   T InnerAlloc(TInt index){
      T pItem = NULL;
      if(!_pFrees->IsEmpty()){
         pItem = _pStorage->Get(index);
         MO_ASSERT(_pFrees->Contains(pItem));
         _pFrees->Remove(pItem);
         _pItems->Push(pItem);
      }else{
         MO_FATAL("Free item is empty. alloc item failure. (total=%d, used=%d, free=%d)",
               _pStorage->Count(), _pItems->Count(), _pFrees->Count());
      }
      return pItem;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻���������</T>
   void InnerFree(T pItem){
      // ������
      if(NULL == pItem){
         return;
      }
      // ��ʹ�ü����Ƴ�
#ifdef _MO_DEBUG
      if(!_pItems->Contains(pItem)){
         MO_ERROR("Free item is not exists in use collection. (using_count=%d, free_count=%d)",
               _pItems->Count(), _pFrees->Count());
      }
#endif // _MO_DEBUG
      _pItems->Remove(pItem);
      // �����ͷż�����
      if(!_pFrees->Contains(pItem)){
         _pFrees->Unshift(pItem);
      }else{
         MO_ERROR("Free item is already exists in free collection. (using_count=%d, free_count=%d)",
               _pItems->Count(), _pFrees->Count());
      }
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻������ײ���</T>
   void InnerFreeLast(T pItem){
      // ������
      if(NULL == pItem){
         return;
      }
      // ��ʹ�ü����Ƴ�
#ifdef _MO_DEBUG
      if(!_pItems->Contains(pItem)){
         MO_ERROR("Free item is not exists in use collection. (using_count=%d, free_count=%d)",
               _pItems->Count(), _pFrees->Count());
      }
#endif // _MO_DEBUG
      _pItems->Remove(pItem);
      // �����ͷż�����
      if(!_pFrees->Contains(pItem)){
         _pFrees->Push(pItem);
      }else{
         MO_ERROR("Free item is already exists in free collection. (using_count=%d, free_count=%d)",
               _pItems->Count(), _pFrees->Count());
      }
   }
   //------------------------------------------------------------
   // <T>�ͷ����ж���</T>
   void InnerReleaseAll(){
      // ɾ�������Ӷ���
      TVectorIteratorC<T> iterator = _pStorage->IteratorC();
      while(iterator.Next()){
         T pItem = *iterator;
         MO_DELETE(pItem);
      }
      // ��ռ���
      _pItems->Clear();
      _pFrees->Clear();
      _pStorage->Clear();
   }
public:
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   FItemList* Items(){
      return _pItems;
   }
   //------------------------------------------------------------
   // <T>����Ƿ��п��ж���</T>
   TBool HasFrees(){
      return !_pFrees->IsEmpty();
   }
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   FItemList* Frees(){
      return _pFrees;
   }
   //------------------------------------------------------------
   // <T>��ô洢�б�</T>
   FItemVector* Storage(){
      return _pStorage;
   }
};

//============================================================
// <T>�ռ�����ӿ�</T>
//
// @history 110729 MAOCY ����
//============================================================
template <typename T>
class MObjectPool{
public:
   typedef FList<T*> FObjectList;
protected:
   FObjectList* _pItems;
   FObjectList* _pFrees;
public:
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MObjectPool(){
      _pItems = MO_CREATE(FObjectList);
      _pFrees = MO_CREATE(FObjectList);
   }
   //------------------------------------------------------------
   // <T>�����ռ�ģ�顣</T>
   MO_ABSTRACT ~MObjectPool(){
      this->InnerReleaseAll();
      MO_DELETE(_pItems);
      MO_DELETE(_pFrees);
   }
protected:
   //------------------------------------------------------------
   // <T>��������</T>
   MO_ABSTRACT T* InnerCreate(){
      MO_FATAL("Free object is empty. create object failure. (total=%d, used=%d, free=%d)",
            _pItems->Count() + _pFrees->Count(), _pItems->Count(), _pFrees->Count());
   }
   //------------------------------------------------------------
   // <T>ɾ������</T>
   MO_ABSTRACT void InnerDelete(T* pObject){
      MO_FATAL("Delete object is invalid.");
   }
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   T* InnerStore(T* pObject){
      MO_ASSERT(pObject);
      // ������������
      _pFrees->Push(pObject);
      return pObject;
   }
   //------------------------------------------------------------
   // <T>�ռ�һ������</T>
   MO_ABSTRACT T* InnerAlloc(){
      T* pObject = NULL;
      if(!_pFrees->IsEmpty()){
         pObject = _pFrees->Shift();
      }else{
         pObject = InnerCreate();
      }
      _pItems->Push(pObject);
      return pObject;
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻���������</T>
   void InnerFreeFirst(T* pObject){
      MO_ASSERT(pObject);
      if(!_pItems->Contains(pObject)){
         MO_FATAL("Free object is not exists collection. (total=%d, used=%d, free=%d)",
               _pItems->Count() + _pFrees->Count(), _pItems->Count(), _pFrees->Count());
      }
      _pItems->Remove(pObject);
      _pFrees->Unshift(pObject);
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ�����󵽻������ײ���</T>
   void InnerFreeLast(T* pObject){
      MO_ASSERT(pObject);
      if(!_pItems->Contains(pObject)){
         MO_FATAL("Free object is not exists collection. (total=%d, used=%d, free=%d)",
               _pItems->Count() + _pFrees->Count(), _pItems->Count(), _pFrees->Count());
      }
      _pItems->Remove(pObject);
      _pFrees->Push(pObject);
   }
   //------------------------------------------------------------
   // <T>�ͷ�һ������</T>
   MO_ABSTRACT void InnerFree(T* pObject){
      InnerFreeLast(pObject);
   }
   //------------------------------------------------------------
   // <T>�ͷ����ж���</T>
   void InnerReleaseAll(){
      // ɾ������ʹ�ü���
      if(!_pItems->IsEmpty()){
         TListIteratorC<T*> iterator = _pItems->IteratorC();
         while(iterator.Next()){
            T* pObject = *iterator;
            MO_DELETE(pObject);
         }
         _pItems->Clear();
      }
      // ɾ���������ɼ���
      if(!_pFrees->IsEmpty()){
         TListIteratorC<T*> iterator = _pFrees->IteratorC();
         while(iterator.Next()){
            T* pObject = *iterator;
            MO_DELETE(pObject);
         }
         _pFrees->Clear();
      }
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ���ʹ�ö���</T>
   MO_INLINE TBool HasItem(){
      return !_pItems->IsEmpty();
   }
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   MO_INLINE FObjectList* Items(){
      return _pItems;
   }
   //------------------------------------------------------------
   // <T>����Ƿ��п��ж���</T>
   MO_INLINE TBool HasFree(){
      return !_pFrees->IsEmpty();
   }
   //------------------------------------------------------------
   // <T>���ʹ���б�</T>
   MO_INLINE FObjectList* Frees(){
      return _pFrees;
   }
};

//============================================================
// <T>��������ģ��</T>
//
// @history 110526 MAOCY ����
//============================================================
template <typename T>
class FSharedPoolModule :
      public FSharedModule,
      public MObjectPool<T>{
public:
   typedef FSet<TInt, T*> FItemSet;
protected:
   TInt _capacity;
   TInt _counter;
   FItemSet* _pItemSet;
public:
   //------------------------------------------------------------
   FSharedPoolModule(){
      _capacity = 0;
      _counter = 0;
      _pItemSet = MO_CREATE(FItemSet);
   }
   //------------------------------------------------------------
   MO_ABSTRACT ~FSharedPoolModule(){
      this->InnerReleaseAll();
      MO_DELETE(_pItemSet);
   }
public:
   //------------------------------------------------------------
   TSize Capacity(){
      return _capacity;
   }
   //------------------------------------------------------------
   MO_ABSTRACT TSize ObjectCapacity(){
      return T::CalculateCapacity();
   }
   //------------------------------------------------------------
   MO_ABSTRACT T* CreateObject(){
      return MO_CREATE(T);
   }
   //------------------------------------------------------------
   // <T>����������Ϣ��</T>
   MO_OVERRIDE TBool OnLoadConfig(FXmlNode* pConfig){
      if(pConfig->HasNode()){
         TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
         while(iterator.Next("Property")){
            if(iterator->IsAttribute("name", "capacity")){
               _capacity = iterator->TextAsInt();
            }
         }
      }
      MO_DEBUG("Load shared module(%s) property. (capacity=%d)", (TCharC*)_name, _capacity);
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>���乲���ڴ档</T>
   MO_OVERRIDE void OnSharedLink(TShareSegment& segment){
      MO_ASSERT(_capacity > 0)
      for(TInt n=0; n<_capacity; n++){
         // ��������
         T* pObject = CreateObject();
         segment.SharedLink(pObject);
         InnerStore(pObject);
      }
   }
   //------------------------------------------------------------
   // <T>���㹲���ڴ��С��</T>
   MO_OVERRIDE TSize SharedCapacity(){
      TSize objectCapacity = ObjectCapacity();
      TSize capacity = objectCapacity * _capacity;
      return capacity;
   }
public:
   //------------------------------------------------------------
   T* GetByIndex(TInt index){
      return this->_pStorage->Get(index);
   }
   //------------------------------------------------------------
   T* FindByIndex(TInt index){
      return this->_pStorage->Nvl(index, NULL);
   }
   //------------------------------------------------------------
   T* GetById(TInt id){
      return this->_pItemSet->Get(id);
   }
   //------------------------------------------------------------
   T* FindById(TInt id){
      return this->_pItemSet->Find(id);
   }
public:
   //------------------------------------------------------------
   MO_ABSTRACT T* Alloc(){
      T* pItem = this->InnerAlloc();
      MO_ASSERT(pItem);
      return pItem;
   }
   //------------------------------------------------------------
   MO_ABSTRACT T* Alloc(TInt index){
      MO_ASSERT(index >= 0);
      T* pItem = this->InnerAlloc(index);
      MO_ASSERT(pItem);
      return pItem;
   }
   //------------------------------------------------------------
   MO_ABSTRACT T* AllocById(TInt id){
      MO_ASSERT(id > 0);
      T* pItem = this->Alloc();
      this->_pItemSet->Set(id, pItem);
      return pItem;
   }
   //------------------------------------------------------------
   MO_ABSTRACT void Free(T* pItem){
      MO_ASSERT(pItem);
      this->InnerFree(pItem);
   }
   //------------------------------------------------------------
   MO_ABSTRACT void FreeById(TInt id){
      MO_ASSERT(id > 0);
      T* pItem = GetById(id);
      MO_ASSERT(pItem);
      this->Free(pItem);
   }
public:
   //------------------------------------------------------------
   // <T>���ݱ�ţ���ù�������</T>
   T* LinkById(TInt id){
      MO_ASSERT(id > 0);
      T* pItem = _pItemSet->Find(id);
      if(NULL != pItem){
         MO_FATAL("Item is already exists. (name=%s, id=%d)", (TCharC*)_name, id);
      }
      pItem = Alloc();
      pItem->SetId(id);
      _pItemSet->Set(id, pItem);
      return pItem;
   }
   //------------------------------------------------------------
   // <T>���ݱ�ţ����ͬ������</T>
   T* SyncById(TInt id){
      MO_ASSERT(id > 0);
      T* pItem = _pItemSet->Find(id);
      if(NULL == pItem){
         pItem = Alloc();
         pItem->SetId(id);
         _pItemSet->Set(id, pItem);
      }
      return pItem;
   }
   //------------------------------------------------------------
   void Unlink(T* pItem){
      TInt id = pItem->Id();
      MO_ASSERT(id > 0);
      T* pFind = _pItemSet->Find(id);
      if(NULL != pFind){
         MO_ASSERT(pFind == pItem);
         _pItemSet->Set(id, NULL);
         InnerFree(pFind);
      }
   }
public:
   //------------------------------------------------------------
   // <T>��������ڴ�ķ�����Ϣ��</T>
   void DumpShared(){
      TChar format[MO_MEMORY_FORMATLENGTH];
      TInt capacity = T::CalculateCapacity();
      TInt total = capacity * _capacity;
      MO_INFO(MO_DUMP_SHARED_FMT "%4d + %4d * %d",
            (TCharC*)_name,
            RInt::FormatCapacity(total, format, MO_MEMORY_FORMATLENGTH),
            0, capacity, _capacity);
   }
};

MO_NAMESPACE_END

#endif // __MO_CR_MODULE_H__
