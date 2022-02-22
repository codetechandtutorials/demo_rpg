#pragma once
#include "corestats.h"
#include "buff.h"
#include <string>
#include <typeinfo>

class ItemDelegate {
public:
  std::string Name;
protected:
  virtual ~ItemDelegate() = 0 {}
  ItemDelegate(std::string name) : Name(name) {}
  friend class Item;
};

class Potion final : public ItemDelegate {
public:
  Buff* buff;
  welltype HealAmount;
  itemcount Quantity;

  ~Potion() {
    if (buff) {
      delete buff;
      buff = nullptr;
    }
  }

private:
  Potion(std::string name, welltype hp_heal = 1u, itemcount quant = 1u, Buff* buf = nullptr)
    : ItemDelegate(name), buff(buf), HealAmount(hp_heal), Quantity(quant) {
  }

  friend class ItemManager;
};

class EquipmentDelegate : public ItemDelegate {
public:
  const std::uint32_t UniqueId;
  CoreStats Stats;
protected:
  virtual ~EquipmentDelegate() = 0 {}
  EquipmentDelegate(std::string name, CoreStats cstats);
private:
};

enum class ARMORSLOT { HELMET, CHEST, LEGS, BOOTS, GLOVES, RING1, RING2, NECK, NUM_SLOTS };  // NUM SLOTS FOR MAKING ARRAYS OF ARMOR SLOTS
class Armor final : public EquipmentDelegate {
public:
  ARMORSLOT Slot;
private:
  Armor(std::string name, CoreStats cstats, ARMORSLOT slot) : EquipmentDelegate(name, cstats), Slot(slot) {}
  Armor() = delete;
  Armor(const Armor&) = delete;
  Armor(const Armor&&) = delete;

  friend class ItemManager;

};

enum class WEAPONSLOT { MELEE, RANGED, NUM_SLOTS };
class Weapon final : public EquipmentDelegate {
public:
  WEAPONSLOT Slot;
  damagetype MinDamage;
  damagetype MaxDamage;
  bool is2H;

private:
  Weapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false)
    : EquipmentDelegate(name, cstats), Slot(slot), MinDamage(min), MaxDamage(max), is2H(twohanded) {
  }

  Weapon() = delete;
  Weapon(const Weapon&) = delete;
  Weapon(const Weapon&&) = delete;

  friend class ItemManager;
};




//#include <iostream>  // for testing
// use this one in your runtime code
class Item {
public:
  const ItemDelegate* GetData() { return _data; }
  bool GetMarkedForDeletion() const { return _marked_for_deletion; }

  ~Item() {
    if (_data) {
      delete _data;
      _data = nullptr;
    }
  }
private:
  ItemDelegate* _data;
  bool _marked_for_deletion = false;
  Item(ItemDelegate* item) : _data(item) {}
  friend class ItemManager;

  //friend std::ostream& operator<<(std::ostream& os, const Item& t) {
  //  Armor* tmp_cast = dynamic_cast<Armor*>(t._data);
  //  if (tmp_cast) {
  //    return os << tmp_cast->Name << "(Armor: " << tmp_cast->Stats.Armor << ", Resist: " << tmp_cast->Stats.ElementRes << ')';
  //  }
  //  Weapon* tmp_cast2 = dynamic_cast<Weapon*>(t._data);
  //  if (tmp_cast2) {
  //    return  os << tmp_cast2->Name << "(Damage: " << tmp_cast2->MinDamage << '-' << tmp_cast2->MaxDamage << ')';
  //  }
  //  Potion* tmp_cast3 = dynamic_cast<Potion*>(t._data);
  //  if (tmp_cast3) {
  //    return os << tmp_cast3->Name << '(' << tmp_cast3->Quantity << ')';
  //  }
  //  return os;
  //}

};

