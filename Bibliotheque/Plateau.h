#pragma once
#include <SFML/Graphics.hpp>
#include "Personnage.h"
#include "Element.h"
#include "noisette.h"
#include "Plateau.h"
#include "nuage.h"
#include <random>

class Plateau
{
public:
	void draw(RenderWindow& window);
	void translate(int x);
	void add(unique_ptr<Element> Elem);
	void tourne();
	void moveLeoUp();
	void moveLeoDown();
	void moveLeoRight();
	void moveLeoLeft();
	void gestionClavier();
	int getScore();

	Plateau();
	~Plateau();
private:
	int d7();
	int d1000();
	bool disponible(int y);
	vector<unique_ptr<Element>> mesElem;
	vector<Time> dixderniers;
	Personnage Leo;
	int score;
	int vitesse;
	bool enCollision(unique_ptr<Element>);

};

