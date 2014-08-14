/** @file 
* @brief  数学库
* @author 赵洪德
* @date 2008-10-29
* @version 0.1
*
*四元数
*/



#ifndef _mathematics_h_
#error "Dont include Quaternion directly!!! Use Mathematics.h instead."
#endif

// Constructors
#include <exception>
/**
*@note Constructors                                          
*/
inline Quaternion::Quaternion()
{x = 0; y = 0; z = 0; w =0;}
/**
*@note Constructors                                          
*/
inline Quaternion::Quaternion(const Quaternion& other)
{
	x = other.x; y = other.y; z = other.z; w = other.w;
}
/**
*@note Constructors                                          
*/
inline Quaternion::Quaternion(const double* other)
{
	x = other[0]; y = other[1]; z = other[2]; w = other[3];
}
/**
*@note Constructors                                          
*/
inline Quaternion::Quaternion(double _x, double _y, double _z, double _w)
{
	x = _x; y = _y; z = _z; w = _w;
}
/**
*@note Constructors                                          
*/
inline Quaternion::Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
	this->FromAxes(xAxis, yAxis, zAxis);
	//Matrix3 kRot;
 //
	//kRot.m[0][0] = xAxis.x;
 //   kRot.m[1][0] = xAxis.y;
 //   kRot.m[2][0] = xAxis.z;
 //   kRot.m[0][1] = yAxis.x;
 //   kRot.m[1][1] = yAxis.y;
 //   kRot.m[2][1] = yAxis.z;
 //
 //   kRot.m[0][2] = zAxis.x;
 //   kRot.m[1][2] = zAxis.y;
 //   kRot.m[2][2] = zAxis.z;
 //
 //   FromRotationMatrix(kRot);
}

/**
*@note define operator                                  
*/
inline Quaternion& Quaternion::operator=(const Quaternion& other)
{
	x = other.x; y = other.y; z = other.z; w = other.w;
	return *this;
}
/**
*@note Assign                                      
*/
inline void Quaternion::Assign(const Quaternion& other)
{
	x = other.x; y = other.y; z = other.z; w = other.w;
}
/**
*@note Assign                                      
*/
inline void Quaternion::Assign(const double* other)
{
	x = other[0]; y = other[1]; z = other[2]; w = other[3];
}
/**
*@note Assign                                      
*/
inline void Quaternion::Assign(double _x, double _y, double _z, double _w)
{
	x = _x; y = _y; z = _z; w = _w;
}
/**
*@note invert
*/
inline void Quaternion::Invert()
{
	x = -x; y = -y; z = -z;
}
/**
*@note invert
*/
inline void Quaternion::Invert(const Quaternion& other)
{
	x = -other.x; y = -other.y; z = -other.z;
	w = other.w;
}
/**
*@note define operator                                  
*/
inline Quaternion Quaternion::operator- () const
{
	return Quaternion(-x, -y, -z, -w);
}
/**
*@note 求四元组的长度               
*@return 长度
*/
inline double Quaternion::Length() const
{
	return (double)sqrt(w*w + x*x + y*y + z*z);
}
/**
*@note 四元组长度的平方   
*@return 长度的平方
*/
inline double Quaternion::LengthSqr() const
{
	return w*w + x*x + y*y + z*z;
}
/**
*@note 将四元组单位化                                     
*/

inline void Quaternion::Normalize()
{
	//if((w*w + x*x + y*y + z*z)<1e-6)
	//	AfxMessageBox("quternion error");
	double f = 1.0f / sqrt(w*w + x*x + y*y + z*z); //2009.11.20 LX
	x *= f; y *= f; z *= f; w *= f;
}
/**
*@note 将四元组other单位化          
*@param other 四元数
*/
inline void Quaternion::Normalize(const Quaternion& other)
{
	double f = 1.0f / other.Length();
	x = other.x * f; y = other.y * f; z = other.z * f; w = other.w * f;
}

/**
*@note 两个四元组相乘      
*@param other 乘数
*@return 四元数
*/
inline Quaternion& Quaternion::Mul(const Quaternion& other)
{
	Mul(*this, other);
	return *this;
}
/**
*@note 两个四元组相乘     
*@param q1 四元数1
*@param q2 四元数2
*@return 四元数
*/
/************************************************************************/
inline Quaternion& Quaternion::Mul(const Quaternion& q1, const Quaternion& q2)
{
	/* set  
	       q1=(x1,y1,z1,w1);
		   q2=(x2,y2,z2,w2);
		                    */
	const Vector3 v1 = &q1.x;
	const Vector3 v2 = &q2.x;

	double scalar = q1.w * q2.w - v1.Dot(v2);    // scalar=w1*w2-(x1*x2+y1*y2+z1*z2)

	Vector3 va; va.Cross(v1, v2);                
	Vector3 vb; vb.Mul(v1, q2.w);
	Vector3 vc; vc.Mul(v2, q1.w);
	va.Add(vb); va.Add(vc);

	x = va.x; y = va.y; z = va.z; w = scalar;
	/*    x=y1*z2-z1*y2+x1*w2+x2*w1
	      y=z1*x2-x1*z2+y1*w2+y2*w1
		  z=x1*y2-y1*x2+z1*w2+z2*w1
		                            */

	Normalize();                              //单位化
	return *this;
}
//inline Quaternion Quaternion::Mul (const Quaternion& q, const Vector3& v) const
//{
//	return Quaternion(
//		q.w * v.x + q.y * v.z - q.z * v.y ,
//		q.w * v.y + q.z * v.x - q.x * v.z ,
//		q.w * v.z + q.x * v.y - q.y * v.x ,
//		-(q.x * v.x + q.y * v.y + q.z * v.z)
//		);
//}
//
//inline Quaternion Quaternion::Mul (const Vector3& v, const Quaternion& q) const
//{
//	return Quaternion(
//		q.w * v.x + q.z * v.y - q.y * v.z ,
//		q.w * v.y + q.x * v.z - q.z * v.x ,
//		q.w * v.z + q.y * v.x - q.x * v.y ,
//		-(q.x * v.x + q.y * v.y + q.z * v.z)
//		);
//}

/**
*@note operator                                  
*/

inline Quaternion Quaternion::operator*(const Quaternion& other) const
{
	Quaternion tmp;
	tmp.Mul(*this, other);
	return tmp;
}
/**
*@note operator                                  
*/
inline Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	Mul(*this, other);
	return *this;
}
/**
*@note operator                                  
*/
inline Quaternion Quaternion::operator- (const Quaternion& rkQ) const
{
	return Quaternion(x-rkQ.x,y-rkQ.y,z-rkQ.z,w-rkQ.w);
}
/**
*@note operator                                  
*/
inline Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
	return Quaternion(x+rkQ.x,y+rkQ.y,z+rkQ.z,w+rkQ.w);
}
/**
*@note operator                                  
*/
inline Vector3 Quaternion::operator *(const Vector3& v) const
{
	// nVidia SDK implementation
	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv.Cross(qvec, v);
	uuv.Cross(qvec, uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;
}

// Rotation
//inline Vector3 Quaternion::QVRotation(const Quaternion& q, const Vector3& v) const
//{
//	Quaternion t;
//
//	t = q.Mul(q, v);
//	t = t * q.Inverse();
//
//	return Vector3 (t.x, t.y, t.z);
//}

/**
*@note 绕向量旋转
*@param angle 旋转的角度
*@param v 三维向量
*@return 四元数
*/
inline Quaternion& Quaternion::SetRotate(double angle, const Vector3& v)
{
	return SetRotate(angle, v.x, v.y, v.z);
}

/**
*@note 绕向量旋转
*@param angle 旋转的角度
*@param v 三维向量
*@return 四元数
*/
inline Quaternion& Quaternion::Rotate(double angle, const Vector3& v)
{
	return Rotate(angle, v.x, v.y, v.z);
}

/**
*@note 绕向量旋转
*@param v 三维向量
*@return 四元数
*/
inline Quaternion& Quaternion::SetRotate(const Vector3& v)
{
	return SetRotate(v.x, v.y, v.z);
}

/**
*@note 绕向量旋转
*@param angle 旋转的角度
*@param v 三维向量
*@return 四元数
*/
inline Quaternion& Quaternion::Rotate(const Vector3& v)
{
	return Rotate(v.x, v.y, v.z);
}

/**
*@note 绕向量旋转
*@param angle 旋转的角度
*@param _x 向量分量
*@param _y 向量分量
*@param _z 向量分量
*@return 四元数
*/
inline Quaternion& Quaternion::SetRotate(double angle, double _x, double _y, double _z)
{
	double s = SinD(angle / 2.0f);
	double c = CosD(angle / 2.0f);

	x = _x * s;
	y = _y * s;
	z = _z * s;
	w = c;
	//|x y z w|=|_x*sin(angle/2)  _y*sin(angle/2)  _z*sin(angle/2)  cos(angle/2)|
	//将以上向量单位化
	Normalize();
	return *this;                   //返回单位化后的四元组向量
}
/**
*@note 绕向量旋转
*@param angle 旋转的角度
*@param _x 向量分量
*@param _y 向量分量
*@param _z 向量分量
*@return 四元数
*/
inline Quaternion& Quaternion::Rotate(double angle, double _x, double _y, double _z)
{
	Quaternion tmp;
	tmp.SetRotate(angle, _x, _y, _z);
	Mul(*this, tmp);
	return *this;
}
/**
*@note 绕向量旋转
*@param rx 向量分量
*@param ry 向量分量
*@param rz 向量分量
*@return 四元数
*/
inline Quaternion& Quaternion::SetRotate(double rx, double ry, double rz)
{
	Quaternion qy, qz;
	SetRotate(rx, 1.0f, 0.0f, 0.0f);
	qy.SetRotate(ry, 0.0f, 1.0f, 0.0f);
	qz.SetRotate(rz, 0.0f, 0.0f, 1.0f);
	Mul(*this, qy);
	Mul(*this, qz);
	return *this;
}
/**
*@note 绕向量旋转
*@param rx 向量分量
*@param ry 向量分量
*@param rz 向量分量
*@return 四元数
*/
inline Quaternion& Quaternion::Rotate(double rx, double ry, double rz)
{
	Quaternion tmp;
	tmp.SetRotate(rx, ry, rz);
	Mul(*this, tmp);
	return *this;
}
/**
*@note 从欧拉角计算四元数
*@return 四元数
*/
inline Quaternion& Quaternion::FromEulerAngle(double rx, double ry, double rz, EulerAnglesSeq seq /* = EulerAnglesSeq::SEQ_ZXY */)
{
	switch(seq)
	{
	case SEQ_ZXY:
		{
			return FromEulerAngleZXY(rz, rx, ry);
		}
		break;
	case SEQ_XYZ:
		{
			return FromEulerAngleXYZ(rx, ry, rz);
		}
		break;
	default:
		// error
		throw;
	}

}
/**
*@note 从欧拉角计算四元数，矩阵顺序为ZXY
*@return 四元数
*/
inline Quaternion& Quaternion::FromEulerAngleZXY(double rz, double rx, double ry)
{
	//Quaternion qx, qz;
	//SetRotate ( ry, 0.0f, 1.0f, 0.0f);
	//qx.SetRotate( rx, 1.0f, 0.0f, 0.0f);
	//qz.SetRotate( rz, 0.0f, 0.0f, 1.0f);
	//Mul(*this, qx);
	//Mul(*this, qz);
	//return *this;

	Quaternion qx, qy;
	SetRotate ( rz, 0.0f, 0.0f, 1.0f);
	qx.SetRotate( rx, 1.0f, 0.0f, 0.0f);
	qy.SetRotate( ry, 0.0f, 1.0f, 0.0f);
	Mul(*this, qx);
	Mul(*this, qy);
	return *this;

}
/**
*@note 从欧拉角计算四元数，矩阵顺序为XYZ
*@return 四元数
*/
inline Quaternion& Quaternion::FromEulerAngleXYZ(double rx, double ry, double rz)
{
	Quaternion qy, qz;
	SetRotate( rx, 1.0f, 0.0f, 0.0f );
	qy.SetRotate( ry, 0.0f, 1.0f, 0.0f );
	qz.SetRotate( rz, 0.0f, 0.0f, 1.0f );
	Mul(*this, qy);
	Mul(*this, qz);
	
	return *this;
}
/**
*@note 从四元数计算欧拉角
*@return 三维向量
*/
inline Vector3 Quaternion::ToEulerAngle(EulerAnglesSeq seq /* = EulerAnglesSeq::SEQ_ZXY */) const
{
	switch(seq)
	{
	case SEQ_ZXY:
		{
			return ToEulerAngleZXY();
		}
		break;
	case SEQ_XYZ:
		{
			return ToEulerAngleXYZ();
		}
		break;
	default:
		// error
		throw;
	}

}
/**
*@note 从四元数计算欧拉角，矩阵顺序为ZXY
*@return 三维向量
*/
inline Vector3 Quaternion::ToEulerAngleZXY() const
{
	// by y.w. , May 2006.
	double rx, ry, rz;

	//if ( ( w * x + y * z ) > 0.4995 )
	//{
	//	// singularity problem, let's walk around the gimbal-lock.
	//	rx = 90.0f;
	//	ry = 0.0f;
	//	rz = 2 * ATanD2( y, w );
	//}
	//else if ( ( w * x + y * z ) < - 0.4995 )
	//{
	//	// singularity problem, let's walk around the gimbal-lock.
	//	rx = -90.0f;
	//	ry = 0.0f;
	//	rz = -2 * ATanD2( y, w );
	//}
	//else
	{
		// normal case
		rx = ASinD( 2 * w * x + 2 * y * z);
		ry = -ATanD2(2 * x * z - 2 * w * y , 1 - 2 * x * x - 2 * y * y);
		rz = -ATanD2(2 * x * y - 2 * w * z , 1 - 2 * x * x - 2 * z * z);
	}

	return Vector3(rx, ry, rz);
}
/**
*@note 从四元数计算欧拉角，矩阵顺序为XYZ
*@return 三维向量
*/
inline Vector3 Quaternion::ToEulerAngleXYZ() const
{
	double rx, ry, rz;
	rx = -ATanD2(2 * y * z - 2 * w * x , 1 - 2 * x * x - 2 * y * y);
	ry = ASinD(2 * w * y + 2 * x * z);
	rz = -ATanD2(2 * x * y - 2 * w * z , 1 - 2 * y * y - 2 * z * z);

	return Vector3(rx, ry, rz);
}

/**
*@note 从绕任意轴的旋转计算四元数
*@return 四元数
*/
inline void Quaternion::FromAngleAxis(const double& fAngle, const Vector3& kAxis) 
{
	double ss, cc;
	ss = SinD(fAngle/2);
	cc = CosD(fAngle/2);
	Vector3 v;
	v.Normalize(kAxis);
	this->w = cc;
	this->x = v.x * ss;
	this->y = v.y * ss;
	this->z = v.z * ss;

	//this->Normalize();
	return;
}

/**
*@note 从四元数计算绕任意轴的旋转
*@return 四元数
*/
inline void Quaternion::ToAngleAxis (double& fAngle, Vector3& kAxis) const
{
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	double fSqrLength = x*x+y*y+z*z;
	if ( fSqrLength > 0.0f )
	{
		fAngle = 2.0f*ACosD(w);
		double fInvLength = 1.0f/sqrt(fSqrLength);
		kAxis.x = x*fInvLength;
		kAxis.y = y*fInvLength;
		kAxis.z = z*fInvLength;
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do
		fAngle = 0.0f;
		kAxis.x = 1.0f;
		kAxis.y = 0.0f;
		kAxis.z = 0.0f;
	}
}

/**
*@note 四元数的点积
*@return 点乘积
*/
inline double Quaternion::Dot (const Quaternion& rkQ) const
{
	return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
}

/**
*@note 四元数的范数
*@return
*/
inline double Quaternion::Norm () const
{
	return w*w+x*x+y*y+z*z;
}

inline Quaternion Quaternion::operator* (double fScalar) const
{
	return Quaternion(fScalar*x,fScalar*y,fScalar*z,fScalar*w);
}

/**
*@note 四元数的逆运算
*@return 四元数
*/
inline Quaternion Quaternion::Inverse () const
{
	double fNorm = w*w+x*x+y*y+z*z;
	if ( fNorm > 0.0f )
	{
		double fInvNorm = 1.0f/fNorm;
		return Quaternion(-x*fInvNorm,-y*fInvNorm,-z*fInvNorm,w*fInvNorm);
	}
	else
	{
		// return an invalid result to flag the error
		//for debug
		//CString str;
		//str.Format("%d",fNorm);
		//AfxMessageBox(str);
		//AfxMessageBox("inverse error");
		return IDENTITY;//ZERO;
	}
}

/**
*@note 两个四元数的线性组合
*@return 四元数
*/
inline Quaternion Quaternion::nlerp(double fT, const Quaternion& rkP, 
							 const Quaternion& rkQ, bool shortestPath)
{
	Quaternion result;
	double fCos = rkP.Dot(rkQ);
	if (fCos < 0.0f && shortestPath)
	{
		result = rkP + ((-rkQ) - rkP) * fT;
	}
	else
	{
		result = rkP +  (rkQ - rkP) * fT;
	}
	result.Normalize();
	return result;
}

/**
*@note 将当前的四元数转换
*@return 四元数
*/
inline Quaternion Quaternion::TransitionFromCurrentTo(const Quaternion rkQ)
{
	Quaternion returnQ;
	this->Invert();
	returnQ = (*this)*rkQ;
	return returnQ;
}

/**
*@note 从四元数计算旋转矩阵
*/
inline void Quaternion::ToRotationMatrix (Matrix3& kRot) const
{
	double fTx  = 2.0f *x;
	double fTy  = 2.0f *y;
	double fTz  = 2.0f *z;
	double fTwx = fTx*w;
	double fTwy = fTy*w;
	double fTwz = fTz*w;
	double fTxx = fTx*x;
	double fTxy = fTy*x;
	double fTxz = fTz*x;
	double fTyy = fTy*y;
	double fTyz = fTz*y;
	double fTzz = fTz*z;

	kRot.m[0][0] = 1.0f -(fTyy+fTzz);
	kRot.m[0][1] = fTxy-fTwz;
	kRot.m[0][2] = fTxz+fTwy;
	kRot.m[1][0] = fTxy+fTwz;
	kRot.m[1][1] = 1.0f -(fTxx+fTzz);
	kRot.m[1][2] = fTyz-fTwx;
	kRot.m[2][0] = fTxz-fTwy;
	kRot.m[2][1] = fTyz+fTwx;
	kRot.m[2][2] = 1.0f -(fTxx+fTyy);
}

/**
*@note 从旋转矩阵计算四元数
*/
inline void Quaternion::FromRotationMatrix (const Matrix3& kRot)
{
	// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
	// article "Quaternion Calculus and Fast Animation".

	double fTrace = kRot.m[0][0]+kRot.m[1][1]+kRot.m[2][2];
	double fRoot;

	if ( fTrace > 0.0 )
	{
		// |w| > 1/2, may as well choose w > 1/2
		fRoot = sqrt(fTrace + 1.0f);  // 2w
		w = 0.5f*fRoot;
		fRoot = 0.5f/fRoot;  // 1/(4w)
		x = (kRot.m[2][1]-kRot.m[1][2])*fRoot;
		y = (kRot.m[0][2]-kRot.m[2][0])*fRoot;
		z = (kRot.m[1][0]-kRot.m[0][1])*fRoot;
	}
	else
	{
		// |w| <= 1/2
		static size_t s_iNext[3] = { 1, 2, 0 };
		size_t i = 0;
		if ( kRot.m[1][1] > kRot.m[0][0] )
			i = 1;
		if ( kRot.m[2][2] > kRot.m[i][i] )
			i = 2;
		size_t j = s_iNext[i];
		size_t k = s_iNext[j];

		fRoot = sqrt(kRot.m[i][i]-kRot.m[j][j]-kRot.m[k][k] + 1.0f);
		double* apkQuat[3] = { &x, &y, &z };
		*apkQuat[i] = 0.5f*fRoot;
		fRoot = 0.5f/fRoot;
		w = (kRot.m[k][j]-kRot.m[j][k])*fRoot;
		*apkQuat[j] = (kRot.m[j][i]+kRot.m[i][j])*fRoot;
		*apkQuat[k] = (kRot.m[k][i]+kRot.m[i][k])*fRoot;
	}
}

/**
*@note 从坐标轴计算四元数
*/
inline void Quaternion::FromAxes (const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
{
	Matrix3 kRot;

	kRot.m[0][0] = xaxis.x;
	kRot.m[1][0] = xaxis.y;
	kRot.m[2][0] = xaxis.z;

	kRot.m[0][1] = yaxis.x;
	kRot.m[1][1] = yaxis.y;
	kRot.m[2][1] = yaxis.z;

	kRot.m[0][2] = zaxis.x;
	kRot.m[1][2] = zaxis.y;
	kRot.m[2][2] = zaxis.z;

	FromRotationMatrix(kRot);

}
