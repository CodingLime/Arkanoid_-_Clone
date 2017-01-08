#pragma once
#include <SFML\Graphics.hpp>
#include "Rectangulo.h"
using namespace sf;

using FrameTime = float;

class Bola
{
public:
	float velocidadebola = 0.4f;
	//Atribuição da Altura e Largura da Janela do Programa
	CircleShape forma_bola;
	unsigned int larguraJanela = VideoMode::getDesktopMode().width;
	unsigned int alturaJanela = VideoMode::getDesktopMode().height;
	float  getvelocidadebola();
	void setvelocidadebola(float X);
	void resetVelocidade();
	Vector2f velocidade { -getvelocidadebola(), -getvelocidadebola() };
	bool fimjogo = false;
	//posicao da bola
	Bola(float mX, float mY);
	// falta destrutor
	void resetPosicao(float x, float y);
	void update(FrameTime mFT);
	float const x();
	float const y(); 
	float const esquerda();
	float const direita();
	float const cima();
	float const baixo();
	float const raioBola();
};



