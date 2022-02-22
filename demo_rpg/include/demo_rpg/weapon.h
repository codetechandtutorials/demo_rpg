#pragma once
#include "types.h"
#include "item.h"
#include "corestats.h"
#include <string>

enum class WEAPONSLOT { MELEE, RANGED, NUM_SLOTS };
class Weapon final : public EquipmentDelegate {
public:
  WEAPONSLOT Slot;
  damagetype MinDamage;
  damagetype MaxDamage;
  bool is2H;
private:
  Weapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false);
  Weapon() = delete;
  Weapon(const Weapon&) = delete;
  Weapon(const Weapon&&) = delete;
  ~Weapon();  // only ItemManger can clean this up
  friend class ItemManager;
};
