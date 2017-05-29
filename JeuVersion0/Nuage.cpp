#include "nuage.h"
#include "../pugixml/src/pugixml.hpp"

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

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("jeu.xml");
	pugi::xml_node monjeu = doc.child("monjeu");
	for (pugi::xml_node noouv = monjeu.first_child(); noouv; noouv = noouv.next_sibling())
	{
		if (!strcmp(noouv.name(), "Nuage")) {
			vitesse = noouv.attribute("vitesse").as_int();
			size = noouv.attribute("size").as_int();
		}
	}
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
