#pragma once
#include "types.h"
#include <string>
#include "statblock.h"
struct Buff {
  Buff(const char* name, uint16_t dur = 2u, stattype str = 0,
    stattype intel = 0, stattype agi = 0, stattype arm = 0, stattype elres = 0,
    bool isdebuff = false)
    : Name(name), Duration(dur), Strength(str), Intellect(intel), Agility(agi),
    Armor(arm), ElementRes(elres), isDebuff(isdebuff)
  {}

  std::string Name;
  uint16_t Duration;

  stattype Strength;
  stattype Intellect;
  stattype Agility;
  stattype Armor;
  stattype ElementRes;

  bool isDebuff;
};