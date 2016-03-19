#ifndef __MO_CM_PIPE_H__
#define __MO_CM_PIPE_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_LOCK_H__
#include "MoCmLock.h"
#endif // __MO_CM_LOCK_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

#ifndef __MO_CM_FORMAT_H__
#include "MoCmFormat.h"
#endif // __MO_CM_FORMAT_H__

#ifndef __MO_CM_STREAM_H__
#include "MoCmStream.h"
#endif // __MO_CM_STREAM_H__

#ifndef __MO_CM_SHARED_H__
#include "MoCmShared.h"
#endif // __MO_CM_SHARED_H__

#define MO_PIPE_LENGTH_SIZE 4

MO_NAMESPACE_BEGIN

const TInt MoPipeReserveLength = 16;

//============================================================
// <T>������ģʽ��</T>
//============================================================
enum EStreamLock{
   // ����ģʽ���ʺϵ��̣߳�
   EStreamLock_Unlock = 0,
   // ����ģʽ���ʺ϶��̣߳�
   EStreamLock_Lock = 1,
};

//============================================================
// <T>����������</T>
//============================================================
enum EStreamResult{
   // �ɹ�
   EStreamResult_Success = 0,
   // δ֪
   EStreamResult_Unknown = -1,
   // д�������
   EStreamResult_WriteEmpty = -2,
   // д�����
   EStreamResult_WriteFull = -3,
   // д�뻺����
   EStreamResult_WriteCapacity = -4,
   // ��ȡ������
   EStreamResult_ReadEmpty = -5,
   // ��ȡ����β
   EStreamResult_ReadEnd = -6,
   // ��ȡ���岻��
   EStreamResult_ReadCapacity = -7,
};

//============================================================
// <T>������п�ͷ��Ϣ��</T>
//============================================================
#pragma pack(4)
struct FStreamBlockHead{
   TInt32 length;
   TByte data[1];
};
#pragma pack()

//============================================================
// <T>�������ֿ顣</T>
//============================================================
class MO_CM_DECLARE FStreamBlock : public FObject{
protected:
   TByte* _pMemory;
   TInt _capacity;
   TInt _length;
   TInt _lengthMax;
   TInt _position;
   TInt _lengthTotalRead;
   TInt _lengthTotalWrite;
public:
   FStreamBlock();
   MO_ABSTRACT ~FStreamBlock();
public:
   //------------------------------------------------------------
   // <T>����ڴ档</T>
   MO_INLINE TByte* Memory(){
      return _pMemory;
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Capacity(){
      return _capacity;
   }
   //------------------------------------------------------------
   // <T>���λ�á�</T>
   MO_INLINE TInt Position(){
      return _position;
   }
   //------------------------------------------------------------
   // <T>��ÿ��ó��ȡ�</T>
   MO_INLINE TInt LengthFree(){
      return _capacity - _position;
   }
   //------------------------------------------------------------
   // <T>��ö�ȡ�ܳ��ȡ�</T>
   MO_INLINE TInt LengthTotalRead(){
      return _lengthTotalRead;
   }
   //------------------------------------------------------------
   // <T>���д���ܳ��ȡ�</T>
   MO_INLINE TInt LengthTotalWrite(){
      return _lengthTotalWrite;
   }
public:
   void ForceCapacity(TInt capacity);
public:
   TBool IsEmpty();
   MO_ABSTRACT TBool TestPushAble(TInt length);
   MO_ABSTRACT TBool TestPopAble(TInt length);
public:
   TBool FlipForRead();
   TBool FlipForWrite();
   TBool Reset();
public:
   void Track(MString* pTrack);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FStreamBlock*> FStreamBlockList;

//============================================================
// <T>���ݶ��зֿ��ռ�����</T>
//============================================================
class MO_CM_DECLARE FStreamBlockAllocator : public FPool<FStreamBlock*>{
protected:
   TInt _blockCapacity;
   TInt _blockLimit;
   TThreadLocker _locker;
public:
   FStreamBlockAllocator();
   MO_ABSTRACT ~FStreamBlockAllocator();
public:
   //------------------------------------------------------------
   // <T>��÷ֿ�������</T>
   MO_INLINE TInt BlockCapacity(){
      return _blockCapacity;
   }
   //------------------------------------------------------------
   // <T>���÷ֿ�������</T>
   MO_INLINE void SetBlockCapacity(TInt blockCapacity){
      _blockCapacity = blockCapacity;
   }
   //------------------------------------------------------------
   // <T>��÷ֿ����ơ�</T>
   MO_INLINE TInt BlockLimit(){
      return _blockLimit;
   }
   //------------------------------------------------------------
   // <T>���÷ֿ����ơ�</T>
   MO_INLINE void SetBlockLimit(TInt blockLimit){
      _blockLimit = blockLimit;
   }
protected:
   MO_VIRTUAL FStreamBlock* Create() = 0;
   MO_ABSTRACT void Delete(FStreamBlock* pBlock);
public:
   FStreamBlock* Alloc();
   void Free(FStreamBlock* pBlock);
public:
   MO_ABSTRACT void Track(MString* pTrack);
};
//------------------------------------------------------------
typedef FVector<FStreamBlockAllocator*> FStreamBlockAllocatorVector;

//============================================================
// <T>���ݶ��зֿ黺��ء�</T>
//============================================================
class MO_CM_DECLARE FStreamBlockPool : public FObject{
protected:
   TInt _capacity;
   TInt _blockCapacity;
   FStreamBlockList* _pBlocks;
   FStreamBlockAllocator* _pAllocator;
   TThreadLocker _locker;
public:
   FStreamBlockPool();
   MO_ABSTRACT ~FStreamBlockPool();
public:
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE TInt Capacity(){
      return _capacity;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE void SetCapacity(TInt capacity){
      _capacity = capacity;
   }
   //------------------------------------------------------------
   // <T>��÷ֿ�������</T>
   MO_INLINE TInt BlockCapacity(){
      return _blockCapacity;
   }
   //------------------------------------------------------------
   // <T>���÷ֿ�������</T>
   MO_INLINE void SetBlockCapacity(TInt blockCapacity){
      _blockCapacity = blockCapacity;
   }
   //------------------------------------------------------------
   // <T>��÷ֿ��ռ�����</T>
   MO_INLINE FStreamBlockAllocator* Allocator(){
      return _pAllocator;
   }
   //------------------------------------------------------------
   // <T>���÷ֿ��ռ�����</T>
   MO_INLINE void SetAllocator(FStreamBlockAllocator* pAllocator){
      _pAllocator = pAllocator;
   }
public:
   FStreamBlock* Alloc();
   void Free(FStreamBlock* pBlock);
public:
   TBool Reset();
public:
   void Track(MString* pTrack);
};
//------------------------------------------------------------
typedef FVector<FStreamBlockPool*> FStreamBlockPoolVector;

//============================================================
// <T>���ݹܵ��ӿڡ�</T>
//============================================================
class MO_CM_DECLARE IPipe :
      public IInput,
      public IOutput{
public:
   MO_ABSTRACT ~IPipe(){
   }
public:
   MO_VIRTUAL TBool IsEmpty() = 0;
   MO_VIRTUAL TInt Length() = 0;
   MO_VIRTUAL TInt Reamin() = 0;
public:
   MO_VIRTUAL TInt Peek(TAny* pData, TInt size) = 0;
   MO_VIRTUAL TInt Write(TAnyC* pData, TInt size) = 0;
   MO_VIRTUAL TInt Read(TAny* pData, TInt size) = 0;
   MO_VIRTUAL TBool TryPeek(TAny* pData, TInt size) = 0;
   MO_VIRTUAL TBool TryWrite(TAnyC* pData, TInt size) = 0;
   MO_VIRTUAL TBool TryRead(TAny* pData, TInt size) = 0;
   MO_VIRTUAL TBool Reset() = 0;
   MO_VIRTUAL TBool Close() = 0;
};

//============================================================
// <T>���ݹܵ����塣</T>
//============================================================
struct SPipeInfo{
public:
   TInt32 capacity;
   TInt32 first;
   TInt32 last;
};

//============================================================
// <T>�ܵ����ݡ�</T>
//============================================================
struct SPipeAtom{
public:
   SPipeInfo* infoPtr;
   TByte* memoryPtr;
public:
   TInt capacity;
   TInt length;
   TInt first;
   TInt last;
public:
   //------------------------------------------------------------
   MO_INLINE void Fetch(){
      capacity = infoPtr->capacity;
      first = infoPtr->first;
      last = infoPtr->last;
      // �����У�����βλ�ò����ڳ����У�������һ�����ݿ�ʼ
      if(first <= last){
         // ���㳤�� [--F===L---] [4 = (6 - 2)]
         //           0123456789
         length = last - first;
      }else{
         // ���㳤�� [==L---F===] [6 = (10 - 6) + 2]
         //           0123456789
         length = (capacity - first) + last;
      }
   }
public:
   //------------------------------------------------------------
   MO_INLINE TBool IsEmpty(){
      return (0 == length);
   }
   //------------------------------------------------------------
   MO_INLINE TInt Reamin(){
      return capacity - length - MoPipeReserveLength;
   }
   //------------------------------------------------------------
   MO_INLINE void SetFirst(TInt first){
      infoPtr->first = (TInt32)first;
   }
   //------------------------------------------------------------
   MO_INLINE void SetLast(TInt last){
      infoPtr->last = (TInt32)last;
   }
   //------------------------------------------------------------
   MO_INLINE void Set(TInt first, TInt last){
      infoPtr->first = (TInt32)first;
      infoPtr->last = (TInt32)last;
   }
   //------------------------------------------------------------
   MO_INLINE void Clear(){
      infoPtr->first = 0;
      infoPtr->last = 0;
   }
};

//============================================================
// <T>���ݹܵ���</T>
//============================================================
class MO_CM_DECLARE MPipe : public IPipe{
protected:
   TThreadLocker _locker;
public:
   MPipe();
   MO_ABSTRACT ~MPipe();
public:
   MO_VIRTUAL SPipeInfo* Info() = 0;
   MO_VIRTUAL SPipeAtom Atom() = 0;
public:
   MO_OVERRIDE TBool IsEmpty();
   MO_OVERRIDE TInt Length();
   MO_OVERRIDE TInt Reamin();
public:
   TInt FollowReamin();
   TByte* FollowMemory();
   TBool FollowWrite(TInt size);
   TBool FollowRead(TInt size);
public:
   MO_OVERRIDE TInt Peek(TAny* pData, TInt size);
   MO_OVERRIDE TInt Write(TAnyC* pData, TInt size);
   MO_OVERRIDE TInt Read(TAny* pData, TInt size);
   MO_OVERRIDE TBool TryPeek(TAny* pData, TInt size);
   MO_OVERRIDE TBool TryWrite(TAnyC* pData, TInt size);
   MO_OVERRIDE TBool TryRead(TAny* pData, TInt size);
   MO_OVERRIDE TBool Reset();
   MO_OVERRIDE TBool Close();
   void Track();
};

//============================================================
// <T>���ݹܵ���</T>
//============================================================
class MO_CM_DECLARE FPipe :
      public FObject,
      public MPipe{
protected:
   TBool _linked;
   SPipeInfo _info;
   TByte* _pMemory;
public:
   FPipe();
   FPipe(TSize capacity);
   FPipe(TByte* pMemory, TSize capacity);
   MO_ABSTRACT ~FPipe();
protected:
   MO_OVERRIDE SPipeInfo* Info();
   MO_OVERRIDE SPipeAtom Atom();
public:
   MO_OVERRIDE TInt Length();
   MO_OVERRIDE TInt Reamin();
   TBool Reset();
};

//============================================================
// <T>������п顣</T>
//============================================================
class MO_CM_DECLARE FBufferedPipeBlock : public FStreamBlock{
public:
   FBufferedPipeBlock();
   MO_ABSTRACT ~FBufferedPipeBlock();
public:
   //------------------------------------------------------------
   // <T>�����Ƿ��Ѿ���ȡ��β����</T>
   MO_INLINE TBool TestReadEnd(){
      return (_position == _length);
   }
   //------------------------------------------------------------
   // <T>�����Ƿ��Ѿ�д�뵽β����</T>
   MO_INLINE TBool TestWriteEnd(){
      return (_position == _length);
   }
public:
   TBool TestWriteAble(TInt length);
   TBool TestReadAble(TInt length);
public:
   EStreamResult Peek(TAny* pData, TInt length, TInt *pLength);
   EStreamResult Read(TAny* pData, TInt length, TInt *pLength);
   EStreamResult Write(TAnyC* pData, TInt length, TInt *pLength);
public:
   MO_OVERRIDE void Track(MString* pTrack);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FBufferedPipeBlock*> FBufferedPipeBlockList;

//============================================================
// <T>���ݶ��зֿ��ռ�����</T>
//============================================================
class MO_CM_DECLARE FBufferedPipeBlockAllocator : public FStreamBlockAllocator{
public:
   //------------------------------------------------------------
   // <T>�������ݶ��зֿ黺��ء�</T>
   FBufferedPipeBlockAllocator(){
   }
   //------------------------------------------------------------
   // <T>�������ݶ��зֿ黺��ء�</T>
   MO_ABSTRACT ~FBufferedPipeBlockAllocator(){
   }
public:
   //------------------------------------------------------------
   // <T>����һ�����зֿ顣</T>
   MO_OVERRIDE FStreamBlock* Create(){
      return MO_CREATE(FBufferedPipeBlock);
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FVector<FBufferedPipeBlockAllocator*> FBufferedPipeBlockAllocatorVector;

//============================================================
// <T>������С�</T>
//============================================================
class MO_CM_DECLARE FBufferedPipe : public FObject{
protected:
   EStreamLock _lockCd;
   TInt _countPush;
   TInt _lengthPush;
   TInt _countPop;
   TInt _lengthPop;
protected:
   TThreadLocker _lockerRead;
   TThreadLocker _lockerWrite;
   FStreamBlockPool* _pPool;
   FBufferedPipeBlock* _pReadBlock;
   FBufferedPipeBlockList* _pReadBlocks;
   FBufferedPipeBlock* _pWriteBlock;
   FBufferedPipeBlockList* _pWriteBlocks;
public:
   FBufferedPipe();
   MO_ABSTRACT ~FBufferedPipe();
public:
   //------------------------------------------------------------
   // <T>���������ʽ��</T>
   MO_INLINE EStreamLock LockCd(){
      return _lockCd;
   }
   //------------------------------------------------------------
   // <T>����������ʽ��</T>
   MO_INLINE void SetLockCd(EStreamLock lockCd){
      _lockCd = lockCd;
   }
   //------------------------------------------------------------
   // <T>��û���ء�</T>
   MO_INLINE FStreamBlockPool* Pool(){
      return _pPool;
   }
   //------------------------------------------------------------
   // <T>��û����ռ�����</T>
   MO_INLINE FBufferedPipeBlockAllocator* Allocator(){
      return (FBufferedPipeBlockAllocator*)_pPool->Allocator();
   }
   //------------------------------------------------------------
   // <T>���û����ռ�����</T>
   MO_INLINE void SetAllocator(FBufferedPipeBlockAllocator* pAllocator){
      _pPool->SetAllocator(pAllocator);
   }
   //------------------------------------------------------------
   // <T>��ö�ȡ�鼯�ϡ�</T>
   MO_INLINE FBufferedPipeBlockList* ReadBlocks(){
      return _pReadBlocks;
   }
   //------------------------------------------------------------
   // <T>���д��鼯�ϡ�</T>
   MO_INLINE FBufferedPipeBlockList* WriteBlocks(){
      return _pWriteBlocks;
   }
protected:
   //------------------------------------------------------------
   // <T>��ȡ������</T>
   MO_INLINE void ReadLock(){
      if(EStreamLock_Unlock != _lockCd){
         _lockerRead.Enter();
      }
   }
   //------------------------------------------------------------
   // <T>��ȡ������</T>
   MO_INLINE void ReadUnlock(){
      if(EStreamLock_Unlock != _lockCd){
         _lockerRead.Leave();
      }
   }
   //------------------------------------------------------------
   // <T>д��������</T>
   MO_INLINE void WriteLock(){
      if(EStreamLock_Unlock != _lockCd){
         _lockerWrite.Enter();
      }
   }
   //------------------------------------------------------------
   // <T>д�������</T>
   MO_INLINE void WriteUnlock(){
      if(EStreamLock_Unlock != _lockCd){
         _lockerWrite.Leave();
      }
   }
protected:
   EStreamResult InnerPeek(TAny* pData, TInt length, TInt* pLength);
   EStreamResult InnerRead(TAny* pData, TInt length, TInt* pLength);
   EStreamResult InnerWrite(TAnyC* pData, TInt length, TInt* pLength);
public:
   MO_ABSTRACT TInt Length();
public:
   MO_ABSTRACT TBool TestWriteAble(TInt length);
   MO_ABSTRACT TBool TestReadAble(TInt length);
public:
   MO_ABSTRACT EStreamResult Peek(TAny* pData, TInt length, TInt* pLength);
   MO_ABSTRACT EStreamResult Read(TAny* pData, TInt length, TInt* pLength);
   MO_ABSTRACT EStreamResult Write(TAnyC* pData, TInt length, TInt* pLength);
public:
   MO_ABSTRACT TBool Reset();
public:
   void Dump();
};

//============================================================
// <T>���ݶ��С�</T>
// <P>��������ѹ�����ݺͶ�ȡ���ݡ�</P>
// <P>Push/Pop�������ܺ�Write��Readͬʱʹ�á�</P>
//
// @history 100309 MAOCY ����
// @history 100714 MAOCY ѹ��Ͷ�ȡ���ݵ�����
//============================================================
class MO_CM_DECLARE FQueue : public FPipe{
public:
   FQueue();
   FQueue(TSize capacity);
   FQueue(TByte* pMemory, TSize capacity);
   MO_ABSTRACT ~FQueue();
public:
   TBool Push(TAnyC* pData, TInt size);
   TInt Pop(TAny* pData, TInt capacity);
};

//============================================================
// <T>������п顣</T>
//============================================================
class MO_CM_DECLARE FBufferedQueueBlock : public FStreamBlock{
public:
   TInt _count;
   TInt _countMax;
public:
   FBufferedQueueBlock();
   MO_ABSTRACT ~FBufferedQueueBlock();
public:
   TBool TestPushAble(TInt length);
   TBool TestPopAble(TInt length);
public:
   EStreamResult Push(TAnyC* pData, TInt length);
   EStreamResult Pop(TAny* pData, TInt capacity, TInt* pLength);
public:
   MO_OVERRIDE void Track(MString* pTrack);
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<FBufferedQueueBlock*> FBufferedQueueBlockList;

//============================================================
// <T>���ݶ��зֿ��ռ�����</T>
//============================================================
class MO_CM_DECLARE FBufferedQueueBlockAllocator : public FStreamBlockAllocator{
public:
   //------------------------------------------------------------
   // <T>�������ݶ��зֿ黺��ء�</T>
   FBufferedQueueBlockAllocator(){
   }
   //------------------------------------------------------------
   // <T>�������ݶ��зֿ黺��ء�</T>
   MO_ABSTRACT ~FBufferedQueueBlockAllocator(){
   }
public:
   //------------------------------------------------------------
   // <T>����һ�����зֿ顣</T>
   MO_OVERRIDE FStreamBlock* Create(){
      return MO_CREATE(FBufferedQueueBlock);
   }
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FVector<FBufferedQueueBlockAllocator*> FBufferedQueueBlockAllocatorVector;

//============================================================
// <T>���������Ϣ��</T>
//============================================================
struct MO_CM_DECLARE SQueueInfo{
   TInt32 count;
   TInt32 length;
   TInt64 countPush;
   TInt64 lengthPush;
   TInt64 countPop;
   TInt64 lengthPop;
};

//============================================================
// <T>������С�</T>
//============================================================
class MO_CM_DECLARE FBufferedQueue : public FObject{
protected:
   EStreamLock _lockCd;
   TInt64 _countPush;
   TInt64 _lengthPush;
   TInt64 _countPop;
   TInt64 _lengthPop;
protected:
   TThreadLocker _locker;
   FStreamBlockPool* _pPool;
   FBufferedQueueBlock* _pReadBlock;
   FBufferedQueueBlockList* _pReadBlocks;
   FBufferedQueueBlock* _pWriteBlock;
   FBufferedQueueBlockList* _pWriteBlocks;
public:
   FBufferedQueue();
   MO_ABSTRACT ~FBufferedQueue();
public:
   //------------------------------------------------------------
   // <T>���������ʽ��</T>
   MO_INLINE EStreamLock LockCd(){
      return _lockCd;
   }
   //------------------------------------------------------------
   // <T>����������ʽ��</T>
   MO_INLINE void SetLockCd(EStreamLock lockCd){
      _lockCd = lockCd;
   }
   //------------------------------------------------------------
   // <T>��÷��������</T>
   MO_INLINE TInt64 CountPush(){
      return _countPush;
   }
   //------------------------------------------------------------
   // <T>��÷��볤�ȡ�</T>
   MO_INLINE TInt64 LengthPush(){
      return _lengthPush;
   }
   //------------------------------------------------------------
   // <T>��õ���������</T>
   MO_INLINE TInt64 CountPop(){
      return _countPop;
   }
   //------------------------------------------------------------
   // <T>��õ������ȡ�</T>
   MO_INLINE TInt64 LengthPop(){
      return _lengthPop;
   }
   //------------------------------------------------------------
   // <T>��û���ء�</T>
   MO_INLINE FStreamBlockPool* Pool(){
      return _pPool;
   }
   //------------------------------------------------------------
   // <T>��û����ռ�����</T>
   MO_INLINE FBufferedQueueBlockAllocator* Allocator(){
      return (FBufferedQueueBlockAllocator*)_pPool->Allocator();
   }
   //------------------------------------------------------------
   // <T>���û����ռ�����</T>
   MO_INLINE void SetAllocator(FBufferedQueueBlockAllocator* pAllocator){
      _pPool->SetAllocator(pAllocator);
   }
   //------------------------------------------------------------
   // <T>��ö�ȡ�鼯�ϡ�</T>
   MO_INLINE FBufferedQueueBlockList* ReadBlocks(){
      return _pReadBlocks;
   }
   //------------------------------------------------------------
   // <T>���д��鼯�ϡ�</T>
   MO_INLINE FBufferedQueueBlockList* WriteBlocks(){
      return _pWriteBlocks;
   }
protected:
   TBool InnerPush(TAnyC* pData, TInt length);
   TInt InnerPop(TAny* pData, TInt capacity);
public:
   TInt Count();
   TBool TestPushAble(TInt length);
   TBool TestPopAble();
public:
   TBool Push(TAnyC* pData, TInt length);
   TInt Pop(TAny* pData, TInt capacity);
   TBool BlockedPush(TAnyC* pData, TInt length);
   TInt BlockedPop(TAny* pData, TInt capacity);
public:
   TBool FetchInfo(SQueueInfo* pInfo);
   void Dump();
};

//============================================================
// <T>���ݹܵ���</T>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CM_DECLARE FSharedPipe :
      public FObject,
      public MShared,
      public MPipe{
protected:
   TSize _capacity;
   SPipeInfo* _gInfo;
   TByte* _gData;
public:
   FSharedPipe();
   FSharedPipe(TSize capacity);
   MO_ABSTRACT ~FSharedPipe(){
   }
public:
   static TSize CalculateCapacity(TSize capacity);
public:
   TSize Capacity();
   void SetCapacity(TSize capacity);
   MO_OVERRIDE void OnSharedInitialize();
   MO_OVERRIDE void OnSharedLink(TShareSegment& segment);
   MO_OVERRIDE TSize SharedCapacity();
public:
   MO_OVERRIDE SPipeInfo* Info();
   MO_OVERRIDE SPipeAtom Atom();
public:
   MO_ABSTRACT TBool Create();
public:
   MO_OVERRIDE TBool IsEmpty();
   MO_OVERRIDE TInt Length();
   MO_OVERRIDE TInt Reamin();
   TBool Reset();
};

//============================================================
// <T>���ݶ��С�</T>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CM_DECLARE FSharedQueue : public FSharedPipe{
public:
   FSharedQueue();
   FSharedQueue(TSize capacity);
   MO_ABSTRACT ~FSharedQueue(){
   }
public:
   TBool FollowPush(TInt size);
public:
   TBool Push(TAnyC* pData, TInt size);
   TBool TryPush(TAnyC* pData, TInt size);
   TInt Pop(TAny* pData, TInt capacity);
public:
   TBool BlockedPush(TAnyC* pData, TInt size);
   TInt BlockedPop(TAny* pData, TInt capacity);
	TBool DumpInfo(TChar* pTag);
};

//============================================================
// <T>���ݶ��С�</T>
//
// @history 100309 MAOCY ����
//============================================================
class MO_CM_DECLARE FSharedQueueConnection : public MShared{
protected:
   FSharedQueue* _pInputQueue;
   FSharedQueue* _pOutputQueue;
public:
   FSharedQueueConnection();
   FSharedQueueConnection(TSize inputCapacity, TSize outputCapacity);
   MO_ABSTRACT ~FSharedQueueConnection();
public:
   void SetInputCapacity(TSize capacity);
   void SetOutputCapacity(TSize capacity);
   MO_OVERRIDE void OnSharedLink(TShareSegment& segment);
   MO_OVERRIDE TSize SharedCapacity();
public:
   FSharedQueue* InputQueue();
   FSharedQueue* OutputQueue();
};

MO_NAMESPACE_END

#endif // __MO_CM_PIPE_H__
