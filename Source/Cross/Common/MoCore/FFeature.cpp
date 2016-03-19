#include "MoCrFeature.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FFeature, FConsole);

//============================================================
// <T>���칦�ܡ�</T>
//============================================================
FFeature::FFeature(){
   _name = TC("Feature");
}

//============================================================
// <T>�������ܡ�</T>
//============================================================
FFeature::~FFeature(){
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeature::Startup(){
   MO_INFO(TC("Feature startup. (name=%s)"), (TCharC*)_name);
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FFeature::Suspend(){
   MO_INFO(TC("Feature suspend. (name=%s)"), (TCharC*)_name);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeature::Resume(){
   MO_INFO(TC("Feature resume. (name=%s)"), (TCharC*)_name);
   return ESuccess;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FFeature::Shutdown(){
   MO_INFO(TC("Feature shutdown. (name=%s)"), (TCharC*)_name);
   return ESuccess;
}

MO_NAMESPACE_END
