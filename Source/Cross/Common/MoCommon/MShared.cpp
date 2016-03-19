#include "MoCmShared.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>构造共享对象的实例。</T>
//
// @return 实例
//============================================================
MShared::MShared(){
   MO_CLEAR(_gMemory);
}

//============================================================
// <T>释放共享对象的实例。</T>
//============================================================
MShared::~MShared(){
   MO_CLEAR(_gMemory);
}

//============================================================
// <T>共享内存关联完成。</T>
//============================================================
void MShared::OnSharedLinked(){
}

//============================================================
// <T>共享内存初始化。</T>
//============================================================
void MShared::OnSharedInitialize(){
}

//============================================================
// <T>使用已有的共享内存。</T>
//============================================================
void MShared::OnSharedResume(){
}

//============================================================
// <T>共享内存初始化完成。</T>
//============================================================
void MShared::OnSharedComplete(){
}

//============================================================
// <T>是否已经关联过共享内存。</T>
//
// @return 是否关联过
//============================================================
TBool MShared::IsSharedLinked(){
   return (NULL != _gMemory);
}

//============================================================
// <T>获得共享内存指针。</T>
//
// @return 内存指针
//============================================================
TByte* MShared::SharedMemory(){
   return _gMemory;
}

//============================================================
// <T>关联所需的内存。</T>
// <P>内存是新建的时候，初始化共享内存。</P>
//
// @param segment 所需内存
//============================================================
void MShared::SharedLink(TShareSegment segment){
   // 设置内存指针
   _gMemory = (TByte*)segment.Memory();
   // 分配内存
   OnSharedLink(segment);
   // 分配完毕
   OnSharedLinked();
   // 检查内存
   segment.Check();
   if(segment.IsCreated()){
      // 共享内存初始化
      OnSharedInitialize();
   }else{
      // 共享内存链接
      OnSharedResume();
   }
   // 分配完成
   OnSharedComplete();
}

//============================================================
// <T>创建共享内存。</T>
//
// @return 处理结果
//============================================================
TBool MShared::SharedCreate(){
   // 检查内存
   if(NULL != _gMemory){
      MO_FATAL(TC("Shared memory is already exists."));
   }
   // 计算容量
   TSize capacity = SharedCapacity();
   // 分配内存
   TByte* pValue = MO_TYPES_ALLOC(TByte, capacity);
   TShareSegment segment(pValue, capacity, ETrue);
   SharedLink(segment);
   return ETrue;
}

//============================================================
// <T>释放共享内存。</T>
//
// @return 处理结果
//============================================================
TBool MShared::SharedDestory(){
   // 检查内存
   if(NULL == _gMemory){
      MO_FATAL(TC("Shared memory is not exists."));
   }
   // 计算容量
   MO_FREE(_gMemory);
   return ETrue;
}

//============================================================
// <T>输出调试信息。</T>
//============================================================
void MShared::DumpShared(){
}

MO_NAMESPACE_END
