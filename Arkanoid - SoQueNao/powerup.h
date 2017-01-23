#pragma once
#include "Tijolo.h"
#include "Circulo.h"
#include <iostream>


class powerup :
	public Circulo
{
public:
	void usarPower();
	float velocidade_P{ 0.2f };
	bool destruido{ false };
	Vector2f velocidade{ 0,0 };
	void update(FrameTime mFT);
	void setposition(float mX, float mY);
	void setVelocidadeP(float x, float y);
	void randCor();
	int getScore();
	powerup(float mX, float mY);
	~powerup();
};

