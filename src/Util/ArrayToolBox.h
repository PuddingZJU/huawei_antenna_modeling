#ifndef ArrayToolBox_h__
#define ArrayToolBox_h__

#include <fstream>

#define MAXDBL DBL_MAX

using namespace std;

template<typename T>
class ArrayToolBox
{
public:
	static bool isEqual(const T* a, const T* b, int n)
	{
		for(int i = 0; i < n; i++) {
			if(abs(a[i] - b[i]) > M_LOW_TOLERANCE) {
				return false;
			}
		}
		
		return true;
	}
	static void loadFromFstream(T* a, int n, ifstream& in)
	{
		string token;
		for(int i = 0; i < n; i++) {
			in >> a[i];
		}
	}
	static void save2fstream(T* a, int n, const char* s, ofstream& out)
	{
		out << s << endl;
		for(int i = 0; i < n; i++) {
			out << a[i] << " ";
		}
		out << endl;
	}

	static void denormalizeOne(double *a, double *l, double *u, int n)
	{
		for(int i = 0; i < n; i++) {
			a[i] = a[i]*(u[i] - l[i]) + l[i];
		}
	}
	static void normalizeOne(double *a, double *l, double *u, int n)
	{
		for(int i = 0; i < n; i++) {
			a[i] = (a[i] - l[i])/(u[i] - l[i]);
		}
	}
	static T** createArray(int w, int h);
	static void initArray(T ***a, int w, int h);
	static T sum(const T* a, int n);
	static T aver(const T* a, int n);

	//copy from a to b
	static void copyArray(T** from, T** to, int w, int h);
	static void copyArray(const T *from, T *to, int n);
	
	static void releaseArray(T ***a, int w, int h);	

	static void printArray(const T* a, int n, int w);

	//must be n*n matrix
	static void setIdentity(T* a, int n)
	{

		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(i == j) {
					a[i*n + j] = 1.0;
				} else {
					a[i*n + j] = 0;
				}
			}
		}
	}
	static void setArray(T* a, int n, T val)
	{
		T* p = a;
		while(p != a + n) {
			*p++ = val;			
		}
	}

	static void vectorScale(T* d, int n, double s)
	{
		for(int i = 0; i < n; i++) {
			d[i] *= s;
		}
	}
	static void matrixTranspos(T* d, int n)
	{
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < i; j++) {
				T tmp = d[i*n + j];
				d[i*n + j] = d[j*n + i];
				d[j*n + i] = tmp;
			}
		}
	}
	static void matrixTranspos(const T* in, T* out, int n) 
	{
		for(int i = 0; i < n; i++) {
			for(int j = 0; j <= i; j++) {				
				out[i*n + j] = in[j*n + i];
				out[j*n + i] = in[i*n + j];
			}
		}
	}
	static void crossprod3(T d1[3], T d2[3], T out[3]);
	static T dotprod3(T d1[3], T d2[3]);
	static T slope(T x1, T y1, T x2, T y2);
	static int toInteger(T d);
	static void matrixMul44(T m1[16], T m2[16], T out[16]);
	static void matrixMul41(T m1[16], T m2[4], T out[4]);
	static void loadOneMatrix(T m1[16]);
	static void loadMatrix44(T m1[16], T m2[16]);
	static int randomInt(int start, int end);
	static void normalize(T d1[3], T out[3]);
	static void calVector(T d1[3], T d2[3], T out[3]);
	static bool isNear(T d1, T d2);
	static int nansyfloor(T d);
	static void vectorAdd(T *d1, T *d2, T *out, int n);
	static T vectorLen3(T x1, T y1, T z1, T x2, T y2, T z2);
	static T vectorLen2(T x1, T y1, T x2, T y2);
	static T vectorLen2nsqrt(T x1, T y1, T x2, T y2);
protected:
private:
};

template<typename T>
void ArrayToolBox<T>::printArray( const T* a, int n, int w )
{
	for(int i = 0; i < n; i++) {
		cout << " ";
		cout.width(w);
		cout << left;
		cout << a[i];
	}
}

template<typename T>
T ArrayToolBox<T>::aver( const T* a, int n )
{
	T sum = sum(a, n);
	return sum/n;
}

template<typename T>
T ArrayToolBox<T>::sum( const T* a, int n )
{
	T ret = 0;
	for(int i = 0; i < n; i++) {
		ret += a[i];
	}
	return ret;
}

template<typename T>
void ArrayToolBox<T>::releaseArray( T ***a, int w, int h )
{
	for(int i = 0; i < h; i++) {
		delete (*a)[i];
	}
	delete (*a);
	*a = 0;
}

template<typename T>
void ArrayToolBox<T>::copyArray( T** a, T** b, int w, int h )
{
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			b[i][j] = a[i][j];
		}
	}
}

template<typename T>
void ArrayToolBox<T>::initArray( T ***a, int w, int h )
{
	(*a) = new T*[h];
	for(int i = 0; i < h; i++) {
		(*a)[i] = new T[w];
	}
}

template<typename T>
T** ArrayToolBox<T>::createArray( int w, int h )
{
	T** ret = new T*[h];
	for(int i = 0; i < h; i++) {
		ret[i] = new int[w];
	}
	return ret;
}

template<typename T>
void ArrayToolBox<T>::copyArray( const T *a, T *b, int n )
{
	for(int i = 0; i < n; i++) {
		b[i] = a[i];
	}
}

static const int rowI[4] = {0, 4, 8, 12};

//4½×µ¥Î»¾ØÕó
static const double oneMatrix[16] = {1.0,   0,   0,   0,
	0, 1.0,   0,   0,
	0,   0, 1.0,   0,
	0,   0,   0, 1.0};

template<typename T>
void ArrayToolBox<T>::crossprod3(T d1[3], T d2[3], T out[3])
	//²æ³Ë
{
	out[0] = d1[1]*d2[2] - d1[2]*d2[1];
	out[1] = d1[2]*d2[0] - d1[0]*d2[2];
	out[2] = d1[0]*d2[1] - d1[1]*d2[0];
}

//µã³Ë
template<typename T>
T ArrayToolBox<T>::dotprod3(T d1[3], T d2[3])
{
	return d1[0]*d2[0] + d1[1]*d2[1] + d1[2]*d2[2];
}

//Ð±ÂÊ
template<typename T>
T ArrayToolBox<T>::slope(T x1, T y1, T x2, T y2)
{
	if(x1 != x2){
		T ret = (y1 - y2) / (x1 - x2);
		if(ret > MAXDBL){
			ret = MAXDBL;
		}
		return ret;
	}
	else{
		return MAXDBL;
	}
}

template<typename T>
int ArrayToolBox<T>::toInteger(T d)
{
	return 0;
}

/************************************************************************/
/*	n	n	n	n       n	n	n	n                                   */
/*  n	n	n	n	X	n	n	n	n                                   */
/*  n	n	n	n	    n	n	n	n                                   */
/*  n	n	n	n       n	n	n	n                                   */
/************************************************************************/
template<typename T>
void ArrayToolBox<T>::matrixMul44(T m1[16], T m2[16], T out[16])
{
	T sum = 0;
	for(int j = 0; j < 4; j++){
		for(int i = 0; i < 4; i++){
			for(int k = 0; k < 4; k++){
				sum += m1[j*4 + k] * m2[k*4 + i];
			}
			out[j*4 + i] = sum;
			sum = 0;
		}
	}
}

/************************************************************************/
/*	n	n	n	n       n												*/
/*  n	n	n	n	X	n									            */
/*  n	n	n	n	    n						                        */
/*  n	n	n	n       n			                                    */
/************************************************************************/
template<typename T>
void ArrayToolBox<T>::matrixMul41(T m1[16], T m2[4], T out[4])
{
	T sum = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			sum += m1[i*4 + j]*m2[j];
		}
		out[i] = sum;
		sum = 0;
	}
}

/************************************************************************/
/*	n	n	n	n       n	n	n	n                                   */
/*  n	n	n	n	=	n	n	n	n                                   */
/*  n	n	n	n	    n	n	n	n                                   */
/*  n	n	n	n       n	n	n	n                                   */
/************************************************************************/
template<typename T>
void ArrayToolBox<T>::loadMatrix44(T m1[16], T m2[16])
{
	for(int i = 0; i < 16; i++){
		m1[i] = m2[i];
	}
}

template<typename T>
void ArrayToolBox<T>::loadOneMatrix(T m1[16])
{
	for(int i = 0; i < 16; i++){
		m1[i] = oneMatrix[i];
	}
}

template<typename T>
int ArrayToolBox<T>::randomInt(int start, int end)
{
	return (rand() % (end - start) + start)/2;
}

template<typename T>
void ArrayToolBox<T>::normalize(T d1[3], T out[3])
{
	T len = sqrt(d1[0]*d1[0] + d1[1]*d1[1] + d1[2]*d1[2]);
	if(len != 0){
		for(int i = 0; i < 3; i++){
			out[i] = d1[i]/len;
		}
	} else{
		for(int i = 0; i < 3; i++){
			out[i] = 0;
		}
	}
}

template<typename T>
void ArrayToolBox<T>::calVector(T d1[3], T d2[3], T out[3])
{
	for(int i = 0; i < 3; i++){
		out[i] = d2[i] - d1[i];
	}	
}

template<typename T>
bool ArrayToolBox<T>::isNear(T d1, T d2)
{
	T d = d1 - d2;
	if(d < 0){
		d *= -1.0;
	}
	T td = 0;
	if(d - td == 0){
		return true;
	} else{
		return false;
	}
}

template<typename T>
int ArrayToolBox<T>::nansyfloor(T d)
{
	int i = d;
	if(d - 1.0*i >= 0.5){
		return i + 1;
	} else{
		return i;
	}
}

template<typename T>
void ArrayToolBox<T>::vectorAdd(T *d1, T *d2, T *out, int n)
{
	for(int i = 0; i < n; i++){
		out[i] = d1[i] + d2[i];
	}
}

template<typename T>
T ArrayToolBox<T>::vectorLen2nsqrt(T x1, T y1, T x2, T y2)
{
	T dx = x1 - x2;
	T dy = y1 - y2;
	return dx*dx + dy*dy;
}

template<typename T>
T ArrayToolBox<T>::vectorLen2(T x1, T y1, T x2, T y2)
{
	return sqrt(vectorLen2nsqrt(x1, y1, x2, y2));
}

#endif // ArrayToolBox_h__