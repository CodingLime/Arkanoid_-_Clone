#pragma once
#include "Barra.h"
#include "Bola.h"
#include "powerup.h"
#include "Pontuacoes.h"
class Tijolo :
	public Rectangulo
{
public:
	bool Powerup = false;

	float larguraTijolo();
	float alturaTijolo();
	int nTijolosX();
	int nTijolosY();
	Tijolo(float mX, float mY);
	// falta destrutor
	void setPowerUp();

};