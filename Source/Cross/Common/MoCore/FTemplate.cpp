#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplate, FInstance);

//============================================================
// <T>����ģ�塣</T>
//============================================================
FTemplate::FTemplate(){
   _pSources = MO_CREATE(FTemplateSourceDictionary);
   _pIncludeTags = MO_CREATE(FTemplateTagIncludeCollection);
}

//============================================================
// <T>����ģ�塣</T>
//============================================================
FTemplate::~FTemplate(){
   MO_DELETE(_pSources);
   MO_DELETE(_pIncludeTags);
}

//============================================================
// <T>����һ����ǩ�ڵ��������ݡ�</T>
//
// @param parent ����ǩ
// @param index ����λ��
// @param tag ��ǰ��ǩ
//============================================================
TResult FTemplate::ParseTag(FTemplateContext* pContext, FTemplateTag* pParentTag, TInt index, FTemplateTag* pTag){
   // �������з�
   if(pTag->NowrapLeft()){
      pContext->TrimLastLine();
   }
   if(pTag->NowrapRight()){
      pContext->SetTrimOnceFlag();
   }
   // ����ʼ����
   ETemplateTagResult resultBeginCd = pTag->OnBegin(pContext);
   if(resultBeginCd == ETemplateTagResult_Include){
      // ��ֹ���޵ݹ�
      for(TInt limit = 0; limit < 10000; limit++){
         FTemplateTagCollection* pChildren = pTag->Children();
         if(pChildren != NULL){
            TInt count = pChildren->Count();
            for(TInt n = 0; n < count; n++){
               FTemplateTag* pChild = pChildren->Get(n);
               ParseTag(pContext, pTag, n, pChild);
            }
            // ����ѭ������
            ETemplateTagResult resultLoopCd = pTag->OnLoop(pContext);
            if(resultLoopCd != ETemplateTagResult_Continue){
               break;
            }else{
               // ����ѭ�����ֵ��һ��з�
               if(pTag->NowrapRight()){
                  pContext->SetTrimOnceFlag();
               }
            }
         }
      }
      // �����������
      pTag->OnEnd(pContext);
      // ����������ֵ��һ��з�
      if(pTag->NowrapRight()){
         pContext->TrimLastLine();
      }
   }
   return ESuccess;
}

//============================================================
// <T>����ģ�塣</T>
//============================================================
TResult FTemplate::Parse(FTemplateContext* pContext, TCharC* pPartName){
   // ������Դ
   FTemplateSource* pTemplateSource = NULL;
   if(pPartName == NULL){
      pTemplateSource = _pSources->Get(TC("default"));
   }else{
      pTemplateSource = _pSources->Get(pPartName);
   }
   // ��������
   FTemplateTag* pRootTag = pTemplateSource->RootTag();
   TResult resultCd = ParseTag(pContext, NULL, -1, pRootTag);
   pContext->SourceFormat();
   return resultCd;
}

//============================================================
// <T>�������ýڵ㡣</T>
//============================================================
TResult FTemplate::AdjustConfigNodes(FTemplateContext* pContext){
   MO_CHECK(pContext, return ENull);
   FXmlNodes* pNodes = pContext->MergeConfig()->Nodes();
   TXmlNodeIteratorC iterator = _config->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pConfig = *iterator;
      // MO_INFO("%s - %s", pConfig->Name(), pConfig->Get("name", NULL));
      if(!pConfig->Nodes()->Contains(pConfig)){
         pNodes->Push(pConfig);
      }
   }
   return ESuccess;
}

//============================================================
// <T>������Ϣ��</T>
//============================================================
void TrackTag(MString* pResult, FTemplateTag* pTag, TInt level){
   pResult->AppendRepeat(TC("   "), level);
   pResult->AppendFormat(TC("[%s]"), pTag->Name());
   FTemplateTagCollection* pChildren = pTag->Children();
   if(pChildren != NULL){
      TInt count = pChildren->Count();
      pResult->AppendFormat(TC(":%d\n"), count);
      for(TInt n = 0; n < count; n++){
         FTemplateTag* pChildTag = pChildren->Get(n);
         TrackTag(pResult, pChildTag, level + 1);
      }
   }else{
      pResult->Append(TC("\n"));
   }
}

//============================================================
// <T>������Ϣ��</T>
//
// @return ������
//============================================================
TResult FTemplate::Track(){
   FString* pResult = MO_CREATE(FString);
   FTemplateSourceDictionary::TIteratorC iterator = _pSources->IteratorC();
   while(iterator.Next()){
      FTemplateSource* pTemplateSource = *iterator;
      TrackTag(pResult, pTemplateSource->RootTag(), 0);
   }
   MO_DEBUG(TC("Dump template info:\n%s"), pResult->MemoryC());
   MO_DELETE(pResult);
   return ESuccess;
}

MO_NAMESPACE_END
