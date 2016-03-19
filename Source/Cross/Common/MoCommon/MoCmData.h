#ifndef __MO_CM_DATA_H__
#define __MO_CM_DATA_H__
//------------------------------------------------------------
#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_COLLECTION_H__
#include "MoCmCollection.h"
#endif // __MO_CM_COLLECTION_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

#ifndef __MO_CM_DICTIONARY_H__
#include "MoCmDictionary.h"
#endif // __MO_CM_DICTIONARY_H__

#ifndef __MO_CM_LOCK_H__
#include "MoCmLock.h"
#endif // __MO_CM_LOCK_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ඨ�塣</T>
class ISqlConnection;
class FDatasetMeta;
class FDataset;

//============================================================
// <T>��¼��š�</T>
typedef TInt64 TRecordId;
typedef FVector<TRecordId> FRecordIdVector;
// <T>SQL�ص�������</T>
typedef TInt (*HSqlConnectionCommandInvoker)(ISqlConnection* pConnection, TCharC* pSql, TInt sqlResult, TAny* pParams);

//============================================================
// <T>����ģʽ��</T>
//
// @history 130420 MAOCY ����
//============================================================
enum ESqlMode{
   ESqlMode_Ansy = 0x01,
   ESqlMode_Sync = 0x02,
};

//============================================================
// <T>���ݱ�־��</T>
//
// @history 130420 MAOCY ����
//============================================================
enum ESqlFlag{
   ESqlFlag_Transaction  = 0x01,
   ESqlFlag_Statement    = 0x02,
   ESqlFlag_MultiExecute = 0x04,
};

//============================================================
// <T>���ݲ�����</T>
//
// @history 130422 MAOCY ����
//============================================================
enum ESqlProcess{
   ESqlProcess_Unknown   = 0,
   ESqlProcess_Select    = 1,
   ESqlProcess_Find      = 2,
   ESqlProcess_Fetch     = 3,
   ESqlProcess_Insert    = 4,
   ESqlProcess_Update    = 5,
   ESqlProcess_Delete    = 6,
   ESqlProcess_Function  = 7,
   ESqlProcess_Procedure = 8,
   ESqlProcess_Process   = 9,
   ESqlProcess_Command   = 10,
   ESqlProcess_Count     = 11,
};

//============================================================
// <T>���ݼ���</T>
//
// @history 130425 MAOCY ����
//============================================================
enum ESqlLevel{
   ESqlLevel_Unknown     = 0x00,
   ESqlLevel_Delay       = 0x01,
   ESqlLevel_Immediately = 0x02,
   ESqlLevel_Check       = 0x03,
   ESqlLevel_Count       = 0x04,
};

//============================================================
// <T>�������͡�</T>
//
// @history 100109 MAOCY ����
//============================================================
enum ESqlType{
   ESqlType_Unknown = 0x00,
   ESqlType_Boolean = 0x01,
   ESqlType_Integer = 0x02,
   ESqlType_Float   = 0x03,
   ESqlType_Date    = 0x04,
   ESqlType_String  = 0x05,
   ESqlType_Memo    = 0x06
};

//============================================================
// <T>���ݽ����</T>
//
// @history 100109 MAOCY ����
//============================================================
enum ESqlResult{
   ESqlResult_Success    =  0,
   ESqlResult_Disconnect = -1,
   ESqlResult_Execute    = -2,
};

//============================================================
// <T>�첽�����ַ�����</T>
//
// @history 130422 MAOCY ����
//============================================================
class MO_CM_DECLARE SAnsySql{
public:
   FDatasetMeta* metaPtr;
   ESqlProcess processCd;
   ESqlLevel levelCd;
   TRecordId recordId;
   TCharC* sqlPtr;
   HSqlConnectionCommandInvoker invoker;
   TAny* paramsPtr;
public:
   //------------------------------------------------------------
   // <T>�����첽�����ַ�����</T>
   SAnsySql(){
      MO_CLEAR(metaPtr);
      processCd = ESqlProcess_Unknown;
      levelCd = ESqlLevel_Unknown;
      recordId = 0;
      MO_CLEAR(sqlPtr);
      MO_CLEAR(invoker);
      MO_CLEAR(paramsPtr);
   }
};

//============================================================
// <T>�����ַ�����</T>
//
// @history 130422 MAOCY ����
//============================================================
class MO_CM_DECLARE MSql : public MString{
public:
   void AppendBoolean(TBool value);
   void AppendInteger(TInt value);
   void AppendString(TCharC* pValue, TInt length = -1);
   void AppendStringFormat(TCharC* pFormat, ...);
};
//------------------------------------------------------------
typedef FList<MSql*> FSqlList;

//============================================================
// <T>�����ַ�����</T>
//
// @history 130422 MAOCY ����
//============================================================
class MO_CM_DECLARE FSql :
      public FObject,
      public MSql{
public:
   FSql();
   MO_ABSTRACT ~FSql();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends, TBool force);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TCharC* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<TChar>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const MSql& value){
      Assign(value.MemoryC(), value.Length());
   }
};

//============================================================
// <T>�����ַ�����</T>
//
// @history 130422 MAOCY ����
//============================================================
class MO_CM_DECLARE TSql : public MSql{
protected:
   TChar _memory[MO_FS_SQL_MAX_LENGTH];
public:
   //------------------------------------------------------------
   // <T>���������ַ�����</T>
   TSql(){
      InnerInitialize();
   }
   //------------------------------------------------------------
   // <T>���������ַ�����</T>
   TSql(TCharC* pValue, TInt length = -1){
      InnerInitialize();
      Assign(pValue, length);
   }
   //------------------------------------------------------------
   // <T>���������ַ�����</T>
   TSql(const TPtrC<TChar>& ptr){
      InnerInitialize();
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>���������ַ�����</T>
   TSql(const TSql& value){
      InnerInitialize();
      Assign(value.MemoryC(), value.Length());
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(){
      _pMemory = _memory;
      _capacity = MO_FS_SQL_MAX_LENGTH;
      _memory[0] = 0;
   }
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends){
      MO_ASSERT(size <= MO_FS_SQL_MAX_LENGTH);
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TCharC* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<TChar>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const MSql& value){
      Assign(value.MemoryC(), value.Length());
   }
public:
   //------------------------------------------------------------
   // <T>������ɳ��ȡ�</T>
   MO_INLINE static TInt Size(){
      return MO_FS_SQL_MAX_LENGTH;
   }
};

//============================================================
// <T>�����ַ������塣</T>
//
// @history 130422 MAOCY ����
//============================================================
class FSqlPool : public FPool<FSql*>{
protected:
   TThreadLocker _locker;
public:
   FSqlPool();
   MO_ABSTRACT ~FSqlPool();
public:
   //------------------------------------------------------------
   // <T>��������ַ������塣</T>
   MO_INLINE IThreadLocker* Locker(){
      return &_locker;
   }
public:
   FSql* Alloc();
   void Free(FSql* pSql);
};

//============================================================
// <T>�����ֶΡ�</T>
//
// @history 100108 MAOCY ����
//============================================================
class MO_CM_DECLARE FField{
protected:
   TFsName _name;
   ESqlType _type;
public:
   FField();
   ~FField();
public:
   TCharC* Name();
   ESqlType Type();
   void SetName(TCharC* pName);
   void SetType(ESqlType type);
};

//============================================================
// <T>�����ֶμ��ϡ�</T>
//
// @history 100108 MAOCY ����
//============================================================
class MO_CM_DECLARE FFields : public FDictionary<FField*>{
public:
};

//============================================================
// <T>�����ж���</T>
//
// @history 100108 MAOCY ����
//============================================================
class MO_CM_DECLARE FRow : public FObject{
protected:
   FDataset* _pDataset;
   FStringArray* _pValues;
public:
   FRow(FDataset* pDataset);
   MO_ABSTRACT ~FRow();
public:
   TCharC* operator[](TInt index);
   TCharC* operator[](TCharC* pName);
public:
   TCharC* Get(TInt index);
   TCharC* Get(TCharC* pName);
   void Set(TInt index, TCharC* pValue);
   void Set(TCharC* pName, TCharC* pValue);
};

//============================================================
// <T>���ݼ��Ͻӿڡ�</T>
//============================================================
class MO_CM_DECLARE IDataset{
public:
   //------------------------------------------------------------
   // <T>�������ݼ��Ͻӿڡ�</T>
   MO_ABSTRACT ~IDataset(){
   }
public:
   MO_VIRTUAL TInt Count() = 0;
   MO_VIRTUAL TAny** Ptrs() = 0;
public:
   MO_VIRTUAL void ForceCount(TInt count) = 0;
};

//============================================================
// <T>���ݼ�����Ϣ��</T>
//============================================================
class MO_CM_DECLARE FDatasetMeta : public FObject{
protected:
   TInt _logicCode;
   TCharC* _pLogicName;
   TCharC* _pDataName;
   TCharC* _pDataFields;
   TInt64 _counters[ESqlProcess_Count];
public:
   FDatasetMeta();
   MO_ABSTRACT ~FDatasetMeta();
public:
   //------------------------------------------------------------
   // <T>����߼����롣</T>
   MO_INLINE TInt LogicCode(){
      return _logicCode;
   }
   //------------------------------------------------------------
   // <T>�����߼����롣</T>
   MO_INLINE void SetLogicCode(TInt logicCode){
      _logicCode = logicCode;
   }
   //------------------------------------------------------------
   // <T>����߼����ơ�</T>
   MO_INLINE TCharC* LogicName(){
      return _pLogicName;
   }
   //------------------------------------------------------------
   // <T>�����߼����ơ�</T>
   MO_INLINE void SetLogicName(TCharC* pLogicName){
      _pLogicName = pLogicName;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* DataName(){
      return _pDataName;
   }
   //------------------------------------------------------------
   // <T>�����������ơ�</T>
   MO_INLINE void SetDataName(TCharC* pDataName){
      _pDataName = pDataName;
   }
   //------------------------------------------------------------
   // <T>��������ֶμ��ϡ�</T>
   MO_INLINE TCharC* DataFields(){
      return _pDataFields;
   }
   //------------------------------------------------------------
   // <T>���������ֶμ��ϡ�</T>
   MO_INLINE void SetDataFields(TCharC* pDataFields){
      _pDataFields = pDataFields;
   }
public:
   //------------------------------------------------------------
   // <T>��ô������͵�������</T>
   MO_INLINE TInt64 ProcessTotal(ESqlProcess processCd){
      return _counters[processCd];
   }
   //------------------------------------------------------------
   // <T>���ô������͵�������</T>
   MO_INLINE void SetProcessTotal(ESqlProcess processCd, TInt64 total){
      _counters[processCd] = total;
   }
public:
   MO_ABSTRACT TBool Setup();
public:
   MO_OVERRIDE void Process(ESqlProcess processCd);
   MO_OVERRIDE void Reset();
public:
   MO_OVERRIDE void Dump(MString* pDump);
};
//------------------------------------------------------------
typedef FVector<FDatasetMeta*> FDatasetMetaVecrtor;
typedef FList<FDatasetMeta*> FDatasetMetaList;

//============================================================
// <T>���ݼ��϶���</T>
//
// @history 091208 MAOCY ����
//============================================================
class MO_CM_DECLARE FDataset :
      public FList<FRow*>,
      public IDataset{
protected:
   FFields* _pFields;
public:
   FDataset();
   MO_ABSTRACT ~FDataset();
public:
   FFields* Fields();
   FRow* CreateRow();
public:
   MO_OVERRIDE TInt Count();
   MO_OVERRIDE TAny** Ptrs();
public:
   MO_OVERRIDE void ForceCount(TInt count);
};

//============================================================
// <T>���ݼ��ϡ�</T>
//============================================================
template <typename T>
class MO_CM_DECLARE TDataset{
public:
   typedef FList<T*> FRowList;
protected:
   TInt _count;
   FRowList* _pRows;
   T** _ppPtrs;
public:
   //------------------------------------------------------------
   // <T>�������ݼ��ϡ�</T>
   TDataset(){
      _count = 0;
      _pRows = MO_CREATE(FRowList);
      MO_CLEAR(_ppPtrs);
   }
   //------------------------------------------------------------
   // <T>�������ݼ��ϡ�</T>
   ~TDataset(){
      TListIteratorC<T*> iterator = _pRows->IteratorC();
      while(iterator.Next()){
         T* pRow = *iterator;
         MO_DELETE(pRow);
      }
      MO_DELETE(_pRows);
      MO_FREE(_ppPtrs);
   }
public:
   //------------------------------------------------------------
   // <T>����һ���ж���</T>
   MO_INLINE T* CreateRow(){
      T* pRow = MO_TYPE_ALLOC(T);
      RType<T>::Clear(pRow);
      _pRows->Push(pRow);
      return pRow;
   }
public:
   //------------------------------------------------------------
   // <T>����Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (0 == _count);
   }
   //------------------------------------------------------------
   // <T>��ø�����</T>
   MO_OVERRIDE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>��ö���</T>
   MO_INLINE T* Get(TInt index){
      if((index >= 0) && (index < _count) && (NULL != _ppPtrs)){
         return _ppPtrs[index];
      }
   }
   //------------------------------------------------------------
   // <T>�����ָ�뼯�ϡ�</T>
   MO_OVERRIDE TAny** Ptrs(){
      if(_count != _pRows->Count()){
         // �ͷ��ڴ�
         MO_FREE(_ppPtrs);
         // �ռ��ڴ�
         TInt n = 0;
         TInt count = _pRows->Count();
         _ppPtrs = MO_TYPES_ALLOC(T*, count);
         TListIteratorC<T*> iterator = _pRows->IteratorC();
         while(iterator.Next()){
            _ppPtrs[n++] = *iterator;
         }
         _count = count;
      }
      return _ppPtrs;
   }
public:
   //------------------------------------------------------------
   // <T>ǿ����������</T>
   MO_OVERRIDE void ForceCount(TInt count){
      TInt loop = count - _pRows->Count();
      for(TInt n = 0; n < loop; n++){
         CreateRow();
      }
      _count = count;
   }
};

//============================================================
// <T>�����ӿڡ�</T>
//
// @history 091208 MAOCY ����
//============================================================
class MO_CM_DECLARE ISqlRowFieldFill{
public:
   //------------------------------------------------------------
   // <T>���������ӿڡ�</T>
   MO_ABSTRACT ~ISqlRowFieldFill(){
   }
public:
   MO_VIRTUAL void Fill(TCharC* pName, TCharC* pValue) = 0;
};

//============================================================
// <T>�����ӿڡ�</T>
//
// @history 091208 MAOCY ����
//============================================================
class MO_CM_DECLARE ISqlRowFill{
public:
   //------------------------------------------------------------
   // <T>���������ӿڡ�</T>
   MO_ABSTRACT ~ISqlRowFill(){
   }
public:
   MO_VIRTUAL void Fill(TChar** ppValues, TInt count) = 0;
};

//============================================================
// <T>��������ӿڡ�</T>
//
// @history 091208 MAOCY ����
//============================================================
class MO_CM_DECLARE ISqlRowFiller{
public:
   //------------------------------------------------------------
   // <T>������������ӿڡ�</T>
   MO_ABSTRACT ~ISqlRowFiller(){
   }
public:
   MO_VIRTUAL void Fill(TAny* pRow, TChar** ppValues, TInt count) = 0;
};

//============================================================
// <T>�������ӽӿڡ�</T>
//
// @history 091208 MAOCY ����
//============================================================
class MO_CM_DECLARE ISqlConnection{
public:
   //------------------------------------------------------------
   // <T>�����������ӽӿڡ�</T>
   MO_ABSTRACT ~ISqlConnection(){
   }
public:
   MO_VIRTUAL TInt Id() = 0;
   MO_VIRTUAL TInt Type() = 0;
   MO_VIRTUAL TCharC* Host() = 0;
   MO_VIRTUAL TUint16 Port() = 0;
   MO_VIRTUAL TCharC* UserName() = 0;
   MO_VIRTUAL TCharC* Password() = 0;
   MO_VIRTUAL TCharC* Database() = 0;
   MO_VIRTUAL TCharC* Charset() = 0;
   MO_VIRTUAL ESqlMode ModeCd() = 0;
   MO_VIRTUAL void SetModeCd(ESqlMode modeCd) = 0;
   MO_VIRTUAL TBool IsSupport(ESqlFlag flagCd) = 0;
   MO_VIRTUAL TInt Flag() = 0;
   MO_VIRTUAL TBool IsConnected() = 0;
public:
   MO_VIRTUAL TInt64 CounterTotal() = 0;
   MO_VIRTUAL TInt64 CounterGet(ESqlProcess processCd) = 0;
   MO_VIRTUAL void CounterSet(ESqlProcess processCd, TInt64 total) = 0;
   MO_VIRTUAL void CounterProcess(ESqlProcess processCd) = 0;
   MO_VIRTUAL void CounterReset() = 0;
public:
   MO_VIRTUAL TBool Connect(TCharC* pHost = NULL, TInt port = 0, TCharC* pUserName = NULL, TCharC* pPassword = NULL, TCharC* pDatabase = NULL) = 0;
   MO_VIRTUAL TBool Reconnect() = 0;
   MO_VIRTUAL TBool Begin(TBool flag = ETrue) = 0;
   MO_VIRTUAL TBool Commit() = 0;
   MO_VIRTUAL TBool Rollback() = 0;
   MO_VIRTUAL TBool Close() = 0;
public:
   MO_VIRTUAL TInt ExecuteInsertSql(TCharC* pSql, TRecordId& recordId) = 0;
   MO_VIRTUAL TInt ExecuteSql(TCharC* pSql, ESqlProcess processCd = ESqlProcess_Unknown) = 0;
   MO_VIRTUAL TBool ExecuteAnsySql(SAnsySql* pSql) = 0;
   MO_VIRTUAL TBool ExecuteExist(TCharC* pSql) = 0;
   MO_VIRTUAL TBool ExecuteInteger(TCharC* pSql, TInt64& value) = 0;
   MO_VIRTUAL TBool ExecuteString(TCharC* pSql, TChar* pValue, TInt capacity) = 0;
public:
   MO_VIRTUAL TBool Find(TCharC* pSql, ISqlRowFill* piFill) = 0;
   MO_VIRTUAL TBool Find(TCharC* pSql, ISqlRowFieldFill* piFieldFill) = 0;
   MO_VIRTUAL TBool Find(TCharC* pSql, ISqlRowFiller* piFiller, TAny* pRow) = 0;
   MO_VIRTUAL TInt Fetch(TCharC* pSql, ISqlRowFill** ppiFills, TInt count) = 0;
   MO_VIRTUAL TInt Fetch(TCharC* pSql, ISqlRowFiller* piFiller, TAny** ppRows, TInt count) = 0;
   MO_VIRTUAL TInt Fetch(TCharC* pSql, ISqlRowFiller* piFiller, IDataset* pDataset) = 0;
public:
   MO_VIRTUAL IThreadLocker* Locker() = 0;
   MO_VIRTUAL TBool TestTimeout(TDateTime current) = 0;
   MO_VIRTUAL TBool Refresh() = 0;
   MO_VIRTUAL TBool Free() = 0;
};
//------------------------------------------------------------
typedef FVector<ISqlConnection*> FSqlConnectionVector;
typedef FList<ISqlConnection*> FSqlConnectionList;

//============================================================
// <T>���ݿ����ӡ�</T>
//============================================================
class MO_CM_DECLARE FSqlConnection :
      public FObject,
      public ISqlConnection{
protected:
   TInt _id;
   TInt _type;
   TFsName _host;
   TUint16 _port;
   TFsName _username;
   TFsName _password;
   TFsName _database;
   TFsName _charset;
   ESqlMode _modeCd;
   TInt _flag;
protected:
   TBool _initialized;
   TBool _connected;
   TBool _errored;
   TBool _supportTransaction;
   TBool _inTransaction;
   TBool _dirtyTransaction;
   TTimeSpan _freeTimeout;
   TDateTime _freeDate;
   TInt64 _counters[ESqlProcess_Count];
   TThreadLocker _locker;
public:
   FSqlConnection();
   MO_ABSTRACT ~FSqlConnection();
public:
   MO_OVERRIDE TInt Id();
   MO_OVERRIDE TInt Type();
   MO_OVERRIDE TCharC* Host();
   MO_OVERRIDE TUint16 Port();
   MO_OVERRIDE TCharC* UserName();
   MO_OVERRIDE TCharC* Password();
   MO_OVERRIDE TCharC* Database();
   MO_OVERRIDE TCharC* Charset();
   MO_OVERRIDE ESqlMode ModeCd();
   MO_OVERRIDE void SetModeCd(ESqlMode modeCd);
   MO_OVERRIDE TBool IsSupport(ESqlFlag flagCd);
   MO_OVERRIDE TInt Flag();
   MO_OVERRIDE TBool IsConnected();
public:
   //------------------------------------------------------------
   void SetId(TInt id);
   void SetType(TInt type);
   void SetHost(TCharC* pHost);
   void SetHostPort(TInt port);
   void SetUserName(TCharC* pUserName);
   void SetPassword(TCharC* pPassword);
   void SetDatabase(TCharC* pDatabase);
   void SetCharset(TCharC* pCharset);
   void SetFlag(TInt flag);
public:
   MO_OVERRIDE TInt64 CounterTotal();
   MO_OVERRIDE TInt64 CounterGet(ESqlProcess processCd);
   MO_OVERRIDE void CounterSet(ESqlProcess processCd, TInt64 total);
   MO_OVERRIDE void CounterProcess(ESqlProcess processCd);
   MO_OVERRIDE void CounterReset();
public:
   MO_OVERRIDE IThreadLocker* Locker();
   MO_OVERRIDE TBool TestTimeout(TDateTime current);
   MO_OVERRIDE TBool Refresh();
   MO_OVERRIDE TBool Free();
};

MO_NAMESPACE_END

#endif // __MO_CM_MEMORY_H__
