#pragma once
#include <cmath>
#include <GL/glut.h>
#include "vector3d.h"
#include <iostream>

//#define M_PI 3.14159
const double M_PI = 3.14159;

inline double rot2rad(double  a) { return a / 180 * M_PI; }

using namespace std;

	/**
	*	Crea una cámara que servira para renderizar la escena
	*/
class Camara {
	Vector3D pos; /* Vector3D que guarda la posicion de la camara */
	Vector3D rot; /* Vector3D que guarda la rotacion de la camara */
public:
	/**
	*	Constructor de la clase Camara que inicializa una cámara sin parametros
	*/
	Camara();

	/**
	*	Constructor de la clase Camara a partir de 3 variables de tipo double
	*	@param x primera coordenada del Vector3D de posicion
	*	@param y segunda coordenada del Vector3D de posicion
	*	@param z tercera coordenada del Vector3D de posicion
	*/
	Camara(double x, double y, double z) :pos(Vector3D(x, y, z)) {}

	/**Destructor de la clase Camara*/
	virtual ~Camara();

	/**
	*	Devuelve la Posicion de la camara
	*/
	inline Vector3D getPos() const { return pos; }

	/**
	*	Cambia la Posicion de la camara
	*/
	inline void setPos(Vector3D pos) { this->pos = pos; }

	/**
	*	Devuelve la Rotacion de la camara
	*/
	inline Vector3D getRot() const { return rot; }

	/**
	*	Cambia la Rotacion de la camara
	*/
	inline void setRot(Vector3D rot) { this->rot = rot; }


	/**
	* Renderiza la Cámara	
	*/
	void render() {
		glTranslatef(-this->getPos().getX(), -this->getPos().getY(), -this->getPos().getZ());
		glRotatef(getRot().getX(), 1, 0, 0);
		glRotatef(getRot().getY(), 0, 1, 0);
		glRotatef(getRot().getZ(), 0, 0, 1);
	}
};

	/**
	*	Crea una cámara en primera persona que servira para renderizar la escena
	*/
class CamaraFPS : public Camara {
public:

	/**
	*	Constructor de la clase Camara a partir de 3 variables de tipo double
	*	@param x primera coordenada del Vector3D de posicion
	*	@param y segunda coordenada del Vector3D de posicion
	*	@param z tercera coordenada del Vector3D de posicion
	*/
	CamaraFPS(double x = 0, double y = 1.85, double z = 0) :Camara(x, y, z) {}

	/**
	*	Actualiza la posicion y rotacion de la camara
	*	@param dt el diferencial de tiempo utilizado
	*/
	void update(double dt)
	{
		double ry = rot2rad(getRot().getY()); //ROTACION
		Vector3D dir = { -sin(ry) , 0 , cos(ry) }; //MOVIMIENTO DIRECCION
		setPos(getPos() - dir * dt);

		
	}

	/**
	* Renderiza la Cámara
	*/
	void render() {
		glRotatef(getRot().getX(), 1, 0, 0);
		glRotatef(getRot().getY(), 0, 1, 0);
		glRotatef(getRot().getZ(), 0, 0, 1);
		glTranslatef(-getPos().getX(), -getPos().getY(), -getPos().getZ());
	}
};



