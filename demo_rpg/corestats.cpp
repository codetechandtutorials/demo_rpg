#include "corestats.h"


CoreStats::CoreStats() {
  Strength = 0;
  Intellect = 0;
  Agility = 0;
  Armor = 0;
  ElementRes = 0;
}

CoreStats::CoreStats(stattype s, stattype i, stattype ag, stattype arm, stattype eres)
  : Strength(s), Intellect(i), Agility(ag), Armor(arm), ElementRes(eres) {
}

CoreStats::CoreStats(stattype all) : Strength(all), Intellect(all), Agility(all), Armor(all), ElementRes(all) {}

CoreStats& CoreStats::operator+=(const CoreStats& rhs) {
  this->Strength += rhs.Strength;
  this->Intellect += rhs.Intellect;
  this->Agility += rhs.Agility;
  this->Armor += rhs.Armor;
  this->ElementRes += rhs.ElementRes;
  return *this;
};

CoreStats& CoreStats::operator-=(const CoreStats& rhs) {
  CoreStats tmp = *this;

  this->Strength -= rhs.Strength;
  this->Intellect -= rhs.Intellect;
  this->Agility -= rhs.Agility;
  this->Armor -= rhs.Armor;
  this->ElementRes -= rhs.ElementRes;

  if (this->Strength > tmp.Strength) this->Strength = 0u;
  if (this->Intellect > tmp.Intellect) this->Intellect = 0u;
  if (this->Agility > tmp.Agility) this->Agility = 0u;
  if (this->Armor > tmp.Armor) this->Armor = 0u;
  if (this->ElementRes > tmp.ElementRes) this->ElementRes = 0u;

  return *this;
};

CoreStats& CoreStats::operator=(const stattype& rhs) {
  this->Strength = rhs;
  this->Intellect = rhs;
  this->Agility = rhs;
  this->Armor = rhs;
  this->ElementRes = rhs;
  return *this;
}