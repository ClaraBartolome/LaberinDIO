#pragma once
# include "pared.h"
class Enemigo: public Pared
{
public:
	Enemigo(double x = 0.5, double y = 3, double z = 0.5) : Pared(x, y, z) {};
	~Enemigo();

	void update(double dt);
};

