#include "solido.h"
void Solido::update(double dt) {
	double MAX = 50;
	pos = pos + vel * dt;
	Vector3D a = f / m;
	vel = vel + a * dt;


	/* // Colisiones
	if (pos.getX() > MAX || pos.getX() < -MAX) {
		double d = vel.getX()*-0.9;
		vel.setX(d);
	}
	if (pos.getZ() > MAX || pos.getZ() < -MAX) {
		double d = vel.getZ()*-0.9;
		vel.setZ(d);
	}
	if (pos.getY() < 0) {
		double d = vel.getY()*-0.9;
		vel.setY(d);
		pos.setY(0);
	}
	*/
}
