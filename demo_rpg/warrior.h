#pragma once
#include "hp.h"
#include "statblock.h"
#include "levelsystem.h"
class Warrior : public hp, public StatBlock, public LevelSystem {

public:
	static const hptype BASEHP = (hptype)18u;
	static const stattype BASESTR = (stattype)4u;
	static const stattype BASEINT = (stattype)1u;

	static const hptype HPGROWTH = (hptype)9u;
	static const stattype STRGROWTH = (stattype)2u;
	static const stattype INTGROWTH = (stattype)1u;

	Warrior() : hp(BASEHP, BASEHP), StatBlock(BASESTR, BASEINT) {}

private:
	void LevelUp() override {
		setMaxHP(HPGROWTH + getMaxHp());
		increaseStats(STRGROWTH, INTGROWTH);
	}
};