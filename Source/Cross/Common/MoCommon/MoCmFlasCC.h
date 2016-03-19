//============================================================
// <T>FlasCCƽ̨���塣</T>
//============================================================
#ifdef _MO_FLASCC
#ifndef __MO_CM_FLASCC_H__
#define __MO_CM_FLASCC_H__

//============================================================
// <T>����ͷ�ļ�</T>
//============================================================
#ifndef _NEW_
#include <new>
#endif // _NEW_

#ifndef _TYPEINFO_
#include <typeinfo>
#endif // _TYPEINFO_

#ifndef _SYSCALL_H
#ifndef __CYGWIN__
#include <sys/syscall.h>
#endif // __CYGWIN__
#endif // _SYSCALL_H

#ifndef _SYS_SOCKET_H
#include <sys/socket.h>
#endif // _SYS_SOCKET_H

#ifndef _ARPA_INET_H
#include <arpa/inet.h>
#endif // _ARPA_INET_H

#ifndef _NETINET_IN_H_
#include <netinet/in.h>
#endif // _NETINET_IN_H_

#ifndef __MO_CM_DEFINE_H__
#include "MoCmDefine.h"
#endif // __MO_CM_DEFINE_H__

#ifndef __MO_CM_LINUX_H__
#include "MoCmLinux.h"
#endif // __MO_CM_LINUX_H__

//============================================================
// <T>�������塣</T>
//============================================================
#define MO_FS_PACK_LENGTH       1024*256
#define MO_FS_SQL_MAX_LENGTH    1024*256
#define MO_FS_SPRINT_LENGTH     1024*256
#define MO_FS_LOGGER_LENGTH     1024*256
#define MO_FS_DUMP_LENGTH       1024*256
#define MO_FS_TRACK_LENGTH      1024*256

//============================================================
// <T>��չ�������塣</T>
//============================================================
/// @define �ռ�һ�������ڴ�ָ��
#define MO_ALIGNED_ALLOC(S, T)   malloc(S)
/// @define ��������
#define MO_RAISE_DEBUG()

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������Ͷ��塣</T>
//============================================================
/// @type ֻ������
typedef const int TIntC;
/// @type ����
typedef int TInt;
/// @type ֻ��32λ����
typedef const int TInt32C;
/// @type 32λ����
typedef int TInt32;
/// @type ֻ��64λ����
typedef const long long TInt64C;
/// @type 64λ����
typedef long long TInt64;
/// @type 128λ����
typedef struct{
   long long lower;
   long long high;
} TInt128;
/// @type ֻ���޷�������
typedef const unsigned int TUintC;
/// @type �޷�������
typedef unsigned int TUint;
/// @type ֻ��32λ�޷�������
typedef const unsigned int TUint32C;
/// @type 32λ�޷�������
typedef unsigned int TUint32;
/// @type ֻ��64λ�޷�������
typedef const unsigned long long TUint64C;
/// @type 64λ�޷�������
typedef unsigned long long TUint64;
/// @type 128λ�޷�������
// typedef long double TUint128;

//============================================================
// <T>��չ���Ͷ��塣</T>
//============================================================
typedef TInt      TInstance;
typedef pid_t     TThreadProcessId;

MO_NAMESPACE_END

#endif // __MO_CM_FLASCC_H__
#endif // _MO_FLASCC
