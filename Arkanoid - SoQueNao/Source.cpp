#include "Game.h"

int main()
{
	//if (Keyboard::isKeyPressed(Keyboard::Key::P))
	Game Jogo;
	Jogo.menu();
	while (true)
	{
		sleep(milliseconds(5));
		if (Keyboard::isKeyPressed(Keyboard::Key::P)) Jogo.correr();;
		if (Keyboard::isKeyPressed(Keyboard::Key::Q)) break;
	}

	//Jogo.correr();
	return 0;
}