#include "MoCmMemory.h"
#include "MoCmString8.h"
#include "MoCmClass.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ռ���Ϣ�洢����</T>
//============================================================
FAllocatorStorage::FAllocatorStorage(){
   _able = EFalse;
   _lengthAlloc = 0;
   _lengthFree = 0;
   _pInfos = MO_MEM_CREATE(FAllocatorInfoVector);
}

//============================================================
// <T>�����ռ���Ϣ�洢����</T>
//============================================================
FAllocatorStorage::~FAllocatorStorage(){
   _able = EFalse;
   MO_MEM_DELETE(_pInfos);
}

//============================================================
// <T>����Ƿ����á�</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
TBool FAllocatorStorage::IsAble(){
   return _able;
}

//============================================================
// <T>��ʼͳ���ڴ档</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
void FAllocatorStorage::Enable(){
   _able = ETrue;
   Reset();
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
void FAllocatorStorage::Disable(TBool detail){
   Dump(detail);
   _able = EFalse;
}

//============================================================
// <T>����ڴ���Ϣ��</T>
//
// @param pInfo �ڴ���Ϣ
// @return ������
//============================================================
TBool FAllocatorStorage::FetchInfo(SMemoryInfo* pInfo){
   MO_ASSERT(pInfo);
   pInfo->lengthAlloc = _lengthAlloc;
   pInfo->lengthFree = _lengthFree;
   return ETrue;
}

//============================================================
// <T>�ռ�һ��ָ����С���ڴ档</T>
//
// @param pTypeName ��������
// @param size �ڴ��С
// @return �ڴ�ָ��
//============================================================
TAny* FAllocatorStorage::Alloc(TChar8C* pOwnerName, TChar8C* pTypeName, TInt size, TChar8C* pFileName, TInt lineNumber){
#ifdef _MO_DEBUG
   TAny* pMemory = malloc(sizeof(SAllocatorHeader) + size);
   if(_able){
      SAllocatorInfo* pInfo = NULL;
      //............................................................
      // �����ڴ���Ϣ
      _locker.Enter();
      TInt count = _pInfos->Count();
      for(TInt n = 0; n < count; n++){
         SAllocatorInfo* pFind = _pInfos->Get(n);
         if(NULL != pFind){
            // ���ߴ�
            if(pFind->size != size){
               continue;
            }
            // ���ӵ��������
            if(NULL != pOwnerName){
               if(!RString8::Equals(pFind->ownerNamePtr, pOwnerName)){
                  continue;
               }
            }
            // ���������
            if(NULL != pTypeName){
               if(!RString8::Equals(pFind->typeNamePtr, pTypeName)){
                  continue;
               }
            }
            // ������Ϣ
            pInfo = pFind;
            break;
         }
      }
      //............................................................
      // �����ڴ���Ϣ
      if(NULL == pInfo){
         pInfo = MO_MEM_CREATE(SAllocatorInfo);
         pInfo->storagePtr = this;
         pInfo->index = count;
         pInfo->ownerNamePtr = pOwnerName;
         pInfo->typeNamePtr = pTypeName;
         pInfo->fileNamePtr = pFileName;
         pInfo->lineNumber = lineNumber;
         pInfo->size = size;
         pInfo->count = 0;
         pInfo->total = 0;
         _pInfos->Push(pInfo);
      }
      //............................................................
      // ���¼�����
      pInfo->count++;
      pInfo->total++;
      _lengthAlloc += size;
      _locker.Leave();
      //............................................................
      // ����ͷ��Ϣ
      SAllocatorHeader* pHeader = (SAllocatorHeader*)pMemory;
      pHeader->infoPtr = pInfo;
   }else{
      *(TInt*)pMemory = 0;
   }
   return (TByte*)pMemory + sizeof(SAllocatorHeader);
#else
   return malloc(size);
#endif // _MO_DEBUG
};

//============================================================
// <T>�ͷ��ڴ档</T>
//
// @param pMemory �ڴ�ָ��
//============================================================
void FAllocatorStorage::Free(TAny* pMemory){
   MO_ASSERT(pMemory);
#ifdef _MO_DEBUG
   // ���ͷ��Ϣ
   TAny* pData = (TByte*)pMemory - sizeof(SAllocatorHeader);
   if(_able){
      SAllocatorInfo* pInfo = ((SAllocatorHeader*)pData)->infoPtr;
      if(NULL != pInfo){
         if(pInfo->storagePtr == this){
            // ����ͳ����Ϣ
            _locker.Enter();
            pInfo->count--;
            _lengthFree += pInfo->size;
            _locker.Leave();
         }
      }
   }
   free(pData);
#else
   free(pMemory);
#endif // _MO_DEBUG
}

//============================================================
// <T>����ͳ����Ϣ��</T>
//============================================================
void FAllocatorStorage::Reset(){
   _locker.Enter();
   TInt count = _pInfos->Count();
   for(TInt n = 0; n < count; n++){
      SAllocatorInfo* pInfo = _pInfos->Get(n);
      pInfo->count = 0;
      pInfo->total = 0;
   }
   _locker.Leave();
}

//============================================================
// <T>���������Ϣ��</T>
//============================================================
void FAllocatorStorage::Dump(TBool detail){
   // ����Ƿ���Ը���
   if(!_able){
      return;
   }
   // ��ʾ������Ϣ
   TFsDump dump;
   dump.Append(TC("-- Dump infos begin ------------------------------------------------------------\n"));
   TInt64 totalCapacity = 0;
   TInt validCount = 0;
   TInt count = _pInfos->Count();
   for(TInt n = 0; n < count; n++){
      SAllocatorInfo* pInfo = _pInfos->Get(n);
      // ��ⷽʽ
      if(detail){
         if(0 == pInfo->total){
            continue;
         }
      }else{
         if(0 == pInfo->count){
            continue;
         }
      }
      // ��ʾ��Ϣ
      TInt64 capacity = pInfo->size * pInfo->count;
      totalCapacity += capacity;
      // ����������
      TFsName ownerName;
      if(NULL != pInfo->ownerNamePtr){
         TClassInfo type = pInfo->ownerNamePtr;
         ownerName = type.FullName();
      }
      if(ownerName.IsEmpty()){
         // ownerName = pInfo->ownerNamePtr;
      }
      // ����Ĭ������
      TFsName className;
      if(NULL != pInfo->typeNamePtr){
         TClassInfo type = pInfo->typeNamePtr;
         className = type.FullName();
      }
      if(className.IsEmpty()){
         // className = pInfo->typeNamePtr;
      }
      // �����־
      dump.AppendFormat(TC("-- Class [%-48s][%-64s] - [%8d] -> count=%8d, total=%8d, memory=%22s, file=%s(%d)\n"),
            (TCharC*)ownerName, (TCharC*)className, pInfo->size, pInfo->count, pInfo->total,
            RInt::FormatCapacity(capacity, TFsCode(), TFsCode::Size()), pInfo->fileNamePtr, pInfo->lineNumber);
      validCount++;
   }
   dump.Append(TC("-- Dump infos end --------------------------------------------------------------\n"));
   dump.AppendFormat(TC("   Count: %4d, Memory: %s, (alloc=%s, free=%s)"), validCount,
         RInt::FormatCapacity(totalCapacity, TFsCode(), TFsCode::Size()),
         RInt::FormatCapacity(_lengthAlloc, TFsCode(), TFsCode::Size()),
         RInt::FormatCapacity(_lengthFree, TFsCode(), TFsCode::Size()));
   MO_INFO(TC("Allocator storage info.\n%s"), (TCharC*)dump);
}

MO_NAMESPACE_END
