#include "Barra.h"
#include <iostream>
Barra::Barra(float mX, float mY) {
	forma_req.setPosition(mX, mY);
	forma_req.setSize({
		larguraBarra,
		alturaBarra
	});
	forma_req.setFillColor(Color::Color(255, 137, 66));
	forma_req.setOrigin(larguraBarra / 2.f, alturaBarra / 2.f);
}

Barra::~Barra() {}

void Barra::update(FrameTime mFT, bool bot, Bola bola) {
	forma_req.move(velocidade * mFT);

	// caso seja Jogador
	if (!bot) {
		/*Verifica tecla pressiona(esquerda) no teclado
		  e se a barra chegou ao limite esquerdo do ecra */
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && esquerda() > 0)
			velocidade.x = -velocidadeBarra;
		/*Verifica tecla pressiona(direita) no teclado
		e se a barra chegou ao limite direito do ecra */
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
			direita() < larguraJanela)
			velocidade.x = velocidadeBarra;
		else
		// nenhuma tecla pressionada
			velocidade.x = 0;
	}
	// caso seja Bot
	else {
		/* O bot vai espelhar o movimento da bola*/
		velocidadeBarra = bola.velocidadebola;
		if (bola.velocidade.x < velocidade.x && esquerda() > 0)
			velocidade.x = bola.velocidade.x;
		else if (bola.velocidade.x > velocidade.x && direita() < larguraJanela)
			velocidade.x = bola.velocidade.x;
	}
}
//Reset da posição da barra ao recomeçar um jogo
void Barra::resetPosicao(float mX, float mY) {
	forma_req.setPosition(mX, mY);
	larguraBarra = 100.f * (larguraJanela * 0,03.f);
	forma_req.setSize({ larguraBarra, alturaBarra});
}
//A barra diminuirá no tamanho ao ser intersetada pelo powerup
void Barra::alterartamanho() {
	larguraBarra /= 1.5;
	if (larguraBarra < 70.f) return;

	forma_req.setSize({ larguraBarra, alturaBarra });
}