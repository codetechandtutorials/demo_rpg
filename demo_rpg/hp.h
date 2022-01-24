#pragma once
#include "hitpointtypes.h"

class hp {
public:
	// returns true if set successfully
	bool setMaxHP(hptype new_max_hp) {
		if (new_max_hp < 1)
			return false;

		MaxHP = new_max_hp;

		if (CurrentHP > MaxHP)
			CurrentHP = MaxHP;

		return true;
	}

	hptype getMaxHp() {
		return MaxHP;
	}

	hptype getCurrentHP() {
		return CurrentHP;
	}

	void takeDamage(hptype damage) {
		if (damage > CurrentHP) {
			CurrentHP = 0;
			return;
		}

		CurrentHP -= damage;
	}

	void heal(hptype amount) {
		if (amount + CurrentHP > MaxHP) {
			CurrentHP = MaxHP;
			return;
		}

		CurrentHP += amount;
	}

	hp() { CurrentHP = 1; MaxHP = 1; }

	hp(hptype cHP, hptype mHP) {
		CurrentHP = cHP;
		MaxHP = mHP;
		if (CurrentHP > MaxHP)
			CurrentHP = MaxHP;
	}

private:
	hptype CurrentHP;
	hptype MaxHP;
};



