//============================================================
// <T>Windowsƽ̨���塣</T>
//============================================================
#ifndef __MO_CM_WINDOWS_H__
#define __MO_CM_WINDOWS_H__

#ifndef _NEW_
#include <new>
#endif // _NEW_

#ifndef _TYPEINFO_
#include <typeinfo>
#endif // _TYPEINFO_

#ifndef _INC_ERRNO
#include <errno.h>
#endif // _INC_ERRNO

#ifndef _INC_MEMORY
#include <memory.h>
#endif // _INC_MEMORY

#ifndef _INC_STRING
#include <string.h>
#endif // _INC_STRING

#ifndef _INC_TIME
#include <time.h>
#endif // _INC_TIME

#ifndef _INC_IO
#include <io.h>
#endif // _INC_IO

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif // _INC_STDLIB

#ifndef _INC_STDIO
#include <stdio.h>
#endif // _INC_STDIO

#ifndef _WINDOWS_
#include <Windows.h>
#endif // _WINDOWS_

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
#define _MO_SYS_WINDOWS
/// @define ����������
#define __PRETTY_FUNCTION__ __FUNCTION__

//============================================================
// <T>���Ժ궨��</T>
//============================================================
/// @define ѹջ˳��������(�����������˳��ѹ������ջ,�ɵ����߰Ѳ�������ջ���ɲ���������)
#define MO_CDECL   __cdecl
/// @define C��������ѹջ˳��������(�����������˳��ѹ������ջ,�ɱ������߰Ѳ�������ջ��)
#define MO_STDCALL __stdcall
/// @define ѹջ˳��������(ͷ����DWORD���ͻ���ռ�����ֽڵĲ���������ECX��EDX�Ĵ���������ʣ�µĲ��������ҵ����˳��ѹ��ջ���ɱ������߰Ѳ�������ջ��)
#define MO_FASTCALL __fastcall
/// @define �������ļ�����������
#define MO_IMPORT __declspec(dllimport)
/// @define ����ǰ�ļ��ڵĺ�������
#define MO_EXPORT __declspec(dllexport)
/// @define ��ֹ�Ż������ڲ�
#define MO_NAKED __declspec(naked)
/// @define ��������ʼ���麯����
#define MO_NOVTABLE __declspec(novtable)
/// @define ����������
#define MO_EXTERN   extern
/// @define ���嵼��C����ģʽ
#define MO_EXTERN_C extern "C"

//============================================================
// <T>��׼�������塣</T>
//============================================================
#define MO_LIB_MEMORY_COPY(D, S, V, L)            memcpy_s(D, S, V, L)
#define MO_LIB_MEMORY_MOVE(D, S, V, L)            memmove_s(D, S, V, L)

#define MO_LIB_TYPE_COPY(T, D, V)                 memcpy(D, V, sizeof(T))
#define MO_LIB_TYPE_MOVE(T, D, V)                 memmove(D, V, sizeof(T))

#define MO_LIB_TYPES_COPY(T, D, S, V, L)          memcpy_s(D, sizeof(T) * (S), V, sizeof(T) * (L))
#define MO_LIB_TYPES_MOVE(T, D, S, V, L)          memmove_s(D, sizeof(T) * (S), V, sizeof(T) * (L))

//============================================================
// <T>�ַ����������塣</T>
//============================================================
#define MO_LIB_STRING_LENGTH8(S)                  strlen(S)
#define MO_LIB_STRING_LENGTH16(S)                 wcslen(S)
#define MO_LIB_STRING_LENGTH32(S)                 wcslen(S)

#define MO_LIB_STRING_COMPARE8(D, S)              strcmp(D, S)
#define MO_LIB_STRING_COMPARE16(D, S)             wcscmp(D, S)
#define MO_LIB_STRING_COMPARE32(D, S)             wcscmp(D, S)

#define MO_LIB_STRING_COMPARE_IGNORECASE8(D, S)  _stricmp(D, S)
#define MO_LIB_STRING_COMPARE_IGNORECASE16(D, S) _wcsicmp(D, S)
#define MO_LIB_STRING_COMPARE_IGNORECASE32(D, S) _wcsicmp(D, S)

#define MO_LIB_STRING_COPY8(D, S, V)              strcpy_s(D, S, V)
#define MO_LIB_STRING_COPY16(D, S, V)             wcscpy_s(D, S, V)
#define MO_LIB_STRING_COPY32(D, S, V)             wcscpy_s(D, S, V)

#define MO_LIB_STRING_FORMAT_LENGTH8(F, ...)      _vscprintf(F, __VA_ARGS__)
#define MO_LIB_STRING_FORMAT_LENGTH16(F, ...)     _vscwprintf(F, __VA_ARGS__)
#define MO_LIB_STRING_FORMAT_LENGTH32(F, ...)     _vscwprintf(F, __VA_ARGS__)

#define MO_LIB_STRING_FORMAT8(D, S, F, ...)       sprintf_s(D, S, F, __VA_ARGS__)
#define MO_LIB_STRING_FORMAT16(D, S, F, ...)      swprintf_s(D, S, F, __VA_ARGS__)
#define MO_LIB_STRING_FORMAT32(D, S, F, ...)      swprintf_s(D, S, F, __VA_ARGS__)

#define MO_LIB_STRING_NFORMAT8(D, S, F, ...)      vsprintf_s(D, S, F, __VA_ARGS__)
#define MO_LIB_STRING_NFORMAT16(D, S, F, ...)     vswprintf_s(D, S, F, __VA_ARGS__)
#define MO_LIB_STRING_NFORMAT32(D, S, F, ...)     vswprintf_s(D, S, F, __VA_ARGS__)

#define MO_LIB_STRING_PRINT8(F, ...)              printf(F, __VA_ARGS__)
#define MO_LIB_STRING_PRINT16(F, ...)             wprintf(F, __VA_ARGS__)
#define MO_LIB_STRING_PRINT32(F, ...)             wprintf(F, __VA_ARGS__)

#define MO_LIB_FILE_OPEN8(H, F, V)                fopen_s(H, F, V)
#define MO_LIB_FILE_OPEN16(H, F, V)              _wfopen_s(H, F, V)
#define MO_LIB_FILE_OPEN32(H, F, V)              _wfopen_s(H, F, V)

//------------------------------------------------------------
#ifdef _UNICODE
#define MO_LIB_STRING_LENGTH                      MO_LIB_STRING_LENGTH16
#define MO_LIB_STRING_COMPARE                     MO_LIB_STRING_COMPARE16
#define MO_LIB_STRING_COMPARE_IGNORECASE          MO_LIB_STRING_COMPARE_IGNORECASE16
#define MO_LIB_STRING_COPY                        MO_LIB_STRING_COPY16
#define MO_LIB_STRING_FORMAT_LENGTH               MO_LIB_STRING_FORMAT_LENGTH16
#define MO_LIB_STRING_FORMAT                      MO_LIB_STRING_FORMAT16
#define MO_LIB_STRING_NFORMAT                     MO_LIB_STRING_NFORMAT16
#define MO_LIB_STRING_PRINT                       MO_LIB_STRING_PRINT16
#define MO_LIB_FILE_OPEN                          MO_LIB_FILE_OPEN16
#else
#define MO_LIB_STRING_LENGTH                      MO_LIB_STRING_LENGTH8
#define MO_LIB_STRING_COMPARE                     MO_LIB_STRING_COMPARE8
#define MO_LIB_STRING_COMPARE_IGNORECASE          MO_LIB_STRING_COMPARE_IGNORECASE8
#define MO_LIB_STRING_COPY                        MO_LIB_STRING_COPY8
#define MO_LIB_STRING_FORMAT_LENGTH               MO_LIB_STRING_FORMAT_LENGTH8
#define MO_LIB_STRING_FORMAT                      MO_LIB_STRING_FORMAT8
#define MO_LIB_STRING_NFORMAT                     MO_LIB_STRING_NFORMAT8
#define MO_LIB_STRING_PRINT                       MO_LIB_STRING_PRINT8
#define MO_LIB_FILE_OPEN                          MO_LIB_FILE_OPEN8
#endif // _UNICODE

//============================================================
// <T>��չ�������塣</T>
//============================================================
/// @define �ռ�һ�������ڴ�ָ��
#define MO_ALIGNED_ALLOC(S, T)   _aligned_malloc(S, T)
/// @define �ռ�һ��ҳ�����ڴ�ָ��
#define MO_ALIGNED_PAGE_ALLOC(S) _aligned_malloc(S, 1024*4)
/// @define �ͷ�һ�������ڴ�ָ��
#define MO_ALIGNED_FREE(P)       _aligned_free(P)
/// @define ���ߴ������룩
#define MO_LIB_SLEEP(L)         ::Sleep((TUint32)L)
/// @define ���ߴ���΢�
#define MO_LIB_MICRO_SLEEP(L)   ::Sleep(MO_LIB_MAX((TUint32)(L/1000), 1))
/// @define ���д���
#define MO_LIB_IDLE()           ::SwitchToThread()

//============================================================
// <T>��չ���塣</T>
//============================================================
#define MO_FILE_SPLITTER       \
#define MO_FILE_SPLITTER_CHAR '\\'
#define MO_FILE_SPLITTER_STR  "\\"

#endif // __MO_CM_WINDOWS_H__
