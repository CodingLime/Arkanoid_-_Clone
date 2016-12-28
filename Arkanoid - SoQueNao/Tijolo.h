#pragma once
#include "Barra.h"
#include "Bola.h"
#include "powerup.h"
class Tijolo :
	public Rectangulo
{
public:
	bool destruido = false;
	bool Powerup = false;
	float larguraTijolo();
	float alturaTijolo();
	int nTijolosX();
	int nTijolosY();
	Tijolo(float mX, float mY);

};
class powerup; //why the f this
void testeColisao(Barra& mbarra, Bola& mbola);

void testeColisao(Tijolo& mTijolo, Bola& mbola, powerup& mpowerup);

void testeColisao(Barra& mbarra, powerup& mpower);

template<class T1, class T2>
inline bool Intersecao(T1 & mA, T2 & mB)
{
	return mA.direita() >= mB.esquerda() && mA.esquerda() <= mB.direita() &&
		mA.baixo() >= mB.cima() && mA.cima() <= mB.baixo();
}
