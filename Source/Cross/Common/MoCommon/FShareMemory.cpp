#ifdef _MO_LINUX
#include <sys/ipc.h>
#include <sys/shm.h>
#endif
#include "MoCmMemory.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����һ�鹲���ڴ����</T>
//
// @return �����ڴ����
//============================================================
FShareMemory::FShareMemory(){
   _linked = EFalse;
   _key = 0;
   _pMemory = NULL;
   _created = EFalse;
   _capacity = 0;
   _position = 0;
}

//============================================================
// <T>�ͷ�һ�鹲���ڴ����</T>
//============================================================
FShareMemory::~FShareMemory(){
}

//============================================================
// <T>����һ��ָ����С�Ĺ����ڴ档</T>
//
// @param key �����ڴ��ֵ
// @param capacity �ڴ��С
// @return �Ƿ�ɹ�
//============================================================
TBool FShareMemory::Create(){
#ifdef _MO_WINDOWS
   // ��������
   TFsPath code;
   code.AppendFormat(TC("%s:%d"), (TCharC*)_keyName, _key);
   // �����ļ�
   _hMemory = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, _capacity, (TCharC*)code);
   if(NULL == _hMemory){
      MO_PFATAL(CreateFileMapping);
      return EFalse;
   }
   // ӳ���ļ�
   _pMemory = (TByte*)MapViewOfFile(_hMemory, FILE_MAP_ALL_ACCESS, 0, 0, _capacity);
   if(NULL == _pMemory){
      MO_PFATAL(MapViewOfFile);
      return EFalse;
   }
   MO_INFO(TC("Create share memory. (handle=%d, memory=0x%08X, capacity=%d, code=%s)"), _hMemory, _pMemory, _capacity, (TCharC*)code);
#endif // _MO_WINDOWS
   //............................................................
#ifdef _MO_LINUX
   _pMemory = (TByte*)RShareMemory::Create(_key, _capacity);
#endif // _MO_LINUX
   //............................................................
   // ��������
   _linked = ETrue;
   _created = ETrue;
   _position = 0;
   return ETrue;
}

//============================================================
// <T>ֻ����ʽ����һ�鹲���ڴ档</T>
//
// @param key �����ڴ��ֵ
// @return �Ƿ�ɹ�
//============================================================
TBool FShareMemory::Connect(){
   // ��������
   SShareMemoryInfo info;
   RType<SShareMemoryInfo>::Clear(&info);
   //............................................................
#ifdef _MO_WINDOWS
   // ��������
   TFsPath code;
   code.AppendFormat(TC("%s:%d"), (TCharC*)_keyName, _key);
   // �����ļ�
   _hMemory = OpenFileMapping(FILE_MAP_ALL_ACCESS, ETrue, (TCharC*)code);
   if(NULL == _hMemory){
      MO_PFATAL(OpenFileMapping);
      return EFalse;
   }
   // ӳ���ļ�
   _pMemory = (TByte*)MapViewOfFile(_hMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
   if(NULL == _pMemory){
      TUint32 errorCode = GetLastError();
      MO_ERROR(TC("Connect share memory failure. (handle=%d, memory=0x%08X, error=%d)"), _hMemory, _pMemory, errorCode);
      MO_PFATAL(MapViewOfFile);
      return EFalse;
   }
   MO_INFO(TC("Connect share memory. (handle=%d, memory=0x%08X)"), _hMemory, _pMemory);
#endif // _MO_WINDOWS
   //............................................................
#ifdef _MO_LINUX
   _pMemory = (TByte*)RShareMemory::Connect(_key, ETrue);
#endif // _MO_LINUX
   //............................................................
   // �����������Ϣ
   _linked = ETrue;
   _created = EFalse;
   _position = 0;
   _capacity = info.size;
   return ETrue;
}

////============================================================
//// <T>���Դ���һ�鹲���ڴ档</T>
////
//// @param key �����ڴ��ֵ
//// @param capacity �ڴ��С
//// @return �Ƿ�ɹ�
////============================================================
//TBool FShareMemory::TryCreate(TShareKey key, TSize capacity){
//   _linked = ETrue;
//   _key = key;
//   _pMemory = (TByte*)RShareMemory::TryCreate(key, capacity, _created);
//   _capacity = capacity;
//   _position = 0;
//   return ETrue;
//}
//
////============================================================
//// <T>��д��ʽ����һ�鹲���ڴ档</T>
////
//// @param key �����ڴ��ֵ
//// @return �Ƿ�ɹ�
////============================================================
//TBool FShareMemory::Link(TShareKey key){
//   // ��������
//   SShareMemoryInfo info;
//   RType<SShareMemoryInfo>::Clear(&info);
//   // �����������Ϣ
//   _linked = ETrue;
//   _key = key;
//   _pMemory = (TByte*)RShareMemory::Connect(key, EFalse);
//   _created = EFalse;
//   _capacity = info.size;
//   _position = 0;
//   return ETrue;
//}

//============================================================
// <T>�ӹ����ڴ����ռ�һ��ָ����С���ڴ档</T>
//
// @param size �ڴ��С
// @return �����ڴ�
//============================================================
TAny* FShareMemory::Alloc(TSize size){
   TByte* pMemory = _pMemory + _position;
   _position += size;
   return pMemory;
}

//============================================================
// <T>�ӹ����ڴ�������һ��ָ����С���ڴ档</T>
//
// @param size �ڴ��С
// @return �Ƿ�ɹ�
//============================================================
TBool FShareMemory::Skip(TSize size){
   _position += size;
   return ETrue;
}

//============================================================
// <T>�ڵ�ǰ�����ڴ���ڣ������µĹ����ڴ�Ρ�</T>
//
// @param size ��С
// @return �����ڴ��
//============================================================
TShareSegment FShareMemory::CreateSegment(TSize size){
   TShareSegment segment;
   segment.Initialize(_pMemory + _position, size, _created);
   _position += size;
   return segment;
}

//============================================================
// <T>�ͷ�һ�鹲���ڴ����</T>
//
// @return �Ƿ�ɹ�
//============================================================
TBool FShareMemory::Free(){
   // ��ʼ������
   _key = 0;
   _created = EFalse;
   _capacity = 0;
   _position = 0;
   // �ͷŹ����ڴ�
   if(NULL != _pMemory){
      RShareMemory::Free(_key);
      _pMemory = NULL;
      return ETrue;
   }
   return EFalse;
}

MO_NAMESPACE_END
