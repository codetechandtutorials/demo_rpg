#include "pointwell.h"


[[nodiscard]] const welltype PointWell::GetMax() const noexcept {
  return _max_well;
}
[[nodiscard]] const welltype PointWell::GetCurrent() const noexcept {
  return _current_fullness;
}
[[nodiscard]] const bool PointWell::IsFull() const noexcept { return (_current_fullness == _max_well); }

void PointWell::SetMax(welltype new_max) noexcept {
  if (new_max < 1)
    _max_well = 1;
  else
    _max_well = new_max;

  if (_current_fullness > _max_well)
    _current_fullness = _max_well;
}
void PointWell::ReduceCurrent(welltype damage) noexcept {
  if (damage > _current_fullness) {
    _current_fullness = 0;
    return;
  }

  _current_fullness -= damage;
}
void PointWell::IncreaseCurrent(welltype amount) noexcept {
  if (amount + _current_fullness > _max_well) {
    _current_fullness = _max_well;
    return;
  }

  _current_fullness += amount;
}

PointWell::PointWell() { _current_fullness = 1; _max_well = 1; }

PointWell::PointWell(welltype c, welltype m) {
  _current_fullness = c;
  _max_well = m;
  if (_current_fullness > _max_well)
    _current_fullness = _max_well;
}
