#include "game.h"
#include <vector>
#include <iostream>
//extern int pontuacao;
Game::Game()
{
	//SCORE
	Text Score = criartexto(35, (float(larguraJanela) - 185), (float(alturaJanela) - 50), "TESTE");

	//valor pontuacao
	mostraPontuacao = criartexto(35, float(larguraJanela) - 55, float(alturaJanela) - 50, "");
	string pont = to_string(G_pontuacoes.getpontuacao());
	mostraPontuacao.setString(pont);


	//Fim do jogo
	fimdoJogo = criartexto(20 * (larguraJanela * 0.001), alturaJanela / 2, larguraJanela / 2, "Perdeste buahaha, carrega 'Q' para fechar");

	//construir tijolos
	construir_tijolos();
	gestor.gravarxml();
}

void Game::menu()
{
	auto timePoint1(chrono::high_resolution_clock::now());

	window.clear(Color::Black);

	Text play, bot, score, quit, titulo;

	//Texto Titulo Menu Iniciar
	titulo = criartexto(80 * (larguraJanela * 0.001), larguraJanela / 5, 15 + (alturaJanela * 0.01), "Arkanoid #SQN");
	titulo.setOutlineColor(Color::Yellow);
	titulo.setOutlineThickness(2);
	
	//Texto Play Menu Iniciar
	play = criartexto(80 * (larguraJanela * 0.001), larguraJanela / 10, alturaJanela / 4 + (alturaJanela * 0.01), "[P]lay");

	//Texto bot Menu Iniciar
	bot = criartexto(80 * (larguraJanela * 0.001), (larguraJanela / 10) , alturaJanela / 2 - (alturaJanela * 0.1), "[B]ot - falta");

	//Texto Score Menu Iniciar
	score = criartexto(80 * (larguraJanela * 0.001), larguraJanela / 10, alturaJanela - (alturaJanela * 0.46), "[S]core");

	//Texto Quit Menu Iniciar
	quit = criartexto(80 * (larguraJanela * 0.001), larguraJanela / 10, alturaJanela - (alturaJanela * 0.2), "[Q]uit");


	auto timePoint2(chrono::high_resolution_clock::now());
	auto elapsedTime(timePoint2 - timePoint1);
	FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(
		elapsedTime)
		.count() };

	lastFt = ft;

	auto ftSeconds(ft / 1000.f);
	auto fps(1.f / ftSeconds);

	//Desenhar caixas de texto
	window.draw(titulo);
	window.draw(play);
	window.draw(bot);
	window.draw(score);
	window.draw(quit);
	window.display();

}



void Game::correr()
{
	executando = true;

	restart();
	while (executando)
	{
		auto timePoint1(chrono::high_resolution_clock::now());

		window.clear(Color::Black);

		inputPhase();
		if (!executando) break;

		if (jogo_pausado) break;

		updatePhase();

		executando = drawPhase();

		auto timePoint2(chrono::high_resolution_clock::now());
		auto elapsedTime(timePoint2 - timePoint1);
		FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(
			elapsedTime)
			.count() };

		lastFt = ft;

		auto ftSeconds(ft / 1000.f);
		auto fps(1.f / ftSeconds);
	}
}

void Game::construir_tijolos()
{
	powerups.clear();
	Tijolos.clear();
	for (int iX{ 0 }; iX < tijolo.nTijolosX(); ++iX)
		for (int iY{ 0 }; iY < tijolo.nTijolosY(); ++iY)
		{
			Tijolos.emplace_back( (iX + 1) * (tijolo.larguraTijolo() + 3) + 22, (iY + 2) * (tijolo.alturaTijolo() + 3) ); //mete no fim do vector
			
			// if rand = 1 pega posição, cria lá powerup
			int valorPW = rand() % 14;

			if (valorPW == 1 && tijolo.Powerup == false )
			{
				powerUP.setposition( (iX + 1) * (tijolo.larguraTijolo() + 3) + 22, (iY + 2) * (tijolo.alturaTijolo() + 3) );
				powerups.emplace_back(powerUP);
				(*(--Tijolos.end())).setPowerUp();
			}
		}
}



Text Game::criartexto(int tamanholetra, int posX, int posY, char *Texto)
{
	font.loadFromFile("black.ttf");
	Text nome;
	nome.setFont(font);
	nome.setCharacterSize(tamanholetra);
	nome.setFillColor(Color::White);
	nome.setPosition(posX, posY);
	nome.setString(Texto);
	
	return nome;
}

void Game::inputPhase()
{
	Event evento;
	while (window.pollEvent(evento))
	{
		if (evento.type == Event::Closed)
		{
			window.close();
			break;
		}
	}
	// Verificador de teclas pressionadas 
	if (Keyboard::isKeyPressed(Keyboard::Key::O)) bola.setvelocidadebola(0.005f);
	if (Keyboard::isKeyPressed(Keyboard::Key::I)) bola.setvelocidadebola(-0.005f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) executando = false;
	if (Keyboard::isKeyPressed(Keyboard::Key::R)) restart();
}

void Game::updatePhase()
{
	currentSlice += lastFt;
	for (; currentSlice >= ftSlice; currentSlice -= ftSlice)
	{
		bola.update(ftStep);
		barra.update(ftStep);

		for (vector<powerup>::iterator it = powerups.begin(); it != powerups.end(); it++)
			(*it).update(ftStep);

		testeColisao(barra, bola);
		testeColisao(barra, powerUP, G_pontuacoes);
		
		for (vector<Tijolo>::iterator it = Tijolos.begin(); it != Tijolos.end();)
			if (testeColisao((*it), bola, powerups, G_pontuacoes) == true)
				it = Tijolos.erase(it);
			else
				it++;
	
		for (vector<powerup>::iterator it = powerups.begin(); it != powerups.end();)
			if (testeColisao( (*it) , barra ) == true)
				it = powerups.erase(it);
			else
				it++;
	}
}

bool Game::drawPhase()
{
	if (bola.fimjogo == true)
	{
		topDezEcra();
		bola.fimjogo = false;
		return false;
	}
    //desenha Bola
	window.draw(bola.forma_bola);
	//desenha Barra
	window.draw(barra.forma_req);
	for (vector<powerup>::iterator it = powerups.begin(); it != powerups.end(); it++)
		window.draw((*it).forma_bola);

	//DESENHAR TEXTO SCORE

	window.draw(Texto);
	//Desenhar pontuacao
	Text mostraPontuacao = criartexto(35, float(larguraJanela) - 55, float(alturaJanela) - 50, "");
	mostraPontuacao.setString(to_string(G_pontuacoes.getpontuacao()));
	window.draw(mostraPontuacao);

	//velocidade
	window.draw(criartexto(35, 5, float(alturaJanela)-50, "Velocidade:"));
	//valor velocidade
	Text mostraVel = criartexto(35, 205, float(alturaJanela)-50, "");
	mostraVel.setString(to_string(bola.getvelocidadebola()));
	window.draw(mostraVel);
	
	for (Tijolo& Tijolo : Tijolos) window.draw(Tijolo.forma_req); // fazer ciclo for "normalmente"
																  //	if (fimjogo = true)
																  //	window.draw(fimdojogo);
	/*
	for em cima é a mesma coisa que:
	for(int i=0; i< Tijolos.size(); i++) window.draw(Tijolos[i].forma_req)
	*/
	window.display();

	return true;
}

void Game::restart()
{
	
	bola.resetPosicao(float(larguraJanela) / 2, float(alturaJanela) / 1.2);
	bola.resetVelocidade();
	bola.fimjogo = false;
	barra.resetPosicao(float(larguraJanela) / 2, float(alturaJanela) - 50);
	construir_tijolos();
	G_pontuacoes.resetPontuacao();
	
}

void Game::topDezEcra()
{

	Text scoreTxt = criartexto(20, 120.f, 420.f, "");


	window.clear(Color::Black);
	/*
	for (unsigned int i = 0; i < 10 && i < scoreDatasize; i++) {
		//score number
		ss.str("");
		ss << "#" << (i + 1);
		scoreTxt.setString(ss.str());
		scoreTxt.setPosition(175.f, 110.f + (30 * i));
		window.draw(scoreTxt);
		//score
		ss.str("");
		ss << Gravarpontuacoes.getHighscore().at(i);
		scoreTxt.setString(ss.str());
		scoreTxt.setPosition(470.f - scoreTxt.getLocalBounds().width, 110.f + (30 * i));
		window.draw(scoreTxt);
	}
	*/

	//ESTA MERDA NAO FUNCIONA PORQUE APARECE SEMPRE QUE SE CARREGA NUMA TECLA O WINDOW ANTERIOR

	RenderWindow janela(VideoMode(800, 600), "", Style::None);
	while (janela.isOpen()) {
		Event event;
		string playerInput;
		while (janela.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				janela.close();
				break;

			case Event::TextEntered:
				if (event.text.unicode < 128)
				{
					playerInput = scoreTxt.getString();
					if (event.text.unicode == 13)
					{
						cout << "#1 : " << playerInput << endl;
					}
					else if (event.text.unicode == 8) {
						if (playerInput.size() > 0) playerInput.resize(playerInput.size() - 1);
					}
					else {
						playerInput += static_cast<char>(event.text.unicode);
					}
					scoreTxt.setString(playerInput);

				}
				break;
			}
			janela.display();
			janela.draw(scoreTxt);
		}
	}
}
void Game::testeColisao(Barra & mbarra, Bola & mbola)
{
	if (!Intersecao(mbarra, mbola)) return;

	mbola.velocidade.y = -mbola.getvelocidadebola();
	if (mbola.x() < mbarra.x())
		mbola.velocidade.x = -mbola.getvelocidadebola();
	else
		mbola.velocidade.x = mbola.getvelocidadebola();
}

bool Game::testeColisao(Tijolo & mTijolo, Bola & mbola, vector<powerup>& mpowerup, Pontuacoes& G_pontuacao)
{
	if (!Intersecao(mTijolo, mbola)) return false;
	G_pontuacao.adicionarpontuacao(1);
	if (mTijolo.Powerup == true)
	{
		FloatRect tBox = FloatRect(Vector2f(mTijolo.x(), mTijolo.y()), Vector2f(mTijolo.larguraTijolo(), mTijolo.alturaTijolo()));
		// precurer vector mpowerup
		for (vector<powerup>::iterator it = mpowerup.begin(); it != mpowerup.end(); it++)
			if (tBox.contains(Vector2f((*it).x(), (*it).y()))) {
				(*it).setVelocidadeP(0, 0.4f);
			}
	}
	float sobreporEsquerda{ mbola.direita() - mTijolo.esquerda() };
	float sobreporDireita{ mTijolo.direita() - mbola.esquerda() };
	float sobreporCima{ mbola.baixo() - mTijolo.cima() };
	float sobreporBaixo{ mTijolo.baixo() - mbola.cima() };

	bool bolaFromesquerda(abs(sobreporEsquerda) < abs(sobreporDireita));
	bool bolaFromcima(abs(sobreporCima) < abs(sobreporBaixo));

	float minsobreporX{ bolaFromesquerda ? sobreporEsquerda : sobreporDireita };
	float minsobreporY{ bolaFromcima ? sobreporCima : sobreporBaixo };

	if (abs(minsobreporX) < abs(minsobreporY))
		mbola.velocidade.x = bolaFromesquerda ? -mbola.getvelocidadebola() : mbola.getvelocidadebola();
	else
		mbola.velocidade.y = bolaFromcima ? -mbola.getvelocidadebola() : mbola.getvelocidadebola();

	return true;
}

void Game::testeColisao(Barra & mbarra, powerup & mPower, Pontuacoes& mpontos)
{
	if (!Intersecao(mPower, mbarra)) return;
	mpontos.adicionarpontuacao(mPower.getScore());
}

bool Game::testeColisao(powerup & mpowerup, Barra & mbarra)
{
	if (!Intersecao(mbarra, mpowerup)) return false;
	mbarra.alterartamanho();
	return true;
}
