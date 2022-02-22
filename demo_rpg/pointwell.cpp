#include "pointwell.h"


// returns true if set successfully
bool PointWell::setMax(welltype new_max) {
  if (new_max < 1)
    return false;

  MaxWell = new_max;

  if (CurrentFullness > MaxWell)
    CurrentFullness = MaxWell;

  return true;
}

welltype PointWell::getMax() {
  return MaxWell;
}

welltype PointWell::getCurrent() {
  return CurrentFullness;
}

bool PointWell::isFull() { return (CurrentFullness == MaxWell); }

void PointWell::reduceCurrent(welltype damage) {
  if (damage > CurrentFullness) {
    CurrentFullness = 0;
    return;
  }

  CurrentFullness -= damage;
}

void PointWell::increaseCurrent(welltype amount) {
  if (amount + CurrentFullness > MaxWell) {
    CurrentFullness = MaxWell;
    return;
  }

  CurrentFullness += amount;
}

PointWell::PointWell() { CurrentFullness = 1; MaxWell = 1; }

PointWell::PointWell(welltype c, welltype m) {
  CurrentFullness = c;
  MaxWell = m;
  if (CurrentFullness > MaxWell)
    CurrentFullness = MaxWell;
}
