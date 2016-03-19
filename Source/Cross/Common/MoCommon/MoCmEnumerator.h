//============================================================
// <T>ö�ٹ���</T>
//============================================================
#ifndef __MO_CM_ENUMERATOR_H__
#define __MO_CM_ENUMERATOR_H__

#ifndef __MO_CM_CLASS_H__
#include "MoCmClass.h"
#endif // __MO_CM_CLASS_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>ö����Ŀ��</T>
//
// @history 140514 MAOCY ����
//============================================================
class MO_CM_DECLARE FEnumeratorItem : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FEnumeratorItem, FInstance);
protected:
   TInt _code;
   TString _name;
   TString _description;
public:
   FEnumeratorItem();
   MO_ABSTRACT ~FEnumeratorItem();
public:
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE TInt Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>���ô��롣</T>
   MO_INLINE void SetCode(TInt code){
      _code = code;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����ơ�</T>
   MO_INLINE TBool IsName(TCharC* pName){
      return _name.Equals(pName);
   }
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TCharC* Description(){
      return _description;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void SetDescription(TCharC* pDescription){
      _description = pDescription;
   }
public:
   TResult Dump(MString* pDump);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE GPtrs<FEnumeratorItem> GEnumeratorItemPtrs;

//============================================================
// <T>ö������</T>
//
// @history 140514 MAOCY ����
//============================================================
class MO_CM_DECLARE FEnumerator : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FEnumerator, FInstance);
protected:
   TString _name;
   GEnumeratorItemPtrs _items;
public:
   FEnumerator();
   MO_ABSTRACT ~FEnumerator();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����ơ�</T>
   MO_INLINE TBool IsName(TCharC* pName){
      return _name.Equals(pName);
   }
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
public:
   MO_ABSTRACT TResult Setup();
public:
   FEnumeratorItem* FindByCode(TInt code);
   FEnumeratorItem* FindByName(TCharC* pName);
public:
   TInt Parse(TCharC* pName);
   TInt Parse(TCharC* pName, TInt defaultValue);
   TCharC* Format(TInt code);
   TCharC* Format(TInt code, TCharC* pDefaultValue);
public:
   TResult Register(FEnumeratorItem* pItem);
   TResult Register(TInt code, TCharC* pName, TCharC* pDescription = NULL);
   TResult Unrgister(FEnumeratorItem* pItem);
public:
   MO_ABSTRACT TResult Dump(MString* pDump);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE GPtrDictionary<FEnumerator> GEnumeratorDictionary;

//============================================================
// <T>ö�������ߡ�</T>
//
// @history 140515 MAOCY ����
//============================================================
template <typename T>
class REnumerator{
protected:
   static T* _pInstance;
public:
   //------------------------------------------------------------
   // <T>��ʼ�������ʵ����</T>
   static void Create(){
      // ��������
      MO_ASSERT(!_pInstance);
      _pInstance = MO_PTR_CREATE(T);
      // ��������
      _pInstance->Construct();
   }
   //------------------------------------------------------------
   // <T>�ͷŶ����ʵ����</T>
   static void Destroy(){
      MO_ASSERT(_pInstance);
      MO_PTR_DELETE(_pInstance);
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ���Ч��</T>
   static TBool IsValid(){
      return (NULL != _pInstance);
   }
public:
   //------------------------------------------------------------
   // <T>��ö����ʵ����</T>
   static MO_INLINE T& Instance(){
      return *_pInstance;
   }
   //------------------------------------------------------------
   // <T>��ö����ʵ��ָ�롣</T>
   static MO_INLINE T* InstancePtr(){
      return _pInstance;
   }
public:
   //------------------------------------------------------------
   // <T>�����ַ���Ϊö�����ݡ�</T>
   static TInt Parse(TCharC* pValue){
      MO_CHECK(_pInstance, return 0);
      return _pInstance->Parse(pValue);
   }
   //------------------------------------------------------------
   // <T>�����ַ���Ϊö�����ݡ�</T>
   static TInt Parse(TCharC* pValue, TInt defaultValue){
      MO_CHECK(_pInstance, return defaultValue);
      return _pInstance->Parse(pValue, defaultValue);
   }
   //------------------------------------------------------------
   // <T>��ʽ��ö������Ϊ�ַ�����</T>
   static TCharC* Format(TInt enumValue){
      MO_CHECK(_pInstance, return NULL);
      return _pInstance->Format(enumValue);
   }
   //------------------------------------------------------------
   // <T>��ʽ��ö������Ϊ�ַ�����</T>
   static TCharC* Format(TInt enumValue, TCharC* pDefaultValue){
      MO_CHECK(_pInstance, return pDefaultValue);
      return _pInstance->Format(enumValue, pDefaultValue);
   }
};
//------------------------------------------------------------
template <typename T> T* REnumerator<T>::_pInstance = NULL;

//============================================================
// <T>ö��������̨��</T>
//
// @history 140514 MAOCY ����
//============================================================
class FEnumeratorConsole : public FConsole
{
   MO_CLASS_DECLARE_INHERITS(FEnumeratorConsole, FConsole);
protected:
   GEnumeratorDictionary _enumerators;
public:
   FEnumeratorConsole();
   MO_ABSTRACT ~FEnumeratorConsole();
public:
   //------------------------------------------------------------
   // <T>���ö�ټ��ϡ�</T>
   MO_INLINE GEnumeratorDictionary& Enumerators(){
      return _enumerators;
   }
public:
   //------------------------------------------------------------
   // <T>�������ƻ��ö�١�</T>
   MO_INLINE FEnumerator* Find(TCharC* pName){
      FEnumerator* pEnumerator = _enumerators.Find(pName);
      if(pEnumerator == NULL){
         return NULL;
      }
      return pEnumerator;
   }
   //------------------------------------------------------------
   // <T>�������ƻ��ö�١�</T>
   template<class T>
   MO_INLINE T* Find(TCharC* pName){
      FEnumerator* pEnumerator = _enumerators.Find(pName);
      if(pEnumerator == NULL){
         return NULL;
      }
      return pEnumerator->Convert<T>();
   }
public:
   MO_ABSTRACT TResult Register(FEnumerator* pEnumerator);
   MO_ABSTRACT TResult Unrgister(FEnumerator* pEnumerator);
   MO_ABSTRACT FEnumerator* Sync(TCharC* pName);
};

//============================================================
// <T>ö������������</T>
//
// @history 140514 MAOCY ����
//============================================================
class REnumeratorManager : public RSingleton<FEnumeratorConsole>{
public:
   static FEnumerator* Find(TCharC* pName);
public:
   //------------------------------------------------------------
   // <T>�������ƻ��ö�١�</T>
   template<class T>
   static MO_INLINE T* Find(TCharC* pName){
      FEnumerator* pEnumerator = Find(pName);
      if(pEnumerator == NULL){
         return NULL;
      }
      return pEnumerator->Convert<T>();
   }
};
   
MO_NAMESPACE_END

#endif // __MO_CM_ENUMERATOR_H__
