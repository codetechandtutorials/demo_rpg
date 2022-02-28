#pragma once
#include "playercharacter.h"

class Warrior : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = (welltype)18u;
  static const welltype BASEMP = (welltype)0u;
  static const stattype BASESTR = (stattype)6u;
  static const stattype BASEINT = (stattype)2u;
  static const stattype BASEAGI = (stattype)2u;
  Warrior();
private:
  void level_up() noexcept override;
};