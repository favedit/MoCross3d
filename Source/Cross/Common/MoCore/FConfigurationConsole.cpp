#include <MoCmSystem.h>
#include "MoCrConfigruation.h"

#define MO_TAG_INCLUDE   TC("Include")
#define MO_TAG_COMPONENT TC("Component")
#define MO_PTY_FILE      TC("file")
#define MO_PTY_NAME      TC("name")

MO_NAMESPACE_BEGIN

//============================================================
// <T>��������ö������̨��</T>
//
// @return �����ö������̨
//============================================================
FConfigurationConsole::FConfigurationConsole(){
   _pConfigurations = MO_CREATE(FConfiguraList);
   _pNodes = MO_CREATE(FXmlNodeDictionary);
   _pDocuments = MO_CREATE(FXmlDocumentList);
}

//============================================================
// <T>���������ö������̨��</T>
//============================================================
FConfigurationConsole::~FConfigurationConsole(){
   MO_DELETE(_pNodes);
   MO_DELETE(_pConfigurations);
   if(!_pDocuments->IsEmpty()){
      TListIteratorC<FXmlDocument*> iterator =  _pDocuments->IteratorC();
      while(iterator.Next()){
         FXmlDocument* pDocument = *iterator;
         MO_DELETE(pDocument);
      }
   }
   MO_DELETE(_pDocuments);
}

//============================================================
// <T>ע������ö���</T>
//
// @param pConfig ���ö���
//============================================================
void FConfigurationConsole::Register(IConfiguration* pConfiguration){
   _pConfigurations->Push(pConfiguration);
}

//============================================================
// <T>ע�������ö���</T>
//
// @param pConfig �����ö���
//============================================================
void FConfigurationConsole::Unregister(IConfiguration* pConfiguration){
   _pConfigurations->Remove(pConfiguration);
}

//============================================================
// <T>���������ļ���</T>
//
// @param pFileName �ļ�����
//============================================================
TBool FConfigurationConsole::LoadFile(TCharC* pFileName){
   // ���ļ�
   FXmlDocument* pDocument = MO_CREATE(FXmlDocument);
   if(!pDocument->LoadFile(pFileName)){
      // �����ļ�ʧ�ܡ�
      MO_PFATAL(LoadFile);
      return EFalse;
   }
   _pDocuments->Push(pDocument);
   // ��ȡ���ýڵ�
   if(pDocument->HasNode()){
      TXmlNodeIteratorC iterator = pDocument->Root()->NodeIteratorC();
      while(iterator.Next()){
         if(iterator->IsName(MO_TAG_INCLUDE)){
            // ������������
            TCharC* pName = iterator->Get(MO_PTY_FILE);
            TCharC* pFileName = REnvironment::MappingPath(pName);
            LoadFile(pFileName);
         }else if(iterator->IsName(MO_TAG_COMPONENT)){
            // �����������
            TCharC* pName = iterator->Get(MO_PTY_NAME);
            if(_pNodes->Contains(pName)){
               MO_FATAL(TC("Duplicate component define. (file=%s, name=%s)"), pFileName, pName);
               return EFalse;
            }
            _pNodes->Set(pName, *iterator);
         }
      }
   }
   return ETrue;
}

//============================================================
// <T>ж���ļ���Ϣ��</T>
//
// @return ������
//============================================================
TBool FConfigurationConsole::UnloadFiles(){
   // ж�������ĵ�����
   if(!_pDocuments->IsEmpty()){
      TListIteratorC<FXmlDocument*> iterator =  _pDocuments->IteratorC();
      while(iterator.Next()){
         FXmlDocument* pDocument = *iterator;
         MO_DELETE(pDocument);
      }
      _pDocuments->Clear();
   }
   // ��սڵ㼯��
   _pNodes->Clear();
   return ETrue;
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param pFileName �ļ�����
//============================================================
TBool FConfigurationConsole::LoadConfiguration(TCharC* pFileName){
   // ���������ļ�
   LoadFile(pFileName);
   // ����������Ϣ
   if(!_pConfigurations->IsEmpty()){
      TListIteratorC<IConfiguration*> iterator = _pConfigurations->IteratorC();
      while(iterator.Next()){
         IConfiguration* pConfiguration = *iterator;
         TCharC* pName = pConfiguration->Name();
         MO_ASSERT(pName);
         FXmlNode* pConfig = _pNodes->Find(pName);
         if(pConfig != NULL){
            MO_DEBUG(TC("Load component config. (name=%s)"), pName);
            pConfiguration->LoadConfig(pConfig);
         }
      }
   }
   // ж���ļ�
   UnloadFiles();
   return ETrue;
}

MO_NAMESPACE_END
