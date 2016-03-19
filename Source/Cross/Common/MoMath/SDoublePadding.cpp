#include "MoMtGeom.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���л��������ݵ��������</T>
// 
// @param pOutput �����
// @return ������
//============================================================
TResult SDoublePadding::Serialize(IDataOutput* pOutput){
   MO_CHECK(pOutput, return ENull);
   pOutput->WriteDouble(left);
   pOutput->WriteDouble(top);
   pOutput->WriteDouble(right);
   pOutput->WriteDouble(bottom);
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
// 
// @param pInput ������
// @return ������
//============================================================
TResult SDoublePadding::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   left = pInput->ReadDouble();
   top = pInput->ReadDouble();
   right = pInput->ReadDouble();
   bottom = pInput->ReadDouble();
   return ESuccess;
}

MO_NAMESPACE_END
