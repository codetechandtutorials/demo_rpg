#pragma once
#include "types.h"
#include "buff.h"
#include <vector>

class StatBlock {
  CoreStats base;
  CoreStats fromBuffs;
public:
  StatBlock(stattype s = 1, stattype i = 1, stattype a = 1, stattype arm = 0, stattype elres = 0);
  stattype getBaseStrength();
  stattype getBaseIntellect();
  stattype getBaseAgility();
  stattype getBaseArmor();
  stattype getBaseElementRes();
  stattype getTotalStrength();
  stattype getTotalIntellect();
  stattype getTotalAgility();
  stattype getTotalArmor();
  stattype getTotalElementRes();
protected:
  std::vector<Buff> Buffs;
  void addNewBuff(Buff b);
  void increaseStats(stattype s = 0, stattype i = 0, stattype a = 0, stattype arm = 0, stattype elres = 0);
  void increaseStats(CoreStats cs);
private:
  void recalculate_buffs();
};