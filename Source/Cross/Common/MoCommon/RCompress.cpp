#include "MoCmCompress.h"
#ifdef _MO_LINUX
#include <zlib.h>
#endif // _MO_LINUX

MO_NAMESPACE_BEGIN

//============================================================
// <T>ѹ�����ݡ�</T>
//
// @param pOutput �������
// @param outputCapacity �����������
// @param pOutput ��������
// @param outputLength ���볤��
// @param pLength ������
// @return �Ƿ�ɹ�
//============================================================
TBool RCompress::Deflate(TByte* pOutput, TInt outputCapacity, TByteC* pInput, TInt inputlength, TInt* pLength){
   MO_ASSERT(pOutput);
   MO_ASSERT(pInput);
   MO_ASSERT(pLength);
#ifdef _MO_LINUX
   // ��������
   z_stream stream;
   memset(&stream, 0, sizeof(z_stream));
   stream.next_in = (Bytef*)pInput;
   stream.avail_in = inputlength;
   stream.next_out = (Bytef*)pOutput;
   stream.avail_out = outputCapacity;
   // ��ʼ��
   TInt initResult = deflateInit(&stream, Z_BEST_SPEED);
   if(initResult != Z_OK){
      return EFalse;
   }
   // ѹ������
   while((0 != stream.avail_in) && ((TInt)stream.total_out < outputCapacity)){
      TInt flushResult = deflate(&stream, Z_NO_FLUSH);
      if(flushResult != Z_OK){
         return EFalse;
      }
   }
   // ѹ������
   while(ETrue){
      TInt finishResult = deflate(&stream, Z_FINISH);
      if(Z_STREAM_END == finishResult){
         break;
      }
      if(Z_OK != finishResult){
         return EFalse;
      }
   }
   // �ͷ�����
   TInt endResult = deflateEnd(&stream);
   if(endResult != Z_OK){
      return EFalse;
   }
   *pLength = stream.total_out;
#endif
   return ETrue;
}

//============================================================
// <T>��ѹ�����ݡ�</T>
//
// @param pOutput �������
// @param outputCapacity �����������
// @param pOutput ��������
// @param outputLength ���볤��
// @param pLength ������
// @return �Ƿ�ɹ�
//============================================================
TBool RCompress::Inflate(TByte* pOutput, TInt outputCapacity, TByteC* pInput, TInt inputlength, TInt* pLength){
   MO_ASSERT(pOutput);
   MO_ASSERT(pInput);
   MO_ASSERT(pLength);
#ifdef _MO_LINUX
   // ��������
   z_stream stream;
   memset(&stream, 0, sizeof(z_stream));
   stream.next_in = (Bytef*)pInput;
   stream.avail_in = inputlength;
   stream.next_out = (Bytef*)pOutput;
   stream.avail_out = outputCapacity;
   // ��ʼ��
   TInt initResult = inflateInit(&stream);
   if(initResult != Z_OK){
      return EFalse;
   }
   // ��ѹ������
   while(((TInt)stream.total_in < inputlength) && ((TInt)stream.total_out < outputCapacity)){
      TInt flushResult = inflate(&stream, Z_NO_FLUSH);
      if(Z_STREAM_END == flushResult){
         break;
      }
      if(Z_OK != flushResult){
         return EFalse;
      }
   }
   // �ͷ�����
   TInt endResult = inflateEnd(&stream);
   if(endResult != Z_OK){
      return EFalse;
   }
   *pLength = stream.total_out;
#endif // _MO_LINUX
   return ETrue;
}

//============================================================
// <T>ѹ�����ݡ�</T>
//
// @param pOutput ѹ�������ݡ�
// @param outputLength ѹ���󳤶ȡ�
// @param pOutput ѹ��ǰ���ݡ�
// @param outputLength ѹ��ǰ���ȡ�
// @return �Ƿ�ɹ�
//============================================================
TBool RCompress::CompressRLE(TByte* pOutput, TInt outputCapacity, TByteC* pInput, TInt inputlength, TInt* pLength){
   TByte* pWrite = &pOutput[2];
   // ͳ�Ƹ����ַ����ִ���
   TInt array[256];
   memset(array, 0, sizeof(array));
   for(TInt n = 0; n < inputlength; n++){
      TInt value = pInput[n];
      array[value]++;
   }
   // �ҵ����ִ������ٵ�
   TInt a = 0;
   for(TInt n = 0; n < 256; n++){
      if(array[n] < array[a]){
         a = n;
      }
   }
   TByte k = (TByte)a;
   // �������ַ�����
   TInt length = 1;
   pOutput[length] = k;
   length++;
   // ѹ��
   for(TInt n = 0; n < inputlength; n++){
      // �����ǰ�ַ��ǿ����ַ�
      if(k == pInput[n]){
         *pWrite++ = k;
         *pWrite++ = k;
         TInt count = 1;
         for(TInt m = n + 1; m < inputlength; m++){
            if(pInput[m] == pInput[n]){
               count++;
               n = m;
               if(count == 255){
                  break;
               }
            }else{
               break;
            }
         }
         *pWrite++ = count;
      }else{
         // ��ǰ�㲻�ǿ����ַ�
         TInt count = 1;
         for(TInt m = n + 1; m < inputlength; m++){
            if(pInput[m] == pInput[n]){
               count++;
               n = m;
               if(count == 255){
                  break;
               }
            }else{
               break;
            }
         }
         // �����ǰ�ַ�������ַ���ͬ
         if(count > 1){
            *pWrite++ = k;
            *pWrite++ = pInput[n];
            *pWrite++ = count;
         }else{
            *pWrite++ = pInput[n];
         }
      }
   }
   // ���㳤��
   length = pWrite - pOutput;
   if(length + 1 > outputCapacity){
      return EFalse;
   }
   if(inputlength + 1 > length){
      pOutput[0] = 'Y';
   }else{
      pOutput[0] = 'N';
      if(0 < inputlength){
         memcpy(pOutput + 1, pInput, inputlength);
      }
      length = 1 + inputlength;
   }
   outputCapacity = length;
   *pLength = length;
   return ETrue;
}

//============================================================
// <T>ѹ�����ݡ�</T>
//
// @param pOutput ��ѹ�����ݡ�
// @param outputLength ��ѹ�󳤶ȡ�
// @param pOutput ��ѹǰ���ݡ�
// @param outputLength ��ѹǰ���ȡ�
// @return �Ƿ�ɹ�
//============================================================
TBool RCompress::UncompressRLE(TByte* pOutput, TInt outputCapacity, TByteC* pInput, TInt inputlength, TInt* pLength){
   if(0 == inputlength){
      *pLength = 0;
      return ETrue;
   }
   // �Ƿ����ѹ��
   if(pInput[0] == 'Y'){
      TByte* pWrite = pOutput;
      // ��ÿ����ַ�
      TChar k = pInput[1];
      for(TInt n = 2; n < inputlength; n++){
         if(pInput[n] == k){
            TByte value = pInput[++n];
            TInt count = pInput[++n];
            for(TInt m = 0; m < count; m++){
               *pWrite++ = value;
            }
         }else{
            *pWrite++ = pInput[n];
         }
      }
      TInt length = pWrite - pOutput;
      if(length > outputCapacity){
         return EFalse;
      }
      *pLength = length;
   }else{
      if(outputCapacity < inputlength){
         return EFalse;
      }
      for(TInt n = 1; n < inputlength; n++){
         pOutput[n -1] = pInput[n];
      }
      *pLength = inputlength;
   }
   return ETrue;
}

MO_NAMESPACE_END
