#ifdef _MO_WINDOWS
#include <time.h>
#else
#include <sys/time.h>
#endif
#include <sys/timeb.h>
#include <stdlib.h>
#include <time.h>
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
TCharC* RDateTime::DefaultFormat = TC("%Y%m%d %H%M%S");
TCharC* RDateTime::DefaultFormatT = TC("%Y%m%d%H%M%S");

//============================================================
// <T>��õ�ǰʱ�����</T>
//
// @return ʱ���
//============================================================
TDateTime RDateTime::Current(){
#if defined(_MO_WINDOWS) || defined(_MO_LINUX) || defined(_MO_ANDROID)
   // ���ʱ��
   struct timeb time;
   ftime(&time);
   // �ϳ�ʱ��
   TDateTime second = time.time;
   TDateTime millisecond = MO_TP_DATE_MILLISECONDS_PER_SECONDE * time.millitm;
   return (MO_TP_DATE_MICROSECONDS_PER_SECONDE * second) + millisecond;
#endif // _MO_WINDOWS | _MO_LINUX
#ifdef _MO_FLASCC
   struct timeval time;
   gettimeofday(&time, NULL);
   TDateTime result = (TDateTime)time.tv_sec * 1000000LL + (TDateTime)time.tv_usec;
   return result;
#endif // _MO_FLASCC
}

//============================================================
// <T>��ʱ�䡣</T>
//
// @param pValue �ַ���
// @return ʱ��
//============================================================
TDateTime RDateTime::Parse(TCharC* pValue){
   return Parse(pValue, DefaultFormat);
}

//============================================================
// <T>���ݸ�ʽ���ĸ�ʽ�����ַ���ʱ�䡣</T>
// <P>%Y 4λ��   (1900-2999)</P>
// <P>%y 2λ��   (00-99)</P>
// <P>%m 2λ�·� (01-12)</P>
// <P>%d 2λ��   (00-31)</P>
// <P>%H 2λʱ   (00-24)</P>
// <P>%M 2λ��   (00-60)</P>
// <P>%S 2λ��   (00-60)</P>
// <P>%s 3λ���� (00-999)</P>
//
// @param pValue �ַ���ʱ��
// @param pFormat ��ʽ
// @return ʱ���
//============================================================
TDateTime RDateTime::Parse(TCharC* pValue, TCharC* pFormat){
   MO_ASSERT(pValue);
   MO_ASSERT(pFormat);
   // ��ʼ��ʱ��ṹ
   struct tm data;
   memset(&data, 0, sizeof(tm));
   // �ֽ�ʱ������
   TChar buffer[5];
   TCharC* pValueReader = pValue;
   TCharC* pFormatReader = pFormat;
   TInt length = RString::Length(pFormat);
   MO_ASSERT(length > 0);
   TInt millisecond = 0;
   while(--length >= 0){
      if(*pFormatReader == '%'){
         pFormatReader++;
         TChar formatCd = *pFormatReader;
         switch(formatCd){
            case 'Y':{
               // ��ʽ��Ϊ4λ��
               buffer[0] = pValueReader[0];
               buffer[1] = pValueReader[1];
               buffer[2] = pValueReader[2];
               buffer[3] = pValueReader[3];
               buffer[4] = '\0';
               TInt year = RInt::Parse(buffer);
               data.tm_year = year - 1900;
               pValueReader = pValueReader + 4;
               break;
            }
            case 'y':{
               // ��ʽΪ2λ��
               buffer[0] = pValueReader[0];
               buffer[1] = pValueReader[1];
               buffer[2] = '\0';
               TInt year = RInt::Parse(buffer);
               if(year >= 80){
                  data.tm_year = year;
               }else{
                  data.tm_year = year + 100;
               }
               pValueReader = pValueReader + 2;
               break;
            }
            case 'm':{
               // ��ʽΪ��
               buffer[0] = pValueReader[0];
               buffer[1] = pValueReader[1];
               buffer[2] = '\0';
               TInt month = RInt::Parse(buffer);
               MO_ASSERT_RANGE(month, 0, 13);
               data.tm_mon = month - 1;
               pValueReader = pValueReader + 2;
               break;
            }
            case 'd':{
               // ��ʽΪ�죨�գ�
               buffer[0] = pValueReader[0];
               buffer[1] = pValueReader[1];
               buffer[2] = '\0';
               TInt day = RInt::Parse(buffer);
               MO_ASSERT_RANGE(day, 0, 32);
               data.tm_mday = day;
               pValueReader = pValueReader + 2;
               break;
            }
            case 'H':{
               // ��ʽΪ24Сʱ��Сʱ
               buffer[0] = pValueReader[0];
               buffer[1] = pValueReader[1];
               buffer[2] = '\0';
               TInt hour = RInt::Parse(buffer);
               MO_ASSERT_RANGE(hour, 0, 24);
               data.tm_hour = hour;
               pValueReader = pValueReader + 2;
               break;
            }
            case 'M':{
               // ��ʽΪ����
               buffer[0] = pValueReader[0];
               buffer[1] = pValueReader[1];
               buffer[2] = '\0';
               TInt minute = RInt::Parse(buffer);
               MO_ASSERT_RANGE(minute, 0, 60);
               data.tm_min = minute;
               pValueReader = pValueReader + 2;
               break;
            }
            case 'S':{
               // ��ʽΪ��
               buffer[0] = pValueReader[0];
               buffer[1] = pValueReader[1];
               buffer[2] = '\0';
               TInt second = RInt::Parse(buffer);
               MO_ASSERT_RANGE(second, 0, 60);
               data.tm_sec = second;
               pValueReader = pValueReader + 2;
               break;
            }
            case 's':{
               // ��ʽΪ����
               buffer[0] = pValueReader[0];
               buffer[1] = pValueReader[1];
               buffer[2] = pValueReader[2];
               buffer[3] = '\0';
               millisecond = RInt::Parse(buffer);
               pValueReader = pValueReader + 3;
               break;
            }
            default:{
               MO_STATIC_FATAL(TC("Unknown date code. (code=%d)"), formatCd);
            }
         }
         length--;
      }else{
         pValueReader++;
      }
      pFormatReader++;
   }
   // �ϳ�ʱ��
   TDateTime result = mktime(&data);
   return (result * 1000000) + (millisecond * 1000);
}

//============================================================
TDateTime RDateTime::ParseNvl(TCharC* pValue){
   if(NULL == pValue){
      return 0;
   }
   return Parse(pValue);
}

//============================================================
TDateTime RDateTime::ParseNvl(TCharC* pValue, TCharC* pFormat){
   if(NULL == pValue){
      return 0;
   }
   return Parse(pValue, pFormat);
}

//============================================================
// <T>��ʽ��ʱ��Ϊָ����ʽ�ַ�����</T>
//
// @param pBuffer ��ʽ�����ʱ��
// @param length  pBuffer����
// @param pFormat ��ʽ
// @param dateTime ʱ���
// @return ��ʽ�����ʱ��
//============================================================
TCharC* RDateTime::ToString(TChar* pBuffer, TSize length, TDateTime dateTime, TCharC* pFormat){
   // ���ʱ��
   struct tm data;
   time_t time = dateTime / 1000000;
#ifdef _MO_SYS_WINDOWS
   MO_ASSERT_ERRNO(localtime_s(&data, &time));
#endif // _MO_SYS_WINDOWS
#ifdef _MO_SYS_LINUX
   localtime_r(&time, &data);
#endif // _MO_SYS_LINUX
   // ��ʽ������
   TChar buffer[8];
   TSize valuePosition = 0;
   TSize formatPosition = 0;
   TSize formatLength = RString::Length(pFormat);
   TChar* pWrite = pBuffer;
   while((formatPosition < formatLength) && (valuePosition < length)){
      if(*pFormat == '%'){       
         pFormat++;
         switch(*pFormat++){
            case 'Y':{
               // ��ʽ��Ϊ4λ�꣨�磺2005��
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt year = data.tm_year + 1900;
                  RInt::ToString(year, buffer, 5);
                  if(year < 10){
                     *pWrite++ = '0';
                     *pWrite++ = '0';
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else if(year < 100){
                     *pWrite++ = '0';
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }else if(year < 1000){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                     *pWrite++ = buffer[2];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                     *pWrite++ = buffer[2];
                     *pWrite++ = buffer[3];
                  }
                  formatPosition++;
                  valuePosition = valuePosition + 4;
               }
               break;
            }
            case 'y':{
               // ��ʽ��Ϊ2λ�꣨��05��
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt year = data.tm_year % 100;
                  RInt::ToString(year, buffer, 3);
                  if(year < 10){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }
               }
               formatPosition++;
               valuePosition = valuePosition + 2;
               break;
            }
            case 'm':{
               // ��ʽ��Ϊ��
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt month = data.tm_mon + 1;
                  RInt::ToString(month, buffer, 3);
                  if(month < 10){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }
               }
               formatPosition++;
               valuePosition = valuePosition + 2;
               break;
            }
            case 'd':{
               // ��ʽ��Ϊ�죨�գ�
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt day = data.tm_mday;
                  RInt::ToString(day, buffer, 3);
                  if(day < 10){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }
               }
               formatPosition++;
               valuePosition = valuePosition + 2;
               break;
            }
            case 'H':{
               // ��ʽ��Ϊ24Сʱ��Сʱ
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt hour = data.tm_hour;
                  RInt::ToString(hour, buffer, 3);
                  if(hour < 10){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }
               }
               formatPosition++;
               valuePosition = valuePosition + 2;
               break;
            }
            case 'h':{
               // ��ʽ��Ϊ12Сʱ��Сʱ
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt hour = data.tm_hour % 12;
                  RInt::ToString(hour, buffer, 3);
                  if(hour < 10){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }
               }
               formatPosition++;
               valuePosition = valuePosition + 2;
               break;
            }
            case 'M':{
               // ��ʽ��Ϊ��
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt minute = data.tm_min;
                  RInt::ToString(minute, buffer, 3);
                  if(minute < 10){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }
               }
               formatPosition++;
               valuePosition = valuePosition + 2;
               break;
            }
            case 'S':{
               // ��ʽ��Ϊ��
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt second = data.tm_sec;
                  RInt::ToString(second, buffer, 3);
                  if(second < 10){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }
               }
               formatPosition++;
               valuePosition = valuePosition + 2;
               break;
            }
            case 's':{
               // ��ʽ��Ϊ����
               if(dateTime == 0){
                  *pWrite++ = '0';
                  *pWrite++ = '0';
                  *pWrite++ = '0';
               }else{
                  TInt millisecond = (dateTime % 1000000) / 1000;
                  RInt::ToString(millisecond, buffer, 4);
                  if(millisecond < 10){
                     *pWrite++ = '0';
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                  }else if(millisecond < 100){
                     *pWrite++ = '0';
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                  }else{
                     *pWrite++ = buffer[0];
                     *pWrite++ = buffer[1];
                     *pWrite++ = buffer[2];
                  }
               }
               formatPosition++;
               valuePosition = valuePosition + 3;
               break;
            }
            default:{
               MO_STATIC_FATAL(TC("Unknown date format. (format=%s)"), pFormat);
            }
         }
      }else{
         *pWrite++ = *pFormat++;
         valuePosition++;
      }
      formatPosition++;
   }
   *pWrite = '\0';
   return pBuffer;
}

//============================================================
TUint32 RDateTime::To32(TDateTime dateTime){
   TUint64 to = dateTime / 1000000L;
   TUint32 tot = (TUint32)to;
   return tot;
}

//============================================================
TUint64 RDateTime::To64(TUint32 dateTime){
   TUint64 to = dateTime;
   to *= 1000000L;
   return to;
}

//============================================================
void RDateTime::Split(TDateTime current, SDateTime& dateTime){
   struct tm data;
   time_t time = current / 1000000;
#ifdef _MO_SYS_WINDOWS
   MO_ASSERT_ERRNO(localtime_s(&data, &time));
#endif // _MO_SYS_WINDOWS
#ifdef _MO_SYS_LINUX
   localtime_r(&time, &data);
#endif // _MO_SYS_LINUX
   dateTime.second = data.tm_sec;
   dateTime.minute = data.tm_min;
   dateTime.hour = data.tm_hour;
   dateTime.day = data.tm_mday;
   dateTime.month = data.tm_mon + 1;
   dateTime.year = data.tm_year + 1900;
   dateTime.dayWeek = data.tm_wday;
   dateTime.dayYear = data.tm_yday;
}

//============================================================
TDateTime RDateTime::Mktime(SDateTime& dateTime){
   struct tm data;
   data.tm_isdst = 0;
   data.tm_sec = dateTime.second;
   data.tm_min = dateTime.minute;
   data.tm_hour = dateTime.hour;
   data.tm_mday = dateTime.day;
   data.tm_mon = dateTime.month - 1;
   data.tm_year = dateTime.year - 1900;
   data.tm_wday = dateTime.dayWeek;
   data.tm_yday = dateTime.dayYear;
   return mktime(&data);
}

//============================================================
TBool RDateTime::IsTheNextDay( TDateTime dayEarly, TDateTime dayLate ){
   SDateTime last_day;
   SDateTime today;
   Split(dayEarly, last_day);
   Split(dayLate, today);
   last_day.hour = 0;
   last_day.minute = 0;
   last_day.second = 0;
   today.hour = 0;
   today.minute = 0;
   today.second = 0;
   dayEarly = Mktime(last_day);
   dayLate = Mktime(today);
   return ((dayLate - dayEarly) >= 86398 && (dayLate - dayEarly) <= 86402 ); // �ӵ��ݲ�
}

//============================================================ 
// <T>��ȡ��ǰʱ���ڱ������ǵڼ��ܡ�</T> 
// 
// @param dateTime ʱ�� 
// @return �ڼ��� 
//============================================================
TInt RDateTime::GetNumberOfWeek(SDateTime& dateTime){
   SDateTime firstDate;
   memcpy(&firstDate, &dateTime, sizeof(dateTime));
   firstDate.month = 1;
   firstDate.day = 1;
   RDateTime::Split(RDateTime::Mktime(firstDate), firstDate);
   TInt offset = firstDate.dayWeek;
   if(offset == 0){
      offset = 7;
   }
   TInt curDay = dateTime.dayYear;
   curDay = curDay - (7 - offset + 1);
   if(curDay <= 0){
      return 1;
   }else{
      if(curDay % 7 == 0){
         return curDay / 7 + 1;
      }else{
         return curDay / 7 + 2;
      }
   }
   return 0;
}

MO_NAMESPACE_END
