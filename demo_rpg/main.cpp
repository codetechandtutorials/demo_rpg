#include <iostream>
#include "playercharacter.h"
int main() {
	PlayerCharacter p1(new Warrior());

	for (int i = 0; i < 2; i++) {
		std::cout 
			<< p1.getClassName()
			<< " Level " << p1.getLevel() << '\n'
			<< "-EXP: " << p1.getCurrentEXP() << '/' << p1.getEXPToNextLevel() << '\n'
			<< "-HP: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n'
			<< "-Stength: " << p1.getStrength() << '\n'
			<< "-Intellect: " << p1.getIntellect() << '\n';
		if (i < 1) 
			p1.gainEXP(100u);
	}

	return 0;
}