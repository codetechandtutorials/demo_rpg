#pragma once
#include <cstdint>
typedef std::uint64_t exptype;
typedef std::uint16_t leveltype;

class LevelSystem {
public:
	static const exptype LEVEL2AT = 100u;

	LevelSystem() { 
		CurrentLevel = 1u; 
		CurrentEXP = 0u;
		EXPToNextLevel = LEVEL2AT;
	}

	void gainEXP(exptype gained_exp) {
		CurrentEXP += gained_exp;
		while (check_if_leveled()) {}
	}

	leveltype getLevel() {
		return CurrentLevel;
	}

	exptype getCurrentEXP() {
		return CurrentEXP;
	}

	exptype getEXPToNextLevel() {
		return EXPToNextLevel;
	}
	
	virtual void LevelUp() = 0;

protected:
	leveltype CurrentLevel;
	exptype CurrentEXP;
	exptype EXPToNextLevel;

	bool check_if_leveled() {
		static const leveltype LEVELSCALAR = 2u;
		if (CurrentEXP >= EXPToNextLevel) {
			CurrentLevel++;
			LevelUp();
			EXPToNextLevel *= LEVELSCALAR;
			return true;
		}
		return false;
	}
};