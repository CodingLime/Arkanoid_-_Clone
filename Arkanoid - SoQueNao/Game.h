#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <chrono>
#include "Bola.h"
#include "Barra.h"
#include "Tijolo.h"
#include "Pontuacoes.h"
#include "Gravarpontuacao.h"
using namespace sf;
class Game
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

	//Declaracao de entidades usadas no programa
	Bola bola{ float(larguraJanela) / 2, float(alturaJanela) / 1.2 };
	Barra barra{ float(larguraJanela) / 2, float(alturaJanela) - 50 };
	Tijolo tijolo;
	vector<Tijolo> Tijolos;
	Pontuacoes G_pontuacoes;
	Gravarpontuacao Gravarpontuacoes;
	powerup powerUP{ 0,0 };
	vector<powerup> powerups;
	float ftStep = 1.f;
	float ftSlice = 1.f;
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
	Text texto;
	Font font;

	void testeColisao(Barra& mbarra, Bola& mbola);

	bool testeColisao(Tijolo& mTijolo, Bola& mbola, vector<powerup>& mpowerup, Pontuacoes& G_pontuacao);

	void testeColisao(Barra& mbarra, powerup& mpower, Pontuacoes& mpontos);

	template<class T1, class T2>
	inline bool Intersecao(T1 & mA, T2 & mB)
	{
		return mA.direita() >= mB.esquerda() && mA.esquerda() <= mB.direita() &&
			mA.baixo() >= mB.cima() && mA.cima() <= mB.baixo();
	}
};