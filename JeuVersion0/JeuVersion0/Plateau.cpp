#include "Plateau.h"


void Plateau::draw(RenderWindow& window) {
	for (auto &e : mesElem) {
		e->draw(window);
	}
}

void Plateau::translate(int x) {
	for (auto &e : mesElem) {
		e->translate(x);
	}
}

Plateau::Plateau()
{
	

}

void Plateau::add(unique_ptr<Element>element) {
	mesElem.push_back(move(element));
}

Plateau::~Plateau()
{
	for (auto &e : mesElem) {
		delete &e;
	}
}
