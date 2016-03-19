#include <time.h>
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
TUint32 RRandom::_seed = 0;

//============================================================
//<T>��ʼ��RRandom���󣬲���һ�����ӡ�</T>
//============================================================
void RRandom::Initialize(){
	if (_seed == 0){
		_seed = (TUint32)time(NULL);
		srand(_seed);
	}
}

//===========================================================
//<T>���һ���������</T>
//
//@return �������������
//============================================================
TInt RRandom::Get(){
   Initialize();
   return rand();
}

//============================================================
//<T>���ָ�������ڵ��������</T>
//
//@return �������������
//============================================================
TInt RRandom::Get(TInt min, TInt max){
   Initialize();
   if(min >= max){
      return min;
   }
   TInt range = max - min;
   return (rand() % range) + min;
}

//===========================================================
//<T>���һ���������</T>
//
//@return �������������
TInt RRandom::Generator(){
   Initialize();
   return rand();
}

//============================================================
//<T>���ָ�������ڵ��������</T>
//
//@return �������������
//============================================================
TInt RRandom::Generator(TInt min, TInt max){
   if(min >= max){
      return min;
   }
   TInt range = max - min;
   Initialize();
   return (rand() % range) + min;
}

//===========================================================
//<T>���һ�������������</T>
//
//@return �������������
//============================================================
TFloat RRandom::GeneratorFloat(){
   Initialize();
   TFloat value = (TFloat)(rand() % 1000000);
   return value / 1000000;
}

//===========================================================
//<T>���ָ�������ڸ����������</T>
//
//@return �������������
//============================================================
TFloat RRandom::GeneratorFloat(TFloat min, TFloat max){
   Initialize();
   if(min >= max){
      return min;
   }
   TInt minRange = (TInt)(min * 1000000.0f);
   TInt maxRange = (TInt)(max * 1000000.0f);
   TInt rand = Generator(minRange, maxRange);
   return rand / 1000000.0f;
}

MO_NAMESPACE_END
