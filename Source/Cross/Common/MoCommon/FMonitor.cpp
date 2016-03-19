#include "MoCmXml.h"
#include "MoCmMonitor.h"

#define MO_MONITOR_INTERVAL 1000000
#define MO_TAG_PROPERTY     TC("Property")
#define MO_PTY_NAME         TC("name")

MO_NAMESPACE_BEGIN

MO_CLASS_ABSTRACT_IMPLEMENT_INHERITS(FMonitor, FInstance);

//============================================================
// <T>��������������ʵ����</T>
//
// @return ��ǰʵ��ָ��
//============================================================
FMonitor::FMonitor(){
   _name = TC("Monitor");
   _lock = ETrue;
   _needDelay = ETrue;
   _delay = 0;
   _interval = MO_MONITOR_INTERVAL;
   _processCount = 1;
   _processTimeout = 0;
   _currentDateTime = RDateTime::Current();
   _currentTimeTick = RTimeTick::Current();
   _currentTimeSpan = 0;
   _lastTimeTick = _currentTimeTick;
   _total = 0;
   _count = 0;
   _started = EFalse;
   MO_CLEAR(_pCatcher);
}

//============================================================
// <T>���������������ʵ����</T>
//
// @return ��ǰʵ��ָ��
//============================================================
FMonitor::~FMonitor(){
}

//============================================================
// <T>�ж��Ƿ�ָ�����ơ�</T>
//
// @param pName ����
// @return �Ƿ�
//============================================================
TBool FMonitor::IsName(TCharC* pName) const{
   return _name.Equals(pName);
}

//============================================================
// <T>������ơ�</T>
//
// @return ����
//============================================================
TCharC* FMonitor::Name() const{
   return _name;
}

//============================================================
// <T>�������ơ�</T>
//
// @param pName ����
//============================================================
void FMonitor::SetName(TCharC* pName){
   _name = pName;
}

//============================================================
// <T>���������</T>
//
// @return ����
//============================================================
TBool FMonitor::IsLock() const{
   return _lock;
}

//============================================================
// <T>���������</T>
//
// @return ����
//============================================================
TInt64 FMonitor::Total() const{
   return _total;
}

//============================================================
// <T>����������</T>
//
// @param total ����
//============================================================
void FMonitor::SetTotal(TInt64 total){
   _total = total;
}

//============================================================
// <T>��ô�����</T>
//
// @return ����
//============================================================
TInt64 FMonitor::Count() const{
   return _count;
}

//============================================================
// <T>�����ʱ��</T>
//
// @return ��ʱ
//============================================================
TTimeSpan FMonitor::Delay() const {
   return _delay;
}

//============================================================
// <T>������ʱ��</T>
//
// @param delay ��ʱ
//============================================================
void FMonitor::SetDelay(TTimeSpan delay){
   _delay = delay;
}

//============================================================
// <T>��ü����</T>
//
// @return ���
//============================================================
TTimeSpan FMonitor::Interval() const {
   return _interval;
}

//============================================================
// <T>���ü����</T>
//
// @param interval ���
//============================================================
void FMonitor::SetInterval(TTimeSpan interval){
   _interval = interval;
}

//============================================================
// <T>���ִ�д�����</T>
//
// @return ִ�д���
//============================================================
TInt64 FMonitor::ProcessCount() const{
   return _processCount;
}

//============================================================
// <T>����ִ�д�����</T>
//
// @param count ִ�д���
//============================================================
void FMonitor::SetProcessCount(TInt64 count){
   _processCount = count;
}

//============================================================
// <T>���ִ�г�ʱ��</T>
//
// @return ִ�г�ʱ
//============================================================
TTimeSpan FMonitor::ProcessTimeout() const{
   return _processTimeout;
}

//============================================================
// <T>���ִ�г�ʱ��</T>
//
// @param timeout ִ�г�ʱ
//============================================================
void FMonitor::SetProcessTimeout(TTimeSpan timeout){
   _processTimeout = timeout;
}

//============================================================
// <T>��õ�ǰʱ�䡣</T>
//
// @return ʱ��
//============================================================
TDateTime FMonitor::CurrentDateTime(){
   return _currentDateTime;
}

//============================================================
// <T>��õ�ǰʱ��̶ȡ�</T>
//
// @return ʱ��̶�
//============================================================
TTimeTick FMonitor::CurrentTimeTick(){
   return _currentDateTime;
}

//============================================================
// <T>��õ�ǰʱ��Ρ�</T>
//
// @return ʱ���
//============================================================
TTimeTick FMonitor::CurrentTimeSpan(){
   return _currentDateTime;
}

//============================================================
// <T>�����׽����</T>
//
// @return ��׽��
//============================================================
FCatcher* FMonitor::Catcher(){
   return _pCatcher;
}

//============================================================
// <T>������׽����</T>
//
// @param ��׽��
//============================================================
void FMonitor::SetCatcher(FCatcher* pCatcher){
   _pCatcher = pCatcher;
}

//============================================================
// <T>�����Ƿ�������С�</T>
//
// @param currentTick ��ǰʱ��
// @return �Ƿ����
//============================================================
TBool FMonitor::Test(TTimeTick currentTick){
   TTimeSpan interval = currentTick - _lastTimeTick;
   // �״���ʱ�ж�
   if(_needDelay){
      if(interval > _delay){
         return ETrue;
      }
   }
   // ����ѭ�ж�
   if(-1 == _total){
      if(interval > _interval){
         return ETrue;
      }
   }
   // ����ѭ���ж�
   if(_total  > 0){
      if(_count < _total){
         if(interval > _interval){
            return ETrue;
         }
      }
   }
   return EFalse;
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TBool FMonitor::LoadConfig(FXmlNode* pConfig){
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      if(iterator->IsName(MO_TAG_PROPERTY)){
         if(iterator->IsAttribute(MO_PTY_NAME, TC("lock"))){
            // ��ȡ����
            _lock = iterator->TextAsBool();
            MO_DEBUG(TC("Load monitor(%s) property. (lock=%d)"), (TCharC*)_name, _lock);
         }else if(iterator->IsAttribute(MO_PTY_NAME, TC("delay"))){
            // ��ȡ�ӳ�(����)
            TInt delay = iterator->TextAsInt();
            MO_DEBUG(TC("Load monitor(%s) property. (delay=%dms)"), (TCharC*)_name, delay);
            SetDelay(delay * 1000);
         }else if(iterator->IsAttribute(MO_PTY_NAME, TC("interval"))){
            // ��ȡ�ӳ�(����)
            TInt interval = iterator->TextAsInt(MO_MONITOR_INTERVAL);
            MO_DEBUG(TC("Load monitor(%s) property. (interval=%dms)"), (TCharC*)_name, interval);
            SetInterval(interval * 1000);
         }else if(iterator->IsAttribute(MO_PTY_NAME, TC("process_count"))){
            // ��ȡ�������
            TInt processCount = iterator->TextAsInt(MO_MONITOR_INTERVAL);
            MO_DEBUG(TC("Load monitor(%s) property. (process_count=%d)"), (TCharC*)_name, processCount);
            SetProcessCount(processCount);
         }else if(iterator->IsAttribute(MO_PTY_NAME, TC("process_timeout"))){
            // ��ȡ�ӳ�(����)
            TInt processTimeout = iterator->TextAsInt(MO_MONITOR_INTERVAL);
            MO_DEBUG(TC("Load monitor(%s) property. (process_timeout=%dms)"), (TCharC*)_name, processTimeout);
            SetProcessTimeout(processTimeout * 1000);
         }else if(iterator->IsAttribute(MO_PTY_NAME, TC("total"))){
            // ��ȡ��������
            TInt total = iterator->TextAsInt();
            MO_DEBUG(TC("Load monitor(%s) property. (total=%d)"), (TCharC*)_name, total);
            SetTotal(total);
         }
      }
   }
   return ETrue;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FMonitor::Startup(){
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FMonitor::Shutdown(){
   return ESuccess;
}

//============================================================
// <T>ִ�д���</T>
//
// @param currentTime ��ǰʱ��
// @return ������
//============================================================
TResult FMonitor::Execute(TTimeTick currentTick){
   TResult result = EFailure;
   // ��������
   if(!_started){
      Startup();
      _started = ETrue;
   }
   // �߼�����
   if(0 != _total){
      _currentDateTime = RDateTime::Current();
      _currentTimeTick = currentTick;
      _currentTimeSpan = currentTick - _lastTimeTick;
      _statistics.Begin();
#ifdef _MO_LINUX
      if(NULL != _pCatcher){
         _pCatcher->Enter();
         if(MO_TRAP_CATCHER(_pCatcher)){
            _pCatcher->Recorded();
            result = Process();
         }else{
            _pCatcher->JumpFinish();
            result = EFailure;
         }
         _pCatcher->Leave();
      }else{
         result = Process();
      }
#else
      result = Process();
#endif
      _statistics.End();
      _count++;
      _needDelay = EFalse;
      _lastTimeTick = currentTick;
      // ����ͳ����Ϣ
      if(ESuccess != result){
         _statistics.Update(EFalse);
         MO_ERROR(TC("Process monitor failure. (name=%s, result=%d)"), (TCharC*)_name, result);
      }else{
         _statistics.Update(ETrue);
      }
   }
   return result;
}

MO_NAMESPACE_END
