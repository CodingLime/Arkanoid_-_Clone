#include "game.h"
#include <vector>
#include <iostream>
//extern int pontuacao;

Game::Game()
{
	// On construction, we initialize the window and create
	// the brick wall. On a more serious implementation, it
	// would be a good idea to have a `newGame()` method that
	// can be called at any time to restart the Jogo.

	//window.setFramerateLimit(240); // parece n�o ser necessario para funcionar, remover no fim de tudo

	font.loadFromFile("black.ttf");

	//Texto de Score
	texto.setFont(font);
	texto.setCharacterSize(35);
	texto.setFillColor(Color::White);
	texto.setPosition(float(larguraJanela) - 185, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela
	texto.setString("SCORE:");

	//valor pontuacao
	mostraPontuacao.setFont(font);
	mostraPontuacao.setFillColor(Color::White);
	mostraPontuacao.setCharacterSize(35);
	mostraPontuacao.setPosition(float(larguraJanela) - 55, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela
	string pont = to_string(G_pontuacoes.getpontuacao());
	mostraPontuacao.setString(pont);

	//Fim do jogo
	fimdoJogo.setFont(font);
	fimdoJogo.setCharacterSize(20 * (larguraJanela * 0.001));
	fimdoJogo.setPosition(alturaJanela / 2, larguraJanela / 2);
	fimdoJogo.setFillColor(sf::Color::White);
	fimdoJogo.setString("Perdeste buahaha, carrega 'Q' para fechar");

	construir_tijolos(tijolo);
}

void Game::menu()
{
	auto timePoint1(chrono::high_resolution_clock::now());

	window.clear(Color::Black);

	Text play, bot, score, quit, titulo;
	Font font;
	font.loadFromFile("black.ttf");


	titulo.setFont(font);
	titulo.setCharacterSize(80 * (larguraJanela * 0.001));
	titulo.setFillColor(Color::White);
	titulo.setOutlineColor(Color::Yellow);
	titulo.setOutlineThickness(2);
	titulo.setPosition(larguraJanela / 5, alturaJanela / 15 + (alturaJanela * 0.01));
	titulo.setString("Arkanoid #SQN");

	play.setFont(font);
	play.setCharacterSize(80 * (larguraJanela * 0.001));
	play.setFillColor(Color::White);
	play.setPosition(larguraJanela / 10, alturaJanela / 4 + (alturaJanela * 0.01));
	//play.setPosition(larguraJanela / 2 - (larguraJanela * 0.1), alturaJanela / 4 + (alturaJanela * 0.01));
	play.setString("[P]lay");

	bot.setFont(font);
	bot.setCharacterSize(80 * (larguraJanela * 0.001));
	bot.setFillColor(Color::White);
	bot.setPosition(larguraJanela / 10, alturaJanela / 2 - (alturaJanela * 0.1));
	//bot.setPosition(larguraJanela / 2 - (larguraJanela * 0.1), alturaJanela / 2 - (alturaJanela * 0.1));

	bot.setString("[B]ot - falta");

	score.setFont(font);
	score.setCharacterSize(80 * (larguraJanela * 0.001));
	score.setFillColor(Color::White);
	score.setPosition(larguraJanela / 10, alturaJanela - (alturaJanela * 0.46));
	//score.setPosition(larguraJanela / 2 - (larguraJanela * 0.1), alturaJanela - (alturaJanela * 0.46));

	score.setString("[S]core");

	quit.setFont(font);
	quit.setCharacterSize(80 * (larguraJanela * 0.001));
	quit.setFillColor(Color::White);
	quit.setPosition(larguraJanela / 10, alturaJanela - (alturaJanela * 0.2));
	//quit.setPosition(larguraJanela / 2 - (larguraJanela * 0.1), alturaJanela - (alturaJanela * 0.2));

	quit.setString("[Q]uit");

	auto timePoint2(chrono::high_resolution_clock::now());
	auto elapsedTime(timePoint2 - timePoint1);
	FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(
		elapsedTime)
		.count() };

	lastFt = ft;

	auto ftSeconds(ft / 1000.f);
	auto fps(1.f / ftSeconds);
	window.draw(titulo);
	window.draw(play);
	window.draw(bot);
	window.draw(score);
	window.draw(quit);
	window.display();
}

void Game::classificacao()
{
	auto timePoint1(chrono::high_resolution_clock::now());

	window.clear(Color::Black);
	vector<pair<Text, int>> Stringjogadores;
	vector<pair<Text, int>> Stringpontuacao;
	vector<Int16> inputpontuacaoJogadores;
	vector<int> pontuacaoJogadores;
	vector<Text> nomeJogadores;

	for (size_t i = 0; i < nomeJogadores.size(); i++)
	{
		if (Stringjogadores.size() <= i)
		{
			pair<Text, int> novoJogador;
			Text SnovoJogador;
			SnovoJogador.setString(nomeJogadores[i].getString());
			SnovoJogador.setCharacterSize(15);
			novoJogador.first = SnovoJogador;
			novoJogador.second = inputpontuacaoJogadores[i];
			Stringjogadores.push_back(novoJogador);

	Text titulo;

			//se nao existir placeholder
			String placeholder;
			placeholder = nomeJogadores[i].getString();
			if (placeholder.getSize() == 0)
			{
				Stringjogadores[i].first.setString("AAAA AAAAA");
			}
		}
	}

	//pontuacao
	for (size_t i = 0; i < inputpontuacaoJogadores.size(); i++)
	{
		stringstream ss;
		ss << inputpontuacaoJogadores[i];
		
		pair<Text, int> novaPontuacao;
		novaPontuacao.first.setString(ss.str());
		novaPontuacao.first.setCharacterSize(15);
		novaPontuacao.second = inputpontuacaoJogadores[i];

		if (Stringpontuacao.size() <= i)
		{
			pontuacaoJogadores.push_back(inputpontuacaoJogadores[i]);
			Stringpontuacao.push_back(novaPontuacao);
		}
		else {
			pontuacaoJogadores[i] = inputpontuacaoJogadores[i];
			Stringpontuacao[i] = novaPontuacao;
		}
		
	}
	Font font;
	font.loadFromFile("black.ttf");
}


void Game::correr()
{
	// The `run()` method is used to start the game and
	// contains the game loop.

	// Instead of using `break` to stop the game, we will
	// use a boolean variable, `running`.
	
  executando = true;

	while (executando)
	{
		auto timePoint1(chrono::high_resolution_clock::now());

		window.clear(Color::Black);

		// It's not a bad idea to use methods to make the
		// code more organized. In this case, I've divided
		// the game loop in "input", "update" and "draw"
		// phases. It's one of many possible ways of tidying up
		// the code :)
		inputPhase();

		if (jogo_pausado) break;

		updatePhase();

		drawPhase();

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

void Game::construir_tijolos(Tijolo& mTijolo)
{
	for (int iX{ 0 }; iX < tijolo.nTijolosX(); ++iX)
		for (int iY{ 0 }; iY < tijolo.nTijolosY(); ++iY)
		{
			Tijolos.emplace_back( (iX + 1) * (tijolo.larguraTijolo() + 3) + 22, (iY + 2) * (tijolo.alturaTijolo() + 3) ); //mete no fim do vector
			
			// if rand = 1 pega posição, cria lá powerup
			int valorPW = rand() % 14;
			if (valorPW == 1 && tijolo.Powerup == false)
			{
				powerUP.setposition( (iX + 1) * (tijolo.larguraTijolo() + 3) + 22, (iY + 2) * (tijolo.alturaTijolo() + 3) );
				tijolo.Powerup = true;
			}
		}
}



Text Game::criartexto(int tamanholetra, int posX, int posY, char *Texto)
{
	font.loadFromFile("black.ttf");
	Text nome;
	//Texto de Score
	nome.setFont(font);
	nome.setCharacterSize(tamanholetra);
	nome.setFillColor(Color::White);
	nome.setPosition(posX, posY); // Posição do score fica consoante o tamanho da janela
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
	if (Keyboard::isKeyPressed(Keyboard::Key::O)) bola.setvelocidadebola(0.005f);
	if (Keyboard::isKeyPressed(Keyboard::Key::I)) bola.setvelocidadebola(-0.005f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) executando = false;
	if (Keyboard::isKeyPressed(Keyboard::Key::R)) restart();
}

void Game::updatePhase()
{
	currentSlice += lastFt;
	for (; currentSlice >= ftSlice; currentSlice -= ftSlice)
	{
		bola.update(ftStep);
		barra.update(ftStep);
		powerUP.update(ftStep);
		testeColisao(barra, bola);
		testeColisao(barra, powerUP);
		for (auto& Tijolo : Tijolos) testeColisao(Tijolo, bola, powerUP, G_pontuacoes);

		Tijolos.erase(remove_if(begin(Tijolos), end(Tijolos),
			[](const Tijolo& mTijolo)
		{
			return mTijolo.destruido;
		}),
			end(Tijolos));
	}
}

void Game::drawPhase()
{
	
	
	if (bola.fimjogo == true)
	{
		/*
		jogo_pausado = true;
		window.clear();
		window.draw(criartexto(20 * (larguraJanela * 0.001), alturaJanela / 2, larguraJanela / 2, "Perdeste buahaha, carrega 'R' para Reiniciar!"));*/
		fimdojogo();
	}
    //desenha Bola
	window.draw(bola.forma_bola);
	//desenha Barra
	window.draw(barra.forma_req);

	window.draw(powerUP.forma_P);
	//DESENHAR TEXTO SCORE
	window.draw(criartexto(35, float(larguraJanela) - 185, float(alturaJanela) - 50, "SCORE:"));
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
}

void Game::restart()
{
	
	for (auto& Tijolo : Tijolos) Tijolo.destruido = true;

	for (int iX{ 0 }; iX < tijolo.nTijolosX(); ++iX)
		for (int iY{ 0 }; iY < tijolo.nTijolosY(); ++iY)
			Tijolos.emplace_back((iX + 1) * (tijolo.larguraTijolo() + 3) + 22, (iY + 2) * (tijolo.alturaTijolo() + 3));
	G_pontuacoes.resetPontuacao();
	
}

void Game::topDezEcra()
{
	Text scoreTxt = criartexto(20, 120.f, 420.f, "Pontuacoes");

	stringstream ss;
	unsigned int scoreDatasize = Gravarpontuacoes.getHighscore().size();

	window.clear(Color(0x9f, 0x6d, 0x47));
	window.draw(scoreTxt);

	for (unsigned int i = 0; i < 10 && i < scoreDatasize; i++) {
		//score number
		ss.str("");
		ss << "#" << (i + 1);
		scoreTxt.setString(ss.str());
		scoreTxt.setPosition(175.f, 110.f + (30*i));
		window.draw(scoreTxt);
		//score
		ss.str("");
		ss << Gravarpontuacoes.getHighscore().at(i);
		scoreTxt.setString(ss.str());
		scoreTxt.setPosition(470.f - scoreTxt.getLocalBounds().width, 110.f + (30 * i));
		window.draw(scoreTxt);
	}
window.display();

while (window.isOpen()) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed) {
			window.close();
			
		}
	}
}

}

int Game::fimdojogo()
{
	Text gameoverTxt = criartexto(25,larguraJanela - 2 - gameoverTxt.getLocalBounds().width/2, 160.f, "YOU ARE DEAD");

	stringstream ss;

	ss << "Score: " << G_pontuacoes.getpontuacao();
	gameoverTxt.setString(ss.str());
	gameoverTxt.setPosition(larguraJanela / 2 - gameoverTxt.getLocalBounds().width / 2, 190.f);
	window.draw(gameoverTxt);

	gameoverTxt.setString("Voltar ao menu principal");
	gameoverTxt.setFillColor(Color::White);
	gameoverTxt.setPosition(larguraJanela / 2 - gameoverTxt.getLocalBounds().width / 2, 280.f);
	

	window.display();

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				Game::menu();
				return 0;
			}
		}
	}
	
	return -1;

}

