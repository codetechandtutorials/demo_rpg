#pragma once
#include "hp.h"
#include "statblock.h"
#include "levelsystem.h"
class Rogue : public hp, public StatBlock, public LevelSystem {

public:
	static const hptype BASEHP = (hptype)12u;
	static const stattype BASESTR = (stattype)3u;
	static const stattype BASEINT = (stattype)2u;

	static const hptype HPGROWTH = (hptype)6u;
	static const stattype STRGROWTH = (stattype)2u;
	static const stattype INTGROWTH = (stattype)1u;

	Rogue() : hp(BASEHP, BASEHP), StatBlock(BASESTR, BASEINT) {}

private:
	void LevelUp() override {
		setMaxHP(HPGROWTH + getMaxHp());
		increaseStats(STRGROWTH, INTGROWTH);
	}
};