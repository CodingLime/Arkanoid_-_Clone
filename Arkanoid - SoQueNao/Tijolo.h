#pragma once
#include "Barra.h"
#include "Bola.h"
#include "powerup.h"
class Tijolo :
	public Rectangulo
{
public:
	bool Powerup = false;

	float larguraTijolo = (round(larguraJanela - larguraJanela*0.922));
	float alturaTijolo = (round(alturaJanela - alturaJanela*0.94));

	int nTijolosX();
	int nTijolosY();
	Tijolo(float mX = 0.f, float mY = 0.f);
	// falta destrutor
	void setPowerUp();

};