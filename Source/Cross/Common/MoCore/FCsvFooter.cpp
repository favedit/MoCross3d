#include "MoCrCsv.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>构造一个表尾项。</T>
//============================================================
FCsvFooter::FCsvFooter(){ 
   _index = ENotFound; 
}

//============================================================
// <T>销毁一个表尾项。</T>
//============================================================
FCsvFooter::~FCsvFooter()  {
}

//============================================================
// <T>根据尾部项索引。</T>
//
// @return 尾部项索引。
//============================================================
TInt FCsvFooter::Index(){ 
   return _index;                 
}

//============================================================
// <T>获取尾部项名称。</T>
//
// @return 尾部项名称。
//============================================================
TCharC* FCsvFooter::Name(){ 
   return (TCharC*)_name;         
}

//============================================================
// <T>获取尾部项标题。</T>
//
// @return 尾部项标题。
//============================================================
TCharC* FCsvFooter::Label(){ 
   return (TCharC*)_label;        
}

//============================================================
// <T>获取尾部项描述。</T>
//
// @return 尾部项描述。
//============================================================
TCharC* FCsvFooter::Description(){ 
   return (TCharC*)_description;  
}

//============================================================
// <T>设置尾部项索引。</T>
//
// @param index 尾部项索引。
//============================================================
void FCsvFooter::SetIndex(TInt index){ 
   _index = index;               
}

//============================================================
// <T>设置尾部项名字。</T>
//
// @param name 尾部项名字。
//============================================================
void FCsvFooter::SetName(TCharC* name){ 
   _name = name;              
}

//============================================================
// <T>设置尾部项标题。</T>
//
// @param label 尾部项标题。
//============================================================
void FCsvFooter::SetLabel(TCharC* label){ 
   _label = label;             
}

//============================================================
// <T>设置尾部项描述。</T>
//
// @param description 尾部项描述。
//============================================================
void FCsvFooter::SetDescription(TCharC* description){ 
   _description = description;   
}

MO_NAMESPACE_END
