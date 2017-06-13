#include "Plateau.h"


void Plateau::draw(RenderWindow& window) {
	for (auto &e : mesElem) {
		e->draw(window);
	}
	Joueur2.draw(window);
	Joueur1.draw(window);
}

void Plateau::translate(int x) {
	for (auto &e : mesElem) {
		e->translate(x);
	}
}

Plateau::Plateau()
{

	score1 = 0;
	score2 = 0;
}



void Plateau::moveJoueur1(int x, int y) {
	Joueur1.translate(x, y);
}

void Plateau::moveJoueur2(int x, int y) {
	Joueur2.translate(x, y);
}



bool Plateau::enCollision(unique_ptr<Element> e, Personnage Leo) {
	// paramètres de l'éléments
	int x = e->getPosx();
	int y = e->getPosy();
	int sizex = e->getSizex();
	int sizey = e->getSizey();

	// paramètres du joueur
	int xjoueur = Leo.getPosx();
	int yjoueur = Leo.getPosy();
	int sizejoueurx = Leo.getSizex();
	int sizejoueury = Leo.getSizey();

	// si coin en haut à gauche du joueur est dans l'element
	if (xjoueur > x && xjoueur < x + sizex && yjoueur > y && yjoueur < y + sizey) {
		return true;
	}
	// si coin en haut à droite du joueur est dans l'element
	if (xjoueur + sizejoueurx > x && xjoueur + sizejoueurx < x + sizex && yjoueur > y && yjoueur < y + sizey) {
		return true;
	}
	// si coin en bas à gauche du joueur est dans l'element
	if (xjoueur > x && xjoueur < x + sizex && yjoueur + sizejoueury > y && yjoueur + sizejoueury < y + sizey) {
		return true;
	}
	// si coin en bas à droite du joueur est dans l'element
	if (xjoueur + sizejoueurx > x && xjoueur + sizejoueurx < x + sizex && yjoueur + sizejoueury > y && yjoueur + sizejoueury < y + sizey) {
		return true;
	}
	return false;
}
/*
void Plateau::gestionClavier() {
	for (auto &Leo : persos) {
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			Leo.translate(0, -1);
			cout << "Up" << endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			Leo.translate(0, 1);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			Leo.translate(1, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			Leo.translate(-1, 0);
		}
	}
}
*/

int Plateau::getScore1() {
	return score1;
}
int Plateau::getScore2() {
	return score2;
}

bool Plateau::disponible(int y) {
	int posx = 0;
	int posy = 0;
	int size = 0;
	for (auto &e : mesElem) {
		posx = e->getPosx();
		posy = e->getPosy();
		size = e->getSizex();
		if (posx >= 1920 - size && y == posy) {
			return false;
		}
	}
	return true;
}


void Plateau::tourne() {
	// il ne peut pas y avoir plus de 72 elements à la fois sur le plateau de par leur taille.
	// s'il y en a plus de 72 dans la liste, le premier est nécéssairement en dehors du plateau.
	if (mesElem.size() > 72) {
		mesElem.erase(mesElem.begin());
	}
	
	// Leo mange les elements qu'il touche
	for (auto &e : mesElem) {
		if (enCollision(e->copy(),Joueur1)) {
			e->setMange();
			if (e->estNuage()) {
				score1 += 1;
			}
			else {
				score1 -= 3;
			}
			cout << "score1: " << score1 << endl;
		}
		if (enCollision(e->copy(), Joueur2)) {
			e->setMange();
			if (e->estNuage()) {
				score2 += 1;
			}
			else {
				score2 -= 3;
			}
			cout << "score2: " << score2 << endl;
		}
	}

	// on decale les elements
	translate(-1);


}

void Plateau::add(unique_ptr<Element>element) {
	mesElem.push_back(move(element));
}

Plateau::~Plateau()
{
}