#pragma once
#include "types.h"
#include "playercharacter.h"

class Rogue : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = (welltype)12u;
  static const welltype BASEMP = (welltype)0u;
  static const stattype BASESTR = (stattype)3u;
  static const stattype BASEINT = (stattype)3u;
  static const stattype BASEAGI = (stattype)6u;
  Rogue();
private:
  void level_up() noexcept override;
};