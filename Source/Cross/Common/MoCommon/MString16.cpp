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
TChar16* MString16::MemoryZ(){
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
TString16PtrC MString16::PtrZ(){
   // ���ý�����
   EnsureSize(_length + 1);
   _pMemory[_length] = 0;
   // �����ڴ�ָ��
   return TString16PtrC(_pMemory, _length);
}

//============================================================
// <T>���ֻ���ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::StrC() const{
   return TString16PtrC(_pMemory, _length);
}

//============================================================
// <T>��õ�ǰ�����е���߲�����������á�</T>
//
// @param length ����
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::LeftStrC(TInt length) const{
   MO_ASSERT_BETWEEN(length, 0, _length);
   return TString16PtrC(_pMemory, length);
}

//============================================================
// <T>��õ�ǰ�����еĿ�ʼ����β�����á�</T>
//
// @param offset λ��
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::MidStrC(TInt offset) const{
   MO_ASSERT_BETWEEN(offset, 0, _length);
   return TString16PtrC(_pMemory + offset, _length - offset);
}

//============================================================
// <T>��õ�ǰ�����еĲ�����������á�</T>
//
// @param offset λ��
// @param length ����
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::MidStrC(TInt offset, TInt length) const{
   MO_ASSERT_BETWEEN(offset, 0, _length);
   MO_ASSERT_BETWEEN(length, 0, _length - offset);
   return TString16PtrC(_pMemory + offset, length);
}

//============================================================
// <T>��õ�ǰ�����е��ұ߲�����������á�</T>
//
// @param length ����
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::RightStrC(TInt length) const{
   MO_ASSERT_BETWEEN(length, 0, _length);
   return TString16PtrC(_pMemory + (_length - length), length);
}

//============================================================
// <T>��õ�ǰ�����еĲ�����������á�</T>
//
// @param begin ��ʼλ��
// @param end ����λ��
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::SubStrC(TInt begin, TInt end) const{
   MO_ASSERT_BETWEEN(begin, 0, _length);
   MO_ASSERT_BETWEEN(end, 0, _length);
   MO_ASSERT(begin <= end);
   return TString16PtrC(_pMemory + begin, end - begin);
}

//============================================================
// <T>ȥ����ߵĿհף������ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::TrimLeftStrC() const{
   TInt position = 0;
   TInt length = Length();
   TChar16* pMemory = _pMemory;
   while((position < length) && (pMemory[position] <= ' ')){
      position++;
   }
   return TString16PtrC(pMemory + position, length - position);
}

//============================================================
// <T>ȥ���ұߵĿհף������ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::TrimRightStrC() const{
   TInt position = Length() - 1;
   TChar16* pMemory = _pMemory;
   while((position >= 0) && (pMemory[position] <= ' ')){
      position--;
   }
   return TString16PtrC(pMemory, position);
}

//============================================================
// <T>ȥ�����ߵĿհף������ַ���ָ�롣</T>
//
// @return �ַ���ָ��
//============================================================
TString16PtrC MString16::TrimStrC() const{
   TInt start = 0;
   TInt length = Length();
   TChar16* pMemory = _pMemory;
   // ȥ����߿հ��ַ�
   while((start < length) && (pMemory[start] <= ' ')){
      start++;
   }
   // ȥ���ұ߿հ��ַ�
   TInt end = length - 1;
   while((end >= 0) && (pMemory[end] <= ' ')){
      end--;
   }
   return TString16PtrC(pMemory + start, end - start + 1);
}

//============================================================
// <T>�жϵ�ǰ�ַ�����ָ���ַ����Ƿ���ȡ�</T>
//
// @param pValue ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString16::Equals(TChar16C* pValue) const{
   return RString16::Equals(MemoryC(), pValue);
}

//============================================================
// <T>�������ַ���Сд���жϵ�ǰ�ַ�����ָ���ַ����Ƿ���ȡ�</T>
//
// @param pValue ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString16::EqualsIgnoreCase(TChar16C* pValue) const{
   return (0 == MO_LIB_STRING_COMPARE_IGNORECASE16(MemoryC(), pValue));
}

//============================================================
// <T>�������ַ���Сд���жϵ�ǰ�ַ�����ָ���ַ����Ƿ���ȡ�</T>
//
// @param value ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString16::EqualsIgnoreCase(const TString16PtrC& value) const{
   return (0 == MO_LIB_STRING_COMPARE_IGNORECASE16(MemoryC(), value.MemoryC()));
}

//============================================================
// <T>����ָ�������Ƿ�����ڵ�ǰ����Ŀ�ʼλ�á�</T>
//
// @param pValue ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString16::StartsWith(TChar16C* pValue) const{
   MO_ASSERT(pValue);
   TInt length = MO_LIB_STRING_LENGTH16(pValue);
   return RTypes<TChar16C>::StartsWith(_pMemory, _length, pValue, length);
}

//============================================================
// <T>����ָ�������Ƿ�����ڵ�ǰ����Ľ���λ�á�</T>
//
// @param pValue ָ���ַ���
// @return <L value='ETrue'>���</L>
//         <L value='EFalse'>�����</L>
//============================================================
TBool MString16::EndsWith(TChar16C* pValue) const{
   MO_ASSERT(pValue);
   TInt length = MO_LIB_STRING_LENGTH16(pValue);
   return RTypes<TChar16C>::EndsWith(_pMemory, _length, pValue, length);
}

//============================================================
// <T>�������ַ���Сд���жϵ�ǰ�ַ�����ָ���ַ����Ĵ�С��</T>
//
// @param pValue ָ���ַ���
// @return <L value='С��0'>��ǰ�ַ���С��ָ���ַ���</L>
//         <L value='����0'>��ǰ�ַ������ָ���ַ���</L>
//         <L value='����0'>��ǰ�ַ�������ָ���ַ���</L>
//============================================================
TInt MString16::CompareIgnoreCase(TChar16C* pValue) const{
   return MO_LIB_STRING_COMPARE_IGNORECASE16(MemoryC(), pValue);
}

//============================================================
// <T>�������ַ���Сд���жϵ�ǰ�ַ�����ָ���ַ����Ĵ�С��</T>
//
// @param value ָ���ַ���
// @return <L value='С��0'>��ǰ�ַ���С��ָ���ַ���</L>
//         <L value='����0'>��ǰ�ַ������ָ���ַ���</L>
//         <L value='����0'>��ǰ�ַ�������ָ���ַ���</L>
//============================================================
TInt MString16::CompareIgnoreCase(const TString16PtrC& value) const{
   return MO_LIB_STRING_COMPARE_IGNORECASE16(MemoryC(), value.MemoryC());
}

//============================================================
// <T>���㵱ǰ�ַ����Ĺ�ϣֵ��</T>
//
// @return ��ϣֵ
//============================================================
THashCode MString16::HashCode() const{
   return RTypes<TChar16>::MakeHashCode(_pMemory, _length);
}

//============================================================
// <T>�ӵ�ǰ�ַ����в���ָ���ַ���������λ�á�</T>
//
// @param pValue �ַ���
// @return ����λ��
//============================================================
TInt MString16::Find(TChar16C* pValue){
   TInt length = MO_LIB_STRING_LENGTH16(pValue);
   return RTypes<TChar16>::Find(_pMemory, _length, pValue, length);
}

//============================================================
// <T>�ӵ�ǰ�ַ����в���ָ���ַ���������λ�á�</T>
//
// @param pValue �ַ���
// @param offset λ��
// @return ����λ��
//============================================================
TInt MString16::Find(TChar16C* pValue, TInt offset){
   MO_ASSERT_BETWEEN(offset, 0, _length);
   TInt length = MO_LIB_STRING_LENGTH16(pValue);
   TInt result = RTypes<TChar16>::Find(_pMemory + offset, _length - offset, pValue, length);
   return (ENotFound != result) ? offset + result : ENotFound;
}

//============================================================
// <T>�ӵ�ǰ�ַ����е������ָ���ַ���������λ�á�</T>
//
// @param pValue �ַ���
// @return ����λ��
//============================================================
TInt MString16::LastFind(TChar16C* pValue){
   TInt length = MO_LIB_STRING_LENGTH16(pValue);
   return RTypes<TChar16>::LastFind(_pMemory, _length, pValue, length);
}

//============================================================
// <T>����һ���ַ�������ǰ�ַ�����</T>
// <P>�������С��0�����Զ�����ָ������ݳ��ȡ�</P>
//
// @param pValue �ַ���
// @param length ����
// @return ������
//============================================================
TBool MString16::Assign(TChar16C* pValue, TInt length){
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
      length = MO_LIB_STRING_LENGTH16(pValue);
   }
   // ��������
   if(length > 0){
      // �����ڴ��С
      InnerResize(length + 1, EFalse, EFalse, EFalse);
      // ��������
      RChar16s::Copy(_pMemory, pValue, length);
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
TBool MString16::Assign(const TPtrC<TChar16>& ptr){
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
TBool MString16::Assign(const MString16& value){
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
TBool MString16::AssignPointer(const MString16* pValue){
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
TResult MString16::AssignFormat(TChar16C* pFormat, ...){
   // ������
   MO_CHECK(pFormat, return ENull);
   // �������
   Clear();
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pFormat);
   // ׷������
#ifdef _MO_WINDOWS
   TInt length = MO_LIB_STRING_FORMAT_LENGTH16(pFormat, params);
   InnerResize(length + 1, EFalse, EFalse, EFalse);
   MO_LIB_STRING_NFORMAT16(_pMemory, length + 1, pFormat, params);
#else
   TChar16 buffer[MO_FS_SPRINT_LENGTH];
   TInt length = MO_LIB_STRING_NFORMAT16(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   MO_ERROR_CHECK(length >= 0, return EUnsupport,
         "Format string failure. (format=%s)", pFormat);
   InnerResize(length + 1, EFalse, EFalse, EFalse);
   MO_LIB_TYPES_COPY(TChar16, _pMemory, length, buffer, length);
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
TResult MString16::AssignFormatParameters(TChar16C* pFormat, va_list& params){
   // ������
   MO_CHECK(pFormat, return ENull);
   // �������
   Clear();
   // ׷������
#ifdef _MO_WINDOWS
   TInt length = MO_LIB_STRING_FORMAT_LENGTH16(pFormat, params);
   InnerResize(length + 1, EFalse, EFalse, EFalse);
   MO_LIB_STRING_NFORMAT16(_pMemory, length + 1, pFormat, params);
#else
   TChar16 buffer[MO_FS_SPRINT_LENGTH];
   TInt length = MO_LIB_STRING_NFORMAT16(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   MO_ERROR_CHECK(length >= 0, return EUnsupport,
         "Format string failure. (format=%s)", pFormat);
   InnerResize(length + 1, EFalse, EFalse, EFalse);
   MO_LIB_TYPES_COPY(TChar16, _pMemory, length, buffer, length);
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
TBool MString16::Append(TChar16 value){
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
TBool MString16::Append(TChar16C* pValue, TInt length){
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
      length = MO_LIB_STRING_LENGTH16(pValue);
   }
   // ��������
   if(length > 0){
      // �����ڴ��С
      InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
      // ��������
      RTypes<TChar16>::Copy(_pMemory + _length, pValue, length);
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
TBool MString16::Append(const TPtrC<TChar16>& ptr){
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
TBool MString16::Append(const MString16& value){
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
TBool MString16::AppendInt(TInt value){
   TChar16 buffer[MO_FS_NUMBER_LENGTH];
   return Append(RNumber<TInt32>::ToSignString<TChar16, TUint32>(buffer, MO_FS_NUMBER_LENGTH, value));
}

//============================================================
// <T>�ظ�׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
//
// @param pValue �ַ���
// @param count ����
// @return ������
//============================================================
TBool MString16::AppendRepeat(TChar16C* pValue, TInt count){
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
TResult MString16::AppendFormat(TChar16C* pFormat, ...){
   // ������
   MO_CHECK(pFormat, return ENull);
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pFormat);
   // �����־��Ϣ
#ifdef _MO_WINDOWS
   TInt length = MO_LIB_STRING_FORMAT_LENGTH16(pFormat, params);
   InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
   MO_LIB_STRING_NFORMAT16(_pMemory + _length, length + 1, pFormat, params);
#else
   TChar16 buffer[MO_FS_SPRINT_LENGTH];
   TInt length = MO_LIB_STRING_NFORMAT16(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   MO_ERROR_CHECK(length >= 0, return EUnsupport,
         "Format string failure. (format=%s)", pFormat);
   InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
   MO_LIB_TYPES_COPY(TChar16, _pMemory + _length, length, buffer, length);
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
TResult MString16::AppendFormatParameters(TChar16C* pFormat, va_list& params){
   // ������
   MO_CHECK(pFormat, return ENull);
   // ��ʽ���ɱ�����ַ�����Ϣ
#ifdef _MO_WINDOWS
   TInt length = MO_LIB_STRING_FORMAT_LENGTH16(pFormat, params);
   InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
   length = MO_LIB_STRING_NFORMAT16(_pMemory + _length, length + 1, pFormat, params);
   _length += length;
#else
   TChar16 buffer[MO_FS_SPRINT_LENGTH];
   TInt length = MO_LIB_STRING_NFORMAT16(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   MO_ERROR_CHECK(length >= 0, return EUnsupport,
         "Format string failure. (format=%s)", pFormat);
   InnerResize(_length + length + 1, ETrue, ETrue, EFalse);
   MO_LIB_TYPES_COPY(TChar16, _pMemory + _length, length, buffer, length);
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
void MString16::AppendLine(){
   Append(MO_LINE_CHAR);
}
//============================================================
// <T>׷��һ���ַ���Ϊһ�е���ǰ�ַ��������ĩβ��</T>
//
// @param value �ַ�
// @return ������
//============================================================
void MString16::AppendLine(TChar16 value){
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
void MString16::AppendLine(TChar16C* pValue, TInt length){
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
TResult MString16::AppendLineFormat(TChar16C* pFormat, ...){
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
TResult MString16::AppendLineFormatParameters(TChar16C* pFormat, va_list& params){
   TResult result = AppendFormat(pFormat, params);
   Append(MO_LINE_CHAR);
   return result;
}

//============================================================
// <T>��ָ��UNICODE�ַ���ָ�����ֵ����ǰ�ַ����� </T>
//
// @param pValue UNICODE �ַ���ָ�����
//============================================================
void MString16::Assign8(TChar8C* pValue){
   // ����ת���󳤶�
   TInt length = RString8::ConvertToString16(pValue);
   if(length > 0 ){
      // ǿ������
      ForceSize(length + 1);
      // ת������
      _length = RString8::ConvertToString16(_pMemory, length, pValue);
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
void MString16::Assign16(TChar16C* pValue){
   // ����ת���󳤶�
   TInt length = RString16::ConvertToString16(pValue);
   if(length != -1){
      // ǿ������
      ForceSize(length + 1);
      // ת������
      _length = RString16::ConvertToString16(_pMemory, length, pValue);
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
void MString16::Assign32(TChar32C* pValue){
   // ����ת���󳤶�
   TInt length = RString32::ConvertToString16(pValue);
   if(length != -1){
      // ǿ������
      ForceSize(length + 1);
      // ת������
      _length = RString32::ConvertToString16(_pMemory, length, pValue);
      _pMemory[_length] = 0;
   }else{
      // �������
      Clear();
   }
}

//============================================================
// <T>���ڲ��ַ���ת��ΪСд��</T>
//============================================================
void MString16::ToLower(){
   RChar16::ToLower(_pMemory, _length);
}

//============================================================
// <T>���ڲ��ַ���ת��Ϊ��д��</T>
//============================================================
void MString16::ToUpper(){
   RChar16::ToUpper(_pMemory, _length);
}

//============================================================
// TODO: ��ಹ���ַ���
//============================================================
void MString16::PadLeft(TChar16 pad, TInt length){
   MO_FATAL_UNSUPPORT();
}

//============================================================
// �Ҳಹ���ַ���
//============================================================
void MString16::PadRight(TChar16 pad, TInt length){
   TInt count = length - _length;
   for(TInt n=0; n<count; n++){
      _pMemory[_length++] = pad;
   }
}

//============================================================
// <T>�滻ָ���ַ�Ϊ�����ַ���</T>
//============================================================
TInt MString16::Replace(TChar16 source, TChar16 target){
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
TInt MString16::ToInt(){
   return RInt::Parse16(_pMemory);
}

//============================================================
// <T>��÷Ǹ��������ݡ�</T>
//
// @return �Ǹ�����
//============================================================
TUint MString16::ToUint(){
   return RUint::Parse16(_pMemory);
}

//============================================================
// <T>���64λ�������ݡ�</T>
//
// @return 64λ����
//============================================================
TInt64 MString16::ToInt64(){
   return RInt64::Parse16(_pMemory);
}

//============================================================
// <T>���64λ�Ǹ��������ݡ�</T>
//
// @return 64λ�Ǹ�����
//============================================================
TUint64 MString16::ToUint64(){
   return RUint64::Parse16(_pMemory);
}

//============================================================
// <T>��ø��������ݡ�</T>
//
// @return ������
//============================================================
TFloat MString16::ToFloat(){
   return RFloat::Parse16(_pMemory);
}

//============================================================
// <T>���˫���ȸ��������ݡ�</T>
//
// @return ˫���ȸ�����
//============================================================
TDouble MString16::ToDouble(){
   return RDouble::Parse16(_pMemory);
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param value ����
//============================================================
void MString16::SetInt(TInt value){
   InnerResize(MO_FS_INTEGER_LENGTH, EFalse, EFalse, EFalse);
   RInt::ToString16(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>���÷Ǹ��������ݡ�</T>
//
// @param value �Ǹ�����
//============================================================
void MString16::SetUint(TUint value){
   InnerResize(MO_FS_INTEGER_LENGTH, EFalse, EFalse, EFalse);
   RUint::ToString16(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>����64λ�������ݡ�</T>
//
// @param value 64λ����
//============================================================
void MString16::SetInt64(TInt64 value){
   InnerResize(MO_FS_INTEGER64_LENGTH, EFalse, EFalse, EFalse);
   RInt64::ToString16(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>����64λ�Ǹ��������ݡ�</T>
//
// @param value 64λ�Ǹ�����
//============================================================
void MString16::SetUint64(TUint64 value){
   InnerResize(MO_FS_INTEGER64_LENGTH, EFalse, EFalse, EFalse);
   RUint64::ToString16(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>���ø��������ݡ�</T>
//
// @param value ������
//============================================================
void MString16::SetFloat(TFloat value){
   InnerResize(MO_FS_FLOAT_LENGTH, EFalse, EFalse, EFalse);
   RFloat::ToString16(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>����˫���ȸ��������ݡ�</T>
//
// @param value ˫���ȸ�����
//============================================================
void MString16::SetDouble(TDouble value){
   InnerResize(MO_FS_DOUBLE_LENGTH, EFalse, EFalse, EFalse);
   RDouble::ToString16(value, _pMemory, _capacity);
   Fix();
}

//============================================================
// <T>���л��ַ������ݵ��������</T>
//
// @param pOutput �����
//============================================================
void MString16::Serialize(IDataOutput* pOutput){
   MO_ASSERT(_length < 0x10000);
   pOutput->WriteUint16((TUint16)_length);
   if(_length > 0){
      pOutput->Write(_pMemory, sizeof(TChar16) * _length);
   }
}

//============================================================
// <T>���������ڷ����л��ַ������ݡ�</T>
//
// @param pOutput �����
//============================================================
void MString16::Unserialize(IDataInput* pInput){
   TInt length = pInput->ReadUint16();
   if(length > 0){
      InnerResize(length + 1, EFalse, EFalse, EFalse);
      pInput->Read(_pMemory, sizeof(TChar16) * length);
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
void MString16::UnserializeAutomatic(IDataInput* pInput){
   EChar charCd = (EChar)pInput->ReadUint8();
   TInt length = pInput->ReadUint16();
   if(length > 0){
      InnerResize(length + 1, EFalse, EFalse, EFalse);
      if(charCd == EChar_Char8){
         for(TInt n = 0; n < length; n++){
            _pMemory[n] = (TChar16)pInput->ReadUint8();
         }
      }else if(charCd == EChar_Char16){
         for(TInt n = 0; n < length; n++){
            _pMemory[n] = (TChar16)pInput->ReadUint16();
         }
      }else if(charCd == EChar_Char32){
         for(TInt n = 0; n < length; n++){
            _pMemory[n] = (TChar16)pInput->ReadUint32();
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
void MString16::SetLength(TInt length){
   InnerResize(length + 1, ETrue, EFalse, EFalse);
   _length = length;
   _pMemory[length] = 0;
}

//============================================================
// <T>������ǰ�ַ������ݡ�</T>
// <P>����ַ����к���0�����������Ĳ��֣����������ȡ�</P>
// <P>����ַ�����β��û��0�����Զ�����0���н�β��</P>
//============================================================
void MString16::Fix(){
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
void MString16::Clear(){
   _length = 0;
   if(_pMemory != NULL){
      _pMemory[0] = 0;
   }
}

MO_NAMESPACE_END
