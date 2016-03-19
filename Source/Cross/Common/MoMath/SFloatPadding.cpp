#include "MoMtGeom.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���л��������ݵ��������</T>
// 
// @param pOutput �����
// @return ������
//============================================================
TResult SFloatPadding::Serialize(IDataOutput* pOutput){
   MO_CHECK(pOutput, return ENull);
   pOutput->WriteFloat(left);
   pOutput->WriteFloat(top);
   pOutput->WriteFloat(right);
   pOutput->WriteFloat(bottom);
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
// 
// @param pInput ������
// @return ������
//============================================================
TResult SFloatPadding::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   left = pInput->ReadFloat();
   top = pInput->ReadFloat();
   right = pInput->ReadFloat();
   bottom = pInput->ReadFloat();
   return ESuccess;
}

MO_NAMESPACE_END
