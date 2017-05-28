#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class Personnage
{
public:
	void draw(RenderWindow& window);
	void translate(float x, float y);
	Personnage();
	~Personnage();
private:
	//Texture perso;
	//Sprite Leo;
	RectangleShape *Leo;
	float vitessex;
	float vitessey;
	float posx;
	float posy;
};

