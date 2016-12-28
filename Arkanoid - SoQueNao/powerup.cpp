#include "powerup.h"




void powerup::update(FrameTime mFT)
{
	forma_P.move(velocidade * mFT);

}

void powerup::setposition(float mX, float mY)
{
	forma_P.setPosition(mX, mY);
}


void powerup::setVelocidadeP(float x, float y)
{
	Vector2f velocidade{ x,y };
}

powerup::powerup(float mX, float mY)
{
	forma_P.setPosition(mX, mY);
	forma_P.setRadius(10.f);
	forma_P.setFillColor(Color::Yellow);
	forma_P.setOrigin(10.f, 10.f);
}

float const powerup::x()
{
	return forma_P.getPosition().x;
}

float const powerup::y()
{
	return forma_P.getPosition().y;
}

float const powerup::esquerda()
{
	return x() - forma_P.getRadius();
}

float const powerup::direita()
{
	return x() + forma_P.getRadius();
}

float  const powerup::cima()
{
	return y() - forma_P.getRadius();
}

float const powerup::baixo()
{
	return y() + forma_P.getRadius();
}

powerup::~powerup()
{
}
