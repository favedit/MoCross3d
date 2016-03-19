#ifndef __MO_CM_INTERFACE_H__
#define __MO_CM_INTERFACE_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

MO_NAMESPACE_INCLUDE;

//============================================================
// <T>ɾ���ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
MO_INLINE void operator delete(TAny* pMemory){
   free(pMemory);
}

//============================================================
// <T>ɾ���ڴ档</T>
//
// @param pMemory �ڴ�ָ��
// @param pFileName �ļ�����
// @param lineNumber �ļ��к�
//============================================================
MO_INLINE void operator delete(TAny* pMemory, TCharC* pFileName, TInt lineNumber){
   free(pMemory);
}

//============================================================
// <T>ɾ�������ڴ档</T>
//
// @param pMemory �����ڴ�
//============================================================
MO_INLINE void operator delete[](TAny* pMemory){
   free(pMemory);
}

//============================================================
// <T>ɾ�������ڴ档</T>
//
// @param pMemory �ڴ�ָ��
// @param pFileName �ļ�����
// @param lineNumber �ļ��к�
//============================================================
MO_INLINE void operator delete[](TAny* pMemory, TCharC* pFileName, TInt lineNumber){
   free(pMemory);
}

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ӿڡ�</T>
//
// @history 130227 MAOCY ����
//============================================================
class MO_CM_DECLARE IBase{
public:
   //------------------------------------------------------------
   // <T>���������ӿڡ�</T>
   MO_ABSTRACT ~IBase(){
   }
public:
   MO_VIRTUAL THashCode HashCode() const = 0;
};

//============================================================
// <T>����ӿڡ�</T>
//
// @history 130130 MAOCY ����
//============================================================
class MO_CM_DECLARE IConstruct{
public:
   //------------------------------------------------------------
   // <T>��������ӿڡ�</T>
   MO_ABSTRACT ~IConstruct(){
   }
public:
   MO_VIRTUAL void Construct() = 0;
};

//============================================================
// <T>�Գ�ʼ���ӿڡ�</T>
//============================================================
class MO_CM_DECLARE IInitialize{
public:
   //------------------------------------------------------------
   // <T>�����Գ�ʼ���ӿڡ�</T>
   MO_ABSTRACT ~IInitialize(){
   }
public:
   MO_VIRTUAL TResult Initialize() = 0;
};

//============================================================
// <T>���ͷŽӿڡ�</T>
//============================================================
class MO_CM_DECLARE IReleasable{
public:
   //------------------------------------------------------------
   // <T>�������ͷŽӿڡ�</T>
   MO_ABSTRACT ~IReleasable(){
   }
public:
   MO_VIRTUAL TResult ReferIncrease() = 0;
   MO_VIRTUAL TResult ReferDecrease() = 0;
   MO_VIRTUAL TResult Release() = 0;
};

//============================================================
// <T>�ͷŽӿڡ�</T>
//
// @history 130130 MAOCY ����
//============================================================
class MO_CM_DECLARE IDispose{
public:
   //------------------------------------------------------------
   // <T>�����ͷŽӿڡ�</T>
   MO_ABSTRACT ~IDispose(){
   }
public:
   MO_VIRTUAL TResult Dispose() = 0;
};

//============================================================
// <T>�ȽϽӿڡ�</T>
//============================================================
template <typename T>
class IComparable{
public:
   //------------------------------------------------------------
   // <T>�����ȽϽӿڡ�</T>
   MO_ABSTRACT ~IComparable(){
   }
public:
   MO_VIRTUAL TResult Compare(const IComparable<T>& source) = 0;
};

//============================================================
// <T>��̬�ӿڡ�</T>
//
// @history 130130 MAOCY ����
//============================================================
class MO_CM_DECLARE IStatic : public IDispose{
public:
   //------------------------------------------------------------
   // <T>������̬�ӿڡ�</T>
   MO_ABSTRACT ~IStatic(){
   }
public:
   MO_VIRTUAL TResult Construct() = 0;
   MO_VIRTUAL TResult Dispose() = 0;
};

//============================================================
// <T>������Ϣ�Ľӿڡ�</T>
//
// @history 130130 MAOCY ����
//============================================================
class MO_CM_DECLARE IDump{
public:
   //------------------------------------------------------------
   // <T>����������Ϣ�Ľӿڡ�</T>
   MO_ABSTRACT ~IDump(){
   }
public:
   MO_VIRTUAL void Dump(TChar* pDump, TInt capacity) = 0;
};

//============================================================
// <T>��������</T>
//
// @history 130130 MAOCY ����
//============================================================
class MO_CM_DECLARE FBase{
public:
   TAny* operator new(TSize size);
   TAny* operator new(TSize size, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber);
   TAny* operator new(TSize size, TAny* pMemory);
   TAny* operator new(TSize size, TAny* pMemory, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber);
   void operator delete(TAny* pMemory);
   void operator delete(TAny* pMemory, TAny* pAlloc);
   void operator delete(TAny* pMemory, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber);
};

//============================================================
// <T>���ɶ���</T>
// <P>�ӵ�ǰ���������κ��࣬����ʹ��(MO_NEW)����ʵ��������</P>
//
// @history 130130 MAOCY ����
//============================================================
class MO_CM_DECLARE FFree{
public:
   FFree();
   MO_ABSTRACT ~FFree();
};

//============================================================
// <T>������ࡣ</T>
// <P>�ӵ�ǰ���������κ��࣬����ʹ��(MO_CREATE)����ʵ��������</P>
//
// @history 121121 MAOCY ����
//============================================================
class MO_CM_DECLARE FObject{
public:
   FObject();
   MO_ABSTRACT ~FObject();
public:
   TAny* operator new(TSize size);
   TAny* operator new(TSize size, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber);
   TAny* operator new(TSize size, TAny* pMemory);
   TAny* operator new(TSize size, TAny* pMemory, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber);
   void operator delete(TAny* pMemory);
   void operator delete(TAny* pMemory, TAny* pAlloc);
   void operator delete(TAny* pMemory, TChar8C* pClassName, TChar8C* pFileName, TInt lineNumber);
public:
   MO_ABSTRACT THashCode HashCode() const;
};

//============================================================
// <T>�йܶ�����ࡣ</T>
//
// @history 131202 MAOCY ����
//============================================================
class MO_CM_DECLARE FManagedObject :
      public FObject,
      public IDispose{
protected:
   TInt _referenceCount;
public:
   FManagedObject();
   MO_ABSTRACT ~FManagedObject();
public:
   //------------------------------------------------------------
   // <T>����������Ϣ�Ľӿڡ�</T>
   MO_INLINE TBool IsDisposed(){
      return (_referenceCount == 0);
   }
public:
   //------------------------------------------------------------
   // <T>����һ�����á�</T>
   MO_INLINE void ReferIncrease(){
      _referenceCount++;
   }
   //------------------------------------------------------------
   // <T>����ָ�����������á�</T>
   MO_INLINE void ReferIncrease(TInt referCount){
      _referenceCount += referCount;
   }
   //------------------------------------------------------------
   // <T>����һ�����á�</T>
   MO_INLINE void ReferDecrease(){
      // ������
      if(_referenceCount <= 0){
         return;
      }
      // �ͷŴ���
      if(_referenceCount == 1){
         Dispose();
      }
      // ���ٴ���
      _referenceCount--;
   }
   //------------------------------------------------------------
   // <T>����ָ�����������á�</T>
   MO_INLINE void ReferDecrease(TInt referCount){
      // ������
      if(referCount <= 0){
         return;
      }
      if(_referenceCount <= 0){
         return;
      }
      if(_referenceCount - referCount < 0){
         referCount = _referenceCount;
      }
      // �ͷŴ���
      if(_referenceCount - referCount == 0){
         Dispose();
      }
      // ���ٴ���
      _referenceCount -= referCount;
   }
public:
   MO_ABSTRACT TResult Dispose();
};

MO_NAMESPACE_END

#endif // __MO_CM_INTERFACE_H__
