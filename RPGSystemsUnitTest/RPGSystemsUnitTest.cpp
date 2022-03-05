#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RPGSystemsUnitTest
{
TEST_CLASS(RPGSystemsUnitTest) {
public:
  TEST_METHOD(Core_Abilities) {
    {
      Ability default_abil;
      Assert::AreEqual(std::string("unnamed"), default_abil.GetName());
      Assert::AreEqual(1u, default_abil.GetHPEffect());
      Assert::IsNull(default_abil.GetBuff());
      Assert::AreEqual(0u, default_abil.GetCost());
      Assert::AreEqual(1u, default_abil.GetCooldown());
      Assert::AreEqual((int)ABILITYTARGET::SELF, (int)default_abil.GetTarget());
      Assert::AreEqual((int)ABILITYSCALER::NONE, (int)default_abil.GetScaler());
    }
    {
      Ability constructed_abil("custom_name", 2u,
        new Buff("thicc", 1, 0, 0, 1, 1, 5, false),
        3u, 4u, ABILITYTARGET::ENEMY, ABILITYSCALER::STR);
      Assert::AreEqual(std::string("custom_name"), constructed_abil.GetName());
      Assert::IsNotNull(constructed_abil.GetBuff());
      Assert::AreEqual(2u, constructed_abil.GetHPEffect());
      Assert::AreEqual(3u, constructed_abil.GetCost());
      Assert::AreEqual(4u, constructed_abil.GetCooldown());
      Assert::AreEqual((int)ABILITYTARGET::ENEMY, (int)constructed_abil.GetTarget());
      Assert::AreEqual((int)ABILITYSCALER::STR, (int)constructed_abil.GetScaler());
    }
  }
  TEST_METHOD(Core_Buffs) {
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
  TEST_METHOD(Core_Stats) {
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
  TEST_METHOD(Item_Weapons) {
    Item* a_magic_weapon
      = ItemManager::CreateWeapon("Magic Weapon", CoreStats(5), WEAPONSLOT::MELEE, 1, 3, false);
    Assert::IsNotNull(a_magic_weapon);
    Assert::IsTrue(ItemManager::IsItemWeapon(a_magic_weapon));
    Assert::IsFalse(ItemManager::IsItemArmor(a_magic_weapon));
    Assert::IsFalse(ItemManager::IsItemPotion(a_magic_weapon));
    // const cast check
    {
      const Weapon* weapon = dynamic_cast<const Weapon*>(a_magic_weapon->GetData());
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
      //delete weapon;  // should have a compiler error
    }

    // modify weapon test
    {
      Weapon* weapon_mod = nullptr;
      ItemManager::CastItemToWeapon(a_magic_weapon, weapon_mod);
      Assert::IsNotNull(weapon_mod);  // make sure cast doesn't fail
      Assert::AreEqual(std::string("Magic Weapon"), weapon_mod->Name);
      Assert::AreEqual(5, (int)weapon_mod->Stats.Strength);
      Assert::AreEqual(5, (int)weapon_mod->Stats.Intellect);
      Assert::AreEqual(5, (int)weapon_mod->Stats.Agility);
      Assert::AreEqual(5, (int)weapon_mod->Stats.Armor);
      Assert::AreEqual(5, (int)weapon_mod->Stats.ElementRes);
      Assert::AreEqual((int)WEAPONSLOT::MELEE, (int)weapon_mod->Slot);
      Assert::AreEqual(1, (int)weapon_mod->MinDamage);
      Assert::AreEqual(3, (int)weapon_mod->MaxDamage);
      Assert::IsFalse(weapon_mod->is2H);

      // change things
      weapon_mod->Name = "+1 Magic Weapon";
      weapon_mod->Stats.Strength += 1;
      weapon_mod->Stats.Intellect += 1;
      weapon_mod->Stats.Agility += 1;
      weapon_mod->Stats.Armor += 1;
      weapon_mod->Stats.ElementRes += 1;
      weapon_mod->MinDamage += 1;
      weapon_mod->MaxDamage += 1;
      Assert::AreEqual(std::string("+1 Magic Weapon"), weapon_mod->Name);
      Assert::AreEqual(6, (int)weapon_mod->Stats.Strength);
      Assert::AreEqual(6, (int)weapon_mod->Stats.Intellect);
      Assert::AreEqual(6, (int)weapon_mod->Stats.Agility);
      Assert::AreEqual(6, (int)weapon_mod->Stats.Armor);
      Assert::AreEqual(6, (int)weapon_mod->Stats.ElementRes);
      Assert::AreEqual((int)WEAPONSLOT::MELEE, (int)weapon_mod->Slot);
      Assert::AreEqual(2, (int)weapon_mod->MinDamage);
      Assert::AreEqual(4, (int)weapon_mod->MaxDamage);
      Assert::IsFalse(weapon_mod->is2H);
    }

    ItemManager::DeleteItem(a_magic_weapon);
    Assert::IsNull(a_magic_weapon);
  }
  TEST_METHOD(Item_Armor) {
    Item* armor_item = ItemManager::CreateArmor("SomeArmor", CoreStats(1, 2, 3, 4, 5), ARMORSLOT::HEAD);
    Assert::IsNotNull(armor_item);
    Assert::IsFalse(ItemManager::IsItemWeapon(armor_item));
    Assert::IsTrue(ItemManager::IsItemArmor(armor_item));
    Assert::IsFalse(ItemManager::IsItemPotion(armor_item));

    // const casts
    {
      const Armor* armor = dynamic_cast<const Armor*>(armor_item->GetData());
      Assert::IsNotNull(armor);
      Assert::AreEqual(std::string("SomeArmor"), armor->Name);
      Assert::AreEqual(1, (int)armor->Stats.Strength);
      Assert::AreEqual(2, (int)armor->Stats.Intellect);
      Assert::AreEqual(3, (int)armor->Stats.Agility);
      Assert::AreEqual(4, (int)armor->Stats.Armor);
      Assert::AreEqual(5, (int)armor->Stats.ElementRes);
      Assert::AreEqual((int)ARMORSLOT::HEAD, (int)armor->Slot);
    }

    // mutable casts
    {
      Armor* armor_mod = nullptr;
      ItemManager::CastItemToArmor(armor_item, armor_mod);
      Assert::IsNotNull(armor_mod);
      Assert::AreEqual(std::string("SomeArmor"), armor_mod->Name);
      Assert::AreEqual(1, (int)armor_mod->Stats.Strength);
      Assert::AreEqual(2, (int)armor_mod->Stats.Intellect);
      Assert::AreEqual(3, (int)armor_mod->Stats.Agility);
      Assert::AreEqual(4, (int)armor_mod->Stats.Armor);
      Assert::AreEqual(5, (int)armor_mod->Stats.ElementRes);
      Assert::AreEqual((int)ARMORSLOT::HEAD, (int)armor_mod->Slot);

      // make changes
      armor_mod->Name = "+1 Scale Armor";
      armor_mod->Stats.Strength = 2;
      armor_mod->Stats.Intellect = 2;
      armor_mod->Stats.Agility = 2;
      armor_mod->Stats.Armor = 5;
      armor_mod->Stats.ElementRes = 1;
      armor_mod->Slot = ARMORSLOT::CHEST;

      Assert::AreEqual(std::string("+1 Scale Armor"), armor_mod->Name);
      Assert::AreEqual(2, (int)armor_mod->Stats.Strength);
      Assert::AreEqual(2, (int)armor_mod->Stats.Intellect);
      Assert::AreEqual(2, (int)armor_mod->Stats.Agility);
      Assert::AreEqual(5, (int)armor_mod->Stats.Armor);
      Assert::AreEqual(1, (int)armor_mod->Stats.ElementRes);
      Assert::AreEqual((int)ARMORSLOT::CHEST, (int)armor_mod->Slot);
    }
    ItemManager::DeleteItem(armor_item);
    Assert::IsNull(armor_item);
  }
  TEST_METHOD(Item_Potion) {
    Item* random_potion = ItemManager::CreatePotion("Random Potion", 3, 4, nullptr);
    Assert::IsNotNull(random_potion);
    Assert::IsFalse(ItemManager::IsItemWeapon(random_potion));
    Assert::IsFalse(ItemManager::IsItemArmor(random_potion));
    Assert::IsTrue(ItemManager::IsItemPotion(random_potion));

    // const cast
    {
      const Potion* const_potion = dynamic_cast<const Potion*>(random_potion->GetData());
      Assert::AreEqual(std::string("Random Potion"), const_potion->Name);
      Assert::AreEqual(3, (int)const_potion->HealAmount);
      Assert::AreEqual(4, (int)const_potion->Quantity);
      Assert::IsNull(const_potion->GetBuff());
    }

    // modify potion
    {
      Potion* potion = nullptr;
      ItemManager::CastItemToPotion(random_potion, potion);
      Assert::AreEqual(std::string("Random Potion"), potion->Name);
      Assert::AreEqual(3, (int)potion->HealAmount);
      Assert::AreEqual(4, (int)potion->Quantity);

      // modify
      potion->Name = "Super Potion";
      potion->HealAmount = 10;
      potion->Quantity = 1;
      potion->SetBuff(new Buff("RAWR!", CoreStats(5), 5, false));
      Assert::IsNotNull(potion->GetBuff());
      Assert::AreEqual(std::string("Super Potion"), potion->Name);
      Assert::AreEqual(10, (int)potion->HealAmount);
      Assert::AreEqual(1, (int)potion->Quantity);
      Assert::AreEqual(5, (int)potion->GetBuff()->Duration);
      Assert::AreEqual(std::string("RAWR!"), potion->GetBuff()->Name);
      Assert::AreEqual(5, (int)potion->GetBuff()->BuffedStats.Strength);
      Assert::AreEqual(5, (int)potion->GetBuff()->BuffedStats.Intellect);
      Assert::AreEqual(5, (int)potion->GetBuff()->BuffedStats.Agility);
      Assert::AreEqual(5, (int)potion->GetBuff()->BuffedStats.Armor);
      Assert::AreEqual(5, (int)potion->GetBuff()->BuffedStats.ElementRes);
      Assert::IsFalse(potion->GetBuff()->isDebuff);

      // modify to Poison Potion
      potion->Name = "Poison Potion";
      potion->HealAmount = 0;
      potion->Quantity = 1;
      potion->SetBuff(new Buff("Poisoned", CoreStats(2), 3, true));  // -2 to all stats for 3 rounds
      Assert::IsNotNull(potion->GetBuff());
      Assert::AreEqual(std::string("Poison Potion"), potion->Name);
      Assert::AreEqual(0, (int)potion->HealAmount);
      Assert::AreEqual(1, (int)potion->Quantity);
      Assert::AreEqual(3, (int)potion->GetBuff()->Duration);
      Assert::AreEqual(std::string("Poisoned"), potion->GetBuff()->Name);
      Assert::AreEqual(2, (int)potion->GetBuff()->BuffedStats.Strength);
      Assert::AreEqual(2, (int)potion->GetBuff()->BuffedStats.Intellect);
      Assert::AreEqual(2, (int)potion->GetBuff()->BuffedStats.Agility);
      Assert::AreEqual(2, (int)potion->GetBuff()->BuffedStats.Armor);
      Assert::AreEqual(2, (int)potion->GetBuff()->BuffedStats.ElementRes);
      Assert::IsTrue(potion->GetBuff()->isDebuff);
    }

    ItemManager::DeleteItem(random_potion);
    Assert::IsNull(random_potion);
  }
  TEST_METHOD(Player_Cleric) {
    PlayerCharacter p1(new Cleric());
    Assert::AreEqual((int)Cleric::BASEHP, (int)p1.GetMaxHP());
    Assert::AreEqual((int)Cleric::BASEMP, (int)p1.GetMaxMP());
    Assert::AreEqual(std::string("Heal"), p1.GetAbilityList().front()->GetName());

    p1.GainEXP(100u);
    // level 2
    Assert::AreEqual(2, (int)p1.GetLevel());
    Assert::AreEqual(std::string("Smite"), p1.GetAbilityList()[1]->GetName());
    Assert::AreEqual((int)(Cleric::BASEHP + (Cleric::BASEHP / 2.f)), (int)p1.GetMaxHP());
    Assert::AreEqual((int)(Cleric::BASEMP + (Cleric::BASEMP / 2.f)), (int)p1.GetMaxMP());
  }
  TEST_METHOD(Player_Rogue) {
    PlayerCharacter p1(new Rogue());
    Assert::AreEqual((int)Rogue::BASEHP, (int)p1.GetMaxHP());

    p1.GainEXP(100u);
    // level 2
    Assert::AreEqual(2, (int)p1.GetLevel());
    Assert::AreEqual(std::string("PreciseAttack"), p1.GetAbilityList().front()->GetName());
    Assert::AreEqual((int)(Rogue::BASEHP + (Rogue::BASEHP / 2.f)), (int)p1.GetMaxHP());
  }
  TEST_METHOD(Player_Warrior) {
    PlayerCharacter p1(new Warrior());
    Assert::AreEqual((int)Warrior::BASEHP, (int)p1.GetMaxHP());

    p1.GainEXP(100u);
    // level 2
    Assert::AreEqual(2, (int)p1.GetLevel());
    Assert::AreEqual(std::string("Power Attack"), p1.GetAbilityList().front()->GetName());
    Assert::AreEqual((int)(Warrior::BASEHP + (Warrior::BASEHP / 2.f)), (int)p1.GetMaxHP());

    p1.GainEXP(200u);
    // level 3
    Assert::AreEqual(3, (int)p1.GetLevel());
    Assert::AreEqual(std::string("Healing Surge"), p1.GetAbilityList()[1]->GetName());
    Assert::AreEqual((int)(Warrior::BASEHP + ((Warrior::BASEHP / 2.f) * 2)), (int)p1.GetMaxHP());
  }
  TEST_METHOD(Player_Wizard) {
    PlayerCharacter p1(new Wizard());
    Assert::AreEqual((int)Wizard::BASEHP, (int)p1.GetMaxHP());
    Assert::AreEqual((int)Wizard::BASEMP, (int)p1.GetMaxMP());
    Assert::AreEqual(std::string("Firebolt"), p1.GetAbilityList().front()->GetName());

    p1.GainEXP(100u);
    // level 2
    Assert::AreEqual(2, (int)p1.GetLevel());
    Assert::AreEqual(std::string("IceBolt"), p1.GetAbilityList()[1]->GetName());
    Assert::AreEqual((int)(Wizard::BASEHP + (Wizard::BASEHP / 2.f)), (int)p1.GetMaxHP());
    Assert::AreEqual((int)(Wizard::BASEMP + (Wizard::BASEMP / 2.f)), (int)p1.GetMaxMP());
  }
  TEST_METHOD(Equip_Player) {
    // a player to equip
    PlayerCharacter rogue(new Rogue());

    // equip a full suite of items
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateWeapon("Dagger", CoreStats(), WEAPONSLOT::MELEE, 1, 3, false), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateWeapon("Bow", CoreStats(), WEAPONSLOT::RANGED, 1, 3, false), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateArmor("Helm", CoreStats(0, 0, 0, 1, 1), ARMORSLOT::HEAD), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateArmor("Armor", CoreStats(0, 0, 0, 1, 1), ARMORSLOT::CHEST), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateArmor("Pants", CoreStats(0, 0, 0, 1, 1), ARMORSLOT::LEGS), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateArmor("Shoes", CoreStats(0, 0, 0, 1, 1), ARMORSLOT::FEET), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateArmor("Gloves", CoreStats(0, 0, 0, 1, 1), ARMORSLOT::HANDS), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateArmor("Silver Ring", CoreStats(1), ARMORSLOT::RING1), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateArmor("Gold Ring", CoreStats(2), ARMORSLOT::RING2), &rogue));
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateArmor("Necklace", CoreStats(0, 0, 0, 1, 1), ARMORSLOT::NECK), &rogue));

    // check slots
    Assert::IsNotNull(rogue.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE));
    Assert::IsNotNull(rogue.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED));
    Assert::IsNotNull(rogue.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HEAD));
    Assert::IsNotNull(rogue.GetEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST));
    Assert::IsNotNull(rogue.GetEquippedArmorAt((unsigned long long)ARMORSLOT::LEGS));
    Assert::IsNotNull(rogue.GetEquippedArmorAt((unsigned long long)ARMORSLOT::FEET));
    Assert::IsNotNull(rogue.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HANDS));
    Assert::IsNotNull(rogue.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING1));
    Assert::IsNotNull(rogue.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING2));
    Assert::IsNotNull(rogue.GetEquippedArmorAt((unsigned long long)ARMORSLOT::NECK));

    // equipping a potion should do nothing
    Assert::IsFalse(ItemManager::Equip(ItemManager::CreatePotion("ArmorPot", 0, 1, new Buff("ArmorBuff", CoreStats(0, 0, 0, 3, 0), 5)), &rogue));

    auto backpack = rogue.GetBackpackList();
    Assert::AreEqual(0, (int)backpack.size());

  }

  TEST_METHOD(Enemy_Monster) {
    Monster monster1(10, 2, 4);
    Assert::AreEqual(10, (int)monster1.HP.GetMax());
    Assert::AreEqual(2, (int)monster1.GetMinDamage());
    Assert::AreEqual(4, (int)monster1.GetMaxDamage());

    int damage_rando = 0;
    for (int i = 0; i < 10; ++i) {
      damage_rando = monster1.Attack();
      Assert::IsTrue((damage_rando >= (int)monster1.GetMinDamage()));
      Assert::IsTrue((damage_rando <= (int)monster1.GetMaxDamage()));
    }

  }

  TEST_METHOD(Simple_Battle) {
    PlayerCharacter rogue(new Rogue());
    Assert::IsTrue(ItemManager::Equip(ItemManager::CreateWeapon("Dagger", CoreStats(), WEAPONSLOT::MELEE, 1, 3, false), &rogue));

    Monster monster1(10, 2, 4);

    while (monster1.HP.GetCurrent() > 0 && rogue.GetCurrentHP() > 0) {
      monster1.HP.ReduceCurrent(rogue.MeleeAttack());
      rogue.TakeDamage(monster1.Attack());
    }

    Assert::IsTrue((monster1.HP.GetCurrent() == 0) || (rogue.GetCurrentHP() == 0));

  }
};
}
