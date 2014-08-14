#include "Mathematics.h"


Matrix3 RotateMatrix3(double a, Vector3 raxis);
Matrix3 RotateMatrix3(double thetax, double thetay, double thetaz);
Matrix4 RotateMatrix4(double a, Vector3 raxis);
Matrix4 TranslateMatrix4(Vector3 t);
Matrix3 TransposeMatrix3(Matrix3 m);
Matrix4 TransposeMatrix4(Matrix4 m);
Matrix3 TransposeMul3(Matrix3 m1, Matrix3 m2);