#pragma once
#include "types.h"
struct CoreStats {
  stattype Strength;
  stattype Intellect;
  stattype Agility;
  stattype Armor;
  stattype ElementRes;

  CoreStats();

  CoreStats(stattype s, stattype i, stattype ag, stattype arm, stattype eres);

  CoreStats(stattype all);

  CoreStats& operator+=(const CoreStats& rhs);

  CoreStats& operator-=(const CoreStats& rhs);

  CoreStats& operator=(const stattype& rhs);
};