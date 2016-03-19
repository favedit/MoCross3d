#include "MoCmXml.h"
#include "MoCmFormat.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FXmlNode, FInstance);

//============================================================
// <T>�������ýڵ�ʵ����</T>
//============================================================
FXmlNode::FXmlNode(){
   MO_CLEAR(_pDocument);
   _nodeType = EXmlNodeType_Element;
   MO_CLEAR(_pAttributes);
   MO_CLEAR(_pNodes);
}

//============================================================
// <T>�������ýڵ�ʵ����</T>
//============================================================
FXmlNode::FXmlNode(FXmlDocument* pDocument){
   _pDocument = pDocument;
   _nodeType = EXmlNodeType_Element;
   MO_CLEAR(_pAttributes);
   MO_CLEAR(_pNodes);
}

//============================================================
// <T>�������ýڵ�ʵ����</T>
//
// @param nodeType �ڵ�����
//============================================================
FXmlNode::FXmlNode(FXmlDocument* pDocument, EXmlNodeType nodeType){
   _pDocument = pDocument;
   _nodeType = nodeType;
   MO_CLEAR(_pAttributes);
   MO_CLEAR(_pNodes);
}

//============================================================
// <T>�ͷ����ýڵ�ʵ����</T>
//============================================================
FXmlNode::~FXmlNode(){
   // �ͷ����Ա�
   if(NULL != _pAttributes){
      MO_DELETE(_pAttributes);
   }
   // �ͷŽڵ��
   if(NULL != _pNodes){
      MO_DELETE(_pNodes);
   }
}

//============================================================
// <T>����XML�ı����ݡ�</T>
//
// @param xml �ı�����
// @param pNode �ڵ����
// @param level ���
//============================================================
void FXmlNode::InnerBuildXml(MString* pXml, FXmlNode* pNode, TInt level){
   pXml->AppendRepeat(TC("   "), level);
   if(EXmlNodeType_Comment == pNode->NodeType()){
      // ����ע�ͽڵ�
      pXml->Append(TC("<--"));
      pXml->Append(pNode->Text());
      pXml->Append(TC("-->\n"));
   }else{
      // �������ݽڵ�
      pXml->Append('<');
      pXml->Append(pNode->Name());
      if(pNode->HasAttribute()){
         pXml->Append(' ');
         TAttributesIteratorC iterator = pNode->Attributes()->IteratorC();
         while(iterator.Next()){
            pXml->Append(iterator.Name());
            pXml->Append(TC("=\""));
            RXml::MakeNodeAttribute(pXml, iterator.Value());
            pXml->Append('"');
            if(iterator.HasNext()){
               pXml->Append(' ');
            }
         }
      }
      if(pNode->HasNode()){
         pXml->Append(TC(">\n"));
         // ���������ӽڵ�
         TListIteratorC<FXmlNode*> iterator = pNode->Nodes()->IteratorC();
         while(iterator.Next()){
            FXmlNode* pChildNode = *iterator;
            InnerBuildXml(pXml, pChildNode, level + 1);
         }
         // �رսڵ�
         pXml->AppendRepeat(TC("   "), level);
         pXml->Append(TC("</"));
         pXml->Append(pNode->Name());
         pXml->Append(TC(">\n"));
      }else if(pNode->HasText()){
         pXml->Append(TC(">"));
         RXml::MakeNodeText(pXml, pNode->Text());
         pXml->Append(TC("</"));
         pXml->Append(pNode->Name());
         pXml->Append(TC(">\n"));
      }else{
         pXml->Append(TC("/>\n"));
      }
   }
}

//============================================================
// <T>����ĵ�����</T>
//============================================================
FXmlDocument* FXmlNode::Document(){
   return _pDocument;
}

//============================================================
// <T>��ýڵ����͡�</T>
//
// @return �ڵ�����
//============================================================
EXmlNodeType FXmlNode::NodeType(){
   return _nodeType;
}

//============================================================
// <T>�жϽڵ�������Ƿ�Ϊָ�����ơ�</T>
//
// @param pName ����
// @return
//    <L value='ETrue'>���</L>
//    <L value='EFalse'>����</L>
//============================================================
TBool FXmlNode::IsName(TCharC* pName){
   return _name.EqualsIgnoreCase(pName);
}

//============================================================
// <T>��ýڵ����ơ�</T>
//
// @return �ڵ�����
//============================================================
TCharC* FXmlNode::Name(){
   return _name.MemoryC();
}

//============================================================
// <T>���ýڵ����ơ�</T>
//
// @param name �ڵ�����
//============================================================
void FXmlNode::SetName(TCharC* pName){
   _name.Assign(pName);
}

//============================================================
// <T>�жϽڵ���������Ƶ������Ƿ�Ϊָ�����ݡ�</T>
//
// @param pAttrName ��������
// @param pAttrValue ��������
// @return
//    <L value='ETrue'>���</L>
//    <L value='EFalse'>����</L>
//============================================================
TBool FXmlNode::IsAttribute(TCharC* pAttrName, TCharC* pAttrValue){
   if(NULL == _pAttributes){
      return EFalse;
   }
   TCharC* pValue = _pAttributes->Find(pAttrName);
   TBool result = EFalse;
   if(NULL != pValue){
      if(RString::Equals(pAttrValue, pValue)){
         result = ETrue;
      }
   }
   return result;
}

//============================================================
// <T>��ýڵ����ݡ�</T>
//
// @return �ڵ�����
//============================================================
TBool FXmlNode::HasText(){
   return !_text.IsEmpty();
}

//============================================================
// <T>��ýڵ����ݡ�</T>
//
// @return �ڵ�����
//============================================================
TCharC* FXmlNode::Text(){
   return _text.MemoryC();
}

//============================================================
// <T>�Բ�����ʽ����ýڵ����ݣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ��������
//============================================================
TBool FXmlNode::TextAsBool(TBool nvl){
   return _text.IsEmpty() ? nvl : RBool::IsTrue((TCharC*)_text);
}

//============================================================
// <T>��������ʽ����ýڵ����ݣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ��������
//============================================================
TInt FXmlNode::TextAsInt(TInt nvl){
   return _text.IsEmpty() ? nvl : RInt::Parse((TCharC*)_text);
}

//============================================================
// <T>��������ʽ����ýڵ����ݣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ����������
//============================================================
TInt32 FXmlNode::TextAsInt32(TInt32 nvl){
   return _text.IsEmpty() ? nvl : RInt32::Parse((TCharC*)_text);
}

//============================================================
// <T>��������ʽ����ýڵ����ݣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ����������
//============================================================
TUint32 FXmlNode::TextAsUint32(TUint32 nvl){
   return _text.IsEmpty() ? nvl : RUint32::Parse((TCharC*)_text);
}

//============================================================
// <T>�Գ�������ʽ����ýڵ����ݣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ����������
//============================================================
TInt64 FXmlNode::TextAsInt64(TInt64 nvl){
   return _text.IsEmpty() ? nvl : RInt64::Parse((TCharC*)_text);
}

//============================================================
// <T>�Գ�������ʽ����ýڵ����ݣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ����������
//============================================================
TUint64 FXmlNode::TextAsUint64(TUint64 nvl){
   return _text.IsEmpty() ? nvl : RUint64::Parse((TCharC*)_text);
}

//============================================================
// <T>�Ը�������ʽ����ýڵ����ݣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ����������
//============================================================
TFloat FXmlNode::TextAsFloat(TFloat nvl){
   return _text.IsEmpty() ? nvl : RFloat::Parse((TCharC*)_text);
}

//============================================================
// <T>��ýڵ����ݡ�</T>
//
// @param pText ����ָ��
// @param length ���ݳ���
//============================================================
void FXmlNode::GetText(TChar* pText, TInt length){
   MO_ASSERT(pText);
   TInt copyed = MO_LIB_MIN(_text.Length(), length - 1);
   memcpy(pText, (TCharC*)_text, copyed);
   pText[copyed] = 0;
}

//============================================================
// <T>���ýڵ����ݡ�</T>
//
// @param text �ڵ�����
//============================================================
void FXmlNode::SetText(TCharC* pText){
   _text.Assign(pText);
}

//============================================================
// <T>�ò���ֵ���ýڵ����ݡ�</T>
//
// @param text �ڵ�����
//============================================================
void FXmlNode::SetTextBool(TBool text){
   _text.Assign(RBool::ToString(text));
}

//============================================================
// <T>���������ýڵ����ݡ�</T>
//
// @param text �ڵ�����
//============================================================
void FXmlNode::SetTextInt(TInt text){
   TChar pBuffer[MO_INT_MAXLENGTH];
   _text.Assign(RInt::ToString(text, pBuffer, MO_INT_MAXLENGTH));
}

//============================================================
// <T>�ø��������ýڵ����ݡ�</T>
//
// @param text �ڵ�����
//============================================================
void FXmlNode::SetTextFloat(TFloat text){
   TChar buffer[MO_FLOAT_MAXLENGTH];
   _text.Assign(RFloat::ToString(text, buffer, MO_FLOAT_MAXLENGTH));
}

//============================================================
// <T>׷���ı����ݡ�</T>
//
// @param pText �ı�����
//============================================================
void FXmlNode::TextAppend(TCharC* pText){
   _text.Append(pText);
}

//============================================================
// <T>�ж��Ƿ�������ԡ�</T>
//
// @return
//    <L value='ETrue'>����</L>
//    <L value='EFalse'>������</L>
//============================================================
TBool FXmlNode::HasAttribute(){
   return (NULL != _pAttributes) ? !_pAttributes->IsEmpty() : EFalse;
}

//============================================================
// <T>������Ա�</T>
//
// @return ���Ա�
//============================================================
FAttributes* FXmlNode::Attributes(){
   if(NULL == _pAttributes){
      _pAttributes = MO_CREATE(FAttributes);
   }
   return _pAttributes;
}

//============================================================
// <T>�Ƿ������ԡ�</T>
//
// @param pName ��������
// @return
//    <L value='ETrue'>����</L>
//    <L value='EFalse'>������</L>
//============================================================
TBool FXmlNode::Contains(TCharC* pName){
   if(NULL == _pAttributes){
      return EFalse;
   }
   return _pAttributes->Contains(pName);
}

//============================================================
// <T>�����������ƣ�����������ݡ�</T>
//
// @param pName ��������
// @return ��������
//============================================================
TCharC* FXmlNode::Get(TCharC* pName){
   if(NULL == _pAttributes){
      return NULL;
   }
   return _pAttributes->Get(pName);
}

//============================================================
// <T>�����������ƣ�����������ݣ�������Բ����ڣ��򷵻�Ĭ��ֵ��</T>
//
// @param pName ��������
// @return ��������
//============================================================
TCharC* FXmlNode::Get(TCharC* pName, TCharC* pDefault){
   if(NULL == _pAttributes){
      return pDefault;
   }
   return _pAttributes->FindNvl(pName, pDefault);
}

//============================================================
// <T>�Բ�����ʽ����ýڵ����ԣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ��������
//============================================================
TBool FXmlNode::GetAsBool(TCharC* pName, TBool nvl){
   if(NULL == _pAttributes){
      return nvl;
   }
   TCharC* pValue = _pAttributes->Find(pName);
   return (NULL == pValue) ? nvl : RBool::IsTrue(pValue);
}

//============================================================
// <T>�����ָ�ʽ����ýڵ����ԣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ��������
//============================================================
TInt FXmlNode::GetAsInt(TCharC* pName, TInt nvl){
   if(NULL == _pAttributes){
      return nvl;
   }
   TCharC* pValue = _pAttributes->Find(pName);
   return (NULL == pValue) ? nvl : RInt::Parse(pValue);
}

//============================================================
// <T>�����ָ�ʽ����ýڵ����ԣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ��������
//============================================================
TInt32 FXmlNode::GetAsInt32(TCharC* pName, TInt32 nvl){
   if(NULL == _pAttributes){
      return nvl;
   }
   TCharC* pValue = _pAttributes->Find(pName);
   return (NULL == pValue) ? nvl : RInt32::Parse(pValue);
}

//============================================================
// <T>�����ָ�ʽ����ýڵ����ԣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ��������
//============================================================
TUint32 FXmlNode::GetAsUint32(TCharC* pName, TUint32 nvl){
   if(NULL == _pAttributes){
      return nvl;
   }
   TCharC* pValue = _pAttributes->Find(pName);
   return (NULL == pValue) ? nvl : RUint32::Parse(pValue);
}

//============================================================
// <T>�����ָ�ʽ����ýڵ����ԣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ��������
//============================================================
TInt64 FXmlNode::GetAsInt64(TCharC* pName, TInt64 nvl){
   if(NULL == _pAttributes){
      return nvl;
   }
   TCharC* pValue = _pAttributes->Find(pName);
   return (NULL == pValue) ? nvl : RInt64::Parse(pValue);
}

//============================================================
// <T>�����ָ�ʽ����ýڵ����ԣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ��������
//============================================================
TUint64 FXmlNode::GetAsUint64(TCharC* pName, TUint64 nvl){
   if(NULL == _pAttributes){
      return nvl;
   }
   TCharC* pValue = _pAttributes->Find(pName);
   return (NULL == pValue) ? nvl : RUint64::Parse(pValue);
}

//============================================================
// <T>�Ը�������ʽ����ýڵ����ԣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ������
//============================================================
TFloat FXmlNode::GetAsFloat(TCharC* pName, TFloat nvl){
   if(NULL == _pAttributes){
      return nvl;
   }
   TCharC* pValue = _pAttributes->Find(pName);
   return (NULL == pValue) ? nvl : RFloat::Parse(pValue);
}

//============================================================
// <T>��ʱ���ʽ����ýڵ����ԣ�����ڵ�����Ϊ�գ��򷵻�Ĭ��ֵ��</T>
//
// @param nvl �ڵ�����Ϊ��ʱ��ȡֵ
// @return ������
//============================================================
TDateTime FXmlNode::GetAsDateTime(TCharC* pName, TDateTime nvl){
   if(NULL == _pAttributes){
      return nvl;
   }
   TCharC* pValue = _pAttributes->Find(pName);
   return RDateTime::ParseNvl(pValue, TC("YYYYMMDDHH24MISS"));
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param pValue ��������
//============================================================
TResult FXmlNode::Set(TCharC* pName, TCharC* pValue){
   MO_CHECK(pName, return ENull);
   Attributes()->Set(pName, pValue);
   return ESuccess;
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param value ��������
//============================================================
void FXmlNode::SetBool(TCharC* pName, TBool value){
   Attributes()->Set(pName, RBool::ToString(value));
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param value ��������
//============================================================
void FXmlNode::SetInt(TCharC* pName, TInt value){
   TChar pBuffer[MO_INT_MAXLENGTH];
   Attributes()->Set(pName, RInt::ToString(value, pBuffer, MO_INT_MAXLENGTH));
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param value ��������
//============================================================
void FXmlNode::SetFloat(TCharC* pName, TFloat value){
   TChar buffer[MO_FLOAT_MAXLENGTH];
   Attributes()->Set(pName, RFloat::ToString(value, buffer, MO_FLOAT_MAXLENGTH));
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param value ��������
//============================================================
void FXmlNode::SetDateTime(TCharC* pName, TDateTime value){
   TFsDateTime dateTime = value;
   Attributes()->Set(pName, dateTime.Format(TC("YYYYMMDDHH24MISS")));
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param pValue ��������
//============================================================
TResult FXmlNode::SetNvl(TCharC* pName, TCharC* pValue){
   if(pValue != NULL){
      TInt length = RString::Length(pValue);
      if(length > 0){
         return Set(pName, pValue);
      }
   }
   return EFailure;
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param value ��������
//============================================================
void FXmlNode::SetBoolNvl(TCharC* pName, TBool value){
   if(value){
      SetInt(pName, value);
   }
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param value ��������
//============================================================
void FXmlNode::SetIntNvl(TCharC* pName, TInt value){
   if(value != 0.0f){
      SetInt(pName, value);
   }
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param value ��������
//============================================================
void FXmlNode::SetFloatNvl(TCharC* pName, TFloat value){
   if(value != 0.0f){
      SetFloat(pName, value);
   }
}

//============================================================
// <T>�����������ƣ������������ݡ�</T>
//
// @param pName ��������
// @param value ��������
//============================================================
void FXmlNode::SetDateTimeNvl(TCharC* pName, TDateTime value){
   if(value != 0){
      SetDateTime(pName, value);
   }
}

//============================================================
// <T>�ж��Ƿ���ڽڵ㡣</T>
//
// @return
//    <L value='ETrue'>����</L>
//    <L value='EFalse'>������</L>
//============================================================
TBool FXmlNode::HasNode(){
   return (NULL != _pNodes) ? !_pNodes->IsEmpty() : EFalse;
}

//============================================================
// <T>�Ƿ���ָ�����Ƶ��ӽڵ㡣</T>
//
// @return
//    <L value='ETrue'>����</L>
//    <L value='EFalse'>������</L>
//============================================================
TBool FXmlNode::ContainsNode(TCharC* pName){
   return (NULL != FindNode(pName));
}

//============================================================
// <T>�Ƿ���ָ���������ƺ��������ݵ��ӽڵ㡣</T>
//
// @param pAttrName ��������
// @param pAttrValue ��������
// @return
//    <L value='ETrue'>����</L>
//    <L value='EFalse'>������</L>
//============================================================
TBool FXmlNode::ContainsNode(TCharC* pAttrName, TCharC* pAttrValue){
   return (NULL != FindNode(pAttrName, pAttrValue));
}

//============================================================
// <T>�Ƿ���ָ���ڵ����ƣ����������ƺ��������ݷ��ϵ��ӽڵ㡣</T>
//
// @param pName ��������
// @param pAttrName ��������
// @param pAttrValue ��������
// @return
//    <L value='ETrue'>����</L>
//    <L value='EFalse'>������</L>
//============================================================
TBool FXmlNode::ContainsNode(TCharC* pName, TCharC* pAttrName, TCharC* pAttrValue){
   return (NULL != FindNode(pName, pAttrName, pAttrValue));
}

//============================================================
// <T>����ӽڵ㼯�ϡ�</T>
//
// @return �ӽڵ㼯��
//============================================================
FXmlNodes* FXmlNode::Nodes(){
   if(NULL == _pNodes){
      _pNodes = MO_CREATE(FXmlNodes);
   }
   return _pNodes;
}

//============================================================
// <T>����ӽڵ�ĵ�������</T>
//
// @return �ӽڵ������
//============================================================
TXmlNodeIteratorC FXmlNode::NodeIteratorC(){
   if(NULL == _pNodes){
      return TXmlNodeIteratorC();
   }
   return _pNodes->IteratorC();
}

//============================================================
// <T>���ָ���������ӽڵ㡣</T>
//
// @param index ����λ��
// @return �ӽڵ�
//============================================================
FXmlNode* FXmlNode::Node(TInt index){
   return HasNode() ? _pNodes->GetByIndex(index) : NULL;
}

//============================================================
// <T>���ָ�����Ƶ��ӽڵ㡣</T>
//
// @param pName �ӽڵ�����
// @return �ӽڵ�
//============================================================
FXmlNode* FXmlNode::FindNode(TCharC* pName){
   if(NULL != _pNodes){
      TXmlNodeIteratorC iterator = _pNodes->IteratorC();
      while(iterator.Next()){
         if(iterator->IsName(pName)){
            return iterator.Get();
         }
      }
   }
   return NULL;
}

//============================================================
// <T>���ָ���������ƺ��������ݵ��ӽڵ㡣</T>
//
// @param pAttrName ��������
// @param pAttrValue ��������
// @return �ӽڵ�
//============================================================
FXmlNode* FXmlNode::FindNode(TCharC* pAttrName, TCharC* pAttrValue){
   if(NULL != _pNodes){
      TXmlNodeIteratorC iterator = _pNodes->IteratorC();
      while(iterator.Next()){
         if(iterator->IsAttribute(pAttrName, pAttrValue)){
            return iterator.Get();
         }
      }
   }
   return NULL;
}

//============================================================
// <T>���ָ���ڵ����ƣ����������ƺ��������ݷ��ϵ��ӽڵ㡣</T>
//
// @param pName �ڵ�����
// @param pAttrName ��������
// @param pAttrValue ��������
// @return �ӽڵ�
//============================================================
FXmlNode* FXmlNode::FindNode(TCharC* pName, TCharC* pAttrName, TCharC* pAttrValue){
   if(NULL != _pNodes){
      TXmlNodeIteratorC iterator = _pNodes->IteratorC();
      while(iterator.Next()){
         if(iterator->IsName(pName)){
            if(iterator->IsAttribute(pAttrName, pAttrValue)){
               return iterator.Get();
            }
         }
      }
   }
   return NULL;
}

//============================================================
// <T>����ָ�����Ƶ��ӽڵ㣬����ӽڵ����ݡ�</T>
//
// @param pName �ӽڵ�����
// @return �ӽڵ�����
//============================================================
TCharC* FXmlNode::FindText(TCharC* pName){
   FXmlNode* pNode = FindNode(pName);
   return (NULL == pNode) ? NULL : pNode->Text();
}

//============================================================
// <T>���ָ���������ƺ��������ݵ��ӽڵ����ݡ�</T>
//
// @param pAttrName ��������
// @param pAttrValue ��������
// @return �ӽڵ�����
//============================================================
TCharC* FXmlNode::FindText(TCharC* pAttrName, TCharC* pAttrValue){
   FXmlNode* pNode = FindNode(pAttrName, pAttrValue);
   return (NULL == pNode) ? NULL : pNode->Text();
}

//============================================================
// <T>���ָ���ڵ����ƣ����������ƺ��������ݷ��ϵ��ӽڵ����ݡ�</T>
//
// @param pName �ӽڵ�����
// @param pAttrName ��������
// @param pAttrValue ��������
// @return �ӽڵ�����
//============================================================
TCharC* FXmlNode::FindText(TCharC* pName, TCharC* pAttrName, TCharC* pAttrValue){
   FXmlNode* pNode = FindNode(pName, pAttrName, pAttrValue);
   return (NULL == pNode) ? NULL : pNode->Text();
}

//============================================================
// <T>�����ӽڵ㣬�����ӽڵ���뵱ǰ�ڵ��ڡ�</T>
//
// @return �ӽڵ�
//============================================================
FXmlNode* FXmlNode::CreateNode(){
   FXmlNode* pNode = _pDocument->CreateNode();
   Nodes()->Push(pNode);
   return pNode;
}

//============================================================
// <T>�����ӽڵ㣬�����ӽڵ���뵱ǰ�ڵ��ڡ�</T>
//
// @param pName �ڵ�����
// @return �ӽڵ�
//============================================================
FXmlNode* FXmlNode::CreateNode(TCharC* pName){
   FXmlNode* pNode = _pDocument->CreateNode();
   pNode->SetName(pName);
   Nodes()->Push(pNode);
   return pNode;
}

//============================================================
// <T>�����ӽڵ㣬�����ӽڵ���뵱ǰ�ڵ��ڡ�</T>
// <P>����ʱ����ʼ��һ�����ԡ�</P>
//
// @param pName �ڵ�����
// @param pAttributeName ��������
// @param pAttributeValue ��������
// @return �ӽڵ�
//============================================================
FXmlNode* FXmlNode::CreateNode(TCharC* pName, TCharC* pAttributeName, TCharC* pAttributeValue){
   FXmlNode* pNode = CreateNode(pName);
   pNode->Set(pAttributeName, pAttributeValue);
   return pNode;
}

//============================================================
// <T>���ӽڵ���뵱ǰ�ڵ��ڡ�</T>
//
// @param pNode �ӽڵ�
//============================================================
TResult FXmlNode::Push(FXmlNode* pNode){
   Nodes()->Push(pNode);
   return ESuccess;
}

//============================================================
// <T>���л����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TBool FXmlNode::Serialize(IDataOutput* pOutput){
   return ETrue;
}

//============================================================
// <T>���������з����л����ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TBool FXmlNode::Unserialize(IDataInput* pInput){
   // ��ȡ����
   _name = pInput->ReadString();
   // ��ȡ����
   _text = pInput->ReadString();
   // ��ȡ���Լ���
   TInt attributeCount = pInput->ReadInt16();
   if(attributeCount > 0){
      FAttributes* pAttributes = Attributes();
      for(TInt n = 0; n < attributeCount; n++){
         // ��ȡ��������
         TString attributeName = pInput->ReadString();
         TString attributeValue = pInput->ReadString();
         // ������������
         pAttributes->Set(attributeName, attributeValue);
      }
   }
   // ��ȡ�ڵ㼯��
   TInt nodeCount = pInput->ReadInt16();
   if(nodeCount > 0){
      for(TInt n = 0; n < nodeCount; n++){
         FXmlNode* pNode = CreateNode();
         pNode->Unserialize(pInput);
      }
   }
   return ETrue;
}

//============================================================
// <T>����XML���ݡ�</T>
//
// @param pXml XML����
//============================================================
void FXmlNode::BuildXml(MString* pXml){
   InnerBuildXml(pXml, this, 0);
}

//============================================================
// <T>������ýڵ��XML���ݡ�</T>
//
// @return XML����
//============================================================
TString FXmlNode::Xml(){
   TStringBuffer xml;
   InnerBuildXml(&xml, this, 0);
   return xml;
}

MO_NAMESPACE_END
