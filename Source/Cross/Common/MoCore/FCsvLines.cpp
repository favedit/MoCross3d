#include "MoCrCsv.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������������ݡ�</T>
//============================================================
FCsvLines::FCsvLines(FCsvHeads* pHeads){
   _pHeads = pHeads;
   _pLines = MO_CREATE(FCsvLineVector);
}

//============================================================
// <T>������������ݡ�</T>
//============================================================
FCsvLines::~FCsvLines(){
   TInt count = _pLines->Count();
   for(TInt n =0; n < count; n++){
      FCsvLine* pLine = _pLines->Get(n);
      MO_DELETE(pLine);
   }
   MO_DELETE(_pLines);
}

//============================================================
// <T>��ȡ���������</T>
//
// @return �������������
//============================================================
TInt FCsvLines::Count(){
   return _pLines->Count();
}

//============================================================
// <T>��ȡָ������ŵ������ݡ�</T>
//
// @param index �е����ơ�
// @return �����ݡ�
//============================================================
FCsvLine* FCsvLines::Get(TInt index){
   return _pLines->Get(index);
}

//============================================================
// <T>����һ�������ݣ���ָ���кţ�Ĭ��Ϊĩβ��</T>
//
// @param index �кš�
// @return  �¼���������ݡ�
//============================================================
FCsvLine* FCsvLines::Insert(TInt index){
   FCsvLine* pLine = MO_CREATE(FCsvLine, _pHeads);
   if(-1 == index){
      _pLines->Push(pLine);
   }else{
      _pLines->Insert(index, pLine);
   }
   return pLine;
}

//============================================================
// <T>��������д���ļ���</T>
//
// @param out �ļ�����
//============================================================
void FCsvLines::Store(TDataOutput& out){
   TString dataBegin(TC("@data\n"));
   out.Write((TCharC*)dataBegin, dataBegin.Length());
   TInt count = _pLines->Count();
   for(TInt n =0; n < count; n++){
      FCsvLine* pLine = _pLines->Get(n);
      pLine->Store(out);
   }
   TString check;
   check.AppendFormat(TC("@check data.row=%d\n"), count);
   out.Write((TCharC*)check, check.Length());
}

//============================================================
// <T>��������������ݡ�</T>
//
// @param pValue ���е��������ַ�����
//============================================================
void FCsvLines::Parse(TCharC* pValue){
   TStringRefer temp = pValue;
   TInt linesEnd = temp.Find(TC("@check data.row="));
   MO_ASSERT(ENotFound != linesEnd);
   TInt rowCountStart = temp.IndexOf('=', linesEnd);
   TInt rowCountEnd = temp.IndexOf('\n', rowCountStart);
   TFsName rowCountString = temp.SubStrC(rowCountStart + 1, rowCountEnd);
   TInt rowCount = RInt::Parse(rowCountString);
   TStringRefer lines = temp.SubPtrC(0, linesEnd);
   TInt linesLenth = lines.Length();
   TInt lineStart = 0;
   TInt count = 0;
   while(lineStart < linesLenth){
      TInt lineEnd = lines.IndexOf('\n', lineStart);
      FCsvLine* pLine = MO_CREATE(FCsvLine, _pHeads);
      _pLines->Push(pLine);
      TString onrLine = lines.SubStrC(lineStart, lineEnd + 1);
      pLine->Parse(onrLine);
      lineStart = lineEnd + 1;
      ++count;
   }
   MO_ASSERT(count == rowCount);
}

MO_NAMESPACE_END
