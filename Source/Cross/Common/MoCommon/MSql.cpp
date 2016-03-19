#include "MoCmData.h"
#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>׷��һ������ֵ��</T>
//
// @param value ����ֵ
//============================================================
void MSql::AppendBoolean(TBool value){
   if(value){
      Append(TC("TRUE"));
   }else{
      Append(TC("FALSE"));
   }
}

//============================================================
// <T>׷��һ��������</T>
//
// @param value ����
//============================================================
void MSql::AppendInteger(TInt value){
   TChar buffer[MO_FS_NUMBER_LENGTH];
   Append(RNumber<TInt32>::ToSignString<TChar, TUint32>(buffer, MO_FS_NUMBER_LENGTH, value));
}

//============================================================
// <T>׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
// <P>�������С��0�����Զ�����ָ������ݳ��ȡ�</P>
//
// @param pValue ����
// @param length ����
//============================================================
void MSql::AppendString(TCharC* pValue, TInt length){
   // ����ڴ棨��ֹ׷�����ڴ棩
   if(_pMemory == pValue){
      return;
   }
   // ������
   if(NULL == pValue){
      if(0 != length){
         MO_FATAL(TC("Invalid string memory. (value=0x%08X, length=%d)"), pValue, length);
         return;
      }
   }else{
      // ���㳤��
      if(length <= 0){
         length = RTypes<TChar>::IndexOf(pValue, 0);
      }
   }
   MO_ASSERT(length >= 0);
   // ��������
   if(0 == length){
      Append(TC("NULL"));
   }else{
      // �����ڴ��С
      TInt maxLength = _length + length + length + 1;
      if(maxLength >= _capacity){
         EnsureSize(maxLength);
      }
      // �����ַ���
      TChar* pWriter = _pMemory + _length;
      *pWriter++ = '\'';
      for(TInt n = 0; n < length; n++){
         TChar value = pValue[n];
         if(value == '\''){
            // �����ַ� (')
            *pWriter++ = '\\';
            *pWriter++ = value;
         }else if(value == '"'){
            // �����ַ� (")
            *pWriter++ = '\\';
            *pWriter++ = value;
         }else if(value == '\\'){
            // �����ַ� (\)
            *pWriter++ = '\\';
            *pWriter++ = value;
         }else if(value == '\r'){
            // �����ַ� (\r)
            *pWriter++ = '\\';
            *pWriter++ = value;
         }else if(value == '\n'){
            // �����ַ� (\n)
            *pWriter++ = '\\';
            *pWriter++ = value;
         }else{
            *pWriter++ = value;
         }
      }
      *pWriter++ = '\'';
      // ���㳤��
      _length = pWriter - _pMemory;
      _pMemory[_length] = 0;
   }
}

//============================================================
// <T>׷��һ����ʽ���ַ���������β����</T>
//
// @param pFormat ��ʽ�ַ���
//============================================================
void MSql::AppendStringFormat(TCharC* pFormat, ...){
   // ��ʽ���ɱ�����ַ�����Ϣ
   va_list params;
   va_start(params, pFormat);
   // �����־��Ϣ
#ifdef _MO_LINUX
   TChar buffer[MO_FS_SPRINT_LENGTH];
   TInt length = vsnprintf(buffer, MO_FS_SPRINT_LENGTH - 1, pFormat, params);
   buffer[length] = 0;
   AppendString(buffer);
#endif
   va_end(params);
}

MO_NAMESPACE_END
