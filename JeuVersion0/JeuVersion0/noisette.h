#pragma once
#include "Element.h"
class noisette : public Element

{
public:
	void draw(RenderWindow& window);
	unique_ptr<Element> copy();
	void translate(float x);
	noisette(float x,float y);
	~noisette();

private:
	float posx;
	float posy;
	float vitesse;
	unique_ptr<CircleShape> circle;
};

