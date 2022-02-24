#include "pointwell.h"


[[nodiscard]] const welltype PointWell::GetMax() const noexcept {
  return _max;
}
[[nodiscard]] const welltype PointWell::GetCurrent() const noexcept {
  return _current;
}
[[nodiscard]] const bool PointWell::IsFull() const noexcept { return (_current == _max); }

void PointWell::SetMax(welltype new_max) noexcept {
  if (new_max < 1)
    _max = 1;
  else
    _max = new_max;

  if (_current > _max)
    _current = _max;
}
void PointWell::ReduceCurrent(welltype damage) noexcept {
  if (damage > _current) {
    _current = 0;
    return;
  }

  _current -= damage;
}
void PointWell::IncreaseCurrent(welltype amount) noexcept {
  if (amount + _current > _max) {
    _current = _max;
    return;
  }

  _current += amount;
}

PointWell::PointWell() { _current = 1; _max = 1; }

PointWell::PointWell(welltype c, welltype m) {
  _current = c;
  _max = m;
  if (_current > _max)
    _current = _max;
}
