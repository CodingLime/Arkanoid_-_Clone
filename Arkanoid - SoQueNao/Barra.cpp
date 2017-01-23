#include "Barra.h"


Barra::Barra(float mX, float mY)
{
	forma_req.setPosition(mX, mY);
	forma_req.setSize({ larguraBarra, alturaBarra });
	forma_req.setFillColor(Color::Color(255, 137, 66));
	forma_req.setOrigin(larguraBarra / 2.f, alturaBarra / 2.f);
}

void Barra::update(FrameTime mFT)
{
	forma_req.move(velocidade * mFT);

	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && esquerda() > 0)
		velocidade.x = -velocidadeBarra;
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
		direita() < larguraJanela)
		velocidade.x = velocidadeBarra;
	else
		velocidade.x = 0;
}

void Barra::resetPosicao(float mX, float mY)
{
	forma_req.setPosition(mX, mY);
}

void Barra::alterartamanho()
{
	larguraBarra /= 2;
	forma_req.setSize({ larguraBarra, alturaBarra });
}
