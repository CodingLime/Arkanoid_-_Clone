#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

using FrameTime = float;
// david
// Resolução da janela (1080p ou 720p)
unsigned int larguraJanela{ 1280 }, alturaJanela{ 720 }; 
//unsigned int larguraJanela{ 1920 }, alturaJanela{ 1080 };

float raioBola{ 20.f }, velocidadeBola{ 0.4f };
const float larguraBarra{ 85.f }, alturaBarra{ 18.f }, velocidadeBarra{ 1.0f };

//const float larguraJanela{ 100.f }, alturaTijolo{ 40.f };
const float larguraJanela{float(round(larguraJanela - larguraJanela*0.922))}, alturaTijolo{float(round(alturaJanela - alturaJanela*0.94))};
// TESTE SYNC
const int nTijolosX{ 11 }, nTijolosY{ 4 };
const float ftStep{ 1.f }, ftSlice{ 1.f };
bool fimjogo = false;
bool game_pause = false;
int score = 0;

class bola
{
	public:
	CircleShape forma;
	Vector2f velocidade{ -velocidadeBola, -velocidadeBola };

	bola(float mX, float mY)
	{
		forma.setPosition(mX, mY);
		forma.setRadius(raioBola);
		forma.setFillColor(Color::Magenta);
		forma.setOrigin(raioBola, raioBola);
	}

	void update(FrameTime mFT)
	{
		forma.move(velocidade * mFT);

		if (left() < 0)
			velocidade.x = velocidadeBola;
		else if (right() > larguraJanela)
			velocidade.x = -velocidadeBola;

		if (top() < 0)
			velocidade.y = velocidadeBola;
		else if (bottom() > alturaJanela)
		{
			//velocidade.y = -velocidadeBola;
			fimjogo = true;
		}
	}

	float x() const noexcept { return forma.getPosition().x; }
	float y() const noexcept { return forma.getPosition().y; }
	float left() const noexcept { return x() - forma.getRadius(); }
	float right() const noexcept { return x() + forma.getRadius(); }
	float top() const noexcept { return y() - forma.getRadius(); }
	float bottom() const noexcept { return y() + forma.getRadius(); }
};

class Rectangle
{
	public:
	RectangleShape forma;
	float x() const noexcept { return forma.getPosition().x; }
	float y() const noexcept { return forma.getPosition().y; }
	float left() const noexcept { return x() - forma.getSize().x / 2.f; }
	float right() const noexcept { return x() + forma.getSize().x / 2.f; }
	float top() const noexcept { return y() - forma.getSize().y / 2.f; }
	float bottom() const noexcept { return y() + forma.getSize().y / 2.f; }
};

class Paddle : public Rectangle
{
	public:
	Vector2f velocidade;

	Paddle(float mX, float mY)
	{
		forma.setPosition(mX, mY);
		forma.setSize({ larguraBarra, alturaBarra });
		forma.setFillColor(Color::Red);
		forma.setOrigin(larguraBarra / 2.f, alturaBarra / 2.f);
	}

	void update(FrameTime mFT)
	{
		forma.move(velocidade * mFT);

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
			velocidade.x = -velocidadeBarra;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
			right() < larguraJanela)
			velocidade.x = velocidadeBarra;
		else
			velocidade.x = 0;

		if (Keyboard::isKeyPressed(Keyboard::Key::U))
			velocidadeBola += 1.0f;

		if (Keyboard::isKeyPressed(Keyboard::Key::I))
			velocidadeBola -= 1.0f;
	}
};

class Brick : public Rectangle
{
	public:
	bool destroyed{ false };

	Brick(float mX, float mY)
	{
		forma.setPosition(mX, mY);
		forma.setSize({ larguraJanela, alturaTijolo });
		forma.setFillColor(sf::Color::Black);
		forma.setOutlineColor(sf::Color::Magenta);
		forma.setOutlineThickness(2);
		forma.setOrigin(larguraJanela / 2.f, alturaTijolo / 2.f);
	}
};

template <class T1, class T2>
bool isIntersecting(T1& mA, T2& mB) noexcept
{
	return mA.right() >= mB.left() && mA.left() <= mB.right() &&
		mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, bola& mbola) noexcept
{
	if (!isIntersecting(mPaddle, mbola)) return;

	mbola.velocidade.y = -velocidadeBola;
	if (mbola.x() < mPaddle.x())
		mbola.velocidade.x = -velocidadeBola;
	else
		mbola.velocidade.x = velocidadeBola;
}

void testCollision(Brick& mBrick, bola& mbola) noexcept
{
	if (!isIntersecting(mBrick, mbola)) return;
	mBrick.destroyed = true;
	score++;
	float overlapLeft{ mbola.right() - mBrick.left() };
	float overlapRight{ mBrick.right() - mbola.left() };
	float overlapTop{ mbola.bottom() - mBrick.top() };
	float overlapBottom{ mBrick.bottom() - mbola.top() };

	bool bolaFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool bolaFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX{ bolaFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ bolaFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		mbola.velocidade.x = bolaFromLeft ? -velocidadeBola : velocidadeBola;
	else
		mbola.velocidade.y = bolaFromTop ? -velocidadeBola : velocidadeBola;
}

// Let's create a class for our game.
class Game
{
	public:
	// These members are related to the control of the game.
	RenderWindow window{ { larguraJanela, alturaJanela }, "Arkanoid - Mais Um Clone ?!?!?!?" };
	FrameTime lastFt{ 0.f }, currentSlice{ 0.f };
	bool running{ false };

	// These members are game entities.
	bola bola{ float(larguraJanela) / 2, float(alturaJanela) / 2 };
	Paddle paddle{ float(larguraJanela) / 2, float(alturaJanela) - 50 };
	vector<Brick> bricks;



	Game()
	{
		// On construction, we initialize the window and create
		// the brick wall. On a more serious implementation, it
		// would be a good idea to have a `newGame()` method that
		// can be called at any time to restart the game.

		window.setFramerateLimit(240);

		for (int iX{ 0 }; iX < nTijolosX; ++iX)
			for (int iY{ 0 }; iY < nTijolosY; ++iY)
				bricks.emplace_back((iX + 1) * (larguraJanela + 3) + 22, (iY + 2) * (alturaTijolo + 3));
	}

	void run()
	{
		// The `run()` method is used to start the game and
		// contains the game loop.

		// Instead of using `break` to stop the game, we will
		// use a boolean variable, `running`.
		running = true;

		while (running)
		{
			

			auto timePoint1(chrono::high_resolution_clock::now());

			window.clear(Color::Black);

			// It's not a bad idea to use methods to make the
			// code more organized. In this case, I've divided
			// the game loop in "input", "update" and "draw"
			// phases. It's one of many possible ways of tidying up
			// the code :)
			inputPhase();

			if(!game_pause)
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

			//window.setTitle("Arkanoid POO");
		}
	}

	void inputPhase()
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) running = false;
		/*if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace)) game_pause = true;
		{while (game_pause == true)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::P))
				game_pause = false;
		}
		}*/
	}
	void updatePhase()
	{
		currentSlice += lastFt;
		for (; currentSlice >= ftSlice; currentSlice -= ftSlice)
		{
			bola.update(ftStep);
			paddle.update(ftStep);

			testCollision(paddle, bola);
			for (auto& brick : bricks) testCollision(brick, bola);
			bricks.erase(remove_if(begin(bricks), end(bricks),
				[](const Brick& mBrick)
			{
				return mBrick.destroyed;
			}),
				end(bricks));
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
		Text pontuacao;
		pontuacao.setFont(font);
		pontuacao.setFillColor(Color::White);
		pontuacao.setCharacterSize(35);
		pontuacao.setPosition(float(larguraJanela) - 55, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela
		string pont = to_string(score);
		pontuacao.setString(pont);

		//Fim do jogo
		
		//losegame http://en.sfml-dev.org/forums/index.php?topic=19353.0

		Text fimdoJogo;
		fimdoJogo.setFont(font);
		fimdoJogo.setCharacterSize(30);
		fimdoJogo.setPosition(300,500);
		fimdoJogo.setFillColor(sf::Color::White);
		fimdoJogo.setString("Perdeste buahaha, carrega 'Espaco' para fechar");
		if (fimjogo == true)
		{
			game_pause = true;
			window.clear();
			window.draw(fimdoJogo);
	}

		window.draw(bola.forma);
		window.draw(paddle.forma);
		window.draw(texto);
		window.draw(pontuacao);
		for (auto& brick : bricks) window.draw(brick.forma); // fazer ciclo for "normalmente"
	//	if (fimjogo = true)
		//	window.draw(fimdojogo);
		window.display();
	}
};

int main()
{	
	//if (Keyboard::isKeyPressed(Keyboard::Key::P))
		Game{}.run();
	return 0;
}