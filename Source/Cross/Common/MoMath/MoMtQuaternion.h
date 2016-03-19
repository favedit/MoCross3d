#ifndef __MO_MT_QUATERNION_H__
#define __MO_MT_QUATERNION_H__

#ifndef _MATH_H
#include <math.h>
#endif // _MATH_H

#ifndef __MO_MT_COMMON_H__
#include "MoMtCommon.h"
#endif // __MO_MT_COMMON_H__

#ifndef __MO_MT_VECTOR_H__
#include "MoMtVector.h"
#endif // __MO_MT_VECTOR_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Ԫ����</T>
//============================================================
struct SFloatQuaternion{
public:
   TFloat x;
   TFloat y;
   TFloat z;
   TFloat w;
public:
   //------------------------------------------------------------
   // <T>������Ԫ����</T>
   SFloatQuaternion(){
      x = 0;
      y = 0;
      z = 0;
      w = 1;
   }
   //------------------------------------------------------------
   // <T>������Ԫ����</T>
   SFloatQuaternion(TFloat value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>������Ԫ����</T>
   SFloatQuaternion(const SFloatQuaternion& quaternion){
      x = quaternion.x;
      y = quaternion.y;
      z = quaternion.z;
      w = quaternion.w;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatQuaternion& quaternion){
      return (x==quaternion.x)&&(y==quaternion.y)&&(z==quaternion.z)&&(w==quaternion.w);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatQuaternion& quaternion){
      return (x!=quaternion.x)||(y!=quaternion.y)||(z!=quaternion.z)||(w!=quaternion.w);
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
   MO_INLINE void operator=(const SFloatQuaternion& quaternion){
      x = quaternion.x;
      y = quaternion.y;
      z = quaternion.z;
      w = quaternion.w;
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
   MO_INLINE void operator+=(const SFloatQuaternion& quaternion){
      x += quaternion.x;
      y += quaternion.y;
      z += quaternion.z;
      w += quaternion.w;
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
   MO_INLINE void operator-=(const SFloatQuaternion& quaternion){
      x -= quaternion.x;
      y -= quaternion.y;
      z -= quaternion.z;
      w -= quaternion.w;
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
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat value){
      this->x = value;
      this->y = value;
      this->z = value;
      this->w = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat px, TFloat py, TFloat pz, TFloat pw){
      x = px;
      y = py;
      z = pz;
      w = pw;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatQuaternion& quaternion){
      x = quaternion.x;
      y = quaternion.y;
      z = quaternion.z;
      w = quaternion.w;
   }
public:
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TFloat Absolute(){
      return (TFloat)sqrt((x * x) + (y * y) + (z * z) + (w * w));
   }
   //------------------------------------------------------------
   MO_INLINE void Normalize(){
      TFloat v = Absolute();
      x /= v;
      y /= v;
      z /= v;
      w /= v;
   }
   //------------------------------------------------------------
   MO_INLINE void Increase(SFloatQuaternion& v){
      x += v.x;
      y += v.y;
      z += v.z;
      w += v.w;
   }
   //------------------------------------------------------------
   MO_INLINE void Subtract(SFloatQuaternion& v){
      x -= v.x;
      y -= v.y;
      z -= v.z;
      w -= v.w;
   }
   //------------------------------------------------------------
   MO_INLINE SFloatQuaternion Multiply(SFloatQuaternion& v){
      SFloatQuaternion r;
      r.x = (w * v.x) + (x * v.w) + (y * v.z) - (z * v.y);
      r.y = (w * v.y) + (y * v.w) + (z * v.x) - (x * v.z);
      r.z = (w * v.z) + (z * v.w) + (x * v.y) - (y * v.x);
      r.w = (w * v.w) - (x * v.x) - (y * v.y) - (z * v.z);
      return r;
   }
   //------------------------------------------------------------
   MO_INLINE void ToVector3(SFloatVector3* pValue){
      pValue->x = x / w;
      pValue->y = y / w;
      pValue->z = z / w;
   }
};

//============================================================
// <T>��Ԫ����</T>
//============================================================
struct SDoubleQuaternion{
public:
   TDouble x;
   TDouble y;
   TDouble z;
   TDouble w;
public:
   //------------------------------------------------------------
   // <T>������Ԫ����</T>
   SDoubleQuaternion(){
      x = 0;
      y = 0;
      z = 0;
      w = 1;
   }
   //------------------------------------------------------------
   // <T>������Ԫ����</T>
   SDoubleQuaternion(TDouble value){
      x = value;
      y = value;
      z = value;
      w = value;
   }
   //------------------------------------------------------------
   // <T>������Ԫ����</T>
   SDoubleQuaternion(const SDoubleQuaternion& quaternion){
      x = quaternion.x;
      y = quaternion.y;
      z = quaternion.z;
      w = quaternion.w;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoubleQuaternion& quaternion){
      return (x==quaternion.x)&&(y==quaternion.y)&&(z==quaternion.z)&&(w==quaternion.w);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoubleQuaternion& quaternion){
      return (x!=quaternion.x)||(y!=quaternion.y)||(z!=quaternion.z)||(w!=quaternion.w);
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
   MO_INLINE void operator=(const SDoubleQuaternion& quaternion){
      x = quaternion.x;
      y = quaternion.y;
      z = quaternion.z;
      w = quaternion.w;
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
   MO_INLINE void operator+=(const SDoubleQuaternion& quaternion){
      x += quaternion.x;
      y += quaternion.y;
      z += quaternion.z;
      w += quaternion.w;
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
   MO_INLINE void operator-=(const SDoubleQuaternion& quaternion){
      x -= quaternion.x;
      y -= quaternion.y;
      z -= quaternion.z;
      w -= quaternion.w;
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
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble value){
      this->x = value;
      this->y = value;
      this->z = value;
      this->w = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble px, TDouble py, TDouble pz, TDouble pw){
      x = px;
      y = py;
      z = pz;
      w = pw;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SDoubleQuaternion& quaternion){
      x = quaternion.x;
      y = quaternion.y;
      z = quaternion.z;
      w = quaternion.w;
   }
public:
   //------------------------------------------------------------
   // <T>��þ���ֵ��</T>
   MO_INLINE TDouble Absolute(){
      return sqrt((x * x) + (y * y) + (z * z) + (w * w));
   }
   //------------------------------------------------------------
   MO_INLINE void Normalize(){
      TDouble v = Absolute();
      x /= v;
      y /= v;
      z /= v;
      w /= v;
   }
   //------------------------------------------------------------
   MO_INLINE void Increase(SDoubleQuaternion& v){
      x += v.x;
      y += v.y;
      z += v.z;
      w += v.w;
   }
   //------------------------------------------------------------
   MO_INLINE void Subtract(SDoubleQuaternion& v){
      x -= v.x;
      y -= v.y;
      z -= v.z;
      w -= v.w;
   }
   //------------------------------------------------------------
   MO_INLINE SDoubleQuaternion Multiply(SDoubleQuaternion& v){
      SDoubleQuaternion r;
      r.x = (w * v.x) + (x * v.w) + (y * v.z) - (z * v.y);
      r.y = (w * v.y) + (y * v.w) + (z * v.x) - (x * v.z);
      r.z = (w * v.z) + (z * v.w) + (x * v.y) - (y * v.x);
      r.w = (w * v.w) - (x * v.x) - (y * v.y) - (z * v.z);
      return r;
   }
   //------------------------------------------------------------
   MO_INLINE void ToVector3(SDoubleVector3* pValue){
      pValue->x = x / w;
      pValue->y = y / w;
      pValue->z = z / w;
   }
};

MO_NAMESPACE_END

#endif // __MO_MT_QUATERNION_H__
