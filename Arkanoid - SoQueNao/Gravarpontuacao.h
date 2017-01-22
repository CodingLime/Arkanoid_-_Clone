#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Gravarpontuacao
{
public:
	Gravarpontuacao();
	void Gravar(); // esta
	void addpontuacao(unsigned int pontuacao); // esta
	void ecraGameover(RenderWindow &window, int pontuacao);
	vector<unsigned int> getHighscore(); // esta
private:
	vector<unsigned int> pontuacao; // esta
};