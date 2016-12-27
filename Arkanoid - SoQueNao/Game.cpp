#include "game.h"

Game::Game()
{
	// On construction, we initialize the window and create
	// the brick wall. On a more serious implementation, it
	// would be a good idea to have a `newGame()` method that
	// can be called at any time to restart the Jogo.

	window.setFramerateLimit(240);

	for (int iX{ 0 }; iX < tijolo.nTijolosX(); ++iX)
		for (int iY{ 0 }; iY < tijolo.nTijolosY(); ++iY)
			Tijolos.emplace_back((iX + 1) * (tijolo.larguraTijolo() + 3) + 22, (iY + 2) * (tijolo.alturaTijolo() + 3));
}

void Game::menu()
{
	auto timePoint1(chrono::high_resolution_clock::now());

	window.clear(Color::Black);

	Text play, bot, score, quit;
	Font font;
	font.loadFromFile("black.ttf");

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

	score.setString("[S]core - falta");

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

	window.draw(play);
	window.draw(bot);
	window.draw(score);
	window.draw(quit);
	window.display();
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

	//	if (jogo_pausado) break;

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

	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) executando = false;
}

void Game::updatePhase()
{
	currentSlice += lastFt;
	for (; currentSlice >= ftSlice; currentSlice -= ftSlice)
	{
		bola.update(ftStep);
		barra.update(ftStep);

		testeColisão(barra, bola);
		for (auto& Tijolo : Tijolos) testeColisão(Tijolo, bola);
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
	
	//Texto de Score
	Text texto;
	Font font;
	font.loadFromFile("black.ttf");
	texto.setFont(font);
	texto.setCharacterSize(35);
	texto.setFillColor(Color::White);
	texto.setPosition(float(larguraJanela) - 185, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela
	texto.setString("SCORE:");
	//valor pontuacao
	Text mostraPontuacao;
	mostraPontuacao.setFont(font);
	mostraPontuacao.setFillColor(Color::White);
	mostraPontuacao.setCharacterSize(35);
	mostraPontuacao.setPosition(float(larguraJanela) - 55, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela
	string pont = to_string(tijolo.getPontuacao());
	mostraPontuacao.setString(pont);

	//Fim do jogo

	//losegame http://en.sfml-dev.org/forums/index.php?topic=19353.0

	Text fimdoJogo;
	fimdoJogo.setFont(font);
	fimdoJogo.setCharacterSize(20 * (larguraJanela * 0.001));
	fimdoJogo.setPosition(alturaJanela / 2, larguraJanela / 2);
	fimdoJogo.setFillColor(sf::Color::White);
	fimdoJogo.setString("Perdeste buahaha, carrega 'Q' para fechar");
/*	if (bola.fimjogo() == true)
	{
		jogo_pausado = true;
		window.clear();
		window.draw(fimdoJogo);
	}
	*/
	window.draw(bola.forma_bola);
	window.draw(barra.forma_req);
	window.draw(texto);
	window.draw(mostraPontuacao);
	for (auto& Tijolo : Tijolos) window.draw(Tijolo.forma_req); // fazer ciclo for "normalmente"
																//	if (fimjogo = true)
																//	window.draw(fimdojogo);
	window.display();
}
