#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Gravarpontuacao
{
public:
	Gravarpontuacao();
	void Gravar();
	void addpontuacao(unsigned int pontuacao);
	void ecraGameover(RenderWindow &window, int pontuacao);
	vector<unsigned int> getHighscore();
private:
	vector<unsigned int> pontuacao;
};