#include "item.h"

// don't change this, only the EquipmentDelegate constructor should touch this
static std::uint32_t EQUIPMENTUNIQUEIDITERATOR = 0u;

EquipmentDelegate::EquipmentDelegate(std::string name, CoreStats cstats)
  : ItemDelegate(name), Stats(cstats), UniqueId(++EQUIPMENTUNIQUEIDITERATOR) {
}

