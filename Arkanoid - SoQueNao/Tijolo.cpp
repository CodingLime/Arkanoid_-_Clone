#include "Tijolo.h"
#include <iostream>



int Tijolo::nTijolosX()
{
	return 11;
}

int Tijolo::nTijolosY()
{
	return 4;
}

void Tijolo::setPowerUp()
{
	Powerup = true;
}


Tijolo::Tijolo(float mX, float mY)
{
	forma_req.setPosition(mX, mY);
	forma_req.setSize({ larguraTijolo, alturaTijolo });
	forma_req.setFillColor(sf::Color::Black);
	forma_req.setOutlineColor(Color::Color(102, 0, 204));
	forma_req.setOutlineThickness(2);
	forma_req.setOrigin(larguraTijolo / 2.f, alturaTijolo / 2.f);
}