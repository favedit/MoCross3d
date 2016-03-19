//============================================================
// <T>WindowsX64ƽ̨���塣</T>
//============================================================
#if defined(_MO_WINDOWS) && defined(_MO_X64)
#ifndef __MO_CM_WINDOWS_64_H__
#define __MO_CM_WINDOWS_64_H__

//============================================================
// <T>����ͷ�ļ�</T>
//============================================================
#ifndef __MO_CM_DEFINE_H__
#include "MoCmDefine.h"
#endif // __MO_CM_DEFINE_H__

#ifndef __MO_CM_WINDOWS_H__
#include "MoCmWindows.h"
#endif // __MO_CM_WINDOWS_H__

//============================================================
// <T>��չ�������塣</T>
//============================================================
/// @define ��������
#define MO_RAISE_DEBUG() __debugbreak();
/// @define ���������˳�
#define MO_RAISE_DOWN()  {TInt* pRaise = NULL; *pRaise = 0;}
/// @define �����˳�
#define MO_RAISE_EXIT(C) exit(C)

//============================================================
// <T>�������塣</T>
//============================================================
#ifdef _MO_STACK_MIN
#define MO_FS_PACK_LENGTH       1024*64
#define MO_FS_SQL_MAX_LENGTH    1024*64
#define MO_FS_SPRINT_LENGTH     1024*64
#define MO_FS_LOGGER_LENGTH     1024*64
#define MO_FS_DUMP_LENGTH       1024*64
#define MO_FS_TRACK_LENGTH      1024*64
#else
#define MO_FS_PACK_LENGTH       1024*1024*2
#define MO_FS_SQL_MAX_LENGTH    1024*1024*2
#define MO_FS_SPRINT_LENGTH     1024*1024*2
#define MO_FS_LOGGER_LENGTH     1024*1024*2
#define MO_FS_DUMP_LENGTH       1024*1024*2
#define MO_FS_TRACK_LENGTH      1024*1024*2
#endif // _MO_STACK_MIN

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ͷ��塣</T>
//============================================================
/// @type ֻ������
typedef const __int64 TIntC;
/// @type ����
typedef __int64 TInt;
/// @type ֻ������
typedef const int TInt32C;
/// @type 32λ����
typedef int TInt32;
/// @type ֻ��64λ����
typedef const __int64 TInt64C;
/// @type 64λ����
typedef __int64 TInt64;
/// @type ֻ���޷�������
typedef const unsigned __int64 TUintC;
/// @type �޷�������
typedef unsigned __int64 TUint;
/// @type ֻ��32λ�޷�������
typedef const unsigned int TUint32C;
/// @type 32λ�޷�������
typedef unsigned int TUint32;
/// @type ֻ��64λ�޷�������
typedef const unsigned __int64 TUint64C;
/// @type 64λ�޷�������
typedef unsigned __int64 TUint64;

/// @type ֻ��32λ����
typedef const long TLongC;
/// @type 32λ����
typedef long TLong;
/// @type ֻ��32λ�޷�������
typedef const unsigned long TUlongC;
/// @type 32λ�޷�������
typedef unsigned long TUlong;
typedef unsigned long TDword;

//============================================================
// <T>��չ���Ͷ��塣</T>
//============================================================
typedef HINSTANCE TInstance;
typedef TInt      TThreadProcessId;

MO_NAMESPACE_END

#endif // __MO_CM_WINDOWS_64_H__
#endif // _MO_WINDOWS && _MO_X64
