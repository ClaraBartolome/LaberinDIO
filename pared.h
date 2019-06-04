#pragma once
#include <GL/glut.h>
#include "solido.h"
#include "camara.h"


/**
* Crea una Pared que hereda de solido(con posicion, velocidad, color, fuerza y masa), un tamaño de dimension y un boolean que indica si es vertical u horizontal.
* Servirá para crear el laberinto
*/
class Pared : public Solido {
	Vector3D dim; /*Dimension de la Pared*/
	bool vertical; /*Indica si la pared es horizontal o vertical*/
public:

	/**
	*	Constructor de la clase Pared a partir de 3 variables de tipo double
	*	@param x longitud
	*	@param y altura
	*	@param z profundidad
	*/
	Pared(double x = 4, double y = 3, double z = 0.5) :dim(Vector3D(x, y, z)), vertical(false){}

	/**
	*	Constructor de la clase Pared a partir de otra Pared
	*	@param &p Referencia a una Pared ya creada
	*/
	Pared(const Pared &p) :Solido(p), dim(p.dim), vertical(p.vertical) {}

	/**
	*	Constructor clon de la clase Pared a partir de otro Pared
	*/
	Pared* clone() {
		return new Pared(*this);
	}

	/**
	* Destructor de la clase Pared
	*/
	virtual ~Pared();

	/**
	*	Cambia el valor de vertical
	*	@param b indica si es vertical o no
	*/
	void setVertical(bool b) { vertical = b; }

	/**
	*	Devuelve si es Vertical
	*/
	bool getVertical() { return vertical; }

	/**
	* Renderiza la pared
	*/
	void render() {
		glPushMatrix();
		glTranslatef(this->getPos().getX(), this->getPos().getY(), this->getPos().getZ());
		glTranslatef(0, dim.getY() / 2.0, 0);
		glRotatef(vertical ? 90 : 0, 0, 1, 0);
		glColor3f(this->getCol().getX(), this->getCol().getY(), this->getCol().getZ());

		glScalef(dim.getX(), dim.getY(), dim.getZ());
		glutSolidCube(1);
		glPopMatrix();
	}

	/**
	*	Muestra los parametros de la pared por consola
	*/
	friend ostream &operator<<(ostream &os, const Pared &c);

	/**
	*	Indica si hay colision con la coordenada X de la Camara
	*	@param cam Una camara con la que comprobar la colision
	*/
	bool colisionCamX(CamaraFPS cam)
	{
		bool colision = 0;

		if (this->getVertical()) {
			if ((cam.getPos().getZ() > (this->getPos().getZ() - (dim.getX() / 2)) && (cam.getPos().getZ() < (this->getPos().getZ() + (dim.getX() / 2))))) {
				colision = 1;
			}
		}

		else {
			if ((cam.getPos().getX() > (this->getPos().getX() - (dim.getX() / 2))) && (cam.getPos().getX() < (this->getPos().getX() + (dim.getX() / 2)))) {
				colision = 1;
			}
		}


		return colision;
	}

	/**
	*	Indica si hay colision con la coordenada Y de la Camara
	*	@param cam Una camara con la que comprobar la colision
	*/
	bool colisionCamY(CamaraFPS cam)
	{
		bool colision = 0;

		if (cam.getPos().getY() > this->getPos().getY() && cam.getPos().getY() < (this->getPos().getY() + dim.getY())) {
			colision = 1;
		}

		return colision;
	}

	/**
	*	Indica si hay colision con la coordenada Z de la Camara
	*	@param cam Una camara con la que comprobar la colision
	*/
	bool colisionCamZ(CamaraFPS cam)
	{
		bool colision = 0;

		if (this->getVertical()) {
			if ((cam.getPos().getX() > (this->getPos().getX() - (dim.getZ() / 2)) && (cam.getPos().getX() < (this->getPos().getX() + (dim.getZ() / 2))))) {
				colision = 1;
			}
		}

		else {
			if ((cam.getPos().getZ() + (dim.getZ() / 2) > (this->getPos().getZ()) && (cam.getPos().getZ() < (this->getPos().getZ() + (dim.getZ() / 2))))) {
				colision = 1;
			}

		}

		return colision;
	}

	/**
	*	Indica si hay colision con Camara
	*	@param cam Una camara con la que comprobar la colision
	*/
	bool colisionCam(CamaraFPS cam)
	{
		bool colision = 0;

		if (this->colisionCamX(cam) == 1 && this->colisionCamY(cam) == 1 && this->colisionCamZ(cam) == 1) {
			colision = 1;
		}

		return colision;

	};


	//COLISION PARED CON PARED

	/**
	*	Indica si hay colision con la coordenada X de una Pared
	*	@param cam Un Solido (Que siempre sera una Pared) con el que comprobar la colision
	*/
	bool colisionParX(Solido* s)
	{
		bool colision = 0;

		if (this->getVertical()) {
			if ((s->getPos().getZ() > (this->getPos().getZ() - (dim.getX() / 2)) && (s->getPos().getZ() < (this->getPos().getZ() + (dim.getX() / 2))))) {
				colision = 1;
			}
		}

		else {
			if ((s->getPos().getX() > (this->getPos().getX() - (dim.getX() / 2))) && (s->getPos().getX() < (this->getPos().getX() + (dim.getX() / 2)))) {
				colision = 1;
			}
		}


		return colision;
	}

	/**
	*	Indica si hay colision con la coordenada Y de una Pared
	*	@param cam Un Solido (Que siempre sera una Pared) con el que comprobar la colision
	*/
	bool colisionParY(Solido* s)
	{
		bool colision = 0;

		if ((s->getPos().getY() > (this->getPos().getY() - (dim.getY() / 2))) && (s->getPos().getY() < (this->getPos().getY() + (dim.getY() / 2)))) {
			colision = 1;
		}

		return colision;
	}

	/**
	*	Indica si hay colision con la coordenada Z de una Pared
	*	@param cam Un Solido (Que siempre sera una Pared) con el que comprobar la colision
	*/
	bool colisionParZ(Solido* s)
	{
		bool colision = 0;

		if (this->getVertical()) {
			if ((s->getPos().getX() > (this->getPos().getX() - (dim.getZ() / 2)) && (s->getPos().getX() < (this->getPos().getX() + (dim.getZ() / 2))))) {
				colision = 1;
			}
		}

		else {
			if ((s->getPos().getZ() + (dim.getZ() / 2) > (this->getPos().getZ()) && (s->getPos().getZ() < (this->getPos().getZ() + (dim.getZ() / 2))))) {
				colision = 1;
			}

		}

		return colision;
	}

	/**
	*	Indica si hay colision con una Pared
	*	@param cam Un Solido (Que siempre sera una Pared) con el que comprobar la colision
	*/
	bool colisionPar(Solido* s)
	{
		bool colision = 0;

		if (this->colisionParX(s) == 1 && this->colisionParY(s) == 1 && this->colisionParZ(s) == 1) {
			colision = 1;

		}


		return colision;

	};

	/**
	* Actualiza la posicion, velocidad y aceleracion de la Pared
	* @param dt el diferencial de tiempo utilizado
	*
	*/
	void update(double dt);

};

inline ostream &operator<<(ostream &os, const Pared &c) {
	os << static_cast<const Solido&>(c);
	os << c.dim << endl;
	return os;
}