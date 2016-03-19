#include "MoFbxParser.h"

MO_NAMESPACE_BEGIN;

/*
//============================================================
F3dsGameTrackExporter::F3dsGameTrackExporter(F3dsGameExporter* pExporter, IGameNode* piNode){
   _pExporter = pExporter;
   _piNode = piNode;
   // ��ʼ������
   _pFrameSet = MO_CREATE(FXmlNodeSet);
}

//============================================================
F3dsGameTrackExporter::~F3dsGameTrackExporter(){
   MO_DELETE(_pFrameSet);
}

//============================================================
TBool F3dsGameTrackExporter::GetControlKeys(IGameControl* piControl, IGameKeyTab& keys, IGameControlType keyType, EControlKeyType& typeCd){
   // ������귽ʽ
   if(piControl->GetLinearKeys(keys, keyType)){
      typeCd = EControlKeyType_Linear;
      return ETrue;
   }else if(piControl->GetBezierKeys(keys, keyType)){
      typeCd = EControlKeyType_Bezier;
      return ETrue;
   }else if(piControl->GetTCBKeys(keys, keyType)){
      typeCd = EControlKeyType_Tcb;
      return ETrue;
   }else if(piControl->GetFullSampledKeys(keys, 1, keyType, false)){
      typeCd = EControlKeyType_Sample;
      return ETrue;
   }
   return ETrue;
}

//============================================================
TBool F3dsGameTrackExporter::StoreData(FXmlNode* pNode, IGameKey& key, IGameControlType keyType, EControlKeyType typeCd){
   // �洢����
   switch(typeCd){
      // ���Ա���
      case EControlKeyType_Linear:{
         switch(keyType){
            case IGAME_POS:
            case IGAME_POINT3:
               R3dsExporter::StorePoint3(pNode, key.linearKey.pval);
               break;
            case IGAME_ROT:
               R3dsExporter::StoreQuat(pNode, key.linearKey.qval);
               break;
            case IGAME_SCALE:
               R3dsExporter::StoreScale(pNode, key.linearKey.sval);
               break;
            case IGAME_FLOAT:
               pNode->SetFloat(TC("value"), key.linearKey.fval);
               break;
         }
         break;
      }
      // ���������߱���
      case EControlKeyType_Bezier:{
         switch(keyType){
            case IGAME_POS:
            case IGAME_POINT3:
               //key.bezierKey.pintan;
               //key.bezierKey.pinLength;
               //key.bezierKey.pouttan;
               //key.bezierKey.poutLength;
               R3dsExporter::StorePoint3(pNode, key.bezierKey.pval);
               break;
            case IGAME_POINT4:
               //key.bezierKey.p4intan;
               //key.bezierKey.p4inLength;
               //key.bezierKey.p4outtan;
               //key.bezierKey.p4outLength;
               R3dsExporter::StorePoint4(pNode, key.bezierKey.p4val);
               break;
            case IGAME_ROT:
               R3dsExporter::StoreQuat(pNode, key.bezierKey.qval);
               break;
            case IGAME_SCALE:
               R3dsExporter::StoreScale(pNode, key.bezierKey.sval);
               break;
            case IGAME_FLOAT:
               pNode->SetFloat(TC("fval"), key.bezierKey.fval);
               pNode->SetFloat(TC("fintan"), key.bezierKey.fintan);
               pNode->SetFloat(TC("finLength"), key.bezierKey.finLength);
               pNode->SetFloat(TC("fouttan"), key.bezierKey.fouttan);
               pNode->SetFloat(TC("foutLength"), key.bezierKey.foutLength);
               break;
         }
         break;
      }
      // TCB����
      case EControlKeyType_Tcb:{
         switch(keyType){
            case IGAME_POS:
            case IGAME_POINT3:
               R3dsExporter::StorePoint3(pNode, key.tcbKey.pval);
               break;
            case IGAME_POINT4:
               R3dsExporter::StorePoint4(pNode, key.tcbKey.p4val);
               break;
            case IGAME_ROT:
               R3dsExporter::StoreAngAxis(pNode, key.tcbKey.aval);
               break;
            case IGAME_SCALE:
               R3dsExporter::StoreScale(pNode, key.tcbKey.sval);
               break;
            case IGAME_FLOAT:
               pNode->SetFloat(TC("value"), key.tcbKey.fval);
               break;
         }
         break;
      }
      // ��������
      case EControlKeyType_Sample:{
         switch(keyType){
            case IGAME_POS:
            case IGAME_POINT3:
               R3dsExporter::StorePoint3(pNode, key.sampleKey.pval);
               break;
            case IGAME_POINT4:
               R3dsExporter::StorePoint4(pNode, key.sampleKey.p4val);
               break;
            case IGAME_ROT:
               R3dsExporter::StoreQuat(pNode, key.sampleKey.qval);
               break;
            case IGAME_SCALE:
               R3dsExporter::StoreScale(pNode, key.sampleKey.sval);
               break;
            case IGAME_FLOAT:
               pNode->SetFloat(TC("value"), key.sampleKey.fval);
               break;
            case IGAME_TM:
               R3dsExporter::StoreGameMatrix(pNode, TC("Matrix"), key.sampleKey.gval);
               break;
         }
         break;
      }
   }
   return ETrue;
}

//============================================================
TBool F3dsGameTrackExporter::ConvertTrack(IGameControl* piControl, TCharC* pName, IGameControlType keyType){
   IGameKeyTab keys;
   EControlKeyType typeCd;
   if(GetControlKeys(piControl, keys, keyType, typeCd)){
      TInt count = keys.Count();
      if(count > 0){
         for(TInt n = 0; n < count; n++){
            IGameKey& key = keys[n];
            FXmlNode* pFrameNode = _pFrameSet->Find(key.t);
            if(NULL != pFrameNode){
               // �洢��Ϣ
               FXmlNode* pNode = pFrameNode->CreateNode(pName);
               StoreData(pNode, key, keyType, typeCd);
            }
         }
      }
      return ETrue;
   }
   return EFalse;
}

//============================================================
TBool F3dsGameTrackExporter::ConvertControlType(FXmlNode* pTypeNode, IGameControl* piControl, TCharC* pName, IGameControlType keyType){
   int keyCount = piControl->GetIGameKeyCount(keyType);
   pTypeNode->Set(TC("name"), pName);
   pTypeNode->Set(TC("type"), R3dsClass::GetControlType(piControl->GetControlType(keyType)));
   pTypeNode->SetInt(TC("key_count"), keyCount);
   pTypeNode->SetBool(TC("is_animated"), piControl->IsAnimated(keyType));
   pTypeNode->SetBool(TC("is_leaf"), piControl->IsLeaf(keyType));
   // �������
   /*IGameKeyTab keys;
   EControlKeyType typeCd;
   GetControlKeys(piControl, keys, keyType, typeCd);
   switch(typeCd){
      case EControlKeyType_Linear:
         pTypeNode->Set("type", "linear");
         break;
      case EControlKeyType_Bezier:
         pTypeNode->Set("type", "bezier");
         break;
      case EControlKeyType_Tcb:
         pTypeNode->Set("type", "tcb");
         break;
      case EControlKeyType_Sample:
         pTypeNode->Set("type", "sample");
         break;
      default:
         pTypeNode->Set("type", "unknown");
         break;
   }*
   return ETrue;
}

//============================================================
// <T>�洢����������</T>
//
// @param pTrackNode ������Ϣ
//============================================================
TBool F3dsGameTrackExporter::Convert(FXmlNode* pTrackNode){
   // ��ýڵ���Ϣ
   TInt nodeId = _piNode->GetNodeID();
   // ��������
   pTrackNode->SetInt(TC("bone_id"), nodeId);
   pTrackNode->Set(TC("name"), _piNode->GetName());
   GMatrix objectTm = _piNode->GetObjectTM(0);
   R3dsExporter::StoreGameMatrixSimple(pTrackNode->CreateNode(TC("ObjectMatrix")), objectTm);
   GMatrix localTm = _piNode->GetLocalTM(0);
   R3dsExporter::StoreGameMatrixSimple(pTrackNode->CreateNode(TC("LocalMatrix")), localTm);
   GMatrix worldTm = _piNode->GetWorldTM(0);
   R3dsExporter::StoreGameMatrixSimple(pTrackNode->CreateNode(TC("WorldMatrix")), worldTm);
   // ��ÿؼ�
   IGameControl* piControl = _piNode->GetIGameControl();
   if(NULL == piControl){
      // ����Ĭ�ϵ�������
      FXmlNode* pFramesNode = pTrackNode->CreateNode(TC("FrameCollection"));
      IGameScene* piScene = _pExporter->GameScene();
      Interval range = _pExporter->GetInterface()->GetAnimRange();
      TInt32 frameTick = GetTicksPerFrame();
      TInt32 frameCount = range.Duration() / frameTick;
      pFramesNode->SetInt(TC("count"), frameCount);
      for(TInt32 n = 0; n < frameCount; n++){
         TInt32 tick = frameTick * n;
         // ����һ֡��Ϣ
         FXmlNode* pFrameNode = pFramesNode->CreateNode(TC("Frame"));
         pFrameNode->SetInt(TC("time"), tick * n);
         // ���ö������
         FXmlNode* pObjectTmNode = pFrameNode->CreateNode(TC("ObjectMatrix"));
         GMatrix objectTm = _piNode->GetWorldTM(tick);
         R3dsExporter::StoreGameMatrixSimple(pObjectTmNode, objectTm);
         FXmlNode* pLocalTmNode = pFrameNode->CreateNode(TC("LocalMatrix"));
         GMatrix localTm = _piNode->GetLocalTM(tick);
         R3dsExporter::StoreGameMatrixSimple(pLocalTmNode, localTm);
         FXmlNode* pWorldTmNode = pFrameNode->CreateNode(TC("WorldMatrix"));
         GMatrix worldTm = _piNode->GetWorldTM(tick);
         R3dsExporter::StoreGameMatrixSimple(pWorldTmNode, worldTm);
      }
      return EFalse;
   }
   // ��ô洢����
   FXmlNode* pTypesNode = pTrackNode->CreateNode(TC("Types"));
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("float"), IGAME_FLOAT);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point"), IGAME_POS);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point3"), IGAME_POINT3);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("point4"), IGAME_POINT4);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("rotation"), IGAME_ROT);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("scale"), IGAME_SCALE);
   ConvertControlType(pTypesNode->CreateNode(TC("Type")), piControl, TC("matrix"), IGAME_TM);
   // ��ÿ�����Ϣ
   bool positionAnimated = piControl->IsAnimated(IGAME_POS);
   int keyPositionCount = piControl->GetIGameKeyCount(IGAME_POS);
   bool rotationAnimated = piControl->IsAnimated(IGAME_ROT);
   int keyRotationCount = piControl->GetIGameKeyCount(IGAME_ROT);
   bool scaleAnimated = piControl->IsAnimated(IGAME_SCALE);
   int keyScaleCount = piControl->GetIGameKeyCount(IGAME_SCALE);
   // ����Ƿ��ж���
   if(positionAnimated || rotationAnimated || scaleAnimated){
      // ����Ĭ�ϵ�������
      IGameKeyTab keys;
      if(piControl->GetFullSampledKeys(keys, 1, IGAME_TM, false)){
         TInt count = keys.Count();
         if(count > 0){
            FXmlNode* pFramesNode = pTrackNode->CreateNode(TC("FrameCollection"));
            pFramesNode->SetInt(TC("count"), count);
            for(TInt n=0; n<count; n++){
               // ����һ֡��Ϣ
               IGameKey& key = keys[n];
               FXmlNode* pFrameNode = pFramesNode->CreateNode(TC("Frame"));
               pFrameNode->SetInt(TC("time"), key.t);
               // ���ö������
               FXmlNode* pObjectTmNode = pFrameNode->CreateNode(TC("ObjectMatrix"));
               GMatrix objectTm = _piNode->GetObjectTM(key.t);
               R3dsExporter::StoreGameMatrixSimple(pObjectTmNode, objectTm);
               FXmlNode* pLocalTmNode = pFrameNode->CreateNode(TC("LocalMatrix"));
               GMatrix localTm = _piNode->GetLocalTM(key.t);
               R3dsExporter::StoreGameMatrixSimple(pLocalTmNode, localTm);
               FXmlNode* pWorldTmNode = pFrameNode->CreateNode(TC("WorldMatrix"));
               GMatrix worldTm = _piNode->GetWorldTM(key.t);
               R3dsExporter::StoreGameMatrixSimple(pWorldTmNode, worldTm);
            }
         }
      }
   }
   return ETrue;
}*/

MO_NAMESPACE_END;