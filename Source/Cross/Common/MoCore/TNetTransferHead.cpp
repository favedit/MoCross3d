#include "MoCrNetMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����Ϣ���ơ�</T>
//
// @return ��Ϣ����
//============================================================
TNetTransferHead::TNetTransferHead(){
   RType<SNetTransferHead>::Clear(&_data);
}

//============================================================
void TNetTransferHead::Assign(TNetTransferHead& head){
   _data = head.Data();
}

//============================================================
// <T>���л��ڲ����ݵ���������</T>
//
// @param pMessage ��Ϣ����
//============================================================
TInt TNetTransferHead::Serialize(TAny* pMemory){
   memcpy(pMemory, &_data, sizeof(SNetTransferHead));
   return sizeof(SNetTransferHead);
}

//============================================================
// <T>�����л����������ڲ����ݡ�</T>
//
// @param pMessage ��Ϣ����
//============================================================
TInt TNetTransferHead::Unserialize(TAnyC* pMemory){
   memcpy(&_data, pMemory, sizeof(SNetTransferHead));
   return sizeof(SNetTransferHead);
}

//============================================================
// <T>�����ݴ����Ϊһ�������ַ�����</T>
//
// @param pPack ����ַ���
// @return ������
//============================================================
TBool TNetTransferHead::Pack(MPack* pPack){
   MO_FATAL_UNSUPPORT();
   return EFalse;
}

//============================================================
// <T>��һ������ַ������Ϊ���ݡ�</T>
//
// @param pPack ����ַ���
// @return ������
//============================================================
TBool TNetTransferHead::Unpack(MPack* pPack){
   MO_FATAL_UNSUPPORT();
   return EFalse;
}

//============================================================
TCharC* TNetTransferHead::Dump(TChar* pDump, TSize length){
   return pDump;
}

MO_NAMESPACE_END
