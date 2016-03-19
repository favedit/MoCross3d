#include "MoMtGeom.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���л��������ݵ��������</T>
// 
// @param pOutput �����
// @return ������
//============================================================
TResult SDoubleRectangle::Serialize(IDataOutput* pOutput){
   MO_CHECK(pOutput, return ENull);
   pOutput->WriteDouble(left);
   pOutput->WriteDouble(top);
   pOutput->WriteDouble(width);
   pOutput->WriteDouble(height);
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
// 
// @param pInput ������
// @return ������
//============================================================
TResult SDoubleRectangle::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   left = pInput->ReadDouble();
   top = pInput->ReadDouble();
   width = pInput->ReadDouble();
   height = pInput->ReadDouble();
   return ESuccess;
}

MO_NAMESPACE_END
