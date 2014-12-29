#include "CMath.h"
#undef VTYPE
#define VTYPE	float

Vector3DF &Vector3DF::operator*= (const MatrixF &op)
{
	double *m = op.GetDataF();
	float xa, ya, za;
	xa = x * float(*m++);	ya = x * float(*m++);	za = x * float(*m++);	m++;
	xa += y * float(*m++);	ya += y * float(*m++);	za += y * float(*m++);	m++;
	xa += z * float(*m++);	ya += z * float(*m++);	za += z * float(*m++);	m++;
	xa += float(*m++);		ya += float(*m++);		za += float(*m++);
	x = xa; y = ya; z = za;
	return *this;
}

// p' = Mp
Vector3DF &Vector3DF::operator*= (const Matrix4F &op)
{
	float xa, ya, za;
	xa = x * op.data[0] + y * op.data[4] + z * op.data[8] + op.data[12];
	ya = x * op.data[1] + y * op.data[5] + z * op.data[9] + op.data[13];
	za = x * op.data[2] + y * op.data[6] + z * op.data[10] + op.data[14];
	x = xa; y = ya; z = za;
	return *this;
}


#define min3(a,b,c)		( (a<b) ? ((a<c) ? a : c) : ((b<c) ? b : c) )
#define max3(a,b,c)		( (a>b) ? ((a>c) ? a : c) : ((b>c) ? b : c) )

Vector3DF Vector3DF::RGBtoHSV()
{
	float h, s, v;
	float minv, maxv;
	int i;
	float f;

	minv = min3(x, y, z);
	maxv = max3(x, y, z);
	if (minv == maxv) {
		v = (float)maxv;
		h = 0.0;
		s = 0.0;
	}
	else {
		v = (float)maxv;
		s = (maxv - minv) / maxv;
		f = (x == minv) ? y - z : ((y == minv) ? z - x : x - y);
		i = (x == minv) ? 3 : ((y == minv) ? 5 : 1);
		h = (i - f / (maxv - minv)) / 6.0f;
	}
	return Vector3DF(h, s, v);
}

Vector3DF Vector3DF::HSVtoRGB()
{
	float m, n, f;
	int i = (int)floor(x*6.0);
	f = x*6.0f - i;
	if (i % 2 == 0) f = 1.0f - f;
	m = z * (1.0f - y);
	n = z * (1.0f - y * f);
	switch (i) {
	case 6:
	case 0: return Vector3DF(z, n, m);	break;
	case 1: return Vector3DF(n, z, m);	break;
	case 2: return Vector3DF(m, z, n);	break;
	case 3: return Vector3DF(m, n, z);	break;
	case 4: return Vector3DF(n, m, z);	break;
	case 5: return Vector3DF(z, m, n);	break;
	};
	return Vector3DF(1, 1, 1);
}

Vector4DF &Vector4DF::operator*= (const MatrixF &op)
{
	double *m = op.GetDataF();
	VTYPE xa, ya, za, wa;
	xa = x * float(*m++);	ya = x * float(*m++);	za = x * float(*m++);	wa = x * float(*m++);
	xa += y * float(*m++);	ya += y * float(*m++);	za += y * float(*m++);	wa += y * float(*m++);
	xa += z * float(*m++);	ya += z * float(*m++);	za += z * float(*m++);	wa += z * float(*m++);
	xa += w * float(*m++);	ya += w * float(*m++);	za += w * float(*m++);	wa += w * float(*m++);
	x = xa; y = ya; z = za; w = wa;
	return *this;
}

Vector4DF &Vector4DF::operator*= (const Matrix4F &op)
{
	float xa, ya, za, wa;
	xa = x * op.data[0] + y * op.data[4] + z * op.data[8] + w * op.data[12];
	ya = x * op.data[1] + y * op.data[5] + z * op.data[9] + w * op.data[13];
	za = x * op.data[2] + y * op.data[6] + z * op.data[10] + w * op.data[14];
	wa = x * op.data[3] + y * op.data[7] + z * op.data[11] + w * op.data[15];
	x = xa; y = ya; z = za; w = wa;
	return *this;
}


Vector4DF &Vector4DF::operator*= (const float* op)
{
	float xa, ya, za, wa;
	xa = x * op[0] + y * op[4] + z * op[8] + w * op[12];
	ya = x * op[1] + y * op[5] + z * op[9] + w * op[13];
	za = x * op[2] + y * op[6] + z * op[10] + w * op[14];
	wa = x * op[3] + y * op[7] + z * op[11] + w * op[15];
	x = xa; y = ya; z = za; w = wa;
	return *this;
}

//----------------------------------------------------------------------------------------------------------

// Vector Operations Implemented:
//		=, +, -, *, / (on vectors and scalars)
//		Cross			Cross product vector with op
//		Dot				Dot product vector with op
//		Dist (op)		Distance from vector to op
//		DistSq			Distance^2 from vector to op
//		Length ()		Length of vector
//		Normalize ()	Normalizes vector
//

#include <math.h>

// Vector2DC Code Definition

#undef VTYPE
#define VTYPE		unsigned char
#define VNAME		2DC

// Constructors/Destructors
Vector2DC::Vector2DC() { x = 0; y = 0; }
Vector2DC::Vector2DC(VTYPE xa, VTYPE ya) { x = xa; y = ya; }
Vector2DC::Vector2DC(Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DC::Vector2DC(Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DC::Vector2DC(Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DC::Vector2DC(Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DC::Vector2DC(Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DC::Vector2DC(Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DC::Vector2DC(Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }

// Member Functions
Vector2DC &Vector2DC::operator= (Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator= (Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator= (Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator= (Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator= (Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator= (Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator= (Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }

Vector2DC &Vector2DC::operator+= (Vector2DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator+= (Vector2DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator+= (Vector2DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator+= (Vector3DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator+= (Vector3DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator+= (Vector3DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator+= (Vector4DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }

Vector2DC &Vector2DC::operator-= (Vector2DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator-= (Vector2DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator-= (Vector2DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator-= (Vector3DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator-= (Vector3DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator-= (Vector3DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator-= (Vector4DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }

Vector2DC &Vector2DC::operator*= (Vector2DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator*= (Vector2DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator*= (Vector2DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator*= (Vector3DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator*= (Vector3DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator*= (Vector3DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator*= (Vector4DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }

Vector2DC &Vector2DC::operator/= (Vector2DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator/= (Vector2DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator/= (Vector2DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator/= (Vector3DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator/= (Vector3DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator/= (Vector3DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DC &Vector2DC::operator/= (Vector4DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }

// Note: Cross product does not exist for 2D vectors (only 3D)

double Vector2DC::Dot(Vector2DC &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }
double Vector2DC::Dot(Vector2DI &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }
double Vector2DC::Dot(Vector2DF &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }

double Vector2DC::Dist(Vector2DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DC::Dist(Vector2DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DC::Dist(Vector2DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DC::Dist(Vector3DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DC::Dist(Vector3DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DC::Dist(Vector3DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DC::Dist(Vector4DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DC::DistSq(Vector2DC &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DC::DistSq(Vector2DI &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DC::DistSq(Vector2DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DC::DistSq(Vector3DC &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DC::DistSq(Vector3DI &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DC::DistSq(Vector3DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DC::DistSq(Vector4DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }

Vector2DC &Vector2DC::Normalize(void) {
	double n = (double)x*x + (double)y*y;
	if (n != 0.0) {
		n = sqrt(n);
		x = (VTYPE)(((double)x * 255) / n);
		y = (VTYPE)(((double)y * 255) / n);
	}
	return *this;
}
double Vector2DC::Length(void) { double n; n = (double)x*x + (double)y*y; if (n != 0.0) return sqrt(n); return 0.0; }

#undef VTYPE
#undef VNAME

// Vector2DI Code Definition

#define VNAME		2DI
#define VTYPE		int

// Constructors/Destructors
Vector2DI::Vector2DI() { x = 0; y = 0; }
Vector2DI::Vector2DI(const VTYPE xa, const VTYPE ya) { x = xa; y = ya; }
Vector2DI::Vector2DI(const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DI::Vector2DI(const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DI::Vector2DI(const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DI::Vector2DI(const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DI::Vector2DI(const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DI::Vector2DI(const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DI::Vector2DI(const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }

// Member Functions
Vector2DI &Vector2DI::operator= (const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator= (const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator= (const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator= (const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator= (const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator= (const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator= (const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }

Vector2DI &Vector2DI::operator+= (const Vector2DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator+= (const Vector2DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator+= (const Vector2DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator+= (const Vector3DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator+= (const Vector3DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator+= (const Vector3DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator+= (const Vector4DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }

Vector2DI &Vector2DI::operator-= (const Vector2DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator-= (const Vector2DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator-= (const Vector2DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator-= (const Vector3DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator-= (const Vector3DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator-= (const Vector3DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator-= (const Vector4DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }

Vector2DI &Vector2DI::operator*= (const Vector2DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator*= (const Vector2DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator*= (const Vector2DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator*= (const Vector3DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator*= (const Vector3DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator*= (const Vector3DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator*= (const Vector4DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }

Vector2DI &Vector2DI::operator/= (const Vector2DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator/= (const Vector2DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator/= (const Vector2DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator/= (const Vector3DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator/= (const Vector3DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator/= (const Vector3DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DI &Vector2DI::operator/= (const Vector4DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }

// Note: Cross product does not exist for 2D vectors (only 3D)

double Vector2DI::Dot(const Vector2DC &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }
double Vector2DI::Dot(const Vector2DI &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }
double Vector2DI::Dot(const Vector2DF &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }

double Vector2DI::Dist(const Vector2DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DI::Dist(const Vector2DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DI::Dist(const Vector2DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DI::Dist(const Vector3DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DI::Dist(const Vector3DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DI::Dist(const Vector3DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DI::Dist(const Vector4DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DI::DistSq(const Vector2DC &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DI::DistSq(const Vector2DI &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DI::DistSq(const Vector2DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DI::DistSq(const Vector3DC &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DI::DistSq(const Vector3DI &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DI::DistSq(const Vector3DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DI::DistSq(const Vector4DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }

Vector2DI &Vector2DI::Normalize(void) {
	double n = (double)x*x + (double)y*y;
	if (n != 0.0) {
		n = sqrt(n);
		x = (VTYPE)(((double)x * 255) / n);
		y = (VTYPE)(((double)y * 255) / n);
	}
	return *this;
}
double Vector2DI::Length(void) { double n; n = (double)x*x + (double)y*y; if (n != 0.0) return sqrt(n); return 0.0; }



#undef VTYPE
#undef VNAME

// Vector2DF Code Definition

#define VNAME		2DF
#define VTYPE		float

// Constructors/Destructors
Vector2DF::Vector2DF() { x = 0; y = 0; }
Vector2DF::Vector2DF(const VTYPE xa, const VTYPE ya) { x = xa; y = ya; }
Vector2DF::Vector2DF(const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DF::Vector2DF(const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DF::Vector2DF(const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DF::Vector2DF(const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DF::Vector2DF(const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DF::Vector2DF(const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }
Vector2DF::Vector2DF(const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; }

// Member Functions
Vector2DF &Vector2DF::operator= (const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator= (const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator= (const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator= (const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator= (const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator= (const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator= (const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }

Vector2DF &Vector2DF::operator+= (const Vector2DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator+= (const Vector2DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator+= (const Vector2DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator+= (const Vector3DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator+= (const Vector3DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator+= (const Vector3DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator+= (const Vector4DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }

Vector2DF &Vector2DF::operator-= (const Vector2DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator-= (const Vector2DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator-= (const Vector2DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator-= (const Vector3DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator-= (const Vector3DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator-= (const Vector3DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator-= (const Vector4DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }

Vector2DF &Vector2DF::operator*= (const Vector2DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator*= (const Vector2DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator*= (const Vector2DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator*= (const Vector3DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator*= (const Vector3DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator*= (const Vector3DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator*= (const Vector4DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }

Vector2DF &Vector2DF::operator/= (const Vector2DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator/= (const Vector2DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator/= (const Vector2DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator/= (const Vector3DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator/= (const Vector3DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator/= (const Vector3DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector2DF &Vector2DF::operator/= (const Vector4DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }

// Note: Cross product does not exist for 2D vectors (only 3D)

double Vector2DF::Dot(const Vector2DC &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }
double Vector2DF::Dot(const Vector2DI &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }
double Vector2DF::Dot(const Vector2DF &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y; return dot; }

double Vector2DF::Dist(const Vector2DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DF::Dist(const Vector2DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DF::Dist(const Vector2DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DF::Dist(const Vector3DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DF::Dist(const Vector3DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DF::Dist(const Vector3DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DF::Dist(const Vector4DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector2DF::DistSq(const Vector2DC &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DF::DistSq(const Vector2DI &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DF::DistSq(const Vector2DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DF::DistSq(const Vector3DC &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DF::DistSq(const Vector3DI &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DF::DistSq(const Vector3DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }
double Vector2DF::DistSq(const Vector4DF &v)		{ double a, b; a = (double)x - (double)v.x; b = (double)y - (double)v.y; return (a*a + b*b); }

Vector2DF &Vector2DF::Normalize(void) {
	double n = (double)x*x + (double)y*y;
	if (n != 0.0) {
		n = sqrt(n);
		x /= (float)n;
		y /= (float)n;
	}
	return *this;
}
double Vector2DF::Length(void) { double n; n = (double)x*x + (double)y*y; if (n != 0.0) return sqrt(n); return 0.0; }

#undef VTYPE
#undef VNAME

// Vector3DC Code Definition

#define VNAME		3DC
#define VTYPE		unsigned char

// Constructors/Destructors
Vector3DC::Vector3DC() { x = 0; y = 0; z = 0; }
Vector3DC::Vector3DC(const VTYPE xa, const VTYPE ya, const VTYPE za) { x = xa; y = ya; z = za; }
Vector3DC::Vector3DC(const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DC::Vector3DC(const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DC::Vector3DC(const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DC::Vector3DC(const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DC::Vector3DC(const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DC::Vector3DC(const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DC::Vector3DC(const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }

// Member Functions
Vector3DC &Vector3DC::Set(const VTYPE xa, const VTYPE ya, const VTYPE za) { x = xa; y = ya; z = za; return *this; }

Vector3DC &Vector3DC::operator= (const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; return *this; }
Vector3DC &Vector3DC::operator= (const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; return *this; }
Vector3DC &Vector3DC::operator= (const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; return *this; }
Vector3DC &Vector3DC::operator= (const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator= (const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator= (const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator= (const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }

Vector3DC &Vector3DC::operator+= (const Vector2DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator+= (const Vector2DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator+= (const Vector2DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator+= (const Vector3DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator+= (const Vector3DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator+= (const Vector3DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator+= (const Vector4DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }

Vector3DC &Vector3DC::operator-= (const Vector2DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator-= (const Vector2DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator-= (const Vector2DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator-= (const Vector3DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator-= (const Vector3DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator-= (const Vector3DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator-= (const Vector4DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }

Vector3DC &Vector3DC::operator*= (const Vector2DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator*= (const Vector2DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator*= (const Vector2DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator*= (const Vector3DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator*= (const Vector3DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator*= (const Vector3DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator*= (const Vector4DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }

Vector3DC &Vector3DC::operator/= (const Vector2DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator/= (const Vector2DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator/= (const Vector2DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DC &Vector3DC::operator/= (const Vector3DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator/= (const Vector3DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator/= (const Vector3DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DC &Vector3DC::operator/= (const Vector4DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }

Vector3DC &Vector3DC::Cross(const Vector3DC &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }
Vector3DC &Vector3DC::Cross(const Vector3DI &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }
Vector3DC &Vector3DC::Cross(const Vector3DF &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }

double Vector3DC::Dot(const Vector3DC &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }
double Vector3DC::Dot(const Vector3DI &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }
double Vector3DC::Dot(const Vector3DF &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }

double Vector3DC::Dist(const Vector2DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DC::Dist(const Vector2DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DC::Dist(const Vector2DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DC::Dist(const Vector3DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DC::Dist(const Vector3DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DC::Dist(const Vector3DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DC::Dist(const Vector4DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DC::DistSq(const Vector2DC &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DC::DistSq(const Vector2DI &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DC::DistSq(const Vector2DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DC::DistSq(const Vector3DC &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DC::DistSq(const Vector3DI &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DC::DistSq(const Vector3DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DC::DistSq(const Vector4DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }

Vector3DC &Vector3DC::Normalize(void) {
	double n = (double)x*x + (double)y*y + (double)z*z;
	if (n != 0.0) {
		n = sqrt(n);
		x = (VTYPE)(((double)x * 255) / n);
		y = (VTYPE)(((double)y * 255) / n);
		z = (VTYPE)(((double)z * 255) / n);
	}
	return *this;
}
double Vector3DC::Length(void) { double n; n = (double)x*x + (double)y*y + (double)z*z; if (n != 0.0) return sqrt(n); return 0.0; }



#undef VTYPE
#undef VNAME

// Vector3DI Code Definition

#define VNAME		3DI
#define VTYPE		int

// Constructors/Destructors
Vector3DI::Vector3DI() { x = 0; y = 0; z = 0; }
Vector3DI::Vector3DI(const VTYPE xa, const VTYPE ya, const VTYPE za) { x = xa; y = ya; z = za; }
Vector3DI::Vector3DI(const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DI::Vector3DI(const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DI::Vector3DI(const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DI::Vector3DI(const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DI::Vector3DI(const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DI::Vector3DI(const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DI::Vector3DI(const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }

// Set Functions
Vector3DI &Vector3DI::Set(const int xa, const int ya, const int za)
{
	x = xa; y = ya; z = za;
	return *this;
}

// Member Functions
Vector3DI &Vector3DI::operator= (const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator= (const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator= (const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator= (const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator= (const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator= (const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator= (const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }

Vector3DI &Vector3DI::operator+= (const Vector2DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator+= (const Vector2DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator+= (const Vector2DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator+= (const Vector3DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator+= (const Vector3DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator+= (const Vector3DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator+= (const Vector4DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }

Vector3DI &Vector3DI::operator-= (const Vector2DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator-= (const Vector2DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator-= (const Vector2DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator-= (const Vector3DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator-= (const Vector3DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator-= (const Vector3DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator-= (const Vector4DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }

Vector3DI &Vector3DI::operator*= (const Vector2DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator*= (const Vector2DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator*= (const Vector2DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator*= (const Vector3DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator*= (const Vector3DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator*= (const Vector3DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator*= (const Vector4DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }

Vector3DI &Vector3DI::operator/= (const Vector2DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator/= (const Vector2DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator/= (const Vector2DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DI &Vector3DI::operator/= (const Vector3DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator/= (const Vector3DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator/= (const Vector3DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DI &Vector3DI::operator/= (const Vector4DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }

Vector3DI &Vector3DI::Cross(const Vector3DC &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }
Vector3DI &Vector3DI::Cross(const Vector3DI &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }
Vector3DI &Vector3DI::Cross(const Vector3DF &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }

double Vector3DI::Dot(const Vector3DC &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }
double Vector3DI::Dot(const Vector3DI &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }
double Vector3DI::Dot(const Vector3DF &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }

double Vector3DI::Dist(const Vector2DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DI::Dist(const Vector2DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DI::Dist(const Vector2DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DI::Dist(const Vector3DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DI::Dist(const Vector3DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DI::Dist(const Vector3DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DI::Dist(const Vector4DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DI::DistSq(const Vector2DC &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DI::DistSq(const Vector2DI &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DI::DistSq(const Vector2DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DI::DistSq(const Vector3DC &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DI::DistSq(const Vector3DI &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DI::DistSq(const Vector3DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DI::DistSq(const Vector4DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }

Vector3DI &Vector3DI::Normalize(void) {
	double n = (double)x*x + (double)y*y + (double)z*z;
	if (n != 0.0) {
		n = sqrt(n);
		x = (VTYPE)(((double)x * 255) / n);
		y = (VTYPE)(((double)y * 255) / n);
		z = (VTYPE)(((double)z * 255) / n);
	}
	return *this;
}
double Vector3DI::Length(void) { double n; n = (double)x*x + (double)y*y + (double)z*z; if (n != 0.0) return sqrt(n); return 0.0; }


#undef VTYPE
#undef VNAME

// Vector3DF Code Definition

#define VNAME		3DF
#define VTYPE		float

Vector3DF::Vector3DF(const VTYPE xa, const VTYPE ya, const VTYPE za) { x = xa; y = ya; z = za; }
Vector3DF::Vector3DF(const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DF::Vector3DF(const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DF::Vector3DF(const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; }
Vector3DF::Vector3DF(const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DF::Vector3DF(const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DF::Vector3DF(const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }
Vector3DF::Vector3DF(const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; }

// Set Functions
Vector3DF &Vector3DF::Set(const VTYPE xa, const VTYPE ya, const VTYPE za)
{
	x = (float)xa; y = (float)ya; z = (float)za;
	return *this;
}

// Member Functions
Vector3DF &Vector3DF::operator= (const int op) { x = (VTYPE)op; y = (VTYPE)op; z = (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator= (const double op) { x = (VTYPE)op; y = (VTYPE)op; z = (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator= (const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator= (const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator= (const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator= (const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator= (const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator= (const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator= (const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; return *this; }

Vector3DF &Vector3DF::operator+= (const int op) { x += (VTYPE)op; y += (VTYPE)op; z += (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator+= (const double op) { x += (VTYPE)op; y += (VTYPE)op; z += (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator+= (const Vector2DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator+= (const Vector2DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator+= (const Vector2DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator+= (const Vector3DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator+= (const Vector3DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator+= (const Vector3DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator+= (const Vector4DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }

Vector3DF &Vector3DF::operator-= (const int op) { x -= (VTYPE)op; y -= (VTYPE)op; z -= (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator-= (const double op) { x -= (VTYPE)op; y -= (VTYPE)op; z -= (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator-= (const Vector2DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator-= (const Vector2DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator-= (const Vector2DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator-= (const Vector3DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator-= (const Vector3DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator-= (const Vector3DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator-= (const Vector4DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }

Vector3DF &Vector3DF::operator*= (const int op) { x *= (VTYPE)op; y *= (VTYPE)op; z *= (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator*= (const double op) { x *= (VTYPE)op; y *= (VTYPE)op; z *= (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator*= (const Vector2DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator*= (const Vector2DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator*= (const Vector2DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator*= (const Vector3DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator*= (const Vector3DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator*= (const Vector3DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator*= (const Vector4DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }

Vector3DF &Vector3DF::operator/= (const int op) { x /= (VTYPE)op; y /= (VTYPE)op; z /= (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator/= (const double op) { x /= (VTYPE)op; y /= (VTYPE)op; z /= (VTYPE)op; return *this; }
Vector3DF &Vector3DF::operator/= (const Vector2DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator/= (const Vector2DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator/= (const Vector2DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector3DF &Vector3DF::operator/= (const Vector3DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator/= (const Vector3DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator/= (const Vector3DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector3DF &Vector3DF::operator/= (const Vector4DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }

Vector3DF &Vector3DF::Cross(const Vector3DC &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }
Vector3DF &Vector3DF::Cross(const Vector3DI &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }
Vector3DF &Vector3DF::Cross(const Vector3DF &v) { double ax = x, ay = y, az = z; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); return *this; }

double Vector3DF::Dot(const Vector3DC &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }
double Vector3DF::Dot(const Vector3DI &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }
double Vector3DF::Dot(const Vector3DF &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z; return dot; }

double Vector3DF::Dist(const Vector2DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DF::Dist(const Vector2DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DF::Dist(const Vector2DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DF::Dist(const Vector3DC &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DF::Dist(const Vector3DI &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DF::Dist(const Vector3DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DF::Dist(const Vector4DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }
double Vector3DF::DistSq(const Vector2DC &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DF::DistSq(const Vector2DI &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DF::DistSq(const Vector2DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z; return (a*a + b*b + c*c); }
double Vector3DF::DistSq(const Vector3DC &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DF::DistSq(const Vector3DI &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DF::DistSq(const Vector3DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }
double Vector3DF::DistSq(const Vector4DF &v)		{ double a, b, c; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; return (a*a + b*b + c*c); }

Vector3DF &Vector3DF::Normalize(void) {
	double n = (double)x*x + (double)y*y + (double)z*z;
	if (n != 0.0) {
		n = sqrt(n);
		x /= (float)n; y /= (float)n; z /= (float)n;
	}
	return *this;
}
double Vector3DF::Length(void) { double n; n = (double)x*x + (double)y*y + (double)z*z; if (n != 0.0) return sqrt(n); return 0.0; }


#undef VTYPE
#undef VNAME

// Vector4DF Code Definition

#define VNAME		4DF
#define VTYPE		float

// Constructors/Destructors
Vector4DF::Vector4DF(const VTYPE xa, const VTYPE ya, const VTYPE za, const VTYPE wa) { x = xa; y = ya; z = za; w = wa; }
Vector4DF::Vector4DF(const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; w = (VTYPE)0; }
Vector4DF::Vector4DF(const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; w = (VTYPE)0; }
Vector4DF::Vector4DF(const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; w = (VTYPE)0; }
Vector4DF::Vector4DF(const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; w = (VTYPE)0; }
Vector4DF::Vector4DF(const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; w = (VTYPE)0; }
Vector4DF::Vector4DF(const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; w = (VTYPE)0; }
Vector4DF::Vector4DF(const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; w = (VTYPE)op.w; }

// Member Functions
Vector4DF &Vector4DF::operator= (const int op) { x = (VTYPE)op; y = (VTYPE)op; z = (VTYPE)op; w = (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator= (const double op) { x = (VTYPE)op; y = (VTYPE)op; z = (VTYPE)op; w = (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator= (const Vector2DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; w = (VTYPE)0; return *this; }
Vector4DF &Vector4DF::operator= (const Vector2DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; w = (VTYPE)0;  return *this; }
Vector4DF &Vector4DF::operator= (const Vector2DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)0; w = (VTYPE)0;  return *this; }
Vector4DF &Vector4DF::operator= (const Vector3DC &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; w = (VTYPE)0;  return *this; }
Vector4DF &Vector4DF::operator= (const Vector3DI &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; w = (VTYPE)0;  return *this; }
Vector4DF &Vector4DF::operator= (const Vector3DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; w = (VTYPE)0; return *this; }
Vector4DF &Vector4DF::operator= (const Vector4DF &op) { x = (VTYPE)op.x; y = (VTYPE)op.y; z = (VTYPE)op.z; w = (VTYPE)op.w; return *this; }

Vector4DF &Vector4DF::operator+= (const int op) { x += (VTYPE)op; y += (VTYPE)op; z += (VTYPE)op; w += (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator+= (const double op) { x += (VTYPE)op; y += (VTYPE)op; z += (VTYPE)op; w += (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator+= (const Vector2DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator+= (const Vector2DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator+= (const Vector2DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator+= (const Vector3DC &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator+= (const Vector3DI &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator+= (const Vector3DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator+= (const Vector4DF &op) { x += (VTYPE)op.x; y += (VTYPE)op.y; z += (VTYPE)op.z; w += (VTYPE)op.w; return *this; }

Vector4DF &Vector4DF::operator-= (const int op) { x -= (VTYPE)op; y -= (VTYPE)op; z -= (VTYPE)op; w -= (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator-= (const double op) { x -= (VTYPE)op; y -= (VTYPE)op; z -= (VTYPE)op; w -= (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator-= (const Vector2DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator-= (const Vector2DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator-= (const Vector2DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator-= (const Vector3DC &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator-= (const Vector3DI &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator-= (const Vector3DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator-= (const Vector4DF &op) { x -= (VTYPE)op.x; y -= (VTYPE)op.y; z -= (VTYPE)op.z; w -= (VTYPE)op.w; return *this; }

Vector4DF &Vector4DF::operator*= (const int op) { x *= (VTYPE)op; y *= (VTYPE)op; z *= (VTYPE)op; w *= (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator*= (const double op) { x *= (VTYPE)op; y *= (VTYPE)op; z *= (VTYPE)op; w *= (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator*= (const Vector2DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator*= (const Vector2DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator*= (const Vector2DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator*= (const Vector3DC &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator*= (const Vector3DI &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator*= (const Vector3DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator*= (const Vector4DF &op) { x *= (VTYPE)op.x; y *= (VTYPE)op.y; z *= (VTYPE)op.z; w *= (VTYPE)op.w; return *this; }

Vector4DF &Vector4DF::operator/= (const int op) { x /= (VTYPE)op; y /= (VTYPE)op; z /= (VTYPE)op; w /= (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator/= (const double op) { x /= (VTYPE)op; y /= (VTYPE)op; z /= (VTYPE)op; w /= (VTYPE)op; return *this; }
Vector4DF &Vector4DF::operator/= (const Vector2DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator/= (const Vector2DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator/= (const Vector2DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; return *this; }
Vector4DF &Vector4DF::operator/= (const Vector3DC &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator/= (const Vector3DI &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator/= (const Vector3DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; return *this; }
Vector4DF &Vector4DF::operator/= (const Vector4DF &op) { x /= (VTYPE)op.x; y /= (VTYPE)op.y; z /= (VTYPE)op.z; w /= (VTYPE)op.w; return *this; }

Vector4DF &Vector4DF::Cross(const Vector4DF &v) { double ax = x, ay = y, az = z, aw = w; x = (VTYPE)(ay * (double)v.z - az * (double)v.y); y = (VTYPE)(-ax * (double)v.z + az * (double)v.x); z = (VTYPE)(ax * (double)v.y - ay * (double)v.x); w = (VTYPE)0; return *this; }

double Vector4DF::Dot(const Vector4DF &v)			{ double dot; dot = (double)x*v.x + (double)y*v.y + (double)z*v.z + (double)w*v.w; return dot; }

double Vector4DF::Dist(const Vector4DF &v)		{ double distsq = DistSq(v); if (distsq != 0) return sqrt(distsq); return 0.0; }

double Vector4DF::DistSq(const Vector4DF &v)		{ double a, b, c, d; a = (double)x - (double)v.x; b = (double)y - (double)v.y; c = (double)z - (double)v.z; d = (double)w - (double)v.w; return (a*a + b*b + c*c + d*d); }

Vector4DF &Vector4DF::Normalize(void) {
	double n = (double)x*x + (double)y*y + (double)z*z + (double)w*w;
	if (n != 0.0) {
		n = sqrt(n);
		x /= (float)n; y /= (float)n; z /= (float)n; w /= (float)n;
	}
	return *this;
}
double Vector4DF::Length(void) { double n; n = (double)x*x + (double)y*y + (double)z*z + (double)w*w; if (n != 0.0) return sqrt(n); return 0.0; }

#undef VTYPE
#undef VNAME

// MatrixC Code Definition
#define VNAME		C
#define VTYPE		unsigned char

// Constructors/Destructors

MatrixC::MatrixC(void) { data = NULL; Resize(0, 0); }
MatrixC::~MatrixC(void) { if (data != NULL) delete[] data; }
MatrixC::MatrixC(int r, int c) { data = NULL; Resize(c, r); }

// Member Functions


VTYPE &MatrixC::operator () (int c, int r)
{
#ifdef DEBUG_MATRIX
	if (data == NULL) Error.Print(ErrorLev::Matrix, ErrorDef::MatrixIsNull, true);
	if (r < 0 || r >= rows) Error.Print(ErrorLev::Matrix, ErrorDef::RowOutOfBounds, true);
	if (c < 0 || c >= cols) Error.Print(ErrorLev::Matrix, ErrorDef::ColOutOfBounds, true);
#endif
	return *(data + (r*cols + c));
}
MatrixC &MatrixC::operator= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixC &MatrixC::operator= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixC &MatrixC::operator= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixC &MatrixC::operator= (MatrixC &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	memcpy(data, op.data, len);	// Use only for matricies of like types
	return *this;
}
MatrixC &MatrixC::operator= (MatrixI &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ = (VTYPE)*b++;
	//memcpy (data, op.data, len);	// Use only for matricies of like types
	return *this;
}
MatrixC &MatrixC::operator= (MatrixF &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne; n++, b++) {
		if (*b > 255) {
			*n = (VTYPE)255;
		}
		else if (*b <= 0) {
			*n = (VTYPE)0;
		}
		else {
			*n = (VTYPE)*b;
		}
	}
	return *this;
}

MatrixC &MatrixC::operator+= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixC &MatrixC::operator+= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixC &MatrixC::operator+= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixC &MatrixC::operator+= (MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne; n++)
		*n++ += *b++;
	return *this;
}
MatrixC &MatrixC::operator+= (MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ += (VTYPE)*b++;
	return *this;
}
MatrixC &MatrixC::operator+= (MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m+=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ += (VTYPE)*b++;
	return *this;
}

MatrixC &MatrixC::operator-= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixC &MatrixC::operator-= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixC &MatrixC::operator-= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixC &MatrixC::operator-= (MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}
MatrixC &MatrixC::operator-= (MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}
MatrixC &MatrixC::operator-= (MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m-=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}

MatrixC &MatrixC::operator*= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ *= (VTYPE)op; return *this; }
MatrixC &MatrixC::operator*= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ *= (VTYPE)op; return *this; }
MatrixC &MatrixC::operator*= (double op)			{
	VTYPE *n = data, *nlen = data + len;
	for (; n < nlen;) *n++ *= (VTYPE)op;
	return *this;
}
MatrixC &MatrixC::operator*= (MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}
MatrixC &MatrixC::operator*= (MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}
MatrixC &MatrixC::operator*= (MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m*=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}

MatrixC &MatrixC::operator/= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixC &MatrixC::operator/= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixC &MatrixC::operator/= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixC &MatrixC::operator/= (MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) if (*b != (VTYPE)0) { *n++ /= (VTYPE)*b++; }
	else { *n++ = (VTYPE)0; b++; }
	return *this;
}
MatrixC &MatrixC::operator/= (MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;)  if (*b != (VTYPE)0) { *n++ /= (VTYPE)*b++; }
	else { *n++ = (VTYPE)0; b++; }
	return *this;
}
MatrixC &MatrixC::operator/= (MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixC::m/=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;)  if (*b != (VTYPE)0) { *n++ /= (VTYPE)*b++; }
	else { *n++ = (VTYPE)0; b++; }
	return *this;
}

MatrixC &MatrixC::Multiply(MatrixF &op) {
#ifdef DEBUG_MATRIX 
	if (data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixC::m mult op: Matrix data is null\n");
	if (op.data == NULL)					Debug.Print(DEBUG_MATRIX, "MatrixC::m mult op: Operand matrix (op) data is null\n");
	if (cols != op.rows)					Debug.Print(DEBUG_MATRIX, "MatrixC::m mult op: Matricies not compatible (m.cols != op.rows)\n");
#endif
	if (cols == op.rows) {
		VTYPE *newdata, *n, *ne, *a, *as;		// Pointers into A and new A matricies
		double *b, *bs, *bce, *be;				// Pointers into B matrix
		int newr = rows, newc = op.cols;		// Set new rows and columns
		int newlen = newr * newc;				// Determine new matrix size
		newdata = new VTYPE[newlen];			// Allocate new matrix to hold multiplication
		//		if (newdata==NULL)						{debug.Print ( (char*) "MatrixF::m*=op: Cannot allocate new matrix.\n"); exit(-1);}
		ne = newdata + newlen;					// Calculate end of new matrix
		int bskip = op.cols;					// Calculate row increment for B matrix	
		bce = op.data + bskip;					// Calculate end of first row in B matrix
		be = op.data + op.rows*op.cols;			// Calculate end of B matrix	
		as = data; bs = op.data;				// Goto start of A and B matricies
		for (n = newdata; n < ne;) {				// Compute C = A*B		
			a = as; b = bs;						// Goto beginning of row in A, top of col in B
			*n = (VTYPE)0;						// Initialize n element in C
			for (; b < be;) { *n += (VTYPE)((*a++) * (*b)); b += bskip; }	// Compute n element in C
			if (++bs >= bce) {					// If last col in B..
				bs = op.data;					// Go back to first column in B
				as += cols;					// Goto next row in A
			}
			n++;								// Goto next element in C
		}
		delete[] data;							// Destroy old A matrix
		data = newdata; rows = newr; cols = newc; len = newlen;		// Replace with new A matrix	
	}
	return *this;
}

MatrixC &MatrixC::Resize(int x, int y)
{
	if (data != NULL) {
		if (rows != y || cols != x) {
			delete[] data;
			len = (rows = y) * (cols = x);
			data = new VTYPE[len];
		}
	}
	else {
		len = (rows = y) * (cols = x); data = new VTYPE[len];
	}
#ifdef DEBUG_MATRIX
	if (data == NULL) Debug.Print(DEBUG_MATRIX, "MatrixC::Resize: Out of memory for construction.\n");
#endif	
#ifdef MATRIX_INITIALIZE
	memset(data, 0, sizeof(VTYPE)*len);
#endif		
	return *this;
}
MatrixC &MatrixC::ResizeSafe(int x, int y)
{
	VTYPE *newdata;
	int newlen;
	VTYPE *n, *ne;
	VTYPE *b, *be;
	int bskip;


	if (data != NULL) {
		newlen = x*y;
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixC::SizeSafe: Out of memory for construction.\n");
#endif		
		if (y >= rows && x >= cols) {			// New size is larger (in both r and c)			
			memset(newdata, 0, newlen*sizeof(VTYPE));	// Clear new matrix
			ne = data + len;					// Calculate end of current matrix
			b = newdata;						// Start of new matrix
			be = newdata + cols;				// Last filled column+1 in new matrix
			bskip = x - cols;
			for (n = data; n < ne;) {				// Fill new matrix with old
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += x;
			}
		}
		else if (y < rows && x < cols) {		// New size is smaller (in both r and c)
			ne = newdata + newlen;			// Calculate end of new matrix
			b = data;						// Start of old matrix
			be = data + x;					// Last retrieved column+1 in old matrix
			bskip = cols - x;
			for (n = newdata; n < ne;) {		// Fill new matrix with old
				for (; b < be;) *n++ = *b++;
				b += bskip;
				be += x;
			}
		}
		else {							// Asymetrical resize
#ifdef DEBUG_MATRIX
			Debug.Print(DEBUG_MATRIX, "MatrixC::SizeSafe: Asymetrical resize NOT YET IMPLEMENTED.\n");
#endif
			exit(202);
		}
		delete[] data;
		rows = y; cols = x;
		data = newdata; len = newlen;
	}
	else {
		len = (rows = y) * (cols = x);
		data = new VTYPE[len];
#ifdef DEBUG_MATRIX
		if (data == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixC::SizeSafe: Out of memory for construction.\n");
#endif
	}
	return *this;
}
MatrixC &MatrixC::InsertRow(int r)
{
	VTYPE *newdata;
	VTYPE *r_src, *r_dest;
	int newlen;

	if (data != NULL) {
		newlen = (rows + 1)*cols;
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixC::InsertRow: Out of memory for construction.\n");
#endif
		memcpy(newdata, data, r*cols*sizeof(VTYPE));
		if (r < rows) {
			r_src = data + r*cols;
			r_dest = newdata + (r + 1)*cols;
			if (r < rows) memcpy(r_dest, r_src, (rows - r)*cols*sizeof(VTYPE));
		}
		r_dest = newdata + r*cols;
		memset(r_dest, 0, cols*sizeof(VTYPE));
		rows++;
		delete[] data;
		data = newdata; len = newlen;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixC::InsertRow: Cannot insert row in a null matrix.\n");
#endif
	}
	return *this;
}
MatrixC &MatrixC::InsertCol(int c)
{
	VTYPE *newdata;
	int newlen;

	if (data != NULL) {
		newlen = rows*(cols + 1);
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixC::InsertCol: Out of memory for construction.\n");
#endif
		VTYPE *n, *ne;
		VTYPE *b, *be;
		int bskip, nskip;

		if (c > 0) {
			n = data;							// Copy columns to left of c
			ne = data + len;
			nskip = (cols - c);
			b = newdata;
			be = newdata + c;
			bskip = (cols - c) + 1;
			for (; n < ne;) {
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += (cols + 1);
				n += nskip;
			}
		}
		if (c < cols) {
			n = data + c;						// Copy columns to right of c
			ne = data + len;
			nskip = c;
			b = newdata + (c + 1);
			be = newdata + (cols + 1);
			bskip = c + 1;
			for (; n < ne;) {
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += (cols + 1);
				n += nskip;
			}
		}
		cols++;
		for (n = newdata + c, ne = newdata + len; n < ne; n += cols) *n = (VTYPE)0;
		delete[] data;
		data = newdata; len = newlen;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixF::InsertCol: Cannot insert col in a null matrix.\n");
#endif
	}
	return *this;
}
MatrixC &MatrixC::Transpose(void)
{
	VTYPE *newdata = NULL;
	int r = rows;

	if (data != NULL) {
		if (rows == 1) {
			rows = cols; cols = 1;
		}
		else if (cols == 1) {
			cols = rows; rows = 1;
		}
		else {
			newdata = new VTYPE[len];
#ifdef DEBUG_MATRIX
			if (newdata == NULL)
				Debug.Print(DEBUG_MATRIX, "MatrixF::Transpose: Out of memory for construction.\n");
#endif	
			VTYPE *n, *ne;
			VTYPE *b, *be;
			n = data;						// Goto start of old matrix
			ne = data + len;
			b = newdata;					// Goto start of new matrix
			be = newdata + len;
			for (; n < ne;) {				// Copy rows of old to columns of new
				for (; b < be; b += r) *b = *n++;
				b -= len;
				b++;
			}
		}
		delete[] data;
		data = newdata;
		rows = cols; cols = r;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixC::Transpose: Cannot transpose a null matrix.\n");
#endif
	}
	return *this;
}
MatrixC &MatrixC::Identity(int order)
{
	Resize(order, order);
	VTYPE *n, *ne;
	memset(data, 0, len*sizeof(VTYPE));	// Fill matrix with zeros
	n = data;
	ne = data + len;
	for (; n < ne;) {
		*n = 1;								// Set diagonal element to 1
		n += cols;
		n++;								// Next diagonal element
	}
	return *this;
}

MatrixC &MatrixC::Basis(Vector3DF &c1, Vector3DF &c2, Vector3DF &c3)
{
	Resize(4, 4);
	VTYPE *n = data;
	*n++ = (VTYPE)c1.x; *n++ = (VTYPE)c2.x; *n++ = (VTYPE)c3.x; *n++ = (VTYPE)0;
	*n++ = (VTYPE)c1.y; *n++ = (VTYPE)c2.y; *n++ = (VTYPE)c3.y; *n++ = (VTYPE)0;
	*n++ = (VTYPE)c1.z; *n++ = (VTYPE)c2.z; *n++ = (VTYPE)c3.z; *n++ = (VTYPE)0;
	*n++ = (VTYPE)0; *n++ = (VTYPE)0; *n++ = (VTYPE)0; *n++ = (VTYPE)0;
	return *this;
}
MatrixC &MatrixC::GaussJordan(MatrixF &b)
{
	// Gauss-Jordan solves the matrix equation Ax = b
	// Given the problem:
	//		A*x = b		(where A is 'this' matrix and b is provided)
	// The solution is:
	//		Ainv*b = x
	// This function returns Ainv in A and x in b... that is:
	//		A (this) -> Ainv
	//		b -> solution x
	//

#ifdef DEBUG_MATRIX
	Debug.Print(DEBUG_MATRIX, "MatrixC::GaussJordan: Not implemented for char matrix\n");
#endif
	return *this;
}
int MatrixC::GetX()						{ return cols; }
int MatrixC::GetY()						{ return rows; }
int MatrixC::GetRows(void)				{ return rows; }
int MatrixC::GetCols(void)				{ return cols; }
int MatrixC::GetLength(void)				{ return len; }
VTYPE *MatrixC::GetData(void)			{ return data; }

double MatrixC::GetF(int r, int c)		{ return (double)(*(data + r*cols + c)); }

#undef VTYPE
#undef VNAME

// MatrixI Code Definition
#define VNAME		I
#define VTYPE		int

// Constructors/Destructors

MatrixI::MatrixI(void) { data = NULL; Resize(0, 0); }
MatrixI::~MatrixI(void) { if (data != NULL) delete[] data; }
MatrixI::MatrixI(int r, int c) { data = NULL; Resize(c, r); }

// Member Functions

VTYPE &MatrixI::operator () (int c, int r)
{
#ifdef DEBUG_MATRIX
	if (data == NULL) Debug.Print(DEBUG_MATRIX, "MatrixI::op(): Matrix data is null\n");
	if (r < 0 || r >= rows) Debug.Print(DEBUG_MATRIX, "MatrixI:op(): Row is out of bounds\n");
	if (c < 0 || c >= cols) Debug.Print(DEBUG_MATRIX, "MatrixI:op(): Col is out of bounds\n");
#endif
	return *(data + (r*cols + c));
}
MatrixI &MatrixI::operator= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixI &MatrixI::operator= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixI &MatrixI::operator= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixI &MatrixI::operator= (MatrixC &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ = (VTYPE)*b++;
	// memcpy (data, op.data, len);	// Use only for matricies of like types
	return *this;
}
MatrixI &MatrixI::operator= (MatrixI &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	memcpy(data, op.data, len);	// Use only for matricies of like types
	return *this;
}
MatrixI &MatrixI::operator= (MatrixF &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ = (VTYPE)*b++;
	//memcpy (data, op.data, len);	
	return *this;
}

MatrixI &MatrixI::operator+= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixI &MatrixI::operator+= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixI &MatrixI::operator+= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixI &MatrixI::operator+= (MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ += (VTYPE)*b++;
	return *this;
}
MatrixI &MatrixI::operator+= (MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ += (VTYPE)*b++;
	return *this;
}
MatrixI &MatrixI::operator+= (MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m+=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ += (VTYPE)*b++;
	return *this;
}

MatrixI &MatrixI::operator-= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator-= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator-= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator-= (MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}
MatrixI &MatrixI::operator-= (MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}
MatrixI &MatrixI::operator-= (MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m-=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}

MatrixI &MatrixI::operator*= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ *= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator*= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ *= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator*= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ *= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator*= (MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}
MatrixI &MatrixI::operator*= (MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}
MatrixI &MatrixI::operator*= (MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m*=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}

MatrixI &MatrixI::operator/= (unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator/= (int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator/= (double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixI &MatrixI::operator/= (MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) if (*b != (VTYPE)0) { *n++ /= (VTYPE)*b++; }
	else { *n++ = (VTYPE)0; b++; }
	return *this;
}
MatrixI &MatrixI::operator/= (MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) if (*b != (VTYPE)0) { *n++ /= (VTYPE)*b++; }
	else { *n++ = (VTYPE)0; b++; }
	return *this;
}
MatrixI &MatrixI::operator/= (MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixI::m/=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) if (*b != (VTYPE)0) { *n++ /= (VTYPE)*b++; }
	else { *n++ = (VTYPE)0; b++; }
	return *this;
}

MatrixI &MatrixI::Multiply(MatrixF &op) {
#ifdef DEBUG_MATRIX 
	if (data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixI::m mult op: Matrix data is null\n");
	if (op.data == NULL)					Debug.Print(DEBUG_MATRIX, "MatrixI::m mult op: Operand matrix (op) data is null\n");
	if (cols != op.rows)					Debug.Print(DEBUG_MATRIX, "MatrixI::m mult op: Matricies not compatible (m.cols != op.rows)\n");
#endif
	if (cols == op.rows) {
		VTYPE *newdata, *n, *ne, *a, *as;		// Pointers into A and new A matricies
		double *b, *bs, *bce, *be;				// Pointers into B matrix
		int newr = rows, newc = op.cols;		// Set new rows and columns
		int newlen = newr * newc;				// Determine new matrix size
		newdata = new VTYPE[newlen];			// Allocate new matrix to hold multiplication
		//		if (newdata==NULL)						{debug.Print ((char*) "MatrixF::m*=op: Cannot allocate new matrix.\n"); exit(-1);}
		ne = newdata + newlen;					// Calculate end of new matrix
		int bskip = op.cols;					// Calculate row increment for B matrix	
		bce = op.data + bskip;					// Calculate end of first row in B matrix
		be = op.data + op.rows*op.cols;			// Calculate end of B matrix	
		as = data; bs = op.data;				// Goto start of A and B matricies
		for (n = newdata; n < ne;) {				// Compute C = A*B		
			a = as; b = bs;						// Goto beginning of row in A, top of col in B
			*n = (VTYPE)0;						// Initialize n element in C
			for (; b < be;) { *n += (VTYPE)((*a++) * (*b)); b += bskip; }	// Compute n element in C
			if (++bs >= bce) {					// If last col in B..
				bs = op.data;					// Go back to first column in B
				as += cols;					// Goto next row in A
			}
			n++;								// Goto next element in C
		}
		delete[] data;							// Destroy old A matrix
		data = newdata; rows = newr; cols = newc; len = newlen;		// Replace with new A matrix	
	}
	return *this;
}

MatrixI &MatrixI::Resize(int x, int y)
{
	if (data != NULL) {
		if (rows != y || cols != x) { delete[] data;	len = (rows = y) * (cols = x); data = new VTYPE[len]; }
	}
	else {
		len = (rows = y) * (cols = x); data = new VTYPE[len];
	}
#ifdef DEBUG_MATRIX
	if (data == NULL) Debug.Print(DEBUG_MATRIX, "MatrixC::Size: Out of memory for construction.\n");
#endif	
#ifdef MATRIX_INITIALIZE
	memset(data, 0, sizeof(VTYPE)*len);
#endif		
	return *this;
}
MatrixI &MatrixI::ResizeSafe(int x, int y)
{
	VTYPE *newdata;
	int newlen;
	VTYPE *n, *ne;
	VTYPE *b, *be;
	int bskip;


	if (data != NULL) {
		newlen = x*y;
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixC::SizeSafe: Out of memory for construction.\n");
#endif		
		if (y >= rows && x >= cols) {			// New size is larger (in both r and c)			
			memset(newdata, 0, newlen*sizeof(VTYPE));	// Clear new matrix
			ne = data + len;					// Calculate end of current matrix
			b = newdata;						// Start of new matrix
			be = newdata + cols;				// Last filled column+1 in new matrix
			bskip = x - cols;
			for (n = data; n < ne;) {				// Fill new matrix with old
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += x;
			}
		}
		else if (y < rows && x < cols) {		// New size is smaller (in both r and c)
			ne = newdata + newlen;			// Calculate end of new matrix
			b = data;						// Start of old matrix
			be = data + x;					// Last retrieved column+1 in old matrix
			bskip = cols - x;
			for (n = newdata; n < ne;) {		// Fill new matrix with old
				for (; b < be;) *n++ = *b++;
				b += bskip;
				be += x;
			}
		}
		else {							// Asymetrical resize
#ifdef DEBUG_MATRIX
			Debug.Print(DEBUG_MATRIX, "MatrixC::SizeSafe: Asymetrical resize NOT YET IMPLEMENTED.\n");
#endif
			exit(202);
		}
		delete[] data;
		rows = y; cols = x;
		data = newdata; len = newlen;
	}
	else {
		len = (rows = y) * (cols = x);
		data = new VTYPE[len];
#ifdef DEBUG_MATRIX
		if (data == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixC::SizeSafe: Out of memory for construction.\n");
#endif
	}
	return *this;
}
MatrixI &MatrixI::InsertRow(int r)
{
	VTYPE *newdata;
	VTYPE *r_src, *r_dest;
	int newlen;

	if (data != NULL) {
		newlen = (rows + 1)*cols;
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixC::InsertRow: Out of memory for construction.\n");
#endif
		memcpy(newdata, data, r*cols*sizeof(VTYPE));
		if (r < rows) {
			r_src = data + r*cols;
			r_dest = newdata + (r + 1)*cols;
			if (r < rows) memcpy(r_dest, r_src, (rows - r)*cols*sizeof(VTYPE));
		}
		r_dest = newdata + r*cols;
		memset(r_dest, 0, cols*sizeof(VTYPE));
		rows++;
		delete[] data;
		data = newdata; len = newlen;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixC::InsertRow: Cannot insert row in a null matrix.\n");
#endif
	}
	return *this;
}
MatrixI &MatrixI::InsertCol(int c)
{
	VTYPE *newdata;
	int newlen;

	if (data != NULL) {
		newlen = rows*(cols + 1);
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixC::InsertCol: Out of memory for construction.\n");
#endif
		VTYPE *n, *ne;
		VTYPE *b, *be;
		int bskip, nskip;

		if (c > 0) {
			n = data;							// Copy columns to left of c
			ne = data + len;
			nskip = (cols - c);
			b = newdata;
			be = newdata + c;
			bskip = (cols - c) + 1;
			for (; n < ne;) {
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += (cols + 1);
				n += nskip;
			}
		}
		if (c < cols) {
			n = data + c;						// Copy columns to right of c
			ne = data + len;
			nskip = c;
			b = newdata + (c + 1);
			be = newdata + (cols + 1);
			bskip = c + 1;
			for (; n < ne;) {
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += (cols + 1);
				n += nskip;
			}
		}
		cols++;
		for (n = newdata + c, ne = newdata + len; n < ne; n += cols) *n = (VTYPE)0;
		delete[] data;
		data = newdata; len = newlen;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixI::InsertCol: Cannot insert col in a null matrix.\n");
#endif
	}
	return *this;
}
MatrixI &MatrixI::Transpose(void)
{
	VTYPE *newdata = NULL;
	int r = rows;

	if (data != NULL) {
		if (rows == 1) {
			rows = cols; cols = 1;
		}
		else if (cols == 1) {
			cols = rows; rows = 1;
		}
		else {
			newdata = new VTYPE[len];
#ifdef DEBUG_MATRIX
			if (newdata == NULL)
				Debug.Print(DEBUG_MATRIX, "MatrixF::Transpose: Out of memory for construction.\n");
#endif	
			VTYPE *n, *ne;
			VTYPE *b, *be;
			n = data;						// Goto start of old matrix
			ne = data + len;
			b = newdata;					// Goto start of new matrix
			be = newdata + len;
			for (; n < ne;) {				// Copy rows of old to columns of new
				for (; b < be; b += r) *b = *n++;
				b -= len;
				b++;
			}
		}
		delete[] data;
		data = newdata;
		rows = cols; cols = r;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixC::Transpose: Cannot transpose a null matrix.\n");
#endif
	}
	return *this;
}
MatrixI &MatrixI::Identity(int order)
{
	Resize(order, order);
	VTYPE *n, *ne;
	memset(data, 0, len*sizeof(VTYPE));	// Fill matrix with zeros
	n = data;
	ne = data + len;
	for (; n < ne;) {
		*n = 1;								// Set diagonal element to 1
		n += cols;
		n++;								// Next diagonal element
	}
	return *this;
}
MatrixI &MatrixI::Basis(Vector3DF &c1, Vector3DF &c2, Vector3DF &c3)
{
	Resize(4, 4);
	VTYPE *n = data;
	*n++ = (VTYPE)c1.x; *n++ = (VTYPE)c2.x; *n++ = (VTYPE)c3.x; *n++ = (VTYPE)0;
	*n++ = (VTYPE)c1.y; *n++ = (VTYPE)c2.y; *n++ = (VTYPE)c3.y; *n++ = (VTYPE)0;
	*n++ = (VTYPE)c1.z; *n++ = (VTYPE)c2.z; *n++ = (VTYPE)c3.z; *n++ = (VTYPE)0;
	*n++ = (VTYPE)0; *n++ = (VTYPE)0; *n++ = (VTYPE)0; *n++ = (VTYPE)0;
	return *this;
}
MatrixI &MatrixI::GaussJordan(MatrixF &b)
{
	// Gauss-Jordan solves the matrix equation Ax = b
	// Given the problem:
	//		A*x = b		(where A is 'this' matrix and b is provided)
	// The solution is:
	//		Ainv*b = x
	// This function returns Ainv in A and x in b... that is:
	//		A (this) -> Ainv
	//		b -> solution x
	//

#ifdef DEBUG_MATRIX
	Debug.Print(DEBUG_MATRIX, "MatrixI::GaussJordan: Not implemented for int matrix\n");
#endif	
	return *this;
}
int MatrixI::GetX()						{ return cols; }
int MatrixI::GetY()						{ return rows; }
int MatrixI::GetRows(void)				{ return rows; }
int MatrixI::GetCols(void)				{ return cols; }
int MatrixI::GetLength(void)			{ return len; }
VTYPE *MatrixI::GetData(void)			{ return data; }

double MatrixI::GetF(int r, int c)		{ return (double)(*(data + r*cols + c)); }

#undef VTYPE
#undef VNAME


// MatrixF Code Definition
#define VNAME		F
#define VTYPE		double

// Constructors/Destructors

MatrixF::MatrixF(void) { data = NULL; Resize(0, 0); }

MatrixF::~MatrixF(void) {
	if (data != NULL)
		delete[] data;
}
MatrixF::MatrixF(const int r, const int c) { data = NULL; Resize(r, c); }

// Member Functions

VTYPE MatrixF::GetVal(int c, int r)
{
#ifdef DEBUG_MATRIX
	if (data == NULL) Error.Print(ErrorLev::Matrix, ErrorDef::MatrixIsNull, true);
	if (r < 0 || r >= rows) Error.Print(ErrorLev::Matrix, ErrorDef::RowOutOfBounds, true);
	if (c < 0 || c >= cols) Error.Print(ErrorLev::Matrix, ErrorDef::ColOutOfBounds, true);
#endif
	return *(data + (r*cols + c));
}

VTYPE &MatrixF::operator () (const int c, const int r)
{
#ifdef DEBUG_MATRIX
	if (data == NULL)
		Error.Print(ErrorLev::Matrix, ErrorDef::MatrixIsNull, true);
	if (r < 0 || r >= rows)
		Error.Print(ErrorLev::Matrix, ErrorDef::RowOutOfBounds, true);
	if (c < 0 || c >= cols)
		Error.Print(ErrorLev::Matrix, ErrorDef::ColOutOfBounds, true);
#endif
	return *(data + (r*cols + c));
}
MatrixF &MatrixF::operator= (const unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixF &MatrixF::operator= (const int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixF &MatrixF::operator= (const double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ = (VTYPE)op; return *this; }
MatrixF &MatrixF::operator= (const MatrixC &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ = (VTYPE)*b++;
	//memcpy (data, op.data, len*sizeof(VTYPE));	// Use only for matricies of like types
	return *this;
}
MatrixF &MatrixF::operator= (const MatrixI &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ = (VTYPE)*b++;
	//memcpy (data, op.data, len*sizeof(VTYPE));	// Use only for matricies of like types
	return *this;
}
MatrixF &MatrixF::operator= (const MatrixF &op)			{
#ifdef DEBUG_MATRIX		
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m=op: Operand matrix (op) data is null\n");
#endif
	if (rows != op.rows || cols != op.cols || data == NULL) Resize(op.cols, op.rows);
	memcpy(data, op.data, len*sizeof(VTYPE));
	return *this;
}

MatrixF &MatrixF::operator+= (const unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixF &MatrixF::operator+= (const int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixF &MatrixF::operator+= (const double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ += (VTYPE)op; return *this; }
MatrixF &MatrixF::operator+= (const MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ += (VTYPE)*b++;
	return *this;
}
MatrixF &MatrixF::operator+= (const MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ += (VTYPE)*b++;
	return *this;
}
MatrixF &MatrixF::operator+= (const MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m+=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ += (VTYPE)*b++;
	return *this;
}

MatrixF &MatrixF::operator-= (const unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator-= (const int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator-= (const double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ -= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator-= (const MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}
MatrixF &MatrixF::operator-= (const MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}
MatrixF &MatrixF::operator-= (const MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m-=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ -= (VTYPE)*b++;
	return *this;
}

MatrixF &MatrixF::operator*= (const unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ *= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator*= (const int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ *= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator*= (const double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ *= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator*= (const MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}
MatrixF &MatrixF::operator*= (const MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}
MatrixF &MatrixF::operator*= (const MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) *n++ *= (VTYPE)*b++;
	return *this;
}

MatrixF &MatrixF::operator/= (const unsigned char op)	{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator/= (const int op)				{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator/= (const double op)			{ VTYPE *n = data, *nlen = data + len; for (; n < nlen;) *n++ /= (VTYPE)op; return *this; }
MatrixF &MatrixF::operator/= (const MatrixC &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Matricies must be same size\n");
#endif	 
	VTYPE *n, *ne;
	unsigned char *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) if (*b != (VTYPE)0) { *n++ /= (VTYPE)*b++; }
	else { *n++ = (VTYPE)0; b++; }
	return *this;
}
MatrixF &MatrixF::operator/= (const MatrixI &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Matricies must be same size\n");
#endif	
	VTYPE *n, *ne;
	int *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;) if (*b != (VTYPE)0) { *n++ /= (VTYPE)*b++; }
	else { *n++ = (VTYPE)0; b++; }
	return *this;
}
MatrixF &MatrixF::operator/= (const MatrixF &op)		{
#ifdef DEBUG_MATRIX
	if (data == NULL)							Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Matrix data is null\n");
	if (op.data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Operand matrix (op) data is null\n");
	if (rows != op.rows || cols != op.cols)		Debug.Print(DEBUG_MATRIX, "MatrixF::m/=op: Matricies must be the same size\n");
#endif
	VTYPE *n, *ne;
	double *b;
	n = data; ne = data + len; b = op.data;
	for (; n < ne;)
		if (*b != (VTYPE)0) {
			*n++ /= (VTYPE)*b++;
		}
		else {
			*n++ = (VTYPE)0; b++;
		}
		return *this;
}

MatrixF &MatrixF::Multiply(const MatrixF &op) {
#ifdef DEBUG_MATRIX 
	if (data == NULL)						debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Matrix data is null\n");
	if (op.data == NULL)					debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Operand matrix (op) data is null\n");
	if (cols != op.rows)					debug.Print(DEBUG_MATRIX, "MatrixF::m*=op: Matricies not compatible (m.cols != op.rows)\n");
#endif
	if (cols == op.rows) {
		VTYPE *newdata, *n, *ne, *a, *as;		// Pointers into A and new A matricies
		double *b, *bs, *bce, *be;				// Pointers into B matrix
		int newr = rows, newc = op.cols;		// Set new rows and columns
		int newlen = newr * newc;				// Determine new matrix size
		newdata = new VTYPE[newlen];			// Allocate new matrix to hold multiplication
		//		if (newdata==NULL)						{debug.Print ( (char*) "MatrixF::m*=op: Cannot allocate new matrix.\n"); exit(-1);}
		ne = newdata + newlen;					// Calculate end of new matrix
		int bskip = op.cols;					// Calculate row increment for B matrix	
		bce = op.data + bskip;					// Calculate end of first row in B matrix
		be = op.data + op.rows*op.cols;			// Calculate end of B matrix	
		as = data; bs = op.data;				// Goto start of A and B matricies
		for (n = newdata; n < ne;) {				// Compute C = A*B		
			a = as; b = bs;						// Goto beginning of row in A, top of col in B
			*n = (VTYPE)0;						// Initialize n element in C
			for (; b < be;) { *n += (*a++) * (*b); b += bskip; }	// Compute n element in C
			if (++bs >= bce) {					// If last col in B..
				bs = op.data;					// Go back to first column in B
				as += cols;					// Goto next row in A
			}
			n++;								// Goto next element in C
		}
		delete[] data;							// Destroy old A matrix
		data = newdata; rows = newr; cols = newc; len = newlen;		// Replace with new A matrix	
	}
	return *this;
}

MatrixF &MatrixF::Multiply4x4(const MatrixF &op) {
#ifdef DEBUG_MATRIX 
	if (data == NULL)						Debug.Print(DEBUG_MATRIX, "MatrixF::Multiply4x4 m*=op: Matrix data is null\n");
	if (op.data == NULL)					Debug.Print(DEBUG_MATRIX, "MatrixF::Multiply4x4 m*=op: Operand matrix (op) data is null\n");
	if (rows != 4 || cols != 4)				Debug.Print(DEBUG_MATRIX, "MatrixF::Multiply4x4 m*=op: Matrix m is not 4x4");
	if (op.rows != 4 || op.cols != 4)		Debug.Print(DEBUG_MATRIX, "MatrixF::Multiply4x4 m*=op: Matrix op is not 4x4");
#endif
	register double c1, c2, c3, c4;					// Temporary storage
	VTYPE *n, *a, *b1, *b2, *b3, *b4;
	a = data;	n = data;
	b1 = op.data; b2 = op.data + 4; b3 = op.data + 8; b4 = op.data + 12;

	c1 = *a++;	c2 = *a++;	c3 = *a++; c4 = *a++;					// Calculate First Row
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1) + c2*(*b2) + c3*(*b3) + c4*(*b4);
	b1 -= 3; b2 -= 3; b3 -= 3; b4 -= 3;

	c1 = *a++;	c2 = *a++;	c3 = *a++; c4 = *a++;					// Calculate Second Row
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1) + c2*(*b2) + c3*(*b3) + c4*(*b4);
	b1 -= 3; b2 -= 3; b3 -= 3; b4 -= 3;

	c1 = *a++;	c2 = *a++;	c3 = *a++; c4 = *a++;					// Calculate Third Row
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1) + c2*(*b2) + c3*(*b3) + c4*(*b4);
	b1 -= 3; b2 -= 3; b3 -= 3; b4 -= 3;

	c1 = *a++;	c2 = *a++;	c3 = *a++; c4 = *a;						// Calculate Four Row
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n++ = c1*(*b1++) + c2*(*b2++) + c3*(*b3++) + c4*(*b4++);
	*n = c1*(*b1) + c2*(*b2) + c3*(*b3) + c4*(*b4);

	return *this;
}


MatrixF &MatrixF::Resize(const int x, const int y)
{
	if (data != NULL) {
		if (rows == y && cols == x) return *this;
		delete[] data;
	}
	rows = y; cols = x;
	if (y > 0 && x > 0) {
		len = rows * cols;
		if (len != 0) {
			data = new VTYPE[len];
#ifdef DEBUG_MATRIX
			if (data == NULL) Debug.Print(DEBUG_MATRIX, "MatrixF::Size: Out of memory for construction.\n");
#endif
		}
	}

#ifdef MATRIX_INITIALIZE
	if (data != NULL) memset(data, 0, sizeof(VTYPE)*len);
#endif		
	return *this;
}
MatrixF &MatrixF::ResizeSafe(const int x, const int y)
{
	VTYPE *newdata;
	int newlen;
	VTYPE *n, *ne;
	VTYPE *b, *be;
	int bskip;

	if (data != NULL) {
		newlen = x*y;
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixF::SizeSafe: Out of memory for construction.\n");
#endif		
		if (y >= rows && x >= cols) {			// New size is larger (in both r and c)			
			memset(newdata, 0, newlen*sizeof(VTYPE));	// Clear new matrix
			ne = data + len;					// Calculate end of current matrix
			b = newdata;						// Start of new matrix
			be = newdata + cols;				// Last filled column+1 in new matrix
			bskip = x - cols;
			for (n = data; n < ne;) {				// Fill new matrix with old
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += x;
			}
		}
		else if (y < rows && x < cols) {		// New size is smaller (in both r and c)
			ne = newdata + newlen;			// Calculate end of new matrix
			b = data;						// Start of old matrix
			be = data + x;					// Last retrieved column+1 in old matrix
			bskip = cols - x;
			for (n = newdata; n < ne;) {		// Fill new matrix with old
				for (; b < be;) *n++ = *b++;
				b += bskip;
				be += x;
			}
		}
		else {							// Asymetrical resize
#ifdef DEBUG_MATRIX
			Debug.Print(DEBUG_MATRIX, "MatrixF::SizeSafe: Asymetrical resize NOT YET IMPLEMENTED.\n");
#endif
			exit(202);
		}
		delete[] data;
		rows = y; cols = x;
		data = newdata; len = newlen;
	}
	else {
		len = (rows = y) * (cols = x);
		data = new VTYPE[len];
#ifdef DEBUG_MATRIX
		if (data == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixF::SizeSafe: Out of memory for construction.\n");
#endif
	}
	return *this;
}
MatrixF &MatrixF::InsertRow(const int r)
{
	VTYPE *newdata;
	VTYPE *r_src, *r_dest;
	int newlen;

	if (data != NULL) {
		newlen = (rows + 1)*cols;
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixF::InsertRow: Out of memory for construction.\n");
#endif
		memcpy(newdata, data, r*cols*sizeof(VTYPE));
		if (r < rows) {
			r_src = data + r*cols;
			r_dest = newdata + (r + 1)*cols;
			if (r < rows) memcpy(r_dest, r_src, (rows - r)*cols*sizeof(VTYPE));
		}
		r_dest = newdata + r*cols;
		memset(r_dest, 0, cols*sizeof(VTYPE));
		rows++;
		delete[] data;
		data = newdata; len = newlen;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixF::InsertRow: Cannot insert row in a null matrix.\n");
#endif
	}
	return *this;
}
MatrixF &MatrixF::InsertCol(const int c)
{
	VTYPE *newdata;
	int newlen;

	if (data != NULL) {
		newlen = rows*(cols + 1);
		newdata = new VTYPE[newlen];
#ifdef DEBUG_MATRIX
		if (newdata == NULL)
			Debug.Print(DEBUG_MATRIX, "MatrixF::InsertCol: Out of memory for construction.\n");
#endif
		VTYPE *n, *ne;
		VTYPE *b, *be;
		int bskip, nskip;

		if (c > 0) {
			n = data;							// Copy columns to left of c
			ne = data + len;
			nskip = (cols - c);
			b = newdata;
			be = newdata + c;
			bskip = (cols - c) + 1;
			for (; n < ne;) {
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += (cols + 1);
				n += nskip;
			}
		}
		if (c < cols) {
			n = data + c;						// Copy columns to right of c
			ne = data + len;
			nskip = c;
			b = newdata + (c + 1);
			be = newdata + (cols + 1);
			bskip = c + 1;
			for (; n < ne;) {
				for (; b < be;) *b++ = *n++;
				b += bskip;
				be += (cols + 1);
				n += nskip;
			}
		}
		cols++;
		for (n = newdata + c, ne = newdata + len; n < ne; n += cols) *n = (VTYPE)0;
		delete[] data;
		data = newdata; len = newlen;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixF::InsertCol: Cannot insert col in a null matrix.\n");
#endif
	}
	return *this;
}
MatrixF &MatrixF::Transpose(void)
{
	VTYPE *newdata = NULL;
	int r = rows;

	if (data != NULL) {
		if (rows == 1) {
			rows = cols; cols = 1;
		}
		else if (cols == 1) {
			cols = rows; rows = 1;
		}
		else {
			newdata = new VTYPE[len];
#ifdef DEBUG_MATRIX
			if (newdata == NULL)
				Debug.Print(DEBUG_MATRIX, "MatrixF::Transpose: Out of memory for construction.\n");
#endif	
			VTYPE *n, *ne;
			VTYPE *b, *be;
			n = data;						// Goto start of old matrix
			ne = data + len;
			b = newdata;					// Goto start of new matrix
			be = newdata + len;
			for (; n < ne;) {				// Copy rows of old to columns of new
				for (; b < be; b += r) *b = *n++;
				b -= len;
				b++;
			}
		}
		delete[] data;
		data = newdata;
		rows = cols; cols = r;
	}
	else {
#ifdef DEBUG_MATRIX
		Debug.Print(DEBUG_MATRIX, "MatrixF::Transpose: Cannot transpose a null matrix.\n");
#endif
	}
	return *this;
}
MatrixF &MatrixF::Identity(const int order)
{
	Resize(order, order);
	VTYPE *n, *ne;
	memset(data, 0, len*sizeof(VTYPE));	// Fill matrix with zeros
	n = data;
	ne = data + len;
	for (; n < ne;) {
		*n = 1;								// Set diagonal element to 1
		n += cols;
		n++;								// Next diagonal element
	}
	return *this;
}

// rotates points >>counter-clockwise<< when looking down the X+ axis toward the origin
MatrixF &MatrixF::RotateX(const double ang)
{
	Resize(4, 4);
	VTYPE *n = data;
	double c, s;
	c = cos(ang * 3.141592 / 180);
	s = sin(ang * 3.141592 / 180);
	*n = 1; n += 5;
	*n++ = (VTYPE)c;	*n = (VTYPE)s; n += 3;
	*n++ = (VTYPE)-s;	*n = (VTYPE)c; n += 5;
	*n = 1;
	return *this;
}

// rotates points >>counter-clockwise<< when looking down the Y+ axis toward the origin
MatrixF &MatrixF::RotateY(const double ang)
{
	Resize(4, 4);
	VTYPE *n = data;
	double c, s;
	c = cos(ang * 3.141592 / 180);
	s = sin(ang * 3.141592 / 180);
	*n = (VTYPE)c;		n += 2;
	*n = (VTYPE)-s;	n += 3;
	*n = 1;				n += 3;
	*n = (VTYPE)s;		n += 2;
	*n = (VTYPE)c;		n += 5;
	*n = 1;
	return *this;
}

// rotates points >>counter-clockwise<< when looking down the Z+ axis toward the origin
MatrixF &MatrixF::RotateZ(const double ang)
{
	Resize(4, 4);
	VTYPE *n = data;
	double c, s;
	c = cos(ang * 3.141592 / 180);
	s = sin(ang * 3.141592 / 180);
	*n++ = (VTYPE)c;	*n = (VTYPE)s; n += 3;
	*n++ = (VTYPE)-s;	*n = (VTYPE)c; n += 5;
	*n = 1; n += 5; *n = 1;
	return *this;
}
MatrixF &MatrixF::Ortho(double sx, double sy, double vn, double vf)
{
	// simplified version of OpenGL's glOrtho function
	VTYPE *n = data;
	*n++ = (VTYPE)(1.0 / sx); *n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0;
	*n++ = (VTYPE) 0.0; *n++ = (VTYPE)(1.0 / sy); *n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0;
	*n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0; *n++ = (VTYPE)(-2.0 / (vf - vn)); *n++ = (VTYPE)(-(vf + vn) / (vf - vn));
	*n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0; *n++ = (VTYPE)0; *n++ = (VTYPE) 1.0;
	return *this;
}

MatrixF &MatrixF::Translate(double tx, double ty, double tz)
{
	Resize(4, 4);
	VTYPE *n = data;
	*n++ = (VTYPE) 1.0; *n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0;
	*n++ = (VTYPE) 0.0; *n++ = (VTYPE) 1.0; *n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0;
	*n++ = (VTYPE) 0.0; *n++ = (VTYPE) 0.0; *n++ = (VTYPE) 1.0; *n++ = (VTYPE) 0.0;
	*n++ = (VTYPE)tx; *n++ = (VTYPE)ty; *n++ = (VTYPE)tz; *n++ = (VTYPE) 1.0;
	return *this;
}

MatrixF &MatrixF::Basis(const Vector3DF &c1, const Vector3DF &c2, const Vector3DF &c3)
{
	Resize(4, 4);
	VTYPE *n = data;
	*n++ = (VTYPE)c1.x; *n++ = (VTYPE)c2.x; *n++ = (VTYPE)c3.x; *n++ = (VTYPE)0;
	*n++ = (VTYPE)c1.y; *n++ = (VTYPE)c2.y; *n++ = (VTYPE)c3.y; *n++ = (VTYPE)0;
	*n++ = (VTYPE)c1.z; *n++ = (VTYPE)c2.z; *n++ = (VTYPE)c3.z; *n++ = (VTYPE)0;
	*n++ = (VTYPE)0; *n++ = (VTYPE)0; *n++ = (VTYPE)0; *n++ = (VTYPE)0;
	return *this;
}

#define		SWAP(a, b)		{temp=(a); (a)=(b); (b)=temp;}

MatrixF &MatrixF::GaussJordan(MatrixF &b)
{
	// Gauss-Jordan solves the matrix equation Ax = b
	// Given the problem:
	//		A*x = b		(where A is 'this' matrix and b is provided)
	// The solution is:
	//		Ainv*b = x
	// This function returns Ainv in A and x in b... that is:
	//		A (this) -> Ainv
	//		b -> solution x
	//

	MatrixI index_col, index_row;
	MatrixI piv_flag;
	int r, c, c2, rs, cs;
	double piv_val;
	int piv_row, piv_col;
	double pivinv, dummy, temp;

#ifdef DEBUG_MATRIX
	if (rows != cols) Debug.Print(DEBUG_MATRIX, "MatrixF::GaussJordan: Number of rows and cols of A must be equal.\n");
	if (rows != b.rows) Debug.Print(DEBUG_MATRIX, "MatrixF::GaussJordan: Number of rows of A and rows of b must be equal.\n");
	if (b.cols != 1) Debug.Print(DEBUG_MATRIX, "MatrixF::GaussJordan: Number of cols of b must be 1.\n");
#endif

	index_col.Resize(cols, 1);
	index_row.Resize(cols, 1);
	piv_flag.Resize(cols, 1);
	piv_flag = 0;
	for (c = 0; c < cols; c++) {
		piv_val = 0.0;
		for (rs = 0; rs < rows; rs++) {
			if (piv_flag(rs, 0) != 1)
				for (cs = 0; cs < cols; cs++) {
					if (piv_flag(cs, 0) == 0) {
						if (fabs((*this) (cs, rs)) >= piv_val) {
							piv_val = fabs((*this) (cs, rs));
							piv_row = rs;
							piv_col = cs;
						}
					}
					else if (piv_flag(cs, 0) > 1) {
#ifdef DEBUG_MATRIX
						Debug.Print(DEBUG_MATRIX, "MatrixF::GaussJordan: Singular matrix (dbl pivs).\n");
						//Print ();
#endif
					}
				}
		}
		piv_flag(piv_col, 0)++;
		if (piv_row != piv_col) {
			for (c2 = 0; c2 < cols; c2++) SWAP((*this) (c2, piv_row), (*this) (c2, piv_col));
			for (c2 = 0; c2 < b.cols; c2++) SWAP(b(c2, piv_row), b(c2, piv_col));
		}
		index_row(c, 0) = piv_row;
		index_col(c, 0) = piv_col;
		if ((*this) (piv_col, piv_col) == 0.0) {
#ifdef DEBUG_MATRIX
			Debug.Print(DEBUG_MATRIX, "MatrixF::GaussJordan: Singular matrix (0 piv).\n");
			//Print ();
#endif
		}
		pivinv = 1.0 / ((*this) (piv_col, piv_col));
		(*this) (piv_col, piv_col) = 1.0;
		for (c2 = 0; c2 < cols; c2++) (*this) (c2, piv_col) *= pivinv;
		for (c2 = 0; c2 < b.cols; c2++) b(c2, piv_col) *= pivinv;
		for (r = 0; r < rows; r++) {
			if (r != piv_col) {
				dummy = (*this) (piv_col, r);
				(*this) (piv_col, r) = 0.0;
				for (c2 = 0; c2 < cols; c2++) (*this) (c2, r) -= (*this) (c2, piv_col)*dummy;
				for (c2 = 0; c2 < b.cols; c2++) b(c2, r) -= b(c2, piv_col)*dummy;
			}
		}
	}
	for (c = cols - 1; c >= 0; c--) {
		if (index_row(c, 0) != index_col(c, 0))
			for (r = 0; r < rows; r++)
				SWAP((*this) (index_row(c, 0), r), (*this) (index_col(c, 0), r));
	}
	return *this;
}
MatrixF &MatrixF::Submatrix(MatrixF& b, int mx, int my)
{
	VTYPE* pEnd = data + rows*cols;		// end of matrix
	VTYPE* pVal = data;
	VTYPE* pNewVal = b.data;
	VTYPE* pNewEnd = pNewVal + mx;
	int pNewSkip = cols - mx;

	for (pVal = data; pVal < pEnd;) {
		for (; pNewVal < pNewEnd;) *pVal++ = *pNewVal++;
		pNewVal += pNewSkip;
		pNewEnd += mx;
	}
	return *this;
}

// N-Vector Dot Product
// Elements may be in rows or columns, but:
// - If in rows, number of columns must be one and number of rows must match.
// - If in cols, number of rows must be one and number of cols must match.
double MatrixF::Dot(MatrixF& b)
{
	double d = 0.0;
	VTYPE* pA = data;
	VTYPE* pB = b.data;

	if (rows == 1 && b.rows == 1 && cols == b.cols) {
		VTYPE* pAEnd = data + cols;
		d = 0.0;
		for (; pA < pAEnd;)
			d += (*pA++) * (*pB++);
	}
	else if (cols == 1 && b.cols == 1 && rows == b.rows) {
		VTYPE* pAEnd = data + rows;
		d = 0.0;
		for (; pA < pAEnd;)
			d += (*pA++) * (*pB++);
	}
	return d;
}

#define I(x, y)		( (y*xres) + x )
#define Ix(r)		( r % xres )			// X coordinate from row	
#define Iy(r)		( r / xres )			// Y coordinate from row

MatrixF &MatrixF::MatrixVector5(MatrixF& x, int mrows, MatrixF& b)
{
	double v;

	// A( 2, r ) * B ( r ) + A(1,r)*B(r-1) + A(3,r)*B(r+1) + A(0, r)*B( R-( r ) ) + A(4, r)*B( R+( r ) )
	for (int r = 0; r < mrows; r++) {
		v = GetVal(2, r) * x(0, r);
		if (r > 0) v += GetVal(1, r) * x(0, r - 1);
		if (r < mrows - 1) v += GetVal(3, r) * x(0, r + 1);
		if ((int)GetVal(5, r) >= 0) v += GetVal(0, r) * x(0, (int)GetVal(5, r));
		if ((int)GetVal(6, r) >= 0) v += GetVal(4, r) * x(0, (int)GetVal(6, r));
		b(0, r) = v;
	}
	return *this;
}

MatrixF &MatrixF::ConjugateGradient(MatrixF &b)
{
	return *this;
}

// Sparse Conjugate Gradient 2D (special case)
// This compute conjugate gradients on a 
// sparse "5-7" x N positive definite matrix. 
// Only 'mrows' subset of the row-size of A and b will be used.
MatrixF &MatrixF::ConjugateGradient5(MatrixF &b, int mrows)
{
	double a, g, rdot;
	int i, imax;
	MatrixF x, xnew;				// solution vector
	MatrixF r, rnew;				// residual
	MatrixF p, ptemp;				// search direction
	MatrixF v;

	x.Resize(1, mrows);
	xnew.Resize(1, mrows);
	r.Resize(1, mrows);
	rnew.Resize(1, mrows);
	p.Resize(1, mrows);
	ptemp.Resize(1, mrows);
	v.Resize(1, mrows);

	r.Submatrix(b, 1, mrows);
	MatrixVector5(x, mrows, v);				// (Ax -> v)
	r -= v;										// r = b - Ax
	p = r;

	imax = 20;
	for (i = 0; i < imax; i++) {
		MatrixVector5(p, mrows, v);			// v = Ap
		rdot = r.Dot(r);
		a = rdot / p.Dot(v);					// a = (r . r) / (p . v)		
		xnew = p;
		xnew *= a;
		xnew += x;								// x = x + p*a
		v *= a;
		rnew = r;								// rnew = r - v*a
		rnew -= v;
		g = rnew.Dot(rnew) / rdot;			// g = (rnew . rnew) / (r . r)
		p *= g;
		p += rnew;								// p = rnew + p*g
		r = rnew;
		x = xnew;
	}
	for (int rx = 0; rx < mrows; rx++)
		b(0, rx) = x(0, rx);
	return *this;
}

int MatrixF::GetX()						{ return cols; }
int MatrixF::GetY()						{ return rows; }
int MatrixF::GetRows(void)				{ return rows; }
int MatrixF::GetCols(void)				{ return cols; }
int MatrixF::GetLength(void)				{ return len; }
VTYPE *MatrixF::GetData(void)			{ return data; }

double MatrixF::GetF(const int r, const int c)		{ return (double)(*(data + r*cols + c)); }

void MatrixF::GetRowVec(int r, Vector3DF &v)
{
	VTYPE *n = data + r*cols;
	v.x = (float)*n++; v.y = (float)*n++; v.z = (float)*n++;
}

void MatrixF::Print(char* fname)
{
	char buf[2000];

#ifdef _MSC_VER
	FILE* fp;
	fopen_s(&fp, fname, "w+");
#else
	FILE* fp = fopen(fname, "w+");
#endif

	for (int r = 0; r < rows; r++) {
		buf[0] = '\0';
		for (int c = 0; c < cols; c++) {
#ifdef _MSC_VER
			sprintf_s(buf, "%s %04.3f", buf, GetVal(c, r));
#else
			sprintf(buf, "%s %04.3f", buf, GetVal(c, r));
#endif
		}
		fprintf(fp, "%s\n", buf);
	}
	fprintf(fp, "---------------------------------------\n", buf);
	fflush(fp);
	fclose(fp);
}


// MatrixF Code Definition
#undef VTYPE
#define VNAME		F
#define VTYPE		float

// Constructors/Destructors

Matrix4F::Matrix4F(float* src)	{ for (int n = 0; n < 16; n++) data[n] = src[n]; }
Matrix4F::Matrix4F(float f0, float f1, float f2, float f3,
	float f4, float f5, float f6, float f7,
	float f8, float f9, float f10, float f11,
	float f12, float f13, float f14, float f15)
{
	data[0] = f0;	data[1] = f1;	data[2] = f2;	data[3] = f3;
	data[4] = f4;	data[5] = f5;	data[6] = f6;	data[7] = f7;
	data[8] = f8;	data[9] = f9;	data[10] = f10;	data[11] = f11;
	data[12] = f12;	data[13] = f13;	data[14] = f14;	data[15] = f15;
}

Matrix4F Matrix4F::operator* (const float &op)
{
	return Matrix4F(data[0] * op, data[1] * op, data[2] * op, data[3],
		data[4] * op, data[5] * op, data[6] * op, data[7],
		data[8] * op, data[9] * op, data[10] * op, data[11],
		data[12], data[13], data[14], data[15]);
}

Matrix4F Matrix4F::operator* (const Vector3DF &op)
{
	return Matrix4F(data[0] * op.x, data[1] * op.y, data[2] * op.z, data[3],
		data[4] * op.x, data[5] * op.y, data[6] * op.z, data[7],
		data[8] * op.x, data[9] * op.y, data[10] * op.z, data[11],
		data[12] * op.x, data[13] * op.y, data[14] * op.z, data[15]);
}

Matrix4F &Matrix4F::operator= (const unsigned char op)	{ for (int n = 0; n < 16; n++) data[n] = (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator= (const int op)				{ for (int n = 0; n < 16; n++) data[n] = (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator= (const double op)			{ for (int n = 0; n < 16; n++) data[n] = (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator+= (const unsigned char op)	{ for (int n = 0; n < 16; n++) data[n] += (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator+= (const int op)				{ for (int n = 0; n < 16; n++) data[n] += (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator+= (const double op)			{ for (int n = 0; n < 16; n++) data[n] += (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator-= (const unsigned char op)	{ for (int n = 0; n < 16; n++) data[n] -= (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator-= (const int op)				{ for (int n = 0; n < 16; n++) data[n] -= (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator-= (const double op)			{ for (int n = 0; n < 16; n++) data[n] -= (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator*= (const unsigned char op)	{ for (int n = 0; n < 16; n++) data[n] *= (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator*= (const int op)				{ for (int n = 0; n < 16; n++) data[n] *= (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator*= (const double op)			{ for (int n = 0; n < 16; n++) data[n] *= (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator/= (const unsigned char op)	{ for (int n = 0; n < 16; n++) data[n] /= (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator/= (const int op)				{ for (int n = 0; n < 16; n++) data[n] /= (VTYPE)op; return *this; }
Matrix4F &Matrix4F::operator/= (const double op)			{ for (int n = 0; n < 16; n++) data[n] /= (VTYPE)op; return *this; }

// column-major multiply (like OpenGL)
Matrix4F &Matrix4F::operator*= (const Matrix4F &op) {
	register float orig[16];				// Temporary storage
	memcpy(orig, data, 16 * sizeof(float));

	// Calculate First Row
	data[0] = op.data[0] * orig[0] + op.data[1] * orig[4] + op.data[2] * orig[8] + op.data[3] * orig[12];
	data[1] = op.data[0] * orig[1] + op.data[1] * orig[5] + op.data[2] * orig[9] + op.data[3] * orig[13];
	data[2] = op.data[0] * orig[2] + op.data[1] * orig[6] + op.data[2] * orig[10] + op.data[3] * orig[14];
	data[3] = op.data[0] * orig[3] + op.data[1] * orig[7] + op.data[2] * orig[11] + op.data[3] * orig[15];

	// Calculate Second Row
	data[4] = op.data[4] * orig[0] + op.data[5] * orig[4] + op.data[6] * orig[8] + op.data[7] * orig[12];
	data[5] = op.data[4] * orig[1] + op.data[5] * orig[5] + op.data[6] * orig[9] + op.data[7] * orig[13];
	data[6] = op.data[4] * orig[2] + op.data[5] * orig[6] + op.data[6] * orig[10] + op.data[7] * orig[14];
	data[7] = op.data[4] * orig[3] + op.data[5] * orig[7] + op.data[6] * orig[11] + op.data[7] * orig[15];

	// Calculate Third Row
	data[8] = op.data[8] * orig[0] + op.data[9] * orig[4] + op.data[10] * orig[8] + op.data[11] * orig[12];
	data[9] = op.data[8] * orig[1] + op.data[9] * orig[5] + op.data[10] * orig[9] + op.data[11] * orig[13];
	data[10] = op.data[8] * orig[2] + op.data[9] * orig[6] + op.data[10] * orig[10] + op.data[11] * orig[14];
	data[11] = op.data[8] * orig[3] + op.data[9] * orig[7] + op.data[10] * orig[11] + op.data[11] * orig[15];

	// Calculate Four Row
	data[12] = op.data[12] * orig[0] + op.data[13] * orig[4] + op.data[14] * orig[8] + op.data[15] * orig[12];
	data[13] = op.data[12] * orig[1] + op.data[13] * orig[5] + op.data[14] * orig[9] + op.data[15] * orig[13];
	data[14] = op.data[12] * orig[2] + op.data[13] * orig[6] + op.data[14] * orig[10] + op.data[15] * orig[14];
	data[15] = op.data[12] * orig[3] + op.data[13] * orig[7] + op.data[14] * orig[11] + op.data[15] * orig[15];

	return *this;
}

Matrix4F &Matrix4F::operator= (const float* op)
{
	for (int n = 0; n < 16; n++)
		data[n] = op[n];
	return *this;
}

Matrix4F &Matrix4F::operator*= (const float* op) {
	register float orig[16];				// Temporary storage
	memcpy(orig, data, 16 * sizeof(float));

	// Calculate First Row
	data[0] = op[0] * orig[0] + op[1] * orig[4] + op[2] * orig[8] + op[3] * orig[12];
	data[1] = op[0] * orig[1] + op[1] * orig[5] + op[2] * orig[9] + op[3] * orig[13];
	data[2] = op[0] * orig[2] + op[1] * orig[6] + op[2] * orig[10] + op[3] * orig[14];
	data[3] = op[0] * orig[3] + op[1] * orig[7] + op[2] * orig[11] + op[3] * orig[15];

	// Calculate Second Row
	data[4] = op[4] * orig[0] + op[5] * orig[4] + op[6] * orig[8] + op[7] * orig[12];
	data[5] = op[4] * orig[1] + op[5] * orig[5] + op[6] * orig[9] + op[7] * orig[13];
	data[6] = op[4] * orig[2] + op[5] * orig[6] + op[6] * orig[10] + op[7] * orig[14];
	data[7] = op[4] * orig[3] + op[5] * orig[7] + op[6] * orig[11] + op[7] * orig[15];

	// Calculate Third Row
	data[8] = op[8] * orig[0] + op[9] * orig[4] + op[10] * orig[8] + op[11] * orig[12];
	data[9] = op[8] * orig[1] + op[9] * orig[5] + op[10] * orig[9] + op[11] * orig[13];
	data[10] = op[8] * orig[2] + op[9] * orig[6] + op[10] * orig[10] + op[11] * orig[14];
	data[11] = op[8] * orig[3] + op[9] * orig[7] + op[10] * orig[11] + op[11] * orig[15];

	// Calculate Four Row
	data[12] = op[12] * orig[0] + op[13] * orig[4] + op[14] * orig[8] + op[15] * orig[12];
	data[13] = op[12] * orig[1] + op[13] * orig[5] + op[14] * orig[9] + op[15] * orig[13];
	data[14] = op[12] * orig[2] + op[13] * orig[6] + op[14] * orig[10] + op[15] * orig[14];
	data[15] = op[12] * orig[3] + op[13] * orig[7] + op[14] * orig[11] + op[15] * orig[15];

	return *this;
}


Matrix4F &Matrix4F::Transpose(void)
{
	register float orig[16];				// Temporary storage
	memcpy(orig, data, 16 * sizeof(VTYPE));

	data[0] = orig[0];	data[1] = orig[4];	data[2] = orig[8];	data[3] = orig[12];
	data[4] = orig[1];	data[5] = orig[5];	data[6] = orig[9];	data[7] = orig[13];
	data[8] = orig[2];	data[9] = orig[6];	data[10] = orig[10]; data[11] = orig[14];
	data[12] = orig[3];	data[13] = orig[7];	data[14] = orig[11]; data[15] = orig[15];
	return *this;
}

Matrix4F &Matrix4F::Identity()
{
	memset(data, 0, 16 * sizeof(VTYPE));
	data[0] = 1.0;
	data[5] = 1.0;
	data[10] = 1.0;
	data[15] = 1.0;
	return *this;
}

// Pre-multiply (left side multiply ZYX) = Euler rotation about X, then Y, then Z
//
Matrix4F &Matrix4F::RotateZYX(const Vector3DF& angs)
{
	float cx, sx, cy, sy, cz, sz;
	cx = (float)cos(angs.x * 3.141592 / 180);
	sx = (float)sin(angs.x * 3.141592 / 180);
	cy = (float)cos(angs.y * 3.141592 / 180);
	sy = (float)sin(angs.y * 3.141592 / 180);
	cz = (float)cos(angs.z * 3.141592 / 180);
	sz = (float)sin(angs.z * 3.141592 / 180);
	data[0] = (VTYPE)cz * cy;
	data[1] = (VTYPE)sz * cy;
	data[2] = (VTYPE)-sy;
	data[3] = (VTYPE)0;
	data[4] = (VTYPE)-sz * cx + cz*sy*sx;
	data[5] = (VTYPE)cz * cx - sz*sy*sz;
	data[6] = (VTYPE)-cy * sx;
	data[7] = (VTYPE)0;
	data[8] = (VTYPE)-sz * sx + cz*sy*cx;
	data[9] = (VTYPE)cz * sx + sz*sy*cx;
	data[10] = (VTYPE)cy * cx;
	data[11] = 0;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return *this;
}
Matrix4F &Matrix4F::RotateZYXT(const Vector3DF& angs, const Vector3DF& t)
{
	float cx, sx, cy, sy, cz, sz;
	cx = (float)cos(angs.x * 3.141592 / 180);
	sx = (float)sin(angs.x * 3.141592 / 180);
	cy = (float)cos(angs.y * 3.141592 / 180);
	sy = (float)sin(angs.y * 3.141592 / 180);
	cz = (float)cos(angs.z * 3.141592 / 180);
	sz = (float)sin(angs.z * 3.141592 / 180);
	data[0] = (VTYPE)cy * cz;				// See Diebel 2006, "Representing Attitude"
	data[1] = (VTYPE)cy * sz;
	data[2] = (VTYPE)-sy;
	data[3] = (VTYPE)0;
	data[4] = (VTYPE)sx*sy*cz - cx*sz;
	data[5] = (VTYPE)sx*sy*sz + cx*cz;
	data[6] = (VTYPE)sx * cy;
	data[7] = (VTYPE)0;
	data[8] = (VTYPE)cx*sy*cz + sx*sz;
	data[9] = (VTYPE)cx*sy*sz - sx*cz;
	data[10] = (VTYPE)cx * cy;
	data[11] = 0;
	data[12] = (VTYPE)data[0] * t.x + data[4] * t.y + data[8] * t.z;
	data[13] = (VTYPE)data[1] * t.x + data[5] * t.y + data[9] * t.z;
	data[14] = (VTYPE)data[2] * t.x + data[6] * t.y + data[10] * t.z;
	data[15] = 1;
	return *this;
}
Matrix4F &Matrix4F::RotateTZYX(const Vector3DF& angs, const Vector3DF& t)
{
	float cx, sx, cy, sy, cz, sz;
	cx = (float)cos(angs.x * 3.141592 / 180);
	sx = (float)sin(angs.x * 3.141592 / 180);
	cy = (float)cos(angs.y * 3.141592 / 180);
	sy = (float)sin(angs.y * 3.141592 / 180);
	cz = (float)cos(angs.z * 3.141592 / 180);
	sz = (float)sin(angs.z * 3.141592 / 180);
	data[0] = (VTYPE)cz * cy;
	data[1] = (VTYPE)sz * cy;
	data[2] = (VTYPE)-sy;
	data[3] = (VTYPE)0;
	data[4] = (VTYPE)-sz * cx + cz*sy*sx;
	data[5] = (VTYPE)cz * cx + sz*sy*sz;
	data[6] = (VTYPE)cy * sx;
	data[7] = (VTYPE)0;
	data[8] = (VTYPE)sz * sx + cz*sy*cx;
	data[9] = (VTYPE)-cz * sx + sz*sy*cx;
	data[10] = (VTYPE)cy * cx;
	data[11] = 0;
	data[12] = (VTYPE)t.x;
	data[13] = (VTYPE)t.y;
	data[14] = (VTYPE)t.z;
	data[15] = 1;
	return *this;
}



// rotates points >>counter-clockwise<< when looking down the Y+ axis toward the origin
Matrix4F &Matrix4F::RotateY(const double ang)
{
	memset(data, 0, 16 * sizeof(VTYPE));
	double c, s;
	c = cos(ang * 3.141592 / 180);
	s = sin(ang * 3.141592 / 180);
	data[0] = (VTYPE)c;
	data[2] = (VTYPE)-s;
	data[5] = 1;
	data[8] = (VTYPE)s;
	data[10] = (VTYPE)c;
	data[15] = 1;
	return *this;
}

// rotates points >>counter-clockwise<< when looking down the Z+ axis toward the origin
Matrix4F &Matrix4F::RotateZ(const double ang)
{
	memset(data, 0, 16 * sizeof(VTYPE));
	double c, s;
	c = cos(ang * 3.141592 / 180);
	s = sin(ang * 3.141592 / 180);
	data[0] = (VTYPE)c;	data[1] = (VTYPE)s;
	data[4] = (VTYPE)-s;	data[5] = (VTYPE)c;
	data[10] = 1;
	data[15] = 1;
	return *this;
}

Matrix4F &Matrix4F::Ortho(double sx, double sy, double vn, double vf)
{
	// simplified version of OpenGL's glOrtho function	
	data[0] = (VTYPE)(1.0 / sx); data[1] = (VTYPE) 0.0;		data[2] = (VTYPE) 0.0;				data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE) 0.0;		data[5] = (VTYPE)(1.0 / sy); data[6] = (VTYPE) 0.0;				data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE) 0.0;		data[9] = (VTYPE) 0.0;		data[10] = (VTYPE)(-2.0 / (vf - vn));	data[11] = (VTYPE)(-(vf + vn) / (vf - vn));
	data[12] = (VTYPE) 0.0;		data[13] = (VTYPE) 0.0;		data[14] = (VTYPE)0;				data[15] = (VTYPE) 1.0;
	return *this;
}

Matrix4F &Matrix4F::Translate(double tx, double ty, double tz)
{
	data[0] = (VTYPE) 1.0; data[1] = (VTYPE) 0.0;	data[2] = (VTYPE) 0.0; data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE) 0.0; data[5] = (VTYPE) 1.0; data[6] = (VTYPE) 0.0; data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE) 0.0; data[9] = (VTYPE) 0.0; data[10] = (VTYPE) 1.0; data[11] = (VTYPE) 0.0;
	data[12] = (VTYPE)tx;	data[13] = (VTYPE)ty;	data[14] = (VTYPE)tz;	data[15] = (VTYPE) 1.0;
	return *this;
}

Matrix4F &Matrix4F::Scale(double sx, double sy, double sz)
{
	data[0] = (VTYPE)sx; data[1] = (VTYPE) 0.0;	data[2] = (VTYPE) 0.0; data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE) 0.0; data[5] = (VTYPE)sy; data[6] = (VTYPE) 0.0; data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE) 0.0; data[9] = (VTYPE) 0.0; data[10] = (VTYPE)sz; data[11] = (VTYPE) 0.0;
	data[12] = (VTYPE) 0.0;	data[13] = (VTYPE) 0.0;	data[14] = (VTYPE) 0.0;	data[15] = (VTYPE) 1.0;
	return *this;
}

Matrix4F &Matrix4F::Basis(const Vector3DF &norm)
{
	Vector3DF binorm, tang;
	binorm.Set(0.0, 1.0, 0);		// up vector
	binorm.Cross(norm);
	binorm.Normalize();
	tang = binorm;
	tang.Cross(norm);
	//tang *= -1;
	tang.Normalize();

	data[0] = (VTYPE)binorm.x; data[1] = (VTYPE)binorm.y; data[2] = (VTYPE)binorm.z; data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE)norm.x; data[5] = (VTYPE)norm.y; data[6] = (VTYPE)norm.z; data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE)tang.x; data[9] = (VTYPE)tang.y; data[10] = (VTYPE)tang.z; data[11] = (VTYPE) 0.0;
	data[12] = (VTYPE) 0.0;	 data[13] = (VTYPE) 0.0;  data[14] = (VTYPE) 0.0;  data[15] = (VTYPE) 1.0;
	return *this;

}

Matrix4F &Matrix4F::Basis(const Vector3DF &c1, const Vector3DF &c2, const Vector3DF &c3)
{
	data[0] = (VTYPE)c1.x; data[1] = (VTYPE)c2.x; data[2] = (VTYPE)c3.x; data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE)c1.y; data[5] = (VTYPE)c2.y; data[6] = (VTYPE)c3.y; data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE)c1.z; data[9] = (VTYPE)c2.z; data[10] = (VTYPE)c3.z; data[11] = (VTYPE) 0.0;
	data[12] = (VTYPE)  0.0; data[13] = (VTYPE)  0.0; data[14] = (VTYPE)  0.0; data[15] = (VTYPE) 1.0;
	return *this;
}
Matrix4F &Matrix4F::TransSRT(const Vector3DF &c1, const Vector3DF &c2, const Vector3DF &c3, const Vector3DF& t, const Vector3DF& s)
{
	data[0] = (VTYPE)c1.x*s.x; data[4] = (VTYPE)c2.x*s.x; data[8] = (VTYPE)c3.x*s.x;  data[12] = (VTYPE) 0.0;
	data[1] = (VTYPE)c1.y*s.y; data[5] = (VTYPE)c2.y*s.y; data[9] = (VTYPE)c3.y*s.y;  data[13] = (VTYPE) 0.0;
	data[2] = (VTYPE)c1.z*s.z; data[6] = (VTYPE)c2.z*s.z; data[10] = (VTYPE)c3.z*s.z;  data[14] = (VTYPE) 0.0;
	data[3] = (VTYPE)t.x;		 data[7] = (VTYPE)t.y;	  data[11] = (VTYPE)t.z;		data[15] = (VTYPE) 1.0;
	return *this;
}

Matrix4F &Matrix4F::SRT(const Vector3DF &c1, const Vector3DF &c2, const Vector3DF &c3, const Vector3DF& t, const Vector3DF& s)
{
	data[0] = (VTYPE)c1.x*s.x; data[1] = (VTYPE)c2.x*s.x; data[2] = (VTYPE)c3.x*s.x;  data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE)c1.y*s.y; data[5] = (VTYPE)c2.y*s.y; data[6] = (VTYPE)c3.y*s.y;  data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE)c1.z*s.z; data[9] = (VTYPE)c2.z*s.z; data[10] = (VTYPE)c3.z*s.z;  data[11] = (VTYPE) 0.0;
	data[12] = (VTYPE)t.x;		 data[13] = (VTYPE)t.y;	  data[14] = (VTYPE)t.z;		data[15] = (VTYPE) 1.0;
	return *this;
}
Matrix4F &Matrix4F::SRT(const Vector3DF &c1, const Vector3DF &c2, const Vector3DF &c3, const Vector3DF& t, const float s)
{
	data[0] = (VTYPE)c1.x*s; data[1] = (VTYPE)c1.y*s; data[2] = (VTYPE)c1.z*s;  data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE)c2.x*s; data[5] = (VTYPE)c2.y*s; data[6] = (VTYPE)c2.z*s;  data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE)c3.x*s; data[9] = (VTYPE)c3.y*s; data[10] = (VTYPE)c3.z*s;  data[11] = (VTYPE) 0.0;
	data[12] = (VTYPE)t.x;		 data[13] = (VTYPE)t.y;	  data[14] = (VTYPE)t.z;		data[15] = (VTYPE) 1.0;
	return *this;
}

Matrix4F &Matrix4F::InvTRS(const Vector3DF &c1, const Vector3DF &c2, const Vector3DF &c3, const Vector3DF& t, const Vector3DF& s)
{
	data[0] = (VTYPE)c1.x / s.x; data[1] = (VTYPE)c1.y / s.y; data[2] = (VTYPE)c1.z / s.z;  data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE)c2.x / s.x; data[5] = (VTYPE)c2.y / s.y; data[6] = (VTYPE)c2.z / s.z;  data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE)c3.x / s.x; data[9] = (VTYPE)c3.y / s.y; data[10] = (VTYPE)c3.z / s.z;  data[11] = (VTYPE) 0.0;
	data[12] = (VTYPE)-t.x / s.x; data[13] = (VTYPE)-t.y / s.y; data[14] = (VTYPE)-t.z / s.z;  data[15] = (VTYPE) 1.0;
	return *this;
}

Matrix4F &Matrix4F::InvTRS(const Vector3DF &c1, const Vector3DF &c2, const Vector3DF &c3, const Vector3DF& t, const float s)
{
	data[0] = (VTYPE)c1.x / s; data[1] = (VTYPE)c1.y / s; data[2] = (VTYPE)c1.z / s;  data[3] = (VTYPE) 0.0;
	data[4] = (VTYPE)c2.x / s; data[5] = (VTYPE)c2.y / s; data[6] = (VTYPE)c2.z / s;  data[7] = (VTYPE) 0.0;
	data[8] = (VTYPE)c3.x / s; data[9] = (VTYPE)c3.y / s; data[10] = (VTYPE)c3.z / s;  data[11] = (VTYPE) 0.0;
	data[12] = (VTYPE)-t.x / s; data[13] = (VTYPE)-t.y / s; data[14] = (VTYPE)-t.z / s;  data[15] = (VTYPE) 1.0;
	return *this;
}

Matrix4F &Matrix4F::InvertTRS()
{
	double inv[16], det;
	// mult: 16 *  13 + 4 	= 212
	// add:   16 * 5 + 3 	=   83
	int i;
	inv[0] = data[5] * data[10] * data[15] - data[5] * data[11] * data[14] - data[9] * data[6] * data[15] + data[9] * data[7] * data[14] + data[13] * data[6] * data[11] - data[13] * data[7] * data[10];
	inv[4] = -data[4] * data[10] * data[15] + data[4] * data[11] * data[14] + data[8] * data[6] * data[15] - data[8] * data[7] * data[14] - data[12] * data[6] * data[11] + data[12] * data[7] * data[10];
	inv[8] = data[4] * data[9] * data[15] - data[4] * data[11] * data[13] - data[8] * data[5] * data[15] + data[8] * data[7] * data[13] + data[12] * data[5] * data[11] - data[12] * data[7] * data[9];
	inv[12] = -data[4] * data[9] * data[14] + data[4] * data[10] * data[13] + data[8] * data[5] * data[14] - data[8] * data[6] * data[13] - data[12] * data[5] * data[10] + data[12] * data[6] * data[9];
	inv[1] = -data[1] * data[10] * data[15] + data[1] * data[11] * data[14] + data[9] * data[2] * data[15] - data[9] * data[3] * data[14] - data[13] * data[2] * data[11] + data[13] * data[3] * data[10];
	inv[5] = data[0] * data[10] * data[15] - data[0] * data[11] * data[14] - data[8] * data[2] * data[15] + data[8] * data[3] * data[14] + data[12] * data[2] * data[11] - data[12] * data[3] * data[10];
	inv[9] = -data[0] * data[9] * data[15] + data[0] * data[11] * data[13] + data[8] * data[1] * data[15] - data[8] * data[3] * data[13] - data[12] * data[1] * data[11] + data[12] * data[3] * data[9];
	inv[13] = data[0] * data[9] * data[14] - data[0] * data[10] * data[13] - data[8] * data[1] * data[14] + data[8] * data[2] * data[13] + data[12] * data[1] * data[10] - data[12] * data[2] * data[9];
	inv[2] = data[1] * data[6] * data[15] - data[1] * data[7] * data[14] - data[5] * data[2] * data[15] + data[5] * data[3] * data[14] + data[13] * data[2] * data[7] - data[13] * data[3] * data[6];
	inv[6] = -data[0] * data[6] * data[15] + data[0] * data[7] * data[14] + data[4] * data[2] * data[15] - data[4] * data[3] * data[14] - data[12] * data[2] * data[7] + data[12] * data[3] * data[6];
	inv[10] = data[0] * data[5] * data[15] - data[0] * data[7] * data[13] - data[4] * data[1] * data[15] + data[4] * data[3] * data[13] + data[12] * data[1] * data[7] - data[12] * data[3] * data[5];
	inv[14] = -data[0] * data[5] * data[14] + data[0] * data[6] * data[13] + data[4] * data[1] * data[14] - data[4] * data[2] * data[13] - data[12] * data[1] * data[6] + data[12] * data[2] * data[5];
	inv[3] = -data[1] * data[6] * data[11] + data[1] * data[7] * data[10] + data[5] * data[2] * data[11] - data[5] * data[3] * data[10] - data[9] * data[2] * data[7] + data[9] * data[3] * data[6];
	inv[7] = data[0] * data[6] * data[11] - data[0] * data[7] * data[10] - data[4] * data[2] * data[11] + data[4] * data[3] * data[10] + data[8] * data[2] * data[7] - data[8] * data[3] * data[6];
	inv[11] = -data[0] * data[5] * data[11] + data[0] * data[7] * data[9] + data[4] * data[1] * data[11] - data[4] * data[3] * data[9] - data[8] * data[1] * data[7] + data[8] * data[3] * data[5];
	inv[15] = data[0] * data[5] * data[10] - data[0] * data[6] * data[9] - data[4] * data[1] * data[10] + data[4] * data[2] * data[9] + data[8] * data[1] * data[6] - data[8] * data[2] * data[5];

	det = data[0] * inv[0] + data[1] * inv[4] + data[2] * inv[8] + data[3] * inv[12];
	if (det == 0)    return *this;
	det = 1.0f / det;

	for (i = 0; i < 16; i++)
		data[i] = (float)(inv[i] * det);

	return *this;
}
float Matrix4F::GetF(const int r, const int c)		{ return (float)data[(r << 2) + c]; }

void Matrix4F::GetRowVec(int r, Vector3DF &v)
{
	v.x = data[(r << 2)];
	v.y = data[(r << 2) + 1];
	v.z = data[(r << 2) + 2];
}

Matrix4F &Matrix4F::operator= (float* mat)
{
	for (int n = 0; n < 16; n++)
		data[n] = mat[n];
	return *this;
}

// Translate after (post-translate)
// Computes: M' = T*M
//
Matrix4F &Matrix4F::operator+= (const Vector3DF& t)
{
	data[12] += (VTYPE)t.x;
	data[13] += (VTYPE)t.y;
	data[14] += (VTYPE)t.z;
	return *this;
}

// Translate first (pre-translate)
// Computes: M' = M*T
Matrix4F &Matrix4F::PreTranslate(const Vector3DF& t)
{
	data[12] += (VTYPE)data[0] * t.x + data[4] * t.y + data[8] * t.z;
	data[13] += (VTYPE)data[1] * t.x + data[5] * t.y + data[9] * t.z;
	data[14] += (VTYPE)data[2] * t.x + data[6] * t.y + data[10] * t.z;
	return *this;
}

Matrix4F &Matrix4F::operator*= (const Vector3DF& t)		// quick scale
{
	data[0] *= (VTYPE)t.x;	data[1] *= (VTYPE)t.x;	data[2] *= (VTYPE)t.x;	data[3] *= (VTYPE)t.x;
	data[4] *= (VTYPE)t.y;	data[5] *= (VTYPE)t.y;	data[6] *= (VTYPE)t.y;	data[7] *= (VTYPE)t.y;
	data[8] *= (VTYPE)t.z;	data[9] *= (VTYPE)t.z;	data[10] *= (VTYPE)t.z; data[11] *= (VTYPE)t.z;
	return *this;
}

Matrix4F &Matrix4F::InverseProj(float* mat)
{
	data[0] = 1.0f / mat[0];	data[1] = 0.0f;			data[2] = 0.0f;						data[3] = 0.0f;
	data[4] = 0.0f;			data[5] = 1.0f / mat[5];	data[6] = 0.0f;						data[7] = 0.0f;
	data[8] = 0.0f;			data[9] = 0.0f;			data[10] = 0.0f;					data[11] = 1.0f / mat[14];
	data[12] = mat[8] / mat[0];		data[13] = mat[9] / mat[5];		data[14] = -1.0f;	data[15] = mat[10] / mat[14];
	return *this;
}

Matrix4F &Matrix4F::InverseView(float* mat, Vector3DF& pos)
{
	// NOTE: Assumes there is no scaling in input matrix.
	// Although there can be translation (typical of a view matrix)
	data[0] = mat[0];	data[1] = mat[4];	data[2] = mat[8];	data[3] = 0.0f;
	data[4] = mat[1];	data[5] = mat[5];	data[6] = mat[9];	data[7] = 0.0f;
	data[8] = mat[2];	data[9] = mat[6];	data[10] = mat[10];	data[11] = 0.0f;
	data[12] = pos.x;	data[13] = pos.y;	data[14] = pos.z;	data[15] = 1.0f;
	return *this;
}

Vector4DF Matrix4F::GetT(float* mat)
{
	return Vector4DF(mat[12], mat[13], mat[14], 1.0);
}

void Matrix4F::Print()
{
	printf((char*) "%04.3f %04.3f %04.3f %04.3f\n", data[0], data[1], data[2], data[3]);
	printf((char*) "%04.3f %04.3f %04.3f %04.3f\n", data[4], data[5], data[6], data[7]);
	printf((char*) "%04.3f %04.3f %04.3f %04.3f\n", data[8], data[9], data[10], data[11]);
	printf((char*) "%04.3f %04.3f %04.3f %04.3f\n\n", data[12], data[13], data[14], data[15]);
}
std::string Matrix4F::WriteToStr()
{
	char buf[4096];
	std::string str;
	sprintf_s(buf, 4096, "   %f %f %f %f\n", data[0], data[1], data[2], data[3]); str = buf;
	sprintf_s(buf, 4096, "   %f %f %f %f\n", data[4], data[5], data[6], data[7]); str += buf;
	sprintf_s(buf, 4096, "   %f %f %f %f\n", data[8], data[9], data[10], data[11]); str += buf;
	sprintf_s(buf, 4096, "   %f %f %f %f\n", data[12], data[13], data[14], data[15]); str += buf;
	return str;
}

#undef VTYPE
#undef VNAME

