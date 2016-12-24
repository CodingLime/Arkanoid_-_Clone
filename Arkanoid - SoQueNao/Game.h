#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Bola.h"
#include "Barra.h"
#include "Tijolo.h"
using namespace sf;

class Game
{
public:
	bool jogo_pausado = false;
	//Atribuição da Altura e Largura da Janela do Programa
	unsigned int larguraJanela = VideoMode::getDesktopMode().width;
	unsigned int alturaJanela = VideoMode::getDesktopMode().height;
	//using FrameTime = float;
	
	// These members are related to the control of the game.
	RenderWindow window{ { larguraJanela, alturaJanela }, "Arkanoid - Mais Um Clone ?!?!?!?", Style::Fullscreen };
	FrameTime lastFt{ 0.f }, currentSlice{ 0.f };
	bool executando =true;

	// These members are game entities.
	Bola bola{ float(larguraJanela) / 2, float(alturaJanela) / 2 };
	Barra barra{ float(larguraJanela) / 2, float(alturaJanela) - 50 };
	Tijolo tijolo{ 0, 0 };
	vector<Tijolo> Tijolos;
	float ftStep = 1.f;
	float ftSlice = 1.f;
	Game();

	void menu();
	void correr();
	void inputPhase();
	void updatePhase();
	void drawPhase();
};
