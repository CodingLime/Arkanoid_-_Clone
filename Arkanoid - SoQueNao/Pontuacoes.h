#pragma once
class Pontuacoes
{
public:
	void adicionarpontuacao(unsigned int n = 1);
	unsigned int getpontuacao() const;
	void resetPontuacao();
private:
	unsigned int pontuacao;
};
