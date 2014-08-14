/** @file 
* @brief  数学库
* @author 赵洪德
* @date 2008-10-29
* @version 0.1
*
* 三维矩阵
*/

/**
*@note Constructors		                                
*/ 
inline Matrix3::Matrix3()
{}

/**
*@note 将以other为起始地址的数组赋值给3唯矩阵M[9]       
*param other 起始地址
*/

inline Matrix3::Matrix3(const double* other)           
{
	for(int i = 0; i < 9; i++) M[i] = other[i];
}

/**
*@将9个double变量赋值给唯矩阵M[9]                      
*/
inline Matrix3::Matrix3(const double f0, const double f1, const double f2,
						const double f3, const double f4, const double f5,
						const double f6, const double f7, const double f8)
{
	M[0] = f0;
	M[1] = f1;
	M[2] = f2;
	M[3] = f3;
	M[4] = f4;
	M[5] = f5;
	M[6] = f6;
	M[7] = f7;
	M[8] = f8;
}

/**
*@note 3唯矩阵other赋值给M[9]         
*@param other 三维矩阵
*/
inline Matrix3::Matrix3(const Matrix3& other)
{
	for(int i = 0; i < 9; i++) M[i] = other.M[i];
}

/**
*@note 3唯矩阵other赋值给M[9],同时返回该矩阵    
*@param other 三维矩阵
*/
inline Matrix3& Matrix3::operator=(const Matrix3& other)
{
	for(int i = 0; i < 9; i++) M[i] = other.M[i];
	return *this;
}
/**
*@note assign 
*/
inline void Matrix3::Assign(const Matrix3& other)
{
	for(int i = 0; i < 9; i++) M[i] = other.M[i];
}
/**
*@note assign 
*/
inline void Matrix3::Assign(const double* other)
{
	for(int i = 0; i < 9; i++) M[i] = other[i];
}
/**
*@note operator
*/
inline Matrix3::operator const double*() const
{
	return M;
}
/**
*@note operator
*/
inline Matrix3::operator double*()
{
	return M;
}

/**
*@note 设定为单位矩阵
*@return 三维矩阵
*/
inline Matrix3& Matrix3::SetIdentity()
{
	/*矩阵为：
	        | 1   0  0|
	        | 0   1  0|
	        | 0   0  1|
	                    */

	for(int i = 0; i < 9; i++) M[i] = Matrix3::Identity_Matrix[i];
	return *this;
}

/**
*@note 将矩阵的值全部值为0    
*@return 三维矩阵
*/
inline Matrix3& Matrix3::SetZero()
{
	/*矩阵变换为：
	             | 0   0  0|
	             | 0   0  0|
               	 | 0   0  0|
	                         */
	for(int i = 0; i < 9; i++) M[i] = 0.0f;
	return *this;
}

inline Matrix3& Matrix3::Mul(const Matrix3& other)
{
	Matrix3 tmp;
	tmp.Assign(*this);
	Mul(tmp, other);
	return *this;
}
/**
*@note 两个矩阵相乘  
*@param m1 相乘的三维矩阵1
*@param m2 相乘的三维矩阵2
*/
inline Matrix3& Matrix3::Mul(const Matrix3& m1, const Matrix3& m2)
{
	const double *b = m1.M;              //矩阵m1赋给b
	const double *a = m2.M;              //矩阵m2赋给a
	double *prod = M;

	/* 
	         |a[0]  a[1]  a[2]|   |b[0] b[1] b[2]|
    prod[9]= |a[3]  a[4]  a[5]| * |b[3] b[4] b[5]|
	         |a[6]  a[7]  a[8]|   |b[6] b[7] b[8]|    */

	for(int i = 0; i < 3; i++)          //执行a[9]和b[9]相乘,结果存在prod[9]中
	{
		double a0 = a[i];
		double a1 = a[i + 3];
		double a2 = a[i + 6];
		prod[i]     = a0 * b[0] + a1 * b[1] + a2 * b[2];
		prod[i + 3] = a0 * b[3] + a1 * b[4] + a2 * b[5];
		prod[i + 6] = a0 * b[6] + a1 * b[7] + a2 * b[8];
	}
	return *this;
}
/**
*@note 矩阵和数相乘  
*@param f 与矩阵相乘的数
*@return 三维矩阵
*/

inline Matrix3& Matrix3::Mul(double f)
{
	/* 
	         |M[0]  M[1]  M[2]|   
	   M[9]= |M[3]  M[4]  M[5]| * f
	         |M[6]  M[7]  M[8]|       */

	for(int i = 0; i < 9; i++) M[i] *=f;  //执行相乘
	return *this;                         //返回
}
/**
*@note 矩阵和数相乘  
*@param other 三维矩阵
*@param f 与矩阵相乘的数
*@return 三维矩阵
*/

inline Matrix3& Matrix3::Mul(const Matrix3& other, double f)
{
	const double* m = other.M;
	for(int i = 0; i < 9; i++) M[i] = m[i] * f;
	return *this;
}

inline Vector3 Matrix3::Mul( const Vector3 v )
{
	double x,y,z;

	x = M[0] * v.x + M[1] * v.y + M[2] * v.z;
	y = M[3] * v.x + M[4] * v.y + M[5] * v.z;
	z = M[6] * v.x + M[7] * v.y + M[8] * v.z;

	return Vector3(x, y, z);
}

/**
*@ 矩阵和数相除 
*@param f 除数浮点数
*@return 三维矩阵
*/
inline Matrix3& Matrix3::Div(double f)
{
	/* 
	      |M[0]  M[1]  M[2]|   
	M[9]= |M[3]  M[4]  M[5]| *(1/ f)
	      |M[6]  M[7]  M[8]|             */
	f = 1.0f / f;
	for(int i = 0; i < 9; i++) M[i] *=f; //乘以倒数
	return *this;                        //返回
}
/**
*@note 矩阵和数相除   
*@param other 三维矩阵
*@param f 与矩阵相除的数
*@return 三维矩阵
*/
inline Matrix3& Matrix3::Div(const Matrix3& other, double f)
{
	f = 1.0f / f;
	const double* m = other.M;
	for(int i = 0; i < 9; i++) M[i] = m[i] * f;
	return *this;
}

/**
*@Operators                                  
*/ 

inline Matrix3& Matrix3::operator*=(const Matrix3& other)
{
	Matrix3 tmp;
	tmp.Assign(*this);
	Mul(tmp, other);
	return *this;
}
/**
*@Operators                                  
*/

inline Matrix3 Matrix3::operator*(const Matrix3& other) const
{
	Matrix3 tmp;
	tmp.Mul(*this, other);
	return tmp;
}

/**
*@note 矩阵变换  
*@param tx 矩阵初等变换参数
*@param ty 矩阵初等变换参数
*@return 三维矩阵
*/
inline Matrix3& Matrix3::Translate(double tx, double ty)
{
	/* 
	      |M[0]      M[1]      M[2]|   
	M[9]= |M[3]      M[4]      M[5]| 
	      |M[0] * tx + M[3] * ty + M[6]  M[7]  M[8]   M[1] * tx + M[4] * ty + M[7]      M[2] * tx + M[5] * ty + M[8]   */
	M[6] = M[0] * tx + M[3] * ty + M[6];     //将矩阵M[9]的第一行和第二行分别乘以tx和ty,然后与第三行相加,得到新的矩阵
	M[7] = M[1] * tx + M[4] * ty + M[7];
	M[8] = M[2] * tx + M[5] * ty + M[8];
	return *this;                            //返回
}
/**
*@note 矩阵变换  
*@param tx 矩阵初等变换参数
*@param ty 矩阵初等变换参数
*@return 三维矩阵
*/
inline Matrix3& Matrix3::SetTranslate(double tx, double ty)
{
	SetIdentity();
	M[6] = tx;                              //将tx赋值给M[6]
	M[7] = ty;                              //将ty赋值给M[7]
	return *this;                           //返回新的矩阵
}
/**
*@note 变换矩阵的第一、二行  
*@param sx 初等变换参数一
*@param sy 初等变换参数二
*@return 三维矩阵
*/
inline Matrix3& Matrix3::Scale(double sx, double sy)
{
	/* 
	      |M[0]*sx  M[1]*sx  M[2]*sx|   
	M[9]= |M[3]*sy  M[4]*sy  M[5]*sy| 
       	  |M[6]     M[7]     M[8]   |             */
	M[0] *= sx; M[3] *= sy;                //矩阵的第一行和第二行分别乘以sx和sy
	M[1] *= sx; M[4] *= sy;
	M[2] *= sx; M[5] *= sy;
	return *this;                          //返回新的矩阵
}
/**
*@note 二维缩放矩阵
*@param sx 初等变换参数一
*@param sy 初等变换参数二
*@return 三维矩阵
*/
inline Matrix3& Matrix3::SetScale(double sx, double sy)
{
	/*矩阵变换为：
	             | sx  0  0|
				 | 0  sy  0|
				 | 0   0  1|
				              */
	M[0] = sx; M[4] = sy; M[8] = 1.0f;
	M[1] = M[2] = M[3] = M[5] = M[6] = M[7] = 0.0f;
	return *this;                         //返回
}
/**
*@note 二维旋转变换    
*@param r 旋转的弧度
*@return 三维矩阵
*/
inline Matrix3& Matrix3::Rotate(double r) //r定义为旋转的弧度
{
	/*tmp矩阵定义为：
	               | cos(r) -sin(r)  0|
				   | sin(r)  cos(r)  0|
				   |   0      0      1|
				                        */
	double c = CosD(r), s = SinD(r);
	Matrix3 tmp;
	tmp.SetIdentity();
	tmp.M[0] = c;
	tmp.M[1] = -s;
	tmp.M[3] = s;
	tmp.M[4] = c;
	Mul(tmp);     /*与二维旋转矩阵相乘：
	                  |x~|   | cos(r) -sin(r)  0|   |x|
					  |y~| = | sin(r)  cos(r)  0| * |y|
					  |1 |   |   0      0      1|   |1|
					                                     */
	return *this;                      //返回新的矩阵
}

/**
*@note 设定二维旋转矩阵    
*@param r 旋转的角度
*@return 三维矩阵
*/

inline Matrix3& Matrix3::SetRotate(double r)
{
	/*二维旋转矩阵定义为：
	            | cos(r) -sin(r)  0|
	            | sin(r)  cos(r)  0|
	            |   0      0      1|
	                                 */
	double c = CosD(r), s = SinD(r);
	Matrix3 tmp;
	SetIdentity();                                    //设定为单位矩阵
	M[0] = c;
	M[1] = -s;
	M[3] = s;
	M[4] = c;
	return *this;                                    //返回新的矩阵
}
/**
*@note 绕x,y,z轴旋转得到旋转矩阵 
*@param fYAngle 绕Y轴旋转的角度
*@param fPAngle 绕X轴旋转的角度
*@param fRAngle 绕Z轴旋转的角度
*@return 三维旋转矩阵
*/
/************************************************************************/
inline void Matrix3::FromEulerAnglesZYX (const double& fYAngle, const double& fPAngle, const double& fRAngle)
{
	double fCos, fSin;
    /*绕Z轴旋转的旋转矩阵：
                 	| fCos  -fSin  0|
	         kZmat= | fSin  fCos   0|
	                |   0    0     1|
					                    */	                     
	fCos = CosD(fYAngle);
	fSin = SinD(fYAngle);
	Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

	/*绕Y轴旋转的旋转矩阵：
	                | fCos   0 -fSin|
	         kYmat= |  0     1    0 |
	                |-fSin   0  fCos|
	                                   */
	fCos = CosD(fPAngle);
	fSin = SinD(fPAngle);
	Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

	/*绕X轴旋转的旋转矩阵：
	               | 1      0     0|
	        kXmat= | 0      0  fCos|
	               | 0    fSin fCos|
	                               */
	fCos = CosD(fRAngle);
	fSin = SinD(fRAngle);
	Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

	*this = kZMat*(kYMat*kXMat);        //返回同时绕x,y,z旋转的旋转矩阵
}
inline void Matrix3::FromEulerAnglesZXY(const Vector3& vec)
{
	double cx, cy, cz, sx, sy, sz;
	cx = CosD(vec.x);
	sx = SinD(vec.x);
	cy = CosD(vec.y);
	sy = SinD(vec.y);
	cz = CosD(vec.z);
	sz = SinD(vec.z);

	M[0] = cy * cz - sx * sy * sz;
	M[1] = - cx * sz;
	M[2] = sx * cy * sz + sy * cz;
	M[3] = cy * sz + sx * sy * cz;
	M[4] = cx * cz;
	M[5] = sy * sz - sx * cy * cz;
	M[6] = - cx * sy;
	M[7] = sx;
	M[8] = cx * cy;
}

inline Vector3 Matrix3::ToEulerAnglesZXY()
{
	double x, y, z;
	x = ASinD(M[7]);
	y = ATanD2(-M[6], M[8]);
	z = ATanD2(-M[1], M[4]);
	
	return Vector3(x, y, z);
}


/****************************** 刘璐09.05 *******************************************/
//ADD by LL
//右乘
inline void Matrix3::PostMultiply( Vector3 &v, Vector3 &Dst )
{
	Dst.x = M[0] * v.x + M[1] * v.y + M[2] * v.z;
	Dst.y = M[3] * v.x + M[4] * v.y + M[5] * v.z;
	Dst.z = M[6] * v.x + M[7] * v.y + M[8] * v.z;
}
//左乘
inline void Matrix3::PreMultiply( Vector3 &v, Vector3 &Dst )
{
	Dst.x = v.x * M[0] + v.y * M[3] + v.z * M[6];
	Dst.y = v.x * M[1] + v.y * M[4] + v.z * M[7];
	Dst.z = v.x * M[2] + v.y * M[5] + v.z * M[8];
}

inline bool Matrix3::IsTranspose( Matrix3 &other )
{
	for( int i=0; i<3; i++ )
		for( int j=0; j<3; j++ )
			if( M[i*3+j] != other.M[j*3+i] )
				return false;
	return true;
}	
/*this += other*/
inline Matrix3& Matrix3::Add( Matrix3 &other )
{
	for( int i=0; i<9; i++ )
		M[i] = other.M[i] + M[i];
	return *this;
}

/*this = M2 + M*/
inline Matrix3& Matrix3::Add( Matrix3 &M1, Matrix3 &M2 )
{
	for( int i=0; i<9; i++ )
		M[i] = M2.M[i] + M1.M[i];
	return *this;
}

/*this -= other2*/
inline Matrix3& Matrix3::Subtract( Matrix3 &other )
{
	for( int i=0; i<9; i++ )
		M[i] = M[i] - other.M[i];
	return *this;
}

/*this = M - M2*/
inline Matrix3& Matrix3::Subtract( Matrix3 &M1, Matrix3 &M2 )
{
	for( int i=0; i<9; i++ )
		M[i] = M1.M[i] - M2.M[i];
	return *this;
}

inline void Matrix3::SetFromOuterProduct( Vector3 &v1, Vector3 &v2 )
{
	M[0] = v1.x * v2.x; M[1] = v1.x * v2.y; M[2] = v1.x * v2.z;
	M[3] = v1.y * v2.x; M[4] = v1.y * v2.y; M[5] = v1.y * v2.z;
	M[6] = v1.z * v2.x; M[7] = v1.z * v2.y; M[8] = v1.z * v2.z;
}

inline Matrix3& Matrix3::Invert(const Matrix3& other)
{
	Matrix3 a;
	double d;
	a.CofactorMat(other).Transpose();
	d=Determinant(other);
	return this->Mul(a,1.0/d);
}

inline Matrix3& Matrix3::CofactorMat(const Matrix3 &other)
{
	this->M[0]=other.M[4]*other.M[8]-other.M[5]*other.M[7];
	this->M[1]=other.M[5]*other.M[6]-other.M[3]*other.M[8];
	this->M[2]=other.M[3]*other.M[7]-other.M[4]*other.M[6];

	this->M[3]=other.M[2]*other.M[7]-other.M[1]*other.M[8];
	this->M[4]=other.M[0]*other.M[8]-other.M[2]*other.M[6];
	this->M[5]=other.M[1]*other.M[6]-other.M[0]*other.M[7];

	this->M[6]=other.M[1]*other.M[5]-other.M[2]*other.M[4];
	this->M[7]=other.M[2]*other.M[3]-other.M[0]*other.M[5];
	this->M[8]=other.M[0]*other.M[4]-other.M[1]*other.M[3];
	
	return *this;
}

inline double Matrix3::Determinant(const Matrix3 &other)
{
	double ans;
	ans=other.M[0]*other.M[4]*other.M[8]+other.M[2]*other.M[3]*other.M[7]+other.M[1]*other.M[5]*other.M[6]-other.M[2]*other.M[4]*other.M[6]-other.M[1]*other.M[3]*other.M[8]-other.M[0]*other.M[5]*other.M[7];
	return ans;
}
/****************************** 刘璐09.05 *******************************************/