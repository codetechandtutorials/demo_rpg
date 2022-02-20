#pragma once
#include "types.h"
#include "corestats.h"
#include <string>
struct Buff {
  Buff(const char* name, stattype str = 0, stattype intel = 0, stattype agi = 0,
    stattype arm = 0, stattype elres = 0,  uint16_t dur = 2u, bool isdebuff = false)
    : Name(name), Duration(dur), isDebuff(isdebuff)
  {
    BuffedStats.Strength = str;
    BuffedStats.Intellect = intel;
    BuffedStats.Agility = agi;
    BuffedStats.Armor = arm;
    BuffedStats.ElementRes = elres;
  }

  Buff(const char* name, CoreStats cs, uint16_t dur = 2u, bool isdebuff = false)
    : Name(name), Duration(dur), isDebuff(isdebuff) {
    BuffedStats = cs;
  }

  std::string Name;
  uint16_t Duration;
  CoreStats BuffedStats;
  bool isDebuff;
};