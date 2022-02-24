#include "potion.h"

const Buff* Potion::GetBuff() const { return _buff; }
void Potion::SetBuff(Buff* new_buff) {
  if (_buff) {
    delete _buff;
    _buff = nullptr;
  }
  _buff = new_buff;
}

Potion::Potion(std::string name, welltype hp_heal, itemcount quant, Buff* buf)
  : ItemDelegate(name), _buff(buf), HealAmount(hp_heal), Quantity(quant) {
}
Potion::~Potion() {  // only ItemManger can clean this up
  if (_buff) {
    delete _buff;
    _buff = nullptr;
  }
}