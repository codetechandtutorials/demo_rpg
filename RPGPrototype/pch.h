#pragma once
#include "demo_rpg/playercharacter.h"
#include "demo_rpg/playableclasses_fwd.h"
#include "demo_rpg/monster.h"

char the_map[12][13] =
{ "xxxxxxxxxxxx",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "xxxxxxxxxxxx" };


struct Player {
  Player(PlayerCharacterDelegate* charclass) : us(charclass) {}
  Player() = delete;
  bool IsAlive() { return (us.GetCurrentHP() > 0); }
  PlayerCharacter us;
  int prev_xpos = 3;
  int prev_ypos = 3;
  int xpos = 3;
  int ypos = 3;
};



struct Fightable {
  Fightable(int hp, int min, int max) : monster(hp, min, max) {
    xpworth = (hp + min + max) * 2;
  }
  bool IsAlive() { return (monster.HP.GetCurrent() > 0); }
  Monster monster;
  int xpos = 3;
  int ypos = 3;
  int xpworth;
  Fightable() = delete;
};

