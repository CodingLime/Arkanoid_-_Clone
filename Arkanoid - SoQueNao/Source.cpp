#include "Game.h"

int main()
{
	//if (Keyboard::isKeyPressed(Keyboard::Key::P))
	Game Jogo;
	Jogo.menu();
	while (true)
	{
		sleep(milliseconds(5));
		if (Keyboard::isKeyPressed(Keyboard::Key::P)) Jogo.correr();
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) Jogo.classificacao();
		if (Keyboard::isKeyPressed(Keyboard::Key::Q)) break;
	}

	//Jogo.correr();
	return 0;
}
//#include <SFML/Graphics.hpp>
//enum Cursor { FIRST, SECOND, THIRD, FOURTH };
//
//int main() {
//	sf::RenderWindow window(sf::VideoMode(600, 480), "SFML window");
//	const size_t num_options = 3;
//	sf::RectangleShape rect[num_options];
//	for (size_t n = 0; n<num_options; n++) {
//		rect[n].setPosition(20, n * 100 + 20);
//		rect[n].setSize(sf::Vector2f(560, 80));
//	}
//	Cursor cursor = FIRST;
//	while (window.isOpen()) {
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				window.close();
//			}
//
//			//////////////////////////////////////////////
//			//Here is where I handle the cursor movement//
//			else if (event.type == sf::Event::KeyPressed) {
//				int c = static_cast<int>(cursor);
//				switch (event.key.code) {
//				case sf::Keyboard::Up: {
//					c--;
//					if (c<0) { c = 0; }
//					break;
//				}
//				case sf::Keyboard::Down: {
//					c++;
//					if (c >= num_options) { c = num_options - 1; }
//					break;
//				}
//				default: {
//					break;
//				}
//				}
//				cursor = static_cast<Cursor>(c);
//			}
//		}
//		window.clear(sf::Color::White);
//		for (size_t n = 0; n<num_options; n++) {
//			rect[n].setFillColor(sf::Color::Green);
//			if (cursor == static_cast<Cursor>(n)) {
//				rect[n].setFillColor(sf::Color::Red);
//			}
//			window.draw(rect[n]);
//		}
//		window.display();
//	}
//	return 0;
//}