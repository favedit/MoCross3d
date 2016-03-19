#include "MoCmPipe.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���컺����С�</T>
//============================================================
FBufferedPipe::FBufferedPipe(){
   _lockCd = EStreamLock_Lock;
   _countPush = 0;
   _lengthPush = 0;
   _countPop = 0;
   _lengthPop = 0;
   _pPool = MO_CREATE(FStreamBlockPool);
   MO_CLEAR(_pReadBlock);
   _pReadBlocks = MO_CREATE(FBufferedPipeBlockList);
   MO_CLEAR(_pWriteBlock);
   _pWriteBlocks = MO_CREATE(FBufferedPipeBlockList);
}

//============================================================
// <T>����������С�</T>
//============================================================
FBufferedPipe::~FBufferedPipe(){
   MO_DELETE(_pPool);
   MO_DELETE(_pReadBlocks);
   MO_DELETE(_pWriteBlocks);
}

//============================================================
// <T>�ӹܵ��ڼ���һ�����ݡ�</T>
// <P>���ܻ����𽻻��������������������ݡ�</P>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @param pLength �������
// @return ������
//============================================================
EStreamResult FBufferedPipe::InnerPeek(TAny* pData, TInt length, TInt* pLength){
   TByte* pReader = (TByte*)pData;
   TInt remain = length;
   // ��ȡ�׿�����
   if(remain > 0){
      if(NULL != _pReadBlock){
         TInt lengthPeek = 0;
         if(EStreamResult_Success == _pReadBlock->Peek(pReader, remain, &lengthPeek)){
            pReader += lengthPeek;
            remain -= lengthPeek;
         }
      }
   }
   // ��ȡ����
   if(remain > 0){
      // ��������
      if(!_pReadBlocks->IsEmpty()){
         TListIteratorC<FBufferedPipeBlock*> iterator = _pReadBlocks->IteratorC();
         while((remain > 0) && iterator.Next()){
            FBufferedPipeBlock* pBlock = *iterator;
            TInt lengthRead = 0;
            if(EStreamResult_Success == pBlock->Peek(pReader, remain, &lengthRead)){
               pReader += lengthRead;
               remain -= lengthRead;
            }
         }
      }
   }
   // ��ȡд����
   if(remain > 0){
      FBufferedPipeBlock* pReadBlock = NULL;
      // ����д����
      WriteLock();
      if(NULL != _pWriteBlock){
         if(!_pWriteBlock->IsEmpty()){
            _pWriteBlock->FlipForRead();
            pReadBlock = _pWriteBlock;
            _pReadBlocks->Push(_pWriteBlock);
            MO_CLEAR(_pWriteBlock);
         }
      }
      WriteUnlock();
      // ��ȡ���ݿ�
      if(NULL != pReadBlock){
         TInt lengthPeek = 0;
         if(EStreamResult_Success == pReadBlock->Peek(pReader, remain, &lengthPeek)){
            pReader += lengthPeek;
            remain -= lengthPeek;
         }
      }
   }
   *pLength = length - remain;
   return EStreamResult_Success;
}

//============================================================
// <T>�ӹܵ��ڵ���һ�����������ݡ�</T>
//
// @param pData ����ָ��
// @param capacity ���ݳ���
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
EStreamResult FBufferedPipe::InnerRead(TAny* pData, TInt length, TInt* pLength){
   TByte* pReader = (TByte*)pData;
   TInt remain = length;
   while(remain > 0){
      // ��ö�ȡ��
      if(NULL == _pReadBlock){
         if(!_pReadBlocks->IsEmpty()){
            _pReadBlock = _pReadBlocks->Shift();
         }
      }
      // ����д����
      if(NULL == _pReadBlock){
         WriteLock();
         if(NULL != _pWriteBlock){
            if(!_pWriteBlock->IsEmpty()){
               _pWriteBlock->FlipForRead();
               _pReadBlock = _pWriteBlock;
               MO_CLEAR(_pWriteBlock);
            }
         }
         WriteUnlock();
      }
      // �����Ƿ��ܹ���ȡ����
      if(NULL != _pReadBlock){
         TInt lengthRead = 0;
         if(EStreamResult_Success == _pReadBlock->Read(pReader, remain, &lengthRead)){
            pReader += lengthRead;
            remain -= lengthRead;
            _countPop++;
            _lengthPop += lengthRead;
         }
         // �����Ƿ��Ѿ���ȡ���
         if(_pReadBlock->TestReadEnd()){
            _pPool->Free(_pReadBlock);
            _pReadBlock = NULL;
         }
      }else{
         break;
      }
   }
   *pLength = length - remain;
   return EStreamResult_Success;
}

//============================================================
// <T>��һ��������Ϣд��ܵ���</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @param pLength д�볤��
// @return ѹ���Ƿ�ɹ�
//============================================================
EStreamResult FBufferedPipe::InnerWrite(TAnyC* pData, TInt length, TInt* pLength){
   // д��ȫ������
   TByte* pWriter = (TByte*)pData;
   TInt remain = length;
   while(remain > 0){
      // �ռ��ڴ�
      if(NULL == _pWriteBlock){
         _pWriteBlock = (FBufferedPipeBlock*)_pPool->Alloc();
         if(NULL == _pWriteBlock){
            return EStreamResult_WriteCapacity;
         }
      }
      // ����д��
      if(NULL != _pWriteBlock){
         // д������
         TInt lengthWrite = 0;
         if(EStreamResult_Success == _pWriteBlock->Write(pWriter, remain, &lengthWrite)){
            pWriter += lengthWrite;
            remain -= lengthWrite;
            _countPush++;
            _lengthPush += lengthWrite;
         }
         // ���Խ���
         if(_pWriteBlock->TestWriteEnd()){
            // ��ȡ����
            _pWriteBlock->FlipForRead();
            // �����ȡ����
            ReadLock();
            _pReadBlocks->Push(_pWriteBlock);
            _pWriteBlock = NULL;
            ReadUnlock();
         }
      }else{
         break;
      }
   }
   *pLength = length - remain;
   return EStreamResult_Success;
}

//============================================================
// <T>��ùܵ��ĳ��ȡ�</T>
//
// @return ���ݳ���
//============================================================
TInt FBufferedPipe::Length(){
   return _lengthPush - _lengthPop;
}

//============================================================
// <T>�����Ƿ���д��ָ�����ȵ����ݡ�</T>
//
// @param length ���ݳ���
// @return ѹ���Ƿ�ɹ�
//============================================================
TBool FBufferedPipe::TestWriteAble(TInt length){
   return ETrue;
}

//============================================================
// <T>�����Ƿ��ܴӹܵ��ڵ���һ�����ݡ�</T>
//
// @return �������ݵĳ��ȣ�Ϊ0��ʾû�ж�����Ч���ݣ�Ϊ-1��ʾ�������岻��
//============================================================
TBool FBufferedPipe::TestReadAble(TInt length){
   return EFalse;
}

//============================================================
// <T>�ӹܵ��ڻ��һ�����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @param pLength ��ȡ����
// @return ������
//============================================================
EStreamResult FBufferedPipe::Peek(TAny* pData, TInt length, TInt* pLength){
   EStreamResult resultCd = EStreamResult_Unknown;
   switch(_lockCd){
      case EStreamLock_Unlock:{
         resultCd = InnerPeek(pData, length, pLength);
         break;
      }
      case EStreamLock_Lock:{
         ReadLock();
         resultCd = InnerPeek(pData, length, pLength);
         ReadUnlock();
         break;
      }
      default:{
         MO_FATAL(TC("Unknown lock mode."));
         break;
      }
   }
   return resultCd;
}

//============================================================
// <T>�ӹܵ��ڶ�ȡһ�����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @param pLength ��ȡ����
// @return ������
//============================================================
EStreamResult FBufferedPipe::Read(TAny* pData, TInt length, TInt* pLength){
   EStreamResult resultCd = EStreamResult_Unknown;
   switch(_lockCd){
      case EStreamLock_Unlock:{
         resultCd = InnerRead(pData, length, pLength);
         break;
      }
      case EStreamLock_Lock:{
         ReadLock();
         resultCd = InnerRead(pData, length, pLength);
         ReadUnlock();
         break;
      }
      default:{
         MO_FATAL(TC("Unknown lock mode."));
         break;
      }
   }
   return resultCd;
}

//============================================================
// <T>��ܵ���д��һ�����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @param pLength ��ȡ����
// @return ������
//============================================================
EStreamResult FBufferedPipe::Write(TAnyC* pData, TInt length, TInt* pLength){
   EStreamResult resultCd = EStreamResult_Unknown;
   switch(_lockCd){
      case EStreamLock_Unlock:{
         resultCd = InnerWrite(pData, length, pLength);
         break;
      }
      case EStreamLock_Lock:{
         WriteLock();
         resultCd = InnerWrite(pData, length, pLength);
         WriteUnlock();
         break;
      }
      default:{
         MO_FATAL(TC("Unknown lock mode."));
         break;
      }
   }
   return resultCd;
}

//============================================================
// <T>�������ݡ�</T>
//
// @return ������
//============================================================
TBool FBufferedPipe::Reset(){
   _countPush = 0;
   _lengthPush = 0;
   _countPop = 0;
   _lengthPop = 0;
   _pPool->Reset();
   MO_CLEAR(_pReadBlock);
   _pReadBlocks->Clear();
   MO_CLEAR(_pWriteBlock);
   _pWriteBlocks->Clear();
   return ETrue;
}

//============================================================
// <T>����ڲ���Ϣ��</T>
//============================================================
void FBufferedPipe::Dump(){
   TInt count = _countPush - _countPop;
   TInt length = _lengthPush - _lengthPop;
   TFsDump dump;
   dump.AppendFormat(TC("Buffered queue dump. (capacity=%d, count=%d, length=%d)\n"), _pPool->Capacity(), count, length);
   _pPool->Track(&dump);
   MO_INFO((TCharC*)dump);
}

MO_NAMESPACE_END
