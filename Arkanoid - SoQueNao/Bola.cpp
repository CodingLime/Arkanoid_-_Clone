#include "bola.h"



float Bola::getvelocidadebola()
{
	return velocidadebola;
}

void Bola::setvelocidadebola(float X)
{
	if ((X < 0) && (velocidadebola - X <= 0.16f)) return;
	else	
		velocidadebola += X;
}

void Bola::resetVelocidade()
{
	velocidadebola = 0.4f;
	velocidade.x = -getvelocidadebola();
	velocidade.y = -getvelocidadebola();
}


Bola::Bola(float mX, float mY)
{

	forma_bola.setPosition(mX, mY);
	forma_bola.setRadius(raioBola());
	forma_bola.setFillColor(Color::Color(255,204, 0));
	forma_bola.setOrigin(raioBola(), raioBola());
}

void Bola::resetPosicao(float x, float y)
{
	forma_bola.setPosition(x, y);
}

void Bola::update(FrameTime mFT)
{
	
	forma_bola.move(velocidade * mFT);
	
	if (esquerda() < 0)
		velocidade.x = getvelocidadebola();
	else if (direita() > larguraJanela)
		velocidade.x = -getvelocidadebola();

	if (cima() < 0)
		velocidade.y = getvelocidadebola();
	else if (baixo() > alturaJanela)
	{
		fimjogo = true;
	}
}

float const Bola::raioBola()
{
	return 20.f * 2.f;
}
