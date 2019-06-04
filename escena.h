#pragma once
#include <vector>
#include <string>

#include <algorithm>
#include "solido.h"
#include "camara.h"
#include <iostream>
#include <fstream>

using namespace std;


/**
* Crea una escena sobre la que se desarrollara el juego
*/
class Escena
{
	vector<Solido*> paredes; /* Vector de punteros a solido que guarda las Paredes del Laberinto*/
	vector<Solido*> enemigos; /* Vector de punteros a solido que guarda los enemigos*/
	vector<Solido*> cubos; /* Vector de punteros a solido que guarda el dibujo del win*/
	CamaraFPS cam; /* Camara que manejara el jugador */
	Camara cam2;  /* Camara que sirve como mapa */
	int C = 1; /* Int que decide que camara renderiza */
	double points = 0; /* Double que indica la puntuacion */

public:

	/**
	*	Constructor de la clase Escena que inicializa un Solido sin pasarle parametros
	*/
	Escena();

	/**Destructor de la clase Escena*/
	~Escena();

	/**
	*	Devuelve el vector de Paredes
	*/
	vector<Solido*> getSolidos() { return paredes; }

	/**
	*	Cambia el valor del vector de Paredes
	*	@param &e referencia al nuevo vector
	*/
	void setSolidos(vector<Solido*> e) { paredes = e; }

	/**
	*	Devuelve el vector de Enemigos
	*/
	vector<Solido*> getEnemigos() { return enemigos; }

	/**
	*	Cambia el valor del vector de Enemigos
	*	@param &e referencia al nuevo vector
	*/
	void setEnemigos(vector<Solido*> e) { enemigos = e; }

	/**
	* Renderiza la escena entera
	*/
	void render();

	/**
	* Actualiza la posicion, velocidad y aceleracion de los elementos de la escena
	* @param dt el diferencial de tiempo utilizado
	*
	*/
	void update(double dt);

	/**
	*	Añade una pared al vector paredes
	*	@param &e referencia al nuevo solido
	*/
	void addP(Solido* e) {
		paredes.push_back(e);
	}

	/**
	*	Añade un enemigo al vector enemigo
	*	@param &e referencia al nuevo solido
	*/
	void addE(Solido* e) {
		enemigos.push_back(e);
	}

	/**
	*	Añade un cubo al vector cubos
	*	@param &e referencia al nuevo solido
	*/
	void add(Solido* e) {
		cubos.push_back(e);
	}

	/**
	*	Añade una nueva camara en primera persona
	*	@param c nueva camara
	*/
	void addC(CamaraFPS c) {
		cam = c;
	}

	/**
	*	Añade una nueva camara fija
	*	@param c nueva camara
	*/
	void addCF(Camara c) {
		cam2 = c;
	}

	/**
	*	Modifica la puntuacion
	*	@param p la nueva puntuacion
	*/
	void setPoints(int P) { points = P; }

	/**
	*	Devuelve la puntuacion
	*/
	int getPoints() { return points; }

	/**
	*	Devuelve la camara en primera persona
	*/
	CamaraFPS getCam() {
		return cam;
	}

	/**
	*	Devuelve el int que marca que camara se renderiza
	*/
	int getC() {
		return C;
	}

	/**
	*	Modifica el int que marca que camara se renderiza
	*	@param c el nuevo valor
	*/
	void setC(int c) {
		C = c;
	}


	/**
	*	Despliega el menu en consola
	*/
	void menu() {
		cout << "--------------------------------  \n";
		cout << "-  Bienvenido a LaberinDIO:    - \n";
		cout << "-  Jugar : Y                   - \n";
		cout << "-  Ranking de Puntuaciones : R - \n";
		cout << "-  Salir : X                   - \n";
		cout << "--------------------------------  \n";
	}

	/**
	*	Lee y guarda el Ranking modificado
	*/
	void readAndWrite() {
		string line;
		int r[10];
		int i = 0;
		for (int j = 0; j < 10; j++) {
			r[j] = 9999999999;
		}
		ifstream myfileR("Ranking.txt");

		if (myfileR.is_open()) {
			while (getline(myfileR, line)) {
				//cout << line << "\n";
				if (i < 10){
					if (line != "") {
						r[i] = stoi(line);
						i++;
					}
						
				}
				
			}

			myfileR.close();
			
		}
		else
			cout << "Unable to open file";

		sort(r, r + 10);

		if (this->getPoints() < r[9]) {
			r[9] = this->getPoints();
		}

		sort(r, r + 10);
		

		ofstream myfileW("Ranking.txt");
		if (myfileW.is_open()) {
			for (int i = 0; i < 10; i ++) {
					if ((r[i] % 10) == 0 || r[i] == 0) {
						myfileW << r[i];
						myfileW << "\n";
					}														
			}

			myfileW.close();
		}
		else
			cout << "Unable to openfile";
	}

	/**
	* Actualiza la posicion, velocidad y aceleracion de la camara de la escena
	* @param dt el diferencial de tiempo utilizado
	*
	*/
	void updateCam(double dt) {

		double mvto = dt;

		for (Solido* &s : paredes) {

			if (s->colisionCam(cam) == 1) {

				cam.setPos(Vector3D(0, 1.85, 5));
				points = points + 10;
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
			readAndWrite();
			menu();

		}


	}


	/**
	* Rota la camara de la escena
	* @param r angulo de rotacion
	*
	*/
	void rotCam(Vector3D r)
	{
		cam.setRot(r);
	}


};

