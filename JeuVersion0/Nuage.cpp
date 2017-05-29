#include "nuage.h"

void nuage::draw(RenderWindow& window) {
	window.draw(*rect);
}

unique_ptr<Element> nuage::copy() {
	return make_unique<nuage>(posx, posy);
}
void nuage::translate(int x) {
	posx = posx + x;
	rect->move(x, 0);
}

int nuage::getPosx() {
	return posx;
}

int nuage::getPosy() {
	return posy;
}

int nuage::getSize() {
	return size;
}

bool nuage::estNuage() {
	return true;
}

void nuage::setMange() {
	translate(-2000);
}

nuage::nuage(int x,int y)
{
	posx = x;
	posy = y;
	vitesse = 1; //valeurs initiales, a changer plus tard
	rect = make_unique<RectangleShape>(RectangleShape(Vector2f(size,size)));
	rect->setPosition(x, y);
	rect->setFillColor(Color::White);
}


nuage::~nuage()
{
}
