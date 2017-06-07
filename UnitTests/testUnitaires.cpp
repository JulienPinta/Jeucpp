#include "gtest\gtest.h"
#include "../Bibliotheque/Noisette.h"
#include "../Bibliotheque/monMain.h"
#include "SFML/Graphics.hpp"

TEST(Noisette, getPosxWorks) {
	noisette nois1(100,0);
	EXPECT_EQ(100, nois1.getPosx());
}

TEST(Noisette, getPosyWorks) {
	noisette nois1(0,50);
	EXPECT_EQ(50, nois1.getPosy());
}