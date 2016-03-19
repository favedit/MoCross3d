#include "MoCmLanguage.h"
#include "MoCmFormat.h"
#include "MoCmProperty.h"

#define MO_CM_PACK_SIGN              TC("MP#")
#define MO_CM_PACK_SIGN_LENGTH       3
#define MO_CM_PACK_BASE              '0'
#define MO_CM_PACK_VERSION           'A'
#define MO_CM_PACK_BEGIN             '['
#define MO_CM_PACK_END               ']'
#define MO_CM_PACK_ATTRIBUTE_BEGIN   '('
#define MO_CM_PACK_ATTRIBUTE_END     ')'
#define MO_CM_PACK_PROPERTY_SPLITE   ','
#define MO_CM_PACK_PROPERTY_EMPTY    '0'
#define MO_CM_PACK_NODE_BEGIN        '{'
#define MO_CM_PACK_NODE_END          '}'
#define MO_CM_PACK_COLLECTION_BEGIN  '{'
#define MO_CM_PACK_COLLECTION_END    '}'

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ַ�����</T>
//============================================================
MPack::MPack(){
   _versionCd = EPropertyVersion_A;
   _packCd = EPropertyPack_Name;
   _optionEmpty = EFalse;
   _position = 0;
}

//============================================================
// <T>��������ַ�����</T>
//============================================================
MPack::~MPack(){
}

//============================================================
// <T>��ȡһ���ַ���</T>
//
// @return �ַ�
//============================================================
TInt MPack::ReadChar(){
   if(_position + 1 <= _length){
      return _pMemory[_position++];
   }
   return -1;
}

//============================================================
// <T>��ȡһ���ַ�����</T>
//
// @param pValue �ַ���
// @param length ����
// @return ��ȡ����
//============================================================
TInt MPack::ReadString(TChar* pValue, TInt length){
   if(length > 0){
      if(_position + length <= _length){
         // ��ȡ����
         MO_LIB_MEMORY_COPY(pValue, length, _pMemory + _position, length);
         pValue[length] = 0;
         _position += length;
         return length;
      }
   }
   return 0;
}

//============================================================
// <T>׷��һ���ַ�����ǰ�ַ��������ĩβ��</T>
//
// @param value �ַ���
//============================================================
void MPack::WriteChar(TChar value){
   // ȷ���ڴ�
   if((_position + 1) >= _capacity){
      EnsureSize(_position + 2);
   }
   // ��������
   _pMemory[_position++] = value;
   // ��������
   if(_position > _length){
      _length = _position;
      _pMemory[_length] = 0;
   }
}

//============================================================
// <T>׷��һ���ַ�������ǰ�ַ��������ĩβ��</T>
//
// @param pValue �ַ���
// @param length ����
//============================================================
void MPack::WriteString(TCharC* pValue, TInt length){
   // ����ַ�������
   if(length < 0){
      length = RTypes<TChar>::IndexOf(pValue, 0);
   }
   if(length > 0){
      // ȷ���ڴ�
      if((_position + length) >= _capacity){
         EnsureSize(_position + length + 1);
      }
      // ��������
      RTypes<TChar>::Copy(_pMemory + _position, pValue, length);
      _position += length;
      // ��������
      if(_position > _length){
         _length = _position;
         _pMemory[_length] = 0;
      }
   }
}

//============================================================
// <T>��������ַ�����</T>
//============================================================
TBool MPack::TestAttribute(){
   return ('A' == _pMemory[_position]);
}

//============================================================
// <T>��������ַ�����</T>
//============================================================
TBool MPack::TestNode(){
   return ('N' == _pMemory[_position]);
}

//============================================================
// <T>��������ַ�����</T>
//
// @param [out] count ����
// @return ������
//============================================================
TBool MPack::ReadAttributeBegin(){
   // ��鿪ͷ
   if(_pMemory[_position] != MO_CM_PACK_ATTRIBUTE_BEGIN){
      return EFalse;
   }
   // ��������
   _position++;
   return ETrue;
}

//============================================================
// <T>��������ַ�����</T>
//
// @return ������
//============================================================
TBool MPack::ReadAttributeEnd(){
   _position++;
   return ETrue;
}

//============================================================
// <T>��������ַ�����</T>
//
// @return ������
//============================================================
TBool MPack::ReadNodeBegin(const SPropertyInfo* pInfo){
   // ��鿪ͷ
   if(MO_CM_PACK_NODE_BEGIN != _pMemory[_position]){
      return EFalse;
   }
   _position++;
   return ETrue;
}

//============================================================
// <T>��������ַ�����</T>
//
// @return ������
//============================================================
TBool MPack::ReadNodeEnd(){
   // ��ȡ������
   if(MO_CM_PACK_NODE_END != _pMemory[_position]){
      return EFalse;
   }
   _position++;
   // ��ȡ�ָ�
   if(MO_CM_PACK_PROPERTY_SPLITE == _pMemory[_position]){
      _position++;
   }
   return ETrue;
}

//============================================================
// <T>��������ַ�����</T>
//
// @param [out] count ����
// @return ������
//============================================================
TBool MPack::ReadCollectionBegin(TInt* pCount){
   // ��������
   if(NULL != pCount){
      *pCount = RInt16::ParseHex(_pMemory + _position, 4);
   }
   _position += 5;
   return ETrue;
}

//============================================================
// <T>��������ַ�����</T>
//
// @return ������
//============================================================
TBool MPack::ReadCollectionEnd(){
   _position++;
   return ETrue;
}

//============================================================
// <T>��ȡ����ͷ��Ϣ��</T>
//
// @param pHead ͷ��Ϣ
// @return ������
//============================================================
TBool MPack::ReadPropertyHead(SPropertyHead* pHead){
   // ��鳤��
   if(_position >= _length){
      return EFalse;
   }
   // ��������
   TChar flag = _pMemory[_position];
   if(MO_CM_PACK_NODE_BEGIN == flag){
      MO_DEBUG_WARN(TC("Unpack skip unused object.\n   pack  =%s\n   object=%s)"), _pMemory, _pMemory + _position);
      // ����δ��ȡ�Ķ���򼯺�
      TInt level = 0;
      for(; _position < _length; _position++){
         TChar value = _pMemory[_position];
         if(MO_CM_PACK_NODE_BEGIN == value){
            level++;
         }else if(MO_CM_PACK_NODE_END == value){
            level--;
            if(0 == level){
               _position++;
               break;
            }
         }
      }
      flag = _pMemory[_position];
   }
   // �������Խ�������
   if(MO_CM_PACK_ATTRIBUTE_END == flag){
      return EFalse;
   }
   // ������һ���ַ��Ƿ����Կ�ʼ
   TChar priorFlag = _pMemory[_position - 1];
   if(!((MO_CM_PACK_ATTRIBUTE_BEGIN == priorFlag) || (MO_CM_PACK_PROPERTY_SPLITE == priorFlag))){
      // ����δ��ȡ������
      MO_DEBUG_WARN(TC("Unpack skip unused property.\n   pack    =%s\n   property=%s)"), _pMemory, _pMemory + _position);
      // ����δ��ȡ�Ķ���򼯺�
      for(; _position < _length; _position++){
         TChar value = _pMemory[_position];
         if(MO_CM_PACK_ATTRIBUTE_END == value){
            return EFalse;
         }else if(MO_CM_PACK_PROPERTY_SPLITE == value){
            _position++;
            break;
         }
      }
   }
   // ��ȡ���Ƴ���
   TInt length = RInt8::Parse2(_pMemory + _position);
   if((length <= 0) || (_position + length > _length)){
      return EFalse;
   }
   _position += 2;
   // ��ȡ����
   TFsName name;
   MO_LIB_MEMORY_COPY(name.Memory(), name.Size(), _pMemory + _position, length);
   name.SetLength(length);
   _readHead.SetName(name);
   _position += length;
   // ��ȡ����
   TInt typeCd = RInt8::Parse2(_pMemory + _position);
   _readHead.SetTypeCd((EType)typeCd);
   _position += 2;
   // �������
   if(NULL != pHead){
      pHead->SetName(name);
      pHead->SetTypeCd((EType)typeCd);
   }
   return ETrue;
}

//============================================================
// <T>��ȡ�����������ݡ�</T>
//
// @return ��������
//============================================================
TBool MPack::ReadPropertyBool(const SPropertyInfo* pInfo){
   TFsInteger buffer;
   TInt length = ReadPropertyFixString(pInfo, buffer.Memory(), 1);
   return (length > 0) ? RBool::IsTrue(buffer) : EFalse;
}

//============================================================
// <T>��ȡ�ֽ��������ݡ�</T>
//
// @return ��������
//============================================================
TByte MPack::ReadPropertyByte(const SPropertyInfo* pInfo){
   TFsInteger buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? buffer.Parse() : 0;
}

//============================================================
// <T>��ȡ�ַ��������ݡ�</T>
//
// @return ��������
//============================================================
TChar MPack::ReadPropertyChar(const SPropertyInfo* pInfo){
   TFsInteger buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? buffer.Parse() : 0;
}

//============================================================
// <T>��ȡ�з���8λ�����������ݡ�</T>
//
// @return ��������
//============================================================
TInt8 MPack::ReadPropertyInt8(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt8::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�з���16λ�����������ݡ�</T>
//
// @return ��������
//============================================================
TInt16 MPack::ReadPropertyInt16(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt16::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�з���32λ�����������ݡ�</T>
//
// @return ��������
//============================================================
TInt32 MPack::ReadPropertyInt32(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt32::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�з���64λ�����������ݡ�</T>
//
// @return ��������
//============================================================
TInt64 MPack::ReadPropertyInt64(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt64::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�޷���8λ�����������ݡ�</T>
//
// @return ��������
//============================================================
TUint8 MPack::ReadPropertyUint8(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RUint8::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�޷���16λ�����������ݡ�</T>
//
// @return ��������
//============================================================
TUint16 MPack::ReadPropertyUint16(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RUint16::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�޷���32λ�����������ݡ�</T>
//
// @return ��������
//============================================================
TUint32 MPack::ReadPropertyUint32(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RUint32::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�޷���64λ�����������ݡ�</T>
//
// @return ��������
//============================================================
TUint64 MPack::ReadPropertyUint64(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RUint64::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�����ȸ������������ݡ�</T>
//
// @return ��������
//============================================================
TFloat MPack::ReadPropertyFloat(const SPropertyInfo* pInfo){
   TFsFloat buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? buffer.Parse() : 0;
}

//============================================================
// <T>��ȡ˫���ȸ������������ݡ�</T>
//
// @return ��������
//============================================================
TDouble MPack::ReadPropertyDouble(const SPropertyInfo* pInfo){
   TFsDouble buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? buffer.Parse() : 0;
}

//============================================================
// <T>��ȡʱ���������ݡ�</T>
//
// @return ��������
//============================================================
TTimeTick MPack::ReadPropertyTimeTick(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt64::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡʱ����������ݡ�</T>
//
// @return ��������
//============================================================
TTimeSpan MPack::ReadPropertyTimeSpan(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt64::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡʱ���������ݡ�</T>
//
// @return ��������
//============================================================
TTimeSpan MPack::ReadPropertyDateTime(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt64::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡö���������ݡ�</T>
//
// @return ��������
//============================================================
TInt MPack::ReadPropertyEnum(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�����������ݡ�</T>
//
// @return ��������
//============================================================
TInt MPack::ReadPropertySet(const SPropertyInfo* pInfo){
   TFsNumber buffer;
   TInt length = ReadPropertyString(pInfo, buffer.Memory(), buffer.Size());
   return (length > 0) ? RInt::Parse(buffer) : 0;
}

//============================================================
// <T>��ȡ�ַ����������ݡ�</T>
//
// @return ��������
//============================================================
TInt MPack::ReadPropertyString(const SPropertyInfo* pInfo, TChar* pValue, TInt capacity){
   TInt length = 0;
   // ��ȡ���ȵĳ���
   TInt lengthLength = ReadChar();
   if(-1 != lengthLength){
      lengthLength -= '0';
   }
   // ��ȡ����
   if(lengthLength > 0){
      // ��ȡ����
      TFsInteger lengthString;
      if(0 == ReadString(lengthString.Memory(), lengthLength)){
         return -1;
      }
      length = lengthString.Parse();
      // ��ȡ����
      if(0 == ReadString(pValue, length)){
         return -1;
      }
   }
   // ��ȡ�ָ�
   if(MO_CM_PACK_PROPERTY_SPLITE == _pMemory[_position]){
      _position++;
   }
   return length;
}

//============================================================
// <T>��ȡ�ַ����������ݡ�</T>
//
// @return ��������
//============================================================
TInt MPack::ReadPropertyFixString(const SPropertyInfo* pInfo, TChar* pValue, TInt length){
   TInt result = ReadString(pValue, length);
   // ��ȡ�ָ�
   if(MO_CM_PACK_PROPERTY_SPLITE == _pMemory[_position]){
      _position++;
   }
   return result;
}

//============================================================
// <T>��ȡ�����������ݡ�</T>
//
// @return ��������
//============================================================
TCharC* MPack::ReadPropertyType(const SPropertyInfo* pInfo, TChar* pValue, TInt capacity){
   ReadPropertyString(pInfo, pValue, capacity);
   return pValue;
}

//============================================================
// <T>��ʼ�����</T>
//
// @return ������
//============================================================
TBool MPack::UnpackBegin(){
   // ����λ��
   _position = 0;
   // ��ȡ��ʶ
   TFsCode sign;
   TInt length = ReadString(sign.Memory(), MO_CM_PACK_SIGN_LENGTH);
   if(MO_CM_PACK_SIGN_LENGTH != length){
      MO_FATAL(TC("Unpack sign length invalid. (length=%d, pack=%d:%s)"), length, _length, _pMemory);
      return EFalse;
   }
   sign.SetLength(length);
   if(!sign.Equals(MO_CM_PACK_SIGN)){
      MO_FATAL(TC("Unpack sign invalid. (sign=%s, pack=%d:%s)"), (TCharC*)sign, _length, _pMemory);
      return EFalse;
   }
   // ��ȡ�汾
   TInt versionCd = ReadChar();
   if(versionCd < 0){
      MO_FATAL(TC("Unpack version code invalid. (version_cd=%d, pack=%d:%s)"), versionCd, _length, _pMemory);
      return EFalse;
   }
   _versionCd = (EPropertyVersion)(versionCd - MO_CM_PACK_VERSION);
   // ��ȡ�����ʽ
   TInt packCd = ReadChar();
   if(packCd < 0){
      MO_FATAL(TC("Unpack pack code invalid. (pack_cd=%d, pack=%d:%s)"), packCd, _length, _pMemory);
      return EFalse;
   }
   _packCd = (EPropertyPack)(packCd - MO_CM_PACK_BASE);
   // ��ȡ�����ʼ
   TInt packBegin = ReadChar();
   if(MO_CM_PACK_BEGIN != packBegin){
      MO_FATAL(TC("Unpack begin invalid. (pack_begin=%d, pack=%d:%s)"), packBegin, _length, _pMemory);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>���������</T>
//============================================================
TBool MPack::UnpackEnd(){
   // ��ȡ�������
   TInt packEnd = ReadChar();
   if(MO_CM_PACK_END != packEnd){
      MO_FATAL(TC("Unpack end invalid. (pack_end=%d, pack=%d:%s)"), packEnd, _length, _pMemory);
      return EFalse;
   }
   return ETrue;
}

//============================================================
// <T>д��������Ϣ��</T>
//
// @param pInfo ������Ϣ
// @return ������
//============================================================
TBool MPack::WriteInfo(const SPropertyInfo* pInfo){
   // ������ƺ�����
   TFsName name;
   if(EPropertyPack_Id == _packCd){
      RInt16::ToHexString(pInfo->Id(), name.Memory(), 4);
      name.SetLength(4);
   }else if(EPropertyPack_Name == _packCd){
      RInt8::ToString2(RString::Length(pInfo->Name()), name.Memory(), 2);
      name.SetLength(2);
      name.Append(pInfo->Name());
   }else{
      MO_FATAL_UNSUPPORT();
   }
   // д������
   WriteString(name);
   // д������
   TFsName type;
   RInt8::ToString2(pInfo->TypeCd(), type.Memory(), 2);
   type.SetLength(2);
   WriteString(type);
   // ���ؽ��
   return ETrue;
}

//============================================================
// <T>д�뿪ʼ���Լ��ϡ�</T>
//
// @param count ����
// @return ������
//============================================================
TBool MPack::WriteAttributeBegin(){
   WriteChar(MO_CM_PACK_ATTRIBUTE_BEGIN);
   return ETrue;
}

//============================================================
// <T>д��������Լ��ϡ�</T>
//
// @return ������
//============================================================
TBool MPack::WriteAttributeEnd(){
   if(_pMemory[_position - 1] == MO_CM_PACK_PROPERTY_SPLITE){
      _pMemory[_position - 1] = MO_CM_PACK_ATTRIBUTE_END;
   }else{
      WriteChar(MO_CM_PACK_ATTRIBUTE_END);
   }
   return ETrue;
}

//============================================================
// <T>д�뿪ʼ�ڵ㼯�ϡ�</T>
//
// @param count ����
//============================================================
TBool MPack::WriteNodeBegin(const SPropertyInfo* pInfo){
   // д��������Ϣ
   WriteInfo(pInfo);
   // д��ڵ��־
   WriteChar(MO_CM_PACK_NODE_BEGIN);
   return ETrue;
}

//============================================================
// <T>д�뿪ʼ�ڵ㼯�ϡ�</T>
//
// @param count ����
//============================================================
TBool MPack::WriteNodeBegin(const SPropertyInfo* pInfo, TInt count){
   // ����Ƿ�Ϊ��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(count > 0){
      valid = ETrue;
   }
   // д������
   if(valid){
      // д��������Ϣ
      WriteInfo(pInfo);
      // д��ڵ��־
      WriteChar(MO_CM_PACK_NODE_BEGIN);
      return ETrue;
   }
   return EFalse;
}

//============================================================
// <T>д������ڵ㼯�ϡ�</T>
//============================================================
TBool MPack::WriteNodeEnd(){
   // д��ڵ��־
   WriteChar(MO_CM_PACK_NODE_END);
   WriteChar(MO_CM_PACK_PROPERTY_SPLITE);
   return ETrue;
}

//============================================================
// <T>д������ڵ㼯�ϡ�</T>
//============================================================
TBool MPack::WriteCollectionBegin(TInt count){
   // ȷ����־
   EnsureSize(_position + 6);
   // д������
   RInt16::ToHexString(count, _pMemory + _position, 4);
   _pMemory[_position + 4] = '{';
   _pMemory[_position + 5] = 0;
   _position += 5;
   // ��������
   if(_length < _position){
      _length = _position;
   }
   return ETrue;
}

//============================================================
// <T>д������ڵ㼯�ϡ�</T>
//============================================================
TBool MPack::WriteCollectionEnd(){
   // ȷ���ڴ�
   EnsureSize(_position + 2);
   // д������
   _pMemory[_position    ] = '}';
   _pMemory[_position + 1] = 0;
   _position += 1;
   // ��������
   if(_length < _position){
      _length = _position;
   }
   return ETrue;
}

//============================================================
// <T>д�벼�����ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyBool(const SPropertyInfo* pInfo, TBool value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(value){
         WritePropertyFixString(pInfo, RBool::ToString(value), 1);
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���ֽ����ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyByte(const SPropertyInfo* pInfo, TByte value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���ַ����ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyChar(const SPropertyInfo* pInfo, TChar value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���з���8λ�������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyInt8(const SPropertyInfo* pInfo, TInt8 value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���з���16λ�������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyInt16(const SPropertyInfo* pInfo, TInt16 value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���з���32λ�������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyInt32(const SPropertyInfo* pInfo, TInt32 value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���з���64λ�������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyInt64(const SPropertyInfo* pInfo, TInt64 value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger64(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���޷���8λ�������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyUint8(const SPropertyInfo* pInfo, TUint8 value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���޷���16λ�������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyUint16(const SPropertyInfo* pInfo, TUint16 value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���޷���32λ�������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyUint32(const SPropertyInfo* pInfo, TUint32 value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���޷���64λ�������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyUint64(const SPropertyInfo* pInfo, TUint64 value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger64(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д�뵥���ȸ��������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyFloat(const SPropertyInfo* pInfo, TFloat value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsFloat(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д��˫���ȸ��������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyDouble(const SPropertyInfo* pInfo, TDouble value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsDouble(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д��ʱ�����ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyTimeTick(const SPropertyInfo* pInfo, TTimeTick value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger64(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д��ʱ������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyTimeSpan(const SPropertyInfo* pInfo, TTimeSpan value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger64(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д��ʱ�����ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyDateTime(const SPropertyInfo* pInfo, TDateTime value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger64(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д��ö�����ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertyEnum(const SPropertyInfo* pInfo, TInt value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д�뼯�����ԡ�</T>
//
// @param pInfo ������Ϣ
// @param value ����
//============================================================
void MPack::WritePropertySet(const SPropertyInfo* pInfo, TInt value){
   // �����Ч��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(0 != value){
      valid = ETrue;
   }
   // д������
   if(valid){
      if(0 != value){
         WritePropertyString(pInfo, TFsInteger(value).ToString());
      }else{
         WritePropertyString(pInfo, NULL);
      }
   }
}

//============================================================
// <T>д���ַ������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param pValue �ַ�������
//============================================================
void MPack::WritePropertyString(const SPropertyInfo* pInfo, TCharC* pValue, TInt length){
   // ����Ƿ�Ϊ��
   TBool valid = EFalse;
   if(-1 == length){
      if(NULL != pValue){
         length = RString::Length(pValue);
      }else{
         length = 0;
      }
   }else{
      MO_ASSERT(pValue);
   }
   if(_optionEmpty){
      valid = ETrue;
   }else if(length > 0){
      valid = ETrue;
   }
   // д������
   if(valid){
      // д��������Ϣ
      WriteInfo(pInfo);
      // д������
      if(0 == length){
         WriteChar(MO_CM_PACK_PROPERTY_EMPTY);
      }else{
         TFsInteger valueLength = RString::Length(pValue);
         TFsInteger valueLengthLength = valueLength.Length();
         WriteString(valueLengthLength);
         WriteString(valueLength);
         WriteString(pValue);
      }
      // д�����Էָ�
      WriteChar(MO_CM_PACK_PROPERTY_SPLITE);
   }
}

//============================================================
// <T>д���ַ������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param pValue �ַ�������
//============================================================
void MPack::WritePropertyFixString(const SPropertyInfo* pInfo, TCharC* pValue, TInt length){
   MO_ASSERT(pValue);
   // ����Ƿ�Ϊ��
   TBool valid = EFalse;
   if(_optionEmpty){
      valid = ETrue;
   }else if(length > 0){
      valid = ETrue;
   }
   // д������
   if(valid){
      // д��������Ϣ
      WriteInfo(pInfo);
      // д������
      if(0 == length){
         WriteChar(MO_CM_PACK_PROPERTY_EMPTY);
      }else{
         WriteString(pValue, length);
      }
      // д�����Էָ�
      WriteChar(MO_CM_PACK_PROPERTY_SPLITE);
   }
}

//============================================================
// <T>д���������ԡ�</T>
//
// @param pInfo ������Ϣ
// @param pValue �ַ�������
//============================================================
void MPack::WritePropertyType(const SPropertyInfo* pInfo, TCharC* pValue){
   WritePropertyString(pInfo, pValue);
}

//============================================================
// <T>��ʼ�����</T>
// <P>1 - �����ʶ(MP#)��</P>
// <P>1 - �汾��ʶ(A)��</P>
//============================================================
TBool MPack::PackBegin(){
   _position = 0;
   Clear();
   // д���ʶ
   WriteString(MO_CM_PACK_SIGN);
   // д��汾
   WriteChar(MO_CM_PACK_VERSION + _versionCd);
   // д������ʽ
   WriteChar(MO_CM_PACK_BASE + _packCd);
   // д������ʼ
   WriteChar(MO_CM_PACK_BEGIN);
   return ETrue;
}

//============================================================
// <T>���������</T>
//============================================================
TBool MPack::PackEnd(){
   // д��������
   WriteChar(MO_CM_PACK_END);
   return ETrue;
}

MO_NAMESPACE_END
