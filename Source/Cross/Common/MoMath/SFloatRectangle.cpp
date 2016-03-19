#include "MoMtGeom.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���л��������ݵ��������</T>
// 
// @param pOutput �����
// @return ������
//============================================================
TResult SFloatRectangle::Serialize(IDataOutput* pOutput){
   MO_CHECK(pOutput, return ENull);
   pOutput->WriteFloat(left);
   pOutput->WriteFloat(top);
   pOutput->WriteFloat(width);
   pOutput->WriteFloat(height);
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
// 
// @param pInput ������
// @return ������
//============================================================
TResult SFloatRectangle::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   left = pInput->ReadFloat();
   top = pInput->ReadFloat();
   width = pInput->ReadFloat();
   height = pInput->ReadFloat();
   return ESuccess;
}

MO_NAMESPACE_END
