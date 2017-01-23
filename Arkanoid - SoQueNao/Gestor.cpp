#include "Gestor.h"
#include <iostream>

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

bool Gestor::gravarxml()
{
	cout << "passei aqui gravar" << endl;
	ofstream ficheiro;
	ficheiro.open("dados/config.xml", fstream::in);
	if (!ficheiro)
	{
		cout << "Ficheiro nao encontrado! ira ser criado um novo!" << endl;
		ficheiro.open("dados/config.xml", fstream::in | fstream::trunc);
	}
	ficheiro << "<ConfigJanela>" << endl;
	ficheiro << "Largura_Janela " << larguraJanela << endl;
	ficheiro << "Altura_Janela " << alturaJanela << endl;
	ficheiro << "</ConfigJanela>" << endl;

	ficheiro << "<Barra>" << endl;
	//ficheiro << "Velocidade_Barra" << velocidade_barra < endl;
	ficheiro << "</Barra>" << endl;
	
	ficheiro << "<Bola>" << endl;
	//ficheiro << "Velocidade_Bola" << velocidade_bola << endl;
	ficheiro << "</Bola>" << endl;

	ficheiro << "<PowerUp>" << endl;
	//ficheiro << "Velocidade_powerUp" << velocidade_powerup << endl;
	ficheiro << "</PowerUp>" << endl;

	ficheiro.close();
	return true;
}

bool Gestor::carregarNivel()
{
	ifstream ficheiro;
	string linha;
	ficheiro.open("dados/nivel1.xml");

	while (getline(ficheiro, linha))
	{
		size_t vericador1 = linha.find("<");
		size_t vericador2 = linha.find(">");
		size_t vericador3 = linha.find("</");

		if (vericador1 != std::string::npos && vericador2 != std::string::npos && vericador3 != std::string::npos) {

			if (vericador1 == 0)
			{
				cout << "AQUI" << endl;
				string valor = linha.substr(vericador3 + 2, vericador2 - vericador3 - 2);
				cout << valor << endl;
				if (valor == "Ntijolos_X") {
					
				}
			}
		}
	}
	return false;
}



Gestor::Gestor()
{
}


Gestor::~Gestor()
{
}
