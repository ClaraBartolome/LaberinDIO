#pragma once
# include "pared.h"

/*
* Clase enemigo que hereda de Pared.
*
*/
class Enemigo: public Pared
{
public:
	/**
	*	Constructor de la clase Enemigo a partir del constructor de Pared
	*	@param x primera coordenada del enemigo
	*	@param y segunda coordenada del enemigo
	*	@param z tercera coordenada del enemigo
	*/
	Enemigo(double x = 0.5, double y = 3, double z = 0.5) : Pared(x, y, z) {};

	/**Destructor de la clase Enemigo*/
	~Enemigo();

	/**
	*	Actualiza la posicion, velocidad y aceleracion del enemigo
	*	@param dt el diferencial de tiempo utilizado
	*/
	void update(double dt);
};

