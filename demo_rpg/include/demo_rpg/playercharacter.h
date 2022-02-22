#pragma once
#include "types.h"
#include "statblock.h"
#include "pointwell.h"
#include "ability.h"
#include "item.h"
#include "buff.h"
#include "item_manager.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

class ItemManager;

#define PCCONSTRUCT \
HP->setMax(BASEHP);\
HP->increaseCurrent(BASEHP);\
if (MP) { \
  MP->setMax(BASEMP); \
  MP->increaseCurrent(BASEMP); \
}\
increaseStats(BASESTR, BASEINT, BASEAGI);

#define LEVELUP \
HP->setMax((welltype)((BASEHP / 2.f) + HP->getMax()));\
HP->increaseCurrent((welltype)(BASEHP / 2.f));\
if (MP) {\
  MP->setMax((welltype)((BASEMP / 2.f) + HP->getMax()));\
  MP->increaseCurrent((welltype)(BASEMP / 2.f));\
}\
increaseStats((stattype)((BASESTR + 1u) / 2.f), (stattype)((BASEINT + 1u) / 2.f), (stattype)((BASEAGI + 1u) / 2.f));

class PlayerCharacterDelegate : public StatBlock {
public:
  static const exptype LEVEL2AT = 100u;

  PlayerCharacterDelegate() : StatBlock(0u, 0u) {
    CurrentLevel = (leveltype)1u;
    CurrentEXP = (exptype)0u;
    EXPToNextLevel = LEVEL2AT;
    HP = std::make_unique<PointWell>(1u, 1u);
  }

  void gainEXP(exptype gained_exp) {
    CurrentEXP += gained_exp;
    while (check_if_leveled()) {}
  }

  leveltype getLevel() {
    return CurrentLevel;
  }

  exptype getCurrentEXP() {
    return CurrentEXP;
  }

  exptype getEXPToNextLevel() {
    return EXPToNextLevel;
  }

  void applyBuff(Buff b) {
    addNewBuff(b);
  }

  std::vector<Buff> getBuffList() {
    return Buffs;
  }

  virtual void LevelUp() = 0;
  virtual std::string getClassName() = 0;

  std::unique_ptr<PointWell> HP;
  std::unique_ptr<PointWell> MP;

  std::vector<Ability> Abilities;

protected:
  leveltype CurrentLevel;
  exptype CurrentEXP;
  exptype EXPToNextLevel;

  bool check_if_leveled() {
    static const leveltype LEVELSCALAR = 2u;
    if (CurrentEXP >= EXPToNextLevel) {
      CurrentLevel++;
      LevelUp();
      EXPToNextLevel *= LEVELSCALAR;
      return true;
    }
    return false;
  }
};

class Cleric : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = (welltype)14u;
  static const welltype BASEMP = (welltype)10u;
  static const stattype BASESTR = (stattype)3u;
  static const stattype BASEINT = (stattype)5u;
  static const stattype BASEAGI = (stattype)1u;
  std::string getClassName() override { return std::string("Cleric"); }
  Cleric() : PlayerCharacterDelegate() {
    MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
    PCCONSTRUCT

      Abilities.emplace_back("Heal", 2u, nullptr, 2u, 1u, ABILITYTARGET::ALLY, ABILITYSCALER::INT);
  }
private:
  void LevelUp() override {
    LEVELUP
      if (CurrentLevel == 2) {
        Abilities.emplace_back("Smite", 2u, nullptr, 2u, 1u, ABILITYTARGET::ENEMY, ABILITYSCALER::INT);
      }
  }
};

class Wizard : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = (welltype)10u;
  static const welltype BASEMP = (welltype)14u;
  static const stattype BASESTR = (stattype)1u;
  static const stattype BASEINT = (stattype)8u;
  static const stattype BASEAGI = (stattype)2u;
  std::string getClassName() override { return std::string("Wizard"); }
  Wizard() : PlayerCharacterDelegate() {
    MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
    PCCONSTRUCT
      Abilities.emplace_back("Firebolt", 4u, nullptr, 2u, 1u, ABILITYTARGET::ENEMY, ABILITYSCALER::INT);
  }
private:
  void LevelUp() override {
    LEVELUP
      if (CurrentLevel == 2) {
        Abilities.emplace_back("IceBolt", 6u, nullptr, 3u, 1u, ABILITYTARGET::ENEMY, ABILITYSCALER::INT);

        MP->setMax(1u + MP->getMax());
        MP->increaseCurrent(1u);

        increaseStats(0, 1);
      }
  }
};

class Warrior : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = (welltype)18u;
  static const welltype BASEMP = (welltype)0u;
  static const stattype BASESTR = (stattype)6u;
  static const stattype BASEINT = (stattype)2u;
  static const stattype BASEAGI = (stattype)2u;
  std::string getClassName() override { return std::string("Warrior"); }
  Warrior() : PlayerCharacterDelegate() {
    //MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
    PCCONSTRUCT

  }
private:
  void LevelUp() override {
    LEVELUP
      if (CurrentLevel == 2) {
        Abilities.emplace_back("PowerAttack", 4u, nullptr, 0u, 3u, ABILITYTARGET::ENEMY, ABILITYSCALER::STR);
      }
  }
};

class Rogue : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = (welltype)12u;
  static const welltype BASEMP = (welltype)0u;
  static const stattype BASESTR = (stattype)3u;
  static const stattype BASEINT = (stattype)3u;
  static const stattype BASEAGI = (stattype)6u;
  std::string getClassName() override { return std::string("Rogue"); }
  Rogue() : PlayerCharacterDelegate() {
    //MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
    PCCONSTRUCT

  }
private:
  void LevelUp() override {
    LEVELUP
      if (CurrentLevel == 2) {
        Abilities.emplace_back("PreciseAttack", 6u, nullptr, 0u, 3u, ABILITYTARGET::ENEMY, ABILITYSCALER::AGI);
      }
  }
};

class PlayerCharacter {
private:
  PlayerCharacterDelegate* pcclass;
  Item* EquippedArmor[(unsigned long long)ARMORSLOT::NUM_SLOTS];
  Item* EquippedWeapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
  std::vector<Item*> Backpack;
  void cleanup_backpack() {
    const auto to_remove = std::stable_partition(Backpack.begin(), Backpack.end(),
      [](const Item* i) -> bool { return !i->GetMarkedForDeletion(); }
    );
    std::for_each(to_remove, Backpack.end(), [](Item* i) { delete i; });
    Backpack.erase(to_remove, Backpack.end());
  }
  friend class ItemManager;

public:
  PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {
    auto i = 0;
    for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      EquippedArmor[i] = nullptr;
    }
    for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      EquippedWeapons[i] = nullptr;
    }
  }
  ~PlayerCharacter() {
    delete pcclass;
    pcclass = nullptr;
    auto i = 0;
    for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      if (EquippedArmor[i]) {
        delete EquippedArmor[i];
        EquippedArmor[i] = nullptr;
      }
    }
    for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      if (EquippedWeapons[i]) {
        delete EquippedWeapons[i];
        EquippedWeapons[i] = nullptr;
      }
    }
  }

  // Getters
  const std::string getClassName() const { return pcclass->getClassName(); }
  const leveltype getLevel() const { return pcclass->getLevel(); }
  const exptype getCurrentEXP() const { return pcclass->getCurrentEXP(); }
  const exptype getEXPToNextLevel() const { return pcclass->getEXPToNextLevel(); }
  const welltype getCurrentHP() const { return pcclass->HP->getCurrent(); }
  const welltype getMaxHP() const { return pcclass->HP->getMax(); }
  const welltype getCurrentMP() const {
    if (pcclass->MP)
      return pcclass->MP->getCurrent();
    else
      return 0;
  }
  const welltype getMaxMP() const {
    if (pcclass->MP)
      return pcclass->MP->getMax();
    else
      return 0;
  }
  const stattype getBaseStrength() const { return pcclass->getBaseStrength(); }
  const stattype getBaseIntellect() const { return pcclass->getBaseIntellect(); }
  const stattype getBaseAgility() const { return pcclass->getBaseAgility(); }
  const stattype getBaseArmor() const { return pcclass->getBaseArmor(); }
  const stattype getBaseElementRes() const { return pcclass->getBaseElementRes(); }
  const stattype getTotalStrength() const {
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
  const stattype getTotalIntellect() const {
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
  const stattype getTotalAgility() const {
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
  const stattype getTotalArmor() {
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
  const stattype getTotalElementRes() const {
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
  const std::vector<Ability> getAbilityList() const { return pcclass->Abilities; }
  const std::vector<Buff> getBuffList() const { return pcclass->getBuffList(); }
  const std::vector<Item*> getBackpackList() const { return Backpack; }
  const Armor* getEquippedArmorAt(unsigned long long i) const {
    if (!EquippedArmor[i]) return nullptr;
    return (dynamic_cast<const Armor*>(EquippedArmor[i]->GetData()));
  }
  const Weapon* getEquippedWeaponAt(unsigned long long i) const {
    if (!EquippedWeapons[i]) return nullptr;
    return (dynamic_cast<const Weapon*>(EquippedWeapons[i]->GetData()));
  }

  // Modifiers
  void gainEXP(exptype amt) { pcclass->gainEXP(amt); }
  void takeDamage(welltype amt) { pcclass->HP->reduceCurrent(amt); }
  void heal(welltype amt) { pcclass->HP->increaseCurrent(amt); }
  void applyBuff(Buff buff) {
    pcclass->applyBuff(buff);
  }

  // deleted constructors
  PlayerCharacter() = delete;
  PlayerCharacter(const PlayerCharacter&) = delete;
  PlayerCharacter(const PlayerCharacter&&) = delete;
};