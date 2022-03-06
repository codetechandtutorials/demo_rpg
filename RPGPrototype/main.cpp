#include "pch.h"
#include "demo_rpg/random.h"
#include "demo_rpg/item.h"
#include "demo_rpg/item_manager.h"
#include <iostream>

Player* MainCharacter = nullptr;
Fightable* CurrentMonster = nullptr;
int monsters_defeated = 0;

void display_character_sheet() {
  system("CLS");
  std::cout
    << "Your Character\n"
    << "L: " << MainCharacter->us.GetLevel() << " XP: " << MainCharacter->us.GetCurrentEXP() << " NEXT: " << MainCharacter->us.GetEXPToNextLevel() << '\n'
    << "Hit Points: " << MainCharacter->us.GetCurrentHP() << "/" << MainCharacter->us.GetMaxHP() << '\n'
    << "Armor: " << MainCharacter->us.GetTotalArmor() << "  Resistance: " << MainCharacter->us.GetTotalElementRes() << '\n'
    << "STR: " << MainCharacter->us.GetTotalStrength() << " AGI: " << MainCharacter->us.GetTotalAgility() << " INT: " << MainCharacter->us.GetTotalIntellect() << '\n'
    << "\n\nEquipped Gear\n";
  if (MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)) {
    std::string weapon_name = MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->Name;
    std::cout << "MELEE: " << weapon_name << "  damage(" << MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->MinDamage << '-' << MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->MaxDamage << ")\n";
  }
  if (MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)) {
    std::string weapon_name = MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->Name;
    std::cout << "RANGED: " << weapon_name << "  damage(" << MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->MinDamage << '-' << MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->MaxDamage << ")\n";
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HEAD)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HEAD)->Name;
    std::cout << "HEAD: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::NECK)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::NECK)->Name;
    std::cout << "NECK: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST)->Name;
    std::cout << "CHEST: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HANDS)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HANDS)->Name;
    std::cout << "HANDS: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING1)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING1)->Name;
    std::cout << "RING1: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING2)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING2)->Name;
    std::cout << "RING2: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::LEGS)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::LEGS)->Name;
    std::cout << "LEGS: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::FEET)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::FEET)->Name;
    std::cout << "FEET: " << armor_name << '\n';
  }

  std::cin.ignore(100, '\n');
  std::cout << "\n press enter to continue\n";
  char c = getchar();
}

void open_inventory() {
  bool done = false;
  int selected_item_num = 0;
  while (!done) {
    system("CLS");
    auto list_of_items = MainCharacter->us.GetBackpackList();
    std::cout
      << "CURRENT INVENTORY\n"
      << "-----------------\n\n";
    int items_in_backpack_count = 0;
    for (const auto& item : list_of_items) {
      if (selected_item_num == items_in_backpack_count)
        std::cout << "> ";
      else
        std::cout << "  ";
      std::cout << item->GetData()->Name << '\n';
      if (ItemManager::IsItemPotion(item)) {
        Potion* potion = nullptr;
        ItemManager::CastItemToPotion(item, potion);
        if (potion)
          std::cout << "    Quantity: " << potion->Quantity << '\n';
      }
      items_in_backpack_count++;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n d = done, w = up, s = down, u = use/equip current\n";
    char c = getchar();
    switch (c) {
    case 'd':
      done = true;
      break;
    case 'w':
      selected_item_num--;
      if (selected_item_num < 0)
        selected_item_num = 0;
      break;
    case 's':
      selected_item_num++;
      if (selected_item_num > list_of_items.size() - 1)
        selected_item_num = (int)list_of_items.size() - 1;
      break;
    case 'u':
      if (list_of_items.empty())
        continue;
      if (ItemManager::IsItemPotion(list_of_items[selected_item_num]))
        ItemManager::Use(list_of_items[selected_item_num], &(MainCharacter->us));
      else
        ItemManager::Equip(list_of_items[selected_item_num], &(MainCharacter->us));
      break;
    default:
      break;
    }
  }

}

bool combat_inventory() {
  bool done = false;
  bool action_used = false;
  int selected_item_num = 0;
  while (!done) {
    system("CLS");
    auto list_of_items = MainCharacter->us.GetBackpackList();
    std::cout
      << "CURRENT INVENTORY\n"
      << "-----------------\n\n";
    int items_in_backpack_count = 0;
    for (const auto& item : list_of_items) {
      if (selected_item_num == items_in_backpack_count)
        std::cout << "> ";
      else
        std::cout << "  ";
      std::cout << item->GetData()->Name << '\n';
      if (ItemManager::IsItemPotion(item)) {
        Potion* potion = nullptr;
        ItemManager::CastItemToPotion(item, potion);
        if (potion)
          std::cout << "    Quantity: " << potion->Quantity << '\n';
      }
      items_in_backpack_count++;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n d = done, w = up, s = down, u = use/equip current\n";
    char c = getchar();
    switch (c) {
    case 'd':
      done = true;
      break;
    case 'w':
      selected_item_num--;
      if (selected_item_num < 0)
        selected_item_num = 0;
      break;
    case 's':
      selected_item_num++;
      if (selected_item_num > list_of_items.size() - 1)
        selected_item_num = (int)list_of_items.size() - 1;
      break;
    case 'u':
      if (list_of_items.empty())
        continue;
      if (ItemManager::IsItemPotion(list_of_items[selected_item_num])) {
        action_used = ItemManager::Use(list_of_items[selected_item_num], &(MainCharacter->us));
      } else {
        action_used = ItemManager::Equip(list_of_items[selected_item_num], &(MainCharacter->us));
      }
      break;
    default:
      break;
    }
    if (action_used)
      break;
  }
  return action_used;
}

bool combat_ability_selection() {
  bool ability_done = false;
  bool action_used = false;
  int selected_ability = 0;
  while (!ability_done) {
    auto current_abilities = MainCharacter->us.GetAbilityList();
    system("CLS");
    std::cout
      << "CURRENT ABILITIES\n\n";
    int abilites_in_list_count = 0;
    for (const auto& abil : current_abilities) {
      std::cout << ((selected_ability == abilites_in_list_count) ? "> " : "  ");
      std::cout << abil->GetName() << '\n';
      //todo: cooldowns and mp
      abilites_in_list_count++;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n d = done, w = up, s = down, u = use\n";
    char c = getchar();
    switch (c) {
    case 'd':
      ability_done = true;
      break;
    case 'w':
      selected_ability--;
      if (selected_ability < 0)
        selected_ability = 0;
      break;
    case 's':
      selected_ability++;
      if (selected_ability > current_abilities.size() - 1)
        selected_ability = (int)current_abilities.size() - 1;
      break;
    case 'u':
      if (current_abilities[selected_ability]->GetTarget() == ABILITYTARGET::ENEMY) {
        int total_damage = 0;
        total_damage += current_abilities[selected_ability]->GetHPEffect();
        switch (current_abilities[selected_ability]->GetScaler()) {
        case ABILITYSCALER::STR:
          total_damage += (int)(MainCharacter->us.GetTotalStrength() / 2.f);
          break;
        case ABILITYSCALER::INT:
          total_damage += (int)(MainCharacter->us.GetTotalIntellect() / 2.f);
          break;
        case ABILITYSCALER::AGI:
          total_damage += (int)(MainCharacter->us.GetTotalAgility() / 2.f);
          break;
        default:
          break;
        }
        CurrentMonster->monster.HP.ReduceCurrent(total_damage);
      } else {  // itsa heal (probably)
        int total_heal = 0;
        total_heal += current_abilities[selected_ability]->GetHPEffect();
        switch (current_abilities[selected_ability]->GetScaler()) {
        case ABILITYSCALER::STR:
          total_heal += (int)(MainCharacter->us.GetTotalStrength() / 2.f);
          break;
        case ABILITYSCALER::INT:
          total_heal += (int)(MainCharacter->us.GetTotalIntellect() / 2.f);
          break;
        case ABILITYSCALER::AGI:
          total_heal += (int)(MainCharacter->us.GetTotalAgility() / 2.f);
          break;
        default:
          break;
        }
        MainCharacter->us.Heal(total_heal);
      }
      action_used = true;
      break;
    default:
      break;
    }
    if (action_used)
      break;
  }
  return action_used;
}

Item* drop_random_item() {
  // 8 armor items, 2 weapon types, 1 potion : 11 different drop types
  int drop_seed = Random::NTK(1, 100);
  if (drop_seed < 6) {
    std::string name;
    CoreStats local_stats;
    int magical_power = Random::NTK(0, 2);
    switch (magical_power) {
    case 0: name = "Helmet";
      local_stats = CoreStats(0, 0, 0, 1, 0);
      break;
    case 1: name = "+1 Helmet";
      local_stats = CoreStats(1, 1, 1, 2, 1);
      break;
    case 2: name = "+2 Helmet";
      local_stats = CoreStats(2, 2, 2, 3, 2);
      break;
    default:
      break;
    }
    return ItemManager::CreateArmor(name, local_stats, ARMORSLOT::HEAD);
  } else if (drop_seed < 12) {
    return ItemManager::CreateArmor("Breastplate", CoreStats(0, 0, 0, 1, 0), ARMORSLOT::CHEST);
  } else if (drop_seed < 18) {
    return ItemManager::CreateArmor("Leg Guards", CoreStats(0, 0, 0, 1, 0), ARMORSLOT::LEGS);
  } else if (drop_seed < 24) {
    return ItemManager::CreateArmor("Boots", CoreStats(0, 0, 0, 1, 0), ARMORSLOT::FEET);
  } else if (drop_seed < 30) {
    return ItemManager::CreateArmor("Gloves", CoreStats(0, 0, 0, 1, 0), ARMORSLOT::HANDS);
  } else if (drop_seed < 36) {
    return ItemManager::CreateArmor("Ring1", CoreStats(1, 1, 1, 0, 0), ARMORSLOT::RING1);
  } else if (drop_seed < 42) {
    return ItemManager::CreateArmor("Ring2", CoreStats(1, 1, 1, 0, 0), ARMORSLOT::RING2);
  } else if (drop_seed < 48) {
    return ItemManager::CreateArmor("Neck Gaurd", CoreStats(0, 0, 0, 1, 1), ARMORSLOT::NECK);
  } else if (drop_seed < 54) {
    return ItemManager::CreateWeapon("1H Sword", CoreStats(0, 0, 0, 0, 0), WEAPONSLOT::MELEE, 2, 3);
  } else if (drop_seed < 60) {
    return ItemManager::CreateWeapon("Bow", CoreStats(0, 0, 0, 0, 0), WEAPONSLOT::RANGED, 2, 3);
  } else if (drop_seed < 91) {
    return ItemManager::CreatePotion("Potion Of Healing", Random::NTK(2, 5), Random::NTK(1, 2));
  }
  return nullptr;
}

void create_monster(Fightable* in_out, const Player* base_calc) {
  if (!base_calc)
    return;

  if (in_out) {
    delete in_out;
    in_out = nullptr;
  }

  int lowest_hp = base_calc->us.GetLevel() * 2;
  int max_hp = base_calc->us.GetLevel() * 8;

  int lowest_dam = base_calc->us.GetLevel();
  int max_dam = base_calc->us.GetLevel() * 2;

  in_out = new Fightable(Random::NTK(lowest_hp, max_hp), lowest_dam, max_dam);


  in_out->xpos = Random::NTK(1, 11);
  in_out->ypos = Random::NTK(1, 11);

  while (the_map[in_out->xpos][in_out->ypos] == 'P' || the_map[in_out->xpos][in_out->ypos] == 'x') {
    in_out->xpos = Random::NTK(1, 11);
    in_out->ypos = Random::NTK(1, 11);
  }

  the_map[in_out->xpos][in_out->ypos] = 'M';

  CurrentMonster = in_out;
}

void fight_sequence(Player& player1) {
  if (!CurrentMonster) {
    return;
  }
  // options available per turn
  enum class FightOptions { NONE, ATTACK, INVENTORY, ABILITY };
  while (player1.IsAlive() && CurrentMonster->IsAlive()) {
    FightOptions action_taken = FightOptions::NONE;
    char action = '\0';
    while (action_taken == FightOptions::NONE) {
      // display fight interface
      system("CLS");
      std::cout
        << "Player         vs       Monster\n"
        << "hp: " << player1.us.GetCurrentHP() << '/' << player1.us.GetMaxHP() << "                  hp: " << CurrentMonster->monster.HP.GetCurrent() << '/' << CurrentMonster->monster.HP.GetMax() << '\n'
        << "action(a:attack,i:inv,b:abilites): ";
      action = getchar();
      switch (action) {
      case 'a':
        action_taken = FightOptions::ATTACK;
        CurrentMonster->monster.HP.ReduceCurrent(player1.us.MeleeAttack());
        break;
      case 'i':
        action_taken = (combat_inventory()) ? FightOptions::INVENTORY : FightOptions::NONE;
        break;
      case 'b':
        action_taken = (combat_ability_selection()) ? FightOptions::ABILITY : FightOptions::NONE;
        break;
      default:
        break;
      }
    }

    // monster hits when your turn is over
    if (CurrentMonster->IsAlive()) {
      // monster attack every turn
      int damage_we_take = CurrentMonster->monster.Attack();
      damage_we_take -= player1.us.GetTotalArmor();
      if (damage_we_take < 1)
        damage_we_take = 1;
      player1.us.TakeDamage(damage_we_take);
    }

  }

  if (player1.IsAlive()) {
    std::cout << "You Won vs the Monster!\n";

    // gain xp
    player1.us.GainEXP(CurrentMonster->xpworth);
    std::cout << "xp gained: " << CurrentMonster->xpworth << '\n';

    // drop a random item
    Item* item_drop = drop_random_item();
    if (item_drop) {
      ItemManager::MoveToBackpack(item_drop, &player1.us);
      std::cout << "item recieved: " << item_drop->GetData()->Name << '\n';
    }

    // note monsters defeated count and prepare the next one
    monsters_defeated++;
    create_monster(CurrentMonster, &player1);
  } else {
    std::cout << "You were defeated by the Monster!\n";
  }

  std::cin.ignore(100, '\n');
  std::cout << "\n Press Enter to Continue\n";
  char a = getchar();

}

void moveplayeronmap(Player& player1) {
  // if they haven't move, return and do nothing
  if (player1.xpos == player1.prev_xpos && player1.ypos == player1.prev_ypos)
    return;

  if (the_map[player1.xpos][player1.ypos] == 'M') {
    fight_sequence(player1);
  }

  // check that the player hasn't moved into a wall
  if (the_map[player1.xpos][player1.ypos] != 'x') {
    // draw the charater at new location
    the_map[player1.xpos][player1.ypos] = 'P';
    // make old location a black area
    the_map[player1.prev_xpos][player1.prev_ypos] = ' ';
    // update current location to be previous before next update
    player1.prev_xpos = player1.xpos;
    player1.prev_ypos = player1.ypos;
  } else {
    // hit a wall, move back to prev location
    player1.xpos = player1.prev_xpos;
    player1.ypos = player1.prev_ypos;
  }
}

void showmap() {
  system("CLS");
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 13; j++) {
      std::cout << the_map[i][j];
    }
    std::cout << '\n';
  }
}

int main(int argc, char** argv) {

  std::cout << "Choose a class: \n"
    << "1 = Cleric    2 = Warrior\n"
    << "3 = Rogue     4 = Wizard\n";
  int choice = 0;
  while (choice == 0) {
    std::cin >> choice;
    std::cout << "chose: " << choice << '\n';
    if (choice < 1 || choice > 4)
      choice = 0;
  }

  switch (choice) {
  case 1:
  {
    MainCharacter = new Player(new Cleric());
  }
  break;
  case 2:
  {
    MainCharacter = new Player(new Warrior());
  }
  break;
  case 3:
  {
    MainCharacter = new Player(new Rogue());
  }
  break;
  case 4:
  {
    MainCharacter = new Player(new Wizard());
  }
  break;
  default:
    return -12;  // failed to make player character
  }

  ItemManager::MoveToBackpack(drop_random_item(), &MainCharacter->us);
  ItemManager::MoveToBackpack(drop_random_item(), &MainCharacter->us);

  create_monster(CurrentMonster, MainCharacter);

  the_map[MainCharacter->xpos][MainCharacter->ypos] = 'P';
  the_map[CurrentMonster->xpos][CurrentMonster->ypos] = 'M';

  showmap();

  for (;;) {
    std::cout << "\nmove(wasd), inv(i), charsheet(c): ";
    char c = getchar();

    switch (c) {
    case 'w':
      MainCharacter->xpos--;
      break;
    case 's':
      MainCharacter->xpos++;
      break;
    case 'a':
      MainCharacter->ypos--;
      break;
    case 'd':
      MainCharacter->ypos++;
      break;
    case 'i':
      open_inventory();
      break;
    case 'c':
      display_character_sheet();
      break;
    default:
      break;
    }

    std::cin.clear();

    moveplayeronmap(*MainCharacter);

    if (MainCharacter->IsAlive()) {
      showmap();
    } else {
      break;
    }
  }

  std::cout << "Total Monsters Defeated: " << monsters_defeated << '\n';
  char c = getchar();
  return EXIT_SUCCESS;
}