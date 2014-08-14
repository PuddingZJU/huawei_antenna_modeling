/** @file 
* @brief  ��ѧ��
* @author �Ժ��
* @date 2008-10-29
* @version 0.1
*
* ��ά����
*/


#ifndef _mathematics_h_
#error "Dont include Matrix4 directly!!! Use Mathematics.h instead."
#endif

/**
*@note Constructors                                 
*/ 
inline Matrix4::Matrix4()
{}
/**
*@note ����other��ά����ֵ��4Ψ����M[16]
*@param other ��ά����
*/
inline Matrix4::Matrix4(const Matrix4& other)
{
	for(int i = 0; i < 16; i++) M[i] = other.M[i];
}
/**
*@note ��16��double������ֵ��Ψ����M[16]   
*@param other 16�����ݵ���ʼ��ַ
*/
inline Matrix4::Matrix4(const double* other)
{
	for(int i = 0; i < 16; i++) M[i] = other[i];
}
/**
*@note��ֵ��Ψ����M[16]   
*@param other ��Ԫ��
*/
inline Matrix4::Matrix4(const Quaternion& other)
{
	Assign(other);
}
/**
*@operator                                         
*/

inline Matrix4& Matrix4::operator=(const Matrix4& other)
{
	for(int i = 0; i < 16; i++) M[i] = other.M[i];
	return *this;
}
/**
*@note Ϊ��4Ψ����ֵ 
*@param other ��ά����
*/

inline void Matrix4::Assign(const Matrix4& other)
{
	for(int i = 0; i < 16; i++) M[i] = other.M[i];
}

inline void Matrix4::Assign(const double* other)
{
	for(int i = 0; i < 16; i++) M[i] = other[i];
}
/**
*@note operator                                         
*/
inline Matrix4& Matrix4::operator=(const Quaternion& other)
{
	Assign(other);
	return *this;
}
/**
*@note operator                                         
*/
inline Matrix4::operator const double*() const
{
	return M;
}
/**
*@note operator                                         
*/
inline Matrix4::operator double*()
{
	return M;
}

/**
*@note ��M[16]�趨Ϊ��λ����     
*@return ��ά����
*/

inline Matrix4& Matrix4::SetIdentity()
{
	/*��M[16]������Ϊ��
	                 | 1  0  0  0 |
					 | 0  1  0  0 |
					 | 0  0  1  0 |
					 | 0  0  0  1 |
					                */
	for(int i = 0; i < 16; i++) M[i] = Matrix4::Identity_Matrix[i];
	return *this;                             //���ظþ���
}
/**
*@note ��M[16]�趨Ϊ0����      
*@return ��ά����
*/
inline Matrix4& Matrix4::SetZero()
{
	/*��M[16]������Ϊ��
	                  | 0  0  0  0 |
	                  | 0  0  0  0 |
	                  | 0  0  0  0 |
	                  | 0  0  0  0 |
	                                   */
	for(int i = 0; i < 16; i++) M[i] = 0.0f;
	return *this;                          // ���ظþ���
}
/**
*@note ��M[16]�趨ΪOrientation_Switch_Matrix    
*@return ��ά����
*/
inline Matrix4& Matrix4::SetSwitchOrientation()
{
	/*��M[16]������Ϊ��
	                  | 1  0  0  0 |
	                  | 0  1  0  0 |
	                  | 0  0 -1  0 |
	                  | 0  0  0  1 |
	                                   */
	for(int i = 0; i < 16; i++) M[i] = Matrix4::Orientation_Switch_Matrix[i];
	return *this;                          //���ظþ���
}
/**
*@note ��M[16]�趨Ϊ Perspective_Matrix     
*@return ��ά����
*/

inline Matrix4& Matrix4::SetPerspective()
{
	/*��M[16]������Ϊ��
                   	| 1  0  0  0 |
	                | 0  1  0  0 |
	                | 0  0  1 -1 |
	                | 0  0  0  0 |
	*/
	for(int i = 0; i < 16; i++) M[i] = Matrix4::Perspective_Matrix[i];
	return *this;                         //���ظþ���
}
/**
*@note �������   
*@param other ��ά����
*@return ��ά����
*/

inline Matrix4& Matrix4::Mul(const Matrix4& other)
{
	Matrix4 tmp;
	tmp.Assign(*this);
	Mul(tmp, other);
	return *this;
}
/**
*@note  �������      
*@param m1 ����1
*@param m2 ����2
*@return  ��ά����
*/
inline Matrix4& Matrix4::Mul(const Matrix4& m1, const Matrix4& m2)
{
	const double *b = m1.M;                    //m1����b
	const double *a = m2.M;                    //m2����a
	double *prod = M;
    
	/*������ˣ�
	            |a[0]  a[1]  a[2]  a[3]|   |b[0]  b[1]  b[2]  b[3]|
				|a[4]  a[5]  a[6]  a[7]|   |b[4]  b[5]  b[6]  b[7]|
	prod[16]=   |a[8]  a[9] a[10] a[11]| * |b[8]  b[9] b[10] b[11]|
	            |a[12] a[13] a[14] a[15]|  |b[12] b[13] b[14] b[15]|
				                                                    */
	  
	for(int i = 0; i < 4; i++)
	{
		double a0 = a[i];
		double a1 = a[i + 4];
		double a2 = a[i + 8];
		double a3 = a[i + 12];
		prod[i] = a0 * b[0] + a1 * b[1] + a2 * b[2] + a3 * b[3];
		prod[i + 4] = a0 * b[4] + a1 * b[5] + a2 * b[6] + a3 * b[7];
		prod[i + 8] = a0 * b[8] + a1 * b[9] + a2 * b[10] + a3 * b[11];
		prod[i + 12] = a0 * b[12] + a1 * b[13] + a2 * b[14] + a3 * b[15];
	}
	return *this;                                //���ظþ���
}

/**
*@note ����M[16]�������         
*@param f ����������
*@return ��ά����
*/
inline Matrix4& Matrix4::Mul(double f)
{

	/*������ˣ�
	             |M[0]  M[1]  M[2]  M[3]|  
	             |M[4]  M[5]  M[6]  M[7]|   
	      M[16]= |M[8]  M[9] M[10] M[11]| *   f
	             |M[12] M[13] M[14] M[15]| 
	                                                  */
	for(int i = 0; i < 16; i++) M[i] *=f;
	return *this;
}
/**
*@note ����other[16]����f���   
*@param other ��ά����
*@param f  ��˵ĸ�����
*@return ��ά����
*/
inline Matrix4& Matrix4::Mul(const Matrix4& other, double f)
{
	/*������ˣ�
           	|m[0]  m[1]  m[2]  m[3]|  
	        |m[4]  m[5]  m[6]  m[7]|   
	M[16]=  |m[8]  m[9] m[10] m[11]| *   f
	        |m[12] m[13] m[14] m[15]| 
                                     	*/
	const double* m = other.M;
	for(int i = 0; i < 16; i++) M[i] = m[i] * f;
	return *this;
}
/**
*@note �������������    
*@param v ��ά����
*@return ��˺����ά����
*/
inline Vector3 Matrix4::Mul(const Vector3& v)
{

	/*������ˣ�
      |x|    |M[0]  M[1]  M[2]  M[3]|    |v.x|
	  |y|    |M[4]  M[5]  M[6]  M[7]|    |v.y|
	  |z|  = |M[8]  M[9] M[10] M[11]| *  |v.z|
	  |w|    |M[12] M[13] M[14] M[15]|   |1.0|
	                                             */
	double x,y,z,w;

	x = M[0] * v.x + M[1] * v.y + M[2] * v.z + M[3];
	y = M[4] * v.x + M[5] * v.y + M[6] * v.z + M[7];
	z = M[8] * v.x + M[9] * v.y + M[10] * v.z + M[11];
	w = M[12] * v.x + M[13] * v.y + M[14] * v.z + M[15];

	if(w == 0)
	{
		return Vector3(1e20,1e20,1e20);  //�����
	}

	return Vector3(x/w, y/w, z/w);        //��������λ���󲢷���
}

/**
*@note ����M[16]�������           
*@param f ����
*@return ��ά����
*/
inline Matrix4& Matrix4::Div(double f)
{

	/*������ˣ�
	                 |M[0]  M[1]  M[2]  M[3]|  
                     |M[4]  M[5]  M[6]  M[7]|   
	          M[16]= |M[8]  M[9] M[10] M[11]| * (1.0/f)
	                 |M[12] M[13] M[14] M[15]| 
	                                                 */
	f = 1.0f / f;
	for(int i = 0; i < 16; i++) M[i] *=f;
	return *this;                        //���ظþ���
}
/**
*@note ����M[16]�������         
*@param other ��ά����
*@param f ����
*@return ��ά����
*/
inline Matrix4& Matrix4::Div(const Matrix4& other, double f)
{
	/*������ˣ�
	                 |m[0]  m[1]  m[2]  m[3]|  
	                 |m[4]  m[5]  m[6]  m[7]|   
	         M[16]=  |m[8]  m[9] m[10] m[11]| *(1.0/f)
	                 |m[12] m[13] m[14] m[15]| 
	                                             */
	f = 1.0f / f;
	const double* m = other.M;
	for(int i = 0; i < 16; i++) M[i] = m[i] * f;
	return *this;                       //���ظþ���
}

/**
*@note Operators                                         
*/

inline Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	Matrix4 tmp;
	tmp.Assign(*this);
	Mul(tmp, other);
	return *this;
}

/**
*@note Operators                                         
*/

inline Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	Matrix4 tmp;
	tmp.Mul(*this, other);
	return tmp;
}

/**
*@note  Transformation       
*@param tx �任����һ
*@param ty �任������
*@param tz �任������
*@return ��ά����
*/

inline Matrix4& Matrix4::Translate(double tx, double ty, double tz)
{
	M[12] = M[0] * tx + M[4] * ty + M[8]  * tz + M[12];
	M[13] = M[1] * tx + M[5] * ty + M[9]  * tz + M[13];
	M[14] = M[2] * tx + M[6] * ty + M[10] * tz + M[14];
	M[15] = M[3] * tx + M[7] * ty + M[11] * tz + M[15];
	return *this;

}
/**
 *@note  Transformation       
 *@param tx �任����һ
 *@param ty �任������
 *@param tz �任������
 *@return ��ά����
 */

inline Matrix4& Matrix4::SetTranslate(double tx, double ty, double tz)
{
	SetIdentity();
	return Translate(tx, ty, tz);
}
/**
*@note �任����ĵ�һ����������      
*@param sx ��һ�еı任����
*@param sy �ڶ��еı任����
*@param sz �����еı任����
*@return ��ά����
*/
inline Matrix4& Matrix4::Scale(double sx, double sy, double sz)
{
	/* 
	          |M[0]*sx  M[1]*sx  M[2]*sx  M[3]*sx|  
	          |M[4]*sy  M[5]*sy  M[6]*sy  M[7]*sy|   
	   M[16]= |M[8]*sz  M[9]*sz M[10]*sz  M[11]*sz| 
	          |M[12]    M[13]   M[14]     M[15]   | 
                                                         	*/

	M[0] *= sx; M[4] *= sy; M[8]  *= sz;     //�����һ���������зֱ����sx��sy��sz
	M[1] *= sx; M[5] *= sy; M[9]  *= sz;
	M[2] *= sx; M[6] *= sy; M[10] *= sz;
	M[3] *= sx; M[7] *= sy; M[11] *= sz;
	return *this;                            //�����µľ���
}
/**
*@note ��Ψ���ž���    
*@param sx ����һ
*@param sy ������
*@param sz ������
*@return ��ά����
*/
inline Matrix4& Matrix4::SetScale(double sx, double sy, double sz)
{
	SetIdentity();                            //�趨Ϊ��λ����

	/* ���ž�����Ϊ��
	             | sx  0  0  0 |
				 | 0   sy 0  0 |
				 | 0   0 sz  0 |
				 | 0   0  0  1 |
				                    */
	return Scale(sx, sy, sz);                 //�������ž���
}
/** 
*@note rotate                                  
*/
inline Matrix4& Matrix4::Rotate(double rx, double ry, double rz)
{
	Matrix4 tmp;
	tmp.SetRotate(rx, ry, rz);
	Mul(tmp);
	return *this;
}
/** 
*@note rotate                                  
*/
inline Matrix4& Matrix4::Rotate(double angle, double x, double y, double z)
{
	Matrix4 tmp;
	tmp.SetRotate(angle, x, y, z);
	Mul(tmp);
	return *this;
}

inline Matrix4& Matrix4::SetRotate(const Vector3& r)
{
	return SetRotate(r.x, r.y, r.z);
}
/** 
*@note rotate                                  
*/
inline Matrix4& Matrix4::Rotate(const Vector3& r)
{
	return Rotate(r.x, r.y, r.z);
}

inline Matrix4& Matrix4::SetRotate(double angle, const Vector3& r)
{
	return SetRotate(angle, r.x, r.y, r.z);
}
/** 
 *@note rotate                                  
 */
inline Matrix4& Matrix4::Rotate(double angle, const Vector3& r)
{
	return Rotate(angle, r.x, r.y, r.z);
}
