#include "Gestor.h"


void Gestor::addPontos(unsigned int n)
{
	pontos += n;
}

unsigned int Gestor::getPontos()
{
	return pontos;
}

void Gestor::resetPontos()
{
	pontos = 0;
}

vector<unsigned int> Gestor::getTop10()
{
	return top10;
}

void Gestor::gravarTop10()
{
	ofstream os("TOP10.txt", ios::binary | ios::out);

	if (os) {
		for (unsigned int i = 0; i < 10 && i < top10.size(); ++i)
			os.write((char*)&top10[i], sizeof(unsigned int));

		os.close();
	}
}

void Gestor::lerTop10()
{
	ifstream f("TOP10.txt", ios::binary | ios::in);

	if (f) {
		unsigned int aux;

		for (int i = 0; i < 10; ++i) {
			f.read((char*)&aux, sizeof(unsigned int));
			top10.push_back(aux);
		}

		f.close();
	}
	else {
		for (unsigned int i = 0; i < 10; ++i)
			top10.push_back(0);
	}
}

void Gestor::addTop10(unsigned int pontuacao)
{
	top10.push_back(pontuacao);
	sort(top10.begin(), top10.end(), [](unsigned int x, unsigned int y) { return x > y; });
}



Gestor::Gestor()
{
}


Gestor::~Gestor()
{
}
