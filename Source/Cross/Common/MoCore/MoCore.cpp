#include "MoCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// ������Ϣ�������
INetMessageFactory* RNetMessageFactory::_pFactory = NULL;

//============================================================
// <T>��ʼ�����Ŀ⡣</T>
//
// @return ���п�
//============================================================
void MoCoreInitialize(){
   // ��ʼ�����ù�����
   RConfigurationManager::Create();
   RXmlContainerManager::Create();
   // ��ʼ��ʱ������
   RTimerManager::Create();
   // ��ʼ��ģ�������
   RModuleManager::Create();
   RApplication::Instance().InterruptListeners()->Push(RModuleManager::Instance().InterruptListener());
   RApplication::Instance().ReloadListeners()->Push(RModuleManager::Instance().ReloadListener());
   RApplication::Instance().UnloadListeners()->Push(RModuleManager::Instance().UnloadListener());
   // ��ʼ������ģ�������
   RSharedModuleManager::Create();
   // ��ʼ�����������
   RServiceManager::Create();
   // ��ʼ������������
   RMonitorService::Create();
   // ��ʼ��ͳ�Ʒ���
   RStatisticsManager::Create();
   // ��ʼ��ģ�������
   RTemplateManager::Create();
   // ��ʼ�����ܹ�����
   RFeatureManager::Create();
}

//============================================================
// <T>�ͷź��Ŀ⡣</T>
//============================================================
void MoCoreRelease(){
   // �ͷŹ��ܹ�����
   RFeatureManager::Destroy();
   // �ͷ�ͳ�Ʒ���
   RStatisticsManager::Destroy();
   // �ͷż���������
   RMonitorService::Destroy();
   // �ͷŷ��������
   RServiceManager::Destroy();
   // �ͷż�ʱ������
   RTimerManager::Destroy();
   // �ͷŹ���ģ�������
   RSharedModuleManager::Destroy();
   // �ͷ�ģ�������
   RApplication::Instance().InterruptListeners()->Remove(RModuleManager::Instance().InterruptListener());
   RApplication::Instance().ReloadListeners()->Remove(RModuleManager::Instance().ReloadListener());
   RApplication::Instance().UnloadListeners()->Remove(RModuleManager::Instance().UnloadListener());
   RModuleManager::Destroy();
   // �ͷ����ù�����
   RConfigurationManager::Destroy();
   RXmlContainerManager::Destroy();
}

MO_NAMESPACE_END
