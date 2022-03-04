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

class EquipmentDelegate : public ItemDelegate {
public:
  const std::uint32_t UniqueId;
  CoreStats Stats;
protected:
  virtual ~EquipmentDelegate() = 0 {}
  EquipmentDelegate(std::string name, CoreStats cstats);
private:
};

// use this one in your runtime code
class Item final {
public:
  const ItemDelegate* GetData() { return _data; }
  bool GetMarkedForDeletion() const { return _marked_for_deletion; }
  bool GetMarkedAsBackpackRefGone() const { return _marked_as_backpack_ref_gone; }
private:
  ~Item() {   // only ItemManger can clean this up
    if (_data) {
      delete _data;
      _data = nullptr;
    }
  }
  ItemDelegate* _data;
  bool _marked_for_deletion = false;
  bool _marked_as_backpack_ref_gone = false;
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

