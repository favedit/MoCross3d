#include "MoCrService.h"
#include "MoCrMessage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ж��źš�</T>
//
// @return ������
//============================================================
TBool FInterruptListener::Process(){
   // �ͷ�����ģ��
   FModuleList* pModuleList = RModuleManager::Instance().Modules();
   if(!pModuleList->IsEmpty()){
      FModuleList::TIteratorC iterator = pModuleList->IteratorC();
      while(iterator.Next()){
         iterator->Release();
      }
   }
   // �ͷ����з���
   FServiceList* pServiceList = RServiceManager::Instance().Services();
   if(!pServiceList->IsEmpty()){
      FServiceList::TIteratorC iterator = pServiceList->IteratorC();
      while(iterator.Next()){
         iterator->Shutdown();
      }
   }
   return ETrue;
}

MO_NAMESPACE_END
