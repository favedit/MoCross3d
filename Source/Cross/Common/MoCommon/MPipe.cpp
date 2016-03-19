#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
MPipe::MPipe(){
}

//============================================================
MPipe::~MPipe(){
}

//============================================================
// <T>�жϹܵ��Ƿ�Ϊ�ա�</T>
//
// @return �Ƿ�Ϊ��
//============================================================
TBool MPipe::IsEmpty(){
   SPipeAtom atom = Atom();
   return (atom.length > 0);
}

//============================================================
// <T>��ùܵ��Ա�ռ�ó��ȡ�</T>
//
// @return ��ռ�ó��ȡ�
//============================================================
TInt MPipe::Length(){
   SPipeAtom atom = Atom();
   return atom.length;
}

//============================================================
// <T>��ùܵ���ʣ��ĳ��ȡ�</T>
//
// @return ʣ��ĳ���
//============================================================
TInt MPipe::Reamin(){
   SPipeAtom atom = Atom();
   return atom.capacity - atom.length - MoPipeReserveLength;
}


//============================================================
// <T>��ùܵ���ʣ�������������ȡ�</T>
//
// @return ʣ��ĳ���
//============================================================
TInt MPipe::FollowReamin(){
   SPipeAtom atom = Atom();
   TInt followRemain = 0;
   if(atom.first < atom.last){
      // �����ȡ���� [---F===L----]
      followRemain = atom.capacity - atom.last - MoPipeReserveLength;
   }else{
      // �����ȡ���� [===L---F====]
      followRemain = atom.first - atom.last - MoPipeReserveLength;
   }
   return followRemain;
}

//============================================================
TByte* MPipe::FollowMemory(){
   SPipeAtom atom = Atom();
   return atom.memoryPtr + atom.last;
}

//============================================================
// <T>�������ܵ���д�����ݡ�</T>
//
// @param size ��С
// @return ������
//============================================================
TBool MPipe::FollowWrite(TInt size){
   SPipeAtom atom = Atom();
   atom.SetLast(atom.last + size);
   return ETrue;
}

//============================================================
// <T>�������ܵ��ж������ݡ�</T>
//
// @param size ��С
// @return ������
//============================================================
TBool MPipe::FollowRead(TInt size){
   SPipeAtom atom = Atom();
   atom.SetFirst(atom.first + size);
   return ETrue;
}

//============================================================
// <T>���Խ�һ��������ʰȡ�����ݻ�������</T>
// <P>��Ӱ���ڲ����ݿ�ʼ�ͽ���λ�á�</P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return ʰȡ�����ݵĳ���
//============================================================
TInt MPipe::Peek(TAny* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      return 0;
   }
   // ��ȡ����
   SPipeAtom atom = Atom();
   // �ж��Ƿ���Զ���
   TUint32 peeked = MO_LIB_MIN(size, atom.length);
   // ��ȡ����
   if(atom.first < atom.last){
      // �����ȡ���� [---F===L----]
      memcpy(pData, atom.memoryPtr + atom.first, peeked);
   }else{
      // �����ȡ���� [===L---F====]
      TUint32 remain = atom.capacity - atom.first;
      if(peeked <= remain){
         memcpy(pData, atom.memoryPtr + atom.first, peeked);
      }else{
         memcpy(pData, atom.memoryPtr + atom.first, remain);
         memcpy((TByte*)pData + remain, atom.memoryPtr, peeked - remain);
      }
   }
   return peeked;
}

//============================================================
// <T>���ܵ�д��ָ���������ݡ�</T>
// <P>����ܵ���д��Ĳ��ֲ��㣬��ֻд���ܹ�д�������ݡ�</P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return ʵ��д�����ݳ���
//============================================================
TInt MPipe::Write(TAnyC* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      return 0;
   }
   // ��ȡ����
   SPipeAtom atom = Atom();
   // �ж��Ƿ����д��
   TInt position = 0;
   TInt remainLength = atom.capacity - atom.length - MoPipeReserveLength;
   TInt writted = MO_LIB_MIN(remainLength, size);
   // д������
   if(atom.first <= atom.last){
      // ����д������ [---F===L----]
      TInt remain = atom.capacity - atom.last;
      // д������
      if(writted < remain){
         position = atom.last + writted;
         memcpy(atom.memoryPtr + atom.last, pData, writted);
      }else if(writted == remain){
         memcpy(atom.memoryPtr + atom.last, pData, writted);
      }else{
         position = writted - remain;
         memcpy(atom.memoryPtr + atom.last, pData, remain);
         memcpy(atom.memoryPtr, (TByte*)pData + remain, position);
      }
   }else{
      // ����д������ [===L---F====]
      position = atom.last + writted;
      memcpy(atom.memoryPtr + atom.last, pData, writted);
   }
   // ���ý�βλ��
   atom.SetLast(position);
   return writted;
}

//============================================================
// <T>�ӹܵ���ȡָ�����ȵ����ݡ�</T>
// <P>����ɶ����ݲ��㣬��ֻ��ȡ�ܹ���ȡ�������ݡ�</P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return ʵ��ȡ�����ݳ��ȡ�
//============================================================
TInt MPipe::Read(TAny* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      return 0;
   }
   // ��ȡ����
   SPipeAtom atom = Atom();
   // �ж��Ƿ���Զ���
   TInt position = 0;
   TInt readed = MO_LIB_MIN(size, atom.length);
   // ��ȡ����
   if(atom.first < atom.last){
      // �����ȡ���� [---F===L----]
      position = atom.first + readed;
      memcpy(pData, atom.memoryPtr + atom.first, readed);
   }else{
      // �����ȡ���� [===L---F====]
      TInt remain = atom.capacity - atom.first;
      if(readed < remain){
         position = atom.first + readed;
         memcpy(pData, atom.memoryPtr + atom.first, readed);
      }else if(readed == remain){
         memcpy(pData, atom.memoryPtr + atom.first, readed);
      }else{
         position = readed - remain;
         memcpy(pData, atom.memoryPtr + atom.first, remain);
         memcpy((TByte*)pData + remain, atom.memoryPtr, position);
      }
   }
   // ���ÿ�ʼλ��
   atom.SetFirst(position);
   return readed;
}

//============================================================
// <T>���Խ�һ��������ʰȡ�����ݻ�������</T>
// <P>��Ӱ���ڲ����ݿ�ʼ�ͽ���λ�á�</P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return ʰȡ�Ƿ�ɹ�
//============================================================
TBool MPipe::TryPeek(TAny* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      return ETrue;
   }
   // _locker.Enter();
   // ��ȡ����
   SPipeAtom atom = Atom();
   // �ж��Ƿ���Զ���
   if(size > atom.length){
      return EFalse;
   }
   // ��ȡ����
   if(atom.first < atom.last){
      // �����ȡ���� [---F===L----]
      memcpy(pData, atom.memoryPtr + atom.first, size);
   }else{
      // �����ȡ���� [===L---F====]
      TInt remain = atom.capacity - atom.first;
      if(size <= remain){
         memcpy(pData, atom.memoryPtr + atom.first, size);
      }else{
         memcpy(pData, atom.memoryPtr + atom.first, remain);
         memcpy((TByte*)pData + remain, atom.memoryPtr, size - remain);
      }
   }
   // _locker.Leave();
   return ETrue;
}

//============================================================
// <T>���Խ�һ��������д�����ݻ�������</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return д���Ƿ�ɹ�
//============================================================
TBool MPipe::TryWrite(TAnyC* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      return ETrue;
   }
   // _locker.Enter();
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
      // д������
      if(size < remain){
         position = atom.last + size;
         memcpy(atom.memoryPtr + atom.last, pData, size);
      }else if(size == remain){
         memcpy(atom.memoryPtr + atom.last, pData, size);
      }else{
         position = size - remain;
         memcpy(atom.memoryPtr + atom.last, pData, remain);
         memcpy(atom.memoryPtr, (TByte*)pData + remain, position);
      }
   }else{
      // ����д������ [===L---F====]
      position = atom.last + size;
      memcpy(atom.memoryPtr + atom.last, pData, size);
   }
   // ���ý�β
   atom.SetLast(position);
   // _locker.Leave();
   return ETrue;
}

//============================================================
// <T>���Խ�һ�������ݶ�ȡ���ݻ�������</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return ��ȡ�Ƿ�ɹ�
//============================================================
TBool MPipe::TryRead(TAny* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      return ETrue;
   }
   // _locker.Enter();
   // ��ȡ����
   SPipeAtom atom = Atom();
   // �ж��Ƿ���Զ���
   if(size > atom.length){
      return EFalse;
   }
   // ��ȡ����
   TInt position = 0;
   if(atom.first < atom.last){
      // �����ȡ���� [---F===L----]
      position = atom.first + size;
      memcpy(pData, atom.memoryPtr + atom.first, size);
   }else{
      // �����ȡ���� [===L---F====]
      TInt remain = atom.capacity - atom.first;
      if(size < remain){
         position = atom.first + size;
         memcpy(pData, atom.memoryPtr + atom.first, size);
      }else if(size == remain){
         memcpy(pData, atom.memoryPtr + atom.first, size);
      }else{
         position = size - remain;
         memcpy(pData, atom.memoryPtr + atom.first, remain);
         memcpy((TByte*)pData + remain, atom.memoryPtr, position);
      }
   }
   // ���ý�β
   atom.SetFirst(position);
   // _locker.Leave();
   return ETrue;
}

//============================================================
// <T>���ùܵ���</T>
//
// @return ������
//============================================================
TBool MPipe::Reset(){
   SPipeAtom atom = Atom();
   atom.Set(0, 0);
   return ETrue;
}

//============================================================
// <T>�رչܵ���</T>
//
// @return ������
//============================================================
TBool MPipe::Close(){
   return ETrue;
}

//============================================================
void MPipe::Track(){
   SPipeAtom atom = Atom();
   MO_DEBUG(TC("Track pipe. (memory=0x%08X, capacity=%d, length=%d, first=%d, last=%d)"),
         atom.memoryPtr, atom.capacity, atom.length, atom.first, atom.last);
}

MO_NAMESPACE_END
