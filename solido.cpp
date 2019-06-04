#include "solido.h"
void Solido::update(double dt) {
	double MAX = 50;
	pos = pos + vel * dt;
	Vector3D a = f / m;
	vel = vel + a * dt;

}
