#include "game.h"
#include <vector>
#include <iostream>

Game::Game()
{
	//Carrega o TOP10 para a memoria
	Gestor::lerTop10();
}

Game::~Game()
{
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
	bot = criartexto(80 * (larguraJanela * 0.001), (larguraJanela / 10) , alturaJanela / 2 - (alturaJanela * 0.1), "[B]ot");

	//Texto Score Menu Iniciar
	score = criartexto(80 * (larguraJanela * 0.001), larguraJanela / 10, alturaJanela - (alturaJanela * 0.46), "[S]core");

	//Texto Quit Menu Iniciar
	quit = criartexto(80 * (larguraJanela * 0.001), larguraJanela / 10, alturaJanela - (alturaJanela * 0.2), "[Q]uit");

	auto timePoint2(chrono::high_resolution_clock::now());
	auto elapsedTime(timePoint2 - timePoint1);
	FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(elapsedTime).count() };
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



void Game::correr(bool bot)
{
	construir_tijolos();
	executando = true;

	//Varias são repostas no valor padrão
	restart();

	while (executando)
	{
		auto timePoint1(chrono::high_resolution_clock::now());

		window.clear(Color::Black);

		inputPhase();
		if (!executando) break;

		if (jogo_pausado) break;

		updatePhase(bot);

		executando = drawPhase();

		auto timePoint2(chrono::high_resolution_clock::now());
		auto elapsedTime(timePoint2 - timePoint1);
		FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(elapsedTime).count() };
		lastFt = ft;
		auto ftSeconds(ft / 1000.f);
		auto fps(1.f / ftSeconds);
	}
}

void Game::construir_tijolos()
{
	powerups.clear();
	tijolos.clear();
	for (int iX{ 0 }; iX < tijolo.nTijolosX(); ++iX)
		for (int iY{ 0 }; iY < tijolo.nTijolosY(); ++iY)
		{
			tijolos.emplace_back((iX + 1) * (tijolo.larguraTijolo + 3) + 22, (iY + 2) * (tijolo.alturaTijolo + 3) ); 

			// if rand = 1 pega posição, cria lá o powerup
			int valorPW = rand() % 14;
			if (valorPW == 1 && tijolo.Powerup == false )
			{
				powerUP.setposition( (iX + 1) * (tijolo.larguraTijolo + 3) + 22, (iY + 2) * (tijolo.alturaTijolo + 3) );
				powerups.emplace_back(powerUP);
				(*(--tijolos.end())).setPowerUp();
			}
		}
}


/* Metodo para criar automaticamente caixas de texto
   tamanholetra : Tamanho da fonte
   posX			: Posicao Horizontal
   posY			: Posicao Vertical
   Texto		: Conteudo da caixa de texto 
   retorna uma variavel do tipo Text */
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
	// Verifica teclas pressionadas 
	if (Keyboard::isKeyPressed(Keyboard::Key::O)) bola.setvelocidadebola(0.005f);
	if (Keyboard::isKeyPressed(Keyboard::Key::I)) bola.setvelocidadebola(-0.005f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) executando = false;
	if (Keyboard::isKeyPressed(Keyboard::Key::R)) restart();
}

void Game::updatePhase(bool bot)
{
	currentSlice += lastFt;
	for (; currentSlice >= ftSlice; currentSlice -= ftSlice)
	{
		//Atualização da posição da bola
		bola.update(ftStep);
		//Atualização da posição da Barra
		barra.update(ftStep,bot, bola);
		
		//Atualiza todos os powerups
		for (vector<powerup>::iterator it = powerups.begin(); it != powerups.end(); it++)
			(*it).update(ftStep);

		//Verificação se existe colisao entre a barra do jogador e a bola
		testeColisao(barra, bola);

		/*Verifica se existe colisão entre a bola e todos os tijolos
		  Se existir powerup no tijolo destruido, o powerup passa a ativo */
		for (vector<Tijolo>::iterator it = tijolos.begin(); it != tijolos.end();)
			if (testeColisao((*it), bola, powerups) == true)
				it = tijolos.erase(it);
			else
				it++;

		/*Verifica se existe colisão entre o powerup e a barra do jogador
		  Ao existir colisão o powerup desaparece */
		for (vector<powerup>::iterator it = powerups.begin(); it != powerups.end();)
			if (testeColisao( (*it) , barra ) == true)
				it = powerups.erase(it);
			else
				it++;
	}
}

bool Game::drawPhase()
{
	//Se o utilizador destruir todos os Tijolos acaba o jogo
	if (bola.fimjogo == true || totaltijolos == 44)
	{
		InserirnomeEcra();
		bola.fimjogo = false;
		return false;
	}
    //desenha Bola
	window.draw(bola.forma_bola);
	//desenha Barra
	window.draw(barra.forma_req);
	for (vector<powerup>::iterator it = powerups.begin(); it != powerups.end(); it++)
		window.draw((*it).forma_bola);

	//Desenha Texto Score
	Text txtpontuacao = criartexto(35, float(larguraJanela) - 185, float(alturaJanela) - 50, "SCORE:");
	window.draw(txtpontuacao);

	//Desenhar pontuacao atual do jogador
	Text mostraPontuacao = criartexto(35, float(larguraJanela) - 55, float(alturaJanela) - 50, "");
	mostraPontuacao.setString(to_string(getPontos()));
	window.draw(mostraPontuacao);

	//Desenha texto velocidade da bola
	window.draw(criartexto(35, 5, float(alturaJanela)-50, "Velocidade:"));
	//Desenha o valor da velocidade da bola
	Text mostraVel = criartexto(35, 205, float(alturaJanela)-50, "");
	mostraVel.setString(to_string(bola.getvelocidadebola()));
	window.draw(mostraVel);
	
	//Desenha todos os Tijolos
	for (Tijolo& Tijolo : tijolos) window.draw(Tijolo.forma_req); 
	
	window.display();
	return true;
}


/*  Metodo para Reniciar todas as variaveis
	A posição da bola, barra e tijolos são restauradas para as definicoes de inicio do jogo */
void Game::restart()
{
	bola.resetPosicao(float(larguraJanela) / 2, float(alturaJanela) / 1.2);
	bola.resetVelocidade();
	bola.fimjogo = false;
	barra.resetPosicao(float(larguraJanela) / 2, float(alturaJanela) - 50);
	construir_tijolos();
	resetPontos();
}

void Game::InserirnomeEcra()
{
	//Texto Gameover
	Text txtGameover = criartexto(50, larguraJanela / 2.7, 15 + (alturaJanela * 0.05), "__Game Over__ ");
	txtGameover.setOutlineColor(Color::Yellow);
	txtGameover.setOutlineThickness(2);
	//Texto Pontuacao
	Text Pontuacao = criartexto(20, larguraJanela / 2.7, 15 + (alturaJanela * 0.25), "Pontuacao: ");
	//Texto score
	Text score = criartexto(20, larguraJanela / 2.25, 15 + (alturaJanela * 0.25), "");
	score.setString(to_string(getPontos()));
	//Texto Nome
	Text txtNome = criartexto(25, larguraJanela / 2.7, 15 + (alturaJanela * 0.50), "Insira o seu nome! : ");
	//Texto NomeJogador
	Text nomejogador = criartexto(20, larguraJanela / 2.7, 15 + (alturaJanela * 0.55), "");
	stringstream ss;
	
	//Desenha uma nova janela para apresentar a identificação do jogador
	RenderWindow janela(VideoMode(larguraJanela, alturaJanela), "", Style::None);
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
					playerInput = nomejogador.getString();
					if (event.text.unicode == 13) //(13 - Tecla Enter
					{
						jogador fimjogo;
						fimjogo.setname(playerInput);
						fimjogo.setscore(getPontos());
						addTop10(fimjogo);
						gravarTop10();
						janela.close();
					}
					else if (event.text.unicode == 8) //(8) - Tecla Backspace 
					{
						//Ao pressionar a tecla backspace vai ser apagado o ultimo caracter introduzido
						if (playerInput.size() > 0) playerInput.resize(playerInput.size() - 1);
						janela.clear();
					}
					else {
						//Adiciona a string todos os caracters pressionados
						playerInput += static_cast<char>(event.text.unicode);
					}
					nomejogador.setString(playerInput);
				}
				break;
			}
			//Desenhar Elementos no ecrã
			janela.display();
			janela.draw(txtGameover);
			janela.draw(Pontuacao);
			janela.draw(score);
			janela.draw(txtNome);
			janela.draw(nomejogador);
		}
	}
}

void Game::Top10Ecra()
{
	//Criação de uma nova janela para apresentar TOP10
	RenderWindow janela(VideoMode(larguraJanela, alturaJanela), "", Style::None);
	while (janela.isOpen()) {
		stringstream ss;
		//Texto Titulo TOP10
		Text txtTop10 = criartexto(80, larguraJanela / 2.4, 15 + (alturaJanela * 0.05), " # TOP 10 ");
		txtTop10.setOutlineColor(Color::Yellow);
		txtTop10.setOutlineThickness(2);
		//Texto Melhores Jogadores
		Text txtNome = criartexto(50, larguraJanela / 2.7, 15 + (alturaJanela * 0.25), "Melhores Jogadores : ");
		//Texto Jogador
		Text scoreTxt = criartexto(35, larguraJanela / 2.8, 15 + (alturaJanela * 0.40), "");
		int i = 1;

		//Metodo pecorre os 10 primeiros jogadores da lista de jogadores disponiveis
		for (vector<jogador>::iterator it = jogadores.begin(); it != jogadores.end() && i <= 10; it++, i++)
		{
			ss << "  #"<<i << "  "<< (*it).nome << "          "<< "Pontuacao: " << (*it).score << endl;
			scoreTxt.setString(ss.str());
		}
		Event event;
		string playerInput;
		while (janela.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Q))
			{
				janela.close();
			}

			//Desenha todas os elementos na janela
			janela.display();
			janela.draw(txtTop10);
			janela.draw(txtNome);
			janela.draw(scoreTxt);
		}
	}
}

/* Teste Colisao entre a barra e a bola
 Se existir interseção entre os 2 elementos, 
 a bola muda de direção consoante se acertar no lado esquerdo
 ou direito da barra */
void Game::testeColisao(Barra & mbarra, Bola & mbola)
{
	if (!Intersecao(mbarra, mbola)) return;

	mbola.velocidade.y = -mbola.getvelocidadebola();
	if (mbola.x() < mbarra.x())
		mbola.velocidade.x = -mbola.getvelocidadebola();
	else
		mbola.velocidade.x = mbola.getvelocidadebola();
}

/* Teste Colisao entre a barra e a bola e o powerup
A bola ao intersetar o tijolo ele será eliminado, e incrementado 1 ponto 
na pontuação do jogador e incrementa-se o numero de tijolos destruidos pelo
jogador.
Se o tijolo desruido contiver um powerup, esse será libertado 
e entrará num estado de movimento caindo do tijolo*/
bool Game::testeColisao(Tijolo & mTijolo, Bola & mbola, vector<powerup>& mpowerup)
{
	if (!Intersecao(mTijolo, mbola)) return false;
	addPontos(1);
	totaltijolos++;
	if (mTijolo.Powerup == true)
	{
		FloatRect tBox = FloatRect(Vector2f(mTijolo.x(), mTijolo.y()), Vector2f(mTijolo.larguraTijolo, mTijolo.alturaTijolo));
		for (vector<powerup>::iterator it = mpowerup.begin(); it != mpowerup.end(); it++)
			if (tBox.contains(Vector2f((*it).x(), (*it).y()))) {
				(*it).setVelocidadeP(0, 0.4f);
			}
	}
	/* Se a bola se sobrepor a Esquerda/direita/cima/baixo do tijolo é trocada a direção da bola*/
	float sobreporEsquerda{ mbola.direita() - mTijolo.esquerda() };
	float sobreporDireita{ mTijolo.direita() - mbola.esquerda() };
	float sobreporCima{ mbola.baixo() - mTijolo.cima() };
	float sobreporBaixo{ mTijolo.baixo() - mbola.cima() };

	bool bolaVemdaesquerda(abs(sobreporEsquerda) < abs(sobreporDireita));
	bool bolaVemdeCima(abs(sobreporCima) < abs(sobreporBaixo));

	float minsobreporX{ bolaVemdaesquerda ? sobreporEsquerda : sobreporDireita };
	float minsobreporY{ bolaVemdeCima ? sobreporCima : sobreporBaixo };

	if (abs(minsobreporX) < abs(minsobreporY))
		mbola.velocidade.x = bolaVemdaesquerda ? -mbola.getvelocidadebola() : mbola.getvelocidadebola();
	else
		mbola.velocidade.y = bolaVemdeCima ? -mbola.getvelocidadebola() : mbola.getvelocidadebola();

	return true;
}

/*Teste de colisao do powerup com a barra do jogador
	Ao existir colisão a barra diminui de tamanho
	e o jogador perde pontos.
*/
bool Game::testeColisao(powerup & mpowerup, Barra & mbarra)
{
	if (!Intersecao(mbarra, mpowerup)) return false;
	mbarra.alterartamanho();
	addPontos(mpowerup.getScore());
	return true;
}
