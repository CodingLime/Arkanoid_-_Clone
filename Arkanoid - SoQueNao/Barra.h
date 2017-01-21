#pragma once
#include "Rectangulo.h"
#include <SFML\Graphics.hpp>
using namespace sf;


class Barra :
	public Rectangulo
{
public:

	/* ### TO-DO ###
	# variáveis: passaram a ser recebidas por uma class "gestor"

	*/

	Barra(float mX, float mY);
	// falta destrutor
	void update(FrameTime mFT);
	void resetPosicao(float mX, float mY);
	void alterartamanho();
private:
	int pontuacao; //procurar onde ist é usado, pois parece que não é usado
	float larguraBarra = 100.f * (larguraJanela * 0, 03.f);
	float alturaBarra = 18.f * (alturaJanela * 0, 02.f);
	float velocidadeBarra = 1.0f * (alturaJanela * 0, 01.f);
	Vector2f velocidade;
};

