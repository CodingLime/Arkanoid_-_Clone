#include "Barra.h"


Barra::Barra(float mX, float mY)
{
	forma_req.setPosition(mX, mY);
	forma_req.setSize({ larguraBarra, alturaBarra });
	forma_req.setFillColor(Color::Color(255, 137, 66));
	forma_req.setOrigin(larguraBarra / 2.f, alturaBarra / 2.f);
}

void Barra::update(FrameTime mFT, bool bot, Bola bola)
{
	forma_req.move(velocidade * mFT);
	if(!bot)
	{ 
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && esquerda() > 0)
		velocidade.x = -velocidadeBarra;
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
		direita() < larguraJanela)
		velocidade.x = velocidadeBarra;
	else
		velocidade.x = 0;
	}

	else 
	{
		velocidadeBarra = bola.velocidadebola;
		if (bola.velocidade.x < velocidade.x && esquerda() > 0)
			velocidade.x = bola.velocidade.x;
		else if (bola.velocidade.x > velocidade.x && direita() < larguraJanela)
			velocidade.x = bola.velocidade.x;
	}
}

void Barra::resetPosicao(float mX, float mY)
{
	forma_req.setPosition(mX, mY);
	larguraBarra = 100.f * (larguraJanela * 0, 03.f);
	forma_req.setSize({ larguraBarra, alturaBarra });
}

void Barra::alterartamanho()
{
	larguraBarra /= 2;
	forma_req.setSize({ larguraBarra, alturaBarra });
}
