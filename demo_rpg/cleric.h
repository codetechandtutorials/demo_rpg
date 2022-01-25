#pragma once
#include "hp.h"
#include "statblock.h"
#include "levelsystem.h"
class Cleric : public hp, public StatBlock, public LevelSystem {
public:

	static const hptype BASEHP = (hptype)14u;
	static const stattype BASESTR = (stattype)2u;
	static const stattype BASEINT = (stattype)3u;

	static const hptype HPGROWTH = (hptype)7u;
	static const stattype STRGROWTH = (stattype)1u;
	static const stattype INTGROWTH = (stattype)2u;

	Cleric() : hp(BASEHP, BASEHP), StatBlock(BASESTR, BASEINT) {}

private:
	void LevelUp() override {
		setMaxHP(HPGROWTH + getMaxHp());
		increaseStats(STRGROWTH, INTGROWTH);
	}
};