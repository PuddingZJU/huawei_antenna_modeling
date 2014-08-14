//#include "ArrayToolBox.h"
//#include <math.h>
//#include   <stdlib.h>   
//int rowI[4] = {0, 4, 8, 12};
//
////4½×µ¥Î»¾ØÕó
//double oneMatrix[16] = {1.0,   0,   0,   0,
//						  0, 1.0,   0,   0,
//						  0,   0, 1.0,   0,
//						  0,   0,   0, 1.0};
//
//
//void ArrayToolBox<double>::crossprod3(double d1[3], double d2[3], double out[3])
////²æ³Ë
//{
//	out[0] = d1[1]*d2[2] - d1[2]*d2[1];
//	out[1] = d1[2]*d2[0] - d1[0]*d2[2];
//	out[2] = d1[0]*d2[1] - d1[1]*d2[0];
//}
//
////µã³Ë
//double ArrayToolBox<double>::dotprod3(double d1[3], double d2[3])
//{
//	return d1[0]*d2[0] + d1[1]*d2[1] + d1[2]*d2[2];
//}
//
////Ð±ÂÊ
//double ArrayToolBox<double>::slope(double x1, double y1, double x2, double y2)
//{
//	if(x1 != x2){
//		double ret = (y1 - y2) / (x1 - x2);
//		if(ret > MAXDBL){
//			ret = MAXDBL;
//		}
//		return ret;
//	}
//	else{
//		return MAXDBL;
//	}
//}
//
//int ArrayToolBox<double>::toInteger(double d)
//{
//	return 0;
//}
//
///************************************************************************/
///*	n	n	n	n       n	n	n	n                                   */
///*  n	n	n	n	X	n	n	n	n                                   */
///*  n	n	n	n	    n	n	n	n                                   */
///*  n	n	n	n       n	n	n	n                                   */
///************************************************************************/
//void ArrayToolBox<double>::matrixMul44(double m1[16], double m2[16], double out[16])
//{
//	double sum = 0;
//	for(int j = 0; j < 4; j++){
//		for(int i = 0; i < 4; i++){
//			for(int k = 0; k < 4; k++){
//				sum += m1[j*4 + k] * m2[k*4 + i];
//			}
//			out[j*4 + i] = sum;
//			sum = 0;
//		}
//	}
//}
//
///************************************************************************/
///*	n	n	n	n       n												*/
///*  n	n	n	n	X	n									            */
///*  n	n	n	n	    n						                        */
///*  n	n	n	n       n			                                    */
///************************************************************************/
//void ArrayToolBox<double>::matrixMul41(double m1[16], double m2[4], double out[4])
//{
//	double sum = 0;
//	for(int i = 0; i < 4; i++){
//		for(int j = 0; j < 4; j++){
//			sum += m1[i*4 + j]*m2[j];
//		}
//		out[i] = sum;
//		sum = 0;
//	}
//}
//
///************************************************************************/
///*	n	n	n	n       n	n	n	n                                   */
///*  n	n	n	n	=	n	n	n	n                                   */
///*  n	n	n	n	    n	n	n	n                                   */
///*  n	n	n	n       n	n	n	n                                   */
///************************************************************************/
//void ArrayToolBox<double>::loadMatrix44(double m1[16], double m2[16])
//{
//	for(int i = 0; i < 16; i++){
//		m1[i] = m2[i];
//	}
//}
//
//void ArrayToolBox<double>::loadOneMatrix(double m1[16])
//{
//	for(int i = 0; i < 16; i++){
//		m1[i] = oneMatrix[i];
//	}
//}
//
//int ArrayToolBox<double>::randomInt(int start, int end)
//{
//	return (rand() % (end - start) + start)/2;
//}
//
//void normize(double d1[3], double out[3])
//{
//	double len = sqrt(d1[0]*d1[0] + d1[1]*d1[1] + d1[2]*d1[2]);
//	if(len != 0){
//		for(int i = 0; i < 3; i++){
//			out[i] = d1[i]/len;
//		}
//	} else{
//		for(int i = 0; i < 3; i++){
//			out[i] = 0;
//		}
//	}
//}
//
//void ArrayToolBox<double>::calVector(double d1[3], double d2[3], double out[3])
//{
//	for(int i = 0; i < 3; i++){
//		out[i] = d2[i] - d1[i];
//	}	
//}
//
//bool ArrayToolBox<double>::isNear(double d1, double d2)
//{
//	double d = d1 - d2;
//	if(d < 0){
//		d *= -1.0;
//	}
//	double td = 0;
//	if(d - td == 0){
//		return true;
//	} else{
//		return false;
//	}
//}
//
//int ArrayToolBox<double>::nansyfloor(double d)
//{
//	int i = d;
//	if(d - 1.0*i >= 0.5){
//		return i + 1;
//	} else{
//		return i;
//	}
//}
//
//void ArrayToolBox<double>::vectorAdd(double *d1, double *d2, double *out, int n)
//{
//	for(int i = 0; i < n; i++){
//		out[i] = d1[i] + d2[i];
//	}
//}
//
//double ArrayToolBox<double>::vectorLen2nsqrt(double x1, double y1, double x2, double y2)
//{
//	double dx = x1 - x2;
//	double dy = y1 - y2;
//	return dx*dx + dy*dy;
//}
//
//double ArrayToolBox<double>::vectorLen2(double x1, double y1, double x2, double y2)
//{
//	return sqrt(ArrayToolBox<double>::vectorLen2nsqrt(x1, y1, x2, y2));
//}