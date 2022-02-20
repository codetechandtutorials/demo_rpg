#include "pch.h"
#include "CppUnitTest.h"
#include "demo_rpg/playercharacter.h"
#include "demo_rpg/types.h"
#include "demo_rpg/item_manager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RPGSystemsUnitTest
{
TEST_CLASS(RPGSystemsUnitTest) {
public:

  TEST_METHOD(WarriorTest) {
    PlayerCharacter p1(new Warrior());
    Assert::AreEqual((int)Warrior::BASEHP, (int)p1.getMaxHP());

    p1.gainEXP(100u);
    Assert::AreEqual(2, (int)p1.getLevel());
    Assert::AreEqual(std::string("PowerAttack"), p1.getAbilityList().front().Name);
    Assert::AreEqual((int)(Warrior::BASEHP + (Warrior::BASEHP / 2.f)), (int)p1.getMaxHP());

  }

  TEST_METHOD(EquipTest) {
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
