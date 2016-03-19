#include "MoCrAsset.h"
#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateConsole, FConsole);

//============================================================
// <T>����ģ�����̨��</T>
//============================================================
FTemplateConsole::FTemplateConsole(){
   _pParser = MO_CREATE(FTemplateParser);
   _pTemplates = MO_CREATE(FTemplateDictionary);
   _pParser->SetSpace(TC("shader"));
}

//============================================================
// <T>����ģ�����̨��</T>
//============================================================
FTemplateConsole::~FTemplateConsole(){
   MO_DELETE(_pParser);
   MO_DELETE(_pTemplates);
}

//============================================================
// <T>����һ����ǩ�ڵ��������ݡ�</T>
//
// @param parent ����ǩ
// @param index ����λ��
// @param tag ��ǰ��ǩ
//============================================================
FTemplate* FTemplateConsole::Load(FTemplateContext* pContext, TCharC* pTemplateName){
   MO_CHECK(pContext, return NULL);
   MO_CHECK(pTemplateName, return NULL);
   // ����ģ��
   FTemplate* pTemplate = _pTemplates->Find(pTemplateName);
   if(pTemplate != NULL){
      return pTemplate;
   }
   //............................................................
   // ��ģ������
   TStringBuffer source;
   TResult result = RAssetManager::Instance().OpenAssetString(&source, pTemplateName);
   if(result != ESuccess){
      MO_FATAL(TC("Open template failure. (name=%s)"), pTemplateName);
      return NULL;
   }
   TCharC* pSpace = pContext->Space();
   GPtr<FXmlParser> xmlParser = FXmlParser::InstanceCreate();
   FXmlNode* pConfig = xmlParser->LoadNode(source);
   //............................................................
   // ����ģ��
   pTemplate = FTemplate::InstanceCreate();
   pTemplate->SetConfig(pConfig);
   pTemplate->AdjustConfigNodes(pContext);
   //............................................................
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      if(pNode->IsName(TC("Source"))){
         // ����������
         if(pNode->Contains(TC("include"))){
         }else{
            //............................................................
            // ��������
            TCharC* pName = pNode->Get(TC("name"), TC("default"));
            TCharC* pSource = pNode->Text();
            // ����������
            GPtr<FTemplateBuilder> builder = FTemplateBuilder::InstanceCreate();
            builder->SetConsole(this);
            builder->SetContext(pContext);
            builder->SetTemplate(pTemplate);
            // ����������
            GPtr<FTemplateParser> parser = FTemplateParser::InstanceCreate();
            parser->SetBuilder(builder);
            parser->SetSpace(pSpace);
            // ��������
            FTemplateSource* pTemplateSource = parser->Load(pSource);
            MO_FATAL_CHECK(pTemplateSource, return NULL, TC("Build template failure."));
            pTemplate->Sources()->Set(pName, pTemplateSource);
         }
      }
   }
   //............................................................
   // �洢ģ��
   _pTemplates->Set(pTemplateName, pTemplate);
   return pTemplate;
}

MO_NAMESPACE_END
