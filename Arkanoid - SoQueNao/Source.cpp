#include "Game.h"

int main()
{
	Game Jogo;
	
	while (true)
	{
		//Inicializa o programa mostrando a janela de menu
		Jogo.menu();
		sleep(milliseconds(5));
		//verica se as teclas correspondentes as opções do menu foram pressionadas
		if (Keyboard::isKeyPressed(Keyboard::Key::P)) Jogo.correr(false);
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) Jogo.Top10Ecra();
		if (Keyboard::isKeyPressed(Keyboard::Key::B)) Jogo.correr(true);
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Q)) break;
	}
	return 0;
}
