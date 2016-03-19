#include "MoCrCsv.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����һ�����Ρ�</T>
//============================================================
FCsvSegment::FCsvSegment(){
   _name = TC("default");
   _pHeads = MO_CREATE(FCsvHeads);
   _pLines = MO_CREATE(FCsvLines, _pHeads);
   _pFooters = MO_CREATE(FCsvFooters);
}

//============================================================
// <T>����һ�����Ρ�</T>
//============================================================
FCsvSegment::~FCsvSegment(){
   MO_DELETE(_pHeads);
   MO_DELETE(_pLines);
   MO_DELETE(_pFooters);
}

//============================================================
// <T>��ȡ��ε����֡�</T>
//
// @return  ��ε����֡�
//============================================================
TCharC* FCsvSegment::Name(){ 
   return (TCharC*)_name;
}

//============================================================
// <T>��ȡ���ͷ����</T>
//
// @return  ���ͷ����
//============================================================
FCsvHeads* FCsvSegment::Heads() {
   return _pHeads;
}

//============================================================
// <T>��ȡ ��ε������ݡ�</T>
//
// @return  ��ε������ݡ�
//============================================================
FCsvLines* FCsvSegment::Lines(){
   return _pLines;
}

//============================================================
// <T>��ȡ��ε�β�</T>
//
// @return  ��ε�β�
//============================================================
FCsvFooters* FCsvSegment::Footers(){
   return _pFooters;
}

//============================================================
// <T>��һ����ͷ��</T>
//
// @return  ���ͷ��
//============================================================
FCsvHead* FCsvSegment::InsertHead(TCharC* pName){
   FCsvHead* pHead = _pHeads->Insert(pName);
   return pHead;
}

//============================================================
// <T>��һ���µ����ݡ�</T>
//
// @return  һ���µ����ݡ�
//============================================================
FCsvLine* FCsvSegment::InsertLine(){
   FCsvLine* pLine = _pLines->Insert();
   return pLine;
}

//============================================================
// <T>��һ����β��</T>
//
// @return  ���β��
//============================================================
FCsvFooter* FCsvSegment::InsertFooter(TCharC* pName){
   return _pFooters->Insert(pName);
}

//============================================================
// <T>���ñ�ε����֡�</T>
//
// @param  pName ��ε����֡�
//============================================================
void FCsvSegment::SetName(TCharC* pName) { 
   _name = pName; 
}

//============================================================
// <T>����δ����ļ���</T>
//
// @param out ����ļ�����
// @param saveHead �Ƿ񱣴��ͷ����Ϣ��
//============================================================
void FCsvSegment::Store(TDataOutput& out, TBool saveHead){
   if(saveHead){
      TString segmentBegin;
      segmentBegin.Append(TC("@segment.start "));
      segmentBegin.Append(_name);
      segmentBegin.Append('\n');
      out.Write((TCharC*)segmentBegin, segmentBegin.Length());
   }
   _pHeads->SaveToFile(out);
   _pLines->Store(out);
   _pFooters->Store(out);
   if(saveHead){
      TString segmentEnd;
      segmentEnd.Append(TC("@segment.end\n"));
      out.Write((TCharC*)segmentEnd, segmentEnd.Length());
   }
}

MO_NAMESPACE_END
