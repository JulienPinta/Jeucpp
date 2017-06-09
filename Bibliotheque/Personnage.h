#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>

using namespace std;
using namespace sf;

class Personnage
{
public:
	void draw(RenderWindow& window);
	void translate(int x, int y);
	Personnage();
	~Personnage();
	int getPosx();
	int getPosy();
	int getSize();
private:
	Texture perso;
	Sprite Leosprite;
	//RectangleShape *Leo;
	int vitessex;
	int vitessey;
	int size;
	int posx;
	int posy;
};