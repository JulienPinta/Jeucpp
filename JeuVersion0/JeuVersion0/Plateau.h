#pragma once
#include "Element.h"
#include "Personnage.h"
class Plateau : public Element
{
public:
	void draw(RenderWindow& window);
	void translate(int x);
	void add(unique_ptr<Element> Elem);
	Plateau();
	~Plateau();
private:
	vector<unique_ptr<Element>> mesElem;
	Personnage Leo;
	int score;
};

