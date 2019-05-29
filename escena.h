#pragma once
#include <vector>
#include <string>
#include "solido.h"
#include "camara.h"
#include <iostream>
#include <fstream>

using namespace std;

class Escena
{
	vector<Solido*> paredes;
	vector<Solido*> enemigos;
	vector<Solido*> cubos;
	CamaraFPS cam;
	Camara cam2;
	int C = 1; //Int que decide que camara renderiza
	double points = 0;

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

	void setPoints(int P) { points = P; }

	int getPoints() { return points; }


	CamaraFPS getCam() {
		return cam;
	}

	int getC() {
		return C;
	}

	void setC(int c) {
		C = c;
	}

	void menu() {
		cout << "--------------------------------  \n";
		cout << "-  Bienvenido a LaberinDIO:    - \n";
		cout << "-  Jugar : Y                   - \n";
		cout << "-  Ranking de Puntuaciones : R - \n";
		cout << "-  Salir : X                   - \n";
		cout << "--------------------------------  \n";
	}


	void write() {
		ofstream myfile("Ranking.txt");
		if (myfile.is_open()) {
			myfile << "Puntuacion: ";
			myfile << this->getPoints();
			myfile.close();
		}
		else
			cout << "Unable to openfile";
	}

	void read() {
		string line;
		ifstream myfile("Ranking.txt");
		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				cout << line << "\ n";
			}
			myfile.close();
		}
		else
			cout << "Unable to open file";
	}

	void updateCam(double dt) {

		double mvto = dt;

		for (Solido* &s : paredes) {

			if (s->colisionCam(cam) == 1) {

				cam.setPos(Vector3D(0, 1.85, 5));
				points = points + 100;
				cout << "Puntuacion: ";
				cout << points;
				cout << "\n";

			}

		}


		cam.update(mvto);
		//cout << cam.getPos();
		//cout << "\n";

		//FINAL 
		if (cam.getPos().getX() >= 12, 5 && cam.getPos().getX() <= 7, 5 && cam.getPos().getY() == 1.85 && cam.getPos().getZ() <= -47) {
			cout << "Ganaste \n";
			cout << "Puntuacion final: ";
			cout << points;
			cout << "\n";
			cam.setPos(Vector3D(1003, 3, 0));
			cam.setRot(Vector3D(90, 0, 0));
			menu();

		}


	}

	void rotCam(Vector3D r)
	{
		cam.setRot(r);
	}


};

