#pragma once
#include "Barra.h"
#include "Bola.h"
class Tijolo :
	public Rectangulo
{
public:
	int pontuacao = 0;
	bool destruido = false;
	float larguraTijolo();
	float alturaTijolo();
	int nTijolosX();
	int nTijolosY();
	Tijolo(float mX, float mY);
	int getPontuacao();
	void setPontuacao();
	
};




void testeColis�o(Barra& mbarra, Bola& mbola);

void testeColis�o(Tijolo& mTijolo, Bola& mbola);

template<class T1, class T2>
inline bool Interse��o(T1 & mA, T2 & mB)
{
	return mA.direita() >= mB.esquerda() && mA.esquerda() <= mB.direita() &&
		mA.baixo() >= mB.cima() && mA.cima() <= mB.baixo();
}
