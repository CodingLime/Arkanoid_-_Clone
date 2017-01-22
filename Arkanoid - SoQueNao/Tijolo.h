#pragma once
#include "Barra.h"
#include "Bola.h"
#include "Powerup.h"
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
	Tijolo(float mX = 0.f, float mY = 0.f);
	// falta destrutor
	void setPowerUp();

};