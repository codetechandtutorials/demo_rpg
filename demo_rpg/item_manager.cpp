#include "item_manager.h"
#include "playercharacter.h"
#include "potion.h"
#include "armor.h"
#include "weapon.h"

Item* ItemManager::CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot) {
  Item* temp_item = new Item(new Armor(name, cstats, slot));
  return temp_item;
}
void ItemManager::CastItemToArmor(const Item* in, Armor*& out) {
  out = dynamic_cast<Armor*>(in->_data);
}
bool ItemManager::IsItemArmor(const Item* in) {
  if (dynamic_cast<Armor*>(in->_data)) return true;
  else return false;
}



Item* ItemManager::CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded) {
  Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
  return temp_item;
}
void ItemManager::CastItemToWeapon(const Item* in, Weapon*& out) {
  out = dynamic_cast<Weapon*>(in->_data);
}
bool ItemManager::IsItemWeapon(const Item* in) {
  if (dynamic_cast<Weapon*>(in->_data)) return true;
  else return false;
}



Item* ItemManager::CreatePotion(std::string name, welltype heal, itemcount qaunt, Buff* buff) {
  Item* temp_item = new Item(new Potion(name, heal, (qaunt == 0) ? 1 : qaunt, buff));
  return temp_item;
}
void ItemManager::CastItemToPotion(const Item* in, Potion*& out) {
  out = dynamic_cast<Potion*>(in->_data);
}
bool ItemManager::IsItemPotion(const Item* in) {
  if (dynamic_cast<Potion*>(in->_data)) return true;
  else return false;
}



// character item helpers
bool ItemManager::Equip(Item* item_to_equip, PlayerCharacter* p_char) {
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
    } else {
      p_char->EquippedWeapons[slot_num] = item_to_equip;
    }
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
    if (potion->buff) {
      if (potion->buff->isDebuff) {
        p_char->takeDamage(potion->HealAmount);
      }
      p_char->applyBuff(*potion->buff);
    } else {  // healing potion only, no buff/debuff, only use if not already max health 
      if (p_char->IsMaxHealth()) { return false; } else { p_char->heal(potion->HealAmount); }
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
  if (!item_to_move->GetData() || !item_to_move || !p_char)
    return false;
  p_char->Backpack.push_back(item_to_move);
  return true;
}

void ItemManager::DeleteItem(Item*& item_to_delete/*, std::vector<Item*>& pack_to_delete_from*/) {
  delete item_to_delete;
  item_to_delete = nullptr;
}
