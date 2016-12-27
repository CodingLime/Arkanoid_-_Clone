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


Bola::Bola(float mX, float mY)
{

	forma_bola.setPosition(mX, mY);
	forma_bola.setRadius(raioBola());
	forma_bola.setFillColor(Color::Magenta);
	forma_bola.setOrigin(raioBola(), raioBola());
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
		//velocidade.y = -velocidadeBola;
		fimjogo = true;
	}
}

float const Bola::x() 
{
 return forma_bola.getPosition().x;
}

float const Bola::y()
{
	return forma_bola.getPosition().y;
}

float const Bola::esquerda()
{
	 return x() - forma_bola.getRadius();
}

float const Bola::direita()
{
	return x() + forma_bola.getRadius();
}

float  const Bola::cima()
{
	return y() - forma_bola.getRadius();
}

float const Bola::baixo()
{
	return y() + forma_bola.getRadius();
}


float const Bola::raioBola()
{
	return 20.f * (larguraJanela * 0,2.f);
}
