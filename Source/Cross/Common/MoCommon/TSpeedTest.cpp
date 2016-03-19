#include "MoCmSystem.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ٶȲ�������</T>
//============================================================
TSpeedTest::TSpeedTest(){
   _beginTick = RTimeTick::Current();
   _endTick = _beginTick;
}

//============================================================
// <T>��ʼΪ�����������ü�ʱ��</T>
//
// @param pDescription ���ú�������
//============================================================
TSpeedTest::TSpeedTest(TCharC* pDescription){
   _beginTick = RTimeTick::Current();
   _endTick = _beginTick;
   _description = pDescription;
}

//============================================================
// <T>��ʾ������Ϣ��</T>
//============================================================
void TSpeedTest::Track(){
   TTimeSpan span = TimeSpan();
   if(_description.IsEmpty()){
      MO_DEBUG(TC("Speed test track. (timespan=%d)"), span);
   }else{
      MO_DEBUG(TC("Speed test track. (timespan=%d, description=%s"), span, (TCharC*)_description);
   }
}

MO_NAMESPACE_END
