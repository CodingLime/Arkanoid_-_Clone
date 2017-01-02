#pragma once
#include "Tijolo.h"
class powerup
{
public:
	float velocidade_P{ 0.2f };
	CircleShape forma_P;
	bool destruido{ false };
	Vector2f velocidade{ 0,0 };
	void update(FrameTime mFT);
	void setposition(float mX, float mY);
	void setVelocidadeP(float x, float y);
	void randCor();
	float getScore();
	powerup(float mX, float mY);
	float const x();
	float const y();
	float const esquerda();
	float const direita();
	float const cima();
	float const baixo();
	~powerup();
};

