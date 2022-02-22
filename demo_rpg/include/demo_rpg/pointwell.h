#pragma once
#include "types.h"
class PointWell {
public:
  // returns true if set successfully
  bool setMax(welltype new_max);
  welltype getMax();
  welltype getCurrent();
  bool isFull();
  void reduceCurrent(welltype damage);
  void increaseCurrent(welltype amount);
  PointWell();
  PointWell(welltype c, welltype m);

private:
  welltype CurrentFullness;
  welltype MaxWell;
};
