#pragma once
#include "Element.h"
class noisette : public Element

{
public:
	void draw(RenderWindow& window);
	unique_ptr<Element> copy();
	void translate(int x);
	noisette(int x,int y);
	~noisette();
	int getPosx();
	int getPosy();
	int getSize();
	void setMange();
	bool estNuage();

private:
	bool enVie = true;
	int posx;
	int posy;
	int vitesse;
	int size = 118;
	unique_ptr<CircleShape> circle;
};

