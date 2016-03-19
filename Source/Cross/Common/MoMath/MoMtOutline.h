#ifndef __MO_MT_OUTLINE_H__
#define __MO_MT_OUTLINE_H__

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
// <T>��ά������������</T>
//============================================================
struct MO_MT_DECLARE SFloatOutline3{
public:
   SFloatPoint3 min;
   SFloatPoint3 max;
public:
   //------------------------------------------------------------
   // <T>������ά������������</T>
   SFloatOutline3(){
   }
   //------------------------------------------------------------
   // <T>������ά������������</T>
   SFloatOutline3(TFloat minX, TFloat minY, TFloat minZ, TFloat maxX, TFloat maxY, TFloat maxZ){
      min.Set(minX, minY, minZ);
      max.Set(maxX, maxY, maxZ);
   }
   //------------------------------------------------------------
   // <T>������ά������������</T>
   SFloatOutline3(const SFloatPoint3& minPoint, const SFloatPoint3& maxPoint){
      min = minPoint;
      max = maxPoint;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatOutline3& value){
      return (min == value.min) && (max == value.max);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatOutline3& value){
      return (min != value.min) || (max != value.max);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatOutline3& value){
      min = value.min;
      max = value.max;
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return min.IsEmpty() && max.IsEmpty();
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat minX, TFloat minY, TFloat minZ, TFloat maxX, TFloat maxY, TFloat maxZ){
      min.Set(minX, minY, minZ);
      max.Set(maxX, maxY, maxZ);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatPoint3& minPoint, const SFloatPoint3& maxPoint){
      min = minPoint;
      max = maxPoint;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatOutline3& value){
      min = value.min;
      max = value.max;
   }
public:
   //------------------------------------------------------------
   // <T>��С����</T>
   MO_INLINE void Min(){
      min.Max();
      max.Min();
   }
   //------------------------------------------------------------
   // <T>�����</T>
   MO_INLINE void Max(){
      min.Min();
      max.Max();
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SFloatPoint3& minPoint, const SFloatPoint3& maxPoint){
      min.MergeMax(minPoint);
      max.MergeMin(maxPoint);
   }
   //------------------------------------------------------------
   // <T>�����С�㴦��</T>
   MO_INLINE void MergeMin(const SFloatOutline3& value){
      min.MergeMax(value.min);
      max.MergeMin(value.max);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SFloatPoint3& minPoint, const SFloatPoint3& maxPoint){
      min.MergeMin(minPoint);
      max.MergeMax(maxPoint);
   }
   //------------------------------------------------------------
   // <T>������㴦��</T>
   MO_INLINE void MergeMax(const SFloatOutline3& value){
      min.MergeMin(value.min);
      max.MergeMax(value.max);
   }
public:
   //------------------------------------------------------------
   // <T>���л��������ݵ��������</T>
   void Serialize(IDataOutput* pOutput){
      min.Serialize(pOutput);
      max.Serialize(pOutput);
   }
   //------------------------------------------------------------
   // <T>�������������л��������ݡ�</T>
   void Unserialize(IDataInput* pInput){
      min.Unserialize(pInput);
      max.Unserialize(pInput);
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

MO_NAMESPACE_END

#endif // __MO_MT_OUTLINE_H__
