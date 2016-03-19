#ifndef __MO_CM_STRING8_H__
#define __MO_CM_STRING8_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_TYPE_H__
#include "MoCmType.h"
#endif // __MO_CM_TYPE_H__

#ifndef __MO_CM_ARRAY_H__
#include "MoCmArray.h"
#endif // __MO_CM_ARRAY_H__

#ifndef __MO_CM_VECTOR_H__
#include "MoCmVector.h"
#endif // __MO_CM_VECTOR_H__

#ifndef __MO_CM_LIST_H__
#include "MoCmList.h"
#endif // __MO_CM_LIST_H__

MO_NAMESPACE_BEGIN

//============================================================
class IDataInput;
class IDataOutput;

//============================================================
// <T>ANSI�ַ���ָ�롣</T>
//============================================================
class TString8PtrC : public TChar8PtrC{
public:
   //------------------------------------------------------------
   // <T>������ָ�빹������</T>
   TString8PtrC(TChar8C* pMemory){
      Assign(pMemory);
   }
   //------------------------------------------------------------
   // <T>������ָ��ͳ��ȹ�������</T>
   TString8PtrC(TChar8C* pMemory, TInt length){
      Set(pMemory, length);
   }
   //------------------------------------------------------------
   // <T>������ָ����󹹽�����</T>
   TString8PtrC(const TString8PtrC& ptr){
      Set(ptr);
   }
public:
   //------------------------------------------------------------
   // <T>����ָ�븳ֵ������</T>
   void operator=(TChar8C* pMemory){
      Assign(pMemory);
   }
public:
   //------------------------------------------------------------
   // <T>����ָ�븴�Ʋ�����</T>
   void Assign(TChar8C* pMemory){
      TInt length = RChar8s::Length(pMemory);
      Set(pMemory, length);
   }
};

//============================================================
// <T>ֻ��ANSI�ַ�����</T>
//============================================================
class MO_CM_DECLARE MString8 : public MArray<TChar8>{
public:
   //------------------------------------------------------------
   // <T>��ǰ�ַ�����׷��һ���ַ�����</T>
   MO_INLINE void operator+=(TChar8C* pValue){
      Append(pValue);
   }
 public:
   TChar8* MemoryZ();
   TString8PtrC PtrZ();
 public:
   TString8PtrC StrC() const;
   TString8PtrC LeftStrC(TInt length) const;
   TString8PtrC MidStrC(TInt offset) const;
   TString8PtrC MidStrC(TInt offset, TInt length) const;
   TString8PtrC RightStrC(TInt length) const;
   TString8PtrC SubStrC(TInt begin, TInt end) const;
   TString8PtrC TrimLeftStrC() const;
   TString8PtrC TrimRightStrC() const;
   TString8PtrC TrimStrC() const;
public:
   TBool Equals(TChar8C* pValue) const;
   TBool EqualsIgnoreCase(TChar8C* pValue) const;
   TBool EqualsIgnoreCase(const TString8PtrC& value) const;
   TBool StartsWith(TChar8C* pValue) const;
   TBool EndsWith(TChar8C* pValue) const;
   TInt CompareIgnoreCase(TChar8C* pValue) const;
   TInt CompareIgnoreCase(const TString8PtrC& value) const;
   THashCode HashCode() const;
   TInt Find(TChar8C* pValue);
   TInt Find(TChar8C* pValue, TInt offset);
   TInt LastFind(TChar8C* pValue);
public:
   TBool Assign(TChar8C* pValue, TInt length = -1);
   TBool Assign(const TPtrC<TChar8>& ptr);
   TBool Assign(const MString8& value);
   TBool AssignPointer(const MString8* pValue);
   TResult AssignFormat(TChar8C* pFormat, ...);
   TResult AssignFormatParameters(TChar8C* pFormat, va_list& params);
   TBool Append(TChar8 value);
   TBool Append(TChar8C* pValues, TInt length = -1);
   TBool Append(const TPtrC<TChar8>& ptr);
   TBool Append(const MString8& value);
   TBool AppendInt(TInt value);
   TBool AppendRepeat(TChar8C* pValue, TInt count);
   TResult AppendFormat(TChar8C* pFormat, ...);
   TResult AppendFormatParameters(TChar8C* pFormat, va_list& params);
   void AppendLine();
   void AppendLine(TChar8 value);
   void AppendLine(TChar8C* pValues, TInt length = -1);
   TResult AppendLineFormat(TChar8C* pFormat, ...);
   TResult AppendLineFormatParameters(TChar8C* pFormat, va_list& params);
public:
   void Assign8(TChar8C* pValue);
   void Assign16(TChar16C* pValue);
   void Assign32(TChar32C* pValue);
public:
   void ToLower();
   void ToUpper();
   void PadLeft(TChar8 pad, TInt length);
   void PadRight(TChar8 pad, TInt length);
   TInt Replace(TChar8 source, TChar8 target);
public:
   TInt ToInt();
   TUint ToUint();
   TInt64 ToInt64();
   TUint64 ToUint64();
   TFloat ToFloat();
   TDouble ToDouble();
   void SetInt(TInt value);
   void SetUint(TUint value);
   void SetInt64(TInt64 value);
   void SetUint64(TUint64 value);
   void SetFloat(TFloat value);
   void SetDouble(TDouble value);
public:
   void Serialize(IDataOutput* pOutput);
   void Unserialize(IDataInput* pInput);
   void UnserializeAutomatic(IDataInput* pInput);
public:
   void SetLength(TInt length);
   void Fix();
   void Clear();
};

//============================================================
// <T>�ַ������á�</T>
//============================================================
class MO_CM_DECLARE TString8Refer : public MString8{
public:
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   TString8Refer(TChar8C* pValue){
      MO_ASSERT(pValue);
      _pMemory = MO_CAST_CONST(pValue, TChar8*);
      _length = RChar8s::Length(pValue);
      _capacity = _length;
   }
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   TString8Refer(TChar8* pValue){
      MO_ASSERT(pValue);
      _pMemory = pValue;
      _length = RChar8s::Length(pValue);
      _capacity = _length;
   }
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   TString8Refer(TChar8* pValue, TInt size){
      MO_ASSERT(pValue);
      _length = 0;
      _pMemory = pValue;
      _capacity = size;
   }
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   TString8Refer(const TChar8PtrC& ptr){
      _length = ptr.Length();
      _pMemory = MO_CAST_CONST(ptr.MemoryC(), TChar8*);
      _capacity = _length;
   }
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   MO_ABSTRACT ~TString8Refer(){
   }
protected:
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force){
      MO_ASSERT(size <= _capacity);
   }
public:
   //------------------------------------------------------------
   // <T>�����������ݵ��ڲ���</T>
   MO_INLINE void operator=(TChar8C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>�����������ݵ��ڲ���</T>
   MO_INLINE void operator=(const TString8PtrC& value){
      Assign(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>�����������ݵ��ڲ���</T>
   MO_INLINE void operator=(const TString8Refer& value){
      Assign(value.MemoryC(), value.Length());
   }
};

//============================================================
// <T>�ַ�����</T>
//============================================================
class MO_CM_DECLARE TString8 : public MString8{
public:
   TString8();
   TString8(TChar8C* pValue, TInt length = -1);
   TString8(const TString8PtrC& ptr);
   TString8(const MString8& value);
   TString8(const TString8& value);
   MO_ABSTRACT ~TString8();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar8C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ���ָ�����</T>
   MO_INLINE void operator=(const TString8PtrC& value){
      Assign(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const MString8& value){
      Assign(value.MemoryC(), value.Length());
   }
public:
   void Append8(TChar8C* pValue);
   void Append16(TChar16C* pValue);
   void Append32(TChar32C* pValue);
};

//============================================================
// <T>�ַ�����</T>
//============================================================
class MO_CM_DECLARE FString8 :
      public FObject,
      public MString8{
protected:
   TBool _buffered;
public:
   FString8();
   FString8(TChar8C* pValue, TInt length = -1);
   FString8(const TString8PtrC& value);
   FString8(const MString8& value);
   MO_ABSTRACT ~FString8();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar8C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const TString8PtrC& value){
      Assign(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const MString8& value){
      Assign(value.MemoryC(), value.Length());
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE TVectorIteratorC<FString8*> TString8sIteratorC;
typedef MO_CM_DECLARE FVector<FString8*> FString8Vector;

//============================================================
// <T>����ANSI�ַ��������ࡣ</T>
//
// @tools
// @author maocy
// @version 1.0.1
//============================================================
template <TInt S>
class TFixString8 : public MString8{
protected:
   TChar8 _memory[S];
public:
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   TFixString8(){
      InnerInitialize();
   }
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   TFixString8(TChar8C* pValue, TInt length = -1){
      InnerInitialize();
      Assign(pValue, length);
   }
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   TFixString8(const TString8PtrC& ptr){
      InnerInitialize();
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   TFixString8(const TFixString8<S>& value){
      InnerInitialize();
      Assign(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   MO_ABSTRACT ~TFixString8(){
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(){
      MO_ASSERT(S > 0);
      _pMemory = _memory;
      _capacity = S;
      _memory[0] = 0;
   }
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force){
      MO_ASSERT(size <= S);
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar8C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<TChar8>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const TFixString8<S>& value){
      Assign(value.MemoryC(), value.Length());
   }
public:
   //------------------------------------------------------------
   // <T>������ɳ��ȡ�</T>
   static MO_INLINE TInt Size(){
      return S;
   }
};

//============================================================
// <T>�����ַ�����</T>
//============================================================
#define MO_BCD_TFIXSTRING8(C, P) \
class MO_CM_DECLARE C : public P{ \
public: \
   C(){ \
   } \
   C(const C& value) : P(value){ \
   } \
   C(TChar8C* pValue, TInt length=-1) : P(pValue, length){ \
   } \
   C(const TString8PtrC& ptr) : P(ptr){ \
   } \
   MO_ABSTRACT ~C(){ \
   } \
public: \
   MO_INLINE void operator=(TChar8C* pValue){ \
      Assign(pValue); \
   } \
   MO_INLINE void operator=(const C& value){ \
      Assign(value.MemoryC(), value.Length()); \
   } \
   MO_INLINE void operator=(const TString8PtrC& value){ \
      Assign(value.MemoryC(), value.Length()); \
   } \
public: \
   static MO_INLINE TInt Size(){ \
      return P::Size(); \
   } \
};
//------------------------------------------------------------
MO_BCD_TFIXSTRING8(TFsNumber8,   TFixString8<MO_FS_NUMBER_LENGTH>);
MO_BCD_TFIXSTRING8(TFsTimeTick8, TFixString8<MO_FS_TIMETICK_LENGTH>);
MO_BCD_TFIXSTRING8(TFsCode8,     TFixString8<MO_FS_CODE_LENGTH>);
MO_BCD_TFIXSTRING8(TFsName8,     TFixString8<MO_FS_NAME_LENGTH>);
MO_BCD_TFIXSTRING8(TFsLabel8,    TFixString8<MO_FS_LABEL_LENGTH>);
MO_BCD_TFIXSTRING8(TFsText8,     TFixString8<MO_FS_TEXT_LENGTH>);
MO_BCD_TFIXSTRING8(TFsCommand8,  TFixString8<MO_FS_COMMAND_LENGTH>);
MO_BCD_TFIXSTRING8(TFsNote8,     TFixString8<MO_FS_NOTE_LENGTH>);
MO_BCD_TFIXSTRING8(TFsLogger8,   TFixString8<MO_FS_LOGGER_LENGTH>);
MO_BCD_TFIXSTRING8(TFsDump8,     TFixString8<MO_FS_DUMP_LENGTH>);
MO_BCD_TFIXSTRING8(TFsSql8,      TFixString8<MO_FS_SQL_LENGTH>);
MO_BCD_TFIXSTRING8(TFsTrack8,    TFixString8<MO_FS_TRACK_LENGTH>);
MO_BCD_TFIXSTRING8(TFsFileName8, TFixString8<MO_FS_FILENAME_LENGTH>);
MO_BCD_TFIXSTRING8(TFsPath8,     TFixString8<MO_FS_PATH_LENGTH>);

//============================================================
// <T>�ַ������塣</T>
//============================================================
class MO_CM_DECLARE TStringBuffer8 : public MString8{
public:
   TStringBuffer8();
   TStringBuffer8(TChar8C* pValue, TInt length = -1);
   TStringBuffer8(const TString8PtrC& ptr);
   TStringBuffer8(const MString8& value);
   MO_ABSTRACT ~TStringBuffer8();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar8C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ���ָ�����</T>
   MO_INLINE void operator=(const TString8PtrC& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const MString8& value){
      Assign(value.MemoryC(), value.Length());
   }
};

//============================================================
// <T>�ַ������塣</T>
//============================================================
class MO_CM_DECLARE FStringBuffer8 :
      public FObject,
      public MString8{
public:
   FStringBuffer8();
   FStringBuffer8(TChar8C* pValue, TInt length = -1);
   FStringBuffer8(const TString8PtrC& ptr);
   FStringBuffer8(const MString8& value);
   MO_ABSTRACT ~FStringBuffer8();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar8C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const TString8PtrC& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const MString8& value){
      Assign(value.MemoryC(), value.Length());
   }
};

//============================================================
// <T>�ַ����ָ�����</T>
//============================================================
template<TInt S>
class TFixStringToken8{
protected:
   TInt _count;
   TInt _results[S];
   TChar8 _memory[S];
public:
   //------------------------------------------------------------
   // <T>�����ַ����ָ�����</T>
   TFixStringToken8(){
      _count = 0;
   }
   //------------------------------------------------------------
   // <T>�����ַ����ָ�����</T>
   TFixStringToken8(TChar8C* pSource, TChar8 splitter){
      _count = 0;
      Split(pSource, splitter);
   }
   //------------------------------------------------------------
   // <T>�����ַ����ָ�����</T>
   TFixStringToken8(TChar8C* pSource, TChar8C* pSplitter){
      _count = 0;
      Split(pSource, pSplitter);
   }
public:
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   TCharC* Get(TInt n){
      return &_memory[_results[n]];
   }
public:
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   void Split(TChar8C* pSource, TChar8 splitter){
      TString8Refer value(pSource);
      TInt begin = 0;
      TInt length = value.Length();
      TInt count = 0;
      while(begin < length){
         TInt index = value.IndexOf(splitter, begin);
         if(ENotFound == index){
            break;
         }
         _results[_count++] = begin;
         for(TInt n = begin; n < index; n++){
            _memory[count++] = pSource[n];
         }
         _memory[count++] = '\0';
         begin = index + 1;
      }
      _results[_count++] = begin;
      for(TInt n = begin; n < length; n++){
         _memory[count++] = pSource[n];
      }
      _memory[count++] = '\0';
      MO_ASSERT(count <= MO_FS_TEXT_LENGTH);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   void Split(TChar8C* pSource, TChar8C* pSplitter){
      TInt lengthSource = RChar8s::Length(pSource);
      TInt lengthSplitter = RChar8s::Length(pSplitter);
      TInt begin = 0;
      TInt index = 0;
      TInt count = 0;
      for(TInt n = 0; n < lengthSource; n++){
         if(pSource[n] == pSplitter[0]){
            TBool result = ETrue;
            index = n;
            for(TInt m = 1; m < lengthSplitter; m++){
               if(pSource[n + m] != pSplitter[m]){
                  result = EFalse;
                  break;
               }
               result = ETrue;
            }
            if(ETrue == result){
               _results[_count++] = begin;
               for(TInt n = begin; n < index; n++){
                  _memory[count++] = pSource[n];
               }
               _memory[count++] = '\0';
               begin = index + lengthSplitter;
            }
         }
      }
      _results[_count++] = begin;
      for(TInt n = begin; n < lengthSource; n++){
         _memory[count++] = pSource[n];
      }
      _memory[count++] = '\0';
      MO_ASSERT(count <= MO_FS_TEXT_LENGTH);
   }
};
//------------------------------------------------------------
typedef TFixStringToken8<MO_FS_TEXT_LENGTH> TFsStringToken8;

//============================================================
// <T>�ַ������ϡ�</T>
//============================================================
class MO_CM_DECLARE MString8s{
protected:
   TInt _count;
   FString8Vector* _pStrings;
public:
   MString8s();
   MO_ABSTRACT ~MString8s();
public:
   TChar8C* operator[](TInt index) const;
   void operator +=(TChar8C* pValue);
   void operator +=(const MString8s& strings);
   void operator -=(TChar8C* pValue);
   void operator -=(const MString8s& strings);
public:
   TBool IsEmpty() const;
   TInt Count() const;
   TBool Contains(TChar8C* pValue) const;
public:
   TString8sIteratorC IteratorC() const;
   TChar8C* First() const;
   TChar8C* Last() const;
   TChar8C* Get(TInt index) const;
   TInt IndexOf(TChar8C* pValue) const;
   TString8 Join(TChar8 splitter);
   TString8 Join(TChar8C* splitter);
   TInt Pack(TChar8* pPack, TInt length);
   TString8 Pack();
public:
   void EnsureSize(TInt size);
   void Set(TInt index, TChar8C* pValue);
   void Assign(const MString8s& strings);
   void Append(const MString8s& strings);
   void AppendSplit(TChar8C* pValue, TChar8 splitter);
   void AppendSplit(TChar8C* pValue, TChar8C* pSplitter);
   void Push(TChar8C* pValue);
   void Push(const TString8PtrC& value);
   void Remove(TChar8C* pValue);
   void Remove(const MString8s& strings);
   void Delete(TInt index);
   void Split(TChar8C* pValue, TChar8 splitter);
   void Split(TChar8C* pValue, TChar8C* pSplitter);
   void Unpack(TChar8C* pPack);
   void Clear();
};

//============================================================
class MO_CM_DECLARE TString8s : public MString8s{
public:
   //------------------------------------------------------------
   TString8s(){
   }
   //------------------------------------------------------------
   TString8s(const MString8s& strings){
      Append(strings);
   }
   //------------------------------------------------------------
   TString8s(const TString8s& strings){
      Append(strings);
   }
   //------------------------------------------------------------
   MO_ABSTRACT ~TString8s(){
   }
public:
   //------------------------------------------------------------
   void operator=(const MString8s& strings){
      Assign(strings);
   }
   //------------------------------------------------------------
   void operator=(const TString8s& strings){
      Assign(strings);
   }
};

//============================================================
class MO_CM_DECLARE FString8s :
      public FObject,
      public MString8s{
public:
   //------------------------------------------------------------
   FString8s(){
   }
   //------------------------------------------------------------
   FString8s(const MString8s& strings){
      Append(strings);
   }
   //------------------------------------------------------------
   FString8s(const FString8s& strings){
      Append(strings);
   }
   //------------------------------------------------------------
   MO_ABSTRACT ~FString8s(){
   }
public:
   //------------------------------------------------------------
   void operator=(const MString8s& strings){
      Assign(strings);
   }
   //------------------------------------------------------------
   void operator=(const FString8s& strings){
      Assign(strings);
   }
};

//============================================================
// <T>ֻ�������������</T>
//
// @tool
//============================================================
class MO_CM_DECLARE MProperties8IteratorC{
public:
   TInt _index;
   TInt _count;
   FString8s* _pNames;
   FString8s* _pValues;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   MO_INLINE MProperties8IteratorC(){
   }
   //------------------------------------------------------------
   // ����ֻ��������
   MO_INLINE MProperties8IteratorC(const MProperties8IteratorC& iterator){
   }
   //------------------------------------------------------------
   // ����ֻ��������
   MO_INLINE MProperties8IteratorC(TInt count, FString8s* pNames, FString8s* pValues){
   }
public:
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   //inline const FString& operator *() const{
   //}
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   //inline const FString* operator->() const{
   //}
public:
   //------------------------------------------------------------
   // <T>��ǰ�ڵ��Ƿ������ݡ�</T>
   MO_INLINE TBool IsEmpty(){
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasNext(){
      return ETrue;
   }
   //------------------------------------------------------------
   //<T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Next(){
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ������һ��λ�á�</T>
   MO_INLINE TBool HasPrior(){
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�ƶ�����һ��λ�á�</T>
   MO_INLINE TBool Prior(){
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void Reset(){
   }
public:
   //------------------------------------------------------------
   // <T>�ж������Ƿ���ͬ��</T>
   MO_INLINE TBool IsName(TCharC* pName) const{
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>�ж������Ƿ���ͬ��</T>
   MO_INLINE TBool IsValue(TCharC* pValue) const{
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ơ�</T>
   MO_INLINE TCharC* Name() const{
      return NULL;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰλ�õ��������ݡ�</T>
   MO_INLINE TCharC* Value() const{
      return NULL;
   }
};

//============================================================
// <T>��д�����������</T>
//
// @tool
//============================================================
class MO_CM_DECLARE MProperties8Iterator : public MProperties8IteratorC{
public:
   //------------------------------------------------------------
   // �������������
   MProperties8Iterator(){
   }
   //------------------------------------------------------------
   // �������������
   MProperties8Iterator(const MProperties8IteratorC& iterator){
   }
public:
   //------------------------------------------------------------
   // ���õ�ǰλ�õ���������
   MO_INLINE void SetName(TCharC* pName) const{
   }
   //------------------------------------------------------------
   // ���õ�ǰλ�õ���������
   MO_INLINE void SetValue(TCharC* pValue) const{
   }
};

//============================================================
// <T>���Լ��ϣ���ֵ�����ݿ����ظ��ļ��ϣ���</T>
//
// @manager
// @history 091207 MAOCY ����
//============================================================
class MO_CM_DECLARE MProperties8{
protected:
   TInt _count;
   FString8s* _pNames;
   FString8s* _pValues;
public:
   MProperties8();
   MO_ABSTRACT ~MProperties8();
public:
   TChar8C* operator[](TChar8C* pName);
public:
   TBool IsEmpty() const;
   TInt Count() const;
   TBool Contains(TChar8C* pName) const;
   TBool ContainsValue(TChar8C* pValue) const;
   FString8s* Names();
   FString8s* Values();
public:
   TChar8C* Name(TInt index) const;
   void SetName(TInt index, TChar8C* pName) const;
   TChar8C* Value(TInt index) const;
   void SetValue(TInt index, TChar8C* pValue) const;
   TChar8C* Get(TChar8C* pName) const;
   TChar8C* Find(TChar8C* pName) const;
   TChar8C* FindNvl(TChar8C* pName, TChar8C* pDefault) const;
   TChar8C* Search(TChar8C* pValue) const;
   void Join(FString8* pValue, TChar8 nameSpliter, TChar8 valueSpliter);
   void Join(FString8* pValue, TChar8C* pNameSpliter, TChar8C* valueSpliter);
   TInt Pack(TChar8* pPack, TInt length);
   // TAttributesIteratorC IteratorC() const;
   TString8 Dump() const;
public:
   void EnsureSize(TInt size);
   void Assign(const MProperties8& properties);
   void Append(const MProperties8& properties);
   void AppendSplit(TChar8C* pValue, TChar8 nameSpliter, TChar8 valueSpliter);
   void AppendSplit(TChar8C* pValue, TChar8C* pNameSpliter, TChar8C* valueSpliter);
   void Add(TChar8C* pName, TChar8C* pValue);
   void Set(TChar8C* pName, TChar8C* pValue);
   void Split(TChar8C* pValue, TChar8 nameSpliter, TChar8 valueSpliter);
   void Split(TChar8C* pValue, TChar8C* pNameSpliter, TChar8C* valueSpliter);
   void Unpack(TChar8C* pPack);
   TString8 Remove(TChar8C* pName);
   void Clear();
};

//============================================================
// <T>���Ա����</T>
//============================================================
class MO_CM_DECLARE TProperties8 : public MProperties8{
public:
   //------------------------------------------------------------
   // <T>�������Ա����</T>
   TProperties8(){
   }
   //------------------------------------------------------------
   // <T>�������Ա����</T>
   TProperties8(TInt capacity){
      EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   TProperties8(const MProperties8& properties){
      Append(properties);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   TProperties8(const TProperties8& properties){
      Append(properties);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   MO_ABSTRACT ~TProperties8(){
   }
};

//============================================================
// <T>���Ա����</T>
//============================================================
class MO_CM_DECLARE FProperties8 :
      public FObject,
      public MProperties8{
public:
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FProperties8(){
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FProperties8(TInt capacity){
      EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FProperties8(const MProperties8& properties){
      Append(properties);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FProperties8(const FProperties8& properties){
      Append(properties);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   MO_ABSTRACT ~FProperties8(){
   }
};

//============================================================
// <T>ANSI�ַ��������ࡣ</T>
//============================================================
class MO_CM_DECLARE RString8{
public:
   static TChar8C* EmptyPtr;
   static TString8 EmptyString;
public:
   static TInt Length(TChar8C* pValue);
   static TBool Equals(TChar8C* pSource, TChar8C* pTarget);
   static TBool Constains(TChar8C* pSource, TChar8C* pValue);
   static TInt Find(TChar8C* pSource, TChar8C* pValue);
   static THashCode MakeHashCode(TChar8C* pValues);
   static THashCode MakeNocaseHashCode(TChar8C* pValues);
public:
   static TBool AllocCopy(TChar8C* pValues, TChar8** ppTarget);
   static TBool AllocFree(TChar8* pTarget);
   static TInt SafeCopy(TChar8* pTarget, TSize size, TChar8C* pValue);
   static TInt ForceCopy(TChar8* pTarget, TSize size, TChar8C* pValue);
   static TInt ReplaceAll(TChar8* pValues, TChar8* pSource, TChar8* pTarget, TChar8* pBuffer, TInt bufferLength);
public:
   static TInt ConvertToString8(TChar8C* pValue);
   static TInt ConvertToString8(TChar8* pTarget, TInt capacity, TChar8C* pValue);
   static TInt ConvertToString16(TChar8C* pValue);
   static TInt ConvertToString16(TChar16* pTarget, TInt capacity, TChar8C* pValue);
   static TInt ConvertToString32(TChar8C* pValue);
   static TInt ConvertToString32(TChar32* pTarget, TInt capacity, TChar8C* pValue);
};

MO_NAMESPACE_END

#endif // __MO_CM_STRING8_H__
