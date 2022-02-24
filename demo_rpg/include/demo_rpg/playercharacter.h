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
  static const exptype LEVEL2AT = 100u;
  PlayerCharacterDelegate();
  virtual ~PlayerCharacterDelegate() = 0;
  [[nodiscard]] leveltype GetLevel() const noexcept;
  [[nodiscard]] exptype GetCurrentEXP() const noexcept;
  [[nodiscard]] exptype GetEXPToNextLevel() const noexcept;
  void GiveEXP(const exptype amt) noexcept;
  std::unique_ptr<PointWell> HP;
  std::unique_ptr<PointWell> MP;
  std::vector<Ability> Abilities;
  std::vector<Buff> Buffs;
protected:
private:
  exptype CurrentEXP;
  exptype EXPToNextLevel;
  virtual void level_up() = 0;
  leveltype CurrentLevel;
  [[nodiscard]] bool check_if_leveled() noexcept;
};

class PlayerCharacter final {
public:
  PlayerCharacter(PlayerCharacterDelegate* pc);
  ~PlayerCharacter();

  // Getters
  [[nodiscard]] const leveltype GetLevel() const noexcept;
  [[nodiscard]] const exptype getCurrentEXP() const noexcept;
  [[nodiscard]] const exptype getEXPToNextLevel() const noexcept;
  [[nodiscard]] const welltype getCurrentHP() const noexcept;
  [[nodiscard]] const welltype getMaxHP() const noexcept;
  [[nodiscard]] const welltype getCurrentMP() const noexcept;
  [[nodiscard]] const bool IsMaxHealth() const noexcept;
  [[nodiscard]] const welltype getMaxMP() const noexcept;
  [[nodiscard]] const stattype getBaseStrength() const noexcept;
  [[nodiscard]] const stattype getBaseIntellect() const noexcept;
  [[nodiscard]] const stattype getBaseAgility() const noexcept;
  [[nodiscard]] const stattype getBaseArmor() const noexcept;
  [[nodiscard]] const stattype getBaseElementRes() const noexcept;
  [[nodiscard]] const stattype getTotalStrength() const noexcept;
  [[nodiscard]] const stattype getTotalIntellect() const noexcept;
  [[nodiscard]] const stattype getTotalAgility() const noexcept;
  [[nodiscard]] const stattype getTotalArmor() const noexcept;
  [[nodiscard]] const stattype getTotalElementRes() const noexcept;
  [[nodiscard]] const std::vector<Ability> getAbilityList() const noexcept;
  [[nodiscard]] const std::vector<Buff> getBuffList() const noexcept;
  [[nodiscard]] const std::vector<Item*> getBackpackList() const noexcept;
  [[nodiscard]] const Armor* getEquippedArmorAt(unsigned long long i) const noexcept;
  [[nodiscard]] const Weapon* getEquippedWeaponAt(unsigned long long i) const noexcept;

  // Modifiers
  void gainEXP(exptype amt) noexcept;
  void takeDamage(welltype amt) noexcept;
  void heal(welltype amt) noexcept;
  void applyBuff(Buff buff) noexcept;

private:
  PlayerCharacterDelegate* pcclass;
  std::vector<Item*> Backpack;

  Item* EquippedArmor[(unsigned long long)ARMORSLOT::NUM_SLOTS];
  Item* EquippedWeapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
  
  void move_to_backpack(Item* item_to_move) noexcept;
  void cleanup_backpack() noexcept;
  friend class ItemManager;

  // deleted constructors
  PlayerCharacter() = delete;
  PlayerCharacter(const PlayerCharacter&) = delete;
  PlayerCharacter(const PlayerCharacter&&) = delete;
};