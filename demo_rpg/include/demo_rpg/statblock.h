#pragma once
#include "types.h"
#include "buff.h"
#include <vector>

class StatBlock {
  CoreStats base;
  CoreStats fromBuffs;
public:
  explicit StatBlock(stattype s = 1, stattype i = 1, stattype a = 1, stattype arm = 0, stattype elres = 0) {
    base.Strength = s;
    base.Intellect = i;
    base.Agility = a;
    base.Armor = arm;
    base.ElementRes = elres;
  }
  stattype getBaseStrength() { return   base.Strength; }
  stattype getBaseIntellect() { return  base.Intellect; }
  stattype getBaseAgility() { return    base.Agility; }
  stattype getBaseArmor() { return      base.Armor; }
  stattype getBaseElementRes() { return base.ElementRes; }

  stattype getTotalStrength() { return   base.Strength   + fromBuffs.Strength; }
  stattype getTotalIntellect() { return  base.Intellect  + fromBuffs.Intellect; }
  stattype getTotalAgility() { return    base.Agility    + fromBuffs.Agility; }
  stattype getTotalArmor() { return      base.Armor      + fromBuffs.Armor; }
  stattype getTotalElementRes() { return base.ElementRes + fromBuffs.ElementRes; }

protected:
  void addNewBuff(Buff b) {
    for (auto& buff : Buffs) {
      if (b.Name == buff.Name) {
        buff.Duration = b.Duration;
        return;
      }
    }
    Buffs.push_back(b);
    recalculate_buffs();
  }
  std::vector<Buff> Buffs;
  void increaseStats(stattype s = 0, stattype i = 0, stattype a = 0, stattype arm = 0, stattype elres = 0) {
    base.Strength += s;
    base.Intellect += i;
    base.Agility += a;
    base.Armor += arm;
    base.ElementRes += elres;
  }
  void increaseStats(CoreStats cs) {
    base += cs;
  }
private:
  void recalculate_buffs() {
    CoreStats tmp_total;
    for (const auto& b : Buffs) {
      if (b.isDebuff) {
        tmp_total -= b.BuffedStats;
      } else {
        tmp_total += b.BuffedStats;
      }
    }
    fromBuffs = tmp_total;
  }
};