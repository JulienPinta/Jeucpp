#include "../pugixml/src/pugixml.hpp"
#include "Personnage.h"

void Personnage::draw(RenderWindow& window) {
	window.draw(Leosprite);
}

void Personnage::translate(int x, int y) {
	posx = posx + x*vitessex;
	posy = posy + y*vitessey;
	Leosprite.setPosition(posx, posy);
}

int Personnage::getPosx() {
	return posx;
}

int Personnage::getPosy() {
	return posy;
}


int Personnage::getSizex() {
	return sizex;

}

int Personnage::getSizey() {
	return sizey;

}


Personnage::Personnage()
{
	if (!perso.loadFromFile(("montgolfiere.png"))) {
	cout << "error load file" << endl;
	}
	perso.setSmooth(true);
	Leosprite.setTexture(perso);
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("jeu.xml");
	pugi::xml_node monjeu = doc.child("monjeu");
	for (pugi::xml_node noouv = monjeu.first_child(); noouv; noouv = noouv.next_sibling())
	{
		if (!strcmp(noouv.name(), "Leo")) {
			vitessex = noouv.attribute("vitessex").as_int();
			vitessey = noouv.attribute("vitessey").as_int();
			sizex = noouv.attribute("sizex").as_int();
			sizey = noouv.attribute("sizey").as_int();
		}
	}
	posx = 0;
	posy = 200;
	Leosprite.setPosition(posx, posy);
}


Personnage::~Personnage()
{
}
