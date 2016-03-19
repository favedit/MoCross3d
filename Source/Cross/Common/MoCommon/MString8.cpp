#include "MoCmLanguage.h"
#include "MoCmStream.h"
#include "MoCmString8.h"
#include "MoCmString16.h"
#include "MoCmString32.h"

#define MO_LINE_CHAR '\n'

MO_NAMESPACE_BEGIN

//============================================================
// <T>���һ��ĩβ�ǿյ��ַ�����</T>
//
// @return �ַ���
//============================================================
TChar8* MString8::MemoryZ(){
   // ���ý�����
   EnsureSize(_length + 1);
   _pMemory[_length] = 0;
   // �����ڴ�ָ��
   return _pMemory;
}

//============================================================
// <T>����ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::PtrZ(){
   // ���ý�����
   EnsureSize(_length + 1);
   _pMemory[_length] = 0;
   // �����ڴ�ָ��
   return TString8PtrC(_pMemory, _length);
}

//============================================================
// <T>���ֻ���ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::StrC() const{
   return TString8PtrC(_pMemory, _length);
}

//============================================================
// <T>��õ�ǰ�����е���߲�����������á�</T>
//
// @param length ����
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::LeftStrC(TInt length) const{
   MO_ASSERT_BETWEEN(length, 0, _length);
   return TString8PtrC(_pMemory, length);
}

//============================================================
// <T>��õ�ǰ�����еĿ�ʼ����β�����á�</T>
//
// @param offset λ��
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::MidStrC(TInt offset) const{
   MO_ASSERT_BETWEEN(offset, 0, _length);
   return TString8PtrC(_pMemory + offset, _length - offset);
}

//============================================================
// <T>��õ�ǰ�����еĲ�����������á�</T>
//
// @param offset λ��
// @param length ����
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::MidStrC(TInt offset, TInt length) const{
   MO_ASSERT_BETWEEN(offset, 0, _length);
   MO_ASSERT_BETWEEN(length, 0, _length - offset);
   return TString8PtrC(_pMemory + offset, length);
}

//============================================================
// <T>��õ�ǰ�����е��ұ߲�����������á�</T>
//
// @param length ����
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::RightStrC(TInt length) const{
   MO_ASSERT_BETWEEN(length, 0, _length);
   return TString8PtrC(_pMemory + (_length - length), length);
}

//============================================================
// <T>��õ�ǰ�����еĲ�����������á�</T>
//
// @param begin ��ʼλ��
// @param end ����λ��
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::SubStrC(TInt begin, TInt end) const{
   MO_ASSERT_BETWEEN(begin, 0, _length);
   MO_ASSERT_BETWEEN(end, 0, _length);
   MO_ASSERT(begin <= end);
   return TString8PtrC(_pMemory + begin, end - begin);
}

//============================================================
// <T>ȥ����ߵĿհף������ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::TrimLeftStrC() const{
   TInt position = 0;
   TInt length = Length();
   TChar8* pMemory = _pMemory;
   while((position < length) && (pMemory[position] <= ' ')){
      position++;
   }
   return TString8PtrC(pMemory + position, length - position);
}

//============================================================
// <T>ȥ���ұߵĿհף������ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::TrimRightStrC() const{
   TInt position = Length() - 1;
   TChar8* pMemory = _pMemory;
   while((position >= 0) && (pMemory[position] <= ' ')){
      position--;
   }
   return TString8PtrC(pMemory, position);
}

//============================================================
// <T>ȥ�����ߵĿհף������ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString8PtrC MString8::TrimStrC() const{
   TInt start = 0;
   TInt length = Length();
   TChar8* pMemory = _pMemory;
   // ȥ����߿հ��ַ�
   while((start < length) && (pMemory[start] <= ' ')){
      start++;
   }
   // ȥ���ұ߿հ��ַ�
   TInt end = length - 1;
   while((end >= 0) && (pMemory[end] <= ' ')){
      end--;
   }
   return TString8PtrC(pMemory + start, end - start + 1);
}

//============================================================
// <T>�жϵ�ǰ�ַ�����ָ���ַ����Ƿ���ȡ�</T>
//
// @param pValue ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString8::Equals(TChar8C* pValue) const{
   return RString8::Equals(MemoryC(), pValue);
}

//============================================================
// <T>�������ַ���Сд���жϵ�ǰ�ַ�����ָ���ַ����Ƿ���ȡ�</T>
//
// @param pValue ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString8::EqualsIgnoreCase(TChar8C* pValue) const{
   return (0 == MO_LIB_STRING_COMPARE_IGNORECASE8(MemoryC(), pValue));
}

//============================================================
// <T>�������ַ���Сд���жϵ�ǰ�ַ�����ָ���ַ����Ƿ���ȡ�</T>
//
// @param value ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString8::EqualsIgnoreCase(const TString8PtrC& value) const{
   return (0 == MO_LIB_STRING_COMPARE_IGNORECASE8(MemoryC(), value.MemoryC()));
}

//============================================================
// <T>����ָ�������Ƿ�����ڵ�ǰ����Ŀ�ʼλ�á�</T>
//
// @param pValue ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString8::StartsWith(TChar8C* pValue) const{
   MO_ASSERT(pValue);
   TInt length = MO_LIB_STRING_LENGTH8(pValue);
   return RTypes<TChar8C>::StartsWith(_pMemory, _length, pValue, length);
}

//============================================================
// <T>����ָ�������Ƿ�����ڵ�ǰ����Ľ���λ�á�</T>
//
// @param pValue ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString8::EndsWith(TChar8C* pValue) const{
   MO_ASSERT(pValue);
   TInt length = MO_LIB_STRING_LENGTH8(pValue);
   return RTypes<TChar8C>::EndsWith(_pMemory, _length, pValue, length);
}

//============================================================
// <T>�������ַ���Сд���жϵ�ǰ�ַ�����ָ���ַ����Ĵ�С��</T>
//
// @param pValue ָ���ַ���
// @return <L value='С��0'>��ǰ�ַ���С��ָ���ַ���</L>
//         <L value='����0'>��ǰ�ַ������ָ���ַ���</L>
//         <L value='����0'>��ǰ�ַ�������ָ���ַ���</L>
//============================================================
TInt MString8::CompareIgnoreCase(TChar8C* pValue) const{
   return MO_LIB_STRING_COMPARE_IGNORECASE8(MemoryC(), pValue);
}

//============================================================
// <T>�������ַ���Сд���жϵ�ǰ�ַ�����ָ���ַ����Ĵ�С��</T>
//
// @param value ָ���ַ���
// @return <L value='С��0'>��ǰ�ַ���С��ָ���ַ���</L>
//         <L value='����0'>��ǰ�ַ������ָ���ַ���</L>
//         <L value='����0'>��ǰ�ַ�������ָ���ַ���</L>
//============================================================
TInt MString8::CompareIgnoreCase(const TString8PtrC& value) const{
   return MO_LIB_STRING_COMPARE_IGNORECASE8(MemoryC(), value.MemoryC());
}

//============================================================
// <T>���㵱ǰ�ַ����Ĺ�ϣֵ��</T>
//
// @return ��ϣֵ
//============================================================
THashCode MString8::HashCode() const{
   return RTypes<TChar8>::MakeHashCode(_pMemory, _length);
}

//============================================================
// <T>�ӵ�ǰ�ַ����в���ָ���ַ���������λ�á�</T>
//
// @param pValue �ַ���
// @return ����λ��
//============================================================
TInt MString8::Find(TChar8C* pValue){
   TInt length = MO_LIB_STRING_LENGTH8(pValue);
   return RTypes<TChar8>::Find(_pMemory, _length, pValue, length);
}

//============================================================
// <T>�ӵ�ǰ�ַ����в���ָ���ַ���������λ�á�</T>
//
// @param pValue �ַ���
// @param offset λ��
// @return ����λ��
//============================================================
TInt MString8::Find(TChar8C* pValue, TInt offset){
   MO_ASSERT_BETWEEN(offset, 0, _length);
   TInt length = MO_LIB_STRING_LENGTH8(pValue);
   TInt result = RTypes<TChar8>::Find(_pMemory + offset, _length - offset, pValue, length);
   return (ENotFound != result) ? offset + result : ENotFound;
}

//============================================================
// <T>�ӵ�ǰ�ַ����е������ָ���ַ���������λ�á�</T>
//
// @param pValue �ַ���
// @return ����λ��
//============================================================
TInt MString8::LastFind(TChar8C* pValue){
   TInt length = MO_LIB_STRING_LENGTH8(pValue);
   return RTypes<TChar8>::LastFind(_pMemory, _length, pValue, length);
}

//============================================================
// <T>����һ���ַ�������ǰ�ַ�����</T>
// <P>�������С��0�����Զ�����ָ������ݳ��ȡ�</P>
//
// @param pValue �ַ���
// @param length ����
// @return ������
//============================================================
TBool MString8::Assign(TChar8C* pValue, TInt length){
   // �������
   Clear();
   // ������
   if(NULL == pValue){
      return EFalse;
   }
   // ����ڴ�
   if(_pMemory == pValue){
      return EFalse;
   }
   // ���㳤��
   if(length <= 0){
      length = MO_LIB_STRING_LENGTH8(pValue);
   }
   // ��������
   if(length > 0){
      // �����ڴ��С
      InnerResize(length + 1, EFalse, EFalse, EFalse);
      // ��������
      RChar8s::Copy(_pMemory, pValue, length);
      _length = length;
      _pMemory[_length] = 0;
   }
   return ETrue;
}

//============================================================
// <T>����һ���ַ�������ǰ�ַ�����</T>
//
// @param ptr �ַ���ָ��
// @return ������
//============================================================
TBool MString8::Assign(const TPtrC<TChar8>& ptr){
   // ������
   if(ptr.IsEmpty()){
      Clear();
      return ETrue;
   }
   // ��������
   return Assign(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>����һ���ַ�������ǰ�ַ�����</T>
//
// @param value �ַ���
// @return ������
//============================================================
TBool MString8::Assign(const MString8& value){
   // ������
   if(value.IsEmpty()){
      Clear();
      return ETrue;
   }
   // ��������
   return Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>����һ���ַ�������ǰ�ַ�����</T>
//
// @param value �ַ���
// @return ������
//============================================================
TBool MString8::AssignPointer(const MString8* pValue){
   // ָ��Ϊ��
   if(NULL == pValue){
      Clear();
      return ETrue;
   }
   // ����Ϊ��
   if(pValue->IsEmpty()){
      Clear();
      return ETrue;
   }
   // �����ַ���
   return Assign(pValue->MemoryC(), pValue->Length());
}

//============================================================
// <T>׷��һ����ʽ���ַ���������β����</T>
//
// @param pFormat ��ʽ
// @param params ��������
// @return ������
//============================================================
TResult MString8::AssignFormat(TChar8C* pFormat, ...){
   // ������
   MO_CHECK(pFormat, return ENull);
   // �������
   Clear();
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pFormat);
   // ׷������
#ifdef _MO_WINDOWS
   TInt length = MO_LIB_STRING_FORMAT_LENGTH8(pFormat, params);
   InnerResize(length + 1, EFalse, EFalse, EFalse);
   MO_LIB_STRING_NFORMAT8(_pMemory, length + 1, pFormat, params);
#else
   TChar8 buffer[MO_FS_SPRINT_LENGTH];
   TInt length = MO_LIB_STRING_NFORMAT8(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   MO_ERROR_CHECK(length >= 0, return EUnsupport,
         "Format string failure. (format=%s)", pFormat);
   InnerResize(length + 1, EFalse, EFalse, EFalse);
   MO_LIB_TYPES_COPY(TChar8, _pMemory, length, buffer, length);
#endif // _MO_WINDOWS
   va_end(params);
   // ��������
   _length = length;
   _pMemory[length] = 0;
   return ESuccess;
}

//============================================================
// <T>׷��һ����ʽ���ַ���������β����</T>
//
// @param pFormat ��ʽ
// @param params ��������
// @return ������
//============================================================
TResult MString8::AssignFormatParameters(TChar8C* pFormat, va_list& params){
   // ������
   MO_CHECK(pFormat, return ENull);
   // �������
   Clear();
   // ׷������
#ifdef _MO_WINDOWS
   TInt length = MO_LIB_STRING_FORMAT_LENGTH8(pFormat, params);
   InnerResize(length + 1, EFalse, EFalse, EFalse);
   MO_LIB_STRING_NFORMAT8(_pMemory, length + 1, pFormat, params);
#else
   TChar8 buffer[MO_FS_SPRINT_LENGTH];
   TInt length = MO_LIB_STRING_NFORMAT8(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   MO_ERROR_CHECK(length >= 0, return EUnsupport,
         "Format string failure. (format=%s)", pFormat);
   InnerResize(length + 1, EFalse, EFalse, EFalse);
   MO_LIB_TYPES_COPY(TChar8, _pMemory, length, buffer, length);
#endif // _MO_WINDOWS
   // ��������
   _length = length;
   _pMemory[length] = 0;
   return ESuccess;
}

//============================================================
// <T>׷��һ���ַ�����ǰ�ַ��������ĩβ��</T>
//
// @param value �ַ�
// @return ������
//============================================================
TBool MString8::Append(TChar8 value){
   InnerResize(_length + 2, ETrue, ETrue, EFalse);
   _pMemory[_length++] = value;
   _pMemory[_length] = 0;
   return ETrue;
}

//============================================================
// <T>׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
// <P>�������С��0�����Զ�����ָ������ݳ��ȡ�</P>
//
// @param pValue �ַ���
// @param length ����
// @return ������
//============================================================
TBool MString8::Append(TChar8C* pValue, TInt length){
   // ������
   if(NULL == pValue){
      return EFalse;
   }
   // ����ڴ�
   if(_pMemory == pValue){
      return EFalse;
   }
   // ���㳤��
   if(length <= 0){
      length = MO_LIB_STRING_LENGTH8(pValue);
   }
   // ��������
   if(length > 0){
      // �����ڴ��С
      InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
      // ��������
      RTypes<TChar8>::Copy(_pMemory + _length, pValue, length);
      _length += length;
      _pMemory[_length] = 0;
   }
   return ETrue;
}

//============================================================
// <T>׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
//
// @param ptr �ַ���ָ��
// @return ������
//============================================================
TBool MString8::Append(const TPtrC<TChar8>& ptr){
   // ������
   if(ptr.IsEmpty()){
      return EFalse;
   }
   // ׷������
   return Append(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
//
// @param value �ַ���
// @return ������
//============================================================
TBool MString8::Append(const MString8& value){
   // ������
   if(value.IsEmpty()){
      return EFalse;
   }
   // ׷������
   return Append(value.MemoryC(), value.Length());
}

//============================================================
// <T>׷��һ�����ֵ���ǰ�ַ��������ĩβ��</T>
//
// @param value ����
// @return ������
//============================================================
TBool MString8::AppendInt(TInt value){
   TChar8 buffer[MO_FS_NUMBER_LENGTH];
   return Append(RNumber<TInt32>::ToSignString<TChar8, TUint32>(buffer, MO_FS_NUMBER_LENGTH, value));
}

//============================================================
// <T>�ظ�׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
//
// @param pValue �ַ���
// @param count ����
// @return ������
//============================================================
TBool MString8::AppendRepeat(TChar8C* pValue, TInt count){
   // ������
   if((NULL == pValue) || (0 == count)){
      return EFalse;
   }
   // ׷������
   for(TInt n = 0; n < count; n++){
      Append(pValue);
   }
   return ETrue;
}

//============================================================
// <T>׷��һ����ʽ���ַ���������β����</T>
//
// @param pFormat ��ʽ
// @param params ��������
// @return ������
//============================================================
TResult MString8::AppendFormat(TChar8C* pFormat, ...){
   // ������
   MO_CHECK(pFormat, return ENull);
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pFormat);
   // �����־��Ϣ
#ifdef _MO_WINDOWS
   TInt length = MO_LIB_STRING_FORMAT_LENGTH8(pFormat, params);
   InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
   MO_LIB_STRING_NFORMAT8(_pMemory + _length, length + 1, pFormat, params);
#else
   TChar8 buffer[MO_FS_SPRINT_LENGTH];
   TInt length = MO_LIB_STRING_NFORMAT8(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   MO_ERROR_CHECK(length >= 0, return EUnsupport,
         "Format string failure. (format=%s)", pFormat);
   InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
   MO_LIB_TYPES_COPY(TChar8, _pMemory + _length, length, buffer, length);
#endif // _MO_WINDOWS
   va_end(params);
   // ��������
   _length += length;
   _pMemory[_length] = 0;
   return ETrue;
}

//============================================================
// <T>׷��һ����ʽ���ַ���������β����</T>
//
// @param pFormat ��ʽ
// @param params ��������
// @return ������
//============================================================
TResult MString8::AppendFormatParameters(TChar8C* pFormat, va_list& params){
   // ������
   MO_CHECK(pFormat, return ENull);
   // ��ʽ���ɱ�����ַ�����Ϣ
#ifdef _MO_WINDOWS
   TInt length = MO_LIB_STRING_FORMAT_LENGTH8(pFormat, params);
   InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
   length = MO_LIB_STRING_NFORMAT8(_pMemory + _length, length + 1, pFormat, params);
   _length += length;
#else
   TChar8 buffer[MO_FS_SPRINT_LENGTH];
   TInt length = MO_LIB_STRING_NFORMAT8(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   MO_ERROR_CHECK(length >= 0, return EUnsupport,
         "Format string failure. (format=%s)", pFormat);
   InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
   MO_LIB_TYPES_COPY(TChar8, _pMemory + _length, length, buffer, length);
#endif // _MO_WINDOWS
   // ��������
   _length += length;
   _pMemory[_length] = 0;
   return ETrue;
}

//============================================================
// <T>׷��һ�����С�</T>
//
// @return ������
//============================================================
void MString8::AppendLine(){
   Append(MO_LINE_CHAR);
}
//============================================================
// <T>׷��һ���ַ���Ϊһ�е���ǰ�ַ��������ĩβ��</T>
//
// @param value �ַ�
// @return ������
//============================================================
void MString8::AppendLine(TChar8 value){
   Append(value);
   Append(MO_LINE_CHAR);
}

//============================================================
// <T>׷��һ���ַ�����Ϊһ�е���ǰ�ַ��������ĩβ��</T>
// <P>�������С��0�����Զ�����ָ������ݳ��ȡ�</P>
//
// @param pValue �ַ���
// @param length ����
// @return ������
//============================================================
void MString8::AppendLine(TChar8C* pValue, TInt length){
   Append(pValue, length);
   Append(MO_LINE_CHAR);
}

//============================================================
// <T>׷��һ����ʽ���ַ�����Ϊһ�е�����β����</T>
//
// @param pFormat ��ʽ
// @param params ��������
// @return ������
//============================================================
TResult MString8::AppendLineFormat(TChar8C* pFormat, ...){
   va_list params;
   va_start(params, pFormat);
   TResult result = AppendFormat(pFormat, params);
   va_end(params);
   Append(MO_LINE_CHAR);
   return result;
}

//============================================================
// <T>׷��һ����ʽ���ַ�����Ϊһ�е�����β����</T>
//
// @param pFormat ��ʽ
// @param params ��������
// @return ������
//============================================================
TResult MString8::AppendLineFormatParameters(TChar8C* pFormat, va_list& params){
   TResult result = AppendFormat(pFormat, params);
   Append(MO_LINE_CHAR);
   return result;
}

//============================================================
// <T>��ָ��UNICODE�ַ���ָ�����ֵ����ǰ�ַ����� </T>
//
// @param pValue UNICODE �ַ���ָ�����
//============================================================
void MString8::Assign8(TChar8C* pValue){
   // ����ת���󳤶�
   TInt length = RString8::ConvertToString8(pValue);
   if(length != -1){
      // ǿ������
      ForceSize(length + 1);
      // ת������
      _length = RString8::ConvertToString8(_pMemory, length, pValue);
      _pMemory[_length] = 0;
   }else{
      // �������
      Clear();
   }
}

//============================================================
// <T>��ָ��UNICODE�ַ���ָ�����ֵ����ǰ�ַ����� </T>
//
// @param pValue UNICODE �ַ���ָ�����
//============================================================
void MString8::Assign16(TChar16C* pValue){
   // ����ת���󳤶�
   TInt length = RString16::ConvertToString8(pValue);
   if(length != -1){
      // ǿ������
      ForceSize(length + 1);
      // ת������
      _length = RString16::ConvertToString8(_pMemory, length, pValue);
      _pMemory[_length] = 0;
   }else{
      // �������
      Clear();
   }
}

//============================================================
// <T>��ָ��UNICODE�ַ���ָ�����ֵ����ǰ�ַ����� </T>
//
// @param pValue UNICODE �ַ���ָ�����
//============================================================
void MString8::Assign32(TChar32C* pValue){
   // ����ת���󳤶�
   TInt length = RString32::ConvertToString8(pValue);
   if(length != -1){
      // ǿ������
      ForceSize(length + 1);
      // ת������
      _length = RString32::ConvertToString8(_pMemory, length, pValue);
      _pMemory[_length] = 0;
   }else{
      // �������
      Clear();
   }
}

//============================================================
// <T>���ڲ��ַ���ת��ΪСд��</T>
//============================================================
void MString8::ToLower(){
   RChar8::ToLower(_pMemory, _length);
}

//============================================================
// <T>���ڲ��ַ���ת��Ϊ��д��</T>
//============================================================
void MString8::ToUpper(){
   RChar8::ToUpper(_pMemory, _length);
}

//============================================================
// TODO: ��ಹ���ַ���
//============================================================
void MString8::PadLeft(TChar8 pad, TInt length){
   MO_FATAL_UNSUPPORT();
}

//============================================================
// �Ҳಹ���ַ���
//============================================================
void MString8::PadRight(TChar8 pad, TInt length){
   TInt count = length - _length;
   for(TInt n=0; n<count; n++){
      _pMemory[_length++] = pad;
   }
}

//============================================================
// <T>�滻ָ���ַ�Ϊ�����ַ���</T>
//============================================================
TInt MString8::Replace(TChar8 source, TChar8 target){
   TInt result = 0;
   for(TInt n = 0; n < _length; n++){
      if(source == _pMemory[n]){
         _pMemory[n] = target;
         result++;
      }
   }
   return result;
}

//============================================================
// <T>����������ݡ�</T>
//
// @return ����
//============================================================
TInt MString8::ToInt(){
   return RInt::Parse8(_pMemory);
}

//============================================================
// <T>��÷Ǹ��������ݡ�</T>
//
// @return �Ǹ�����
//============================================================
TUint MString8::ToUint(){
   return RUint::Parse8(_pMemory);
}

//============================================================
// <T>���64λ�������ݡ�</T>
//
// @return 64λ����
//============================================================
TInt64 MString8::ToInt64(){
   return RInt64::Parse8(_pMemory);
}

//============================================================
// <T>���64λ�Ǹ��������ݡ�</T>
//
// @return 64λ�Ǹ�����
//============================================================
TUint64 MString8::ToUint64(){
   return RUint64::Parse8(_pMemory);
}

//============================================================
// <T>��ø��������ݡ�</T>
//
// @return ������
//============================================================
TFloat MString8::ToFloat(){
   return RFloat::Parse8(_pMemory);
}

//============================================================
// <T>���˫���ȸ��������ݡ�</T>
//
// @return ˫���ȸ�����
//============================================================
TDouble MString8::ToDouble(){
   return RDouble::Parse8(_pMemory);
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void MString8::SetInt(TInt value){
   InnerResize(MO_FS_INTEGER_LENGTH, EFalse, EFalse, EFalse);
   RInt::ToString8(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>���÷Ǹ��������ݡ�</T>
//
// @param value �Ǹ�����
//============================================================
void MString8::SetUint(TUint value){
   InnerResize(MO_FS_INTEGER_LENGTH, EFalse, EFalse, EFalse);
   RUint::ToString8(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>����64λ�������ݡ�</T>
//
// @param value 64λ����
//============================================================
void MString8::SetInt64(TInt64 value){
   InnerResize(MO_FS_INTEGER64_LENGTH, EFalse, EFalse, EFalse);
   RInt64::ToString8(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>����64λ�Ǹ��������ݡ�</T>
//
// @param value 64λ�Ǹ�����
//============================================================
void MString8::SetUint64(TUint64 value){
   InnerResize(MO_FS_INTEGER64_LENGTH, EFalse, EFalse, EFalse);
   RUint64::ToString8(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>���ø��������ݡ�</T>
//
// @param value ������
//============================================================
void MString8::SetFloat(TFloat value){
   InnerResize(MO_FS_FLOAT_LENGTH, EFalse, EFalse, EFalse);
   RFloat::ToString8(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>����˫���ȸ��������ݡ�</T>
//
// @param value ˫���ȸ�����
//============================================================
void MString8::SetDouble(TDouble value){
   InnerResize(MO_FS_DOUBLE_LENGTH, EFalse, EFalse, EFalse);
   RDouble::ToString8(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>���л��ַ������ݵ��������</T>
//
// @param pOutput �����
//============================================================
void MString8::Serialize(IDataOutput* pOutput){
   MO_ASSERT(_length < 0x10000);
   pOutput->WriteUint16((TUint16)_length);
   if(_length > 0){
      pOutput->Write(_pMemory, sizeof(TChar8) * _length);
   }
}

//============================================================
// <T>���������ڷ����л��ַ������ݡ�</T>
//
// @param pOutput �����
//============================================================
void MString8::Unserialize(IDataInput* pInput){
   TInt length = pInput->ReadUint16();
   if(length > 0){
      InnerResize(length + 1, EFalse, EFalse, EFalse);
      pInput->Read(_pMemory, sizeof(TChar8) * length);
   }
   _length = length;
   if(_pMemory != NULL){
      _pMemory[length] = 0;
   }
}

//============================================================
// <T>���������ڷ����л��ַ������ݡ�</T>
//
// @param pOutput �����
//============================================================
void MString8::UnserializeAutomatic(IDataInput* pInput){
   EChar charCd = (EChar)pInput->ReadUint8();
   TInt length = pInput->ReadUint16();
   if(length > 0){
      InnerResize(length + 1, EFalse, EFalse, EFalse);
      if(charCd == EChar_Char8){
         for(TInt n = 0; n < length; n++){
            _pMemory[n] = (TChar8)pInput->ReadUint8();
         }
      }else if(charCd == EChar_Char16){
         for(TInt n = 0; n < length; n++){
            _pMemory[n] = (TChar8)pInput->ReadUint16();
         }
      }else if(charCd == EChar_Char32){
         for(TInt n = 0; n < length; n++){
            _pMemory[n] = (TChar8)pInput->ReadUint32();
         }
      }
   }
   _length = length;
   if(_pMemory != NULL){
      _pMemory[length] = 0;
   }
}

//============================================================
// <T>�����ַ����ĳ��ȡ�</T>
//
// @param length ����
//============================================================
void MString8::SetLength(TInt length){
   InnerResize(length + 1, ETrue, EFalse, EFalse);
   _length = length;
   _pMemory[length] = 0;
}

//============================================================
// <T>������ǰ�ַ������ݡ�</T>
// <P>����ַ����к���0�����������Ĳ��֣����������ȡ�</P>
// <P>����ַ�����β��û��0�����Զ�����0���н�β��</P>
//============================================================
void MString8::Fix(){
   if(_pMemory != NULL){
      for(TInt n = 0; n < _capacity; n++){
         if(_pMemory[n] == 0){
            _length = n;
            break;
         }
      }
      _pMemory[_length] = 0;
   }
}

//============================================================
// <T>����������ݡ�</T>
//============================================================
void MString8::Clear(){
   _length = 0;
   if(_pMemory != NULL){
      _pMemory[0] = 0;
   }
}

MO_NAMESPACE_END
