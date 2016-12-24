#pragma once
#include "Barra.h"
#include "Bola.h"
class Tijolo :
	public Rectangulo
{
public:

	bool destruido= false;
	float larguraTijolo();
	float alturaTijolo();
	int nTijolosX();
	int nTijolosY();
	Tijolo(float mX, float mY);
	int pontuacao(int pontos = 0);

};


template <class T1, class T2>
bool Interseção(T1& mA, T2& mB);

void testeColisão(Barra& mbarra, Bola& mbola);

void testeColisão(Tijolo& mTijolo, Bola& mbola);

template<class T1, class T2>
inline bool Interseção(T1 & mA, T2 & mB);

template<class T1, class T2>
inline bool Interseção(T1 & mA, T2 & mB)
{
	return mA.direita() >= mB.esquerda() && mA.esquerda() <= mB.direita() &&
		mA.baixo() >= mB.cima() && mA.cima() <= mB.baixo();
}
