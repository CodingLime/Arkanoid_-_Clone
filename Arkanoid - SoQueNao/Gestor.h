#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include "Bola.h"
#include "Barra.h"
#include "Tijolo.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf; // tem a ver com a biblioteca SFML
class Gestor
{
public:

	struct jogador {
		string nome;
		int score;
		void setname(string str);
		void setscore(int ponts);
};

	vector<jogador>jogadores;
	

	// TAMANHO JANELA
	/// altura e largura da janela do jogo
	unsigned int larguraJanela = VideoMode::getDesktopMode().width;
	unsigned int alturaJanela = VideoMode::getDesktopMode().height;
	
	// PONTOS/SCORE
	/// parte relativa ao score/pontos durante o jogo
	unsigned int pontos = 0;
	void addPontos(unsigned int n= 1);
	unsigned int getPontos();
	void resetPontos();

	// TOP10 + LER e GRAVAR 
	/// parte relativa ao ecra fim de jogo/gameover que mostra top 10 scores
	void gravarTop10();
	void lerTop10();
	void addTop10(jogador novo);

	bool gravarxml();
	bool carregarNivel();


	/* ORIGINAL - Game.h -- APAGAR
	Bola bola{ float(larguraJanela) / 2, float(alturaJanela) / 1.2 };
	Barra barra{ float(larguraJanela) / 2, float(alturaJanela) - 50 };
	Tijolo tijolo;
	vector<Tijolo> Tijolos;
	Pontuacoes G_pontuacoes; <- removido
	Gravarpontuacao Gravarpontuacoes; <- removido
	powerup powerUP{ 0,0 };
	vector<powerup> powerups;
	float ftStep = 1.f;
	float ftSlice = 1.f;
	*/
	Bola bola{ float(larguraJanela) / 2, float(alturaJanela) / 1.2 };
	Barra barra{ float(larguraJanela) / 2, float(alturaJanela) - 50 };
	Tijolo tijolo{alturaJanela, larguraJanela};
	vector<Tijolo> tijolos;
	powerup powerUP{ 0,0 };
	vector<powerup> powerups;
	float ftStep = 1.f;
	float ftSlice = 1.f;


	Gestor();
	~Gestor();
};