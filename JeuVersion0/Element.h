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
	virtual unique_ptr<Element> copy() = 0;
	virtual void setMange() = 0;
	virtual int getPosx() = 0;
	virtual int getPosy() = 0;
	virtual int getSize() = 0;
	virtual bool estNuage() = 0;
	Element();
	~Element();

private:
	int size;
	int posx;
	int posy;
};

