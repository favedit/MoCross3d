#include "MoCmString8.h"
#include "MoCmString16.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ�����</T>
//============================================================
TString8::TString8(){
}

//============================================================
// <T>�����ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
TString8::TString8(TChar8C* pValue, TInt length){
   Assign(pValue, length);
}

//============================================================
// <T>�����ַ�����</T>
//
// @param ptr �ַ���ָ��
//============================================================
TString8::TString8(const TString8PtrC& ptr){
   Assign(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>�����ַ�����</T>
//
// @param value �ַ���
//============================================================
TString8::TString8(const MString8& value){
   Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����ַ�����</T>
//
// @param value �ַ���
//============================================================
TString8::TString8(const TString8& value){
   Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����ַ�����</T>
//============================================================
TString8::~TString8(){
   MO_FREE(_pMemory);
}

//============================================================
// <T>�����ڴ��С��</T>
//
// @param size ��С
// @param copy ����
// @param extends ��չ
//============================================================
void TString8::InnerResize(TInt size, TBool copy, TBool extends, TBool force){
   if(size != _capacity){
      // ����ռ����ɹ����򲻽��и������ݴ���
      TChar8* pAlloc = MO_TYPES_ALLOC(TChar8, size);
      MO_ASSERT(pAlloc);
      // ���������ǰ�ڴ�
      if(NULL != _pMemory){
         // �������С�ڴ棬���鳤��
         if(_length > size){
            _length = size;
         }
         // ������Ч����
         if(copy && (_length > 0)){
            MO_LIB_TYPES_COPY(TChar8, pAlloc, size, _pMemory, _length);
         }
         // �ͷ���ǰ�ڴ�
         MO_FREE(_pMemory);
      }
      // �����µ��ڴ�
      _pMemory = pAlloc;
      _pMemory[_length] = 0;
      _capacity = size;
   }
}

//============================================================
// <T>��ָ��UNICODE�ַ���ָ�������ӵ���ǰ�ַ����� </T>
//
// @param pValue UNICODE �ַ���ָ�����
//============================================================
void TString8::Append8(TChar8C* pValue){
	//   TSize length = RString16::ConvertToString8(pValue);
	//   if(0 == length){
	//      MO_ERROR(TC("Convert error!"));
	//   }else{
	//      InnerInitialize(length + _length);
	//      RString16::ConvertToString8(_pMemory + length, length, pValue);
	//      _length = _length + length;
	//   }
}

//============================================================
// <T>��ָ��UNICODE�ַ���ָ�������ӵ���ǰ�ַ����� </T>
//
// @param pValue UNICODE �ַ���ָ�����
//============================================================
void TString8::Append16(TChar16C* pValue){
//   TSize length = RString16::ConvertToString8(pValue);
//   if(0 == length){
//      MO_ERROR(TC("Convert error!"));
//   }else{
//      InnerInitialize(length + _length);
//      RString16::ConvertToString8(_pMemory + length, length, pValue);
//      _length = _length + length;
//   }
}

//============================================================
// <T>��ָ��UNICODE�ַ���ָ�������ӵ���ǰ�ַ����� </T>
//
// @param pValue UNICODE �ַ���ָ�����
//============================================================
void TString8::Append32(TChar32C* pValue){
//   TInt length = RString32::ConvertToString8(pValue);
//   if(-1 == length){
//      MO_ERROR("convert error!");
//   }else{
//      InnerInitialize(length + _length);
//      RString32::ConvertToString8(_pMemory + length, length, pValue);
//      _length = _length + length;
//   }
}

MO_NAMESPACE_END
