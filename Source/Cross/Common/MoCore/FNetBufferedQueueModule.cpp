#include "MoCrNetPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ӷ��󣬲���Ҫ������</T>
// <P>�Ժ�ʹ��ǰ��Ҫ������������ܵ���С��</P>
//
// @return ��ǰʵ��ָ��
//============================================================
FNetBufferedQueueModule::FNetBufferedQueueModule(){
   _name = TC("Module.NetQueue");
   // ��ʼ�����ж���
   _pStorage = MO_CREATE(FSharedNetQueueStorage);
}

//============================================================
// <T>�������Ӷ���</T>
//============================================================
FNetBufferedQueueModule::~FNetBufferedQueueModule(){
   MO_DELETE(_pStorage);
}

//============================================================
// <T>����������Ϣ��</T>
//
// @return ������
//============================================================
TResult FNetBufferedQueueModule::OnLoadConfig(FXmlNode* pConfig){
   return _pStorage->LoadConfig(pConfig);
}

//============================================================
// <T>��ô洢����</T>
//
// @return �ն��е�ָ�롣
//============================================================
FSharedNetQueueStorage* FNetBufferedQueueModule::Storage(){
   return _pStorage;
}

//============================================================
// <T>��ùܵ����ӡ�</T>
//
// @return �ն��е�ָ�롣
//============================================================
FNetBufferedQueueConnection* FNetBufferedQueueModule::Connection(){
   return _pStorage->Connection();
}

MO_NAMESPACE_END
