#include "Personnage.h"
#include "../pugixml/src/pugixml.hpp"

void Personnage::draw(RenderWindow& window) {
	window.draw(*Leo);
}

void Personnage::translate(int x,int y) {
	posx = posx + x*vitessex;
	posy = posy + y*vitessey;
	Leo->setPosition(posx, posy);
}

int Personnage::getPosx() {
	return posx;
}

int Personnage::getPosy() {
	return posy;
}


int Personnage::getSize() {
	return size;
	
}

Personnage::Personnage()
{
	/*if (!perso.loadFromFile(("Leo.png"),IntRect(96,0,32,48))) {
		cout << "error load file" << endl;
	}
	perso.setSmooth(true);
	Leo.setTexture(perso);*/
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("jeu.xml");
	pugi::xml_node monjeu = doc.child("monjeu");
	for (pugi::xml_node noouv = monjeu.first_child(); noouv; noouv = noouv.next_sibling())
	{
		if (!strcmp(noouv.name(), "Leo")) {
			vitessex = noouv.attribute("vitessex").as_int();
			vitessey = noouv.attribute("vitessey").as_int();
			size = noouv.attribute("size").as_int();
		}
	}
	Leo = new RectangleShape(Vector2f(size,size));
	vitessex = 4;
	vitessey = 4;
	posx = 0;
	posy = 200;
	Leo->setPosition(posx, posy);
	Leo->setFillColor(Color::Red);
}


Personnage::~Personnage()
{
}
