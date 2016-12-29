#include "Gravarpontuacao.h"
#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::ios;


Gravarpontuacao::Gravarpontuacao()
{
	ifstream f("pontuacao.txt", ios::binary | ios::in);

	if (f) {
		unsigned int aux;

		for (int i = 0; i < 10; ++i) {
			f.read((char*)&aux, sizeof(unsigned int));
			pontuacao.push_back(aux);
		}

		f.close();
	}
	else {
		for (unsigned int i = 0; i < 10; ++i)
			pontuacao.push_back(0);

		Gravar();
	}
}

void Gravarpontuacao::Gravar()
{
	ofstream os("pontuacao.txt", ios::binary | ios::out);

	if (os) {
		for (unsigned int i = 0; i < 10 && i < pontuacao.size(); ++i)
			os.write((char*)&pontuacao[i], sizeof(unsigned int));

		os.close();
	}
}

void Gravarpontuacao::addpontuacao(unsigned int pontos)
{
	pontuacao.push_back(pontos);

	sort(pontuacao.begin(), pontuacao.end(), [](unsigned int x, unsigned int y) { return x > y; });
}

vector<unsigned int> Gravarpontuacao::getHighscore()
{
	return pontuacao;
}

