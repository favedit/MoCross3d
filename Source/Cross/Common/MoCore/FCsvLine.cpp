#include "MoCrCsv.h"

MO_NAMESPACE_BEGIN

//============================================================
TBool FCsvLine::WrapedByRefer(TCharC* pValue){
   TString refer = pValue;
   TInt length = refer.Length();
   return (refer[0] == '"' && refer[length - 1] == '"');
}

//============================================================
void FCsvLine::SinglePairRefer(TCharC* pValue, TString& result){
   TString refer = pValue;
   TInt length = refer.Length();
   TInt pos = 0;
   while(pos < length){
      TChar cur = refer[pos];
      if(cur == '"' && pos < length - 1){
         if(refer[pos + 1] == '"'){
            ++pos;
         }
      }
      result.Append(cur);
      ++pos;
   }
}

//============================================================
// <T>����һ�����ݡ�</T>
//============================================================
FCsvLine::FCsvLine(){
   _pHeads = NULL;
   _pCells = MO_CREATE(FStrings); 
}
//============================================================
// <T>����һ�����ݡ�</T>
//
// @param pHeads ��ͷָ�롣
//============================================================
FCsvLine::FCsvLine(FCsvHeads* pHeads){
   _pHeads = pHeads;
   _pCells = MO_CREATE(FStrings); 
}
//============================================================
// <T>����һ�����ݡ�</T>
FCsvLine::~FCsvLine(){ 
   MO_DELETE(_pCells);
}

//============================================================
// <T>��һ�б������ļ���</T>
//
// @param out �ļ��������
//============================================================
void FCsvLine::Store(TDataOutput& out){
   TString csvCell;
   TString csvLine;
   TInt count = _pCells->Count();
   for(TInt n = 0; n < count; n++){
      csvCell.Clear();
      TString tempCell;
      TStringRefer cell = _pCells->Get(n);
      TInt cellLength = cell.Length();
      // ������յĸ�
      MO_ASSERT( 0 != cellLength);
      // ����˫����
      TInt start = 0;
      TInt index = cell.IndexOf('"');
      if(ENotFound != index){
         while(ENotFound != index){
            index++;
            tempCell.Append(cell.SubStrC(start, index));
            // �������ſ�ͷ���β
            if(index != 1 && index != cellLength){
               tempCell.Append('"');
            }else{
               tempCell.Append('"');
               tempCell.Append('"');
            }
            start = index;
            if(start < cellLength){
               index = cell.IndexOf('"', start);
            }else{
               break;
            }
         }
         // ������������
         if(start < cellLength - 1){
            tempCell.Append(cell.SubStrC(start, cell.Length()));
         }
      }else{
         tempCell = cell;
      }
      // ������
      TInt tempCellLen = tempCell.Length();
      if(tempCell.Contains(',')){
         // ���ԡ���ͷ
         if(tempCell[0] != '"'){
            csvCell.Append('"');
         }
         csvCell.Append(tempCell);
         // ���ԡ���β
         if(tempCell[tempCellLen  -1] != '"'){
            csvCell.Append('"');
         }
      }else{
         csvCell = tempCell;
      }
      // �����з�
      TInt csvCellLen = csvCell.Length();
      TInt lfStart = 0;
      TInt lfIndex = csvCell.IndexOf('\n');
      if(ENotFound != lfIndex){
         while(ENotFound != lfIndex){
            //  �������з�ǰ�������
            if(lfStart < lfIndex){
               TString sub = csvCell.SubStrC(lfStart, lfIndex);
               csvLine.Append(sub);
            }
            csvLine.Append('\\');
            csvLine.Append('n');
            // �������з�
            lfIndex++;
            lfStart = lfIndex;
            if(lfStart < csvCellLen){
               lfIndex = csvCell.IndexOf('\n', lfStart);
            }else{
               break;
            }  
         }
         if(lfStart < csvCellLen - 1){
            TString sub = csvCell.SubStrC(lfStart, csvCell.Length());
            csvLine.Append(sub);
         }
      }else{
         csvLine.Append(csvCell);
      }
      // һ���ʽ������
      if((count - 1) == n){
         csvLine.Append('\n');
      }else{
         csvLine.Append(',');
      }  
   }
   out.Write((TCharC*)csvLine, csvLine.Length());
}

//============================================================
// <T>���������һ�С�</T>
//
// @param pLine �����һ�С�
//============================================================
void FCsvLine::Parse(TCharC* pLine){
   TStringRefer line = pLine;
   TInt lineLength = line.Length();
   TInt cellStart, cellEnd, pos, dummy;
   cellStart = cellEnd = pos = dummy = 0;
   while(pos < lineLength){
      TChar cur = pLine[pos];
      if(cur == '"'){
         dummy++;
      }else if(cur == ','){
         TInt dummyTemp = dummy % 2;
         if(0 == dummyTemp){
            dummy = 0;
            cellEnd = pos;
            if(cellEnd == cellStart){
               _pCells->Push(TC(""));
            }else{
               TString cellText = line.SubStrC(cellStart, cellEnd);
               TInt cellTextLen = cellText.Length();
               TString cell;
               if(WrapedByRefer(cellText)){
                  TString tempCell = cellText.SubStrC(1, cellTextLen - 1);
                  SinglePairRefer(tempCell, cell);
               }else{
                  SinglePairRefer(cellText, cell);
               }
               _pCells->Push(cell);
            }
            cellStart = cellEnd + 1;
         }
      }else if(cur == '\n'){
         cellEnd = pos;
         dummy %= 2;
         MO_ASSERT(0 == dummy);
         if(cellEnd == cellStart){
            _pCells->Push(TC(""));
         }else{
            TString cellText = line.SubStrC(cellStart, cellEnd);
            TInt cellTextLen = cellText.Length();
            TString cell;
            if(WrapedByRefer(cellText)){
               TString tempCell = cellText.SubStrC(1, cellTextLen - 1);
               SinglePairRefer(tempCell, cell);
            }else{
               SinglePairRefer(cellText, cell);
            }
            _pCells->Push(cell);
         }
      }     
      pos++;
   }
}

//============================================================
// <T>�����һ�����ݵĸ�����</T>
//
// @return ��һ�����ݵĸ�����
//============================================================
TInt FCsvLine::Count(){
   return _pCells->Count();
}

//============================================================
// <T>�ҵ��е���š�</T>
//
// @param pName �е����ơ�
// @return �е���š�
void FCsvLine::SetHeads(FCsvHeads* pHeads){
   _pHeads = pHeads;
}

//============================================================
// <T>���ָ����,����ų�������ʱ���⡣</T>
//
// @param index �е���š�
// @return �е�ֵ��
//============================================================
TCharC* FCsvLine::At(TInt index){
   return _pCells->Get(index);
}

//============================================================
// <T>���ָ���У�����ų�������ʱ����������Ĭ��ֵ��</T>
//
// @param index �е���š�
// @return �е�ֵ��
//============================================================
TCharC* FCsvLine::At(TInt index, TCharC* pValue){
   TInt count = _pCells->Count();
   if(index < count){
      return _pCells->Get(index);
   }
   return pValue;
}

//============================================================
// <T>���ָ����,����ų�������ʱ���⡣</T>
//
// @param index �е���š�
// @return �е�ֵ��
//============================================================
TBool FCsvLine::AtBoolean(TInt index){
   TCharC* pCell = _pCells->Get(index);
   return RBool::ParseNvl(pCell);
}

//============================================================
// <T>���ָ���У�����ų�������ʱ����������Ĭ��ֵ��</T>
//
// @param index �е���š�
// @param default Ĭ��ֵ��
// @return �е�ֵ��
//============================================================
TBool FCsvLine::AtBoolean(TInt index, TBool value){
   TInt count = _pCells->Count();
   if(index < count){
      TBool result = RBool::ParseNvl(_pCells->Get(index));
      return result;
   }
   return value;
}

//============================================================
// <T>���ָ����,����ų�������ʱ���⡣</T>
//
// @param index �е���š�
// @return �е�ֵ��
//============================================================
TInt FCsvLine::AtInt(TInt index){
   TCharC* pValue = _pCells->Get(index);
   TInt result = RInt::ParseNvl(pValue);
   return result;
}

//============================================================
// <T>���ָ���У�����ų�������ʱ����������Ĭ��ֵ��</T>
//
// @param index �е���š�
// @param default Ĭ��ֵ��
// @return �е�ֵ��
//============================================================
TInt FCsvLine::AtInt(TInt index, TInt value){
   TInt count = _pCells->Count();
   if(index < count){
      TInt result = RInt::ParseNvl(_pCells->Get(index));
      return result;
   }
   return value;
}

//============================================================
// <T>���ָ����,����ų�������ʱ���⡣</T>
//
// @param index �е���š�
// @return �е�ֵ��
//============================================================
TFloat FCsvLine::AtFloat(TInt index){
   TCharC* pValue = _pCells->Get(index);
   TFloat result = RFloat::ParseNvl(pValue);
   return result;
}

//============================================================
// <T>���ָ���У�����ų�������ʱ����������Ĭ��ֵ��</T>
//
// @param index �е���š�
// @param default Ĭ��ֵ��
// @return �е�ֵ��
//============================================================
TFloat FCsvLine::AtFloat(TInt index, TFloat value){
   TInt count = _pCells->Count();
   if(index < count){
      TCharC* pValue = _pCells->Get(index);
      TFloat result = RFloat::ParseNvl(pValue);
      return result;
   }
   return value;
}

//============================================================
// <T>����������ȡĳ���ϵ����ݡ�</T>
//
// @param pName �е����ơ�
// @return �����ϵ����ݡ�
//============================================================
TCharC* FCsvLine::Get(TCharC* pName){
   TInt index = _pHeads->IndexOf(pName);
   return _pCells->Get(index);
}

//============================================================
// <T>����������ȡĳ���ϵ����ݡ�</T>
//
// @param pName �е����֡�
// @param default û��ָ��������ʱ���ص�ֵ��
// @return �����ϵ����ݡ�
//============================================================
TCharC* FCsvLine::Get(TCharC* pName, TCharC* pValue){
   TInt index = _pHeads->IndexOf(pName);
   return At(index, pValue);
}

//============================================================
// <T>����������ȡĳ���ϵ����ݡ�</T>
//
// @param pName �е����ơ�
// @return �����ϵ����ݡ�
//============================================================
TBool FCsvLine::GetBoolean(TCharC* pName){
   TInt index = _pHeads->IndexOf(pName);
   return AtBoolean(index);
}

//============================================================
// <T>����������ȡĳ���ϵ����ݡ�</T>
//
// @param pName �е����֡�
// @param default û��ָ��������ʱ���ص�ֵ��
// @return �����ϵ����ݡ�
//============================================================
TBool FCsvLine::GetBoolean(TCharC* pName, TBool value){
   TInt index = _pHeads->IndexOf(pName);
   return AtBoolean(index, value);
}


//============================================================
// <T>����������ȡĳ���ϵ����ݡ�</T>
//
// @param pName �е����ơ�
// @return �����ϵ����ݡ�
//============================================================
TInt FCsvLine::GetInt(TCharC* pName){
   TInt index = _pHeads->IndexOf(pName);
   return AtInt(index);
}

//============================================================
// <T>����������ȡĳ���ϵ����ݡ�</T>
//
// @param pName �е����֡�
// @param default û��ָ��������ʱ���ص�ֵ��
// @return �����ϵ����ݡ�
//============================================================
TInt FCsvLine::GetInt(TCharC* pName, TInt value){
   TInt index = _pHeads->IndexOf(pName);
   return AtInt(index, value);
}

//============================================================
// <T>����������ȡĳ���ϵ����ݡ�</T>
//
// @param pName �е����ơ�
// @return �����ϵ����ݡ�
//============================================================
TFloat FCsvLine::GetFloat(TCharC* pName){
   TInt index = _pHeads->IndexOf(pName);
   return AtFloat(index);
}

//============================================================
// <T>����������ȡĳ���ϵ����ݡ�</T>
//
// @param pName �е����֡�
// @param default û��ָ��������ʱ���ص�ֵ��
// @return �����ϵ����ݡ�
//============================================================
TFloat FCsvLine::GetFloat(TCharC* pName, TFloat value){
   TInt index = _pHeads->IndexOf(pName);
   return AtFloat(index, value);
}

//============================================================
// <T>���ø���ĳ���ϵ����ݡ�</T>
//
// @param index �е�������
// @param pValue �������ݵ�ֵ��
//============================================================
void FCsvLine::Set(TInt index, TCharC* pValue){
   _pCells->Set(index, pValue);
}

//============================================================
// <T>���ø���ĳ���ϵ����ݡ�</T>
//
// @param index �е�������
// @param value �������ݵ�ֵ��
//============================================================
void FCsvLine::SetBoolean(TInt index, TBool value){
   TCharC* pValue = RBool::ToString(value);
   _pCells->Set(index, pValue);
}

//============================================================
// <T>���ø���ĳ���ϵ����ݡ�</T>
//
// @param index �е�������
// @param value �������ݵ�ֵ��
//============================================================
void FCsvLine::SetInt(TInt index, TInt value){
   TChar buffer[16];
   RInt::ToString(value, buffer, 16);
   _pCells->Set(index, buffer);
}

//============================================================
// <T>���ø���ĳ���ϵ����ݡ�</T>
//
// @param index �е�������
// @param value �������ݵ�ֵ��
//============================================================
void FCsvLine::SetFloat(TInt index, TFloat value){
   TChar buffer[32];
   RFloat::ToString(value, buffer, 32);
   _pCells->Set(index, buffer);
}

//============================================================
// <T>���ָ�����ϵ�һ�����ݡ�</T>
//
// @param pName �е����ơ�
// @param value �����ϵ�ֵ��
//============================================================
void FCsvLine::Put(TCharC* pName, TCharC* pValue){
   TInt index = _pHeads->IndexOf(pName);
   _pCells->Set(index, pValue);
}

//============================================================
// <T>���ָ�����ϵ�һ�����ݡ�</T>
//
// @param pName �е����ơ�
// @param value �����ϵ�ֵ��
//============================================================
void FCsvLine::PutBoolean(TCharC* pName, TBool value){
   TInt index = _pHeads->IndexOf(pName);
   SetBoolean(index, value);
}

//============================================================
// <T>���ָ�����ϵ�һ�����ݡ�</T>
//
// @param pName �е����ơ�
// @param value �����ϵ�ֵ��
//============================================================
void FCsvLine::PutInt(TCharC* pName, TInt value){
   TInt index = _pHeads->IndexOf(pName);
   SetInt(index, value);
}

//============================================================
// <T>���ָ�����ϵ�һ�����ݡ�</T>
//
// @param pName �е����ơ�
// @param value �����ϵ�ֵ��
//============================================================
void FCsvLine::PutFloat(TCharC* pName, TFloat value){
   TInt index = _pHeads->IndexOf(pName);
   SetFloat(index, value);
}

//============================================================
// <T>׷�ӵ�����һ�����ݡ�</T>
//
// @param value �������ݵ�ֵ��
//============================================================
void FCsvLine::Push(TCharC* pValue){
   _pCells->Push(pValue);
}

//============================================================
// <T>׷�ӵ�����һ�����ݡ�</T>
//
// @param value �������ݵ�ֵ��
//============================================================
void FCsvLine::PushBoolean(TBool value){
   _pCells->Push(RBool::ToString(value));
}

//============================================================
// <T>׷�ӵ�����һ�����ݡ�</T>
//
// @param value �������ݵ�ֵ��
//============================================================
void FCsvLine::PushInt(TInt value){
   TChar buffer[16];
   RInt::ToString(value, buffer, 16);
   _pCells->Push(buffer);
}

//============================================================
// <T>׷�ӵ�����һ�����ݡ�</T>
//
// @param value �������ݵ�ֵ��
//============================================================
void FCsvLine::PushFloat(TFloat value){
   TChar buffer[32];
   RFloat::ToString(value, buffer, 32);
   _pCells->Push(buffer);
}

MO_NAMESPACE_END
