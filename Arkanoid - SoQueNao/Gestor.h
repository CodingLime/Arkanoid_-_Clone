#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf; // tem a ver com a biblioteca SFML
class Gestor
{
public:
	unsigned int larguraJanela = VideoMode::getDesktopMode().width;
	unsigned int alturaJanela = VideoMode::getDesktopMode().height;
	
	// PONTOS/SCORE
	/// parte relativa ao score/pontos durante o jogo
	unsigned int pontos;
	void addPontos(unsigned int n= 1);
	unsigned int getPontos();
	void resetPontos();

	// TOP10 + GAMEOVER 
	/// parte relativa ao ecra fim de jogo/gameover que mostra top 10 scores
	vector<unsigned int> top10;
	vector<unsigned int> getTop10();
	void gravarTop10();
	void lerTop10();
	void addTop10(unsigned int pontuacao);

	Gestor();
	~Gestor();
};