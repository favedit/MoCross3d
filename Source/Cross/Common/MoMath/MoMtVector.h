#ifndef __MO_MT_VECTOR_H__
#define __MO_MT_VECTOR_H__

#ifndef _MATH_H
#include <math.h>
#endif // _MATH_H

#ifndef __MO_MT_COMMON_H__
#include "MoMtCommon.h"
#endif // __MO_MT_COMMON_H__

#ifndef __MO_MT_POINT_H__
#include "MoMtPoint.h"
#endif // __MO_MT_POINT_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ά����ʸ����</T>
//============================================================
struct MO_MT_DECLARE SIntVector2{
public:
   TInt x;
   TInt y;
public:
   //------------------------------------------------------------
   // <T>�����ά����ʸ����</T>
   SIntVector2(){
      x = 0;
      y = 0;
   }
   //------------------------------------------------------------
   // <T>�����ά����ʸ����</T>
   SIntVector2(TInt value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����ά����ʸ����</T>
   SIntVector2(TInt px, TInt py){
      x = px;
      y = py;
   }
   //------------------------------------------------------------
   // <T>�����ά����ʸ����</T>
   SIntVector2(const SIntVector2& value){
      x = value.x;
      y = value.y;
   }
   //------------------------------------------------------------
   // <T>�����ά����ʸ����</T>
   SIntVector2(const SIntPoint2& source, const SIntPoint2& target){
      x = source.x - target.x;
      y = source.y - target.y;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator ==(const SIntVector2& value){
      return ((x == value.x) && (y == value.y));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator !=(const SIntVector2& value){
      return ((x != value.x) || (y != value.y));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TInt value){
      x = y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SIntVector2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TInt value){
      x += value;
      y += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntVector2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TInt value){
      x -= value;
      y -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntVector2& value){
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
      x /= value;
      y /= value;
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TInt value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SIntPoint2& source, const SIntPoint2& target){
      x = target.x - source.x;
      y = target.y - source.y;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntVector2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TInt xValue, TInt yValue){
      x += xValue;
      y += yValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SIntVector2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TInt xValue, TInt yValue){
      x -= xValue;
      y -= yValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SIntVector2& value){
      x -= value.x;
      y -= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TInt xValue, TInt yValue){
      x *= xValue;
      y *= yValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SIntVector2& value){
      x *= value.x;
      y *= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SIntVector2 MulToVector2(TInt value){
      return SIntVector2(x * value, y * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TInt xValue, TInt yValue){
      x /= xValue;
      y /= yValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SIntVector2& value){
      x /= value.x;
      y /= value.y;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SIntVector2& source, const SIntVector2& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SIntVector2& source, const SIntVector2& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
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
// <T>��ά������ʸ����</T>
//============================================================
struct MO_MT_DECLARE SFloatVector2{
public:
   TFloat x;
   TFloat y;
public:
   //------------------------------------------------------------
   // <T>�����ά������ʸ����</T>
   SFloatVector2(){
      x = 0.0f;
      y = 0.0f;
   }
   //------------------------------------------------------------
   // <T>�����ά������ʸ����</T>
   SFloatVector2(TFloat value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����ά������ʸ����</T>
   SFloatVector2(TFloat px, TFloat py){
      x = px;
      y = py;
   }
   //------------------------------------------------------------
   // <T>�����ά������ʸ����</T>
   SFloatVector2(const SFloatVector2& value){
      x = value.x;
      y = value.y;
   }
   //------------------------------------------------------------
   // <T>�����ά������ʸ����</T>
   SFloatVector2(const SFloatPoint2& source, const SFloatPoint2& target){
      x = source.x - target.x;
      y = source.y - target.y;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator ==(const SFloatVector2& value){
      return ((x == value.x) && (y == value.y));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator !=(const SFloatVector2& value){
      return ((x != value.x) || (y != value.y));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TFloat value){
      x = y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatVector2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TFloat value){
      x += value;
      y += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatVector2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TFloat value){
      x -= value;
      y -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatVector2& value){
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
      x /= value;
      y /= value;
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TFloat value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatPoint2& source, const SFloatPoint2& target){
      x = target.x - source.x;
      y = target.y - source.y;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatPoint2& source, const SFloatPoint2& target, TBool normalize){
      x = target.x - source.x;
      y = target.y - source.y;
      if(normalize){
         Normalize();
      }
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatVector2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TFloat xValue, TFloat yValue){
      x += xValue;
      y += yValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SFloatVector2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TFloat xValue, TFloat yValue){
      x -= xValue;
      y -= yValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SFloatVector2& value){
      x -= value.x;
      y -= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TFloat xValue, TFloat yValue){
      x *= xValue;
      y *= yValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SFloatVector2& value){
      x *= value.x;
      y *= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SFloatVector2 MulToVector2(TFloat value){
      return SFloatVector2(x * value, y * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TFloat xValue, TFloat yValue){
      x /= xValue;
      y /= yValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SFloatVector2& value){
      x /= value.x;
      y /= value.y;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SFloatVector2& source, const SFloatVector2& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SFloatVector2& source, const SFloatVector2& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
   }
   //------------------------------------------------------------
   MO_INLINE TFloat Absolute() const{
      return (TFloat)sqrt((x * x) + (y * y));
   }
   //------------------------------------------------------------
   MO_INLINE void Normalize(){
      TFloat value = Absolute();
      if(value != 0.0f){
         x /= value;
         y /= value;
      }
   }
   //------------------------------------------------------------
   // <T>����нǡ�</T>
   TFloat Angle(const SFloatVector2& value){
      TFloat result = (x * value.x) + (y * value.y);
      result /= Absolute();
      result /= value.Absolute();
      return (TFloat)acos(result);
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
// <T>��ά˫������ʸ����</T>
//============================================================
struct MO_MT_DECLARE SDoubleVector2{
public:
   TDouble x;
   TDouble y;
public:
   //------------------------------------------------------------
   // <T>�����ά˫������ʸ����</T>
   SDoubleVector2(){
      x = 0;
      y = 0;
   }
   //------------------------------------------------------------
   // <T>�����ά˫������ʸ����</T>
   SDoubleVector2(TDouble value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�����ά˫������ʸ����</T>
   SDoubleVector2(TDouble px, TDouble py){
      x = px;
      y = py;
   }
   //------------------------------------------------------------
   // <T>�����ά˫������ʸ����</T>
   SDoubleVector2(const SDoubleVector2& value){
      x = value.x;
      y = value.y;
   }
   //------------------------------------------------------------
   // <T>�����ά˫������ʸ����</T>
   SDoubleVector2(const SDoublePoint2& source, const SDoublePoint2& target){
      x = source.x - target.x;
      y = source.y - target.y;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator ==(const SDoubleVector2& value){
      return ((x == value.x) && (y == value.y));
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator !=(const SDoubleVector2& value){
      return ((x != value.x) || (y != value.y));
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TDouble value){
      x = y = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SDoubleVector2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TDouble value){
      x += value;
      y += value;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoubleVector2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TDouble value){
      x -= value;
      y -= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoubleVector2& value){
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
      x /= value;
      y /= value;
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TDouble value){
      x = value;
      y = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SDoublePoint2& source, const SDoublePoint2& target){
      x = target.x - source.x;
      y = target.y - source.y;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SDoublePoint2& source, const SDoublePoint2& target, TBool normalize){
      x = target.x - source.x;
      y = target.y - source.y;
      if(normalize){
         Normalize();
      }
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoubleVector2& value){
      x = value.x;
      y = value.y;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TDouble xValue, TDouble yValue){
      x += xValue;
      y += yValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SDoubleVector2& value){
      x += value.x;
      y += value.y;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TDouble xValue, TDouble yValue){
      x -= xValue;
      y -= yValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SDoubleVector2& value){
      x -= value.x;
      y -= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TDouble xValue, TDouble yValue){
      x *= xValue;
      y *= yValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SDoubleVector2& value){
      x *= value.x;
      y *= value.y;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SDoubleVector2 MulToVector2(TDouble value){
      return SDoubleVector2(x * value, y * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TDouble xValue, TDouble yValue){
      x /= xValue;
      y /= yValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SDoubleVector2& value){
      x /= value.x;
      y /= value.y;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SDoubleVector2& source, const SDoubleVector2& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SDoubleVector2& source, const SDoubleVector2& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
   }
   //------------------------------------------------------------
   MO_INLINE TDouble Absolute() const{
      return sqrt((x * x) + (y * y));
   }
   //------------------------------------------------------------
   MO_INLINE void Normalize(){
      TDouble value = Absolute();
      if(value != 0){
         x /= value;
         y /= value;
      }
   }
   //------------------------------------------------------------
   // <T>����нǡ�</T>
   TDouble Angle(const SDoubleVector2& value){
      TDouble result = (x * value.x) + (y * value.y);
      result /= Absolute();
      result /= value.Absolute();
      return acos(result);
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
// <T>��ά����ʸ����</T>
//============================================================
struct MO_MT_DECLARE SIntVector3{
public:
   TInt x;
   TInt y;
   TInt z;
public:
   //------------------------------------------------------------
   // <T>������ά����ʸ����</T>
   SIntVector3(){
      x = 0;
      y = 0;
      z = 0;
   }
   //------------------------------------------------------------
   // <T>������ά����ʸ����</T>
   SIntVector3(TInt value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>������ά����ʸ����</T>
   SIntVector3(TInt xValue, TInt yValue, TInt zValue){
      Set(xValue, yValue, zValue);
   }
   //------------------------------------------------------------
   // <T>������ά����ʸ����</T>
   SIntVector3(const SIntPoint3& source, const SIntPoint3& target){
      Set(source, target);
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SIntVector3& value){
      return (x == value.x) && (y == value.y) && (z == value.z);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SIntVector3& value){
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
   MO_INLINE void operator=(const SIntVector3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TInt value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntVector3& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TInt value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntVector3& value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TInt value){
      Mul(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TInt value){
      Div(value);
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TInt value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue, TInt zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SIntPoint3& source, const SIntPoint3& target){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntVector3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TInt xValue, TInt yValue, TInt zValue){
      x += xValue;
      y += yValue;
      z += zValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SIntVector3& value){
      x += value.x;
      y += value.y;
      z += value.z;
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
   MO_INLINE void Sub(const SIntVector3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TInt xValue, TInt yValue, TInt zValue){
      x *= xValue;
      y *= yValue;
      z *= zValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SIntVector3& value){
      x *= value.x;
      y *= value.y;
      z *= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SIntVector3 MulToVector3(TInt value){
      return SIntVector3(x * value, y * value, z * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TInt xValue, TInt yValue, TInt zValue){
      x /= xValue;
      y /= yValue;
      z /= zValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SIntVector3& value){
      x /= value.x;
      y /= value.y;
      z /= value.z;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SIntVector3& source, const SIntVector3& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SIntVector3& source, const SIntVector3& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
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
// <T>��ά������ʸ����</T>
//============================================================
struct MO_MT_DECLARE SFloatVector3{
public:
   TFloat x;
   TFloat y;
   TFloat z;
public:
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector3(){
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
   }
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector3(TFloat value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector3(TFloat xValue, TFloat yValue, TFloat zValue){
      Set(xValue, yValue, zValue);
   }
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector3(const SFloatPoint3& source, const SFloatPoint3& target){
      Set(source, target);
   }
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector3(const SFloatPoint3& source, const SFloatPoint3& target, TBool normalize){
      Set(source, target, normalize);
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatVector3& value){
      return (x == value.x) && (y == value.y) && (z == value.z);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatVector3& value){
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
   MO_INLINE void operator=(const SFloatVector3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TFloat value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatVector3& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TFloat value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatVector3& value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TFloat value){
      Mul(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TFloat value){
      Div(value);
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TFloat value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue, TFloat zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatPoint3& source, const SFloatPoint3& target){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatPoint3& source, const SFloatPoint3& target, TBool normalize){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
      if(normalize){
         Normalize();
      }
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatVector3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TFloat xValue, TFloat yValue, TFloat zValue){
      x += xValue;
      y += yValue;
      z += zValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SFloatVector3& value){
      x += value.x;
      y += value.y;
      z += value.z;
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
   MO_INLINE void Sub(const SFloatVector3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TFloat xValue, TFloat yValue, TFloat zValue){
      x *= xValue;
      y *= yValue;
      z *= zValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SFloatVector3& value){
      x *= value.x;
      y *= value.y;
      z *= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SFloatVector3 MulToVector3(TFloat value){
      return SFloatVector3(x * value, y * value, z * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TFloat xValue, TFloat yValue, TFloat zValue){
      x /= xValue;
      y /= yValue;
      z /= zValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SFloatVector3& value){
      x /= value.x;
      y /= value.y;
      z /= value.z;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SFloatVector3& source, const SFloatVector3& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SFloatVector3& source, const SFloatVector3& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
   }
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TFloat Absolute() const{
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
   // <T>�������</T>
   MO_INLINE TFloat DotPoint3(SFloatPoint3& value){
      return (x * value.x) + (y * value.y) + (z * value.z);
   }
   //------------------------------------------------------------
   // <T>���(�ڻ�)��</T>
   MO_INLINE void Cross(const SFloatVector3& value){
      TFloat xValue = (y * value.z) - (z * value.y);
      TFloat yValue = (z * value.x) - (x * value.z);
      TFloat zValue = (x * value.y) - (y * value.x);
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>���(�ڻ�)��</T>
   MO_INLINE void Cross(SFloatVector3& output, const SFloatVector3& input){
      output.x = (y * input.z) - (z * input.y);
      output.y = (z * input.x) - (x * input.z);
      output.z = (x * input.y) - (y * input.x);
   }
   //------------------------------------------------------------
   // <T>���(���)��</T>
   MO_INLINE void Multiply(const SFloatVector3& value){
   }
   //------------------------------------------------------------
   // <T>����нǡ�</T>
   TFloat Angle(const SFloatVector3& value){
      TFloat result = (x * value.x) + (y * value.y) + (z * value.z);
      result /= Absolute();
      result /= value.Absolute();
      return (TFloat)acos(result);
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
// <T>��ά˫������ʸ����</T>
//============================================================
struct MO_MT_DECLARE SDoubleVector3{
public:
   TDouble x;
   TDouble y;
   TDouble z;
public:
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector3(){
      x = 0;
      y = 0;
      z = 0;
   }
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector3(TDouble value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector3(TDouble xValue, TDouble yValue, TDouble zValue){
      Set(xValue, yValue, zValue);
   }
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector3(const SDoublePoint3& source, const SDoublePoint3& target){
      Set(source, target);
   }
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector3(const SDoublePoint3& source, const SDoublePoint3& target, TBool normalize){
      Set(source, target, normalize);
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoubleVector3& value){
      return (x == value.x) && (y == value.y) && (z == value.z);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoubleVector3& value){
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
   MO_INLINE void operator=(const SDoubleVector3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TDouble value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoubleVector3& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TDouble value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoubleVector3& value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TDouble value){
      Mul(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TDouble value){
      Div(value);
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TDouble value){
      x = value;
      y = value;
      z = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue, TDouble zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SDoublePoint3& source, const SDoublePoint3& target){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SDoublePoint3& source, const SDoublePoint3& target, TBool normalize){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
      if(normalize){
         Normalize();
      }
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoubleVector3& value){
      x = value.x;
      y = value.y;
      z = value.z;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TDouble xValue, TDouble yValue, TDouble zValue){
      x += xValue;
      y += yValue;
      z += zValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SDoubleVector3& value){
      x += value.x;
      y += value.y;
      z += value.z;
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
   MO_INLINE void Sub(const SDoubleVector3& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TDouble xValue, TDouble yValue, TDouble zValue){
      x *= xValue;
      y *= yValue;
      z *= zValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SDoubleVector3& value){
      x *= value.x;
      y *= value.y;
      z *= value.z;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SDoubleVector3 MulToVector3(TDouble value){
      return SDoubleVector3(x * value, y * value, z * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TDouble xValue, TDouble yValue, TDouble zValue){
      x /= xValue;
      y /= yValue;
      z /= zValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SDoubleVector3& value){
      x /= value.x;
      y /= value.y;
      z /= value.z;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SDoubleVector3& source, const SDoubleVector3& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SDoubleVector3& source, const SDoubleVector3& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
   }
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TDouble Absolute() const{
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
   // <T>�������</T>
   MO_INLINE TDouble DotPoint3(SDoublePoint3& value){
      return (x * value.x) + (y * value.y) + (z * value.z);
   }
   //------------------------------------------------------------
   // <T>���(�ڻ�)��</T>
   MO_INLINE void Cross(const SDoubleVector3& value){
      TDouble xValue = (y * value.z) - (z * value.y);
      TDouble yValue = (z * value.x) - (x * value.z);
      TDouble zValue = (x * value.y) - (y * value.x);
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>���(�ڻ�)��</T>
   MO_INLINE void Cross(SDoubleVector3& output, const SDoubleVector3& input){
      output.x = (y * input.z) - (z * input.y);
      output.y = (z * input.x) - (x * input.z);
      output.z = (x * input.y) - (y * input.x);
   }
   //------------------------------------------------------------
   // <T>���(���)��</T>
   MO_INLINE void Multiply(const SDoubleVector3& value){
   }
   //------------------------------------------------------------
   // <T>����нǡ�</T>
   TDouble Angle(const SDoubleVector3& value){
      TDouble result = (x * value.x) + (y * value.y) + (z * value.z);
      result /= Absolute();
      result /= value.Absolute();
      return acos(result);
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
// <T>��ά����ʸ����</T>
//============================================================
struct MO_MT_DECLARE SIntVector4{
public:
   TInt x;
   TInt y;
   TInt z;
   TInt w;
public:
   //------------------------------------------------------------
   // <T>������ά����ʸ����</T>
   SIntVector4(){
      x = 0;
      y = 0;
      z = 0;
      w = 0;
   }
   //------------------------------------------------------------
   // <T>������ά����ʸ����</T>
   SIntVector4(TInt value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>������ά����ʸ����</T>
   SIntVector4(TInt px, TInt py, TInt pz, TInt pw){
      x = px;
      y = py;
      z = pz;
      w = pw;
   }
   //------------------------------------------------------------
   // <T>������ά����ʸ����</T>
   SIntVector4(const SIntPoint4& source, const SIntPoint4& target){
      x = source.x - target.x;
      y = source.y - target.y;
      z = source.z - target.z;
      w = source.w - target.w;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SIntVector4& value){
      return (x == value.x) && (y == value.y) && (z == value.z) && (w == value.w);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SIntVector4& value){
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
   MO_INLINE void operator=(const SIntVector4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TInt value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntVector4& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TInt value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntVector4& value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TInt value){
      Mul(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TInt value){
      Div(value);
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TInt value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue, TInt zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TInt xValue, TInt yValue, TInt zValue, TInt wValue){
      x = xValue;
      y = yValue;
      z = zValue;
      w = wValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SIntPoint4& source, const SIntPoint4& target){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
      w = target.w - source.w;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntVector4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TInt xValue, TInt yValue, TInt zValue, TInt wValue){
      x += xValue;
      y += yValue;
      z += zValue;
      w += wValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SIntVector4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TInt xValue, TInt yValue, TInt zValue, TInt wValue){
      x -= xValue;
      y -= yValue;
      z -= zValue;
      w -= wValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SIntVector4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.w;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TInt xValue, TInt yValue, TInt zValue, TInt wValue){
      x *= xValue;
      y *= yValue;
      z *= zValue;
      w *= wValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SIntVector4& value){
      x *= value.x;
      y *= value.y;
      z *= value.z;
      w *= value.w;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SIntVector4 MulToVector4(TInt value){
      return SIntVector4(x * value, y * value, z * value, w * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TInt xValue, TInt yValue, TInt zValue, TInt wValue){
      x /= xValue;
      y /= yValue;
      z /= zValue;
      w /= wValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SIntVector4& value){
      x /= value.x;
      y /= value.y;
      z /= value.z;
      w /= value.w;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SIntVector4& source, const SIntVector4& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
      w = MO_LIB_MIN(source.w, target.w);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SIntVector4& source, const SIntVector4& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
      w = MO_LIB_MAX(source.w, target.w);
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
// <T>��ά������ʸ����</T>
//============================================================
struct MO_MT_DECLARE SFloatVector4{
public:
   TFloat x;
   TFloat y;
   TFloat z;
   TFloat w;
public:
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector4(){
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
      w = 0.0f;
   }
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector4(TFloat value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector4(TFloat px, TFloat py, TFloat pz, TFloat pw){
      x = px;
      y = py;
      z = pz;
      w = pw;
   }
   //------------------------------------------------------------
   // <T>������ά������ʸ����</T>
   SFloatVector4(const SFloatPoint4& source, const SFloatPoint4& target){
      x = source.x - target.x;
      y = source.y - target.y;
      z = source.z - target.z;
      w = source.w - target.w;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatVector4& value){
      return (x == value.x) && (y == value.y) && (z == value.z) && (w == value.w);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatVector4& value){
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
   MO_INLINE void operator=(const SFloatVector4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TFloat value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatVector4& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TFloat value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatVector4& value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TFloat value){
      Mul(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TFloat value){
      Div(value);
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TFloat value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue, TFloat zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TFloat xValue, TFloat yValue, TFloat zValue, TFloat wValue){
      x = xValue;
      y = yValue;
      z = zValue;
      w = wValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatPoint4& source, const SFloatPoint4& target){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
      w = target.w - source.w;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatPoint4& source, const SFloatPoint4& target, TBool normalize){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
      w = target.w - source.w;
      if(normalize){
         Normalize();
      }
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatVector4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TFloat xValue, TFloat yValue, TFloat zValue, TFloat wValue){
      x += xValue;
      y += yValue;
      z += zValue;
      w += wValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SFloatVector4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TFloat xValue, TFloat yValue, TFloat zValue, TFloat wValue){
      x -= xValue;
      y -= yValue;
      z -= zValue;
      w -= wValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SFloatVector4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.w;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TFloat xValue, TFloat yValue, TFloat zValue, TFloat wValue){
      x *= xValue;
      y *= yValue;
      z *= zValue;
      w *= wValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SFloatVector4& value){
      x *= value.x;
      y *= value.y;
      z *= value.z;
      w *= value.w;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SFloatVector4 MulToVector4(TFloat value){
      return SFloatVector4(x * value, y * value, z * value, w * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TFloat xValue, TFloat yValue, TFloat zValue, TFloat wValue){
      x /= xValue;
      y /= yValue;
      z /= zValue;
      w /= wValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SFloatVector4& value){
      x /= value.x;
      y /= value.y;
      z /= value.z;
      w /= value.w;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SFloatVector4& source, const SFloatVector4& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
      w = MO_LIB_MIN(source.w, target.w);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SFloatVector4& source, const SFloatVector4& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
      w = MO_LIB_MAX(source.w, target.w);
   }
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TFloat Absolute() const{
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
   // <T>���(�ڻ�)��</T>
   MO_INLINE void Cross(const SFloatVector4& value){
   }
   //------------------------------------------------------------
   // <T>���(���)��</T>
   MO_INLINE void Multiply(const SFloatVector4& value){
   }
   //------------------------------------------------------------
   // <T>����нǡ�</T>
   TFloat Angle(const SFloatVector4& value){
      TFloat result = (x * value.x) + (y * value.y) + (z * value.z) + (w * value.w);
      result /= Absolute();
      result /= value.Absolute();
      return (TFloat)acos(result);
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
// <T>��ά˫������ʸ����</T>
//============================================================
struct MO_MT_DECLARE SDoubleVector4{
public:
   TDouble x;
   TDouble y;
   TDouble z;
   TDouble w;
public:
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector4(){
      x = 0;
      y = 0;
      z = 0;
      w = 0;
   }
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector4(TDouble value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector4(TDouble px, TDouble py, TDouble pz, TDouble pw){
      x = px;
      y = py;
      z = pz;
      w = pw;
   }
   //------------------------------------------------------------
   // <T>������ά˫������ʸ����</T>
   SDoubleVector4(const SDoublePoint4& source, const SDoublePoint4& target){
      x = source.x - target.x;
      y = source.y - target.y;
      z = source.z - target.z;
      w = source.w - target.w;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoubleVector4& value){
      return (x == value.x) && (y == value.y) && (z == value.z) && (w == value.w);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoubleVector4& value){
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
   MO_INLINE void operator=(const SDoubleVector4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(TDouble value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoubleVector4& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(TDouble value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoubleVector4& value){
      Sub(value);
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TDouble value){
      Mul(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TDouble value){
      Div(value);
   }
public:
   //------------------------------------------------------------
   // <T>��ȫ�������ݡ�</T>
   MO_INLINE void SetAll(TDouble value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue){
      x = xValue;
      y = yValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue, TDouble zValue){
      x = xValue;
      y = yValue;
      z = zValue;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TDouble xValue, TDouble yValue, TDouble zValue, TDouble wValue){
      x = xValue;
      y = yValue;
      z = zValue;
      w = wValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SDoublePoint4& source, const SDoublePoint4& target){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
      w = target.w - source.w;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SDoublePoint4& source, const SDoublePoint4& target, TBool normalize){
      x = target.x - source.x;
      y = target.y - source.y;
      z = target.z - source.z;
      w = target.w - source.w;
      if(normalize){
         Normalize();
      }
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoubleVector4& value){
      x = value.x;
      y = value.y;
      z = value.z;
      w = value.w;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(TDouble xValue, TDouble yValue, TDouble zValue, TDouble wValue){
      x += xValue;
      y += yValue;
      z += zValue;
      w += wValue;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SDoubleVector4& value){
      x += value.x;
      y += value.y;
      z += value.z;
      w += value.w;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(TDouble xValue, TDouble yValue, TDouble zValue, TDouble wValue){
      x -= xValue;
      y -= yValue;
      z -= zValue;
      w -= wValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SDoubleVector4& value){
      x -= value.x;
      y -= value.y;
      z -= value.z;
      w -= value.w;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(TDouble xValue, TDouble yValue, TDouble zValue, TDouble wValue){
      x *= xValue;
      y *= yValue;
      z *= zValue;
      w *= wValue;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void Mul(const SDoubleVector4& value){
      x *= value.x;
      y *= value.y;
      z *= value.z;
      w *= value.w;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE SDoubleVector4 MulToVector4(TDouble value){
      return SDoubleVector4(x * value, y * value, z * value, w * value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(TDouble xValue, TDouble yValue, TDouble zValue, TDouble wValue){
      x /= xValue;
      y /= yValue;
      z /= zValue;
      w /= wValue;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Div(const SDoubleVector4& value){
      x /= value.x;
      y /= value.y;
      z /= value.z;
      w /= value.w;
   }
public:
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SDoubleVector4& source, const SDoubleVector4& target){
      x = MO_LIB_MIN(source.x, target.x);
      y = MO_LIB_MIN(source.y, target.y);
      z = MO_LIB_MIN(source.z, target.z);
      w = MO_LIB_MIN(source.w, target.w);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SDoubleVector4& source, const SDoubleVector4& target){
      x = MO_LIB_MAX(source.x, target.x);
      y = MO_LIB_MAX(source.y, target.y);
      z = MO_LIB_MAX(source.z, target.z);
      w = MO_LIB_MAX(source.w, target.w);
   }
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TDouble Absolute() const{
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
   // <T>���(�ڻ�)��</T>
   MO_INLINE void Cross(const SDoubleVector4& value){
   }
   //------------------------------------------------------------
   // <T>���(���)��</T>
   MO_INLINE void Multiply(const SDoubleVector4& value){
   }
   //------------------------------------------------------------
   // <T>����нǡ�</T>
   TDouble Angle(const SDoubleVector4& value){
      TDouble result = (x * value.x) + (y * value.y) + (z * value.z) + (w * value.w);
      result /= Absolute();
      result /= value.Absolute();
      return acos(result);
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

#endif // __MO_MT_VECTOR_H__
