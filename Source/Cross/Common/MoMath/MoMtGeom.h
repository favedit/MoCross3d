#ifndef __MO_MT_GEOM_H__
#define __MO_MT_GEOM_H__

#ifndef _MATH_H
#include <math.h>
#endif // _MATH_H

#ifndef __MO_MT_COMMON_H__
#include "MoMtCommon.h"
#endif // __MO_MT_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Χ��</T>
//============================================================
struct MO_MT_DECLARE SIntRange{
public:
   TInt min;
   TInt max;
public:
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SIntRange(){
      min = 0;
      max = 0;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SIntRange(TInt value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SIntRange(TInt minValue, TInt maxValue){
      min = minValue;
      max = maxValue;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SIntRange(const SIntRange& value){
      min = value.min;
      max = value.max;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SIntRange& value){
      return (min == value.min) && (max == value.max);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SIntRange& value){
      return (min != value.min) || (max != value.max);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TInt value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SIntRange& value){
      min = value.min;
      max = value.max;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntRange& value){
      min += value.min;
      max += value.max;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntRange& value){
      min -= value.min;
      max -= value.max;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TInt value){
      min *= value;
      max *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TInt value){
      MO_ASSERT(0 != value);
      min /= value;
      max /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt minValue, TInt maxValue){
      min = minValue;
      max = maxValue;
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��Χ��</T>
//============================================================
struct MO_MT_DECLARE SFloatRange{
public:
   TFloat min;
   TFloat max;
public:
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SFloatRange(){
      min = 0.0f;
      max = 0.0f;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SFloatRange(TFloat value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SFloatRange(TFloat minValue, TFloat maxValue){
      min = minValue;
      max = maxValue;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SFloatRange(const SFloatRange& value){
      min = value.min;
      max = value.max;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatRange& value){
      return (min == value.min) && (max == value.max);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatRange& value){
      return (min != value.min) || (max != value.max);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TFloat value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatRange& value){
      min = value.min;
      max = value.max;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatRange& value){
      min += value.min;
      max += value.max;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatRange& value){
      min -= value.min;
      max -= value.max;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TFloat value){
      min *= value;
      max *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TFloat value){
      MO_ASSERT(0 != value);
      min /= value;
      max /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat minValue, TFloat maxValue){
      min = minValue;
      max = maxValue;
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��Χ��</T>
//============================================================
struct MO_MT_DECLARE SDoubleRange{
public:
   TDouble min;
   TDouble max;
public:
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SDoubleRange(){
      min = 0;
      max = 0;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SDoubleRange(TDouble value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SDoubleRange(TDouble minValue, TDouble maxValue){
      min = minValue;
      max = maxValue;
   }
   //------------------------------------------------------------
   // <T>���췶Χ��</T>
   SDoubleRange(const SDoubleRange& value){
      min = value.min;
      max = value.max;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoubleRange& value){
      return (min == value.min) && (max == value.max);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoubleRange& value){
      return (min != value.min) || (max != value.max);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(TDouble value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SDoubleRange& value){
      min = value.min;
      max = value.max;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoubleRange& value){
      min += value.min;
      max += value.max;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoubleRange& value){
      min -= value.min;
      max -= value.max;
   }
   //------------------------------------------------------------
   // <T>��˴���</T>
   MO_INLINE void operator*=(TDouble value){
      min *= value;
      max *= value;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator/=(TDouble value){
      MO_ASSERT(0 != value);
      min /= value;
      max /= value;
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble value){
      min = value;
      max = value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble minValue, TDouble maxValue){
      min = minValue;
      max = maxValue;
   }
public:
   TBool Parse(TCharC* pValue);
   TCharC* Format(TChar* pBuffer, TInt capacity);
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>��������ɫ��</T>
//============================================================
struct MO_MT_DECLARE SFloatColor4{
public:
   // ��ɫ
   TFloat red;
   // ��ɫ
   TFloat green;
   // ��ɫ
   TFloat blue;
   // ͸��
   TFloat alpha;
public:
   //------------------------------------------------------------
   // <T>���측������ɫ��</T>
   MO_INLINE SFloatColor4(TFloat redValue = 0.0f, TFloat greenValue = 0.0f, TFloat blueValue = 0.0f, TFloat alphaValue = 1.0f){
      red = redValue;
      green = greenValue;
      blue = blueValue;
      alpha = alphaValue;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatColor4& value){
      return (red == value.red) && (green == value.green) && (blue == value.blue) && (alpha == value.alpha);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatColor4& value){
      return (red != value.red) || (green != value.green) || (blue != value.blue) || (alpha != value.alpha);
   }
public:
   //------------------------------------------------------------
   // <T>������ɫ��</T>
   MO_INLINE void Set(TFloat redValue = 0.0f, TFloat greenValue = 0.0f, TFloat blueValue = 0.0f, TFloat alphaValue = 1.0f){
      red = redValue;
      green = greenValue;
      blue = blueValue;
      alpha = alphaValue;
   }
   //------------------------------------------------------------
   // <T>����ȫ����ɫ��</T>
   MO_INLINE void SetAll(TFloat value = 0.0f){
      red = value;
      green = value;
      blue = value;
      alpha = value;
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Assign(const SFloatColor4& value){
      red = value.red;
      green = value.green;
      blue = value.blue;
      alpha = value.alpha;
   }
   //------------------------------------------------------------
   // <T>����һ����ɫϵ����</T>
   MO_INLINE void AssignPower(const SFloatColor4& value){
      alpha *= value.alpha;
      red *= value.red * alpha;
      green *= value.green * alpha;
      blue *= value.blue * alpha;
   }
   //------------------------------------------------------------
   // <T>����һ����ɫ��</T>
   MO_INLINE void Multiply(const SFloatColor4& value){
      red *= value.red;
      green *= value.green;
      blue *= value.blue;
      alpha *= value.alpha;
   }
public:
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>�������Ρ�</T>
//============================================================
struct MO_MT_DECLARE SIntRectangle{
public:
   TInt left;
   TInt top;
   TInt width;
   TInt height;
public:
   //------------------------------------------------------------
   // <T>�����������Ρ�</T>
   SIntRectangle(){
      left = 0;
      top = 0;
      width = 0;
      height = 0;
   }
   //------------------------------------------------------------
   // <T>�����������Ρ�</T>
   SIntRectangle(TInt leftValue, TInt topValue, TInt widthValue, TInt heightValue){
      left = leftValue;
      top = topValue;
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SIntRectangle& value) const{
      return (left == value.left) && (top == value.top) && (width == value.width) && (height == value.height);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SIntRectangle& value) const{
      return (left != value.left) || (top != value.top) || (width != value.width) || (height != value.height);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SIntRectangle& value){
      left = value.left;
      top = value.top;
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntRectangle& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntRectangle& value){
      Sub(value);
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (left == 0) && (top == 0) && (width == 0) && (height == 0);
   }
   //------------------------------------------------------------
   // <T>����ұ߽硣</T>
   MO_INLINE TInt Right() const{
      if(width > 0){
         return left + width - 1;
      }else if(width < 0){
         return left + width + 1;
      }
      return left;
   }
   //------------------------------------------------------------
   // <T>����±߽硣</T>
   MO_INLINE TInt Bottom() const{
      if(width > 0){
         return top + height - 1;
      }else if(width < 0){
         return top + height + 1;
      }
      return top;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void SetLocation(TInt leftValue, TInt topValue){
      left = leftValue;
      top = topValue;
   }
   //------------------------------------------------------------
   // <T>���óߴ硣</T>
   MO_INLINE void SetSize(TInt widthValue, TInt heightValue){
      width = widthValue;
      height = heightValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt leftValue, TInt topValue, TInt widthValue, TInt heightValue){
      left = leftValue;
      top = topValue;
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�����±߽磬�������ϱ߽磬�����Ƿ��ڷ�Χ�ڡ�</T>
   MO_INLINE TBool TestInRange(TInt x, TInt y) const{
      if(x < left){
         return EFalse;
      }
      if(x >= left + width){
         return EFalse;
      }
      if(y < top){
         return EFalse;
      }
      if(y >= top + height){
         return EFalse;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�������±߽磬�������ϱ߽磬�����Ƿ��ڷ�Χ�ڡ�</T>
   MO_INLINE TBool TestInBetween(TInt x, TInt y) const{
      if(x < left){
         return EFalse;
      }
      if(x > left + width){
         return EFalse;
      }
      if(y < top){
         return EFalse;
      }
      if(y > top + height){
         return EFalse;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SIntRectangle& value){
      left = value.left;
      top = value.top;
      width = value.width;
      height = value.height;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SIntRectangle& value){
      left += value.left;
      top += value.top;
      width += value.width;
      height += value.height;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SIntRectangle& value){
      left -= value.left;
      top -= value.top;
      width -= value.width;
      height -= value.height;
   }
   //------------------------------------------------------------
   // <T>��С����</T>
   MO_INLINE void Shrink(TInt leftValue, TInt topValue, TInt rightValue, TInt bottomValue){
      left += leftValue;
      top += topValue;
      width -= leftValue + rightValue;
      height -= topValue + bottomValue;
   }
   //------------------------------------------------------------
   // <T>��չ����</T>
   MO_INLINE void Spread(TInt leftValue, TInt topValue, TInt rightValue, TInt bottomValue){
      left -= leftValue;
      top -= topValue;
      width += leftValue + rightValue;
      height += topValue + bottomValue;
   }
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Reset(){
      left = 0;
      top = 0;
      width = 0;
      height = 0;
   }
public:
   TResult Serialize8(IDataOutput* pOutput);
   TResult Unserialize8(IDataInput* pInput);
   TResult Serialize16(IDataOutput* pOutput);
   TResult Unserialize16(IDataInput* pInput);
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>���������Ρ�</T>
//============================================================
struct MO_MT_DECLARE SFloatRectangle{
public:
   TFloat left;
   TFloat top;
   TFloat width;
   TFloat height;
public:
   //------------------------------------------------------------
   // <T>���측�������Ρ�</T>
   SFloatRectangle(){
      left = 0.0f;
      top = 0.0f;
      width = 0.0f;
      height = 0.0f;
   }
   //------------------------------------------------------------
   // <T>���측�������Ρ�</T>
   SFloatRectangle(TFloat leftValue, TFloat topValue, TFloat widthValue, TFloat heightValue){
      left = leftValue;
      top = topValue;
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatRectangle& value) const{
      return (left == value.left) && (top == value.top) && (width == value.width) && (height == value.height);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatRectangle& value) const{
      return (left != value.left) || (top != value.top) || (width != value.width) || (height != value.height);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatRectangle& value){
      left = value.left;
      top = value.top;
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatRectangle& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatRectangle& value){
      Sub(value);
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (left == 0.0f) && (top == 0.0f) && (width == 0.0f) && (height == 0.0f);
   }
   //------------------------------------------------------------
   // <T>����ұ߽硣</T>
   MO_INLINE TFloat Right() const{
      if(width > 0){
         return left + width - 1;
      }else if(width < 0){
         return left + width + 1;
      }
      return left;
   }
   //------------------------------------------------------------
   // <T>����±߽硣</T>
   MO_INLINE TFloat Bottom() const{
      if(width > 0){
         return top + height - 1;
      }else if(width < 0){
         return top + height + 1;
      }
      return top;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void SetLocation(TFloat leftValue, TFloat topValue){
      left = leftValue;
      top = topValue;
   }
   //------------------------------------------------------------
   // <T>���óߴ硣</T>
   MO_INLINE void SetSize(TFloat widthValue, TFloat heightValue){
      width = widthValue;
      height = heightValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat leftValue, TFloat topValue, TFloat widthValue, TFloat heightValue){
      left = leftValue;
      top = topValue;
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�����±߽磬�������ϱ߽磬�����Ƿ��ڷ�Χ�ڡ�</T>
   MO_INLINE TBool TestInRange(TFloat x, TFloat y) const{
      if(x < left){
         return EFalse;
      }
      if(x >= left + width){
         return EFalse;
      }
      if(y < top){
         return EFalse;
      }
      if(y >= top + height){
         return EFalse;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�������±߽磬�������ϱ߽磬�����Ƿ��ڷ�Χ�ڡ�</T>
   MO_INLINE TBool TestInBetween(TFloat x, TFloat y) const{
      if(x < left){
         return EFalse;
      }
      if(x > left + width){
         return EFalse;
      }
      if(y < top){
         return EFalse;
      }
      if(y > top + height){
         return EFalse;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SFloatRectangle& value){
      left = value.left;
      top = value.top;
      width = value.width;
      height = value.height;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SFloatRectangle& value){
      left += value.left;
      top += value.top;
      width += value.width;
      height += value.height;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SFloatRectangle& value){
      left -= value.left;
      top -= value.top;
      width -= value.width;
      height -= value.height;
   }
   //------------------------------------------------------------
   // <T>��С����</T>
   MO_INLINE void Shrink(TFloat leftValue, TFloat topValue, TFloat rightValue, TFloat bottomValue){
      left += leftValue;
      top += topValue;
      width -= leftValue + rightValue;
      height -= topValue + bottomValue;
   }
   //------------------------------------------------------------
   // <T>��չ����</T>
   MO_INLINE void Spread(TFloat leftValue, TFloat topValue, TFloat rightValue, TFloat bottomValue){
      left -= leftValue;
      top -= topValue;
      width += leftValue + rightValue;
      height += topValue + bottomValue;
   }
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Reset(){
      left = 0.0f;
      top = 0.0f;
      width = 0.0f;
      height = 0.0f;
   }
public:
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>˫���������Ρ�</T>
//============================================================
struct MO_MT_DECLARE SDoubleRectangle{
public:
   TDouble left;
   TDouble top;
   TDouble width;
   TDouble height;
public:
   //------------------------------------------------------------
   // <T>����˫���������Ρ�</T>
   SDoubleRectangle(){
      left = 0;
      top = 0;
      width = 0;
      height = 0;
   }
   //------------------------------------------------------------
   // <T>����˫���������Ρ�</T>
   SDoubleRectangle(TDouble leftValue, TDouble topValue, TDouble widthValue, TDouble heightValue){
      left = leftValue;
      top = topValue;
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoubleRectangle& value) const{
      return (left == value.left) && (top == value.top) && (width == value.width) && (height == value.height);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoubleRectangle& value) const{
      return (left != value.left) || (top != value.top) || (width != value.width) || (height != value.height);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SDoubleRectangle& value){
      left = value.left;
      top = value.top;
      width = value.width;
      height = value.height;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoubleRectangle& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoubleRectangle& value){
      Sub(value);
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (left == 0) && (top == 0) && (width == 0) && (height == 0);
   }
   //------------------------------------------------------------
   // <T>����ұ߽硣</T>
   MO_INLINE TDouble Right() const{
      if(width > 0){
         return left + width - 1;
      }else if(width < 0){
         return left + width + 1;
      }
      return left;
   }
   //------------------------------------------------------------
   // <T>����±߽硣</T>
   MO_INLINE TDouble Bottom() const{
      if(width > 0){
         return top + height - 1;
      }else if(width < 0){
         return top + height + 1;
      }
      return top;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void SetLocation(TDouble leftValue, TDouble topValue){
      left = leftValue;
      top = topValue;
   }
   //------------------------------------------------------------
   // <T>���óߴ硣</T>
   MO_INLINE void SetSize(TDouble widthValue, TDouble heightValue){
      width = widthValue;
      height = heightValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble leftValue, TDouble topValue, TDouble widthValue, TDouble heightValue){
      left = leftValue;
      top = topValue;
      width = widthValue;
      height = heightValue;
   }
public:
   //------------------------------------------------------------
   // <T>�����±߽磬�������ϱ߽磬�����Ƿ��ڷ�Χ�ڡ�</T>
   MO_INLINE TBool TestInRange(TDouble x, TDouble y) const{
      if(x < left){
         return EFalse;
      }
      if(x >= left + width){
         return EFalse;
      }
      if(y < top){
         return EFalse;
      }
      if(y >= top + height){
         return EFalse;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�������±߽磬�������ϱ߽磬�����Ƿ��ڷ�Χ�ڡ�</T>
   MO_INLINE TBool TestInBetween(TDouble x, TDouble y) const{
      if(x < left){
         return EFalse;
      }
      if(x > left + width){
         return EFalse;
      }
      if(y < top){
         return EFalse;
      }
      if(y > top + height){
         return EFalse;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Assign(const SDoubleRectangle& value){
      left = value.left;
      top = value.top;
      width = value.width;
      height = value.height;
   }
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SDoubleRectangle& value){
      left += value.left;
      top += value.top;
      width += value.width;
      height += value.height;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SDoubleRectangle& value){
      left -= value.left;
      top -= value.top;
      width -= value.width;
      height -= value.height;
   }
   //------------------------------------------------------------
   // <T>��С����</T>
   MO_INLINE void Shrink(TDouble leftValue, TDouble topValue, TDouble rightValue, TDouble bottomValue){
      left += leftValue;
      top += topValue;
      width -= leftValue + rightValue;
      height -= topValue + bottomValue;
   }
   //------------------------------------------------------------
   // <T>��չ����</T>
   MO_INLINE void Spread(TDouble leftValue, TDouble topValue, TDouble rightValue, TDouble bottomValue){
      left -= leftValue;
      top -= topValue;
      width += leftValue + rightValue;
      height += topValue + bottomValue;
   }
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Reset(){
      left = 0;
      top = 0;
      width = 0;
      height = 0;
   }
public:
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>�����߾ࡣ</T>
//============================================================
struct MO_MT_DECLARE SIntPadding{
public:
   TInt left;
   TInt top;
   TInt right;
   TInt bottom;
public:
   //------------------------------------------------------------
   // <T>���������߾ࡣ</T>
   SIntPadding(){
      left = 0;
      top = 0;
      right = 0;
      bottom = 0;
   }
   //------------------------------------------------------------
   // <T>���������߾ࡣ</T>
   SIntPadding(TInt leftValue, TInt topValue, TInt rightValue, TInt bottomValue){
      left = leftValue;
      top = topValue;
      right = rightValue;
      bottom = bottomValue;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SIntPadding& value){
      return (left == value.left) && (top == value.top) && (right == value.right) && (bottom == value.bottom);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SIntPadding& value){
      return (left != value.left) || (top != value.top) || (right != value.right) || (bottom != value.bottom);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SIntPadding& value){
      left = value.left;
      top = value.top;
      right = value.right;
      bottom = value.bottom;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SIntPadding& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SIntPadding& value){
      Sub(value);
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (left == 0) && (top == 0) && (right == 0) && (bottom == 0);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TInt leftValue, TInt topValue, TInt rightValue, TInt bottomValue){
      left = leftValue;
      top = topValue;
      right = rightValue;
      bottom = bottomValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SIntPadding& value){
      left = value.left;
      top = value.top;
      right = value.right;
      bottom = value.bottom;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SIntPadding& value){
      left += value.left;
      top += value.top;
      right += value.right;
      bottom += value.bottom;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SIntPadding& value){
      left -= value.left;
      top -= value.top;
      right -= value.right;
      bottom -= value.bottom;
   }
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Reset(){
      left = 0;
      top = 0;
      right = 0;
      bottom = 0;
   }
public:
   TResult Serialize8(IDataOutput* pOutput);
   TResult Unserialize8(IDataInput* pInput);
   TResult Serialize16(IDataOutput* pOutput);
   TResult Unserialize16(IDataInput* pInput);
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>�������߾ࡣ</T>
//============================================================
struct MO_MT_DECLARE SFloatPadding{
public:
   TFloat left;
   TFloat top;
   TFloat right;
   TFloat bottom;
public:
   //------------------------------------------------------------
   // <T>���측�����߾ࡣ</T>
   SFloatPadding(){
      left = 0.0f;
      top = 0.0f;
      right = 0.0f;
      bottom = 0.0f;
   }
   //------------------------------------------------------------
   // <T>���측�����߾ࡣ</T>
   SFloatPadding(TFloat leftValue, TFloat topValue, TFloat rightValue, TFloat bottomValue){
      left = leftValue;
      top = topValue;
      right = rightValue;
      bottom = bottomValue;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SFloatPadding& value){
      return (left == value.left) && (top == value.top) && (right == value.right) && (bottom == value.bottom);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SFloatPadding& value){
      return (left != value.left) || (top != value.top) || (right != value.right) || (bottom != value.bottom);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SFloatPadding& value){
      left = value.left;
      top = value.top;
      right = value.right;
      bottom = value.bottom;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SFloatPadding& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SFloatPadding& value){
      Sub(value);
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (left == 0.0f) && (top == 0.0f) && (right == 0.0f) && (bottom == 0.0f);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TFloat leftValue, TFloat topValue, TFloat rightValue, TFloat bottomValue){
      left = leftValue;
      top = topValue;
      right = rightValue;
      bottom = bottomValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SFloatPadding& value){
      left = value.left;
      top = value.top;
      right = value.right;
      bottom = value.bottom;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SFloatPadding& value){
      left += value.left;
      top += value.top;
      right += value.right;
      bottom += value.bottom;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SFloatPadding& value){
      left -= value.left;
      top -= value.top;
      right -= value.right;
      bottom -= value.bottom;
   }
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Reset(){
      left = 0.0f;
      top = 0.0f;
      right = 0.0f;
      bottom = 0.0f;
   }
public:
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>˫�������߾ࡣ</T>
//============================================================
struct MO_MT_DECLARE SDoublePadding{
public:
   TDouble left;
   TDouble top;
   TDouble right;
   TDouble bottom;
public:
   //------------------------------------------------------------
   // <T>����˫�������߾ࡣ</T>
   SDoublePadding(){
      left = 0;
      top = 0;
      right = 0;
      bottom = 0;
   }
   //------------------------------------------------------------
   // <T>����˫�������߾ࡣ</T>
   SDoublePadding(TDouble leftValue, TDouble topValue, TDouble rightValue, TDouble bottomValue){
      left = leftValue;
      top = topValue;
      right = rightValue;
      bottom = bottomValue;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(const SDoublePadding& value){
      return (left == value.left) && (top == value.top) && (right == value.right) && (bottom == value.bottom);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(const SDoublePadding& value){
      return (left != value.left) || (top != value.top) || (right != value.right) || (bottom != value.bottom);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void operator=(const SDoublePadding& value){
      left = value.left;
      top = value.top;
      right = value.right;
      bottom = value.bottom;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void operator+=(const SDoublePadding& value){
      Add(value);
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void operator-=(const SDoublePadding& value){
      Sub(value);
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (left == 0) && (top == 0) && (right == 0) && (bottom == 0);
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(TDouble leftValue, TDouble topValue, TDouble rightValue, TDouble bottomValue){
      left = leftValue;
      top = topValue;
      right = rightValue;
      bottom = bottomValue;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void Set(const SDoublePadding& value){
      left = value.left;
      top = value.top;
      right = value.right;
      bottom = value.bottom;
   }
public:
   //------------------------------------------------------------
   // <T>��Ӵ���</T>
   MO_INLINE void Add(const SDoublePadding& value){
      left += value.left;
      top += value.top;
      right += value.right;
      bottom += value.bottom;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE void Sub(const SDoublePadding& value){
      left -= value.left;
      top -= value.top;
      right -= value.right;
      bottom -= value.bottom;
   }
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Reset(){
      left = 0;
      top = 0;
      right = 0;
      bottom = 0;
   }
public:
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>����������</T>
//============================================================
struct MO_MT_DECLARE SFloatCoord{
public:
   TFloat x1;
   TFloat y1;
   TFloat x2;
   TFloat y2;
public:
   //------------------------------------------------------------
   // <T>���측������ɫ��</T>
   MO_INLINE SFloatCoord(TFloat x1Value = 0.0f, TFloat y1Value = 0.0f, TFloat x2Value = 0.0f, TFloat y2Value = 0.0f){
      x1 = x1Value;
      y1 = y1Value;
      x2 = x2Value;
      y2 = y2Value;
   }
public:
   //------------------------------------------------------------
   // <T>������ɫ��</T>
   MO_INLINE void Set(TFloat x1Value = 0.0f, TFloat y1Value = 0.0f, TFloat x2Value = 0.0f, TFloat y2Value = 0.0f){
      x1 = x1Value;
      y1 = y1Value;
      x2 = x2Value;
      y2 = y2Value;
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Assign(const SFloatCoord& value){
      x1 = value.x1;
      y1 = value.y1;
      x2 = value.x2;
      y2 = value.y2;
   }
};

//============================================================
// <T>���ι��ߡ�</T>
//============================================================
class MO_MT_DECLARE RGeomUtil{
public:
   static TFloat Length3(TFloat x1, TFloat y1, TFloat z1, TFloat x2, TFloat y2, TFloat z2);
};

MO_NAMESPACE_END

#endif // __MO_MT_GEOM_H__
