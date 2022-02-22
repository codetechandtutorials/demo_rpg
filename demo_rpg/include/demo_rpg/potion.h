#pragma once
#include "types.h"
#include "buff.h"
#include "item.h"

class Potion final : public ItemDelegate {
public:
  welltype HealAmount;
  itemcount Quantity;
  const Buff* GetBuff() const;
  void SetBuff(Buff* new_buff);
private:
  Buff* _buff;
  Potion(std::string name, welltype hp_heal = 1u, itemcount quant = 1u, Buff* buf = nullptr);
  ~Potion();  // only ItemManger can clean this up
  friend class ItemManager;
};