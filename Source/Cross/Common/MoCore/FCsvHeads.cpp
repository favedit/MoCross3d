#include "MoCrCsv.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����csvͷ����</T>
//============================================================
FCsvHeads::FCsvHeads(){
   _pHeads = MO_CREATE(FCsvHeadDictionary);
}

//============================================================
// <T>����csvͷ����</T>
//============================================================
FCsvHeads::~FCsvHeads(){
   FDictionary<FCsvHead*>::TIteratorC it = _pHeads->IteratorC();
   while(it.Next()){
      FCsvHead* pHead = it.Value();
      MO_DELETE(pHead);
   }
   MO_DELETE(_pHeads);
}

//============================================================
// <T>�ҵ��е���š�</T>
//
// @param pName �е����ơ�
// @return �е���š�
//============================================================
TInt FCsvHeads::IndexOf(TCharC* pHeadName){ 
   FCsvHead* pHeader = _pHeads->Find(pHeadName);
   if(pHeader){
      return pHeader->Index();
   }
   return ENotFound;
}

//============================================================
// <T>��ͷ�������ļ���</T>
//
// @param pName �е����ơ�
// @return �½���ͷ����
//============================================================
FCsvHead* FCsvHeads::Insert(TCharC* pName){
   FCsvHead* pHead = MO_CREATE(FCsvHead);
   TInt count = _pHeads->Count();
   pHead->SetName(pName);
   pHead->SetIndex(count);
   _pHeads->Set(pName, pHead);
   return pHead;
}

//============================================================
// <T>��ͷ�������ļ���</T>
//
// @param out �ļ��������
//============================================================
void FCsvHeads::SaveToFile(TDataOutput& out){
   FDictionary<FCsvHead*>::TIteratorC it = _pHeads->IteratorC();
   TString head = TC("@head.name\n");
   TBool showLabel = EFalse;
   TBool showDescription = EFalse;
   TInt count = 0;
   TInt headCount = _pHeads->Count() - 1;
   while(it.Next()){
      FCsvHead* pHead = it.Value();
      head.Append(pHead->Name());
      if(count != headCount){
         head.Append(',');
      }else{
         head.Append('\n');
      }
      TInt labelLength = RString::Length(pHead->Label());
      if(labelLength){
         showLabel = ETrue;
      }
      TInt desLength = RString::Length(pHead->Description());
      if(desLength){
         showDescription= ETrue;
      }
      ++count;
   }
   if(showLabel){
      head.Append(TC("@head.label\n"));
      count = 0;
      it.Reset();
      while(it.Next()){
         FCsvHead* pHead = it.Value();
         head.Append(pHead->Label());
         if(count != headCount){
            head.Append(',');
         }else{
            head.Append('\n');
         }
      }
   }
   if(showDescription){
      head.Append(TC("@head.description\n"));
      count = 0;
      it.Reset();
      while(it.Next()){
         FCsvHead* pHead = it.Value();
         head.Append(pHead->Description());
         if(count != headCount){
            head.Append(',');
         }else{
            head.Append('\n');
         }
      }
   }
   out.Write((TCharC*)head, head.Length());
}

//============================================================
// <T>���������ͷ���ַ�����</T>
//
// @param pValue �����ͷ���ַ�����
//============================================================
void FCsvHeads::Parse(TCharC* pValue){
   TStringRefer head = pValue;
   TInt headNamesBegin = head.IndexOf('\n') + 1;
   TInt headNamesEnd = head.IndexOf('\n', headNamesBegin);
   TBool hasLabel = EFalse;
   TInt labelsBegin = ENotFound;
   TInt labelsEnd = ENotFound;
   // ����label
   TInt headLength = head.Length();
   if(headNamesEnd != headLength -1){
      hasLabel = ETrue;
      labelsBegin =  head.IndexOf('\n', headNamesEnd + 1) + 1;
      labelsEnd = head.IndexOf('\n', labelsBegin);
   }
   TInt nameBegin = headNamesBegin;
   TInt nameEnd = head.IndexOf(',', nameBegin);
   TInt labelBegin = ENotFound;
   TInt labelEnd = ENotFound;
   if(hasLabel){
      labelBegin = labelsBegin;
      labelEnd = head.IndexOf(',', labelBegin);
   }
   TInt count = 0;
   while(nameBegin < headNamesEnd){
      if(ENotFound == nameEnd){
         nameEnd = headNamesEnd;
         if(hasLabel){
            MO_ASSERT(ENotFound == labelEnd);
            labelEnd = labelsEnd;
         }

      }
      FCsvHead* pHead = MO_CREATE(FCsvHead);
      pHead->SetIndex(count);
      TFsName name = head.SubStrC(nameBegin, nameEnd);
      pHead->SetName(name);
      _pHeads->Set(pHead->Name(), pHead);
      nameBegin = nameEnd + 1;
      if(nameBegin < headNamesEnd){
         nameEnd = head.IndexOf(',', nameBegin);
      }
      if(hasLabel){
         TFsLabel label = head.SubStrC(labelBegin, labelEnd);
         pHead->SetLabel(label);
         labelBegin = labelEnd + 1;
         if( labelBegin < labelsEnd){
            labelEnd =  head.IndexOf(',', labelBegin);
         }
      }
      count++;
   }  
}

MO_NAMESPACE_END
