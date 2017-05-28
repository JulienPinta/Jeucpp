#include "Personnage.h"


void Personnage::draw(RenderWindow& window) {
	window.draw(*Leo);
}

void Personnage::translate(float x,float y) {
	posx = posx + x*vitessex;
	posy = posy + y*vitessey;
	Leo->setPosition(posx, posy);
}

Personnage::Personnage()
{
	/*if (!perso.loadFromFile(("Leo.png"),IntRect(96,0,32,48))) {
		cout << "error load file" << endl;
	}
	perso.setSmooth(true);
	Leo.setTexture(perso);*/
	Leo = new RectangleShape(Vector2f(40,40));
	vitessex = 1;
	vitessey = 1;
	posx = 0;
	posy = 200;
	Leo->setPosition(posx, posy);
}


Personnage::~Personnage()
{
}
