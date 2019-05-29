//#pragma once
#ifndef VECTOR3D__
#define VECTOR3D__
#include <iostream>

using namespace std;

class Vector3D {
private:
	double x, y, z;
public:
	//Vector3D():x(0),y(0),z(0) {}
	Vector3D(double px = 0, double y = 0, double z = 0) :x(px), y(y), z(z) {}
	Vector3D(const Vector3D &v) :x(v.x), y(v.y), z(v.z) {}
	Vector3D* clone() {
		return new Vector3D(*this);
	}
	//Vector3D() :x(0), y(0), z(0) {}
	//Vector3D(double px) :x(px), y(0), z(0) {}
	//Vector3D(double px, double y) :x(px), y(y), z(0) {}
	//Vector3D(double px, double y, double z) :x(px), y(y), z(z) {}
	inline double getX() const { return x; }
	inline double getY() const { return y; }
	inline double getZ() const { return z; }
	//inline void setX(double  d) { x = d; }
	inline void setX(double &d) { x = d; }
	inline void setX(const double &d) { x = d; }
	inline void setY(double &d) { y = d; }
	inline void setY(const double &d) { y = d; }
	inline void setZ(double &d) { z = d; }
	inline void setZ(const double &d) { z = d; }
	Vector3D suma(const Vector3D &b);
	Vector3D operator+(const Vector3D &b);
	Vector3D operator-(const Vector3D &b);
	Vector3D resta(Vector3D b);
	Vector3D productoPorEscalar(double b);
	Vector3D operator*(double b);
	Vector3D operator/(double b);
	double productoEscalar(Vector3D v);
	double operator*(Vector3D v);
	inline Vector3D crossProduct(const Vector3D &v2) {
		Vector3D &v1 = *this;
		return Vector3D(v1.y*v2.z - v1.z*v2.y,
			v1.z*v2.x - v1.x*v2.z,
			v1.x*v2.y - v1.y*v2.x);
	}
	inline double lengthSquared() {
		return x * x + y * y + z * z;
	}

	inline double length() {
		return sqrt(lengthSquared());
	}
	inline bool equalsZero(double a) {
		//float almost never is 0.0
		//This value shoud be a const
		return fabs(a) < 0.000001;
	}
	inline void normalize() {
		double magnitude = length();
		//assert(!equalsZero(magnitude));
		if (equalsZero(magnitude)) {
			throw runtime_error("Magnitud de vector muy pequeña en normalize()");
		}

		magnitude = 1.0 / magnitude;

		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
	}
	friend ostream &operator<<(ostream &os, const Vector3D &v);
};
inline ostream &operator<<(ostream &os, const Vector3D &v) {
	os << v.x << "," << v.y << "," << v.z;
	return os;
}
#endif // !VECTOR3D__
/*
//Devolver constante de un objeto mutable v
class Vector3D {
	const double &getX() { return x; }
	double &getY() { return y; }
	.......
};
//Objeto mutable ya que no se declara con const
Vector3D v(1, 2, 3);

const double &d = v.getX();
d = 4;///ERROR d es constante
double &c = v.getY();
c = 7;


//Devolver valores a objetos const v
class Vector3D {
	double getX() { return x; }
	double getY() const { return y; }
	.......
};
//Objeto const v
const Vector3D v(1, 2, 3);
double d = v.getX();//No se pude hacer v es constante
double c = v.getY();//se puede hacer ya que getY() est permitido en const
*/