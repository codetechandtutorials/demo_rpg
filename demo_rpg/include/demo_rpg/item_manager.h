#pragma once
#include "corestats.h"
#include "item.h"
#include "armor.h"
#include "weapon.h"

class Potion;
class Armor;
class Weapon;
class PlayerCharacter;

class ItemManager {
public:
  static Item* CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot);

  // out will be nullptr if this cast fails
  static void CastItemToArmor(const Item* in, Armor*& out);

  // returns true if Item is Armor, false otherwise
  static bool IsItemArmor(const Item* in);

  static Item* CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false);

  // out will be nullptr if this cast fails
  static void CastItemToWeapon(const Item* in, Weapon*& out);

  // returns true if Item in is a Weapon, false otherwise
  static bool IsItemWeapon(const Item* in);

  // makes at least 1 potion
  static Item* CreatePotion(std::string name, welltype Heal = 1u, itemcount qaunt = 1u, Buff* _buff = nullptr);

  // out will be nullptr if this cast fails
  static void CastItemToPotion(const Item* in, Potion*& out);

  // returns true if Item is Potion, false otherwise
  static bool IsItemPotion(const Item* in);

  // Equips a weapon or armor and returns true, returns false if the action failed.
  // if an item was previously equipped in that slot, it will move to the character's backpack
  static bool Equip(Item* item_to_equip, PlayerCharacter* p_char);

  static bool Use(Item* item_to_use, PlayerCharacter* p_char);

  static bool MoveToBackpack(Item* item_to_move, PlayerCharacter* p_char);

  static void DeleteItem(Item*& item_to_delete/*, std::vector<Item*>& pack_to_delete_from*/);
};
