#pragma once
#include <SFML\Graphics.hpp>
#include "Rectangulo.h"
using namespace sf;

using FrameTime = float;

class Bola
{
public:
	//Atribuição da Altura e Largura da Janela do Programa
	CircleShape forma_bola;
	unsigned int larguraJanela = VideoMode::getDesktopMode().width;
	unsigned int alturaJanela = VideoMode::getDesktopMode().height;
	Vector2f velocidade{ -velocidadebola(), -velocidadebola() };
	bool fimjogo(bool B_fimjogo=false);
	//posicao da bola
	Bola(float mX, float mY);
	void update(FrameTime mFT);
	float const x();
	float const y(); 
	float const esquerda();
	float const direita();
	float const cima();
	float const baixo();
	float const velocidadebola();
	float const raioBola();

};



