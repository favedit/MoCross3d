#include "MoCmFile.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ļ���Ϣ��</T>
//============================================================
TFileInfo::TFileInfo(){
}

//============================================================
// <T>�����ļ���Ϣ��</T>
//
// @param pFileName �ļ�����
//============================================================
TFileInfo::TFileInfo(TCharC* pFileName){
   _fileName = pFileName;
   Parse(pFileName);
}

//============================================================
// <T>�����ļ���Ϣ��</T>
//============================================================
TFileInfo::~TFileInfo(){
}

//============================================================
// <T>����ļ���С��</T>
//
// @return �ļ���С
//============================================================
TInt TFileInfo::Size(){
   return RFile::FileSize(_fileName);
}

//============================================================
// <T>����ļ���С��</T>
//
// @return �ļ���С
//============================================================
TInt64 TFileInfo::LargeSize(){
   return (TUint64)RFile::FileSize(_fileName);
}

//============================================================
// <T>����ļ��������ڡ�</T>
//
// @return ��������
//============================================================
TDateTime TFileInfo::CreateDate(){
   return 0;
}

//============================================================
// <T>����ļ��������ڡ�</T>
//
// @return ��������
//============================================================
TDateTime TFileInfo::UpdateDate(){
   return 0;
}

//============================================================
// <T>�ж��Ƿ�Ϊ�ļ���</T>
//
// @return �Ƿ�Ϊ�ļ�
//============================================================
TBool TFileInfo::IsFile(){
   return RFile::ExistFile(_fileName);
}

//============================================================
// <T>�ж��Ƿ�ΪĿ¼��</T>
//
// @return �Ƿ�ΪĿ¼
//============================================================
TBool TFileInfo::IsDirectory(){
   return RFile::ExistPath(_fileName.MemoryC());
}

//============================================================
// <T>�����ļ���Ϣ��</T>
//
// @param pFileName �ļ�����
// @return ������
//============================================================
TResult TFileInfo::Parse(TCharC* pFileName){
   MO_CHECK(pFileName, return ENull);
   // �滻�ַ�
#ifdef _MO_WINDOWS
   _fileName.Replace('\\', '/');
#endif // _MO_WINDOWS
   // ȡ�̷�
   TInt driverEnd = _fileName.IndexOf(':');
   if(ENotFound != driverEnd){
      _driver = _fileName.LeftStrC(driverEnd);
   }
   // ȡ·�����ļ���
	TFsName oneDirs[MoDirMaxLayer];
	TInt count = 0;
	TInt lastLayerEnd = _fileName.IndexOf('/');
	if(ENotFound != lastLayerEnd){
		// ���·����/���ڿ�ʼ��û���̷���
		if(0 != lastLayerEnd && ENotFound == driverEnd){
			oneDirs[count] = _fileName.LeftStrC(lastLayerEnd);
			count++;
		}
		for(TInt n = 0 ; n < MoDirMaxLayer; n++){
			TInt curLayerEnd = _fileName.IndexOf('/', lastLayerEnd + 1);
			if(ENotFound != curLayerEnd){
				oneDirs[count] = _fileName.SubStrC(lastLayerEnd + 1, curLayerEnd);
				if(oneDirs[count].Equals(TC(".."))){
					--count;
				}else{
					++count;
				}
				lastLayerEnd = curLayerEnd;
			}else{
				break;
			}	
		}
		_name = _fileName.SubStrC(lastLayerEnd + 1, _fileName.Length());
		MO_ASSERT(count >=0 && count < MoDirMaxLayer);
		_path.Clear();
		for(TInt n = 0; n < count; n++){
			_path.Append('/');
			_path.Append((TCharC*)oneDirs[n]);
		}
		_path.Append('/');
	}else{
		_path.Assign(TC("."));
		_name = _fileName;
	}
   // ȡ��չ��
   TInt extensionStart = _name.LastIndexOf('.');
   if(extensionStart != ENotFound){
      _code = _name.LeftStrC(extensionStart);
      _extension = _name.RightStrC(_name.Length() - extensionStart - 1);
   }else{
      _code = _name;
   }
   // ���ȫ����
	_fullName.Clear();
	if(!_driver.IsEmpty()){
		_fullName.Assign(_driver);
		_fullName.Append(':');
	}
	_fullName.Append(_path);
	_fullName.Append(_name);
   return ESuccess;
}

MO_NAMESPACE_END
