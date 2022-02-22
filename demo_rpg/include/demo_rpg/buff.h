#pragma once
#include "types.h"
#include "corestats.h"
#include <string>
struct Buff {
  Buff() {
    Name = "undefined";
    Duration = 2u;
    BuffedStats = CoreStats();
    isDebuff = false;
  }

  Buff(const char* name, stattype str = 0, stattype intel = 0, stattype agi = 0,
    stattype arm = 0, stattype elres = 0, uint16_t dur = 2u, bool isdebuff = false)
    : Name(name), BuffedStats(str, intel, agi, arm, elres), Duration(dur), isDebuff(isdebuff) {
  }

  Buff(const char* name, CoreStats cs, uint16_t dur = 2u, bool isdebuff = false)
    : Name(name), BuffedStats(cs), Duration(dur), isDebuff(isdebuff) {
  }


  std::string Name;
  uint16_t Duration;
  CoreStats BuffedStats;
  bool isDebuff;

  Buff& operator=(const char* name) {
    this->Name = std::string(name);
    this->Duration = 2u;
    this->BuffedStats = CoreStats(0);
    this->isDebuff = false;
    return *this;
  }
};