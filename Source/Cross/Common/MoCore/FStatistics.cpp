#include "MoCrStatistics.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FStatistics, FInstance);

//============================================================
// <T>����ͳ������</T>
//============================================================
FStatistics::FStatistics(){
   _code = 0;
   Reset();
}

//============================================================
// <T>����ͳ������</T>
//============================================================
FStatistics::~FStatistics(){
}

//============================================================
// <T>���´���</T>
//
// @param result ���
// @return ������
//============================================================
TResult FStatistics::Update(TBool result){
   _count++;
   if(!result){
      _failureCount++;
   }
   TTimeSpan span = _endTick - _beginTick;
   // ������Сʱ��
   if(_minSpan == 0){
      _minSpan = span;
   }else if(span < _minSpan){
      _minSpan = span;
   }
   // �������ʱ��
   if(_maxSpan == 0){
      _maxSpan = span;
   }else if(span > _maxSpan){
      _maxSpan = span;
   }
   // ���ִ���ٶ� (10����)
   if(span > 10000){
      _slowCount++;
   }
   // ������ʱ��
   _currentSpan = span;
   _countSpan += span;
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @param result ���
// @return ������
//============================================================
TResult FStatistics::Finish(TBool result){
   End();
   return Update(result);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FStatistics::Reset(){
   _count = 0;
   _failureCount = 0;
   _slowCount = 0;
   _beginTick = 0;
   _endTick = 0;
   _minSpan = 0;
   _currentSpan = 0;
   _maxSpan = 0;
   _countSpan = 0;
   return ESuccess;
}

//============================================================
// <T>��ø�����Ϣ��</T>
//
// @return ������
//============================================================
TResult FStatistics::Dump(MString* pDump){
   MO_ASSERT(pDump);
   TTimeTick averageSpan = AverageTick();
   pDump->AppendFormat(TC("%-40s: count=%6d, span=%6lld (%6lld ~ %6lld), average_span=%6lld, count_span=%8lld"),
         (TCharC*)_name, _count, _currentSpan, _minSpan, _maxSpan, averageSpan, _countSpan);
   return ESuccess;
}

//============================================================
// <T>��ʾ������Ϣ��</T>
//
// @return ������
//============================================================
TResult FStatistics::Track(){
   TFsDump dump;
   TResult resultCd = Dump(&dump);
   MO_INFO((TCharC*)dump);
   return resultCd;
}

MO_NAMESPACE_END
