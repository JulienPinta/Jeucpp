#include "Personnage.h"


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
