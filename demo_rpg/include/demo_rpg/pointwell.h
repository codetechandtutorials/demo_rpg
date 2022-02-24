#pragma once
#include "types.h"
class PointWell {
public:
  [[nodiscard]] const welltype GetMax() const noexcept;
  [[nodiscard]] const welltype GetCurrent() const noexcept;
  [[nodiscard]] const bool IsFull() const noexcept;

  void SetMax(welltype new_max) noexcept;
  void ReduceCurrent(welltype damage) noexcept;
  void IncreaseCurrent(welltype amount) noexcept;

  PointWell();
  PointWell(welltype c, welltype m);

private:
  welltype _current;
  welltype _max;
};
