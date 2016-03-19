#ifdef _MO_LINUX
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#endif
#include "MoCmMemory.h"
#include "MoCmLanguage.h"

#define MO_SHARE_MEMORY_ACCESS 0666
#define MO_SHARE_MEMORY_FLAG "MOSM"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����һ�鹲���ڴ档</T>
// <P>�����ǰ���ڣ�����������˳���</P>
//
// @param key �����ڴ��ֵ
// @param size �ڴ��С
// @return �����ڴ�
//============================================================
TAny* RShareMemory::InnerCreate(TShareKey key, TSize size){
#ifdef _MO_LINUX
   // ���������ڴ�
   TChar format[MO_MEMORY_FORMATLENGTH];
   MO_STATIC_DEBUG(TC("Create share memory. (key=0x%08X, size=%s)"),
         key, RInt::FormatCapacity(size, format, MO_MEMORY_FORMATLENGTH));
   // ���������ڴ�ͷ��Ϣ�Ĵ�С
   size += sizeof(SShareMemoryInfo);
   TInt handle = shmget(key, size, IPC_CREAT | IPC_EXCL | MO_SHARE_MEMORY_ACCESS);
   if(handle < 0){
      MO_STATIC_PFATAL(shmget);
   }
   // ��õ�ǰ�߳̿��Է��ʵ��ڴ�
   TByte* pMemory = (TByte*)shmat(handle, NULL, 0);
   MO_ASSERT(pMemory);
   // ������Ϣ
   SShareMemoryInfo* pInfo = (SShareMemoryInfo*)pMemory;
   memcpy(pInfo->flag, MO_SHARE_MEMORY_FLAG, sizeof(pInfo->flag));
   pInfo->size = size;
   pInfo->createDate = RDateTime::Current();
   pInfo->updateDate = pInfo->createDate;
   // ��ý��ָ��
   TByte* pResult = pMemory + sizeof(SShareMemoryInfo);
   memset(pResult, 0, size - sizeof(SShareMemoryInfo));
   return pResult;
#endif
   return NULL;
}

//============================================================
// <T>����һ�鹲���ڴ�ļ�ֵ��</T>
//
// @param pFileName �ļ�����
// @param id ��ʶ
//============================================================
TShareKey RShareMemory::MakeKey(TCharC* pFileName, TInt id){
#ifdef _MO_LINUX
   // TODO: ftok ��ú����п����ظ�
   // key_t tk = ftok(pFileName, id);
   // TShareKey key = ftok(pFileName, id);
   // if(key < 0){
   //    MO_STATIC_PFATAL(ftok);
   // }
   struct stat info;
   TInt result = stat(pFileName, &info);
   if(result < 0){
      MO_STATIC_PFATAL(stat);
   }
   TInt devId = info.st_dev << 16;
   TInt indexId = info.st_ino;
   key_t key = indexId + devId + (id << 8);
   return key;
#endif // _MO_LINUX
   return id;
}

//============================================================
// <T>��ȡ�����ڴ�Ķ�����Ϣ��</T>
//
// @param key �����ڴ��ֵ
// @param [out] info ������Ϣ
// @return �Ƿ��ȡ�ɹ�
//============================================================
TBool RShareMemory::FetchInfo(TShareKey key, SShareMemoryInfo& info){
#ifdef _MO_LINUX
   MO_STATIC_DEBUG(TC("Fetch info share memory info. (key=0x%08X)"), key);
   // ����һ�鹲���ڴ�
   TInt handle = shmget(key, 0, MO_SHARE_MEMORY_ACCESS);
   if(handle < 0){
      return EFalse;
   }
   // ��õ�ǰ�߳̿��Է��ʵ��ڴ�
   TByte* pMemory = (TByte*)shmat(handle, NULL, 0);
   MO_ASSERT(pMemory);
   SShareMemoryInfo* pInfo = (SShareMemoryInfo*)pMemory;
   // ��֤��־
   if(0 != memcmp(pInfo->flag, MO_SHARE_MEMORY_FLAG, sizeof(pInfo->flag))){
      MO_STATIC_DEBUG(TC("Share memory is not system type memory. (key=0x%08X)"), key);
      return EFalse;
   }
   // ��ȡ��Ϣ
   info = *pInfo;
   TChar format[MO_MEMORY_FORMATLENGTH];
   MO_STATIC_INFO(TC("Fetch share memory info success. (key=0x%08X, memory=0x%08X, size=%s)"),
         key, pInfo, RInt::FormatCapacity(info.size, format, MO_MEMORY_FORMATLENGTH));
#endif // _MO_LINUX
   return ETrue;
}

//============================================================
// <T>����һ��ָ����С�Ĺ����ڴ档</T>
// <P>��������ڴ���ڣ���ɾ���ɹ����ڴ棬���´���ָ����С�Ĺ����ڴ档</P>
//
// @param key �����ڴ��ֵ
// @param size �ڴ��С
// @return �����ڴ�
//============================================================
TAny* RShareMemory::Create(TShareKey key, TSize size){
#ifdef _MO_LINUX
   // ����һ�鹲���ڴ�
   TInt handle = shmget(key, 0, MO_SHARE_MEMORY_ACCESS);
   if(handle < 0){
      MO_STATIC_PWARN(shmget);
   }else{
      // ��õ�ǰ�߳̿��Է��ʵ��ڴ�
      TByte* pMemory = (TByte*)shmat(handle, NULL, 0);
      MO_ASSERT(pMemory);
      // ��ֹ�����̷�����鹲���ڴ�
      if(ESuccess != shmdt(pMemory)){
         MO_STATIC_PFATAL(shmdt);
      }
      // ɾ�������ڴ���
      MO_STATIC_DEBUG(TC("Remove old share memory. (key=0x%08X)"), key);
      if(ESuccess != shmctl(handle, IPC_RMID, NULL)){
         MO_STATIC_PFATAL(shmctl);
      }
   }
#endif
   // ���������ڴ�
   return InnerCreate(key, size);
}

//============================================================
// <T>���Դ���һ�鹲���ڴ档</T>
// <P>��������ڴ��Сһ�£���ֱ��ʹ�þɹ����ڴ档</P>
// <P>��������ڴ��С��һ�£���ɾ���ɹ����ڴ棬���´���ָ����С�Ĺ����ڴ档</P>
//
// @param key �����ڴ��ֵ
// @param size �ڴ��С
// @param created �Ƿ񴴽�
// @return �����ڴ�
//============================================================
TAny* RShareMemory::TryCreate(TShareKey key, TSize size, TBool& created){
#ifdef _MO_LINUX
   MO_STATIC_DEBUG(TC("Fetch info share memory info. (key=0x%08X)"), key);
   // ����һ�鹲���ڴ�
   TInt handle = shmget(key, 0, MO_SHARE_MEMORY_ACCESS);
   if(handle >= 0){
      // ��õ�ǰ�߳̿��Է��ʵ��ڴ�
      TByte* pMemory = (TByte*)shmat(handle, NULL, 0);
      MO_ASSERT(pMemory);
      SShareMemoryInfo* pInfo = (SShareMemoryInfo*)pMemory;
      // ��֤��־
      if(memcmp(pInfo->flag, MO_SHARE_MEMORY_FLAG, sizeof(pInfo->flag))){
         // ʹ�õ�ǰ�ڴ�
         if((TSize)pInfo->size == size){
            created = EFalse;
            return pMemory + sizeof(SShareMemoryInfo);
         }
      }
      // ��ֹ�����̷�����鹲���ڴ�
      if(ESuccess != shmdt(pMemory)){
         MO_STATIC_PFATAL(shmdt);
      }
      // ɾ�������ڴ���
      MO_STATIC_DEBUG(TC("Remove share memory. (key=0x%08X)"), key);
      if(ESuccess != shmctl(handle, IPC_RMID, NULL)){
         MO_STATIC_PFATAL(shmctl);
      }
   }
#endif // _MO_LINUX
   // ���������ڴ�
   created = ETrue;
   return InnerCreate(key, size);
}

//============================================================
// <T>����һ�鹲���ڴ档</T>
//
// @param key �����ڴ��ֵ
// @return �����ڴ�
//============================================================
TAny* RShareMemory::Connect(TShareKey key, TBool readOnly){
   TByte* pResult = NULL;
   MO_STATIC_DEBUG(TC("Connect share memory. (key=0x%08X)"), key);
#ifdef _MO_LINUX
   // ����һ�鹲���ڴ�
   TInt handle = shmget(key, 0, MO_SHARE_MEMORY_ACCESS);
   if(handle < 0){
      MO_STATIC_PFATAL(shmget);
   }
   // ��õ�ǰ�߳̿��Է��ʵ��ڴ�
   TByte* pMemory = NULL;
   if(readOnly){
      pMemory = (TByte*)shmat(handle, NULL, SHM_RDONLY);
   }else{
      pMemory = (TByte*)shmat(handle, NULL, 0);
   }
   MO_ASSERT(pMemory);
   SShareMemoryInfo* pInfo = (SShareMemoryInfo*)pMemory;
   // ��֤��־
   if(memcmp(pInfo->flag, MO_SHARE_MEMORY_FLAG, sizeof(pInfo->flag))){
      MO_STATIC_DEBUG(TC("Connect share memory failure. (key=0x%08X)"), key);
      return NULL;
   }
   TChar format[MO_MEMORY_FORMATLENGTH];
   MO_STATIC_DEBUG(TC("Connect share memory success. (key=0x%08X, memory=0x%08X, size=%s)"),
         key, pMemory, RInt::FormatCapacity(pInfo->size, format, MO_MEMORY_FORMATLENGTH));
   pResult = pMemory + sizeof(SShareMemoryInfo);
#endif // _MO_LINUX
   return pResult;
}

//============================================================
// <T>�ͷ�һ�鹲���ڴ档</T>
//
// @param key �����ڴ��ֵ
//============================================================
void RShareMemory::Free(TShareKey key){
#ifdef _MO_LINUX
   // ����һ�鹲���ڴ�
   TInt handle = shmget(key, 0, MO_SHARE_MEMORY_ACCESS);
   if(handle < 0){
      MO_STATIC_PFATAL(shmget);
   }
   // ɾ�������ڴ���
   if(ESuccess != shmctl(handle, IPC_RMID, NULL)){
      MO_STATIC_PFATAL(shmctl);
   }
   MO_STATIC_DEBUG("Free share memory. (key=0x%08X)", key);
#endif // _MO_LINUX
}

MO_NAMESPACE_END
