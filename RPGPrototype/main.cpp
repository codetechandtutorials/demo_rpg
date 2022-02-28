#include "pch.h"
#include "demo_rpg/random.h"
#include <iostream>

Player* MainCharacter = nullptr;
Fightable* CurrentMonster = nullptr;
int monsters_defeated = 0;

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

// returns true on win, false otherwise
void enterfightsequence(Player& player1) {
  if (!CurrentMonster) {
    return;
  }
  while (player1.IsAlive() && CurrentMonster->IsAlive()) {
    system("CLS");
    // display fight interface
    std::cout
      << "Player         vs       Monster\n"
      << "hp: " << player1.us.GetCurrentHP() << '/' << player1.us.GetMaxHP() << "                  hp: " << CurrentMonster->monster.HP.GetCurrent() << '/' << CurrentMonster->monster.HP.GetMax() << '\n'
      << "action(a:attack): ";
    char action = '1';
    while (action != 'a') {
      action = getchar();
    }
    CurrentMonster->monster.HP.ReduceCurrent(player1.us.MeleeAttack());

    if (CurrentMonster->IsAlive()) {
      player1.us.TakeDamage(CurrentMonster->monster.Attack());
    }
  }

  if (player1.IsAlive()) {
    std::cout << "You Won vs the Monster!\n";
    std::cout << "xp gained: " << CurrentMonster->xpworth << '\n';
    player1.us.GainEXP(CurrentMonster->xpworth);
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
    enterfightsequence(player1);
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

  create_monster(CurrentMonster, MainCharacter);

  the_map[MainCharacter->xpos][MainCharacter->ypos] = 'P';
  the_map[CurrentMonster->xpos][CurrentMonster->ypos] = 'M';

  showmap();

  for (;;) {
    std::cout << "\nmove(wasd): ";
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