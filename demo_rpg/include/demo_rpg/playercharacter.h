#pragma once
#include "types.h"
#include "statblock.h"
#include "pointwell.h"
#include "ability.h"
#include "item.h"
#include "potion.h"
#include "armor.h"
#include "weapon.h"
#include "buff.h"
#include "item_manager.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>


class PlayerCharacterDelegate : public StatBlock {
public:
  PlayerCharacterDelegate();
  virtual ~PlayerCharacterDelegate() = 0;

  // getters
  leveltype getLevel() const;
  exptype getCurrentEXP() const;
  exptype getEXPToNextLevel() const;
  const std::vector<Buff>& getBuffList() const;

  // mutators
  void gainEXP(exptype gained_exp);
  void applyBuff(Buff b);
  std::unique_ptr<PointWell> HP;
  std::unique_ptr<PointWell> MP;
  std::vector<Ability> Abilities;

  static const exptype LEVEL2AT = 100u;
protected:
  leveltype CurrentLevel;
  exptype CurrentEXP;
  exptype EXPToNextLevel;
  virtual void level_up() = 0;
  bool check_if_leveled();
};







class PlayerCharacter {
private:
  PlayerCharacterDelegate* pcclass;
  Item* EquippedArmor[(unsigned long long)ARMORSLOT::NUM_SLOTS];
  Item* EquippedWeapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
  std::vector<Item*> Backpack;
  void cleanup_backpack();
  friend class ItemManager;

public:
  PlayerCharacter(PlayerCharacterDelegate* pc);
  ~PlayerCharacter();

  // Getters
  const leveltype getLevel() const;
  const exptype getCurrentEXP() const;
  const exptype getEXPToNextLevel() const;
  const welltype getCurrentHP() const;
  const welltype getMaxHP() const;
  const welltype getCurrentMP() const;
  const bool IsMaxHealth() const;
  const welltype getMaxMP() const;
  const stattype getBaseStrength() const;
  const stattype getBaseIntellect() const;
  const stattype getBaseAgility() const;
  const stattype getBaseArmor() const;
  const stattype getBaseElementRes() const;
  const stattype getTotalStrength() const;
  const stattype getTotalIntellect() const;
  const stattype getTotalAgility() const;
  const stattype getTotalArmor() const;
  const stattype getTotalElementRes() const;
  const std::vector<Ability> getAbilityList() const;
  const std::vector<Buff> getBuffList() const;
  const std::vector<Item*> getBackpackList() const;
  const Armor* getEquippedArmorAt(unsigned long long i) const;
  const Weapon* getEquippedWeaponAt(unsigned long long i) const;

  // Modifiers
  void gainEXP(exptype amt);
  void takeDamage(welltype amt);
  void heal(welltype amt);
  void applyBuff(Buff buff);

  // deleted constructors
  PlayerCharacter() = delete;
  PlayerCharacter(const PlayerCharacter&) = delete;
  PlayerCharacter(const PlayerCharacter&&) = delete;
};