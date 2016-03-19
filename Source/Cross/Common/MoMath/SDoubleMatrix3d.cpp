#include "MoMtMatrix.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>׷��һ�������������ݡ�</T>
//
// @param pData ����
// @return ������
//============================================================
TResult SDoubleMatrix3d::AppendData(TDoubleC* pData){
   // ������
   MO_CHECK(pData, return ENull);
   // �������
   TDouble v00 = (data[0][0] * pData[0]) + (data[0][1] * pData[4]) + (data[0][2] * pData[ 8]) + (data[0][3] * pData[12]);
   TDouble v01 = (data[0][0] * pData[1]) + (data[0][1] * pData[5]) + (data[0][2] * pData[ 9]) + (data[0][3] * pData[13]);
   TDouble v02 = (data[0][0] * pData[2]) + (data[0][1] * pData[6]) + (data[0][2] * pData[10]) + (data[0][3] * pData[14]);
   TDouble v03 = (data[0][0] * pData[3]) + (data[0][1] * pData[7]) + (data[0][2] * pData[11]) + (data[0][3] * pData[15]);
   TDouble v04 = (data[1][0] * pData[0]) + (data[1][1] * pData[4]) + (data[1][2] * pData[ 8]) + (data[1][3] * pData[12]);
   TDouble v05 = (data[1][0] * pData[1]) + (data[1][1] * pData[5]) + (data[1][2] * pData[ 9]) + (data[1][3] * pData[13]);
   TDouble v06 = (data[1][0] * pData[2]) + (data[1][1] * pData[6]) + (data[1][2] * pData[10]) + (data[1][3] * pData[14]);
   TDouble v07 = (data[1][0] * pData[3]) + (data[1][1] * pData[7]) + (data[1][2] * pData[11]) + (data[1][3] * pData[15]);
   TDouble v08 = (data[2][0] * pData[0]) + (data[2][1] * pData[4]) + (data[2][2] * pData[ 8]) + (data[2][3] * pData[12]);
   TDouble v09 = (data[2][0] * pData[1]) + (data[2][1] * pData[5]) + (data[2][2] * pData[ 9]) + (data[2][3] * pData[13]);
   TDouble v10 = (data[2][0] * pData[2]) + (data[2][1] * pData[6]) + (data[2][2] * pData[10]) + (data[2][3] * pData[14]);
   TDouble v11 = (data[2][0] * pData[3]) + (data[2][1] * pData[7]) + (data[2][2] * pData[11]) + (data[2][3] * pData[15]);
   TDouble v12 = (data[3][0] * pData[0]) + (data[3][1] * pData[4]) + (data[3][2] * pData[ 8]) + (data[3][3] * pData[12]);
   TDouble v13 = (data[3][0] * pData[1]) + (data[3][1] * pData[5]) + (data[3][2] * pData[ 9]) + (data[3][3] * pData[13]);
   TDouble v14 = (data[3][0] * pData[2]) + (data[3][1] * pData[6]) + (data[3][2] * pData[10]) + (data[3][3] * pData[14]);
   TDouble v15 = (data[3][0] * pData[3]) + (data[3][1] * pData[7]) + (data[3][2] * pData[11]) + (data[3][3] * pData[15]);
   // ��������
   data[0][0] = v00;
   data[0][1] = v01;
   data[0][2] = v02;
   data[0][3] = v03;
   data[1][0] = v04;
   data[1][1] = v05;
   data[1][2] = v06;
   data[1][3] = v07;
   data[2][0] = v08;
   data[2][1] = v09;
   data[2][2] = v10;
   data[2][3] = v11;
   data[3][0] = v12;
   data[3][1] = v13;
   data[3][2] = v14;
   data[3][3] = v15;
   return ESuccess;
}

//============================================================
// <T>׷��һ�������������ݡ�</T>
//
// @param matrix ����
// @return ������
//============================================================
TResult SDoubleMatrix3d::Append(const SDoubleMatrix3d& matrix){
   return AppendData((TDoubleC*)matrix.data);
}

//============================================================
// <T>���㵱ǰ����������</T>
//
// @return ������
//============================================================
TBool SDoubleMatrix3d::Invert(){
   // �������
   TDouble invert[4][4];
   invert[0][0] =  data[1][1] * data[2][2] * data[3][3] -
                   data[1][1] * data[2][3] * data[3][2] -
                   data[2][1] * data[1][2] * data[3][3] +
                   data[2][1] * data[1][3] * data[3][2] +
                   data[3][1] * data[1][2] * data[2][3] -
                   data[3][1] * data[1][3] * data[2][2];
   invert[1][0] = -data[1][0] * data[2][2] * data[3][3] +
                   data[1][0] * data[2][3] * data[3][2] +
                   data[2][0] * data[1][2] * data[3][3] -
                   data[2][0] * data[1][3] * data[3][2] -
                   data[3][0] * data[1][2] * data[2][3] +
                   data[3][0] * data[1][3] * data[2][2];
   invert[2][0] =  data[1][0] * data[2][1] * data[3][3] -
                   data[1][0] * data[2][3] * data[3][1] -
                   data[2][0] * data[1][1] * data[3][3] +
                   data[2][0] * data[1][3] * data[3][1] +
                   data[3][0] * data[1][1] * data[2][3] -
                   data[3][0] * data[1][3] * data[2][1];
   invert[3][0] = -data[1][0] * data[2][1] * data[3][2] +
                   data[1][0] * data[2][2] * data[3][1] +
                   data[2][0] * data[1][1] * data[3][2] -
                   data[2][0] * data[1][2] * data[3][1] -
                   data[3][0] * data[1][1] * data[2][2] +
                   data[3][0] * data[1][2] * data[2][1];
   invert[0][1] = -data[0][1] * data[2][2] * data[3][3] +
                   data[0][1] * data[2][3] * data[3][2] +
                   data[2][1] * data[0][2] * data[3][3] -
                   data[2][1] * data[0][3] * data[3][2] -
                   data[3][1] * data[0][2] * data[2][3] +
                   data[3][1] * data[0][3] * data[2][2];
   invert[1][1] =  data[0][0] * data[2][2] * data[3][3] -
                   data[0][0] * data[2][3] * data[3][2] -
                   data[2][0] * data[0][2] * data[3][3] +
                   data[2][0] * data[0][3] * data[3][2] +
                   data[3][0] * data[0][2] * data[2][3] -
                   data[3][0] * data[0][3] * data[2][2];
   invert[2][1] = -data[0][0] * data[2][1] * data[3][3] +
                   data[0][0] * data[2][3] * data[3][1] +
                   data[2][0] * data[0][1] * data[3][3] -
                   data[2][0] * data[0][3] * data[3][1] -
                   data[3][0] * data[0][1] * data[2][3] +
                   data[3][0] * data[0][3] * data[2][1];
   invert[3][1] =  data[0][0] * data[2][1] * data[3][2] -
                   data[0][0] * data[2][2] * data[3][1] -
                   data[2][0] * data[0][1] * data[3][2] +
                   data[2][0] * data[0][2] * data[3][1] +
                   data[3][0] * data[0][1] * data[2][2] -
                   data[3][0] * data[0][2] * data[2][1];
   invert[0][2] =  data[0][1] * data[1][2] * data[3][3] -
                   data[0][1] * data[1][3] * data[3][2] -
                   data[1][1] * data[0][2] * data[3][3] +
                   data[1][1] * data[0][3] * data[3][2] +
                   data[3][1] * data[0][2] * data[1][3] -
                   data[3][1] * data[0][3] * data[1][2];
   invert[1][2] = -data[0][0] * data[1][2] * data[3][3] +
                   data[0][0] * data[1][3] * data[3][2] +
                   data[1][0] * data[0][2] * data[3][3] -
                   data[1][0] * data[0][3] * data[3][2] -
                   data[3][0] * data[0][2] * data[1][3] +
                   data[3][0] * data[0][3] * data[1][2];
   invert[2][2] =  data[0][0] * data[1][1] * data[3][3] -
                   data[0][0] * data[1][3] * data[3][1] -
                   data[1][0] * data[0][1] * data[3][3] +
                   data[1][0] * data[0][3] * data[3][1] +
                   data[3][0] * data[0][1] * data[1][3] -
                   data[3][0] * data[0][3] * data[1][1];
   invert[3][2] = -data[0][0] * data[1][1] * data[3][2] +
                   data[0][0] * data[1][2] * data[3][1] +
                   data[1][0] * data[0][1] * data[3][2] -
                   data[1][0] * data[0][2] * data[3][1] -
                   data[3][0] * data[0][1] * data[1][2] +
                   data[3][0] * data[0][2] * data[1][1];
   invert[0][3] = -data[0][1] * data[1][2] * data[2][3] +
                   data[0][1] * data[1][3] * data[2][2] +
                   data[1][1] * data[0][2] * data[2][3] -
                   data[1][1] * data[0][3] * data[2][2] -
                   data[2][1] * data[0][2] * data[1][3] +
                   data[2][1] * data[0][3] * data[1][2];
   invert[1][3] =  data[0][0] * data[1][2] * data[2][3] -
                   data[0][0] * data[1][3] * data[2][2] -
                   data[1][0] * data[0][2] * data[2][3] +
                   data[1][0] * data[0][3] * data[2][2] +
                   data[2][0] * data[0][2] * data[1][3] -
                   data[2][0] * data[0][3] * data[1][2];
   invert[2][3] = -data[0][0] * data[1][1] * data[2][3] +
                   data[0][0] * data[1][3] * data[2][1] +
                   data[1][0] * data[0][1] * data[2][3] -
                   data[1][0] * data[0][3] * data[2][1] -
                   data[2][0] * data[0][1] * data[1][3] +
                   data[2][0] * data[0][3] * data[1][1];
   invert[3][3] =  data[0][0] * data[1][1] * data[2][2] -
                   data[0][0] * data[1][2] * data[2][1] -
                   data[1][0] * data[0][1] * data[2][2] +
                   data[1][0] * data[0][2] * data[2][1] +
                   data[2][0] * data[0][1] * data[1][2] -
                   data[2][0] * data[0][2] * data[1][1];
   // ��������
   TDouble rate = data[0][0] * invert[0][0] + data[0][1] * invert[1][0] + data[0][2] * invert[2][0] + data[0][3] * invert[3][0];
   if(rate == 0){
     return EFalse;
   }
   rate = 1 / rate;
   // ��������
   for(TInt y = 0; y < 4; y++){
      for(TInt x = 0; x < 4; x++){
        data[y][x] = invert[y][x] * rate;
      }
   }
   return ETrue;
}

//============================================================
// <T>ǿ�Ƹ������ݡ�</T>
//============================================================
void SDoubleMatrix3d::UpdateForce(){
   TDouble rsx = sin(rx);
   TDouble rcx = cos(rx);
   TDouble rsy = sin(ry);
   TDouble rcy = cos(ry);
   TDouble rsz = sin(rz);
   TDouble rcz = cos(rz);
   data[0][0] = rcy * rcz * sx;
   data[0][1] = rcy * rsz * sx;
   data[0][2] = -rsy * sx;
   data[0][3] = 0;
   data[1][0] = (rsx * rsy * rcz - rcx * rsz) * sy;
   data[1][1] = (rsx * rsy * rsz + rcx * rcz) * sy;
   data[1][2] = rsx * rcy * sy;
   data[1][3] = 0;
   data[2][0] = (rcx * rsy * rcz + rsx * rsz) * sz;
   data[2][1] = (rcx * rsy * rsz - rsx * rcz) * sz;
   data[2][2] = rcx * rcy * sz;
   data[2][3] = 0;
   data[3][0] = tx;
   data[3][1] = ty;
   data[3][2] = tz;
   data[3][3] = 1;
}

//============================================================
// <T>�������ݡ�</T>
//============================================================
void SDoubleMatrix3d::Update(){
   if(dirty){
      UpdateForce();
      dirty = EFalse;
   }
}

//============================================================
// <T>��λ������</T>
//============================================================
void SDoubleMatrix3d::Identity(){
   tx = ty = tz = 0;
   rx = ry = rz = 0;
   sx = sy = sz = 1;
   for(TInt y = 0; y < 4; y++){
      for(TInt x = 0; x < 4; x++){
         data[y][x] = (x == y) ? 1 : 0;
      }
   }
   dirty = EFalse;
}

//============================================================
// <T>ƽ�����ݡ�</T>
//
// @param x X����
// @param y Y����
// @param z Z����
//============================================================
void SDoubleMatrix3d::Translate(TDouble x, TDouble y, TDouble z){
   TDouble data[4][4];
   data[0][0] = 1;
   data[0][1] = 0;
   data[0][2] = 0;
   data[0][3] = 0;
   data[1][0] = 0;
   data[1][1] = 1;
   data[1][2] = 0;
   data[1][3] = 0;
   data[2][0] = 0;
   data[2][1] = 0;
   data[2][2] = 1;
   data[2][3] = 0;
   data[3][0] = x;
   data[3][1] = y;
   data[3][2] = z;
   data[3][3] = 1;
   AppendData((TDoubleC*)data);
}

//============================================================
// <T>X����ת���ݡ�</T>
//  1    0   0 0
//  0  cos sin 0
//  0 -sin cos 0
//  0    0   0 1 
//
// @param value ����
//============================================================
void SDoubleMatrix3d::RotationX(TDouble value){
   // ������ת
   TDouble rs = sin(value);
   TDouble rc = cos(value);
   // ׷������
   TDouble data[4][4];
   data[0][0] = 1;
   data[0][1] = 0;
   data[0][2] = 0;
   data[0][3] = 0;
   data[1][0] = 0;
   data[1][1] = rc;
   data[1][2] = rs;
   data[1][3] = 0;
   data[2][0] = 0;
   data[2][1] = -rs;
   data[2][2] = rc;
   data[2][3] = 0;
   data[3][0] = 0;
   data[3][1] = 0;
   data[3][2] = 0;
   data[3][3] = 1;
   AppendData((TDoubleC*)data);
}

//============================================================
// <T>Y����ת���ݡ�</T>
//  cos   0  sin  0
//  0     1    0  0
//  -sin  0  cos  0
//  0     0    0  1 
//
// @param value ����
//============================================================
void SDoubleMatrix3d::RotationY(TDouble value){
   // ������ת
   TDouble rs = sin(value);
   TDouble rc = cos(value);
   // ׷������
   TDouble data[4][4];
   data[0][0] = rc;
   data[0][1] = 0;
   data[0][2] = rs;
   data[0][3] = 0;
   data[1][0] = 0;
   data[1][1] = 1;
   data[1][2] = 0;
   data[1][3] = 0;
   data[2][0] = -rs;
   data[2][1] = 0;
   data[2][2] = rc;
   data[2][3] = 0;
   data[3][0] = 0;
   data[3][1] = 0;
   data[3][2] = 0;
   data[3][3] = 1;
   AppendData((TDoubleC*)data);
}

//============================================================
// <T>Z����ת���ݡ�</T>
//  cos  sin  0 0
//  -sin cos  1 0
//  0      0  1 0
//  0      0  0 1 
//
// @param value ����
//============================================================
void SDoubleMatrix3d::RotationZ(TDouble value){
   // ������ת
   TDouble rs = sin(value);
   TDouble rc = cos(value);
   // ׷������
   TDouble data[4][4];
   data[0][0] = rc;
   data[0][1] = rs;
   data[0][2] = 0;
   data[0][3] = 0;
   data[1][0] = -rs;
   data[1][1] = rc;
   data[1][2] = 1;
   data[1][3] = 0;
   data[2][0] = 0;
   data[2][1] = 0;
   data[2][2] = 1;
   data[2][3] = 0;
   data[3][0] = 0;
   data[3][1] = 0;
   data[3][2] = 0;
   data[3][3] = 1;
   AppendData((TDoubleC*)data);
}

//============================================================
// <T>������ת���ݡ�</T>
//  1    0   0 0
//  0  cos sin 0
//  0 -sin cos 0
//  0    0   0 1 
//
// @param x X����
// @param y Y����
// @param z Z����
//============================================================
void SDoubleMatrix3d::Rotation(TDouble x, TDouble y, TDouble z){
   // ������ת
   TDouble rsx = sin(x);
   TDouble rcx = cos(x);
   TDouble rsy = sin(y);
   TDouble rcy = cos(y);
   TDouble rsz = sin(z);
   TDouble rcz = cos(z);
   // ׷������
   TDouble data[4][4];
   data[0][0] = rcy * rcz;
   data[0][1] = rcy * rsz;
   data[0][2] = -rsy;
   data[0][3] = 0;
   data[1][0] = rsx * rsy * rcz - rcx * rsz;
   data[1][1] = rsx * rsy * rsz + rcx * rcz;
   data[1][2] = rsx * rcy;
   data[1][3] = 0;
   data[2][0] = rcx * rsy * rcz + rsx * rsz;
   data[2][1] = rcx * rsy * rsz - rsx * rcx;
   data[2][2] = rcx * rcy;
   data[2][3] = 0;
   data[3][0] = 0;
   data[3][1] = 0;
   data[3][2] = 0;
   data[3][3] = 1;
   AppendData((TDoubleC*)data);
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param x X����
// @param y Y����
// @param z Z����
//============================================================
void SDoubleMatrix3d::Scale(TDouble x, TDouble y, TDouble z){
   TDouble data[4][4];
   data[0][0] = x;
   data[0][1] = 0;
   data[0][2] = 0;
   data[0][3] = 0;
   data[1][0] = 0;
   data[1][1] = y;
   data[1][2] = 0;
   data[1][3] = 0;
   data[2][0] = 0;
   data[2][1] = 0;
   data[2][2] = z;
   data[2][3] = 0;
   data[3][0] = 0;
   data[3][1] = 0;
   data[3][2] = 0;
   data[3][3] = 1;
   AppendData((TDoubleC*)data);
}



//============================================================
// <T>�任һ����ά�������ݡ�</T>
// <P>ÿ�������X,Y,X����ά�ȡ�</P>
//
// @param pOutput �������
// @param pInput ��������
// @param count ������
// @return ������
//============================================================
TResult SDoubleMatrix3d::Transform(TDouble* pOutput, TDoubleC* pInput, TInt count){
   // ������
   MO_CHECK(pOutput, return ENull);
   MO_CHECK(pInput, return ENull);
   MO_CHECK(count > 0, return EFailure);
   // ��������
   for(TInt n = 0; n < count; n++){
      TInt index = (n << 1) + n; // = 3 * n
      pOutput[index    ] = (pInput[index] * data[0][0]) + (pInput[index + 1] * data[1][0]) +(pInput[index + 2] * data[2][0]) + data[3][0];
      pOutput[index + 1] = (pInput[index] * data[0][1]) + (pInput[index + 1] * data[1][1]) +(pInput[index + 2] * data[2][1]) + data[3][1];
      pOutput[index + 2] = (pInput[index] * data[0][2]) + (pInput[index + 1] * data[1][2]) +(pInput[index + 2] * data[2][2]) + data[3][2];
   }
   return ESuccess;
}

//============================================================
// <T>�任һ����ά�������ݡ�</T>
//
// @param x X����
// @param y Y����
// @param z Z����
// @return �任����ά����
//============================================================
SDoublePoint3 SDoubleMatrix3d::TransformPoint3(TDouble x, TDouble y, TDouble z){
   SDoublePoint3 result;
   result.x = (x * data[0][0]) + (y * data[1][0]) +(z * data[2][0]) + data[3][0];
   result.y = (x * data[0][1]) + (y * data[1][1]) +(z * data[2][1]) + data[3][1];
   result.z = (x * data[0][2]) + (y * data[1][2]) +(z * data[2][2]) + data[3][2];
   return result;
}

//============================================================
// <T>�任һ����ά�������ݡ�</T>
//
// @param value ��ά����
// @return �任����ά����
//============================================================
SDoublePoint3 SDoubleMatrix3d::TransformPoint3(const SDoublePoint3& value){
   SDoublePoint3 result;
   result.x = (value.x * data[0][0]) + (value.y * data[1][0]) +(value.z * data[2][0]) + data[3][0];
   result.y = (value.x * data[0][1]) + (value.y * data[1][1]) +(value.z * data[2][1]) + data[3][1];
   result.z = (value.x * data[0][2]) + (value.y * data[1][2]) +(value.z * data[2][2]) + data[3][2];
   return result;
}

//============================================================
// <T>�任һ����ά�������ݡ�</T>
//
// @param input ���붥��
// @param output �������
// @return �任����ά����
//============================================================
void SDoubleMatrix3d::TransformPoint3(SDoublePoint3& output, const SDoublePoint3& input){
   output.x = (input.x * data[0][0]) + (input.y * data[1][0]) +(input.z * data[2][0]) + data[3][0];
   output.y = (input.x * data[0][1]) + (input.y * data[1][1]) +(input.z * data[2][1]) + data[3][1];
   output.z = (input.x * data[0][2]) + (input.y * data[1][2]) +(input.z * data[2][2]) + data[3][2];
}

//============================================================
// <T>�任һ����ά�������ݡ�</T>
//
// @param x X����
// @param y Y����
// @param z Z����
// @return �任����ά����
//============================================================
SDoubleVector3 SDoubleMatrix3d::TransformVector3(TDouble x, TDouble y, TDouble z){
   SDoubleVector3 result;
   result.x = (x * data[0][0]) + (y * data[1][0]) +(z * data[2][0]) + data[3][0];
   result.y = (x * data[0][1]) + (y * data[1][1]) +(z * data[2][1]) + data[3][1];
   result.z = (x * data[0][2]) + (y * data[1][2]) +(z * data[2][2]) + data[3][2];
   return result;
}

//============================================================
// <T>�任һ����ά�������ݡ�</T>
//
// @param value ��ά����
// @return �任����ά����
//============================================================
SDoubleVector3 SDoubleMatrix3d::TransformVector3(const SDoubleVector3& value){
   SDoubleVector3 result;
   result.x = (value.x * data[0][0]) + (value.y * data[1][0]) +(value.z * data[2][0]) + data[3][0];
   result.y = (value.x * data[0][1]) + (value.y * data[1][1]) +(value.z * data[2][1]) + data[3][1];
   result.z = (value.x * data[0][2]) + (value.y * data[1][2]) +(value.z * data[2][2]) + data[3][2];
   return result;
}

//============================================================
// <T>�任һ����ά�������ݡ�</T>
//
// @param input ���뷽��
// @param output �������
// @return �任����ά����
//============================================================
void SDoubleMatrix3d::TransformVector3(SDoubleVector3& output, const SDoubleVector3& input){
   output.x = (input.x * data[0][0]) + (input.y * data[1][0]) +(input.z * data[2][0]) + data[3][0];
   output.y = (input.x * data[0][1]) + (input.y * data[1][1]) +(input.z * data[2][1]) + data[3][1];
   output.z = (input.x * data[0][2]) + (input.y * data[1][2]) +(input.z * data[2][2]) + data[3][2];
}

//============================================================
// <T>���л��������ݵ�������ڡ�</T>
//
// @param pOutput �����
// @param transpose ת��
// @return ������
//============================================================
TResult SDoubleMatrix3d::SerializeData4x3(IDataOutput* pOutput, TBool transpose){
   if(transpose){
      TDouble result[4][3];
      result[0][0] = data[0][0];
      result[0][1] = data[1][0];
      result[0][2] = data[2][0];
      result[0][3] = data[3][0];
      result[1][0] = data[0][1];
      result[1][1] = data[1][1];
      result[1][2] = data[2][1];
      result[1][3] = data[3][1];
      result[2][0] = data[0][2];
      result[2][1] = data[1][2];
      result[2][2] = data[2][2];
      result[2][3] = data[3][2];
      pOutput->Write(result, sizeof(TDouble) * 12);
   }else{
      pOutput->Write(data, sizeof(TDouble) * 12);
   }
   return ESuccess;
}

//============================================================
// <T>���������ﷴ���л��������ݡ�</T>
//
// @param pInput ������
// @param transpose ת��
// @return ������
//============================================================
TResult SDoubleMatrix3d::UnserializeData4x3(IDataInput* pInput, TBool transpose){
   if(transpose){
      TDouble result[4][3];
      pInput->Read(result, sizeof(TDouble) * 12);
      data[0][0] = result[0][0];
      data[0][1] = result[1][0];
      data[0][2] = result[2][0];
      data[0][3] = result[3][0];
      data[1][0] = result[0][1];
      data[1][1] = result[1][1];
      data[1][2] = result[2][1];
      data[1][3] = result[3][1];
      data[2][0] = result[0][2];
      data[2][1] = result[1][2];
      data[2][2] = result[2][2];
      data[2][3] = result[3][2];
   }else{
      pInput->Read(data, sizeof(TDouble) * 12);
   }
   return ESuccess;
}

//============================================================
// <T>���л��������ݵ�������ڡ�</T>
//
// @param pOutput �����
// @param transpose ת��
// @return ������
//============================================================
TResult SDoubleMatrix3d::SerializeData4x4(IDataOutput* pOutput, TBool transpose){
   if(transpose){
      TDouble result[4][4];
      result[0][0] = data[0][0];
      result[0][1] = data[1][0];
      result[0][2] = data[2][0];
      result[0][3] = data[3][0];
      result[1][0] = data[0][1];
      result[1][1] = data[1][1];
      result[1][2] = data[2][1];
      result[1][3] = data[3][1];
      result[2][0] = data[0][2];
      result[2][1] = data[1][2];
      result[2][2] = data[2][2];
      result[2][3] = data[3][2];
      result[3][0] = data[0][3];
      result[3][1] = data[1][3];
      result[3][2] = data[2][3];
      result[3][3] = data[3][3];
      pOutput->Write(result, sizeof(TDouble) * 16);
   }else{
      pOutput->Write(data, sizeof(TDouble) * 16);
   }
   return ESuccess;
}

//============================================================
// <T>���������ﷴ���л��������ݡ�</T>
//
// @param pInput ������
// @param transpose ת��
// @return ������
//============================================================
TResult SDoubleMatrix3d::UnserializeData4x4(IDataInput* pInput, TBool transpose){
   if(transpose){
      TDouble result[4][4];
      pInput->Read(result, sizeof(TDouble) * 16);
      data[0][0] = result[0][0];
      data[0][1] = result[1][0];
      data[0][2] = result[2][0];
      data[0][3] = result[3][0];
      data[1][0] = result[0][1];
      data[1][1] = result[1][1];
      data[1][2] = result[2][1];
      data[1][3] = result[3][1];
      data[2][0] = result[0][2];
      data[2][1] = result[1][2];
      data[2][2] = result[2][2];
      data[2][3] = result[3][2];
      data[3][0] = result[0][3];
      data[3][1] = result[1][3];
      data[3][2] = result[2][3];
      data[3][3] = result[3][3];
   }else{
      pInput->Read(data, sizeof(TDouble) * 16);
   }
   return ESuccess;
}

//============================================================
// <T>���л��������ݵ�������ڡ�</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult SDoubleMatrix3d::Serialize(IDataOutput* pOutput){
   // д��ƽ����Ϣ
   pOutput->WriteDouble(tx);
   pOutput->WriteDouble(ty);
   pOutput->WriteDouble(tz);
   // д����ת����
   pOutput->WriteDouble(rx);
   pOutput->WriteDouble(ry);
   pOutput->WriteDouble(rz);
   // ��ȡ������Ϣ
   pOutput->WriteDouble(sx);
   pOutput->WriteDouble(sy);
   pOutput->WriteDouble(sz);
   return ESuccess;
}

//============================================================
// <T>���������ﷴ���л��������ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult SDoubleMatrix3d::Unserialize(IDataInput* pInput){
   // ��ȡƽ����Ϣ
   tx = pInput->ReadDouble();
   ty = pInput->ReadDouble();
   tz = pInput->ReadDouble();
   // ��ȡ��ת����
   rx = pInput->ReadDouble();
   ry = pInput->ReadDouble();
   rz = pInput->ReadDouble();
   // ��ȡ������Ϣ
   sx = pInput->ReadDouble();
   sy = pInput->ReadDouble();
   sz = pInput->ReadDouble();
   // ���´���
   UpdateForce();
   return ESuccess;
}

MO_NAMESPACE_END
