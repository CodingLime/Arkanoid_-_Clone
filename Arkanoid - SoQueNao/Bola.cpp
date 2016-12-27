#include "bola.h"



bool Bola::fimjogo(bool Val)
{
	return Val;
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
		velocidade.x = velocidadebola();
	else if (direita() > larguraJanela)
		velocidade.x = -velocidadebola();

	if (cima() < 0)
		velocidade.y = velocidadebola();
	else if (baixo() > alturaJanela)
	{
		//velocidade.y = -velocidadeBola;
		//fimjogo(true);
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

float const Bola::velocidadebola()
{
	return 0.4f * (alturaJanela * 0, 2.f);
}

float const Bola::raioBola()
{
	return 20.f * (larguraJanela * 0, 2.f);
}
