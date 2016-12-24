#include "Rectangulo.h"

float Rectangulo::x()
{
	return forma_req.getPosition().x;
}

float Rectangulo::y()
{
	return forma_req.getPosition().y;
}

float Rectangulo::esquerda()
{
	return x() - forma_req.getSize().x / 2.f;
}

float Rectangulo::direita()
{
	return x() + forma_req.getSize().x / 2.f;
}

float Rectangulo::cima()
{
	return y() - forma_req.getSize().y / 2.f;
}

float Rectangulo::baixo()
{
	return y() + forma_req.getSize().y / 2.f;
}
