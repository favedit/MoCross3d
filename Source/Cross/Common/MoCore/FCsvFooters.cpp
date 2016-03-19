#include "MoCrCsv.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����β���</T>
//============================================================
FCsvFooters::FCsvFooters(){
   _pFooters = MO_CREATE(FCsvFooterDictionary);
}

//============================================================
// <T>����β���</T>
//============================================================
FCsvFooters::~FCsvFooters(){
   FDictionary<FCsvFooter*>::TIteratorC it = _pFooters->IteratorC();
   while(it.Next()){
      FCsvFooter* pFooter = it.Value();
      MO_DELETE(pFooter);
   }
   MO_DELETE(_pFooters);
}

//============================================================
// <T>�������ƻ�ȡĳ��β����������</T>
//
// @param pFootName β��������ơ�
// @return ĳ��β����������
//============================================================
TInt FCsvFooters::IndexOf(TCharC* pFootName){ 
   FCsvFooter* pFooter = _pFooters->Find(pFootName);
   if(pFooter){
      return pFooter->Index();
   }
   return ENotFound;
}

//============================================================
// <T>����һ���µ�β���</T>
//
// @param pName β��������ơ�
// @param index β����Ĳ���λ�á�
// @return �µ�β���
//============================================================
FCsvFooter* FCsvFooters::Insert(TCharC* pName, TInt index){
   FCsvFooter* pFoot = MO_CREATE(FCsvFooter);
   pFoot->SetName(pName);
   _pFooters->Set(pName, pFoot);
   return pFoot;
}

//============================================================
// <T>��β��������ļ���</T>
//
// @param out ����ļ�����
//============================================================
void FCsvFooters::Store(TDataOutput& out){
   FDictionary<FCsvFooter*>::TIteratorC it = _pFooters->IteratorC();
   TString foot = TC("@footer.name\n");
   TBool showLabel = EFalse;
   TBool showDescription = EFalse;
   TInt count = 0;
   TInt lastFooterIndex = _pFooters->Count() - 1;
   while(it.Next()){
      FCsvFooter* pFoot = it.Value();
      foot.Append(pFoot->Name());
      if(count != lastFooterIndex){
         foot.Append(',');
      }else{
         foot.Append('\n');
      }

      TInt labelLength = RString::Length(pFoot->Label());
      if(labelLength){
         showLabel = ETrue;
      }
      TInt desLength = RString::Length(pFoot->Description());
      if(desLength){
         showDescription= ETrue;
      }
      ++count;
   }
   if(showLabel){
      foot.Append(TC("@footer.label\n"));
      count = 0;
      it.Reset();
      while(it.Next()){
         FCsvFooter* pFoot = it.Value();
         foot.Append(pFoot->Label());
         if(count != lastFooterIndex){
            foot.Append(',');
         }else{
            foot.Append('\n');
         }
      }
   }
   if(showDescription){
      foot.Append(TC("@head.description\n"));
      count = 0;
      it.Reset();
      while(it.Next()){
         FCsvFooter* pFoot = it.Value();
         foot.Append(pFoot->Description());
         if(count != lastFooterIndex){
            foot.Append(',');
         }else{
            foot.Append('\n');
         }
      }
   }
   out.Write((TCharC*)foot, foot.Length());
}

//============================================================
// <T>�������β���</T>
//
// @param pValue β�����ַ�����
//============================================================
void FCsvFooters::Parse(TCharC* pValue){
   TStringRefer foot = pValue;
   TInt namesBegin = foot.IndexOf('\n') + 1;
   TInt namesEnd = foot.IndexOf('\n', namesBegin);
   TBool hasLabel = EFalse;
   TInt labelsBegin = ENotFound;
   TInt labelsEnd = ENotFound;
   // ����label
   TInt headLength = foot.Length();
   if(namesEnd != headLength -1){
      hasLabel = ETrue;
      labelsBegin =  foot.IndexOf('\n', namesEnd + 1) + 1;
      labelsEnd = foot.IndexOf('\n', labelsBegin);
   }
   TInt nameBegin = namesBegin;
   TInt nameEnd = foot.IndexOf(',', nameBegin);
   TInt labelBegin = ENotFound;
   TInt labelEnd = ENotFound;
   if(hasLabel){
      labelBegin = labelsBegin;
      labelEnd = foot.IndexOf(',', labelBegin);
   }
   TInt count = 0;
   while(nameBegin < namesEnd){
      if(ENotFound == nameEnd){
         nameEnd = namesEnd;
         if(hasLabel){
            MO_ASSERT(ENotFound == labelEnd);
            labelEnd = labelsEnd;
         }
      }
      FCsvFooter* pFooter = MO_CREATE(FCsvFooter);
      pFooter->SetIndex(count);
      TFsName name = foot.SubStrC(nameBegin, nameEnd);
      pFooter->SetName(name);
      _pFooters->Set(pFooter->Name(), pFooter);
      nameBegin = nameEnd + 1;
      if(nameBegin < namesEnd){
         nameEnd = foot.IndexOf(',', nameBegin);
      }
      if(hasLabel){
         TFsLabel label = foot.SubStrC(labelBegin, labelEnd);
         pFooter->SetLabel(label);
         labelBegin = labelEnd + 1;
         if(labelBegin < labelsEnd){
            labelEnd =  foot.IndexOf(',', labelBegin);
         }
      }
      count++;
   }
}

MO_NAMESPACE_END
