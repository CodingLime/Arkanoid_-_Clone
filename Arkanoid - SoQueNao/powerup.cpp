#include "powerup.h"


void powerup::usarPower()
{

}

void powerup::update(FrameTime mFT)
{
	forma_bola.move(velocidade * mFT);

}

void powerup::setposition(float mX, float mY)
{
	forma_bola.setPosition(mX, mY);
}

void powerup::setVelocidadeP(float x, float y)
{
	velocidade.x = x;
	velocidade.y = y;
}

void powerup::randCor()
{
	int i = rand() % 2;
	forma_bola.setFillColor((i == 0) ? Color::Yellow : Color::Green);
}

int powerup::getScore()
{
		return -5;
}

powerup::powerup(float mX, float mY)
{
	forma_bola.setPosition(mX, mY);
	forma_bola.setRadius(10.f);
	forma_bola.setFillColor(Color::Yellow);
	forma_bola.setOrigin(10.f, 10.f);
}

powerup::~powerup()
{
}
