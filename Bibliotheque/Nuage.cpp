#include "../pugixml/src/pugixml.hpp"
#include "nuage.h"
void nuage::draw(RenderWindow& window) {
	window.draw(nuagsprite);
}

unique_ptr<Element> nuage::copy() {
	return make_unique<nuage>(posx, posy);
}
void nuage::translate(int x) {
	posx = posx + x;
	nuagsprite.move(x, 0);
}

int nuage::getPosx() {
	return posx;
}

int nuage::getPosy() {
	return posy;
}

int nuage::getSizex() {
	return sizex;
}

int nuage::getSizey() {
	return sizey;
}

bool nuage::estNuage() {
	return true;
}

void nuage::setMange() {
	translate(-2000);
}

nuage::nuage(int x, int y)
{
	if (!nuag.loadFromFile(("nuage.png"))) {
		cout << "error load file" << endl;
	}
	nuag.setSmooth(true);
	nuagsprite.setTexture(nuag);
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("jeu.xml");
	pugi::xml_node monjeu = doc.child("monjeu");
	for (pugi::xml_node noouv = monjeu.first_child(); noouv; noouv = noouv.next_sibling())
	{
		if (!strcmp(noouv.name(), "Nuage")) {
			vitesse = noouv.attribute("vitesse").as_int();
			sizex = noouv.attribute("sizex").as_int();
			sizey = noouv.attribute("sizey").as_int();
		}
	}
	posx = x;
	posy = y;
	nuagsprite.setPosition(x, y);
}


nuage::~nuage()
{
}
