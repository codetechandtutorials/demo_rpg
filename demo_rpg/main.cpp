#include <iostream>
#include "allclasses.h"
int main() {
	Warrior warr1;
	Wizard wiz1;
	Cleric cler1;
	Rogue rog1;

	std::cout << "Warrior\n"
		<< "-MaxHP: " << warr1.getMaxHp() << '\n'
		<< "-Stength: " << warr1.getStrength() << '\n'
		<< "-Intellect: " << warr1.getIntellect() << '\n';

	std::cout << "Wizard\n"
		<< "-MaxHP: " << wiz1.getMaxHp() << '\n'
		<< "-Stength: " << wiz1.getStrength() << '\n'
		<< "-Intellect: " << wiz1.getIntellect() << '\n';

	std::cout << "Cleric\n"
		<< "-MaxHP: " << cler1.getMaxHp() << '\n'
		<< "-Stength: " << cler1.getStrength() << '\n'
		<< "-Intellect: " << cler1.getIntellect() << '\n';

	std::cout << "Rogue\n"
		<< "-MaxHP: " << rog1.getMaxHp() << '\n'
		<< "-Stength: " << rog1.getStrength() << '\n'
		<< "-Intellect: " << rog1.getIntellect() << '\n';


	return 0;
}