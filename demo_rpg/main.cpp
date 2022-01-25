#include <iostream>
#include "allclasses.h"
int main() {
	Cleric cler1;
	for (int i = 0; i < 2; i++) {
		std::cout 
			<< "Cleric Level " << cler1.getLevel() << '\n'
			<< "-EXP: " << cler1.getCurrentEXP() << "/" << cler1.getEXPToNextLevel() << '\n'
			<< "-MaxHP: " << cler1.getMaxHp() << '\n'
			<< "-Stength: " << cler1.getStrength() << '\n'
			<< "-Intellect: " << cler1.getIntellect() << '\n';
		if (i < 1) 
			cler1.gainEXP(100u);
	}

	std::cout << "------------\n";

	Rogue rog;
	for (int i = 0; i < 2; i++) {
		std::cout
			<< "Rogue Level " << rog.getLevel() << '\n'
			<< "-EXP: " << rog.getCurrentEXP() << "/" << rog.getEXPToNextLevel() << '\n'
			<< "-MaxHP: " << rog.getMaxHp() << '\n'
			<< "-Stength: " << rog.getStrength() << '\n'
			<< "-Intellect: " << rog.getIntellect() << '\n';
		if (i < 1)
			rog.gainEXP(100u);
	}

	return 0;
}