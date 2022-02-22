#include "statblock.h"

StatBlock::StatBlock(stattype s, stattype i, stattype a, stattype arm, stattype elres) {
  base.Strength = s;
  base.Intellect = i;
  base.Agility = a;
  base.Armor = arm;
  base.ElementRes = elres;
}
stattype StatBlock::GetBaseStrength() { return   base.Strength; }
stattype StatBlock::GetBaseIntellect() { return  base.Intellect; }
stattype StatBlock::GetBaseAgility() { return    base.Agility; }
stattype StatBlock::GetBaseArmor() { return      base.Armor; }
stattype StatBlock::GetBaseElementRes() { return base.ElementRes; }

stattype StatBlock::GetTotalStrength() { return   base.Strength + fromBuffs.Strength; }
stattype StatBlock::GetTotalIntellect() { return  base.Intellect + fromBuffs.Intellect; }
stattype StatBlock::GetTotalAgility() { return    base.Agility + fromBuffs.Agility; }
stattype StatBlock::GetTotalArmor() { return      base.Armor + fromBuffs.Armor; }
stattype StatBlock::GetTotalElementRes() { return base.ElementRes + fromBuffs.ElementRes; }

void StatBlock::add_or_refresh_buff(Buff b) {
  for (auto& _buff : Buffs) {
    if (b.Name == _buff.Name) {
      _buff.Duration = b.Duration;
      return;
    }
  }
  Buffs.push_back(b);
  recalculate_buffs();
}
void StatBlock::increase_stats(stattype s, stattype i, stattype a, stattype arm, stattype elres) {
  base.Strength += s;
  base.Intellect += i;
  base.Agility += a;
  base.Armor += arm;
  base.ElementRes += elres;
}
void StatBlock::increase_stats(CoreStats cs) {
  base += cs;
}
void StatBlock::recalculate_buffs() {
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