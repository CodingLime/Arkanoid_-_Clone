#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

using FrameTime = float;
// david
// Resolução da janela (1080p ou 720p)
unsigned int windowWidth{ 1280 }, windowHeight{ 720 }; 
//unsigned int windowWidth{ 1920 }, windowHeight{ 1080 };

const float ballRadius{ 20.f }, ballVelocity{ 0.4f };
const float paddleWidth{ 85.f }, paddleHeight{ 18.f }, paddleVelocity{ 1.0f };

//const float blockWidth{ 100.f }, blockHeight{ 40.f };
const float blockWidth{float(round(windowWidth - windowWidth*0.922))}, blockHeight{float(round(windowHeight - windowHeight*0.94))};
// TESTE SYNC
const int countBlocksX{ 11 }, countBlocksY{ 4 };
const float ftStep{ 1.f }, ftSlice{ 1.f };
bool fimjogo = false;
bool game_pause = false;
int score = 0;

class Ball
{
	public:
	CircleShape shape;
	Vector2f velocity{ -ballVelocity, -ballVelocity };

	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::Magenta);
		shape.setOrigin(ballRadius, ballRadius);
	}

	void update(FrameTime mFT)
	{
		shape.move(velocity * mFT);

		if (left() < 0)
			velocity.x = ballVelocity;
		else if (right() > windowWidth)
			velocity.x = -ballVelocity;

		if (top() < 0)
			velocity.y = ballVelocity;
		else if (bottom() > windowHeight)
		{
			//velocity.y = -ballVelocity;
			fimjogo = true;
		}
	}

	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getRadius(); }
	float right() const noexcept { return x() + shape.getRadius(); }
	float top() const noexcept { return y() - shape.getRadius(); }
	float bottom() const noexcept { return y() + shape.getRadius(); }
};

class Rectangle
{
	public:
	RectangleShape shape;
	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getSize().x / 2.f; }
	float right() const noexcept { return x() + shape.getSize().x / 2.f; }
	float top() const noexcept { return y() - shape.getSize().y / 2.f; }
	float bottom() const noexcept { return y() + shape.getSize().y / 2.f; }
};

class Paddle : public Rectangle
{
	public:
	Vector2f velocity;

	Paddle(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setSize({ paddleWidth, paddleHeight });
		shape.setFillColor(Color::Red);
		shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
	}

	void update(FrameTime mFT)
	{
		shape.move(velocity * mFT);

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
			velocity.x = -paddleVelocity;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
			right() < windowWidth)
			velocity.x = paddleVelocity;
		else
			velocity.x = 0;
	}
};

class Brick : public Rectangle
{
	public:
	bool destroyed{ false };

	Brick(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setSize({ blockWidth, blockHeight });
		shape.setFillColor(sf::Color::Black);
		shape.setOutlineColor(sf::Color::Magenta);
		shape.setOutlineThickness(2);
		shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
	}
};

template <class T1, class T2>
bool isIntersecting(T1& mA, T2& mB) noexcept
{
	return mA.right() >= mB.left() && mA.left() <= mB.right() &&
		mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall) noexcept
{
	if (!isIntersecting(mPaddle, mBall)) return;

	mBall.velocity.y = -ballVelocity;
	if (mBall.x() < mPaddle.x())
		mBall.velocity.x = -ballVelocity;
	else
		mBall.velocity.x = ballVelocity;
}

void testCollision(Brick& mBrick, Ball& mBall) noexcept
{
	if (!isIntersecting(mBrick, mBall)) return;
	mBrick.destroyed = true;
	score++;
	float overlapLeft{ mBall.right() - mBrick.left() };
	float overlapRight{ mBrick.right() - mBall.left() };
	float overlapTop{ mBall.bottom() - mBrick.top() };
	float overlapBottom{ mBrick.bottom() - mBall.top() };

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
	else
		mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}

// Let's create a class for our game.
class Game
{
	public:
	// These members are related to the control of the game.
	RenderWindow window{ { windowWidth, windowHeight }, "Arkanoid - Mais Um Clone ?!?!?!?" };
	FrameTime lastFt{ 0.f }, currentSlice{ 0.f };
	bool running{ false };

	// These members are game entities.
	Ball ball{ float(windowWidth) / 2, float(windowHeight) / 2 };
	Paddle paddle{ float(windowWidth) / 2, float(windowHeight) - 50 };
	vector<Brick> bricks;



	Game()
	{
		// On construction, we initialize the window and create
		// the brick wall. On a more serious implementation, it
		// would be a good idea to have a `newGame()` method that
		// can be called at any time to restart the game.

		window.setFramerateLimit(240);

		for (int iX{ 0 }; iX < countBlocksX; ++iX)
			for (int iY{ 0 }; iY < countBlocksY; ++iY)
				bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
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
			ball.update(ftStep);
			paddle.update(ftStep);

			testCollision(paddle, ball);
			for (auto& brick : bricks) testCollision(brick, ball);
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
		texto.setPosition(float(windowWidth) - 185, float(windowHeight) - 50); // Posição do score fica consoante o tamanho da janela
		texto.setString("SCORE:");
		//valor pontuacao
		Text pontuacao;
		pontuacao.setFont(font);
		pontuacao.setFillColor(Color::White);
		pontuacao.setCharacterSize(35);
		pontuacao.setPosition(float(windowWidth) - 55, float(windowHeight) - 50); // Posição do score fica consoante o tamanho da janela
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

		window.draw(ball.shape);
		window.draw(paddle.shape);
		window.draw(texto);
		window.draw(pontuacao);
		for (auto& brick : bricks) window.draw(brick.shape); // fazer ciclo for "normalmente"
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