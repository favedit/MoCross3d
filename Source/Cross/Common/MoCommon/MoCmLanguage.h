#ifndef __MO_CM_LANGUAGE_H__
#define __MO_CM_LANGUAGE_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

#ifndef __MO_CM_PROPERTY_H__
#include "MoCmProperty.h"
#endif // __MO_CM_PROPERTY_H__

#define MO_DATE_MICROSECONDS_PER_DAY    86400000000LL
#define MO_DATE_MICROSECONDS_PER_HOUR    3600000000LL
#define MO_DATE_MICROSECONDS_PER_MINUTE    60000000L
#define MO_DATE_MICROSECONDS_PER_SECONDE    1000000L
#define MO_DATE_MILLISECONDS_PER_DAY       86400000
#define MO_DATE_MILLISECONDS_PER_HOUR       3600000
#define MO_DATE_MILLISECONDS_PER_MINUTE       60000
#define MO_DATE_MILLISECONDS_PER_SECONDE       1000
#define MO_DATE_SECONDS_PER_DAY               86400
#define MO_DATE_SECONDS_PER_HOUR               3600
#define MO_DATE_SECONDS_PER_MINUTE               60

#define MO_PROPERTY_MAXCNT                     1024

MO_NAMESPACE_BEGIN

//============================================================
// <T>���󼯺ϡ�</T>
//============================================================
template <typename T>
class FObjects : public FVector<T>{
public:
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FObjects(){
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FObjects(TInt capacity){
      this->InnerResize(capacity, EFalse, EFalse, EFalse);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FObjects(const T* pValues, TInt count){
      this->Assign(pValues, count);
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FObjects(const TPtrC<T>& ptr){
      this->Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FObjects(const MVector<T>& values){
      this->Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����䳤���顣</T>
   FObjects(const FObjects<T>& values){
      this->Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>�����䳤���顣</T>
   MO_ABSTRACT ~FObjects(){
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ������ָ�롣</T>
   MO_INLINE void operator=(const TPtrC<T>& ptr){
      this->Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const MVector<T>& values){
      this->Assign(values.MemoryC(), values.Count());
   }
   //------------------------------------------------------------
   // <T>����ǰ��������Ϊָ���������顣</T>
   MO_INLINE void operator=(const FVector<T>& values){
      this->Assign(values.MemoryC(), values.Count());
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FObject*> FObjectList;
typedef MO_CM_DECLARE FVector<FObject*> FObjectVector;
typedef MO_CM_DECLARE FSet<TUint32, FObject*> FObjectSet;

//============================================================
// <T>���������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RInt : public RType<TInt>{
public:
   static TBool IsInteger(TCharC* pValue);
public:
   static TInt InRange(TInt value, TInt min, TInt max);
   static TInt InBetween(TInt value, TInt min, TInt max);
public:
   static TInt Parse8(TChar8C* pValue);
   static TInt Parse16(TChar16C* pValue);
   static TInt Parse32(TChar32C* pValue);
   static TInt Parse(TCharC* pValue);
   static TInt ParseNvl(TCharC* pValue);
public:
   static TChar8C* ToString8(TInt value, TChar8* pBuffer, TInt capacity);
   static TChar16C* ToString16(TInt value, TChar16* pBuffer, TInt capacity);
   static TChar32C* ToString32(TInt value, TChar32* pBuffer, TInt capacity);
   static TCharC* ToString(TInt value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TInt value, TChar* pBuffer, TInt capacity);
public:
   static TCharC* FormatCapacity(TInt64 size, TChar* pBuffer, TInt capacity);
   static TInt CountDigit(TInt value);
};

//============================================================
// <T>�޷������������������ࡣ</T>
//============================================================
class MO_CM_DECLARE RUint : public RType<TUint>{
public:
   static TUint InRange(TUint value, TUint min, TUint max);
   static TUint InBetween(TUint value, TUint min, TUint max);
public:
   static TUint Parse8(TChar8C* pValue);
   static TUint Parse16(TChar16C* pValue);
   static TUint Parse32(TChar32C* pValue);
   static TUint Parse(TCharC* pValue);
   static TUint ParseNvl(TCharC* pValue);
   static TUint ParseHex(TCharC* pValue);
   static TUint ParseHexNvl(TCharC* pValue);
public:
   static TChar8C* ToString8(TUint value, TChar8* pBuffer, TInt capacity);
   static TChar16C* ToString16(TUint value, TChar16* pBuffer, TInt capacity);
   static TChar32C* ToString32(TUint value, TChar32* pBuffer, TInt capacity);
   static TCharC* ToString(TUint value, TChar* pBuffer, TInt capacity);
   static TCharC* ToHexString(TUint value, TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>ʱ��β����ࡣ</T>
//============================================================
class MO_CM_DECLARE RTimeSpan{
public:
   //------------------------------------------------------------
   // <T>��ü����</T>
   static MO_INLINE TInt CalculateTick(TTimeTick beginTick, TTimeTick endTick){
      return (TInt)(endTick - beginTick);
   }
   //------------------------------------------------------------
   // <T>��ü���롣</T>
   static MO_INLINE TInt CalculateSecond(TTimeTick beginTick, TTimeTick endTick){
      return (TInt)((endTick - beginTick) / 1000000LL);
   }
   //------------------------------------------------------------
   // <T>��ü���롣</T>
   static MO_INLINE TFloat CalculateFloatSecond(TTimeTick beginTick, TTimeTick endTick){
      return (TFloat)(endTick - beginTick) / 1000000.0f;
   }
};

//============================================================
// <T>ʱ�����ڽṹ��</T>
//============================================================
struct SDateTime{
   TInt second;			/* Seconds.	[0-60] (1 leap second) */
   TInt minute;			/* Minutes.	[0-59] */
   TInt hour;			/* Hours.	[0-23] */
   TInt day;			/* Day.		[1-31] */
   TInt month;			/* Month.	[0-11] */
   TInt year;			/* Year	- 1900.  */
   TInt dayWeek;		/* Day of week.	[0-6] */
   TInt dayYear;		/* Days in year.[0-365]	*/
};

//============================================================
// <T>ʱ�����ڹ����ࡣ</T>
// <P>�������壺</P>
// <P>%Y ��4λ���꣬      0000-9999</P>
// <P>%y ��2λ���꣬      00-99</P>
// <P>%m ��2λ��12�£�    01-12</P>
// <P>%d ��2λ��31�գ�    01-31</P>
// <P>%j ��3λ���ڼ��գ�  001-366</P>
// <P>%H ��2λ��24Сʱ�ƣ�00-23</P>
// <P>%I ��2λ��12Сʱ�ƣ�01-12</P>
// <P>%M ��2λ�����ӣ�    00-59</P>
// <P>%S ��2λ���룬      00-59</P>
// <P>%s ��3λ�����룬    000-999</P>
//
//============================================================
class MO_CM_DECLARE RDateTime{
public:
   static TCharC* DefaultFormat;
   static TCharC* DefaultFormatT;
public:
   static TDateTime Current();
   static TDateTime Parse(TCharC* pValue);
   static TDateTime Parse(TCharC* pValue, TCharC* pFormat);
   static TDateTime ParseNvl(TCharC* pValue);
   static TDateTime ParseNvl(TCharC* pValue, TCharC* pFormat);
public:
   static TCharC* ToString(TChar* pBuffer, TSize length, TDateTime dateTime, TCharC* pFormat);
   static TUint32 To32(TDateTime dateTime);
   static TUint64 To64(TUint32 dateTime);
public:
   static void Split(TDateTime current, SDateTime& dateTime);
   static TDateTime Mktime(SDateTime& dateTime);
	static TBool IsTheNextDay( TDateTime dayEarly, TDateTime dayLate );
   static TInt GetNumberOfWeek(SDateTime& dateTime);
};

//============================================================
// <T>ʱ��̶ȡ�</T>
// <P>����û�����壬������¼ʱ��</P>
//
// @manager
// @source RDateTime.cpp
// @history 100128 MAOCY ����
//============================================================
class MO_CM_DECLARE RTimeTick{
#ifdef _MO_WINDOWS
protected:
   static TUint64 _frequency;
#endif
public:
   static TTimeTick Current();
   static TFsTimeTick Format(TTimeTick tick);
};

//============================================================
// <T>Ψһ����ࡣ</T>
//
// @manager
// @history 110426 MAOCY ����
//============================================================
typedef MO_CM_DECLARE TFixString<40> TGuid;

//============================================================
// <T>Ψһ��Ź����ࡣ</T>
//
// @manager
// @history 110426 MAOCY ����
//============================================================
class MO_CM_DECLARE RGuid{
public:
   static TGuid Generate();
};

//============================================================
// <T>����������ࡣ</T>
//
// @manager
// @history 100304 MAOCY ����
//============================================================
class MO_CM_DECLARE RRandom{
protected:
   static TUint32 _seed;
public:
   static void Initialize();
   static TInt Get();
   static TInt Get(TInt min, TInt max);
   static TInt Generator();
   static TInt Generator(TInt min, TInt max);
   static TFloat GeneratorFloat();
   static TFloat GeneratorFloat(TFloat min, TFloat max);
};

//============================================================
// <T>����ת���������ࡣ</T>
//
// @reference
// @history 110703 MAOCY ����
//============================================================
class MO_CM_DECLARE RTypeConverter{
public:
   static TBool ToBool(EType typeCd, TAny* pValue, TBool& value);
   static TBool ToInt8(EType typeCd, TAny* pValue, TInt8& value);
   static TBool ToInt16(EType typeCd, TAny* pValue, TInt16& value);
   static TBool ToInt32(EType typeCd, TAny* pValue, TInt32& value);
   static TBool ToInt64(EType typeCd, TAny* pValue, TInt64& value);
   static TBool ToUint8(EType typeCd, TAny* pValue, TUint8& value);
   static TBool ToUint16(EType typeCd, TAny* pValue, TUint16& value);
   static TBool ToUint32(EType typeCd, TAny* pValue, TUint32& value);
   static TBool ToUint64(EType typeCd, TAny* pValue, TUint64& value);
   static TBool ToFloat(EType typeCd, TAny* pValue, TFloat& value);
   static TBool ToDouble(EType typeCd, TAny* pValue, TDouble& value);
   static TBool ToDate(EType typeCd, TAny* pValue, TDate& value);
   static TBool ToTime(EType typeCd, TAny* pValue, TTime& value);
   static TBool ToTick(EType typeCd, TAny* pValue, TTick& value);
   static TBool ToSpan(EType typeCd, TAny* pValue, TSpan& value);
   static TBool ToDateTime(EType typeCd, TAny* pValue, TDateTime& value);
   static TBool ToTimeTick(EType typeCd, TAny* pValue, TTimeTick& value);
   static TBool ToTimeSpan(EType typeCd, TAny* pValue, TTimeSpan& value);
   static TBool ToString(EType typeCd, TAny* pValue, TCharC** ppValue);
public:
   static TBool Convert(EType sourceTypeCd, TAny* pSource, EType targetTypeCd, TAny** pTarget);
};

//============================================================
// <T>�̼߳�������</T>
//
// @tool
// @history 091214 MAOCY ����
//============================================================
class MO_CM_DECLARE TThreadCounter{
private:
   TInt _value;
public:
   TThreadCounter();
public:
   TInt Get();
   void Set(TInt value);
   void Increment();
   void Decrement();
};

//============================================================
// <T>����������ࡣ</T>
//============================================================
class MO_CM_DECLARE MNamed{
protected:
   TFsName _name;
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   TCharC* Name() const{
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   void SetName(TCharC* pName){
      _name = pName;
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_LANGUAGE_H__
