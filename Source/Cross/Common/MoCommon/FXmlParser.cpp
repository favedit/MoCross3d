#include "MoCmFormat.h"
#include "MoCmXml.h"
#include "MoCmLanguage.h"
#include "MoCmFile.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FXmlParser, FConfigParser);

//============================================================
// <T>�������ý�������</T>
//============================================================
FXmlParser::FXmlParser(){
   _builder = FXmlBuilder::InstanceCreate();
   _pFactory->Register(MO_CONFIG_ELEMENT_NODE, FXmlNode::Class());
   _pFactory->Register(MO_CONFIG_ELEMENT_TEXT, FXmlNode::Class());
}

//============================================================
// <T>�ͷ����ý�������</T>
//============================================================
FXmlParser::~FXmlParser(){
}

//============================================================
// <T>ɨ��ͷ��Ϣ��</T>
//
// @param pSource ��Դ
// @return ���ݿ�ʼ
//============================================================
TCharC* FXmlParser::ScanHeader(TCharC* pSource){
   MO_ASSERT(pSource);
   // ����ͷ��Ϣ������
   TInt begin = -1;
   TInt end = -1;
   TInt length = RString::Length(pSource);
   for(TInt n = 0; n < length; n++){
      TChar value = pSource[n];
      // ��������
      if((value == 0) || (value == '>') || (value == '\r') || (value == '\n')){
         return pSource;
      }
      // ���ҿ�ʼ��־
      if((value == '<') && (pSource[n + 1] == '?') && (pSource[n + 2] == 'x') && (pSource[n + 3] == 'm') && (pSource[n + 4] == 'l') && (pSource[n + 5] == ' ')){
         begin = n;
         continue;
      }
      // ���ҽ�����־
      if((value == '?') && (pSource[n + 1] == '>')){
         end = n;
         break;
      }
   }
   // ��������
   TFsText headSource = TStringPtrC(pSource + begin + 6, end - begin - 6);
   FXmlNode* pHeadNode = MO_CREATE(FXmlNode);
   ParseAttribute(pHeadNode, headSource);
   TCharC* pVersion = pHeadNode->Get(TC("version"), NULL);
   TCharC* pEncoding = pHeadNode->Get(TC("encoding"), NULL);
   // ���ؿ�ʼ����
   TCharC* pReader = pSource + end + 2;
   if(*pReader == '\r'){
      pReader++;
   }
   if(*pReader == '\n'){
      pReader++;
   }
   return pReader;
}

//============================================================
// <T>����Դ�м���һ�����ýڵ㡣</T>
//
// @param pSource ��Դ
// @return ���ýڵ�
//============================================================
FXmlNode* FXmlParser::LoadNode(TCharC* pSource){
   // ɨ��ͷ��Ϣ
   TCharC* pBody = ScanHeader(pSource);
   FInstance* pRootInstance = Parse(pBody);
   // ��������
   return pRootInstance->Convert<FXmlNode>();
}

//============================================================
// <T>���ļ��м���һ�����ýڵ㡣</T>
//
// @param pFileName �ļ�����
// @return ���ýڵ�
//============================================================
FXmlNode* FXmlParser::LoadNodeFile(TCharC* pFileName){
   // �����ļ�
   FFileString* pFile = MO_CREATE(FFileString);
   pFile->LoadFile(pFileName);
   // ��������
   TCharC* pSource = pFile->MemoryC();
   FXmlNode* pNode = LoadNode(pSource);
   // �ͷ���Դ
   MO_DELETE(pFile);
   return pNode;
}

//============================================================
FXmlDocument* FXmlParser::LoadDocument(TCharC* pSource){
   return NULL;
}

//============================================================
FXmlDocument* FXmlParser::LoadDocumentFile(TCharC* pFileName){
   return NULL;
}

MO_NAMESPACE_END
