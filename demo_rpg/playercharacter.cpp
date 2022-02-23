#include "playercharacter.h"
#include <memory>

PlayerCharacterDelegate::~PlayerCharacterDelegate() {}

PlayerCharacterDelegate::PlayerCharacterDelegate() : StatBlock(0u, 0u) {
  CurrentLevel = (leveltype)1u;
  CurrentEXP = (exptype)0u;
  EXPToNextLevel = LEVEL2AT;
  HP = std::make_unique<PointWell>(1u, 1u);
}

void PlayerCharacterDelegate::gainEXP(exptype gained_exp) {
  CurrentEXP += gained_exp;
  while (check_if_leveled()) {}
}

leveltype PlayerCharacterDelegate::getLevel() const {
  return CurrentLevel;
}

exptype PlayerCharacterDelegate::getCurrentEXP() const {
  return CurrentEXP;
}

exptype PlayerCharacterDelegate::getEXPToNextLevel() const {
  return EXPToNextLevel;
}

const std::vector<Buff>& PlayerCharacterDelegate::getBuffList() const {
  return Buffs;
}

void PlayerCharacterDelegate::applyBuff(Buff b) {
  addNewBuff(b);
}


bool PlayerCharacterDelegate::check_if_leveled() {
  static const leveltype LEVELSCALAR = 2u;
  if (CurrentEXP >= EXPToNextLevel) {
    CurrentLevel++;
    level_up();
    EXPToNextLevel *= LEVELSCALAR;
    return true;
  }
  return false;
}


void PlayerCharacter::cleanup_backpack() {
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
const leveltype PlayerCharacter::getLevel() const { return pcclass->getLevel(); }
const exptype PlayerCharacter::getCurrentEXP() const { return pcclass->getCurrentEXP(); }
const exptype PlayerCharacter::getEXPToNextLevel() const { return pcclass->getEXPToNextLevel(); }
const bool PlayerCharacter::IsMaxHealth() const { return pcclass->HP->isFull(); }
const welltype PlayerCharacter::getCurrentHP() const { return pcclass->HP->getCurrent(); }
const welltype PlayerCharacter::getMaxHP() const { return pcclass->HP->getMax(); }
const welltype PlayerCharacter::getCurrentMP() const {
  if (pcclass->MP)
    return pcclass->MP->getCurrent();
  else
    return 0;
}
const welltype PlayerCharacter::getMaxMP() const {
  if (pcclass->MP)
    return pcclass->MP->getMax();
  else
    return 0;
}
const stattype PlayerCharacter::getBaseStrength() const { return pcclass->getBaseStrength(); }
const stattype PlayerCharacter::getBaseIntellect() const { return pcclass->getBaseIntellect(); }
const stattype PlayerCharacter::getBaseAgility() const { return pcclass->getBaseAgility(); }
const stattype PlayerCharacter::getBaseArmor() const { return pcclass->getBaseArmor(); }
const stattype PlayerCharacter::getBaseElementRes() const { return pcclass->getBaseElementRes(); }
const stattype PlayerCharacter::getTotalStrength() const {
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
const stattype PlayerCharacter::getTotalIntellect() const {
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
const stattype PlayerCharacter::getTotalAgility() const {
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
const stattype PlayerCharacter::getTotalArmor() const {
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
const stattype PlayerCharacter::getTotalElementRes() const {
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
const std::vector<Ability> PlayerCharacter::getAbilityList() const { return pcclass->Abilities; }
const std::vector<Buff> PlayerCharacter::getBuffList() const { return pcclass->getBuffList(); }
const std::vector<Item*> PlayerCharacter::getBackpackList() const { return Backpack; }
const Armor* PlayerCharacter::getEquippedArmorAt(unsigned long long i) const {
  if (!EquippedArmor[i]) return nullptr;
  return (dynamic_cast<const Armor*>(EquippedArmor[i]->GetData()));
}
const Weapon* PlayerCharacter::getEquippedWeaponAt(unsigned long long i) const {
  if (!EquippedWeapons[i]) return nullptr;
  return (dynamic_cast<const Weapon*>(EquippedWeapons[i]->GetData()));
}

// Modifiers
void PlayerCharacter::gainEXP(exptype amt) { pcclass->gainEXP(amt); }
void PlayerCharacter::takeDamage(welltype amt) { pcclass->HP->reduceCurrent(amt); }
void PlayerCharacter::heal(welltype amt) { pcclass->HP->increaseCurrent(amt); }
void PlayerCharacter::applyBuff(Buff buff) {
  pcclass->applyBuff(buff);
}