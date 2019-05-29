#pragma once
#include <vector>
#include "solido.h"
#include "camara.h"

using namespace std;

class Escena
{
	vector<Solido*> paredes;
	vector<Solido*> enemigos;
	vector<Solido*> cubos;
	CamaraFPS cam;
	Camara cam2;
	int C = 1; //Int que decide que camara renderiza

public:
	Escena();
	~Escena();
	vector<Solido*> getSolidos() { return paredes; }
	void setSolidos(vector<Solido*> e) { paredes = e; }
	vector<Solido*> getEnemigos() { return enemigos; }
	void setEnemigos(vector<Solido*> e) { enemigos = e; }
	void render();
	void update(double dt);

	void addP(Solido* e) {
		paredes.push_back(e);
	}
	void addE(Solido* e) {
		enemigos.push_back(e);
	}
	void add(Solido* e) {
		cubos.push_back(e);
	}

	void addC(CamaraFPS c) {
		cam = c;
	}
	void addCF(Camara c) {
		cam2 = c;
	}

	CamaraFPS getCam() {
		return cam;
	}

	int getC() {
		return C;
	}

	void setC(int c) {
		C = c;
	}

	void updateCam(double dt) {

		double mvto = dt;

		for (Solido* &s : paredes) {

			if (s->colisionCam(cam) == 1) {

				cam.setPos(Vector3D(0, 1.85, 5));



			}

		}


		cam.update(mvto);
		//cout << cam.getPos();
		//cout << "\n";

	}

	void rotCam(Vector3D r)
	{
		cam.setRot(r);
	}


};

