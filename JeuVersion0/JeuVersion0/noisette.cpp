#include "noisette.h"

void noisette::draw(RenderWindow& window) {
	window.draw(*circle);
}

void noisette::translate(float x) {
	circle->move(x,0);

}

unique_ptr<Element> noisette::copy() {
	return make_unique<noisette>(posx,posy);
}

noisette::noisette(float x, float y)
{
	posx = x;
	posy = y;
	vitesse = 1; //valeurs initiales, a changer plus tard
	circle = make_unique<CircleShape>(CircleShape(40));
	circle->setFillColor(Color(149, 86, 40)); //valeurs trouvées pour faire du marron
	circle->setPosition(posx, posy);
}


noisette::~noisette()
{
}
