#include "statblock.h"

StatBlock::StatBlock(stattype s, stattype i, stattype a, stattype arm, stattype elres) {
  base.Strength = s;
  base.Intellect = i;
  base.Agility = a;
  base.Armor = arm;
  base.ElementRes = elres;
}
stattype StatBlock::getBaseStrength() { return   base.Strength; }
stattype StatBlock::getBaseIntellect() { return  base.Intellect; }
stattype StatBlock::getBaseAgility() { return    base.Agility; }
stattype StatBlock::getBaseArmor() { return      base.Armor; }
stattype StatBlock::getBaseElementRes() { return base.ElementRes; }

stattype StatBlock::getTotalStrength() { return   base.Strength + fromBuffs.Strength; }
stattype StatBlock::getTotalIntellect() { return  base.Intellect + fromBuffs.Intellect; }
stattype StatBlock::getTotalAgility() { return    base.Agility + fromBuffs.Agility; }
stattype StatBlock::getTotalArmor() { return      base.Armor + fromBuffs.Armor; }
stattype StatBlock::getTotalElementRes() { return base.ElementRes + fromBuffs.ElementRes; }

void StatBlock::addNewBuff(Buff b) {
  for (auto& buff : Buffs) {
    if (b.Name == buff.Name) {
      buff.Duration = b.Duration;
      return;
    }
  }
  Buffs.push_back(b);
  recalculate_buffs();
}
void StatBlock::increaseStats(stattype s, stattype i, stattype a, stattype arm, stattype elres) {
  base.Strength += s;
  base.Intellect += i;
  base.Agility += a;
  base.Armor += arm;
  base.ElementRes += elres;
}
void StatBlock::increaseStats(CoreStats cs) {
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