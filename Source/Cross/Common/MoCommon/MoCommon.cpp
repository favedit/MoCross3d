#ifdef _MO_LINUX
#include <libxml/parser.h>
#endif // _MO_LINUX
#include "MoCommon.h"
#include "MoCmSystem.h"
#include "MoCmSingleton.h"
#include "MoCmShared.h"
#include "MoCmSharedList.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ�����п⡣</T>
//============================================================
void MoInitialize(){
   // ��ʼ���ռ���
   RAllocator::Create();
   RMemory::LinkStorage(RAllocator::Storage());
   // ��ʼ��Ψһ���������
   RSingletonManager::SafeCreate();
   // ��ʼ������
   RApplication::Create();
   RApplication::InstallCatcher();
   // ��ʼ����־������
   RLoggerManager::Create();
   RApplication::Instance().InterruptListeners()->Push(RLoggerManager::Instance().InterruptListener());
   RApplication::Instance().ReloadListeners()->Push(RLoggerManager::Instance().ReloadListener());
   RApplication::Instance().UnloadListeners()->Push(RLoggerManager::Instance().UnloadListener());
   RApplication::Instance().ShutdownListeners()->Push(RLoggerManager::Instance().ShutdownListener());
   // ��ʼ���̹߳�����
   RThreadManager::Create();
   // ��ʼ�����������
   RTaskManager::Create();
   // ��ʼ��������������
   RSharedManager::Create();
   // ��ʼ��׽��������
   RCatcherManager::Create();
   // ��ʼö�ٹ�����
   REnumeratorManager::Create();
   // ����־
   RLogger::Link(RLoggerManager::InstancePtr());
   MO_STATIC_INFO(TC("Common framework initialize."));
   // ���������Ϣ
   MO_STATIC_INFO(TC(" - Environment. ( bool=%d,  char8=%d,   char16=%d,   char32=%d)"), sizeof(TBool),  sizeof(TChar8),  sizeof(TChar16),   sizeof(TChar32));
   MO_STATIC_INFO(TC(" - Environment. ( int8=%d,  int16=%d,    int32=%d,    int64=%d)"), sizeof(TUint8), sizeof(TUint16), sizeof(TUint32),   sizeof(TUint64));
   MO_STATIC_INFO(TC(" - Environment. (uint8=%d, uint16=%d,   uint32=%d,   uint64=%d)"), sizeof(TInt8),  sizeof(TInt16),  sizeof(TInt32),    sizeof(TInt64));
   MO_STATIC_INFO(TC(" - Environment. (float=%d, double=%d, datetime=%d, timetick=%d)"), sizeof(TFloat), sizeof(TDouble), sizeof(TDateTime), sizeof(TTimeTick));
   // ��������
   RNetSocket::Startup();
   //............................................................
#ifdef _MO_WINDOWS
   CoInitialize(NULL);
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   xmlInitParser();
#endif // _MO_LINUX
   //............................................................
   // �����������߳�
   RMonitorManager::Create();
   RMonitorManager::Instance().Startup();
}

//============================================================
// <T>�ͷ����п⡣</T>
//============================================================
void MoRelease(){
   // �رռ������߳�
   RMonitorManager::Instance().Shutdown();
   RMonitorManager::Destroy();
   //............................................................
   // �ر�����
   RNetSocket::Cleanup();
   // �ر���־
   MO_STATIC_INFO(TC("Common framework release."));
   RLogger::Link(NULL);
   // �ͷŲ�׽��������
   RCatcherManager::Destroy();
   // �ͷ�ö�ٹ�����
   REnumeratorManager::Destroy();
   // �ͷŹ�����������
   RSharedManager::Destroy();
   // �ͷ����������
   RTaskManager::Destroy();
   // �ͷ��̹߳�����
   RThreadManager::Destroy();
   // �ͷų���
   RApplication::Destroy();
   // �ͷ���־������
   RLoggerManager::Destroy();
   // �ͷ�Ψһ���������
   RSingletonManager::Destroy();
   // �ͷ��ռ���
   RMemory::LinkStorage(NULL);
   RAllocator::Destroy();
   //............................................................
#ifdef _MO_WINDOWS
   CoUninitialize();
#endif // _MO_WINDOWS
#ifdef _MO_LINUX
   xmlCleanupParser();
#endif // _MO_LINUX
}

MO_NAMESPACE_END
