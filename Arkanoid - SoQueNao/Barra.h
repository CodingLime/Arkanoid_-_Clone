#pragma once
#include "Rectangulo.h"
#include <SFML\Graphics.hpp>
using namespace sf;


class Barra :
	public Rectangulo
{
public:

	Barra(float mX, float mY);
	// falta destrutor
	void update(FrameTime mFT);
	void resetPosicao(float mX, float mY);
	
private:
	int pontuacao;
	float larguraBarra = 100.f * (larguraJanela * 0, 03.f);
	float alturaBarra = 18.f * (alturaJanela * 0, 02.f);
	float velocidadeBarra = 1.0f * (alturaJanela * 0, 01.f);
	Vector2f Tamanho_barra;
	Vector2f velocidade;
};

