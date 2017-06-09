#pragma once
#include "Element.h"
class noisette : public Element

{
public:
	void draw(RenderWindow& window);
	unique_ptr<Element> copy();
	void translate(int x);
	noisette(int x, int y);
	~noisette();
	int getPosx();
	int getPosy();
	int getSizex();
	int getSizey();
	void setMange();
	bool estNuage();

private:
	bool enVie = true;
	int posx;
	int posy;
	int vitesse;
	int sizex;
	int sizey;
	Texture noisett;
	Sprite noisettsprite;
};


