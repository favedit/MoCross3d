#include "MoMtPoint.h"

MO_NAMESPACE_BEGIN

//============================================================
//<T>解析字符串内容。</T>
// 
// @param pValue 字符串
// @return 是否解析成功
//============================================================
TBool SFloatPoint4::Parse(TCharC* pValue){
   // 检查长度
   TStringRefer value(pValue);
   TInt length = value.Length();
   if(length == 0){
      MO_ERROR(TC("It is invalid length."));
      return EFalse;
   }
   // 分割内容
   TFsText temp;
   TInt begin = 0;
   TInt index = value.IndexOf(',', begin);
   if(ENotFound  == index){
      MO_ERROR(TC("Splite value failure."));
      return EFalse;
   }
   // 解析内容X
   temp.Assign(value.SubStrC(begin, index));
   x = RFloat::Parse(temp.MemoryC());
   // 分割内容
   begin = index + 1;
   index = value.IndexOf(',', begin);
   if(ENotFound == index){
      MO_ERROR(TC("Splite value failure."));
      return EFalse;
   }
   // 解析内容Y
   temp.Assign(value.SubStrC(begin, index));
   y = RFloat::Parse(temp.MemoryC());
   // 分割内容
   begin = index + 1;
   index = value.IndexOf(',', begin);
   if(ENotFound == index){
      MO_ERROR(TC("Splite value failure."));
      return EFalse;
   }
   // 解析内容Z
   temp.Assign(value.SubStrC(begin, index));
   z = RFloat::Parse(temp.MemoryC());
   // 解析内容W
   temp.Assign(value.SubStrC(index + 1, length));
   w = RFloat::Parse(temp.MemoryC());
   return ETrue;
}

//============================================================
// <T>格式化内容为显示内容。</T>
//
// @param pBuffer 缓冲指针
// @param capacity 缓冲长度
// @return 字符串
//============================================================
TCharC* SFloatPoint4::Format(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AssignFormat(TC("x=%f, y=%f, z=%f, w=%f"), x, y, z, w);
   return pBuffer;
}

//============================================================
// <T>格式化内容为字符串。</T>
//
// @param pBuffer 缓冲指针
// @param capacity 缓冲长度
// @return 字符串
//============================================================
TCharC* SFloatPoint4::ToString(TChar* pBuffer, TInt capacity){
   TStringRefer result(pBuffer, capacity);
   result.AppendFormat(TC("%f,%f,%f,%f"), x, y, z, w);
   return pBuffer;
}

MO_NAMESPACE_END
