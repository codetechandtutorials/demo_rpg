#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RPGSystemsUnitTest
{
TEST_CLASS(RPGSystemsUnitTest) {
public:

  TEST_METHOD(Abilities) {
    {
      Ability default_abil;
      Assert::AreEqual(std::string("unnamed"), default_abil.Name);
      Assert::AreEqual(1u, default_abil.HpEffect);
      Assert::IsNull(default_abil.GivenBuff);
      Assert::AreEqual(0u, default_abil.Cost);
      Assert::AreEqual(1u, default_abil.Cooldown);
      Assert::AreEqual((int)ABILITYTARGET::SELF, (int)default_abil.Target);
      Assert::AreEqual((int)ABILITYSCALER::NONE, (int)default_abil.Scaler);
    }
    {
      Ability constructed_abil("custom_name", 2u,
        new Buff("thicc", 1, 0, 0, 1, 1, 5, false),
        3u, 4u, ABILITYTARGET::ENEMY, ABILITYSCALER::STR);
      Assert::AreEqual(std::string("custom_name"), constructed_abil.Name);
      Assert::IsNotNull(constructed_abil.GivenBuff);
      Assert::AreEqual(2u, constructed_abil.HpEffect);
      Assert::AreEqual(3u, constructed_abil.Cost);
      Assert::AreEqual(4u, constructed_abil.Cooldown);
      Assert::AreEqual((int)ABILITYTARGET::ENEMY, (int)constructed_abil.Target);
      Assert::AreEqual((int)ABILITYSCALER::STR, (int)constructed_abil.Scaler);
    }
  }

  TEST_METHOD(Buffs) {
    {
      Buff a_buff;
      Assert::AreEqual(std::string("undefined"), a_buff.Name);
      Assert::AreEqual(0, (int)a_buff.BuffedStats.Strength);
      Assert::AreEqual(0, (int)a_buff.BuffedStats.Intellect);
      Assert::AreEqual(0, (int)a_buff.BuffedStats.Agility);
      Assert::AreEqual(0, (int)a_buff.BuffedStats.Armor);
      Assert::AreEqual(0, (int)a_buff.BuffedStats.ElementRes);
      Assert::AreEqual(2, (int)a_buff.Duration);
      Assert::IsFalse(a_buff.isDebuff);
    }
    {
      Buff a_buff("somename", CoreStats(1, 2, 3, 4, 5), 3, true);
      Assert::AreEqual(1, (int)a_buff.BuffedStats.Strength);
      Assert::AreEqual(2, (int)a_buff.BuffedStats.Intellect);
      Assert::AreEqual(3, (int)a_buff.BuffedStats.Agility);
      Assert::AreEqual(4, (int)a_buff.BuffedStats.Armor);
      Assert::AreEqual(5, (int)a_buff.BuffedStats.ElementRes);
      Assert::AreEqual(3, (int)a_buff.Duration);
      Assert::IsTrue(a_buff.isDebuff);
    }
    {
      Buff b_buff("somename", 1, 2, 3, 4, 5, 3, true);
      Assert::AreEqual(1, (int)b_buff.BuffedStats.Strength);
      Assert::AreEqual(2, (int)b_buff.BuffedStats.Intellect);
      Assert::AreEqual(3, (int)b_buff.BuffedStats.Agility);
      Assert::AreEqual(4, (int)b_buff.BuffedStats.Armor);
      Assert::AreEqual(5, (int)b_buff.BuffedStats.ElementRes);
      Assert::AreEqual(3, (int)b_buff.Duration);
      Assert::IsTrue(b_buff.isDebuff);
    }
  }
  TEST_METHOD(Stats) {
    CoreStats stats_default;
    Assert::AreEqual(0, (int)stats_default.Strength);
    Assert::AreEqual(0, (int)stats_default.Intellect);
    Assert::AreEqual(0, (int)stats_default.Agility);
    Assert::AreEqual(0, (int)stats_default.Armor);
    Assert::AreEqual(0, (int)stats_default.ElementRes);
    CoreStats statsa(5);
    Assert::AreEqual(5, (int)statsa.Strength);
    Assert::AreEqual(5, (int)statsa.Intellect);
    Assert::AreEqual(5, (int)statsa.Agility);
    Assert::AreEqual(5, (int)statsa.Armor);
    Assert::AreEqual(5, (int)statsa.ElementRes);
    CoreStats statsb(1, 2, 3, 4, 5);
    Assert::AreEqual(1, (int)statsb.Strength);
    Assert::AreEqual(2, (int)statsb.Intellect);
    Assert::AreEqual(3, (int)statsb.Agility);
    Assert::AreEqual(4, (int)statsb.Armor);
    Assert::AreEqual(5, (int)statsb.ElementRes);
    stats_default += statsa;
    Assert::AreEqual(5, (int)stats_default.Strength);
    Assert::AreEqual(5, (int)stats_default.Intellect);
    Assert::AreEqual(5, (int)stats_default.Agility);
    Assert::AreEqual(5, (int)stats_default.Armor);
    Assert::AreEqual(5, (int)stats_default.ElementRes);
    stats_default -= statsa;
    Assert::AreEqual(0, (int)stats_default.Strength);
    Assert::AreEqual(0, (int)stats_default.Intellect);
    Assert::AreEqual(0, (int)stats_default.Agility);
    Assert::AreEqual(0, (int)stats_default.Armor);
    Assert::AreEqual(0, (int)stats_default.ElementRes);
    stats_default = statsb;
    Assert::AreEqual(1, (int)statsb.Strength);
    Assert::AreEqual(2, (int)statsb.Intellect);
    Assert::AreEqual(3, (int)statsb.Agility);
    Assert::AreEqual(4, (int)statsb.Armor);
    Assert::AreEqual(5, (int)statsb.ElementRes);
  }

  TEST_METHOD(WeaponItem) {
    Item* a_magic_weapon = ItemManager::CreateWeapon("Magic Weapon", CoreStats(5), WEAPONSLOT::MELEE, 1, 3, false);
    Assert::IsNotNull(a_magic_weapon);
    Assert::IsTrue(ItemManager::IsItemWeapon(a_magic_weapon));
    Assert::IsFalse(ItemManager::IsItemArmor(a_magic_weapon));
    Assert::IsFalse(ItemManager::IsItemPotion(a_magic_weapon));
    // cast item data to weapon to check if it is a weapon
    Weapon* weapon = nullptr;
    ItemManager::CastItemToWeapon(a_magic_weapon, weapon);
    Assert::IsNotNull(weapon);  // make sure cast doesn't fail
    Assert::AreEqual(std::string("Magic Weapon"), weapon->Name);
    Assert::AreEqual(5, (int)weapon->Stats.Strength);
    Assert::AreEqual(5, (int)weapon->Stats.Intellect);
    Assert::AreEqual(5, (int)weapon->Stats.Agility);
    Assert::AreEqual(5, (int)weapon->Stats.Armor);
    Assert::AreEqual(5, (int)weapon->Stats.ElementRes);
    Assert::AreEqual((int)WEAPONSLOT::MELEE, (int)weapon->Slot);
    Assert::AreEqual(1, (int)weapon->MinDamage);
    Assert::AreEqual(3, (int)weapon->MaxDamage);
    Assert::IsFalse(weapon->is2H);
    delete a_magic_weapon;
    a_magic_weapon = nullptr;
    Assert::IsNull(a_magic_weapon);
    weapon = nullptr;
    Assert::IsNull(weapon);
  }

  TEST_METHOD(ArmorItems) {
    Item* armor_item = ItemManager::CreateArmor("SomeArmor", CoreStats(1, 2, 3, 4, 5), ARMORSLOT::HELMET);
    Assert::IsNotNull(armor_item);
    Assert::IsFalse(ItemManager::IsItemWeapon(armor_item));
    Assert::IsTrue(ItemManager::IsItemArmor(armor_item));
    Assert::IsFalse(ItemManager::IsItemPotion(armor_item));

    Armor* armor = nullptr;
    ItemManager::CastItemToArmor(armor_item, armor);
    Assert::AreEqual(std::string("SomeArmor"), armor->Name);
    Assert::AreEqual(1, (int)armor->Stats.Strength);
    Assert::AreEqual(2, (int)armor->Stats.Intellect);
    Assert::AreEqual(3, (int)armor->Stats.Agility);
    Assert::AreEqual(4, (int)armor->Stats.Armor);
    Assert::AreEqual(5, (int)armor->Stats.ElementRes);
    Assert::AreEqual((int)ARMORSLOT::HELMET, (int)armor->Slot);

    delete armor_item;
    armor_item = nullptr;
    Assert::IsNull(armor_item);

    armor = nullptr;
    Assert::IsNull(armor);

  }

  TEST_METHOD(PotionItems) {
    Item* random_potion = ItemManager::CreatePotion("Random Potion", 3, 4, nullptr);
    Assert::IsNotNull(random_potion);
    Assert::IsFalse(ItemManager::IsItemWeapon(random_potion));
    Assert::IsFalse(ItemManager::IsItemArmor(random_potion));
    Assert::IsTrue(ItemManager::IsItemPotion(random_potion));
    Potion* potion = nullptr;
    ItemManager::CastItemToPotion(random_potion, potion);
    Assert::AreEqual(std::string("Random Potion"), potion->Name);
    Assert::AreEqual(3, (int)potion->HealAmount);
    Assert::AreEqual(4, (int)potion->Quantity);
    delete random_potion;
    random_potion = nullptr;
    Assert::IsNull(random_potion);
    potion = nullptr;
    Assert::IsNull(potion);
  }

  TEST_METHOD(WarriorClass) {
    PlayerCharacter p1(new Warrior());
    Assert::AreEqual((int)Warrior::BASEHP, (int)p1.getMaxHP());

    p1.gainEXP(100u);
    Assert::AreEqual(2, (int)p1.getLevel());
    Assert::AreEqual(std::string("PowerAttack"), p1.getAbilityList().front().Name);
    Assert::AreEqual((int)(Warrior::BASEHP + (Warrior::BASEHP / 2.f)), (int)p1.getMaxHP());

  }

  TEST_METHOD(Equip) {
    PlayerCharacter rogue(new Rogue());
    Assert::IsTrue(ItemManager::Equip(
      ItemManager::CreateWeapon("Dagger", CoreStats(), WEAPONSLOT::MELEE, 1, 3, false),
      &rogue));

    Assert::IsNotNull(rogue.getEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE));

    Assert::IsFalse(ItemManager::Equip(
      ItemManager::CreatePotion("ArmorPot", 0, 1, new Buff("ArmorBuff", CoreStats(0, 0, 0, 3, 0), 5)),
      &rogue));
  }

};
}
