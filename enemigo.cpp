#include "enemigo.h"







Enemigo::~Enemigo()
{
}

void Enemigo::update(double dt)
{
	//if (this->pared == 0) { //si es un enemigo

	this->setPos(this->getPos() + this->getVel() * dt);
	Vector3D a = this->getF() / this->getM();
	this->setVel((this->getVel() + (a * dt)));

	//}

}
