#include "ComputeVector.h"
#include "Line.h"


double ComputeVector::angle( Vector2 s, Vector2 e )
{
	double sax = angleX(s);
	e.Rotate(sax);
	return angleX(e);
}

double ComputeVector::angleX( Vector2 p )
{	
	p.Normalize();
	double a = atan(p.y/p.x)*M_RAD_TO_DEG;
	if(a > 0) {
		if(p.y >= 0) {
			//no need to change.
		} else {
			a += 180.0;
		}
	} else if(a < 0) {
		if(p.y >= 0) {
			a += 180.0;
		} else {
			a += 360.0;
		}
	} else {
		if(p.x < 0) {
			a = 180;
		}
	}
	return a;
}


Vector3 ComputeVector::Interpolate2P(const Vector3& vBase,const Vector3& vRef, 
									 const Vector3& vP1, const Vector3& vP2)
{
	//法线
	Vector3 vN = vRef - vBase;

	//中点
	Vector3 vM = (vP1+vP2)/2;

	//中点与法线确定的平面，与法线的交点
	Vector3 vI =Vector3((vN.x*vN.x*vM.x + (vN.y*vN.y+vN.z*vN.z)*vBase.x - 
		vN.x*vN.y*(vBase.y-vM.y) - vN.x*vN.z*(vBase.z-vM.z))/(vN.x*vN.x + vN.y*vN.y + vN.z*vN.z),
		(vN.y*vN.y*vM.y + (vN.x*vN.x+vN.z*vN.z)*vBase.y - vN.x*vN.y*(vBase.x-vM.x) - 
		vN.y*vN.z*(vBase.z-vM.z))/(vN.x*vN.x + vN.y*vN.y + vN.z*vN.z),
		(vN.z*vN.z*vM.z + (vN.x*vN.x+vN.y*vN.y)*vBase.z - vN.x*vN.z*(vBase.x-vM.x) -
		vN.y*vN.z*(vBase.y-vM.y))/(vN.x*vN.x + vN.y*vN.y + vN.z*vN.z));

	//交点到两点的向量
	Vector3 vIP1 = vP1 - vI;
	Vector3 vIP2 = vP2 - vI;

	//新点的方向
	Vector3 vT = vIP1 + vIP2;
	//vT.Normalize();

	////长度
	//double scale = (vIP1.Length() + vIP2.Length()) / 2;
	//vT *= scale;

	//vT += vI;
	//
	//return vT;

	return vI + vT * sqrt(0.5);
}

Vector3 ComputeVector::Interpolate3P(const Vector3& vBase,const Vector3& vP1, 
									 const Vector3& vP2)
{
	return vBase + ((vP1-vBase)+(vP2-vBase)) * sqrt(0.5);
}

Vector3 ComputeVector::ParallelP(const Vector3& vBase, const Vector3& vP1, 
								 const Vector3& vP2)
{
	return vBase + (vP2 - vP1);
}

Vector3 ComputeVector::TipPoint(const Vector3& vBase, const Vector3& vRef)
{
	return vBase + (vBase - vRef)/8.0;
}

Vector3 ComputeVector::MidPoint(const Vector3& vBase, const Vector3& vRef)
{
	return (vBase + vRef)/2.0;
}

Vector3 ComputeVector::InterpolateEllipse(const Vector3& v1, const Vector3& v2,
										  double theta, Axis axis)
{
	Vector3 v;

	if(theta <= 0.0)
	{
		return v1;
	}

	if(theta >= 90.0)
	{
		return v2;
	}

	double d;

	switch(axis)
	{
	case X_AXIS:

		if(v1.x == v2.x || v1.z == v2.z )
		{
			v.Lerp( v1, v2, theta / 90.0);
			return v;
		}

		d = sqrt( 1.0 / ( 1.0 / (v1.x - v2.x) / (v1.x - v2.x) 
			+ TanD(theta) * TanD(theta) / (v2.z - v1.z) / (v2.z - v1.z) ) );

		v.x = v2.x + d * ( (v1.x - v2.x)>0 ? 1.0 : -1.0 ) ;
		v.z = v1.z + d * TanD(theta) * ( (v2.z - v1.z)>0 ? 1.0 : -1.0 ) ;
		v.y = v1.y + ( v.z - v1.z ) * (v2.y - v1.y) / (v2.z - v1.z) ;
			/*v1.y + (v2.y - v1.y) * ( 1.0 - v.x / (v1.x - v2.x) )*/ ;

		return v;

	case Y_AXIS:

		if(v1.x == v2.x || v1.y == v2.y )
		{
			v.Lerp( v1, v2, theta / 90.0);
			return v;
		}

		d = sqrt( 1.0 / ( 1.0 / (v1.y - v2.y) / (v1.y - v2.y) 
			+ TanD(theta) * TanD(theta) / (v2.x - v1.x) / (v2.x - v1.x) ) );

		v.y = v2.y + d * ( (v1.y - v2.y)>0 ? 1.0 : -1.0 ) ;
		v.x = v1.x + d * TanD(theta) * ( (v2.x - v1.x)>0 ? 1.0 : -1.0 ) ;
		v.z = v1.z + ( v.x - v1.x ) * (v2.z - v1.z) / (v2.x - v1.x) ;

		return v;
	
	default:
	case Z_AXIS:

		if(v1.z == v2.z || v1.y == v2.y )
		{
			v.Lerp( v1, v2, theta / 90.0);
			return v;
		}

		d = sqrt( 1.0 / ( 1.0 / (v1.z - v2.z) / (v1.z - v2.z) 
			+ TanD(theta) * TanD(theta) / (v2.y - v1.y) / (v2.y - v1.y) ) );

		v.z = v2.z + d * ( (v1.z - v2.z)>0 ? 1.0 : -1.0 ) ;
		v.y = v1.y + d * TanD(theta) * ( (v2.y - v1.y)>0 ? 1.0 : -1.0 ) ;
		v.x = v1.x + ( v.y - v1.y ) * (v2.x - v1.x) / (v2.y - v1.y) ;

		return v;
	}
}

Matrix4 ComputeVector::OrthoProject(int a, int b, int x, int y, int z)
{
	Matrix4 m;

	m.SetTranslate(-x,-y,-z);

	m.Rotate( 0, a, 0 );

	m.Rotate(-b, 0, 0);

	return m.Translate(x,y,z);
}

Matrix4 ComputeVector::PlaneTransform(Vector3 vb1, Vector3 vb2, 
									  Vector2 pb1, Vector2 pb2)
{
	Matrix4 m;

	Vector2 vv = vb2 - vb1;
	Vector2 vp = pb2 - pb1;

	if(vv.Length() == 0 || vp.Length() == 0)
	{
		return m.SetIdentity();
	}

	double s = vp.Length() / vv.Length();

	vv.Normalize();
	vp.Normalize();

	Vector3 vc;
	vc.Cross( Vector3(vp.x, vp.y, 0), Vector3(vv.x, vv.y, 0) );
	vc.Normalize();

	double r = vc.z * ACosD( vv.Dot(vp) );
	

	//m.SetTranslate(-vb1.x, -vb1.y, -vb1.z);

	m.SetRotate(0, 0, r);

	m.Scale(s, s, 1.0);

	return m/*.Translate(pb1.x, pb1.y, vb1.z)*/;
}

double ComputeVector::PlaneRotate( const Vector2& ps1, const Vector2& ps2, 
								  const Vector2& pt1, const Vector2& pt2)
{
	Vector2 vs = ps2 - ps1;
	Vector2 vt;

	if( ps1.DistanceSqr(pt1) <= ps1.DistanceSqr(pt2) )
	{
		vt = pt2 - pt1;
	}
	else
	{
		vt = pt1 - pt2;
	}
	
	vs.Normalize();
	vt.Normalize();

	Vector3 vc;
	vc.Cross( Vector3(vs.x, vs.y, 0), Vector3(vt.x, vt.y, 0) );
	vc.Normalize();

	return - vc.z * ACosD( vs.Dot(vt) );
}

double ComputeVector::PlaneRotate( Vector2 vs, Vector2 vt )
{
	vs.Normalize();
	vt.Normalize();

	Vector3 vc;
	vc.Cross( Vector3(vs.x, vs.y, 0), Vector3(vt.x, vt.y, 0) );
	vc.Normalize();

	return - vc.z * ACosD( vs.Dot(vt) );
}

Vector3 ComputeVector::ComputeAngle(int lon, int lat)
{
	return Vector3( CosD(lat)*SinD(lon) ,SinD(lat), CosD(lat)*CosD(lon) );
}

bool ComputeVector::IsInTriangle(const Vector3& p0, const Vector3& p1, 
								 const Vector3& p2, const Vector3& p3)
{
// 	if(p0.DistanceSqr(p1) < M_LOW_TOLERANCE) {
// 		return true;
// 	}
// 	if(p0.DistanceSqr(p2) < M_LOW_TOLERANCE) {
// 		return true;
// 	}
// 	if(p0.DistanceSqr(p3) < M_LOW_TOLERANCE) {
// 		return true;
// 	}

	Vector3 v1 = p2 - p1;
	Vector3 v2 = p3 - p2;
	Vector3 v3 = p1 - p3;

	Vector3 v01 = p0 - p1;
	Vector3 v02 = p0 - p2;
	Vector3 v03 = p0 - p3;

	Vector3 n1,n2,n3;
	n1.Cross(v1,v01);
	n2.Cross(v2,v02);
	n3.Cross(v3,v03);

	double ln1 = n1.Length();
	double ln2 = n2.Length();
	double ln3 = n3.Length();
	if(ln1 < M_LOW_TOLERANCE && ln2 < M_LOW_TOLERANCE && ln3 < M_LOW_TOLERANCE) {
		return false;
	}

	if( ( n1.Dot(n2) >0 && n2.Dot(n3) > 0 )
			|| ( ln1 < M_LOW_TOLERANCE && n2.Dot(n3) >= 0 ) 
			|| ( ln2 < M_LOW_TOLERANCE && n3.Dot(n1) >= 0 )
			|| ( ln3 < M_LOW_TOLERANCE && n1.Dot(n2) >= 0 ))

	{
		return true;
	}

	return false;
}

Vector3 ComputeVector::Intersection(const Vector3& p0, const Vector3& n0,
									const Vector3& p1, const Vector3& p2, 
									const Vector3& p3)
{
	Vector3 v1 = p2 - p1;
	Vector3 v2 = p3 - p2;

	Vector3 n;
	n.Cross(v1,v2);
	n.Normalize();

	double dn = n.Dot(n0);

	if( dn == 0.0 )
		return Vector3();

	double t = ( n.Dot(p0) - n.Dot(p1) ) / dn;

	return Vector3( p0.x - n0.x * t, p0.y - n0.y * t, p0.z - n0.z * t );
}

Vector3 ComputeVector::Intersection( const Vector3& p0, const Vector3& n0, const Vector3& n, const Vector3& p )
{
	double dn = n.Dot(n0);

	if( dn == 0.0 )
		return Vector3();

	double t = ( n.Dot(p0) - n.Dot(p) ) / dn;

	return Vector3( p0.x - n0.x * t, p0.y - n0.y * t, p0.z - n0.z * t );
}

double ComputeVector::AreaOfTriangle( Vector3 v1, Vector3 v2, Vector3 v3 )
{
	Line l(v2, v3);
	Vector3 foot = l.PerpendicularFoot(v1);
	return l.Length()*foot.Distance(v1)/2.0;
}

Quaternion ComputeVector::ComputeRotation(const Vector3& vs, const Vector3& vt)
{
	double dot = vs.Dot(vt);
	if( fabs( dot ) > 0.999999 )
	{
		return Quaternion::IDENTITY;
	}
	else
	{
		Vector3 daxis;
		daxis.Cross( vs, vt );
		daxis.Normalize();
		double da = ACosD(dot);

		Quaternion q;
		q.SetRotate(da,daxis);
		return q;
	}
}

Vector2 ComputeVector::ProjectVector(const Vector3& vec, const Quaternion& ort)
{
	Vector3 v = ort.Inverse() * vec;

	return Vector2(v.x, v.y);
}

bool ComputeVector::coPlane( const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4 )
{
	Vector3 v1 = p2 - p1;
	Vector3 v2 = p3 - p1;
	if(v1.LengthSqr() < M_LOW_TOLERANCE) {
		return true;
	}
	if(v2.LengthSqr() < M_LOW_TOLERANCE) {
		return true;
	}
	Vector3 n = v1;
	n.Cross(v2);
	n.Normalize();
	return abs(p1.Dot(n) - p4.Dot(n)) < M_HIGH_TOLERANCE;
}   

bool ComputeVector::coLine( const Vector3& p1, const Vector3& p2, const Vector3& p3 )
{
	Vector3 v1 = p2 - p1;
	Vector3 v2 = p3 - p2;
	v1.Cross(v2);
	return v1.Length() < M_LOW_TOLERANCE;
}

int ComputeVector::findVector2( const vector<Vector2> &vec, const Vector2 &v )
{
	for(int i = 0; i < vec.size(); i++) {
		if(v.Distance(vec[i]) < M_LOW_TOLERANCE) {
			return i;
		}
	}
	return -1;
}

double ComputeVector::pointLineDistance( 
	const Vector3& o,
	const Vector3& n,
	const Vector3& p )
{
	Vector3 nn;
	nn.Normalize(n);
	Vector3 lp = p - o;	
	return (nn*(lp.Dot(nn))).Distance(lp);
}

Vector3 ComputeVector::planeNorm( const Vector3& p0, const Vector3& p1, const Vector3& p2 )
{
	Vector3 n(p1 - p0);
	n.Cross(p2 - p1);
	if(n.LengthSqr() < M_LOW_TOLERANCE) {
		return Vector3(0, 0, 1.0);
	}
	n.Normalize();
	return n;
}

Vector3 ComputeVector::planeNorm( const vector<Vector3>& vec )
{
	return planeNorm(vec[0], vec[1], vec[2]);
}

double ComputeVector::pointPlaneDistance( 
	const Vector3& p,
	const Vector3& o, 
	const Vector3& n )
{
	return n.Dot(p - o);
}

double ComputeVector::pointPlaneDistance(
	const Vector3& p, 
	const Vector3& p0,
	const Vector3& p1, 
	const Vector3& p2, 
	Vector3* ip /*= 0*/ )
{	
	Vector3 n = planeNorm(p0, p1, p2);
	double dis = pointPlaneDistance(p, p0, n);
	if(ip) {
		*ip = p - n*dis;
	}
	return dis;
}

void ComputeVector::updateMaxV( const Vector3& v, Vector3& maxv )
{
	maxv.x = std::max(v.x, maxv.x);
	maxv.y = std::max(v.y, maxv.y);
	maxv.z = std::max(v.z, maxv.z);
}

void ComputeVector::updateMinV( const Vector3& v, Vector3& minv )
{
	minv.x = std::min(v.x, minv.x);
	minv.y = std::min(v.y, minv.y);
	minv.z = std::min(v.z, minv.z);
}

Vector2 ComputeVector::toViewPoint( Matrix4 mat )
{
	Vector3 n(0, 0, 1.0);
	Vector3 rn = mat.Mul(n);
	rn.Normalize();
	double x = angle(Vector2(n.z, n.x), Vector2(rn.z, rn.x));
	double y = angle(Vector2(n.z, n.y), Vector2(sqrt(1 - rn.y*rn.y), rn.y));
	return Vector2(x, y);
}

Vector2 ComputeVector::interpolate( Vector3 v0, Vector3 v1, Vector3 v2,
	Vector2 t0, Vector2 t1, Vector2 t2, Vector3 v3 )
{
	Vector2 ret;
	ret.x = interpolate(v0, v1, v2, t0.x, t1.x, t2.x, v3);
	ret.y = interpolate(v0, v1, v2, t0.y, t1.y, t2.y, v3);
	return ret;
}

double ComputeVector::interpolate( Vector3 v0, Vector3 v1, Vector3 v2,
	double t0, double t1, double t2, Vector3 v3 )
{	
	double area = AreaOfTriangle(Vector3(v0.x, v0.y, 0), 
		Vector3(v1.x, v1.y, 0), Vector3(v2.x, v2.y, 0));
	Vector2 v00(v0.x, v0.y);
	Vector2 v11(v1.x, v1.y);
	Vector2 v22(v2.x, v2.y);
	Vector2 v33(v3.x, v3.y);
	if(area < M_LOW_TOLERANCE) {
		area = AreaOfTriangle(Vector3(v0.x, 0, v0.z), 
			Vector3(v1.x, 0, v1.z), Vector3(v2.x, 0, v2.z));
		v00 = Vector2(v0.x, v0.z);
		v11 = Vector2(v1.x, v1.z);
		v22 = Vector2(v2.x, v2.z);
		v33 = Vector2(v3.x, v3.z);
		if(area < M_LOW_TOLERANCE){
			area = AreaOfTriangle(Vector3(0, v0.y, v0.z), 
				Vector3(0, v1.y, v1.z), Vector3(0, v2.y, v2.z));
			v00 = Vector2(v0.y, v0.z);
			v11 = Vector2(v1.y, v1.z);
			v22 = Vector2(v2.y, v2.z);
			v33 = Vector2(v3.y, v3.z);
		}
	} 
	return interpolate(v00, v11, v22, t0, t1, t2, v33);
}

double ComputeVector::interpolate( Vector2 v0, Vector2 v1, Vector2 v2, 
	double d0, double d1, double d2, Vector2 v3 )
{
	Vector2 v10 = v1 - v0;
	Vector2 v21 = v2 - v1;
	Vector3 v310(v10.x, v10.y, d1 - d0);
	Vector3 v321(v21.x, v21.y, d2 - d1);
	Vector3 crossV(v310);
	crossV.Cross(v321);
	crossV.Normalize();
	double m = crossV.Dot(Vector3(v0.x, v0.y, d0));
	
	if(abs(crossV.z) < M_LOW_TOLERANCE) {
		return 0;
	} else {
		return (m - (v3.x*crossV.x + v3.y*crossV.y))/crossV.z;
	}
}
