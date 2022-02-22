#pragma once
#include "types.h"
#include "buff.h"
#include <vector>

class StatBlock {
  CoreStats base;
  CoreStats fromBuffs;
public:
  StatBlock(stattype s = 1, stattype i = 1, stattype a = 1, stattype arm = 0, stattype elres = 0);
  stattype GetBaseStrength();
  stattype GetBaseIntellect();
  stattype GetBaseAgility();
  stattype GetBaseArmor();
  stattype GetBaseElementRes();
  stattype GetTotalStrength();
  stattype GetTotalIntellect();
  stattype GetTotalAgility();
  stattype GetTotalArmor();
  stattype GetTotalElementRes();
protected:
  std::vector<Buff> Buffs;
  void add_or_refresh_buff(Buff b);
  void increase_stats(stattype s = 0, stattype i = 0, stattype a = 0, stattype arm = 0, stattype elres = 0);
  void increase_stats(CoreStats cs);
private:
  void recalculate_buffs();
};