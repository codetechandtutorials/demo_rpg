#pragma once
#include "corestats.h"
#include <string>
#include <typeinfo>

class Equipment {
public:
  std::string Name;
  CoreStats Stats;
  virtual const char* GetType() = 0;
protected:
  Equipment(std::string name, CoreStats cstats) : Name(name), Stats(cstats) {}
private:
};

enum class ARMORSLOT { HELMET, CHEST, LEGS, BOOTS, GLOVES, RING1, RING2, NECK, NUM_SLOTS };  // NUM SLOTS FOR MAKING ARRAYS OF ARMOR SLOTS
class Armor final : public Equipment {
public:
  ARMORSLOT Slot;

  Armor(std::string name, CoreStats cstats, ARMORSLOT slot) : Equipment(name, cstats), Slot(slot) {}

  const char* GetType() override { return typeid(*this).name(); };

  Armor() = delete;
  Armor(const Armor&) = delete;
  Armor(const Armor&&) = delete;

private:
};

enum class WEAPONSLOT { MELEE, RANGED, NUM_SLOTS };
class Weapon final : public Equipment {
public:
  WEAPONSLOT Slot;
  damagetype MinDamage;
  damagetype MaxDamage;
  bool is2H;
  Weapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false)
    : Equipment(name, cstats), Slot(slot), MinDamage(min), MaxDamage(max), is2H(twohanded) {
  }
  const char* GetType() override { return typeid(*this).name(); };

  Weapon() = delete;
  Weapon(const Weapon&) = delete;
  Weapon(const Weapon&&) = delete;
};