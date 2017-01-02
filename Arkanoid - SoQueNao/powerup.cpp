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
	velocidade.x = x;
	velocidade.y = y;

}

void powerup::randCor()
{
	int i = rand() % 2;
	forma_P.setFillColor((i == 0) ? Color::Yellow : Color::Green);
}

float powerup::getScore()
{
	if (forma_P.getFillColor() == Color::Yellow)
		return -5.f;
	else 
		return 10.0f;
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
