#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���칲����е�ʵ����</T>
//============================================================
FSharedQueue::FSharedQueue(){
}

//============================================================
// <T>���칲����е�ʵ����</T>
//
// @param capacity ��������
//============================================================
FSharedQueue::FSharedQueue(TSize capacity) : FSharedPipe(capacity){
   if(0 != (capacity % 4)){
      MO_FATAL(TC("Queue size is must mod 4. (capacity=%d)"), capacity);
   }
}

//============================================================
// <T>������ùܵ���ʣ�������������ȡ�</T>
//
// @return ʣ��ĳ���
//============================================================
TBool FSharedQueue::FollowPush(TInt size){
   SPipeAtom atom = Atom();
   // ���ý�βλ��
   TInt last = atom.last + sizeof(TInt32) + size;
   TInt mod = atom.last % sizeof(TInt32);
   if(0 != mod){
      last += sizeof(TInt32) - mod;
   }
   if(last == atom.capacity){
      last = 0;
   }
   atom.SetLast(last);
   return ETrue;
}

//============================================================
// <T>��һ��������Ϣд��ܵ���</T>
// <P>��д�����ݳ���(4byte)����д���������ݡ�
//    �������ݿ��ܱ��ֳ����˷���ܵ���β�����ײ���</P>
//    ÿ�ν�βλ�õ�ƫ��ֻ��Ϊ4byte�ı���(sizeof(TInt32))��
// </P>
//
// @param pData ����ָ��
// @param size ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FSharedQueue::Push(TAnyC* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      MO_FATAL(TC("Push data is empty. (data=0x%08X, size=%d)"), pData, size);
   }
   // ��ȡ�ܵ�����
   SPipeAtom atom = Atom();
   // �ж��Ƿ�ܵ�����
   TInt freeLength = atom.Reamin();
   if(size > freeLength){
      MO_FATAL(TC("Current queue is full. (data=0x%08X, total=%d, length=%d, first=%d, last=%d, size=%d)"), atom.memoryPtr, atom.capacity, atom.length, atom.first, atom.last, size);
   }
   // д������
   TInt position = 0;
   TInt block = sizeof(TInt32);
   TByte* pRead = (TByte*)pData;
   TByte* pWrite = atom.memoryPtr + atom.last;
   if(atom.first <= atom.last){
      // ����д������ [--F====L--]
      //               0123456789
      TInt remain = atom.capacity - atom.last;
      if(remain < block){
         MO_FATAL(TC("Remain free data is too small. (remain=%d)"), remain);
      }
      *(TInt32*)pWrite = (TInt32)size;
      remain -= block;
      pWrite += block;
      // д������
      if(size < remain){
         position = atom.last + block + size;
         memcpy(pWrite, pRead, size);
      }else if(size == remain){
         position = 0;
         memcpy(pWrite, pRead, size);
      }else if(size > remain){
         if(remain > 0){
            position = size - remain;
            memcpy(pWrite, pRead, remain);
            memcpy(atom.memoryPtr, pRead + remain, position);
         }else if(remain == 0){
            position = size;
            memcpy(atom.memoryPtr, pRead, size);
         }else{
            MO_FATAL(TC("Remain free length is invalid. (remain=%d)"), remain);
         }
      }
   }else{
      // ����д������ [==L----F==]
      //               0123456789
      *(TInt32*)pWrite = (TInt32)size;
      position = atom.last + block + size;
      memcpy(pWrite + block, pRead, size);
   }
   // ���ý�βλ��
   TInt mod = position % block;
   if(0 != mod){
      position += block - mod;
   }
   if(position == atom.capacity){
      position = 0;
   }
   atom.SetLast(position);
   return ETrue;
}

//============================================================
// <T>��һ��������Ϣд��ܵ���</T>
// <P>��д�����ݳ���(4byte)����д���������ݡ�
//    �������ݿ��ܱ��ֳ����˷���ܵ���β�����ײ���</P>
//    ÿ�ν�βλ�õ�ƫ��ֻ��Ϊ4byte�ı���(sizeof(TInt32))��
// </P>
//
// @param pData ����ָ��
// @param size ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FSharedQueue::TryPush(TAnyC* pData, TInt size){
   // ������
   MO_ASSERT(pData);
   if(0 == size){
      MO_WARN(TC("Push data is empty. (data=0x%08X, size=%d)"), pData, size);
      return EFalse;
   }
   // ��ȡ�ܵ�����
   SPipeAtom atom = Atom();
   // �ж��Ƿ�ܵ�����
   TInt freeLength = atom.Reamin();
   if(size > freeLength){
      MO_WARN(TC("Current queue is full. (data=0x%08X, total=%d, length=%d, first=%d, last=%d, size=%d)"), atom.memoryPtr, atom.capacity, atom.length, atom.first, atom.last, size);
      return EFalse;
   }
   // д������
   TInt position = 0;
   TInt block = sizeof(TInt32);
   TByte* pRead = (TByte*)pData;
   TByte* pWrite = atom.memoryPtr + atom.last;
   if(atom.first <= atom.last){
      // ����д������ [--F====L--]
      //               0123456789
      TInt remain = atom.capacity - atom.last;
      if(remain < block){
         MO_WARN(TC("Remain free data is too small. (remain=%d)"), remain);
         return EFalse;
      }
      *(TInt32*)pWrite = (TInt32)size;
      remain -= block;
      pWrite += block;
      // д������
      if(size < remain){
         position = atom.last + block + size;
         memcpy(pWrite, pRead, size);
      }else if(size == remain){
         position = 0;
         memcpy(pWrite, pRead, size);
      }else if(size > remain){
         if(remain > 0){
            position = size - remain;
            memcpy(pWrite, pRead, remain);
            memcpy(atom.memoryPtr, pRead + remain, position);
         }else if(remain == 0){
            position = size;
            memcpy(atom.memoryPtr, pRead, size);
         }else{
            MO_WARN(TC("Remain free length is invalid. (remain=%d)"), remain);
            return EFalse;
         }
      }
   }else{
      // ����д������ [==L----F==]
      //               0123456789
      *(TInt32*)pWrite = (TInt32)size;
      position = atom.last + block + size;
      memcpy(pWrite + block, pRead, size);
   }
   // ���ý�βλ��
   TInt mod = position % block;
   if(0 != mod){
      position += block - mod;
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
//    ÿ�ο�ʼλ�õ�ƫ��ֻ��Ϊ4byte�ı���(sizeof(TInt32))��
// </P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч����
//============================================================
TInt FSharedQueue::Pop(TAny* pData, TInt capacity){
   // ������
   MO_ASSERT(pData);
   MO_ASSERT(capacity > 0);
   TInt block = sizeof(TInt32);
   // ��ȡ����
   SPipeAtom atom = Atom();
   // �ж��Ƿ���Զ���
   if(atom.length <= block){
      return 0;
   }
   // ��ȡ����
   TByte* pRead = atom.memoryPtr + atom.first;
   TInt size = *(TInt32*)pRead;
   if(0 == size){
      MO_FATAL(TC("Read data length is 0. (memory=0x%08X, total=%d, length=%d, first=%d, last=%d)"),
            atom.memoryPtr, atom.capacity, atom.length, atom.first, atom.last);
   }
   if(size > capacity){
      TFsDump buffer;
      MO_FATAL(TC("Read data length is large than capacity. (memory=0x%08X, total=%d, length=%d, first=%d, last=%d, size=%d)\n%s"),
            atom.memoryPtr, atom.capacity, atom.length, atom.first, atom.last, size,
            RByte::Dump(pRead - 32, 256, buffer.Memory(), buffer.Size()));
   }
   if(size > atom.length){
      TFsDump buffer;
      MO_FATAL(TC("Read data length is large than length. (memory=0x%08X, total=%d, length=%d, first=%d, last=%d, size=%d)\n%s"),
            atom.memoryPtr, atom.capacity, atom.length, atom.first, atom.last, size,
            RByte::Dump(pRead - 32, 256, buffer.Memory(), buffer.Size()));
   }
   pRead += block;
   // ��ȡ����
   TInt position = 0;
   if(atom.first < atom.last){
      // �����ȡ���� [--F====L--]
      //              [0123456789]
      position = atom.first + block + size;
      memcpy(pData, pRead, size);
   }else{
      // �����ȡ���� [==L----F==]
      //              [0123456789]
      TInt remain = atom.capacity - atom.first - block;
      if(size < remain){
         position = atom.first + block + size;
         memcpy(pData, pRead, size);
      }else if(size == remain){
         position = 0;
         memcpy(pData, pRead, size);
      }else if(size > remain){
         if(remain > 0){
            position = size - remain;
            memcpy(pData, pRead, remain);
            memcpy((TByte*)pData + remain, atom.memoryPtr, position);
         }else if(remain == 0){
            position = size;
            memcpy(pData, atom.memoryPtr, size);
         }else{
            MO_FATAL(TC("Remain free length is invalid. (remain=%d)"), remain);
         }
      }
   }
   // ���ÿ�ʼλ��
   TInt mod = position % block;
   if(0 != mod){
      position += block - mod;
   }
   if(position == atom.capacity){
      position = 0;
   }
   atom.SetFirst(position);
   return size;
}

//============================================================
// <T>��ܵ��ڶ���ʽѹ��һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param size ���ݳ���
// @return ѹ�������Ƿ�ɹ���ΪFalseʱ��ǰ�̻߳����
//============================================================
TBool FSharedQueue::BlockedPush(TAnyC* pData, TInt size){
   if(Push(pData, size)) {
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>�ӹܵ��ڶ���ʽ����һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0ʱ��ǰ�̻߳����
//============================================================
TInt FSharedQueue::BlockedPop(TAny* pData, TInt capacity){
   TInt length = 0;
   do{
      length = Pop(pData, capacity);
      if(0 == length){
         MO_LIB_SLEEP(1);
      }
   }while(0 == length);
   return length;
}

//============================================================
// <T>����ܵ�ʹ�������</T>
//
// @return bool
//============================================================
TBool FSharedQueue::DumpInfo(TChar* pTag){
	if (NULL == pTag){
		return EFalse;
	}
	SPipeAtom atom = Atom();
	MO_INFO(TC("[%s]QInfo:(total=%d, length=%d, first=%d, last=%d, free=%d)"), pTag, atom.capacity, atom.length, atom.first, atom.last, atom.Reamin());
	return ETrue;
}


MO_NAMESPACE_END
