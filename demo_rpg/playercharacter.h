#pragma once
#include "statblock.h"
#include "pointwell.h"
#include "ability.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
typedef std::uint64_t exptype;
typedef std::uint16_t leveltype;

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

    Abilities.emplace_back("Heal", 2u, 1u, ABILITYTARGET::ALLY, 2u, ABILITYSCALER::INT);
  }
private:
  void LevelUp() override {
    LEVELUP
    if (CurrentLevel == 2) {
      Abilities.emplace_back("Smite", 2u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALER::INT);
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
      Abilities.emplace_back("Firebolt", 2u, 1u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::INT);
  }
private:
  void LevelUp() override {
    LEVELUP
      if (CurrentLevel == 2) {
        Abilities.emplace_back("IceBolt", 3u, 1u, ABILITYTARGET::ENEMY, 6u, ABILITYSCALER::INT);

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
        Abilities.emplace_back("PowerAttack", 0u, 3u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::STR);
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
        Abilities.emplace_back("PreciseAttack", 0u, 3u, ABILITYTARGET::ENEMY, 6u, ABILITYSCALER::AGI);
      }
  }
};


class PlayerCharacter {
private:
  PlayerCharacterDelegate* pcclass;

public:
  PlayerCharacter() = delete;
  PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {}
  ~PlayerCharacter() { delete pcclass; pcclass = nullptr; }

  std::string getClassName() { return pcclass->getClassName(); }
  leveltype getLevel() { return pcclass->getLevel(); }
  exptype getCurrentEXP() { return pcclass->getCurrentEXP(); }
  exptype getEXPToNextLevel() { return pcclass->getEXPToNextLevel(); }
  welltype getCurrentHP() { return pcclass->HP->getCurrent(); }
  welltype getMaxHP() { return pcclass->HP->getMax(); }

  welltype getCurrentMP() { 
    if (pcclass->MP)
      return pcclass->MP->getCurrent();
    else
      return 0;
  }
  welltype getMaxMP() {
    if (pcclass->MP)
      return pcclass->MP->getMax();
    else
      return 0;
  }

  stattype getStrength() { return pcclass->getStrength(); }
  stattype getIntellect() { return pcclass->getIntellect(); }
  stattype getAgility() { return pcclass->getAgility(); }
  stattype getArmor() { return pcclass->getArmor(); }
  stattype getElementRes() { return pcclass->getElementRes(); }

  std::vector<Ability> getAbilityList() { return pcclass->Abilities; }

  void gainEXP(exptype amt) { pcclass->gainEXP(amt); }
  void takeDamage(welltype amt) { pcclass->HP->reduceCurrent(amt); }
  void heal(welltype amt) { pcclass->HP->increaseCurrent(amt); }
};