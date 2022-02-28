#pragma once
#include "types.h"
#include "playercharacter.h"

class Wizard : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = (welltype)10u;
  static const welltype BASEMP = (welltype)14u;
  static const stattype BASESTR = (stattype)1u;
  static const stattype BASEINT = (stattype)8u;
  static const stattype BASEAGI = (stattype)2u;
  Wizard();
private:
  void level_up() noexcept override;
};