#pragma once
#include "hp.h"
#include "statblock.h"
class Rogue : public hp, public StatBlock {

public:
	static const hptype HPGROWTH = (hptype)13u;
	static const stattype BASESTR = (stattype)3u;
	static const stattype BASEINT = (stattype)2u;

	Rogue() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {}

private:
};