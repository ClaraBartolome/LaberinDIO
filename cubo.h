#pragma once
#include <GL/glut.h>
#include "solido.h"
#include "camara.h"

/**
* Crea un cubo que hereda de solido(con posicion, velocidad, color, fuerza y masa) y un tamaño de lado .
* Servirá para el dibujo del WIN 
*/
class Cubo :public Solido
{
	double s; /* Lado del cubo */
public:

	/**
	*	Constructor de la clase Cubo que inicializa un Cubo sin pasarle parametros
	*/
	Cubo() : Solido(), s(0.25) {}

	/**
	*	Constructor de la clase Cubo a partir de 4 variables, 3 de tipo Vector3D y la última de tipo double
	*	@param p Vector3D de posicion
	*	@param c Vector3D de color
	*	@param v Vector3D de velocidad
	*	@param d double que indica el tamaño del lado
	*/
	Cubo(Vector3D p, Vector3D c = Vector3D(1, 0, 0), Vector3D v = Vector3D(), double d = 0.25) :
		Solido(p, c, v),
		s(d) {}

	/**
	*	Constructor de la clase Cubo a partir de otro Cubo
	*	@param &c Referencia a un Cubo ya creado
	*/
	Cubo(const Cubo &c) :Solido(c), s(c.s) {}

	/**
	*	Constructor clon de la clase Cubo a partir de otro Cubo
	*/
	Cubo *clone() {
		return new Cubo(*this);
	}

	/**
	*	Destructor de la clase Cubo
	*/
	~Cubo();

	/* Metodos de acceso */

	/**
	*	Devuelve el lado
	*/
	double getS() { return s; }

	/**
	*	Cambia el valor del lado
	*	@param d referencia al valor nuevo
	*/
	void setS(double d) { s = d; }

	/**
	* Renderiza el Cubo
	*/
	void render();

	/**
	*	Muestra los parametros del Cubo por consola
	*/
	friend ostream &operator<<(ostream &os, const Cubo &c);

	/**
	*	Comprueba si el Cubo tiene colision con una camara
	*/
	bool colisionCam(CamaraFPS cam) { return 0; }

	/**
	*	Comprueba si el Cubo tiene colision con una Pared
	*/
	bool colisionPar(Solido* s) { return 0; }

	/**
	* Actualiza la posicion, velocidad y aceleracion del Cubo
	* @param dt el diferencial de tiempo utilizado
	*
	*/
	void update(double dt) {}
};
inline ostream &operator<<(ostream &os, const Cubo &c) {
	os << static_cast<const Solido&>(c);
	os << c.s << endl;
	return os;
}