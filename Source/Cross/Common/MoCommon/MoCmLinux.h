//============================================================
// <T>LinuxX86ƽ̨���塣</T>
//============================================================
#ifndef __MO_CM_LINUX_H__
#define __MO_CM_LINUX_H__

#ifndef _STDARG_H
#include <stdarg.h>
#endif // _STDARG_H

#ifndef _CTYPE_H_
#include <ctype.h>
#endif // _CTYPE_H_

#ifndef _FCNTL_H
#include <fcntl.h>
#endif // _FCNTL_H

#ifndef _UNISTD_H_
#include <unistd.h>
#endif // _UNISTD_H_

#ifndef _WCHAR_H
#include <wchar.h>
#endif // _WCHAR_H

#ifndef _INC_ERRNO
#include <errno.h>
#endif // _INC_ERRNO

#ifndef _INC_STRING
#include <string.h>
#endif // _INC_STRING

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif // _INC_STDLIB

#ifndef _INC_STDIO
#include <stdio.h>
#endif // _INC_STDIO

#ifndef _PTHREAD_H_
#include <pthread.h>
#endif // _PTHREAD_H_

//============================================================
// <T>����ͷ�ļ�</T>
//============================================================
#ifndef __MO_CM_DEFINE_H__
#include "MoCmDefine.h"
#endif // __MO_CM_DEFINE_H__

//============================================================
// <T>����궨��</T>
//============================================================
/// @define ���Ķ���
#define _MO_SYS_LINUX

//============================================================
// <T>���Ժ궨��</T>
//============================================================
/// @define ѹջ˳��������(�����������˳��ѹ������ջ,�ɵ����߰Ѳ�������ջ���ɲ���������)
#define MO_CDECL
/// @define C��������ѹջ˳��������(�����������˳��ѹ������ջ,�ɱ������߰Ѳ�������ջ��)
#define MO_STDCALL
/// @define ѹջ˳��������(ͷ����DWORD���ͻ���ռ�����ֽڵĲ���������ECX��EDX�Ĵ���������ʣ�µĲ��������ҵ����˳��ѹ��ջ���ɱ������߰Ѳ�������ջ��)
#define MO_FASTCALL
/// @define �������ļ�����������
#define MO_IMPORT
/// @define ����ǰ�ļ��ڵĺ�������
#define MO_EXPORT
/// @define ��ֹ�Ż������ڲ�
#define MO_NAKED
/// @define ��������ʼ���麯����
#define MO_NOVTABLE
/// @define ����������
#define MO_EXTERN   extern
/// @define ���嵼��C����ģʽ
#define MO_EXTERN_C extern "C"

//============================================================
// <T>��׼�������塣</T>
//============================================================
#define MO_LIB_MEMORY_COPY(D, S, V, L)           memcpy(D, V, L)
#define MO_LIB_MEMORY_MOVE(D, S, V, L)           memmove(D, V, L)

#define MO_LIB_TYPE_COPY(T, D, V)                memcpy(D, V, sizeof(T))
#define MO_LIB_TYPE_MOVE(T, D, V)                memmove(D, V, sizeof(T))

#define MO_LIB_TYPES_COPY(T, D, S, V, L)         memcpy(D, V, sizeof(T) * (L))
#define MO_LIB_TYPES_MOVE(T, D, S, V, L)         memmove(D, V, sizeof(T) * (L))

//============================================================
// <T>�ַ����������塣</T>
//============================================================
#define MO_LIB_STRING_LENGTH8(S)                 strlen(S)
#define MO_LIB_STRING_LENGTH16(S)                wcslen(S)
#define MO_LIB_STRING_LENGTH32(S)                wcslen(S)

#define MO_LIB_STRING_COPY8(D, S, V)             strcpy(D, V)
#define MO_LIB_STRING_COPY16(D, S, V)            wcscpy(D, V)
#define MO_LIB_STRING_COPY32(D, S, V)            wcscpy(D, V)

#define MO_LIB_STRING_COMPARE8(D, S)             strcmp(D, S)
#define MO_LIB_STRING_COMPARE16(D, S)            wcscmp(D, S)
#define MO_LIB_STRING_COMPARE32(D, S)            wcscmp(D, S)

#define MO_LIB_STRING_COMPARE_IGNORECASE8(D, S)  strcasecmp(D, S)
#ifdef _MO_ANDROID
#define MO_LIB_STRING_COMPARE_IGNORECASE16(D, S) wcscmp(D, S)
#define MO_LIB_STRING_COMPARE_IGNORECASE32(D, S) wcscmp(D, S)
#else
#define MO_LIB_STRING_COMPARE_IGNORECASE16(D, S) wcscasecmp(D, S)
#define MO_LIB_STRING_COMPARE_IGNORECASE32(D, S) wcscasecmp(D, S)
#endif // _MO_ANDROID

#define MO_LIB_STRING_FORMAT_LENGTH8(F, ...)    _vscprintf(F, __VA_ARGS__)
#define MO_LIB_STRING_FORMAT_LENGTH16(F, ...)   _vscwprintf(F, __VA_ARGS__)
#define MO_LIB_STRING_FORMAT_LENGTH32(F, ...)   _vscwprintf(F, __VA_ARGS__)

#define MO_LIB_STRING_FORMAT8(D, S, F, ...)      sprintf(D, F, __VA_ARGS__)
#define MO_LIB_STRING_FORMAT16(D, S, F, ...)     swprintf(D, F, __VA_ARGS__)
#define MO_LIB_STRING_FORMAT32(D, S, F, ...)     swprintf(D, F, __VA_ARGS__)

#define MO_LIB_STRING_NFORMAT8(D, S, F, ...)     vsnprintf(D, S, F, __VA_ARGS__)
#define MO_LIB_STRING_NFORMAT16(D, S, F, ...)    vswprintf(D, S, F, __VA_ARGS__)
#define MO_LIB_STRING_NFORMAT32(D, S, F, ...)    vswprintf(D, S, F, __VA_ARGS__)

#define MO_LIB_STRING_PRINT8(D, S, F, ...)       printf(F, __VA_ARGS__)
#define MO_LIB_STRING_PRINT16(D, S, F, ...)      wprintf(F, __VA_ARGS__)
#define MO_LIB_STRING_PRINT32(D, S, F, ...)      wprintf(F, __VA_ARGS__)

//------------------------------------------------------------
#ifdef _UNICODE
#define MO_LIB_STRING_LENGTH                     MO_LIB_STRING_LENGTH32
#define MO_LIB_STRING_COMPARE                    MO_LIB_STRING_COMPARE32
#define MO_LIB_STRING_COMPARE_IGNORECASE         MO_LIB_STRING_COMPARE_IGNORECASE32
#define MO_LIB_STRING_COPY                       MO_LIB_STRING_COPY32
#define MO_LIB_STRING_FORMAT_LENGTH              MO_LIB_STRING_FORMAT_LENGTH16
#define MO_LIB_STRING_FORMAT                     MO_LIB_STRING_FORMAT32
#define MO_LIB_STRING_NFORMAT                    MO_LIB_STRING_NFORMAT32
#define MO_LIB_STRING_PRINT                      MO_LIB_STRING_PRINT32
#else
#define MO_LIB_STRING_LENGTH                     MO_LIB_STRING_LENGTH8
#define MO_LIB_STRING_COMPARE                    MO_LIB_STRING_COMPARE8
#define MO_LIB_STRING_COMPARE_IGNORECASE         MO_LIB_STRING_COMPARE_IGNORECASE8
#define MO_LIB_STRING_COPY                       MO_LIB_STRING_COPY8
#define MO_LIB_STRING_FORMAT_LENGTH              MO_LIB_STRING_FORMAT_LENGTH8
#define MO_LIB_STRING_FORMAT                     MO_LIB_STRING_FORMAT8
#define MO_LIB_STRING_NFORMAT                    MO_LIB_STRING_NFORMAT8
#define MO_LIB_STRING_PRINT                      MO_LIB_STRING_PRINT8
#endif // _UNICODE

//============================================================
// <T>��չ�������塣</T>
//============================================================
/// @define �ռ�һ��ҳ�����ڴ�ָ��
#define MO_ALIGNED_PAGE_ALLOC(S) valloc(S)
/// @define �ͷ�һ�������ڴ�ָ��
#define MO_ALIGNED_FREE(P)       free(P)
/// @define ���ߴ������룩
#define MO_LIB_SLEEP(L)          usleep(1000*L)
/// @define ���ߴ���΢�
#define MO_LIB_MICRO_SLEEP(L)    usleep(L)
/// @define ���д���
#define MO_LIB_IDLE()            sched_yield()

//============================================================
// <T>��չ���塣</T>
//============================================================
#define MO_FILE_SPLITTER       /
#define MO_FILE_SPLITTER_CHAR '/;'
#define MO_FILE_SPLITTER_STR  "/"

#endif // __MO_CM_LINUX_H__
