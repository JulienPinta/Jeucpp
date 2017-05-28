#include <SFML/Graphics.hpp>
#include "Personnage.h"
#include "Element.h"
#include "noisette.h"
#include "Plateau.h"
#include "nuage.h"

Texture perso;
Sprite Leo;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
	//auto Leo = new Personnage();
	auto noiset = make_unique<noisette>(30, 30);
	auto noiset2 = make_unique<noisette>(30, 220);
	auto nuag = make_unique<nuage>(30, 400);
	Plateau plat;
	plat.add(noiset->copy());
	plat.add(noiset2->copy());
	plat.add(nuag->copy());
	/*perso.setSmooth(true);
	Leo.setTexture(perso);*/
	cout << "hello world" << endl;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		plat.draw(window);
		plat.translate(1);
		window.display();
	}

	return 0;
}