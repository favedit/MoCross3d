#ifndef __MO_CM_PROPERTY_H__
#define __MO_CM_PROPERTY_H__

#ifndef __MO_CM_RUNTIME_H__
#include "MoCmRuntime.h"
#endif // __MO_CM_RUNTIME_H__

#ifndef __MO_CM_COLLECTION_H__
#include "MoCmCollection.h"
#endif // __MO_CM_COLLECTION_H__

#ifndef __MO_CM_STRING_H__
#include "MoCmString.h"
#endif // __MO_CM_STRING_H__

#define MO_PROPERTY_MAXCNT                     1024

MO_NAMESPACE_BEGIN

//============================================================
// ���Ͷ���
typedef TUint16 TPropertyId;

//============================================================
// �ṹ����
class TProperty;
class TFsProperties;

//============================================================
// <T>���Լ�����ʽ��</T>
//============================================================
enum EPropertySearch{
   // @member δ֪
   EPropertySearch_Unknown = 0,
   // @member ���
   EPropertySearch_Id = 1,
   // @member ����
   EPropertySearch_Name = 2,
};

//============================================================
// <T>�����޸ķ�ʽ��</T>
//============================================================
enum EPropertyModify{
   // @member �޲���
   EPropertyModify_None,
   // @member ��ȡ
   EPropertyModify_Get,
   // @member ����
   EPropertyModify_Set,
   // @member �޸�
   EPropertyModify_Mod,
};

//============================================================
// <T>���Դ����ʽ��</T>
//============================================================
enum EPropertyPack{
   // @member δ֪
   EPropertyPack_Unknown = 0,
   // @member ���
   EPropertyPack_Id = 1,
   // @member ����
   EPropertyPack_Name = 2,
};

//============================================================
// <T>���Դ���汾��</T>
//============================================================
enum EPropertyVersion{
   // @member A�汾
   EPropertyVersion_A = 0,
   // @member ����
   EPropertyVersion_Count = 1,
};

//============================================================
// <T>����ͷ��Ϣ��</T>
//============================================================
struct MO_CM_DECLARE SPropertyHead{
protected:
   // ���Ա��
   TPropertyId _id;
   // ��������
   TFsName _name;
   // ��������
   EType _typeCd;
public:
   //------------------------------------------------------------
   // <T>��������ͷ��Ϣ��</T>
   SPropertyHead(){
      _id = 0;
      _typeCd = EType_Any;
   }
public:
   //------------------------------------------------------------
   // <T>������Ա�š�</T>
   MO_INLINE TPropertyId Id() const{
      return _id;
   }
   //------------------------------------------------------------
   // <T>�������Ա�š�</T>
   MO_INLINE void SetId(TPropertyId id){
      _id = id;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* Name() const{
      return _name;
   }
   //------------------------------------------------------------
   // <T>�����������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>����������͡�</T>
   MO_INLINE EType TypeCd() const{
      return _typeCd;
   }
   //------------------------------------------------------------
   // <T>�����������͡�</T>
   MO_INLINE void SetTypeCd(EType typeCd){
      _typeCd = typeCd;
   }
};

//============================================================
// <T>����������Ϣ��</T>
//============================================================
struct MO_CM_DECLARE SPropertyInfo{
protected:
   TPropertyId _id; // ���Ա��
   TCharC* _pName;  // ��������
   EType _typeCd;   // ��������
public:
   //------------------------------------------------------------
   // <T>��������������Ϣ��</T>
   SPropertyInfo(const SPropertyInfo& info){
   }
   //------------------------------------------------------------
   // <T>��������������Ϣ��</T>
   SPropertyInfo(TPropertyId id, TCharC* pName, EType typeCd){
      _id = id;
      _pName = pName;
      _typeCd = typeCd;
   }
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����Ա�š�</T>
   MO_INLINE TBool IsId(TPropertyId id) const{
      return (_id == id);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ���������ơ�</T>
   MO_INLINE TBool IsName(TCharC* pName) const{
      return RString::Equals(_pName, pName);
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ���������͡�</T>
   MO_INLINE TBool IsTypeCd(EType typeCd) const{
      return (_typeCd == typeCd);
   }
public:
   //------------------------------------------------------------
   // <T>������Ա�š�</T>
   MO_INLINE TPropertyId Id() const{
      return _id;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* Name() const{
      return _pName;
   }
   //------------------------------------------------------------
   // <T>����������͡�</T>
   MO_INLINE EType TypeCd() const {
      return _typeCd;
   }
};

//============================================================
// <T>���Լ��ϡ�</T>
//============================================================
class MO_CM_DECLARE IProperties{
public:
   //------------------------------------------------------------
   // <T>�������Լ��ϡ�</T>
   MO_ABSTRACT ~IProperties(){
   }
public:
   MO_VIRTUAL TBool PropertyGet(TProperty* pProperty, TPropertyId propertyId) = 0;
   MO_VIRTUAL TBool PropertyGet(TProperty* pProperty, TCharC* pName) = 0;
   MO_VIRTUAL TBool PropertySet(const TProperty* pProperty, EPropertySearch serachCd = EPropertySearch_Id) = 0;
   MO_VIRTUAL TBool PropertyGetAll(TFsProperties* pProperties) = 0;
   MO_VIRTUAL TBool PropertySetAll(TFsProperties* pProperties) = 0;
};

//============================================================
// <T>���Զ���</T>
//============================================================
class MO_CM_DECLARE TProperty{
protected:
   SPropertyInfo* _pInfo;
   TAny* _pData;
   EModify _modifyCd;
public:
   TProperty();
   TProperty(SPropertyInfo* pInfo);
   TProperty(SPropertyInfo* pInfo, TAny* pData);
   TProperty(SPropertyInfo* pInfo, EModify modifyCd, TAny* pData);
public:
   //------------------------------------------------------------
   // <T>����������Ϣ��</T>
   MO_INLINE TBool Link(SPropertyInfo* pInfo, TAny* pData){
      _pInfo = pInfo;
      _pData = pData;
      return ETrue;
   }
   //------------------------------------------------------------
   // <T>������Ա�š�</T>
   MO_INLINE TPropertyId PropertyId() const{
      if(NULL != _pInfo){
         return _pInfo->Id();
      }
      return 0;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* PropertyName() const{
      if(NULL != _pInfo){
         return _pInfo->Name();
      }
      return NULL;
   }
   //------------------------------------------------------------
   // <T>����������͡�</T>
   MO_INLINE EType PropertyTypeCd() const{
      if(NULL != _pInfo){
         return _pInfo->TypeCd();
      }
      return EType_Any;
   }
   //------------------------------------------------------------
   // <T>����޸����͡�</T>
   MO_INLINE EModify ModifyCd() const{
      return _modifyCd;
   }
   //------------------------------------------------------------
   // <T>�����޸����͡�</T>
   MO_INLINE void SetModifyCd(EModify modifyCd){
      _modifyCd = modifyCd;
   }
public:
   TBool Attach(TProperty& property);
   TBool Assign(const TProperty* pProperty);
   TBool Modify(const TProperty* pProperty, EPropertyModify modifyCd);
public:
   TBool IsValid();
   SPropertyInfo* Info();
   void SetInfo(SPropertyInfo* pInfo);
   TAnyC* GetC();
   TAny* Get();
   void Set(TAny* pValue);
   void Set(SPropertyInfo* pInfo, TAny* pValue);
public:
   TBool AsBool();
   TInt8 AsInt8();
   TInt16 AsInt16();
   TInt32 AsInt32();
   TInt64 AsInt64();
   TUint8 AsUint8();
   TUint16 AsUint16();
   TUint32 AsUint32();
   TUint64 AsUint64();
   TFloat AsFloat();
   TDouble AsDouble();
   TDate AsDate();
   TTime AsTime();
   TTick AsTick();
   TSpan AsSpan();
   TDateTime AsDateTime();
   TTimeTick AsTimeTick();
   TTimeSpan AsTimeSpan();
   TCharC* AsString();
public:
   //------------------------------------------------------------
   template <typename T> T AsEnum(){
      return *(T*)Get();
   }
   //------------------------------------------------------------
   template <typename T> T AsSet(){
      return *(T*)Get();
   }
   //------------------------------------------------------------
   template <typename T> T* AsStruct(){
      return (T*)Get();
   }
   //------------------------------------------------------------
   template <typename T> T* AsObject(){
      return (T*)Get();
   }
};
//------------------------------------------------------------
class TFsProperties : public TFixVector<TProperty, MO_PROPERTY_MAXCNT>{
};

//============================================================
// <T>����ַ�����</T>
// <P>OptionEmptyΪ�ٵ�ʱ�򣬲�д������ΪĬ��ֵ�����ԡ�</P>
// <P>���� name=value��{���Ƴ��ȵĳ���}{���Ƴ���}{����}{���ݳ��ȵĳ���}{���ݳ���}{����}��</P>
// <P>ÿ���ڵ�������Լ��Ϻͽڵ㼯�ϣ������ĸA��ͷ�������Լ��ϣ����N��ͷ���ǽڵ㼯�ϣ����Լ����в������ٰ����ڵ㼯�ϡ�</P>
// <P>���Լ���       ��A      {[����]��[����]��[����]...}��</P>
// <P>�ڵ㼯��       ��N[����]{[�ڵ�]��[�ڵ�]��[�ڵ�]...}��</P>
//
// @tools
//============================================================
class MO_CM_DECLARE MPack : public MString{
protected:
   EPropertyVersion _versionCd;
   EPropertyPack _packCd;
   TBool _optionEmpty;
   TInt _position;
   SPropertyHead _readHead;
public:
   MPack();
   MO_ABSTRACT ~MPack();
public:
   //------------------------------------------------------------
   // <T>��ô���汾��</T>
   MO_INLINE EPropertyVersion Version(){
      return _versionCd;
   }
   //------------------------------------------------------------
   // <T>���ô���汾��</T>
   MO_INLINE void SetVersion(EPropertyVersion versionCd){
      _versionCd = versionCd;
   }
   //------------------------------------------------------------
   // <T>��ô�����͡�</T>
   MO_INLINE EPropertyPack PackCd(){
      return _packCd;
   }
   //------------------------------------------------------------
   // <T>���ô�����͡�</T>
   MO_INLINE void SetPackCd(EPropertyPack packCd){
      _packCd = packCd;
   }
   //------------------------------------------------------------
   // <T>�������ա�</T>
   MO_INLINE TBool OptionEmpty(){
      return _optionEmpty;
   }
   //------------------------------------------------------------
   // <T>��������ա�</T>
   MO_INLINE void SetOptionEmpty(TBool optionEmpty){
      _optionEmpty = optionEmpty;
   }
   //------------------------------------------------------------
   // <T>���λ�á�</T>
   MO_INLINE TInt Position(){
      return _position;
   }
   //------------------------------------------------------------
   // <T>����λ�á�</T>
   MO_INLINE void SetPosition(TInt position){
      _position = position;
   }
protected:
   TInt ReadChar();
   TInt ReadString(TChar* pValue, TInt length);
   void WriteChar(TChar value);
   void WriteString(TCharC* pValue, TInt length = -1);
public:
   TBool TestAttribute();
   TBool TestNode();
public:
   TBool ReadAttributeBegin();
   TBool ReadAttributeEnd();
   TBool ReadNodeBegin(const SPropertyInfo* pInfo);
   TBool ReadNodeEnd();
   TBool ReadCollectionBegin(TInt* pCount);
   TBool ReadCollectionEnd();
   TBool ReadPropertyHead(SPropertyHead* pHead);
public:
   TBool ReadPropertyBool(const SPropertyInfo* pInfo);
   TByte ReadPropertyByte(const SPropertyInfo* pInfo);
   TChar ReadPropertyChar(const SPropertyInfo* pInfo);
   TInt8 ReadPropertyInt8(const SPropertyInfo* pInfo);
   TInt16 ReadPropertyInt16(const SPropertyInfo* pInfo);
   TInt32 ReadPropertyInt32(const SPropertyInfo* pInfo);
   TInt64 ReadPropertyInt64(const SPropertyInfo* pInfo);
   TUint8 ReadPropertyUint8(const SPropertyInfo* pInfo);
   TUint16 ReadPropertyUint16(const SPropertyInfo* pInfo);
   TUint32 ReadPropertyUint32(const SPropertyInfo* pInfo);
   TUint64 ReadPropertyUint64(const SPropertyInfo* pInfo);
   TFloat ReadPropertyFloat(const SPropertyInfo* pInfo);
   TDouble ReadPropertyDouble(const SPropertyInfo* pInfo);
   TTimeTick ReadPropertyTimeTick(const SPropertyInfo* pInfo);
   TTimeSpan ReadPropertyTimeSpan(const SPropertyInfo* pInfo);
   TTimeSpan ReadPropertyDateTime(const SPropertyInfo* pInfo);
   TInt ReadPropertyEnum(const SPropertyInfo* pInfo);
   TInt ReadPropertySet(const SPropertyInfo* pInfo);
   TInt ReadPropertyString(const SPropertyInfo* pInfo, TChar* pValue, TInt capacity);
   TInt ReadPropertyFixString(const SPropertyInfo* pInfo, TChar* pValue, TInt length);
   TCharC* ReadPropertyType(const SPropertyInfo* pInfo, TChar* pValue, TInt capacity);
public:
   TBool UnpackBegin();
   TBool UnpackEnd();
public:
   TBool WriteInfo(const SPropertyInfo* pInfo);
   TBool WriteAttributeBegin();
   TBool WriteAttributeEnd();
   TBool WriteNodeBegin(const SPropertyInfo* pInfo);
   TBool WriteNodeBegin(const SPropertyInfo* pInfo, TInt count);
   TBool WriteNodeEnd();
   TBool WriteCollectionBegin(TInt count);
   TBool WriteCollectionEnd();
public:
   void WritePropertyBool(const SPropertyInfo* pInfo, TBool value);
   void WritePropertyByte(const SPropertyInfo* pInfo, TByte value);
   void WritePropertyChar(const SPropertyInfo* pInfo, TChar value);
   void WritePropertyInt8(const SPropertyInfo* pInfo, TInt8 value);
   void WritePropertyInt16(const SPropertyInfo* pInfo, TInt16 value);
   void WritePropertyInt32(const SPropertyInfo* pInfo, TInt32 value);
   void WritePropertyInt64(const SPropertyInfo* pInfo, TInt64 value);
   void WritePropertyUint8(const SPropertyInfo* pInfo, TUint8 value);
   void WritePropertyUint16(const SPropertyInfo* pInfo, TUint16 value);
   void WritePropertyUint32(const SPropertyInfo* pInfo, TUint32 value);
   void WritePropertyUint64(const SPropertyInfo* pInfo, TUint64 value);
   void WritePropertyFloat(const SPropertyInfo* pInfo, TFloat value);
   void WritePropertyDouble(const SPropertyInfo* pInfo, TDouble value);
   void WritePropertyTimeTick(const SPropertyInfo* pInfo, TTimeTick value);
   void WritePropertyTimeSpan(const SPropertyInfo* pInfo, TTimeSpan value);
   void WritePropertyDateTime(const SPropertyInfo* pInfo, TDateTime value);
   void WritePropertyEnum(const SPropertyInfo* pInfo, TInt value);
   void WritePropertySet(const SPropertyInfo* pInfo, TInt value);
   void WritePropertyString(const SPropertyInfo* pInfo, TCharC* pValue, TInt length = -1);
   void WritePropertyFixString(const SPropertyInfo* pInfo, TCharC* pValue, TInt length);
   void WritePropertyType(const SPropertyInfo* pInfo, TCharC* pValue);
public:
   TBool PackBegin();
   TBool PackEnd();
};

//============================================================
// <T>�ַ���������ߡ�</T>
//
// @history 130422 MAOCY ����
//============================================================
class MO_CM_DECLARE FPack :
      public FObject,
      public MPack{
public:
   FPack();
   FPack(EPropertyPack packCd);
   MO_ABSTRACT ~FPack();
protected:
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends);
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TCharC* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<TChar>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const MPack& value){
      Assign(value.MemoryC(), value.Length());
   }
};

//============================================================
// <T>�ַ���������ߡ�</T>
//
// @history 130422 MAOCY ����
//============================================================
class MO_CM_DECLARE TPack : public MPack{
protected:
   TChar _memory[MO_FS_PACK_LENGTH];
public:
   //------------------------------------------------------------
   // <T>�����ַ���������ߡ�</T>
   TPack(){
      InnerInitialize();
   }
   //------------------------------------------------------------
   // <T>�����ַ���������ߡ�</T>
   TPack(EPropertyPack packCd){
      InnerInitialize();
      _packCd = packCd;
   }
   //------------------------------------------------------------
   // <T>�����ַ���������ߡ�</T>
   TPack(TCharC* pValue, TInt length = -1){
      InnerInitialize();
      Assign(pValue, length);
   }
   //------------------------------------------------------------
   // <T>�����ַ���������ߡ�</T>
   TPack(const TPtrC<TChar>& ptr){
      InnerInitialize();
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>�����ַ���������ߡ�</T>
   TPack(const MPack& value){
      InnerInitialize();
      Assign(value.MemoryC(), value.Length());
   }
protected:
   //------------------------------------------------------------
   // <T>�ڲ���ʼ����</T>
   MO_INLINE void InnerInitialize(){
      _pMemory = _memory;
      _capacity = MO_FS_PACK_LENGTH;
      _memory[0] = 0;
   }
   //------------------------------------------------------------
   // <T>�����ڴ��С��</T>
   MO_OVERRIDE void InnerResize(TInt size, TBool copy, TBool extends){
      MO_ASSERT(size <= MO_FS_PACK_LENGTH);
   }
public:
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ��������ݡ�</T>
   MO_INLINE void operator=(TCharC* pValue){
      Assign(pValue);
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const TPtrC<TChar>& ptr){
      Assign(ptr.MemoryC(), ptr.Length());
   }
   //------------------------------------------------------------
   // <T>����ǰ�ַ�������������Ϊָ���ַ�����������ݡ�</T>
   MO_INLINE void operator=(const MPack& value){
      Assign(value.MemoryC(), value.Length());
   }
public:
   //------------------------------------------------------------
   // <T>������ɳ��ȡ�</T>
   MO_INLINE static TInt Size(){
      return MO_FS_PACK_LENGTH;
   }
};

MO_NAMESPACE_END

#endif // __MO_CM_PROPERTY_H__
