#ifndef __MO_CM_BIT_H__
#define __MO_CM_BIT_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>λ�򹤾��ࡣ</T>
//
// @tool
// @history 110629 MAOCY ����
//============================================================
template <typename T>
struct TBitSet{
protected:
   T _value;
public:
   //------------------------------------------------------------
   // <T>����λ�򹤾��ࡣ</T>
   inline TBitSet(){
      _value = 0;
   }
   //------------------------------------------------------------
   // <T>����λ�򹤾��ࡣ</T>
   inline TBitSet(T value){
      _value = value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   TBool operator==(T value){
      return (_value == value);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   TBool operator!=(T value){
      return (_value != value);
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   operator T(){
      return _value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   void operator=(T value){
      _value = value;
   }
public:
   //------------------------------------------------------------
   // <T>������ݴ�С��</T>
   static inline TSize Size(){
      return sizeof(T);
   }
public:
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   inline T Get(){
      return _value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   inline void Set(){
      _value = ~0;
   }
   //------------------------------------------------------------
   // <T>��ת���ݡ�</T>
   inline void Inverse(){
      _value = ~_value;
   }
   //------------------------------------------------------------
   // <T>�޸����ݡ�</T>
   inline void Modify(T value){
      _value = value;
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   inline void Clear(){
      _value = 0;
   }
   //------------------------------------------------------------
   // <T>���ָ��λ���ݡ�</T>
   inline TBool GetBit(TInt index){
      return _value & (1 << index);
   }
   //------------------------------------------------------------
   // <T>����ָ��λ���ݡ�</T>
   inline void SetBit(TInt index){
      _value |= (1 << index);
   }
   //------------------------------------------------------------
   // <T>��תָ��λ���ݡ�</T>
   inline void InverseBit(TInt index){
      T flag = (1 << index);
      if(_value & flag){
         _value &= ~flag;
      }else{
         _value |= flag;
      }
   }
   //------------------------------------------------------------
   // <T>�޸�ָ��λ���ݡ�</T>
   inline void ModifyBit(TInt index, TBool value){
      T flag = (1 << index);
      if(value){
         _value |= flag;
      }else{
         _value &= ~flag;
      }
   }
   //------------------------------------------------------------
   // <T>���ָ��λ���ݡ�</T>
   inline void ClearBit(TInt index){
      T flag = (1 << index);
      _value &= ~flag;
   }
   //------------------------------------------------------------
   // <T>�������ָ��</T>
   inline T* Refer(){
      return &_value;
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_BIT_H__
