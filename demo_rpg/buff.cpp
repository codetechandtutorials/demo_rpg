#include "buff.h"

Buff::Buff() {
  Name = "undefined";
  Duration = 2u;
  BuffedStats = CoreStats();
  isDebuff = false;
}

Buff::Buff(const char* name, stattype str, stattype intel, stattype agi, stattype arm, stattype elres, uint16_t dur, bool isdebuff)
  : Name(name), BuffedStats(str, intel, agi, arm, elres), Duration(dur), isDebuff(isdebuff) {
}

Buff::Buff(const char* name, CoreStats cs, uint16_t dur, bool isdebuff)
  : Name(name), BuffedStats(cs), Duration(dur), isDebuff(isdebuff) {
}

Buff& Buff::operator=(const char* name) {
  this->Name = std::string(name);
  this->Duration = 2u;
  this->BuffedStats = CoreStats(0);
  this->isDebuff = false;
  return *this;
}