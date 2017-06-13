#include "noisette.h"
#include "../pugixml/src/pugixml.hpp"

void noisette::draw(RenderWindow& window) {
	window.draw(noisettsprite);
}

void noisette::translate(int x) {
	posx = posx + x;
	noisettsprite.move(x, 0);

}

int noisette::getPosx() {
	return posx;
}

int noisette::getPosy() {
	return posy;
}

int noisette::getSizex() {
	return sizex;
}

int noisette::getSizey() {
	return sizey;
}

unique_ptr<Element> noisette::copy() {
	return make_unique<noisette>(posx, posy);
}

bool noisette::estNuage() {
	return false;
}
// on le pousse hors du plateau
void noisette::setMange() {
	translate(-2000);
}

noisette::noisette(int x, int y)
{
	if (!noisett.loadFromFile(("noisette.png"))) {
		cout << "error load file" << endl;
	}
	noisett.setSmooth(true);
	noisettsprite.setTexture(noisett);
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("jeu.xml");
	pugi::xml_node monjeu = doc.child("monjeu");
	for (pugi::xml_node noouv = monjeu.first_child(); noouv; noouv = noouv.next_sibling())
	{
		if (!strcmp(noouv.name(), "Noisette")) {
			//vitesse = noouv.attribute("vitesse").as_int();
			sizex = noouv.attribute("sizex").as_int();
			sizey = noouv.attribute("sizey").as_int();
		}
	}
	posx = x;
	posy = y;
	noisettsprite.setPosition(posx, posy);
}


noisette::~noisette()
{
}
