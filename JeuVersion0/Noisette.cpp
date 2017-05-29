#include "noisette.h"

void noisette::draw(RenderWindow& window) {
	window.draw(*circle);
}

void noisette::translate(int x) {
	posx = posx + x;
	circle->move(x,0);

}

int noisette::getPosx() {
	return posx;
}

int noisette::getPosy() {
	return posy;
}

int noisette::getSize() {
	return size;
}

unique_ptr<Element> noisette::copy() {
	return make_unique<noisette>(posx,posy);
}

bool noisette::estNuage() {
	return false;
}

void noisette::setMange() {
	translate(-2000);
}

noisette::noisette(int x, int y)
{
	posx = x;
	posy = y;
	vitesse = 1; //valeurs initiales, a changer plus tard
	circle = make_unique<CircleShape>(CircleShape(size/2));
	circle->setFillColor(Color(149, 86, 40)); //valeurs trouvées pour faire du marron
	circle->setPosition(posx, posy);
}


noisette::~noisette()
{
}
