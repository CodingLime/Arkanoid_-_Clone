#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
using FrameTime = float;

/* Coisas a passar para ficheiro

raioBola
velocidadeBola

larguraBarra
alturaBarra
velocidadeBarra

larguraTijolo
alturaTijolo

nTijolosX
nTijolosY
-> passar para matriz.txt ?!?!

ftStep
ftSlice
-> verificar de novo o que estas duas são
*/

// PROCURAR
/// Ao criar uma classe, se se pode passar valores ao ser criada

// FAZER
/// Guardar em ficheiro valores padrão para bola, barra, tijolo, etc
/// Criar opção no menu para passar jogo para fullscreen
/// Fazer ecra GameOver tanto para tijolos todos destruidos ou bola bater em baixo
/// Realizar as verificações de conversão de variaveis de int para double, etc etc etcs


// Resolução da janela consoante resolução do PC do utilizador
unsigned int larguraJanela{ VideoMode::getDesktopMode().width }, alturaJanela{ VideoMode::getDesktopMode().height };

// Altera consoante resolução da janela
float raioBola{ 20.f * (alturaJanela * 0,2.f) }, velocidadeBola{ 0.4f * (alturaJanela * 0,2.f) };
const float larguraBarra{ 100.f * (larguraJanela * 0,03.f) }, alturaBarra{ 18.f * (alturaJanela * 0,02.f) }, velocidadeBarra{ 1.0f * (alturaJanela * 0,01.f) };

const float larguraTijolo{float(round(larguraJanela - larguraJanela*0.922))}, alturaTijolo{float(round(alturaJanela - alturaJanela*0.94))};
const int nTijolosX{ 11 }, nTijolosY{ 4 };
const float ftStep{ 1.f }, ftSlice{ 1.f };


bool fimjogo = false; // classe Game (?)
bool jogo_pausado = false; // classe Game (?)
int pontuacao = 0; // source.cpp mas passar valor para classe game

class Bola
{
	public:
	CircleShape forma_bola;
	Vector2f velocidade{ -velocidadeBola, -velocidadeBola };

	Bola(float mX, float mY)
	{
		forma_bola.setPosition(mX, mY);
		forma_bola.setRadius(raioBola);
		forma_bola.setFillColor(Color::Magenta);
		forma_bola.setOrigin(raioBola, raioBola);
	}

	void update(FrameTime mFT)
	{
		forma_bola.move(velocidade * mFT);

		if (esquerda() < 0)
			velocidade.x = velocidadeBola;
		else if (direita() > larguraJanela)
			velocidade.x = -velocidadeBola;

		if (cima() < 0)
			velocidade.y = velocidadeBola;
		else if (baixo() > alturaJanela)
		{
			//velocidade.y = -velocidadeBola;
			fimjogo = true;
		}
	}

	float x() const noexcept { return forma_bola.getPosition().x; }
	float y() const noexcept { return forma_bola.getPosition().y; }
	float esquerda() const noexcept { return x() - forma_bola.getRadius(); }
	float direita() const noexcept { return x() + forma_bola.getRadius(); }
	float cima() const noexcept { return y() - forma_bola.getRadius(); }
	float baixo() const noexcept { return y() + forma_bola.getRadius(); }
};

class Rectangulo
{
	public:
	RectangleShape forma_req;
	float x() const noexcept { return forma_req.getPosition().x; }
	float y() const noexcept { return forma_req.getPosition().y; }
	float esquerda() const noexcept { return x() - forma_req.getSize().x / 2.f; }
	float direita() const noexcept { return x() + forma_req.getSize().x / 2.f; }
	float cima() const noexcept { return y() - forma_req.getSize().y / 2.f; }
	float baixo() const noexcept { return y() + forma_req.getSize().y / 2.f; }
};

class Barra : public Rectangulo
{
	public:
	Vector2f velocidade;

	Barra(float mX, float mY)
	{
		forma_req.setPosition(mX, mY);
		forma_req.setSize({ larguraBarra, alturaBarra });
		forma_req.setFillColor(Color::Red);
		forma_req.setOrigin(larguraBarra / 2.f, alturaBarra / 2.f);
	}

	void update(FrameTime mFT)
	{
		forma_req.move(velocidade * mFT);

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && esquerda() > 0)
			velocidade.x = -velocidadeBarra;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
			direita() < larguraJanela)
			velocidade.x = velocidadeBarra;
		else
			velocidade.x = 0;

		if (Keyboard::isKeyPressed(Keyboard::Key::U))
			velocidadeBola += 1.0f;

		if (Keyboard::isKeyPressed(Keyboard::Key::I))
			velocidadeBola -= 1.0f;
	}
};

class Tijolo : public Rectangulo
{
	public:
	bool destruido{ false };

	Tijolo(float mX, float mY)
	{
		forma_req.setPosition(mX, mY);
		forma_req.setSize({ larguraTijolo, alturaTijolo });
		forma_req.setFillColor(sf::Color::Black);
		forma_req.setOutlineColor(sf::Color::Magenta);
		forma_req.setOutlineThickness(2);
		forma_req.setOrigin(larguraTijolo / 2.f, alturaTijolo / 2.f);
	}
};

template <class T1, class T2>
bool Interseção(T1& mA, T2& mB) noexcept
{
	return mA.direita() >= mB.esquerda() && mA.esquerda() <= mB.direita() &&
		mA.baixo() >= mB.cima() && mA.cima() <= mB.baixo();
}

void testeColisão(Barra& mbarra, Bola& mbola) noexcept
{
	if (!Interseção(mbarra, mbola)) return;

	mbola.velocidade.y = -velocidadeBola;
	if (mbola.x() < mbarra.x())
		mbola.velocidade.x = -velocidadeBola;
	else
		mbola.velocidade.x = velocidadeBola;
}

void testeColisão(Tijolo& mTijolo, Bola& mbola) noexcept
{
	if (!Interseção(mTijolo, mbola)) return;
	mTijolo.destruido = true;
	pontuacao++;
	float sobreporEsquerda{ mbola.direita() - mTijolo.esquerda() };
	float sobreporDireita{ mTijolo.direita() - mbola.esquerda() };
	float sobreporCima{ mbola.baixo() - mTijolo.cima() };
	float sobreporBaixo{ mTijolo.baixo() - mbola.cima() };

	bool bolaFromesquerda(abs(sobreporEsquerda) < abs(sobreporDireita));
	bool bolaFromcima(abs(sobreporCima) < abs(sobreporBaixo));

	float minsobreporX{ bolaFromesquerda ? sobreporEsquerda : sobreporDireita };
	float minsobreporY{ bolaFromcima ? sobreporCima : sobreporBaixo };

	if (abs(minsobreporX) < abs(minsobreporY))
		mbola.velocidade.x = bolaFromesquerda ? -velocidadeBola : velocidadeBola;
	else
		mbola.velocidade.y = bolaFromcima ? -velocidadeBola : velocidadeBola;
}

// Classe do Jogo
class Game
{
	public:
	// These members are related to the control of the game.
	RenderWindow window{ { larguraJanela, alturaJanela }, "Arkanoid - Mais Um Clone ?!?!?!?", Style::Fullscreen };
	FrameTime lastFt{ 0.f }, currentSlice{ 0.f };
	bool executando{ false };

	// These members are game entities.
	Bola bola{ float(larguraJanela) / 2, float(alturaJanela) / 2 };
	Barra barra{ float(larguraJanela) / 2, float(alturaJanela) - 50 };
	vector<Tijolo> Tijolos;



	Game()
	{
		// On construction, we initialize the window and create
		// the brick wall. On a more serious implementation, it
		// would be a good idea to have a `newGame()` method that
		// can be called at any time to restart the Jogo.

		window.setFramerateLimit(240); // verificar se é necessário, senão remover

		for (int iX{ 0 }; iX < nTijolosX; ++iX)
			for (int iY{ 0 }; iY < nTijolosY; ++iY)
				Tijolos.emplace_back((iX + 1) * (larguraTijolo + 3) + 22, (iY + 2) * (alturaTijolo + 3));
	}

	void menu()
	{
			auto timePoint1(chrono::high_resolution_clock::now());

			window.clear(Color::Black);

			Text play, bot, score, quit;
			Font font;
			font.loadFromFile("black.ttf");

			play.setFont(font);
			play.setCharacterSize(80 * (larguraJanela * 0.001));
			play.setFillColor(Color::White);
			play.setPosition(larguraJanela/10, alturaJanela/4 + (alturaJanela * 0.01));
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
			quit.setPosition(larguraJanela / 10, alturaJanela  - (alturaJanela * 0.2));
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

	void correr()
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

	void inputPhase()
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
	void updatePhase()
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

	
	void drawPhase()
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
		string pont = to_string(pontuacao);
		mostraPontuacao.setString(pont);

		//Fim do jogo
		
		//losegame http://en.sfml-dev.org/forums/index.php?topic=19353.0

		Text fimdoJogo;
		fimdoJogo.setFont(font);
		fimdoJogo.setCharacterSize(20 * (larguraJanela * 0.001));
		fimdoJogo.setPosition(alturaJanela/2,larguraJanela/2);
		fimdoJogo.setFillColor(sf::Color::White);
		fimdoJogo.setString("Perdeste buahaha, carrega 'Q' para fechar");
		if (fimjogo == true)
		{
			jogo_pausado = true;
			window.clear();
			window.draw(fimdoJogo);
		}

		window.draw(bola.forma_bola);
		window.draw(barra.forma_req);
		window.draw(texto);
		window.draw(mostraPontuacao);
		for (auto& Tijolo : Tijolos) window.draw(Tijolo.forma_req); // fazer ciclo for "normalmente"
	//	if (fimjogo = true)
		//	window.draw(fimdojogo);
		window.display();
	}
};

int main()
{	
	//if (Keyboard::isKeyPressed(Keyboard::Key::P))
	Game Jogo;
	Jogo.menu();
	while(true)
	{
		sleep(milliseconds(5));
		if (Keyboard::isKeyPressed(Keyboard::Key::P)) Jogo.correr();;
		if (Keyboard::isKeyPressed(Keyboard::Key::Q)) break;
	}
	
	//Jogo.correr();
	return 0;
}