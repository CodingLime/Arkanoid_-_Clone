#include "Circulo.h"

Circulo::Circulo()
{
}

Circulo::~Circulo()
{
}

float Circulo::x()
{
	return forma_bola.getPosition().x;
}

float Circulo::y()
{
	return forma_bola.getPosition().y;
}

float Circulo::esquerda()
{
	return x() - forma_bola.getRadius();
}

float Circulo::direita()
{
	return x() + forma_bola.getRadius();
}

float Circulo::cima()
{
	return y() - forma_bola.getRadius();
}

float Circulo::baixo()
{
	return y() + forma_bola.getRadius();
}