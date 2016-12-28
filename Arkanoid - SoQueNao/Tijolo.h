#pragma once
#include "Barra.h"
#include "Bola.h"
#include "powerup.h"
class Tijolo :
	public Rectangulo
{
public:
	bool destruido = false;
	float larguraTijolo();
	float alturaTijolo();
	int nTijolosX();
	int nTijolosY();
	Tijolo(float mX, float mY);

};
class powerup;
void testeColisao(Barra& mbarra, Bola& mbola);

void testeColisao(Tijolo& mTijolo, Bola& mbola, powerup& mpowerup);


/* IMPLEMENTAR QULQUER DIA
void testeColisao(powerup& mPower, Barra& mbarra;)*/

template<class T1, class T2>
inline bool Intersecao(T1 & mA, T2 & mB)
{
	return mA.direita() >= mB.esquerda() && mA.esquerda() <= mB.direita() &&
		mA.baixo() >= mB.cima() && mA.cima() <= mB.baixo();
}
