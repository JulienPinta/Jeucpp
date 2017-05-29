#include "monMain.h"
#include <SFML/Graphics.hpp>
#include "Personnage.h"
#include "Element.h"
#include "noisette.h"
#include "Plateau.h"
#include "nuage.h"
#include <random>

Texture perso;
Sprite Leo;


int monMain()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	RectangleShape fond = RectangleShape(Vector2f(1920, 1080));
	fond.setFillColor(Color(119, 181, 254));


	Plateau plat;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}

		window.clear();
		window.draw(fond);
		plat.draw(window);
		plat.gestionClavier();
		plat.tourne();

		window.display();
	}

	return 0;
}