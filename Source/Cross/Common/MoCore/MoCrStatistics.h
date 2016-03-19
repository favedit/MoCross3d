#ifndef __MO_CR_STATISTICS_H__
#define __MO_CR_STATISTICS_H__

#ifndef __MO_CR_COMMON_H__
#include "MoCrCommon.h"
#endif // __MO_CR_COMMON_H__

#ifndef __MO_CR_SERVICE_H__
#include "MoCrService.h"
#endif // __MO_CR_SERVICE_H__

MO_NAMESPACE_BEGIN

//============================================================
class FStatisticsConsole;

//============================================================
// <T>ͳ�Ʊ�š�</T>
typedef TUint32 TStatisticsId;
//============================================================
// <T>ͳ�Ʊ��</T>
// [16Bit] = 65536 ��������
// [16Bit] = 65536 ������
//============================================================
union SStatisticsData{
   TUint32 value;
   struct{
      TUint16 groupId;
      TUint16 itemId;
   } items;
};
//------------------------------------------------------------
struct MO_CR_DECLARE SStatisticsId{
public:
   SStatisticsData data;
public:
   //------------------------------------------------------------
   // <T>����ͳ�Ʊ��</T>
   SStatisticsId(){
      data.value = 0;
   }
   //------------------------------------------------------------
   // <T>����ͳ�Ʊ��</T>
   SStatisticsId(TStatisticsId id){
      data.value = id;
   }
   //------------------------------------------------------------
   // <T>����ͳ�Ʊ��</T>
   SStatisticsId(TUint16 groupId, TUint16 itemId){
      data.items.groupId = groupId;
      data.items.itemId = itemId;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator==(TStatisticsId value){
      return (data.value == value);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ȡ�</T>
   MO_INLINE TBool operator!=(TStatisticsId value){
      return (data.value != value);
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void operator=(TStatisticsId value){
      data.value = value;
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE operator TStatisticsId(){
      return data.value;
   }
public:
   //------------------------------------------------------------
   // <T>��÷����š�</T>
   MO_INLINE TUint16 GroupId(){
      return data.items.groupId;
   };
   //------------------------------------------------------------
   // <T>���÷����š�</T>
   MO_INLINE void SetGroupId(TUint16 groupId){
      data.items.groupId = groupId;
   };
   //------------------------------------------------------------
   // <T>�����Ŀ��š�</T>
   MO_INLINE TUint16 ItemId(){
      return data.items.itemId;
   };
   //------------------------------------------------------------
   // <T>������Ŀ��š�</T>
   MO_INLINE void SetItemHandle(TUint16 itemId){
      data.items.itemId = itemId;
   };
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���Ч��</T>
   MO_INLINE TBool IsValid(){
      return (data.value != 0);
   };
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE TStatisticsId Get(){
      return data.value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Set(TStatisticsId value){
      data.value = value;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void Reset(){
      data.value = 0;
   }
public:
   //------------------------------------------------------------
   // <T>�����ʾ��Ϣ��</T>
   TCharC* ToDisplay(TChar* pText, TSize capacity){
      TStringRefer text(pText, capacity);
      text.AssignFormat(TC("%04X:%04X"), data.items.groupId, data.items.itemId);
      return pText;
   }
};

//============================================================
// <T>ͳ�����ӿڡ�</T>
//
// @face
//============================================================
class MO_CR_DECLARE IStatistics{
public:
   //------------------------------------------------------------
   // <T>����ͳ����Ϣ��</T>
   MO_ABSTRACT ~IStatistics(){
   }
public:
   MO_VIRTUAL TStatisticsId Code() = 0;
public:
   MO_VIRTUAL void Begin() = 0;
   MO_VIRTUAL void End() = 0;
public:
   MO_VIRTUAL TResult Update(TBool result = ETrue) = 0;
   MO_VIRTUAL TResult Reset() = 0;
};
//------------------------------------------------------------
typedef FSet<TStatisticsId, IStatistics*> FStatisticsSet;

//============================================================
// <T>ͳ�ƴ������ӿڡ�</T>
//
// @face
//============================================================
class MO_CR_DECLARE IStatisticsTrigger{
public:
   //------------------------------------------------------------
   // <T>����ͳ�ƴ������ӿڡ�</T>
   MO_ABSTRACT ~IStatisticsTrigger(){
   }
public:
   MO_VIRTUAL TResult StatisticsRefresh() = 0;
};
//------------------------------------------------------------
typedef FList<IStatisticsTrigger*> FStatisticsTriggerList;

//============================================================
// <T>ͳ������</T>
//
// @class
//============================================================
class MO_CR_DECLARE FStatistics :
      public FInstance,
      public IStatistics
{
   MO_CLASS_DECLARE_INHERITS(FStatistics, FInstance);
protected:
   // @attribtue ����
   TString _name;
   // @attribtue ����
   TStatisticsId _code;
   // @attribtue ִ�д���
   TInt _count;
   // @attribtue ʧ�ܴ���
   TInt _failureCount;
   // @attribtue ִ��������
   TInt _slowCount;
   // @attribtue ��ʼʱ��
   TTimeTick _beginTick;
   // @attribtue ����ʱ��
   TTimeTick _endTick;
   // @attribtue ��Сʱ��
   TTimeSpan _minSpan;
   // @attribtue ��ǰʱ��
   TTimeSpan _currentSpan;
   // @attribtue ���ʱ��
   TTimeSpan _maxSpan;
   // @attribtue ����ʱ��ͳ��
   TTimeSpan _countSpan;
public:
   FStatistics();
   MO_ABSTRACT ~FStatistics();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE TStatisticsId Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>���ô��롣</T>
   MO_INLINE void SetCode(TStatisticsId code){
      _code = code;
   }
   //------------------------------------------------------------
   // <T>���ִ�д�����</T>
   MO_INLINE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>���ʧ�ܴ�����</T>
   MO_INLINE TInt FailureCount(){
      return _failureCount;
   }
   //------------------------------------------------------------
   // <T>���ִ����������</T>
   MO_INLINE TInt SlowCount(){
      return _slowCount;
   }
   //------------------------------------------------------------
   // <T>��ÿ�ʼʱ�̡�</T>
   MO_INLINE TTimeTick BeginTick(){
      return _beginTick;
   }
   //------------------------------------------------------------
   // <T>��ý���ʱ�̡�</T>
   MO_INLINE TTimeTick EndTick(){
      return _endTick;
   }
   //------------------------------------------------------------
   // <T>�����Сʱ�Ρ�</T>
   MO_INLINE TTimeSpan MinSpan(){
      return _minSpan;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰʱ�Ρ�</T>
   MO_INLINE TTimeSpan CurrentSpan(){
      return _currentSpan;
   }
   //------------------------------------------------------------
   // <T>������ʱ�Ρ�</T>
   MO_INLINE TTimeSpan MaxTick(){
      return _maxSpan;
   }
   //------------------------------------------------------------
   // <T>��ô���ʱ��ͳ�ơ�</T>
   MO_INLINE TTimeTick CountSpan(){
      return _countSpan;
   }
   //------------------------------------------------------------
   // <T>���ƽ��ִ��ʱ�̡�</T>
   MO_INLINE TTimeTick AverageTick(){
      if(_count > 0){
         return _countSpan / _count;
      }
      return 0;
   }
public:
   //------------------------------------------------------------
   // <T>��ʼ����</T>
   MO_ABSTRACT void Begin(){
      _beginTick = RTimeTick::Current();
   }
   //------------------------------------------------------------
   // <T>��������</T>
   MO_ABSTRACT void End(){
      _endTick = RTimeTick::Current();
   }
public:
   MO_ABSTRACT TResult Update(TBool result = ETrue);
   MO_ABSTRACT TResult Finish(TBool result = ETrue);
   MO_ABSTRACT TResult Reset();
public:
   MO_ABSTRACT TResult Dump(MString* pDump);
   MO_ABSTRACT TResult Track();
};
//------------------------------------------------------------
typedef MO_CR_DECLARE GPtr<FStatistics> GStatisticsPtr;
typedef MO_CR_DECLARE FDictionary<FStatistics*> FStatisticsDictionary;

//============================================================
// <T>ͳ����Ϣ��������</T>
//
// @class
//============================================================
class MO_CR_DECLARE FStatisticsMonitor : public FMonitor{
protected:
   FStatisticsConsole* _pConsole;
public:
   FStatisticsMonitor();
   MO_ABSTRACT ~FStatisticsMonitor();
public:
   //------------------------------------------------------------
   // <T>��ô�������</T>
   MO_INLINE FStatisticsConsole* Console(){
      return _pConsole;
   }
   //------------------------------------------------------------
   // <T>���ô�������</T>
   MO_INLINE void SetConsole(FStatisticsConsole* pConsole){
      _pConsole = pConsole;
   }
public:
   MO_OVERRIDE TResult Process();
};

//============================================================
// <T>ͳ����Ϣ����̨��</T>
//
// @class
// @history 130407 MAOCY ����
//============================================================
class MO_CR_DECLARE FStatisticsConsole : public FConsole{
protected:
   FStatisticsDictionary* _pStatisticsDictionary;
   FStatisticsSet* _pStatisticsSet;
   FStatisticsTriggerList* _pStatisticsTriggers;
   FStatisticsMonitor* _pMonitor;
public:
   FStatisticsConsole();
   MO_ABSTRACT ~FStatisticsConsole();
public:
   //------------------------------------------------------------
   // <T>���ͳ�������ϡ�</T>
   MO_INLINE FStatisticsSet* StatisticsSet(){
      return _pStatisticsSet;
   }
   //------------------------------------------------------------
   // <T>��ô��������ϡ�</T>
   MO_INLINE FStatisticsTriggerList* StatisticsTriggers(){
      return _pStatisticsTriggers;
   }
   //------------------------------------------------------------
   // <T>��ü�������</T>
   MO_INLINE FStatisticsMonitor* Monitor(){
      return _pMonitor;
   }
public:
   FStatistics* SyncByName(TCharC* pName, FClass* pClass = NULL);
   //------------------------------------------------------------
   // <T>��������ͬ��ͳ����Ϣ��</T>
   template <class T>
   MO_INLINE T* SyncByName(TCharC* pName){
      FInstance* pInstance = SyncByName(pName, T::Class());
      return pInstance->Convert<T>();
   }
public:
   IStatistics* StatisticsFind(TStatisticsId code);
   IStatistics* StatisticsFind(TInt groupId, TInt itemId);
   IStatistics* StatisticsSync(TStatisticsId code);
   IStatistics* StatisticsSync(TInt groupId, TInt itemId);
public:
   TResult StatisticsRegister(IStatistics* pStatistics);
   TResult StatisticsUnregister(IStatistics* pStatistics);
public:
   TResult TriggerRegister(IStatisticsTrigger* pTrigger);
   TResult TriggerUnregister(IStatisticsTrigger* pTrigger);
public:
   TResult StartupMonitor();
   MO_OVERRIDE TResult TriggerRefresh(TTimeTick currentTick);
public:
   MO_ABSTRACT TResult Reset();
   MO_ABSTRACT TResult Track();
};

//============================================================
// <T>ͳ����Ϣ��������</T>
//============================================================
class MO_CR_DECLARE RStatisticsManager : public RSingleton<FStatisticsConsole>{
};

MO_NAMESPACE_END

#endif // __MO_CR_STATISTICS_H__
