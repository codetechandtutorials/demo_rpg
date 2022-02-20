#pragma once
#include "types.h"
#include "item.h"


class ItemManager {
public:
  static Item* CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot) {
    Item* temp_item = new Item(new Armor(name, cstats, slot));
    return temp_item;
  }

  static Item* CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false) {
    Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
    return temp_item;
  }

  // makes at least 1 potion
  static Item* CreatePotion(std::string name, welltype heal = 1u, itemcount qaunt = 1u, Buff* buff = nullptr) {
    Item* temp_item = new Item(new Potion(name, heal, (qaunt == 0) ? 1 : qaunt, buff));
    return temp_item;
  }

  // Equips a weapon or armor and returns true, returns false if the action failed.
  // if an item was previously equipped in that slot, it will move to the character's backpack
  static bool Equip(Item* item_to_equip, PlayerCharacter* p_char) {
    if (!item_to_equip->GetData() || !item_to_equip || !p_char)
      return false;

    Armor* armor = dynamic_cast<Armor*>(item_to_equip->_data);
    if (armor) {
      unsigned long long slot_num = (unsigned long long)armor->Slot;
      if (p_char->EquippedArmor[slot_num]) {
        MoveToBackpack(p_char->EquippedArmor[slot_num], p_char);  // move old item to backpack
        p_char->EquippedArmor[slot_num] = item_to_equip;  // equip new item
      } else {
        p_char->EquippedArmor[slot_num] = item_to_equip;
      }
      return true;
    }

    Weapon* weapon = dynamic_cast<Weapon*>(item_to_equip->_data);
    if (weapon) {
      unsigned long long slot_num = (unsigned long long)weapon->Slot;
      if (p_char->EquippedWeapons[slot_num]) {
        MoveToBackpack(p_char->EquippedWeapons[slot_num], p_char);  // move old item to backpack
        p_char->EquippedWeapons[slot_num] = item_to_equip;  // equip new item
      }
      else {
        p_char->EquippedWeapons[slot_num] = item_to_equip;
      }
      return true;
    }

    return false;

  }

  static bool Use(Item* item_to_use, PlayerCharacter* p_char) {
    if (!item_to_use->GetData() || !item_to_use || !p_char)
      return false;

    Potion* potion = dynamic_cast<Potion*>(item_to_use->_data);
    if (potion) {
      // apply buff if it has one
      if (potion->buff) {
        p_char->applyBuff(*potion->buff);
      }

      // if max health and trying to use a heal potion, don't use it
      if (p_char->pcclass->HP->isFull() && !potion->buff)
        return false; // don't use the potion

      // increase hp by the heal amount (could be 0 and that's fine)
      p_char->pcclass->HP->increaseCurrent(potion->HealAmount);

      // we used the potion, reduce quantity
      potion->Quantity--;

      if (potion->Quantity == 0) {
        item_to_use->marked_for_deletion = true;
        p_char->cleanup_backpack();
      }
      return true;
    }

    return false;
  }

  static bool MoveToBackpack(Item* item_to_move, PlayerCharacter* p_char) {
    if (!item_to_move->GetData() || !item_to_move || !p_char)
      return false;
    p_char->Backpack.push_back(item_to_move);
    return true;
  }

};
