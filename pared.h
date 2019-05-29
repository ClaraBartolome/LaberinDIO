#pragma once
#include <GL/glut.h>
#include "solido.h"
#include "camara.h"

class Pared : public Solido {
	Vector3D dim;
	bool vertical;
	//bool pared; //DISTINGUIRA SI ES PARED O ENEMIGO
public:
	//x=longitud, y=altura, z=profundidad
	Pared(double x = 4, double y = 3, double z = 0.5) :dim(Vector3D(x, y, z)), vertical(false){}
	Pared(const Pared &p) :Solido(p), dim(p.dim), vertical(p.vertical) {}

	Pared* clone() {
		return new Pared(*this);
	}

	virtual ~Pared();
	void setVertical(bool b) { vertical = b; }
	bool getVertical() { return vertical; }
	//void setPared(bool p) { pared = p; }
	//bool getPared() { return pared; }

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
	friend ostream &operator<<(ostream &os, const Pared &c);

	//e.posX > this.posX && e.posX < this.posX + this.ancho && e.posY > this.posY && e.posY < this.posY + this.alto

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
	bool colisionCamY(CamaraFPS cam)
	{
		bool colision = 0;

		if (cam.getPos().getY() > this->getPos().getY() && cam.getPos().getY() < (this->getPos().getY() + dim.getY())) {
			colision = 1;
		}

		return colision;
	}

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

	bool colisionCam(CamaraFPS cam)
	{
		bool colision = 0;

		if (this->colisionCamX(cam) == 1 && this->colisionCamY(cam) == 1 && this->colisionCamZ(cam) == 1) {
			colision = 1;
		}

		return colision;

	};


	//COLISION PARED CON PARED

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
	bool colisionParY(Solido* s)
	{
		bool colision = 0;

		if ((s->getPos().getY() > (this->getPos().getY() - (dim.getY() / 2))) && (s->getPos().getY() < (this->getPos().getY() + (dim.getY() / 2)))) {
			colision = 1;
		}

		return colision;
	}

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

	bool colisionPar(Solido* s)
	{
		bool colision = 0;

		if (this->colisionParX(s) == 1 && this->colisionParY(s) == 1 && this->colisionParZ(s) == 1) {
			colision = 1;

		}


		return colision;

	};

	void update(double dt);

};

inline ostream &operator<<(ostream &os, const Pared &c) {
	os << static_cast<const Solido&>(c);
	os << c.dim << endl;
	return os;
}