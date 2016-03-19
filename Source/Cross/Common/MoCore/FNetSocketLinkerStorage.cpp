#include "MoCrNetMessage.h"
#include "MoCrNetLinker.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ϣ�ܵ������һ����Ϣ��</T>
//
// @return ִ�н��
//============================================================
FNetSocketLinkerStorage::FNetSocketLinkerStorage(){
}

//============================================================
// <T>����Ϣ�ܵ������һ����Ϣ��</T>
//
// @return ִ�н��
//============================================================
FNetSocketLinkerStorage::~FNetSocketLinkerStorage(){
}

//============================================================
// <T>�����������������������</T>
//
// @param index ����
// @return ����������
//============================================================
SNetSocketLinker* FNetSocketLinkerStorage::Get(TInt index){
   MO_ASSERT_RANGE(index, 0, MO_NET_SOCKET_MAX_COUNT);
   return &_linkers[index];
}

//============================================================
// <T>����ָ��������������������</T>
//
// @param index ����
// @return ����������
//============================================================
SNetSocketLinker* FNetSocketLinkerStorage::Link(TInt index){
   // �������������
   MO_ASSERT_RANGE(index, 0, MO_NET_SOCKET_MAX_COUNT);
   SNetSocketLinker& linker = _linkers[index];
   // ��������״̬
   linker.SetConnected(ETrue);
   return &linker;
}

//============================================================
// <T>����ָ����������������������</T>
//
// @param pTransfer �������
// @return ����������
//============================================================
SNetSocketLinker* FNetSocketLinkerStorage::LinkTransfer(TNetTransfer* pTransfer){
   // �������������
   MO_ASSERT(pTransfer);
   TInt index = pTransfer->TransferHead().Socket().Index();
   // ���ӹ���
   return Link(index);
}

//============================================================
// <T>�Ͽ�ָ���˿ڵ�������������</T>
//
// @param port �˿�
// @return ����������
//============================================================
SNetSocketLinker* FNetSocketLinkerStorage::Unlink(TInt index){
   // �������������
   MO_ASSERT_RANGE(index, 0, MO_NET_SOCKET_MAX_COUNT);
   SNetSocketLinker& linker = _linkers[index];
   // ��������״̬
   linker.SetConnected(EFalse);
   return &linker;
}

//============================================================
// <T>�Ͽ�ָ����������������������</T>
//
// @param pTransfer �������
// @return ����������
//============================================================
SNetSocketLinker* FNetSocketLinkerStorage::UnlinkTransfer(TNetTransfer* pTransfer){
   // �������λ��
   MO_ASSERT(pTransfer);
   TInt index = pTransfer->TransferHead().Socket().Index();
   // �Ͽ�����
   return Unlink(index);
}

MO_NAMESPACE_END
