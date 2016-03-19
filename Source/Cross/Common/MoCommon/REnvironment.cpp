#include "MoCmSystem.h"

#define MO_ARG_HOME TC("-home")

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������·���������·����</T>
// <P>��·������-home��������ġ�</P>
//
// @param pPath ���·��
// @param ... ����
// @return ����·��
//============================================================
TFsPath REnvironment::MappingPath(TCharC* pPath, ...){
   MO_ASSERT(pPath);
   TFsPath path;
   // �����Ŀ¼
   TCharC* pHome = RApplication::Instance().Parameters()->FindValue(MO_ARG_HOME);
   if(NULL == pHome){
#ifdef _MO_WINDOWS
      path = RApplication::GetCurrentDirectory();
#else
      MO_ASSERT(pHome);
#endif
   }else{
      path = pHome;
   }
   // ����·��
   va_list params;
   va_start(params, pPath);
   path.AppendFormatParameters(pPath, params);
   va_end(params);
   // ��ʽ��
   path.Replace('\\', '/');
   TFileInfo fileInfo = (TCharC*)path;
   path.Assign(fileInfo.FullName());
   return path;
}

MO_NAMESPACE_END
