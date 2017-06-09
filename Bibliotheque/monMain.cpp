#include "monMain.h"
#include <SFML/Graphics.hpp>
#include "Element.h"
#include "noisette.h"
#include "Plateau.h"
#include "nuage.h"
#include "SampleNetworkLogic.h"
#include <random>
#include <Common-cpp\inc\Common.h>
#include <LoadBalancing-cpp\inc\Client.h>
#include <LoadBalancing-cpp\inc\Listener.h>


int monMain()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	RectangleShape fond = RectangleShape(Vector2f(1920, 1080));
	fond.setFillColor(Color(119, 181, 254));
	
	static const ExitGames::Common::JString appID = L"2a1a1b5b-7a32-4a96-8f2b-2a5b6454062c"; // set your app id here
	static const ExitGames::Common::JString appVersion = L"1.0";

	SampleNetworkLogic networkLogic(appID, appVersion);

	networkLogic.createRoom("leo", 2);

	//networkLogic.connect();

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