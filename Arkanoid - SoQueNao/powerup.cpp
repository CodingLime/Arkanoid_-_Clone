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

powerup::~powerup()
{
}
