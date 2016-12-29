#include "Pontuacoes.h"
#include <SFML\Graphics.hpp>
void Pontuacoes::adicionarpontuacao(unsigned int n)
{
	pontuacao += n;
}

unsigned int Pontuacoes::getpontuacao() const
{
	return pontuacao;
}

void Pontuacoes::resetPontuacao()
{
	pontuacao = 0;
}
