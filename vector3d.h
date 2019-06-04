//#pragma once
#ifndef VECTOR3D__
#define VECTOR3D__
#include <iostream>


using namespace std;
/**
*
*	Crea un vector con 3 dimensiones y sus operaciones necesarias
*
*/
class Vector3D {
private:
	double x, /* Coordenada x */
		   y, /* Coordenada y */
		   z; /* Coordenada z */
public:
	/**
	*	Constructor de la clase Vector3D a partir de 3 variables de tipo double
	*	@param px primera coordenada del vector
	*	@param y segunda coordenada del vector
	*	@param z tercera coordenada del vector	
	*/
	Vector3D(double px = 0, double y = 0, double z = 0) :x(px), y(y), z(z) {}

	/**
	*	Constructor de la clase Vector3D a partir de otro Vector3D
	*	@param &v Referencia a un Vector3D ya creado
	*/
	Vector3D(const Vector3D &v) :x(v.x), y(v.y), z(v.z) {}

	/**
	*	Constructor clon de la clase Vector3D
	*/
	Vector3D* clone() {
		return new Vector3D(*this);
	}

	/**
	*	Devuelve la coordenada x	
	*/
	inline double getX() const { return x; }

	/**
	*	Devuelve la coordenada y
	*/
	inline double getY() const { return y; }

	/**
	*	Devuelve la coordenada z
	*/
	inline double getZ() const { return z; }

	/**
	*	Cambia el valor de la coordenada x
	*	@param &d referencia al valor nuevo
	*/
	inline void setX(double &d) { x = d; }

	/**
	*	Cambia el valor de la coordenada x
	*	@param &d referencia al valor nuevo constante
	*/
	inline void setX(const double &d) { x = d; }

	/**
	*	Cambia el valor de la coordenada y
	*	@param &d referencia al valor nuevo
	*/
	inline void setY(double &d) { y = d; }

	/**
	*	Cambia el valor de la coordenada y
	*	@param &d referencia al valor nuevo constante
	*/
	inline void setY(const double &d) { y = d; }

	/**
	*	Cambia el valor de la coordenada z
	*	@param &d referencia al valor nuevo
	*/
	inline void setZ(double &d) { z = d; }

	/**
	*	Cambia el valor de la coordenada z
	*	@param &d referencia al valor nuevo constante
	*/
	inline void setZ(const double &d) { z = d; }

	/**
	*	Suma dos Vectores 3D
	*	@param &b segunda componente de la suma
	*	@return r Resultado de la suma de los dos Vectores	
	*/
	Vector3D suma(const Vector3D &b);

	/**
	*	Suma dos Vectores 3D sobrecargando la operacion predefinida
	*	@param &b segunda componente de la suma
	*	@return r Resultado de la suma de los dos Vectores
	*/
	Vector3D operator+(const Vector3D &b);

	/**
	*	Resta dos Vectores 3D sobrecargando la operacion predefinida
	*	@param &b segunda componente de la resta
	*	@return r Resultado de la resta de los dos Vectores
	*/
	Vector3D operator-(const Vector3D &b);

	/**
	*	Resta dos Vectores 3D 
	*	@param &b segunda componente de la resta
	*	@return r Resultado de la resta de los dos Vectores
	*/
	Vector3D resta(Vector3D b);
	/**
	*	Multiplica dos Vectores 3D 
	*	@param &b segunda componente de la multiplicacion
	*	@return r Resultado de la multiplicacion de los dos Vectores
	*/
	Vector3D productoPorEscalar(double b);
	/**
	*	Multiplica dos Vectores 3D sobrecargando la operacion predefinida
	*	@param &b segunda componente de la multiplicacion
	*	@return r Resultado de la multiplicacion de los dos Vectores
	*/
	Vector3D operator*(double b);
	/**
	*	Divide dos Vectores 3D sobrecargando la operacion predefinida
	*	@param &b segunda componente de la Division
	*	@return r Resultado de la division de los dos Vectores
	*/
	Vector3D operator/(double b);

	/*
	Multiplica un Vector 3D por un escalar
	@param &b Vector3D a multiplicar
	@return r Resultado de la multiplicacion de los dos Vectores
	*/
	double productoEscalar(Vector3D v);

	/**
	*	Multiplica un Vector 3D por un escalar sobrecargando la operacion predefinida
	*	@param &b Vector3D a multiplicar
	*	@return r Resultado de la multiplicacion de los dos Vectores
	*/
	double operator*(Vector3D v);

	/**
	*	Producto vectorial de dos Vectores3D
	*	@param &b Vector3D a multiplicar
	*	@return r Resultado del Producto vectorial de los dos Vectores
	*/
	inline Vector3D crossProduct(const Vector3D &v2) {
		Vector3D &v1 = *this;
		return Vector3D(v1.y*v2.z - v1.z*v2.y,
			v1.z*v2.x - v1.x*v2.z,
			v1.x*v2.y - v1.y*v2.x);
	}

	/**
	*	Modulo al cuadrado de un Vector3D
	*	@return double modulo al cuadrado del vector
	*/
	inline double lengthSquared() {
		return x * x + y * y + z * z;
	}

	/**
	*	Modulo de un Vector3D
	*	@return double modulo del vector
	*/
	inline double length() {
		return sqrt(lengthSquared());
	}

	/**
	*	Devuelve el resultado de la comprobacion sobre si el vector3D es igual a 0
	*	@return bool Vector3D es igual a 0
	*/
	inline bool equalsZero(double a) {
		//float almost never is 0.0
		//This value shoud be a const
		return fabs(a) < 0.000001;
	}

	/**
	*	Normaliza el vector3D
	*/
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

	/**
	*	Muestra el Vector3D por consola
	*/
	friend ostream &operator<<(ostream &os, const Vector3D &v);
};
inline ostream &operator<<(ostream &os, const Vector3D &v) {
	os << v.x << "," << v.y << "," << v.z;
	return os;
}
#endif // !VECTOR3D__
