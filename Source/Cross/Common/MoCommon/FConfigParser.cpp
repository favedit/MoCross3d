#include "MoCmFormat.h"
#include "MoCmConfig.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FConfigParser, FInstance);

//============================================================
// <T>�������ý�������</T>
//============================================================
FConfigParser::FConfigParser(){
   _optionTextNode = EFalse;
   _pFactory = MO_CREATE(FClassFactory);
   MO_CLEAR(_pRootNode);
   _start.Assign(TC("<"));
   _tagFlags = _start.MemoryC();
   _startLength = _start.Length();
   _tagEnd.Assign(TC("</"));
   _dataStart = TC("<![CDATA[");
   _dataEnd = TC("]]>");
}

//============================================================
// <T>�ͷ����ý�������</T>
//============================================================
FConfigParser::~FConfigParser(){
   MO_DELETE(_pFactory);
}

//============================================================
// <T>���ݱ�ǩ���ƴ�����ǩ��</T>
//
// @param pTagName ��ǩ����
// @return �ڵ����
//============================================================
FInstance* FConfigParser::CreateNode(TCharC* pTagName){
   MO_ASSERT(pTagName);
   // �����ڵ�
   FInstance* pInstance = NULL;
   if(_pFactory->Contains(pTagName)){
      pInstance = _pFactory->Create(pTagName);
   }else{
      pInstance = _pFactory->Create(MO_CONFIG_ELEMENT_NODE);
   }
   _builder->SetName(pInstance, pTagName);
   // ���ø��ڵ�
   if(_pRootNode == NULL){
      _pRootNode = pInstance;
   }
   return pInstance;
}

//============================================================
// <T>����ģ���ǩ��</T>
//============================================================
void FConfigParser::SetSpace(TCharC* pSpace){
   _space = pSpace;
   _start.AssignFormat(TC("<%s:"), (TCharC*)_space);
   _tagFlags = _start.MemoryC();
   _startLength = _start.Length();
   _tagEnd.AssignFormat(TC("</%s:"), (TCharC*)_space);
}

//============================================================
// <T>�������Լ��ϡ�</T>
//
// @param pNode Ԫ�ض���
// @param pSource ��������
//============================================================
TResult FConfigParser::ParseAttribute(FInstance* pNode, TCharC* pSource){
   MO_CHECK(pNode, return ENull);
   MO_CHECK(pSource, return ENull);
   // ��鳤��
   TInt length = RChars::Length(pSource);
   if(length == 0){
      return ESuccess;
   }
   // ��������
   _attributeName.Clear();
   _attributeValue.Clear();
   _attributeNameBuffer.Clear();
   _attributeValueBuffer.Clear();
   TInt n = 0;
   while(ETrue){
      // �ֽ���������
      if(n >= length){
         break;
      }
      for(; n < length; n++){
         TChar loopChar = pSource[n];
         if(loopChar == '='){
            _attributeName = _attributeNameBuffer.MemoryC();
            _attributeNameBuffer.Clear();
            break;
         }else if(loopChar != ' '){
            _attributeNameBuffer.Append(loopChar);
         }
      }
      // �ֽ���������
      if(n + 1 >= length){
         break;
      }
      n++;
      TChar valueChar = pSource[n];
      if((valueChar == '\'') || (valueChar == '\"')){
         n++;
      }else{
         valueChar = ' ';
      }
      for(; n < length; n++){
         TChar loopChar = pSource[n];
         if(loopChar == valueChar){
            _attributeValue = _attributeValueBuffer.MemoryC();
            _attributeValueBuffer.Clear();
            if(valueChar != ' '){
               n++;
            }
            _builder->Set(pNode, _attributeName, _attributeValue);
            break;
         }else{
            _attributeValueBuffer.Append(loopChar);
         }
      }
   }
   return ESuccess;
}

//============================================================
// <T>�������롣</T>
//
// @param pParentNode ���ڵ�
// @param chars �����ַ���
// @param start ��ʼ����λ��
// @param length ��������
// @param endTag ��ǩ������־
// @return ����λ��
//============================================================
TInt FConfigParser::ParseSource(FInstance* pParentNode, TCharC* pSource, TInt start, TInt length, TCharC* pEndTag){
   // ��������
   TStringBuffer tagName;
   TStringBuffer tagContent;
   TStringBuffer temp;
   // ���ɱ���
   TBool findEndTag = (pEndTag != NULL);
   TCharC* endTagChars = NULL;
   TInt endTagLength = 0;
   if(findEndTag){
      endTagChars = pEndTag;
      endTagLength = RChars::Length(pEndTag);
   }
   // ��������
   TInt n = start;
   for(; n < length; n++){
      TChar loopChar = pSource[n];
      // ���ұ�ǩ����λ��
      if(findEndTag){
         TInt endEqualsLength = 0;
         for(TInt i = 0; i < endTagLength; i++){
            if(pSource[n + i] == endTagChars[i]){
               endEqualsLength++;
               continue;
            }
            break;
         }
         if(endEqualsLength == endTagLength){
            // �������λ��
            n += endTagLength - 1;
            if(!temp.IsEmpty()){
               if(_optionTextNode && (pParentNode != NULL)){
                  FInstance* pTextNode = CreateNode(MO_CONFIG_ELEMENT_TEXT);
                  _builder->SetText(pTextNode, temp);
                  _builder->Push(pParentNode, pTextNode);
               }
               temp.Clear();
            }
            return n;
         }
      }
      //............................................................
      // ����ע�Ͳ��� <!-- -->
      if(loopChar == '<' && pSource[n + 1] == '!' && pSource[n + 2] == '-' && pSource[n + 3] == '-'){
         for(n += 4; n < length; n++){
            if(pSource[n] == '-' && pSource[n + 1] == '-' && pSource[n + 2] == '>'){
               n += 3;
               loopChar = pSource[n];
               break;
            }
         }
      }
      //............................................................
      // ���ұ�ǩ��ʼλ��
      TInt equalsLength = 0;
      for(TInt i = 0; i < _startLength; i++){
         if(pSource[n + i] == _tagFlags[i]){
            equalsLength++;
            continue;
         }
         break;
      }
      if(equalsLength == _startLength){
         // ���潫ǰ������
         if(!temp.IsEmpty()){
            if(_optionTextNode && (pParentNode != NULL)){
               FInstance* pTextNode = CreateNode(MO_CONFIG_ELEMENT_TEXT);
               _builder->SetText(pTextNode, temp);
               _builder->Push(pParentNode, pTextNode);
            }
            temp.Clear();
         }
         // �ֽ��ǩ
         n += _startLength;
         //............................................................
         TBool bTagClose = ETrue; // ��ǰ��ǩ�Ƿ����
         TBool bTagNameFind = EFalse; // ��ǰ��ǩ�Ƿ����
         // ���ұ�ǩ���ƺͱ�ǩ����
         tagName.Clear();
         tagContent.Clear();
         while(ETrue){
            loopChar = pSource[n];
            if(loopChar == ' '){
               bTagNameFind = ETrue;
            }
            if(loopChar == '>'){
               bTagNameFind = ETrue;
               bTagClose = EFalse;
               break;
            }
            if((loopChar == '/') && (pSource[n + 1] == '>')){
               bTagNameFind = ETrue;
               bTagClose = ETrue;
               n++;
               break;
            }
            if(!bTagNameFind){
               tagName.Append(loopChar);
            }else{
               tagContent.Append(loopChar);
            }
            n++;
         }
         //............................................................
         // �������ݽڵ�
         TBool dataSegment = EFalse;
         TCharC* pData = &pSource[n + 1];
         TInt dataBegin = -1;
         TInt dataEnd = -1;
         if(RTypes<TChar>::Equals(pData, (TCharC*)_dataStart, _dataStart.Length())){
            dataBegin = n + 1;
            dataEnd = RChars::Find(pData, length - n, (TCharC*)_dataEnd, _dataEnd.Length());
            if(dataEnd == ENotFound){
               MO_FATAL(TC("Data segment is not end. (tag_name=%s)"), (TCharC*)tagName);
            }
            dataSegment = ETrue;
         }
         //............................................................
         // ��ǩ�رմ���
         FInstance* pChildNode = CreateNode(tagName);
         if(!tagContent.IsEmpty()){
            ParseAttribute(pChildNode, tagContent);
         }
         if(pParentNode != NULL){
            _builder->Push(pParentNode, pChildNode);
         }
         if(dataSegment){
            TString data = TStringPtrC(pData + _dataStart.Length() , dataEnd - _dataStart.Length() - _dataEnd.Length());
            _builder->SetText(pChildNode, data);
            bTagClose = ETrue;
            TFsName tagEnd;
            tagEnd.AppendFormat(TC("%s%s>"), (TCharC*)_tagEnd, (TCharC*)tagName);
            TInt findTagEnd = RChars::Find(pData, length - n, (TCharC*)tagEnd, tagEnd.Length());
            if(findTagEnd == ENotFound){
               MO_FATAL(TC("Tag end is not found. (tag_name=%s)"), (TCharC*)tagName);
            }
            n += findTagEnd + tagEnd.Length();
         }
         if(!bTagClose){
            TFsName tagEnd;
            tagEnd.AppendFormat(TC("%s%s>"), (TCharC*)_tagEnd, (TCharC*)tagName);
            n = ParseSource(pChildNode, pSource, n + 1, length, tagEnd);
         }
         // ��ǩ���ô���
         _builder->Setup(pChildNode);
      }else{
         temp.Append(loopChar);
      }
   }
   // ׷��β���ַ���
   if(!temp.IsEmpty()){
      if(pParentNode != NULL){
         FInstance* pTextNode = CreateNode(MO_CONFIG_ELEMENT_TEXT);
         _builder->SetText(pTextNode, temp);
         _builder->Push(pParentNode, pTextNode);
      }
      temp.Clear();
   }
   return n;
}

//============================================================
// <T>���������ı����ݡ�</T>
//
// @param pSource ��Դ����
// @return ʵ��
//============================================================
FInstance* FConfigParser::Parse(TCharC* pSource){
   TInt length = RChars::Length(pSource);
   _pRootNode = NULL;
   ParseSource(NULL, pSource, 0, length, NULL);
   return _pRootNode;
}

//============================================================
// <T>���������ı����ݡ�</T>
//
// @param pInstance ʵ��
// @param pSource ��Դ����
// @return ������
//============================================================
TResult FConfigParser::Parse(FInstance* pInstance, TCharC* pSource){
   TInt length = RChars::Length(pSource);
   _pRootNode = pInstance;
   ParseSource(pInstance, pSource, 0, length, NULL);
   return ESuccess;
}

MO_NAMESPACE_END
