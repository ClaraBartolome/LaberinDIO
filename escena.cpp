#include "escena.h"
#include "solido.h"

Escena::Escena()
{
}

Escena::~Escena() {
	for (Solido *s : paredes) {
		delete s;
	}
	paredes.clear();//No necesario es llamado automaticamente por el destructor de vector
}

void Escena::render() {
	switch (C) {
	case 1:
		cam.render();
		break;
		{
	case 2:
		cam2.render();
		break;
		}
	}


	for (Solido* s : paredes)
	{
		s->render();
	}
	for (Solido* e : enemigos)
	{
		e->render();
	}
	for (Solido* e : cubos)
	{
		e->render();
	}


}

void Escena::update(double dt) {


	for (Solido* &s : paredes) {
		s->update(dt);
		for (Solido* e : enemigos)
		{

			if (s->colisionPar(e)) {

				if (abs(e->getPos().getX()) != (e->getPos().getX() + e->getVel().getX())) {
					double d = e->getVel().getX()* -1;
					e->setVel(Vector3D(d, 0, e->getVel().getZ()));
				}
				if (abs(e->getPos().getZ()) != (e->getPos().getZ() + e->getVel().getZ())) {
					double d = e->getVel().getZ()* -1;
					e->setVel(Vector3D(e->getVel().getX(), 0, d));
				}

			}



		}


	}

	for (Solido* e : enemigos)
	{
		e->update(dt);

		if (e->colisionCam(cam) == 1) {
			cam.setPos(Vector3D(0, 1.85, 5));
		}

	}

}
