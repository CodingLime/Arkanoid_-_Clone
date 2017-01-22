#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <chrono>
#include "Gestor.h"

using namespace sf;

class Game : 
	public Gestor
{
public:
	bool jogo_pausado = false;
	//altura e largura da janela, vai buscar resolucao do monitor a ser usado
	unsigned int larguraJanela = VideoMode::getDesktopMode().width;
	unsigned int alturaJanela = VideoMode::getDesktopMode().height;
	//using FrameTime = float;
	
	//faz render da janela do jogo, define altura, largura, nome e stilo da janela
	RenderWindow window{ { larguraJanela, alturaJanela }, "Arkanoid - Mais Um Clone ?!?!?!?", Style::Fullscreen };
	//variaveis usadas por causa da libraria SFML
	FrameTime lastFt{ 0.f }, currentSlice{ 0.f };
	
	//variavel usada para controlar
	bool executando = true;

	Game();
	// falta destrutor

	void menu();
	void correr();
	void construir_tijolos();
	Text criartexto(int tamanholetra, int posX, int posY, char *Texto);
	void inputPhase();
	void updatePhase();
	bool drawPhase();
	void restart();
	void topDezEcra();

private:	
	Text fimdoJogo;
	Text mostraPontuacao;
	Text Texto;
	Font font;

	void testeColisao(Barra& mbarra, Bola& mbola);

	bool testeColisao(Tijolo& mTijolo, Bola& mbola, vector<powerup>& mpowerup);

	void testeColisao(Barra& mbarra, powerup& mpower);


	bool testeColisao(powerup & mpowerup, Barra & mbarra);
	template<class T1, class T2>
	inline bool Intersecao(T1 & mA, T2 & mB)
	{
		return mA.direita() >= mB.esquerda() && mA.esquerda() <= mB.direita() &&
			mA.baixo() >= mB.cima() && mA.cima() <= mB.baixo();
	}
};