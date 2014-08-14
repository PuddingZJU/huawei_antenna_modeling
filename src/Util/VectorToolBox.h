#ifndef VectorToolBox_h__
#define VectorToolBox_h__

#include <vector>
#include <set>
#include <map>
#include "qpoint.h"
#include "Mathematics.h"
#include "..\src\corelib\tools\qstring.h"
#include "..\src\corelib\io\qtextstream.h"
#include <assert.h>

using namespace std;

template<typename t>
class Trans1D
{
public:
	Trans1D(t scale, t translate)
		: m_Scale(scale)
		, m_Translate(translate)
	{};
	Trans1D(t oldMin, t oldMax, t newMin, t newMax)
		: m_Scale((newMax - newMin)/(oldMax - oldMin))
		, m_Translate(newMin - oldMin*(newMax - newMin)/(oldMax - oldMin))
	{
		//y = (x - oldMin)/(oldMax - oldMin) * (newMax - newMin) + newMin;
	}
	Trans1D()
		: m_Scale(1.0)
		, m_Translate(0)
	{}
	t map(t val)
	{
		return val*m_Scale + m_Translate;
	}
	Trans1D inverted()
	{
		return Trans1D(1.0/m_Scale, -m_Translate/m_Scale);
	}

protected:
	t m_Scale;
	t m_Translate;
};
 
template<typename T>
class VectorToolBox
{
public:	
	static void test()
	{
		consoleSeprate("test VectorToolBox::filterDuplicatedEles");
		{
			vector<double> valVec(10);
			for(int i = 0; i < valVec.size(); i++) {
				valVec[i] = Rand(0, 1.0);
			}
			vector<double> vec(100);
			for(int i = 0; i < vec.size(); i++) {
				vec[i] = valVec[Rand(-M_LOW_TOLERANCE, valVec.size() - M_LOW_TOLERANCE)];
			}
			filterDuplicatedEles(vec);
		}
		consolePauss();
		consoleSeprate("test VectorToolBox::maxEles");
		vector<int> vec(100);
		for(int i = 0; i < vec.size(); i++) {
			vec[i] = i;
		}
		for(int i = 0; i < 100; i++) {
			int s = Rand(-M_LOW_TOLERANCE, 99 + M_LOW_TOLERANCE);
			s = Clamp(s, 0, 99);
			int e = Rand(-M_LOW_TOLERANCE, 99 + M_LOW_TOLERANCE);
			e = Clamp(e, 0, 99);
			int tmp = vec[s];
			vec[s] = vec[e];
			vec[e] = tmp;
		}
		set<int> idxSet;
		VectorToolBox<int>::maxEles(vec, 0.25, idxSet);
		vec = VectorToolBox<int>::getElements(vec, idxSet);
		for(set<int>::iterator i = idxSet.begin(); i != idxSet.end(); i++) {
			printf("%d ", *i);
		}
		printf("\n");
		consolePauss();
	}

	static void to1D(const vector< vector<T> >& Mat, vector<T>& vec)
	{
		vec.clear();
		vector< vector<T> >::const_iterator iiter = Mat.begin();
		while(iiter != Mat.end()) {
			vec.insert(vec.end(), iiter->begin(), iiter->end());
			iiter++;
		}
	}

	static bool contains(const vector<T>& vec, T val)
	{
		for(int i = 0; i < vec.size(); i++) {
			if(val == vec[i]) {
				return true;
			}
		}
		return false;
	}

	static void genHist(const vector<T>& vec, vector<double>& hist, int binNum, T s, T e)
	{
		hist.clear();
		hist.resize(binNum, 0);
		T step = (e - s)/binNum;
		vector<T>::const_iterator iter = vec.begin();
		while(iter != vec.end()) {
			hist[(*iter - s)/step]++;
			iter++;
		}
	}

	static void syncEles(vector<T>& vec, map<int, QString> idxNameMap, map<int, QString> tarIdxNameMap)
	{
		vector<T> newVec(tarIdxNameMap.size(), T());
		map<int, QString>::iterator tarIter = tarIdxNameMap.begin();
		while(tarIter != tarIdxNameMap.end()) {			
			map<int, QString>::iterator iter = MapToolbox<int, QString>::findValue(idxNameMap, tarIter->second);
			if(iter != idxNameMap.end()) {
				newVec[tarIter->first] = vec[iter->first];
			}
			tarIter++;
		}
		vec = newVec;
	}
	static void delAndShrink(vector<T>& vec, vector<bool> delFlagVec )
	{
		int p0 = 0;
		int p1 = 0;
		int num = vec.size();
		while(p0 < num && p1 < num) {
			if(delFlagVec[p0]) {
				if(p1 < p0) {
					p1 = p0;
				}
				while(p1 < num) {
					if(!delFlagVec[p1]) {
						break;
					}
					p1++;
				}
				if(p1 >= num) {
					break;
				}
				vec[p0] = vec[p1];
				delFlagVec[p1] = true;
				delFlagVec[p0] = false;
			}
			p0++;
		}
		vec.resize(p0);
	}
	static void filterDuplicatedEles(vector<T>& vec)
	{
		int num = vec.size();
		vector<bool> delFlagVec(num);
		for(int i = 0; i < num; i++) {
			if(delFlagVec[i]) {
				continue;
			}
			double v0 = vec[i];
			for(int j = i + 1; j < num; j++) {
				if(delFlagVec[j]) {
					continue;
				}
				double v1 = vec[j];
				if(abs(v0 - v1) < M_LOW_TOLERANCE) {
					delFlagVec[j] = true;
					if(v1 > v0) {
						vec[i] = v1;
						v0 = v1;
					}
				}
			}
		}

		delAndShrink(vec, delFlagVec);
	}
	static T maxEle(const vector< vector<double> >& mat) 
	{
		T ret = mat.front().front();;
		for(int i = 0; i < mat.size(); i++) {
			for(int j = 0; j < mat[i].size(); j++) {
				if(mat[i][j] > ret) {
					ret = mat[i][j];
				}
			}
		}
		return ret;
	}
	static T minEle(const vector< vector<double> >& mat) 
	{
		T ret = mat.front().front();
		for(int i = 0; i < mat.size(); i++) {
			for(int j = 0; j < mat[i].size(); j++) {
				if(mat[i][j] < ret) {
					ret = mat[i][j];
				}
			}
		}
		return ret;
	}
	static void combine(const vector<T>& vec0, const vector<T>& vec1, vector<T>& rsltVec)
	{
		rsltVec = vec0;
		rsltVec.insert(rsltVec.end(), vec1.begin(), vec1.end());
	}
	static void combine(vector<T>& vec0, const vector<T>& vec1)
	{
		vec0.insert(vec0.end(), vec1.begin(), vec1.end());
	}
	static T minEle(const vector<T>& vec, int* idx = 0)
	{
		int i = 0;
		T ret = 0;
		vector<T>::const_iterator iter = vec.begin();
		while(iter != vec.end()) {
			if(*iter < ret) {
				ret = *iter;
				if(idx) {
					*idx = i;
				}
			}
			i++;
			iter++;
		}
		return ret;
	}
	
	static T maxEle(const vector<T>& vec, int* idx = 0)
	{
		int i = 0;
		T ret = -10000000000;
		vector<T>::const_iterator iter = vec.begin();
		while(iter != vec.end()) {
			if(*iter > ret) {
				ret = *iter;
				if(idx) {
					*idx = i;
				}
			}
			iter++;
			i++;
		}
		return ret;
	}
	static void fillVector_ContiInts(vector<int>& srcVec);
	static bool existInVec(vector<T>& vec, T p);
	static void randomSample(int n, vector<int>& out, float w);	
	static vector<T> getElements(const vector<T>& vec, const set<int>& iset)
	{
		vector<T> ret;
		set<int>::const_iterator iiter = iset.begin();
		while(iiter != iset.end()) {
			ret.push_back(vec[*iiter]);
			iiter++;
		}
		return ret;
	}
	static vector<T> getElements(const vector<T>& vec, const vector<int>& ivec)
	{
		vector<T> ret;
		vector<int>::const_iterator iter = ivec.begin();
		while(iter != ivec.end()) {
			ret.push_back(vec[*iter]);
			iter++;
		}
		return ret;
	}
	static vector<T> getIndexs(const vector<T>& vec, const set<T>& valSet)
	{

	}
	static T sum(const vector<T>& vec);
	static T sum(const vector<T>& vec, int si, int ei);

	enum VectorDisOpt
	{
		DIS_SQUARE = 1,
		DIS_ABS = 2
	};
	static T vectorDis(const vector<T>& vec0, const vector<T>& vec1, int option = DIS_SQUARE);	
	static void norm1Vector(const vector<T>& vec, vector<T>& nvec)
	{
		T sum = VectorToolBox<T>::sum(vec);
		nvec = vec;
		VectorToolBox<T>::mul(nvec, 1.0/sum);
	}
	static void norm2Vector(const vector<T>& vec, vector<double>& nvec);
	static void norm2Vector(const vector<T>& vec, vector<float>& nvec);
	static void add(const vector<T>& vec, T a, vector<T>& otherVec);
	static void add(vector<T>& vec, T a);

	static double length(const vector<T>& vec);

	//rsltVec = vec1 + vec2
	static void add(const vector<T>& vec1, const vector<T>& vec2, 
		vector<T>& rsltVec) 
	{
		AssertLog(vec1.size() == vec2.size());
		rsltVec.resize(vec1.size());
		auto i1 = vec1.begin();
		auto i2 = vec2.begin();
		auto ri = rsltVec.begin();
		while(i1 != vec1.end()) {
			*ri = *i1 + *i2;
			i1++;
			i2++;
			ri++;
		}
	}

	//rsltVec = vec1 - vec2
	static void minus(const vector<T>& vec1, const vector<T>& vec2, 
		vector<T>& rsltVec);
	static void mul(vector<T>& vec, double a)
	{
		auto iter = vec.begin();
		while(iter != vec.end()) {
			*iter *= a;
			iter++;
		}
	}

	static T average(const vector<T>& vec)
	{
		T ret = 0;
		for(auto i = vec.begin(); i != vec.end(); i++) {
			ret += *i;
		}
		return ret/(double)vec.size();
	}
// 	static void mul(vector<T>::iterator bi, vector<T>::iterator ei, T a)
// 	{
// 		vector<T>::iterator i = bi;
// 		while(i != ei) {
// 			*i *= a;
// 			i++;
// 		}
// 	}
	static bool isSame(const vector<T>& vec1, const vector<T>& vec2);
	static void eraseEle(vector<T>& vec, int i);
	static void eraseEles(vector<T>& vec, vector<int>& iVec);
	static void eraseEles(vector<T>& vec, set<int>& iSet);

	//small key first
	static void sort(const vector<double>& keyVec, vector<T>& valueVec, 
		double trancThre = DBL_MAX	//trancate keys larger than trancThre
		); 

	static void maxEles(const vector<T>& vec, float ratio, set<int>& mIdxVec)
	{
		ratio = Clamp(ratio, 0, 1.0);
		vector<int> idxVec(vec.size());
		vector<double> keyVec(vec.size());
		for(int i = 0; i < vec.size(); i++) {
			idxVec[i] = i;
			keyVec[i] = (double)vec[i];
		}
		VectorToolBox<int>::sort(keyVec, idxVec, 
			VectorToolBox<double>::maxEle(keyVec));	//small first
		int maxIdx = (1.0 - ratio)*(vec.size() - 1);
		maxIdx = maxIdx < 0 ? 0 : maxIdx;
		maxIdx = maxIdx >= vec.size() ? vec.size() - 1 : maxIdx;
		mIdxVec.clear();
		mIdxVec.insert(idxVec.begin() + maxIdx, idxVec.end());
	}

	static void printVector(const vector<T>& vec, int typeId = -1);

	//elements are divided by ",". ended with ","
	static QString toString(const vector<T>& vec) 
	{
		QString ret;
		QTextStream out(&ret);
		vector<T>::const_iterator iter = vec.begin();
		while(iter != vec.end()) {
			out << *iter << ",";
			iter++;
		}
		return ret;
	}

	//best with T = double.
	//elements are divided by ","
	static vector<T> fromString(const QString& str)
	{
		vector<T> ret;
		QStringList slst = str.split(",");
		slst.removeAll("");
		foreach(QString str, slst) {
			ret.push_back(str.trimmed().toDouble());
		}
		return ret;
	}

	static void sort(vector<T>& vec, 
		map<int, QString>& srcIdxNameMap,
		map<int, QString>& tarIdxNameMap);

	static void erasePtrEles(vector<T*>& vec, set<int>& iSet)
	{
		set<int>::iterator iter = iSet.begin();	
		int count = 0;
		while(iter != iSet.end()) {
			int di = *iter;
			delete vec[di - count];
			vec.erase(vec.begin() + (di - count));
			iter++;
			count++;
		}
	}

	static void releasePointerVec(vector<T*>& vec) 
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if(vec[i])
				delete vec[i];
		}
		vec.clear();	
	}

	static void copyPointerVec(vector<T*>& vec)
	{
		for(int i = 0; i < vec.size(); i++) {
			if(vec[i]) {
				vec[i] = new T(*vec[i]);
			}
		}
	}

	static void randomVector(vector<T>& vec, T min, T max, bool noRepeat = false)
	{
		for(int i = 0; i < vec.size(); i++) {
			T val = (T)Rand((double)min, (double)max);
			if(noRepeat) {
				while(contains(vec, val)) {
					val = (T)Rand((double)min, (double)max);
				}
			}			
			vec[i] = val;
		}
	}

	static void disturbVector(vector<T>& vec, T min, T max)
	{
		vector<T>::iterator iter = vec.begin();
		while(iter != vec.end()) {
			*iter += Rand(min, max);
			iter++;
		}
	}

	static bool allZero(const vector<T>& vec, double thre = M_LOW_TOLERANCE) 
	{
		for(int i = 0; i < vec.size(); i++) {
			if(abs(vec[i]) > thre) {
				return false;
			}
		}
		return true;
	}

	static void genVec(vector<T>& vec, int size, T s = 0, T e = 0)
	{
		if(size < 0) {
			return;
		}
		vec.clear();
		if(s == e) {
			vec = vector<T>(size, s);
			return;
		}
		vec.resize(size);
		double step;
		if(size == 1) {
			step = 0;
		} else {
			step = (double)(e - s)/(double)(size - 1);
		}
		
		for(int i = 0; i < size; i++) {
			vec[i] = s + i*step;
		}
	}

	static void mul(vector<T>& vec, const vector<T>& aVec)
	{
		if(vec.size() != aVec.size()) {
			printf("vector sizes not equal");
			return;
		}
		vector<T>::iterator iter = vec.begin();
		vector<T>::const_iterator aIter = aVec.begin();
		while(iter != vec.end()) {
			*iter *= *aIter;
			iter++;
			aIter++;
		}
	}

	static void rotate(vector<T>& vec)
	{
		std::rotate(vec.begin(), vec.begin() + 1, vec.end());
	}
	static void reverseRotate(vector<T>& vec)
	{
		std::rotate(vec.rbegin(), vec.rbegin() + 1, vec.rend());
	}

	static T weightedSum(const vector<T>& vec, const vector<double>& wVec)
	{
		if(vec.size() != wVec.size()) {
			printf("vec.size() != wVec.size()\n");
			return T();
		}
		vector<T>::const_iterator iter = vec.begin();
		vector<double>::const_iterator wIter = wVec.begin();
		T ret = T();
		while(iter != vec.end() && wIter != wVec.end()) {
			ret += (*iter) * (*wIter);
			iter++;
			wIter++;
		}
		return ret;
	}
};	

template<typename T>
T VectorToolBox<T>::sum( const vector<T>& vec, int si, int ei )
{
	T ret = T();
	for(int i = si; i < ei; i++) {
		ret += vec[i];
	}
	return ret;
}

//values of srcIdxNameMap and tarIdxNameMap must be the same
template<typename T>
void VectorToolBox<T>::sort( vector<T>& vec, 
							map<int, QString>& srcIdxNameMap,
							map<int, QString>& tarIdxNameMap )
{
	vector<T> newVec(vec.size());
	map<QString, int> tarIdxNameMap_inv = MapToolbox<int, QString>::invert(tarIdxNameMap);
	for(int i = 0; i < vec.size(); i++) {
		newVec[i] = vec[tarIdxNameMap_inv[srcIdxNameMap[i]]];
	}
}

template<typename T>
void VectorToolBox<T>::eraseEles( vector<T>& vec, set<int>& iSet )
{
	vector<T> buf;
	set<int>::iterator iter = iSet.begin();	
	int count = 0;
	while(iter != iSet.end()) {
		int di = *iter;
		vec.erase(vec.begin() + (di - count));
		iter++;
		count++;
	}
}

template<typename T>
void VectorToolBox<T>::printVector( const vector<T>& vec, int typeId /*= -1*/ )
{
	vector<T>::const_iterator i = vec.begin();
	while(i != vec.end()) {
		cout << *i << " ";
		i++;
	}
	cout << endl;
}

template<typename T>
double VectorToolBox<T>::length( const vector<T>& vec )
{
	double length = 0;
	vector<T>::const_iterator iter = vec.begin();	
	while(iter != vec.end()) {
		double val = (double)(*iter)*(double)(*iter);
		if(val > -1.0/M_LOW_TOLERANCE && val < 1.0/M_LOW_TOLERANCE) {
			length += val;
		}		
		iter++;
	}
	return sqrt(length/(double)vec.size());
}

template<typename T>
void VectorToolBox<T>::eraseEle( vector<T>& vec, int i )
{
	vec.erase(vec.begin() + i);
}

template<typename T>
void VectorToolBox<T>::eraseEles( vector<T>& vec, vector<int>& iVec )
{
	vector<T> buf;
	vector<int>::iterator iter = iVec.begin();	
	int count = 0;
	while(iter != iVec.end()) {
		int di = *iter;
		vec.erase(vec.begin() + (di - count));
		iter++;
		count++;
	}
}

template<typename T>
void VectorToolBox<T>::minus( const vector<T>& vec1, const vector<T>& vec2, vector<T>& rsltVec )
{
	int num = vec1.size();
	if(num != vec2.size()) {
		printf("vector size not match\n");
		return ;
	}
	rsltVec.resize(num);
	for(int i = 0; i < num; i++) {
		rsltVec[i] = vec1[i] - vec2[i];
	}
}

template<typename T>
void VectorToolBox<T>::sort(const vector<double>& keyVec, vector<T>& valueVec,
							double trancThre)
{
	map<double, T*> sortMap;
	for(int i = 0; i < keyVec.size(); i++) {
		double key = keyVec[i];
		T* value = &valueVec[i];
		map<double, T*>::iterator iter = sortMap.find(key);
		while(iter != sortMap.end()) {	
			key += M_LOW_TOLERANCE;
			iter = sortMap.find(key);			
		}
		sortMap[key] = value;
	}
	map<double, T*>::iterator iter = sortMap.begin();
	int idx = 0;
	vector<T> buf;
	while(iter != sortMap.end()) {
		if(iter->first > trancThre + M_HIGH_TOLERANCE) {
			break;
		}
		buf.push_back(*(iter->second));
		iter++;
	}
	valueVec = buf;
}

template<typename T>
bool VectorToolBox<T>::existInVec( vector<T>& vec, T p )
{
	for(int i = 0; i < vec.size(); i++) {
		if(p == vec[i]) {
			return true;
		}
	}
	return false;
}

template<typename T>
void VectorToolBox<T>::fillVector_ContiInts( vector<int>& srcVec )
{
	for(int i = 0; i < srcVec.size(); i++) {
		srcVec[i] = i;
	}
}

template<typename T>
void VectorToolBox<T>::randomSample( int n, vector<int>& out, float w )
{
	for(int i = 0; i < n; i++) {
		double rv = Rand(0, 1.0);
		if(rv < w) {
			out.push_back(i);
		}
	}
}

template<typename T>
bool VectorToolBox<T>::isSame( const vector<T>& vec1, const vector<T>& vec2 )
{
	if(vec1.size() != vec2.size()) {
		return false;
	}
	for(int i = 0; i < vec1.size(); i++) {
		if(vec1[i] != vec2[i]) {
			return false;
		}
	}
	return true;
}

template<typename T>
void VectorToolBox<T>::add( vector<T>& vec, T a )
{
	 for(int i = 0; i < vec.size(); i++) {
	 	vec[i] = vec[i] + a;
	 }
}

template<typename T>
void VectorToolBox<T>::add( const vector<T>& vec, T a, vector<T>& otherVec )
{
	otherVec.resize(vec.size());
	for(int i = 0;  i < vec.size(); i++) {
		otherVec[i] = vec[i] + a;
	}
}

template<typename T>
void VectorToolBox<T>::norm2Vector( const vector<T>& vec, vector<double>& nvec )
{
	double sum = 0;
	vector<T>::const_iterator ci = vec.begin();
	while(ci != vec.end()) {
		sum += (*ci)*(*ci);
		ci++;
	}
	if(sum == 0) {
		nvec.resize(vec.size(), 0);
		return;
	} else {
		nvec.resize(vec.size());
	}	
	sum = sqrt(sum);
	ci = vec.begin();
	vector<double>::iterator i = nvec.begin();
	while(ci != vec.end()) {
		*i = *ci/sum;		
		ci++;
		i++;
	}
}

template<typename T>
void VectorToolBox<T>::norm2Vector( const vector<T>& vec, vector<float>& nvec )
{
	float sum = 0;
	vector<T>::const_iterator ci = vec.begin();
	while(ci != vec.end()) {
		sum += (*ci)*(*ci);
		ci++;
	}
	if(sum == 0) {
		nvec.resize(vec.size(), 0);
		return;
	} else {
		nvec.resize(vec.size());
	}	
	sum = sqrt(sum);
	ci = vec.begin();
	vector<float>::iterator i = nvec.begin();
	while(ci != vec.end()) {
		*i = *ci/sum;		
		ci++;
		i++;
	}
}

template<typename T>
T VectorToolBox<T>::vectorDis( const vector<T>& vec0, const vector<T>& vec1, int option )
{
	if(vec0.size() != vec1.size()) {
		printf("vector dimensions do not match.\n");
		return T();
	}
	T dis = 0;
	vector<T>::const_iterator ci0, ci1;
	ci0 = vec0.begin();
	ci1 = vec1.begin();

	if(option & VectorToolBox::DIS_SQUARE) {
		while(ci0 != vec0.end()) {
			dis += (*ci0 - *ci1)*(*ci0 - *ci1);
			ci0++;
			ci1++;
		}
		return sqrt(dis);
	} else {
		while(ci0 != vec0.end()) {
			dis += abs(*ci0 - *ci1);
			ci0++;
			ci1++;
		}
		return dis;
	}
}

template<typename T>
T VectorToolBox<T>::sum( const vector<T>& vec )
{
	T ret = T();
	for(int i = 0; i < vec.size(); i++) {
		ret = ret + vec[i];
	}
	return ret;
}

#endif // VectorToolBox_h__