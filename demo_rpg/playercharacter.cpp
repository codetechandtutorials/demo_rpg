#include "playercharacter.h"
#include <memory>

PlayerCharacterDelegate::~PlayerCharacterDelegate() {}


void PlayerCharacterDelegate::GiveEXP(const exptype amt) noexcept {
  CurrentEXP += amt;
  while (check_if_leveled()) {}
}

PlayerCharacterDelegate::PlayerCharacterDelegate() : StatBlock(0u, 0u) {
  CurrentLevel = (leveltype)1u;
  CurrentEXP = (exptype)0u;
  EXPToNextLevel = LEVEL2AT;
}

[[nodiscard]] leveltype PlayerCharacterDelegate::GetLevel() const noexcept {
  return CurrentLevel;
}

[[nodiscard]] exptype PlayerCharacterDelegate::GetCurrentEXP() const noexcept {
  return CurrentEXP;
}

[[nodiscard]] exptype PlayerCharacterDelegate::GetEXPToNextLevel() const noexcept {
  return EXPToNextLevel;
}

[[nodiscard]] bool PlayerCharacterDelegate::check_if_leveled() noexcept {
  static const leveltype LEVELSCALAR = 2u;
  if (CurrentEXP >= EXPToNextLevel) {
    CurrentLevel++;
    level_up();
    EXPToNextLevel *= LEVELSCALAR;
    return true;
  }
  return false;
}

void PlayerCharacter::move_to_backpack(Item* item_to_move) noexcept {
  Backpack.push_back(item_to_move);
}

void PlayerCharacter::cleanup_backpack() noexcept {
  const auto to_remove = std::stable_partition(Backpack.begin(), Backpack.end(),
    [](const Item* i) -> bool { return !i->GetMarkedForDeletion(); }
  );
  std::for_each(to_remove, Backpack.end(), [](Item*& i) { ItemManager::DeleteItem(i); });
  Backpack.erase(to_remove, Backpack.end());
}

PlayerCharacter::PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {
  auto i = 0;
  for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
    EquippedArmor[i] = nullptr;
  }
  for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
    EquippedWeapons[i] = nullptr;
  }
}

PlayerCharacter::~PlayerCharacter() {
  delete pcclass;
  pcclass = nullptr;
  auto i = 0;
  for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
    if (EquippedArmor[i]) {
      ItemManager::DeleteItem(EquippedArmor[i]);
    }
  }
  for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
    if (EquippedWeapons[i]) {
      ItemManager::DeleteItem(EquippedWeapons[i]);
    }
  }
}

// Getters
[[nodiscard]] const leveltype PlayerCharacter::GetLevel() const noexcept { return pcclass->GetLevel(); }
[[nodiscard]] const exptype PlayerCharacter::getCurrentEXP() const noexcept { return pcclass->GetCurrentEXP(); }
[[nodiscard]] const exptype PlayerCharacter::getEXPToNextLevel() const noexcept { return pcclass->GetEXPToNextLevel(); }
[[nodiscard]] const bool PlayerCharacter::IsMaxHealth() const noexcept { return pcclass->HP->isFull(); }
[[nodiscard]] const welltype PlayerCharacter::getCurrentHP() const noexcept { return pcclass->HP->getCurrent(); }
[[nodiscard]] const welltype PlayerCharacter::getMaxHP() const noexcept { return pcclass->HP->getMax(); }
[[nodiscard]] const welltype PlayerCharacter::getCurrentMP() const noexcept {
  if (pcclass->MP)
    return pcclass->MP->getCurrent();
  else
    return 0;
}
[[nodiscard]] const welltype PlayerCharacter::getMaxMP() const noexcept {
  if (pcclass->MP)
    return pcclass->MP->getMax();
  else
    return 0;
}
[[nodiscard]] const stattype PlayerCharacter::getBaseStrength() const noexcept { return pcclass->getBaseStrength(); }
[[nodiscard]] const stattype PlayerCharacter::getBaseIntellect() const noexcept { return pcclass->getBaseIntellect(); }
[[nodiscard]] const stattype PlayerCharacter::getBaseAgility() const noexcept { return pcclass->getBaseAgility(); }
[[nodiscard]] const stattype PlayerCharacter::getBaseArmor() const noexcept { return pcclass->getBaseArmor(); }
[[nodiscard]] const stattype PlayerCharacter::getBaseElementRes() const noexcept { return pcclass->getBaseElementRes(); }
[[nodiscard]] const stattype PlayerCharacter::getTotalStrength() const noexcept {
  stattype str_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(EquippedArmor[i], armor);
      if (armor) {
        str_from_armor += armor->Stats.Strength;
      }
      armor = nullptr;
    }
  }
  stattype str_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(EquippedWeapons[i], weapon);
      if (weapon) {
        str_from_weapons += weapon->Stats.Strength;
      }
      weapon = nullptr;
    }
  }
  return pcclass->getTotalStrength() + str_from_armor + str_from_weapons;
}
[[nodiscard]] const stattype PlayerCharacter::getTotalIntellect() const noexcept {
  stattype int_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(EquippedArmor[i], armor);
      if (armor) {
        int_from_armor += armor->Stats.Intellect;
      }
      armor = nullptr;
    }
  }
  stattype int_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(EquippedWeapons[i], weapon);
      if (weapon) {
        int_from_weapons += weapon->Stats.Intellect;
      }
      weapon = nullptr;
    }
  }
  return pcclass->getTotalIntellect() + int_from_armor + int_from_weapons;
}
[[nodiscard]] const stattype PlayerCharacter::getTotalAgility() const noexcept {
  stattype agil_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(EquippedArmor[i], armor);
      if (armor) {
        agil_from_armor += armor->Stats.Agility;
      }
      armor = nullptr;
    }
  }
  stattype agil_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(EquippedWeapons[i], weapon);
      if (weapon) {
        agil_from_weapons += weapon->Stats.Agility;
      }
      weapon = nullptr;
    }
  }
  return pcclass->getTotalAgility() + agil_from_armor + agil_from_weapons;
}
[[nodiscard]] const stattype PlayerCharacter::getTotalArmor() const noexcept {
  // get all armor from equipped armor
  stattype armor_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(EquippedArmor[i], armor);
      if (armor) {
        armor_from_armor += armor->Stats.Armor;
      }
      armor = nullptr;
    }
  }
  stattype armor_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(EquippedWeapons[i], weapon);
      if (weapon) {
        armor_from_weapons += weapon->Stats.Armor;
      }
      weapon = nullptr;
    }
  }
  return pcclass->getTotalArmor() + armor_from_armor + armor_from_weapons;
}
[[nodiscard]] const stattype PlayerCharacter::getTotalElementRes() const noexcept {
  stattype resist_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(EquippedArmor[i], armor);
      if (armor) {
        resist_from_armor += armor->Stats.ElementRes;
      }
      armor = nullptr;
    }
  }
  stattype elres_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(EquippedWeapons[i], weapon);
      if (weapon) {
        elres_from_weapons += weapon->Stats.ElementRes;
      }
      weapon = nullptr;
    }
  }
  return pcclass->getTotalElementRes() + resist_from_armor + elres_from_weapons;
}
[[nodiscard]] const std::vector<Ability> PlayerCharacter::getAbilityList() const noexcept { return pcclass->Abilities; }
[[nodiscard]] const std::vector<Buff> PlayerCharacter::getBuffList() const noexcept { return pcclass->Buffs; }
[[nodiscard]] const std::vector<Item*> PlayerCharacter::getBackpackList() const noexcept { return Backpack; }
[[nodiscard]] const Armor* PlayerCharacter::getEquippedArmorAt(unsigned long long i) const noexcept {
  if (!EquippedArmor[i]) return nullptr;
  return (dynamic_cast<const Armor*>(EquippedArmor[i]->GetData()));
}
[[nodiscard]] const Weapon* PlayerCharacter::getEquippedWeaponAt(unsigned long long i) const noexcept {
  if (!EquippedWeapons[i]) return nullptr;
  return (dynamic_cast<const Weapon*>(EquippedWeapons[i]->GetData()));
}

// Modifiers
void PlayerCharacter::gainEXP(exptype amt) noexcept { pcclass->GiveEXP(amt); }
void PlayerCharacter::takeDamage(welltype amt) noexcept { pcclass->HP->reduceCurrent(amt); }
void PlayerCharacter::heal(welltype amt) noexcept { pcclass->HP->increaseCurrent(amt); }
void PlayerCharacter::applyBuff(Buff buff) noexcept {
  pcclass->Buffs.push_back(buff);
}