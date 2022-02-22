#pragma once
#include "item.h"
#include "corestats.h"
#include <string>

enum class ARMORSLOT { HEAD, CHEST, LEGS, FEET, HANDS, RING1, RING2, NECK, NUM_SLOTS };
class Armor final : public EquipmentDelegate {
public:
  ARMORSLOT Slot;
private:
  Armor(std::string name, CoreStats cstats, ARMORSLOT slot);
  Armor() = delete;
  Armor(const Armor&) = delete;
  Armor(const Armor&&) = delete;
  ~Armor(); // only ItemManger can clean this up
  friend class ItemManager;
};