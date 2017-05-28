#include "nuage.h"

void nuage::draw(RenderWindow& window) {
	window.draw(*rect);
}

unique_ptr<Element> nuage::copy() {
	return make_unique<nuage>(posx, posy);
}
void nuage::translate(int x) {
	rect->move(x, 0);
}

nuage::nuage(int x,int y)
{
	posx = x;
	posy = y;
	vitesse = 1; //valeurs initiales, a changer plus tard
	rect = make_unique<RectangleShape>(RectangleShape(Vector2f(40,40)));
	rect->setPosition(x, y);
	rect->setFillColor(Color::Red);
}


nuage::~nuage()
{
}
