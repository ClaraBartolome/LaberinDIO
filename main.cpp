#include <iostream>
#include <fstream>
#include <string>
#include <GL/glut.h>
#include "vector3d.h"
#include "solido.h"
#include "escena.h"
#include "camara.h"
#include "pared.h"
#include "cubo.h" // SIRVE PARA EL DIBUJO WIN
#include "enemigo.h"

using namespace std;

int mx = -1;
int my = -1;
double t = 0;
double dt = 0.1;

CamaraFPS cam;

Camara camf;

Escena e;

bool jugar = false;

void write() {
	ofstream myfile("Ranking.txt");
	if (myfile.is_open()) {
		myfile << "Puntuacion: ";
		myfile << e.getPoints();
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
			cout << "Puntuacion: ";
			cout << line << "\n";
		}
		myfile.close();
	}
	else
		cout << "Unable to open file";
}

void menu() {
	cout << "--------------------------------  \n";
	cout << "-  Bienvenido a LaberinDIO:    - \n";
	cout << "-  Jugar : Y                   - \n";
	cout << "-  Ranking de Puntuaciones : R - \n";
	cout << "-  Salir : X                   - \n";
	cout << "--------------------------------  \n";
}

void displayMe(void)
{
	/* Borrar pantalla*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* Inicializar transformaciones*/
	glLoadIdentity();

	/* Camara */
	//e.getCam().render();

	/* Luces */
	GLfloat lightpos[] = { 5.0,15.0,5.0,0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	/* Visualiza escena */
	e.render();

	/* Mostrar Buffer*/
	glutSwapBuffers();
}

void mouseMoved(int x, int y)
{
	if (mx >= 0) {
		Vector3D r;
		r = e.getCam().getRot() + Vector3D(0, x - mx, 0);
		e.rotCam(r);
	}

	mx = x;
	glutPostRedisplay();
}

void mousePress(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mx = x;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		mx = -1;
	}
}

void keyPressed(unsigned char key, int px, int py) {
	Vector3D vp;
	double x;
	switch (key) {
	case '1':
		e.setC(1);
		break;
	case '2':
		e.setC(2);
		break;
	case 'w':
	case 'W':
		if (e.getCam().getPos().getX() != 1003) {
			e.updateCam(dt * 4);
		}
		break;
	case 's':
	case 'S':
		if (e.getCam().getPos().getX() != 1003) {
			e.updateCam(-dt * 4);
		}
		break;
	case 'Y':
	case 'y':
		jugar = true;
		cam.setPos(Vector3D(0, 1.85, 5));
		e.addC(cam);
		e.setPoints(0);
		cout << " ¡A jugar!";
		cout << " \n";

		
		break;
	case 'R':
	case 'r':
		if (jugar == false) {
			cout << "Ranking de Puntuaciones: \n";
			read();

			menu();
			
		}
		break;
	case 'F':
	case 'f':
		if (jugar == false) {
		cam.setPos(Vector3D(0, 1.85, 5));
		e.addC(cam);
		e.setPoints(0);
		}
		
		break;
	case 'n':
	case 'N':
		cam.setPos(Vector3D(10, 1.85, -45));
		e.addC(cam);
		break;

	case 'x':
	case 'X':
		if (jugar == false) {
			exit(0);
		}
		
		break;
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay(); //request display() call ASAP
}

double getRand(double max, double min = 0) {
	double n = max - min;
	int ir = rand() % 1000;
	return min + (double)ir / 1000 * n;
}

void init(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	cam.setPos(Vector3D(0, 1.85, 300)); // JUGADOR FUERA MAPA
	camf.setPos(Vector3D(0, 0, 80)); // MAPA
	camf.setRot(Vector3D(90, 0, 0));

	Pared *p;

	Enemigo *n;



	p = new Pared(5);
	p->setPos(Vector3D(0, 0, 7.5));
	e.addP(p);
	p = new Pared(5);
	p->setPos(Vector3D(0, 0, 7.55));
	e.addP(p);

	p = new Pared(15);
	p->setPos(Vector3D(2.5, 0, 0));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(15);
	p->setPos(Vector3D(2.55, 0, 0));
	p->setVertical(true);
	e.addP(p);

	p = new Pared(10);
	p->setPos(Vector3D(-2.5, 0, 2.5));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(10);
	p->setPos(Vector3D(-2.55, 0, 2.5));
	p->setVertical(true);
	e.addP(p);


	p = new Pared(15, 0.1, 5);
	p->setPos(Vector3D(0, 0, 0));
	p->setCol(Vector3D(1, 0, 1));
	p->setVertical(true);
	e.addP(p);


	p = new Pared(20);
	p->setPos(Vector3D(-7.5, 0, -7.5));
	e.addP(p);
	p = new Pared(20);
	p->setPos(Vector3D(-7.5, 0, -7.55));
	e.addP(p);

	p = new Pared(20);
	p->setPos(Vector3D(-12.5, 0, -2.5));
	e.addP(p);
	p = new Pared(20);
	p->setPos(Vector3D(-12.5, 0, -2.55));
	e.addP(p);


	p = new Pared(20, 0.1, 5);
	p->setPos(Vector3D(-10, 0, -5));
	p->setCol(Vector3D(1, 0, 1));
	e.addP(p);


	p = new Pared(10);
	p->setPos(Vector3D(-17.5, 0, -12.5));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(10);
	p->setPos(Vector3D(-17.45, 0, -12.5));
	p->setVertical(true);
	e.addP(p);

	p = new Pared(20);
	p->setPos(Vector3D(-22.5, 0, -12.5));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(20);
	p->setPos(Vector3D(-22.55, 0, -12.5));
	p->setVertical(true);
	e.addP(p);


	p = new Pared(20, 0.1, 5);
	p->setPos(Vector3D(-20, 0, -12.5));
	p->setCol(Vector3D(1, 0, 1));
	p->setVertical(true);
	e.addP(p);


	p = new Pared(50);
	p->setPos(Vector3D(7.5, 0, -17.5));
	e.addP(p);
	p = new Pared(50);
	p->setPos(Vector3D(7.5, 0, -17.45));
	e.addP(p);

	p = new Pared(60);
	p->setPos(Vector3D(7.5, 0, -22.5));
	e.addP(p);
	p = new Pared(60);
	p->setPos(Vector3D(7.45, 0, -22.5));
	e.addP(p);


	p = new Pared(60, 0.1, 5);
	p->setPos(Vector3D(7.5, 0, -20));
	p->setCol(Vector3D(1, 0, 1));
	e.addP(p);



	p = new Pared(40);
	p->setPos(Vector3D(32.5, 0, 2.5));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(40);
	p->setPos(Vector3D(32.45, 0, 2.5));
	p->setVertical(true);
	e.addP(p);

	p = new Pared(50);
	p->setPos(Vector3D(37.5, 0, 2.5));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(50);
	p->setPos(Vector3D(37.55, 0, 2.5));
	p->setVertical(true);
	e.addP(p);



	p = new Pared(50, 0.1, 5);
	p->setPos(Vector3D(35, 0, 2.5));
	p->setCol(Vector3D(1, 0, 1));
	p->setVertical(true);
	e.addP(p);



	p = new Pared(70);
	p->setPos(Vector3D(-2.5, 0, 22.5));
	e.addP(p);
	p = new Pared(70);
	p->setPos(Vector3D(-2.5, 0, 22.45));
	e.addP(p);

	p = new Pared(80);
	p->setPos(Vector3D(-2.5, 0, 27.5));
	e.addP(p);
	p = new Pared(80);
	p->setPos(Vector3D(-2.5, 0, 27.55));
	e.addP(p);



	p = new Pared(80, 0.1, 5);
	p->setPos(Vector3D(-2.5, 0, 25));
	p->setCol(Vector3D(1, 0, 1));
	e.addP(p);



	p = new Pared(50);
	p->setPos(Vector3D(-37.5, 0, -2.5));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(50);
	p->setPos(Vector3D(-37.45, 0, -2.5));
	p->setVertical(true);
	e.addP(p);

	p = new Pared(60);
	p->setPos(Vector3D(-42.5, 0, -2.5));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(60);
	p->setPos(Vector3D(-42.55, 0, -2.5));
	p->setVertical(true);
	e.addP(p);



	p = new Pared(60, 0.1, 5);
	p->setPos(Vector3D(-40, 0, -2.5));
	p->setCol(Vector3D(1, 0, 1));
	p->setVertical(true);
	e.addP(p);




	p = new Pared(50);
	p->setPos(Vector3D(-12.5, 0, -27.5));
	e.addP(p);
	p = new Pared(50);
	p->setPos(Vector3D(-12.5, 0, -27.45));
	e.addP(p);

	p = new Pared(50);
	p->setPos(Vector3D(-17.5, 0, -32.5));
	e.addP(p);
	p = new Pared(50);
	p->setPos(Vector3D(-17.5, 0, -32.55));
	e.addP(p);



	p = new Pared(50, 0.1, 5);
	p->setPos(Vector3D(-15, 0, -30));
	p->setCol(Vector3D(1, 0, 1));
	e.addP(p);



	p = new Pared(20);
	p->setPos(Vector3D(12.5, 0, -37.5));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(20);
	p->setPos(Vector3D(12.55, 0, -37.5));
	p->setVertical(true);
	e.addP(p);

	p = new Pared(15);
	p->setPos(Vector3D(7.5, 0, -40));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(15);
	p->setPos(Vector3D(7.45, 0, -40));
	p->setVertical(true);
	e.addP(p);



	p = new Pared(20, 0.1, 5);
	p->setPos(Vector3D(10, 0, -37.5));
	p->setCol(Vector3D(1, 0, 1));
	p->setVertical(true);
	e.addP(p);



	p = new Pared(5);
	p->setPos(Vector3D(10, 0, -47.5));
	p->setCol(Vector3D(0, 1, 0));
	e.addP(p);
	p = new Pared(5);
	p->setPos(Vector3D(10, 0, -47.55));
	p->setCol(Vector3D(0, 1, 0));
	e.addP(p);


	p = new Pared(100);
	p->setPos(Vector3D(0, 0, -50));
	e.addP(p);
	p = new Pared(100);
	p->setPos(Vector3D(0, 0, 50));
	e.addP(p);
	p = new Pared(100);
	p->setPos(Vector3D(-50, 0, 0));
	p->setVertical(true);
	e.addP(p);
	p = new Pared(100);
	p->setPos(Vector3D(50, 0, 0));
	p->setVertical(true);
	e.addP(p);



	//ENEMIGOS
	n = new Enemigo();
	n->setPos(Vector3D(-10, 0.3, -6));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0, 0, 0.5));
	n->setVertical(true);
	e.addE(n);

	n = new Enemigo();
	n->setPos(Vector3D(-20, 0.3, -13));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0.5, 0, 0));
	e.addE(n);

	n = new Enemigo();
	n->setPos(Vector3D(-6, 0.3, -20));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0, 0, 0.5));
	n->setVertical(true);
	e.addE(n);

	n = new Enemigo();
	n->setPos(Vector3D(10, 0.3, -20));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0, 0, 0.5));
	n->setVertical(true);
	e.addE(n);


	n = new Enemigo();
	n->setPos(Vector3D(35, 0.3, -10));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0.5, 0, 0));
	e.addE(n);

	n = new Enemigo();
	n->setPos(Vector3D(35, 0.3, 15));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0.5, 0, 0));
	e.addE(n);



	n = new Enemigo();
	n->setPos(Vector3D(20, 0.3, 25));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0, 0, 0.5));
	n->setVertical(true);
	e.addE(n);

	n = new Enemigo();
	n->setPos(Vector3D(0, 0.3, 25));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0, 0, 0.5));
	n->setVertical(true);
	e.addE(n);

	n = new Enemigo();
	n->setPos(Vector3D(-20, 0.3, 25));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0, 0, 0.5));
	n->setVertical(true);
	e.addE(n);



	n = new Enemigo();
	n->setPos(Vector3D(-40, 0.3, -10));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0.5, 0, 0));
	e.addE(n);

	n = new Enemigo();
	n->setPos(Vector3D(-40, 0.3, 10));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0.5, 0, 0));
	e.addE(n);



	n = new Enemigo();
	n->setPos(Vector3D(-25, 0.3, -30));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0, 0, 0.5));
	n->setVertical(true);
	e.addE(n);

	n = new Enemigo();
	n->setPos(Vector3D(-5, 0.3, -30));
	n->setCol(Vector3D(1, 0, 0));
	n->setVel(Vector3D(0, 0, 0.5));
	n->setVertical(true);
	e.addE(n);


	//Mensaje de victoria
	Cubo *c;


	c = new Cubo();
	c->setPos(Vector3D(1000, 0, 0));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1000.25, 0, 0.25));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1000.50, 0, 0.50));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1000.75, 0, 0.75));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1001, 0, 1));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1001.25, 0, 0.75));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1001.50, 0, 0.50));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1001.75, 0, 0.25));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1001.25, 0, 0.25));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1001.75, 0, 0.75));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1002, 0, 1));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1002.25, 0, 0.75));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1002.50, 0, 0.50));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1002.75, 0, 0.25));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1003, 0, 0));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);


	c = new Cubo();
	c->setPos(Vector3D(1004, 0, 0));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1004, 0, 0.25));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1004, 0, 0.50));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1004, 0, 0.75));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1004, 0, 1));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);


	c = new Cubo();
	c->setPos(Vector3D(1005, 0, 0));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1005, 0, 0.25));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1005, 0, 0.50));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1005, 0, 0.75));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1005, 0, 1));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1005.25, 0, 0.25));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1005.50, 0, 0.50));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1005.75, 0, 0.75));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1006, 0, 1));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1006, 0, 0.75));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1006, 0, 0.50));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1006, 0, 0.25));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);
	c = new Cubo();
	c->setPos(Vector3D(1006, 0, 0));
	c->setCol(Vector3D(0, 1, 0));
	e.add(c);


	e.addC(cam);
	e.addCF(camf);

}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (GLfloat)width / (GLfloat)height, 1.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
	t += dt;
	e.update(dt);

	//jugar a false en caso de que ganes para que funcione el menu
	if (e.getCam().getPos().getX() == 1003 && e.getCam().getPos().getY() == 3 && e.getCam().getPos().getZ() == 0) {
		jugar = false;
	}
	displayMe();

}

int main(int argc, char** argv) {

	srand(10);

	std::locale::global(std::locale("spanish"));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);                    // window size
	glutInitWindowPosition(300, 320);                // distance from the top-left screen
	glutCreateWindow("LABERINDIO - WRYYYYY");    // message displayed on top bar window

	menu();
	
	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(displayMe);
	glutKeyboardFunc(keyPressed);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mousePress);
	glutIdleFunc(idle);
	glutMainLoop();
	

	return 0;
}







