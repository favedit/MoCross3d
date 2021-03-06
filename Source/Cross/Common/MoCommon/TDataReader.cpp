#include "MoCmStream.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>构造输入数据流的实例。</T>
//
// @return 实例指针
//============================================================
TDataReader::TDataReader(){
   _pReader = NULL;
}

//============================================================
// <T>构造输入数据流的实例。</T>
//
// @param pInput 输入接口
//============================================================
TDataReader::TDataReader(IReader* pReader){
   _pReader = pReader;
}

//============================================================
// <T>析构输入数据流的实例。</T>
//============================================================
TDataReader::~TDataReader(){
}

//============================================================
// <T>获得输入接口。</T>
//
// @return 输入接口
//============================================================
IReader* TDataReader::Reader(){
   return _pReader;
}

//============================================================
// <T>设置输入接口。</T>
//
// @param pInput 输入接口
//============================================================
void TDataReader::SetReader(IReader* pReader){
   _pReader = pReader;
}

//============================================================
// <T>读取数据</T>
//
// @return 返回读取长度
//============================================================
TInt TDataReader::Read(TChar* pData, TSize size){
   return _pReader->Read(pData, size);
}

MO_NAMESPACE_END
