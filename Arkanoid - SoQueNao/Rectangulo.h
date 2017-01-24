#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Rectangulo
{
public:

	Rectangulo();
	~Rectangulo();

	using FrameTime = float;
	//Atribuição da Altura e Largura da Janela do Programa
	unsigned int larguraJanela = VideoMode::getDesktopMode().width;
	unsigned int alturaJanela = VideoMode::getDesktopMode().height;
	RectangleShape forma_req;
	float x();
	float y();
	float esquerda(); 
	float direita(); 
	float cima(); 
	float baixo();

};