#include "MoCmData.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ݼ�����Ϣ��</T>
//============================================================
FDatasetMeta::FDatasetMeta(){
   _logicCode = 0;
   MO_CLEAR(_pLogicName);
   MO_CLEAR(_pDataName);
   MO_CLEAR(_pDataFields);
   // ���ü�����
   Reset();
}

//============================================================
// <T>�������ݼ�����Ϣ��</T>
//============================================================
FDatasetMeta::~FDatasetMeta(){
}

//============================================================
// <T>��������������̡߳�</T>
//
// @return ������
//============================================================
TBool FDatasetMeta::Setup(){
   return ESuccess;
}

//============================================================
// <T>�����߼���</T>
//============================================================
void FDatasetMeta::Process(ESqlProcess processCd){
   _counters[processCd]++;
}

//============================================================
// <T>���ô���</T>
//============================================================
void FDatasetMeta::Reset(){
   for(TInt n = 0; n < ESqlProcess_Count; n++){
      _counters[n] = 0;
   }
}

//============================================================
// <T>����ڲ���Ϣ��</T>
//
// @param pDump ��Ϣ�ַ���
//============================================================
void FDatasetMeta::Dump(MString* pDump){
   TInt64 findTotal = _counters[ESqlProcess_Find];
   TInt64 fetchTotal = _counters[ESqlProcess_Fetch];
   TInt64 insertTotal = _counters[ESqlProcess_Insert];
   TInt64 updateTotal = _counters[ESqlProcess_Update];
   TInt64 deleteTotal = _counters[ESqlProcess_Delete];
   pDump->AppendFormat(TC("[G=%8lld, F=%8lld, I=%8lld, U=%8lld, D=%8lld]"),
         findTotal, fetchTotal, insertTotal, updateTotal, deleteTotal);
}

MO_NAMESPACE_END
