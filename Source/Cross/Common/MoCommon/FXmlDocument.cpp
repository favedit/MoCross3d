#include <fcntl.h>
#ifdef _MO_WINDOWS
#import <msxml6.dll> named_guids
#endif // _MO_SYS_WINDOWS
#ifdef _MO_LINUX
#include <libxml/parser.h>
#include <libxml/xmlsave.h>
#endif // _MO_LINUX
#include "MoCmXml.h"
#include "MoCmSystem.h"

#define MO_DEF_ROOT_NAME TC("Configuration")
#define MO_DEF_NODE_NAME TC("Node")

#define MO_CRT_BSTR_TO_STRING(V) _com_util::ConvertBSTRToString(V)
#define MO_CRT_STRING_TO_BSTR(V) _com_util::ConvertStringToBSTR(V)

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������ļ�ʵ����</T>
//============================================================
FXmlDocument::FXmlDocument(){
   _encoding = TC("UTF-8");
   _indent = TC("   ");
   _pNodes = MO_CREATE(FXmlNodes);
   MO_CLEAR(_pRoot);
}

//============================================================
// <T>���������ļ�ʵ�������������ļ���</T>
//
// @param fileName �ļ�����
//============================================================
FXmlDocument::FXmlDocument(TCharC* pFileName){
   _encoding = TC("UTF-8");
   _indent = TC("   ");
   _pNodes = MO_CREATE(FXmlNodes);
   MO_CLEAR(_pRoot);
   LoadFile(pFileName);
}

//============================================================
// <T>���������ļ�ʵ�������������ļ���</T>
//
// @param fileName �ļ�����
//============================================================
FXmlDocument::FXmlDocument(FXmlNode* pRootNode){
   _encoding = TC("UTF-8");
   _indent = TC("   ");
   _pNodes = MO_CREATE(FXmlNodes);
   _pRoot = pRootNode;
}

//============================================================
// <T>�ͷŵ�ǰʵ����</T>
//
// @param fileName �ļ�����
//============================================================
FXmlDocument::~FXmlDocument(){
   TListIteratorC<FXmlNode*> iterator = _pNodes->IteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      MO_DELETE(pNode);
   }
   MO_DELETE(_pNodes);
}

//============================================================
// <T>���һ���ļ����ơ�</T>
//
// @return �ļ�����
//============================================================
TCharC* FXmlDocument::FileName(){
   return _fileName.MemoryC();
}

//============================================================
// <T>������ֱ��롣</T>
//
// @return ���ֱ���
//============================================================
TCharC* FXmlDocument::Encoding(){
   return _encoding.MemoryC();
}

//============================================================
// <T>�������ֱ��롣</T>
//
// @param pEncoding ���ֱ���
//============================================================
void FXmlDocument::SetEncoding(TCharC* pEncoding){
   _encoding.Assign(pEncoding);
}

//============================================================
// <T>�ж��Ƿ���ڽڵ㡣</T>
//
// @return �Ƿ���ڽڵ�
//============================================================
TBool FXmlDocument::HasNode(){
   return NULL != _pRoot;
}

//============================================================
// <T>��ø��ڵ㡣</T>
//
// @return ���ýڵ�
//============================================================
FXmlNode* FXmlDocument::Root(){
   if(NULL == _pRoot){
      // �������ڵ�
      _pRoot = CreateNode(EXmlNodeType_Element);
      _pRoot->SetName(MO_DEF_ROOT_NAME);
   }
   return _pRoot;
}

//============================================================
// <T>����һ�����ýڵ㡣</T>
//
// @return ���ýڵ�
//============================================================
FXmlNode* FXmlDocument::CreateNode(EXmlNodeType type){
   FXmlNode* pNode = MO_CREATE(FXmlNode, this, type);
   pNode->SetName(MO_DEF_NODE_NAME);
   _pNodes->Push(pNode);
   return pNode;
}

//============================================================
// <T>ͬ��Ԫ�ؽڵ㵽���ýڵ��ڡ�</T>
//
// @param piDocument �ĵ�����
// @param pNode ���ýڵ�
// @param piNode Ԫ�ؽڵ�
//============================================================
#ifdef _MO_WINDOWS
void SyncNodeFromElement(FXmlDocument* pDocument, MSXML2::IXMLDOMDocument3Ptr piDocument, FXmlNode* pNode, MSXML2::IXMLDOMNodePtr piNode){
#ifdef _UNICODE
#else
   pNode->SetName(MO_CRT_BSTR_TO_STRING(piNode->nodeName));
#endif
   // �ж��Ƿ��������
   MSXML2::IXMLDOMNamedNodeMapPtr piAttributes = piNode->Getattributes();
   TInt attrLength = piAttributes->Getlength();
   if(attrLength > 0){
      // ��ȡ��������
      FAttributes* pAttributes = pNode->Attributes();
      for(TInt n=0; n<attrLength; n++){
         MSXML2::IXMLDOMNodePtr attrNode = piAttributes->Getitem(n);
#ifdef _UNICODE
#else
         TCharC* pAttrName = MO_CRT_BSTR_TO_STRING(attrNode->nodeName);
         TCharC* pAttrValue = MO_CRT_BSTR_TO_STRING(attrNode->nodeValue.bstrVal);
         pAttributes->Set(pAttrName, pAttrValue);
#endif
      }
   }
   // �ж��Ƿ�����ӽڵ�
   MSXML2::IXMLDOMNodeListPtr piChildren = piNode->GetchildNodes();
   TInt nodeLength = piChildren->Getlength();
   if(nodeLength > 0){
      // ��ȡ��������
      FXmlNodes* pChildren = pNode->Nodes();
      for(TInt n=0; n<nodeLength; n++){
         // ��õ�ǰ�ӽڵ�
         MSXML2::IXMLDOMNodePtr piChild = piChildren->Getitem(n);
         switch(piChild->GetnodeType()){
            case NODE_ELEMENT:{
                  FXmlNode* pChild = pDocument->CreateNode(EXmlNodeType_Element);
                  SyncNodeFromElement(pDocument, piDocument, pChild, piChild);
                  pChildren->Push(pChild);
               }
               break;
            case NODE_TEXT:{
#ifdef _UNICODE
#else
               pNode->TextAppend(MO_CRT_BSTR_TO_STRING(piChild->nodeValue.bstrVal));
#endif
               }
               break;
            case NODE_CDATA_SECTION:{
#ifdef _UNICODE
#else
                  pNode->SetText(MO_CRT_BSTR_TO_STRING(piChild->nodeValue.bstrVal));
#endif
               }
               break;
            case NODE_COMMENT:{
                  FXmlNode* pChild = pDocument->CreateNode(EXmlNodeType_Comment);
#ifdef _UNICODE
#else
                  pChild->SetText(MO_CRT_BSTR_TO_STRING(piChild->nodeValue.bstrVal));
#endif
                  pChildren->Push(pChild);
               }
               break;
         }
      }
   }
}
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
void SyncNodeFromElement(FXmlDocument* pDocument, FXmlNode* pNode, xmlDocPtr xdocPtr, xmlNodePtr xnodePtr){
   pNode->SetName((TCharC*)xnodePtr->name);
   // �ж��Ƿ��������
   xmlAttrPtr xattrsPtr = xnodePtr->properties;
   if(NULL != xattrsPtr){
      // ��ȡ��������
      FAttributes* pAttributes = pNode->Attributes();
      while(NULL != xattrsPtr){
         // ��������
         xmlChar* szAttrValue = xmlGetProp(xnodePtr, xattrsPtr->name);
         pAttributes->Set((TCharC*)xattrsPtr->name, (TCharC*)szAttrValue);
         xmlFree(szAttrValue);
         // �����һ���ڵ�
         xattrsPtr = xattrsPtr->next;
      }
   }
   // �ж��Ƿ�����ӽڵ�
   xmlNodePtr xchildPtr = xnodePtr->children;
   if(NULL != xchildPtr){
      // ��ȡ��������
      FXmlNodes* pChildren = pNode->Nodes();
      while(NULL != xchildPtr){
         // ��õ�ǰ�ӽڵ�
         switch(xchildPtr->type){
            case XML_ELEMENT_NODE:{
               // �����ڵ�
               FXmlNode* pChild = pDocument->CreateNode(EXmlNodeType_Element);
               SyncNodeFromElement(pDocument, pChild, xdocPtr, xchildPtr);
               pChildren->Push(pChild);
               break;
            }
            case XML_TEXT_NODE:{
               // ����ı�����
               xmlChar* szText = xmlNodeGetContent(xchildPtr);
               pNode->TextAppend((TCharC*)szText);
               xmlFree(szText);
               break;
            }
            case XML_CDATA_SECTION_NODE:{
               // ����ı�����
               xmlChar* szText = xmlNodeGetContent(xchildPtr);
               pNode->SetText((TCharC*)szText);
               xmlFree(szText);
               break;
            }
            case XML_COMMENT_NODE:{
               // ����ע�ͽڵ�
               FXmlNode* pChild = pDocument->CreateNode(EXmlNodeType_Comment);
               xmlChar* szText = xmlNodeGetContent(xchildPtr);
               pChild->SetText((TCharC*)szText);
               xmlFree(szText);
               pChildren->Push(pChild);
               break;
            }
            case XML_ATTRIBUTE_NODE:
            case XML_ENTITY_REF_NODE:
            case XML_ENTITY_NODE:
            case XML_PI_NODE:
            case XML_DOCUMENT_NODE:
            case XML_DOCUMENT_TYPE_NODE:
            case XML_DOCUMENT_FRAG_NODE:
            case XML_NOTATION_NODE:
            case XML_HTML_DOCUMENT_NODE:
            case XML_DTD_NODE:
            case XML_ELEMENT_DECL:
            case XML_ATTRIBUTE_DECL:
            case XML_ENTITY_DECL:
            case XML_NAMESPACE_DECL:
            case XML_XINCLUDE_START:
            case XML_XINCLUDE_END:
            case XML_DOCB_DOCUMENT_NODE:{
               break;
            }
         }
         xchildPtr = xchildPtr->next;
      }
   }
}
#endif // _MO_LINUX

//============================================================
// <T>ͬ�����ýڵ㵽Ԫ�ؽڵ��ڡ�</T>
//
// @param piDocument �ĵ�����
// @param piNode Ԫ�ؽڵ�
// @param pNode ���ýڵ�
// @param level �ڵ���
//============================================================
#ifdef _MO_SYS_WINDOWS
void SyncElementFromNode(FXmlDocument* pDocument, MSXML2::IXMLDOMDocument3Ptr piDocument, MSXML2::IXMLDOMNodePtr piNode, FXmlNode* pNode, TInt level){
   // �����ı�����
   if(!pNode->HasNode()){
      if(!pNode->HasText()){
         piNode->put_text(_bstr_t(pNode->Text()));
      }
   }
   // �ж��Ƿ��������
   if(pNode->HasAttribute()){
      FAttributes* pAttributes = pNode->Attributes();
      TAttributesIteratorC iterator = pAttributes->IteratorC();
      while(iterator.Next()){
         MSXML2::IXMLDOMAttributePtr piAttribute = piDocument->createAttribute(_bstr_t(iterator.Name()));
         piAttribute->put_value(_variant_t(iterator.Value()));
         piNode->attributes->setNamedItem(piAttribute);
      }
   }
   // �ж��Ƿ�����ӽڵ�
   if(pNode->HasNode()){
      FXmlNodes* pNodes = pNode->Nodes();
      TInt count = pNodes->Count();
      // ��ȡ�����ӽڵ�
      for(TInt n = 0; n < count; n++){
         FXmlNode* pChild = pNodes->GetByIndex(n);
         switch(pChild->NodeType()){
            case EXmlNodeType_Element:{
                  // �½����з�
                  //TString space("\n");
                  //space.AppendRepeat(_indent, level);
                  //piNode->appendChild(piDocument->createTextNode(space.MemoryC()));
                  // �½��ڵ�����
                  MSXML2::IXMLDOMElementPtr piChild = piDocument->createElement(_bstr_t(pChild->Name()));
                  SyncElementFromNode(pDocument, piDocument, piChild, pChild, level+1);
                  piNode->appendChild(piChild);
               }
               break;
            case EXmlNodeType_Text:{
               }
               break;
            case EXmlNodeType_Data:{
               }
               break;
            case EXmlNodeType_Comment:{
                  //piChild = piDocument->createNode(NODE_COMMENT, _bstr_t(pChild->Name().MemoryC()), _bstr_t());
                  //SyncElementFromNode(piDocument, piChild, pChild);
                  //piNode->appendChild(piChild);
               }
               break;
         }
      }
      // �½����з�
      //TString afterSpace("\n");
      //afterSpace.AppendRepeat(_indent, level-1);
      //piNode->appendChild(piDocument->createTextNode(afterSpace.MemoryC()));
   }
}
#endif // _MO_SYS_WINDOWS
#ifdef _MO_LINUX
void SyncElementFromNode(FXmlDocument* pDocument, FXmlNode* pNode, xmlDocPtr xdocPtr, xmlNodePtr xnodePtr){
   // �����ı�����
   if(!pNode->HasNode()){
      if(pNode->HasText()){
         xmlNodeSetContent(xnodePtr, BAD_CAST(pNode->Text()));
      }
   }
   // �ж��Ƿ��������
   if(pNode->HasAttribute()){
      // ��ȡ��������
      TAttributesIteratorC iterator = pNode->Attributes()->IteratorC();
      while(iterator.Next()){
         xmlNewProp(xnodePtr, BAD_CAST(iterator.Name()), BAD_CAST(iterator.Value()));
      }
   }
   // �ж��Ƿ�����ӽڵ�
   if(pNode->HasNode()){
      TXmlNodeIteratorC iterator = pNode->NodeIteratorC();
      // ��ȡ�����ӽڵ�
      while(iterator.Next()){
         FXmlNode* pChild = *iterator;
         switch(pChild->NodeType()){
            case EXmlNodeType_Element:{
               // �½��ڵ�����
               xmlNodePtr xchildPtr = xmlNewChild(xnodePtr, NULL, BAD_CAST(pChild->Name()), BAD_CAST(pChild->Text()));
               // �ݹ鴦��
               SyncElementFromNode(pDocument, pChild, xdocPtr, xchildPtr);
               break;
               }
            case EXmlNodeType_Text:{
               break;
               }
            case EXmlNodeType_Data:{
               break;
               }
            case EXmlNodeType_Comment:{
               xmlNodePtr xchildPtr = xmlNewComment(BAD_CAST(pChild->Text()));
               xmlAddChild(xnodePtr, xchildPtr);
               break;
               }
         }
      }
   }
}
#endif // _MO_LINUX

//============================================================
// <T>���л����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TBool FXmlDocument::Serialize(IDataOutput* pOutput){
   return Root()->Serialize(pOutput);
}

//============================================================
// <T>���������з����л����ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TBool FXmlDocument::Unserialize(IDataInput* pInput){
   return Root()->Unserialize(pInput);
}

//============================================================
// <T>���л����ݵ��ļ���</T>
//
// @param pOutput �����
// @return ������
//============================================================
TBool FXmlDocument::SerializeFile(TCharC* pFileName){
   MO_FATAL_UNSUPPORT();
   return ETrue;
}

//============================================================
// <T>���ļ��з����л����ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TBool FXmlDocument::UnserializeFile(TCharC* pFileName){
   // ���ļ�
#ifdef _MO_WINDOWS
   TFileHandle handle;
#ifdef _UNICODE
   _wfopen_s(&handle, pFileName, TC("rb"));
#else
   fopen_s(&handle, pFileName, "rb");
#endif
#else
   TFileHandle handle = fopen(pFileName, "rb");
#endif
   if(NULL == handle){
      MO_PERROR(fopen);
      return EFalse;
   }
   // ��ó���
   if(ESuccess != fseek(handle, 0, SEEK_END)){
      MO_PERROR(fseek);
      return EFalse;
   }
   TInt length = ftell(handle);
   // �ӿ�ʼλ�ö�ȡ
   if(ESuccess != fseek(handle, 0, SEEK_SET)){
      MO_PERROR(fseek);
      return EFalse;
   }
   TByte* pMemory = MO_TYPES_ALLOC(TByte, length);
   TInt readed = fread(pMemory, length, 1, handle);
   if(1 != readed){
      MO_PFATAL(fread);
   }
   // �����л��ļ�
   TLinkInput input(pMemory, length);
   Unserialize(&input);
   // �ر��ļ�
   if(ESuccess != fclose(handle)){
      MO_PFATAL(fclose);
   }
   MO_FREE(pMemory);
   return ETrue;
}

//============================================================
// <T>���������ļ���</T>
//
// @param fileName �ļ�����
//============================================================
TBool FXmlDocument::LoadFile(TCharC* pFileName){
   TFileInfo fileInfo = pFileName;
   _fileName.Assign(fileInfo.FullName());
#ifdef _MO_SYS_WINDOWS
   // �洢Ҫ�����ļ�������
   // �����ĵ�����
   MSXML2::IXMLDOMDocument3Ptr piDocument;
   HRESULT hr = piDocument.CreateInstance(__uuidof(MSXML2::DOMDocument60));
   if(FAILED(hr)){
      MO_FATAL(TC("Create document failure. (file_name=%s)"), (TCharC*)_fileName);
      return EFalse;
   }
   piDocument->put_async(VARIANT_FALSE);
   piDocument->put_validateOnParse(VARIANT_FALSE);
   piDocument->put_resolveExternals(VARIANT_FALSE);
   piDocument->put_preserveWhiteSpace(VARIANT_TRUE);
   VARIANT_BOOL result = piDocument->load((TCharC*)_fileName);
   if(!result){
      piDocument.Release();
      MO_FATAL(TC("Load configuration file failure. (file_name=%s)"), (TCharC*)_fileName);
      return EFalse;
   }
   // Ԫ�ؽڵ㵽���ýڵ�
   MSXML2::IXMLDOMElementPtr piRoot = piDocument->documentElement;
   if(NULL == piRoot){
      piDocument.Release();
      MO_FATAL(TC("Load configuration roor failure. (file_name=%s)"), (TCharC*)_fileName);
      return EFalse;
   }
   SyncNodeFromElement(this, piDocument, Root(), piRoot);
   // �ͷŶ���
   piDocument.Release();
#endif // _MO_SYS_WINDOWS
#ifdef _MO_LINUX
   // ���ĵ�
   xmlDocPtr xdocPtr;
   if(NULL == (xdocPtr = xmlReadFile(_fileName, NULL, XML_PARSE_RECOVER | XML_PARSE_NOBLANKS))){
      MO_PERROR(xmlParseFile);
      return EFalse;
   }
   // ��ø��ڵ�
   xmlNodePtr nodePtr;
   if(NULL == (nodePtr = xmlDocGetRootElement(xdocPtr))){
      MO_PERROR(xmlDocGetRootElement);
      xmlFreeDoc(xdocPtr);
      xdocPtr = NULL;
      return EFalse;
   }
   // Ԫ�ؽڵ㵽���ýڵ�
   SyncNodeFromElement(this, Root(), xdocPtr, nodePtr);
   // �ͷŶ���
   xmlFreeDoc(xdocPtr);
#ifdef _MO_DEBUG
   xmlMemoryDump();
#endif // _MO_DEBUG
#endif // _MO_LINUX
   return ETrue;
}

//============================================================
// <T>�洢�����ļ���</T>
//
// @param fileName �ļ�����
//============================================================
TBool FXmlDocument::SaveFile8(TCharC* pFileName){
#ifdef _MO_SYS_WINDOWS
   // �����ı�����
   FStringBuffer* pXml = MO_CREATE(FStringBuffer);
   BuildXml(pXml);
#ifdef _MO_UNICODE
   FStringBuffer8* pXml8 = MO_CREATE(FStringBuffer8);
   pXml8->Assign16(pXml->MemoryC());
#else
   FStringBuffer8* pXml8 = pXml;
#endif // _MO_UNICODE
   // �洢�ļ�
   HANDLE handle = CreateFile(pFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   MO_ASSERT(INVALID_HANDLE_VALUE != handle);
   TDword writted;
   WriteFile(handle, pXml8->MemoryC(), pXml8->ByteLength(), &writted, NULL);
   MO_ASSERT(writted == pXml8->ByteLength());
   CloseHandle(handle);
   // �ͷ���Դ
#ifdef _MO_UNICODE
   MO_DELETE(pXml8);
#endif // _MO_UNICODE
   MO_DELETE(pXml);
#endif // _MO_SYS_WINDOWS
   return ETrue;
}

//============================================================
// <T>�洢�����ļ���</T>
//
// @param fileName �ļ�����
//============================================================
TBool FXmlDocument::SaveFile(TCharC* pFileName){
#ifdef _MO_WINDOWS
#if 1
   // �����ļ�
   FStringBuffer* pXml = MO_CREATE(FStringBuffer);
   BuildXml(pXml);
   HANDLE handle = CreateFile(pFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   MO_ASSERT(INVALID_HANDLE_VALUE != handle);
   TDword writted;
   WriteFile(handle, pXml->MemoryC(), pXml->ByteLength(), &writted, NULL);
   MO_ASSERT(writted == pXml->ByteLength());
   CloseHandle(handle);
   MO_DELETE(pXml);
#else
   // �����ĵ�����
   MSXML2::IXMLDOMDocument3Ptr piDocument;
   HRESULT hr = piDocument.CreateInstance(__uuidof(MSXML2::DOMDocument60));
   if(FAILED(hr)){
      throw EError_Unknown;
   }
   piDocument->put_async(VARIANT_FALSE);
   piDocument->put_validateOnParse(VARIANT_FALSE);
   piDocument->put_resolveExternals(VARIANT_FALSE);
   piDocument->put_preserveWhiteSpace(VARIANT_TRUE);
   // �����ļ�����
   MSXML2::IXMLDOMProcessingInstructionPtr piInstruction = piDocument->createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
   piDocument->appendChild(piInstruction);
   // ��������
   //MSXML2::IXMLDOMTextPtr piSpace = piDocument->createTextNode("\n");
   //piFragment->appendChild(piSpace);
   // ͬ�����ýڵ㵽Ԫ�ؽڵ�
   FXmlNode* pRoot = Root();
   MSXML2::IXMLDOMElementPtr piRoot = piDocument->createNode(NODE_ELEMENT, _bstr_t(pRoot->Name()), _bstr_t());
   SyncElementFromNode(this, piDocument, piRoot, pRoot, 1);
   piDocument->documentElement = piRoot;
   piDocument->save(_bstr_t(pFileName));
   // �ͷŶ���
   piDocument.Release();
#endif
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
#if 0
   // TODO:�޷����Ƹ�ʽ��
   // ���ļ�
   xmlDocPtr xdocPtr = xmlNewDoc(BAD_CAST("1.0"));
   if(NULL == xdocPtr){
      MO_PERROR(xmlNewDoc);
      return EFalse;
   }
   // �������ڵ�
   FXmlNode* pRoot = Root();
   xmlNodePtr xnodePtr = xmlNewDocNode(xdocPtr, NULL, BAD_CAST(pRoot->Name().MemoryC()), BAD_CAST(pRoot->Text().MemoryC()));
   if(NULL == xnodePtr){
      MO_PERROR(xmlNewDocNode);
      xmlFreeDoc(xdocPtr);
      xdocPtr = NULL;
      return EFalse;
   }
   xmlDocSetRootElement(xdocPtr, xnodePtr);
   // ͬ���ڵ�
   SyncElementFromNode(this, Root(), xdocPtr, xnodePtr);
   // �����ļ�
   /*xmlKeepBlanksDefault(0);
   xmlSaveCtxtPtr xctxtPtr = xmlSaveToFilename(fileName.MemoryC(), "UTF-8", XML_SAVE_FORMAT);
   if(NULL == xctxtPtr){
      MO_PERROR(xmlSaveToFilename);
      return EFalse;
   }
   if(xmlSaveDoc(xctxtPtr, xdocPtr) < 0){
      MO_PERROR(xmlSaveDoc);
      return EFalse;
   }
   xmlSaveClose(xctxtPtr);*/
   // xmlSaveFormatFileEnc(fileName.MemoryC(), xdocPtr, "UTF-8", 1);
   // �ͷŶ���
   xmlFreeDoc(xdocPtr);
#ifdef _MO_DEBUG
   xmlMemoryDump();
#endif
#else
   // �����ļ�
   TString xml = Xml();
   TInt handle = open(pFileName, O_CREAT | O_TRUNC | O_WRONLY, 0777);
   TInt size = write(handle, xml.MemoryC(), xml.Length());
   MO_ASSERT(size == xml.Length());
   close(handle);
#endif
#endif // _MO_LINUX
   return ETrue;
}

//============================================================
// <T>���XML�ַ�����</T>
//
// @return XML�ַ���
//============================================================
void FXmlDocument::BuildXml(MString* pXml){
   pXml->EnsureSize(1024*1024);
   pXml->Append(TC("<?xml version=\"1.0\" encoding=\""));
   pXml->Append(_encoding);
   pXml->Append(TC("\"?>\n"));
   Root()->BuildXml(pXml);
}

//============================================================
// <T>���XML�ַ�����</T>
//
// @return XML�ַ���
//============================================================
TString FXmlDocument::Xml(){
   TStringBuffer xml;
   xml.EnsureSize(1024*1024);
   xml.Append(TC("<?xml version=\"1.0\" encoding=\""));
   xml.Append(_encoding);
   xml.Append(TC("\"?>\n"));
   Root()->BuildXml(&xml);
   return xml;
}

MO_NAMESPACE_END
