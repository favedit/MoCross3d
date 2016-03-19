#ifdef _MO_WINDOWS
#include <winsock.h>
#else
#include <unistd.h>
#include <arpa/inet.h>
#endif
#include "MoCmNet.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ַת��Ϊ���֡�</T>
//
// @param pHost ������ַ
// @return ����
//============================================================
TInt RNetHost::NetHostToInt(TChar* pHost){
#ifdef _UNICODE
   return 0;
#else
   return inet_addr(pHost);
#endif
};

//============================================================
// <T>����ת��Ϊ������ַ��</T>
//
// @param host ������ַ
// @param pHost �����ַ���
// @param length �����ַ�������
//============================================================
TInt RNetHost::NetHostToChar(TInt host, TChar* pHost, TSize length){
   struct in_addr addr;
   addr.s_addr = host;
#ifdef _UNICODE
   return 0;
#else
   return RString::SafeCopy(pHost, length, inet_ntoa(addr));
#endif
};

MO_NAMESPACE_END
