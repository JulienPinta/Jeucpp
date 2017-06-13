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
	void moveJoueur1(int x, int y);
	void moveJoueur2(int x, int y);
	bool disponible(int y);
	int getScore1();
	int getScore2();

	Plateau();
	~Plateau();
private:

	
	vector<unique_ptr<Element>> mesElem;
	vector<Time> dixderniers;
	int score1;
	int score2;
	bool enCollision(unique_ptr<Element>, Personnage Leo);
	Personnage Joueur1;
	Personnage Joueur2;

};

