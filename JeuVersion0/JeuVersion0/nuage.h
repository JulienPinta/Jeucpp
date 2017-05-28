#pragma once
#include "Element.h"

class nuage : public Element
{
public: 
	void draw(RenderWindow& window);
	void translate(int x);
	unique_ptr<Element> copy();
	nuage(int posx,int posy);
	~nuage();
private:
	int posx;
	int posy;
	int taille;
	float vitesse;
	unique_ptr<RectangleShape> rect;
};

