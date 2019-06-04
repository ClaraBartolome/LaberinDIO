#pragma once

#include <GL/glut.h>
#include "vector3d.h"
#include "Camara.h"

/**
* Crea un solido con posicion, velocidad, color, fuerza y masa. 
* Servirá de base para el resto de clases que salen en la escena
*/
class Solido {
	Vector3D pos; /* Vector3D que indica la posicion */
	Vector3D vel; /* Vector3D que indica la velocidad */
	Vector3D col; /* Vector3D que indica el color */
	Vector3D f; /* Vector3D que indica la fuerza */
	double m; /* Double que indica la masa */
public:
	/* Constructores */

	/**
	*	Constructor de la clase Solido que inicializa un Solido sin pasarle parametros
	*/
	Solido() :
		pos(Vector3D()),
		vel(),
		col(1, 1, 0),
		f(),
		m(1) {}

	/**
	*	Constructor de la clase Solido a partir de 5 variables, 4 de tipo Vector3D y la última de tipo double
	*	@param p Vector3D de posicion
	*	@param c Vector3D de color
	*	@param v Vector3D de velocidad
	*	@param f Vector3D de fuerza
	*	@param m double de masa
	*/
	Solido(Vector3D p, Vector3D c = Vector3D(1, 0, 0), Vector3D v = Vector3D(), Vector3D f = Vector3D(), double m = 1) :
		pos(Vector3D(p.getX(), p.getY(), p.getZ())),
		vel(p.getX(), p.getY(), p.getZ()),
		col(c), f(f), m(m) {}

	/**
	*	Constructor de la clase Solido a partir de otro Solido
	*	@param &c Referencia a un Solido ya creado
	*/
	Solido(const Solido &c) :pos(c.pos), vel(c.vel), col(c.col), f(c.f), m(c.m) {}

	/**
	*	Constructor clon de la clase Solido
	*/
	virtual Solido* clone() = 0;

	/* Metodos de acceso */

	/**
	*	Devuelve la posicion
	*/
	Vector3D getPos() { return pos; }

	/**
	*	Cambia el valor de la posicion
	*	@param &v referencia al valor nuevo
	*/
	void setPos(const Vector3D &v) { pos = v; }

	/**
	*	Devuelve la velocidad
	*/
	Vector3D getVel() { return vel; }

	/**
	*	Cambia el valor de la velocidad
	*	@param &v referencia al valor nuevo
	*/
	void setVel(const Vector3D &v) { vel = v; }

	/**
	*	Devuelve el color
	*/
	Vector3D getCol() { return col; }

	/**
	*	Cambia el valor del color
	*	@param v referencia al valor nuevo
	*/
	void setCol(Vector3D v) { col = v; }

	/**
	*	Devuelve la fuerza
	*/
	Vector3D getF() { return f; }

	/**
	*	Cambia el valor de la fuerza
	*	@param v referencia al valor nuevo
	*/
	void setF(Vector3D v) { f = v; }

	/**
	*	Devuelve la masa
	*/
	double getM() { return m; }

	/**
	*	Cambia el valor de la masa
	*	@param d referencia al valor nuevo
	*/
	void setM(double d) { m = d; }


	/**
	* Suma un Vector3D al valor de la fuerza f
	*  @param fv valor a sumar
	*/
	void acumulaFuerza(Vector3D fv) { f = f + fv; }

	/**
	* Actualiza la posicion, velocidad y aceleracion del solido
	* @param dt el diferencial de tiempo utilizado
	*
	*/
	virtual void update(double dt) = 0;

	/**
	* Renderiza el Solido, esta clase se implementara en las clases hijas de Solido
	*/
	virtual void render() = 0;

	/**
	*	Muestra los parametros del Solido por consola
	*/
	friend ostream &operator<<(ostream &os, const Solido &c);

	/**
	*	Comprueba si el Solido tiene colision con una camara. Implementado en sus clases hijas
	*/
	virtual bool colisionCam(CamaraFPS cam) = 0;

	/**
	*	Comprueba si el Solido tiene colision con una Pared. Implementado en sus clases hijas
	*/
	virtual bool colisionPar(Solido* s) = 0;
};
inline ostream &operator<<(ostream &os, const Solido &c) {
	os << c.pos << endl;
	os << c.vel << endl;
	os << c.col << endl;
	os << c.f << endl;
	os << c.m << endl;
	return os;
}
