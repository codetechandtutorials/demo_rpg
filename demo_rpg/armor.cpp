#include "armor.h"

Armor::Armor(std::string name, CoreStats cstats, ARMORSLOT slot) : EquipmentDelegate(name, cstats), Slot(slot) {}
Armor::~Armor() {}
