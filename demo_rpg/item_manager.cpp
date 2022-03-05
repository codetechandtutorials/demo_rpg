#include "item_manager.h"
#include "playercharacter.h"
#include "potion.h"
#include "armor.h"
#include "weapon.h"

[[nodiscard]] Item* ItemManager::CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot) {
  Item* temp_item = new Item(new Armor(name, cstats, slot));
  return temp_item;
}
void ItemManager::CastItemToArmor(const Item* in, Armor*& out) {
  if (!in) return;
  out = dynamic_cast<Armor*>(in->_data);
}
bool ItemManager::IsItemArmor(const Item* in) {
  if (dynamic_cast<Armor*>(in->_data)) return true;
  else return false;
}



[[nodiscard]] Item* ItemManager::CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded) {
  Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
  return temp_item;
}
void ItemManager::CastItemToWeapon(const Item* in, Weapon*& out) {
  if (!in) return;
  out = dynamic_cast<Weapon*>(in->_data);
}
bool ItemManager::IsItemWeapon(const Item* in) {
  if (dynamic_cast<Weapon*>(in->_data)) return true;
  else return false;
}



[[nodiscard]] Item* ItemManager::CreatePotion(std::string name, welltype Heal, itemcount qaunt, Buff* _buff) {
  Item* temp_item = new Item(new Potion(name, Heal, (qaunt == 0) ? 1 : qaunt, _buff));
  return temp_item;
}
void ItemManager::CastItemToPotion(const Item* in, Potion*& out) {
  if (!in) return;
  out = dynamic_cast<Potion*>(in->_data);
}
bool ItemManager::IsItemPotion(const Item* in) {
  if (dynamic_cast<Potion*>(in->_data)) return true;
  else return false;
}



// character item helpers
// returns true if equip was successful
bool ItemManager::Equip(Item* item_to_equip, PlayerCharacter* p_char) {
  if (!item_to_equip->GetData() || !item_to_equip || !p_char)
    return false;

  if (IsItemPotion(item_to_equip))
    return false;

  Armor* armor = dynamic_cast<Armor*>(item_to_equip->_data);
  if (armor) {
    unsigned long long slot_num = (unsigned long long)armor->Slot;
    if (p_char->_equipped_armor[slot_num]) {
      p_char->_equipped_armor[slot_num]->_marked_as_backpack_ref_gone = false;
      MoveToBackpack(p_char->_equipped_armor[slot_num], p_char);  // move old item to backpack
      p_char->_equipped_armor[slot_num] = item_to_equip;  // equip new item
      item_to_equip->_marked_as_backpack_ref_gone = true;
    } else {
      p_char->_equipped_armor[slot_num] = item_to_equip;
      item_to_equip->_marked_as_backpack_ref_gone = true;
    }
    p_char->cleanup_backpack();  // get rid of pointers in backpack that are now equipped
    return true;
  }

  Weapon* weapon = dynamic_cast<Weapon*>(item_to_equip->_data);
  if (weapon) {
    unsigned long long slot_num = (unsigned long long)weapon->Slot;
    if (p_char->_equipped_weapons[slot_num]) {
      p_char->_equipped_weapons[slot_num]->_marked_as_backpack_ref_gone = false;
      MoveToBackpack(p_char->_equipped_weapons[slot_num], p_char);  // move old item to backpack
      p_char->_equipped_weapons[slot_num] = item_to_equip;  // equip new item
      item_to_equip->_marked_as_backpack_ref_gone = true;
    } else {
      p_char->_equipped_weapons[slot_num] = item_to_equip;
      item_to_equip->_marked_as_backpack_ref_gone = true;
    }
    p_char->cleanup_backpack();  // get rid of pointers in backpack that are now equipped
    return true;
  }

  return false;

}


// returns true if the potion was used, false otherwise
bool ItemManager::Use(Item* item_to_use, PlayerCharacter* p_char) {
  if (!item_to_use->GetData() || !item_to_use || !p_char)
    return false;

  Potion* potion = nullptr;
  CastItemToPotion(item_to_use, potion);

  if (potion && potion->Quantity > 0) {
    // apply buff if it has one
    if (potion->_buff) {
      if (potion->_buff->isDebuff) {
        p_char->TakeDamage(potion->HealAmount);
      }
      p_char->ApplyBuff(*potion->_buff);
    } else {  // healing potion only, no buff/debuff, only use if not already max health 
      if (p_char->IsMaxHealth()) { return false; } else { p_char->Heal(potion->HealAmount); }
    }

    // we used the potion, reduce quantity
    potion->Quantity--;
    if (potion->Quantity == 0) {
      item_to_use->_marked_for_deletion = true;
      p_char->cleanup_backpack();  // assumes using it out of player inventory (todo: refactor)
    }
    return true;
  }
  return false;
}

bool ItemManager::MoveToBackpack(Item* item_to_move, PlayerCharacter* p_char) {
  if (!item_to_move || !p_char)
    return false;
  if (!item_to_move->GetData())
    return false;

  p_char->move_to_backpack(item_to_move);
  return true;
}

void ItemManager::DeleteItem(Item*& item_to_delete/*, std::vector<Item*>& pack_to_delete_from*/) {
  delete item_to_delete;
  item_to_delete = nullptr;
}
