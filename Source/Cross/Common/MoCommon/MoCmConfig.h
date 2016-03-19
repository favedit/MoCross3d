#ifndef __MO_CM_CONFIG_H__
#define __MO_CM_CONFIG_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_CLASS_H__
#include "MoCmClass.h"
#endif // __MO_CM_CLASS_H__

#define MO_EACH_NODE(I, X) TXmlNodeIteratorC I = X->NodeIteratorC();while(I.next())

#define MO_CONFIG_ELEMENT_NODE TC("config:node")
#define MO_CONFIG_ELEMENT_TEXT TC("config:text")

MO_NAMESPACE_BEGIN

//============================================================
// <T>���������ݽӿڡ�<T>
//============================================================
class MO_CM_DECLARE IConfiguration : public IConfig{
public:
   //------------------------------------------------------------
   // <T>�������������ݽӿڡ�<T>
   MO_ABSTRACT ~IConfiguration(){
   }
public:
   MO_VIRTUAL TCharC* Name() = 0;
};
//------------------------------------------------------------
typedef MO_CM_DECLARE FList<IConfiguration*> FConfiguraList;
typedef MO_CM_DECLARE FSet<TInt, IConfiguration*> FConfiguraSet;

//============================================================
// <T>���ù�������</T>
//============================================================
class MO_CM_DECLARE FConfigBuilder : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FConfigBuilder, FInstance);
public:
   FConfigBuilder();
   MO_ABSTRACT ~FConfigBuilder();
public:
   MO_ABSTRACT TResult SetName(FInstance* pInstance, TCharC* pName);
   MO_ABSTRACT TResult SetText(FInstance* pInstance, TCharC* pText);
public:
   MO_ABSTRACT TResult Set(FInstance* pInstance, TCharC* pName, TCharC* pValue);
   MO_ABSTRACT TResult Push(FInstance* pInstance, FInstance* pChildInstance);
   MO_ABSTRACT TResult Setup(FInstance* pInstance);
};

//============================================================
// <T>���ý�������</T>
//============================================================
class MO_CM_DECLARE FConfigParser : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FConfigParser, FInstance);
protected:
   // �����Ƿ񴴽��ı��ڵ�
   TBool _optionTextNode;
   // ��ʼ��ǩǰ׺
   TString _space;
   // ��ʼ��ǩ
   TString _start;
   // ��ʼ��ǩ����
   TCharC* _tagFlags;
   // ��ʼ��ǩ����
   TInt _startLength;
   // ������ǩ
   TString _tagEnd;
   // ���ڵ�
   FInstance* _pRootNode;
   // ���ݿ�ʼ
   TFsCode _dataStart;
   // ���ݽ���
   TFsCode _dataEnd;
   // ������
   GPtr<FConfigBuilder> _builder;
   // �๤��
   FClassFactory* _pFactory;
protected:
   TStringBuffer _attributeName;
   TStringBuffer _attributeValue;
   TStringBuffer _attributeNameBuffer;
   TStringBuffer _attributeValueBuffer;
public:
   FConfigParser();
   MO_ABSTRACT ~FConfigParser();
public:
   //------------------------------------------------------------
   // <T>����Ƿ񴴽��ı��ڵ㡣</T>
   MO_INLINE TBool OptionTextNode(){
      return _optionTextNode;
   }
   //------------------------------------------------------------
   // <T>�����Ƿ񴴽��ı��ڵ㡣</T>
   MO_INLINE void SetOptionTextNode(TBool optionTextNode){
      _optionTextNode = optionTextNode;
   }
   //------------------------------------------------------------
   // <T>��ù�������</T>
   MO_INLINE FConfigBuilder* Builder(){
      return _builder;
   }
   //------------------------------------------------------------
   // <T>���ù�������</T>
   MO_INLINE void SetBuilder(FConfigBuilder* pBuilder){
      _builder = pBuilder;
   }
   //------------------------------------------------------------
   // <T>����๤����</T>
   MO_INLINE FClassFactory* Factory(){
      return _pFactory;
   }
public:
   void SetSpace(TCharC* pSpace);
   FInstance* CreateNode(TCharC* pTagName);
   TResult ParseAttribute(FInstance* pNode, TCharC* pSource);
   TInt ParseSource(FInstance* pParentNode, TCharC* pSource, TInt start, TInt length, TCharC* pEndTag);
   FInstance* Parse(TCharC* pSource);
   TResult Parse(FInstance* pInstance, TCharC* pSource);
};

MO_NAMESPACE_END

#endif // __MO_CM_CONFIG_H__
