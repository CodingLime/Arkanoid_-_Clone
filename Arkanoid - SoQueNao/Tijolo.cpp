#include "Tijolo.h"

int pontuacao = 0;

float Tijolo::larguraTijolo()
{
	return float(round(larguraJanela - larguraJanela*0.922));
}

float Tijolo::alturaTijolo()
{
	return float (round(alturaJanela - alturaJanela*0.94));
}

int Tijolo::nTijolosX()
{
	return 11;
}

int Tijolo::nTijolosY()
{
	return 4;
}



Tijolo::Tijolo(float mX, float mY)
{
	forma_req.setPosition(mX, mY);
	forma_req.setSize({ larguraTijolo(), alturaTijolo() });
	forma_req.setFillColor(sf::Color::Black);
	forma_req.setOutlineColor(sf::Color::Magenta);
	forma_req.setOutlineThickness(2);
	forma_req.setOrigin(larguraTijolo() / 2.f, alturaTijolo() / 2.f);
}





void testeColisão(Barra & mbarra, Bola & mbola)
{
	if (!Interseção(mbarra, mbola)) return;

	mbola.velocidade.y = -mbola.velocidadebola();
	if (mbola.x() < mbarra.x())
		mbola.velocidade.x = -mbola.velocidadebola();
	else
		mbola.velocidade.x = mbola.velocidadebola();
}

void testeColisão(Tijolo & mTijolo, Bola & mbola)
{
	if (!Interseção(mTijolo, mbola)) return;
	pontuacao++;
	mTijolo.destruido = true;
	printf("%d \n", pontuacao);
	float sobreporEsquerda{ mbola.direita() - mTijolo.esquerda() };
	float sobreporDireita{ mTijolo.direita() - mbola.esquerda() };
	float sobreporCima{ mbola.baixo() - mTijolo.cima() };
	float sobreporBaixo{ mTijolo.baixo() - mbola.cima() };

	bool bolaFromesquerda(abs(sobreporEsquerda) < abs(sobreporDireita));
	bool bolaFromcima(abs(sobreporCima) < abs(sobreporBaixo));

	float minsobreporX{ bolaFromesquerda ? sobreporEsquerda : sobreporDireita };
	float minsobreporY{ bolaFromcima ? sobreporCima : sobreporBaixo };

	if (abs(minsobreporX) < abs(minsobreporY))
		mbola.velocidade.x = bolaFromesquerda ? -mbola.velocidadebola() : mbola.velocidadebola();
	else
		mbola.velocidade.y = bolaFromcima ? -mbola.velocidadebola() : mbola.velocidadebola();
}
