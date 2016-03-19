#ifndef __MO_MT_SIZE_H__
#define __MO_MT_SIZE_H__

#ifndef _MATH_H
#include <math.h>
#endif // _MATH_H

#ifndef __MO_MT_COMMON_H__
#include "MoMtCommon.h"
#endif // __MO_MT_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ά������С��</T>
//============================================================
struct MO_MT_DECLARE SIntSize2{
public:
   TInt width;
   TInt height;
public:
   //------------------------------------------------------------
   // <T>�����ά������С��</T>
   SIntSize2(){
      width = 0;
      height = 0;
   }
   //------------------------------------------------------------
   // <T>�����ά������С��</T>
   SIntSize2(TInt value){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����ά������С��</T>
   SIntSize2(TInt widthValue, TInt heightValue){
      width = widthValue;
      height = heightValue;
   }
   //------------------------------------------------------------
   // <T>�����ά������С��</T>
   SIntSize2(const SIntSize2& value){
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator == (const SIntSize2& value){
      return ((width == value.width) && (height == value.height));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator != (const SIntSize2& value){
      return ((width != value.width) || (height != value.height));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator = (TInt value){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator = (const SIntSize2& value){
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (width == 0) && (height == 0);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void SetAll(TInt value = 0){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt widthValue = 0, TInt heightValue = 0){
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntSize2& value){
      width = value.width;
      height = value.height;
   }
   //------------------------------------------------------------
   MO_INLINE TInt Square(){
      return width * height;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteInt(width);
      pOutput->WriteInt(height);
   }
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize16(IDataOutput* pOutput){
      pOutput->WriteInt16((TInt16)width);
      pOutput->WriteInt16((TInt16)height);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      width = pInput->ReadInt();
      height = pInput->ReadInt();
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize16(IDataInput* pInput){
      width = pInput->ReadInt16();
      height = pInput->ReadInt16();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά��������С��</T>
//============================================================
struct MO_MT_DECLARE SFloatSize2{
public:
   TFloat width;
   TFloat height;
public:
   //------------------------------------------------------------
   // <T>�����ά��������С��</T>
   SFloatSize2(){
      width = 0.0f;
      height = 0.0f;
   }
   //------------------------------------------------------------
   // <T>�����ά��������С��</T>
   SFloatSize2(TFloat value){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����ά��������С��</T>
   SFloatSize2(TFloat widthValue, TFloat heightValue){
      width = widthValue;
      height = heightValue;
   }
   //------------------------------------------------------------
   // <T>�����ά��������С��</T>
   SFloatSize2(const SFloatSize2& value){
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator == (const SFloatSize2& value){
      return ((width == value.width) && (height == value.height));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator != (const SFloatSize2& value){
      return ((width != value.width) || (height != value.height));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator = (TFloat value){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator = (const SFloatSize2& value){
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (width == 0.0f) && (height == 0.0f);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void SetAll(TFloat value = 0.0f){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat widthValue = 0.0f, TFloat heightValue = 0.0f){
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatSize2& value){
      width = value.width;
      height = value.height;
   }
   //------------------------------------------------------------
   MO_INLINE TFloat Square(){
      return width * height;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteFloat(width);
      pOutput->WriteFloat(height);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      width = pInput->ReadFloat();
      height = pInput->ReadFloat();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά˫��������С��</T>
//============================================================
struct MO_MT_DECLARE SDoubleSize2{
public:
   TDouble width;
   TDouble height;
public:
   //------------------------------------------------------------
   // <T>�����ά˫��������С��</T>
   SDoubleSize2(){
      width = 0;
      height = 0;
   }
   //------------------------------------------------------------
   // <T>�����ά˫��������С��</T>
   SDoubleSize2(TDouble value){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����ά˫��������С��</T>
   SDoubleSize2(TDouble widthValue, TDouble heightValue){
      width = widthValue;
      height = heightValue;
   }
   //------------------------------------------------------------
   // <T>�����ά˫��������С��</T>
   SDoubleSize2(const SDoubleSize2& value){
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator == (const SDoubleSize2& value){
      return ((width == value.width) && (height == value.height));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator != (const SDoubleSize2& value){
      return ((width != value.width) || (height != value.height));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator = (TDouble value){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator = (const SDoubleSize2& value){
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (width == 0) && (height == 0);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void SetAll(TDouble value = 0){
      width = value;
      height = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble widthValue = 0, TDouble heightValue = 0){
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoubleSize2& value){
      width = value.width;
      height = value.height;
   }
   //------------------------------------------------------------
   MO_INLINE TDouble Square(){
      return width * height;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteDouble(width);
      pOutput->WriteDouble(height);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      width = pInput->ReadDouble();
      height = pInput->ReadDouble();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά������С��</T>
//============================================================
struct MO_MT_DECLARE SIntSize3{
public:
   TInt width;
   TInt height;
   TInt deep;
public:
   //------------------------------------------------------------
   // <T>������ά������С��</T>
   SIntSize3(){
      width = 0;
      height = 0;
      deep = 0;
   }
   //------------------------------------------------------------
   // <T>������ά������С��</T>
   SIntSize3(TInt value){
      width = value;
      height = value;
      deep = value;
   }
   //------------------------------------------------------------
   // <T>������ά������С��</T>
   SIntSize3(TInt widthValue, TInt heightValue, TInt deepValue){
      width = widthValue;
      height = heightValue;
      deep = deepValue;
   }
   //------------------------------------------------------------
   // <T>������ά������С��</T>
   SIntSize3(const SIntSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator ==(const SIntSize3& value){
      return ((width == value.width) && (height == value.height) && (deep == value.deep));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator !=(const SIntSize3& value){
      return ((width != value.width) || (height != value.height) || (deep != value.deep));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TInt value){
      width = value;
      height = value;
      deep = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SIntSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (width == 0) && (height == 0) && (deep == 0);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt widthValue = 0, TInt heightValue = 0, TInt deepValue = 0){
      width = widthValue;
      height = heightValue;
      deep = deepValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   MO_INLINE TInt Square(){
      return width * height * deep;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteInt(width);
      pOutput->WriteInt(height);
      pOutput->WriteInt(deep);
   }
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize16(IDataOutput* pOutput){
      pOutput->WriteInt16((TInt16)width);
      pOutput->WriteInt16((TInt16)height);
      pOutput->WriteInt16((TInt16)deep);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      width = pInput->ReadInt();
      height = pInput->ReadInt();
      deep = pInput->ReadInt();
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize16(IDataInput* pInput){
      width = pInput->ReadInt16();
      height = pInput->ReadInt16();
      deep = pInput->ReadInt16();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά��������С��</T>
//============================================================
struct MO_MT_DECLARE SFloatSize3{
public:
   TFloat width;
   TFloat height;
   TFloat deep;
public:
   //------------------------------------------------------------
   // <T>������ά��������С��</T>
   SFloatSize3(){
      width = 0.0f;
      height = 0.0f;
      deep = 0.0f;
   }
   //------------------------------------------------------------
   // <T>������ά��������С��</T>
   SFloatSize3(TFloat value){
      width = value;
      height = value;
      deep = value;
   }
   //------------------------------------------------------------
   // <T>������ά��������С��</T>
   SFloatSize3(TFloat widthValue, TFloat heightValue, TFloat deepValue){
      width = widthValue;
      height = heightValue;
      deep = deepValue;
   }
   //------------------------------------------------------------
   // <T>������ά��������С��</T>
   SFloatSize3(const SFloatSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator ==(const SFloatSize3& value){
      return ((width == value.width) && (height == value.height) && (deep == value.deep));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator !=(const SFloatSize3& value){
      return ((width != value.width) || (height != value.height) || (deep != value.deep));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TFloat value){
      width = value;
      height = value;
      deep = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (width == 0.0f) && (height == 0.0f) && (deep == 0.0f);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat widthValue = 0.0f, TFloat heightValue = 0.0f, TFloat deepValue = 0.0f){
      width = widthValue;
      height = heightValue;
      deep = deepValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   MO_INLINE TFloat Square(){
      return width * height * deep;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteFloat(width);
      pOutput->WriteFloat(height);
      pOutput->WriteFloat(deep);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      width = pInput->ReadFloat();
      height = pInput->ReadFloat();
      deep = pInput->ReadFloat();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά˫��������С��</T>
//============================================================
struct MO_MT_DECLARE SDoubleSize3{
public:
   TDouble width;
   TDouble height;
   TDouble deep;
public:
   //------------------------------------------------------------
   // <T>������ά˫��������С��</T>
   SDoubleSize3(){
      width = 0;
      height = 0;
      deep = 0;
   }
   //------------------------------------------------------------
   // <T>������ά˫��������С��</T>
   SDoubleSize3(TDouble value){
      width = value;
      height = value;
      deep = value;
   }
   //------------------------------------------------------------
   // <T>������ά˫��������С��</T>
   SDoubleSize3(TDouble widthValue, TDouble heightValue, TDouble deepValue){
      width = widthValue;
      height = heightValue;
      deep = deepValue;
   }
   //------------------------------------------------------------
   // <T>������ά˫��������С��</T>
   SDoubleSize3(const SDoubleSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator ==(const SDoubleSize3& value){
      return ((width == value.width) && (height == value.height) && (deep == value.deep));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator !=(const SDoubleSize3& value){
      return ((width != value.width) || (height != value.height) || (deep != value.deep));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TDouble value){
      width = value;
      height = value;
      deep = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SDoubleSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (width == 0) && (height == 0) && (deep == 0);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble widthValue = 0, TDouble heightValue = 0, TDouble deepValue = 0){
      width = widthValue;
      height = heightValue;
      deep = deepValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoubleSize3& value){
      width = value.width;
      height = value.height;
      deep = value.deep;
   }
public:
   //------------------------------------------------------------
   MO_INLINE TDouble Square(){
      return width * height * deep;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteDouble(width);
      pOutput->WriteDouble(height);
      pOutput->WriteDouble(deep);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      width = pInput->ReadDouble();
      height = pInput->ReadDouble();
      deep = pInput->ReadDouble();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

MO_NAMESPACE_END

#endif // __MO_MT_SIZE_H__
