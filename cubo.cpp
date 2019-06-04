#include "cubo.h"
Cubo::~Cubo()
{
}
void Cubo::render() {
	glPushMatrix();
	glTranslatef(this->getPos().getX(), (*this).getPos().getY(), getPos().getZ());
	glColor3f(getCol().getX(), getCol().getY(), getCol().getZ());
	glutSolidCube(s);
	glPopMatrix();
}
