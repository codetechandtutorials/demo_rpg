#pragma once
#include "types.h"
#include "buff.h"
#include <vector>
class StatBlock {
  stattype BaseStrength;
  stattype BaseIntellect;
  stattype BaseAgility;
  stattype BaseArmor;
  stattype BaseElementRes;

  stattype TotalStrengthFromBuffs = 0;
  stattype TotalIntellectFromBuffs = 0;
  stattype TotalAgilityFromBuffs = 0;
  stattype TotalArmorFromBuffs = 0;
  stattype TotalElementResFromBuffs = 0;
public:
  explicit StatBlock(stattype s = 1, stattype i = 1, stattype a = 1, stattype arm = 0, stattype elres = 0) {
    BaseStrength = s;
    BaseIntellect = i;
    BaseAgility = a;
    BaseArmor = arm;
    BaseElementRes = elres;
  }
  stattype getBaseStrength() { return BaseStrength; }
  stattype getBaseIntellect() { return BaseIntellect; }
  stattype getBaseAgility() { return BaseAgility; }
  stattype getBaseArmor() { return BaseArmor; }
  stattype getBaseElementRes() { return BaseElementRes; }

  stattype getTotalStrength() { return BaseStrength + TotalStrengthFromBuffs; }
  stattype getTotalIntellect() { return BaseIntellect + TotalIntellectFromBuffs; }
  stattype getTotalAgility() { return BaseAgility + TotalAgilityFromBuffs; }
  stattype getTotalArmor() { return BaseArmor + TotalArmorFromBuffs; }
  stattype getTotalElementRes() { return BaseElementRes + TotalElementResFromBuffs; }

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
    BaseStrength += s;
    BaseIntellect += i;
    BaseAgility += a;
    BaseArmor += arm;
    BaseElementRes += elres;
  }
private:
  void recalculate_buffs() {

    stattype totalstrengthfrombuffs = 0;
    stattype totalintellectfrombuffs = 0;
    stattype totalagilityfrombuffs = 0;
    stattype totalarmorfrombuffs = 0;
    stattype totalelementresfrombuffs = 0;

    for (const auto& b : Buffs) {
      if (b.isDebuff) {
        totalstrengthfrombuffs -= b.Strength;
        totalintellectfrombuffs -= b.Intellect;
        totalagilityfrombuffs -= b.Agility;
        totalarmorfrombuffs -= b.Armor;
        totalelementresfrombuffs -= b.ElementRes;
      }
      else {
        totalstrengthfrombuffs += b.Strength;
        totalintellectfrombuffs += b.Intellect;
        totalagilityfrombuffs += b.Agility;
        totalarmorfrombuffs += b.Armor;
        totalelementresfrombuffs += b.ElementRes;
      }
    }

    TotalStrengthFromBuffs = totalstrengthfrombuffs;
    TotalIntellectFromBuffs = totalintellectfrombuffs;
    TotalAgilityFromBuffs = totalagilityfrombuffs;
    TotalArmorFromBuffs = totalarmorfrombuffs;
    TotalElementResFromBuffs = totalelementresfrombuffs;

    if (TotalStrengthFromBuffs < 0) TotalStrengthFromBuffs = 0;
    if (TotalIntellectFromBuffs < 0) TotalIntellectFromBuffs = 0;
    if (TotalAgilityFromBuffs < 0) TotalAgilityFromBuffs = 0;
    if (TotalArmorFromBuffs < 0) TotalArmorFromBuffs = 0;
    if (TotalElementResFromBuffs < 0) TotalElementResFromBuffs = 0;

  }
};