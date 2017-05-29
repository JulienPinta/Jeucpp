#pragma once
#include "Element.h"

class nuage : public Element
{
public:
	void draw(RenderWindow& window);
	void translate(int x);
	unique_ptr<Element> copy();
	nuage(int posx, int posy);
	~nuage();
	int getPosx();
	int getPosy();
	int getSize();
	bool estNuage();
	void setMange();
private:
	bool enVie = true;
	int posx;
	int posy;
	int taille;
	int vitesse;
	int size = 118;
	unique_ptr<RectangleShape> rect;
};

