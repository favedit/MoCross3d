//============================================================
// <T>LinuxX64ƽ̨���塣</T>
//============================================================
#if defined(_MO_LINUX) && defined(_MO_X64)
#ifndef __MO_CM_LINUX_64_H__
#define __MO_CM_LINUX_64_H__

//============================================================
// <T>����ͷ�ļ�</T>
//============================================================
#ifndef _NEW_
#include <new>
#endif // _NEW_

#ifndef _TYPEINFO_
#include <typeinfo>
#endif // _TYPEINFO_

#ifndef _MALLOC_H
#include <malloc.h>
#endif // _MALLOC_H

#ifndef _INC_MEMORY
#include <memory.h>
#endif // _INC_MEMORY

#ifndef _LIBICONV_H
#include <iconv.h>
#endif // _LIBICONV_H

#ifndef _SYSCALL_H
#ifndef __CYGWIN__
#include <sys/syscall.h>
#endif // __CYGWIN__
#endif // _SYSCALL_H

#ifndef _SYS_EPOLL_H
#ifndef __CYGWIN__
#include <sys/epoll.h>
#endif // __CYGWIN__
#endif // _SYS_EPOLL_H

#ifndef _SYS_SOCKET_H
#include <sys/socket.h>
#endif // _SYS_SOCKET_H

#ifndef _ARPA_INET_H
#include <arpa/inet.h>
#endif // _ARPA_INET_H

#ifndef __MO_CM_DEFINE_H__
#include "MoCmDefine.h"
#endif // __MO_CM_DEFINE_H__

#ifndef __MO_CM_LINUX_H__
#include "MoCmLinux.h"
#endif // __MO_CM_LINUX_H__

//============================================================
// <T>�������塣</T>
//============================================================
#ifdef __CYGWIN__
#define MO_FS_PACK_LENGTH       1024*256
#define MO_FS_SQL_MAX_LENGTH    1024*256
#define MO_FS_SPRINT_LENGTH     1024*256
#define MO_FS_LOGGER_LENGTH     1024*256
#define MO_FS_DUMP_LENGTH       1024*256
#define MO_FS_TRACK_LENGTH      1024*256
#else
#define MO_FS_PACK_LENGTH       1024*1024*4
#define MO_FS_SQL_MAX_LENGTH    1024*1024*4
#define MO_FS_SPRINT_LENGTH     1024*1024*4
#define MO_FS_LOGGER_LENGTH     1024*1024*4
#define MO_FS_DUMP_LENGTH       1024*1024*4
#define MO_FS_TRACK_LENGTH      1024*1024*4
#endif // __CYGWIN__

//============================================================
// <T>��չ�������塣</T>
//============================================================
/// @define ��������
#define MO_RAISE_DEBUG()       __asm__ __volatile__ ("int $3");
/// @define ���������˳�
#define MO_RAISE_DOWN()        {TInt* pRaise = NULL; *pRaise = 0;}
/// @define �����˳�
#define MO_RAISE_EXIT(C)       exit(C)
/// @define �ռ�һ�������ڴ�ָ��
#define MO_ALIGNED_ALLOC(S, T) memalign(T, S)

MO_NAMESPACE_BEGIN
      
//============================================================
// <T>�������Ͷ��塣</T>
//============================================================
/// @type ֻ������
typedef const long int TIntC;
/// @type ����
typedef long int TInt;
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
typedef const unsigned long int TUintC;
/// @type �޷�������
typedef unsigned long int TUint;
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

#endif // __MO_CM_LINUX_64_H__
#endif // _MO_LINUX && _MO_X64
