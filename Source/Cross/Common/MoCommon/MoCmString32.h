#ifndef __MO_CM_STRING32_H__
#define __MO_CM_STRING32_H__

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
class TString32PtrC : public TChar32PtrC{
public:
   //------------------------------------------------------------
   // <T>������ָ�빹������</T>
   TString32PtrC(TChar32C* pMemory){
      Assign(pMemory);
   }
   //------------------------------------------------------------
   // <T>������ָ��ͳ��ȹ�������</T>
   TString32PtrC(TChar32C* pMemory, TInt length){
      Set(pMemory, length);
   }
   //------------------------------------------------------------
   // <T>������ָ����󹹽�����</T>
   TString32PtrC(const TString32PtrC& ptr){
      Set(ptr);
   }
public:
   //------------------------------------------------------------
   // <T>����ָ�븳ֵ������</T>
   void operator=(TChar32C* pMemory){
      Assign(pMemory);
   }
public:
   //------------------------------------------------------------
   // <T>����ָ�븴�Ʋ�����</T>
   void Assign(TChar32C* pMemory){
      TInt length = RChar32s::Length(pMemory);
      Set(pMemory, length);
   }
};

//============================================================
// <T>ֻ��ANSI�ַ�����</T>
//============================================================
class MO_CM_DECLARE MString32 : public MArray<TChar32>{
public:
   //------------------------------------------------------------
   // <T>��ǰ�ַ�����׷��һ���ַ�����</T>
   MO_INLINE void operator+=(TChar32C* pValue){
      Append(pValue);
   }
 public:
   TChar32* MemoryZ();
   TString32PtrC PtrZ();
 public:
   TString32PtrC StrC() const;
   TString32PtrC LeftStrC(TInt length) const;
   TString32PtrC MidStrC(TInt offset) const;
   TString32PtrC MidStrC(TInt offset, TInt length) const;
   TString32PtrC RightStrC(TInt length) const;
   TString32PtrC SubStrC(TInt begin, TInt end) const;
   TString32PtrC TrimLeftStrC() const;
   TString32PtrC TrimRightStrC() const;
   TString32PtrC TrimStrC() const;
public:
   TBool Equals(TChar32C* pValue) const;
   TBool EqualsIgnoreCase(TChar32C* pValue) const;
   TBool EqualsIgnoreCase(const TString32PtrC& value) const;
   TBool StartsWith(TChar32C* pValue) const;
   TBool EndsWith(TChar32C* pValue) const;
   TInt CompareIgnoreCase(TChar32C* pValue) const;
   TInt CompareIgnoreCase(const TString32PtrC& value) const;
   THashCode HashCode() const;
   TInt Find(TChar32C* pValue);
   TInt Find(TChar32C* pValue, TInt offset);
   TInt LastFind(TChar32C* pValue);
public:
   TBool Assign(TChar32C* pValue, TInt length = -1);
   TBool Assign(const TPtrC<TChar32>& ptr);
   TBool Assign(const MString32& value);
   TBool AssignPointer(const MString32* pValue);
   TResult AssignFormat(TChar32C* pFormat, ...);
   TResult AssignFormatParameters(TChar32C* pFormat, va_list& params);
   TBool Append(TChar32 value);
   TBool Append(TChar32C* pValues, TInt length = -1);
   TBool Append(const TPtrC<TChar32>& ptr);
   TBool Append(const MString32& value);
   TBool AppendInt(TInt value);
   TBool AppendRepeat(TChar32C* pValue, TInt count);
   TResult AppendFormat(TChar32C* pFormat, ...);
   TResult AppendFormatParameters(TChar32C* pFormat, va_list& params);
   void AppendLine();
   void AppendLine(TChar32 value);
   void AppendLine(TChar32C* pValues, TInt length = -1);
   TResult AppendLineFormat(TChar32C* pFormat, ...);
   TResult AppendLineFormatParameters(TChar32C* pFormat, va_list& params);
public:
   void Assign8(TChar8C* pValue);
   void Assign16(TChar16C* pValue);
   void Assign32(TChar32C* pValue);
public:
   void ToLower();
   void ToUpper();
   void PadLeft(TChar32 pad, TInt length);
   void PadRight(TChar32 pad, TInt length);
   TInt Replace(TChar32 source, TChar32 target);
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
class MO_CM_DECLARE TString32Refer : public MString32{
public:
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   TString32Refer(TChar32C* pValue){
      MO_ASSERT(pValue);
      _pMemory = MO_CAST_CONST(pValue, TChar32*);
      _length = RChar32s::Length(pValue);
      _capacity = _length;
   }
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   TString32Refer(TChar32* pValue){
      MO_ASSERT(pValue);
      _pMemory = pValue;
      _length = RChar32s::Length(pValue);
      _capacity = _length;
   }
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   TString32Refer(TChar32* pValue, TInt size){
      MO_ASSERT(pValue);
      _length = 0;
      _pMemory = pValue;
      _capacity = size;
   }
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   TString32Refer(const TChar32PtrC& ptr){
      _length = ptr.Length();
      _pMemory = MO_CAST_CONST(ptr.MemoryC(), TChar32*);
      _capacity = _length;
   }
   //------------------------------------------------------------
   // <T>�����ַ������á�</T>
   MO_ABSTRACT ~TString32Refer(){
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
   MO_INLINE void operator=(TChar32C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>�����������ݵ��ڲ���</T>
   MO_INLINE void operator=(const TString32PtrC& value){
      Assign(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>�����������ݵ��ڲ���</T>
   MO_INLINE void operator=(const TString32Refer& value){
      Assign(value.MemoryC(), value.Length());
   }
};

//============================================================
// <T>�ַ�����</T>
//============================================================
class MO_CM_DECLARE TString32 : public MString32{
public:
   TString32();
   TString32(TChar32C* pValue, TInt length = -1);
   TString32(const TString32PtrC& ptr);
   TString32(const MString32& value);
   TString32(const TString32& value);
   MO_ABSTRACT ~TString32();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar32C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ���ָ�����</T>
   MO_INLINE void operator=(const TString32PtrC& value){
      Assign(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const MString32& value){
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
class MO_CM_DECLARE FString32 :
      public FObject,
      public MString32{
protected:
   TBool _buffered;
public:
   FString32();
   FString32(TChar32C* pValue, TInt length = -1);
   FString32(const TString32PtrC& value);
   FString32(const MString32& value);
   MO_ABSTRACT ~FString32();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar32C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const TString32PtrC& value){
      Assign(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const MString32& value){
      Assign(value.MemoryC(), value.Length());
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE TVectorIteratorC<FString32*> TString32sIteratorC;
typedef MO_CM_DECLARE FVector<FString32*> FString32Vector;

//============================================================
// <T>����ANSI�ַ��������ࡣ</T>
//
// @tools
// @author maocy
// @version 1.0.1
//============================================================
template <TInt S>
class TFixString32 : public MString32{
protected:
   TChar32 _memory[S];
public:
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   TFixString32(){
      InnerInitialize();
   }
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   TFixString32(TChar32C* pValue, TInt length = -1){
      InnerInitialize();
      Assign(pValue, length);
   }
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   TFixString32(const TString32PtrC& ptr){
      InnerInitialize();
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   TFixString32(const TFixString32<S>& value){
      InnerInitialize();
      Assign(value.MemoryC(), value.Length());
   }
   //------------------------------------------------------------
   // <T>����һ�������ַ����ࡣ</T>
   MO_ABSTRACT ~TFixString32(){
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
   MO_INLINE void operator=(TChar32C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<TChar32>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const TFixString32<S>& value){
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
#define MO_BCD_TFIXSTRING32(C, P) \
class MO_CM_DECLARE C : public P{ \
public: \
   C(){ \
   } \
   C(const C& value) : P(value){ \
   } \
   C(TChar32C* pValue, TInt length=-1) : P(pValue, length){ \
   } \
   C(const TString32PtrC& ptr) : P(ptr){ \
   } \
   MO_ABSTRACT ~C(){ \
   } \
public: \
   MO_INLINE void operator=(TChar32C* pValue){ \
      Assign(pValue); \
   } \
   MO_INLINE void operator=(const C& value){ \
      Assign(value.MemoryC(), value.Length()); \
   } \
   MO_INLINE void operator=(const TString32PtrC& value){ \
      Assign(value.MemoryC(), value.Length()); \
   } \
public: \
   static MO_INLINE TInt Size(){ \
      return P::Size(); \
   } \
};
//------------------------------------------------------------
MO_BCD_TFIXSTRING32(TFsNumber32,   TFixString32<MO_FS_NUMBER_LENGTH>);
MO_BCD_TFIXSTRING32(TFsTimeTick32, TFixString32<MO_FS_TIMETICK_LENGTH>);
MO_BCD_TFIXSTRING32(TFsCode32,     TFixString32<MO_FS_CODE_LENGTH>);
MO_BCD_TFIXSTRING32(TFsName32,     TFixString32<MO_FS_NAME_LENGTH>);
MO_BCD_TFIXSTRING32(TFsLabel32,    TFixString32<MO_FS_LABEL_LENGTH>);
MO_BCD_TFIXSTRING32(TFsText32,     TFixString32<MO_FS_TEXT_LENGTH>);
MO_BCD_TFIXSTRING32(TFsCommand32,  TFixString32<MO_FS_COMMAND_LENGTH>);
MO_BCD_TFIXSTRING32(TFsNote32,     TFixString32<MO_FS_NOTE_LENGTH>);
MO_BCD_TFIXSTRING32(TFsLogger32,   TFixString32<MO_FS_LOGGER_LENGTH>);
MO_BCD_TFIXSTRING32(TFsDump32,     TFixString32<MO_FS_DUMP_LENGTH>);
MO_BCD_TFIXSTRING32(TFsSql32,      TFixString32<MO_FS_SQL_LENGTH>);
MO_BCD_TFIXSTRING32(TFsTrack32,    TFixString32<MO_FS_TRACK_LENGTH>);
MO_BCD_TFIXSTRING32(TFsFileName32, TFixString32<MO_FS_FILENAME_LENGTH>);
MO_BCD_TFIXSTRING32(TFsPath32,     TFixString32<MO_FS_PATH_LENGTH>);

//============================================================
// <T>�ַ������塣</T>
//============================================================
class MO_CM_DECLARE TStringBuffer32 : public MString32{
public:
   TStringBuffer32();
   TStringBuffer32(TChar32C* pValue, TInt length = -1);
   TStringBuffer32(const TString32PtrC& ptr);
   TStringBuffer32(const MString32& value);
   MO_ABSTRACT ~TStringBuffer32();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar32C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ��ANSI�ַ���ָ�����</T>
   MO_INLINE void operator=(const TString32PtrC& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const MString32& value){
      Assign(value.MemoryC(), value.Length());
   }
};

//============================================================
// <T>�ַ������塣</T>
//============================================================
class MO_CM_DECLARE FStringBuffer32 :
      public FObject,
      public MString32{
public:
   FStringBuffer32();
   FStringBuffer32(TChar32C* pValue, TInt length = -1);
   FStringBuffer32(const TString32PtrC& ptr);
   FStringBuffer32(const MString32& value);
   MO_ABSTRACT ~FStringBuffer32();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TChar32C* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const TString32PtrC& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ���ָ�����</T>
   MO_INLINE void operator=(const MString32& value){
      Assign(value.MemoryC(), value.Length());
   }
};

//============================================================
// <T>�ַ����ָ�����</T>
//============================================================
template<TInt S>
class TFixStringToken32{
protected:
   TInt _count;
   TInt _results[S];
   TChar32 _memory[S];
public:
   //------------------------------------------------------------
   // <T>�����ַ����ָ�����</T>
   TFixStringToken32(){
      _count = 0;
   }
   //------------------------------------------------------------
   // <T>�����ַ����ָ�����</T>
   TFixStringToken32(TChar32C* pSource, TChar32 splitter){
      _count = 0;
      Split(pSource, splitter);
   }
   //------------------------------------------------------------
   // <T>�����ַ����ָ�����</T>
   TFixStringToken32(TChar32C* pSource, TChar32C* pSplitter){
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
   void Split(TChar32C* pSource, TChar32 splitter){
      TString32Refer value(pSource);
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
   void Split(TChar32C* pSource, TChar32C* pSplitter){
      TInt lengthSource = RChar32s::Length(pSource);
      TInt lengthSplitter = RChar32s::Length(pSplitter);
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
typedef TFixStringToken32<MO_FS_TEXT_LENGTH> TFsStringToken32;

//============================================================
// <T>�ַ������ϡ�</T>
//============================================================
class MO_CM_DECLARE MString32s{
protected:
   TInt _count;
   FString32Vector* _pStrings;
public:
   MString32s();
   MO_ABSTRACT ~MString32s();
public:
   TChar32C* operator[](TInt index) const;
   void operator +=(TChar32C* pValue);
   void operator +=(const MString32s& strings);
   void operator -=(TChar32C* pValue);
   void operator -=(const MString32s& strings);
public:
   TBool IsEmpty() const;
   TInt Count() const;
   TBool Contains(TChar32C* pValue) const;
public:
   TString32sIteratorC IteratorC() const;
   TChar32C* First() const;
   TChar32C* Last() const;
   TChar32C* Get(TInt index) const;
   TInt IndexOf(TChar32C* pValue) const;
   TString32 Join(TChar32 splitter);
   TString32 Join(TChar32C* splitter);
   TInt Pack(TChar32* pPack, TInt length);
   TString32 Pack();
public:
   void EnsureSize(TInt size);
   void Set(TInt index, TChar32C* pValue);
   void Assign(const MString32s& strings);
   void Append(const MString32s& strings);
   void AppendSplit(TChar32C* pValue, TChar32 splitter);
   void AppendSplit(TChar32C* pValue, TChar32C* pSplitter);
   void Push(TChar32C* pValue);
   void Push(const TString32PtrC& value);
   void Remove(TChar32C* pValue);
   void Remove(const MString32s& strings);
   void Delete(TInt index);
   void Split(TChar32C* pValue, TChar32 splitter);
   void Split(TChar32C* pValue, TChar32C* pSplitter);
   void Unpack(TChar32C* pPack);
   void Clear();
};

//============================================================
class MO_CM_DECLARE TString32s : public MString32s{
public:
   //------------------------------------------------------------
   TString32s(){
   }
   //------------------------------------------------------------
   TString32s(const MString32s& strings){
      Append(strings);
   }
   //------------------------------------------------------------
   TString32s(const TString32s& strings){
      Append(strings);
   }
   //------------------------------------------------------------
   MO_ABSTRACT ~TString32s(){
   }
public:
   //------------------------------------------------------------
   void operator=(const MString32s& strings){
      Assign(strings);
   }
   //------------------------------------------------------------
   void operator=(const TString32s& strings){
      Assign(strings);
   }
};

//============================================================
class MO_CM_DECLARE FString32s :
      public FObject,
      public MString32s{
public:
   //------------------------------------------------------------
   FString32s(){
   }
   //------------------------------------------------------------
   FString32s(const MString32s& strings){
      Append(strings);
   }
   //------------------------------------------------------------
   FString32s(const FString32s& strings){
      Append(strings);
   }
   //------------------------------------------------------------
   MO_ABSTRACT ~FString32s(){
   }
public:
   //------------------------------------------------------------
   void operator=(const MString32s& strings){
      Assign(strings);
   }
   //------------------------------------------------------------
   void operator=(const FString32s& strings){
      Assign(strings);
   }
};

//============================================================
// <T>ֻ�������������</T>
//
// @tool
//============================================================
class MO_CM_DECLARE MProperties32IteratorC{
public:
   TInt _index;
   TInt _count;
   FString32s* _pNames;
   FString32s* _pValues;
public:
   //------------------------------------------------------------
   // ����ֻ��������
   MO_INLINE MProperties32IteratorC(){
   }
   //------------------------------------------------------------
   // ����ֻ��������
   MO_INLINE MProperties32IteratorC(const MProperties32IteratorC& iterator){
   }
   //------------------------------------------------------------
   // ����ֻ��������
   MO_INLINE MProperties32IteratorC(TInt count, FString32s* pNames, FString32s* pValues){
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
class MO_CM_DECLARE MProperties32Iterator : public MProperties32IteratorC{
public:
   //------------------------------------------------------------
   // �������������
   MProperties32Iterator(){
   }
   //------------------------------------------------------------
   // �������������
   MProperties32Iterator(const MProperties32IteratorC& iterator){
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
class MO_CM_DECLARE MProperties32{
protected:
   TInt _count;
   FString32s* _pNames;
   FString32s* _pValues;
public:
   MProperties32();
   MO_ABSTRACT ~MProperties32();
public:
   TChar32C* operator[](TChar32C* pName);
public:
   TBool IsEmpty() const;
   TInt Count() const;
   TBool Contains(TChar32C* pName) const;
   TBool ContainsValue(TChar32C* pValue) const;
   FString32s* Names();
   FString32s* Values();
public:
   TChar32C* Name(TInt index) const;
   void SetName(TInt index, TChar32C* pName) const;
   TChar32C* Value(TInt index) const;
   void SetValue(TInt index, TChar32C* pValue) const;
   TChar32C* Get(TChar32C* pName) const;
   TChar32C* Find(TChar32C* pName) const;
   TChar32C* FindNvl(TChar32C* pName, TChar32C* pDefault) const;
   TChar32C* Search(TChar32C* pValue) const;
   void Join(FString32* pValue, TChar32 nameSpliter, TChar32 valueSpliter);
   void Join(FString32* pValue, TChar32C* pNameSpliter, TChar32C* valueSpliter);
   TInt Pack(TChar32* pPack, TInt length);
   // TAttributesIteratorC IteratorC() const;
   TString32 Dump() const;
public:
   void EnsureSize(TInt size);
   void Assign(const MProperties32& properties);
   void Append(const MProperties32& properties);
   void AppendSplit(TChar32C* pValue, TChar32 nameSpliter, TChar32 valueSpliter);
   void AppendSplit(TChar32C* pValue, TChar32C* pNameSpliter, TChar32C* valueSpliter);
   void Add(TChar32C* pName, TChar32C* pValue);
   void Set(TChar32C* pName, TChar32C* pValue);
   void Split(TChar32C* pValue, TChar32 nameSpliter, TChar32 valueSpliter);
   void Split(TChar32C* pValue, TChar32C* pNameSpliter, TChar32C* valueSpliter);
   void Unpack(TChar32C* pPack);
   TString32 Remove(TChar32C* pName);
   void Clear();
};

//============================================================
// <T>���Ա����</T>
//============================================================
class MO_CM_DECLARE TProperties32 : public MProperties32{
public:
   //------------------------------------------------------------
   // <T>�������Ա����</T>
   TProperties32(){
   }
   //------------------------------------------------------------
   // <T>�������Ա����</T>
   TProperties32(TInt capacity){
      EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   TProperties32(const MProperties32& properties){
      Append(properties);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   TProperties32(const TProperties32& properties){
      Append(properties);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   MO_ABSTRACT ~TProperties32(){
   }
};

//============================================================
// <T>���Ա����</T>
//============================================================
class MO_CM_DECLARE FProperties32 :
      public FObject,
      public MProperties32{
public:
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FProperties32(){
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FProperties32(TInt capacity){
      EnsureSize(capacity);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FProperties32(const MProperties32& properties){
      Append(properties);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   FProperties32(const FProperties32& properties){
      Append(properties);
   }
   //------------------------------------------------------------
   // <T>�������Ա�</T>
   MO_ABSTRACT ~FProperties32(){
   }
};

//============================================================
// <T>ANSI�ַ��������ࡣ</T>
//============================================================
class MO_CM_DECLARE RString32{
public:
   static TChar32C* EmptyPtr;
   static TString32 EmptyString;
public:
   static TInt Length(TChar32C* pValue);
   static TBool Equals(TChar32C* pSource, TChar32C* pTarget);
   static TBool Constains(TChar32C* pSource, TChar32C* pValue);
   static TInt Find(TChar32C* pSource, TChar32C* pValue);
   static THashCode MakeHashCode(TChar32C* pValues);
   static THashCode MakeNocaseHashCode(TChar32C* pValues);
public:
   static TBool AllocCopy(TChar32C* pValues, TChar32** ppTarget);
   static TBool AllocFree(TChar32* pTarget);
   static TInt SafeCopy(TChar32* pTarget, TSize size, TChar32C* pValue);
   static TInt ForceCopy(TChar32* pTarget, TSize size, TChar32C* pValue);
   static TInt ReplaceAll(TChar32* pValues, TChar32* pSource, TChar32* pTarget, TChar32* pBuffer, TInt bufferLength);
public:
   static TInt ConvertToString8(TChar32C* pValue);
   static TInt ConvertToString8(TChar8* pTarget, TInt capacity, TChar32C* pValue);
   static TInt ConvertToString16(TChar32C* pValue);
   static TInt ConvertToString16(TChar16* pTarget, TInt capacity, TChar32C* pValue);
   static TInt ConvertToString32(TChar32C* pValue);
   static TInt ConvertToString32(TChar32* pTarget, TInt capacity, TChar32C* pValue);
};

MO_NAMESPACE_END

#endif // __MO_CM_STRING32_H__
