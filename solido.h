#pragma once

#include <GL/glut.h>
#include "vector3d.h"
#include "Camara.h"

class Solido {
	Vector3D pos;
	Vector3D vel;
	Vector3D col;
	Vector3D f;
	double m;
public:
	/* Constructores */
	Solido() :
		pos(Vector3D()),
		vel(),
		col(1, 1, 0),
		f(),
		m(1) {}
	Solido(Vector3D p, Vector3D c = Vector3D(1, 0, 0), Vector3D v = Vector3D(), Vector3D f = Vector3D(), double m = 1) :
		pos(Vector3D(p.getX(), p.getY(), p.getZ())),
		vel(p.getX(), p.getY(), p.getZ()),
		col(c), f(f), m(m) {}
	Solido(const Solido &c) :pos(c.pos), vel(c.vel), col(c.col), f(c.f), m(c.m) {}
	virtual Solido* clone() = 0;
	/* Metodos de acceso */
	Vector3D getPos() { return pos; }
	void setPos(const Vector3D &v) { pos = v; }
	Vector3D getVel() { return vel; }
	void setVel(const Vector3D &v) { vel = v; }
	Vector3D getCol() { return col; }
	void setCol(Vector3D v) { col = v; }
	Vector3D getF() { return f; }
	void setF(Vector3D v) { f = v; }
	double getM() { return m; }
	void setM(double d) { m = d; }

	void acumulaFuerza(Vector3D fv) { f = f + fv; }

	virtual void update(double dt) = 0;
	virtual void render() = 0;
	friend ostream &operator<<(ostream &os, const Solido &c);

	virtual bool colisionCam(CamaraFPS cam) = 0;
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
