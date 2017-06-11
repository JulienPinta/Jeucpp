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
	int getSizex();
	int getSizey();
private:
	Texture perso;
	Sprite Leosprite;
	//RectangleShape *Leo;
	int vitessex;
	int vitessey;
	int sizex;
	int sizey;
	int posx;
	int posy;
};