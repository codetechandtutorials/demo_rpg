#include <iostream>
#include "playercharacter.h"
int main() {

	// just test code for now, replace 'Warrior' with your class to test
	PlayerCharacter p1(new Warrior());
	for (int i = 0; i < 2; i++) {
		std::cout
			<< p1.getClassName()
			<< " Level " << p1.getLevel() << '\n'
			<< "-EXP: " << p1.getCurrentEXP() << '/' << p1.getEXPToNextLevel() << '\n'
			<< "-HP: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n'
			<< "-MP: " << p1.getCurrentMP() << '/' << p1.getMaxMP() << '\n'
			<< "-Stength: " << p1.getStrength() << '\n'
			<< "-Intellect: " << p1.getIntellect() << '\n'
			<< "-Agility: " << p1.getAgility() << '\n'
			<< "-Armor: " << p1.getArmor() << '\n'
			<< "-Resist: " << p1.getElementRes() << '\n';

		auto AllAbilities= p1.getAbilityList();

		std::cout << "-Abilities:\n";
		for (auto& abil : AllAbilities) {
			std::cout << "  -" << abil.Name << '\n';
		}

		if (i < 1) 
			p1.gainEXP(100u);
	}

	return 0;
}