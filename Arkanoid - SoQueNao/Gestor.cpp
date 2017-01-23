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

void Gestor::gravarTop10()
{
	
	ofstream ficheiro;
	ficheiro.open("dados/TOP10.xml", fstream::in);
	if (!ficheiro)
	{
		cout << "Ficheiro nao encontrado! ira ser criado um novo!" << endl;
		ficheiro.open("dados/TOP10.xml", fstream::in | fstream::trunc);
	}
	int i = 1;
	ficheiro << "<TOP10>" << endl;
	for (vector<jogador>::iterator it = jogadores.begin(); it != jogadores.end(); it++)
	{ 	
		ficheiro << "<#" << i << ">" << endl;
		ficheiro << "<Nome>" << (*it).nome << "</Nome>" << endl;
		ficheiro << "<Pontuacao>" << (*it).score << "</Pontuacao>" << endl;
		ficheiro << "</#" << i << ">" << endl;
		i++;
	}
	ficheiro << "</TOP10>" << endl;

	ficheiro.close();
}

void Gestor::lerTop10()
{
	ifstream ficheiro;
		ficheiro.open("dados/TOP10.xml");
		jogador jogadorexistente;
		if (!ficheiro)
		{
			cout << "ficheiro nao existe!" << endl;
		}
		else{

		string linha;
		string valor;
		while (getline(ficheiro, linha))
		{
		
			size_t vericador1 = linha.find("<");
			size_t vericador2 = linha.find(">");
			size_t vericador3 = linha.find("</");

			if (vericador1 != std::string::npos && vericador2 != std::string::npos && vericador3 != std::string::npos) {

				if (vericador3 == 0)
				{
					valor = linha.substr(vericador3 + 2, vericador2 - vericador3 - 2);
				}
				else {
					string nome = linha.substr(vericador1 + 1, vericador2 - vericador1 - 1);
				

					string valor = linha.substr(vericador2 + 1, vericador3 - vericador2 - 1);
					
					if (nome == "Nome") {
					
						jogadorexistente.setname(valor);

					}
					if (nome == "Pontuacao")
					{
						
						jogadorexistente.setscore(atoi(valor.c_str()));
						jogadores.push_back(jogadorexistente);
					}
				}
			}
			if (valor == "TOP10")
				break;
		}
		}
		
		ficheiro.close();
}

void Gestor::addTop10(jogador novo)
{
	jogadores.push_back(novo);
	sort(jogadores.begin(), jogadores.end(), [](jogador x, jogador y) { return x.score > y.score; });
}
//NAO IMPLEMENTADO NAO IMPLELETAR
bool Gestor::gravarxml()
{

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
//NAO IMPLEMENTADO!
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

void Gestor::jogador::setname(string str)
{
	nome = str;
}

void Gestor::jogador::setscore(int ponts)
{
	score = ponts;
}
