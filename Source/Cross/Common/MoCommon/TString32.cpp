#include "MoCmString32.h"
#include "MoCmString8.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ�����</T>
//============================================================
TString32::TString32(){
}

//============================================================
// <T>�����ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
TString32::TString32(TChar32C* pValue, TInt length){
	Assign(pValue, length);
}

//============================================================
// <T>�����ַ�����</T>
//
// @param ptr �ַ���ָ��
//============================================================
TString32::TString32(const TString32PtrC& ptr){
	Assign(ptr.MemoryC(), ptr.Length());
}

//============================================================
// <T>�����ַ�����</T>
//
// @param value �ַ���
//============================================================
TString32::TString32(const MString32& value){
	Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����ַ�����</T>
//
// @param value �ַ���
//============================================================
TString32::TString32(const TString32& value){
	Assign(value.MemoryC(), value.Length());
}

//============================================================
// <T>�����ַ�����</T>
//============================================================
TString32::~TString32(){
	MO_FREE(_pMemory);
}

//============================================================
// <T>�����ڴ��С��</T>
//
// @param size ��С
// @param copy ����
// @param extends ��չ
//============================================================
void TString32::InnerResize(TInt size, TBool copy, TBool extends, TBool force){
	if(size != _capacity){
		// ����ռ����ɹ����򲻽��и������ݴ���
		TChar32* pAlloc = MO_TYPES_ALLOC(TChar32, size);
		MO_ASSERT(pAlloc);
		// ���������ǰ�ڴ�
		if(NULL != _pMemory){
			// �������С�ڴ棬���鳤��
			if(_length > size){
				_length = size;
			}
			// ������Ч����
			if(copy && (_length > 0)){
				MO_LIB_TYPES_COPY(TChar32, pAlloc, size, _pMemory, _length);
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
void TString32::Append8(TChar8C* pValue){
}

//============================================================
void TString32::Append16(TChar32C* pValue){
}

//============================================================
void TString32::Append32(TChar32C* pValue){
}
//
//
////============================================================
//// <T>��ָ��ANSI�ַ���ָ�����ֵ����ǰ�ַ�����</T>
////
//// @param pValue ANSI�ַ���ָ��
////============================================================
//void TString32::AssignAnsi(TChar8C* pValue){
//   TSize length = RString8::ConvertToString32(pValue);
//   if(-1 == length){
//      MO_ERROR(TC("Convert error!"));
//   }else{
//      InnerInitialize(length);
//      Clear();
//      RString8::ConvertToString32(_pMemory, length, pValue);
//      _length = length;
//   }
//}
//
////============================================================
//// <T>��ָ��ANSI�ַ���ָ�������ӵ���ǰ�ַ�����</T>
////
//// @param pValue ANSI�ַ���ָ��
////============================================================
//void TString32::AppendAnsi(TChar8C* pValue){
//   MO_ASSERT(pValue);
//   TSize length = RString8::ConvertToString32(pValue);
//   if(-1 == length){
//      MO_ERROR(TC("Convert error!"));
//   }else{
//      InnerInitialize(length + _length);
//      RString8::ConvertToString32(_pMemory + length, length, pValue);
//      _length = _length + length;
//   }
//}

MO_NAMESPACE_END
