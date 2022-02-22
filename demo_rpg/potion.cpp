#include "potion.h"

const Buff* Potion::GetBuff() const { return buff; }
void Potion::SetBuff(Buff* new_buff) {
  if (buff) {
    delete buff;
    buff = nullptr;
  }
  buff = new_buff;
}

Potion::Potion(std::string name, welltype hp_heal, itemcount quant, Buff* buf)
  : ItemDelegate(name), buff(buf), HealAmount(hp_heal), Quantity(quant) {
}
Potion::~Potion() {  // only ItemManger can clean this up
  if (buff) {
    delete buff;
    buff = nullptr;
  }
}