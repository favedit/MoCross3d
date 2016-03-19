#ifndef __MO_CM_TYPE_H__
#define __MO_CM_TYPE_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_INTERFACE_H__
#include "MoCmInterface.h"
#endif // __MO_CM_INTERFACE_H__

//============================================================
// <T>�߼����塣</T>
//============================================================
/// @define ��þ���ֵ
#define MO_LIB_ABS(V)         ((V) > 0 ? (V) : -(V))
/// @define �������ֵ�н�С��ֵ
#define MO_LIB_MIN(A, B)      ((A) < (B) ? (A) : (B))
/// @define �������ֵ�нϴ��ֵ
#define MO_LIB_MAX(A, B)      ((A) > (B) ? (A) : (B))
/// @define �����ָ����Χ�е�ֵ
#define MO_LIB_RANGE(A, B, C) (((A) > (B)) ? ((A) < (C) ? (A) : (C)) : (B))
/// @define �����һ������ΪNULL����ȡ�ڶ�������
#define MO_LIB_NVL(V, D)      (NULL == (V) ? (V) : (D))
/// @define ȡһ�����͵�Ĭ��ֵ
#define MO_LIB_DEFAULT(T)     (T)NULL
/// @define ��������ֵ
#define MO_LIB_SWAP(T, A, B)  {T (V) = (A); (A) = (B); (B) = (V);}
//------------------------------------------------------------
/// @define �ֽڶ���
#define MO_LIB_ALIGN_2(x) (((x) + 1) & ~1U)
#define MO_LIB_ALIGN_4(x) (((x) + 3) & ~3U)
#define MO_LIB_ALIGN_8(x) (((x) + 7) & ~7U)

//------------------------------------------------------------
// �������Ͷ���
#define MO_TYPE_BOOL_TRUE_CHAR     'Y'
#define MO_TYPE_BOOL_TRUE_STRING   TC("Y")
#define MO_TYPE_BOOL_TRUE_DISPLAY  TC("True")
#define MO_TYPE_BOOL_FALSE_CHAR    'N'
#define MO_TYPE_BOOL_FALSE_STRING  TC("N")
#define MO_TYPE_BOOL_FALSE_DISPLAY TC("False")

//------------------------------------------------------------
#define MO_TYPE_SORT_THRESHOLD     7

//------------------------------------------------------------
#define MO_TP_BYTE_BIT 8
#define MO_TP_BYTE_MIN 0x00
#define MO_TP_BYTE_MAX 0xFF

#ifdef _UNICODE
#define MO_TP_CHAR_BIT 16
#define MO_TP_CHAR_MIN (-32768)
#define MO_TP_CHAR_MAX 32767
#else
#define MO_TP_CHAR_BIT 8
#define MO_TP_CHAR_MIN (-128)
#define MO_TP_CHAR_MAX 127
#endif

#define MO_TP_INT8_BIT 8
#define MO_TP_INT8_MIN (-127 - 1)
#define MO_TP_INT8_MAX 127

#define MO_TP_INT16_BIT 16
#define MO_TP_INT16_MIN (-32767 - 1)
#define MO_TP_INT16_MAX 32767

#define MO_TP_INT32_BIT 32
#define MO_TP_INT32_MIN (-2147483647 - 1)
#define MO_TP_INT32_MAX 2147483647

#define MO_TP_INT64_BIT 64
#define MO_TP_INT64_MIN (-9223372036854775807i64 - 1)
#define MO_TP_INT64_MAX 9223372036854775807i64

#define MO_TP_UINT8_BIT 8
#define MO_TP_UINT8_MIN 0x00
#define MO_TP_UINT8_MAX 0xFF

#define MO_TP_UINT16_BIT 16
#define MO_TP_UINT16_MIN 0x0000
#define MO_TP_UINT16_MAX 0xFFFF

#define MO_TP_UINT32_BIT 32
#define MO_TP_UINT32_MIN 0x00000000
#define MO_TP_UINT32_MAX 0xFFFFFFFF

#define MO_TP_UINT64_BIT 64
#define MO_TP_UINT64_MIN 0x0000000000000000UL
#define MO_TP_UINT64_MAX 0xFFFFFFFFFFFFFFFFUL

#define MO_TP_FLOAT_DIG       6
#define MO_TP_FLOAT_BIT       32
#define MO_TP_FLOAT_MIN       1.175494351e-38F
#define MO_TP_FLOAT_VAL       0.0F
#define MO_TP_FLOAT_MAX       3.402823466e+38F
#define MO_TP_FLOAT_MIN_EXP10 (-37)
#define MO_TP_FLOAT_MIN_EXP   (-125)
#define MO_TP_FLOAT_MAX_EXP10 38
#define MO_TP_FLOAT_MAX_EXP   128

#define MO_TP_DOUBLE_DIG       15
#define MO_TP_DOUBLE_BIT       64
#define MO_TP_DOUBLE_MIN       2.2250738585072014e-308
#define MO_TP_DOUBLE_VAL       0.0F
#define MO_TP_DOUBLE_MAX       1.7976931348623158e+308
#define MO_TP_DOUBLE_MIN_EXP10 (-307)
#define MO_TP_DOUBLE_MIN_EXP   (-1021)
#define MO_TP_DOUBLE_MAX_EXP10 308
#define MO_TP_DOUBLE_MAX_EXP   1024

//------------------------------------------------------------
// ʱ�����Ͷ���
#define MO_TP_DATE_MICROSECONDS_PER_DAY    86400000000L
#define MO_TP_DATE_MICROSECONDS_PER_HOUR    3600000000L
#define MO_TP_DATE_MICROSECONDS_PER_MINUTE    60000000L
#define MO_TP_DATE_MICROSECONDS_PER_SECONDE    1000000L
#define MO_TP_DATE_MILLISECONDS_PER_DAY       86400000
#define MO_TP_DATE_MILLISECONDS_PER_HOUR       3600000
#define MO_TP_DATE_MILLISECONDS_PER_MINUTE       60000
#define MO_TP_DATE_MILLISECONDS_PER_SECONDE       1000
#define MO_TP_DATE_SECONDS_PER_DAY               86400
#define MO_TP_DATE_SECONDS_PER_HOUR               3600
#define MO_TP_DATE_SECONDS_PER_MINUTE               60

//============================================================
// ��ʽ��
#ifdef _MO_X64
#define MO_FMT_INT      TC("ld")
#define MO_FMT_HEX      TC("lX")
#define MO_FMT_HEX_FULL TC("016lX")
#define MO_FMT_POINTER  TC("0x%016X")
#else
#define MO_FMT_INT      TC("d")
#define MO_FMT_HEX      TC("X")
#define MO_FMT_HEX_FULL TC("08X")
#define MO_FMT_POINTER  TC("0x%08X")
#endif // _MO_X64
//------------------------------------------------------------
#ifdef _MO_LINUX
#define MO_FMT_INT64   TC("lld")
#else
#ifdef _MO_X64
#define MO_FMT_INT64   TC("l64d")
#else
#define MO_FMT_INT64   TC("lld")
#endif // _MO_X64
#endif // _MO_LINUX

//------------------------------------------------------------
// �߼�����
#define MO_LG_SORT_THRESHOLD 7
#define MO_SORT_SWAP(tmp, a, b) do { (tmp) = (a); (a) = (b); (b) = (tmp); } while(0)

MO_NAMESPACE_BEGIN

const TInt MoSortThreshold = 7;

//============================================================
// <T>�ַ�����</T>
//============================================================
enum EChar{
   EChar_Unknown = 0,
   EChar_Char8   = 1,
   EChar_Char16  = 2,
   EChar_Char32  = 3,
};

//============================================================
// <T>�������͵Ĺ�����</T>
//============================================================
template <typename T>
class RType{
protected:
   static T _default;
public:
   //------------------------------------------------------------
   // ���Ĭ��ֵ
   MO_INLINE static T Default() {
      return _default;
   }
   //------------------------------------------------------------
   // ��÷ǿ�ֵ
   MO_INLINE static T Nvl(T value, T other) {
      return (_default == value) ? other : _default;
   }
   //------------------------------------------------------------
   // ���ָ��
   MO_INLINE static void Clear(T* pMemory) {
      if(NULL != pMemory){
         MO_LIB_TYPE_CLEAR(T, pMemory);
      }
   }
};
//------------------------------------------------------------
template <typename T> T RType<T>::_default;

//============================================================
// <T>����Ļ������ܺ�����</T>
//
// @reference
// @author maocy
// @version 1.0.1
//============================================================
template <typename T>
class RTypes{
public:
   //------------------------------------------------------------
   // <T>�����������Ƚ���������Ĵ�С����С��ʱ���ظ�ֵ���ɵ�������</T>
   typedef TInt (*HComparer)(const T& source, const T& target);
   //------------------------------------------------------------
   // <T>�����������Ƚ���������Ĵ�С����С��ʱ���ظ�ֵ���ɵ�������</T>
   typedef TInt (*HComparerObject)(const T& source, const T& target, TAny* pCondition);
   //------------------------------------------------------------
   // <T>�����������Ƚ���������Ĵ�С����С��ʱ���ظ�ֵ���ɵ�������</T>
   typedef TInt (*HComparerValue)(T source, T target, TAny* pCondition);
public:
   //------------------------------------------------------------
   // <T>������ǰ���Ⱥ��������ȣ�������������ź󳤶ȡ�</T>
   MO_INLINE static TInt CalculateTypeCapacity(TInt lengthOld, TInt lengthNew){
      TInt capacity = 0;
      do{
         // ���ռ�������С��Ĭ��ֵ<C>MO_MEMORY_CAPACITY</C>�ĳ���
         capacity = lengthNew;
         if(capacity < MO_MEMORY_CAPACITY){
            capacity = MO_MEMORY_CAPACITY;
         }
         // �״ε���
         if(0 == lengthOld){
            break;
         }
         // ������С�ڷ�ֵʱ������2������
         if(lengthOld <= MO_MEMORY_EXTEND_CAPACITY){
            capacity += capacity;
            break;
         }
         // ������С�ڷ�ֵʱ������1.5������
         capacity += (capacity >> 1);
      }while(0);
      // ���뵽��������
      TInt blockCount = capacity / MO_MEMORY_CAPACITY;
      if(0 != (capacity % MO_MEMORY_CAPACITY)){
         blockCount++;
      }
      capacity = MO_MEMORY_CAPACITY * blockCount;
      return capacity;
   }
   //------------------------------------------------------------
   // <T>������ǰ����������������������������ź������</T>
   MO_INLINE static TInt CalculateObjectCapacity(TInt countOld, TInt countNew){
      TInt capacity = 0;
      do{
         // ���ռ�������С��Ĭ��ֵ<C>MO_OBJECT_CAPACITY</C>�ĳ���
         capacity = countNew;
         if(capacity < MO_OBJECT_CAPACITY){
            capacity = MO_OBJECT_CAPACITY;
         }
         // �״ε���
         if(0 == countOld){
            break;
         }
         // ������С�ڷ�ֵʱ������2������
         if(countOld <= MO_OBJECT_EXTEND_CAPACITY){
            capacity += capacity;
            break;
         }
         // ������С�ڷ�ֵʱ������1.5������
         capacity += (capacity >> 1);
      }while(0);
      // ���뵽��������
      TInt blockCount = capacity / MO_OBJECT_CAPACITY;
      if(0 != (capacity % MO_OBJECT_CAPACITY)){
         blockCount++;
      }
      capacity = MO_OBJECT_CAPACITY * blockCount;
      return capacity;
   }
public:
   //------------------------------------------------------------
   // <T>�ж�һ��ֵ�Ƿ������ָ�������С�</T>
   MO_INLINE static TBool Contains(const T* pValues, TInt length, T value){
      if((NULL != pValues) && (length > 0)){
         while(--length >= 0){
            if(*pValues++ == value){
               return ETrue;
            }
         }
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE static TBool Equals(const T* pSource, const T* pTarget, TInt length){
      if((NULL != pSource) && (NULL != pTarget) && (length >= 0)){
         // ѭ���ж�ÿһ���Ƿ����
         while(--length >= 0){
            if(*pSource++ != *pTarget++){
               return EFalse;
            }
         }
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE static TBool Equals(const T* pSource, TInt sourceLength, const T* pTarget, TInt targetLength){
      if((NULL != pSource) && (sourceLength >= 0) && (NULL != pTarget) && (targetLength >= 0)){
         // �жϳ����Ƿ����
         if(sourceLength != targetLength){
            return EFalse;
         }
         // ѭ���ж�ÿһ���Ƿ����
         while(--sourceLength >= 0){
            if(*pSource++ != *pTarget++){
               return EFalse;
            }
         }
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>����ָ�������Ƿ�����ڵ�ǰ����Ŀ�ʼλ�á�</T>
   MO_INLINE static TBool StartsWith(const T* pSource, TInt sourceLength, const T* pFind, TInt findLength){
      if((NULL != pSource) && (sourceLength >= 0) && (NULL != pFind) && (findLength >= 0)){
         // ���Ȳ���ʱֱ�ӷ��ؽ��
         if(sourceLength < findLength){
            return EFalse;
         }
         // ��ʼ��������
         return Equals(pSource, pFind, findLength);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>����ָ�������Ƿ�����ڵ�ǰ����Ľ���λ�á�</T>
   MO_INLINE static TBool EndsWith(const T* pSource, TInt sourceLength, const T* pFind, TInt findLength){
      if((NULL != pSource) && (sourceLength >= 0) && (NULL != pFind) && (findLength >= 0)){
         // ���Ȳ���ʱֱ�ӷ��ؽ��
         if(sourceLength < findLength){
            return EFalse;
         }
         // ��ʼ��������
         return Equals(pSource + sourceLength - findLength, pFind, findLength);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж���������Ĵ�С��</T>
   MO_INLINE static TInt Compare(const T* pSource, TInt sourceLength, const T* pTarget, TInt targetLength){
      if((NULL != pSource) && (sourceLength >= 0) && (NULL != pTarget) && (targetLength >= 0)){
         // ѭ���ж�ÿһ��Ĵ�С
         TInt n = -1;
         TInt loop = (sourceLength < targetLength) ? sourceLength : targetLength;
         while(++n < loop){
            if(pSource[n] != pTarget[n]){
               return pSource[n] - pTarget[n];
            }
         }
         // ȫ������һ����ʱ�򣬾��Գ����ж������С
         return sourceLength - targetLength;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж�һ��ֵ������ָ���������״γ��ֵ�����λ�á�</T>
   MO_INLINE static TInt IndexOf(const T* pValues, T value){
      if(NULL != pValues){
         const T* pSearch = pValues;
         while(ETrue){
            if(*pSearch == value){
               return pSearch - pValues;
            }
            pSearch++;
         }
      }
      return ENotFound;
   }
   //------------------------------------------------------------
   // <T>�ж�һ��ֵ������ָ���������״γ��ֵ�����λ�á�</T>
   MO_INLINE static TInt IndexOf(const T* pValues, TInt length, T value){
      if((NULL != pValues) && (length > 0)){
         const T* pSearch = pValues;
         while(--length >= 0){
            if(*pSearch == value){
               return pSearch - pValues;
            }
            pSearch++;
         }
      }
      return ENotFound;
   }
   //------------------------------------------------------------
   // <T>�ж�һ����ֵ������ָ���������״γ��ֵ�����λ�á�</T>
   MO_INLINE static TInt IndexsOf(const T* pValues, TInt length, const T* pFind, TInt findLength){
      if((NULL != pValues) && (length > 0) && (NULL != pFind) && (findLength > 0)){
         const T* pSearch = pValues;
         while(--length >= 0){
            for(TInt n = 0; n < findLength; n++){
               if(*pSearch == pFind[n]){
                  return pSearch - pValues;
               }
            }
            pSearch++;
         }
      }
      return ENotFound;
   }
   //------------------------------------------------------------
   // <T>�ж�һ��ֵ������ָ�������������ֵ�����λ�á�</T>
   MO_INLINE static TInt LastIndexOf(const T* pValues, TInt length, T value){
      if((NULL != pValues) && (length > 0)){
         const T* pSearch = pValues + length;
         while(--length >= 0){
            pSearch--;
            if(*pSearch == value){
               return pSearch - pValues;
            }
         }
      }
      return ENotFound;
   }
public:
   //------------------------------------------------------------
   // <T>��һ�������в�����һ���������״γ��ֵ�����λ�á�</T>
   static TInt Find(const T* pValues, TInt valueLength, const T* pFind, TInt findLength){
      if((NULL != pValues) && (valueLength >=0) && (NULL != pFind) && (findLength >= 0)){
         // �жϳ���
         if((0 == valueLength) && (0 == findLength)){
            return ETrue;
         }
         // ȡ��Ҫ���ҵĵ�һ������
         const T& first = pFind[0];
         // ѭ������ÿһ������
         TInt position = -1;
         TInt length = valueLength - findLength;
         while(++position <= length){
            // ����鵽��һ����������Һ��������
            if(pValues[position] == first){
               TInt n = 0;
               while(++n < findLength){
                  if(pValues[position + n] != pFind[n]){
                      break;
                  }
               }
               // ������ϲ��ҳ����򷵻�����λ��
               if(n == findLength){
                  return position;
               }
            }
         }
      }
      // û�в鵽����
      return ENotFound;
   }
   //------------------------------------------------------------
   // <T>��һ�������в�����һ���������״γ��ֵ�����λ�á�</T>
   static TInt LastFind(const T* pValues, TInt valueLength, const T* pFind, TInt findLength){
      if((NULL != pValues) && (valueLength >=0) && (NULL != pFind) && (findLength >= 0)){
         // �жϳ���
         if((0 == valueLength) && (0 == findLength)){
            return ETrue;
         }
         // ȡ��Ҫ���ҵĵ�һ������
         const T& first = pFind[0];
         // ѭ������ÿһ������
         TInt position = -1;
         TInt length = valueLength - findLength;
         while(++position <= length){
            // ����鵽��һ����������Һ��������
            if(pValues[length - position] == first){
               TInt n = 0;
               while (++n < findLength){
                  if (pValues[length - position + n] != pFind[n]){
                      break;
                  }
               }
               // ������ϲ��ҳ����򷵻�����λ��
               if(n == findLength){
                  return length - position;
               }
            }
         }
      }
      // û�в鵽����
      return ENotFound;
   }
   //------------------------------------------------------------
   // <T>�ж�һ�������������г��ֵĴ�����</T>
   static TInt Count(const T* pValues, TInt length, T value){
      TInt count = 0;
      if((NULL != pValues) && (length > 0)){
         // ���������ҵ���ͬ�Ĳ���
         for(TInt n = 0; n < length; n++){
            if(pValues[n] == value){
               count++;
            }
         }
      }
      return count;
   }
   //------------------------------------------------------------
   // <T>�ж�һ�����������������г��ֵĴ�����</T>
   static TInt Count(const T* pValues, TInt valueLength, const T* pFind, TInt findLength){
      TInt count = 0;
      if((NULL != pValues) && (valueLength > 0) && (NULL != pFind) && (findLength > 0)){
         // ȡ��Ҫ���ҵĵ�һ������
         const T& first = pFind[0];
         // ���������ҵ���ͬ�Ĳ���
         TInt position = -1;
         TInt loop = valueLength - findLength;
         while(++position < loop){
            // ����鵽��һ����������Һ��������
            if(pValues[position] == first){
               TBool result = ETrue;
               for(TInt n = 1; n < findLength; n++){
                  if(pValues[position + n] != pFind[n]){
                     result = EFalse;
                     break;
                  }
               }
               // ������ϲ��ҳ��������
               if(result){
                  count++;
               }
            }
         }
      }
      return count;
   }
   //------------------------------------------------------------
   // <T>�������������ÿһ��ֵ���ۺϹ�ϣֵ��</T>
   static THashCode MakeHashCode(const T* pValues, TInt length){
      THashCode hash = 0;
      if((NULL != pValues) && (length > 0)){
         while(--length >= 0){
            hash += (hash << 4) + (hash << 3) + (hash << 2) + (hash << 1) + pValues[length];
         }
      }
      return hash;
   }
   //------------------------------------------------------------
   // <T>���һ�����������Ϊ������ݡ�</T>
   static void Fill(T* pValues, TInt length, T value){
      if((NULL != pValues) && (length > 0)){
         while(--length >= 0){
            *pValues++ = value;
         }
      }
   }
   //------------------------------------------------------------
   // <T>����ԭ���鵽Ŀ�����顣</T>
   // <P>�ײ���ʵ�֣��ٶȽϿ죬����(Դ��ַ) < (Ŀ���׵�ַ) < (Դ��ַ+���Ƴ���ʱ)��
   //    ���ݻ��������������Ӷ����ƴ���</P>
   MO_INLINE static void Copy(T* pTarget, const T* pSource, TInt length){
      if((NULL != pTarget) && (NULL != pSource) && (length > 0)){
         if(pTarget != pSource){
            memcpy(pTarget, pSource, sizeof(T) * length);
         }
      }
   }
   //------------------------------------------------------------
   // <T>�ƶ�ԭ���鵽Ŀ�����顣</T>
   // <P>�ײ����ʵ�֣��ٶȽ�����������������ƴ���</P>
   MO_INLINE static void Move(T* pTarget, const T* pSource, TInt length){
      if((NULL != pTarget) && (NULL != pSource) && (length > 0)){
         if(pTarget != pSource){
            memmove(pTarget, pSource, sizeof(T) * length);
         }
      }
   }
   //------------------------------------------------------------
   // <T>�滻������ָ������Ϊ��һ�����ݡ�</T>
   MO_INLINE static void Replace(T* pValues, TInt length, T source, T target){
      if((NULL != pValues) && (length > 0)){
         while(--length >= 0){
            if(pValues[length] == source){
               pValues[length] = target;
            }
         }
      }
   }
   //------------------------------------------------------------
   // <T>�滻������ָ����������Ϊ��һ���������ݡ�</T>
   static TInt Replace(T* pValue, TInt length, const T* pSource, TInt sourceLength, const T* pTarget, TInt targetLength, T* pBuffer, TInt bufferLength){
      TInt count = 0;
      if((NULL != pValue) && (length > 0) && (NULL != pSource) && (sourceLength > 0) && (NULL != pTarget) && (targetLength > 0)){
         // ����׸�����
         const T& sourceFirst = pSource[0];
         // ���������ҵ���ͬ�Ĳ���
         TInt start = 0;
         TInt end = 0;
         for(TInt n = 0; n < length; n++){
            if(pValue[n] == sourceFirst){
               // ����λ��
               start = n;
               TBool result = ETrue;
               for(TInt m = 1; m < sourceLength; m++){
                  if(pValue[n + m] != pSource[m]){
                     result = EFalse;
                     break;
                  }
               }
               // ��ʼ�滻
               if(result){
                  // �����м�����
                  for(TInt i = end; i < start; i++){
                     *pBuffer++ = pValue[i];
                     count++;
                  }
                  // ����Ŀ������
                  for(TInt i = 0; i < targetLength; i++){
                     *pBuffer++ = pTarget[i];
                     count++;
                  }
                  end = start + sourceLength;
               }
            }
         }
         // ���Ʋ�������
         for(TInt n = end; n < length; n++){
            *pBuffer++ = pValue[n];
            count++;
         }
         // ��ⳤ��
         if(count > bufferLength){
            return -1;
         }
      }
      return count;
   }
   //------------------------------------------------------------
   // <T>���������Ƴ�ָ�����������ݡ�</T>
   static TInt Remove(T* pValue, TInt length, T value){
      TInt count = 0;
      if((NULL != pValue) && (length > 0)){
         T* pWriter = pValue;
         while(--length >= 0){
            if(pValue[length] != value){
               *pWriter++ = pValue[length];
               count++;
            }
         }
      }
      return count;
   }
   //------------------------------------------------------------
   // <T>����һ�������������������Ϊ�㡣</T>
   MO_INLINE static void Clear(T* pValue, TInt length){
      if((NULL != pValue) && (length > 0)){
         memset(pValue, 0, sizeof(T) * length);
      }
   }
protected:
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ��п�������</T>
   static void InnerQuickSort(T* pItems, int left, int right){
      // ��鷶Χ
      if(left >= right){
         return;
      }
      // ���ڻ�׼ֵʱ��ʹ��ð������
      TInt size = right - left + 1;
      if(size <= MO_TYPE_SORT_THRESHOLD){
         SortBubble(&pItems[left], size);
         return;
      }
      // ��û�׼ֵ
      T value = pItems[left];
      // ��������
      TInt begin = left;
      TInt end = right;
      while(begin != end){
         // ������ǰ�Ƚ�
         while((begin < end) && (pItems[end] >= value)){
            end--;
         }
         pItems[begin] = pItems[end];
         // ǰ�����Ƚ�
         while((begin < end) && (pItems[begin] <= value)){
            begin++;
         }
         pItems[end] = pItems[begin];
      }
      pItems[begin] = value;
      // �ݹ�����
      InnerQuickSort(pItems, left, begin - 1);
      InnerQuickSort(pItems, begin + 1, right);
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ��п�������</T>
   static void InnerQuickSort(T* pItems, int left, int right, HComparer hComparer){
      // ��鷶Χ
      if(left >= right){
         return;
      }
      // ���ڻ�׼ֵʱ��ʹ��ð������
      TInt size = right - left + 1;
      if(size <= MO_TYPE_SORT_THRESHOLD){
         SortBubble(&pItems[left], size, hComparer);
         return;
      }
      // ��û�׼ֵ
      T value = pItems[left];
      // ��������
      TInt begin = left;
      TInt end = right;
      while(begin != end){
         // ������ǰ�Ƚ�
         while((begin < end) && (hComparer(pItems[end], value) >= 0)){
            end--;
         }
         pItems[begin] = pItems[end];
         // ǰ�����Ƚ�
         while((begin < end) && (hComparer(pItems[begin], value) <= 0)){
            begin++;
         }
         pItems[end] = pItems[begin];
      }
      pItems[begin] = value;
      // �ݹ�����
      InnerQuickSort(pItems, left, begin - 1, hComparer);
      InnerQuickSort(pItems, begin + 1, right, hComparer);
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ��п�������</T>
   static void InnerQuickSortObject(T* pItems, int left, int right, HComparerObject hComparer, TAny* pCondition = NULL){
      // ��鷶Χ
      if(left >= right){
         return;
      }
      // ���ڻ�׼ֵʱ��ʹ��ð������
      TInt size = right - left + 1;
      if(size <= MO_TYPE_SORT_THRESHOLD){
         SortBubbleObject(&pItems[left], size, hComparer, pCondition);
         return;
      }
      // ��û�׼ֵ
      T value = pItems[left];
      // ��������
      TInt begin = left;
      TInt end = right;
      while(begin != end){
         // ������ǰ�Ƚ�
         while((begin < end) && (hComparer(pItems[end], value, pCondition) >= 0)){
            end--;
         }
         pItems[begin] = pItems[end];
         // ǰ�����Ƚ�
         while((begin < end) && (hComparer(pItems[begin], value, pCondition) <= 0)){
            begin++;
         }
         pItems[end] = pItems[begin];
      }
      pItems[begin] = value;
      // �ݹ�����
      InnerQuickSortObject(pItems, left, begin - 1, hComparer, pCondition);
      InnerQuickSortObject(pItems, begin + 1, right, hComparer, pCondition);
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ��п�������</T>
   static void InnerQuickSortValue(T* pItems, int left, int right, HComparerValue hComparer, TAny* pCondition = NULL){
      // ��鷶Χ
      if(left >= right){
         return;
      }
      // ���ڻ�׼ֵʱ��ʹ��ð������
      TInt size = right - left + 1;
      if(size <= MO_TYPE_SORT_THRESHOLD){
         SortBubbleValue(&pItems[left], size, hComparer, pCondition);
         return;
      }
      // ��û�׼ֵ
      T value = pItems[left];
      // ��������
      TInt begin = left;
      TInt end = right;
      while(begin != end){
         // ������ǰ�Ƚ�
         while((begin < end) && (hComparer(pItems[end], value, pCondition) >= 0)){
            end--;
         }
         pItems[begin] = pItems[end];
         // ǰ�����Ƚ�
         while((begin < end) && (hComparer(pItems[begin], value, pCondition) <= 0)){
            begin++;
         }
         pItems[end] = pItems[begin];
      }
      pItems[begin] = value;
      // �ݹ�����
      InnerQuickSortValue(pItems, left, begin - 1, hComparer, pCondition);
      InnerQuickSortValue(pItems, begin + 1, right, hComparer, pCondition);
   }
public:
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ���ð������</T>
   static void SortBubble(T* pItems, TInt length){
      TInt loop = length - 1;
      for(TInt j = 0; j < loop; j++){
         for(TInt i = loop; i > j; i--){
            if(pItems[i] < pItems[i-1]){
               T temp = pItems[i];
               pItems[i] = pItems[i-1];
               pItems[i-1] = temp;
            }
         }
      }
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ���ð������</T>
   static void SortBubble(T* pItems, TInt length, HComparer hComparer){
      TInt loop = length - 1;
      for(TInt j = 0; j < loop; j++){
         for(TInt i = loop; i > j; i--){
            if(hComparer(pItems[i], pItems[i-1]) < 0){
               T temp = pItems[i];
               pItems[i] = pItems[i-1];
               pItems[i-1] = temp;
            }
         }
      }
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ���ð������</T>
   static void SortBubbleObject(T* pItems, TInt length, HComparerObject hComparer, TAny* pCondition = NULL){
      TInt loop = length - 1;
      for(TInt j = 0; j < loop; j++){
         for(TInt i = loop; i > j; i--){
            if(hComparer(pItems[i], pItems[i-1], pCondition) < 0){
               T temp = pItems[i];
               pItems[i] = pItems[i-1];
               pItems[i-1] = temp;
            }
         }
      }
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ���ð������</T>
   static void SortBubbleValue(T* pItems, TInt length, HComparerValue hComparer, TAny* pCondition = NULL){
      TInt loop = length - 1;
      for(TInt j = 0; j < loop; j++){
         for(TInt i = loop; i > j; i--){
            if(hComparer(pItems[i], pItems[i-1], pCondition) < 0){
               T temp = pItems[i];
               pItems[i] = pItems[i-1];
               pItems[i-1] = temp;
            }
         }
      }
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ��п�������</T>
   static void SortQuick(T* pItems, TInt count){
      InnerQuickSort(pItems, 0, count - 1);
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ��п�������</T>
   static void SortQuick(T* pItems, TInt count, HComparer hComparer){
      InnerQuickSort(pItems, 0, count - 1, hComparer);
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ��п�������</T>
   static void SortQuickObject(T* pItems, TInt count, HComparerObject hComparer, TAny* pCondition = NULL){
      InnerQuickSortObject(pItems, 0, count - 1, hComparer, pCondition);
   }
   //------------------------------------------------------------
   // <T>�����ݼ��Ͻ��п�������</T>
   static void SortQuickValue(T* pItems, TInt count, HComparerValue hComparer, TAny* pCondition = NULL){
      InnerQuickSortValue(pItems, 0, count - 1, hComparer, pCondition);
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE RTypes<TBool> RBools;
typedef MO_CM_DECLARE RTypes<TByte> RBytes;
typedef MO_CM_DECLARE RTypes<TInt> RInts;
typedef MO_CM_DECLARE RTypes<TInt8> RInt8s;
typedef MO_CM_DECLARE RTypes<TInt16> RInt16s;
typedef MO_CM_DECLARE RTypes<TInt32> RInt32s;
typedef MO_CM_DECLARE RTypes<TInt64> RInt64s;
typedef MO_CM_DECLARE RTypes<TUint> RUints;
typedef MO_CM_DECLARE RTypes<TUint8> RUint8s;
typedef MO_CM_DECLARE RTypes<TUint16> RUint16s;
typedef MO_CM_DECLARE RTypes<TUint32> RUint32s;
typedef MO_CM_DECLARE RTypes<TUint64> RUint64s;
typedef MO_CM_DECLARE RTypes<TFloat> RFloats;
typedef MO_CM_DECLARE RTypes<TDouble> RDoubles;

//============================================================
// <T>�ַ����Ϲ����ࡣ</T>
//
// @refer
//============================================================
template <typename T>
class RCharTypes : public RTypes<T>{
public:
   //------------------------------------------------------------
   // <T>����ַ����ȡ�</T>
   MO_INLINE static TInt Length(const T* pValue){
      TInt length = 0;
      if(NULL != pValue){
         while(*pValue++){
            length++;
         }
      }
      return length;
   }
   //------------------------------------------------------------
   // <T>����ַ����ȡ�</T>
   MO_INLINE static TInt IndexsOf(const T* pValue, const T* pFind){
      TInt valueLength = Length(pValue);
      TInt findLength = Length(pFind);
      TInt result = RTypes<T>::IndexsOf(pValue, valueLength, pFind, findLength);
      return result;
   }
   //------------------------------------------------------------
   // <T>����ַ���ϣֵ��</T>
   MO_INLINE static THashCode MakeHashCode(const T* pValue){
      TInt length = Length(pValue);
      return RTypes<T>::MakeHashCode(pValue, length);
   }
public:
   //------------------------------------------------------------
   // <T>�ж��ַ����Ƿ���ȡ�</T>
   MO_INLINE static TBool Equals(const T* pSource, const T* pTarget){
      TBool result = EFalse;
      if((NULL != pSource) && (NULL != pTarget)){
         TInt sourceLength = Length(pSource);
         TInt targetLength = Length(pTarget);
         result = RTypes<T>::Equals(pSource, sourceLength, pTarget, targetLength);
      }
      return result;
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE RCharTypes<TChar8> RChar8s;
typedef MO_CM_DECLARE RCharTypes<TChar16> RChar16s;
typedef MO_CM_DECLARE RCharTypes<TChar32> RChar32s;
typedef MO_CM_DECLARE RCharTypes<TChar> RChars;

//============================================================
// <T>�������ֵĹ�����</T>
//============================================================
template <typename T>
class RNumber{
public:
   //------------------------------------------------------------
   // <T>�����ַ���Ϊ�з�������</T>
   template <typename C>
   static MO_INLINE TBool IsSignInteger(const C* pValue){
      // ���Ϊ��
      if(NULL == pValue){
         return EFalse;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return EFalse;
      }
      // �������
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         if(' ' == n){
            continue;
         }else if((0 == n) && (('-' == value) || ('+' == value))){
            continue;
         }else if((value >= '0') && (value <= '9')){
            continue;
         }
         return EFalse;
      }
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�����ַ���Ϊ�з�������</T>
   template <typename C>
   static MO_INLINE TBool IsUnsignInteger(const C* pValue){
      // ���Ϊ��
      if(NULL == pValue){
         return EFalse;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return EFalse;
      }
      // �������
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         if(' ' == n){
            continue;
         }else if((value >= '0') && (value <= '9')){
            continue;
         }
         return EFalse;
      }
      return ETrue;
   }
public:
   //------------------------------------------------------------
   // <T>����ʮ�����ַ���Ϊ����</T>
   template <typename C>
   static MO_INLINE T ParseSign(const C* pValue){
      T result = 0;
      // ���Ϊ��
      if(NULL == pValue){
         return result;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return result;
      }
      // ת������
      TBool negative = EFalse;
      TBool hasNumber = EFalse;
      // �����ַ�����
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         // ������ո�
         if(' ' == value){
            continue;
         }
         // ������
         if('-' == value){
            if(hasNumber){
               MO_STATIC_FATAL(TC("Input value is invalid. (value=%s)"), pValue);
            }
            negative = ETrue;
            continue;
         }
         // �������
         if((value < '0') || (value > '9')){
            MO_STATIC_FATAL(TC("Input value is not number. (value=%s)"), pValue);
         }
         // ������
         hasNumber = ETrue;
         result *= 10;
         result += value - '0';
      }
      // ������
      if(negative){
         result = -result;
      }
      return result;
   }
   //------------------------------------------------------------
   // <T>����ʮ�����ַ���Ϊ����</T>
   template <typename C>
   static MO_INLINE T ParseSign(const C* pValue, T defaultValue){
      // ���Ϊ��
      if(NULL == pValue){
         return defaultValue;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return defaultValue;
      }
      // ת������
      T result = 0;
      TBool negative = EFalse;
      TBool hasNumber = EFalse;
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         // ������ո�
         if(' ' == value){
            continue;
         }
         // ������
         if('-' == value){
            if(hasNumber){
               return defaultValue;
            }
            negative = ETrue;
            continue;
         }
         // �������
         if((value < '0') || (value > '9')){
            return defaultValue;
         }
         // ������
         hasNumber = ETrue;
         result *= 10;
         result += value - '0';
      }
      // ������
      if(negative){
         result = -result;
      }
      return result;
   }
   //------------------------------------------------------------
   // <T>����ʮ�����ַ���Ϊ����</T>
   template <typename C>
   static MO_INLINE T ParseUnsign(const C* pValue){
      T result = 0;
      // ���Ϊ��
      if(NULL == pValue){
         return result;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return result;
      }
      // ת������
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         // ������ո�
         if(' ' == value){
            continue;
         }
         // ������
         if('-' == value){
            MO_STATIC_FATAL(TC("Input value is invalid. (value=%s)"), pValue);
         }
         // �������
         if((value < '0') || (value > '9')){
            MO_STATIC_FATAL(TC("Input value is not number. (value=%s)"), pValue);
         }
         // ������
         result *= 10;
         result += value - '0';
      }
      return result;
   }
   //------------------------------------------------------------
   // <T>����ʮ�����ַ���Ϊ����</T>
   template <typename C>
   static MO_INLINE T ParseUnsign(const C* pValue, T defaultValue){
      // ���Ϊ��
      if(NULL == pValue){
         return defaultValue;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return defaultValue;
      }
      // ת������
      T result = 0;
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         // ������ո�
         if(' ' == value){
            continue;
         }
         // ������
         if('-' == value){
            return defaultValue;
         }
         // �������
         if((value < '0') || (value > '9')){
            return defaultValue;
         }
         // ������
         result *= 10;
         result += value - '0';
      }
      return result;
   }
   //------------------------------------------------------------
   // <T>����ʮ�������ַ���Ϊ����</T>
   template <typename C>
   static MO_INLINE T ParseSignHex(const C* pValue){
      T result = 0;
      // ���Ϊ��
      if(NULL == pValue){
         return result;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return result;
      }
      // ת������
      TBool negative = EFalse;
      TBool hasNumber = EFalse;
      // �����ַ�����
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         // ������ո�
         if(' ' == value){
            continue;
         }
         // ������
         if('-' == value){
            if(hasNumber){
               MO_STATIC_FATAL(TC("Input value is invalid. (value=%s)"), pValue);
            }
            negative = ETrue;
            continue;
         }
         // �任����
         TInt temp = -1;
         if((value >= '0') && (value <= '9')){
            temp = value - '0';
         }else if((value >= 'a') && (value <= 'f')){
            temp = value - 'a' + 10;
         }else if((value >= 'A') && (value <= 'F')){
            temp = value - 'A' + 10;
         }
         // �������
         if((temp < 0) || (temp > 15)){
            MO_STATIC_FATAL(TC("Input value is not hex. (value=%s)"), pValue);
         }
         // ������
         hasNumber = ETrue;
         result <<= 4;
         result += temp;
      }
      // ������
      if(negative){
         result = -result;
      }
      return result;
   }
   //------------------------------------------------------------
   // <T>����ʮ�������ַ���Ϊ����</T>
   template <typename C>
   static MO_INLINE T ParseSignHex(const C* pValue, T defaultValue){
      // ���Ϊ��
      if(NULL == pValue){
         return defaultValue;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return defaultValue;
      }
      // ת������
      T result = 0;
      TBool negative = EFalse;
      TBool hasNumber = EFalse;
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         // ������ո�
         if(' ' == value){
            continue;
         }
         // ������
         if('-' == value){
            if(hasNumber){
               return defaultValue;
            }
            negative = ETrue;
            continue;
         }
         // �任����
         TInt temp = -1;
         if((value >= '0') && (value <= '9')){
            temp = value - '0';
         }else if((value >= 'a') && (value <= 'f')){
            temp = value - 'a' + 10;
         }else if((value >= 'A') && (value <= 'F')){
            temp = value - 'A' + 10;
         }
         // �������
         if((temp < 0) || (temp > 15)){
            return defaultValue;
         }
         // ������
         hasNumber = ETrue;
         result <<= 4;
         result += temp;
      }
      // ������
      if(negative){
         result = -result;
      }
      return result;
   }
      //------------------------------------------------------------
   // <T>����ʮ�������ַ���Ϊ����</T>
   template <typename C>
   static MO_INLINE T ParseUnsignHex(const C* pValue){
      T result = 0;
      // ���Ϊ��
      if(NULL == pValue){
         return result;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return result;
      }
      // ת������
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         // ������ո�
         if(' ' == value){
            continue;
         }
         // ������
         if('-' == value){
            MO_STATIC_FATAL(TC("Input value is invalid. (value=%s)"), pValue);
         }
         // �任����
         TInt temp = -1;
         if((value >= '0') && (value <= '9')){
            temp = value - '0';
         }else if((value >= 'a') && (value <= 'f')){
            temp = value - 'a' + 10;
         }else if((value >= 'A') && (value <= 'F')){
            temp = value - 'A' + 10;
         }
         // �������
         if((temp < 0) || (temp > 15)){
            MO_STATIC_FATAL(TC("Input value is not hex. (value=%s)"), pValue);
         }
         // ������
         result <<= 4;
         result += temp;
      }
      return result;
   }
   //------------------------------------------------------------
   // <T>����ʮ�������ַ���Ϊ����</T>
   template <typename C>
   static MO_INLINE T ParseUnsignHex(const C* pValue, T defaultValue){
      // ���Ϊ��
      if(NULL == pValue){
         return defaultValue;
      }
      // ��鳤��
      TInt length = RCharTypes<C>::Length(pValue);
      if(0 == length){
         return defaultValue;
      }
      // ת������
      T result = 0;
      for(TInt n = 0; n < length; n++){
         C value = pValue[n];
         // ������ո�
         if(' ' == value){
            continue;
         }
         // ������
         if('-' == value){
            return defaultValue;
         }
         // �任����
         TInt temp = -1;
         if((value >= '0') && (value <= '9')){
            temp = value - '0';
         }else if((value >= 'a') && (value <= 'f')){
            temp = value - 'a' + 10;
         }else if((value >= 'A') && (value <= 'F')){
            temp = value - 'A' + 10;
         }
         // �������
         if((temp < 0) || (temp > 15)){
            return defaultValue;
         }
         // ������
         result <<= 4;
         result += temp;
      }
      return result;
   }
public:
   //------------------------------------------------------------
   // <T>��ʽ������Ϊʮ�����ַ���</T>
   template <typename C, typename U>
   static MO_INLINE const C* ToSignString(C* pBuffer, TInt capacity, T value){
      // ���Ϊ��
      if(NULL == pBuffer){
         MO_STATIC_FATAL(TC("Conver buffer is null. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      // �������
      if(0 == capacity){
         MO_STATIC_FATAL(TC("Conver buffer length is not enought. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      // ���Ϊ0
      if(0 == value){
         pBuffer[0] = TC('0');
         pBuffer[1] = 0;
         return pBuffer;
      }
      // ���Ϊ����
      C* pWriter = pBuffer;
      TInt position = 0;
      U data = value;
      if(value < 0){
         MO_ASSERT(capacity > 1);
         data = -value;
         *pWriter++ = '-';
         position++;
      }
      // ������ַ���
      TInt index = MO_FS_NUMBER_LENGTH;
      C buffer[MO_FS_NUMBER_LENGTH];
      while(data > 0){
         buffer[--index] = (data % 10) + TC('0');
         data /= 10;
      }
      // ��ת�ַ���
      while((position++ < capacity) && (index < MO_FS_NUMBER_LENGTH)){
         *pWriter++ = buffer[index++];
      }
      *pWriter++ = 0;
      // �������
      if(position > capacity){
         MO_STATIC_FATAL(TC("Conver buffer length is not enought. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      return pBuffer;
   }
   //------------------------------------------------------------
   // <T>��ʽ������Ϊʮ�����ַ���</T>
   template <typename C>
   static MO_INLINE const C* ToUnsignString(C* pBuffer, TInt capacity, T value){
      // ���Ϊ��
      if(NULL == pBuffer){
         MO_STATIC_FATAL(TC("Conver buffer is null. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      // �������
      if(0 == capacity){
         MO_STATIC_FATAL(TC("Conver buffer length is not enought. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      // ���Ϊ0
      if(0 == value){
         pBuffer[0] = TC('0');
         pBuffer[1] = 0;
         return pBuffer;
      }
      // ������ַ���
      C* pWriter = pBuffer;
      TInt index = MO_FS_NUMBER_LENGTH;
      C buffer[MO_FS_NUMBER_LENGTH];
      while(value > 0){
         buffer[--index] = (value % 10) + TC('0');
         value /= 10;
      }
      // ��ת�ַ���
      TInt position = 0;
      while((position++ < capacity) && (index < MO_FS_NUMBER_LENGTH)){
         *pWriter++ = buffer[index++];
      }
      *pWriter++ = 0;
      // �������
      if(position > capacity){
         MO_STATIC_FATAL(TC("Conver buffer length is not enought. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      return pBuffer;
   }
   //------------------------------------------------------------
   // <T>��ʽ������Ϊʮ�������ַ���</T>
   template <typename C>
   static MO_INLINE TCharC* ToHexString(C* pBuffer, TInt capacity, T value){
      // ���Ϊ��
      if(NULL == pBuffer){
         MO_STATIC_FATAL(TC("Conver buffer is null. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      // �������
      if(0 == capacity){
         MO_STATIC_FATAL(TC("Conver buffer length is not enought. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      // ���Ϊ0
      if(0 == value){
         pBuffer[0] = TC('0');
         pBuffer[1] = 0;
         return pBuffer;
      }
      // ������ַ���
      C* pWriter = pBuffer;
      TInt position = 0;
      TInt index = MO_FS_NUMBER_LENGTH;
      C buffer[MO_FS_NUMBER_LENGTH];
      while(value > 0){
         TInt temp = value & 0x0F;
         if(temp > 9){
            buffer[--index] = temp + 'A';
         }else{
            buffer[--index] = temp + '0';
         }
         value >>= 4;
      }
      // ��ת�ַ���
      while((position++ < capacity) && (index < MO_FS_NUMBER_LENGTH)){
         *pWriter++ = buffer[index++];
      }
      *pWriter++ = 0;
      // �������
      if(position > capacity){
         MO_STATIC_FATAL(TC("Conver buffer length is not enought. (buffer=0x%08X, capacity=%d, value=%d)"), pBuffer, capacity, value);
         return pBuffer;
      }
      return pBuffer;
   }
};

//============================================================
// <T>����ֵ�����������ࡣ</T>
//============================================================
class MO_CM_DECLARE RBool : public RType<TBool>{
public:
   static TBool IsTrue(TChar value);
   static TBool IsTrue(TCharC* pValue, TBool defaultValue = EFalse);
public:
   static TBool Parse(TChar value);
   static TBool Parse(TCharC* pValue, TBool defaultValue = EFalse);
   static TBool ParseNvl(TCharC* pValue, TBool defaultValue = EFalse);
public:
   static TChar ToChar(TBool value);
   static TCharC* ToString(TBool value);
   static TCharC* ToDisplay(TBool value);
};

//============================================================
// <T>�ֽڲ����������ࡣ</T>
//============================================================
class MO_CM_DECLARE RByte : public RType<TByte>{
public:
   static TChar HEX_CHARS[16];
   static TByte HEX_BYTES[256];
public:
   static TSize Parse(TCharC* pSource, TSize length, TByte* pBytes, TSize capacity);
public:
   static TCharC* Format(TByteC* pBytes, TInt length, TChar* pSource, TSize capacity);
   static TCharC* FormatDisplay(TByteC* pBytes, TInt length, TChar* pSource, TSize capacity);
   static TCharC* FormatMemory(TByteC* pBytes, TInt count, TInt columns, TChar* pResult, TInt length);
public:
   static TCharC* Dump(TByteC* pBytes, TInt count, TChar* pResult, TInt length);
};

//============================================================
// <T>8λ���������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RInt8 : public RType<TInt8>{
public:
   static TBool Test(TCharC* pSource);
public:
   static TInt8 Parse8(TChar8C* pSource);
   static TInt8 Parse16(TChar16C* pSource);
   static TInt8 Parse32(TChar32C* pSource);
   static TInt8 Parse(TCharC* pSource, TInt8 defaultValue = 0);
   static TInt8 ParseNvl(TCharC* pSource);
   static TInt8 Parse2(TCharC* pSource);
   static TInt8 ParseHex(TCharC* pSource, TInt length = -1);
   static TInt8 ParseHexNvl(TCharC* pSource, TInt length = -1);
public:
   static TCharC* ToString(TInt8 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToString2(TInt8 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TInt8 value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>16λ���������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RInt16 : public RType<TInt16>{
public:
   static TBool Test(TCharC* pSource);
public:
   static TInt16 Parse8(TChar8C* pValue);
   static TInt16 Parse16(TChar16C* pValue);
   static TInt16 Parse32(TChar32C* pValue);
   static TInt16 Parse(TCharC* pValue, TInt16 defaultValue = 0);
   static TInt16 ParseNvl(TCharC* pValue);
   static TInt16 ParseHex(TCharC* pSource, TInt length = -1);
   static TInt16 ParseHexNvl(TCharC* pSource, TInt length = -1);
public:
   static TCharC* ToString(TInt16 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TInt16 value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>32λ���������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RInt32 : public RType<TInt32>{
public:
   static TBool Test(TCharC* pSource);
public:
   static TInt32 Parse8(TChar8C* pValue);
   static TInt32 Parse16(TChar16C* pValue);
   static TInt32 Parse32(TChar32C* pValue);
   static TInt32 Parse(TCharC* pValue);
   static TInt32 ParseNvl(TCharC* pValue);
   static TInt32 ParseHex(TCharC* pSource, TInt length = -1);
   static TInt32 ParseHexNvl(TCharC* pSource, TInt length = -1);
public:
   static TCharC* ToString(TInt32 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TInt32 value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>64λ���������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RInt64 : public RType<TInt64>{
public:
   static TBool Test(TCharC* pSource);
public:
   static TInt64 Parse8(TChar8C* pValue);
   static TInt64 Parse16(TChar16C* pValue);
   static TInt64 Parse32(TChar32C* pValue);
   static TInt64 Parse(TCharC* pValue);
   static TInt64 ParseNvl(TCharC* pValue);
   static TInt64 ParseHex(TCharC* pSource, TInt length = -1);
   static TInt64 ParseHexNvl(TCharC* pSource, TInt length = -1);
public:
   static TChar8C* ToString8(TInt64 value, TChar8* pBuffer, TInt capacity);
   static TChar16C* ToString16(TInt64 value, TChar16* pBuffer, TInt capacity);
   static TChar32C* ToString32(TInt64 value, TChar32* pBuffer, TInt capacity);
   static TCharC* ToString(TInt64 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TInt64 value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>8λ�޷������������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RUint8 : public RType<TUint8>{
public:
   static TBool Test(TCharC* pSource);
public:
   static TUint8 Parse8(TChar8C* pValue);
   static TUint8 Parse16(TChar16C* pValue);
   static TUint8 Parse32(TChar32C* pValue);
   static TUint8 Parse(TCharC* pValue);
   static TUint8 ParseNvl(TCharC* pValue);
   static TUint8 ParseHex(TCharC* pSource, TInt length = -1);
   static TUint8 ParseHexNvl(TCharC* pSource, TInt length = -1);
public:
   static TCharC* ToString(TUint8 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TUint8 value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>16λ�޷������������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RUint16 : public RType<TUint16>{
public:
   static TBool Test(TCharC* pValue);
public:
   static TUint16 Parse8(TChar8C* pValue);
   static TUint16 Parse16(TChar16C* pValue);
   static TUint16 Parse32(TChar32C* pValue);
   static TUint16 Parse(TCharC* pValue);
   static TUint16 ParseNvl(TCharC* pValue, TUint16 defaultValue = 0);
   static TUint16 ParseHex(TCharC* pSource, TInt length = -1);
   static TUint16 ParseHexNvl(TCharC* pSource, TInt length = -1);
public:
   static TCharC* ToString(TUint16 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TUint16 value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>32λ�޷������������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RUint32 : public RType<TUint32>{
public:
   static TBool Test(TCharC* pValue);
public:
   static TUint32 Parse8(TChar8C* pValue);
   static TUint32 Parse16(TChar16C* pValue);
   static TUint32 Parse32(TChar32C* pValue);
   static TUint32 Parse(TCharC* pValue);
   static TUint32 ParseNvl(TCharC* pValue);
   static TUint32 ParseHex(TCharC* pSource, TInt length = -1);
   static TUint32 ParseHexNvl(TCharC* pSource, TInt length = -1);
public:
   static TCharC* ToString(TUint32 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TUint32 value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>64λ�޷������������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RUint64 : public RType<TUint64>{
public:
   static TBool Test(TCharC* pValue);
public:
   static TUint64 Parse8(TChar8C* pValue);
   static TUint64 Parse16(TChar16C* pValue);
   static TUint64 Parse32(TChar32C* pValue);
   static TUint64 Parse(TCharC* pValue);
   static TUint64 ParseNvl(TCharC* pValue);
   static TUint64 ParseHex(TCharC* pSource, TInt length = -1);
   static TUint64 ParseHexNvl(TCharC* pSource, TInt length = -1);
public:
   static TChar8C* ToString8(TUint64 value, TChar8* pBuffer, TInt capacity);
   static TChar16C* ToString16(TUint64 value, TChar16* pBuffer, TInt capacity);
   static TChar32C* ToString32(TUint64 value, TChar32* pBuffer, TInt capacity);
   static TCharC* ToString(TUint64 value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TUint64 value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>�����������������ࡣ</T>
// <P>�ֽ�����4Byte, HEX�ַ�����8�ַ���</P>
//============================================================
class MO_CM_DECLARE RFloat : public RType<TFloat>{
public:
   static TBool IsFloat(TCharC* pValue);
public:
   static TFloat InRange(TFloat value, TFloat min, TFloat max);
public:
   static TFloat Parse8(TChar8C* pValue);
   static TFloat Parse16(TChar16C* pValue);
   static TFloat Parse32(TChar32C* pValue);
   static TFloat Parse(TCharC* pValue);
   static TFloat ParseNvl(TCharC* pValue);
   static TFloat ParseHex(TCharC* pValue);
   static TFloat ParseHexNvl(TCharC* pValue);
public:
   static TChar8C* ToString8(TFloat value, TChar8* pBuffer, TInt capacity);
   static TChar16C* ToString16(TFloat value, TChar16* pBuffer, TInt capacity);
   static TChar32C* ToString32(TFloat value, TChar32* pBuffer, TInt capacity);
   static TCharC* ToString(TFloat value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TFloat value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>˫�����������ࡣ</T>
// <P>�ֽ�����8Byte, HEX�ַ�����16�ַ���</P>
//============================================================
class MO_CM_DECLARE RDouble : public RType<TDouble>{
public:
   static TBool IsDouble(TCharC* pValue);
public:
   static TDouble InRange(TDouble value, TDouble min, TDouble max);
public:
   static TDouble Parse8(TChar8C* pValue);
   static TDouble Parse16(TChar16C* pValue);
   static TDouble Parse32(TChar32C* pValue);
   static TDouble Parse(TCharC* pValue);
   static TDouble ParseNvl(TCharC* pValue);
   static TDouble ParseHex(TCharC* pValue);
   static TDouble ParseHexNvl(TCharC* pValue);
public:
   static TChar8C* ToString8(TDouble value, TChar8* pBuffer, TInt capacity);
   static TChar16C* ToString16(TDouble value, TChar16* pBuffer, TInt capacity);
   static TChar32C* ToString32(TDouble value, TChar32* pBuffer, TInt capacity);
   static TCharC* ToString(TDouble value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TDouble value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>8λ�ַ������ࡣ</T>
//
// @refer
//============================================================
class MO_CM_DECLARE RChar8 : public RType<TChar8>{
public:
   static TBool IsAlphaNumber(TChar8 value);
   static TBool IsAlpha(TChar8 value);
   static TBool IsControl(TChar8 value);
   static TBool IsDigit(TChar8 value);
   static TBool IsDigitX(TChar8 value);
   static TBool IsLower(TChar8 value);
   static TBool IsUpper(TChar8 value);
   static TBool IsGraphics(TChar8 value);
   static TBool IsPrint(TChar8 value);
   static TBool IsPunct(TChar8 value);
   static TBool IsSpace(TChar8 value);
public:
   static TInt CompareIgnoreCase(TChar8C* pSource, TChar8C* pTarget);
public:
   static void ToLower(TChar8* pValues, TInt length);
   static void ToUpper(TChar8* pValues, TInt length);
public:
   static TInt ConvertTo16(TChar8C* pValue);
   static TInt ConvertTo16(TChar16* pOutput, TSize size, TChar8C* pValue);
   static TInt ConvertTo32(TChar8C* pValue);
   static TInt ConvertTo32(TChar32* pOutput, TSize size, TChar8C* pValue);
   static TInt ConvertToUtf8(TChar8C* pValue);
   static TInt ConvertToUtf8(TChar16* pOutput, TSize size, TChar8C* pValue);
};

//============================================================
// <T>16λ�ַ������ࡣ</T>
//
// @refer
//============================================================
class MO_CM_DECLARE RChar16 : public RType<TChar16>{
public:
   static TBool IsAlphaNumber(TChar16 value);
   static TBool IsAlpha(TChar16 value);
   static TBool IsControl(TChar16 value);
   static TBool IsDigit(TChar16 value);
   static TBool IsDigitX(TChar16 value);
   static TBool IsLower(TChar16 value);
   static TBool IsUpper(TChar16 value);
   static TBool IsGraphics(TChar16 value);
   static TBool IsPrint(TChar16 value);
   static TBool IsPunct(TChar16 value);
   static TBool IsSpace(TChar16 value);
public:
   static TInt CompareIgnoreCase(TChar16C* pSource, TChar16C* pTarget);
public:
   static void ToLower(TChar16* pValues, TInt length);
   static void ToUpper(TChar16* pValues, TInt length);
public:
   static TInt ConvertTo8(TChar16C* pValue);
   static TInt ConvertTo8(TChar8* pOutput, TSize size, TChar16C* pValue);
   static TInt ConvertTo32(TChar16C* pValue);
   static TInt ConvertTo32(TChar32* pOutput, TSize size, TChar16C* pValue);
   static TInt ConvertToUtf8(TChar16C* pValue);
   static TInt ConvertToUtf8(TChar8* pOutput, TSize size, TChar16C* pValue);
};

//============================================================
// <T>32λ�ַ������ࡣ</T>
//
// @refer
//============================================================
class MO_CM_DECLARE RChar32 : public RType<TChar32>{
public:
   static TBool IsAlphaNumber(TChar32 value);
   static TBool IsAlpha(TChar32 value);
   static TBool IsControl(TChar32 value);
   static TBool IsDigit(TChar32 value);
   static TBool IsDigitX(TChar32 value);
   static TBool IsLower(TChar32 value);
   static TBool IsUpper(TChar32 value);
   static TBool IsGraphics(TChar32 value);
   static TBool IsPrint(TChar32 value);
   static TBool IsPunct(TChar32 value);
   static TBool IsSpace(TChar32 value);
public:
   static TInt CompareIgnoreCase(TChar32C* pSource, TChar32C* pTarget);
public:
   static void ToLower(TChar32* pValues, TInt length);
   static void ToUpper(TChar32* pValues, TInt length);
public:
   static TInt ConvertTo8(TChar32C* pValue);
   static TInt ConvertTo8(TChar8* pOutput, TSize size, TChar32C* pValue);
   static TInt ConvertTo16(TChar32C* pValue);
   static TInt ConvertTo16(TChar16* pOutput, TSize size, TChar32C* pValue);
};

//============================================================
// <T>�������ݼ��ϡ�</T>
//
// @history 110113 MAOCY ����
//============================================================
template <typename T>
class TRfrTypes{
protected:
   T* _pMemory;
   TUint16 _size;
   TUint16 _length;
public:
   //------------------------------------------------------------
   // <T>�����������ݼ��ϡ�</T>
   TRfrTypes(){
      _length = 0;
      _size = 0;
      MO_CLEAR(_pMemory);
   }
   //------------------------------------------------------------
   // <T>�����������ݼ��ϡ�</T>
   TRfrTypes(T* pMemory, TInt size){
      _pMemory = pMemory;
      _size = size;
      _length = 0;
   }
public:
   //------------------------------------------------------------
   // <T>ת��ָ�����͡�</T>
   MO_INLINE operator const T*() const{
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>ת��ָ�����͡�</T>
   MO_INLINE operator T*(){
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE const T& operator[](TInt index) const{
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE T& operator[](TInt index){
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == _length);
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TInt Length() const{
      return _length;
   }
   //------------------------------------------------------------
   // <T>����ڲ�����ָ�롣</T>
   MO_INLINE const T* MemoryC() const{
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>����ڲ�����ָ�롣</T>
   MO_INLINE T* Memory(){
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE const T& Get(TInt index) const{
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE T& Get(TInt index){
      MO_ASSERT_RANGE(index, 0, _length);
      return _pMemory[index];
   }
public:
   //------------------------------------------------------------
   // <T>�����������á�</T>
   void Attach(T* pMemory, TInt size){
      _pMemory = pMemory;
      _size = size;
      _length = 0;
   }
   //------------------------------------------------------------
   // <T>׷���������ݡ�</T>
   void Appand(const T* pMemory, TInt length){
      MO_ASSERT(_length + length < _size);
      memcpy(_pMemory + _length, pMemory, sizeof(T) * length);
      _length += length;
   }
   //------------------------------------------------------------
   // <T>����һ�����ݡ�</T>
   void Push(const T& value){
      MO_ASSERT(_length + 1 < _size);
      _pMemory[_length++] = value;
   }
   //------------------------------------------------------------
   // <T>�����ڲ����ݡ�</T>
   void Reset(){
      _length = 0;
   }
};

//============================================================
// <T>���ö��󼯺ϡ�</T>
//
// @history 110113 MAOCY ����
//============================================================
template <typename T>
class TRfrObjects{
protected:
   T* _pItems;
   TUint16 _size;
   TUint16 _count;
public:
   //------------------------------------------------------------
   // <T>�������ö��󼯺ϡ�</T>
   TRfrObjects(){
      _count = 0;
      _size = 0;
      MO_CLEAR(_pItems);
   }
   //------------------------------------------------------------
   // <T>�������ö��󼯺ϡ�</T>
   TRfrObjects(T* pItems, TInt size){
      _pItems = pItems;
      _size = size;
      _count = 0;
   }
public:
   //------------------------------------------------------------
   // <T>ת��ָ�����͡�</T>
   MO_INLINE operator const T*() const{
      return _pItems;
   }
   //------------------------------------------------------------
   // <T>ת��ָ�����͡�</T>
   MO_INLINE operator T*(){
      return _pItems;
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE const T& operator[](TInt index) const{
      MO_ASSERT_RANGE(index, 0, _count);
      return _pItems[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE T& operator[](TInt index){
      MO_ASSERT_RANGE(index, 0, _count);
      return _pItems[index];
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TInt Count() const{
      return _count;
   }
   //------------------------------------------------------------
   // <T>����ڲ�����ָ�롣</T>
   MO_INLINE const T* MemoryC() const{
      return _pItems;
   }
   //------------------------------------------------------------
   // <T>����ڲ�����ָ�롣</T>
   MO_INLINE T* Memory(){
      return _pItems;
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE const T& Get(TInt index) const{
      MO_ASSERT_RANGE(index, 0, _count);
      return _pItems[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE T& Get(TInt index){
      MO_ASSERT_RANGE(index, 0, _count);
      return _pItems[index];
   }
public:
   //------------------------------------------------------------
   // <T>�����������á�</T>
   MO_INLINE void Attach(T* pItems, TInt size){
      _pItems = pItems;
      _size = size;
      _count = 0;
   }
   //------------------------------------------------------------
   // <T>׷���������ݡ�</T>
   MO_INLINE void Appand(const T* pItems, TInt count){
      MO_ASSERT(_count + count < _size);
      memcpy(_pItems + _count, pItems, sizeof(T) * count);
      _count += count;
   }
   //------------------------------------------------------------
   // <T>����һ�����ݡ�</T>
   MO_INLINE void Push(const T& value){
      MO_ASSERT(_count + 1 < _size);
      _pItems[_count++] = value;
   }
   //------------------------------------------------------------
   // <T>�����ڲ����ݡ�</T>
   MO_INLINE void Reset(){
      _count = 0;
   }
};

//============================================================
// <T>ֻ���ڵ��������</T>
//
// @tool
// @history 100318 MAOCY ����
//============================================================
template <typename T>
class TStackIteratorC{
protected:
   T* _pMemory;
   TInt _length;
   TInt _index;
public:
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TStackIteratorC(){
      _pMemory = NULL;
      _length = 0;
      _index = -1;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TStackIteratorC(const TStackIteratorC& iterator){
      _pMemory = iterator._pMemory;
      _length = iterator._length;
      _index = iterator._index;
   }
   //------------------------------------------------------------
   // <T>����ֻ����������</T>
   TStackIteratorC(T* pMemory, TInt length){
      _pMemory = pMemory;
      _length = length;
      _index = -1;
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const TBool operator==(T value) const{
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _length);
      return (_pMemory[_index] == value);
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T& operator *() const{
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _length);
      return _pMemory[_index];
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE const T* operator->() const{
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _length);
      return &_pMemory[_index];
   }
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return (0 == _length);
   }
   //------------------------------------------------------------
   // <T>�ж����������Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(T value){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _length);
      return (_pMemory[_index] == value);
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE T& Get(){
      MO_ASSERT(_pMemory);
      MO_ASSERT_RANGE(_index, 0, _length);
      return _pMemory[_index];
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      return (_length > 0) ? _index + 1 < _length : EFalse;
   }
   //------------------------------------------------------------
   //<T> �ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      if(_length > 0 && (_index + 1 < _length)){
         _index++;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return (_length > 0) ? _index - 1 >= 0 : EFalse;
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      if(_length > 0 && (_index + 1 < _length)){
         _index--;
         return ETrue;
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
      _index = -1;
   }
};

//============================================================
// <T>����ջ���ݼ��ϡ�</T>
//
// @history 100318 MAOCY ����
//============================================================
template <typename T, TInt S>
class TStackTypes{
public:
   typedef TInt (*HComparer) (const T&, const T&);
   typedef TStackIteratorC<T> TIteratorC;
protected:
   TInt _length;
#ifdef _MO_DEBUG
   T _memory[S];
#else
   TByte _memory[sizeof(T) * S];
#endif // _MO_DEBUG
public:
   //------------------------------------------------------------
   // <T>���춨��ջ���ݼ��ϡ�</T>
   TStackTypes(){
      _length = 0;
   }
public:
   //------------------------------------------------------------
   // <T>���ֻ������ָ�롣</T>
   MO_INLINE operator const T*() const{
      return (T*)_memory;
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE operator T*(){
      return (T*)_memory;
   }
   //------------------------------------------------------------
   // <T>�������λ�õ�ֻ�����ݡ�</T>
   MO_INLINE const T& operator[](TInt index) const{
      MO_ASSERT_RANGE(index, 0, S);
      return ((T*)_memory)[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE T& operator[](TInt index){
      MO_ASSERT_RANGE(index, 0, S);
      return ((T*)_memory)[index];
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == _length);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�������</T>
   MO_INLINE TBool IsFull() const{
      return (S == _length);
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TSize Length() const{
      return _length;
   }
   //------------------------------------------------------------
   // <T>�������������</T>
   MO_INLINE static TInt Size(){
      return S;
   }
   //------------------------------------------------------------
   // <T>���ֻ������ָ�롣</T>
   MO_INLINE const T* MemoryC() const{
      return (T*)_memory;
   }
   //------------------------------------------------------------
   // <T>�������ָ�롣</T>
   MO_INLINE T* Memory(){
      return (T*)_memory;
   }
   //------------------------------------------------------------
   // <T>���ֻ���ײ����ݡ�</T>
   MO_INLINE const T& FirstC() const{
      MO_ASSERT(_length > 0);
      T* pMemory = (T*)_memory;
      return pMemory[0];
   }
   //------------------------------------------------------------
   // <T>����ײ����ݡ�</T>
   MO_INLINE T& First(){
      MO_ASSERT(_length > 0);
      T* pMemory = (T*)_memory;
      return pMemory[0];
   }
   //------------------------------------------------------------
   // <T>���ֻ��β�����ݡ�</T>
   MO_INLINE const T& LastC() const{
      MO_ASSERT(_length > 0);
      T* pMemory = (T*)_memory;
      return pMemory[_length - 1];
   }
   //------------------------------------------------------------
   // <T>���β�����ݡ�</T>
   MO_INLINE T& Last(){
      MO_ASSERT(_length > 0);
      T* pMemory = (T*)_memory;
      return pMemory[_length - 1];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ�ֻ�����ݡ�</T>
   MO_INLINE const T& GetC(TInt index) const{
      MO_ASSERT_RANGE(index, 0, S);
      T* pMemory = (T*)_memory;
      return pMemory[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE T& Get(TInt index){
      MO_ASSERT_RANGE(index, 0, S);
      T* pMemory = (T*)_memory;
      return pMemory[index];
   }
   //------------------------------------------------------------
   // <T>���ֻ����������</T>
   MO_INLINE TIteratorC IteratorC(){
      return TIteratorC((T*)_memory, _length);
   }
public:
   //------------------------------------------------------------
   // <T>���ֻ��ָ�롣</T>
   MO_INLINE TPtrC<T> PtrC(){
      return TPtrC<T>((T*)_memory, _length);
   }
   //------------------------------------------------------------
   // <T>���ָ�롣</T>
   MO_INLINE TPtr<T> Ptr(){
      return TPtr<T>((T*)_memory, &_length, S);
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(const T* pMemory, TInt length){
      MO_ASSERT(pMemory);
      if(_length != length){
         return EFalse;
      }
      return RTypes<T>::Equals((T*)_memory, pMemory, length);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(const TStackTypes<T, S>& value){
      return Equals(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>�������ݳ��ȡ�</T>
   MO_INLINE void SetLength(TInt length){
      MO_ASSERT_BETWEEN(length, 0, S);
      _length = length;
   }
   //------------------------------------------------------------
   // <T>�������ݵ�ȷ�����ȡ�</T>
   MO_INLINE void EnsureLength(TInt length){
      MO_ASSERT_BETWEEN(length, 0, S);
      if(length > _length){
         _length = length;
      }
   }
public:
   //------------------------------------------------------------
   // <T>�����ⲿ���ݡ�</T>
   MO_INLINE void Assign(const T* pMemory, TInt length){
      if(NULL != pMemory){
         if((_length < 0) || (_length > S) || (length < 0) || (length > S)){
            MO_FATAL(TC("Assign range is invalid. (current=%d, assign=%d, size=%d)"), _length, length, S);
         }else{
            MO_LIB_TYPES_COPY(T, (T*)_memory, S, pMemory, length);
            _length = length;
         }
      }else{
         MO_FATAL(TC("Assign memory is null."));
      }
   }
   //------------------------------------------------------------
   // <T>�����ⲿ���ݡ�</T>
   MO_INLINE void Assign(TStackTypes<T, S>& values){
      Assign(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>׷���ⲿ���ݵ�β����</T>
   MO_INLINE void Append(const T* pMemory, TInt length){
      // ����������Ϸ���
      if((_length < 0) || (_length > S) || (_length < 0) || (_length > S)){
         MO_FATAL(TC("This is invalid. (length=%d, size=%d)"), _length, S);
         return;
      }
      // ׷���ⲿ����
      if(NULL != pMemory){
         if((length < 0) || (_length + length > S)){
            MO_FATAL(TC("Append range is invalid. (current=%d, assign=%d, size=%d)"), _length, length, S);
         }else{
            T* pTarget = (T*)_memory;
            MO_LIB_TYPES_COPY(T, pTarget + _length, S - _length, pMemory, length);
            _length += length;
         }
      }else{
         MO_FATAL(TC("Append memory is null."));
      }
   }
   //------------------------------------------------------------
   // <T>׷���ⲿ���ݵ�β����</T>
   MO_INLINE void Append(TStackTypes<T, S>& values){
      Append(values.MemoryC(), values.Length());
   }
   //------------------------------------------------------------
   // <T>�ռ�һ�������ݡ�</T>
   MO_INLINE T& Alloc(){
      T* pMemory = (T*)_memory;
      if((_length < 0) || (_length >= S)){
         T& value = pMemory[S - 1];
         MO_FATAL(TC("Alloc memory full. (length=%d, size=%d)"), _length, S);
         return value;
      }else{
         T& value = pMemory[_length++];
         MO_LIB_TYPE_CLEAR(T, &value);
         return value;
      }
   }
   //------------------------------------------------------------
   // <T>�ռ�һ��ָ������λ�õĿ����ݡ�</T>
   MO_INLINE T& Alloc(TInt index){
      T* pMemory = (T*)_memory;
      if((_length < 0) || (_length > S) || (index < 0) || (index >= S)){
         T& value = pMemory[S - 1];
         MO_FATAL(TC("Alloc index memory invalid. (index=%d, length=%d, size=%d)"), index, _length, S);
         return value;
      }else{
         T& value = pMemory[index++];
         MO_LIB_TYPE_CLEAR(T, &value);
         if(index > _length){
            _length = index;
         }
         return value;
      }
   }
   //------------------------------------------------------------
   // <T>����һ����ֵ��β����</T>
   MO_INLINE void Push(T& value){
      if((_length < 0) || (_length >= S)){
         MO_FATAL(TC("Push memory full. (length=%d, size=%d)"), _length, S);
      }else{
         T* pMemory = (T*)_memory;
         MO_LIB_TYPE_COPY(T, pMemory + _length, &value);
         _length++;
      }
   }
   //------------------------------------------------------------
   // <T>ɾ��һ��ָ������λ�õ����ݡ�</T>
   MO_INLINE TBool Delete(TInt index, T* pValue = NULL){
      // ������
      if((_length < 0) || (_length >= S) || (index < 0) || (index >= _length)){
         MO_FATAL(TC("Delete index is invalid. (index=%d, length=%d, size=%d)"), index, _length, S);
         return EFalse;
      }
      // ��������
      T* pMemory = (T*)_memory;
      if(NULL != pValue){
         MO_LIB_TYPE_COPY(T, pValue, pMemory + index);
      }
      // ɾ������
      TInt size = _length - index - 1;
      if(size > 0){
         MO_LIB_TYPES_MOVE(T, pMemory + index, size, pMemory + index + 1, size);
      }
      _length--;
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ɾ���ײ����ݡ�</T>
   MO_INLINE TBool RemoveFirst(T* pValue = NULL){
      if(_length > 0){
         return Delete(0, pValue);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>ɾ��β�����ݡ�</T>
   MO_INLINE TBool RemoveLast(T* pValue = NULL){
      if(_length > 0){
         return Delete(_length - 1, pValue);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>����ڲ���</T>
   MO_INLINE void Clear(){
      _length = 0;
   }
   //------------------------------------------------------------
   // <T>�����ڲ���</T>
   MO_INLINE void Reset(){
      _length = 0;
   }
};

//============================================================
// <T>����ջ�ַ�����</T>
//
// @history 100902 MAOCY ����
//============================================================
template <TInt S>
class TStackString : public TStackTypes<TChar, S>{
public:
   //------------------------------------------------------------
   // <T>���춨��ջ�ַ�����</T>
   TStackString(){
      Set(NULL);
   }
   //------------------------------------------------------------
   // <T>���춨��ջ�ַ�����</T>
   TStackString(TCharC* pValue){
      Set(pValue);
   }
public:
   //------------------------------------------------------------
   MO_INLINE void operator=(TCharC* pValue){
      Set(pValue);
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰ�ݻ�������һ��β�����ַ���</T>
   MO_INLINE TSize Capacity(){
      TSize capacity = sizeof(TUint16) + 1;
      capacity += sizeof(TChar) * this->_length;
      return capacity;
   }
   //------------------------------------------------------------
   // <T>������Ϣ���Լ��ڲ���</T>
   MO_INLINE void Assign(const TStackString<S>& value){
      Set((TChar*)value._memory);
      this->_length = value._length;
   }
   //------------------------------------------------------------
   // <T>׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
   // <P>�������С��0�����Զ�����ָ������ݳ��ȡ�</P>
   MO_INLINE void Append(TCharC* pValue, TInt length = -1){
      // ���ָ��
      if(NULL == pValue){
         return;
      }
      // ��ȡ����
      if(length <= 0){
         length = RTypes<TChar>::IndexOf(pValue, 0);
      }
      // ��鳤��
      if(this->_length + length + 1 >= S){
         MO_FATAL("Append string length invalid. (length=%d, size=%d, value=%d:%s)", this->_length, S, length, pValue);
         length = S - this->_length - 1;
      }
      // ��������
      if(length > 0){
         TChar* pMemory = (TChar*)this->_memory;
         MO_LIB_TYPES_COPY(TChar, pMemory + this->_length, S - this->_length, pValue, length);
         this->_length += length;
         pMemory[this->_length] = 0;
      }
   }
   //------------------------------------------------------------
   // <T>׷��һ����ʽ���ַ���������β����</T>
   MO_INLINE void AppendFormat(TCharC* pFormat, ...){
      // ��ʽ���ɱ�����ַ�����Ϣ
      va_list params;
      va_start(params, pFormat);
      // �����־��Ϣ
   #ifdef _MO_WINDOWS
      TInt length = _vscprintf(pFormat, params);
      MO_ASSERT_RANGE(this->_length + length + 1, 0, S);
      length = vsprintf_s(_pMemory + _length, length + 1, pFormat, params);
      this->_length += length;
   #else
      TChar buffer[MO_FS_SPRINT_LENGTH];
      vsnprintf(buffer, MO_FS_SPRINT_LENGTH, pFormat, params);
      Append(buffer);
   #endif
      va_end(params);
   }
   // ------------------------------------------------------------
   // ׷��һ����ʽ�ַ���
   MO_INLINE void AppendFormat(TCharC* pFormat, va_list& params){
#ifdef _MO_WINDOWS
      TInt length = _vscprintf(pFormat, params);
      MO_ASSERT_RANGE(this->_length + length + 1, 0, S);
      length = vsprintf_s(_pMemory + _length, length + 1, pFormat, params);
      this->_length += length;
#else
      TChar buffer[MO_FS_SPRINT_LENGTH];
      vsnprintf(buffer, MO_FS_SPRINT_LENGTH, pFormat, params);
      Append(buffer);
#endif
   }
   //------------------------------------------------------------
   // <T>�����ڲ����ݡ�</T>
   MO_INLINE void Set(TCharC* pValue){
      TInt length = 0;
      if(NULL != pValue){
         length = RTypes<TChar>::IndexOf(pValue, 0);
         if(length >= S){
            MO_FATAL("Set string length invalid. (size=%d, value=%d:%s)", S, length, pValue);
            length = S - 1;
         }
         if(length > 0){
            MO_LIB_TYPES_COPY(TChar, this->_memory, S, pValue, length);
         }
      }
      this->_length = length;
      ((TChar*)this->_memory)[this->_length] = 0;
   }
   //------------------------------------------------------------
   // <T>���л��ڲ����ݵ���������</T>
   // <P>�ౣ��һ����β���ַ���</P>
   MO_INLINE TInt Serialize(TAny* pMemory){
      TByte* pPtr = (TByte*)pMemory;
      *(TUint16*)pPtr = this->_length;
      TInt total = sizeof(TChar) * this->_length;
      if(total > 0){
         MO_LIB_MEMORY_COPY(pPtr + sizeof(TUint16), total, this->_memory, total);
      }
      return sizeof(TUint16) + total;
   }
   //------------------------------------------------------------
   // <T>�����л����������ڲ����ݡ�</T>
   MO_INLINE TInt Unserialize(TAnyC* pMemory){
      TByteC* pPtr = (TByteC*)pMemory;
      this->_length = *(TUint16*)pPtr;
      TInt total = sizeof(TChar) * this->_length;
      if(total > 0){
         MO_LIB_MEMORY_COPY(this->_memory, S, pPtr + sizeof(TUint16), total);
      }
      MO_ASSERT(this->_length + 1 < S);
      ((TChar*)this->_memory)[this->_length] = 0;
      return sizeof(TUint16) + total;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Fix(){
      this->_length = RTypes<TChar>::IndexOf((TChar*)this->_memory, 0);
   }
   //------------------------------------------------------------
   // <T>����ڲ����ݵ��ⲿ��</T>
   MO_INLINE TCharC* ToString(TChar* pValue, TInt capacity){
      MO_ASSERT(pValue);
      MO_ASSERT(capacity > this->_length + 1);
      MO_LIB_TYPES_COPY(TChar, pValue, capacity, this->_memory, this->_length + 1);
      return pValue;
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE void Clear(){
      this->_length = 0;
      ((TChar*)this->_memory)[0] = 0;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      this->_length = 0;
      ((TChar*)this->_memory)[0] = 0;
   }
};

//============================================================
// <T>����ջ���󼯺�</T>
//
// @history 100318 MAOCY ����
//============================================================
template <typename T, TInt S>
class TStackObjects{
public:
   typedef TInt (*HComparer) (const T&, const T&);
   typedef TStackIteratorC<T> TIteratorC;
protected:
   TInt _count;
#ifdef _MO_DEBUG
   T _items[S];
#else
   TByte _items[sizeof(T) * S];
#endif // _MO_DEBUG
public:
   //------------------------------------------------------------
   // <T>���춨��ջ���󼯺ϡ�</T>
   TStackObjects(){
      _count = 0;
   }
public:
   //------------------------------------------------------------
   // <T>ת��ָ�����͡�</T>
   MO_INLINE operator const T*() const{
      return (T*)_items;
   }
   //------------------------------------------------------------
   // <T>ת��ָ�����͡�</T>
   MO_INLINE operator T*(){
      return (T*)_items;
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE const T& operator[](TInt index) const{
      MO_ASSERT_RANGE(index, 0, S);
      return ((T*)_items)[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE T& operator[](TInt index){
      MO_ASSERT_RANGE(index, 0, S);
      return ((T*)_items)[index];
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty() const{
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsNotEmpty() const{
      return (_count > 0);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�������</T>
   MO_INLINE TBool IsFull() const{
      return (S == _count);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�δ����</T>
   MO_INLINE TBool IsNotFull() const{
      return (_count < S);
   }
   //------------------------------------------------------------
   // <T>�������������</T>
   MO_INLINE TInt Count() const{
      return _count;
   }
   //------------------------------------------------------------
   // <T>�������������</T>
   MO_INLINE static TInt Size(){
      return S;
   }
   //------------------------------------------------------------
   // <T>���ֻ���ڲ�����ָ�롣</T>
   MO_INLINE const T* ItemsC() const{
      return (T*)_items;
   }
   //------------------------------------------------------------
   // <T>����ڲ�����ָ�롣</T>
   MO_INLINE T* Items(){
      return (T*)_items;
   }
   //------------------------------------------------------------
   // <T>���ֻ���ײ����ݡ�</T>
   MO_INLINE const T& FirstC() const{
      MO_ASSERT(_count > 0);
      T* pItems = (T*)_items;
      return pItems[0];
   }
   //------------------------------------------------------------
   // <T>����ײ����ݡ�</T>
   MO_INLINE T& First(){
      MO_ASSERT(_count > 0);
      T* pItems = (T*)_items;
      return pItems[0];
   }
   //------------------------------------------------------------
   // <T>���ֻ��β�����ݡ�</T>
   MO_INLINE const T& LastC() const{
      MO_ASSERT(_count > 0);
      T* pItems = (T*)_items;
      return pItems[_count - 1];
   }
   //------------------------------------------------------------
   // <T>���ֻ��β�����ݡ�</T>
   MO_INLINE T& Last(){
      MO_ASSERT(_count > 0);
      T* pItems = (T*)_items;
      return pItems[_count - 1];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE const T& GetC(TInt index) const{
      MO_ASSERT_RANGE(index, 0, S);
      T* pItems = (T*)_items;
      return pItems[index];
   }
   //------------------------------------------------------------
   // <T>�������λ�õ����ݡ�</T>
   MO_INLINE T& Get(TInt index){
      MO_ASSERT_RANGE(index, 0, S);
      T* pItems = (T*)_items;
      return pItems[index];
   }
   //------------------------------------------------------------
   // <T>���ֻ����������</T>
   MO_INLINE TIteratorC IteratorC(){
      return TIteratorC((T*)_items, _count);
   }
public:
   //------------------------------------------------------------
   // <T>�Ƿ���ȡ�</T>
   MO_INLINE TBool Equals(const T* pItems, TInt count){
      MO_ASSERT(pItems);
      if(_count != count){
         return EFalse;
      }
      return RTypes<T>::Equals((T*)_items, pItems, count);
   }
   //------------------------------------------------------------
   // <T>�������ݵĳ��ȡ�</T>
   MO_INLINE void SetCount(TInt count){
      MO_ASSERT_BETWEEN(count, 0, S);
      _count = count;
   }
   //------------------------------------------------------------
   // <T>�������ݵ�ȷ�����ȡ�</T>
   MO_INLINE void EnsureCount(TInt count){
      MO_ASSERT_BETWEEN(count, 0, S);
      if(count > _count){
         _count = count;
      }
   }
   //------------------------------------------------------------
   // <T>ʹ�����������ڲ������������</T>
   MO_INLINE void Sort(HComparer hComparer){
      RTypes<T>::SortQuick((T*)_items, _count, hComparer);
   }
public:
   //------------------------------------------------------------
   // <T>�����ⲿ���ݡ�</T>
   MO_INLINE void Assign(const T* pItems, TInt count){
      if(NULL != pItems){
         if((_count < 0) || (_count > S) || (count < 0) || (count > S)){
            MO_FATAL("Assign range is invalid. (current=%d, assign=%d, size=%d)", _count, count, S);
         }else{
            MO_LIB_TYPES_COPY(T, (T*)_items, S, pItems, count);
            _count = count;
         }
      }else{
         MO_FATAL("Assign memory is null.");
      }
   }
   //------------------------------------------------------------
   // <T>�����ⲿ���ݡ�</T>
   MO_INLINE void Assign(TStackObjects<T, S>& objects){
      Assign(objects.ItemsC(), objects.Count());
   }
   //------------------------------------------------------------
   // <T>׷���ⲿ���ݵ�β����</T>
   MO_INLINE void Append(const T* pItems, TInt count){
      if(NULL != pItems){
         if((_count < 0) || (_count > S) || (count < 0) || (_count + count > S)){
            MO_FATAL("Append range is invalid. (current=%d, assign=%d, size=%d)", _count, count, S);
         }else{
            T* pTarget = (T*)_items;
            MO_LIB_TYPES_COPY(T, pTarget + _count, S - _count, pItems, count);
            _count += count;
         }
      }else{
         MO_FATAL("Append memory is null.");
      }
   }
   //------------------------------------------------------------
   // <T>׷���ⲿ���ݵ�β����</T>
   MO_INLINE void Append(TStackObjects<T, S>& objects){
      Append(objects.ItemsC(), objects.Count());
   }
   //------------------------------------------------------------
   // <T>�ռ�һ�������ݡ�</T>
   MO_INLINE T& Alloc(){
      T* pItems = (T*)_items;
      if((_count < 0) || (_count >= S)){
         T& value = pItems[S - 1];
         MO_FATAL("Alloc memory full. (count=%d, size=%d)", _count, S);
         return value;
      }else{
         T& value = pItems[_count++];
         MO_LIB_TYPE_CLEAR(T, &value);
         return value;
      }
   }
   //------------------------------------------------------------
   // <T>�ռ�һ��ָ������λ�õĿ����ݡ�</T>
   MO_INLINE T& Alloc(TInt index){
      T* pItems = (T*)_items;
      if((_count < 0) || (_count > S) || (index < 0) || (index >= S)){
         T& value = pItems[S - 1];
         MO_FATAL("Alloc index memory invalid. (index=%d, count=%d, size=%d)", index, _count, S);
         return value;
      }else{
         T& value = pItems[index++];
         MO_LIB_TYPE_CLEAR(T, &value);
         if(index > _count){
            _count = index;
         }
         return value;
      }
   }
   //------------------------------------------------------------
   // <T>����һ����ֵ��β����</T>
   MO_INLINE void Push(T& value){
      if((_count < 0) || (_count >= S)){
         MO_FATAL("Push memory full. (count=%d, size=%d)", _count, S);
      }else{
         T* pItems = (T*)_items;
         MO_LIB_TYPE_COPY(T, pItems + _count, &value);
         _count++;
      }
   }
   //------------------------------------------------------------
   // <T>ɾ��һ��ָ������λ�õ����ݡ�</T>
   MO_INLINE TBool Delete(TInt index, T* pValue = NULL){
      // ������
      if((_count < 0) || (_count > S) || (index < 0) || (index >= _count)){
         MO_FATAL("Delete index is invalid. (index=%d, count=%d, size=%d)", index, _count, S);
         return EFalse;
      }
      // ��������
      T* pItems = (T*)_items;
      if(NULL != pValue){
         MO_LIB_TYPE_COPY(T, pValue, pItems + index);
      }
      // ɾ������
      TInt size = _count - index - 1;
      if(size > 0){
         MO_LIB_TYPES_MOVE(T, pItems + index, size, pItems + index + 1, size);
      }
      _count--;
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>ɾ���ײ����ݡ�</T>
   MO_INLINE TBool RemoveFirst(T* pValue = NULL){
      if(_count > 0){
         return Delete(0, pValue);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>ɾ��β�����ݡ�</T>
   MO_INLINE TBool RemoveLast(T* pValue = NULL){
      if(_count > 0){
         return Delete(_count - 1, pValue);
      }
      return EFalse;
   }
   //------------------------------------------------------------
   // <T>����ڲ���</T>
   MO_INLINE void Clear(){
      _count = 0;
   }
   //------------------------------------------------------------
   // <T>�����ڲ���</T>
   MO_INLINE void Reset(){
      _count = 0;
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_TYPE_H__
