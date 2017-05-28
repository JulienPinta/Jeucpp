#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>

using namespace std;
using namespace sf;

class Element
{
public:
	virtual void draw(RenderWindow& window) = 0;
	virtual void translate(int x) = 0;
	Element();
	~Element();

private:
	int posx;
	int posy;
};

