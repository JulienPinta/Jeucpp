#include "Plateau.h"


void Plateau::draw(RenderWindow& window) {
	for (auto &e : mesElem) {
		e->draw(window);
	}
	Leo.draw(window);
}

void Plateau::translate(int x) {
	for (auto &e : mesElem) {
		e->translate(x);
	}
}

Plateau::Plateau()
{
	// temps en microsecondes qu'on attend entre chaque rafraichissement, determine la vitesse du jeu
	vitesse = 10;
	score = 0;
}

// random entre 0 et7 
int Plateau::d7()
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> distribution(0,7);
	return distribution(engine);
}

// random entre 0 et 1000

int Plateau::d1000()
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> distribution(0, 1000);
	return distribution(engine);
}

void Plateau::moveLeoUp() {
	Leo.translate(0,-1);
}

void Plateau::moveLeoDown() {
	Leo.translate(0, 1);
}

void Plateau::moveLeoRight() {
	Leo.translate(1, 0);
}

void Plateau::moveLeoLeft() {
	Leo.translate(-1, 0);
}



bool Plateau::enCollision(unique_ptr<Element> e) {
	// paramètres de l'éléments
	int x= e->getPosx();
	int y= e->getPosy();
	int size = e->getSize();

	// paramètres du joueur
	int xjoueur = Leo.getPosx();
	int yjoueur = Leo.getPosy();
	int sizejoueur = Leo.getSize();
	
	// si coin en haut à gauche du joueur est dans l'element
	if (xjoueur > x && xjoueur < x + size && yjoueur > y && yjoueur < y + size) {
		return true;
	}
	// si coin en haut à droite du joueur est dans l'element
	if (xjoueur+sizejoueur > x && xjoueur+sizejoueur < x + size && yjoueur > y && yjoueur < y + size) {
		return true;
	}
	// si coin en bas à gauche du joueur est dans l'element
	if (xjoueur > x && xjoueur < x + size && yjoueur + sizejoueur > y && yjoueur + sizejoueur < y + size) {
		return true;
	}
	// si coin en bas à droite du joueur est dans l'element
	if (xjoueur + sizejoueur > x && xjoueur + sizejoueur < x + size && yjoueur + sizejoueur > y && yjoueur + sizejoueur < y + size) {
		return true;
	}
	return false;
}

void Plateau::gestionClavier() {
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		Leo.translate(0, -1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)){
		Leo.translate(0, 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)){
		Leo.translate(1, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		Leo.translate(-1, 0);
	}
}

int Plateau::getScore() {
	return score;
}

bool Plateau::disponible(int y) {
	int posx = 0;
	int posy = 0;
	int size = 0;
	for (auto &e : mesElem) {
		posx = e->getPosx();
		posy = e->getPosy();
		size = e->getSize();
		if (posx >= 1920 - size && y == posy) {
			return false;
		}
	}
	return true;
}

void Plateau::tourne() {

	if (mesElem.size() > 144) {
		mesElem.erase(mesElem.begin());
	}
	// on redéfinit la vitesse d'apparition des elements en fonction de la vitesse du joueur
	if (dixderniers.size() >= 10) {
	}
	sleep(milliseconds(vitesse));

	// Leo mange les elements qu'il touche
	for (auto &e : mesElem) {
		if (enCollision(e->copy())) {
			e->setMange();
			if (e->estNuage()) {
				score += 1;
			}
			else {
				score -= 10;
			}
			cout << "score: " << score << endl;
		}
	}

	// on decale les elements
	translate(-1);

	// 3 chances sur 190 de faire apparaitre une noisette;
	int y = 120 * d7();

	bool libre = disponible(y);
	
	if (libre && d1000() < 5) {
		auto nois = make_unique<noisette>(1920, y);
		add(nois->copy());
	}
	// 10 chances sur 190 de faire apparaitre un nuage;
	if (libre && d1000() > 985) {
		auto n = make_unique<nuage>(1920, y);
		add(n->copy());
	}

}

void Plateau::add(unique_ptr<Element>element) {
	mesElem.push_back(move(element));
}

Plateau::~Plateau()
{
}
