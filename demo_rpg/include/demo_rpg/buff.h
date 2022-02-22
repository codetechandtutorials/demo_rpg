#pragma once
#include "types.h"
#include "corestats.h"
#include <string>
struct Buff {
  Buff();

  Buff(const char* name, stattype str = 0, stattype intel = 0, stattype agi = 0,
    stattype arm = 0, stattype elres = 0, uint16_t dur = 2u, bool isdebuff = false);

  Buff(const char* name, CoreStats cs, uint16_t dur = 2u, bool isdebuff = false);

  std::string Name;
  uint16_t Duration;
  CoreStats BuffedStats;
  bool isDebuff;

  Buff& operator=(const char* name);
};