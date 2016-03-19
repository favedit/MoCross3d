#include "MoCrFeature.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FFeatureConsole, FConsole);

//============================================================
// <T>���칦�ܿ���̨��</T>
//============================================================
FFeatureConsole::FFeatureConsole(){
   _name = TC("Feature.Console");
   _pClasses = MO_CREATE(FClassCollection);
}

//============================================================
// <T>�������ܿ���̨��</T>
//============================================================
FFeatureConsole::~FFeatureConsole(){
   MO_DELETE(_pClasses);
}

//============================================================
// <T>ע��һ�����ܡ�</T>
//
// @param pClass ������
// @return ������
//============================================================
TResult FFeatureConsole::Register(FClass* pClass){
   MO_CHECK(pClass, return ENull);
   _pClasses->Push(pClass);
   return ESuccess;
}

//============================================================
// <T>ע��һ�����ܡ�</T>
//
// @param pClass ������
// @return ������
//============================================================
TResult FFeatureConsole::Unregister(FClass* pClass){
   MO_CHECK(pClass, return ENull);
   _pClasses->Remove(pClass);
   return ESuccess;
}

//============================================================
// <T>���������</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Construct(){
   TResult resultCd = FConsole::Construct();
   // ���칦�ܼ���
   TInt count = _pClasses->Count();
   for(TInt n = 0; n < count; n++){
      FClass* pClass = _pClasses->Get(n);
      FFeature* pFeature =  pClass->InstanceInheritCreate<FFeature>();
      pFeature->Construct();
      _features.Push(pFeature);
   }
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Startup(){
   TInt count = _features.Count();
   for(TInt n = 0; n < count ; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Startup();
   }
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Suspend(){
   TInt count = _features.Count();
   for(TInt n = 0; n < count ; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Suspend();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Resume(){
   TInt count = _features.Count();
   for(TInt n = 0; n < count ; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Resume();
   }
   return ESuccess;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Shutdown(){
   TInt count = _features.Count();
   for(TInt n = 0; n < count ; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Shutdown();
   }
   return ESuccess;
}

//============================================================
// <T>�ͷ������</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Dispose(){
   TResult resultCd = FConsole::Dispose();
   // �������ܼ���
   TInt count = _features.Count();
   for(TInt n = 0; n < count; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Dispose();
   }
   _features.Clear();
   return resultCd;
}

MO_NAMESPACE_END
