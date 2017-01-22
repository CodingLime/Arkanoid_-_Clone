#pragma once
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class Circulo
{
public:

	Circulo();
	~Circulo();

	unsigned int larguraJanela = VideoMode::getDesktopMode().width;
	unsigned int alturaJanela = VideoMode::getDesktopMode().height;
	CircleShape forma_bola;
	float x();
	float y();
	float esquerda();
	float direita();
	float cima();
	float baixo();
};

