#include "MoCmPipe.h"
#include "MoCmSingleton.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�޲������캯����</T>
//
// @return ��ǰʵ��ָ�� ָ�롣
//============================================================
FSharedPipe::FSharedPipe(){
   _capacity = 0;
   MO_CLEAR(_gInfo);
   MO_CLEAR(_gData);
}

//============================================================
// <T>���������캯��</T>
//
// @param capacity �ܵ�������
// @return ��ǰʵ��ָ�롣
//============================================================
FSharedPipe::FSharedPipe(TSize capacity){
   _capacity = capacity;
   MO_CLEAR(_gInfo);
   MO_CLEAR(_gData);
}

//============================================================
// <T>���㹲��ܵ������ڴ�ռ䡣</T>
//
// @return ����ռ䡣
//============================================================
TSize FSharedPipe::CalculateCapacity(TSize capacity){
   return sizeof(SPipeInfo) + capacity;
}

//============================================================
TSize FSharedPipe::Capacity(){
   return _capacity;
}

//============================================================
// <T>����FSharedPipe�����ڴ�ռ䡣</T>
//
// @param capacity ������ݵ��ڴ泤�ȡ�
//============================================================
void FSharedPipe::SetCapacity(TSize capacity){
   _capacity = capacity;
}

//============================================================
// <T>��ʼ�������ڴ档</T>
//============================================================
void FSharedPipe::OnSharedInitialize(){
   _gInfo->capacity = _capacity;
   _gInfo->first = 0;
   _gInfo->last = 0;
}

//============================================================
// <T>���乲���ڴ档</T>
//============================================================
void FSharedPipe::OnSharedLink(TShareSegment& segment){
   // �����Ϣ����
   _gInfo = segment.TypeAlloc<SPipeInfo>();
   // ����ڴ沿��
   _gData = (TByte*)segment.Alloc(_capacity);
}

//============================================================
// <T>���㹲��ܵ������ڴ�ռ䡣</T>
//
// @return ����ռ䡣
//============================================================
TSize FSharedPipe::SharedCapacity(){
   return CalculateCapacity(_capacity);
}

//============================================================
// <T>��ü��㹲��ܵ������ڴ�ռ䡣</T>
//
// @return ����ռ䡣
//============================================================
SPipeInfo* FSharedPipe::Info(){
   return _gInfo;
}

//============================================================
// <T>��ȡ����ܵ��ĳ�Ա��</T>
//
// @param pMemory ���ݵĴ���ڴ�
// @param capacity ������ݵ��ڴ泤�ȡ�
// @param length �Ѵ����ݳ���
// @param first ��λ��
// @param last дλ��
// @return �޷���
//============================================================
SPipeAtom FSharedPipe::Atom(){
   SPipeAtom atom;
   atom.infoPtr = _gInfo;
   atom.memoryPtr = _gData;
   atom.Fetch();
   return atom;
}

//============================================================
// <T>��ʹ�ù����ڴ洴������</T>
//
// @return �Ƿ�Ϊ��
//============================================================
TBool FSharedPipe::Create(){
   // �����ڴ�
   MO_ASSERT(_capacity > 0);
   TSize capacity = SharedCapacity();
   MO_ASSERT(capacity > 0);
   TByte* pMemory = MO_TYPES_ALLOC(TByte, capacity);
   RTypes<TByte>::Clear(pMemory, capacity);
   // ���������ڴ�
   TShareSegment segment(pMemory, capacity, ETrue);
   segment.SharedLink(this);
   return ETrue;
}

//============================================================
// <T>�жϹܵ��Ƿ�Ϊ�ա�</T>
//
// @return �Ƿ�Ϊ��
//============================================================
TBool FSharedPipe::IsEmpty(){
   SPipeAtom atom = Atom();
   return atom.IsEmpty();
}

//============================================================
// <T>��ùܵ��Ա�ռ�ó��ȡ�</T>
//
// @return ��ռ�ó��ȡ�
//============================================================
TInt FSharedPipe::Length(){
   SPipeAtom atom = Atom();
   return atom.length;
}

//============================================================
// <T>��ùܵ���ʣ��ĳ��ȡ�</T>
//
// @return ʣ��ĳ���
//============================================================
TInt FSharedPipe::Reamin(){
   SPipeAtom atom = Atom();
   return atom.Reamin();
}

//============================================================
// <T>����FSharePipe����</T>
//
// @return TBool������ʾ��ʼ���ɹ���
//============================================================
TBool FSharedPipe::Reset(){
   SPipeAtom atom = Atom();
   atom.Clear();
   return ETrue;
}

MO_NAMESPACE_END
