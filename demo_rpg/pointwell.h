#pragma once
#include <cstdint>
typedef std::uint16_t welltype;
class PointWell {
public:
	// returns true if set successfully
	bool setMax(welltype new_max) {
		if (new_max < 1)
			return false;

		MaxWell = new_max;

		if (CurrentFullness > MaxWell)
			CurrentFullness = MaxWell;

		return true;
	}

	welltype getMax() {
		return MaxWell;
	}

	welltype getCurrent() {
		return CurrentFullness;
	}

	void reduceCurrent(welltype damage) {
		if (damage > CurrentFullness) {
			CurrentFullness = 0;
			return;
		}

		CurrentFullness -= damage;
	}

	void increaseCurrent(welltype amount) {
		if (amount + CurrentFullness > MaxWell) {
			CurrentFullness = MaxWell;
			return;
		}

		CurrentFullness += amount;
	}

	PointWell() { CurrentFullness = 1; MaxWell = 1; }

	PointWell(welltype c, welltype m) {
		CurrentFullness = c;
		MaxWell = m;
		if (CurrentFullness > MaxWell)
			CurrentFullness = MaxWell;
	}

private:
	welltype CurrentFullness;
	welltype MaxWell;
};
