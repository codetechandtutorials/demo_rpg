#include "playercharacter.h"
#include <memory>

PlayerCharacterDelegate::~PlayerCharacterDelegate() {}


void PlayerCharacterDelegate::GiveEXP(const exptype amt) noexcept {
  _current_exp += amt;
  while (check_if_leveled()) {}
}

PlayerCharacterDelegate::PlayerCharacterDelegate() : StatBlock(0u, 0u) {
  _current_level = (leveltype)1u;
  _current_exp = (exptype)0u;
  _exp_to_next_level = LEVEL2AT;
}

[[nodiscard]] leveltype PlayerCharacterDelegate::GetLevel() const noexcept {
  return _current_level;
}

[[nodiscard]] exptype PlayerCharacterDelegate::GetCurrentEXP() const noexcept {
  return _current_exp;
}

[[nodiscard]] exptype PlayerCharacterDelegate::GetEXPToNextLevel() const noexcept {
  return _exp_to_next_level;
}

[[nodiscard]] const bool PlayerCharacterDelegate::check_if_leveled() noexcept {
  static const leveltype LEVELSCALAR = 2u;
  if (_current_exp >= _exp_to_next_level) {
    _current_level++;
    level_char_up();
    _exp_to_next_level *= LEVELSCALAR;
    return true;
  }
  return false;
}

void PlayerCharacter::move_to_backpack(Item* item_to_move) noexcept {
  _backpack.push_back(item_to_move);
}

void PlayerCharacter::cleanup_backpack() noexcept {
  const auto to_remove = std::stable_partition(_backpack.begin(), _backpack.end(),
    [](const Item* i) -> bool { return !i->GetMarkedForDeletion(); }
  );
  std::for_each(to_remove, _backpack.end(), [](Item*& i) { ItemManager::DeleteItem(i); });
  _backpack.erase(to_remove, _backpack.end());
}

PlayerCharacter::PlayerCharacter(PlayerCharacterDelegate* pc) : _player_class(pc) {
  auto i = 0;
  for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
    _equipped_armor[i] = nullptr;
  }
  for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
    _equipped_weapons[i] = nullptr;
  }
}

PlayerCharacter::~PlayerCharacter() {
  delete _player_class;
  _player_class = nullptr;
  auto i = 0;
  for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
    if (_equipped_armor[i]) {
      ItemManager::DeleteItem(_equipped_armor[i]);
    }
  }
  for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
    if (_equipped_weapons[i]) {
      ItemManager::DeleteItem(_equipped_weapons[i]);
    }
  }
}

// Getters
[[nodiscard]] const leveltype PlayerCharacter::GetLevel() const noexcept { return _player_class->GetLevel(); }
[[nodiscard]] const exptype PlayerCharacter::GetCurrentEXP() const noexcept { return _player_class->GetCurrentEXP(); }
[[nodiscard]] const exptype PlayerCharacter::GetEXPToNextLevel() const noexcept { return _player_class->GetEXPToNextLevel(); }
[[nodiscard]] const bool PlayerCharacter::IsMaxHealth() const noexcept { return _player_class->HP->IsFull(); }
[[nodiscard]] const welltype PlayerCharacter::GetCurrentHP() const noexcept { return _player_class->HP->GetCurrent(); }
[[nodiscard]] const welltype PlayerCharacter::GetMaxHP() const noexcept { return _player_class->HP->GetMax(); }
[[nodiscard]] const welltype PlayerCharacter::GetCurrentMP() const noexcept {
  if (_player_class->MP)
    return _player_class->MP->GetCurrent();
  else
    return 0;
}
[[nodiscard]] const welltype PlayerCharacter::GetMaxMP() const noexcept {
  if (_player_class->MP)
    return _player_class->MP->GetMax();
  else
    return 0;
}
[[nodiscard]] const stattype PlayerCharacter::GetBaseStrength() const noexcept { return _player_class->GetBaseStrength(); }
[[nodiscard]] const stattype PlayerCharacter::GetBaseIntellect() const noexcept { return _player_class->GetBaseIntellect(); }
[[nodiscard]] const stattype PlayerCharacter::GetBaseAgility() const noexcept { return _player_class->GetBaseAgility(); }
[[nodiscard]] const stattype PlayerCharacter::GetBaseArmor() const noexcept { return _player_class->GetBaseArmor(); }
[[nodiscard]] const stattype PlayerCharacter::GetBaseElementRes() const noexcept { return _player_class->GetBaseElementRes(); }
[[nodiscard]] const stattype PlayerCharacter::GetTotalStrength() const noexcept {
  stattype str_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(_equipped_armor[i], armor);
      if (armor) {
        str_from_armor += armor->Stats.Strength;
      }
      armor = nullptr;
    }
  }
  stattype str_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(_equipped_weapons[i], weapon);
      if (weapon) {
        str_from_weapons += weapon->Stats.Strength;
      }
      weapon = nullptr;
    }
  }
  return _player_class->GetTotalStrength() + str_from_armor + str_from_weapons;
}
[[nodiscard]] const stattype PlayerCharacter::GetTotalIntellect() const noexcept {
  stattype int_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(_equipped_armor[i], armor);
      if (armor) {
        int_from_armor += armor->Stats.Intellect;
      }
      armor = nullptr;
    }
  }
  stattype int_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(_equipped_weapons[i], weapon);
      if (weapon) {
        int_from_weapons += weapon->Stats.Intellect;
      }
      weapon = nullptr;
    }
  }
  return _player_class->GetTotalIntellect() + int_from_armor + int_from_weapons;
}
[[nodiscard]] const stattype PlayerCharacter::GetTotalAgility() const noexcept {
  stattype agil_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(_equipped_armor[i], armor);
      if (armor) {
        agil_from_armor += armor->Stats.Agility;
      }
      armor = nullptr;
    }
  }
  stattype agil_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(_equipped_weapons[i], weapon);
      if (weapon) {
        agil_from_weapons += weapon->Stats.Agility;
      }
      weapon = nullptr;
    }
  }
  return _player_class->GetTotalAgility() + agil_from_armor + agil_from_weapons;
}
[[nodiscard]] const stattype PlayerCharacter::GetTotalArmor() const noexcept {
  // get all armor from equipped armor
  stattype armor_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(_equipped_armor[i], armor);
      if (armor) {
        armor_from_armor += armor->Stats.Armor;
      }
      armor = nullptr;
    }
  }
  stattype armor_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(_equipped_weapons[i], weapon);
      if (weapon) {
        armor_from_weapons += weapon->Stats.Armor;
      }
      weapon = nullptr;
    }
  }
  return _player_class->GetTotalArmor() + armor_from_armor + armor_from_weapons;
}
[[nodiscard]] const stattype PlayerCharacter::GetTotalElementRes() const noexcept {
  stattype resist_from_armor = 0;
  {
    Armor* armor = nullptr;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToArmor(_equipped_armor[i], armor);
      if (armor) {
        resist_from_armor += armor->Stats.ElementRes;
      }
      armor = nullptr;
    }
  }
  stattype elres_from_weapons = 0;
  {
    Weapon* weapon = nullptr;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      ItemManager::CastItemToWeapon(_equipped_weapons[i], weapon);
      if (weapon) {
        elres_from_weapons += weapon->Stats.ElementRes;
      }
      weapon = nullptr;
    }
  }
  return _player_class->GetTotalElementRes() + resist_from_armor + elres_from_weapons;
}
[[nodiscard]] const std::vector<Ability> PlayerCharacter::GetAbilityList() const noexcept { return _player_class->Abilities; }
[[nodiscard]] const std::vector<Buff> PlayerCharacter::GetBuffList() const noexcept { return _player_class->Buffs; }
[[nodiscard]] const std::vector<Item*> PlayerCharacter::GetBackpackList() const noexcept { return _backpack; }
[[nodiscard]] const Armor* PlayerCharacter::GetEquippedArmorAt(unsigned long long i) const noexcept {
  if (!_equipped_armor[i]) return nullptr;
  return (dynamic_cast<const Armor*>(_equipped_armor[i]->GetData()));
}
[[nodiscard]] const Weapon* PlayerCharacter::GetEquippedWeaponAt(unsigned long long i) const noexcept {
  if (!_equipped_weapons[i]) return nullptr;
  return (dynamic_cast<const Weapon*>(_equipped_weapons[i]->GetData()));
}

// Modifiers
void PlayerCharacter::GainEXP(exptype amt) noexcept { _player_class->GiveEXP(amt); }
void PlayerCharacter::TakeDamage(welltype amt) noexcept { _player_class->HP->ReduceCurrent(amt); }
void PlayerCharacter::Heal(welltype amt) noexcept { _player_class->HP->IncreaseCurrent(amt); }
void PlayerCharacter::ApplyBuff(Buff _buff) noexcept {
  _player_class->Buffs.push_back(_buff);
}