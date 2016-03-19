#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ݶ��е�ʵ����</T>
//============================================================
FQueue::FQueue(){
}

//============================================================
// <T>�������ݶ��е�ʵ����</T>
//
// @param capacity ��������
//============================================================
FQueue::FQueue(TSize capacity) : FPipe(capacity){
}

//============================================================
// <T>�������ݶ��е�ʵ����</T>
//
// @param pMemory �����ڴ�
// @param capacity ��������
//============================================================
FQueue::FQueue(TByte* pMemory, TSize capacity) : FPipe(pMemory, capacity){
}

//============================================================
// <T>�������ݶ��е�ʵ����</T>
//============================================================
FQueue::~FQueue(){
}

//============================================================
// <T>��һ��������Ϣд��ܵ���</T>
// <P>��д�����ݳ���(4byte)����д���������ݡ�
//    �������ݿ��ܱ��ֳ����˷���ܵ���β�����ײ���</P>
//    ÿ�ν�βλ�õ�ƫ��ֻ��Ϊ4byte�ı���(sizeof(TUint32))��
// </P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FQueue::Push(TAnyC* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      return ETrue;
   }
   // ��ȡ����
   SPipeAtom atom = Atom();
   // �ж��Ƿ����д��
   if((atom.capacity - atom.length) < (size + MoPipeReserveLength)){
      return EFalse;
   }
   // д������
   TInt position = 0;
   if(atom.first <= atom.last){
      // ����д������ [---F===L----]
      TInt remain = atom.capacity - atom.last;
      MO_ASSERT(remain >= (TInt)sizeof(TUint32));
      *(TUint32*)(atom.memoryPtr + atom.last) = size;
      remain -= sizeof(TUint32);
      TByte* pLast = atom.memoryPtr + atom.last + sizeof(TUint32);
      // д������
      if(size < remain){
         memcpy(pLast, pData, size);
         position = atom.last + sizeof(TUint32) + size;
      }else if(size == remain){
         memcpy(pLast, pData, size);
         position = 0;
      }else{
         memcpy(pLast, pData, remain);
         memcpy(atom.memoryPtr, (TByte*)pData + remain, size - remain);
         position = size - remain;
      }
   }else{
      // ����д������ [===L---F====]
      TByte* pWrite = atom.memoryPtr + atom.last;
      *(TUint32*)pWrite = size;
      pWrite += sizeof(TUint32);
      // д������
      memcpy(pWrite, pData, size);
      position = atom.last + sizeof(TUint32) + size;
   }
   // ���ý�βλ��
   TInt mod = position % sizeof(TUint32);
   if(0 != mod){
      position += sizeof(TUint32) - mod;
   }
   if(position == atom.capacity){
      position = 0;
   }
   atom.SetLast(position);
   return ETrue;
}

//============================================================
// <T>�ӹܵ��ڵ���һ����������Ϣ��</T>
// <P>�ȶ������ݳ���(4byte)���ٶ����������ݡ�
//    �������ݿ��ܱ��ֳ����˷���ܵ���β�����ײ���</P>
//    ÿ�ο�ʼλ�õ�ƫ��ֻ��Ϊ4byte�ı���(sizeof(TUint32))��
// </P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч����
//============================================================
TInt FQueue::Pop(TAny* pData, TInt capacity){
   // ������
   MO_ASSERT(pData);
   MO_ASSERT(capacity > 0);
   // ��ȡ����
   SPipeAtom atom = Atom();
   // �ж��Ƿ���Զ���
   if(atom.length <= (TInt)sizeof(TUint32)){
      return 0;
   }
   TByte* pRead = atom.memoryPtr + atom.first;
   TInt size = *(TUint32*)pRead;
   MO_ASSERT(size > 0);
   MO_ASSERT(size <= atom.capacity);
   MO_ASSERT(size <= atom.length);
   pRead += sizeof(TUint32);
   // ��ȡ����
   TInt position = 0;
   if(atom.first < atom.last){
      // �����ȡ���� [---F===L----]
      memcpy(pData, pRead, size);
      position = atom.first + sizeof(TUint32) + size;
   }else{
      // �����ȡ���� [===L---F====]
      TInt remain = atom.capacity - atom.first - sizeof(TUint32);
      if(size < remain){
         memcpy(pData, pRead, size);
         position = atom.first + sizeof(TUint32) + size;
      }else if(size == remain){
         memcpy(pData, pRead, size);
         position = 0;
      }else{
         memcpy(pData, pRead, remain);
         memcpy((TByte*)pData + remain, atom.memoryPtr, size - remain);
         position = size - remain;
      }
   }
   // ���ÿ�ʼλ��
   TInt mod = position % sizeof(TUint32);
   if(0 != mod){
      position += sizeof(TUint32) - mod;
   }
   if(position == atom.capacity){
      position = 0;
   }
   atom.SetFirst(position);
   return size;
}

MO_NAMESPACE_END
