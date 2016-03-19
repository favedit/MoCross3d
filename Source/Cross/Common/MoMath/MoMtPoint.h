#ifndef __MO_MT_POINT_H__
#define __MO_MT_POINT_H__

#ifndef _MATH_H
#include <math.h>
#endif // _MATH_H

#ifndef __MO_MT_COMMON_H__
#include "MoMtCommon.h"
#endif // __MO_MT_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ά�������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SIntPoint2{
public:
   TInt x;
   TInt y;
public:
   //------------------------------------------------------------
   // <T>�����ά�������ꡣ</T>
   SIntPoint2(){
      x = 0;
      y = 0;
   }
   //------------------------------------------------------------
   // <T>�����ά�������ꡣ</T>
   SIntPoint2(TInt value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����ά�������ꡣ</T>
   SIntPoint2(TInt px, TInt py){
      x = px;
      y = py;
   }
   //------------------------------------------------------------
   // <T>�����ά�������ꡣ</T>
   SIntPoint2(const SIntPoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SIntPoint2& value){
      return (x == value.x) && (y == value.y);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SIntPoint2& value){
      return (x != value.x) || (y != value.y);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TInt value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SIntPoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntPoint2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntPoint2& value){
      x -= value.x;
      y -= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TInt value){
      x *= value;
      y *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TInt value){
      MO_ASSERT(0 != value);
      x /= value;
      y /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0) && (y == 0);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void SetAll(TInt value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntPoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0;
      y = 0;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteInt(x);
      pOutput->WriteInt(y);
   }
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize16(IDataOutput* pOutput){
      pOutput->WriteInt16((TInt16)x);
      pOutput->WriteInt16((TInt16)y);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadInt();
      y = pInput->ReadInt();
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize16(IDataInput* pInput){
      x = pInput->ReadInt16();
      y = pInput->ReadInt16();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά���������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SFloatPoint2{
public:
   TFloat x;
   TFloat y;
public:
   //------------------------------------------------------------
   // <T>�����ά���������ꡣ</T>
   SFloatPoint2(){
      x = 0.0f;
      y = 0.0f;
   }
   //------------------------------------------------------------
   // <T>�����ά���������ꡣ</T>
   SFloatPoint2(TFloat value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����ά���������ꡣ</T>
   SFloatPoint2(TFloat px, TFloat py){
      x = px;
      y = py;
   }
   //------------------------------------------------------------
   // <T>�����ά���������ꡣ</T>
   SFloatPoint2(const SFloatPoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatPoint2& value){
      return (x == value.x) && (y == value.y);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatPoint2& value){
      return (x != value.x) || (y != value.y);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TFloat value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatPoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatPoint2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatPoint2& value){
      x -= value.x;
      y -= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TFloat value){
      x *= value;
      y *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TFloat value){
      MO_ASSERT(0.0f != value);
      x /= value;
      y /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0.0f) && (y == 0.0f);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void SetAll(TFloat value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatPoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TFloat Absolute(){
      return (TFloat)sqrt((x * x) + (y * y));
   }
   //------------------------------------------------------------
   // <T>��λ������</T>
   MO_INLINE void Normalize(){
      TFloat value = Absolute();
      if(value != 0.0f){
         x /= value;
         y /= value;
      }
   }
   //------------------------------------------------------------
   // <T>��þ��롣</T>
   MO_INLINE TFloat Distance(const SFloatPoint2& value){
      TFloat cx = x - value.x;
      TFloat cy = y - value.y;
      return (TFloat)sqrt((cx * cx) + (cy * cy));
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0.0f;
      y = 0.0f;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteFloat(x);
      pOutput->WriteFloat(y);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadFloat();
      y = pInput->ReadFloat();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά˫���������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SDoublePoint2{
public:
   TDouble x;
   TDouble y;
public:
   //------------------------------------------------------------
   // <T>�����ά˫���������ꡣ</T>
   SDoublePoint2(){
      x = 0;
      y = 0;
   }
   //------------------------------------------------------------
   // <T>�����ά˫���������ꡣ</T>
   SDoublePoint2(TDouble value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����ά˫���������ꡣ</T>
   SDoublePoint2(TDouble px, TDouble py){
      x = px;
      y = py;
   }
   //------------------------------------------------------------
   // <T>�����ά˫���������ꡣ</T>
   SDoublePoint2(const SDoublePoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoublePoint2& value){
      return (x == value.x) && (y == value.y);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoublePoint2& value){
      return (x != value.x) || (y != value.y);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TDouble value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SDoublePoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoublePoint2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoublePoint2& value){
      x -= value.x;
      y -= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TDouble value){
      x *= value;
      y *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TDouble value){
      MO_ASSERT(0 != value);
      x /= value;
      y /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0) && (y == 0);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void SetAll(TDouble value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoublePoint2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TDouble Absolute(){
      return sqrt((x * x) + (y * y));
   }
   //------------------------------------------------------------
   // <T>��λ������</T>
   MO_INLINE void Normalize(){
      TDouble value = Absolute();
      if(value != 0){
         x /= value;
         y /= value;
      }
   }
   //------------------------------------------------------------
   // <T>��þ��롣</T>
   MO_INLINE TDouble Distance(const SDoublePoint2& value){
      TDouble cx = x - value.x;
      TDouble cy = y - value.y;
      return sqrt((cx * cx) + (cy * cy));
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0;
      y = 0;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteDouble(x);
      pOutput->WriteDouble(y);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadDouble();
      y = pInput->ReadDouble();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά�������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SIntPoint3{
public:
   TInt x;
   TInt y;
   TInt z;
public:
   //------------------------------------------------------------
   // <T>������ά�������ꡣ</T>
   SIntPoint3(){
      x = 0;
      y = 0;
      z = 0;
   }
   //------------------------------------------------------------
   // <T>������ά�������ꡣ</T>
   SIntPoint3(TInt value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>������ά�������ꡣ</T>
   SIntPoint3(TInt px, TInt py, TInt pz){
      x = px;
      y = py;
      z = pz;
   }
   //------------------------------------------------------------
   // <T>������ά�������ꡣ</T>
   SIntPoint3(const SIntPoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SIntPoint3& value){
      return (x == value.x) && (y == value.y) && (z == value.z);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SIntPoint3& value){
      return (x != value.x) || (y != value.y) || (z != value.z);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TInt value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SIntPoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TInt value){
      x += value;
      y += value;
      z += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntPoint3& value){
      x += value.x;
      y += value.y;
      z += value.z;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TInt value){
      x -= value;
      y -= value;
      z -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntPoint3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TInt value){
      x *= value;
      y *= value;
      z *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TInt value){
      x /= value;
      y /= value;
      z /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0) && (y == 0) && (z == 0);
   }
   //------------------------------------------------------------
   // <T>����ȫ���������ݡ�</T>
   MO_INLINE void SetAll(TInt value = 0){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue, TInt zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntPoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TInt value){
      x += value;
      y += value;
      z += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TInt xValue, TInt yValue, TInt zValue){
      x += xValue;
      y += yValue;
      z += zValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SIntPoint3& value){
      x += value.x;
      y += value.y;
      z += value.z;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TInt value){
      x -= value;
      y -= value;
      z -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TInt xValue, TInt yValue, TInt zValue){
      x -= xValue;
      y -= yValue;
      z -= zValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SIntPoint3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SIntPoint3& source, const SIntPoint3& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SIntPoint3& source, const SIntPoint3& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0;
      y = 0;
      z = 0;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteInt(x);
      pOutput->WriteInt(y);
      pOutput->WriteInt(z);
   }
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize16(IDataOutput* pOutput){
      pOutput->WriteInt16((TInt16)x);
      pOutput->WriteInt16((TInt16)y);
      pOutput->WriteInt16((TInt16)z);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadInt();
      y = pInput->ReadInt();
      z = pInput->ReadInt();
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize16(IDataInput* pInput){
      x = pInput->ReadInt16();
      y = pInput->ReadInt16();
      z = pInput->ReadInt16();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά���������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SFloatPoint3{
public:
   TFloat x;
   TFloat y;
   TFloat z;
public:
   //------------------------------------------------------------
   // <T>������ά���������ꡣ</T>
   SFloatPoint3(){
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
   }
   //------------------------------------------------------------
   // <T>������ά���������ꡣ</T>
   SFloatPoint3(TFloat value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>������ά���������ꡣ</T>
   SFloatPoint3(TFloat px, TFloat py, TFloat pz){
      x = px;
      y = py;
      z = pz;
   }
   //------------------------------------------------------------
   // <T>������ά���������ꡣ</T>
   SFloatPoint3(const SFloatPoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatPoint3& value){
      return (x == value.x) && (y == value.y) && (z == value.z);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatPoint3& value){
      return (x != value.x) || (y != value.y) || (z != value.z);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TFloat value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatPoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TFloat value){
      x += value;
      y += value;
      z += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatPoint3& value){
      x += value.x;
      y += value.y;
      z += value.z;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TFloat value){
      x -= value;
      y -= value;
      z -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatPoint3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TFloat value){
      x *= value;
      y *= value;
      z *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TFloat value){
      x /= value;
      y /= value;
      z /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0.0f) && (y == 0.0f) && (z == 0.0f);
   }
   //------------------------------------------------------------
   // <T>����ȫ���������ݡ�</T>
   MO_INLINE void SetAll(TFloat value = 0.0f){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue, TFloat zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatPoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TFloat value){
      x += value;
      y += value;
      z += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TFloat xValue, TFloat yValue, TFloat zValue){
      x += xValue;
      y += yValue;
      z += zValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SFloatPoint3& value){
      x += value.x;
      y += value.y;
      z += value.z;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TFloat value){
      x -= value;
      y -= value;
      z -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TFloat xValue, TFloat yValue, TFloat zValue){
      x -= xValue;
      y -= yValue;
      z -= zValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SFloatPoint3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>��С����</T>
   MO_INLINE void Min(){
      x = -MO_TP_FLOAT_MAX;
      y = -MO_TP_FLOAT_MAX;
      z = -MO_TP_FLOAT_MAX;
   }
   //------------------------------------------------------------
   // <T>�����</T>
   MO_INLINE void Max(){
      x = MO_TP_FLOAT_MAX;
      y = MO_TP_FLOAT_MAX;
      z = MO_TP_FLOAT_MAX;
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SFloatPoint3& value){
      if(x > value.x){
         x = value.x;
      }
      if(y > value.y){
         y = value.y;
      }
      if(z > value.z){
         z = value.z;
      }
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SFloatPoint3& source, const SFloatPoint3& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SFloatPoint3& value){
      if(x < value.x){
         x = value.x;
      }
      if(y < value.y){
         y = value.y;
      }
      if(z < value.z){
         z = value.z;
      }
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SFloatPoint3& source, const SFloatPoint3& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
   }
public:
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TFloat Absolute(){
      return (TFloat)sqrt((x * x) + (y * y) + (z * z));
   }
   //------------------------------------------------------------
   // <T>��λ������</T>
   MO_INLINE void Normalize(){
      TFloat value = Absolute();
      if(value != 0.0f){
         x /= value;
         y /= value;
         z /= value;
      }
   }
   //------------------------------------------------------------
   // <T>��þ��롣</T>
   MO_INLINE TFloat Distance(const SFloatPoint3& value){
      TFloat cx = x - value.x;
      TFloat cy = y - value.y;
      TFloat cz = z - value.z;
      return (TFloat)sqrt((cx * cx) + (cy * cy) + (cz * cz));
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteFloat(x);
      pOutput->WriteFloat(y);
      pOutput->WriteFloat(z);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadFloat();
      y = pInput->ReadFloat();
      z = pInput->ReadFloat();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά˫���������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SDoublePoint3{
public:
   TDouble x;
   TDouble y;
   TDouble z;
public:
   //------------------------------------------------------------
   // <T>������ά˫���������ꡣ</T>
   SDoublePoint3(){
      x = 0;
      y = 0;
      z = 0;
   }
   //------------------------------------------------------------
   // <T>������ά˫���������ꡣ</T>
   SDoublePoint3(TDouble value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>������ά˫���������ꡣ</T>
   SDoublePoint3(TDouble px, TDouble py, TDouble pz){
      x = px;
      y = py;
      z = pz;
   }
   //------------------------------------------------------------
   // <T>������ά˫���������ꡣ</T>
   SDoublePoint3(const SDoublePoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoublePoint3& value){
      return (x == value.x) && (y == value.y) && (z == value.z);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoublePoint3& value){
      return (x != value.x) || (y != value.y) || (z != value.z);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TDouble value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SDoublePoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TDouble value){
      x += value;
      y += value;
      z += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoublePoint3& value){
      x += value.x;
      y += value.y;
      z += value.z;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TDouble value){
      x -= value;
      y -= value;
      z -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoublePoint3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TDouble value){
      x *= value;
      y *= value;
      z *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TDouble value){
      x /= value;
      y /= value;
      z /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0) && (y == 0) && (z == 0);
   }
   //------------------------------------------------------------
   // <T>����ȫ���������ݡ�</T>
   MO_INLINE void SetAll(TDouble value = 0){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue, TDouble zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoublePoint3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TDouble value){
      x += value;
      y += value;
      z += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TDouble xValue, TDouble yValue, TDouble zValue){
      x += xValue;
      y += yValue;
      z += zValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SDoublePoint3& value){
      x += value.x;
      y += value.y;
      z += value.z;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TDouble value){
      x -= value;
      y -= value;
      z -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TDouble xValue, TDouble yValue, TDouble zValue){
      x -= xValue;
      y -= yValue;
      z -= zValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SDoublePoint3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SDoublePoint3& source, const SDoublePoint3& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SDoublePoint3& source, const SDoublePoint3& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
   }
public:
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TDouble Absolute(){
      return sqrt((x * x) + (y * y) + (z * z));
   }
   //------------------------------------------------------------
   // <T>��λ������</T>
   MO_INLINE void Normalize(){
      TDouble value = Absolute();
      if(value != 0){
         x /= value;
         y /= value;
         z /= value;
      }
   }
   //------------------------------------------------------------
   // <T>��þ��롣</T>
   MO_INLINE TDouble Distance(const SDoublePoint3& value){
      TDouble cx = x - value.x;
      TDouble cy = y - value.y;
      TDouble cz = z - value.z;
      return sqrt((cx * cx) + (cy * cy) + (cz * cz));
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0;
      y = 0;
      z = 0;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteDouble(x);
      pOutput->WriteDouble(y);
      pOutput->WriteDouble(z);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadDouble();
      y = pInput->ReadDouble();
      z = pInput->ReadDouble();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά�������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SIntPoint4{
public:
   TInt x;
   TInt y;
   TInt z;
   TInt w;
public:
   //------------------------------------------------------------
   // <T>������ά�������ꡣ</T>
   SIntPoint4(){
      x = 0;
      y = 0;
      z = 0;
      w = 0;
   }
   //------------------------------------------------------------
   // <T>������ά�������ꡣ</T>
   SIntPoint4(TInt value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>������ά�������ꡣ</T>
   SIntPoint4(TInt px, TInt py, TInt pz, TInt pw){
      x = px;
      y = py;
      z = pz;
      w = pw;
   }
   //------------------------------------------------------------
   // <T>������ά�������ꡣ</T>
   SIntPoint4(const SIntPoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SIntPoint4& value){
      return (x == value.x) && (y == value.y) && (z == value.z) && (w == value.w);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SIntPoint4& value){
      return (x != value.x) || (y != value.y) || (z != value.z) || (w != value.w);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TInt value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SIntPoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TInt value){
      x += value;
      y += value;
      z += value;
      w += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntPoint4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TInt value){
      x -= value;
      y -= value;
      z -= value;
      w -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntPoint4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TInt value){
      x *= value;
      y *= value;
      z *= value;
      w *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TInt value){
      x /= value;
      y /= value;
      z /= value;
      w /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0) && (y == 0) && (z == 0) && (w == 0);
   }
   //------------------------------------------------------------
   // <T>����ȫ���������ݡ�</T>
   MO_INLINE void SetAll(TInt value = 0){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue, TInt zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue, TInt zValue, TInt wValue){
      x = xValue;
      y = yValue;
      z = zValue;
      w = wValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntPoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TInt value){
      x += value;
      y += value;
      z += value;
      w += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SIntPoint4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TInt value){
      x -= value;
      y -= value;
      z -= value;
      w -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SIntPoint4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.w;
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SIntPoint4& source, const SIntPoint4& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
      w = MO_LIB_MIN(source.w, target.w);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SIntPoint4& source, const SIntPoint4& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
      w = MO_LIB_MAX(source.w, target.w);
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0;
      y = 0;
      z = 0;
      w = 0;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteInt(x);
      pOutput->WriteInt(y);
      pOutput->WriteInt(z);
      pOutput->WriteInt(w);
   }
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize16(IDataOutput* pOutput){
      pOutput->WriteInt16((TInt16)x);
      pOutput->WriteInt16((TInt16)y);
      pOutput->WriteInt16((TInt16)z);
      pOutput->WriteInt16((TInt16)w);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadInt();
      y = pInput->ReadInt();
      z = pInput->ReadInt();
      w = pInput->ReadInt();
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize16(IDataInput* pInput){
      x = pInput->ReadInt16();
      y = pInput->ReadInt16();
      z = pInput->ReadInt16();
      w = pInput->ReadInt16();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά���������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SFloatPoint4{
public:
   TFloat x;
   TFloat y;
   TFloat z;
   TFloat w;
public:
   //------------------------------------------------------------
   // <T>������ά���������ꡣ</T>
   SFloatPoint4(){
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
      w = 0.0f;
   }
   //------------------------------------------------------------
   // <T>������ά���������ꡣ</T>
   SFloatPoint4(TFloat value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>������ά���������ꡣ</T>
   SFloatPoint4(TFloat px, TFloat py, TFloat pz, TFloat pw){
      x = px;
      y = py;
      z = pz;
      w = pw;
   }
   //------------------------------------------------------------
   // <T>������ά���������ꡣ</T>
   SFloatPoint4(const SFloatPoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatPoint4& value){
      return (x == value.x) && (y == value.y) && (z == value.z) && (w == value.w);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatPoint4& value){
      return (x != value.x) || (y != value.y) || (z != value.z) || (w != value.w);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TFloat value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatPoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TFloat value){
      x += value;
      y += value;
      z += value;
      w += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatPoint4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TFloat value){
      x -= value;
      y -= value;
      z -= value;
      w -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatPoint4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TFloat value){
      x *= value;
      y *= value;
      z *= value;
      w *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TFloat value){
      x /= value;
      y /= value;
      z /= value;
      w /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0.0f) && (y == 0.0f) && (z == 0.0f) && (w == 0.0f);
   }
   //------------------------------------------------------------
   // <T>����ȫ���������ݡ�</T>
   MO_INLINE void SetAll(TFloat value = 0.0f){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue, TFloat zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue, TFloat zValue, TFloat wValue){
      x = xValue;
      y = yValue;
      z = zValue;
      w = wValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatPoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TFloat value){
      x += value;
      y += value;
      z += value;
      w += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SFloatPoint4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TFloat value){
      x -= value;
      y -= value;
      z -= value;
      w -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SFloatPoint4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.w;
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SFloatPoint4& source, const SFloatPoint4& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
      w = MO_LIB_MIN(source.w, target.w);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SFloatPoint4& source, const SFloatPoint4& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
      w = MO_LIB_MAX(source.w, target.w);
   }
public:
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   TFloat Absolute(){
      return (TFloat)sqrt((x * x) + (y * y) + (z * z) + (w * w));
   }
   //------------------------------------------------------------
   // <T>��λ������</T>
   MO_INLINE void Normalize(){
      TFloat value = Absolute();
      if(value != 0.0f){
         x /= value;
         y /= value;
         z /= value;
         w /= value;
      }
   }
   //------------------------------------------------------------
   // <T>��þ��롣</T>
   MO_INLINE TFloat Distance(const SFloatPoint4& value){
      TFloat cx = x - value.x;
      TFloat cy = y - value.y;
      TFloat cz = z - value.z;
      TFloat cw = w - value.w;
      return (TFloat)sqrt((cx * cx) + (cy * cy) + (cz * cz) + (cw * cw));
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
      w = 0.0f;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteFloat(x);
      pOutput->WriteFloat(y);
      pOutput->WriteFloat(z);
      pOutput->WriteFloat(w);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadFloat();
      y = pInput->ReadFloat();
      z = pInput->ReadFloat();
      w = pInput->ReadFloat();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��ά˫���������ꡣ</T>
//============================================================
struct MO_MT_DECLARE SDoublePoint4{
public:
   TDouble x;
   TDouble y;
   TDouble z;
   TDouble w;
public:
   //------------------------------------------------------------
   // <T>������ά˫���������ꡣ</T>
   SDoublePoint4(){
      x = 0;
      y = 0;
      z = 0;
      w = 0;
   }
   //------------------------------------------------------------
   // <T>������ά˫���������ꡣ</T>
   SDoublePoint4(TDouble value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>������ά˫���������ꡣ</T>
   SDoublePoint4(TDouble px, TDouble py, TDouble pz, TDouble pw){
      x = px;
      y = py;
      z = pz;
      w = pw;
   }
   //------------------------------------------------------------
   // <T>������ά˫���������ꡣ</T>
   SDoublePoint4(const SDoublePoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoublePoint4& value){
      return (x == value.x) && (y == value.y) && (z == value.z) && (w == value.w);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoublePoint4& value){
      return (x != value.x) || (y != value.y) || (z != value.z) || (w != value.w);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TDouble value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SDoublePoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TDouble value){
      x += value;
      y += value;
      z += value;
      w += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoublePoint4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TDouble value){
      x -= value;
      y -= value;
      z -= value;
      w -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoublePoint4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TDouble value){
      x *= value;
      y *= value;
      z *= value;
      w *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TDouble value){
      x /= value;
      y /= value;
      z /= value;
      w /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (x == 0) && (y == 0) && (z == 0) && (w == 0);
   }
   //------------------------------------------------------------
   // <T>����ȫ���������ݡ�</T>
   MO_INLINE void SetAll(TDouble value = 0){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue, TDouble zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue, TDouble zValue, TDouble wValue){
      x = xValue;
      y = yValue;
      z = zValue;
      w = wValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoublePoint4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TDouble value){
      x += value;
      y += value;
      z += value;
      w += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SDoublePoint4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TDouble value){
      x -= value;
      y -= value;
      z -= value;
      w -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SDoublePoint4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.w;
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SDoublePoint4& source, const SDoublePoint4& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
      w = MO_LIB_MIN(source.w, target.w);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SDoublePoint4& source, const SDoublePoint4& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
      w = MO_LIB_MAX(source.w, target.w);
   }
public:
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   TDouble Absolute(){
      return sqrt((x * x) + (y * y) + (z * z) + (w * w));
   }
   //------------------------------------------------------------
   // <T>��λ������</T>
   MO_INLINE void Normalize(){
      TDouble value = Absolute();
      if(value != 0){
         x /= value;
         y /= value;
         z /= value;
         w /= value;
      }
   }
   //------------------------------------------------------------
   // <T>��þ��롣</T>
   MO_INLINE TDouble Distance(const SDoublePoint4& value){
      TDouble cx = x - value.x;
      TDouble cy = y - value.y;
      TDouble cz = z - value.z;
      TDouble cw = w - value.w;
      return sqrt((cx * cx) + (cy * cy) + (cz * cz) + (cw * cw));
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      x = 0;
      y = 0;
      z = 0;
      w = 0;
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      pOutput->WriteDouble(x);
      pOutput->WriteDouble(y);
      pOutput->WriteDouble(z);
      pOutput->WriteDouble(w);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      x = pInput->ReadDouble();
      y = pInput->ReadDouble();
      z = pInput->ReadDouble();
      w = pInput->ReadDouble();
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

MO_NAMESPACE_END

#endif // __MO_MT_POINT_H__
