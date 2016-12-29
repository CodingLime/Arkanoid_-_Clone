#pragma once
#include <vector>
using namespace std;
class Gravarpontuacao
{
public:
	Gravarpontuacao();
	void Gravar();
	void addpontuacao(unsigned int pontuacao);
	vector<unsigned int> getHighscore();
private:
	vector<unsigned int> pontuacao;
};


