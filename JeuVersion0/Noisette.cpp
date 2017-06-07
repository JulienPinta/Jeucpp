#include "noisette.h"
#include "../pugixml/src/pugixml.hpp"

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
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("jeu.xml");
	pugi::xml_node monjeu = doc.child("monjeu");
	for (pugi::xml_node noouv = monjeu.first_child(); noouv; noouv = noouv.next_sibling())
	{
		if (!strcmp(noouv.name(), "Noisette")) {
			vitesse = noouv.attribute("vitesse").as_int();
			size = noouv.attribute("size").as_int();
		}
	}
	posx = x;
	posy = y;
	circle = make_unique<CircleShape>(CircleShape(size/2));
	circle->setFillColor(Color(149, 86, 40)); //valeurs trouvées pour faire du marron
	circle->setPosition(posx, posy);
}


noisette::~noisette()
{
}
