/** @file 
* @brief  ��ѧ��
* @author �Ժ��
* @date 2008-10-29
* @version 0.1
*
* ��ά����
*/

/**
*@note Constructors		                                
*/ 
inline Matrix3::Matrix3()
{}

/**
*@note ����otherΪ��ʼ��ַ�����鸳ֵ��3Ψ����M[9]       
*param other ��ʼ��ַ
*/

inline Matrix3::Matrix3(const double* other)           
{
	for(int i = 0; i < 9; i++) M[i] = other[i];
}

/**
*@��9��double������ֵ��Ψ����M[9]                      
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
*@note 3Ψ����other��ֵ��M[9]         
*@param other ��ά����
*/
inline Matrix3::Matrix3(const Matrix3& other)
{
	for(int i = 0; i < 9; i++) M[i] = other.M[i];
}

/**
*@note 3Ψ����other��ֵ��M[9],ͬʱ���ظþ���    
*@param other ��ά����
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
*@note �趨Ϊ��λ����
*@return ��ά����
*/
inline Matrix3& Matrix3::SetIdentity()
{
	/*����Ϊ��
	        | 1   0  0|
	        | 0   1  0|
	        | 0   0  1|
	                    */

	for(int i = 0; i < 9; i++) M[i] = Matrix3::Identity_Matrix[i];
	return *this;
}

/**
*@note �������ֵȫ��ֵΪ0    
*@return ��ά����
*/
inline Matrix3& Matrix3::SetZero()
{
	/*����任Ϊ��
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
*@note �����������  
*@param m1 ��˵���ά����1
*@param m2 ��˵���ά����2
*/
inline Matrix3& Matrix3::Mul(const Matrix3& m1, const Matrix3& m2)
{
	const double *b = m1.M;              //����m1����b
	const double *a = m2.M;              //����m2����a
	double *prod = M;

	/* 
	         |a[0]  a[1]  a[2]|   |b[0] b[1] b[2]|
    prod[9]= |a[3]  a[4]  a[5]| * |b[3] b[4] b[5]|
	         |a[6]  a[7]  a[8]|   |b[6] b[7] b[8]|    */

	for(int i = 0; i < 3; i++)          //ִ��a[9]��b[9]���,�������prod[9]��
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
*@note ����������  
*@param f �������˵���
*@return ��ά����
*/

inline Matrix3& Matrix3::Mul(double f)
{
	/* 
	         |M[0]  M[1]  M[2]|   
	   M[9]= |M[3]  M[4]  M[5]| * f
	         |M[6]  M[7]  M[8]|       */

	for(int i = 0; i < 9; i++) M[i] *=f;  //ִ�����
	return *this;                         //����
}
/**
*@note ����������  
*@param other ��ά����
*@param f �������˵���
*@return ��ά����
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
*@ ���������� 
*@param f ����������
*@return ��ά����
*/
inline Matrix3& Matrix3::Div(double f)
{
	/* 
	      |M[0]  M[1]  M[2]|   
	M[9]= |M[3]  M[4]  M[5]| *(1/ f)
	      |M[6]  M[7]  M[8]|             */
	f = 1.0f / f;
	for(int i = 0; i < 9; i++) M[i] *=f; //���Ե���
	return *this;                        //����
}
/**
*@note ����������   
*@param other ��ά����
*@param f ������������
*@return ��ά����
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
*@note ����任  
*@param tx ������ȱ任����
*@param ty ������ȱ任����
*@return ��ά����
*/
inline Matrix3& Matrix3::Translate(double tx, double ty)
{
	/* 
	      |M[0]      M[1]      M[2]|   
	M[9]= |M[3]      M[4]      M[5]| 
	      |M[0] * tx + M[3] * ty + M[6]  M[7]  M[8]   M[1] * tx + M[4] * ty + M[7]      M[2] * tx + M[5] * ty + M[8]   */
	M[6] = M[0] * tx + M[3] * ty + M[6];     //������M[9]�ĵ�һ�к͵ڶ��зֱ����tx��ty,Ȼ������������,�õ��µľ���
	M[7] = M[1] * tx + M[4] * ty + M[7];
	M[8] = M[2] * tx + M[5] * ty + M[8];
	return *this;                            //����
}
/**
*@note ����任  
*@param tx ������ȱ任����
*@param ty ������ȱ任����
*@return ��ά����
*/
inline Matrix3& Matrix3::SetTranslate(double tx, double ty)
{
	SetIdentity();
	M[6] = tx;                              //��tx��ֵ��M[6]
	M[7] = ty;                              //��ty��ֵ��M[7]
	return *this;                           //�����µľ���
}
/**
*@note �任����ĵ�һ������  
*@param sx ���ȱ任����һ
*@param sy ���ȱ任������
*@return ��ά����
*/
inline Matrix3& Matrix3::Scale(double sx, double sy)
{
	/* 
	      |M[0]*sx  M[1]*sx  M[2]*sx|   
	M[9]= |M[3]*sy  M[4]*sy  M[5]*sy| 
       	  |M[6]     M[7]     M[8]   |             */
	M[0] *= sx; M[3] *= sy;                //����ĵ�һ�к͵ڶ��зֱ����sx��sy
	M[1] *= sx; M[4] *= sy;
	M[2] *= sx; M[5] *= sy;
	return *this;                          //�����µľ���
}
/**
*@note ��ά���ž���
*@param sx ���ȱ任����һ
*@param sy ���ȱ任������
*@return ��ά����
*/
inline Matrix3& Matrix3::SetScale(double sx, double sy)
{
	/*����任Ϊ��
	             | sx  0  0|
				 | 0  sy  0|
				 | 0   0  1|
				              */
	M[0] = sx; M[4] = sy; M[8] = 1.0f;
	M[1] = M[2] = M[3] = M[5] = M[6] = M[7] = 0.0f;
	return *this;                         //����
}
/**
*@note ��ά��ת�任    
*@param r ��ת�Ļ���
*@return ��ά����
*/
inline Matrix3& Matrix3::Rotate(double r) //r����Ϊ��ת�Ļ���
{
	/*tmp������Ϊ��
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
	Mul(tmp);     /*���ά��ת������ˣ�
	                  |x~|   | cos(r) -sin(r)  0|   |x|
					  |y~| = | sin(r)  cos(r)  0| * |y|
					  |1 |   |   0      0      1|   |1|
					                                     */
	return *this;                      //�����µľ���
}

/**
*@note �趨��ά��ת����    
*@param r ��ת�ĽǶ�
*@return ��ά����
*/

inline Matrix3& Matrix3::SetRotate(double r)
{
	/*��ά��ת������Ϊ��
	            | cos(r) -sin(r)  0|
	            | sin(r)  cos(r)  0|
	            |   0      0      1|
	                                 */
	double c = CosD(r), s = SinD(r);
	Matrix3 tmp;
	SetIdentity();                                    //�趨Ϊ��λ����
	M[0] = c;
	M[1] = -s;
	M[3] = s;
	M[4] = c;
	return *this;                                    //�����µľ���
}
/**
*@note ��x,y,z����ת�õ���ת���� 
*@param fYAngle ��Y����ת�ĽǶ�
*@param fPAngle ��X����ת�ĽǶ�
*@param fRAngle ��Z����ת�ĽǶ�
*@return ��ά��ת����
*/
/************************************************************************/
inline void Matrix3::FromEulerAnglesZYX (const double& fYAngle, const double& fPAngle, const double& fRAngle)
{
	double fCos, fSin;
    /*��Z����ת����ת����
                 	| fCos  -fSin  0|
	         kZmat= | fSin  fCos   0|
	                |   0    0     1|
					                    */	                     
	fCos = CosD(fYAngle);
	fSin = SinD(fYAngle);
	Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

	/*��Y����ת����ת����
	                | fCos   0 -fSin|
	         kYmat= |  0     1    0 |
	                |-fSin   0  fCos|
	                                   */
	fCos = CosD(fPAngle);
	fSin = SinD(fPAngle);
	Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

	/*��X����ת����ת����
	               | 1      0     0|
	        kXmat= | 0      0  fCos|
	               | 0    fSin fCos|
	                               */
	fCos = CosD(fRAngle);
	fSin = SinD(fRAngle);
	Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

	*this = kZMat*(kYMat*kXMat);        //����ͬʱ��x,y,z��ת����ת����
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


/****************************** ���09.05 *******************************************/
//ADD by LL
//�ҳ�
inline void Matrix3::PostMultiply( Vector3 &v, Vector3 &Dst )
{
	Dst.x = M[0] * v.x + M[1] * v.y + M[2] * v.z;
	Dst.y = M[3] * v.x + M[4] * v.y + M[5] * v.z;
	Dst.z = M[6] * v.x + M[7] * v.y + M[8] * v.z;
}
//���
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
/****************************** ���09.05 *******************************************/